#!/usr/bin/env python3
"""Scan US assembly owners and emit family-oriented candidate batches.

The scanner is deliberately conservative.  It does not claim to decompile a
function from instruction text.  Instead it records the structural evidence
that is useful when generating candidates (calls, globals, jump tables,
memory widths, bounds, and loops), and emits compile-ready candidates only for
simple wrapper and bounded-lookup shapes.

Example:

    python3 tools/scan_asm_families.py \
        --family bounded_lookup \
        --out-dir build/asm-family-batches

Each generated ``*.candidates.txt`` file is directly consumable by
``tools/try_pragma_compare.py --bundle``.  The accompanying manifest keeps
the unsupported or ambiguous owners visible for manual review.
"""

from __future__ import annotations

import argparse
import json
import re
from collections import defaultdict
from dataclasses import asdict, dataclass, field
from pathlib import Path
from typing import Iterable


PRAGMA_RE = re.compile(
    r'#pragma\s+GLOBAL_ASM\("asm/us/nonmatchings/([^"\n]+)"\)'
)
INSTRUCTION_RE = re.compile(
    r"/\*.*?\*/\s+([A-Za-z][A-Za-z0-9_.]*)\s*(.*?)\s*$"
)
LABEL_RE = re.compile(r"(?:glabel|jlabel)\s+([.A-Za-z_][A-Za-z0-9_.]*)")
GLOBAL_RE = re.compile(r"%(?:hi|lo)\(([^)]+)\)|\b(D_[0-9A-Fa-f]+)\b")
JUMP_TABLE_RE = re.compile(r"\b(jtbl_[0-9A-Fa-f]+)\b")
MEMORY_RE = re.compile(
    r"\b(lbu|lb|lhu|lh|lw|sb|sh|sw)\s+\$[^,]+,\s*((?:-?(?:0x[0-9A-Fa-f]+|\d+))|%lo\(([^)]+)\))\(\$([A-Za-z0-9]+)\)"
)
IMMEDIATE_RE = re.compile(r"(?<![A-Za-z0-9_])(-?(?:0x[0-9A-Fa-f]+|\d+))(?![A-Za-z0-9_])")

BRANCH_OPS = {
    "beq", "beql", "bne", "bnel", "beqz", "bnez", "bltz", "bltzl",
    "bgez", "bgezl", "blez", "blezl", "bgtz", "bgtzl", "b",
}
LOAD_OPS = {"lbu", "lb", "lhu", "lh", "lw"}
STORE_OPS = {"sb", "sh", "sw"}
SIMPLE_WRAPPER_OPS = {
    "addiu", "addu", "lui", "lw", "move", "nop", "ori", "or", "sw",
    "jal", "jr",
}
SIMPLE_LOOKUP_OPS = {
    "addiu", "addu", "andi", "lbu", "lb", "lhu", "lh", "lw", "lui",
    "move", "nop", "or", "sll", "sra", "srl", "slti", "sltiu", "slt",
    "beq", "beqz", "bne", "bnez", "bltz", "bgez", "beql", "bnel", "jr",
}


@dataclass
class Instruction:
    op: str
    operands: str
    line: int


@dataclass
class MemoryAccess:
    op: str
    offset: int | None
    base: str
    line: int
    symbol: str | None = None


@dataclass
class Owner:
    function: str
    source: str
    asm: str
    label: str
    family: str
    confidence: float
    instruction_count: int
    calls: list[str] = field(default_factory=list)
    globals: list[str] = field(default_factory=list)
    global_declarations: dict[str, str] = field(default_factory=dict)
    jump_tables: list[str] = field(default_factory=list)
    memory_accesses: list[MemoryAccess] = field(default_factory=list)
    bounds: list[int] = field(default_factory=list)
    branches: int = 0
    loops: bool = False
    candidate_codes: list[str] = field(default_factory=list)
    candidate_labels: list[str] = field(default_factory=list)
    notes: list[str] = field(default_factory=list)


