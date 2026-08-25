#!/usr/bin/env python3
"""Transplant a previously accepted GS candidate's C body onto a similar-shaped GS pragma.

``pragma_targets.similar_solved`` already ranks winners recorded in
``probe-stats.jsonl`` by opcode-sequence similarity to a target, but the
ordinary m2c sweep never uses the result -- it is surfaced only as a hint in
``draft_candidates``.  A winner whose instruction stream matches the
target's *exactly*, index for index, at the same length, is stronger than a
hint: this exact compiler (IDO 7.1, same flags, same tree) is known to turn
some C body into that shape, and only the symbol names and a handful of
literal immediates need to change to turn it into a candidate for the new
target.  ``call_sequence`` -- 80% of the remaining targets -- is exactly the
family where wrapper functions repeat with different callees, which is what
makes this transfer likely to pay off there.

Pipeline, given a target ``function`` and a same-length, high-similarity row
from ``find_templates``:

  1. parse both the target's and the winner's ``.s`` (reusing
     ``s1_transfer_sweep.parse_gs_asm``);
  2. walk the two instruction lists together, requiring
     ``xmatch_stadium1.norm`` to agree at every index -- the same "identical
     shape" test ``s1_transfer_sweep.align_words(strict=True)`` runs, but
     scanned for every difference instead of stopping at the first;
  3. everywhere the winner's operand names a ``jal``/``%hi``/``%lo`` symbol,
     pair it with the target's operand at the same index -- winner name ->
     target name, required to be consistent everywhere it recurs;
  4. everywhere else a masked-equal instruction still differs in its raw
     word -- a literal-bearing op (``addiu``/``ori``/``andi``/loads/stores/
     ``slti``/``sltiu``) -- the winner's C body is searched for that literal
     (hex or decimal); found in exactly one place, it is substituted for the
     target's value; a branch/local-jump offset needs neither renaming nor
     substitution, since no C literal represents it; anything else
     differing fails the transfer;
  5. the winner's own accepted C source (``declarations`` split out via
     ``sweep_targets.split_candidate_declarations``, then both pieces
     renamed) is emitted as one ``TemplateCandidate`` labeled
     ``template:<winner function>:<score>``.

This worktree's ``disasm/asm/us/nonmatchings`` tree is only partially
extracted and it has no ``probe-stats.jsonl`` of its own; both are read
read-only from the sibling checkout this worktree was branched from,
whenever the local copy is missing or incomplete -- the same fallback
``s1_transfer_sweep`` already uses for GS ``.s`` files (see
``_fallback_repo_root``/``default_asm_roots``/``default_stats_path``).
Never writes tracked sources itself: candidates are handed to
``try_pragma_compare.try_candidates_detailed`` like any other.

Usage:
    tools/template_transfer.py --dry-run --limit 30
    tools/template_transfer.py --dry-run --function func_8410AE50
    tools/template_transfer.py --family call_sequence --limit 50
    tools/template_transfer.py --no-gate --max-instructions 16
"""

from __future__ import annotations

import argparse
import collections
import json
import re
import sys
import time
from dataclasses import dataclass, field
from pathlib import Path
from typing import Iterable

import dedupe_externs
import pragma_targets as targets
import s1_transfer_sweep as transfer_sweep
import scan_asm_families as scanner
import sweep_targets
import try_pragma_compare as runner
import xmatch_stadium1 as xmatch

REPO_ROOT = targets.REPO_ROOT

# Literal-bearing I-type ops: a raw-word difference here (after xmatch.norm
# already called the instruction pair "the same shape") is a plain constant
# that might be spelled out in the winner's C body, unlike a relocation
# (covered by the symbol rename) or a branch offset (no C literal represents
# it at all).
IMMEDIATE_OPS = {
    "addiu", "ori", "andi", "lw", "sw", "lbu", "sb", "lh", "sh", "lhu", "slti", "sltiu",
}
_UNSIGNED_IMMEDIATE_OPS = {"ori", "andi"}

# similar_solved/solved_shapes score over every winner regardless of the
# limit passed in (limit only truncates the sorted result), so overfetching
# a generous pool here to filter by same_length afterwards costs nothing.
_RANK_POOL = 200


