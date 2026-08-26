#!/usr/bin/env python3
"""Sweep small pragma-backed functions through m2c drafts and the candidate runner.

For every remaining owner that passes the size/family filters, this asks m2c
for a ``--valid-syntax`` draft, rewrites it into a few IDO-compilable
variants (raw ``u8 *`` field access, unknown types resolved several ways),
probes all variants per source in isolation, and gates the byte hits through
``COMPARE=1``.  Every attempt lands in the probe stats file, so the run also
measures how well mechanical drafts convert per family.

Usage:
    tools/sweep_targets.py --max-instructions 16                # everything small
    tools/sweep_targets.py --family call_sequence --limit 50    # a sample
    tools/sweep_targets.py --no-gate --source disasm/src/229E0.c
    tools/sweep_targets.py --fragment-range 17-32 --max-instructions 16
    tools/sweep_targets.py --skip-attempted --max-instructions 16
    tools/sweep_targets.py --near-miss --near-miss-parallel 4
    tools/sweep_targets.py --near-miss --near-miss-labels m2c:,manual: --near-miss-retry
    tools/sweep_targets.py --exclude-family multi_call_wrapper --min-family-remaining 5
    tools/sweep_targets.py --large --large-seconds 240

Sources with uncommitted changes are skipped: another session may be
mid-transaction in them.  A fragment-range sweep is exclusive: do not hand
decompile or probe owners in that band until the sweep has finished.

``--skip-attempted`` tracks skip state per ``(function, variant label)`` pair,
not per function: a variant spelling added to ``FAMILY_VARIANTS`` after an
owner's earlier reject is still swept, since only the exact label already
recorded in the stats file is skipped.

``--near-miss`` considers every recorded label by default (not only ``m2c:``
drafts); pass ``--near-miss-labels`` to restrict it to one or more prefixes.
It skips owners that already have a ``permute:`` attempt on file (a previous
near-miss run), unless ``--near-miss-retry`` is given, and
``--near-miss-parallel`` (default 2) runs multiple ``decomp-permuter``
budgets concurrently while still gating each result sequentially.  It also
skips a stats row whose function no longer owns a pragma (a later run
already accepted it) before spending a permuter budget on it.  The default
``--near-miss-min-similarity`` is 0.8.  Owners whose best recorded attempt is
``register_allocation_only`` or ``immediate_drift`` tend to need more search
time than a real semantic gap; ``--near-miss-kind-seconds`` (default 120,
versus the plain ``--near-miss-seconds`` default of 45) gives only those two
mismatch kinds that longer budget.

``--exclude-family`` (repeatable) drops one or more families from a sweep
entirely; ``--min-family-remaining`` drops any family whose remaining-owner
count in the listing is below the threshold (default 0, meaning off).  Use
these once a family's accepted rate saturates -- the per-family summary's
new ``remaining`` counter is the number to watch.

``--large`` switches to owners with more than ``--min-instructions``
(default 64) instructions, which m2c's ordinary ``--valid-syntax`` draft
usually cannot even compile.  It drafts with ``--gotos-only`` instead, tries
only the ``s32-s32``/``u8-void`` type spellings, and sends every
``probe_rejected`` result at similarity >= 0.7 straight into the near-miss
permuter machinery with a ``--large-seconds`` budget (default 180) instead
of gating the probe hits the way the ordinary sweep does.
"""

from __future__ import annotations

import argparse
import collections
import json
import os
import re
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
from collections.abc import Iterable

import dedupe_externs
import permute_candidate
import pragma_targets as targets
import try_pragma_compare as runner

FIELD_RE = re.compile(r"M2C_FIELD\(\s*([^,]+?)\s*,\s*([^,]+?)\s*,\s*([^)]+?)\s*\)")
UNK_GLOBAL_RE = re.compile(r"^extern M2C_UNK (\w+);", re.M)
UNK_FUNCTION_RE = re.compile(r"^M2C_UNK (\w+)\(([^)]*)\);(\s*/\* extern \*/)?", re.M)
UNK_TYPE_RE = re.compile(r"\bM2C_UNK\b")
EMPTY_BLOCK_RE = re.compile(r"\{\s*\}")
EXTERN_LINE_RE = re.compile(r"^\s*extern\b.*;\s*$")
COMMENT_LINE_RE = re.compile(r"^\s*/\*.*\*/\s*$")
FIRST_S32_ARG_RE = re.compile(
    r"(^\s*[\w\s*]+\bfunc_[0-9A-Fa-f]+\s*\(\s*)s32(?=\s+arg\d+\s*[,)])",
    re.M,
)

VARIANTS: dict[str, dict[str, str]] = {
    # unknown globals, unknown call returns, other unknown types
    "u8-void": {"global": "u8", "call": "void", "type": "s32"},
    "s32-s32": {"global": "s32", "call": "s32", "type": "s32"},
    "ptr-void": {"global": "u8 *", "call": "void", "type": "s32"},
    "u16-s32": {"global": "u16", "call": "s32", "type": "s32"},
    # Extra spellings are kept behind family/compile-failure selection.  They
    # are deliberately not part of the first pass for every owner: narrow
    # globals and pointer-returning calls can change IDO scheduling.
    "s16-void": {"global": "s16", "call": "void", "type": "s32"},
    "u32-void": {"global": "u32", "call": "void", "type": "s32"},
    "ptr-s32": {"global": "u8 *", "call": "s32", "type": "s32"},
    # Narrow temporary/argument spellings are useful for the byte-flag and
    # halfword families.  Keep them separate from the global-width guesses so
    # a retry can change one ABI hypothesis at a time.
    "u8-narrow-void": {"global": "u8", "call": "void", "type": "u8"},
    "s16-narrow-void": {"global": "u8", "call": "void", "type": "s16"},
    # Some range-checked byte lookups take a register-sized value in the
    # recovered draft even though the ABI masks it with ``andi 0xFF`` before
    # the bounds checks.  Rewriting just that first parameter to ``u8`` lets
    # IDO preserve the original argument home-store and register schedule.
    "u8-arg": {
        "global": "u8",
        "call": "void",
        "type": "s32",
        "arg": "u8",
        "drop_mask_temp": "1",
    },
}

# The ordinary pass deliberately stays small.  Probe statistics show that
# ``u8-void`` and ``s32-s32`` account for essentially all successful type
# spellings; the remaining hypotheses are useful only when a diagnostic points
# at them.  They remain in ``VARIANTS`` so a targeted retry can still use them.
DEFAULT_VARIANT_NAMES: tuple[str, ...] = ("u8-void", "s32-s32")

# These orders encode the narrow IDO spellings learned from accepted owners.
# They are candidate priorities, not ABI proof; every spelling still goes
# through an isolated probe and the sequential ROM gate.  ``u8-arg`` is kept
# only for bounded lookups, where an entry ``andi 0xff`` is evidence that the
# recovered argument itself may be byte-typed.
FAMILY_VARIANTS: dict[str, tuple[str, ...]] = {
    "bounded_lookup": ("u8-void", "s32-s32", "u8-arg"),
    "state_field_access": DEFAULT_VARIANT_NAMES,
    "constant_map": DEFAULT_VARIANT_NAMES,
    "direct_wrapper": DEFAULT_VARIANT_NAMES,
    "multi_call_wrapper": DEFAULT_VARIANT_NAMES,
    "call_sequence": DEFAULT_VARIANT_NAMES,
}


_CFE_ERROR_RE = re.compile(r"(?m)^cfe:\s+Error(?:\s+\d+)?\s*:\s*(.*)$")
_ROM_SYMBOL_RE = re.compile(r"\b(?:func_[0-9A-Fa-f]+|D_[0-9A-Fa-f]+)\b")
_SOURCE_FUNCTION_DEFINITION_RE = re.compile(
    r"(?m)^[^;{}\n]*\b(func_[0-9A-Fa-f]+)\s*\([^;{}\n]*\)\s*\{"
)
_SYMBOL_INDEX_CACHE: tuple[Path, int, dict[str, str]] | None = None


def _first_cfe_error(diagnostic: str | None) -> str | None:
    """Return the first CFE error message, excluding warnings and context."""
    text = diagnostic or ""
    match = _CFE_ERROR_RE.search(text)
    if match is not None:
        return match.group(1).strip()
    # Keep the helper useful for callers that pass only an already-extracted
    # compiler message. Real runner diagnostics always include ``cfe:``.
    if "cfe:" not in text.lower() and text.strip():
        return text.strip()
    return None


def _is_type_error(message: str) -> bool:
    """Whether a CFE message is actionable by changing a type spelling."""
    text = message.lower()
    # Undefined names, syntax errors, and redeclarations cannot be fixed by
    # trying another global/callee width. Diagnostics often contain the word
    # ``pointer`` in a preceding warning; only this first error is considered.
    if any(token in text for token in (
        "undefined", "syntax", "redeclaration", "redefinition",
        "undeclared", "too many arguments", "too few arguments",
    )):
        return False
    return any(token in text for token in (
        "operand", "pointer", "conversion", "convert", "dereference",
        "selector requires", "lvalue", "type for", "argument",
        "number of arguments", "incompatible", "unknown type",
    ))


def compile_failure_variant_names(diagnostic: str | None) -> tuple[str, ...]:
    """Choose extra type spellings from a compiler diagnostic sample."""
    message = _first_cfe_error(diagnostic)
    if message is None or not _is_type_error(message):
        return ()
    text = message.lower()
    names: list[str] = []
    if any(token in text for token in (
        "pointer", "incompatible", "conversion", "dereference", "operand",
        "selector requires",
    )):
        names.extend(("ptr-void", "ptr-s32", "u32-void"))
    if any(token in text for token in ("short", "16", "halfword", "s16")):
        names.append("s16-void")
    if any(token in text for token in ("unknown type", "undeclared", "m2c_unk")):
        names.extend(("s32-s32", "u16-s32"))
    return tuple(dict.fromkeys(name for name in names if name in VARIANTS))


