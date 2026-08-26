#!/usr/bin/env python3
"""Feature-cluster analysis for the ``call_sequence``/``unclassified`` catch-alls.

``tools/scan_asm_families.py::classify`` groups pragma-backed owners into a
small set of families for candidate generation.  Two of those families are
catch-alls: ``call_sequence`` (has calls, no backward branch, but does not
match any of the tighter shapes) and ``unclassified`` (none of the above).
Together they cover the large majority of remaining owners, which leaves
``sweep_targets.py`` with almost no ranking signal.

This tool extracts cheap structural features from each owner's ``.s`` and
buckets it into one of several candidate sub-family "shapes".  It is a
*reporting* tool: it never edits the classifier, it only prints a cluster
summary so a shape's size and evidence can be checked before it is promoted
into ``scan_asm_families.classify``.  The bucketing rules mirror the ones
promoted into ``classify`` (kept in sync by hand, not by import, since
``classify`` also has to interleave with every pre-existing family's rules).

Example:

    python3 tools/analyze_family_shapes.py --family call_sequence
    python3 tools/analyze_family_shapes.py --family unclassified --json out.json

The worktree's own ``disasm/asm/us/nonmatchings`` tree may be a partial
checkout (splat extraction not re-run locally).  ``--asm-fallback-root``
(auto-guessed for a ``.claude/worktrees/<name>`` layout) is consulted
read-only for any owner whose ``.s`` is missing locally; nothing is ever
written there.
"""

from __future__ import annotations

import argparse
import json
import statistics
from collections import Counter, defaultdict
from dataclasses import asdict, dataclass, field
from pathlib import Path

import scan_asm_families as scanner

REPO_ROOT = Path(__file__).resolve().parent.parent

FLOAT_MEM_OPS = {"lwc1", "swc1"}
FLOAT_ARITH_OPS = {"add.s", "sub.s", "mul.s", "div.s", "neg.s", "abs.s", "sqrt.s", "mov.s"}
MULT_DIV_OPS = {"mult", "multu", "div", "divu"}
BOOLEAN_RESULT_OPS = {"slt", "sltu", "slti", "sltiu", "xor", "xori"}
SAVED_REGS = {f"$s{i}" for i in range(9)} | {"$fp", "$ra"}


def _guess_asm_fallback_root() -> Path | None:
    """Read-only fallback root for a partially generated worktree asm tree.

    ``disasm/asm/us/nonmatchings`` is generated per-checkout; a fresh
    worktree may not have run splat extraction.  A owner's ``.s`` is
    deterministic from the ROM + yaml, so it is safe to read (never write)
    the same relative path from the checkout this worktree was branched
    from.  Mirrors ``s1_transfer_sweep._guess_gs_asm_fallback_root`` for the
    ``.claude/worktrees/<name>`` layout used by this agent harness.
    """
    parent = REPO_ROOT.parent
    if parent.name == "worktrees" and parent.parent.name == ".claude":
        candidate = parent.parent.parent
        if candidate.is_dir() and (candidate / "disasm" / "asm").is_dir():
            return candidate
    return None


def resolve_asm_path(asm_root: Path, fallback_root: Path | None, asm_rel: Path) -> Path | None:
    candidate = asm_root / asm_rel
    if candidate.exists():
        return candidate
    if fallback_root is not None:
        candidate = fallback_root / "disasm" / "asm" / "us" / "nonmatchings" / asm_rel
        if candidate.exists():
            return candidate
    return None


def source_owners_with_fallback(
    source_root: Path, asm_root: Path, fallback_root: Path | None
) -> list[tuple[str, Path, Path]]:
    """Same contract as ``scan_asm_families.source_owners``, with a fallback root."""
    owners: list[tuple[str, Path, Path]] = []
    for source_path in sorted(source_root.rglob("*.c")):
        if any(part.startswith(".pragma_probe_") for part in source_path.parts):
            continue
        text = source_path.read_text(encoding="utf-8", errors="replace")
        for match in scanner.PRAGMA_RE.finditer(text):
            asm_rel = Path(match.group(1))
            asm_path = resolve_asm_path(asm_root, fallback_root, asm_rel)
            if asm_path is not None:
                owners.append((asm_rel.stem, source_path, asm_path))
    return owners


def count_backward_branches(instructions: list[scanner.Instruction], labels: dict[str, int]) -> int:
    count = 0
    for index, instruction in enumerate(instructions):
        if instruction.op not in scanner.BRANCH_OPS:
            continue
        target = scanner.operand_tokens(instruction.operands)[-1:]
        if target and target[0] in labels and labels[target[0]] <= index:
            count += 1
    return count


