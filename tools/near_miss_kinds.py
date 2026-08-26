#!/usr/bin/env python3
"""Targeted, deterministic near-miss rewrites, grouped by mismatch kind.

``tools/sweep_targets.py``'s ``near_miss``/``permute_and_gate`` path already
sends the best recorded candidate for a still-open owner straight into
``decomp-permuter``, which is a broad, comparatively expensive search.  The
probe stats show two mismatch classes dominating the remaining near-miss
population -- ``register_allocation_only`` (identical opcodes/immediates,
only register choice differs) and ``immediate_drift`` (identical
opcodes/registers, only an offset or constant differs) -- plus a smaller
``operand_or_scheduling_drift`` population at very high similarity.  All
three are usually one small, mechanical source-shape change away from a
byte match: a declaration reordered, a literal off by a struct-field width,
a loop form swapped.  This module generates those specific rewrites first,
so a probe-only batch can find the byte match before spending a permuter
budget at all.

Usage:
    tools/near_miss_kinds.py report
    tools/near_miss_kinds.py list --kind register_allocation_only --limit 20
    tools/near_miss_kinds.py run --kinds register_allocation_only,immediate_drift --limit 50

The stats file defaults to ``resolve_stats_path()``, which checks the new
``disasm/probe-stats/probe-stats.jsonl`` location before falling back to the
legacy ``disasm/build/probe-stats.jsonl`` -- a separate migration is moving
the default, and this keeps the module correct on either side of it.

Every candidate generator here is pure: C text in, a bounded, deduplicated,
labeled list of ``(label, text)`` rewrites out.  Labels are always
``kind:<mismatch_kind>:<rule>[:detail]`` so the probe stats this module
writes (via the ordinary runner) show exactly which rule produced a hit.
None of these generators claims semantic insight -- they are narrow,
reversible source-shape hypotheses.  The runner (isolated object probe, then
the sequential full-ROM gate) remains the sole authority on whether a
rewrite is correct.
"""

from __future__ import annotations

import argparse
import collections
import itertools
import json
import re
import sys
from pathlib import Path
from typing import Callable

import pragma_targets as targets
import sweep_targets as sweep
import try_pragma_compare as pragma_runner

CAP_DEFAULT = 24


def resolve_stats_path() -> Path:
    """Return the probe-stats JSONL, preferring the new location over the legacy one.

    A separate migration is moving the default stats path from
    ``disasm/build/probe-stats.jsonl`` (``pragma_targets.STATS_PATH``) to
    ``disasm/probe-stats/probe-stats.jsonl``.  Checking both here keeps this
    module correct whichever side of that migration the checkout is on,
    without either module needing to know about the other's default.
    """
    new_path = targets.REPO_ROOT / "disasm" / "probe-stats" / "probe-stats.jsonl"
    if new_path.exists():
        return new_path
    if targets.STATS_PATH.exists():
        return targets.STATS_PATH
    return new_path


def _stats_records(path: Path) -> list[dict[str, object]]:
    """Parse a probe-stats JSONL file into its batch records."""
    if not path.exists():
        return []
    records: list[dict[str, object]] = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        line = line.strip()
        if not line:
            continue
        try:
            value = json.loads(line)
        except json.JSONDecodeError:
            continue
        if isinstance(value, dict):
            records.append(value)
    return records


def select_pool(
    stats_rows,
    min_similarity: float = 0.9,
    kinds=None,
) -> dict[str, list[dict[str, object]]]:
    """Return the best non-accepted attempt per still-open owner, by kind.

    ``stats_rows`` is the parsed list of top-level probe-stats batch records
    (each carrying an ``attempts`` list).  For every function this picks the
    single highest-``similarity_score`` attempt across every batch/label
    recorded for it, keeps it only if that best attempt is not
    ``accepted`` and the owner still holds a ``GLOBAL_ASM`` pragma (checked
    with ``pragma_targets.require_owner`` -- a later full-gate acceptance
    from a different run may have already solved it since these stats were
    recorded), and buckets the survivors by ``mismatch_kind``.  ``kinds``,
    when given, restricts the result to those kind names.
    """
    kind_filter = set(kinds) if kinds is not None else None
    best_by_function: dict[str, dict[str, object]] = {}
    for record in stats_rows:
        if not isinstance(record, dict):
            continue
        source = record.get("source")
        attempts = record.get("attempts")
        if not isinstance(attempts, list):
            continue
        for attempt in attempts:
            if not isinstance(attempt, dict):
                continue
            function = attempt.get("function")
            if not isinstance(function, str) or not function:
                continue
            score = attempt.get("similarity_score")
            if not isinstance(score, (int, float)):
                continue
            candidate = attempt.get("candidate")
            if not isinstance(candidate, str) or not candidate.strip():
                continue
            status = str(attempt.get("status") or "")
            existing = best_by_function.get(function)
            replace = existing is None
            if existing is not None:
                current_score = float(existing["similarity_score"])
                if float(score) > current_score:
                    replace = True
                elif (
                    float(score) == current_score
                    and status == "accepted"
                    and existing.get("best_status") != "accepted"
                ):
                    replace = True
            if not replace:
                continue
            best_by_function[function] = {
                "function": function,
                "source": source,
                "candidate": candidate,
                "declarations": attempt.get("declarations"),
                "label": attempt.get("label"),
                "similarity_score": float(score),
                "exact_similarity_score": attempt.get("exact_similarity_score"),
                "best_status": status,
                "mismatch_kind": attempt.get("mismatch_kind"),
                "assembly_diff": attempt.get("assembly_diff"),
                "first_diff_offset": attempt.get("first_diff_offset"),
                "expected_instruction_text": attempt.get("expected_instruction_text"),
                "actual_instruction_text": attempt.get("actual_instruction_text"),
            }

    grouped: dict[str, list[dict[str, object]]] = collections.defaultdict(list)
    for function, entry in best_by_function.items():
        if entry.get("best_status") == "accepted":
            continue
        if float(entry["similarity_score"]) < min_similarity:
            continue
        kind = entry.get("mismatch_kind")
        kind_name = kind if isinstance(kind, str) and kind else "unknown"
        if kind_filter is not None and kind_name not in kind_filter:
            continue
        try:
            targets.require_owner(function)
        except KeyError:
            continue
        grouped[kind_name].append(entry)

    for kind_name, entries in grouped.items():
        entries.sort(key=lambda e: (-float(e["similarity_score"]), str(e["function"])))
    return dict(grouped)