def mismatch_variant_names(attempt: dict[str, object]) -> tuple[str, ...]:
    """Select type retries from an isolated instruction-diff diagnostic.

    The normal pass should not spend probes on every ABI width.  A shift by
    sixteen, however, is strong evidence that m2c inferred a halfword field or
    temporary, so request the narrow spellings only for that owner.  This is
    deliberately conservative: an ordinary ``sll``/``sra`` or a missing diff
    does not expand the matrix.
    """
    if attempt.get("status") != "probe_rejected":
        return ()
    diffs = attempt.get("assembly_diff")
    if not isinstance(diffs, list):
        return ()
    instruction_text: list[str] = []
    for diff in diffs:
        if not isinstance(diff, dict):
            continue
        for key in ("expected", "actual", "expected_instruction_text", "actual_instruction_text"):
            value = diff.get(key)
            if isinstance(value, str):
                instruction_text.append(value.lower())
    joined = "\n".join(instruction_text)
    if not re.search(r"\b(?:sll|sra)\b[^\n]*,\s*(?:16|0x10)\b", joined):
        return ()
    return ("s16-void", "s16-narrow-void")


_IMMEDIATE_RE = re.compile(r"(?<![A-Za-z0-9_])-?(?:0x[0-9A-Fa-f]+|[0-9]+)(?![A-Za-z0-9_])")
_IMMEDIATE_REPAIR_OPS = {
    "addiu", "ori", "andi", "slti", "sltiu",
    "lb", "lbu", "lh", "lhu", "lw", "lwc1", "sb", "sh", "sw", "swc1",
}


def _parse_immediate(token: str) -> int | None:
    try:
        return int(token, 0)
    except ValueError:
        try:
            return int(token, 10)
        except ValueError:
            return None


def _replace_immediate_occurrence(
    candidate: str, actual_value: int, expected_value: int, occurrence: int
) -> str | None:
    """Replace one visible candidate literal while preserving its spelling."""
    seen = 0

    def replacement(match: re.Match[str]) -> str:
        nonlocal seen
        value = _parse_immediate(match.group(0))
        if value != actual_value:
            return match.group(0)
        if seen != occurrence:
            seen += 1
            return match.group(0)
        seen += 1
        token = match.group(0)
        if token.lower().startswith("0x"):
            prefix = "0X" if token.startswith("0X") else "0x"
            sign = "-" if expected_value < 0 else ""
            return f"{sign}{prefix}{abs(expected_value):X}" if prefix == "0X" else f"{sign}{prefix}{abs(expected_value):x}"
        return str(expected_value)

    rewritten = _IMMEDIATE_RE.sub(replacement, candidate)
    return rewritten if rewritten != candidate else None


def immediate_repair_candidates(
    candidate: str, attempt: dict[str, object], *, limit: int = 8
) -> list[tuple[str, str]]:
    """Generate literal-only repairs for a same-opcode immediate drift.

    This is intentionally a narrow rule, not a semantic decompiler.  The
    mismatch classifier has already established that the whole instruction
    stream differs only in immediates; here we require the per-instruction
    expected/actual opcode to agree and replace only a literal that is visibly
    present in the candidate text.  The runner remains the authority.
    """
    if attempt.get("status") != "probe_rejected" or attempt.get("mismatch_kind") != "immediate_drift":
        return []
    diffs = attempt.get("assembly_diff")
    if not isinstance(diffs, list):
        return []
    repairs: list[tuple[str, str]] = []
    seen: set[str] = set()
    for diff_index, diff in enumerate(diffs):
        if not isinstance(diff, dict):
            continue
        expected = diff.get("expected") or diff.get("expected_instruction_text")
        actual = diff.get("actual") or diff.get("actual_instruction_text")
        if not isinstance(expected, str) or not isinstance(actual, str):
            continue
        expected_op = expected.strip().split(None, 1)[0].lower() if expected.strip() else ""
        actual_op = actual.strip().split(None, 1)[0].lower() if actual.strip() else ""
        if expected_op != actual_op or expected_op not in _IMMEDIATE_REPAIR_OPS:
            continue
        expected_values = [value for value in (_parse_immediate(t) for t in _IMMEDIATE_RE.findall(expected)) if value is not None]
        actual_values = [value for value in (_parse_immediate(t) for t in _IMMEDIATE_RE.findall(actual)) if value is not None]
        if len(expected_values) != len(actual_values):
            continue
        for immediate_index, (expected_value, actual_value) in enumerate(zip(expected_values, actual_values)):
            if expected_value == actual_value or actual_value == 0:
                continue
            occurrences = [
                match for match in _IMMEDIATE_RE.finditer(candidate)
                if _parse_immediate(match.group(0)) == actual_value
            ]
            for occurrence in range(min(len(occurrences), limit - len(repairs))):
                rewritten = _replace_immediate_occurrence(
                    candidate, actual_value, expected_value, occurrence
                )
                if rewritten is None or rewritten in seen:
                    continue
                seen.add(rewritten)
                repairs.append((f"{diff_index}-{immediate_index}-{occurrence}", rewritten))
                if len(repairs) >= limit:
                    return repairs
    return repairs


_STACK_SLOT_DECL_RE = re.compile(
    r"^(?P<indent>\s*)(?P<type>(?:(?:const\s+)?(?:u|s)?(?:8|16|32|64)|f(?:32|64)|void\s*\*))"
    r"\s+(?P<name>sp[0-9A-Fa-f]+)(?P<suffix>\s*(?:=\s*[^;]+)?;)\s*$"
)


def stack_slot_order_candidate(
    candidate: str, attempt: dict[str, object]
) -> str | None:
    """Reorder m2c stack-local declarations by ascending ABI slot.

    IDO's local allocation is sensitive to declaration order.  m2c commonly
    emits the same fixed locals in descending slot order (``sp28, sp26,
    sp24``), while the matching source declares them from the lowest slot up.
    This is a narrow source-shape retry for an existing mismatch; it does not
    infer or alter types, expressions, or call order.
    """
    if attempt.get("status") != "probe_rejected":
        return None
    if attempt.get("mismatch_kind") not in {
        "immediate_drift", "operand_or_scheduling_drift", "instruction_drift",
    }:
        return None
    lines = candidate.splitlines(keepends=True)
    # Only touch the initial local declaration block in each function.  Once
    # a statement or a non-declaration is seen, later ``sp`` names may be
    # nested-scope locals and moving them would change source semantics.
    changed = False
    index = 0
    while index < len(lines):
        match = _STACK_SLOT_DECL_RE.match(lines[index])
        if match is None:
            index += 1
            continue
        start = index
        declarations: list[tuple[int, str]] = []
        while index < len(lines):
            current = _STACK_SLOT_DECL_RE.match(lines[index])
            if current is None:
                break
            slot = int(current.group("name")[2:], 16)
            declarations.append((slot, lines[index]))
            index += 1
        if len(declarations) < 2:
            continue
        ordered = sorted(declarations, key=lambda item: item[0])
        if [line for _, line in declarations] != [line for _, line in ordered]:
            lines[start:index] = [line for _, line in ordered]
            changed = True
    return "".join(lines) if changed else None


def rewrite_draft(draft: str, variant: dict[str, str]) -> str | None:
    """Turn an m2c ``--valid-syntax`` draft into plain C for one type guess."""
    if "M2C_ERROR" in draft:
        return None
    text = FIELD_RE.sub(lambda m: f"(*({m.group(2)})((u8 *)({m.group(1)}) + ({m.group(3)})))", draft)
    text = UNK_GLOBAL_RE.sub(lambda m: f"extern {variant['global']} {m.group(1)};", text)
    text = UNK_FUNCTION_RE.sub(lambda m: f"extern {variant['call']} {m.group(1)}({m.group(2)});", text)
    text = UNK_TYPE_RE.sub(variant["type"], text)
    if variant.get("arg") == "u8":
        text = FIRST_S32_ARG_RE.sub(r"\1u8", text, count=1)
        if variant.get("drop_mask_temp") == "1":
            text = re.sub(r"\n\s*s32\s+temp_a0;\n", "\n", text, count=1)
            text = re.sub(r"\n\s*temp_a0\s*=\s*arg0\s*&\s*0xFF;\n", "\n", text, count=1)
            text = re.sub(r"\btemp_a0\b", "arg0", text)
    text = re.sub(r"\s*/\* extern \*/", "", text)
    if "M2C_" in text:
        return None
    return text.strip() + "\n"


def compile_failure_candidates(
    draft: str,
    diagnostics: Iterable[str | None],
    *,
    function: str | None = None,
    source_path: Path | None = None,
) -> list[tuple[str, str]]:
    """Rewrite a draft using type spellings suggested by compile diagnostics.

    A source can produce several compile failures for the same m2c draft
    (one per first-pass variant).  Collecting the diagnostics first lets us
    union their targeted retry spellings while deduplicating identical C
    bodies.  This keeps the retry pass small, but still lets a later,
    more-specific diagnostic add a useful ``s16``/pointer rewrite.
    """
    candidates: list[tuple[str, str]] = []
    seen: set[str] = set()
    for diagnostic in diagnostics:
        for name in compile_failure_variant_names(diagnostic):
            code = rewrite_draft(draft, VARIANTS[name])
            if code is None:
                continue
            if function is not None and source_path is not None:
                code = prepare_candidate_declarations(function, source_path, code)
            if code in seen:
                continue
            seen.add(code)
            candidates.append((f"m2c:{name}:compile-retry", code))
    return candidates


