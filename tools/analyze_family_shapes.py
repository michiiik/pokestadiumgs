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
import re
import statistics
import sys
from collections import Counter, defaultdict
from dataclasses import asdict, dataclass, field
from pathlib import Path

import pragma_targets
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


def owners_for_source(
    source_path: Path, asm_root: Path, fallback_root: Path | None
) -> list[tuple[str, Path, Path]]:
    """Remaining pragma owners of a single tracked source file, with a fallback root."""
    text = source_path.read_text(encoding="utf-8", errors="replace")
    owners: list[tuple[str, Path, Path]] = []
    for match in scanner.PRAGMA_RE.finditer(text):
        asm_rel = Path(match.group(1))
        asm_path = resolve_asm_path(asm_root, fallback_root, asm_rel)
        if asm_path is not None:
            owners.append((asm_rel.stem, source_path, asm_path))
    return owners


def source_owners_with_fallback(
    source_root: Path, asm_root: Path, fallback_root: Path | None
) -> list[tuple[str, Path, Path]]:
    """Same contract as ``scan_asm_families.source_owners``, with a fallback root."""
    owners: list[tuple[str, Path, Path]] = []
    for source_path in sorted(source_root.rglob("*.c")):
        if any(part.startswith(".pragma_probe_") for part in source_path.parts):
            continue
        owners.extend(owners_for_source(source_path, asm_root, fallback_root))
    return owners


def display_relpath(path: Path) -> str:
    try:
        return path.resolve().relative_to(REPO_ROOT).as_posix()
    except ValueError:
        return path.as_posix()


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


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
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
    return parser.parse_args(argv)


