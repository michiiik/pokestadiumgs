#!/usr/bin/env python3
"""Triage scanner: codify manually-found fleet rejection patterns.

Several human triage passes over ``docs/regions/**/*.md`` and
``disasm/probe-stats/probe-stats.jsonl`` have found real systemic bugs by
manually pattern-matching a handful of shapes in the fleet's plateaued and
rejected owners (a toolchain-level ``lui $at``-coalescing limitation, a
jump-table ``.rodata`` layout backlog, a host-side probe-infrastructure bug
that silently discarded correct candidates).  This tool codifies three of
those shapes so a human -- or an orchestrating Claude session -- does not
have to manually re-derive them from the raw ledger every time:

1. ``jump_table_stale_rejection`` -- an owner rejected with
   ``mismatch_kind == "section_layout_drift"`` at a high raw similarity
   whose jump-table layout is *not* (or is no longer) excluded by the known
   backlog (``tools/pragma_targets.py``'s ``_jump_table_readiness``).
2. ``register_tie_permuter_candidate`` -- an owner whose best recorded
   attempt is a near-1.0 ``register_allocation_only`` tie that has never
   been escalated to the tie pool or run through the permuter.
3. ``score_clustering`` -- two or more distinct owners whose best recorded
   attempt shares an identical ``(similarity_score,
   raw_similarity_score)`` pair that ``tools/container_agent.py``'s own
   ``_is_normalized_only_match`` would flag as suspicious.

This is a pure, deterministic, read-only analysis tool: it makes no LLM
calls, spawns no agents, and performs no remediation.  Its entire job is
detection and structured reporting -- deciding what (if anything) to do
about a finding is left to whoever reads its output.

Data sources (both read-only):

* ``disasm/probe-stats/probe-stats.jsonl`` -- read via ``tools/probe_stats``
  across every resolved path (default: the same primary-checkout-first
  shared ledger ``tools/try_pragma_compare.py``'s ``_probe_stats_target``/
  ``_probe_stats_history_paths`` already resolve for a linked worktree, so
  this tool sees the same history a live fleet run would, not just
  whatever a container's own local copy happens to hold).
* ``docs/regions/**/*.md`` -- parsed for the ``tie-pool yes``/``tie-pool
  no`` marker ``tools/container_agent.py``'s ``_plateau_region_note_text``/
  ``_time_cap_region_note_text`` already write into every plateau/time-cap
  note, the project's existing on-disk representation of "has this owner's
  best tie already been hand to the permuter pool."

Deduplication: a small JSON state file (default
``disasm/probe-stats/triage_state.json``, sibling of ``claims.json`` and
``renames.jsonl`` -- this project's existing convention for lightweight
per-tool state next to the probe-stats ledger) remembers a fingerprint per
``(signature, owner-set)`` key so a re-run does not re-report an unchanged
finding forever.  A finding is re-reported the moment its fingerprint
changes -- new attempts accumulate, scores shift, jump-table readiness
flips -- because the fingerprint is derived from exactly the evidence that
made it a finding in the first place.

Usage:
    tools/triage_investigations.py scan
    tools/triage_investigations.py scan --json
    tools/triage_investigations.py scan --include-seen
    tools/triage_investigations.py scan --reset-state
    tools/triage_investigations.py scan --stats /path/to/probe-stats.jsonl
"""

from __future__ import annotations

import argparse
import collections
import hashlib
import json
import re
import sys
from datetime import datetime, timezone
from pathlib import Path

TOOLS_DIR = Path(__file__).resolve().parent
if str(TOOLS_DIR) not in sys.path:
    sys.path.insert(0, str(TOOLS_DIR))

import container_agent  # noqa: E402  (reused: NORMALIZED_ONLY_* / _is_normalized_only_match)
import pragma_targets as targets  # noqa: E402  (reused: find_owner / _jump_table_readiness)
import probe_stats  # noqa: E402
import try_pragma_compare as runner  # noqa: E402  (reused: _probe_stats_history_paths)

REPO_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_STATE_PATH = REPO_ROOT / "disasm" / "probe-stats" / "triage_state.json"

# Signature 1: a "jump-table-shaped" rejection -- see AGENTS.md's
# section_layout_drift note and tools/add_rodata_subsegments.py's module
# docstring for why a switch with no owned .rodata subsegment lands here.
JUMP_TABLE_MISMATCH_KIND = "section_layout_drift"
JUMP_TABLE_RAW_THRESHOLD = 0.95