# ---------------------------------------------------------------------------
# Shared helpers
# ---------------------------------------------------------------------------

# A narrow local-declaration line: the same fixed-width/pointer spellings
# ``sweep_targets._STACK_SLOT_DECL_RE`` recognizes, but not limited to
# ``sp``-prefixed names -- m2c drafts and hand-decompiled sources both use
# plain ``temp``/``var`` names for ordinary locals.
_LOCAL_DECL_RE = re.compile(
    r"^(?P<indent>[ \t]*)(?P<type>(?:const\s+)?(?:(?:u|s)(?:8|16|32|64)|f(?:32|64)|void\s*\*+))"
    r"\s+(?P<name>[A-Za-z_]\w*)(?P<suffix>(?:\[[^\]]*\])?\s*(?:=\s*[^;]+)?;)\s*$"
)


def _first_decl_block(lines: list[str]) -> tuple[int, int] | None:
    """Return the ``[start, end)`` line range of the first local-decl block."""
    index = 0
    while index < len(lines):
        if _LOCAL_DECL_RE.match(lines[index]):
            start = index
            while index < len(lines) and _LOCAL_DECL_RE.match(lines[index]):
                index += 1
            if index - start >= 2:
                return start, index
            return None
        index += 1
    return None


def _brace_insert_index(lines: list[str]) -> int:
    """Line index right after a function's opening ``{`` (0 if none found)."""
    for index, line in enumerate(lines):
        if "{" in line:
            return index + 1
    return 0


def _merge_capped(
    generators, code: str, entry: dict[str, object] | None, *, cap: int,
) -> list[tuple[str, str]]:
    """Run several generators over ``code``, deduplicating and capping the total."""
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    for generator in generators:
        for label, candidate in generator(code, entry):
            if candidate in seen:
                continue
            seen.add(candidate)
            results.append((label, candidate))
            if len(results) >= cap:
                return results
    return results


# ---------------------------------------------------------------------------
# register_allocation_only: identical opcodes/immediates, register choice only
# ---------------------------------------------------------------------------


def decl_order_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 10,
) -> list[tuple[str, str]]:
    """Permute the first block of simple local declarations.

    IDO's register allocation is sensitive to declaration order.  All orders
    are tried when there are at most four locals; a larger block gets
    adjacent swaps and a full reverse instead of the factorial blow-up, plus
    the ascending (``sweep_targets.stack_slot_order_candidate``) and
    descending stack-slot orders for any ``sp``-named locals present.
    """
    lines = code.splitlines(keepends=True)
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    block = _first_decl_block(lines)
    if block is not None:
        start, end = block
        decl_lines = lines[start:end]
        n = len(decl_lines)
        identity = tuple(range(n))
        if n <= 4:
            orders = [perm for perm in itertools.permutations(range(n)) if perm != identity]
        else:
            orders = []
            for i in range(n - 1):
                order = list(range(n))
                order[i], order[i + 1] = order[i + 1], order[i]
                orders.append(tuple(order))
            orders.append(tuple(reversed(range(n))))
        for order in orders:
            new_lines = list(lines)
            new_lines[start:end] = [decl_lines[i] for i in order]
            candidate = "".join(new_lines)
            if candidate in seen:
                continue
            seen.add(candidate)
            label = f"kind:register_allocation_only:decl-order:{'-'.join(map(str, order))}"
            results.append((label, candidate))
            if len(results) >= limit:
                return results

    # ``stack_slot_order_candidate`` only fires for probe_rejected attempts
    # with a mismatch_kind it recognizes; that classification is orthogonal
    # to whether the reorder itself is worth trying here, so satisfy its
    # guard with a synthetic attempt rather than duplicating its regex.
    synthetic = {"status": "probe_rejected", "mismatch_kind": "instruction_drift"}
    ascending = sweep.stack_slot_order_candidate(code, synthetic)
    if ascending is not None and ascending not in seen:
        seen.add(ascending)
        results.append(("kind:register_allocation_only:decl-order:stack-ascending", ascending))
        if len(results) >= limit:
            return results[:limit]
    descending = _stack_slot_descending(code)
    if descending is not None and descending not in seen:
        seen.add(descending)
        results.append(("kind:register_allocation_only:decl-order:stack-descending", descending))
    return results[:limit]


def _stack_slot_descending(code: str) -> str | None:
    """Reorder ``sp``-named stack-slot declarations by descending slot.

    The mirror image of ``sweep_targets.stack_slot_order_candidate`` (which
    only ever sorts ascending); reuses its declaration regex rather than
    re-deriving it.
    """
    pattern = sweep._STACK_SLOT_DECL_RE
    lines = code.splitlines(keepends=True)
    changed = False
    index = 0
    while index < len(lines):
        if pattern.match(lines[index]) is None:
            index += 1
            continue
        start = index
        declarations: list[tuple[int, str]] = []
        while index < len(lines):
            current = pattern.match(lines[index])
            if current is None:
                break
            slot = int(current.group("name")[2:], 16)
            declarations.append((slot, lines[index]))
            index += 1
        if len(declarations) < 2:
            continue
        ordered = sorted(declarations, key=lambda item: -item[0])
        if [line for _, line in declarations] != [line for _, line in ordered]:
            lines[start:index] = [line for _, line in ordered]
            changed = True
    return "".join(lines) if changed else None