@dataclass
class TemplateCandidate:
    function: str
    label: str
    code: str
    declarations: str
    rename_map: dict[str, str]
    immediates: list[dict[str, object]]
    outcome: str
    notes: list[str] = field(default_factory=list)


# --------------------------------------------------------------------------
# Fallback roots (this worktree's asm tree and probe stats are incomplete)
# --------------------------------------------------------------------------

def _fallback_repo_root() -> Path | None:
    """The sibling checkout this worktree was branched from, read-only.

    Delegates to ``s1_transfer_sweep``'s own guesser so every tool that
    needs a fallback root agrees on which checkout backs a missing local
    file.
    """
    return transfer_sweep._guess_gs_asm_fallback_root()


def _fallback_asm_root(fallback_root: Path | None) -> Path | None:
    if fallback_root is None:
        return None
    candidate = fallback_root / "disasm" / "asm" / "us" / "nonmatchings"
    return candidate if candidate.is_dir() else None


def default_asm_roots(fallback_root: Path | None = None) -> list[Path]:
    """Local ``ASM_ROOT`` first, then the fallback checkout's, when it exists."""
    root = fallback_root if fallback_root is not None else _fallback_repo_root()
    roots = [targets.ASM_ROOT]
    fallback_asm = _fallback_asm_root(root)
    if fallback_asm is not None:
        roots.append(fallback_asm)
    return roots


def default_stats_path(fallback_root: Path | None = None) -> Path:
    """Local ``probe-stats.jsonl`` if present, else the sibling checkout's, read-only.

    This worktree has no probe history of its own; without this fallback,
    every winner lookup would come back empty.
    """
    if targets.STATS_PATH.exists():
        return targets.STATS_PATH
    root = fallback_root if fallback_root is not None else _fallback_repo_root()
    if root is not None:
        candidate = root / "disasm" / "build" / "probe-stats.jsonl"
        if candidate.exists():
            return candidate
    return targets.STATS_PATH


_WINNER_ASM_INDEX_CACHE: dict[tuple[str, ...], dict[str, Path]] = {}


def winner_asm_index(roots: Iterable[Path]) -> dict[str, Path]:
    """``function -> .s path`` across ``roots`` (first root wins), cached per root set.

    A winner's pragma is long gone, so ``pragma_targets.owner_index`` no
    longer lists it -- but splat's ``.s`` output is content-addressed by
    function name and stays in the tree after the pragma is replaced, so
    scanning for ``<function>.s`` still finds it.
    """
    key = tuple(str(root) for root in roots)
    cached = _WINNER_ASM_INDEX_CACHE.get(key)
    if cached is not None:
        return cached
    index: dict[str, Path] = {}
    for root in roots:
        if not root.is_dir():
            continue
        for path in root.rglob("*.s"):
            index.setdefault(path.stem, path)
    _WINNER_ASM_INDEX_CACHE[key] = index
    return index


# --------------------------------------------------------------------------
# Ranking
# --------------------------------------------------------------------------

_LENGTH_BUCKET_CACHE: tuple[tuple[str, ...], set[int]] | None = None


def _solved_lengths(stats_path: Path, asm_roots: list[Path] | None) -> set[int]:
    """Every opcode-sequence length among the winners, cached (``pragma_targets.solved_shapes`` already is).

    A sweep over thousands of remaining targets calls ``find_templates``
    once per target; most target lengths have no same-length winner at all,
    so this lets ``find_templates`` skip ``similar_solved``'s full
    ``difflib.SequenceMatcher`` scan over every winner for those, at the
    cost of one cheap set lookup.
    """
    global _LENGTH_BUCKET_CACHE
    key = (str(stats_path), tuple(str(root) for root in (asm_roots or [])))
    if _LENGTH_BUCKET_CACHE is not None and _LENGTH_BUCKET_CACHE[0] == key:
        return _LENGTH_BUCKET_CACHE[1]
    lengths = {
        len(row["ops"]) for row in targets.solved_shapes(stats_path, asm_roots=asm_roots)
        if isinstance(row.get("ops"), list)
    }
    _LENGTH_BUCKET_CACHE = (key, lengths)
    return lengths