def parse_int(token: str) -> int | None:
    token = token.strip()
    try:
        return int(token, 0)
    except ValueError:
        return None


def parse_instructions(text: str) -> tuple[str, list[Instruction], dict[str, int]]:
    label = ""
    instructions: list[Instruction] = []
    labels: dict[str, int] = {}
    for line_no, line in enumerate(text.splitlines(), 1):
        label_match = LABEL_RE.search(line)
        if label_match:
            current = label_match.group(1)
            if not label:
                label = current
            labels[current] = len(instructions)
        instruction_match = INSTRUCTION_RE.search(line)
        if instruction_match:
            instructions.append(
                Instruction(
                    op=instruction_match.group(1),
                    operands=instruction_match.group(2).strip(),
                    line=line_no,
                )
            )
    return label, instructions, labels


def operand_tokens(operands: str) -> list[str]:
    return [token.strip() for token in operands.split(",")]


def extract_calls(instructions: Iterable[Instruction]) -> list[str]:
    calls: list[str] = []
    for instruction in instructions:
        if instruction.op != "jal":
            continue
        target = operand_tokens(instruction.operands)
        if target:
            calls.append(target[-1])
    return calls


def extract_memory_accesses(instructions: Iterable[Instruction]) -> list[MemoryAccess]:
    accesses: list[MemoryAccess] = []
    for instruction in instructions:
        match = MEMORY_RE.search(f"{instruction.op} {instruction.operands}")
        if not match:
            continue
        offset = parse_int(match.group(2))
        accesses.append(
            MemoryAccess(
                op=match.group(1),
                offset=offset,
                base=match.group(4),
                line=instruction.line,
                symbol=match.group(3),
            )
        )
    return accesses


def extract_globals(text: str) -> list[str]:
    values: set[str] = set()
    for match in GLOBAL_RE.finditer(text):
        values.add(match.group(1) or match.group(2))
    return sorted(values)


def extract_jump_tables(text: str) -> list[str]:
    return sorted(set(JUMP_TABLE_RE.findall(text)))


def extract_bounds(instructions: Iterable[Instruction]) -> list[int]:
    bounds: list[int] = []
    for instruction in instructions:
        if instruction.op not in {"slti", "sltiu", "sltiu"}:
            continue
        tokens = operand_tokens(instruction.operands)
        if len(tokens) < 3:
            continue
        value = parse_int(tokens[2])
        if value is not None:
            bounds.append(value)
    return bounds


def has_loop(instructions: list[Instruction], labels: dict[str, int]) -> bool:
    for index, instruction in enumerate(instructions):
        if instruction.op not in BRANCH_OPS:
            continue
        target = operand_tokens(instruction.operands)[-1:]
        if target and target[0] in labels and labels[target[0]] <= index:
            return True
    return False