def _is_prototype_line(line: str) -> bool:
    """Whether a leading declaration-block line is a bare function prototype.

    Matches ``<type> (*name(args))(args);`` (a function-pointer-returning
    prototype) and plain ``<ret> name(args);`` -- both without the
    ``extern`` keyword (handled separately by ``EXTERN_LINE_RE``) but
    structurally a declaration rather than the start of a definition, which
    opens a ``{`` body instead of ending in ``;``.
    """
    text = line.strip()
    if not text or "{" in text or "}" in text:
        return False
    return text.endswith(";") and "(" in text and not text.startswith("extern")


def _declaration_symbol(line: str) -> str | None:
    """Return the symbol name one extern/prototype declaration line declares."""
    text = line.strip().rstrip(";").strip()
    if not text:
        return None
    match = re.search(r"\(\*\s*(\w+)\s*\(", text)
    if match:
        return match.group(1)
    paren = text.find("(")
    head = text[:paren] if paren != -1 else text
    tokens = re.findall(r"\w+", head)
    return tokens[-1] if tokens else None


def _declaration_symbols(declarations: str) -> dict[str, str]:
    """Map each symbol declared in a declarations block to its exact line."""
    symbols: dict[str, str] = {}
    for line in declarations.splitlines():
        line = line.strip()
        if not line:
            continue
        name = _declaration_symbol(line)
        if name:
            symbols[name] = line
    return symbols


def split_candidate_declarations(code: str) -> tuple[str, str]:
    """Separate leading m2c externs/prototypes so compatible gate batches can share them."""
    declarations: list[str] = []
    body: list[str] = []
    in_prefix = True
    for line in code.splitlines():
        if in_prefix and (
            not line.strip()
            or COMMENT_LINE_RE.match(line)
            or EXTERN_LINE_RE.match(line)
            or _is_prototype_line(line)
        ):
            if line.strip():
                # m2c labels each draft with a comment. It is useful context
                # when printed, but not a declaration and not needed in the
                # probe source prefix.
                if not COMMENT_LINE_RE.match(line):
                    declarations.append(line.strip())
            continue
        in_prefix = False
        body.append(line)
    unique = list(dict.fromkeys(declarations))
    declaration_text = "\n".join(unique) + ("\n" if unique else "")
    body_text = "\n".join(body).strip() + "\n"
    return declaration_text, body_text


def _symbol_index_declarations() -> dict[str, str]:
    """Read the generated cross-source declaration index once per mtime."""
    global _SYMBOL_INDEX_CACHE
    try:
        path = targets.repository_symbol_header()
        if path is None or not path.exists():
            return {}
        mtime = path.stat().st_mtime_ns
    except OSError:
        return {}
    if _SYMBOL_INDEX_CACHE is not None:
        cached_path, cached_mtime, cached = _SYMBOL_INDEX_CACHE
        if cached_path == path and cached_mtime == mtime:
            return cached
    declarations: dict[str, str] = {}
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        name = _declaration_symbol(line)
        if name and _ROM_SYMBOL_RE.fullmatch(name):
            declarations[name] = line.rstrip(";") + ";"
    _SYMBOL_INDEX_CACHE = (path, mtime, declarations)
    return declarations


def _owner_symbol_declarations(
    source_path: Path, function: str,
) -> tuple[int, dict[str, list[tuple[int, str]]]]:
    """Return the pragma offset and declarations visible in the owner file."""
    try:
        text = source_path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        # Discovery tests and callers that provide a synthetic owner may not
        # materialize the source path. In that case the candidate's own
        # declarations remain untouched and the real index is still usable.
        return 0, {}
    pragma = re.search(
        rf'^#pragma GLOBAL_ASM\("asm/us/nonmatchings/[^\"]+/{re.escape(function)}\.s"\)',
        text,
        re.MULTILINE,
    )
    cutoff = pragma.start() if pragma is not None else len(text)
    declarations: dict[str, list[tuple[int, str]]] = collections.defaultdict(list)
    # ``pragma_targets`` already has the conservative extern parser used for
    # the index. Reuse its normalized spelling, but retain source positions so
    # declarations below the pragma can be injected before the replacement.
    for match in targets._EXTERN_DECL_RE.finditer(text):
        declaration = targets._normalise_declaration("extern " + match.group(1)) + ";"
        names = _ROM_SYMBOL_RE.findall(declaration)
        if len(names) == 1:
            declarations[names[0]].append((match.start(), declaration))
    for match in _SOURCE_FUNCTION_DEFINITION_RE.finditer(text):
        name = match.group(1)
        declaration = text[match.start() : match.end() - 1].strip() + ";"
        declarations[name].append((match.start(), targets._normalise_declaration(declaration)))
    return cutoff, declarations


def prepare_candidate_declarations(
    function: str, source_path: Path, candidate: str,
) -> str:
    """Make an m2c body compile in the real owner source context.

    m2c sees the whole owner while drafting, so it may omit an ``extern`` for
    a symbol declared later in that file or supplied only by the generated
    repository index. The isolated probe, however, replaces the pragma in
    source order. Remove candidate declarations that conflict with any
    owner-local spelling, inject the exact below-pragma owner declaration, and
    use the index spelling only for symbols absent from the owner entirely.
    """
    declarations_text, body = split_candidate_declarations(candidate)
    candidate_lines = [line for line in declarations_text.splitlines() if line.strip()]
    cutoff, owner_declarations = _owner_symbol_declarations(source_path, function)
    index_declarations = _symbol_index_declarations()

    kept: list[str] = []
    declared_by_candidate: set[str] = set()
    for line in candidate_lines:
        name = _declaration_symbol(line)
        if name is None:
            kept.append(line)
            continue
        declared_by_candidate.add(name)
        # Any owner-local declaration must win over m2c's context-derived or
        # variant-derived spelling. This prevents the common below-pragma
        # redeclaration failure while preserving guesses for truly unknown
        # cross-source symbols.
        if name in owner_declarations:
            continue
        kept.append(line)

    required: list[str] = []
    seen = set(kept)
    for name in _ROM_SYMBOL_RE.findall(candidate):
        if name == function:
            continue
        entries = owner_declarations.get(name, [])
        below = [declaration for position, declaration in entries if position >= cutoff]
        if below:
            declaration = below[0]
        elif entries:
            # Already visible above the pragma; no prefix is needed.
            continue
        elif name not in declared_by_candidate:
            declaration = index_declarations.get(name)
            if declaration is None:
                continue
        else:
            continue
        if declaration not in seen:
            seen.add(declaration)
            required.append(declaration)

    prefix = "\n".join(kept + required)
    return (prefix + "\n" if prefix else "") + body


def partition_gate_batches(
    gate_batches: dict[str, list[tuple[str, str, str]]],
    *,
    source_rel: str,
    family_of: dict[str, str],
    summary: dict[str, collections.Counter],
) -> list[tuple[str, list[tuple[str, str, str]]]]:
    """Order gate batches by size, deferring any whose declarations conflict.

    Two declaration blocks that declare the same symbol with different text
    cannot both be installed in the same source: m2c commonly infers a
    different prototype for the same callee across different owners'
    drafts (see the runner's incremental installer, which otherwise has to
    discover this the hard way per batch).  The larger group (ties: first
    seen) gates first; a smaller group that conflicts with an
    already-committed prototype is deferred instead of being sent through a
    combined install that is doomed to fail to compile.
    """
    batch_order = sorted(gate_batches.items(), key=lambda item: -len(item[1]))
    committed_symbols: dict[str, str] = {}
    active: list[tuple[str, list[tuple[str, str, str]]]] = []
    for declarations, batch in batch_order:
        symbols = _declaration_symbols(declarations)
        conflicts = {
            name: text
            for name, text in symbols.items()
            if name in committed_symbols and committed_symbols[name] != text
        }
        if conflicts:
            functions = [function for function, _, _ in batch]
            print(
                f"{source_rel}: prototype conflict on {', '.join(sorted(conflicts))}; "
                f"deferring {', '.join(functions)}",
                file=sys.stderr,
            )
            for function in functions:
                summary[family_of[function]]["deferred_conflicting_prototype"] += 1
            continue
        committed_symbols.update(symbols)
        active.append((declarations, batch))
    return active


def _accumulate_timing(total: dict[str, float], result: dict[str, object]) -> None:
    """Add one runner result's ``timing`` into a sweep-wide running total."""
    timing = result.get("timing")
    if not isinstance(timing, dict):
        return
    for key in ("probe_seconds", "gate_seconds", "gate_runs", "install_compiles"):
        value = timing.get(key)
        if isinstance(value, (int, float)):
            total[key] = total.get(key, 0) + value


def padding_retry(attempt: dict[str, object]) -> int | None:
    """Return the C_FUNCTION_PADDING byte count that would complete a prefix match.

    The runner reports ``symbol_size_drift`` when every byte of the shorter
    symbol matches and only the baseline's trailing alignment nops are
    missing; the declarative padding marker reproduces exactly those bytes.
    """
    if attempt.get("mismatch_kind") != "symbol_size_drift" or attempt.get("diff_offsets"):
        return None
    expected = attempt.get("expected_size")
    actual = attempt.get("actual_size")
    if not isinstance(expected, int) or not isinstance(actual, int) or expected <= actual:
        return None
    if attempt.get("expected_tail_kind") not in {"jr_nop_plus_alignment", "nop_only_tail"}:
        return None
    padding = expected - actual
    return padding if padding % 4 == 0 else None