def find_templates(
    function: str,
    *,
    limit: int = 3,
    minimum: float = 0.9,
    stats_path: Path | None = None,
    asm_roots: list[Path] | None = None,
    asm_text: str | None = None,
) -> list[dict[str, object]]:
    """Same-length, high-similarity winners for ``function`` (wraps ``pragma_targets.similar_solved``).

    Raises ``similar_solved``'s own default ``minimum`` (0.6) to 0.9 and
    additionally requires the winner's opcode sequence be exactly the same
    *length* as the target's: at this similarity, equal length is what makes
    an index-for-index rename plausible.  A same-similarity, different-length
    winner is still a fine hint (that is what ``similar_solved`` alone is
    for), just not a transfer candidate.
    """
    if asm_text is not None:
        effective_stats = stats_path if stats_path is not None else targets.STATS_PATH
        target_length = len(targets._opcode_sequence(asm_text))
        if target_length not in _solved_lengths(effective_stats, asm_roots):
            return []
    ranked = targets.similar_solved(
        function, limit=_RANK_POOL, minimum=minimum,
        stats_path=stats_path, asm_roots=asm_roots, asm_text=asm_text,
    )
    same_length = [row for row in ranked if row.get("same_length")]
    return same_length[:limit]


# --------------------------------------------------------------------------
# Immediate literal substitution
# --------------------------------------------------------------------------

def _immediate_value(word: int, mnemonic: str) -> int:
    raw = word & 0xFFFF
    if mnemonic in _UNSIGNED_IMMEDIATE_OPS:
        return raw
    return raw - 0x10000 if raw & 0x8000 else raw


def _literal_spellings(value: int) -> list[str]:
    if value < 0:
        spellings = {str(value), f"-0x{-value:x}", f"-0x{-value:X}"}
    else:
        spellings = {str(value), f"0x{value:x}", f"0x{value:X}"}
    # Large positive constants are sometimes spelled as the unsigned 16-bit
    # pattern (e.g. 0xFFF8 for -8) rather than a negative literal.
    unsigned16 = value & 0xFFFF
    spellings.add(f"0x{unsigned16:x}")
    spellings.add(f"0x{unsigned16:X}")
    return sorted(spellings)


def _count_spelling(body: str, spelling: str) -> int:
    pattern = re.compile(r"(?<![\w.])" + re.escape(spelling) + r"(?![\w.])")
    return len(pattern.findall(body))


def _locate_immediate(body: str, spellings: list[str]) -> str | None:
    """The one spelling of a literal found exactly once in ``body``, across every spelling tried."""
    hits = [(spelling, _count_spelling(body, spelling)) for spelling in spellings]
    if sum(count for _, count in hits) != 1:
        return None
    return next(spelling for spelling, count in hits if count == 1)


def _format_like(spelling: str, value: int) -> str:
    """Spell ``value`` the same way (hex vs decimal, case, sign) as ``spelling``."""
    negative = spelling.startswith("-")
    core = spelling[1:] if negative else spelling
    if core[:2].lower() == "0x":
        digits = core[2:]
        upper = digits != digits.lower()
        magnitude = abs(value)
        text = format(magnitude, "X" if upper else "x")
        return f"{'-' if value < 0 else ''}0x{text}"
    return str(value)


def _resolve_immediate(
    target_instr: transfer_sweep.SourceInstr, winner_instr: transfer_sweep.SourceInstr, winner_body: str
) -> dict[str, object]:
    winner_value = _immediate_value(winner_instr.word, winner_instr.mnemonic)
    target_value = _immediate_value(target_instr.word, target_instr.mnemonic)
    spelling = _locate_immediate(winner_body, _literal_spellings(winner_value))
    entry: dict[str, object] = {
        "index": target_instr.index,
        "mnemonic": winner_instr.mnemonic,
        "winner_value": winner_value,
        "target_value": target_value,
        "located": spelling is not None,
    }
    if spelling is not None:
        entry["spelling"] = spelling
        entry["replacement"] = _format_like(spelling, target_value)
    return entry