_WIDTH_SWAPS: dict[str, tuple[str, ...]] = {
    "s32": ("u8", "u16", "s16"),
    "u32": ("s32",),
    "u8": ("s32",),
    "u16": ("s32",),
    "s16": ("s32",),
}
_TYPED_DECL_RE = re.compile(
    r"\b(?P<type>u8|u16|u32|s8|s16|s32)(?P<sep>\s+)(?P<name>[A-Za-z_]\w*)"
    r"(?=(?:\[[^\]]*\])?\s*(?:=[^;]*)?;)",
    re.M,
)


def type_width_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 8,
) -> list[tuple[str, str]]:
    """Swap one temporary's declared width at a time (``s32``<->``u8``/``u16``/``s16``, ``u32``<->``s32``)."""
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    for match in _TYPED_DECL_RE.finditer(code):
        current_type = match.group("type")
        for alt in _WIDTH_SWAPS.get(current_type, ()):
            start, end = match.span("type")
            candidate = code[:start] + alt + code[end:]
            if candidate in seen:
                continue
            seen.add(candidate)
            label = (
                f"kind:register_allocation_only:type-width:"
                f"{match.group('name')}:{current_type}-to-{alt}"
            )
            results.append((label, candidate))
            if len(results) >= limit:
                return results
    return results


_SIMPLE_ASSIGN_RE = re.compile(
    r"^(?P<indent>[ \t]*)(?:u8|u16|u32|u64|s8|s16|s32|s64|f32|f64|void\s*\*+)"
    r"\s+(?P<name>[A-Za-z_]\w*)\s*=\s*(?P<expr>[^;]+);[ \t]*\n",
    re.M,
)
_HOIST_EXPR_RE = re.compile(r"\b[A-Za-z_]\w*(?:(?:->|\.)[A-Za-z_]\w*|\[[^\[\]]+\])+")


def inline_single_use_temp_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 6,
) -> list[tuple[str, str]]:
    """Replace a single-use temporary with its initializer expression."""
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    for match in _SIMPLE_ASSIGN_RE.finditer(code):
        name = match.group("name")
        expr = match.group("expr").strip()
        rest = code[match.end():]
        before = code[:match.start()]
        name_re = re.compile(rf"\b{re.escape(name)}\b")
        if len(name_re.findall(before)) or len(name_re.findall(rest)) != 1:
            continue
        new_rest = name_re.sub(f"({expr})", rest, count=1)
        candidate = before + new_rest
        if candidate in seen:
            continue
        seen.add(candidate)
        results.append((f"kind:register_allocation_only:inline-temp:{name}", candidate))
        if len(results) >= limit:
            break
    return results


def hoist_repeated_subexpr_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 4,
) -> list[tuple[str, str]]:
    """Introduce a temporary for a field/index expression repeated >=2 times."""
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    counts = collections.Counter(_HOIST_EXPR_RE.findall(code))
    repeated = sorted(expr for expr, n in counts.items() if n >= 2)
    lines = code.splitlines(keepends=True)
    insert_at = _brace_insert_index(lines)
    for order, expr in enumerate(repeated[:limit]):
        temp_name = f"temp_hoist{order}"
        rewritten = re.sub(rf"(?<!\w){re.escape(expr)}(?!\w)", temp_name, code)
        if rewritten == code:
            continue
        new_lines = rewritten.splitlines(keepends=True)
        new_lines.insert(insert_at, f"    s32 {temp_name} = {expr};\n")
        candidate = "".join(new_lines)
        if candidate in seen:
            continue
        seen.add(candidate)
        results.append((f"kind:register_allocation_only:hoist-temp:{temp_name}", candidate))
    return results[:limit]


def hoist_inline_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 8,
) -> list[tuple[str, str]]:
    """Hoist a repeated sub-expression, or inline a single-use temporary."""
    results = list(inline_single_use_temp_candidates(code, entry, limit=limit))
    for label, candidate in hoist_repeated_subexpr_candidates(code, entry, limit=limit):
        if len(results) >= limit:
            break
        results.append((label, candidate))
    return results[:limit]


_TOKEN = r"[A-Za-z_]\w*(?:(?:->|\.)[A-Za-z_]\w*)*(?:\[[A-Za-z_0-9]+\])?|0[xX][0-9A-Fa-f]+|\d+"
_COMMUTE_RE = re.compile(rf"(?P<a>{_TOKEN})(?P<sp1>\s*)(?P<op>\+|==|&|\|)(?P<sp2>\s*)(?P<b>{_TOKEN})")


def commute_swap_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 8,
) -> list[tuple[str, str]]:
    """Swap operand order of a commutative ``a OP b`` expression, one at a time."""
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    for match in _COMMUTE_RE.finditer(code):
        op = match.group("op")
        start, end = match.span()
        before_char = code[start - 1] if start > 0 else ""
        after_char = code[end] if end < len(code) else ""
        if op == "&" and (before_char == "&" or after_char == "&"):
            continue
        if op == "|" and (before_char == "|" or after_char == "|"):
            continue
        if op == "+" and (after_char == "+" or before_char == "+"):
            continue
        a, b = match.group("a"), match.group("b")
        if a == b:
            continue
        swapped = f"{b}{match.group('sp1')}{op}{match.group('sp2')}{a}"
        candidate = code[:start] + swapped + code[end:]
        if candidate in seen:
            continue
        seen.add(candidate)
        results.append((f"kind:register_allocation_only:commute-swap:{len(results)}", candidate))
        if len(results) >= limit:
            break
    return results