def classify(
    instructions: list[Instruction],
    calls: list[str],
    globals_: list[str],
    jump_tables: list[str],
    accesses: list[MemoryAccess],
    bounds: list[int],
    loops: bool,
) -> tuple[str, float, list[str]]:
    branches = sum(instruction.op in BRANCH_OPS for instruction in instructions)
    narrow_copy = sum(access.op in {"lbu", "lb", "lhu", "lh", "sb", "sh"} for access in accesses)
    stores = sum(access.op in STORE_OPS for access in accesses)
    notes: list[str] = []
    simple_wrapper_shape = all(instruction.op in SIMPLE_WRAPPER_OPS for instruction in instructions)
    non_stack_access = any(
        access.base != "sp" and access.symbol is None for access in accesses
    )
    global_stores = any(access.symbol is not None and access.op in STORE_OPS for access in accesses)

    if calls and loops and any(call in {"osRecvMesg", "osSendMesg"} for call in calls):
        return "queue_dma_loop", 0.92, ["queue call plus backward branch"]
    if calls and len(calls) >= 2 and not branches and len(instructions) <= 40 and simple_wrapper_shape and not non_stack_access:
        return "multi_call_wrapper", 0.90, ["short call sequence without control-flow branches"]
    if calls and len(calls) == 1 and not branches and len(instructions) <= 28 and simple_wrapper_shape and not non_stack_access and not global_stores:
        if narrow_copy >= 2 and stores:
            return "copy_worker", 0.88, ["narrow loads/stores surrounding one worker call"]
        return "direct_wrapper", 0.90, ["single call with epilogue-only control flow"]
    if not calls and jump_tables:
        return "jump_table_map", 0.90, ["computed jump through a rodata jump table"]
    if not calls and bounds and globals_ and any(access.op in LOAD_OPS for access in accesses):
        return "bounded_lookup", 0.88, ["range check, global table reference, and load"]
    if not calls and bounds and globals_ and stores:
        return "bounded_state_mutator", 0.84, ["range check and global narrow store"]
    if not calls and branches and not globals_:
        return "constant_map", 0.76, ["branch-only map with immediate results"]
    if not calls and globals_ and stores:
        return "state_field_access", 0.78, ["global field access with explicit stores"]
    if loops:
        return "loop_or_state_machine", 0.55, ["backward branch requires manual control-flow review"]
    if calls:
        notes.append("call shape is longer or contains branches")
        return "call_sequence", 0.52, notes
    return "unclassified", 0.30, ["no conservative family template matched"]


def source_owners(source_root: Path, asm_root: Path) -> list[tuple[str, Path, Path]]:
    """Return only pragma-backed owners, avoiding alias .s duplicates."""
    owners: list[tuple[str, Path, Path]] = []
    for source_path in sorted(source_root.rglob("*.c")):
        text = source_path.read_text(encoding="utf-8")
        source_rel = source_path.as_posix()
        for match in PRAGMA_RE.finditer(text):
            asm_rel = Path(match.group(1))
            asm_path = asm_root / asm_rel
            if asm_path.exists():
                owners.append((asm_rel.stem, source_path, asm_path))
    return owners


def find_arg_count(instructions: list[Instruction], call_index: int) -> int:
    values = re.findall(r"\$a([0-3])", " ".join(i.operands for i in instructions[:call_index]))
    return max((int(value) for value in values), default=-1) + 1


def instruction_immediate(instruction: Instruction) -> int | None:
    tokens = operand_tokens(instruction.operands)
    if len(tokens) < 3:
        return None
    return parse_int(tokens[2])


def extract_global_declarations(text: str) -> dict[str, str]:
    declarations: dict[str, str] = {}
    pattern = re.compile(
        r"(?m)(?:^|;)\s*(?:extern\s+)?(?P<type>(?:const\s+)?(?:u|s)(?:8|16|32|64)(?:\s*\*)?)\s*"
        r"(?P<name>D_[0-9A-Fa-f]+)\s*(?P<array>\[[^\]]*\])?\s*;"
    )
    for match in pattern.finditer(text):
        suffix = match.group("array") or ""
        declarations[match.group("name")] = (
            f"extern {match.group('type').strip()} {match.group('name')}{suffix};"
        )
    return declarations