def _apply_immediates(body: str, immediates: list[dict[str, object]]) -> str:
    text = body
    for entry in immediates:
        if not entry.get("located"):
            continue
        pattern = re.compile(r"(?<![\w.])" + re.escape(str(entry["spelling"])) + r"(?![\w.])")
        text = pattern.sub(str(entry["replacement"]), text, count=1)
    return text


# --------------------------------------------------------------------------
# Alignment, rename map, immediates -- one pass over the aligned instructions
# --------------------------------------------------------------------------

def align_and_map(
    parsed_target: transfer_sweep.ParsedAsm,
    parsed_winner: transfer_sweep.ParsedAsm,
    winner_function: str,
    target_function: str,
    winner_body: str,
) -> tuple[dict[str, str], list[dict[str, object]], bool, bool, list[str]]:
    """Build the winner-name -> target-name rename map and immediate substitutions.

    Assumes ``len(parsed_target.instructions) == len(parsed_winner.instructions)``
    (the caller only reaches here for a ``find_templates`` same-length row).
    Returns ``(rename_map, immediates, alignment_ok, inconsistent, notes)``:

    * ``alignment_ok`` is False when some instruction pair differs in a way
      that is neither a symbol operand, a branch/local-jump offset, nor a
      literal-bearing immediate op -- or a symbol operand the target has
      nothing at the same index for.
    * ``inconsistent`` is True when the same winner symbol would have to map
      to two different target symbols.

    ``rename_map`` is seeded with ``{winner_function: target_function}`` --
    the winner's own name in its definition and any self-reference -- and is
    never overridden by a decoded pairing.
    """
    rename_map: dict[str, str] = {winner_function: target_function}
    immediates: list[dict[str, object]] = []
    notes: list[str] = []
    alignment_ok = True
    inconsistent = False
    for t, w in zip(parsed_target.instructions, parsed_winner.instructions):
        if xmatch.norm(t.word) != xmatch.norm(w.word):
            alignment_ok = False
            notes.append(f"index {t.index}: opcode class differs: target=0x{t.word:08X} winner=0x{w.word:08X}")
            continue
        if t.word == w.word:
            continue
        w_sym = w.jal_sym or w.hi_sym or w.lo_sym
        if w_sym is not None:
            t_sym = t.jal_sym or t.hi_sym or t.lo_sym
            if t_sym is None:
                alignment_ok = False
                notes.append(f"index {t.index}: winner names {w_sym} but target has no symbol operand there")
                continue
            existing = rename_map.get(w_sym)
            if existing is not None and existing != t_sym:
                inconsistent = True
                notes.append(f"{w_sym} maps to both {existing} and {t_sym}")
                continue
            rename_map[w_sym] = t_sym
            continue
        if w.mnemonic in scanner.BRANCH_OPS or w.mnemonic == "j":
            continue  # branch/local-jump offset: no C literal represents it
        if w.mnemonic in IMMEDIATE_OPS:
            entry = _resolve_immediate(t, w, winner_body)
            immediates.append(entry)
            if not entry["located"]:
                notes.append(
                    f"index {t.index}: immediate {entry['winner_value']} -> {entry['target_value']} "
                    f"not uniquely located in the winner body"
                )
            continue
        alignment_ok = False
        notes.append(f"index {t.index}: unhandled opcode difference ({w.mnemonic})")
    return rename_map, immediates, alignment_ok, inconsistent, notes


# --------------------------------------------------------------------------
# Candidate generation
# --------------------------------------------------------------------------