def duplicate_tail_helper_count(attempt: dict[str, object]) -> int | None:
    """Return the number of empty helpers needed for a duplicate return tail.

    A duplicate ``jr $ra``/delay-slot pair is emitted as a real neighboring
    function by IDO, not as ``C_FUNCTION_PADDING``.  The runner can therefore
    safely retry a clean prefix match by appending one empty helper for every
    missing eight-byte pair.  This remains a candidate until the MCP probes
    and gates it, just like the alignment-padding retry above.
    """
    if (
        attempt.get("mismatch_kind") != "symbol_size_drift"
        or attempt.get("diff_offsets")
        or attempt.get("expected_tail_kind") != "duplicate_jr_nop_tail"
    ):
        return None
    expected = attempt.get("expected_size")
    actual = attempt.get("actual_size")
    if not isinstance(expected, int) or not isinstance(actual, int) or expected <= actual:
        return None
    missing = expected - actual
    if missing % 8:
        return None
    return missing // 8


def append_duplicate_tail_helpers(function: str, code: str, count: int) -> str:
    """Append ``count`` uniquely named empty helpers to a candidate body."""
    helpers = []
    for index in range(count):
        suffix = "_padding" if index == 0 else f"_padding{index + 1}"
        helpers.append(f"void {function}{suffix}(void) {{}}")
    return code.rstrip() + "\n" + "\n".join(helpers) + "\n"


FUNCPTR_PROTOTYPE_RE = re.compile(r"\(\*\s*(\w+)\s*\([^)]*\)\)\s*\(([^)]*)\)\s*;")


def callee_unprototyped_variant(code: str) -> str | None:
    """Erase a function-pointer-returning prototype's callee parameter list.

    m2c infers a different parameter list for the same shared callee from
    each owner's usage -- for example ``s32 (*func_80003240(s32 *))(s32);``
    in one owner versus ``...)(s32 *);`` in another -- which makes a
    combined install across those owners fail to compile even though each
    compiles alone.  Rewriting the callee's parameter list to ``()``
    sidesteps the conflict; this is only a hypothesis, so whether the body
    still matches is left entirely to the probe like every other type
    guess.  Returns ``None`` when ``code`` has no such prototype.
    """
    if not FUNCPTR_PROTOTYPE_RE.search(code):
        return None

    def erase_callee_params(match: re.Match[str]) -> str:
        text = match.group(0)
        params = match.group(2)
        offset = match.start(2) - match.start(0)
        return text[:offset] + text[offset + len(params):]

    rewritten = FUNCPTR_PROTOTYPE_RE.sub(erase_callee_params, code)
    return rewritten if rewritten != code else None


def draft_variants(
    function: str,
    context: bool = True,
    family: str | None = None,
    variant_names: tuple[str, ...] | None = None,
    extra_m2c_args: tuple[str, ...] = (),
    label_prefix: str = "m2c",
) -> tuple[list[tuple[str, str]], str | None]:
    """Return ``[(label, code)]`` variants for one function and the raw draft.

    ``extra_m2c_args``/``label_prefix`` let ``--large`` mode reuse this same
    command-building and rewrite logic with ``--gotos-only`` and an
    ``m2c-gotos:`` label instead of duplicating it; see ``draft_large_variants``.
    """
    owner = targets.require_owner(function)
    context_path = targets.preprocessed_context(owner) if context else None
    command = [sys.executable, str(targets.M2C_SCRIPT), "--target", "mips-ido-c", "--valid-syntax", "--globals", "used"]
    command += list(extra_m2c_args)
    if context_path is not None:
        command += ["--context", str(context_path)]
    result = subprocess.run(command + [str(owner.asm_path)], text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=60)
    if result.returncode != 0 or not result.stdout.strip():
        return [], None
    draft = result.stdout
    seen: set[str] = set()
    variants: list[tuple[str, str]] = []
    names = variant_names or FAMILY_VARIANTS.get(family or "", DEFAULT_VARIANT_NAMES)
    for name in names:
        variant = VARIANTS[name]
        code = rewrite_draft(draft, variant)
        if code is None or code in seen:
            continue
        code = prepare_candidate_declarations(function, owner.source_path, code)
        seen.add(code)
        variants.append((f"{label_prefix}:{name}", code))
        unprototyped = callee_unprototyped_variant(code)
        if unprototyped is not None and unprototyped not in seen:
            seen.add(unprototyped)
            variants.append((f"{label_prefix}:{name}:callee-unprototyped", unprototyped))
    return variants, draft


# ``--large`` only tries the two narrowest, most broadly useful type
# spellings: a wide draft matrix is not worth the m2c/compile cost for an
# owner this large, and the near-miss permuter is what actually closes the
# gap, not the draft's exact type guess.
LARGE_VARIANT_NAMES: tuple[str, ...] = ("s32-s32", "u8-void")


def draft_large_variants(function: str, context: bool = True) -> tuple[list[tuple[str, str]], str | None]:
    """Draft an owner too large for the ordinary sweep with m2c ``--gotos-only``.

    Past roughly 64 instructions, m2c's ``--valid-syntax`` structured
    control-flow recovery commonly fails to produce a draft at all;
    ``--gotos-only`` (``pragma_targets.DRAFT_VARIANTS["m2c-gotos"]``) keeps
    the draft close to the assembly's real branches instead.
    """
    return draft_variants(
        function,
        context=context,
        variant_names=LARGE_VARIANT_NAMES,
        extra_m2c_args=tuple(targets.DRAFT_VARIANTS["m2c-gotos"]),
        label_prefix="m2c-gotos",
    )


def template_variants_for(
    function: str, skip_attempts: set[tuple[str, str]] | None,
) -> list[tuple[str, str]]:
    """``template:...`` candidates for ``function`` (``template_transfer.py``), self-contained like an m2c block.

    ``template_transfer`` is imported lazily here, not at module scope: it
    imports ``split_candidate_declarations`` from this module, and a
    top-level import in both directions would be circular.  A template
    candidate's declarations and body are concatenated into one self-
    contained text -- the same shape an m2c draft already has for this
    module's own probe pass -- so it needs no special handling downstream;
    ``split_candidate_declarations`` recovers the two pieces again for the
    gate pass exactly as it does for any other candidate.
    """
    import template_transfer
    try:
        candidates = template_transfer.generate_template_candidates(function)
    except (KeyError, OSError) as error:
        print(f"{function}: template variant error: {error}", file=sys.stderr)
        return []
    variants: list[tuple[str, str]] = []
    for candidate in candidates:
        if candidate.outcome != "candidate":
            continue
        if skip_attempts is not None and (function, candidate.label) in skip_attempts:
            continue
        variants.append((candidate.label, candidate.declarations + candidate.code))
    return variants


def previously_attempted(stats_path: Path = targets.STATS_PATH, label_prefix: str = "m2c:") -> set[str]:
    """Functions that already have sweep attempts recorded in the stats file."""
    attempted: set[str] = set()
    if not stats_path.exists():
        return attempted
    for line in stats_path.read_text(encoding="utf-8").splitlines():
        try:
            record = json.loads(line)
        except json.JSONDecodeError:
            continue
        for attempt in record.get("attempts", []):
            label = attempt.get("label") or ""
            if label.startswith(label_prefix) and attempt.get("function"):
                attempted.add(str(attempt["function"]))
    return attempted


def previously_attempted_labels(
    stats_path: Path = targets.STATS_PATH, label_prefix: str = "m2c:"
) -> set[tuple[str, str]]:
    """``(function, label)`` pairs that already have a sweep attempt on file.

    Unlike ``previously_attempted``, this is keyed per variant spelling: a
    function that only has an old-label reject on file is still swept for a
    new label added later to ``FAMILY_VARIANTS``, because only the exact
    ``(function, label)`` pair already attempted is skipped.
    """
    attempted: set[tuple[str, str]] = set()
    if not stats_path.exists():
        return attempted
    for line in stats_path.read_text(encoding="utf-8").splitlines():
        try:
            record = json.loads(line)
        except json.JSONDecodeError:
            continue
        for attempt in record.get("attempts", []):
            label = attempt.get("label") or ""
            function = attempt.get("function")
            if label.startswith(label_prefix) and function:
                attempted.add((str(function), label))
    return attempted


def parse_fragment_range(value: str) -> tuple[int, int]:
    """Parse the inclusive ``START-END`` fragment selector used by sweeps."""
    match = re.fullmatch(r"(\d+)-(\d+)", value.strip())
    if match is None:
        raise ValueError("fragment range must be START-END")
    start, end = (int(match.group(1)), int(match.group(2)))
    if start > end:
        raise ValueError("fragment range start must not exceed end")
    return start, end


def _fragment_number(source: str) -> int | None:
    match = re.search(r"(?:^|/)fragments/(\d+)(?:/|$)", source.replace("\\", "/"))
    return int(match.group(1)) if match else None


def _sweep_listing(
    *,
    max_instructions: int | None,
    min_instructions: int | None,
    family: str | None,
    source: str | None,
    limit: int,
    fragment_range: tuple[int, int] | None,
) -> dict[str, object]:
    """Select sweep rows without truncating a fragment band prematurely.

    ``pragma_targets.list_targets`` applies ``limit`` after its global sort.
    Applying a fragment filter to that already-truncated list silently drops
    owners in the requested band when the repository has more than ``limit``
    remaining owners.  Fetch the complete owner index for a band selection,
    then apply the user's limit after filtering.
    """
    listing_limit = limit
    if fragment_range is not None:
        listing_limit = max(limit, len(targets.owner_index()))
    listing = targets.list_targets(
        source=source,
        family=family,
        max_instructions=max_instructions,
        min_instructions=min_instructions,
        limit=listing_limit,
    )
    rows = list(listing["targets"])
    if fragment_range is None:
        return listing

    start, end = fragment_range
    band_rows = [
        row
        for row in rows
        if isinstance(row, dict)
        and (fragment := _fragment_number(str(row["source"]))) is not None
        and start <= fragment <= end
    ]
    selected = band_rows[:max(0, limit)]
    return {
        **listing,
        "matched": len(selected),
        "available_in_range": len(band_rows),
        "targets": selected,
        "truncated": len(band_rows) > max(0, limit),
    }