_LVALUE = r"\*?[A-Za-z_]\w*(?:(?:->|\.)[A-Za-z_]\w*)*"
_IF_ASSIGN_RE = re.compile(
    rf"if\s*\((?P<cond>[^()]+)\)\s*\{{?\s*(?P<name>{_LVALUE})\s*=\s*1;\s*\}}?"
)
_NE_ZERO_RE = re.compile(rf"(?P<name>{_LVALUE})\s*=\s*(?P<cond>[^;]+?)\s*!=\s*0;")


def _first_diff_is_slt_or_xor(entry: dict[str, object] | None) -> bool:
    if not entry:
        return False
    for key in ("expected_instruction_text", "actual_instruction_text"):
        value = entry.get(key)
        if isinstance(value, str) and value.strip():
            op = value.strip().split(None, 1)[0].lower()
            if op.startswith("slt") or op.startswith("xor"):
                return True
    return False


def boolean_normalize_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 6,
) -> list[tuple[str, str]]:
    """``if (x) y = 1;`` <-> ``y = x != 0;`` normalisation, guarded by the diff opcode."""
    if entry is not None and not _first_diff_is_slt_or_xor(entry):
        return []
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    for match in _IF_ASSIGN_RE.finditer(code):
        cond, name = match.group("cond").strip(), match.group("name")
        replacement = f"{name} = ({cond}) != 0;"
        candidate = code[:match.start()] + replacement + code[match.end():]
        if candidate not in seen:
            seen.add(candidate)
            results.append((f"kind:register_allocation_only:bool-normalize:{name}", candidate))
            if len(results) >= limit:
                return results
    for match in _NE_ZERO_RE.finditer(code):
        cond, name = match.group("cond").strip(), match.group("name")
        replacement = f"if ({cond}) {{ {name} = 1; }}"
        candidate = code[:match.start()] + replacement + code[match.end():]
        if candidate not in seen:
            seen.add(candidate)
            results.append((f"kind:register_allocation_only:bool-normalize:{name}", candidate))
            if len(results) >= limit:
                return results
    return results


def register_allocation_only_candidates(
    code: str, entry: dict[str, object] | None, *, cap: int = CAP_DEFAULT,
) -> list[tuple[str, str]]:
    generators = (
        decl_order_candidates,
        type_width_candidates,
        hoist_inline_candidates,
        commute_swap_candidates,
        boolean_normalize_candidates,
    )
    return _merge_capped(generators, code, entry, cap=cap)


# ---------------------------------------------------------------------------
# immediate_drift: identical opcodes/registers, only an offset/constant differs
# ---------------------------------------------------------------------------

_LAST_IMM_RE = re.compile(r"(-?(?:0x[0-9A-Fa-f]+|\d+))\s*$")
_PAREN_IMM_RE = re.compile(r"(-?(?:0x[0-9A-Fa-f]+|\d+))\(")


def _parse_imm_text(text: str) -> int | None:
    """Parse the operand immediate from a decoded instruction's text.

    Handles both the load/store ``op $reg, IMM($base)`` shape (the immediate
    is not trailing) and the ``addiu $sp, $sp, IMM`` shape (it is).
    """
    text = text.strip()
    match = _PAREN_IMM_RE.search(text) or _LAST_IMM_RE.search(text)
    if match is None:
        return None
    try:
        return int(match.group(1), 0)
    except ValueError:
        return None


def _first_diff_delta(entry: dict[str, object] | None) -> int | None:
    if not entry:
        return None
    expected = _parse_imm_text(str(entry.get("expected_instruction_text") or ""))
    actual = _parse_imm_text(str(entry.get("actual_instruction_text") or ""))
    if expected is None or actual is None:
        return None
    return expected - actual


def offset_shift_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 10,
) -> list[tuple[str, str]]:
    """Shift a struct/byte offset by the expected-actual immediate delta.

    Reuses ``sweep_targets.immediate_repair_candidates`` for the direct
    literal substitution (``+ 0x10`` -> ``+ 0x14``), then additionally scales
    any bracketed array index (``arg0[2]`` -> ``arg0[3]``) by the delta
    divided by a plausible element width.
    """
    results: list[tuple[str, str]] = []
    synthetic = {
        "status": "probe_rejected",
        "mismatch_kind": "immediate_drift",
        "assembly_diff": entry.get("assembly_diff") if entry else None,
    }
    for suffix, text in sweep.immediate_repair_candidates(code, synthetic, limit=limit):
        results.append((f"kind:immediate_drift:offset-shift:{suffix}", text))
        if len(results) >= limit:
            return results[:limit]

    delta = _first_diff_delta(entry)
    if delta:
        for width in (1, 2, 4, 8):
            if delta % width:
                continue
            step = delta // width
            if step == 0:
                continue
            for match in re.finditer(r"\[(\d+)\]", code):
                index_value = int(match.group(1))
                new_index = index_value + step
                if new_index < 0:
                    continue
                start, end = match.span(1)
                candidate = code[:start] + str(new_index) + code[end:]
                if candidate == code:
                    continue
                label = (
                    f"kind:immediate_drift:offset-shift:index[{index_value}->{new_index}]w{width}"
                )
                results.append((label, candidate))
                if len(results) >= limit:
                    return results[:limit]
    return results[:limit]


_SP_ADJUST_RE = re.compile(r"addiu\s+\$sp\s*,\s*\$sp\s*,\s*(-?\S+)")