def main_shapes(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
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


# ---------------------------------------------------------------------------
# ``siblings`` / ``unlock``: deliberate family-unlock hunting.
#
# A fleet wave on 2026-08-28 found by accident that six of twelve accepts in
# ``4AC10.c`` shared one spelling (the ``gbi.h`` display-list macros) because
# they were siblings -- near-identical opcode shapes calling the same helper.
# The tools below make that discoverable on purpose: cluster a file's (or the
# whole tree's) remaining pragma owners by opcode shape, so an agent's first
# job is "solve one member of the largest group, then batch its siblings with
# the same spelling" instead of stumbling into it after the fact.
# ---------------------------------------------------------------------------

# The Gfx command-word pointer every display-list append macro
# (``gSPDisplayList``/``gDPSetFillColor``/``gDPFillRectangle``, see AGENTS.md
# S4 "Display-list append") increments through, plus the RDP command
# constants (``G_SETFILLCOLOR``/``G_FILLRECT``/``G_ENDDL``/``G_TEXRECT``/
# ``G_SETTILE``/``G_LOADBLOCK``/``G_SETTILESIZE``-family opcode bytes) those
# macros emit into the high half-word of the first or second command word.
GBI_POINTER_SYMBOL = "D_800D0510"
GBI_CONSTANT_RE = re.compile(
    r"0x(?:DB060038|DA380000|DE000000|E7000000|F7000000"
    r"|FD[0-9A-Fa-f]{6}|F5[0-9A-Fa-f]{6}|F3[0-9A-Fa-f]{6})"
)
GBI_MACRO_HINT = (
    "gbi.h macros (gSPDisplayList/gDPSetFillColor/gDPFillRectangle) writing "
    "into D_800D0510++, not hand-written words.w0/w1 stores -- see AGENTS.md "
    "S4 'Display-list append'"
)

# Two shapes at similarity 1.0 with different registers are usually the same
# hand-decompilation spelling with a register-allocation tie (see AGENTS.md
# S2.5's "near-miss" guidance); 0.15 keeps a group tight enough that its
# members are plausibly the same C spelling rather than merely the same
# family, while still absorbing a handful of scheduling differences.
SIBLING_DISTANCE_THRESHOLD = 0.15


def is_gbi_macro_asm(asm_text: str) -> bool:
    return GBI_POINTER_SYMBOL in asm_text or bool(GBI_CONSTANT_RE.search(asm_text))


def shape_signature(instructions: list[scanner.Instruction]) -> list[str]:
    """Abstract an owner's assembly into an opcode-shape token sequence.

    Registers and immediates are dropped (two owners differing only in which
    temp register IDO picked, or in a literal offset, are the same shape).
    A ``jal`` keeps its target name as part of the token instead of being
    abstracted to a bare ``jal``, because siblings usually call the same
    helper -- that is the signal this tool is built to surface. A run of
    consecutive ``sw`` (or ``lw``) instructions collapses to one token: the
    number of fields a display-list/record constructor happens to touch is
    not part of its shape.
    """
    tokens: list[str] = []
    for instruction in instructions:
        if instruction.op == "jal":
            targets = scanner.operand_tokens(instruction.operands)
            token = f"jal:{targets[-1]}" if targets else "jal"
        else:
            token = instruction.op
        if token in ("sw", "lw") and tokens and tokens[-1] == token:
            continue
        tokens.append(token)
    return tokens


def edit_distance(a: list[str], b: list[str]) -> int:
    """Levenshtein distance over token sequences (insert/delete/substitute)."""
    if a == b:
        return 0
    n, m = len(a), len(b)
    if n == 0:
        return m
    if m == 0:
        return n
    previous = list(range(m + 1))
    for i in range(1, n + 1):
        current = [i] + [0] * m
        ai = a[i - 1]
        for j in range(1, m + 1):
            cost = 0 if ai == b[j - 1] else 1
            current[j] = min(
                previous[j] + 1,  # deletion
                current[j - 1] + 1,  # insertion
                previous[j - 1] + cost,  # substitution / match
            )
        previous = current
    return previous[m]


def normalized_distance(a: list[str], b: list[str]) -> float:
    if not a and not b:
        return 0.0
    return edit_distance(a, b) / max(len(a), len(b), 1)


@dataclass
class SiblingOwner:
    function: str
    source: str
    asm: str
    instruction_count: int
    tokens: list[str] = field(default_factory=list)
    calls: set[str] = field(default_factory=set)
    gbi_macro: bool = False


def build_sibling_owner(function: str, source_path: Path, asm_path: Path) -> SiblingOwner:
    text = asm_path.read_text(encoding="utf-8", errors="replace")
    _, instructions, _ = scanner.parse_instructions(text)
    return SiblingOwner(
        function=function,
        source=display_relpath(source_path),
        asm=display_relpath(asm_path),
        instruction_count=len(instructions),
        tokens=shape_signature(instructions),
        calls=set(scanner.extract_calls(instructions)),
        gbi_macro=is_gbi_macro_asm(text),
    )


@dataclass
class SiblingGroup:
    group_id: int
    members: list[SiblingOwner]
    shared_jal_targets: list[str]
    gbi_macro: bool
    closest_solved: dict[str, object] | None = None

    @property
    def size(self) -> int:
        return len(self.members)

    @property
    def instruction_range(self) -> tuple[int, int]:
        counts = [member.instruction_count for member in self.members]
        return (min(counts), max(counts))


def cluster_siblings(
    owners: list[SiblingOwner], threshold: float = SIBLING_DISTANCE_THRESHOLD
) -> list[SiblingGroup]:
    """Group owners whose shape signatures are identical or within ``threshold``.

    Greedy nearest-cluster assignment (each owner joins its closest existing
    cluster if within threshold, else starts a new one) rather than
    union-find: a transitive chain (A close to B, B close to C, A far from C)
    would otherwise merge unrelated shapes into one group, which defeats the
    point of a spelling-hunting tool.
    """
    clusters: list[dict[str, object]] = []
    for owner in sorted(owners, key=lambda item: item.function):
        best_index: int | None = None
        best_distance: float | None = None
        for index, cluster in enumerate(clusters):
            distance = normalized_distance(owner.tokens, cluster["representative"])
            if distance <= threshold and (best_distance is None or distance < best_distance):
                best_index, best_distance = index, distance
        if best_index is not None:
            clusters[best_index]["members"].append(owner)
        else:
            clusters.append({"representative": owner.tokens, "members": [owner]})

    groups: list[SiblingGroup] = []
    for cluster in clusters:
        members: list[SiblingOwner] = cluster["members"]
        shared: set[str] | None = None
        for member in members:
            shared = set(member.calls) if shared is None else shared & member.calls
        groups.append(
            SiblingGroup(
                group_id=0,
                members=sorted(members, key=lambda item: item.function),
                shared_jal_targets=sorted(shared or set()),
                gbi_macro=any(member.gbi_macro for member in members),
            )
        )
    groups.sort(key=lambda group: (-group.size, group.members[0].function))
    for index, group in enumerate(groups, start=1):
        group.group_id = index
    return groups


_FUNCTION_LOCATION_CACHE: dict[str, str] | None = None
FUNCTION_DEFINITION_RE = re.compile(
    r"(?m)^\s*(?:static\s+)?(?:const\s+)?(?:void|[us](?:8|16|32|64))(?:\s*\*)?\s+"
    r"(func_[0-9A-Fa-f]+)\s*\([^;{]*\)\s*\{"
)


def build_function_locations(source_root: Path | None = None) -> dict[str, str]:
    """Map every already-decompiled ``func_*`` definition to its source file.

    Used only to annotate a "closest solved" match with the file an agent
    should open next; a function this misses (an unusual multi-line
    signature) simply shows ``"?"`` for its source, never a wrong file.
    """
    global _FUNCTION_LOCATION_CACHE
    if _FUNCTION_LOCATION_CACHE is not None and source_root is None:
        return _FUNCTION_LOCATION_CACHE
    root = source_root or (REPO_ROOT / "disasm" / "src")
    locations: dict[str, str] = {}
    for source_path in sorted(root.rglob("*.c")):
        if any(part.startswith(".pragma_probe_") for part in source_path.parts):
            continue
        text = source_path.read_text(encoding="utf-8", errors="replace")
        for match in FUNCTION_DEFINITION_RE.finditer(text):
            locations.setdefault(match.group(1), display_relpath(source_path))
    if source_root is None:
        _FUNCTION_LOCATION_CACHE = locations
    return locations


_SOLVED_SIGNATURE_CACHE: dict[str, dict[str, object]] | None = None


def _stats_path_override(fallback_root: Path | None) -> Path | None:
    """A worktree's own probe-stats file is usually absent (gitignored,
    per-checkout process memory); AGENTS.md SS1.2 says worktrees fall back
    read-only to the sibling checkout for probe stats, same as ``disasm/asm``.
    """
    if pragma_targets.probe_stats.DEFAULT_STATS_PATH.exists():
        return None
    if fallback_root is None:
        return None
    candidate = fallback_root / "disasm" / "probe-stats" / "probe-stats.jsonl"
    return candidate if candidate.exists() else None


def build_solved_index(
    asm_root: Path, fallback_root: Path | None, source_root: Path | None = None
) -> dict[str, dict[str, object]]:
    """Shape signature + source file for every accepted (already-solved) owner.

    Cached for the process lifetime: this reads the whole probe-stats history
    once, which is the expensive part of "closest solved", and every caller
    in one run (a single file's siblings report or the tree-wide ``--all``
    walk) asks with the same ``asm_root``/``fallback_root``.
    """
    global _SOLVED_SIGNATURE_CACHE
    if _SOLVED_SIGNATURE_CACHE is not None:
        return _SOLVED_SIGNATURE_CACHE

    asm_roots = [asm_root]
    if fallback_root is not None:
        asm_roots.append(fallback_root / "disasm" / "asm" / "us" / "nonmatchings")
    stats_override = _stats_path_override(fallback_root)
    rows = pragma_targets.solved_shapes(stats_path=stats_override, asm_roots=asm_roots)

    asm_index: dict[str, Path] = {}
    for root in asm_roots:
        if not root.is_dir():
            continue
        for path in root.rglob("*.s"):
            asm_index.setdefault(path.stem, path)

    locations = build_function_locations(source_root)
    index: dict[str, dict[str, object]] = {}
    for row in rows:
        function = str(row["function"])
        asm_path = asm_index.get(function)
        if asm_path is None:
            continue
        text = asm_path.read_text(encoding="utf-8", errors="replace")
        _, instructions, _ = scanner.parse_instructions(text)
        index[function] = {
            "tokens": shape_signature(instructions),
            "source": locations.get(function, "?"),
        }
    _SOLVED_SIGNATURE_CACHE = index
    return index


def find_closest_solved(
    group: SiblingGroup, solved_index: dict[str, dict[str, object]]
) -> dict[str, object] | None:
    """The nearest already-accepted spelling to any member of ``group``.

    Its spelling is the first variant worth trying on the group's easiest
    member, per the coordinator's "solve one, batch its siblings" workflow.
    """
    member_names = {member.function for member in group.members}
    best: tuple[str, float, str] | None = None
    for name, row in solved_index.items():
        if name in member_names:
            continue
        tokens = row["tokens"]
        if not isinstance(tokens, list) or not tokens:
            continue
        for member in group.members:
            distance = normalized_distance(member.tokens, tokens)
            if best is None or distance < best[1]:
                best = (name, distance, str(row["source"]))
    if best is None:
        return None
    name, distance, source = best
    return {"function": name, "source": source, "distance": round(distance, 3)}


def group_to_dict(group: SiblingGroup) -> dict[str, object]:
    low, high = group.instruction_range
    return {
        "group_id": group.group_id,
        "size": group.size,
        "instruction_range": [low, high],
        "shared_jal_targets": group.shared_jal_targets,
        "gbi_macro": group.gbi_macro,
        "suggested_spelling": GBI_MACRO_HINT if group.gbi_macro else None,
        "members": [member.function for member in group.members],
        "closest_solved": group.closest_solved,
    }


def _resolve_source_arg(value: str) -> Path:
    candidate = Path(value)
    if candidate.is_absolute():
        return candidate
    for base in (Path.cwd(), REPO_ROOT):
        resolved = (base / value).resolve()
        if resolved.exists():
            return resolved
    return REPO_ROOT / value


def build_file_siblings_report(
    source_path: Path,
    asm_root: Path,
    fallback_root: Path | None,
    *,
    min_group: int = 2,
    source_root: Path | None = None,
) -> dict[str, object]:
    owner_tuples = owners_for_source(source_path, asm_root, fallback_root)
    owners = [build_sibling_owner(function, src, asm) for function, src, asm in owner_tuples]
    groups = cluster_siblings(owners)
    # A group below --min-group is still shown when it is tagged gbi-macro:
    # a lone display-list builder (the callee every sibling calls, not a
    # sibling itself) is exactly the "solve this one first" evidence the
    # wave of 2026-08-28 found by accident, and hiding it behind the size
    # filter would put the tool back where it started.
    displayed = [group for group in groups if group.size >= min_group or group.gbi_macro]
    solved_index = build_solved_index(asm_root, fallback_root, source_root)
    for group in displayed:
        group.closest_solved = find_closest_solved(group, solved_index)
    return {
        "source": display_relpath(source_path),
        "owners_remaining": len(owners),
        "groups_found": len(groups),
        "groups_shown": len(displayed),
        "min_group": min_group,
        "groups": [group_to_dict(group) for group in displayed],
    }


def build_all_siblings_report(
    source_root: Path,
    asm_root: Path,
    fallback_root: Path | None,
    *,
    min_group: int = 2,
    top: int = 30,
) -> dict[str, object]:
    all_groups: list[tuple[SiblingGroup, str]] = []
    files_scanned = 0
    owners_total = 0
    for source_path in sorted(source_root.rglob("*.c")):
        if any(part.startswith(".pragma_probe_") for part in source_path.parts):
            continue
        owner_tuples = owners_for_source(source_path, asm_root, fallback_root)
        if not owner_tuples:
            continue
        files_scanned += 1
        owners = [build_sibling_owner(function, src, asm) for function, src, asm in owner_tuples]
        owners_total += len(owners)
        source_display = display_relpath(source_path)
        for group in cluster_siblings(owners):
            if group.size >= min_group or group.gbi_macro:
                all_groups.append((group, source_display))

    all_groups.sort(key=lambda item: (-item[0].size, item[1], item[0].members[0].function))
    top_groups = all_groups[:top]
    # The closest-solved search is the expensive step (compared against
    # every accepted winner in the tree); only compute it for the groups
    # actually shown, not every group found while walking ~6,800 owners.
    solved_index = build_solved_index(asm_root, fallback_root, source_root)
    rows: list[dict[str, object]] = []
    for rank, (group, source) in enumerate(top_groups, start=1):
        group.closest_solved = find_closest_solved(group, solved_index)
        row = group_to_dict(group)
        row["rank"] = rank
        row["source"] = source
        rows.append(row)
    return {
        "files_scanned": files_scanned,
        "owners_remaining_total": owners_total,
        "groups_found_total": len(all_groups),
        "top": top,
        "min_group": min_group,
        "groups": rows,
    }


def render_siblings_report(report: dict[str, object]) -> str:
    lines: list[str] = []
    if "source" in report:
        lines.append(
            f"source: {report['source']}  (owners remaining: {report['owners_remaining']}, "
            f"groups found: {report['groups_found']}, shown: {report['groups_shown']}, "
            f"min-group: {report['min_group']})"
        )
    else:
        lines.append(
            f"tree-wide: {report['files_scanned']} files scanned, "
            f"{report['owners_remaining_total']} remaining owners, "
            f"{report['groups_found_total']} groups >= min-group {report['min_group']} "
            f"(top {report['top']} shown)"
        )
    groups = report["groups"]
    if not groups:
        lines.append("  (no groups met the threshold)")
        return "\n".join(lines)
    for group in groups:
        low, high = group["instruction_range"]
        tag = " [gbi-macro]" if group["gbi_macro"] else ""
        rank_prefix = f"#{group['rank']} " if "rank" in group else ""
        source_suffix = f"  source: {group['source']}" if "source" in group else ""
        lines.append(
            f"{rank_prefix}group {group['group_id']}: size {group['size']}, "
            f"instructions {low}-{high}{tag}{source_suffix}"
        )
        if group["shared_jal_targets"]:
            lines.append(f"    shared jal targets: {', '.join(group['shared_jal_targets'])}")
        lines.append(f"    members: {', '.join(group['members'])}")
        if group["gbi_macro"]:
            lines.append(f"    suggested spelling: {group['suggested_spelling']}")
        closest = group["closest_solved"]
        if closest:
            lines.append(
                f"    closest solved: {closest['function']} "
                f"({closest['source']}, distance {closest['distance']})"
            )
        else:
            lines.append("    closest solved: none found")
        lines.append("")
    return "\n".join(lines).rstrip()


def _add_fallback_args(parser: argparse.ArgumentParser) -> None:
    parser.add_argument("--source-root", type=Path, default=REPO_ROOT / "disasm" / "src")
    parser.add_argument("--asm-root", type=Path, default=REPO_ROOT / "disasm" / "asm" / "us" / "nonmatchings")
    parser.add_argument(
        "--asm-fallback-root",
        type=Path,
        default=None,
        help="read-only checkout root to fall back to for a missing .s (auto-guessed if omitted)",
    )
    parser.add_argument("--no-fallback", action="store_true", help="disable the asm fallback root lookup")


def _resolve_fallback_root(args: argparse.Namespace) -> Path | None:
    if args.no_fallback:
        return None
    return args.asm_fallback_root or _guess_asm_fallback_root()


def cmd_siblings(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(
        prog="analyze_family_shapes.py siblings",
        description=(
            "Cluster a file's (or the whole tree's) remaining pragma owners by "
            "opcode shape, so an agent can solve one member of the largest "
            "group and batch its siblings with the same spelling."
        ),
    )
    parser.add_argument("--source", help="path to a disasm/src/*.c file (required unless --all)")
    parser.add_argument(
        "--all", action="store_true", help="walk every source file; print the largest unsolved groups tree-wide"
    )
    parser.add_argument(
        "--min-group",
        type=int,
        default=2,
        help="minimum group size to report (a gbi-macro-tagged group is always reported)",
    )
    parser.add_argument("--top", type=int, default=30, help="--all only: how many groups to print")
    parser.add_argument("--json", action="store_true", help="print machine-readable JSON instead of a text report")
    _add_fallback_args(parser)
    args = parser.parse_args(argv)
    fallback_root = _resolve_fallback_root(args)

    if args.all:
        report = build_all_siblings_report(
            args.source_root, args.asm_root, fallback_root, min_group=args.min_group, top=args.top
        )
    else:
        if not args.source:
            parser.error("--source is required unless --all is given")
        source_path = _resolve_source_arg(args.source)
        if not source_path.exists():
            print(f"error: source file not found: {args.source}", file=sys.stderr)
            return 1
        report = build_file_siblings_report(
            source_path, args.asm_root, fallback_root, min_group=args.min_group, source_root=args.source_root
        )

    if args.json:
        print(json.dumps(report, indent=2, default=str))
    else:
        print(render_siblings_report(report))
    return 0


def cmd_unlock(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(
        prog="analyze_family_shapes.py unlock",
        description="List remaining pragma owners that call a given function (its callers).",
    )
    parser.add_argument("--function", required=True, help="e.g. func_8004A010")
    parser.add_argument("--json", action="store_true")
    _add_fallback_args(parser)
    args = parser.parse_args(argv)
    fallback_root = _resolve_fallback_root(args)

    owners = source_owners_with_fallback(args.source_root, args.asm_root, fallback_root)
    callers: list[dict[str, object]] = []
    for function, source_path, asm_path in owners:
        if function == args.function:
            continue
        text = asm_path.read_text(encoding="utf-8", errors="replace")
        _, instructions, _ = scanner.parse_instructions(text)
        call_count = scanner.extract_calls(instructions).count(args.function)
        if call_count:
            callers.append(
                {
                    "function": function,
                    "source": display_relpath(source_path),
                    "call_count": call_count,
                    "instruction_count": len(instructions),
                }
            )
    callers.sort(key=lambda row: (-row["call_count"], row["function"]))
    report = {"target": args.function, "caller_count": len(callers), "callers": callers}

    if args.json:
        print(json.dumps(report, indent=2))
    else:
        print(f"{args.function}: {len(callers)} remaining owner(s) call it")
        for row in callers:
            print(
                f"  {row['function']}  ({row['source']}, {row['call_count']}x, "
                f"{row['instruction_count']} instructions)"
            )
    return 0


def main() -> int:
    argv = sys.argv[1:]
    if argv and argv[0] == "siblings":
        return cmd_siblings(argv[1:])
    if argv and argv[0] == "unlock":
        return cmd_unlock(argv[1:])
    return main_shapes(argv)


if __name__ == "__main__":
    raise SystemExit(main())