def _stats_records(stats_path: Path = targets.STATS_PATH) -> list[dict[str, object]]:
    records: list[dict[str, object]] = []
    if not stats_path.exists():
        return records
    for line in stats_path.read_text(encoding="utf-8").splitlines():
        try:
            value = json.loads(line)
        except json.JSONDecodeError:
            continue
        if isinstance(value, dict):
            records.append(value)
    return records


def _near_miss_sort_key(attempt: dict[str, object]) -> tuple[float, str]:
    score = attempt.get("similarity_score")
    return (
        -float(score) if isinstance(score, (int, float)) else 0.0,
        str(attempt.get("function") or ""),
    )


def near_miss(
    *,
    stats_path: Path = targets.STATS_PATH,
    minimum_similarity: float = 0.8,
    seconds: float = 45.0,
    kind_seconds: float | None = 120.0,
    threads: int = 4,
    workers: int | None = None,
    limit: int | None = None,
    label_prefixes: tuple[str, ...] | None = None,
    skip_permuted: bool = True,
    parallel: int = 2,
) -> dict[str, object]:
    """Permute high-scoring rejects, then gate only score-0 outputs.

    ``label_prefixes`` selects which recorded labels are eligible; ``None``
    (the default) considers any label with a recorded candidate and
    similarity score, not only ``m2c:`` drafts.  ``skip_permuted`` excludes
    owners that already have a ``permute:``-labeled attempt on file (a
    previous near-miss run over the same candidate).  ``parallel`` (default
    2) runs that many ``decomp-permuter`` budgets concurrently; gating a
    score-0 output still happens on the main thread as each permute job
    completes, since it holds the runner's cross-process transaction lock.

    A candidate whose owner no longer holds a ``GLOBAL_ASM`` pragma (a later
    full-gate acceptance from a different run solved it since these stats
    were recorded) is skipped before it ever reaches the permuter and is
    counted in the result's ``skipped_solved``.  ``kind_seconds`` (default
    120, versus the plain ``seconds`` default of 45) gives a longer budget
    than ``seconds`` to owners whose recorded best attempt is
    ``register_allocation_only`` or ``immediate_drift`` -- these are cases
    where the permuter is reordering declarations/temporaries rather than
    searching a real semantic gap, so a longer budget tends to pay off.
    ``minimum_similarity`` defaults to 0.8.  The permute-then-gate loop
    itself is ``permute_and_gate``, shared with ``--large`` mode.
    """
    grouped: dict[str, dict[str, object]] = {}
    permuted_functions: set[str] = set()
    for record in _stats_records(stats_path):
        source = record.get("source")
        for attempt in record.get("attempts", []):
            if not isinstance(attempt, dict):
                continue
            function = attempt.get("function")
            label = str(attempt.get("label") or "")
            status = str(attempt.get("status") or "")
            score = attempt.get("similarity_score")
            candidate = attempt.get("candidate")
            if isinstance(function, str) and label.startswith("permute:"):
                permuted_functions.add(function)
            if not isinstance(function, str):
                continue
            if label_prefixes is not None:
                if not any(label.startswith(prefix) for prefix in label_prefixes):
                    continue
            elif not label:
                continue
            # A full-gate acceptance solves the owner for this pass.  An
            # isolated probe_match is deliberately not considered accepted:
            # it still needs the sequential gate and may be a useful near
            # miss if its score is recorded.
            if not isinstance(score, (int, float)):
                continue
            if float(score) < minimum_similarity or not isinstance(candidate, str) or not candidate.strip():
                continue
            row = grouped.setdefault(function, {
                "function": function,
                "source": source,
                "candidate": candidate,
                "declarations": attempt.get("declarations"),
                "label": label,
                "similarity_score": float(score),
                "best_status": status,
                "mismatch_kind": attempt.get("mismatch_kind"),
                "statuses": set(),
            })
            statuses = row["statuses"]
            assert isinstance(statuses, set)
            statuses.add(status)
            current_score = float(row["similarity_score"])
            current_status = str(row.get("best_status"))
            if (
                float(score) > current_score
                or (
                    float(score) == current_score
                    and status == "accepted"
                    and current_status != "accepted"
                )
            ):
                row.update({
                    "source": source,
                    "candidate": candidate,
                    "declarations": attempt.get("declarations"),
                    "label": label,
                    "similarity_score": float(score),
                    "best_status": status,
                    "mismatch_kind": attempt.get("mismatch_kind"),
                })

    candidates = [
        row for row in grouped.values()
        if str(row.get("best_status")) != "accepted"
    ]
    skipped_permuted = 0
    if skip_permuted:
        before = len(candidates)
        candidates = [row for row in candidates if str(row["function"]) not in permuted_functions]
        skipped_permuted = before - len(candidates)
    candidates.sort(key=lambda row: (-float(row["similarity_score"]), str(row["function"])))

    # A stats row can outlive the pragma it was recorded against: a later
    # run (this one's own earlier source, or a different session) may have
    # already installed a full-gate winner for the same function.  Check
    # ownership before spending a permuter budget on it, not after --
    # ``require_owner`` is cheap, ``decomp-permuter`` is not.
    owned_candidates: list[dict[str, object]] = []
    skipped_solved = 0
    for row in candidates:
        try:
            targets.require_owner(str(row["function"]))
        except KeyError:
            skipped_solved += 1
            continue
        owned_candidates.append(row)
    candidates = owned_candidates

    if limit is not None:
        candidates = candidates[:max(0, limit)]

    result = permute_and_gate(
        candidates, seconds=seconds, kind_seconds=kind_seconds, threads=threads, workers=workers, parallel=parallel,
    )
    return {
        "candidates": len(candidates),
        "accepted": result["accepted"],
        "attempts": result["attempts"],
        "skipped_permuted": skipped_permuted,
        "skipped_solved": skipped_solved,
    }


_LONGER_BUDGET_KINDS = {"register_allocation_only", "immediate_drift"}


def permute_and_gate(
    rows: list[dict[str, object]],
    *,
    seconds: float,
    threads: int,
    workers: int | None,
    parallel: int,
    kind_seconds: float | None = None,
) -> dict[str, object]:
    """Permute each row's candidate, then gate any score-0 output.

    Shared by ``near_miss`` and ``--large`` mode.  Each row needs
    ``function``, ``candidate``, and ``label`` keys, plus the optional
    ``declarations``/``similarity_score``/``mismatch_kind`` keys ``near_miss``
    already carries from stats rows.  ``parallel`` runs that many
    ``decomp-permuter`` budgets concurrently; gating a score-0 output still
    happens on the main thread as each permute job completes, since it holds
    the runner's cross-process transaction lock.  ``kind_seconds``, when
    given, is the budget for a row whose ``mismatch_kind`` is
    ``register_allocation_only`` or ``immediate_drift`` instead of
    ``seconds`` -- the permuter tends to need more search time there than
    for a real semantic gap.
    """

    def permute_job(row: dict[str, object]) -> tuple[dict[str, object], dict[str, object] | None, str | None]:
        function = str(row["function"])
        candidate = str(row["candidate"])
        budget = seconds
        if kind_seconds is not None and row.get("mismatch_kind") in _LONGER_BUDGET_KINDS:
            budget = kind_seconds
        try:
            permutation = permute_candidate.permute(
                function,
                candidate,
                declarations=row.get("declarations") if isinstance(row.get("declarations"), str) else None,
                seconds=budget,
                threads=threads,
                stop_on_zero=True,
            )
        except (FileNotFoundError, KeyError, RuntimeError, ValueError) as error:
            return row, None, str(error)
        return row, permutation, None

    def record_permute_outcome(
        row: dict[str, object],
        *,
        status: str,
        candidate: str,
        budget: float,
        permutation: dict[str, object] | None = None,
        error: str | None = None,
    ) -> None:
        """Persist permuter outcomes so later near-miss runs can skip them."""
        function = str(row["function"])
        try:
            source_path = targets.require_owner(function).source_path
        except KeyError:
            return
        outputs = permutation.get("outputs") if isinstance(permutation, dict) else None
        output_count = len(outputs) if isinstance(outputs, list) else 0
        numeric_scores: list[float] = []
        if isinstance(outputs, list):
            for output in outputs:
                if not isinstance(output, dict):
                    continue
                try:
                    numeric_scores.append(float(output.get("score")))
                except (TypeError, ValueError):
                    continue
        best_score = min(numeric_scores) if numeric_scores else None
        stat_attempt = {
            "function": function,
            "status": status,
            "probe_status": "permute",
            "mismatch_kind": row.get("mismatch_kind"),
            "similarity_score": row.get("similarity_score"),
            "permute_score": best_score,
            "permute_budget_seconds": budget,
            "permute_output_count": output_count,
            "permute_already_matching": bool(
                permutation.get("already_matching")
            ) if isinstance(permutation, dict) else False,
            "permute_error": error,
        }
        runner._record_probe_stats(
            source_path,
            [stat_attempt],
            [f"permute:{row['label']}"],
            [(function, candidate)],
            row.get("declarations") if isinstance(row.get("declarations"), str) else None,
            timing={"permute_seconds": budget, "gate_runs": 0},
            batch_status=status,
        )

    accepted: list[str] = []
    attempts: list[dict[str, object]] = []
    with ThreadPoolExecutor(max_workers=max(1, parallel)) as executor:
        futures = [executor.submit(permute_job, row) for row in rows]
        for future in as_completed(futures):
            row, permutation, error = future.result()
            function = str(row["function"])
            budget = seconds
            if kind_seconds is not None and row.get("mismatch_kind") in _LONGER_BUDGET_KINDS:
                budget = kind_seconds
            if permutation is None:
                attempts.append({"function": function, "status": "permute_failed", "error": error})
                record_permute_outcome(
                    row, status="permute_failed", candidate=str(row["candidate"]),
                    budget=budget, error=error,
                )
                continue
            outputs = permutation.get("outputs") or []
            score_zero = []
            for item in outputs:
                if not isinstance(item, dict):
                    continue
                try:
                    is_zero = float(item.get("score")) == 0.0
                except (TypeError, ValueError):
                    is_zero = False
                if is_zero:
                    score_zero.append(item)
            if permutation.get("already_matching") and not score_zero:
                score_zero = [{"score": 0, "code": str(row["candidate"])}]
            first_output_code = next(
                (
                    item.get("code") for item in outputs
                    if isinstance(item, dict) and isinstance(item.get("code"), str)
                ),
                str(row["candidate"]),
            )
            gate_results: list[dict[str, object]] = []
            for output in score_zero:
                code = output.get("code") if isinstance(output, dict) else None
                if not isinstance(code, str):
                    continue
                try:
                    gated = runner.try_candidates_detailed(
                        targets.require_owner(function).source_path,
                        [(function, code)],
                        labels=[f"permute:{row['label']}"],
                        declarations=row.get("declarations") if isinstance(row.get("declarations"), str) else None,
                        gate=True,
                        probe_workers=workers,
                    )
                except (KeyError, OSError, RuntimeError) as error:
                    gate_results.append({"status": "gate_failed", "error": str(error)})
                    continue
                gate_results.append(gated)
                accepted.extend(str(name) for name in gated.get("accepted", []))
                if gated.get("accepted"):
                    break
            if gate_results:
                final_gate = gate_results[-1]
                outcome_status = (
                    "accepted" if accepted and function in accepted
                    else str(final_gate.get("batch_status") or "compare_rejected")
                )
            else:
                outcome_status = "permute_rejected"
            record_permute_outcome(
                row,
                status=outcome_status,
                candidate=str(first_output_code),
                budget=budget,
                permutation=permutation,
            )
            attempts.append({
                "function": function,
                "label": row["label"],
                "similarity_score": row.get("similarity_score"),
                "permute_score": min(
                    (float(item.get("score")) for item in outputs if isinstance(item, dict)
                     and str(item.get("score", "")).replace(".", "", 1).isdigit()),
                    default=None,
                ),
                "permute_budget_seconds": budget,
                "permute": permutation,
                "gate": gate_results,
            })
    attempts.sort(key=_near_miss_sort_key)
    return {"accepted": accepted, "attempts": attempts}


