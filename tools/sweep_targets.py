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
``--near-miss-parallel`` runs multiple ``decomp-permuter`` budgets
concurrently while still gating each result sequentially.
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
}

# These orders encode the narrow IDO spellings learned from accepted owners.
# They are candidate priorities, not ABI proof; every spelling still goes
# through an isolated probe and the sequential ROM gate.
FAMILY_VARIANTS: dict[str, tuple[str, ...]] = {
    "bounded_lookup": ("u8-void", "u16-s32", "s32-s32", "ptr-void"),
    "state_field_access": ("u8-void", "u8-narrow-void", "s16-narrow-void", "s16-void", "u16-s32", "s32-s32", "ptr-void"),
    "constant_map": ("s32-s32", "u8-void", "u16-s32"),
    "direct_wrapper": ("s32-s32", "ptr-void", "u8-void", "ptr-s32"),
    # Accepted setup sequences most often use byte-backed globals and void
    # callees; try that spelling before the register-sized fallback.  The
    # narrow variant stays last because it is valuable when the draft exposes
    # a byte flag, but is too disruptive as a first hypothesis.
    "multi_call_wrapper": ("u8-void", "s32-s32", "ptr-void", "ptr-s32", "u8-narrow-void"),
    "call_sequence": ("u8-void", "s32-s32", "ptr-void", "ptr-s32", "u8-narrow-void"),
}


def compile_failure_variant_names(diagnostic: str | None) -> tuple[str, ...]:
    """Choose extra type spellings from a compiler diagnostic sample."""
    text = (diagnostic or "").lower()
    names: list[str] = []
    if any(token in text for token in ("pointer", "incompatible", "conversion", "dereference")):
        names.extend(("ptr-void", "ptr-s32", "u32-void"))
    if any(token in text for token in ("short", "16", "halfword", "s16")):
        names.append("s16-void")
    if any(token in text for token in ("unknown type", "undeclared", "m2c_unk")):
        names.extend(("s32-s32", "u16-s32"))
    return tuple(dict.fromkeys(name for name in names if name in VARIANTS))


def rewrite_draft(draft: str, variant: dict[str, str]) -> str | None:
    """Turn an m2c ``--valid-syntax`` draft into plain C for one type guess."""
    if "M2C_ERROR" in draft:
        return None
    text = FIELD_RE.sub(lambda m: f"(*({m.group(2)})((u8 *)({m.group(1)}) + ({m.group(3)})))", draft)
    text = UNK_GLOBAL_RE.sub(lambda m: f"extern {variant['global']} {m.group(1)};", text)
    text = UNK_FUNCTION_RE.sub(lambda m: f"extern {variant['call']} {m.group(1)}({m.group(2)});", text)
    text = UNK_TYPE_RE.sub(variant["type"], text)
    text = re.sub(r"\s*/\* extern \*/", "", text)
    if "M2C_" in text:
        return None
    return text.strip() + "\n"