# Signature 2: a register-allocation tie worth a permuter escalation.
REGISTER_TIE_MISMATCH_KIND = "register_allocation_only"
REGISTER_TIE_SIMILARITY_THRESHOLD = 0.95

# A permuter-sourced attempt is recorded with these fields populated (see
# tools/sweep_targets.py's record_permute_outcome) and/or one of these
# labels (tools/sweep_targets.py's "permute:{label}" prefix,
# tools/container_agent.py's literal "permuter:zero"/"permuter-only:best").
# Deliberately NOT "any label containing 'permuter'": an agent is free to
# name a hand-written hypothesis something like
# "call_sequence:permuter-shape:exact" that never touched the permuter --
# only the runner-populated permute_* fields or the exact labels the
# permuter integration itself writes are trustworthy signal.
_PERMUTE_FIELDS = (
    "permute_score",
    "permute_budget_seconds",
    "permute_output_count",
    "permute_already_matching",
)
_PERMUTER_EXACT_LABELS = {"permuter:zero", "permuter-only:best"}
_PERMUTER_LABEL_PREFIX = "permute:"

# Signature 3: exact-match clustering only. Both real precedents this
# session found (func_84136D84-family, func_84111248/func_841112C8) were
# exact matches; a fuzzy tolerance would trade a clean, high-confidence
# signal for a noisier one without a concrete case motivating it. Floats
# are rounded before grouping only to guard against harmless repr noise
# (e.g. 0.1 + 0.2), not to implement a real tolerance window.
_CLUSTER_ROUND_NDIGITS = 6

# A follow-up investigation (func_800533A4 / func_82B07BEC / func_8300ADA4 /
# func_86300120, all sharing (1.0, 0.9487)) found a false-positive class the
# generic _is_normalized_only_match near-1.0 branch cannot see: that branch
# fires on similarity >= 0.999 and raw < 0.95 "regardless of ratio" (see its
# docstring in tools/container_agent.py), which is the right call for a
# large function -- a 5% raw gap there is a real chunk of diverging code --
# but for a SHORT function it can be crossed by a single wrong register or
# immediate. raw_similarity_score is round(raw_matches / instruction_count,
# 4), so a function with instruction_count words only has instruction_count
# + 1 distinct achievable values; at instruction_count == 39 (all four owners
# above were exactly 156-byte/39-instruction functions), being off by just 2
# raw words already lands at 37/39 == 0.9487 < 0.95. All four owners' best
# attempts really were independent near-misses (a branch-offset drift, a
# stack-frame-size drift, and two unrelated register swaps -- confirmed by
# hand and by a genuine (non-closing) decomp-permuter run against the two
# register_allocation_only owners) that collided on the same coarse bin, not
# evidence of one shared cause. SCORE_CLUSTER_QUANTIZATION_MAX_RAW_MISMATCH
# is the absolute raw-word gap (not a percentage) below which that collision
# stops being surprising; 2 is exactly the observed case. This only touches
# the near-1.0 trigger: the generalized branch's real precedent
# (func_84111248/func_841112C8 at (0.8125, 0.125), ratio 6.5x) has a raw gap
# far larger than any instruction count could make coincidental, so it is
# untouched by this constant.
SCORE_CLUSTER_QUANTIZATION_MAX_RAW_MISMATCH = 2

_REGION_NOTE_LINE_RE = re.compile(
    r"^(?P<function>[A-Za-z_][A-Za-z0-9_]*): (?:plateau at|time cap at) "
    r"(?P<similarity>\S+) \(raw (?P<raw>[^)]+)\)(?: after \d+s)?, "
    r"mismatch (?P<mismatch_kind>\S+); tried families: (?P<families>.*?); "
    r"(?P<tie_pool>tie-pool (?:yes|no))\s*$",
    re.MULTILINE,
)


# ---------------------------------------------------------------------------
# Data loading
# ---------------------------------------------------------------------------


def _coerce_float(value: object) -> float | None:
    if isinstance(value, bool):
        return None
    if isinstance(value, (int, float)):
        return float(value)
    return None