def wrapper_candidates(owner: Owner, instructions: list[Instruction]) -> list[str]:
    if len(owner.calls) != 1:
        return []
    call_index = next((i for i, instruction in enumerate(instructions) if instruction.op == "jal"), -1)
    if call_index < 0:
        return []

    state = {f"$a{i}": f"arg{i}" for i in range(4)}
    state["$zero"] = "0"
    stack_args: dict[int, str] = {}
    touched_args = {
        int(value)
        for value in re.findall(
            r"\$a([0-3])", " ".join(i.operands for i in instructions[: call_index + 2])
        )
    }
    global_exprs: set[str] = set()
    # Include the branch-delay instruction: wrappers commonly prepare the
    # final $a0 value there (for example ``jal ...`` / ``addu $a0, ...``).
    setup_instructions = instructions[: call_index + 2]
    for instruction in setup_instructions:
        tokens = operand_tokens(instruction.operands)
        if len(tokens) < 2:
            continue
        if instruction.op == "sw":
            stack_match = re.match(r"(-?(?:0x[0-9A-Fa-f]+|\d+))\(\$sp\)", tokens[1])
            if stack_match and tokens[0] in state:
                offset = parse_int(stack_match.group(1))
                if offset is not None and offset >= 0x10 and offset % 4 == 0:
                    expression = state[tokens[0]]
                    if expression != "UNSUPPORTED":
                        stack_args[offset] = expression
            continue
        dest, source = tokens[0], tokens[1]
        third = tokens[2] if len(tokens) >= 3 else ""
        if instruction.op == "move" and source in state:
            state[dest] = state[source]
        elif instruction.op in {"or", "addu"} and len(tokens) >= 3 and third == "$zero" and source in state:
            state[dest] = state[source]
        elif instruction.op in {"addiu", "ori"} and source == "$zero":
            value = instruction_immediate(instruction)
            if value is not None:
                state[dest] = str(value)
            else:
                state[dest] = "UNSUPPORTED"
        elif instruction.op == "addiu" and source in state:
            global_match = re.search(r"%lo\((D_[0-9A-Fa-f]+)\)", instruction.operands)
            if global_match and state[source].startswith("&"):
                state[dest] = state[source]
            else:
                value = instruction_immediate(instruction)
                state[dest] = f"({state[source]} + {value})" if value is not None else "UNSUPPORTED"
        elif instruction.op == "lui":
            match = re.search(r"%hi\((D_[0-9A-Fa-f]+)\)", instruction.operands)
            state[dest] = f"&{match.group(1)}" if match else "UNSUPPORTED"
        elif instruction.op in {"lw", "lbu", "lb", "lhu", "lh"}:
            match = re.search(r"%lo\((D_[0-9A-Fa-f]+)\)", instruction.operands)
            if match:
                state[dest] = match.group(1)
                global_exprs.add(match.group(1))
            else:
                state[dest] = "UNSUPPORTED"
        else:
            state[dest] = "UNSUPPORTED"

    call_arg_count = max(touched_args, default=-1) + 1
    if call_arg_count == 0 or call_arg_count > 4:
        return []
    if stack_args:
        expected_offsets = list(range(0x10, max(stack_args) + 4, 4))
        if any(offset not in stack_args for offset in expected_offsets):
            owner.notes.append("stack argument layout has a gap; manual wrapper review needed")
            return []
    expressions = [state[f"$a{i}"] for i in range(call_arg_count)]
    expressions.extend(stack_args[offset] for offset in sorted(stack_args))
    if any(expression == "UNSUPPORTED" for expression in expressions):
        return []

    # Only emit wrappers whose result is not consumed after the call.  A
    # return-preserving wrapper needs a separate type/prototype decision.
    post_call = instructions[call_index + 2 :]
    if any("$v0" in instruction.operands for instruction in post_call):
        owner.notes.append("return value is consumed; manual return-type review needed")
        return []

    arg_indices = [
        int(value)
        for expression in expressions
        for value in re.findall(r"\barg([0-3])\b", expression)
    ]
    arg_count = max(arg_indices, default=-1) + 1
    if any(
        expression.startswith("&") or expression.startswith("D_")
        for expression in expressions
    ):
        global_exprs.update(
            expression.lstrip("&")
            for expression in expressions
            if expression.lstrip("&").startswith("D_")
        )

    args = ", ".join(expressions)
    declarations = [owner.global_declarations[name] for name in sorted(global_exprs) if name in owner.global_declarations]
    for name in sorted(global_exprs):
        if name not in owner.global_declarations:
            declarations.append(f"extern u32 {name};")
    prefix = "\n".join(declarations)

    candidates: list[str] = []
    labels: list[str] = []
    type_variants = [("void", "s32"), ("s32", "s32"), ("u32", "s32"),
                     ("void", "u32"), ("s32", "u32"), ("u32", "u32")]
    if global_exprs:
        type_variants.extend([("void", "void *"), ("s32", "void *")])
    for return_type, parameter_type in type_variants:
        # The wrapper's own parameters are still ordinary register-sized
        # values.  A loaded global, however, is commonly a pointer; declaring
        # that callee argument as ``s32`` makes the generated candidate fail
        # before comparison.  Keep those types independent in the matrix.
        parameters = ", ".join(
            f"{parameter_type} arg{i}" for i in range(arg_count)
        ) or "void"
        callee_types = []
        for expression in expressions:
            if expression.startswith("&") or expression.startswith("D_"):
                declaration = owner.global_declarations.get(expression.lstrip("&"), "")
                callee_types.append("void *" if ("*" in declaration or "[" in declaration or not declaration) else parameter_type)
            else:
                callee_types.append(parameter_type)
        prototype = ", ".join(callee_types)
        body = f"{owner.calls[0]}({args});" if return_type == "void" else f"return {owner.calls[0]}({args});"
        declaration = f"extern {return_type} {owner.calls[0]}({prototype});"
        code = f"{prefix + chr(10) if prefix else ''}{declaration}\n{return_type} {owner.function}({parameters}) {{ {body} }}"
        candidates.append(code)
        labels.append(f"wrapper-{return_type.replace(' ', '_')}-{parameter_type.replace(' ', '_')}")
    owner.candidate_labels = labels
    return candidates