def generate_template_candidates(
    function: str,
    *,
    limit: int = 3,
    minimum: float = 0.9,
    stats_path: Path | None = None,
    asm_roots: list[Path] | None = None,
    fallback_root: Path | None = None,
    owner: targets.Owner | None = None,
) -> list[TemplateCandidate]:
    """Template-transfer candidates for ``function``, best winner first.

    Never writes tracked sources; this only produces text for the runner to
    probe.  Every entry -- even a diagnostic one -- carries an ``outcome``
    so a caller can tell a real candidate from ``alignment_failed`` /
    ``inconsistent_rename`` / ``winner_asm_missing`` without probing it.

    ``owner`` lets a caller that already resolved one (``sweep``/``dry_run``,
    from a single ``pragma_targets.owner_index()`` call) skip
    ``require_owner``'s own lookup -- ``owner_index`` revalidates its cache
    by rescanning every tracked source's mtime on every call, which adds up
    fast across a sweep of thousands of targets.
    """
    owner = owner if owner is not None else targets.require_owner(function)
    root = fallback_root if fallback_root is not None else _fallback_repo_root()
    resolved = transfer_sweep.gs_asm_text(owner, root)
    if resolved is None:
        return [TemplateCandidate(
            function=function, label="template:none", code="", declarations="",
            rename_map={}, immediates=[], outcome="winner_asm_missing",
            notes=[f"target .s not found locally or under the fallback checkout ({owner.asm})"],
        )]
    target_text, _source = resolved
    parsed_target = transfer_sweep.parse_gs_asm(target_text)

    resolved_stats = stats_path if stats_path is not None else default_stats_path(root)
    roots = asm_roots if asm_roots is not None else default_asm_roots(root)

    rows = find_templates(
        function, limit=limit, minimum=minimum,
        stats_path=resolved_stats, asm_roots=roots, asm_text=target_text,
    )
    index = winner_asm_index(roots)

    results: list[TemplateCandidate] = []
    for row in rows:
        winner_function = str(row["function"])
        score = float(row["similarity"])
        label = f"template:{winner_function}:{score:.2f}"
        winner_path = index.get(winner_function)
        if winner_path is None:
            results.append(TemplateCandidate(
                function=function, label=label, code="", declarations="",
                rename_map={}, immediates=[], outcome="winner_asm_missing",
                notes=[f"no .s found for {winner_function} under {[str(r) for r in roots]}"],
            ))
            continue
        winner_text = winner_path.read_text(encoding="utf-8", errors="replace")
        parsed_winner = transfer_sweep.parse_gs_asm(winner_text)
        if len(parsed_winner.instructions) != len(parsed_target.instructions):
            results.append(TemplateCandidate(
                function=function, label=label, code="", declarations="",
                rename_map={}, immediates=[], outcome="alignment_failed",
                notes=[
                    f"instruction count differs: target={len(parsed_target.instructions)} "
                    f"winner={len(parsed_winner.instructions)}"
                ],
            ))
            continue

        winner_code = str(row["code"])
        decl_text, body_text = sweep_targets.split_candidate_declarations(winner_code)
        stored_declarations = row.get("declarations")
        if isinstance(stored_declarations, str) and stored_declarations.strip():
            decl_text = transfer_sweep.merge_declarations([stored_declarations, decl_text]) or ""
        rename_map, immediates, alignment_ok, inconsistent, notes = align_and_map(
            parsed_target, parsed_winner, winner_function, function, body_text,
        )
        if not alignment_ok:
            outcome = "alignment_failed"
        elif inconsistent:
            outcome = "inconsistent_rename"
        else:
            outcome = "candidate"

        renamed_decl = transfer_sweep.rename_identifiers(decl_text, rename_map)
        renamed_body = transfer_sweep.rename_identifiers(body_text, rename_map)
        final_body = _apply_immediates(renamed_body, immediates)
        results.append(TemplateCandidate(
            function=function, label=label, code=final_body.strip() + "\n",
            declarations=renamed_decl, rename_map=rename_map, immediates=immediates,
            outcome=outcome, notes=notes,
        ))
    return results


# --------------------------------------------------------------------------
# Driver
# --------------------------------------------------------------------------