def _is_permuter_attempt(attempt: dict[str, object]) -> bool:
    """See the ``_PERMUTE_FIELDS``/``_PERMUTER_EXACT_LABELS`` comment above."""
    for field_name in _PERMUTE_FIELDS:
        if attempt.get(field_name) is not None:
            return True
    label = attempt.get("label")
    if isinstance(label, str):
        if label in _PERMUTER_EXACT_LABELS or label.startswith(_PERMUTER_LABEL_PREFIX):
            return True
    return False


def default_stats_paths(repo_root: Path | None = None) -> list[Path]:
    """The same primary-checkout-first shared ledger the runner itself reads.

    Mirrors ``tools/try_pragma_compare.py``'s ``_probe_stats_history_paths``
    exactly (see that function's docstring): a linked worktree's own
    ``disasm/probe-stats/probe-stats.jsonl`` is not the fleet's shared
    history, the primary checkout's is.
    """
    root = repo_root or REPO_ROOT
    return list(runner._probe_stats_history_paths(root))


def resolve_stats_paths(
    explicit: "Path | list[Path] | None", *, repo_root: Path | None = None
) -> list[Path]:
    """Expand a ``--stats`` override the same way ``pragma_targets --stats``
    does, or fall back to ``default_stats_paths`` when none was given."""
    if explicit:
        paths = explicit if isinstance(explicit, (list, tuple)) else [explicit]
        return list(probe_stats.resolve_paths(tuple(Path(p) for p in paths)))
    return default_stats_paths(repo_root)


def load_owner_attempts(stats_paths: "list[Path] | tuple[Path, ...]") -> dict[str, list[dict]]:
    """Return ``{function: [attempt, ...]}`` across every resolved batch file.

    Each entry carries only the fields the three detectors need, normalized
    to real ``float``/``str``/``None`` so a detector never has to defend
    against a malformed row itself. ``_order`` is a global, monotonically
    increasing read-order counter -- a best-effort fallback ordering when a
    legacy (schema 1) attempt has no batch ``timestamp`` to sort by.
    """
    by_owner: dict[str, list[dict]] = collections.defaultdict(list)
    order = 0
    for _path, batch in probe_stats.iter_batches_with_paths(stats_paths):
        timestamp = batch.get("timestamp")
        timestamp = timestamp if isinstance(timestamp, str) and timestamp else None
        source = batch.get("source")
        source = source if isinstance(source, str) and source else None
        attempts = batch.get("attempts")
        if not isinstance(attempts, list):
            continue
        for raw_attempt in attempts:
            if not isinstance(raw_attempt, dict):
                continue
            function = raw_attempt.get("function")
            if not isinstance(function, str) or not function:
                continue
            mismatch_kind = raw_attempt.get("mismatch_kind")
            label = raw_attempt.get("label")
            status = raw_attempt.get("status")
            by_owner[function].append({
                "function": function,
                "similarity_score": _coerce_float(raw_attempt.get("similarity_score")),
                "raw_similarity_score": _coerce_float(raw_attempt.get("raw_similarity_score")),
                "expected_size": _coerce_float(raw_attempt.get("expected_size")),
                "mismatch_kind": mismatch_kind if isinstance(mismatch_kind, str) else None,
                "label": label if isinstance(label, str) else None,
                "status": status if isinstance(status, str) else None,
                "timestamp": timestamp,
                "source": source,
                "is_permuter": _is_permuter_attempt(raw_attempt),
                "_order": order,
            })
            order += 1
    return dict(by_owner)


def _normalize_source(raw_source: "str | None") -> "str | None":
    """Best-effort ``disasm/src/...`` relative path from a batch's absolute
    ``source`` (recorded per-environment, e.g. ``/work/disasm/src/...`` in a
    container or an arbitrary host checkout path)."""
    if not raw_source:
        return None
    normalized = raw_source.replace("\\", "/")
    marker = "disasm/src/"
    index = normalized.find(marker)
    return normalized[index:] if index != -1 else normalized


def owner_source(function: str, attempts: list[dict], *, find_owner=None) -> "str | None":
    """The owner's current source path if it is still a live pragma owner,
    else a best-effort reconstruction from recorded batch ``source`` paths."""
    lookup = find_owner or targets.find_owner
    owner = lookup(function)
    if owner is not None:
        return owner.source
    for attempt in attempts:
        normalized = _normalize_source(attempt.get("source"))
        if normalized:
            return normalized
    return None