def stack_frame_size(instructions: list[scanner.Instruction]) -> int | None:
    for instruction in instructions:
        if instruction.op != "addiu":
            continue
        tokens = scanner.operand_tokens(instruction.operands)
        if len(tokens) >= 3 and tokens[0] == "$sp" and tokens[1] == "$sp":
            value = scanner.parse_int(tokens[2])
            if value is not None and value < 0:
                return -value
    return None


def saved_register_count(instructions: list[scanner.Instruction]) -> int:
    count = 0
    for instruction in instructions:
        if instruction.op != "sw":
            continue
        tokens = scanner.operand_tokens(instruction.operands)
        if len(tokens) >= 2 and tokens[0] in SAVED_REGS and tokens[1].endswith("($sp)"):
            count += 1
    return count


def float_op_counts(instructions: list[scanner.Instruction]) -> tuple[int, int, int, int]:
    mem = arith = compare = cvt = 0
    for instruction in instructions:
        op = instruction.op
        if op in FLOAT_MEM_OPS:
            mem += 1
        elif op in FLOAT_ARITH_OPS:
            arith += 1
        elif op.startswith("c.") and op.endswith(".s"):
            compare += 1
        elif op.startswith("cvt.") or op in {"mtc1", "mfc1"}:
            cvt += 1
    return mem, arith, compare, cvt


def has_jr_register(instructions: list[scanner.Instruction]) -> bool:
    for instruction in instructions:
        if instruction.op != "jr":
            continue
        tokens = scanner.operand_tokens(instruction.operands)
        if tokens and tokens[0] != "$ra":
            return True
    return False


@dataclass
class Features:
    function: str
    source: str
    family_before: str
    instruction_count: int
    jal_count: int
    distinct_callees: int
    branch_count: int
    backward_branches: int
    has_jtbl: bool
    has_jr_reg: bool
    float_mem_ops: int
    float_arith_ops: int
    float_compare_ops: int
    float_cvt_ops: int
    stack_frame: int | None
    saved_regs: int
    global_stores: int
    narrow_accesses: int
    mult_div_ops: int
    self_recursion: bool
    all_calls_same_callee: bool
    boolean_result_ops: int
    shape: str = field(default="")


def extract_features(function: str, source_path: Path, asm_path: Path) -> Features:
    text = asm_path.read_text(encoding="utf-8", errors="replace")
    label, instructions, labels = scanner.parse_instructions(text)
    calls = scanner.extract_calls(instructions)
    globals_ = scanner.extract_globals(text)
    jump_tables = scanner.extract_jump_tables(text)
    accesses = scanner.extract_memory_accesses(instructions)
    bounds = scanner.extract_bounds(instructions)
    loops = scanner.has_loop(instructions, labels)
    family_before, _confidence, _notes = scanner.classify(
        instructions, calls, globals_, jump_tables, accesses, bounds, loops
    )
    mem, arith, compare, cvt = float_op_counts(instructions)
    narrow = sum(
        access.op in {"lb", "lbu", "lh", "lhu", "sb", "sh"} for access in accesses
    )
    global_stores = sum(
        access.symbol is not None and access.op in scanner.STORE_OPS for access in accesses
    )
    return Features(
        function=function,
        source=source_path.relative_to(REPO_ROOT).as_posix() if source_path.is_absolute() else source_path.as_posix(),
        family_before=family_before,
        instruction_count=len(instructions),
        jal_count=len(calls),
        distinct_callees=len(set(calls)),
        branch_count=sum(instruction.op in scanner.BRANCH_OPS for instruction in instructions),
        backward_branches=count_backward_branches(instructions, labels),
        has_jtbl=bool(jump_tables),
        has_jr_reg=has_jr_register(instructions),
        float_mem_ops=mem,
        float_arith_ops=arith,
        float_compare_ops=compare,
        float_cvt_ops=cvt,
        stack_frame=stack_frame_size(instructions),
        saved_regs=saved_register_count(instructions),
        global_stores=global_stores,
        narrow_accesses=narrow,
        mult_div_ops=sum(instruction.op in MULT_DIV_OPS for instruction in instructions),
        self_recursion=function in calls,
        all_calls_same_callee=len(calls) > 1 and len(set(calls)) == 1,
        boolean_result_ops=sum(instruction.op in BOOLEAN_RESULT_OPS for instruction in instructions),
    )