def _sp_delta(entry: dict[str, object] | None) -> int | None:
    if not entry:
        return None
    expected_match = _SP_ADJUST_RE.search(str(entry.get("expected_instruction_text") or ""))
    actual_match = _SP_ADJUST_RE.search(str(entry.get("actual_instruction_text") or ""))
    if not expected_match or not actual_match:
        return None
    try:
        expected_value = int(expected_match.group(1), 0)
        actual_value = int(actual_match.group(1), 0)
    except ValueError:
        return None
    return expected_value - actual_value


def frame_padding_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 4,
) -> list[tuple[str, str]]:
    """Add an ``s32 pad[k]`` local to grow the frame to the expected ``addiu $sp`` size."""
    delta = _sp_delta(entry)
    if not delta:
        return []
    grow_bytes = -delta  # both values are negative stack adjustments
    if grow_bytes <= 0 or grow_bytes % 4:
        return []
    words = grow_bytes // 4
    lines = code.splitlines(keepends=True)
    block = _first_decl_block(lines)
    insert_at = block[1] if block is not None else _brace_insert_index(lines)
    new_lines = list(lines)
    new_lines.insert(insert_at, f"    s32 pad_frame[{words}];\n")
    candidate = "".join(new_lines)
    if candidate == code:
        return []
    return [(f"kind:immediate_drift:frame-padding:{grow_bytes}", candidate)][:limit]


_LITERAL_ALT_PAIRS: tuple[tuple[str, str], ...] = (
    ("0xFF7F", "~0x80"),
    ("0xff7f", "~0x80"),
    ("0xFFFE", "~1"),
    ("0xfffe", "~1"),
    ("0xFFFFFFFF", "-1"),
    ("0xffffffff", "-1"),
)
_NEGATIVE_LITERAL_RE = re.compile(r"(?<![\w.])-([1-9]\d{0,9})\b")


def literal_width_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 8,
) -> list[tuple[str, str]]:
    """Rewrite a literal between its masked/complement and plain spellings."""
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    for original, alt in _LITERAL_ALT_PAIRS:
        for needle, replacement in ((original, alt), (alt, original)):
            if needle not in code:
                continue
            candidate = code.replace(needle, replacement, 1)
            if candidate in seen:
                continue
            seen.add(candidate)
            label = f"kind:immediate_drift:literal-width:{needle}-to-{replacement}"
            results.append((label, candidate))
            if len(results) >= limit:
                return results
    for match in _NEGATIVE_LITERAL_RE.finditer(code):
        value = int(match.group(1))
        masked = f"0x{(0x100000000 - value) & 0xFFFFFFFF:X}"
        start, end = match.span()
        candidate = code[:start] + masked + code[end:]
        if candidate in seen:
            continue
        seen.add(candidate)
        label = f"kind:immediate_drift:literal-width:neg{value}-to-{masked}"
        results.append((label, candidate))
        if len(results) >= limit:
            break
    return results[:limit]


_SHIFT_RE = re.compile(r"\b([A-Za-z_]\w*)\s*<<\s*(\d+)\b")
_MUL_SHIFT_RE = re.compile(r"\b([A-Za-z_]\w*)\s*\*\s*\(1\s*<<\s*(\d+)\)")
_INDEX_RE = re.compile(r"\b([A-Za-z_]\w*)\[([A-Za-z_]\w*)\]")
_PTR_ADD_RE = re.compile(r"\*\(\s*([A-Za-z_]\w*)\s*\+\s*([A-Za-z_]\w*)\s*\)")


def stride_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 8,
) -> list[tuple[str, str]]:
    """``arg << k`` <-> ``arg * (1 << k)``, and array-index <-> pointer-add forms."""
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}

    def add(label: str, candidate: str) -> bool:
        if candidate in seen:
            return False
        seen.add(candidate)
        results.append((label, candidate))
        return len(results) >= limit

    for match in _SHIFT_RE.finditer(code):
        name, k = match.group(1), match.group(2)
        replacement = f"{name} * (1 << {k})"
        candidate = code[:match.start()] + replacement + code[match.end():]
        if add(f"kind:immediate_drift:stride:shift-to-mul:{name}", candidate):
            return results
    for match in _MUL_SHIFT_RE.finditer(code):
        name, k = match.group(1), match.group(2)
        replacement = f"{name} << {k}"
        candidate = code[:match.start()] + replacement + code[match.end():]
        if add(f"kind:immediate_drift:stride:mul-to-shift:{name}", candidate):
            return results
    for match in _INDEX_RE.finditer(code):
        arr, idx = match.group(1), match.group(2)
        replacement = f"*({arr} + {idx})"
        candidate = code[:match.start()] + replacement + code[match.end():]
        if add(f"kind:immediate_drift:stride:index-to-ptr:{arr}", candidate):
            return results
    for match in _PTR_ADD_RE.finditer(code):
        arr, idx = match.group(1), match.group(2)
        replacement = f"{arr}[{idx}]"
        candidate = code[:match.start()] + replacement + code[match.end():]
        if add(f"kind:immediate_drift:stride:ptr-to-index:{arr}", candidate):
            return results
    return results


def immediate_drift_candidates(
    code: str, entry: dict[str, object] | None, *, cap: int = CAP_DEFAULT,
) -> list[tuple[str, str]]:
    generators = (
        offset_shift_candidates,
        frame_padding_candidates,
        literal_width_candidates,
        stride_candidates,
    )
    return _merge_capped(generators, code, entry, cap=cap)


# ---------------------------------------------------------------------------
# operand_or_scheduling_drift (similarity >= 0.95 only): statement shape
# ---------------------------------------------------------------------------

_MERGE_RETURN_RE = re.compile(
    r"(?P<indent>[ \t]*)(?:u8|u16|u32|u64|s8|s16|s32|s64|f32|f64|void\s*\*+)"
    r"\s+(?P<name>[A-Za-z_]\w*)\s*=\s*(?P<expr>[^;]+);\n\s*return\s+(?P=name);"
)
_SPLIT_RETURN_RE = re.compile(r"return\s+(?P<expr>[A-Za-z_]\w*\s*\([^;]*\));")