def compile_failure_candidates(
    draft: str,
    diagnostics: Iterable[str | None],
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
            if code in seen:
                continue
            seen.add(code)
            candidates.append((f"m2c:{name}:compile-retry", code))
    return candidates


def split_candidate_declarations(code: str) -> tuple[str, str]:
    """Separate leading m2c externs so compatible gate batches can share them."""
    declarations: list[str] = []
    body: list[str] = []
    in_prefix = True
    for line in code.splitlines():
        if in_prefix and (not line.strip() or EXTERN_LINE_RE.match(line)):
            if line.strip():
                declarations.append(line.strip())
            continue
        in_prefix = False
        body.append(line)
    unique = list(dict.fromkeys(declarations))
    declaration_text = "\n".join(unique) + ("\n" if unique else "")
    body_text = "\n".join(body).strip() + "\n"
    return declaration_text, body_text


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


def draft_variants(
    function: str,
    context: bool = True,
    family: str | None = None,
    variant_names: tuple[str, ...] | None = None,
) -> tuple[list[tuple[str, str]], str | None]:
    """Return ``[(label, code)]`` variants for one function and the raw draft."""
    owner = targets.require_owner(function)
    context_path = targets.preprocessed_context(owner) if context else None
    command = [sys.executable, str(targets.M2C_SCRIPT), "--target", "mips-ido-c", "--valid-syntax", "--globals", "used"]
    if context_path is not None:
        command += ["--context", str(context_path)]
    result = subprocess.run(command + [str(owner.asm_path)], text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=60)
    if result.returncode != 0 or not result.stdout.strip():
        return [], None
    draft = result.stdout
    seen: set[str] = set()
    variants: list[tuple[str, str]] = []
    names = variant_names or FAMILY_VARIANTS.get(family or "", tuple(VARIANTS))
    for name in names:
        variant = VARIANTS[name]
        code = rewrite_draft(draft, variant)
        if code is None or code in seen:
            continue
        seen.add(code)
        variants.append((f"m2c:{name}", code))
    return variants, draft


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
    minimum_similarity: float = 0.9,
    seconds: float = 45.0,
    threads: int = 4,
    workers: int | None = None,
    limit: int | None = None,
    label_prefixes: tuple[str, ...] | None = None,
    skip_permuted: bool = True,
    parallel: int = 1,
) -> dict[str, object]:
    """Permute high-scoring rejects, then gate only score-0 outputs.

    ``label_prefixes`` selects which recorded labels are eligible; ``None``
    (the default) considers any label with a recorded candidate and
    similarity score, not only ``m2c:`` drafts.  ``skip_permuted`` excludes
    owners that already have a ``permute:``-labeled attempt on file (a
    previous near-miss run over the same candidate).  ``parallel`` runs that
    many ``decomp-permuter`` budgets concurrently; gating a score-0 output
    still happens on the main thread as each permute job completes, since it
    holds the runner's cross-process transaction lock.
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
    if limit is not None:
        candidates = candidates[:max(0, limit)]

    def permute_job(row: dict[str, object]) -> tuple[dict[str, object], dict[str, object] | None, str | None]:
        function = str(row["function"])
        candidate = str(row["candidate"])
        try:
            permutation = permute_candidate.permute(
                function,
                candidate,
                declarations=row.get("declarations") if isinstance(row.get("declarations"), str) else None,
                seconds=seconds,
                threads=threads,
                stop_on_zero=True,
            )
        except (FileNotFoundError, KeyError, RuntimeError, ValueError) as error:
            return row, None, str(error)
        return row, permutation, None

    accepted: list[str] = []
    attempts: list[dict[str, object]] = []
    with ThreadPoolExecutor(max_workers=max(1, parallel)) as executor:
        futures = [executor.submit(permute_job, row) for row in candidates]
        for future in as_completed(futures):
            row, permutation, error = future.result()
            function = str(row["function"])
            if permutation is None:
                attempts.append({"function": function, "status": "permute_failed", "error": error})
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
            attempts.append({
                "function": function,
                "label": row["label"],
                "similarity_score": row["similarity_score"],
                "permute": permutation,
                "gate": gate_results,
            })
    attempts.sort(key=_near_miss_sort_key)
    return {
        "candidates": len(candidates),
        "accepted": accepted,
        "attempts": attempts,
        "skipped_permuted": skipped_permuted,
    }


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

    summary: dict[str, collections.Counter] = collections.defaultdict(collections.Counter)
    accepted_functions: list[str] = []
    touched_sources: list[str] = []
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
                planned = FAMILY_VARIANTS.get(fam, tuple(VARIANTS))
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
            for label, code in compile_failure_candidates(draft, diagnostics):
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
        if extra_blocks:
            try:
                extra_probe = runner.try_candidates_detailed(
                    source_path,
                    extra_blocks,
                    labels=extra_labels,
                    gate=False,
                    probe_workers=workers,
                )
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
            if attempt.get("status") == "probe_match":
                gate_blocks.append(blocks[index])
                gate_labels.append(labels[index])
            elif padding:
                function, code = blocks[index]
                gate_blocks.append((function, code.rstrip() + f"\n#pragma C_FUNCTION_PADDING({padding})\n"))
                gate_labels.append(labels[index] + "+padding")
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
            for declarations, batch in gate_batches.items():
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
        "summary": {family: dict(sorted(counter.items())) for family, counter in sorted(summary.items())},
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
    parser.add_argument("--near-miss", action="store_true", help="permute rejects at similarity >= 0.9")
    parser.add_argument("--stats", type=Path, default=targets.STATS_PATH, help="probe stats JSONL for --near-miss")
    parser.add_argument("--near-miss-seconds", type=float, default=45.0)
    parser.add_argument("--near-miss-threads", type=int, default=4)
    parser.add_argument("--near-miss-limit", type=int)
    parser.add_argument("--near-miss-parallel", type=int, default=1, help="concurrent decomp-permuter budgets")
    parser.add_argument("--near-miss-labels", type=str, help="comma-separated label prefixes to consider (default: any)")
    parser.add_argument("--near-miss-retry", action="store_true", help="do not skip owners with an existing permute: attempt")
    args = parser.parse_args()
    if args.near_miss:
        label_prefixes = tuple(
            prefix for prefix in (args.near_miss_labels or "").split(",") if prefix
        ) or None
        result = near_miss(
            stats_path=args.stats,
            seconds=args.near_miss_seconds,
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
    )
    text = json.dumps(result, indent=2)
    if args.json:
        args.json.write_text(text + "\n")
    print(text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