def load_region_tie_pool_status(docs_root: Path) -> dict[str, dict[str, bool]]:
    """Return ``{function: {"ever_yes": bool, "last_yes": bool}}`` parsed
    from every auto-generated plateau/time-cap line in ``docs_root``'s
    region-notes tree (see ``_REGION_NOTE_LINE_RE``'s module docstring
    reference: the exact format ``tools/container_agent.py``'s
    ``_plateau_region_note_text``/``_time_cap_region_note_text`` write).

    ``ever_yes`` is the signal signature 2 excludes on: once an owner's
    best tie has ever been handed to the tie pool, a fresh scan should not
    re-flag it just because a later, unrelated plateau note happened to
    record ``tie-pool no`` for a different (worse) attempt in the same
    run. ``last_yes`` is kept for callers that want the most recent status
    instead, but is not used by the current detectors.
    """
    status: dict[str, dict[str, bool]] = {}
    if not docs_root.is_dir():
        return status
    for md_path in sorted(docs_root.rglob("*.md")):
        try:
            text = md_path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        for match in _REGION_NOTE_LINE_RE.finditer(text):
            function = match.group("function")
            is_yes = match.group("tie_pool") == "tie-pool yes"
            entry = status.setdefault(function, {"ever_yes": False, "last_yes": False})
            entry["ever_yes"] = entry["ever_yes"] or is_yes
            entry["last_yes"] = is_yes
    return status


def accepted_functions(owners_attempts: dict[str, list[dict]]) -> set[str]:
    """Functions with at least one recorded ``status == "accepted"`` attempt
    anywhere in the read ledger.

    The shared probe-stats ledger can run ahead of the tracked source: a
    container's local accept lands in probe-stats immediately, but the
    matching ``GLOBAL_ASM`` pragma removal only reaches a given checkout
    once that PR merges. A ``find_owner`` check alone misses an owner that
    was *just* solved elsewhere -- observed directly during this tool's own
    real-data validation, where func_84111248/func_841112C8/func_841125A4
    were all accepted in an isolated research worktree/the shared ledger
    minutes before a scan, while their pragmas were still present in every
    checkout that hadn't pulled that merge yet. An accepted attempt is
    authoritative regardless of git state.
    """
    return {
        function for function, attempts in owners_attempts.items()
        if any(attempt["status"] == "accepted" for attempt in attempts)
    }


# ---------------------------------------------------------------------------
# Findings
# ---------------------------------------------------------------------------


def _fingerprint(payload: dict) -> str:
    encoded = json.dumps(payload, sort_keys=True, separators=(",", ":"), default=str).encode("utf-8")
    return hashlib.sha256(encoded).hexdigest()[:16]


def make_finding(
    signature: str,
    owners: list[str],
    *,
    source: "str | None",
    evidence: dict,
    next_action: str,
) -> dict:
    owners = sorted(owners)
    key = f"{signature}:{','.join(owners)}"
    fingerprint = _fingerprint({"signature": signature, "owners": owners, "evidence": evidence})
    return {
        "signature": signature,
        "owners": owners,
        "source": source,
        "evidence": evidence,
        "next_action": next_action,
        "key": key,
        "fingerprint": fingerprint,
    }


# --- Signature 1: jump-table-shaped rejection not covered by the known fix -