def split_merge_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 6,
) -> list[tuple[str, str]]:
    """``a = f(); return a;`` <-> ``return f();``."""
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    for match in _MERGE_RETURN_RE.finditer(code):
        expr = match.group("expr").strip()
        replacement = f"{match.group('indent')}return {expr};"
        candidate = code[:match.start()] + replacement + code[match.end():]
        if candidate not in seen:
            seen.add(candidate)
            results.append((f"kind:operand_or_scheduling_drift:merge-return:{match.group('name')}", candidate))
            if len(results) >= limit:
                return results
    for match in _SPLIT_RETURN_RE.finditer(code):
        expr = match.group("expr").strip()
        indent_match = re.search(r"[ \t]*$", code[:match.start()].rsplit("\n", 1)[-1])
        indent = indent_match.group(0) if indent_match else ""
        replacement = f"s32 temp_ret = {expr};\n{indent}return temp_ret;"
        candidate = code[:match.start()] + replacement + code[match.end():]
        if candidate not in seen:
            seen.add(candidate)
            results.append(("kind:operand_or_scheduling_drift:split-return", candidate))
            if len(results) >= limit:
                return results
    return results


_ASSIGN_STMT_RE = re.compile(r"^(?P<indent>[ \t]*)(?P<lhs>\*?[A-Za-z_][\w\->.\[\]]*)\s*=\s*(?P<rhs>[^;]+);[ \t]*$")
_CALL_STMT_RE = re.compile(r"^(?P<indent>[ \t]*)(?P<name>[A-Za-z_]\w*)\s*\((?P<args>[^;]*)\);[ \t]*$")


def _bare_name(token: str) -> str:
    """Strip a store's ``*``/``->``/``.``/``[`` decorations down to its base identifier."""
    token = token.lstrip("*")
    for separator in ("->", ".", "["):
        token = token.split(separator, 1)[0]
    return token


def reorder_store_call_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 6,
) -> list[tuple[str, str]]:
    """Swap an adjacent store/call pair when neither reads the other's base variable."""
    lines = code.splitlines(keepends=True)
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    for i in range(len(lines) - 1):
        first, second = lines[i].rstrip("\n"), lines[i + 1].rstrip("\n")
        assign_first = _ASSIGN_STMT_RE.match(first)
        call_second = _CALL_STMT_RE.match(second)
        call_first = _CALL_STMT_RE.match(first)
        assign_second = _ASSIGN_STMT_RE.match(second)
        swap_case = None
        if assign_first and call_second:
            bare = _bare_name(assign_first.group("lhs"))
            reference = re.compile(rf"\b{re.escape(bare)}\b")
            if not reference.search(call_second.group("args")) and not reference.search(assign_first.group("rhs")):
                swap_case = "store-before-call"
        elif call_first and assign_second:
            bare = _bare_name(assign_second.group("lhs"))
            if not re.search(rf"\b{re.escape(bare)}\b", call_first.group("args")):
                swap_case = "store-after-call"
        if swap_case is None:
            continue
        new_lines = list(lines)
        new_lines[i], new_lines[i + 1] = lines[i + 1], lines[i]
        candidate = "".join(new_lines)
        if candidate in seen:
            continue
        seen.add(candidate)
        results.append((f"kind:operand_or_scheduling_drift:reorder-store-call:{swap_case}:{i}", candidate))
        if len(results) >= limit:
            break
    return results


_WHILE_RE = re.compile(r"\bwhile\s*\((?P<cond>[^()]+)\)\s*\{")
_FOR_EMPTY_RE = re.compile(r"\bfor\s*\(\s*;\s*(?P<cond>[^;]+);\s*\)\s*\{")


def _find_matching_brace(text: str, open_index: int) -> int:
    depth = 0
    for i in range(open_index, len(text)):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return i
    return -1


def _do_while_to_while(code: str) -> str | None:
    match = re.search(r"\bdo\s*\{", code)
    if not match:
        return None
    open_index = match.end() - 1
    close_index = _find_matching_brace(code, open_index)
    if close_index == -1:
        return None
    tail_match = re.match(r"\s*while\s*\(([^()]+)\)\s*;", code[close_index + 1:])
    if not tail_match:
        return None
    cond = tail_match.group(1).strip()
    body = code[open_index + 1:close_index]
    end = close_index + 1 + tail_match.end()
    replacement = f"while ({cond}) {{{body}}}"
    return code[:match.start()] + replacement + code[end:]


def loop_form_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 6,
) -> list[tuple[str, str]]:
    """``while`` <-> ``for`` <-> ``do/while``, tried only at the loop head/tail."""
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    for match in _WHILE_RE.finditer(code):
        replacement = f"for (;{match.group('cond').strip()};) {{"
        candidate = code[:match.start()] + replacement + code[match.end():]
        if candidate not in seen:
            seen.add(candidate)
            results.append((f"kind:operand_or_scheduling_drift:loop-form:while-to-for:{len(results)}", candidate))
            if len(results) >= limit:
                return results
    for match in _FOR_EMPTY_RE.finditer(code):
        replacement = f"while ({match.group('cond').strip()}) {{"
        candidate = code[:match.start()] + replacement + code[match.end():]
        if candidate not in seen:
            seen.add(candidate)
            results.append((f"kind:operand_or_scheduling_drift:loop-form:for-to-while:{len(results)}", candidate))
            if len(results) >= limit:
                return results
    do_result = _do_while_to_while(code)
    if do_result is not None and do_result not in seen:
        seen.add(do_result)
        results.append(("kind:operand_or_scheduling_drift:loop-form:do-while-to-while", do_result))
    return results[:limit]