def sweep(
    *,
    max_instructions: int | None,
    min_instructions: int | None,
    family: str | None,
    source: str | None,
    limit: int,
    gate: bool,
    workers: int | None,
    skip_functions: set[str] | None = None,
    skip_attempts: set[tuple[str, str]] | None = None,
    fragment_range: tuple[int, int] | None = None,
    exclude_families: set[str] | None = None,
    min_family_remaining: int = 0,
    templates: bool = False,
) -> dict[str, object]:
    listing = _sweep_listing(
        source=source,
        family=family,
        max_instructions=max_instructions,
        min_instructions=min_instructions,
        limit=limit,
        fragment_range=fragment_range,
    )
    rows = listing["targets"]
    family_counts: dict[str, int] = dict(listing.get("family_counts") or {})
    summary: dict[str, collections.Counter] = collections.defaultdict(collections.Counter)

    # A family stops being worth probing once its accepted rate saturates
    # (see the ``multi_call_wrapper``/``multi_call`` evidence in AGENTS.md).
    # ``min_family_remaining`` reads that signal straight from the listing's
    # per-family counts, so a caller does not have to track it by hand.
    saturated_families = {
        fam for fam, remaining in family_counts.items()
        if min_family_remaining > 0 and remaining < min_family_remaining
    }
    skip_family_names = (exclude_families or set()) | saturated_families
    if skip_family_names:
        kept_rows = []
        for row in rows:
            fam = str(row["family"])
            if fam in skip_family_names:
                summary[fam]["excluded_family"] += 1
                continue
            kept_rows.append(row)
        rows = kept_rows

    dirty = dedupe_externs.dirty_sources()
    by_source: dict[str, list[dict[str, object]]] = collections.defaultdict(list)
    skipped_dirty_targets = 0
    skipped_dirty_paths: set[Path] = set()
    for row in rows:
        row_path = (targets.REPO_ROOT / str(row["source"])).resolve()
        if row_path in dirty:
            skipped_dirty_targets += 1
            skipped_dirty_paths.add(row_path)
            continue
        by_source[str(row["source"])].append(row)

    accepted_functions: list[str] = []
    touched_sources: list[str] = []
    sweep_timing: dict[str, float] = {
        "probe_seconds": 0.0, "gate_seconds": 0.0, "gate_runs": 0, "install_compiles": 0,
    }
    started = time.monotonic()

    # Phase 1: draft every remaining owner's m2c candidates through a pool.
    # One m2c subprocess per function used to run sequentially inside the
    # per-source loop below; independent functions draft concurrently here
    # regardless of which source owns them.  ``skip_attempts`` is applied per
    # (function, variant label) pair, not per function, so a variant spelling
    # added to ``FAMILY_VARIANTS`` after an earlier reject is still drafted.
    jobs: list[tuple[str, str, str, tuple[str, ...] | None]] = []
    family_of_all: dict[str, str] = {}
    for source_rel, source_rows in by_source.items():
        for row in source_rows:
            function = str(row["function"])
            fam = str(row["family"])
            family_of_all[function] = fam
            if skip_functions and function in skip_functions:
                summary[fam]["skipped_attempted"] += 1
                continue
            variant_names: tuple[str, ...] | None = None
            if skip_attempts is not None:
                planned = FAMILY_VARIANTS.get(fam, DEFAULT_VARIANT_NAMES)
                remaining = tuple(
                    name for name in planned if (function, f"m2c:{name}") not in skip_attempts
                )
                if not remaining:
                    summary[fam]["skipped_attempted"] += 1
                    continue
                variant_names = remaining
            jobs.append((source_rel, function, fam, variant_names))

    draft_workers = max(1, workers if workers else int(os.environ.get("PRAGMA_PROBE_WORKERS", "10")))
    draft_results: dict[str, object] = {}
    draft_started = time.monotonic()
    if jobs:
        with ThreadPoolExecutor(max_workers=draft_workers) as executor:
            futures = {
                executor.submit(draft_variants, function, family=fam, variant_names=variant_names): function
                for _, function, fam, variant_names in jobs
            }
            for future in as_completed(futures):
                function = futures[future]
                try:
                    draft_results[function] = future.result()
                except KeyError as error:
                    draft_results[function] = error
                except (OSError, subprocess.SubprocessError) as error:
                    draft_results[function] = error
    draft_seconds = round(time.monotonic() - draft_started, 1)

    for source_rel, rows in sorted(by_source.items(), key=lambda item: -len(item[1])):
        blocks: list[tuple[str, str]] = []
        labels: list[str] = []
        family_of: dict[str, str] = {}
        draft_of: dict[str, str] = {}
        labels_of: dict[str, set[str]] = collections.defaultdict(set)
        for row in rows:
            function = str(row["function"])
            family_of[function] = family_of_all[function]
            if function not in draft_results:
                # Already accounted for (skipped_attempted) in the drafting
                # phase above.
                continue
            outcome = draft_results[function]
            if isinstance(outcome, KeyError):
                # Another session replaced this pragma since the target list
                # was captured; it is no longer ours to attempt.
                summary[family_of[function]]["vanished"] += 1
                continue
            if isinstance(outcome, (OSError, subprocess.SubprocessError)):
                summary[family_of[function]]["draft_failed"] += 1
                print(f"{function}: draft error: {outcome}", file=sys.stderr)
                continue
            variants, draft = outcome
            if draft is None:
                summary[family_of[function]]["draft_failed"] += 1
                continue
            if not variants:
                summary[family_of[function]]["draft_unusable"] += 1
                continue
            draft_of[function] = draft
            if templates:
                # Prepended so a template candidate probes before this
                # function's m2c variants: once it probe_matches, the m2c
                # variants after it are reported skipped rather than reprobed.
                for label, code in template_variants_for(function, skip_attempts):
                    blocks.append(
                        (
                            function,
                            prepare_candidate_declarations(
                                function, targets.REPO_ROOT / source_rel, code
                            ),
                        )
                    )
                    labels.append(label)
                    labels_of[function].add(label)
            for label, code in variants:
                blocks.append((function, code))
                labels.append(label)
                labels_of[function].add(label)
        if not blocks:
            continue
        source_path = targets.REPO_ROOT / source_rel
        # Pass 1: probe every variant in isolation.  Pass 2 gates only the
        # hits, plus padding retries for bodies that matched the baseline
        # prefix but stopped short of its trailing alignment nops.
        try:
            probe = runner.try_candidates_detailed(
                source_path, blocks, labels=labels, gate=False, probe_workers=workers
            )
        except Exception as error:  # one broken source must not end the sweep
            print(f"{source_rel}: probe pass failed: {error}", file=sys.stderr)
            summary["_errors"]["probe_pass_failed"] += 1
            continue
        _accumulate_timing(sweep_timing, probe)
        # Compile failures are useful diagnostics, not dead ends.  Feed a
        # small, diagnostic-selected family of extra type spellings through a
        # second isolated pass before deciding which bodies reach the gate.
        extra_blocks: list[tuple[str, str]] = []
        extra_labels: list[str] = []
        extra_seen: set[tuple[str, str]] = set()
        diagnostics_by_function: dict[str, list[str | None]] = collections.defaultdict(list)
        for attempt in probe["attempts"]:
            if attempt.get("status") == "compile_failed":
                diagnostics_by_function[str(attempt["function"])].append(
                    attempt.get("diagnostic") if isinstance(attempt.get("diagnostic"), str) else None
                )
        for function, diagnostics in diagnostics_by_function.items():
            draft = draft_of.get(function)
            if draft is None:
                continue
            for label, code in compile_failure_candidates(
                draft,
                diagnostics,
                function=function,
                source_path=source_path,
            ):
                if label in labels_of[function]:
                    continue
                if skip_attempts is not None and (function, label) in skip_attempts:
                    continue
                key = (function, code)
                if key in extra_seen:
                    continue
                extra_seen.add(key)
                extra_blocks.append((function, code))
                extra_labels.append(label)
                labels_of[function].add(label)
        # A compile diagnostic is not the only useful signal.  Keep the
        # ordinary matrix narrow, then expand a rejected owner only when its
        # instruction diff contains the distinctive halfword shift shape.
        mismatch_names_by_function: dict[str, list[str]] = collections.defaultdict(list)
        for attempt in probe["attempts"]:
            function = str(attempt.get("function", ""))
            for name in mismatch_variant_names(attempt):
                if name not in mismatch_names_by_function[function]:
                    mismatch_names_by_function[function].append(name)
        for function, names in mismatch_names_by_function.items():
            draft = draft_of.get(function)
            if draft is None:
                continue
            for name in names:
                code = rewrite_draft(draft, VARIANTS[name])
                if code is None:
                    continue
                label = f"m2c:{name}:mismatch-retry"
                if label in labels_of[function]:
                    continue
                if skip_attempts is not None and (function, label) in skip_attempts:
                    continue
                key = (function, code)
                if key in extra_seen:
                    continue
                extra_seen.add(key)
                extra_blocks.append((function, code))
                extra_labels.append(label)
                labels_of[function].add(label)
        # Immediate-only drift is a stronger signal than a blind type retry:
        # use the persisted expected/actual instruction pair to substitute a
        # visible candidate literal, then send each spelling through the same
        # isolated probe pass.  This also covers non-m2c/template candidates
        # because it works from the attempted body itself.
        for attempt in probe["attempts"]:
            if attempt.get("mismatch_kind") != "immediate_drift":
                continue
            index = int(attempt["index"])
            if index >= len(blocks):
                continue
            function, candidate = blocks[index]
            base_label = labels[index]
            for suffix, code in immediate_repair_candidates(candidate, attempt):
                label = f"{base_label}:immediate-retry:{suffix}"
                if label in labels_of[function]:
                    continue
                if skip_attempts is not None and (function, label) in skip_attempts:
                    continue
                key = (function, code)
                if key in extra_seen:
                    continue
                extra_seen.add(key)
                extra_blocks.append((function, code))
                extra_labels.append(label)
                labels_of[function].add(label)
        # m2c often emits fixed stack locals in descending slot order.  When
        # the probe has already shown a code-generation drift, try the
        # declaration-order-only spelling before spending a permuter budget.
        for attempt in probe["attempts"]:
            index = int(attempt.get("index", -1))
            if index < 0 or index >= len(blocks):
                continue
            function, candidate = blocks[index]
            rewritten = stack_slot_order_candidate(candidate, attempt)
            if rewritten is None:
                continue
            base_label = labels[index]
            label = f"{base_label}:stack-slots-ascending"
            if label in labels_of[function]:
                continue
            if skip_attempts is not None and (function, label) in skip_attempts:
                continue
            key = (function, rewritten)
            if key in extra_seen:
                continue
            extra_seen.add(key)
            extra_blocks.append((function, rewritten))
            extra_labels.append(label)
            labels_of[function].add(label)
        if extra_blocks:
            try:
                extra_probe = runner.try_candidates_detailed(
                    source_path,
                    extra_blocks,
                    labels=extra_labels,
                    gate=False,
                    probe_workers=workers,
                )
                _accumulate_timing(sweep_timing, extra_probe)
                offset = len(blocks)
                for attempt in extra_probe["attempts"]:
                    attempt["index"] = int(attempt["index"]) + offset
                probe["attempts"].extend(extra_probe["attempts"])
                blocks.extend(extra_blocks)
                labels.extend(extra_labels)
            except Exception as error:
                print(f"{source_rel}: compile-retry probe failed: {error}", file=sys.stderr)
                summary["_errors"]["compile_retry_failed"] += 1
        gate_blocks: list[tuple[str, str]] = []
        gate_labels: list[str] = []
        for attempt in probe["attempts"]:
            index = int(attempt["index"])
            padding = padding_retry(attempt)
            duplicate_helpers = duplicate_tail_helper_count(attempt)
            if attempt.get("status") == "probe_match":
                gate_blocks.append(blocks[index])
                gate_labels.append(labels[index])
            elif padding:
                function, code = blocks[index]
                gate_blocks.append((function, code.rstrip() + f"\n#pragma C_FUNCTION_PADDING({padding})\n"))
                gate_labels.append(labels[index] + "+padding")
            elif duplicate_helpers:
                function, code = blocks[index]
                gate_blocks.append(
                    (function, append_duplicate_tail_helpers(function, code, duplicate_helpers))
                )
                gate_labels.append(labels[index] + f"+duplicate-tail-{duplicate_helpers}")
        result = probe
        if gate_blocks:
            # m2c puts an extern block in every draft.  Different owners may
            # infer different types for the same shared symbol, so a single
            # combined source can fail before the actual candidates are
            # compared.  Strip the local boilerplate and gate compatible
            # declaration blocks separately; each call still uses the MCP
            # transaction lock and the full ROM compare.
            gate_batches: dict[str, list[tuple[str, str, str]]] = collections.defaultdict(list)
            for (function, code), label in zip(gate_blocks, gate_labels):
                declarations, body = split_candidate_declarations(code)
                gate_batches[declarations].append((function, body, label))
            gate_attempts: list[dict[str, object]] = []
            gate_accepted: list[str] = []
            gate_statuses: list[str] = []
            for declarations, batch in partition_gate_batches(
                gate_batches, source_rel=source_rel, family_of=family_of, summary=summary
            ):
                try:
                    gate_result = runner.try_candidates_detailed(
                        source_path,
                        [(function, body) for function, body, _ in batch],
                        labels=[label for _, _, label in batch],
                        declarations=declarations or None,
                        gate=gate,
                        probe_workers=workers,
                    )
                except Exception as error:
                    print(f"{source_rel}: gate pass failed: {error}", file=sys.stderr)
                    summary["_errors"]["gate_pass_failed"] += 1
                    gate_statuses.append("gate_pass_failed")
                    continue
                _accumulate_timing(sweep_timing, gate_result)
                gate_statuses.append(str(gate_result.get("batch_status")))
                gate_attempts.extend(gate_result.get("attempts", []))
                gate_accepted.extend(str(name) for name in gate_result.get("accepted", []))
            batch_status = "accepted" if gate_accepted else (gate_statuses[0] if len(set(gate_statuses)) == 1 and gate_statuses else "no_candidate_accepted")
            result = {
                "status": 0 if gate_accepted else 1,
                "accepted": gate_accepted,
                "attempts": gate_attempts,
                "rejected_ranking": probe.get("rejected_ranking", {}),
                "batch_status": batch_status,
                "probe_workers": workers,
                "gate": gate,
            }
            # Keep the diagnostics of pass 1 for functions that had nothing to gate.
            gated_functions = {function for function, _ in gate_blocks}
            result["attempts"] = list(result["attempts"]) + [
                attempt for attempt in probe["attempts"] if attempt["function"] not in gated_functions
            ]
        per_function: dict[str, dict[str, object]] = {}
        for attempt in result["attempts"]:
            function = str(attempt["function"])
            status = str(attempt.get("status"))
            best = per_function.setdefault(function, {"status": None, "score": -1.0, "kind": None})
            rank = {"accepted": 5, "probe_match": 4, "compare_rejected": 3, "probe_rejected": 2, "compile_failed": 1, "skipped": 0}
            if rank.get(status, 0) > rank.get(str(best["status"]), -1):
                best["status"] = status
            score = attempt.get("similarity_score")
            if isinstance(score, (int, float)) and score > float(best["score"]):
                best["score"] = float(score)
                best["kind"] = attempt.get("mismatch_kind")
        for function, best in per_function.items():
            fam = family_of[function]
            summary[fam]["attempted"] += 1
            summary[fam][f"best:{best['status']}"] += 1
            if best["kind"]:
                summary[fam][f"kind:{best['kind']}"] += 1
            if best["score"] >= 0.9 and best["status"] not in {"accepted", "probe_match"}:
                summary[fam]["near_miss_ge_0.9"] += 1
        if result.get("accepted"):
            accepted_functions.extend(result["accepted"])
            touched_sources.append(source_rel)
        print(
            f"{source_rel}: {len(rows)} targets, {len(blocks)} probes, "
            f"accepted {len(result.get('accepted', []))} ({result['batch_status']})",
            file=sys.stderr,
        )
    # Surface the listing's per-family remaining-owner count next to the
    # counters this run actually produced, so a saturated family (a good
    # ``--exclude-family``/``--min-family-remaining`` candidate) is visible
    # even when this run gave it zero attempts.
    for fam, remaining in family_counts.items():
        summary[fam]["remaining"] = remaining
    return {
        "matched": listing["matched"],
        "available_in_range": listing.get("available_in_range"),
        "skipped_dirty_sources": len(skipped_dirty_paths),
        "skipped_dirty_targets": skipped_dirty_targets,
        "sources": len(by_source),
        "accepted": accepted_functions,
        "touched_sources": sorted(set(touched_sources)),
        "elapsed_seconds": round(time.monotonic() - started, 1),
        "draft_seconds": draft_seconds,
        "timing": {
            "probe_seconds": round(sweep_timing["probe_seconds"], 3),
            "gate_seconds": round(sweep_timing["gate_seconds"], 3),
            "gate_runs": int(sweep_timing["gate_runs"]),
            "install_compiles": int(sweep_timing["install_compiles"]),
        },
        "summary": {family: dict(sorted(counter.items())) for family, counter in sorted(summary.items())},
    }