def bounded_lookup_candidates(owner: Owner, instructions: list[Instruction]) -> list[str]:
    if not owner.bounds or not owner.globals:
        owner.notes.append("auto lookup translation suppressed: missing bound or global evidence")
        return []
    global_name = next(
        (
            access.symbol
            for access in owner.memory_accesses
            if access.op in LOAD_OPS and access.symbol and access.symbol.startswith("D_")
        ),
        next((value for value in owner.globals if value.startswith("D_")), None),
    )
    if global_name is None:
        owner.notes.append("auto lookup translation suppressed: no direct D_ global")
        return []

    # A family label is intentionally broad, but generated C is limited to a
    # short single-table lookup.  This prevents a long state machine that
    # happens to contain a bound and a global from producing misleading code.
    if (
        owner.instruction_count > 32
        or owner.branches > 4
        or any(instruction.op not in SIMPLE_LOOKUP_OPS for instruction in instructions)
        or any(access.op in STORE_OPS for access in owner.memory_accesses)
    ):
        owner.notes.append(
            "auto lookup translation suppressed: control flow or side effects exceed the simple-table shape"
        )
        return []
    bound_instruction = next(
        (
            instruction
            for instruction in instructions
            if instruction.op in {"slti", "sltiu"}
            and len(operand_tokens(instruction.operands)) >= 3
            and operand_tokens(instruction.operands)[1] == "$a0"
        ),
        None,
    )
    global_loads = [
        access for access in owner.memory_accesses
        if access.op in LOAD_OPS and access.symbol == global_name
    ]
    if bound_instruction is None or len(global_loads) != 1:
        owner.notes.append(
            "auto lookup translation suppressed: index register or one-table-load evidence is incomplete"
        )
        return []
    bound = owner.bounds[0]
    has_negative_check = any(instruction.op.startswith("bltz") for instruction in instructions)
    if bound_instruction.op == "sltiu":
        conditions = [f"(u32)arg0 < {bound}"]
    elif has_negative_check:
        conditions = [f"arg0 >= 0 && arg0 < {bound}"]
    else:
        conditions = [f"arg0 < {bound}", f"arg0 >= 0 && arg0 < {bound}"]

    shift = 0
    stride = 1
    for instruction in instructions:
        tokens = operand_tokens(instruction.operands)
        if instruction.op == "sll" and len(tokens) >= 3 and tokens[1] == "$a0":
            parsed = parse_int(tokens[2])
            if parsed is not None:
                shift = parsed
                stride = 1 << parsed
                break

    load = global_loads[0]
    type_info = {
        "lw": ("s32", "s32"),
        "lbu": ("u8", "u8"),
        "lb": ("s8", "s8"),
        "lhu": ("u16", "u16"),
        "lh": ("s16", "s16"),
    }
    result_type, element_type = type_info[load.op]
    known_declaration = owner.global_declarations.get(global_name)
    if known_declaration:
        base = global_name if ("*" in known_declaration or "[" in known_declaration) else f"&{global_name}"
        declarations = [known_declaration]
    else:
        base = global_name
        declarations = []

    candidates: list[str] = []
    labels: list[str] = []
    index_forms = ["arg0", "(u32)arg0"] if not has_negative_check else ["arg0"]
    expression_forms: list[tuple[str, str]] = []
    if stride == 1 and not known_declaration:
        expression_forms.append((f"{global_name}[INDEX]", f"extern {element_type} {global_name}[];"))
    elif stride == 1:
        expression_forms.append((f"*((({element_type} *){base}) + INDEX)", ""))
    expression_forms.append(
        (
            f"*(({element_type} *)((u8 *){base} + INDEX * {stride}))",
            "" if known_declaration else f"extern u8 {global_name}[];",
        )
    )
    for condition in conditions:
        for index in index_forms:
            for expression_template, declaration in expression_forms:
                expression = expression_template.replace("INDEX", index)
                declaration_lines = declarations + ([declaration] if declaration else [])
                prefix = "\n".join(dict.fromkeys(declaration_lines))
                body = (
                    f"{result_type} result = 0; if ({condition}) result = {expression}; return result;"
                )
                code = f"{prefix + chr(10) if prefix else ''}{result_type} {owner.function}(s32 arg0) {{ {body} }}"
                candidates.append(code)
                labels.append(f"lookup-init-{condition.replace(' ', '_')}-{index.replace('(', '').replace(')', '')}-{len(candidates)}")
                ternary = f"return ({condition}) ? {expression} : 0;"
                code = f"{prefix + chr(10) if prefix else ''}{result_type} {owner.function}(s32 arg0) {{ {ternary} }}"
                candidates.append(code)
                labels.append(f"lookup-ternary-{condition.replace(' ', '_')}-{index.replace('(', '').replace(')', '')}-{len(candidates)}")
    owner.candidate_labels = labels[:10]
    return candidates[:10]