def detect_jump_table_stale_rejections(
    owners_attempts: dict[str, list[dict]],
    *,
    find_owner=None,
    repo_root: "Path | None" = None,
) -> list[dict]:
    lookup = find_owner or targets.find_owner
    root = repo_root or targets.REPO_ROOT
    findings: list[dict] = []
    for function, attempts in sorted(owners_attempts.items()):
        qualifying = [
            attempt
            for attempt in attempts
            if attempt["mismatch_kind"] == JUMP_TABLE_MISMATCH_KIND
            and attempt["raw_similarity_score"] is not None
            and attempt["raw_similarity_score"] >= JUMP_TABLE_RAW_THRESHOLD
        ]
        if not qualifying:
            continue
        owner = lookup(function)
        if owner is None:
            # No longer a live GLOBAL_ASM owner -- already decompiled/accepted
            # (or renamed away) since this rejection was recorded.
            continue
        try:
            if not owner.asm_path.exists():
                continue
            row = targets._classify_owner(owner)
        except OSError:
            continue
        ready, unready = targets._jump_table_readiness(owner, row, repo_root=root)
        if unready:
            # Already covered by the known, tracked jump-table backlog
            # exclusion -- not a new finding.
            continue
        best = max(qualifying, key=lambda attempt: attempt["raw_similarity_score"])
        if ready:
            classification = "stale_past_fix"
            note = (
                f"The owning file now has a .rodata subsegment for its jump "
                f"table (see disasm/yamls/us/rom.yaml) -- this rejection may "
                f"predate that fix landing. Re-probe {function} as a C switch; "
                f"see tools/add_rodata_subsegments.py."
            )
        else:
            classification = "new_occurrence"
            has_jump_table = bool(row.get("jump_tables"))
            if has_jump_table:
                note = (
                    f"{function}'s jump table has no owned .rodata subsegment "
                    f"yet and is not on the tracked jump_table_unready backlog "
                    f"-- run tools/add_rodata_subsegments.py for-jtbl on its "
                    f"table(s), then re-probe."
                )
            else:
                note = (
                    f"{function} was rejected as {JUMP_TABLE_MISMATCH_KIND} but "
                    f"its current assembly shows no jump table -- the extra/"
                    f"missing bytes likely come from a different section-layout "
                    f"cause; read the .s before assuming this is jump-table work."
                )
        findings.append(make_finding(
            "jump_table_stale_rejection",
            [function],
            source=owner.source,
            evidence={
                "matching_attempts": len(qualifying),
                "best_raw_similarity_score": best["raw_similarity_score"],
                "best_similarity_score": best["similarity_score"],
                "mismatch_kind": JUMP_TABLE_MISMATCH_KIND,
                "example_label": best["label"],
                "has_jump_table": bool(row.get("jump_tables")),
                "jump_table_status": "ready" if ready else ("unready" if unready else "not_applicable"),
                "classification": classification,
            },
            next_action=note,
        ))
    return findings


# --- Signature 2: register-allocation tie needing permuter escalation ------


def detect_register_tie_permuter_candidates(
    owners_attempts: dict[str, list[dict]],
    *,
    region_tie_pool_status: dict[str, dict[str, bool]],
    find_owner=None,
) -> list[dict]:
    lookup = find_owner or targets.find_owner
    findings: list[dict] = []
    for function, attempts in sorted(owners_attempts.items()):
        owner = lookup(function)
        if owner is None:
            # No longer a live GLOBAL_ASM owner -- already resolved (or
            # renamed away) since this history was recorded; nothing left
            # to escalate.
            continue
        scored = [attempt for attempt in attempts if attempt["similarity_score"] is not None]
        if not scored:
            continue
        best = max(
            scored,
            key=lambda attempt: (attempt["similarity_score"], attempt["raw_similarity_score"] or 0.0),
        )
        if best["mismatch_kind"] != REGISTER_TIE_MISMATCH_KIND:
            continue
        if best["similarity_score"] < REGISTER_TIE_SIMILARITY_THRESHOLD:
            continue
        if region_tie_pool_status.get(function, {}).get("ever_yes"):
            continue
        if any(attempt["is_permuter"] for attempt in attempts):
            continue
        source = owner.source
        findings.append(make_finding(
            "register_tie_permuter_candidate",
            [function],
            source=source,
            evidence={
                "best_similarity_score": best["similarity_score"],
                "best_raw_similarity_score": best["raw_similarity_score"],
                "best_mismatch_kind": best["mismatch_kind"],
                "prior_attempts": len(attempts),
                "tie_pool_escalated": False,
                "permuter_attempted": False,
            },
            next_action=(
                f"Register-allocation tie at similarity "
                f"{best['similarity_score']} with no tie-pool escalation or "
                f"permuter attempt on record; run tools/permute_candidate.py "
                f"on {function} (see docs/REGISTER_TIES.md) before spending "
                f"more hand-variant probe budget."
            ),
        ))
    return findings


# --- Signature 3: suspicious cross-owner score clustering ------------------