def classify_shape(features: Features) -> str:
    """Bucket a catch-all owner into a candidate sub-family.

    This mirrors (by hand, not by import) the rules promoted into
    ``scan_asm_families.classify``; see that function's comments for why the
    order matters and why some originally suggested shapes (``loop_over_table``,
    a jump-table-plus-loop ``state_machine``) never fire here: any owner with
    a backward branch is already claimed by the pre-existing
    ``loop_or_state_machine`` family before either catch-all is reached, so
    ``features.backward_branches`` and ``features.stack_frame``-driven loop
    shapes are always empty for this pool by construction.
    """
    instr = features.instruction_count
    calls = features.jal_count
    float_total = (
        features.float_mem_ops + features.float_arith_ops
        + features.float_compare_ops + features.float_cvt_ops
    )

    if features.has_jtbl:
        return "dispatcher_switch"
    if instr > 256:
        return "large_mixed"
    if calls == 0 and float_total >= 3:
        # A 3-component vector copy/scale/add is a multiple-of-3 pair of
        # lwc1/swc1 with little arithmetic; data shows only 2 such owners
        # remain unclaimed (most were already solved -- see AGENTS.md's
        # "three verified three-component float copy helpers" note), so it
        # is folded into float_math as a named sub-shape rather than kept as
        # its own top-level family.
        return "float_math"
    if calls == 0 and instr <= 32 and features.boolean_result_ops >= 1 and features.branch_count <= 3:
        return "predicate"
    if 1 <= calls <= 2 and features.branch_count == 0 and (features.global_stores + features.narrow_accesses) >= 2:
        return "init_sequence"
    if calls >= 3 and features.global_stores <= 1 and features.narrow_accesses <= 1:
        return "call_chain"
    if calls == 0 and features.branch_count >= 5:
        return "state_machine"
    if calls:
        return "call_sequence"
    return "unclassified"


def summarize(rows: list[Features]) -> dict[str, object]:
    by_shape: dict[str, list[Features]] = defaultdict(list)
    for row in rows:
        row.shape = classify_shape(row)
        by_shape[row.shape].append(row)
    summary: dict[str, object] = {}
    for shape, group in sorted(by_shape.items(), key=lambda item: -len(item[1])):
        counts = [item.instruction_count for item in group]
        summary[shape] = {
            "count": len(group),
            "median_instructions": statistics.median(counts),
            "p25_instructions": statistics.quantiles(counts, n=4)[0] if len(counts) >= 4 else min(counts),
            "p75_instructions": statistics.quantiles(counts, n=4)[2] if len(counts) >= 4 else max(counts),
            "with_jtbl": sum(1 for item in group if item.has_jtbl),
            "example_functions": [item.function for item in group[:5]],
        }
    return summary


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--source-root", type=Path, default=REPO_ROOT / "disasm" / "src")
    parser.add_argument("--asm-root", type=Path, default=REPO_ROOT / "disasm" / "asm" / "us" / "nonmatchings")
    parser.add_argument(
        "--asm-fallback-root",
        type=Path,
        default=None,
        help="read-only checkout root to fall back to for a missing .s (auto-guessed if omitted)",
    )
    parser.add_argument(
        "--no-fallback", action="store_true", help="disable the asm fallback root lookup"
    )
    parser.add_argument(
        "--family",
        action="append",
        dest="families",
        default=None,
        help="only analyze owners currently in this family (repeatable; default call_sequence,unclassified)",
    )
    parser.add_argument("--limit", type=int, default=0, help="limit scanned owners after filtering")
    parser.add_argument("--json", type=Path, help="write full per-owner feature rows to this path")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    fallback_root = None
    if not args.no_fallback:
        fallback_root = args.asm_fallback_root or _guess_asm_fallback_root()
    families = set(args.families) if args.families else {"call_sequence", "unclassified"}

    owners = source_owners_with_fallback(args.source_root, args.asm_root, fallback_root)
    rows: list[Features] = []
    for function, source_path, asm_path in owners:
        features = extract_features(function, source_path, asm_path)
        if features.family_before not in families:
            continue
        rows.append(features)
        if args.limit and len(rows) >= args.limit:
            break

    summary = summarize(rows)
    report = {
        "asm_fallback_root": str(fallback_root) if fallback_root else None,
        "owners_scanned": len(rows),
        "families_considered": sorted(families),
        "shape_summary": summary,
    }
    print(json.dumps(report, indent=2, default=str))
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(
            json.dumps([asdict(row) for row in rows], indent=2, default=str) + "\n",
            encoding="utf-8",
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