_POSTFIX_RE = re.compile(r"\b([A-Za-z_]\w*)\+\+")
_PREFIX_RE = re.compile(r"\+\+([A-Za-z_]\w*)\b")


def increment_style_candidates(
    code: str, entry: dict[str, object] | None = None, *, limit: int = 8,
) -> list[tuple[str, str]]:
    """``i++`` <-> ``++i``, one occurrence at a time."""
    results: list[tuple[str, str]] = []
    seen: set[str] = {code}
    for match in _POSTFIX_RE.finditer(code):
        name = match.group(1)
        candidate = code[:match.start()] + f"++{name}" + code[match.end():]
        if candidate not in seen:
            seen.add(candidate)
            results.append((f"kind:operand_or_scheduling_drift:increment-style:post-to-pre:{name}:{len(results)}", candidate))
            if len(results) >= limit:
                return results
    for match in _PREFIX_RE.finditer(code):
        name = match.group(1)
        candidate = code[:match.start()] + f"{name}++" + code[match.end():]
        if candidate not in seen:
            seen.add(candidate)
            results.append((f"kind:operand_or_scheduling_drift:increment-style:pre-to-post:{name}:{len(results)}", candidate))
            if len(results) >= limit:
                return results
    return results


def operand_or_scheduling_drift_candidates(
    code: str, entry: dict[str, object] | None, *, cap: int = CAP_DEFAULT,
) -> list[tuple[str, str]]:
    score = entry.get("similarity_score") if entry else None
    if not isinstance(score, (int, float)) or float(score) < 0.95:
        return []
    generators = (
        split_merge_candidates,
        reorder_store_call_candidates,
        loop_form_candidates,
        increment_style_candidates,
    )
    return _merge_capped(generators, code, entry, cap=cap)


_KIND_GENERATORS: dict[str, Callable[..., list[tuple[str, str]]]] = {
    "register_allocation_only": register_allocation_only_candidates,
    "immediate_drift": immediate_drift_candidates,
    "operand_or_scheduling_drift": operand_or_scheduling_drift_candidates,
}


def generate_candidates(
    kind: str, code: str, entry: dict[str, object] | None = None, *, cap: int = CAP_DEFAULT,
) -> list[tuple[str, str]]:
    """Dispatch to the rewrite generators for ``kind`` (``[]`` if unknown)."""
    generator = _KIND_GENERATORS.get(kind)
    if generator is None:
        return []
    return generator(code, entry, cap=cap)


# ---------------------------------------------------------------------------
# Driver
# ---------------------------------------------------------------------------


def _rule_key(label: str) -> str:
    parts = label.split(":")
    if len(parts) >= 3 and parts[0] == "kind":
        return f"{parts[1]}:{parts[2]}"
    return label


def run(
    pool,
    runner=pragma_runner,
    *,
    probe_workers: int | None = None,
    permute_seconds: float = 0.0,
    permute_threads: int = 4,
    cap: int = CAP_DEFAULT,
) -> dict[str, object]:
    """Probe every generated rewrite per owner, gate the hits, print a rule summary.

    ``pool`` is either ``select_pool``'s ``{kind: [entry, ...]}`` mapping or
    a flat list of entries (each already carrying its own ``mismatch_kind``).
    For each owner this sends every generated rewrite through one probe-only
    batch (``gate=False``), then gates only the ``probe_match`` hits in
    similarity order, stopping at the first accepted one -- mirroring
    ``sweep_targets.permute_and_gate``.  When nothing probe-matches and
    ``permute_seconds`` is positive (default 0, off), the best-scoring
    generated rewrite (or the original candidate, if none scored) is handed
    to ``sweep_targets.permute_and_gate`` as a last resort.
    """
    if isinstance(pool, dict):
        items = [entry for entries in pool.values() for entry in entries]
    else:
        items = list(pool)

    accepted: list[str] = []
    owners_processed = 0
    rule_summary: dict[str, collections.Counter] = collections.defaultdict(collections.Counter)
    owner_reports: list[dict[str, object]] = []

    for entry in items:
        function = str(entry["function"])
        kind = str(entry.get("mismatch_kind") or "unknown")
        code = str(entry["candidate"])
        declarations = entry.get("declarations") if isinstance(entry.get("declarations"), str) else None
        candidates = generate_candidates(kind, code, entry, cap=cap)
        if not candidates:
            continue
        try:
            source_path = targets.require_owner(function).source_path
        except KeyError:
            continue
        owners_processed += 1

        labels = [label for label, _ in candidates]
        blocks = [(function, rewrite) for _, rewrite in candidates]
        for label in labels:
            rule_summary[_rule_key(label)]["attempts"] += 1

        try:
            probe = runner.try_candidates_detailed(
                source_path, blocks, labels=labels, gate=False,
                declarations=declarations, probe_workers=probe_workers,
            )
        except Exception as error:  # one broken owner must not end the run
            owner_reports.append({"function": function, "status": "probe_failed", "error": str(error)})
            continue

        probe_attempts = probe.get("attempts", []) if isinstance(probe, dict) else []
        probe_matches = [a for a in probe_attempts if isinstance(a, dict) and a.get("status") == "probe_match"]
        for attempt in probe_matches:
            index = attempt.get("index")
            if isinstance(index, int) and 0 <= index < len(labels):
                rule_summary[_rule_key(labels[index])]["probe_match"] += 1

        owner_accepted = False
        for attempt in probe_matches:
            index = attempt.get("index")
            if not isinstance(index, int) or not (0 <= index < len(labels)):
                continue
            try:
                gated = runner.try_candidates_detailed(
                    source_path, [blocks[index]], labels=[labels[index]],
                    gate=True, declarations=declarations, probe_workers=probe_workers,
                )
            except Exception as error:
                owner_reports.append({"function": function, "status": "gate_failed", "error": str(error)})
                continue
            if gated.get("accepted"):
                accepted.extend(str(name) for name in gated["accepted"])
                rule_summary[_rule_key(labels[index])]["accepted"] += 1
                owner_accepted = True
                owner_reports.append({"function": function, "status": "accepted", "label": labels[index]})
                break
        if owner_accepted:
            continue

        if permute_seconds > 0:
            best_index = None
            best_score = -1.0
            for attempt in probe_attempts:
                if not isinstance(attempt, dict):
                    continue
                score = attempt.get("similarity_score")
                index = attempt.get("index")
                if isinstance(score, (int, float)) and isinstance(index, int) and float(score) > best_score:
                    best_score = float(score)
                    best_index = index
            if best_index is not None and 0 <= best_index < len(labels):
                permute_label, permute_code = labels[best_index], blocks[best_index][1]
            else:
                permute_label, permute_code = entry.get("label"), code
            permute_row = {
                "function": function,
                "candidate": permute_code,
                "label": permute_label,
                "declarations": declarations,
                "similarity_score": entry.get("similarity_score"),
                "mismatch_kind": kind,
            }
            permute_result = sweep.permute_and_gate(
                [permute_row], seconds=permute_seconds, threads=permute_threads,
                workers=probe_workers, parallel=1,
            )
            accepted.extend(str(name) for name in permute_result.get("accepted", []))
            owner_reports.append({"function": function, "status": "permuted", "result": permute_result})

    return {
        "owners": owners_processed,
        "accepted": accepted,
        "rule_summary": {rule: dict(counter) for rule, counter in sorted(rule_summary.items())},
        "owner_reports": owner_reports,
    }


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