def _best_attempt(attempts: list[dict]) -> "dict | None":
    """The attempt this owner's clustering signal is measured from.

    Ranked by ``(similarity_score, raw_similarity_score)`` -- i.e. the same
    "best recorded attempt" notion ``pragma_targets.OwnerHardness`` and
    every auto-generated plateau/time-cap region note already use (see
    ``_plateau_region_note_text``'s ``owner_state["best_similarity"]``),
    not strict chronological recency. Real data needed this distinction:
    the func_84111248/func_841112C8 precedent's shared (0.8125, 0.125) pair
    is each owner's *best* attempt, but a handful of later, lower-scoring
    exploratory hypotheses (which don't even agree with each other) sort
    after it by timestamp -- picking "most recent by clock time" would
    silently drop a real, matching cluster the moment one owner's history
    diverges from the other's after the shared plateau, which is exactly
    backwards: the plateau itself is the signal, not whichever hypothesis
    happened to be tried last.
    """
    candidates = [
        attempt for attempt in attempts
        if attempt["similarity_score"] is not None and attempt["raw_similarity_score"] is not None
    ]
    if not candidates:
        return None
    return max(candidates, key=lambda attempt: (attempt["similarity_score"], attempt["raw_similarity_score"]))


def _quantization_artifact_evidence(
    similarity: float,
    raw: float,
    functions: list[str],
    latest_by_owner: dict[str, dict],
) -> dict[str, object]:
    """Per-owner raw-word-mismatch counts, and whether the cluster is fully
    explained by short-function score quantization rather than a shared
    cause (see ``SCORE_CLUSTER_QUANTIZATION_MAX_RAW_MISMATCH`` above).

    Only meaningful for the near-1.0 ``_is_normalized_only_match`` trigger
    (``similarity >= 0.999``): that is the branch whose threshold is a fixed
    percentage regardless of function size. Below that similarity, a raw gap
    this small cannot occur by construction, so this always reports
    ``is_likely`` False without needing to re-derive the branch condition.
    """
    per_owner_words: dict[str, "int | None"] = {}
    instruction_counts: set[int] = set()
    all_known = similarity >= 0.999
    for function in functions:
        expected_size = latest_by_owner[function].get("expected_size")
        instruction_count = (
            int(expected_size) // 4
            if isinstance(expected_size, (int, float)) and expected_size and expected_size > 0
            else None
        )
        if instruction_count is None:
            per_owner_words[function] = None
            all_known = False
            continue
        instruction_counts.add(instruction_count)
        per_owner_words[function] = round((1.0 - raw) * instruction_count)
    is_likely = all_known and all(
        (words is not None and words <= SCORE_CLUSTER_QUANTIZATION_MAX_RAW_MISMATCH)
        for words in per_owner_words.values()
    )
    return {
        "raw_mismatch_words_by_owner": per_owner_words,
        "instruction_counts": sorted(instruction_counts),
        "likely_quantization_artifact": is_likely,
    }


def detect_score_clustering(
    owners_attempts: dict[str, list[dict]],
    *,
    find_owner=None,
) -> list[dict]:
    lookup = find_owner or targets.find_owner
    latest_by_owner: dict[str, dict] = {}
    for function, attempts in owners_attempts.items():
        if lookup(function) is None:
            # Already resolved (or renamed away) -- not a live candidate to
            # investigate, and must not pad out (or falsely justify) a
            # cluster with owners still genuinely in play.
            continue
        latest = _best_attempt(attempts)
        if latest is not None:
            latest_by_owner[function] = latest

    groups: dict[tuple[float, float], list[str]] = collections.defaultdict(list)
    for function, attempt in latest_by_owner.items():
        key = (
            round(attempt["similarity_score"], _CLUSTER_ROUND_NDIGITS),
            round(attempt["raw_similarity_score"], _CLUSTER_ROUND_NDIGITS),
        )
        groups[key].append(function)

    findings: list[dict] = []
    for (similarity, raw), functions in sorted(groups.items()):
        if len(functions) < 2:
            continue
        probe_attempt = {"similarity_score": similarity, "raw_similarity_score": raw, "status": None}
        if not container_agent._is_normalized_only_match(probe_attempt):
            continue
        functions = sorted(functions)
        ratio = (similarity / raw) if raw else None
        per_owner = {}
        sources: set[str] = set()
        for function in functions:
            source = owner_source(function, owners_attempts[function], find_owner=lookup)
            if source:
                sources.add(source)
            per_owner[function] = {
                "source": source,
                "mismatch_kind": latest_by_owner[function]["mismatch_kind"],
                "timestamp": latest_by_owner[function]["timestamp"],
                "label": latest_by_owner[function]["label"],
            }
        quantization = _quantization_artifact_evidence(similarity, raw, functions, latest_by_owner)
        if quantization["likely_quantization_artifact"]:
            next_action = (
                f"{len(functions)} distinct owners ({', '.join(functions)}) share the "
                f"identical (similarity={similarity}, raw={raw}) pair, but this looks "
                f"like short-function score quantization, not a shared cause: every "
                f"owner is only {SCORE_CLUSTER_QUANTIZATION_MAX_RAW_MISMATCH} or fewer "
                f"raw instruction-words off (instruction_counts="
                f"{quantization['instruction_counts']}), and at that size there are too "
                f"few achievable raw_similarity_score bins for the collision to be "
                f"surprising by itself -- verify each owner's real assembly_diff before "
                f"assuming a common bug (see SCORE_CLUSTER_QUANTIZATION_MAX_RAW_MISMATCH "
                f"in this file)."
            )
        else:
            next_action = (
                f"{len(functions)} distinct owners ({', '.join(functions)}) share the "
                f"identical (similarity={similarity}, raw={raw}) pair (ratio "
                f"{ratio if ratio is not None else 'inf'}x) -- the normalized metric "
                f"may be hiding a shared systemic cause rather than {len(functions)} "
                f"independent near-misses; investigate together, not one at a time."
            )
        findings.append(make_finding(
            "score_clustering",
            functions,
            source=sorted(sources)[0] if len(sources) == 1 else None,
            evidence={
                "similarity_score": similarity,
                "raw_similarity_score": raw,
                "ratio": ratio,
                "owner_count": len(functions),
                "per_owner": per_owner,
                **quantization,
            },
            next_action=next_action,
        ))
    return findings