def _classify_from_text(text: str) -> dict[str, object]:
    """``pragma_targets._classify_owner``'s classification, from ``.s`` text directly.

    ``_classify_owner`` keys its cache on ``owner.asm_path.stat()``, which
    does not exist for an owner only found through the fallback root; this
    duplicates its handful of ``scan_asm_families`` calls against text
    instead of a locally-readable path.
    """
    _, instructions, labels = scanner.parse_instructions(text)
    calls = scanner.extract_calls(instructions)
    globals_ = scanner.extract_globals(text)
    jump_tables = scanner.extract_jump_tables(text)
    accesses = scanner.extract_memory_accesses(instructions)
    bounds = scanner.extract_bounds(instructions)
    loops = scanner.has_loop(instructions, labels)
    family, _confidence, _notes = scanner.classify(
        instructions, calls, globals_, jump_tables, accesses, bounds, loops
    )
    return {"family": family, "instructions": len(instructions)}


def _select_functions_via_fallback(
    *, family: str | None, max_instructions: int | None, limit: int,
) -> list[str]:
    """Same ranking as ``pragma_targets.list_targets``, sized from the fallback ``.s`` when needed.

    ``list_targets`` requires ``owner.asm_path.exists()`` locally for every
    row; in a worktree whose ``disasm/asm`` tree is only partially
    extracted, that can leave it with nothing to rank at all even though
    every owner's ``.s`` is readable through the fallback root.  Only used
    when the ordinary listing comes back empty (see ``select_functions``),
    so a fully-extracted checkout's behavior is unchanged.
    """
    owners = targets.owner_index()
    fallback_root = _fallback_repo_root()
    rows: list[tuple[int, str, str]] = []
    for function, owner in owners.items():
        resolved = transfer_sweep.gs_asm_text(owner, fallback_root)
        if resolved is None:
            continue
        text, _source = resolved
        info = _classify_from_text(text)
        count = int(info["instructions"])
        if max_instructions is not None and count > max_instructions:
            continue
        if family and info["family"] != family:
            continue
        rows.append((count, owner.source, function))
    rows.sort()
    return [function for _, _, function in rows[: max(0, limit)]]


def select_functions(
    *, functions: list[str] | None, family: str | None, max_instructions: int | None, limit: int,
) -> list[str]:
    if functions:
        owners = targets.owner_index()
        return [function for function in functions if function in owners]
    listing = targets.list_targets(family=family, max_instructions=max_instructions, limit=limit)
    selected = [str(row["function"]) for row in listing["targets"]]
    if selected:
        return selected
    return _select_functions_via_fallback(family=family, max_instructions=max_instructions, limit=limit)


def run_source_group(
    source_path: Path, candidates: list[TemplateCandidate], *, gate: bool, workers: int | None,
) -> dict[str, object]:
    blocks = [(candidate.function, candidate.code) for candidate in candidates]
    labels = [candidate.label for candidate in candidates]
    if not blocks:
        return {"attempts": [], "accepted": []}
    declarations = transfer_sweep.merge_declarations(
        [candidate.declarations for candidate in candidates if candidate.declarations]
    ) or None
    probe = runner.try_candidates_detailed(
        source_path, blocks, labels=labels, declarations=declarations, gate=False, probe_workers=workers,
    )
    gate_blocks: list[tuple[str, str]] = []
    gate_labels: list[str] = []
    for attempt in probe["attempts"]:
        if attempt.get("status") == "probe_match":
            index = int(attempt["index"])
            gate_blocks.append(blocks[index])
            gate_labels.append(labels[index])
    if not gate_blocks:
        return probe
    return runner.try_candidates_detailed(
        source_path, gate_blocks, labels=gate_labels, declarations=declarations, gate=gate, probe_workers=workers,
    )