LARGE_MINIMUM_INSTRUCTIONS = 64
LARGE_SECONDS_DEFAULT = 180.0
LARGE_MINIMUM_SIMILARITY = 0.7


def large_sweep(
    *,
    min_instructions: int = LARGE_MINIMUM_INSTRUCTIONS,
    family: str | None = None,
    source: str | None = None,
    limit: int = 2000,
    workers: int | None = None,
    large_seconds: float = LARGE_SECONDS_DEFAULT,
    permute_threads: int = 4,
    permute_parallel: int = 1,
    minimum_similarity: float = LARGE_MINIMUM_SIMILARITY,
) -> dict[str, object]:
    """Draft, probe, and permute owners too large for the ordinary sweep.

    Owners with more than ``min_instructions`` instructions rarely produce a
    usable m2c ``--valid-syntax`` draft at all -- past that size its
    structured control-flow recovery tends to give up.  This drafts with
    ``draft_large_variants`` (``--gotos-only``, only the ``s32-s32``/
    ``u8-void`` type spellings) instead, probes every variant in isolation
    like the ordinary sweep, and then -- instead of gating the probe hits --
    feeds every ``probe_rejected`` result whose ``similarity_score`` is at
    least ``minimum_similarity`` straight into ``permute_and_gate`` with a
    flat ``large_seconds`` budget.  decomp-permuter's search is what
    actually closes the gap for a function this size, not another draft
    variant, so there is no gate-the-probe-hits pass here at all.
    """
    listing = targets.list_targets(
        source=source,
        family=family,
        min_instructions=min_instructions + 1,
        limit=limit,
    )
    rows = list(listing["targets"])
    dirty = dedupe_externs.dirty_sources()
    by_source: dict[str, list[dict[str, object]]] = collections.defaultdict(list)
    skipped_dirty_targets = 0
    for row in rows:
        row_path = (targets.REPO_ROOT / str(row["source"])).resolve()
        if row_path in dirty:
            skipped_dirty_targets += 1
            continue
        by_source[str(row["source"])].append(row)

    drafted = 0
    probed = 0
    permute_rows: list[dict[str, object]] = []
    for source_rel, source_rows in by_source.items():
        source_path = targets.REPO_ROOT / source_rel
        blocks: list[tuple[str, str]] = []
        labels: list[str] = []
        for row in source_rows:
            function = str(row["function"])
            try:
                variants, draft = draft_large_variants(function)
            except (KeyError, OSError, subprocess.SubprocessError) as error:
                print(f"{function}: large draft error: {error}", file=sys.stderr)
                continue
            if draft is None or not variants:
                continue
            drafted += 1
            for label, code in variants:
                blocks.append((function, code))
                labels.append(label)
        if not blocks:
            continue
        try:
            probe = runner.try_candidates_detailed(
                source_path, blocks, labels=labels, gate=False, probe_workers=workers
            )
        except Exception as error:  # one broken source must not end the sweep
            print(f"{source_rel}: large probe pass failed: {error}", file=sys.stderr)
            continue
        probed += len(blocks)
        for attempt in probe.get("attempts", []):
            if attempt.get("status") != "probe_rejected":
                continue
            score = attempt.get("similarity_score")
            if not isinstance(score, (int, float)) or float(score) < minimum_similarity:
                continue
            index = int(attempt["index"])
            function, code = blocks[index]
            permute_rows.append({
                "function": function,
                "candidate": code,
                "label": labels[index],
                "similarity_score": float(score),
                "mismatch_kind": attempt.get("mismatch_kind"),
            })

    permute_result = permute_and_gate(
        permute_rows,
        seconds=large_seconds,
        threads=permute_threads,
        workers=workers,
        parallel=permute_parallel,
    )
    return {
        "matched": listing["matched"],
        "skipped_dirty_targets": skipped_dirty_targets,
        "sources": len(by_source),
        "drafted": drafted,
        "probed": probed,
        "permuted": len(permute_rows),
        "accepted": permute_result["accepted"],
        "attempts": permute_result["attempts"],
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--max-instructions", type=int)
    parser.add_argument("--min-instructions", type=int)
    parser.add_argument("--family")
    parser.add_argument("--source")
    parser.add_argument("--limit", type=int, default=2000)
    parser.add_argument("--no-gate", action="store_true", help="probe only; never edit tracked sources")
    parser.add_argument("--workers", type=int)
    parser.add_argument("--json", type=Path, help="write the summary to this file")
    parser.add_argument("--skip-attempted", action="store_true", help="skip (function, variant label) pairs that already have m2c sweep attempts in the stats file")
    parser.add_argument("--fragment-range", type=str, help="inclusive fragment band, e.g. 17-32")
    parser.add_argument(
        "--exclude-family", action="append", dest="exclude_families", metavar="NAME",
        help="drop this family from the sweep entirely (repeatable)",
    )
    parser.add_argument(
        "--min-family-remaining", type=int, default=0,
        help="skip a family whose remaining owner count in the listing is below N (default 0: off)",
    )
    parser.add_argument(
        "--templates", action="store_true",
        help="prepend template-transfer candidates (tools/template_transfer.py) ahead of the m2c "
             "variants for each function, so they probe first (default: off)",
    )
    parser.add_argument("--near-miss", action="store_true", help="permute rejects at similarity >= --near-miss-min-similarity")
    parser.add_argument("--stats", type=Path, default=targets.STATS_PATH, help="probe stats JSONL for --near-miss")
    parser.add_argument("--near-miss-seconds", type=float, default=45.0)
    parser.add_argument(
        "--near-miss-min-similarity", type=float, default=0.8,
        help="minimum recorded similarity score to consider a candidate (default 0.8)",
    )
    parser.add_argument(
        "--near-miss-kind-seconds", type=float, default=120.0,
        help=(
            "permuter budget for owners whose best recorded attempt is "
            "register_allocation_only or immediate_drift, instead of "
            "--near-miss-seconds; these mismatch kinds tend to need more search "
            "time than a real semantic gap (default 120)"
        ),
    )
    parser.add_argument("--near-miss-threads", type=int, default=4)
    parser.add_argument("--near-miss-limit", type=int)
    parser.add_argument("--near-miss-parallel", type=int, default=2, help="concurrent decomp-permuter budgets (default 2)")
    parser.add_argument("--near-miss-labels", type=str, help="comma-separated label prefixes to consider (default: any)")
    parser.add_argument("--near-miss-retry", action="store_true", help="do not skip owners with an existing permute: attempt")
    parser.add_argument(
        "--large", action="store_true",
        help="sweep owners with more than --min-instructions (default 64) instructions via --gotos-only drafts and the near-miss permuter",
    )
    parser.add_argument(
        "--large-seconds", type=float, default=LARGE_SECONDS_DEFAULT,
        help="decomp-permuter budget per owner in --large mode (default 180)",
    )
    args = parser.parse_args()
    if args.large:
        result = large_sweep(
            min_instructions=args.min_instructions if args.min_instructions is not None else LARGE_MINIMUM_INSTRUCTIONS,
            family=args.family,
            source=args.source,
            limit=args.limit,
            workers=args.workers,
            large_seconds=args.large_seconds,
            permute_threads=args.near_miss_threads,
            permute_parallel=args.near_miss_parallel,
        )
        text = json.dumps(result, indent=2, default=list)
        if args.json:
            args.json.write_text(text + "\n")
        print(text)
        return 0 if result["accepted"] else 1
    if args.near_miss:
        label_prefixes = tuple(
            prefix for prefix in (args.near_miss_labels or "").split(",") if prefix
        ) or None
        result = near_miss(
            stats_path=args.stats,
            minimum_similarity=args.near_miss_min_similarity,
            seconds=args.near_miss_seconds,
            kind_seconds=args.near_miss_kind_seconds,
            threads=args.near_miss_threads,
            workers=args.workers,
            limit=args.near_miss_limit,
            label_prefixes=label_prefixes,
            skip_permuted=not args.near_miss_retry,
            parallel=args.near_miss_parallel,
        )
        text = json.dumps(result, indent=2, default=list)
        if args.json:
            args.json.write_text(text + "\n")
        print(text)
        return 0 if result["accepted"] else 1
    try:
        fragment_range = parse_fragment_range(args.fragment_range) if args.fragment_range else None
    except ValueError as error:
        parser.error(str(error))
    result = sweep(
        max_instructions=args.max_instructions,
        min_instructions=args.min_instructions,
        family=args.family,
        source=args.source,
        limit=args.limit,
        gate=not args.no_gate,
        workers=args.workers,
        skip_attempts=previously_attempted_labels() if args.skip_attempted else None,
        fragment_range=fragment_range,
        exclude_families=set(args.exclude_families) if args.exclude_families else None,
        min_family_remaining=args.min_family_remaining,
        templates=args.templates,
    )
    text = json.dumps(result, indent=2)
    if args.json:
        args.json.write_text(text + "\n")
    print(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