# ---------------------------------------------------------------------------
# State / dedup
# ---------------------------------------------------------------------------


def load_state(path: Path) -> dict:
    if not path.exists():
        return {}
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return {}
    return data if isinstance(data, dict) else {}


def save_state(path: Path, state: dict) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp_path = path.with_suffix(path.suffix + ".tmp")
    tmp_path.write_text(json.dumps(state, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    tmp_path.replace(path)


def annotate_seen(findings: list[dict], state: dict) -> None:
    """Set ``finding["seen"]`` in place: True iff ``state`` already recorded
    this exact fingerprint for this key (unchanged since last scan)."""
    for finding in findings:
        prior = state.get(finding["key"])
        finding["seen"] = bool(prior and prior.get("fingerprint") == finding["fingerprint"])


def updated_state(findings: list[dict], state: dict, *, now: str) -> dict:
    """Return a new state dict reflecting every currently-detected finding
    (not just the ones a caller chose to display) -- ``--include-seen``
    must not prevent ``last_seen``/fingerprints from staying current."""
    new_state = dict(state)
    for finding in findings:
        key = finding["key"]
        fingerprint = finding["fingerprint"]
        prior = new_state.get(key)
        first_seen = prior.get("first_seen") if prior and prior.get("fingerprint") == fingerprint else now
        new_state[key] = {
            "fingerprint": fingerprint,
            "signature": finding["signature"],
            "owners": finding["owners"],
            "first_seen": first_seen or now,
            "last_seen": now,
        }
    return new_state


# ---------------------------------------------------------------------------
# Report assembly / CLI
# ---------------------------------------------------------------------------


def run_scan(
    *,
    repo_root: "Path | None" = None,
    stats_paths: "Path | list[Path] | None" = None,
    docs_root: "Path | None" = None,
    state_path: "Path | None" = None,
    include_seen: bool = False,
    reset_state: bool = False,
    find_owner=None,
) -> dict:
    """Run all three detectors and return the full report dict.

    Always persists the refreshed state file to ``state_path`` (default
    ``DEFAULT_STATE_PATH``, inside this checkout's ``disasm/probe-stats/``).
    A caller that must not write into a checkout it doesn't own (e.g.
    read-only validation against a live fleet checkout) should pass an
    explicit ``state_path`` pointing somewhere else instead.
    """
    root = repo_root or REPO_ROOT
    resolved_stats = resolve_stats_paths(stats_paths, repo_root=root)
    resolved_docs_root = docs_root or (root / "docs" / "regions")
    resolved_state_path = state_path or DEFAULT_STATE_PATH

    owners_attempts = load_owner_attempts(resolved_stats)
    region_tie_pool_status = load_region_tie_pool_status(resolved_docs_root)

    # Drop already-accepted owners before any detector sees them -- see
    # accepted_functions's docstring for why a live pragma alone is not a
    # reliable enough "still open" signal.
    already_accepted = accepted_functions(owners_attempts)
    if already_accepted:
        owners_attempts = {
            function: attempts for function, attempts in owners_attempts.items()
            if function not in already_accepted
        }

    findings: list[dict] = []
    findings.extend(detect_jump_table_stale_rejections(
        owners_attempts, find_owner=find_owner, repo_root=root,
    ))
    findings.extend(detect_register_tie_permuter_candidates(
        owners_attempts, region_tie_pool_status=region_tie_pool_status, find_owner=find_owner,
    ))
    findings.extend(detect_score_clustering(owners_attempts, find_owner=find_owner))

    state = {} if reset_state else load_state(resolved_state_path)
    annotate_seen(findings, state)
    now = datetime.now(timezone.utc).isoformat()
    new_state = updated_state(findings, state, now=now)
    save_state(resolved_state_path, new_state)

    displayed = [finding for finding in findings if include_seen or not finding["seen"]]
    counts: dict[str, int] = collections.Counter(finding["signature"] for finding in displayed)
    suppressed = sum(1 for finding in findings if finding["seen"] and not include_seen)

    return {
        "generated_at": now,
        "repo_root": str(root),
        "stats_paths": [str(path) for path in resolved_stats],
        "docs_root": str(resolved_docs_root),
        "state_path": str(resolved_state_path),
        "counts": dict(counts),
        "suppressed_seen": suppressed,
        "findings": displayed,
    }


def _format_evidence(evidence: dict) -> str:
    parts = []
    for key in ("best_similarity_score", "best_raw_similarity_score", "similarity_score",
                "raw_similarity_score", "ratio", "matching_attempts", "prior_attempts",
                "jump_table_status", "classification"):
        if key in evidence and evidence[key] is not None:
            parts.append(f"{key}={evidence[key]}")
    return " ".join(parts)


def print_table(report: dict) -> None:
    findings = report["findings"]
    print(f"triage scan: {len(findings)} finding(s) "
          f"({report['suppressed_seen']} already-seen suppressed)")
    if report["counts"]:
        counts_line = ", ".join(f"{sig}={count}" for sig, count in sorted(report["counts"].items()))
        print(f"  by signature: {counts_line}")
    print()
    for finding in findings:
        seen_marker = " [seen]" if finding.get("seen") else " [new]"
        owners = ", ".join(finding["owners"])
        print(f"[{finding['signature']}]{seen_marker} {owners}")
        if finding["source"]:
            print(f"    source: {finding['source']}")
        evidence_line = _format_evidence(finding["evidence"])
        if evidence_line:
            print(f"    evidence: {evidence_line}")
        print(f"    next action: {finding['next_action']}")
        print()


def main(argv: "list[str] | None" = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    commands = parser.add_subparsers(dest="command", required=True)

    scan = commands.add_parser("scan", help="run all three detectors and report findings")
    scan.add_argument("--json", action="store_true", help="emit JSON (default output format)")
    scan.add_argument("--table", action="store_true", help="emit a human-readable summary instead of JSON")
    scan.add_argument("--include-seen", action="store_true", help="also show findings unchanged since the last scan")
    scan.add_argument("--reset-state", action="store_true", help="forget all prior dedup state before scanning")
    scan.add_argument("--stats", type=Path, action="append", help="probe-stats file (default: the shared primary-checkout ledger)")
    scan.add_argument("--state", type=Path, help=f"dedup state file (default: {DEFAULT_STATE_PATH})")
    scan.add_argument("--docs-root", type=Path, help="docs/regions root (default: <repo>/docs/regions)")
    scan.add_argument("--repo-root", type=Path, help="repo root (default: this checkout)")

    args = parser.parse_args(argv)

    if args.command == "scan":
        report = run_scan(
            repo_root=args.repo_root,
            stats_paths=args.stats,
            docs_root=args.docs_root,
            state_path=args.state,
            include_seen=args.include_seen,
            reset_state=args.reset_state,
        )
        if args.table:
            print_table(report)
        else:
            print(json.dumps(report, indent=2, sort_keys=True))
        return 0
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