SIMILARITY_BANDS: tuple[tuple[float, float, str], ...] = (
    (0.9, 0.95, "0.90-0.95"),
    (0.95, 1.0 + 1e-9, "0.95-1.00"),
)


def pool_report(pool: dict[str, list[dict[str, object]]], *, min_similarity: float = 0.9) -> dict[str, object]:
    """Counts per mismatch kind x similarity band, for the ``report`` CLI command."""
    rows: dict[str, object] = {}
    total = 0
    for kind, entries in sorted(pool.items(), key=lambda item: -len(item[1])):
        bands: dict[str, int] = {}
        for low, high, label in SIMILARITY_BANDS:
            if high <= min_similarity:
                continue
            count = sum(1 for e in entries if low <= float(e["similarity_score"]) < high)
            if count:
                bands[label] = count
        rows[kind] = {"total": len(entries), "bands": bands}
        total += len(entries)
    return {"total": total, "kinds": rows}


def main() -> int:
    # ``--stats``/``--min-similarity`` are accepted both before and after the
    # subcommand (``near_miss_kinds.py report --stats X`` and
    # ``near_miss_kinds.py --stats X report`` both work) since either order
    # reads naturally from the command line.
    common = argparse.ArgumentParser(add_help=False)
    common.add_argument("--stats", type=Path, help="probe-stats.jsonl (default: resolve_stats_path())")
    common.add_argument("--min-similarity", type=float, default=0.9)

    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter, parents=[common],
    )
    commands = parser.add_subparsers(dest="command", required=True)

    commands.add_parser("report", help="print pool counts per kind x similarity band", parents=[common])

    list_cmd = commands.add_parser("list", help="list pool entries for one kind", parents=[common])
    list_cmd.add_argument("--kind", required=True)
    list_cmd.add_argument("--limit", type=int, default=20)

    run_cmd = commands.add_parser("run", help="probe/gate the generated rewrites for the pool", parents=[common])
    run_cmd.add_argument("--kinds", type=str, help="comma-separated mismatch kinds (default: all)")
    run_cmd.add_argument("--limit", type=int)
    run_cmd.add_argument("--workers", type=int)
    run_cmd.add_argument("--permute-seconds", type=float, default=0.0)
    run_cmd.add_argument("--json", type=Path)

    args = parser.parse_args()
    stats_path = args.stats if args.stats is not None else resolve_stats_path()
    rows = _stats_records(stats_path)

    if args.command == "report":
        pool = select_pool(rows, min_similarity=args.min_similarity)
        print(json.dumps(pool_report(pool, min_similarity=args.min_similarity), indent=2))
        return 0

    if args.command == "list":
        pool = select_pool(rows, min_similarity=args.min_similarity, kinds=(args.kind,))
        entries = pool.get(args.kind, [])[: max(0, args.limit)]
        for entry in entries:
            print(json.dumps({
                "function": entry.get("function"),
                "source": entry.get("source"),
                "similarity_score": entry.get("similarity_score"),
                "label": entry.get("label"),
                "mismatch_kind": entry.get("mismatch_kind"),
                "expected_instruction_text": entry.get("expected_instruction_text"),
                "actual_instruction_text": entry.get("actual_instruction_text"),
            }))
        return 0

    if args.command == "run":
        kinds = tuple(k for k in (args.kinds or "").split(",") if k) or None
        pool = select_pool(rows, min_similarity=args.min_similarity, kinds=kinds)
        flat = [entry for entries in pool.values() for entry in entries]
        flat.sort(key=lambda e: (-float(e["similarity_score"]), str(e["function"])))
        if args.limit is not None:
            flat = flat[: max(0, args.limit)]
        result = run(flat, probe_workers=args.workers, permute_seconds=args.permute_seconds)
        text = json.dumps(result, indent=2, default=list)
        if args.json:
            args.json.write_text(text + "\n")
        print(text)
        return 0 if result.get("accepted") else 1

    return 1


if __name__ == "__main__":
    raise SystemExit(main())