def generate_candidates(owner: Owner, instructions: list[Instruction]) -> list[str]:
    if owner.family in {"direct_wrapper", "multi_call_wrapper"}:
        return wrapper_candidates(owner, instructions)
    if owner.family == "bounded_lookup":
        return bounded_lookup_candidates(owner, instructions)
    owner.notes.append("family detected; no automatic C translation emitted")
    return []


def build_owner(function: str, source_path: Path, asm_path: Path, asm_root: Path) -> Owner:
    text = asm_path.read_text(encoding="utf-8")
    source_text = source_path.read_text(encoding="utf-8")
    label, instructions, labels = parse_instructions(text)
    calls = extract_calls(instructions)
    globals_ = extract_globals(text)
    jump_tables = extract_jump_tables(text)
    accesses = extract_memory_accesses(instructions)
    bounds = extract_bounds(instructions)
    loops = has_loop(instructions, labels)
    family, confidence, notes = classify(
        instructions, calls, globals_, jump_tables, accesses, bounds, loops
    )
    owner = Owner(
        function=function,
        source=source_path.relative_to(Path.cwd()).as_posix(),
        asm=asm_path.relative_to(Path.cwd()).as_posix(),
        label=label,
        family=family,
        confidence=confidence,
        instruction_count=len(instructions),
        calls=calls,
        globals=globals_,
        global_declarations=extract_global_declarations(source_text),
        jump_tables=jump_tables,
        memory_accesses=accesses,
        bounds=bounds,
        branches=sum(instruction.op in BRANCH_OPS for instruction in instructions),
        loops=loops,
        notes=notes,
    )
    owner.candidate_codes = generate_candidates(owner, instructions)
    return owner


