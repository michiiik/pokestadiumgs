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
    r"\b(lbu|lb|lhu|lh|lw|sb|sh|sw)\s+\$[^,]+,\s*(-?(?:0x[0-9A-Fa-f]+|\d+))\(\$([A-Za-z0-9]+)\)"
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


@dataclass
class Instruction:
    op: str
    operands: str
    line: int


@dataclass
class MemoryAccess:
    op: str
    offset: int
    base: str
    line: int


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
    jump_tables: list[str] = field(default_factory=list)
    memory_accesses: list[MemoryAccess] = field(default_factory=list)
    bounds: list[int] = field(default_factory=list)
    branches: int = 0
    loops: bool = False
    candidate_codes: list[str] = field(default_factory=list)
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
        if offset is None:
            continue
        accesses.append(
            MemoryAccess(
                op=match.group(1),
                offset=offset,
                base=match.group(3),
                line=instruction.line,
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
    non_stack_access = any(access.base != "sp" for access in accesses)

    if calls and loops and any(call in {"osRecvMesg", "osSendMesg"} for call in calls):
        return "queue_dma_loop", 0.92, ["queue call plus backward branch"]
    if calls and len(calls) >= 2 and not branches and len(instructions) <= 40 and simple_wrapper_shape and not non_stack_access:
        return "multi_call_wrapper", 0.90, ["short call sequence without control-flow branches"]
    if calls and len(calls) == 1 and not branches and len(instructions) <= 28 and simple_wrapper_shape and not non_stack_access:
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


def wrapper_candidates(owner: Owner, instructions: list[Instruction]) -> list[str]:
    if len(owner.calls) != 1:
        return []
    call_index = next((i for i, instruction in enumerate(instructions) if instruction.op == "jal"), -1)
    if call_index < 0:
        return []

    state = {f"$a{i}": f"arg{i}" for i in range(4)}
    constant_destinations: list[int] = []
    # Include the branch-delay instruction: wrappers commonly prepare the
    # final $a0 value there (for example ``jal ...`` / ``addu $a0, ...``).
    setup_instructions = instructions[: call_index + 2]
    for instruction in setup_instructions:
        tokens = operand_tokens(instruction.operands)
        if len(tokens) < 3:
            continue
        dest, source, third = tokens[0], tokens[1], tokens[2]
        if dest not in state:
            continue
        if instruction.op in {"or", "addu"} and third == "$zero" and source in state:
            state[dest] = state[source]
        elif instruction.op in {"addiu", "ori"} and source == "$zero":
            value = instruction_immediate(instruction)
            if value is not None:
                state[dest] = str(value)
                constant_destinations.append(int(dest[-1]) + 1)
            else:
                state[dest] = "UNSUPPORTED"
        else:
            state[dest] = "UNSUPPORTED"

    arg_count = find_arg_count(setup_instructions, len(setup_instructions))
    call_arg_count = max([arg_count, *constant_destinations], default=0)
    if call_arg_count == 0 or call_arg_count > 4:
        return []
    expressions = [state[f"$a{i}"] for i in range(call_arg_count)]
    if any(expression == "UNSUPPORTED" for expression in expressions):
        return []

    # Only emit wrappers whose result is not consumed after the call.  A
    # return-preserving wrapper needs a separate type/prototype decision.
    post_call = instructions[call_index + 2 :]
    if any("$v0" in instruction.operands for instruction in post_call):
        owner.notes.append("return value is consumed; manual return-type review needed")
        return []

    parameters = ", ".join(f"s32 arg{i}" for i in range(arg_count))
    prototype = ", ".join("s32" for _ in range(call_arg_count))
    args = ", ".join(expressions)
    return [
        f"extern void {owner.calls[0]}({prototype});\n"
        f"void {owner.function}({parameters}) {{ {owner.calls[0]}({args}); }}"
    ]


def bounded_lookup_candidates(owner: Owner, instructions: list[Instruction]) -> list[str]:
    if not owner.bounds or not owner.globals:
        return []
    global_name = next((value for value in owner.globals if value.startswith("D_")), None)
    if global_name is None:
        return []
    bound = owner.bounds[0]
    signed = any(instruction.op.startswith("bltz") for instruction in instructions)
    condition = f"arg0 >= 0 && arg0 < {bound}" if signed else f"(u32)arg0 < {bound}"

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

    load = next((access for access in owner.memory_accesses if access.op in LOAD_OPS), None)
    if load is not None:
        type_info = {
            "lw": ("s32", "s32"),
            "lbu": ("u8", "u8"),
            "lb": ("s8", "s8"),
            "lhu": ("u16", "u16"),
            "lh": ("s16", "s16"),
        }
        result_type, element_type = type_info[load.op]
        if stride == 1:
            expression = f"{global_name}[arg0]"
            declaration = f"extern {element_type} {global_name}[];"
        else:
            expression = f"*(({element_type} *)((u8 *){global_name} + arg0 * {stride}))"
            declaration = f"extern u8 {global_name}[];"
        return [
            f"{declaration}\n{result_type} {owner.function}(s32 arg0) {{ "
            f"{result_type} result = 0; if ({condition}) result = {expression}; return result; }}"
        ]

    # A bounded address calculation with no load is the pointer-return form.
    if stride <= 0:
        return []
    return [
        f"extern u8 {global_name}[];\n"
        f"u8 *{owner.function}(s32 arg0) {{ u8 *result = NULL; "
        f"if ({condition}) result = {global_name} + arg0 * {stride}; return result; }}"
    ]


def generate_candidates(owner: Owner, instructions: list[Instruction]) -> list[str]:
    if owner.family in {"direct_wrapper", "multi_call_wrapper"}:
        return wrapper_candidates(owner, instructions)
    if owner.family == "bounded_lookup":
        return bounded_lookup_candidates(owner, instructions)
    owner.notes.append("family detected; no automatic C translation emitted")
    return []


def build_owner(function: str, source_path: Path, asm_path: Path, asm_root: Path) -> Owner:
    text = asm_path.read_text(encoding="utf-8")
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
    value["memory_accesses"] = [asdict(item) for item in owner.memory_accesses]
    return value


def render_bundle(owners: list[Owner]) -> str:
    lines = [
        "/* Generated by tools/scan_asm_families.py. Review before running. */",
        "/* Candidates are ordered per function; the runner keeps the first winner. */",
        "",
    ]
    for owner in owners:
        for candidate in owner.candidate_codes:
            lines.extend(
                [
                    f"/* family: {owner.family}; asm: {owner.asm}; calls: {','.join(owner.calls)} */",
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
        "schema": 1,
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