def sweep(
    functions: list[str], *, gate: bool, workers: int | None, limit: int = 3, minimum: float = 0.9,
    stats_path: Path | None = None,
) -> dict[str, object]:
    started = time.monotonic()
    owners = targets.owner_index()
    dirty = dedupe_externs.dirty_sources()
    fallback_root = _fallback_repo_root()
    resolved_stats = stats_path if stats_path is not None else default_stats_path(fallback_root)
    asm_roots = default_asm_roots(fallback_root)
    by_source: dict[Path, list[TemplateCandidate]] = collections.defaultdict(list)
    outcome_counts: collections.Counter = collections.Counter()
    vanished = 0
    skipped_dirty = 0
    for function in functions:
        owner = owners.get(function)
        if owner is None:
            vanished += 1
            continue
        if owner.source_path.resolve() in dirty:
            skipped_dirty += 1
            continue
        candidates = generate_template_candidates(
            function, limit=limit, minimum=minimum,
            stats_path=resolved_stats, asm_roots=asm_roots, fallback_root=fallback_root, owner=owner,
        )
        for candidate in candidates:
            outcome_counts[candidate.outcome] += 1
            if candidate.outcome == "candidate":
                by_source[owner.source_path].append(candidate)

    accepted: list[str] = []
    touched_sources: list[str] = []
    attempts: list[dict[str, object]] = []
    for source_path, candidates in by_source.items():
        try:
            result = run_source_group(source_path, candidates, gate=gate, workers=workers)
        except Exception as error:  # one broken source must not end the sweep
            print(f"{source_path}: template sweep failed: {error}", file=sys.stderr)
            continue
        attempts.extend(result.get("attempts", []))
        if result.get("accepted"):
            accepted.extend(str(name) for name in result["accepted"])
            touched_sources.append(str(source_path.relative_to(REPO_ROOT)))

    return {
        "requested": len(functions),
        "vanished": vanished,
        "skipped_dirty_sources": skipped_dirty,
        "outcome_counts": dict(sorted(outcome_counts.items())),
        "accepted": accepted,
        "touched_sources": sorted(set(touched_sources)),
        "attempts": attempts,
        "elapsed_seconds": round(time.monotonic() - started, 1),
    }


def dry_run(
    functions: list[str], *, limit: int = 3, minimum: float = 0.9, stats_path: Path | None = None,
) -> dict[str, object]:
    owners = targets.owner_index()
    fallback_root = _fallback_repo_root()
    resolved_stats = stats_path if stats_path is not None else default_stats_path(fallback_root)
    asm_roots = default_asm_roots(fallback_root)
    outcome_counts: collections.Counter = collections.Counter()
    rows: list[dict[str, object]] = []
    for function in functions:
        owner = owners.get(function)
        if owner is None:
            outcome_counts["owner_missing"] += 1
            continue
        candidates = generate_template_candidates(
            function, limit=limit, minimum=minimum,
            stats_path=resolved_stats, asm_roots=asm_roots, fallback_root=fallback_root, owner=owner,
        )
        if not candidates:
            outcome_counts["no_template"] += 1
            continue
        for candidate in candidates:
            outcome_counts[candidate.outcome] += 1
        rows.append({
            "function": function,
            "candidates": [
                {
                    "label": candidate.label,
                    "outcome": candidate.outcome,
                    "rename_map_size": len(candidate.rename_map),
                    "immediates": len(candidate.immediates),
                    "notes": candidate.notes,
                }
                for candidate in candidates
            ],
        })
    return {"outcome_counts": dict(sorted(outcome_counts.items())), "rows": rows}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--function", action="append", dest="functions", help="restrict to this GS function (repeatable)")
    parser.add_argument("--family", help="restrict to this scan_asm_families family")
    parser.add_argument("--max-instructions", type=int)
    parser.add_argument("--limit", type=int, default=2000, help="maximum target functions to consider")
    parser.add_argument("--dry-run", action="store_true", help="generate and print candidates; call no runner")
    parser.add_argument("--no-gate", action="store_true", help="probe only; never edit tracked sources")
    parser.add_argument("--workers", type=int)
    parser.add_argument("--json", type=Path, help="write the summary to this file")
    parser.add_argument(
        "--stats", type=Path,
        help="probe-stats.jsonl to rank winners from (default: local, else the sibling checkout's, read-only)",
    )
    args = parser.parse_args()

    functions = select_functions(
        functions=args.functions, family=args.family, max_instructions=args.max_instructions, limit=args.limit,
    )

    if args.dry_run:
        result = dry_run(functions, stats_path=args.stats)
    else:
        result = sweep(functions, gate=not args.no_gate, workers=args.workers, stats_path=args.stats)
    text = json.dumps(result, indent=2)
    if args.json:
        args.json.write_text(text + "\n")
    print(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