def json_owner(owner: Owner) -> dict:
    value = asdict(owner)
    # Declarations are an internal candidate-generation aid; the manifest
    # already records the referenced globals and should not repeat every
    # declaration in a large source file for every owner.
    value.pop("global_declarations", None)
    value["memory_accesses"] = [asdict(item) for item in owner.memory_accesses]
    return value


def render_bundle(owners: list[Owner]) -> str:
    lines = [
        "/* Generated by tools/scan_asm_families.py. Review before running. */",
        "/* Candidates are ordered per function; the runner keeps the first winner. */",
        "",
    ]
    for owner in owners:
        labels = owner.candidate_labels or [f"variant-{i + 1}" for i in range(len(owner.candidate_codes))]
        for candidate_index, candidate in enumerate(owner.candidate_codes):
            label = labels[candidate_index] if candidate_index < len(labels) else f"variant-{candidate_index + 1}"
            lines.extend(
                [
                    f"/* family: {owner.family}; variant: {label}; asm: {owner.asm}; calls: {','.join(owner.calls)} */",
                    f"/* candidate: {owner.function} */",
                    candidate,
                    "/* end candidate */",
                    "",
                ]
            )
    return "\n".join(lines)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--asm-root", type=Path, default=Path("disasm/asm/us/nonmatchings"))
    parser.add_argument("--source-root", type=Path, default=Path("disasm/src"))
    parser.add_argument("--out-dir", type=Path, default=Path("build/asm-family-batches"))
    parser.add_argument("--family", help="Only emit this detected family")
    parser.add_argument("--source", help="Only scan owners from this source path")
    parser.add_argument("--limit", type=int, default=0, help="Limit scanned owners after filtering")
    return parser.parse_args()


def display_path(path: Path) -> str:
    try:
        return path.relative_to(Path.cwd()).as_posix()
    except ValueError:
        return path.as_posix()


def main() -> int:
    args = parse_args()
    asm_root = args.asm_root.resolve()
    source_root = args.source_root.resolve()
    out_dir = args.out_dir.resolve()
    out_dir.mkdir(parents=True, exist_ok=True)

    owners: list[Owner] = []
    for function, source_path, asm_path in source_owners(source_root, asm_root):
        source_rel = source_path.relative_to(Path.cwd()).as_posix()
        if args.source and source_rel != args.source:
            continue
        owner = build_owner(function, source_path, asm_path, asm_root)
        owners.append(owner)

    if args.family:
        owners = [owner for owner in owners if owner.family == args.family]
    owners.sort(key=lambda owner: (owner.source, owner.family, owner.function))
    if args.limit > 0:
        owners = owners[: args.limit]

    groups: dict[tuple[str, str], list[Owner]] = defaultdict(list)
    for owner in owners:
        if owner.candidate_codes:
            groups[(owner.source, owner.family)].append(owner)

    bundles: list[dict[str, object]] = []
    for (source, family), group in sorted(groups.items()):
        source_key = re.sub(r"[^A-Za-z0-9_.-]+", "_", source.removesuffix(".c"))
        bundle_path = out_dir / f"{source_key}.{family}.candidates.txt"
        bundle_path.write_text(render_bundle(group), encoding="utf-8")
        bundles.append(
            {
                "source": source,
                "family": family,
                "bundle": display_path(bundle_path),
                "functions": [owner.function for owner in group],
                "candidate_count": sum(len(owner.candidate_codes) for owner in group),
            }
        )

    manifest = {
        "schema": 2,
        "tool": "scan_asm_families.py",
        "owners": [json_owner(owner) for owner in owners],
        "bundles": bundles,
    }
    manifest_path = out_dir / "manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    print(json.dumps({"owners": len(owners), "bundles": bundles, "manifest": display_path(manifest_path)}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
