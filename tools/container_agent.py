#!/usr/bin/env python3
"""Single-source-file decompilation driver (GitHub issue #39).

Works on ONE ``disasm/src`` file at a time, one ``GLOBAL_ASM`` owner at a
time, in many short iterations, climbing toward a 1.0 similarity / accepted
match per owner. Candidate *generation* is fully delegated to an external
"generator command" the caller supplies (``--generator-cmd``); this driver
never contains model-specific code. It only:

1. discovers the file's remaining owners (``tools/pragma_targets.py targets``,
   falling back to a regex scan of the source for ``#pragma GLOBAL_ASM``);
2. for the active owner, writes a prompt file (file brief + target assembly +
   this run's best-so-far candidates/diagnostics + the batch JSON contract)
   and shells out to the generator command, substituting ``{prompt}``/
   ``{batch}`` with absolute paths;
3. runs ``tools/fleet_probe.py <batch> --json <result>`` itself and reads the
   result;
4. records per-candidate similarity into ``<out>/state.json``;
5. on acceptance, captures the installed function text (plus the batch's
   declarations/companion_edits) into ``<out>/accepted/<owner>.json`` and a
   ``git diff`` into ``<out>/accepted/<owner>.patch``;
6. on a strong near-miss (best similarity >= 0.95) or a runner-reported
   register-tie diagnostic, launches ``tools/permute_candidate.py`` and polls
   its output directory (never blocks on the subprocess itself), feeding the
   best output back as the next iteration's seed;
7. stops an owner after a similarity plateau, moves to the next owner, and
   stops the whole run at ``--budget-seconds``.

Every subprocess call carries an explicit timeout. The generator, probe, and
permuter invocations each live in their own small function
(``invoke_generator``, ``invoke_probe``, ``invoke_permuter``/``poll_permuter``)
so tests can stub them independently of the loop logic.

Usage:
    tools/container_agent.py --source disasm/src/X.c --out /tmp/run1 \\
        --generator-cmd "my-model-cli --prompt {prompt} --out {batch}"

Test mode (no generator; exercise the loop once with a fixed batch):
    tools/container_agent.py --source disasm/src/X.c --out /tmp/run1 \\
        --candidate-file batch.json
"""

from __future__ import annotations

import argparse
import functools
import hashlib
import json
import os
import re
import shlex
import shutil
import signal
import subprocess
import sys
import threading
import time
from datetime import datetime, timezone
from pathlib import Path

TOOLS_DIR = Path(__file__).resolve().parent
REPO_ROOT_DEFAULT = TOOLS_DIR.parent

PRAGMA_RE = re.compile(r'#pragma\s+GLOBAL_ASM\("[^"]*/([A-Za-z_]\w*)\.s"\)')
OUTPUT_DIR_RE = re.compile(r"^output-(\d+)-(\d+)$")

DEFAULT_GENERATOR_TIMEOUT = 1800.0
# Per-owner wall-clock cap (--owner-seconds): with an agentic generator that
# explores via tools/probe_one.py before converging, a single iteration can
# run 12-17 minutes without improving -- long enough that the plateau rule
# (default 6 non-improving iterations) is far too slow a stop, and a run's
# whole --budget-seconds can be eaten by one or two owners. See
# process_owner/process_owner_permuter_only and _owner_elapsed_seconds.
DEFAULT_OWNER_SECONDS = 2400.0
PROBE_TIMEOUT_CAP = 300.0
MISC_TIMEOUT = 60.0
BEST_CANDIDATES_KEPT = 5
TRIED_LABELS_SHOWN = 30

# Part A: m2c draft seed.
M2C_DRAFT_TIMEOUT = 120.0

# Part D: permuter trigger thresholds/concurrency.
PERMUTER_TRIGGER = 0.95
PERMUTER_LOWERED_TRIGGER = 0.90
# "raw well below normalized": how far raw_similarity_score must trail the
# effective (normalized) similarity for a register_allocation_only best
# attempt to count as the lowered-threshold "register-only tie" case (see
# docs/REGISTER_TIES.md: similarity_score near 1.0, exact_similarity_score
# visibly lower, is the tell).
REGISTER_TIE_RAW_GAP = 0.05
DEFAULT_PERMUTER_BODIES = 3

# feedback["diff_excerpt"] rendering (see _build_feedback): how many
# non-exact-match assembly_diff entries to keep, and a byte cap so one
# pathological attempt (hundreds of diff entries) can't blow out state.json
# or the prompt on its own.
DIFF_EXCERPT_MAX_ENTRIES = 40
DIFF_EXCERPT_MAX_BYTES = 3072

# build_prompt's overall size guard: with a full diff excerpt on every one
# of the (up to BEST_CANDIDATES_KEPT) best candidates, a large owner's file
# brief + assembly + candidate bodies can add up. If the fully-rendered
# prompt would exceed this, only the top FULL_DIFF_CANDIDATES entries keep
# their diff excerpt/frame/instruction-count/first-mismatch lines; the rest
# fall back to the header line only.
PROMPT_SIZE_CAP = 60_000
FULL_DIFF_CANDIDATES = 2


# ---------------------------------------------------------------------------
# Small utilities
# ---------------------------------------------------------------------------

def now_iso() -> str:
    return datetime.now(timezone.utc).strftime("%Y-%m-%dT%H:%M:%SZ")


class Logger:
    """Appends timestamped lines to ``<out>/log.txt`` and echoes to stdout."""

    def __init__(self, path: Path) -> None:
        self.path = path
        self.path.parent.mkdir(parents=True, exist_ok=True)

    def log(self, message: str) -> None:
        line = f"[{now_iso()}] {message}"
        print(line)
        with self.path.open("a", encoding="utf-8") as handle:
            handle.write(line + "\n")


def load_json(path: Path) -> dict | None:
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return None


def save_json(path: Path, data: object) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_name(path.name + f".{os.getpid()}.tmp")
    tmp.write_text(json.dumps(data, indent=2, default=str), encoding="utf-8")
    tmp.replace(path)


def _finalize_run(
    summary: dict, out_dir: Path, stopped_reason: str, started: float, *, repo_dir: Path | None = None,
) -> None:
    """Stamp ``summary`` with its stop reason/timing and close out its current
    ``runs`` entry (if any), then write ``<out_dir>/summary.json``.

    Also terminates every still-registered background permuter process
    (Part D) -- the run's single finalize path, so no permuter subprocess a
    background job launched can outlive the run, whichever owner's job is
    still mid-flight when it ends. When ``repo_dir`` is given, also takes a
    last probe-stats export snapshot (see ``export_probe_stats``) so a run
    that stops between iterations still leaves the freshest copy under
    ``<out_dir>/probe-stats/``.
    """
    terminate_all_permuters()
    if repo_dir is not None:
        export_probe_stats(repo_dir, out_dir)
    summary["stopped_reason"] = stopped_reason
    summary["ended_at"] = now_iso()
    summary["wall_seconds"] = round(time.monotonic() - started, 1)
    if summary.get("runs"):
        summary["runs"][-1]["ended"] = summary["ended_at"]
        summary["runs"][-1]["stop_reason"] = stopped_reason
    save_json(out_dir / "summary.json", summary)


# ---------------------------------------------------------------------------
# Probe-stats export (mirrors the host merge-side import in
# tools/container_merge.py's "import-stats" command): the container writes
# its own probe-stats history the same way the host runner does (see
# tools/probe_stats.py / tools/try_pragma_compare.py's
# ``_probe_stats_target``) -- ``PRAGMA_PROBE_STATS`` if set (empty string
# disables it entirely), else ``<repo>/disasm/probe-stats/probe-stats.jsonl``.
# That file lives inside the container's own checkout and is lost once the
# container exits, so every state save (and the run's finalize path) copies
# it out to the mounted ``<out>/probe-stats/probe-stats.jsonl`` -- cheap
# (``shutil.copyfile``), append-only from the host's point of view (the
# source file itself only ever grows within one run).
# ---------------------------------------------------------------------------

def _probe_stats_source_path(repo_dir: Path) -> Path | None:
    """Resolve the probe-stats file the runner would write to, the same way
    it does (``tools/probe_stats.py``'s ``stats_path()``/
    ``tools/try_pragma_compare.py``'s ``_probe_stats_target``):
    ``PRAGMA_PROBE_STATS`` if set (``""`` disables it, ``None`` back means
    "don't export"), else ``<repo_dir>/disasm/probe-stats/probe-stats.jsonl``.
    """
    value = os.environ.get("PRAGMA_PROBE_STATS")
    if value == "":
        return None
    if value is not None:
        return Path(os.path.expandvars(value)).expanduser()
    return repo_dir / "disasm" / "probe-stats" / "probe-stats.jsonl"


def export_probe_stats(repo_dir: Path, out_dir: Path) -> None:
    """Copy the runner's probe-stats file into ``<out_dir>/probe-stats/``.

    A no-op when probe-stats is disabled (``PRAGMA_PROBE_STATS=""``) or the
    source file doesn't exist yet (no probe has run). Safe to call as often
    as every state save -- it's just a ``cp``, and any ``OSError`` is
    swallowed the same way ``save_json``'s sibling metrics calls are: this
    must never turn a successful iteration into a failure.
    """
    source = _probe_stats_source_path(repo_dir)
    if source is None or not source.is_file():
        return
    dest = out_dir / "probe-stats" / "probe-stats.jsonl"
    try:
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(source, dest)
    except OSError:
        pass


def _save_state(
    state: dict, state_path: Path, *, repo_dir: Path, out_dir: Path, summary: dict | None = None,
) -> None:
    """``save_json(state_path, state)`` plus a probe-stats export snapshot --
    the "every state save" half of the probe-stats export contract (the
    other half is ``_finalize_run``).

    When ``summary`` is given, also rewrites ``<out_dir>/summary.json`` from
    it -- so an abrupt kill between iterations (see ``request_stop``) still
    leaves a current summary on disk, not just whatever ``_finalize_run``
    last wrote (which, before this, only ever ran on a normal exit path).
    ``_finalize_run`` still does the final rewrite that fills in
    ``ended_at``/``stopped_reason``.
    """
    save_json(state_path, state)
    export_probe_stats(repo_dir, out_dir)
    if summary is not None:
        save_json(out_dir / "summary.json", summary)


def _new_owner_state() -> dict:
    return {
        "status": "in_progress",
        "best_similarity": 0.0,
        "best_effective_similarity": 0.0,
        "best_raw_similarity": None,
        "best_label": None,
        "iterations": 0,
        "plateau_count": 0,
        "history": [],
        "best_candidates": [],
        "permuter_runs": [],
        "tried_bodies": [],
        "tried_labels": [],
        "m2c_draft": None,
        "m2c_draft_fetched": False,
        "type_conflicts": [],
        "examples": [],
        "examples_fetched": False,
        "tie_pool": False,
        "last_declarations": "",
        # --owner-seconds bookkeeping (see _owner_elapsed_seconds below):
        # "started_at" is a time.monotonic() reading, set the moment this
        # run's timer is running (None when it isn't); "elapsed_seconds" is
        # the total already folded in from earlier runs/attempts.
        "started_at": None,
        "elapsed_seconds": 0.0,
    }


# ---------------------------------------------------------------------------
# --owner-seconds: a per-owner wall-clock cap, independent of --plateau,
# measured from the owner's first generator call (--mode full) or first
# permuter job (--mode permuter-only) in this run. Time already spent on the
# owner in an earlier --resume run counts too -- state.json's
# "elapsed_seconds" carries it forward. Checked only at safe points (never
# while a generator/probe/permuter call is actually running).
# ---------------------------------------------------------------------------

def _owner_mark_started(owner_state: dict) -> None:
    """Start this run's --owner-seconds timer for ``owner_state``, the first
    time this run is about to make a generator call or a permuter job for
    it. Idempotent -- a no-op once the timer is already running this run."""
    if owner_state.get("started_at") is None:
        owner_state["started_at"] = time.monotonic()


def _owner_elapsed_seconds(owner_state: dict) -> float:
    """Total wall-clock time spent on this owner toward --owner-seconds:
    the total already carried over from earlier runs (``elapsed_seconds``,
    folded in by ``_owner_freeze_elapsed`` -- see --resume) plus, if this
    run's timer is currently running (``started_at`` set), the time elapsed
    since it started."""
    total = owner_state.get("elapsed_seconds", 0.0) or 0.0
    started_at = owner_state.get("started_at")
    if started_at is not None:
        total += max(0.0, time.monotonic() - started_at)
    return total


def _owner_freeze_elapsed(owner_state: dict) -> None:
    """Fold this run's running timer (if any) into the persisted
    ``elapsed_seconds`` total and stop it. Called once an owner's attempt
    this run ends (whatever the status), so state.json always holds a
    self-contained total that a later --resume (a fresh process) can keep
    accumulating correctly. Idempotent -- a no-op if the timer was never
    started, or already frozen."""
    if owner_state.get("started_at") is not None:
        owner_state["elapsed_seconds"] = _owner_elapsed_seconds(owner_state)
        owner_state["started_at"] = None


# ---------------------------------------------------------------------------
# Already-tried-body tracking
#
# fleet_probe.py's own preflight (tools/try_pragma_compare.py
# ``validate_candidate_batch`` / ``_duplicate_candidate_errors``) rejects a
# whole batch outright if any one candidate resends a body (under the same
# ``declarations``) it has already rejected -- exit 2, "batch preflight
# failed". A generator that resends a body it already tried earlier in the
# same run loses the whole batch, not just that one candidate. This driver
# tracks every body it has actually sent to the probe (per owner, across the
# whole run, persisted in ``state.json`` so ``--resume`` inherits it too) and
# filters a batch *before* probing, so a repeat never reaches fleet_probe at
# all.
# ---------------------------------------------------------------------------

def _normalize_body_for_dedup(text: str | None) -> str:
    """Strip and collapse runs of whitespace to one space."""
    return " ".join((text or "").split())


def _tried_body_key(body: str | None, declarations: str | None) -> str:
    """The runner's own dedup key is ``(body, declarations)``; hash both
    (independently, whitespace-normalized) into one lookup key."""
    body_hash = hashlib.sha1(_normalize_body_for_dedup(body).encode("utf-8")).hexdigest()
    decl_hash = hashlib.sha1(_normalize_body_for_dedup(declarations).encode("utf-8")).hexdigest()
    return f"{body_hash}:{decl_hash}"


def _owner_candidate_count(batch: dict | None, owner: str) -> int:
    """Count ``batch["candidates"]`` entries whose "function" is ``owner``.

    Used to decide whether a generator that timed out (or otherwise looked
    like it failed) still left something worth probing: a batch file with
    zero candidates for this owner is treated the same as no batch at all.
    """
    if not isinstance(batch, dict):
        return 0
    candidates = batch.get("candidates")
    if not isinstance(candidates, list):
        return 0
    return sum(1 for c in candidates if isinstance(c, dict) and c.get("function") == owner)


def filter_batch(batch: dict, owner_state: dict) -> tuple[dict, list[dict]]:
    """Drop candidates whose ``(body, declarations)`` key was already probed
    this run (``owner_state["tried_bodies"]``), plus exact duplicates within
    ``batch`` itself.

    Returns ``(filtered_batch, dropped)`` where ``filtered_batch`` is a
    shallow copy of ``batch`` with a possibly-shorter ``candidates`` list,
    and ``dropped`` is a list of ``{"label": ..., "reason": ...}`` entries in
    original order.
    """
    declarations = batch.get("declarations")
    tried = set(owner_state.get("tried_bodies") or [])
    seen_in_batch: set[str] = set()
    kept: list[dict] = []
    dropped: list[dict] = []
    for candidate in batch.get("candidates") or []:
        key = _tried_body_key(candidate.get("body"), declarations)
        label = candidate.get("label") or "(unlabelled)"
        if key in tried:
            dropped.append({"label": label, "reason": "already tried this run"})
            continue
        if key in seen_in_batch:
            dropped.append({"label": label, "reason": "duplicate within this batch"})
            continue
        seen_in_batch.add(key)
        kept.append(candidate)
    filtered = dict(batch)
    filtered["candidates"] = kept
    return filtered, dropped


def _record_tried_bodies(batch: dict, owner_state: dict) -> None:
    """Record every candidate actually sent in ``batch`` into
    ``owner_state["tried_bodies"]``/``["tried_labels"]``, regardless of the
    probe's verdict (rejected and compile-failed both count -- a re-send
    still can't produce a new result)."""
    declarations = batch.get("declarations")
    tried = set(owner_state.get("tried_bodies") or [])
    tried_labels = owner_state.setdefault("tried_labels", [])
    for candidate in batch.get("candidates") or []:
        tried.add(_tried_body_key(candidate.get("body"), declarations))
        label = candidate.get("label")
        if label and label not in tried_labels:
            tried_labels.append(label)
    owner_state["tried_bodies"] = sorted(tried)


_PREFLIGHT_INDEX_RE = re.compile(r"candidates\[(\d+)\]")


def _parse_preflight_indices(stderr: str | None) -> list[int]:
    return sorted({int(match) for match in _PREFLIGHT_INDEX_RE.findall(stderr or "")})


# ---------------------------------------------------------------------------
# Normalized-only match detection
#
# The probe's ``similarity_score`` is normalized (it can read 1.0, or close
# to it, even while real register/immediate/field differences remain -- see
# ``raw_similarity_score``). An attempt whose diagnostic flags this
# explicitly, or whose normalized score looks perfect/near-perfect while its
# raw score is well below it and it was NOT actually accepted, is a
# "normalized-only match": it must never be allowed to look like a genuine
# near-miss to the driver (best-candidate selection, the improvement test,
# or the permuter trigger).
# ---------------------------------------------------------------------------

def _is_normalized_only_match(attempt: dict) -> bool:
    if attempt.get("normalized_only") is True:
        return True
    diagnostic = attempt.get("diagnostic") or ""
    if "normalized_only_match" in diagnostic:
        return True
    similarity = attempt.get("similarity_score")
    raw = attempt.get("raw_similarity_score")
    status = attempt.get("status")
    if (
        isinstance(similarity, (int, float)) and similarity >= 0.999
        and status != "accepted"
        and isinstance(raw, (int, float)) and raw < 0.95
    ):
        return True
    return False


def attempt_rank(attempt: dict) -> tuple[float, float]:
    """Rank key for an attempt (or a ``best_candidates`` entry): ``(effective
    similarity, raw similarity)``.

    Ordinarily ``effective`` is just ``similarity_score``. But a
    normalized-only match (see ``_is_normalized_only_match``) has its
    ``effective`` capped at ``0.9 + 0.1 * raw`` so it can never rank above,
    or tie with, a genuine near-miss -- it always stays below the 0.95
    permuter threshold unless raw itself is already high.
    """
    similarity = attempt.get("similarity_score") or 0.0
    raw = attempt.get("raw_similarity_score")
    raw_value = raw if isinstance(raw, (int, float)) else 0.0
    effective = similarity
    if _is_normalized_only_match(attempt):
        effective = min(similarity, 0.9 + 0.1 * raw_value)
    return (effective, raw_value)


# ---------------------------------------------------------------------------
# Per-candidate feedback: fleet_probe's result JSON carries a rich
# ``assembly_diff`` (one entry per compared instruction, with
# expected/actual text, offsets and match flags) plus size/tail/futility
# fields that a 500-char ``diagnostic`` string throws away. This distills
# that into a small, JSON-serializable dict cheap enough to keep in
# ``state.json`` (so --resume inherits it) and to render in the next
# prompt (see build_prompt).
# ---------------------------------------------------------------------------

_FEEDBACK_PASSTHROUGH_KEYS = (
    "expected_size", "actual_size",
    "expected_instruction_count", "actual_instruction_count",
    "first_diff_offset",
    "expected_instruction_text", "actual_instruction_text",
    "mismatch_kind", "futility",
    "register_only_similarity_score", "repeated_drift",
    "expected_tail_kind", "actual_tail_kind",
)


def _build_feedback(attempt: dict) -> dict:
    """Extract a compact feedback dict from one probe attempt.

    Copies the scalar diagnostic fields in ``_FEEDBACK_PASSTHROUGH_KEYS``
    verbatim (only those actually present), then builds ``diff_excerpt``:
    the first ``DIFF_EXCERPT_MAX_ENTRIES`` non-``exact_match`` entries of
    ``assembly_diff``, each rendered as one line, with one line of
    exact-match context immediately before the first mismatch. Capped at
    ``DIFF_EXCERPT_MAX_BYTES``; ``diff_excerpt_truncated`` is set whenever
    the excerpt stopped early (entry/byte cap) or the source
    ``assembly_diff`` was itself already truncated by the probe.
    """
    feedback: dict = {}
    for key in _FEEDBACK_PASSTHROUGH_KEYS:
        value = attempt.get(key)
        if value is not None:
            feedback[key] = value

    diff = attempt.get("assembly_diff") or []
    lines: list[str] = []
    context_line: str | None = None
    shown = 0
    truncated = bool(attempt.get("assembly_diff_truncated"))
    budget = DIFF_EXCERPT_MAX_BYTES
    for entry in diff:
        if entry.get("exact_match"):
            context_line = f"  @{entry.get('expected_offset')}: {entry.get('expected')}  (match)"
            continue
        line = (
            f"  @{entry.get('expected_offset')}: expected `{entry.get('expected')}`"
            f"  actual `{entry.get('actual')}`"
        )
        pending = ([context_line] if (shown == 0 and context_line) else []) + [line]
        pending_size = sum(len(p) + 1 for p in pending)
        if shown >= DIFF_EXCERPT_MAX_ENTRIES or pending_size > budget:
            truncated = True
            break
        lines.extend(pending)
        budget -= pending_size
        shown += 1

    if lines:
        if truncated:
            lines.append("  ... (diff truncated)")
        feedback["diff_excerpt"] = "\n".join(lines)
        feedback["diff_excerpt_truncated"] = truncated
    return feedback


# ---------------------------------------------------------------------------
# Owner discovery
# ---------------------------------------------------------------------------

def discover_owners(
    repo_dir: Path,
    source_rel: str,
    *,
    timeout: float = MISC_TIMEOUT,
    owner_order: str = "size",
    max_instructions: float | None = None,
    logger: "Logger | None" = None,
) -> list[str]:
    """Return the file's remaining GLOBAL_ASM owners.

    ``owner_order="size"`` (default) keeps ``pragma_targets.py targets``'s
    own smallest-instructions-first ranking; ``owner_order="file"`` reorders
    those same owners (after any ``max_instructions`` filtering) to the
    order they appear in the source instead, using
    ``discover_owners_fallback`` purely as an ordering key here (not as its
    usual missing-tool fallback). ``max_instructions`` drops any owner whose
    instruction count exceeds it (unlimited when ``None``); pass it through
    to ``pragma_targets.py targets`` rather than filtering client-side so its
    own accounting (``matched``/``truncated``) stays correct.

    ``pragma_targets.py targets`` always prints a JSON object (``{"matched",
    "family_counts", "targets": [...], "truncated"}``) on stdout -- there is
    no ``--json`` flag (passing one is an argparse error, exit 2, which used
    to make this function silently fall back to the regex scan on every
    call, losing size ordering and ``--max-instructions`` filtering
    entirely; see ``python3 tools/pragma_targets.py targets --help``).

    Falls back to a regex scan of the source (file order, no instruction
    counts, ``max_instructions`` ignored) when ``pragma_targets.py`` is
    unavailable or reports nothing -- e.g. a synthetic test file outside the
    tracked ``disasm/src`` tree -- logging loudly (when a logger is given)
    about exactly why, so a silent loss of size ordering is never invisible
    again.
    """
    command = [
        "python3", "tools/pragma_targets.py", "targets",
        "--source", source_rel, "--limit", "100000",
    ]
    if max_instructions is not None:
        command += ["--max-instructions", str(int(max_instructions))]

    def _fallback(reason: str) -> list[str]:
        if logger is not None:
            logger.log(
                f"discover_owners: falling back to a regex scan of {source_rel} ({reason}); "
                "size ordering and --max-instructions do NOT apply to this owner list"
            )
        return discover_owners_fallback(repo_dir, source_rel)

    try:
        proc = subprocess.run(command, cwd=repo_dir, capture_output=True, text=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return _fallback(f"`{' '.join(command)}` timed out after {timeout:.0f}s")
    except OSError as exc:
        return _fallback(f"`{' '.join(command)}` failed to launch: {exc}")

    if proc.returncode != 0:
        return _fallback(
            f"`{' '.join(command)}` exited {proc.returncode}: {(proc.stderr or '').strip()[:300]}"
        )
    if not proc.stdout.strip():
        return _fallback(f"`{' '.join(command)}` produced no stdout")

    try:
        data = json.loads(proc.stdout)
        rows = [row for row in data.get("targets", []) if row.get("function")]
    except (json.JSONDecodeError, AttributeError, KeyError, ValueError) as exc:
        return _fallback(f"could not parse `{' '.join(command)}` output as JSON: {exc}")

    if not rows:
        return _fallback(f"`{' '.join(command)}` reported no remaining owners for {source_rel}")

    if owner_order == "file":
        file_order = discover_owners_fallback(repo_dir, source_rel)
        rank = {name: index for index, name in enumerate(file_order)}
        rows = sorted(rows, key=lambda row: rank.get(row["function"], len(file_order)))
    if logger is not None:
        logger.log(
            f"owner order ({owner_order}): " + ", ".join(
                f"{row['function']}({row.get('instructions', '?')})" for row in rows
            )
        )
    return [row["function"] for row in rows]


def discover_owners_fallback(repo_dir: Path, source_rel: str) -> list[str]:
    source_path = repo_dir / source_rel
    try:
        text = source_path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return []
    owners: list[str] = []
    for match in PRAGMA_RE.finditer(text):
        name = match.group(1)
        if name not in owners:
            owners.append(name)
    return owners


def file_brief_text(repo_dir: Path, source_rel: str, *, timeout: float = MISC_TIMEOUT) -> str:
    try:
        proc = subprocess.run(
            ["python3", "tools/file_brief.py", source_rel],
            cwd=repo_dir, capture_output=True, text=True, timeout=timeout,
        )
        return proc.stdout
    except (subprocess.TimeoutExpired, OSError) as exc:
        return f"(file_brief.py unavailable: {exc})"


def owner_asm_text(repo_dir: Path, function: str, *, timeout: float = MISC_TIMEOUT) -> str:
    try:
        proc = subprocess.run(
            ["python3", "tools/pragma_targets.py", "asm", function],
            cwd=repo_dir, capture_output=True, text=True, timeout=timeout,
        )
        if proc.returncode == 0:
            return proc.stdout
        return f"(pragma_targets.py asm failed: {proc.stderr.strip()[:500]})"
    except (subprocess.TimeoutExpired, OSError) as exc:
        return f"(pragma_targets.py asm unavailable: {exc})"


# ---------------------------------------------------------------------------
# m2c draft seed (Part A)
#
# ``tools/pragma_targets.py draft <function>`` runs m2c over the owner's
# assembly, with the same host-preprocessed context cache pragma_targets
# itself uses for candidate drafting (AGENTS.md §2.5 step 2). One draft per
# owner is enough: it is a structural hint (unknown-struct fields, guessed
# types), never a match, so it is fetched once per run and cached in
# ``owner_state["m2c_draft"]`` (persisted through state.json for --resume).
# ---------------------------------------------------------------------------

def invoke_m2c_draft(repo_dir: Path, function: str, *, timeout: float) -> subprocess.CompletedProcess:
    """Run ``tools/pragma_targets.py draft`` once. Isolated so tests can stub it."""
    return subprocess.run(
        ["python3", "tools/pragma_targets.py", "draft", function, "--variant", "m2c"],
        cwd=repo_dir, capture_output=True, text=True, timeout=timeout,
    )


def _parse_m2c_draft_output(stdout: str) -> str | None:
    """Extract the drafted C body from ``pragma_targets.py draft``'s stdout.

    Its output is ``/* <label> */\\n<code, or "/* error: ... */">`` per
    variant; requesting a single ``--variant m2c`` gives exactly one block.
    ``None`` when m2c itself failed (the body is an error comment) or stdout
    was empty.
    """
    lines = stdout.splitlines()
    if not lines:
        return None
    body = "\n".join(lines[1:]).strip()
    if not body or body.startswith("/* error:"):
        return None
    return body


def get_m2c_draft(
    repo_dir: Path, owner: str, owner_state: dict, *, timeout: float = M2C_DRAFT_TIMEOUT, logger: Logger,
) -> str | None:
    """Fetch (once per run) and cache an m2c structural draft for ``owner``.

    ``owner_state["m2c_draft_fetched"]`` remembers that the attempt already
    happened, including a failed/timed-out one, so a draft that couldn't be
    produced is never retried every iteration; ``owner_state["m2c_draft"]``
    carries the cached text through ``--resume``.
    """
    if owner_state.get("m2c_draft_fetched"):
        return owner_state.get("m2c_draft")
    owner_state["m2c_draft_fetched"] = True
    try:
        proc = invoke_m2c_draft(repo_dir, owner, timeout=timeout)
    except subprocess.TimeoutExpired:
        logger.log(f"{owner}: m2c draft timed out after {timeout:.0f}s; continuing without it")
        return None
    except OSError as exc:
        logger.log(f"{owner}: m2c draft failed to launch: {exc}; continuing without it")
        return None
    if proc.returncode != 0:
        logger.log(
            f"{owner}: m2c draft failed (exit {proc.returncode}): "
            f"{(proc.stderr or '').strip()[:300]}; continuing without it"
        )
        return None
    draft = _parse_m2c_draft_output(proc.stdout)
    if draft is None:
        logger.log(f"{owner}: m2c draft produced no usable code; continuing without it")
        return None
    owner_state["m2c_draft"] = draft
    return draft


# ---------------------------------------------------------------------------
# Family worked examples
#
# AGENTS.md §2.5 step 2: "Start from the closest accepted winner's spelling,
# not from m2c, when similarity is high and the length matches. Check the
# neighbouring solved functions in the same file." A human agent gets this
# for free from `draft_candidates`/`similar_solved`; a generator only sees
# whatever this driver puts in the prompt. ``collect_family_examples``
# fetches (once per owner per run, like ``get_m2c_draft``) up to
# ``--examples`` already-matched functions of the same family and caches
# them in ``owner_state["examples"]`` so ``--resume``/``--seed-from`` do not
# refetch; ``build_prompt`` renders them as worked examples ahead of the
# m2c draft and best-candidates feedback.
# ---------------------------------------------------------------------------

DEFAULT_EXAMPLES = 3
# Total bytes of rendered example definitions kept per owner -- cheap
# insurance against one huge accepted neighbour (a `large_mixed` owner, or a
# candidate body with several helper definitions after it) blowing out the
# prompt on its own; see build_prompt's own PROMPT_SIZE_CAP for the
# whole-prompt guard this sits inside of.
EXAMPLES_BYTE_CAP = 12_000

# Same shape as tools/file_brief.py's own FUNCTION_DEF_RE/parse_functions:
# a separate non-greedy "return type" group and a "name" group, anchored at
# column 0 (no leading whitespace -- real top-level definitions in this
# codebase are never indented). A single combined "prefix.*(name)" capture
# would greedily prefer the LAST "name(" it can find on the line, which for
# something like "    if (helper()) {" captures "helper" (a call inside the
# condition), not "if" -- this two-group shape avoids that trap instead of
# trying to deny-list control-flow keywords after the fact.
_FUNC_DEF_HEADER_RE = re.compile(
    r"^(?P<ret>[A-Za-z_][\w\s\*]*?)\s+(?P<name>[A-Za-z_]\w*)\s*\((?P<params>[^;{}]*)\)\s*\{", re.M,
)


def invoke_similar_solved(
    repo_dir: Path, function: str, *, limit: int, timeout: float = MISC_TIMEOUT,
) -> subprocess.CompletedProcess:
    """Run ``tools/pragma_targets.py similar`` once. Isolated so tests can
    stub it. ``function`` must currently own a pragma (``similar`` calls
    ``require_owner`` internally and raises/exits non-zero otherwise) --
    true for the owner this driver is actively working."""
    return subprocess.run(
        ["python3", "tools/pragma_targets.py", "similar", function, "--limit", str(limit)],
        cwd=repo_dir, capture_output=True, text=True, timeout=timeout,
    )


def invoke_owner_family_row(
    repo_dir: Path, source_rel: str, *, timeout: float = MISC_TIMEOUT,
) -> subprocess.CompletedProcess:
    """Run ``tools/pragma_targets.py targets --source <source_rel>`` once,
    scoped to one file so ``collect_family_examples`` can read the active
    owner's own ``family``/``asm`` row. Isolated so tests can stub it."""
    return subprocess.run(
        ["python3", "tools/pragma_targets.py", "targets", "--source", source_rel, "--limit", "100000"],
        cwd=repo_dir, capture_output=True, text=True, timeout=timeout,
    )


def _owner_family_and_asm_dir(
    repo_dir: Path, source_rel: str, owner: str, *, logger: Logger,
) -> tuple[str | None, Path | None]:
    """Best-effort ``(family, asm_dir)`` for ``owner`` from
    ``pragma_targets.py targets --source <source_rel>``'s own row for it.
    ``asm_dir`` is the ``disasm/asm/...`` directory ``owner``'s own ``.s``
    lives in -- the same directory every other GLOBAL_ASM owner split from
    that source file landed in, used as a cheap "same family cluster" proxy
    for an already-matched sibling that no longer has a pragma row (and so
    no ``family`` classification) of its own. ``(None, None)`` on any
    failure -- this must never raise."""
    try:
        proc = invoke_owner_family_row(repo_dir, source_rel)
    except (subprocess.TimeoutExpired, OSError) as exc:
        logger.log(f"{owner}: family lookup failed: {exc}")
        return None, None
    if proc.returncode != 0:
        return None, None
    try:
        rows = json.loads(proc.stdout).get("targets") or []
    except (json.JSONDecodeError, AttributeError):
        return None, None
    for row in rows:
        if isinstance(row, dict) and row.get("function") == owner:
            family = row.get("family")
            asm = row.get("asm")
            asm_dir = Path(asm).parent if isinstance(asm, str) else None
            return family, asm_dir
    return None, None


def _iter_defined_function_names(source_text: str, *, exclude: set[str]) -> list[str]:
    """Names of top-level function definitions in ``source_text``
    (``_FUNC_DEF_HEADER_RE``), in file order, excluding anything in
    ``exclude`` (typically the file's still-pragma owners)."""
    names: list[str] = []
    seen: set[str] = set()
    for match in _FUNC_DEF_HEADER_RE.finditer(source_text):
        name = match.group("name")
        if name in exclude or name in seen:
            continue
        seen.add(name)
        names.append(name)
    return names


def _render_family_examples(examples: list[dict]) -> list[str]:
    if not examples:
        return []
    lines = [
        "== worked examples: already-matched functions of the same family "
        "(study their spelling -- declaration order, types, control shape "
        "-- before drafting; never resend one of these bodies verbatim) =="
    ]
    for example in examples:
        family = example.get("family") or "unknown"
        lines.append(f"== matched example (family {family}): {example.get('name')} ==")
        size = example.get("size")
        if size:
            lines.append(f"   (.s size: {size} bytes)")
        lines.append(example.get("definition") or "")
    return lines


def collect_family_examples(
    repo_dir: Path,
    owner: str,
    source_rel: str,
    owner_state: dict,
    *,
    count: int = DEFAULT_EXAMPLES,
    logger: Logger,
) -> list[dict]:
    """Fetch (once per owner per run) and cache up to ``count`` already-
    matched functions of ``owner``'s family, for ``build_prompt``'s worked-
    examples section.

    Prefers ``tools/pragma_targets.py similar <owner>`` (opcode-shape
    similarity against every previously accepted candidate -- AGENTS.md
    §2.5 step 2); each returned row's ``code`` is already a complete C
    definition, taken verbatim. When that returns nothing usable, falls
    back to other already-defined (non-pragma) functions in the same source
    file -- preferring ones whose ``.s`` still lives in the owner's own
    nonmatchings directory (the cheap "same family" signal: that is exactly
    where ``list_targets``'s own family classification comes from) -- and,
    only if that is still short of ``count``, other source files in the
    same directory (e.g. a `fragments/NN/` overlay).

    ``owner_state["examples_fetched"]`` remembers the attempt happened (even
    a zero-result one) so this is never retried every iteration of the same
    owner; ``owner_state["examples"]`` carries the cached list through
    ``--resume``/``--seed-from``. Returns ``[]`` without marking the fetch
    done when ``count <= 0`` (``--examples 0`` disables the feature
    entirely, including the one-time lookups).
    """
    if owner_state.get("examples_fetched"):
        return owner_state.get("examples") or []
    if count <= 0:
        return []
    owner_state["examples_fetched"] = True
    owner_state["examples"] = []

    examples: list[dict] = []
    budget = EXAMPLES_BYTE_CAP

    def _add(name: str, family: str | None, definition: str, size: int | None) -> bool:
        nonlocal budget
        if budget <= 0:
            return False
        text = definition.strip() + "\n"
        if len(text) > budget:
            text = text[:budget].rstrip() + "\n/* ... truncated ... */\n"
        examples.append({"name": name, "family": family, "definition": text, "size": size})
        budget -= len(text)
        return True

    family, asm_dir = _owner_family_and_asm_dir(repo_dir, source_rel, owner, logger=logger)

    try:
        proc = invoke_similar_solved(repo_dir, owner, limit=count)
    except (subprocess.TimeoutExpired, OSError) as exc:
        logger.log(f"{owner}: `similar` lookup failed: {exc}; falling back to file/directory siblings")
        proc = None

    if proc is not None and proc.returncode == 0:
        try:
            rows = json.loads(proc.stdout)
        except json.JSONDecodeError:
            rows = []
        for row in rows if isinstance(rows, list) else []:
            if len(examples) >= count:
                break
            if not isinstance(row, dict):
                continue
            name, code = row.get("function"), row.get("code")
            if not name or not code:
                continue
            if not _add(name, family, code, None):
                break
        if examples:
            logger.log(f"{owner}: {len(examples)} family example(s) via `pragma_targets.py similar`")
            owner_state["examples"] = examples
            return examples

    # Fallback: siblings already defined in the same source file, then (if
    # still short) other files in the same directory.
    try:
        source_text = (repo_dir / source_rel).read_text(encoding="utf-8", errors="replace")
    except OSError as exc:
        logger.log(f"{owner}: could not read {source_rel} for family examples: {exc}")
        owner_state["examples"] = examples
        return examples

    pragma_owners = {match.group(1) for match in PRAGMA_RE.finditer(source_text)}
    pragma_owners.add(owner)
    for name in _iter_defined_function_names(source_text, exclude=pragma_owners):
        if len(examples) >= count:
            break
        definition = extract_installed_function(source_text, name)
        if not definition:
            continue
        size = None
        if asm_dir is not None:
            candidate_asm = repo_dir / asm_dir / f"{name}.s"
            try:
                if candidate_asm.is_file():
                    size = candidate_asm.stat().st_size
            except OSError:
                size = None
        _add(name, family, definition, size)

    if len(examples) < count:
        directory = (repo_dir / source_rel).parent
        try:
            siblings = sorted(p for p in directory.glob("*.c") if p != (repo_dir / source_rel))
        except OSError:
            siblings = []
        seen_names = {example["name"] for example in examples}
        for sibling_path in siblings:
            if len(examples) >= count:
                break
            try:
                sibling_text = sibling_path.read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            sibling_pragma_owners = {match.group(1) for match in PRAGMA_RE.finditer(sibling_text)}
            for name in _iter_defined_function_names(sibling_text, exclude=sibling_pragma_owners):
                if len(examples) >= count:
                    break
                if name in seen_names:
                    continue
                definition = extract_installed_function(sibling_text, name)
                if not definition:
                    continue
                seen_names.add(name)
                _add(name, family, definition, None)

    if examples:
        logger.log(f"{owner}: {len(examples)} family example(s) from file/directory siblings")
    owner_state["examples"] = examples
    return examples


# ---------------------------------------------------------------------------
# Declaration hygiene (Part B)
#
# A generator often repeats a same-file callee's prototype in the batch's
# shared "declarations" blob even though the source already declares (or
# defines) it -- IDO accepts the redundant redeclaration, but it is noise a
# generator keeps re-deriving every iteration, and an inconsistent repeat can
# quietly disagree with the real signature. Drop only exact top-level
# "declarations" statements that name something the file already declares or
# defines; a nested extern inside a candidate's own body is left alone (the
# runner will report a real conflict) -- see the prompt-side rule line
# instead (_extern_block_symbol_names / build_prompt).
# ---------------------------------------------------------------------------

_DECL_TRAILING_NAME_RE = re.compile(r"([A-Za-z_]\w*)\s*$")
_DECL_FUNC_PTR_NAME_RE = re.compile(r"\(\s*\*\s*([A-Za-z_]\w*)\s*\)")


def _split_declaration_statements(declarations: str) -> list[str]:
    """Split a batch's ``declarations`` blob into individual ``...;`` statements."""
    if not declarations:
        return []
    statements: list[str] = []
    for chunk in re.split(r"(?<=;)", declarations):
        statement = chunk.strip()
        if statement:
            statements.append(statement)
    return statements


def _declaration_statement_name(statement: str) -> str | None:
    """Best-effort extraction of the symbol name one declaration statement declares.

    Handles ``extern RET name(params);`` / ``RET name(params);`` (the name
    right before the first ``(``, or inside ``(*name)`` for a function-
    pointer declarator) and plain data declarations, ``extern TYPE name;`` /
    ``extern TYPE name[N];`` (the identifier before ``;``/``[``).
    """
    text = statement.strip().rstrip(";").strip()
    paren = text.find("(")
    if paren != -1:
        head = text[: text.find(")", paren) + 1] if ")" in text[paren:] else text
        ptr_match = _DECL_FUNC_PTR_NAME_RE.search(head)
        if ptr_match:
            return ptr_match.group(1)
        match = _DECL_TRAILING_NAME_RE.search(text[:paren].rstrip())
        return match.group(1) if match else None
    bracket = text.find("[")
    if bracket != -1:
        text = text[:bracket].rstrip()
    match = _DECL_TRAILING_NAME_RE.search(text)
    return match.group(1) if match else None


def _name_declared_in_source(name: str, source_text: str) -> bool:
    """Whether ``name`` already has a declaration, definition, or data symbol
    in ``source_text``: a call/prototype/definition context (``name(``), an
    existing ``extern ...;`` naming it, or an array declaration (``name[``)."""
    escaped = re.escape(name)
    if re.search(rf"\b{escaped}\s*\(", source_text):
        return True
    if re.search(rf"\bextern\b[^;{{}}]*\b{escaped}\b[^;{{}}]*;", source_text):
        return True
    if re.search(rf"\b{escaped}\s*\[", source_text):
        return True
    return False


def _find_source_extern_declaration(name: str, source_text: str) -> str | None:
    """Return the exact text of ``name``'s declaration in ``source_text`` if
    it is a plain one-line ``extern ...;`` statement (no braces, nothing
    else on the line) -- the only shape a companion_edit can safely retarget.
    ``None`` when ``name`` is declared some other way (a function definition,
    an array, a multi-line extern, ...)."""
    pattern = re.compile(
        rf"^[ \t]*extern\b[^\n{{}};]*\b{re.escape(name)}\b[^\n{{}};]*;[ \t]*$", re.M,
    )
    match = pattern.search(source_text)
    return match.group(0) if match else None


# Bare C type keywords: never mistaken for a trailing parameter *name* when
# normalising a declaration's signature (see _strip_param_name) -- "unsigned
# int" is one unnamed parameter, not a type "unsigned" named "int".
_KNOWN_TYPE_TOKENS = {
    "void", "char", "short", "int", "long", "float", "double",
    "signed", "unsigned", "const", "volatile", "struct", "union", "enum",
    "s8", "s16", "s32", "s64", "u8", "u16", "u32", "u64", "f32", "f64",
}
_PARAM_TRAILING_NAME_RE = re.compile(r"^(?P<type>.*[*\s])(?P<name>[A-Za-z_]\w*)$")


def _strip_param_name(param: str) -> str:
    """Drop one parameter's trailing declarator name, e.g. ``"void *arg0"``
    -> ``"void *"``, ``"s32 arg0"`` -> ``"s32"``. A param with no name
    (``"void *"``, ``"s32"``, an unnamed ``"unsigned int"``) is returned
    unchanged."""
    param = param.strip()
    if not param or param in ("void", "..."):
        return param
    match = _PARAM_TRAILING_NAME_RE.match(param)
    if not match:
        return param
    if match.group("name") in _KNOWN_TYPE_TOKENS:
        return param
    type_part = match.group("type").rstrip()
    return type_part or param


def _normalize_declaration_signature(statement: str) -> str:
    """Normalise one declaration statement for signature comparison:
    collapse whitespace, standardize ``*`` spacing, and drop parameter
    *names* (keeping their types) so ``"extern f64 f(void *arg0);"`` and
    ``"extern f64 f(void *);"`` compare equal but a differing return type or
    parameter type does not."""
    text = statement.strip().rstrip(";").strip()
    text = re.sub(r"\s+", " ", text)
    text = re.sub(r"\s*\*\s*", " *", text)
    text = re.sub(r"\s+", " ", text).strip()
    paren = text.find("(")
    if paren == -1:
        return text
    head = text[:paren].rstrip()
    rest = text[paren:]
    close = rest.rfind(")")
    if close == -1:
        return text
    params_str = rest[1:close]
    tail = rest[close + 1:].strip()
    params = [p.strip() for p in params_str.split(",")] if params_str.strip() else []
    normalized_params = [_strip_param_name(p) for p in params]
    result = f"{head}({', '.join(normalized_params)})"
    return f"{result} {tail}" if tail else result


def filter_declarations(batch: dict, source_text: str) -> tuple[dict, list[str], list[dict]]:
    """Drop top-level ``declarations`` statements that redeclare a name the
    source file already declares or defines, and flag the ones that would
    redeclare a name under a DIFFERENT signature (issue #38: a stale file
    declaration must not silently win over a batch's retyped one).

    For each statement naming something already in ``source_text``:
    - If the source declares it via a full definition/array/multi-line
      extern (no single comparable ``extern ...;`` line), or the comparable
      line's normalised signature matches the batch's: dropped silently, as
      before.
    - If the source's plain one-line ``extern ...;`` declaration has a
      DIFFERENT normalised signature: the batch line is a genuine type
      conflict, recorded in the returned ``conflicts`` list. Unless ``name``
      is itself a GLOBAL_ASM owner in this file (never safe to retarget --
      it has no real signature yet), the batch line becomes a
      ``companion_edit`` that replaces the file's stale line, and is removed
      from "declarations" (the companion_edit now supplies the correct
      type, so leaving it in "declarations" too would just redeclare it).
      For a GLOBAL_ASM-owner name, no companion_edit is made and the batch
      line is instead kept in "declarations" as-is (flagged in the
      conflict as such).

    Returns ``(filtered_batch, dropped_statements, conflicts)``.
    ``filtered_batch`` is a shallow copy of ``batch`` with a (possibly
    empty) "declarations" string and, when any companion_edits were
    derived, an updated "companion_edits" list -- or ``batch`` unchanged
    when nothing was dropped/flagged.
    """
    statements = _split_declaration_statements(batch.get("declarations") or "")
    if not statements:
        return batch, [], []
    pragma_owners = {match.group(1) for match in PRAGMA_RE.finditer(source_text)}
    kept: list[str] = []
    dropped: list[str] = []
    conflicts: list[dict] = []
    new_companion_edits: list[dict] = []
    for statement in statements:
        name = _declaration_statement_name(statement)
        if not name or not _name_declared_in_source(name, source_text):
            kept.append(statement)
            continue
        file_line = _find_source_extern_declaration(name, source_text)
        if file_line is None:
            # Declared some other way (a definition, an array, a multi-line
            # extern...) -- no comparable single-line signature to check
            # against, so fall back to the old silent-drop behavior.
            dropped.append(statement)
            continue
        file_sig = _normalize_declaration_signature(file_line)
        batch_sig = _normalize_declaration_signature(statement)
        if file_sig == batch_sig:
            dropped.append(statement)
            continue
        is_pragma_owner = name in pragma_owners
        conflicts.append({
            "name": name,
            "file_declaration": file_line.strip(),
            "batch_declaration": statement.strip(),
            "file_signature": file_sig,
            "batch_signature": batch_sig,
            "companion_edit": not is_pragma_owner,
        })
        if is_pragma_owner:
            # Can't safely retarget a still-pragma owner's declaration --
            # keep the batch's line in "declarations" as-is (a warning is
            # logged by the caller); this risks a redeclaration diagnostic,
            # but a silently-stale extern is worse (issue #38).
            kept.append(statement)
            continue
        edit = {"function": name, "old": file_line, "new": statement.strip()}
        if edit not in new_companion_edits:
            new_companion_edits.append(edit)
        # Not kept in "declarations": the companion_edit now supplies the
        # correct type in place, so repeating it here would just redeclare it.
    if not dropped and not conflicts:
        return batch, [], []
    filtered = dict(batch)
    filtered["declarations"] = "\n".join(kept)
    if new_companion_edits:
        existing_edits = list(batch.get("companion_edits") or [])
        for edit in new_companion_edits:
            if edit not in existing_edits:
                existing_edits.append(edit)
        filtered["companion_edits"] = existing_edits
    return filtered, dropped, conflicts


_EXTERN_BLOCK_SECTION_RE = re.compile(
    r"== extern/prototype block \(deduplicated\) ==\n(.*?)(?=\n==|\Z)", re.S
)
_EXTERN_BLOCK_SYMBOL_RE = re.compile(r"\b(?:func_[0-9A-Fa-f]+|D_[0-9A-Fa-f]+)\b")


def _extern_block_symbol_names(file_brief: str) -> list[str]:
    """Extract func_/D_ symbol names from ``file_brief_text``'s "extern/
    prototype block (deduplicated)" section, in first-seen order."""
    match = _EXTERN_BLOCK_SECTION_RE.search(file_brief)
    if not match:
        return []
    names: list[str] = []
    seen: set[str] = set()
    for name in _EXTERN_BLOCK_SYMBOL_RE.findall(match.group(1)):
        if name not in seen:
            seen.add(name)
            names.append(name)
    return names


# ---------------------------------------------------------------------------
# Prompt construction
# ---------------------------------------------------------------------------

# The "iterate before you write the batch" rule, toggled by --probe-tool
# (default "on"; see parse_args/main). ON is for an agentic generator that
# has real Read/Write/Bash tool access (claude.sh, codex.sh, qwen.sh,
# kimi.sh) and can shell out to tools/probe_one.py itself; OFF is for the
# plain-HTTP wrappers (openai_compat.sh, kimi_api.sh) that have no tool
# access at all, where a paragraph telling the model to run a local script
# would just be noise -- entrypoint.sh sets PROBE_TOOL=off for those two
# AGENT values (see docs/CONTAINER_AGENT.md's "Fast inner loop" section).
PROBE_TOOL_RULE_ON = """\
- You MAY and SHOULD iterate before writing the batch: put a draft in a file
  and run `python3 tools/probe_one.py --source {source_rel} --function {owner}
  --body draft.c [--declarations decls.h]` (about 10-20 s each; use --quiet
  for just the numbers). Read the diff, change one thing, probe again. Do
  this as many times as useful (dozens is fine), then put your best 8-16
  distinct bodies in the batch, best first. probe_one.py's "--body" must
  point at a file holding a COMPLETE function definition (return type, name,
  parameter list, braces) -- the same shape a batch candidate's "body" must
  be, not a bare statement block. The working directory is the repo root, so
  "{source_rel}" and any relative paths you pass resolve from there. Do NOT
  run make, fleet_probe.py, the permuter, import tools/try_pragma_compare.py or
  call its Python API directly, or write into disasm/src yourself. probe_one.py is
  the only sanctioned way to compile or compare.
- Time budget: about {budget_minutes} minutes. Write a first batch file to
  {batch_path} within the first few minutes (even 8 rough candidates), then
  keep improving and OVERWRITE it whenever you have a better set. If you run
  out of time, whatever is in the file is what gets probed.
"""

PROBE_TOOL_RULE_OFF = """\
- Do NOT compile, assemble, run make, probes or the permuter yourself: the
  driver probes every candidate against the ROM right after you write the
  file and feeds the diagnostics back. Spend your time on the C, not on
  building a toolchain loop.
"""

BATCH_CONTRACT = """\
Write a JSON batch file to the path given below (create or overwrite it).
Time budget: about {budget_minutes} minutes. Write a first batch file to
{batch_path} within the first few minutes (even 8 rough candidates), then
keep improving and OVERWRITE it whenever you have a better set. If you run
out of time, whatever is in the file is what gets probed.
Schema:

{{
  "source": "{source_rel}",
  "declarations": "extern ...;\\n...",   // optional: shared externs/prototypes
  "companion_edits": [                    // optional
    {{"function": "func_...", "old": "exact old text", "new": "new text"}}
  ],
  "candidates": [
    {{"function": "{owner}", "label": "family:shape:hypothesis",
     "body": "<COMPLETE function definition: return type, name, parameter list and braces>"}}
  ]
}}

Rules:
- "body" is the whole function definition that replaces the #pragma line,
  e.g. "f64 {owner}(void *arg0, void *arg1) {{ ... }}" on one or more lines. A bare brace
  block with no signature is a compile failure, not a candidate.
- Every candidate's "function" must be exactly "{owner}".
- Provide between 8 and 16 candidates; each candidate tests exactly ONE
  hypothesis (declaration order, temp widths, index-vs-pointer form,
  guard-return vs assign-then-return, explicit temporaries, old-style callee
  prototypes, ...).
- Give every candidate a distinct, descriptive "label"
  ("<family>:<shape>:<hypothesis>").
{probe_rule}- Do not add or remove any "#pragma GLOBAL_ASM" line.
- A companion_edit may only retarget an existing C definition/prototype
  already in the file (or the candidate owner's own stale extern); it must
  not target another still-pragma owner.
- Write ONLY that JSON object (no commentary) to: {batch_path}
"""

# Static reading guide for the per-candidate feedback rendered below (see
# _render_best_candidates). Wording for the mismatch_kind rows is pulled
# from AGENTS.md §2 rule 5 / §2.5 step 5 and docs/REGISTER_TIES.md, so a
# generator gets the same guidance a human agent works from.
DIFF_READING_GUIDE = """\
== how to read the diff ==
Map the signal in a candidate's diagnostics to a source-level change, then
vary only that -- do not restructure the whole function on a repeat diagnostic:
- Stack frame size differs (the "frame:" line, or an "addiu $sp" mismatch)
  while the rest of the body matches: the number/width of locals, u8 buffer
  sizes, or an extra temporary. This is `immediate_drift` territory --
  offsets, strides, literal widths, frame padding.
- Register drift with identical opcodes (mismatch_kind
  register_allocation_only, or similarity_score near 1.0 with a lower raw
  score): declaration order, temporaries, widths (AGENTS.md §2 rule 5) --
  not a semantic problem. For an operand_or_scheduling_drift near-miss, try
  commute-swap, decl-order, hoist-temp, type-width, loop-form,
  reorder-store-call (AGENTS.md §4). A clean register tie
  (similarity_score >= 0.99, mismatch_kind register_allocation_only) rarely
  yields to more hand variants -- see docs/REGISTER_TIES.md and stop after
  two batches.
- Missing/extra nop, or a shifted delay-slot instruction: statement order,
  or short-circuit vs a nested if.
- jump-table / jr differences: the switch's case shape; a non-text
  section_layout_drift on a switch means the file needs its .rodata
  subsegment first (AGENTS.md §2 rule 7), not a body rewrite.
- Float immediates differ: an f32 vs f64 literal, or constant folding
  happening at a different point.
- Call argument setup order differs: the evaluation order of the
  arguments, or an explicit temporary precomputed before the call vs
  passed inline.
- symbol_size_drift, or a duplicated jr/nop / alignment tail: a verified
  `#pragma C_FUNCTION_PADDING(n)` or a `<owner>_padding` helper, not a body
  change (AGENTS.md §2 rule 5).
- text_layout_drift: a recoverable owner-size or frame mismatch -- fix the
  body or add verified padding; the candidate stays eligible for a
  sequential gate once it does.
"""


def _render_best_candidates(best_candidates: list[dict], *, full_diff_count: int) -> list[str]:
    """Render the "best candidates tried so far" section.

    The first ``full_diff_count`` entries (already sorted best-first by the
    caller) get the frame/instruction-count/first-mismatch lines and the
    diff excerpt from their ``feedback`` dict; the rest get the header line
    only. See build_prompt's size guard for why ``full_diff_count`` can be
    less than ``len(best_candidates)``.
    """
    lines: list[str] = [
        "== best candidates tried so far this run (highest similarity first; "
        "do not resend these bodies verbatim, but use their diagnostics) =="
    ]
    for index, entry in enumerate(best_candidates):
        lines.append(
            f"-- label={entry.get('label')} similarity={entry.get('similarity_score')} "
            f"raw={entry.get('raw_similarity_score')} mismatch={entry.get('mismatch_kind')} "
            f"futility={entry.get('futility')}"
        )
        diagnostic = entry.get("diagnostic")
        if diagnostic:
            lines.append(f"   diagnostic: {diagnostic}")
        if entry.get("normalized_only"):
            lines.append(
                "   NORMALIZED-ONLY MATCH: the shape is right but "
                f"immediates/registers/fields differ (raw={entry.get('raw_similarity_score')}); "
                "vary constants, field offsets and operand order, not structure."
            )
        if index < full_diff_count:
            feedback = entry.get("feedback") or {}
            expected_size = feedback.get("expected_size")
            actual_size = feedback.get("actual_size")
            if expected_size is not None and actual_size is not None and expected_size != actual_size:
                lines.append(f"   frame: expected {expected_size} bytes, actual {actual_size}")
            expected_count = feedback.get("expected_instruction_count")
            actual_count = feedback.get("actual_instruction_count")
            if expected_count is not None or actual_count is not None:
                lines.append(f"   instructions: expected {expected_count}, actual {actual_count}")
            first_diff_offset = feedback.get("first_diff_offset")
            if first_diff_offset is not None:
                lines.append(
                    f"   first mismatch at offset {first_diff_offset}: "
                    f"expected `{feedback.get('expected_instruction_text')}` "
                    f"actual `{feedback.get('actual_instruction_text')}`"
                )
            diff_excerpt = feedback.get("diff_excerpt")
            if diff_excerpt:
                lines.append("   diff:")
                lines.extend(f"   {line}" for line in diff_excerpt.splitlines())
        else:
            lines.append("   (diff omitted -- see the top candidates above for the excerpt)")
        body = entry.get("body")
        if body:
            lines.append("   body:")
            lines.append(body)
    return lines


def build_prompt(
    *,
    owner: str,
    source_rel: str,
    file_brief: str,
    asm_text: str,
    best_candidates: list[dict],
    permuter_seed: dict | None,
    batch_path: Path,
    tried_labels: list[str] | None = None,
    m2c_draft: str | None = None,
    examples: list[dict] | None = None,
    probe_tool: bool = True,
    type_conflicts: list[dict] | None = None,
    generator_timeout_minutes: int = round(DEFAULT_GENERATOR_TIMEOUT / 60),
) -> str:
    extern_names = _extern_block_symbol_names(file_brief)
    budget_minutes = max(1, generator_timeout_minutes)
    probe_rule = (PROBE_TOOL_RULE_ON if probe_tool else PROBE_TOOL_RULE_OFF).format(
        source_rel=source_rel, owner=owner, batch_path=batch_path, budget_minutes=budget_minutes,
    )

    def _assemble(full_diff_count: int) -> str:
        parts = [
            f"You are generating candidate C function bodies for one GLOBAL_ASM",
            f"owner, {owner}, in {source_rel}. Read the file brief and the target",
            "assembly below, then write a batch of candidate bodies to the path",
            "given at the end of this prompt.",
            "",
            "== file brief ==",
            file_brief.strip(),
            "",
            f"== target assembly: {owner} ==",
            asm_text.strip(),
        ]
        if examples:
            parts.append("")
            parts.extend(_render_family_examples(examples))
        if m2c_draft:
            parts.append("")
            parts.append("== m2c draft (structure hint, not a match; retype/reshape freely) ==")
            parts.append(m2c_draft.strip())
        if best_candidates:
            parts.append("")
            parts.extend(_render_best_candidates(best_candidates, full_diff_count=full_diff_count))
            parts.append("")
            parts.append(DIFF_READING_GUIDE.rstrip("\n"))
            parts.append("")
            parts.append(
                "Change the hypothesis family for any candidate whose diagnostic "
                "repeats one shown above instead of resending the same source shape."
            )
        if tried_labels:
            shown = list(tried_labels)[-TRIED_LABELS_SHOWN:]
            parts.append("")
            parts.append(
                f"== labels already tried this run (showing last {len(shown)} of "
                f"{len(tried_labels)}; do not resend a body under a repeat of one of "
                "these hypotheses) =="
            )
            parts.append(", ".join(shown))
        if permuter_seed:
            parts.append("")
            parts.append(
                "== decomp-permuter output (score="
                f"{permuter_seed.get('score')}; 0 means an instruction-exact match -- "
                "submit it close to verbatim as one candidate) =="
            )
            parts.append(permuter_seed.get("body") or "")
        if extern_names:
            parts.append("")
            parts.append(
                "The file already declares these callees/data (do not redeclare): "
                + ", ".join(extern_names)
            )
        companion_edit_conflicts = [c for c in (type_conflicts or []) if c.get("companion_edit")]
        if companion_edit_conflicts:
            parts.append("")
            for conflict in companion_edit_conflicts:
                parts.append(
                    f"the file declares {conflict['name']} as `{conflict['file_declaration']}`; "
                    "your batch retyped it via a companion edit."
                )
        parts.append("")
        parts.append(BATCH_CONTRACT.format(
            source_rel=source_rel, owner=owner, batch_path=batch_path, probe_rule=probe_rule,
            budget_minutes=budget_minutes,
        ))
        return "\n".join(parts)

    prompt = _assemble(len(best_candidates))
    if len(prompt) > PROMPT_SIZE_CAP and len(best_candidates) > FULL_DIFF_CANDIDATES:
        # The fully-rendered diffs pushed the prompt past the size guard:
        # keep the excerpt only for the top FULL_DIFF_CANDIDATES entries
        # (already sorted best-first) and fall back to header-only for the
        # rest, rather than truncating file_brief/asm_text/bodies.
        prompt = _assemble(FULL_DIFF_CANDIDATES)
    return prompt


# ---------------------------------------------------------------------------
# Generator invocation
# ---------------------------------------------------------------------------

def render_generator_command(template: str, prompt_path: Path, batch_path: Path) -> str:
    return template.replace("{prompt}", shlex.quote(str(prompt_path))).replace(
        "{batch}", shlex.quote(str(batch_path))
    )


def invoke_generator(command: str, *, cwd: Path, timeout: float) -> subprocess.CompletedProcess:
    """Run the external generator command once. Isolated so tests can stub it.

    Runs via ``_run_bounded`` (not a bare ``subprocess.run``) so a
    termination signal that arrives while this call is blocking (up to
    ``--generator-timeout``, 30 minutes by default) can kill it immediately
    -- see ``request_stop``.
    """
    return _run_bounded(command, cwd=cwd, timeout=timeout, shell=True)


# ---------------------------------------------------------------------------
# Generator health tracking (quota / rate-limit exhaustion)
# ---------------------------------------------------------------------------

# Whole-phrase, case-insensitive signatures. "429" only matches as a
# standalone token (\b429\b) so reasoning text mentioning an offset like
# "0x429" does not trip it.
QUOTA_SIGNATURES = (
    r"\brate[ -]limit\b",
    r"\bquota\b",
    r"\busage limit\b",
    r"\btoo many requests\b",
    r"\b429\b",
)
_QUOTA_RE = re.compile("|".join(f"(?:{sig})" for sig in QUOTA_SIGNATURES), re.IGNORECASE)


def _decode(text: object) -> str:
    if text is None:
        return ""
    if isinstance(text, bytes):
        return text.decode("utf-8", errors="replace")
    return str(text)


def _looks_like_quota(*texts: object) -> bool:
    combined = " ".join(_decode(t) for t in texts)
    return bool(_QUOTA_RE.search(combined))


def _record_generator_outcome(
    gen_failures: dict,
    *,
    ok: bool,
    quota: bool,
    stderr_tail: str,
    owner: str,
    iteration: int,
    max_failures: int,
    logger: Logger,
) -> bool:
    """Update the run's consecutive-generator-failure counter.

    A successful iteration (generator exited zero AND produced a valid batch)
    resets the counter to zero. Otherwise the counter is incremented by 2 when
    the failure looks like a quota/rate-limit signature, else by 1. Returns
    True once ``max_failures`` is reached, meaning the whole run should stop.
    """
    if ok:
        gen_failures["consecutive"] = 0
        return False

    if quota:
        logger.log(f"{owner}: iter {iteration}: generator output looks like a quota/rate-limit signal")

    increment = 2 if quota else 1
    gen_failures["consecutive"] = gen_failures.get("consecutive", 0) + increment

    tail = stderr_tail.strip()
    if tail:
        logger.log(f"{owner}: iter {iteration}: generator stderr tail: {tail[-500:]}")

    logger.log(
        f"{owner}: iter {iteration}: generator failure count now "
        f"{gen_failures['consecutive']} (limit {max_failures})"
    )
    return max_failures > 0 and gen_failures["consecutive"] >= max_failures


# ---------------------------------------------------------------------------
# Probe invocation
# ---------------------------------------------------------------------------

def invoke_probe(
    repo_dir: Path, batch_path: Path, result_path: Path, *, timeout: float
) -> subprocess.CompletedProcess:
    """Run ``tools/fleet_probe.py`` once. Isolated so tests can stub it.

    Runs via ``_run_bounded`` (see ``invoke_generator``) so a termination
    signal that arrives while the probe is running can kill it immediately.
    """
    return _run_bounded(
        ["python3", "tools/fleet_probe.py", str(batch_path), "--json", str(result_path)],
        cwd=repo_dir, timeout=timeout,
    )


# ---------------------------------------------------------------------------
# Permuter invocation and polling
# ---------------------------------------------------------------------------

def _permuter_work_root(repo_dir: Path) -> Path:
    return repo_dir / "disasm" / "build" / "permuter"


def _snapshot_permuter_dirs(repo_dir: Path, function: str) -> set[str]:
    root = _permuter_work_root(repo_dir)
    if not root.is_dir():
        return set()
    prefix = function + "-"
    return {entry.name for entry in root.iterdir() if entry.is_dir() and entry.name.startswith(prefix)}


# Every permuter subprocess ``invoke_permuter`` launches is registered here
# until ``poll_permuter`` confirms it has exited (normally or by force); the
# run's finalize path (see ``_finalize_run``) sweeps whatever is left so a
# background permuter job (Part D) can never outlive the whole run, even one
# still mid-``run_permuter`` inside its worker thread when the run ends.
_PERMUTER_PROCESS_LOCK = threading.Lock()
_ACTIVE_PERMUTER_PROCESSES: set[subprocess.Popen] = set()


def _register_permuter_process(process: subprocess.Popen) -> None:
    with _PERMUTER_PROCESS_LOCK:
        _ACTIVE_PERMUTER_PROCESSES.add(process)


def _unregister_permuter_process(process: subprocess.Popen) -> None:
    with _PERMUTER_PROCESS_LOCK:
        _ACTIVE_PERMUTER_PROCESSES.discard(process)


def terminate_all_permuters() -> None:
    """Terminate every still-registered permuter subprocess.

    Safe to call any time (idempotent, tolerates an already-exited process).
    Called from ``_finalize_run`` so a run never leaves a permuter process
    behind, regardless of which owner's background job launched it.
    """
    with _PERMUTER_PROCESS_LOCK:
        processes = list(_ACTIVE_PERMUTER_PROCESSES)
    for process in processes:
        if process.poll() is None:
            _terminate_process_group(process)
        _unregister_permuter_process(process)


def invoke_permuter(
    repo_dir: Path,
    function: str,
    candidate_path: Path,
    declarations_path: Path | None,
    *,
    seconds: float,
    log_path: Path,
) -> subprocess.Popen:
    """Launch ``tools/permute_candidate.py`` in the background.

    Isolated so tests can stub it. The caller must poll (``poll_permuter``)
    rather than block on this process: it keeps its own work directory under
    ``disasm/build/permuter/<function>-<suffix>/`` (``--keep``), which is
    what a poller inspects.
    """
    command = [
        "python3", "tools/permute_candidate.py", function, str(candidate_path),
        "--seconds", str(seconds), "--keep",
    ]
    if declarations_path is not None:
        command += ["--declarations", str(declarations_path)]
    log_path.parent.mkdir(parents=True, exist_ok=True)
    log_handle = log_path.open("w", encoding="utf-8")
    try:
        process = subprocess.Popen(
            command, cwd=repo_dir, stdout=log_handle, stderr=subprocess.STDOUT,
            text=True, start_new_session=True,
        )
    finally:
        log_handle.close()
    _register_permuter_process(process)
    return process


def _terminate_process_group(process: subprocess.Popen, *, grace: float = 5.0) -> None:
    try:
        os.killpg(process.pid, signal.SIGTERM)
    except (ProcessLookupError, PermissionError, OSError):
        return
    try:
        process.wait(timeout=grace)
        return
    except subprocess.TimeoutExpired:
        pass
    try:
        os.killpg(process.pid, signal.SIGKILL)
    except (ProcessLookupError, PermissionError, OSError):
        pass
    try:
        process.wait(timeout=grace)
    except subprocess.TimeoutExpired:
        process.kill()
        try:
            process.wait(timeout=grace)
        except subprocess.TimeoutExpired:
            pass


# ---------------------------------------------------------------------------
# Graceful termination (SIGTERM/SIGINT)
#
# A ``docker run`` attached to a terminal session that ends sends SIGTERM to
# the container's process; the driver used to just die mid-``subprocess.run``
# (up to a 30-minute generator call), leaving state.json (saved every
# iteration -- see _save_state) intact but summary.json never written at all
# (it was only ever written by _finalize_run, on a normal exit path).
#
# main() installs ``request_stop`` as the handler for both signals. It sets
# the module-level ``_STOP_REQUESTED`` flag (checked by main()'s owner loop,
# process_owner's per-iteration loop, and run_iteration -- see each of their
# "before starting a new generator call"/"before starting a probe"/"before
# launching a permuter" checks) and, if a generator or probe subprocess is
# currently blocking the driver (launched via ``_run_bounded``, registered
# for exactly as long as it runs), terminates it immediately so the driver
# never has to wait out that call's own timeout before reaching the next
# stop_requested() check. A background permuter job's subprocess is handled
# separately: it is already tracked in _ACTIVE_PERMUTER_PROCESSES and swept
# by terminate_all_permuters() inside _finalize_run.
# ---------------------------------------------------------------------------

_STOP_REQUESTED = threading.Event()

_BOUNDED_PROCESS_LOCK = threading.Lock()
_ACTIVE_BOUNDED_PROCESS: subprocess.Popen | None = None


def stop_requested() -> bool:
    return _STOP_REQUESTED.is_set()


def _register_bounded_process(process: subprocess.Popen) -> None:
    global _ACTIVE_BOUNDED_PROCESS
    with _BOUNDED_PROCESS_LOCK:
        _ACTIVE_BOUNDED_PROCESS = process


def _unregister_bounded_process(process: subprocess.Popen) -> None:
    global _ACTIVE_BOUNDED_PROCESS
    with _BOUNDED_PROCESS_LOCK:
        if _ACTIVE_BOUNDED_PROCESS is process:
            _ACTIVE_BOUNDED_PROCESS = None


def _terminate_active_bounded_process() -> None:
    """Terminate whatever generator/probe subprocess ``_run_bounded`` has
    currently registered as running, if any. Safe to call any time
    (idempotent, tolerates none registered or one that already exited)."""
    with _BOUNDED_PROCESS_LOCK:
        process = _ACTIVE_BOUNDED_PROCESS
    if process is not None and process.poll() is None:
        _terminate_process_group(process)


def request_stop(signum: int, frame=None, *, logger: "Logger | None" = None) -> None:
    """SIGTERM/SIGINT handler (installed by main(), optionally bound to the
    run's logger via ``functools.partial``). Idempotent -- only the first
    call logs; every call re-attempts terminating the active bounded
    subprocess (harmless if there isn't one, or it already exited)."""
    first = not _STOP_REQUESTED.is_set()
    _STOP_REQUESTED.set()
    if first:
        try:
            name = signal.Signals(signum).name
        except ValueError:
            name = str(signum)
        message = f"termination requested ({name}); finishing current step"
        if logger is not None:
            logger.log(message)
        else:
            print(f"[{now_iso()}] {message}")
    _terminate_active_bounded_process()


def _run_bounded(
    args, *, cwd: Path, timeout: float, shell: bool = False,
) -> subprocess.CompletedProcess:
    """``subprocess.run``-alike (captures text stdout/stderr, honors
    ``timeout``, raises ``subprocess.TimeoutExpired`` on expiry) used by
    ``invoke_generator``/``invoke_probe`` in place of a bare
    ``subprocess.run`` call.

    Runs the child in its own process group (``start_new_session=True``) and
    registers it as the run's current "active bounded process" for as long
    as it is alive -- see ``_terminate_active_bounded_process``, called from
    ``request_stop`` -- so a termination signal that arrives while this call
    is blocking kills the whole subprocess tree (including anything a
    ``shell=True`` command spawned) immediately, instead of leaving the
    driver to wait out the call's full timeout.
    """
    process = subprocess.Popen(
        args, shell=shell, cwd=cwd,
        stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True,
        start_new_session=True,
    )
    _register_bounded_process(process)
    try:
        try:
            stdout, stderr = process.communicate(timeout=timeout)
        except subprocess.TimeoutExpired:
            _terminate_process_group(process)
            stdout, stderr = process.communicate()
            raise subprocess.TimeoutExpired(args, timeout, output=stdout, stderr=stderr)
    finally:
        _unregister_bounded_process(process)
    return subprocess.CompletedProcess(args, process.returncode, stdout, stderr)


def _extract_function_body(code: str, function: str) -> str:
    """Return only ``function``'s definition from a permuter output file."""
    header = re.compile(rf"^[^\n;{{}}]*\b{re.escape(function)}\s*\([^;]*?\)\s*\{{", re.M | re.S)
    match = header.search(code)
    if match is None:
        return code
    depth = 0
    index = match.end() - 1
    while index < len(code):
        if code[index] == "{":
            depth += 1
        elif code[index] == "}":
            depth -= 1
            if depth == 0:
                return code[match.start(): index + 1].strip() + "\n"
        index += 1
    return code


def _collect_permuter_outputs(work_dir: Path, function: str) -> list[dict]:
    outputs: list[dict] = []
    try:
        entries = list(work_dir.iterdir())
    except OSError:
        return outputs
    for entry in entries:
        match = OUTPUT_DIR_RE.match(entry.name)
        if not match or not entry.is_dir():
            continue
        source = entry / "source.c"
        if not source.exists():
            continue
        try:
            text = source.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        outputs.append({"score": int(match.group(1)), "code": _extract_function_body(text, function)})
    outputs.sort(key=lambda item: (item["score"], len(item["code"])))
    return outputs


def poll_permuter(
    repo_dir: Path,
    function: str,
    process: subprocess.Popen,
    before_dirs: set[str],
    *,
    budget_seconds: float,
    poll_interval: float = 5.0,
) -> dict:
    """Poll the permuter's kept output directory; never block on the process.

    Checks every ``poll_interval`` seconds for a new
    ``disasm/build/permuter/<function>-<suffix>/`` directory and, once found,
    what it contains, until the process exits or ``budget_seconds`` elapses
    -- whichever comes first. If the budget elapses first, the process (and
    its whole process group) is terminated.
    """
    work_root = _permuter_work_root(repo_dir)
    deadline = time.monotonic() + budget_seconds
    work_dir: Path | None = None
    while True:
        if work_dir is None:
            new = sorted(_snapshot_permuter_dirs(repo_dir, function) - before_dirs)
            if new:
                work_dir = work_root / new[0]
        if process.poll() is not None or time.monotonic() >= deadline:
            break
        time.sleep(poll_interval)

    timed_out = process.poll() is None
    if timed_out:
        _terminate_process_group(process)

    if work_dir is None:
        new = sorted(_snapshot_permuter_dirs(repo_dir, function) - before_dirs)
        if new:
            work_dir = work_root / new[0]

    outputs: list[dict] = []
    if work_dir is not None and work_dir.is_dir():
        outputs = _collect_permuter_outputs(work_dir, function)

    _unregister_permuter_process(process)
    return {
        "timed_out": timed_out,
        "work_dir": str(work_dir) if work_dir else None,
        "outputs": outputs,
        "best": outputs[0] if outputs else None,
    }


# A permuter run that exits on its own (never hit its time budget) with zero
# outputs in well under a normal pass almost always means base.c never even
# compiled (a bad declaration, a redeclaration, ...) -- see run_permuter's
# call to _log_permuter_quick_failure below. 10s is generous: a real
# permuter search that actually starts iterating variants runs for the whole
# budget; one that dies in the setup/compile step exits in a couple of
# seconds.
PERMUTER_QUICK_FAILURE_SECONDS = 10.0
PERMUTER_LOG_TAIL_LINES = 5


def _log_permuter_quick_failure(
    owner: str,
    iteration: int,
    label_suffix: str,
    result: dict,
    elapsed: float,
    *,
    logger: Logger,
) -> None:
    """Log a WARNING with the tail of the permuter's own ``permuter.log``
    when a run finishes suspiciously fast with zero outputs -- this is the
    class of failure that otherwise only shows up as a silent
    ``outputs=0`` in the one-line summary (e.g. base.c failed to compile
    because of a stale/conflicting declaration)."""
    work_dir = result.get("work_dir")
    tail_text = "(no work_dir kept -- pass --keep, or the permuter never got far enough to create one)"
    if work_dir:
        log_file = Path(work_dir) / "permuter.log"
        try:
            lines = log_file.read_text(encoding="utf-8", errors="replace").splitlines()
        except OSError:
            tail_text = f"(could not read {log_file})"
        else:
            tail = lines[-PERMUTER_LOG_TAIL_LINES:]
            tail_text = "\n".join(f"    {line}" for line in tail) if tail else "(permuter.log is empty)"
    logger.log(
        f"{owner}: WARNING permuter iter {iteration}{label_suffix} finished in {elapsed:.1f}s "
        f"with zero outputs (likely base.c failed to compile) -- last "
        f"{PERMUTER_LOG_TAIL_LINES} line(s) of permuter.log:\n{tail_text}"
    )


def run_permuter(
    repo_dir: Path,
    out_dir: Path,
    owner: str,
    iteration: int,
    body: str,
    declarations: str | None,
    *,
    permuter_seconds: float,
    logger: Logger,
    label_suffix: str = "",
) -> dict | None:
    """Write the permuter's input files, launch it, and poll for a result.

    ``label_suffix`` (default ``""``, unchanged filenames) distinguishes
    multiple bodies run for the same owner/iteration -- see
    ``_permuter_job_worker`` (Part D), which runs up to ``--permuter-bodies``
    of them sequentially in one background thread.
    """
    tmp_dir = out_dir / "tmp" / "permuter"
    tmp_dir.mkdir(parents=True, exist_ok=True)
    stem = f"{owner}_iter{iteration}{label_suffix}"
    candidate_path = tmp_dir / f"{stem}_candidate.c"
    candidate_path.write_text(body, encoding="utf-8")
    declarations_path = None
    if declarations:
        declarations_path = tmp_dir / f"{stem}_declarations.h"
        declarations_path.write_text(declarations, encoding="utf-8")

    before = _snapshot_permuter_dirs(repo_dir, owner)
    log_path = tmp_dir / f"{stem}_permuter.log"
    started = time.monotonic()
    try:
        process = invoke_permuter(
            repo_dir, owner, candidate_path, declarations_path,
            seconds=permuter_seconds, log_path=log_path,
        )
    except OSError as exc:
        logger.log(f"{owner}: permuter launch failed: {exc}")
        return None

    result = poll_permuter(repo_dir, owner, process, before, budget_seconds=permuter_seconds + 30.0)
    elapsed = time.monotonic() - started
    logger.log(
        f"{owner}: permuter iter {iteration}{label_suffix} finished timed_out={result['timed_out']} "
        f"outputs={len(result['outputs'])} best_score={(result['best'] or {}).get('score')}"
    )
    if not result["timed_out"] and not result["outputs"] and elapsed < PERMUTER_QUICK_FAILURE_SECONDS:
        _log_permuter_quick_failure(owner, iteration, label_suffix, result, elapsed, logger=logger)
    return result


# ---------------------------------------------------------------------------
# Background permuter jobs (Part D): the permuter runs concurrently with the
# *next* generator call instead of blocking the driver. A job is a single
# background thread that runs ``run_permuter`` sequentially over up to
# ``--permuter-bodies`` distinct candidate bodies from one iteration (never
# blocking the caller); the driver polls it (``poll_permuter_jobs``) at the
# start of the next iteration's prompt build and again after that
# iteration's probe, folding any newly-finished body's result into
# ``owner_state`` as it appears. Reuses ``run_permuter``/``invoke_permuter``/
# ``poll_permuter`` unchanged -- only the scheduling is new.
# ---------------------------------------------------------------------------

class PermuterJob:
    """One background permuter pass over up to ``permuter_bodies`` bodies.

    ``results`` is only ever appended to by the worker thread; a poller
    reads it under ``lock`` and tracks how much of it (``consumed``) it has
    already folded into ``owner_state``.
    """

    def __init__(self, thread: threading.Thread, owner: str, iteration: int, labels: list[str]) -> None:
        self.thread = thread
        self.owner = owner
        self.iteration = iteration
        self.labels = labels
        self.lock = threading.Lock()
        self.results: list[dict] = []
        self.consumed = 0


def _permuter_job_worker(
    repo_dir: Path,
    out_dir: Path,
    owner: str,
    iteration: int,
    bodies: list[tuple[str, str]],
    declarations: str | None,
    permuter_seconds: float,
    logger: Logger,
    job: PermuterJob,
) -> None:
    for index, (label, body) in enumerate(bodies):
        result = run_permuter(
            repo_dir, out_dir, owner, iteration, body, declarations,
            permuter_seconds=permuter_seconds, logger=logger, label_suffix=f"_b{index}",
        )
        if result is not None:
            with job.lock:
                job.results.append({"label": label, **result})


def start_permuter_job(
    repo_dir: Path,
    out_dir: Path,
    owner: str,
    iteration: int,
    bodies: list[tuple[str, str]],
    declarations: str | None,
    *,
    permuter_seconds: float,
    logger: Logger,
) -> PermuterJob:
    """Launch a background thread running the permuter over ``bodies``
    (``[(label, body), ...]``) one at a time; never blocks the caller."""
    labels = [label for label, _ in bodies]
    job = PermuterJob(thread=None, owner=owner, iteration=iteration, labels=labels)  # type: ignore[arg-type]
    thread = threading.Thread(
        target=_permuter_job_worker,
        args=(repo_dir, out_dir, owner, iteration, bodies, declarations, permuter_seconds, logger, job),
        daemon=True,
        name=f"permuter-{owner}-iter{iteration}",
    )
    job.thread = thread
    thread.start()
    return job


def poll_permuter_jobs(jobs: list[PermuterJob], owner_state: dict, *, logger: Logger) -> None:
    """Fold newly-finished bodies from background permuter jobs into
    ``owner_state`` (``permuter_runs`` history, ``permuter_seed`` -- lower
    score is better, 0 is instruction-exact). Safe to call repeatedly;
    already-folded results are never re-applied. Mutates ``jobs`` in place,
    dropping jobs whose thread has finished."""
    still_running: list[PermuterJob] = []
    for job in jobs:
        with job.lock:
            new_results = list(job.results[job.consumed:])
            job.consumed = len(job.results)
        for entry in new_results:
            best_output = entry.get("best")
            owner_state.setdefault("permuter_runs", []).append({
                "iteration": job.iteration,
                "label": entry.get("label"),
                "timed_out": entry.get("timed_out"),
                "best_score": (best_output or {}).get("score"),
            })
            if best_output is not None:
                current_seed = owner_state.get("permuter_seed")
                current_score = current_seed.get("score") if current_seed else None
                new_score = best_output.get("score")
                if current_score is None or (isinstance(new_score, (int, float)) and new_score < current_score):
                    owner_state["permuter_seed"] = {
                        "score": new_score,
                        "body": best_output.get("code"),
                        "iteration": job.iteration,
                        "label": entry.get("label"),
                    }
                    logger.log(
                        f"{job.owner}: permuter job iter {job.iteration} label={entry.get('label')} "
                        f"produced a new seed (score={new_score})"
                    )
        if job.thread.is_alive():
            still_running.append(job)
    jobs[:] = still_running


def _select_permuter_bodies(
    scored: list[dict], candidate_bodies: dict[str, str | None], *, limit: int,
) -> list[tuple[str, str]]:
    """Rank this iteration's scored attempts best-first (``attempt_rank``),
    excluding normalized-only matches, and return up to ``limit`` distinct
    ``(label, body)`` pairs -- the material a background permuter job runs
    on (Part D: up to the top 3 distinct bodies by default)."""
    ranked = sorted(
        (attempt for attempt in scored if not _is_normalized_only_match(attempt)),
        key=attempt_rank, reverse=True,
    )
    selected: list[tuple[str, str]] = []
    seen_bodies: set[str] = set()
    for attempt in ranked:
        label = attempt.get("label")
        body = candidate_bodies.get(label)
        if not body:
            continue
        key = _normalize_body_for_dedup(body)
        if key in seen_bodies:
            continue
        seen_bodies.add(key)
        selected.append((label, body))
        if len(selected) >= limit:
            break
    return selected


# ---------------------------------------------------------------------------
# Acceptance capture
# ---------------------------------------------------------------------------

def extract_installed_function(source_text: str, function: str) -> str | None:
    header = re.compile(rf"^[^\n;{{}}]*\b{re.escape(function)}\s*\([^;{{}}]*\)\s*\{{", re.M)
    match = header.search(source_text)
    if match is None:
        return None
    depth = 0
    index = match.end() - 1
    while index < len(source_text):
        if source_text[index] == "{":
            depth += 1
        elif source_text[index] == "}":
            depth -= 1
            if depth == 0:
                return source_text[match.start(): index + 1].strip() + "\n"
        index += 1
    return None


def _find_batch_candidate_body(batch: dict, function: str, label: str | None) -> str | None:
    """Look up ``label``'s exact ``body`` among ``batch["candidates"]``.

    Matches on ``label`` (and ``function``, as a sanity check) so the body
    returned is the VERBATIM text that was actually probed -- a candidate's
    body may itself contain several helper function definitions (e.g. a
    ``<owner>_padding`` companion) that a regex re-extraction of the
    installed source would truncate to just the first one. Returns ``None``
    when ``label`` is missing or no candidate matches it.
    """
    if not label:
        return None
    for candidate in batch.get("candidates") or []:
        if candidate.get("label") == label and candidate.get("function") == function:
            body = candidate.get("body")
            return body if isinstance(body, str) and body else None
    return None


def capture_accepted(
    repo_dir: Path,
    out_dir: Path,
    owner: str,
    function: str,
    batch: dict,
    accepted_attempt: dict,
    *,
    source_rel_fallback: str,
    logger: Logger,
) -> None:
    """Record the accepted candidate under ``<out_dir>/accepted/<function>.json``.

    The body stored is the VERBATIM text from ``batch["candidates"]`` (looked
    up by the accepted attempt's ``label``) whenever that lookup succeeds --
    this is the exact text ``fleet_probe.py`` already link-verified, so a
    later host re-gate (``tools/container_merge.py``) probes the identical
    candidate rather than a re-derived approximation of it. Only when the
    label can't be found in the batch (should not normally happen) does this
    fall back to regex-extracting the installed function from the source
    file -- which returns only the FIRST function definition, so a candidate
    body with padding helpers or other companion definitions after the main
    function would be silently truncated. ``captured_from`` in the written
    JSON records which path was taken.
    """
    source_rel = batch.get("source") or source_rel_fallback
    label = accepted_attempt.get("label")

    body = _find_batch_candidate_body(batch, function, label)
    captured_from = "batch"
    if body is None:
        captured_from = "source"
        logger.log(
            f"{owner}: WARNING accepted label {label!r} not found in batch candidates for "
            f"{function}; falling back to source extraction (may truncate a multi-function body)"
        )
        source_path = repo_dir / source_rel
        try:
            source_text = source_path.read_text(encoding="utf-8", errors="replace")
        except OSError as exc:
            logger.log(f"{owner}: WARNING could not read {source_rel} after acceptance: {exc}")
            source_text = ""
        body = extract_installed_function(source_text, function) if source_text else None
        if body is None:
            logger.log(f"{owner}: WARNING could not extract installed body for {function} from {source_rel}")
            body = ""

    accepted_batch = {
        "source": source_rel,
        "declarations": batch.get("declarations") or "",
        "companion_edits": batch.get("companion_edits") or [],
        "candidates": [{
            "function": function,
            "label": label or "accepted",
            "body": body,
        }],
        "label": label or "accepted",
        "captured_from": captured_from,
        "probe_result": {
            "similarity": accepted_attempt.get("similarity_score"),
            "raw": accepted_attempt.get("raw_similarity_score"),
            "link_verified": accepted_attempt.get("link_verified"),
        },
    }
    accepted_dir = out_dir / "accepted"
    save_json(accepted_dir / f"{function}.json", accepted_batch)

    try:
        diff = subprocess.run(
            ["git", "diff", "--", source_rel],
            cwd=repo_dir, capture_output=True, text=True, timeout=30.0,
        )
        (accepted_dir / f"{function}.patch").write_text(diff.stdout, encoding="utf-8")
    except (subprocess.TimeoutExpired, OSError) as exc:
        logger.log(f"{owner}: WARNING git diff for {function} failed: {exc}")


# ---------------------------------------------------------------------------
# One iteration: run the probe on a batch, record state, react to the result
# ---------------------------------------------------------------------------

def run_iteration(
    *,
    repo_dir: Path,
    out_dir: Path,
    source_rel: str,
    owner: str,
    iteration: int,
    batch: dict,
    batch_path: Path,
    owner_state: dict,
    deadline: float,
    permuter_seconds: float,
    logger: Logger,
    permuter_jobs: list | None = None,
    permuter_bodies: int = DEFAULT_PERMUTER_BODIES,
) -> str:
    """Probe one batch and update ``owner_state`` in place.

    Returns one of ``"accepted"``, ``"continue"``, ``"budget_expired"``.

    ``permuter_jobs`` (Part D), when given, is the caller's persistent list
    of in-flight ``PermuterJob``s for this owner: a strong near-miss/register
    tie appends a newly-started background job to it rather than blocking
    here. The caller (``process_owner``) polls that list with
    ``poll_permuter_jobs`` at the start of the next iteration's prompt build
    and again after that iteration's probe. Omitting it (``None``) starts a
    job that is simply never polled -- fine for a one-shot caller (test mode)
    that has nowhere to feed a later seed anyway.
    """
    if permuter_jobs is None:
        permuter_jobs = []
    result_path = out_dir / "results" / f"{owner}_iter{iteration}.json"
    result_path.parent.mkdir(parents=True, exist_ok=True)

    filtered_batch, dropped = filter_batch(batch, owner_state)
    for entry in dropped:
        logger.log(f"{owner}: iter {iteration}: dropping candidate {entry['label']!r} ({entry['reason']})")
    if dropped:
        batch = filtered_batch
        save_json(batch_path, batch)

    # Declaration hygiene: a generator often repeats a same-file callee's
    # prototype in "declarations" even though the source already declares
    # or defines it. Drop those statements before probing (see
    # filter_declarations) -- a nested extern inside a candidate's own body
    # is left for the runner to report.
    try:
        source_text = (repo_dir / (batch.get("source") or source_rel)).read_text(
            encoding="utf-8", errors="replace"
        )
    except OSError:
        source_text = None
    if source_text is not None:
        decl_filtered_batch, dropped_declarations, declaration_conflicts = filter_declarations(
            batch, source_text
        )
        for statement in dropped_declarations:
            logger.log(
                f"{owner}: iter {iteration}: dropping already-declared statement: {statement!r}"
            )
        for conflict in declaration_conflicts:
            if conflict["companion_edit"]:
                logger.log(
                    f"{owner}: iter {iteration}: TYPE CONFLICT: file declares "
                    f"{conflict['file_signature']}; batch declares {conflict['batch_signature']} "
                    "(companion edit created)"
                )
            else:
                logger.log(
                    f"{owner}: iter {iteration}: WARNING TYPE CONFLICT: file declares "
                    f"{conflict['file_signature']}; batch declares {conflict['batch_signature']} "
                    f"({conflict['name']} is a GLOBAL_ASM owner in this file; keeping batch "
                    "declaration in place, no companion edit)"
                )
        if declaration_conflicts:
            owner_state.setdefault("type_conflicts", []).extend(declaration_conflicts)
        if dropped_declarations or declaration_conflicts:
            batch = decl_filtered_batch
            save_json(batch_path, batch)

    # The most recent iteration's shared declarations -- an approximation
    # (batches often keep the same file-level declarations across a run)
    # used by record_tie_pool to seed a --mode permuter-only pass later,
    # since a best_candidates entry only ever carries its own "body".
    owner_state["last_declarations"] = batch.get("declarations") or ""

    if not (batch.get("candidates") or []):
        logger.log(f"{owner}: iter {iteration}: no candidates remain after dedup filtering; skipping probe")
        owner_state["plateau_count"] = owner_state.get("plateau_count", 0) + 1
        return "continue"

    if stop_requested():
        logger.log(f"{owner}: iter {iteration}: termination requested; skipping probe")
        return "terminated"

    remaining_budget = max(1.0, deadline - time.monotonic())
    probe_timeout = max(10.0, min(PROBE_TIMEOUT_CAP, remaining_budget))
    try:
        probe_proc = invoke_probe(repo_dir, batch_path, result_path, timeout=probe_timeout)
    except subprocess.TimeoutExpired:
        logger.log(f"{owner}: iter {iteration}: probe timed out after {probe_timeout:.0f}s")
        owner_state["plateau_count"] += 1
        return "continue"
    except OSError as exc:
        logger.log(f"{owner}: iter {iteration}: probe failed to launch: {exc}")
        owner_state["plateau_count"] += 1
        return "continue"

    if stop_requested():
        # The probe may have been killed mid-flight by the termination
        # handler (see _run_bounded/_terminate_active_bounded_process): its
        # returncode/output here reflect that kill, not a real probe
        # failure, so this must never count as a plateau/generator-failure
        # signal -- go straight to the run's normal finalize path instead.
        logger.log(f"{owner}: iter {iteration}: termination requested during probe; stopping")
        return "terminated"

    if probe_proc.returncode == 2 and "preflight failed" in (probe_proc.stderr or "").lower():
        indices = _parse_preflight_indices(probe_proc.stderr)
        if indices:
            logger.log(
                f"{owner}: iter {iteration}: preflight failed on candidates {indices}; "
                "dropping them and retrying the probe once"
            )
            index_set = set(indices)
            remaining_candidates = [
                c for i, c in enumerate(batch.get("candidates") or []) if i not in index_set
            ]
            batch = dict(batch)
            batch["candidates"] = remaining_candidates
            save_json(batch_path, batch)
            if not remaining_candidates:
                logger.log(f"{owner}: iter {iteration}: no candidates remain after preflight retry filtering")
                owner_state["plateau_count"] = owner_state.get("plateau_count", 0) + 1
                return "continue"
            if stop_requested():
                logger.log(f"{owner}: iter {iteration}: termination requested; skipping probe retry")
                return "terminated"
            remaining_budget = max(1.0, deadline - time.monotonic())
            probe_timeout = max(10.0, min(PROBE_TIMEOUT_CAP, remaining_budget))
            try:
                probe_proc = invoke_probe(repo_dir, batch_path, result_path, timeout=probe_timeout)
            except subprocess.TimeoutExpired:
                logger.log(f"{owner}: iter {iteration}: probe retry timed out after {probe_timeout:.0f}s")
                owner_state["plateau_count"] += 1
                return "continue"
            except OSError as exc:
                logger.log(f"{owner}: iter {iteration}: probe retry failed to launch: {exc}")
                owner_state["plateau_count"] += 1
                return "continue"
            if stop_requested():
                logger.log(f"{owner}: iter {iteration}: termination requested during probe retry; stopping")
                return "terminated"

    result = load_json(result_path)
    if result is None:
        logger.log(
            f"{owner}: iter {iteration}: probe produced no result JSON "
            f"(exit={probe_proc.returncode}): {probe_proc.stderr.strip()[:500]}"
        )
        owner_state["plateau_count"] += 1
        return "continue"

    # The probe ran (on whatever survived filtering/retry): every one of
    # these bodies has now had its one shot this run, whatever its verdict.
    _record_tried_bodies(batch, owner_state)

    attempts = result.get("attempts") or []
    scored = [a for a in attempts if isinstance(a.get("similarity_score"), (int, float))]
    iteration_best = max(scored, key=attempt_rank) if scored else None

    owner_state["history"].append({
        "iteration": iteration,
        "timestamp": now_iso(),
        "batch_status": result.get("batch_status"),
        "accepted": result.get("accepted") or [],
        "attempts": [
            {
                "label": a.get("label"),
                "function": a.get("function"),
                "status": a.get("status"),
                "similarity_score": a.get("similarity_score"),
                "raw_similarity_score": a.get("raw_similarity_score"),
                "mismatch_kind": a.get("mismatch_kind"),
                "futility": a.get("futility"),
                "link_verified": a.get("link_verified"),
                "diagnostic": ((a.get("diagnostic") or "")[:500]) or None,
            }
            for a in attempts
        ],
    })
    logger.log(
        f"{owner}: iter {iteration}: {len(attempts)} attempt(s) "
        f"best_similarity={iteration_best.get('similarity_score') if iteration_best else None} "
        f"accepted={result.get('accepted')}"
    )

    accepted_functions = result.get("accepted") or []
    if accepted_functions:
        for function in accepted_functions:
            accepted_attempt = next(
                (a for a in attempts if a.get("function") == function and a.get("status") == "accepted"),
                {},
            )
            capture_accepted(
                repo_dir, out_dir, owner, function, batch, accepted_attempt,
                source_rel_fallback=source_rel, logger=logger,
            )
        owner_state["best_similarity"] = 1.0
        owner_state["best_effective_similarity"] = 1.0
        owner_state["best_raw_similarity"] = 1.0
        owner_state["plateau_count"] = 0
        logger.log(f"{owner}: ACCEPTED ({', '.join(accepted_functions)})")
        return "accepted"

    # Keep a small pool of the best-scoring bodies/diagnostics for the next prompt.
    candidate_bodies = {c.get("label"): c.get("body") for c in batch.get("candidates", [])}
    for attempt in scored:
        label = attempt.get("label")
        body = candidate_bodies.get(label)
        if body is None:
            continue
        owner_state["best_candidates"].append({
            "label": label,
            "similarity_score": attempt.get("similarity_score"),
            "raw_similarity_score": attempt.get("raw_similarity_score"),
            "mismatch_kind": attempt.get("mismatch_kind"),
            "futility": attempt.get("futility"),
            "diagnostic": ((attempt.get("diagnostic") or "")[:500]) or None,
            "body": body,
            "normalized_only": _is_normalized_only_match(attempt),
            "feedback": _build_feedback(attempt),
        })
    owner_state["best_candidates"].sort(key=attempt_rank, reverse=True)
    seen_labels: set[str] = set()
    deduped: list[dict] = []
    for entry in owner_state["best_candidates"]:
        if entry["label"] in seen_labels:
            continue
        seen_labels.add(entry["label"])
        deduped.append(entry)
    owner_state["best_candidates"] = deduped[:BEST_CANDIDATES_KEPT]

    previous_effective = owner_state.get("best_effective_similarity") or 0.0
    previous_raw = owner_state.get("best_raw_similarity") or 0.0
    current_effective, current_raw = attempt_rank(iteration_best) if iteration_best else (0.0, 0.0)
    # A normalized-only match never advances "best" tracking -- not even to
    # its own capped effective value -- so a later genuine near-miss is
    # always free to register as an improvement over whatever came before it.
    is_improvement = (
        iteration_best is not None
        and not _is_normalized_only_match(iteration_best)
        and (
            current_effective > previous_effective + 1e-9
            or (
                abs(current_effective - previous_effective) <= 1e-9
                and current_raw > previous_raw + 1e-9
            )
        )
    )
    if is_improvement:
        owner_state["best_effective_similarity"] = current_effective
        owner_state["best_similarity"] = iteration_best.get("similarity_score") or 0.0
        owner_state["best_raw_similarity"] = iteration_best.get("raw_similarity_score")
        owner_state["best_label"] = iteration_best.get("label")
        owner_state["plateau_count"] = 0
    else:
        owner_state["plateau_count"] = owner_state.get("plateau_count", 0) + 1

    # A strong near-miss or a runner-reported register tie is worth a permuter pass.
    # A normalized-only match never triggers it, no matter how close its
    # capped effective similarity gets to the threshold. The bar is 0.95,
    # lowered to 0.90 when the shape is likely to yield to a random-restart
    # search rather than more hand variants: operand_or_scheduling_drift, or
    # a register-allocation tie whose raw score already trails its
    # normalized one by a wide margin (the docs/REGISTER_TIES.md tell,
    # short of the stricter >=0.99/register-tie-futility case below, which
    # always triggers regardless of the bar).
    if iteration_best is not None and permuter_seconds > 0 and time.monotonic() < deadline:
        futility = str(iteration_best.get("futility") or "")
        is_register_tie = futility.startswith("register-tie")
        effective_similarity, raw_similarity = attempt_rank(iteration_best)
        is_normalized_only = _is_normalized_only_match(iteration_best)
        mismatch_kind = str(iteration_best.get("mismatch_kind") or "")
        is_register_only_tie = (
            mismatch_kind == "register_allocation_only"
            and effective_similarity - raw_similarity >= REGISTER_TIE_RAW_GAP
        )
        threshold = (
            PERMUTER_LOWERED_TRIGGER
            if mismatch_kind == "operand_or_scheduling_drift" or is_register_only_tie
            else PERMUTER_TRIGGER
        )
        if not is_normalized_only and (effective_similarity >= threshold or is_register_tie):
            bodies = _select_permuter_bodies(scored, candidate_bodies, limit=permuter_bodies)
            if bodies:
                budget = min(permuter_seconds, max(0.0, deadline - time.monotonic()))
                if stop_requested():
                    logger.log(
                        f"{owner}: iter {iteration}: termination requested; not launching a permuter job"
                    )
                elif budget >= 10.0:
                    job = start_permuter_job(
                        repo_dir, out_dir, owner, iteration, bodies, batch.get("declarations"),
                        permuter_seconds=budget, logger=logger,
                    )
                    permuter_jobs.append(job)
                    logger.log(
                        f"{owner}: iter {iteration}: started background permuter job "
                        f"(threshold={threshold}) on {len(bodies)} body/bodies: "
                        f"{[label for label, _ in bodies]}"
                    )

    if time.monotonic() >= deadline:
        return "budget_expired"
    return "continue"


# ---------------------------------------------------------------------------
# Tie pool: an owner that plateaus with a register-allocation tie or a
# normalized-only best (raw well below the near-perfect normalized score --
# see _is_normalized_only_match/docs/REGISTER_TIES.md) is not a source-shape
# gap a generator is likely to close by writing more C; it is exactly what
# --mode permuter-only (below) is for. record_tie_pool is called once an
# owner's status has actually settled to "plateau" (main()'s owner loop) and
# writes a cumulative <out>/tie-pool.json a later permuter-only pass (this
# run's own --tie-pool-file, or another run's) reads back.
# ---------------------------------------------------------------------------

def _best_is_tie(entry: dict | None) -> bool:
    """Whether a ``best_candidates``-shaped ``entry`` (the owner's own top
    entry, already best-first) is a register-allocation tie worth handing to
    the permuter: a normalized-only match (``normalized_only`` -- similarity
    score near-1.0, raw similarity well below 0.95, see
    ``_is_normalized_only_match``) or a runner-reported register-tie
    futility (``futility`` starting with ``"register-tie"``, the same check
    ``run_iteration``'s own permuter trigger uses)."""
    if not entry:
        return False
    if entry.get("normalized_only"):
        return True
    return str(entry.get("futility") or "").startswith("register-tie")


def record_tie_pool(out_dir: Path, owner: str, source_rel: str, owner_state: dict, *, logger: Logger) -> None:
    """When ``owner``'s best plateaued attempt is a tie (``_best_is_tie``),
    mark ``owner_state["tie_pool"] = True`` and append its best body/
    declarations/raw/label to a cumulative ``<out_dir>/tie-pool.json``
    (``{owner: {source, body, declarations, raw, label}}``) -- a later
    ``--mode permuter-only`` pass's ``--tie-pool-file`` input. A no-op (and
    ``tie_pool`` left at its default ``False``) when the owner's best is not
    a tie, or it has no best_candidates entry at all (e.g. every batch this
    run failed to generate)."""
    best = (owner_state.get("best_candidates") or [None])[0]
    if not _best_is_tie(best) or not best.get("body"):
        return
    owner_state["tie_pool"] = True
    entry = {
        "source": source_rel,
        "body": best.get("body"),
        "declarations": owner_state.get("last_declarations") or "",
        "raw": best.get("raw_similarity_score"),
        "label": best.get("label"),
    }
    path = out_dir / "tie-pool.json"
    pool = load_json(path)
    if not isinstance(pool, dict):
        pool = {}
    pool[owner] = entry
    save_json(path, pool)
    logger.log(f"{owner}: recorded to tie-pool.json (raw={entry['raw']}, label={entry['label']})")


# ---------------------------------------------------------------------------
# Region notes: a short, dated line appended to
# <out_dir>/region-notes/<source path, "/" -> "__">.md on every accept and
# every plateau -- in the exact section format tools/region_notes.py's own
# append() produces (see that tool's docstring) -- so a later host-side step
# (tools/container_merge.py) can fold it into docs/regions/<source_rel>.md
# verbatim. Written under --out, never into the tracked docs/regions/ tree
# directly: a container's checkout has no business editing that tree itself
# (AGENTS.md's shared-checkout rules are a host-only concern).
# ---------------------------------------------------------------------------

def _region_note_section(text: str) -> str:
    """Mirror ``tools/region_notes.py``'s ``append()`` section format: a
    dated ``## YYYY-MM-DD`` heading followed by the note text."""
    date = datetime.now(timezone.utc).date().isoformat()
    return f"## {date}\n\n{text.strip()}\n"


def append_region_note(out_dir: Path, source_rel: str, text: str) -> Path:
    """Append ``text`` as one dated section to
    ``<out_dir>/region-notes/<source_rel, "/" -> "__">.md``, creating it
    with the same header ``tools/region_notes.py``'s own ``append()`` writes
    for a brand-new file. Never rewrites existing content -- always adds
    after it, exactly like the host-side tool."""
    path = out_dir / "region-notes" / (source_rel.replace("/", "__") + ".md")
    path.parent.mkdir(parents=True, exist_ok=True)
    section = _region_note_section(text)
    if not path.exists():
        header = (
            f"# Region notes -- {source_rel}\n\n"
            "Per-file spellings, skip lists, and unsolved shapes for this "
            "source file. Delivered to agents by `tools/file_brief.py`; "
            "extend it with `tools/region_notes.py append`.\n\n"
        )
        path.write_text(header + section, encoding="utf-8")
    else:
        with path.open("a", encoding="utf-8") as handle:
            handle.write("\n" + section)
    return path


def _read_accepted_label(out_dir: Path, owner: str) -> str | None:
    data = load_json(out_dir / "accepted" / f"{owner}.json")
    if isinstance(data, dict):
        label = data.get("label")
        if isinstance(label, str) and label:
            return label
    return None


def _type_conflict_note_lines(owner_state: dict) -> list[str]:
    """One line per companion-edit TYPE CONFLICT recorded this run (see
    ``filter_declarations``/``run_iteration``): ``"<callee> is <new sig>,
    not <old sig>"``. A conflict where the name was itself a still-pragma
    owner (no companion edit made -- see ``filter_declarations``) is not
    included; there is nothing to hand the host a retype for."""
    lines = []
    for conflict in owner_state.get("type_conflicts") or []:
        if not conflict.get("companion_edit"):
            continue
        lines.append(
            f"TYPE CONFLICT: {conflict.get('name')} is {conflict.get('batch_signature')}, "
            f"not {conflict.get('file_signature')}"
        )
    return lines


def _accept_region_note_text(owner: str, out_dir: Path, owner_state: dict) -> str:
    label = _read_accepted_label(out_dir, owner) or owner_state.get("best_label") or "accepted"
    agent = os.environ.get("AGENT", "unknown")
    lines = [f"{owner}: matched ({label}), {owner_state.get('iterations', 0)} iterations, agent {agent}"]
    lines.extend(_type_conflict_note_lines(owner_state))
    return "\n".join(lines)


def _plateau_region_note_text(owner: str, owner_state: dict) -> str:
    best = owner_state.get("best_similarity")
    raw = owner_state.get("best_raw_similarity")
    top = (owner_state.get("best_candidates") or [None])[0] or {}
    kind = top.get("mismatch_kind") or "unknown"
    families = sorted({
        (label.split(":", 1)[0] if ":" in label else label)
        for label in owner_state.get("tried_labels") or []
    })
    tie_pool = "tie-pool yes" if owner_state.get("tie_pool") else "tie-pool no"
    lines = [
        f"{owner}: plateau at {best} (raw {raw}), mismatch {kind}; "
        f"tried families: {', '.join(families) if families else '(none)'}; {tie_pool}"
    ]
    lines.extend(_type_conflict_note_lines(owner_state))
    return "\n".join(lines)


def _time_cap_region_note_text(owner: str, owner_state: dict) -> str:
    """Like ``_plateau_region_note_text``, but for an owner that hit
    ``--owner-seconds`` rather than genuinely plateauing on similarity --
    worth a distinct lead-in so a later pass knows this owner may still have
    headroom, it just ran out of this run's per-owner wall-clock budget."""
    best = owner_state.get("best_similarity")
    raw = owner_state.get("best_raw_similarity")
    elapsed = owner_state.get("elapsed_seconds") or 0.0
    top = (owner_state.get("best_candidates") or [None])[0] or {}
    kind = top.get("mismatch_kind") or "unknown"
    families = sorted({
        (label.split(":", 1)[0] if ":" in label else label)
        for label in owner_state.get("tried_labels") or []
    })
    tie_pool = "tie-pool yes" if owner_state.get("tie_pool") else "tie-pool no"
    lines = [
        f"{owner}: time cap at {best} (raw {raw}) after {elapsed:.0f}s, mismatch {kind}; "
        f"tried families: {', '.join(families) if families else '(none)'}; {tie_pool}"
    ]
    lines.extend(_type_conflict_note_lines(owner_state))
    return "\n".join(lines)


def record_region_note(
    out_dir: Path, source_rel: str, owner: str, owner_state: dict, *, status: str, logger: Logger,
) -> None:
    """Append a region note for an owner that just ended in ``"accepted"``,
    ``"plateau"``, or ``"time_cap"`` this run (see
    ``_accept_region_note_text``/``_plateau_region_note_text``/
    ``_time_cap_region_note_text``); a no-op for any other terminal status
    (``budget_expired``, ``max_iterations``, ``generator_failed``, ...) --
    those are run/box bookkeeping, not durable knowledge about the file."""
    if status == "accepted":
        text = _accept_region_note_text(owner, out_dir, owner_state)
    elif status == "plateau":
        text = _plateau_region_note_text(owner, owner_state)
    elif status == "time_cap":
        text = _time_cap_region_note_text(owner, owner_state)
    else:
        return
    path = append_region_note(out_dir, source_rel, text)
    logger.log(f"{owner}: region note appended to {path}")


# ---------------------------------------------------------------------------
# Per-owner loop: generate -> probe -> react, until a terminal state
# ---------------------------------------------------------------------------

def process_owner(
    *,
    repo_dir: Path,
    out_dir: Path,
    source_rel: str,
    owner: str,
    owner_state: dict,
    state: dict,
    state_path: Path,
    deadline: float,
    max_iterations: int,
    plateau: int,
    permuter_seconds: float,
    generator_cmd: str,
    logger: Logger,
    gen_failures: dict | None = None,
    max_generator_failures: int = 3,
    generator_timeout: float = DEFAULT_GENERATOR_TIMEOUT,
    permuter_bodies: int = DEFAULT_PERMUTER_BODIES,
    probe_tool: bool = True,
    summary: dict | None = None,
    examples_count: int = DEFAULT_EXAMPLES,
    owner_seconds: float = DEFAULT_OWNER_SECONDS,
) -> str:
    if gen_failures is None:
        gen_failures = {"consecutive": 0}
    file_brief = file_brief_text(repo_dir, source_rel)
    asm_text = owner_asm_text(repo_dir, owner)
    m2c_draft = get_m2c_draft(repo_dir, owner, owner_state, logger=logger)
    examples = collect_family_examples(
        repo_dir, owner, source_rel, owner_state, count=examples_count, logger=logger,
    )
    # In-flight background permuter jobs (Part D), local to this owner's
    # loop: started right after a triggering probe result, polled at the
    # start of the next iteration's prompt build and again after that
    # iteration's probe, never blocking the generate/probe cycle in between.
    permuter_jobs: list[PermuterJob] = []

    def _record_iteration_progress() -> None:
        if summary is not None:
            summary["iteration_counts"][owner] = owner_state["iterations"]
            summary["best_per_owner"][owner] = owner_state["best_similarity"]

    while owner_state["iterations"] < max_iterations:
        if time.monotonic() >= deadline:
            owner_state["status"] = "budget_expired"
            return "budget_expired"
        if stop_requested():
            logger.log(f"{owner}: termination requested; stopping before the next iteration")
            owner_state["status"] = "terminated"
            return "terminated"

        iteration = owner_state["iterations"]

        # --owner-seconds: a safe point (no generator/probe/permuter call is
        # in flight) to check this owner's total wall-clock spend before
        # starting another generator call. Checked before marking the timer
        # started, so an owner resumed with elapsed_seconds already at or
        # past the cap ends immediately, without a wasted generator call.
        owner_elapsed = _owner_elapsed_seconds(owner_state)
        if owner_elapsed >= owner_seconds:
            logger.log(
                f"{owner}: iter {iteration}: owner-seconds cap reached "
                f"({owner_elapsed:.0f}s >= {owner_seconds:.0f}s); ending owner as time_cap "
                "before starting another generator call"
            )
            _owner_freeze_elapsed(owner_state)
            owner_state["status"] = "time_cap"
            return "time_cap"
        _owner_mark_started(owner_state)

        poll_permuter_jobs(permuter_jobs, owner_state, logger=logger)

        batch_path = out_dir / "batches" / f"{owner}_iter{iteration}.json"
        prompt_path = out_dir / "prompts" / f"{owner}_iter{iteration}.txt"
        batch_path.parent.mkdir(parents=True, exist_ok=True)
        prompt_path.parent.mkdir(parents=True, exist_ok=True)

        # Computed before build_prompt so the prompt's "time budget" line
        # reflects the timeout that will actually bound this iteration's
        # invoke_generator call below (the configured --generator-timeout
        # clamped by whatever's left of the run's overall deadline, and by
        # whatever's left of this owner's --owner-seconds budget).
        remaining_budget = max(1.0, deadline - time.monotonic())
        remaining_owner_budget = max(1.0, owner_seconds - _owner_elapsed_seconds(owner_state))
        gen_timeout = max(10.0, min(generator_timeout, remaining_budget, remaining_owner_budget))
        if remaining_owner_budget < generator_timeout and remaining_owner_budget <= remaining_budget:
            logger.log(
                f"{owner}: iter {iteration}: generator timeout shrunk to {gen_timeout:.0f}s "
                f"({remaining_owner_budget:.0f}s left of --owner-seconds {owner_seconds:.0f}s)"
            )

        prompt_text = build_prompt(
            owner=owner, source_rel=source_rel, file_brief=file_brief, asm_text=asm_text,
            best_candidates=owner_state["best_candidates"],
            permuter_seed=owner_state.get("permuter_seed"), batch_path=batch_path,
            tried_labels=owner_state.get("tried_labels"), m2c_draft=m2c_draft, examples=examples,
            probe_tool=probe_tool, type_conflicts=owner_state.get("type_conflicts"),
            generator_timeout_minutes=max(1, round(gen_timeout / 60.0)),
        )
        prompt_path.write_text(prompt_text, encoding="utf-8")

        if stop_requested():
            logger.log(f"{owner}: iter {iteration}: termination requested; skipping generator call")
            owner_state["status"] = "terminated"
            return "terminated"

        command = render_generator_command(generator_cmd, prompt_path, batch_path)
        timed_out = False
        timeout_stderr = ""
        try:
            gen_result = invoke_generator(command, cwd=repo_dir, timeout=gen_timeout)
        except subprocess.TimeoutExpired as exc:
            logger.log(f"{owner}: iter {iteration}: generator timed out after {gen_timeout:.0f}s")
            gen_result = None
            timed_out = True
            timeout_stderr = _decode(getattr(exc, "stderr", None))
        except OSError as exc:
            logger.log(f"{owner}: iter {iteration}: generator failed to launch: {exc}")
            owner_state["status"] = "generator_failed"
            # A launch failure never produced a real exit code, so quota
            # classification (which only applies to a non-zero exit) does
            # not apply here.
            exhausted = _record_generator_outcome(
                gen_failures, ok=False, quota=False, stderr_tail=str(exc),
                owner=owner, iteration=iteration, max_failures=max_generator_failures, logger=logger,
            )
            if exhausted:
                logger.log(
                    f"{owner}: generator exhausted after {gen_failures['consecutive']} consecutive "
                    f"failure(s) (limit {max_generator_failures}); stopping run"
                )
                owner_state["status"] = "generator_failed"
                return "generator_exhausted"
            return "generator_failed"

        if stop_requested():
            # The generator may have been killed mid-flight by the
            # termination handler (see _run_bounded/
            # _terminate_active_bounded_process): its exit status/output
            # here reflect that kill, not a real generator failure, so this
            # must never count against max-generator-failures -- go
            # straight to the run's normal finalize path instead.
            logger.log(f"{owner}: iter {iteration}: termination requested during generator call; stopping")
            owner_state["status"] = "terminated"
            return "terminated"

        if gen_result is not None and gen_result.returncode != 0:
            logger.log(
                f"{owner}: iter {iteration}: generator exited {gen_result.returncode}: "
                f"{(gen_result.stderr or '').strip()[:500]}"
            )

        batch = load_json(batch_path)
        timeout_candidate_count = _owner_candidate_count(batch, owner) if timed_out else 0
        timeout_with_batch = timed_out and timeout_candidate_count >= 1
        if timeout_with_batch:
            logger.log(
                f"{owner}: iter {iteration}: generator timed out but left a batch with "
                f"{timeout_candidate_count} candidate(s); probing it"
            )
        gen_ok = timeout_with_batch or (
            (not timed_out) and gen_result is not None and gen_result.returncode == 0 and batch is not None
        )
        if not gen_ok:
            if batch is None:
                logger.log(f"{owner}: iter {iteration}: no valid batch JSON at {batch_path}")
            # Quota/rate-limit classification only applies to a generator
            # that actually exited non-zero, and only inspects stderr: a
            # timeout's captured output is the model's own (possibly
            # truncated) reasoning text, and an exit-0-but-no-batch failure
            # has no non-zero exit to attribute to a quota signal at all.
            # Either case matching a quota phrase by accident must not
            # double-count a plain timeout or missing-batch failure.
            if timed_out:
                quota = False
                stderr_tail = timeout_stderr
            elif gen_result is not None and gen_result.returncode != 0:
                stderr_text = gen_result.stderr or ""
                quota = _looks_like_quota(stderr_text)
                stderr_tail = stderr_text
            else:
                quota = False
                stderr_tail = (gen_result.stderr or "") if gen_result is not None else ""
            exhausted = _record_generator_outcome(
                gen_failures, ok=False, quota=quota, stderr_tail=stderr_tail,
                owner=owner, iteration=iteration, max_failures=max_generator_failures, logger=logger,
            )
            owner_state["iterations"] += 1
            owner_state["plateau_count"] += 1
            _record_iteration_progress()
            _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir, summary=summary)
            if exhausted:
                logger.log(
                    f"{owner}: generator exhausted after {gen_failures['consecutive']} consecutive "
                    f"failure(s) (limit {max_generator_failures}); stopping run"
                )
                owner_state["status"] = "generator_failed"
                return "generator_exhausted"
            if owner_state["plateau_count"] >= plateau:
                owner_state["status"] = "plateau"
                return "plateau"
            continue

        _record_generator_outcome(
            gen_failures, ok=True, quota=False, stderr_tail="",
            owner=owner, iteration=iteration, max_failures=max_generator_failures, logger=logger,
        )

        status = run_iteration(
            repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
            iteration=iteration, batch=batch, batch_path=batch_path, owner_state=owner_state,
            deadline=deadline, permuter_seconds=permuter_seconds, logger=logger,
            permuter_jobs=permuter_jobs, permuter_bodies=permuter_bodies,
        )
        owner_state["iterations"] += 1
        poll_permuter_jobs(permuter_jobs, owner_state, logger=logger)
        _record_iteration_progress()
        _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir, summary=summary)

        if status == "accepted":
            owner_state["status"] = "accepted"
            return "accepted"
        if status == "terminated":
            owner_state["status"] = "terminated"
            return "terminated"
        if status == "budget_expired":
            owner_state["status"] = "budget_expired"
            return "budget_expired"
        if owner_state["plateau_count"] >= plateau:
            owner_state["status"] = "plateau"
            return "plateau"

    owner_state["status"] = "max_iterations"
    return "max_iterations"


# ---------------------------------------------------------------------------
# --mode permuter-only: skip the generator entirely and run the permuter
# straight off whatever best body an owner already has in state (imported
# via --seed-from and/or --tie-pool-file below). Meant to run overnight over
# a tie pool a normal run's plateaus already flagged (docs/REGISTER_TIES.md:
# "coordinators run the permuter overnight ... instead of looping agents
# through the same class of diff") -- there is no next generator call to
# overlap with here, so (unlike Part D's background jobs) this runs the
# permuter in the foreground, one body at a time.
# ---------------------------------------------------------------------------

DEFAULT_PERMUTER_ONLY_SECONDS = 1200.0


def load_tie_pool_file(path: Path) -> dict:
    """Load a ``--tie-pool-file`` (the same shape ``record_tie_pool`` writes
    to ``<out>/tie-pool.json``: ``{owner: {source, body, declarations, raw,
    label}}``). ``{}`` for a missing/unreadable/wrong-shaped file."""
    data = load_json(path)
    return data if isinstance(data, dict) else {}


def seed_state_from_tie_pool(state: dict, tie_pool: dict, *, logger: Logger) -> None:
    """Merge a ``--tie-pool-file``'s entries into ``state`` as a seed
    ``best_candidates`` entry for ``--mode permuter-only``, for any owner
    ``--seed-from`` did not already supply a (presumably better-tracked)
    ``best_candidates`` pool for. Mutates ``state`` in place."""
    for owner, entry in tie_pool.items():
        if not isinstance(entry, dict):
            continue
        body = entry.get("body")
        if not body:
            continue
        owner_state = state.setdefault(owner, _new_owner_state())
        if owner_state.get("best_candidates"):
            continue
        owner_state["best_candidates"] = [{
            "label": entry.get("label") or "tie-pool",
            "similarity_score": None,
            "raw_similarity_score": entry.get("raw"),
            "mismatch_kind": None,
            "futility": None,
            "diagnostic": "seeded from --tie-pool-file",
            "body": body,
            "normalized_only": False,
            "feedback": {},
        }]
        if entry.get("declarations"):
            owner_state["last_declarations"] = entry["declarations"]
        logger.log(f"{owner}: seeded permuter-only body from tie-pool file (raw={entry.get('raw')})")


def _permuter_only_seed_bodies(owner_state: dict, *, limit: int) -> list[tuple[str, str]]:
    """Up to ``limit`` distinct ``(label, body)`` pairs from
    ``owner_state["best_candidates"]`` (already best-first), the material a
    ``--mode permuter-only`` pass runs the permuter on."""
    selected: list[tuple[str, str]] = []
    seen: set[str] = set()
    for entry in owner_state.get("best_candidates") or []:
        body = entry.get("body")
        if not body:
            continue
        key = _normalize_body_for_dedup(body)
        if key in seen:
            continue
        seen.add(key)
        selected.append((entry.get("label") or "seed", body))
        if len(selected) >= limit:
            break
    return selected


def process_owner_permuter_only(
    *,
    repo_dir: Path,
    out_dir: Path,
    source_rel: str,
    owner: str,
    owner_state: dict,
    state: dict,
    state_path: Path,
    deadline: float,
    permuter_seconds: float,
    permuter_bodies: int,
    logger: Logger,
    summary: dict | None = None,
    owner_seconds: float = DEFAULT_OWNER_SECONDS,
) -> str:
    """One owner's pass under ``--mode permuter-only``: never calls the
    generator. Takes up to ``permuter_bodies`` distinct seed bodies from
    ``owner_state["best_candidates"]`` (``_permuter_only_seed_bodies`` --
    populated by ``--seed-from`` and/or ``seed_state_from_tie_pool``) and
    runs the permuter on each in turn. The first output with score 0 is
    probed as a one-candidate batch (label ``"permuter:zero"``) through
    ``run_iteration`` -- the same probe/gate path a normal run uses, so an
    actual accept writes ``accepted/<owner>.json`` exactly as it always
    does. When no body produced a score-0 output, the lowest-scoring output
    across every body tried is recorded as a new (unprobed)
    ``best_candidates[0]`` entry -- the seed a *later* permuter-only pass
    over this same ``--out`` (or a fresh one seeded from it) starts closer
    from -- and this owner is done for the pass.

    Returns ``"accepted"``, ``"plateau"`` (ran but did not gate, or nothing
    to try), ``"time_cap"`` (--owner-seconds reached before a body could be
    started), ``"budget_expired"``, or ``"terminated"``.
    """
    if time.monotonic() >= deadline:
        owner_state["status"] = "budget_expired"
        return "budget_expired"
    if stop_requested():
        owner_state["status"] = "terminated"
        return "terminated"
    # --owner-seconds: an owner resumed with elapsed_seconds already at or
    # past the cap (e.g. a --mode full run that already spent its budget on
    # this owner) is done before even picking a seed body.
    owner_elapsed = _owner_elapsed_seconds(owner_state)
    if owner_elapsed >= owner_seconds:
        logger.log(
            f"{owner}: permuter-only: owner-seconds cap reached "
            f"({owner_elapsed:.0f}s >= {owner_seconds:.0f}s); ending owner as time_cap"
        )
        _owner_freeze_elapsed(owner_state)
        owner_state["status"] = "time_cap"
        return "time_cap"

    bodies = _permuter_only_seed_bodies(owner_state, limit=max(1, permuter_bodies))
    if not bodies:
        logger.log(
            f"{owner}: permuter-only: no seed body in best_candidates (--seed-from/"
            "--tie-pool-file supplied nothing for this owner); skipping"
        )
        owner_state["status"] = "plateau"
        return "plateau"

    declarations = owner_state.get("last_declarations") or ""
    best_output: dict | None = None
    zero_output: dict | None = None
    tried = 0
    for index, (label, body) in enumerate(bodies):
        if stop_requested():
            owner_state["status"] = "terminated"
            return "terminated"
        # Re-checked per body (not just once above): a safe point, since no
        # permuter job is in flight here yet, and this run may already have
        # spent several bodies' worth of time on this owner by the time we
        # reach a later one.
        owner_elapsed = _owner_elapsed_seconds(owner_state)
        if owner_elapsed >= owner_seconds:
            logger.log(
                f"{owner}: permuter-only: owner-seconds cap reached "
                f"({owner_elapsed:.0f}s >= {owner_seconds:.0f}s) before body {index + 1}/"
                f"{len(bodies)}; ending owner as time_cap"
            )
            _owner_freeze_elapsed(owner_state)
            owner_state["status"] = "time_cap"
            return "time_cap"
        _owner_mark_started(owner_state)
        remaining = deadline - time.monotonic()
        if remaining < 10.0:
            owner_state["status"] = "budget_expired"
            return "budget_expired"
        remaining_owner = max(0.0, owner_seconds - owner_elapsed)
        budget = min(permuter_seconds, remaining, remaining_owner)
        logger.log(
            f"{owner}: permuter-only: running permuter on body {index + 1}/{len(bodies)} "
            f"(label={label}, budget={budget:.0f}s)"
        )
        result = run_permuter(
            repo_dir, out_dir, owner, owner_state.get("iterations", 0), body, declarations,
            permuter_seconds=budget, logger=logger, label_suffix=f"_po{index}",
        )
        tried += 1
        if result is None:
            continue
        for output in result.get("outputs") or []:
            if best_output is None or output["score"] < best_output["score"]:
                best_output = output
            if output["score"] == 0 and zero_output is None:
                zero_output = output
        if zero_output is not None:
            logger.log(f"{owner}: permuter-only: body {index + 1} produced a score-0 output; probing it")
            break

    if zero_output is not None:
        batch = {
            "source": source_rel,
            "declarations": declarations,
            "candidates": [{"function": owner, "label": "permuter:zero", "body": zero_output["code"]}],
        }
        iteration = owner_state.get("iterations", 0)
        batch_path = out_dir / "batches" / f"{owner}_permuter_only_iter{iteration}.json"
        save_json(batch_path, batch)
        status = run_iteration(
            repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
            iteration=iteration, batch=batch, batch_path=batch_path, owner_state=owner_state,
            deadline=deadline, permuter_seconds=0.0, logger=logger,
        )
        owner_state["iterations"] = iteration + 1
        if summary is not None:
            summary["iteration_counts"][owner] = owner_state["iterations"]
            summary["best_per_owner"][owner] = owner_state["best_similarity"]
        _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir, summary=summary)
        if status == "accepted":
            owner_state["status"] = "accepted"
            logger.log(f"{owner}: permuter-only: ACCEPTED via permuter:zero")
            return "accepted"
        if status == "terminated":
            owner_state["status"] = "terminated"
            return "terminated"
        if status == "budget_expired":
            owner_state["status"] = "budget_expired"
            return "budget_expired"
        logger.log(f"{owner}: permuter-only: permuter:zero candidate did not gate (status={status})")
        owner_state["status"] = "plateau"
        return "plateau"

    if best_output is not None:
        logger.log(
            f"{owner}: permuter-only: no score-0 output across {tried} body/bodies tried; "
            f"recording best output (score={best_output['score']}) as the new seed body"
        )
        owner_state.setdefault("best_candidates", []).insert(0, {
            "label": "permuter-only:best",
            "similarity_score": None,
            "raw_similarity_score": None,
            "mismatch_kind": None,
            "futility": None,
            "diagnostic": f"permuter-only best output, score={best_output['score']} (not probed)",
            "body": best_output["code"],
            "normalized_only": False,
            "feedback": {},
        })
        owner_state["best_candidates"] = owner_state["best_candidates"][:BEST_CANDIDATES_KEPT]
    else:
        logger.log(f"{owner}: permuter-only: permuter produced no outputs for any of {tried} body/bodies tried")

    owner_state["status"] = "plateau"
    _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir, summary=summary)
    return "plateau"


# ---------------------------------------------------------------------------
# --seed-from: seed a FRESH run's owner_state from one or more earlier
# --out dirs' state.json (this run's own past attempts, or another run's --
# e.g. a different generator/model against the same file). Only ever used
# before an owner's first iteration: status/iterations/plateau_count/history
# are never imported, so a seeded owner still looks exactly like a normal
# pending owner to process_owner/main -- it just starts with a warm
# best_candidates pool, tried-body/label memory, an m2c draft, and a
# permuter seed already in hand, so the very first prompt built for it shows
# those seeded bodies (with their diagnostics) instead of a blank slate.
# Ignored entirely under --resume (see main()): a resumed owner already has
# its own real state, which must never be clobbered by an older run's.
# ---------------------------------------------------------------------------

def _load_seed_state(seed_dir: Path) -> dict:
    state = load_json(seed_dir / "state.json")
    return state if isinstance(state, dict) else {}


def _load_seed_accepted_body(seed_dir: Path, owner: str) -> str | None:
    """The exact installed body ``capture_accepted`` wrote for ``owner`` in
    ``seed_dir`` (``accepted/<owner>.json``'s first candidate), or ``None``
    when that file is missing/unreadable -- an owner marked ``accepted`` in
    ``state.json`` without a matching ``accepted/<owner>.json`` (e.g. a
    hand-built fixture) has nothing to import for the accept itself, though
    it is still recorded loudly (see ``seed_owner_states``)."""
    payload = load_json(seed_dir / "accepted" / f"{owner}.json")
    if not isinstance(payload, dict):
        return None
    candidates = payload.get("candidates")
    if isinstance(candidates, list) and candidates:
        first = candidates[0]
        if isinstance(first, dict):
            body = first.get("body")
            if isinstance(body, str) and body:
                return body
    return None


def _merge_seed_candidates(
    per_source_candidates: list[tuple[str, list[dict]]], *, cap: int,
) -> list[dict]:
    """Merge each source's (already best-first) ``best_candidates`` list into
    one ranked, deduped-by-body pool, capped at ``cap`` -- but always keeping
    at least the single best entry from every contributing source, even past
    the cap, so one source's five near-misses can never fully crowd out
    another source's one good lead.
    """
    seen_bodies: set[str] = set()
    ranked: list[dict] = []
    best_per_source: dict[str, dict] = {}
    for source_label, candidates in per_source_candidates:
        for entry in candidates:
            body = entry.get("body")
            if not body:
                continue
            key = _normalize_body_for_dedup(body)
            if key in seen_bodies:
                continue
            seen_bodies.add(key)
            tagged = dict(entry)
            tagged["seed_source"] = source_label
            ranked.append(tagged)
            best_per_source.setdefault(source_label, tagged)
    ranked.sort(key=attempt_rank, reverse=True)
    kept = ranked[:cap]
    kept_bodies = {_normalize_body_for_dedup(entry.get("body")) for entry in kept}
    for best in best_per_source.values():
        if _normalize_body_for_dedup(best.get("body")) not in kept_bodies:
            kept.append(best)
            kept_bodies.add(_normalize_body_for_dedup(best.get("body")))
    kept.sort(key=attempt_rank, reverse=True)
    return kept


def seed_owner_states(seed_dirs: list[Path], *, logger: Logger) -> dict[str, dict]:
    """Build fresh ``owner_state`` dicts seeded from ``seed_dirs``' own
    ``state.json`` files, keyed by owner.

    Owner names are unique function symbols, not scoped to any one source
    file, so every owner mentioned by any seed dir's ``state.json`` is
    considered -- this does not need (and does not take) the current run's
    own discovered owner list. Only owners with something to import are
    returned; each returned ``owner_state`` starts from ``_new_owner_state()``
    (status ``in_progress``, ``iterations`` 0, empty ``history``) with
    ``best_candidates``/``tried_bodies``/``tried_labels``/``m2c_draft``/
    ``permuter_seed`` merged in from every seed dir that had that owner, plus
    ``seeded_from`` (the contributing seed dir paths) and
    ``seed_best_similarity`` (the best similarity among what was imported, or
    ``None`` if nothing scored). Tolerates older schemas missing
    ``tried_bodies``/``tried_labels``/``feedback``/``normalized_only`` --
    every field is read with ``.get`` and a safe default.
    """
    seed_states = [(str(seed_dir), _load_seed_state(seed_dir)) for seed_dir in seed_dirs]

    owners: list[str] = []
    seen_owners: set[str] = set()
    for _, state in seed_states:
        for owner in state:
            if owner not in seen_owners:
                seen_owners.add(owner)
                owners.append(owner)

    result: dict[str, dict] = {}
    for owner in owners:
        per_source_candidates: list[tuple[str, list[dict]]] = []
        contributing_dirs: list[str] = []
        tried_bodies: set[str] = set()
        tried_labels: list[str] = []
        seen_tried_labels: set[str] = set()
        m2c_draft: str | None = None
        permuter_seed: dict | None = None

        for source_label, state in seed_states:
            entry = state.get(owner)
            if not isinstance(entry, dict) or not entry:
                continue
            contributing_dirs.append(source_label)

            candidates = [c for c in (entry.get("best_candidates") or []) if isinstance(c, dict)]
            candidates.sort(key=attempt_rank, reverse=True)

            if entry.get("status") == "accepted":
                seed_dir = Path(source_label)
                accepted_body = _load_seed_accepted_body(seed_dir, owner)
                logger.log(
                    f"{owner}: seed dir {source_label} already has this owner ACCEPTED -- "
                    "importing its body as a candidate (similarity 1.0); the host merge "
                    "decides whether it actually lands"
                )
                if accepted_body:
                    candidates = [{
                        "label": f"seeded-accepted:{seed_dir.name}",
                        "body": accepted_body,
                        "similarity_score": 1.0,
                        "raw_similarity_score": 1.0,
                        "mismatch_kind": None,
                        "futility": None,
                        "diagnostic": None,
                        "normalized_only": False,
                        "feedback": {},
                    }] + candidates
                else:
                    logger.log(
                        f"{owner}: WARNING seed dir {source_label} marks this owner accepted "
                        f"but has no readable accepted/{owner}.json -- nothing to import for "
                        "the accept itself"
                    )
            if candidates:
                per_source_candidates.append((source_label, candidates))

            for key in entry.get("tried_bodies") or []:
                if isinstance(key, str):
                    tried_bodies.add(key)
            for label in entry.get("tried_labels") or []:
                if isinstance(label, str) and label not in seen_tried_labels:
                    seen_tried_labels.add(label)
                    tried_labels.append(label)

            if m2c_draft is None:
                draft = entry.get("m2c_draft")
                if isinstance(draft, str) and draft:
                    m2c_draft = draft

            seed = entry.get("permuter_seed")
            if isinstance(seed, dict) and isinstance(seed.get("score"), (int, float)):
                if permuter_seed is None or seed["score"] < permuter_seed["score"]:
                    permuter_seed = seed

        if not contributing_dirs:
            continue

        merged = _merge_seed_candidates(per_source_candidates, cap=BEST_CANDIDATES_KEPT)

        owner_state = _new_owner_state()
        owner_state["best_candidates"] = merged
        owner_state["tried_bodies"] = sorted(tried_bodies)
        owner_state["tried_labels"] = tried_labels
        if m2c_draft is not None:
            owner_state["m2c_draft"] = m2c_draft
            owner_state["m2c_draft_fetched"] = True
        if permuter_seed is not None:
            owner_state["permuter_seed"] = permuter_seed
        owner_state["seeded_from"] = contributing_dirs

        if merged:
            best_entry = max(merged, key=attempt_rank)
            best_similarity = best_entry.get("similarity_score")
            best_source = best_entry.get("seed_source") or contributing_dirs[0]
            owner_state["seed_best_similarity"] = best_similarity
            logger.log(
                f"{owner}: seeded {len(merged)} candidate(s), best {best_similarity} "
                f"from {best_source}"
            )
        else:
            owner_state["seed_best_similarity"] = None
            logger.log(
                f"{owner}: seeded 0 candidates (tried-bodies/labels only) from {contributing_dirs}"
            )

        result[owner] = owner_state
    return result


# ---------------------------------------------------------------------------
# Test mode: exercise the loop once with a fixed batch, no generator
# ---------------------------------------------------------------------------

def run_test_mode(
    *,
    repo_dir: Path,
    out_dir: Path,
    source_rel: str,
    candidate_file: Path,
    state: dict,
    state_path: Path,
    summary: dict,
    started: float,
    logger: Logger,
) -> int:
    batch = load_json(candidate_file)
    if batch is None:
        logger.log(f"error: could not read candidate file {candidate_file}")
        _finalize_run(summary, out_dir, "invalid_candidate_file", started, repo_dir=repo_dir)
        return 2

    functions = []
    for candidate in batch.get("candidates", []):
        function = candidate.get("function")
        if function and function not in functions:
            functions.append(function)
    owner = functions[0] if functions else None
    if owner is None:
        logger.log(f"error: {candidate_file} has no candidates with a function name")
        _finalize_run(summary, out_dir, "invalid_candidate_file", started, repo_dir=repo_dir)
        return 2

    batch_source = batch.get("source") or source_rel
    logger.log(f"test mode: using {candidate_file} for owner {owner} (source={batch_source})")
    summary["owners_attempted"].append(owner)
    owner_state = state.setdefault(owner, _new_owner_state())

    batch_path = out_dir / "batches" / f"{owner}_iter0.json"
    save_json(batch_path, batch)

    status = run_iteration(
        repo_dir=repo_dir, out_dir=out_dir, source_rel=batch_source, owner=owner, iteration=0,
        batch=batch, batch_path=batch_path, owner_state=owner_state,
        deadline=time.monotonic() + 3600.0, permuter_seconds=0.0, logger=logger,
    )
    owner_state["iterations"] = 1
    owner_state["status"] = "accepted" if status == "accepted" else "test_mode_done"
    summary["iteration_counts"][owner] = owner_state["iterations"]
    summary["best_per_owner"][owner] = owner_state["best_similarity"]
    if status == "accepted":
        summary["matched"].append(owner)
    _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir, summary=summary)
    _finalize_run(summary, out_dir, "test_mode_exit", started, repo_dir=repo_dir)
    logger.log(f"test mode complete: status={status}")
    return 0


# ---------------------------------------------------------------------------
# CLI / main loop
# ---------------------------------------------------------------------------

def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--source", required=True, help="repo-relative source path, e.g. disasm/src/X.c")
    parser.add_argument("--out", required=True, type=Path, help="output directory for state/logs/accepted candidates")
    parser.add_argument("--repo", type=Path, default=REPO_ROOT_DEFAULT, help="repo root (default: parent of tools/)")
    parser.add_argument("--budget-seconds", type=float, default=7200.0)
    parser.add_argument("--max-iterations", type=int, default=200)
    parser.add_argument(
        "--plateau", type=int, default=6,
        help="stop an owner after N consecutive iterations with no best-similarity improvement",
    )
    parser.add_argument(
        "--owner-seconds", type=float, default=DEFAULT_OWNER_SECONDS,
        help=(
            "per-owner wall-clock cap in seconds (default: 2400), measured from the owner's "
            "first generator call (--mode full) or first permuter job (--mode permuter-only) "
            "in this run; time already spent on the owner in an earlier --resume run counts "
            "too (state.json's elapsed_seconds). An agentic generator that explores via "
            "tools/probe_one.py before converging can make one iteration take 12-17 minutes "
            "-- long enough that --plateau alone is too slow a stop. Checked only at safe "
            "points (before starting a new generator call or permuter job; a running probe "
            "or permuter job is never cut). Exceeding it ends the owner with status "
            "'time_cap', recorded exactly like a plateau (region note, tie-pool check, best "
            "candidates kept for seeding), and the run moves on to the next owner. "
            "--generator-timeout is also shrunk by whatever's left of this budget, alongside "
            "the run's overall --budget-seconds."
        ),
    )
    parser.add_argument(
        "--permuter-seconds", type=float, default=None,
        help=(
            "default: 300 in --mode full, 1200 in --mode permuter-only (a foreground pass "
            "over a tie pool warrants a longer budget than a background job squeezed "
            "between generator calls)"
        ),
    )
    parser.add_argument(
        "--permuter-bodies", type=int, default=DEFAULT_PERMUTER_BODIES,
        help="on a trigger (--mode full) or every owner (--mode permuter-only), run the "
             "permuter on up to this many distinct bodies (default: 3)",
    )
    parser.add_argument(
        "--examples", type=int, default=DEFAULT_EXAMPLES,
        help=(
            "up to this many already-matched functions of the active owner's family, "
            "rendered as worked examples in the prompt (see collect_family_examples); "
            "0 disables the feature entirely (default: 3)"
        ),
    )
    parser.add_argument(
        "--mode", choices=["full", "permuter-only"], default="full",
        help=(
            "'full' (default): the normal generate/probe/permuter loop. "
            "'permuter-only': never calls the generator -- for each owner, runs the "
            "permuter directly on its best known body (from --seed-from and/or "
            "--tie-pool-file) and probes a score-0 output through the normal gate path; "
            "meant for an overnight pass over a tie pool a prior --mode full run flagged "
            "(docs/REGISTER_TIES.md)"
        ),
    )
    parser.add_argument(
        "--tie-pool-file", type=Path,
        help=(
            "in --mode permuter-only, a JSON file shaped like tie-pool.json "
            "({owner: {source, body, declarations, raw, label}}, see record_tie_pool) to "
            "seed owners' best_candidates from, for any owner --seed-from did not already "
            "supply a pool for"
        ),
    )
    parser.add_argument("--owners", help="comma-separated subset/order of owners to work (default: all, discovered)")
    parser.add_argument(
        "--owner-order", choices=["size", "file"], default="size",
        help="discovery order for owners when --owners is not given: smallest-instructions-"
             "first (default) or the order they appear in the source",
    )
    parser.add_argument(
        "--max-instructions", type=int, default=None,
        help="skip discovered owners with more instructions than this (default: unlimited); "
             "ignored when --owners is given explicitly",
    )
    parser.add_argument(
        "--generator-cmd",
        help='shell command template; "{prompt}" and "{batch}" are substituted with absolute paths',
    )
    parser.add_argument(
        "--candidate-file", type=Path,
        help="test mode: use this batch once for the first owner instead of any generator, then exit",
    )
    parser.add_argument(
        "--generator-timeout", type=float, default=DEFAULT_GENERATOR_TIMEOUT,
        help=(
            "cap in seconds on a single generator invocation; the run's remaining "
            "budget still bounds it further (default: 1800, raised from 600 now "
            "that an agentic generator is expected to spend time iterating with "
            "tools/probe_one.py -- see --probe-tool). Kimi K3 at high effort "
            "can exceed 10 minutes for one batch on its own -- raise this further "
            "rather than letting it time out."
        ),
    )
    parser.add_argument(
        "--max-generator-failures", type=int, default=3,
        help=(
            "stop the whole run after this many consecutive generator failures "
            "(non-zero exit, timeout, or no valid batch JSON); a quota/rate-limit-looking "
            "failure counts double (default: 3)"
        ),
    )
    parser.add_argument(
        "--probe-tool", choices=["on", "off"], default=None,
        help=(
            "toggle the BATCH_CONTRACT paragraph telling an agentic generator it "
            "may/should call tools/probe_one.py to iterate on drafts before "
            "writing the batch (see PROBE_TOOL_RULE_ON/OFF). Default: the "
            "PROBE_TOOL env var if set, else 'on'. Pass 'off' (or set "
            "PROBE_TOOL=off) for a generator with no tool access, e.g. the "
            "plain-HTTP openai_compat/kimi_api wrappers -- entrypoint.sh already "
            "does this automatically for those two AGENT values."
        ),
    )
    parser.add_argument(
        "--resume", action="store_true",
        help="resume an existing run in --out (its state.json); without this, a non-empty state.json is an error",
    )
    parser.add_argument(
        "--skip-status", default="accepted",
        help="comma-separated owner statuses to skip when resuming (default: accepted)",
    )
    parser.add_argument(
        "--seed-from",
        help=(
            "comma-separated list of earlier --out dirs (from this or another run) to seed a "
            "FRESH run from: per owner, merges best_candidates (ranked, deduped by normalised "
            "body, capped at BEST_CANDIDATES_KEPT but keeping at least the best from each "
            "source), unions tried_bodies/tried_labels, takes the first m2c_draft found and the "
            "best (lowest-score) permuter_seed. status/iterations/history are never imported -- "
            "the owner still starts pending. Ignored (with a log line) when --resume is also "
            "passed, since a resumed owner already has its own real state."
        ),
    )
    return parser.parse_args(argv)


def _resolve_source_rel(repo_dir: Path, source: str) -> str:
    path = Path(source)
    if path.is_absolute():
        try:
            return path.resolve().relative_to(repo_dir).as_posix()
        except ValueError:
            return source
    return source


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    repo_dir = args.repo.resolve()
    out_dir = args.out
    out_dir.mkdir(parents=True, exist_ok=True)
    logger = Logger(out_dir / "log.txt")

    # Graceful termination: a `docker run` attached to a terminal session
    # that ends sends SIGTERM to this process (SIGINT covers a plain
    # Ctrl-C). request_stop sets _STOP_REQUESTED (checked at every safe
    # point below/in process_owner/run_iteration) and terminates whatever
    # generator/probe subprocess is currently blocking the driver, so the
    # run reaches its normal finalize path instead of dying mid-call with
    # summary.json never written.
    termination_handler = functools.partial(request_stop, logger=logger)
    signal.signal(signal.SIGTERM, termination_handler)
    signal.signal(signal.SIGINT, termination_handler)

    source_rel = _resolve_source_rel(repo_dir, args.source)
    # --probe-tool wins when passed explicitly; otherwise fall back to the
    # PROBE_TOOL env var (entrypoint.sh sets it to "off" for the HTTP-only
    # AGENT values), defaulting to "on" when neither is set.
    probe_tool_arg = args.probe_tool or os.environ.get("PROBE_TOOL", "on")
    probe_tool = probe_tool_arg != "off"
    started = time.monotonic()
    deadline = started + args.budget_seconds
    # --permuter-seconds' default depends on --mode (see parse_args): a
    # foreground permuter-only pass over a tie pool warrants a longer budget
    # than a background job squeezed between two generator calls.
    permuter_seconds = (
        args.permuter_seconds if args.permuter_seconds is not None
        else (DEFAULT_PERMUTER_ONLY_SECONDS if args.mode == "permuter-only" else 300.0)
    )

    state_path = out_dir / "state.json"
    summary_path = out_dir / "summary.json"
    existing_state = load_json(state_path)
    if existing_state:
        if not args.resume:
            logger.log(
                f"error: {state_path} already has a run; pass --resume or use a new --out dir"
            )
            return 2
        state = existing_state
    else:
        state = {}

    if args.seed_from:
        if args.resume:
            logger.log("--seed-from ignored: --resume was passed, and a resumed owner keeps its own state")
        else:
            seed_dirs = [Path(item.strip()) for item in args.seed_from.split(",") if item.strip()]
            seeded = seed_owner_states(seed_dirs, logger=logger)
            for owner, owner_state in seeded.items():
                state[owner] = owner_state
            if seeded:
                _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir)

    if args.tie_pool_file:
        tie_pool = load_tie_pool_file(args.tie_pool_file)
        if tie_pool:
            seed_state_from_tie_pool(state, tie_pool, logger=logger)
            _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir)
        else:
            logger.log(f"--tie-pool-file {args.tie_pool_file}: empty or unreadable, nothing seeded")

    prior_summary = load_json(summary_path) if args.resume else None
    runs: list[dict] = list((prior_summary or {}).get("runs") or [])
    generator_desc = args.generator_cmd or (
        f"--candidate-file {args.candidate_file}" if args.candidate_file else None
    )
    runs.append({"started": now_iso(), "ended": None, "generator_cmd": generator_desc, "stop_reason": None})

    summary: dict = {
        "source": source_rel,
        "started_at": now_iso(),
        "budget_seconds": args.budget_seconds,
        "owners_attempted": [],
        "matched": [],
        "best_per_owner": {},
        "iteration_counts": {},
        "stopped_reason": None,
        "runs": runs,
    }
    # Persist the new "runs" entry (and the rest of the summary skeleton)
    # right away, before any generator/probe call: on --resume in
    # particular, this is what leaves a current summary.json in place from
    # the very start of the run rather than only after _finalize_run (or an
    # in-loop _save_state, see below) next writes one.
    save_json(summary_path, summary)

    if args.candidate_file:
        return run_test_mode(
            repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel,
            candidate_file=args.candidate_file, state=state, state_path=state_path,
            summary=summary, started=started, logger=logger,
        )

    if args.mode != "permuter-only" and not args.generator_cmd:
        logger.log("error: --generator-cmd is required (or use --candidate-file for a one-shot test)")
        _finalize_run(summary, out_dir, "no_generator", started, repo_dir=repo_dir)
        return 2

    if args.owners:
        owners = [name.strip() for name in args.owners.split(",") if name.strip()]
    else:
        owners = discover_owners(
            repo_dir, source_rel, owner_order=args.owner_order,
            max_instructions=args.max_instructions, logger=logger,
        )

    logger.log(f"discovered {len(owners)} owner(s) for {source_rel}: {', '.join(owners) or '(none)'}")

    skip_statuses = {s.strip() for s in (args.skip_status or "").split(",") if s.strip()}
    gen_failures = {"consecutive": 0}

    stopped_reason = "completed" if owners else "no_owners"
    for owner in owners:
        if time.monotonic() >= deadline:
            stopped_reason = "budget_expired"
            break
        if stop_requested():
            stopped_reason = "terminated"
            break
        owner_state = state.setdefault(owner, _new_owner_state())
        if owner_state.get("status") in skip_statuses:
            logger.log(f"{owner}: resume: skipping (status={owner_state.get('status')})")
            summary["iteration_counts"][owner] = owner_state["iterations"]
            summary["best_per_owner"][owner] = owner_state["best_similarity"]
            if owner_state.get("status") == "accepted":
                summary["matched"].append(owner)
            continue
        summary["owners_attempted"].append(owner)
        if args.mode == "permuter-only":
            status = process_owner_permuter_only(
                repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                owner_state=owner_state, state=state, state_path=state_path, deadline=deadline,
                permuter_seconds=permuter_seconds, permuter_bodies=args.permuter_bodies,
                logger=logger, summary=summary, owner_seconds=args.owner_seconds,
            )
        else:
            status = process_owner(
                repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
                owner_state=owner_state, state=state, state_path=state_path, deadline=deadline,
                max_iterations=args.max_iterations, plateau=args.plateau,
                permuter_seconds=permuter_seconds, generator_cmd=args.generator_cmd, logger=logger,
                gen_failures=gen_failures, max_generator_failures=args.max_generator_failures,
                generator_timeout=args.generator_timeout, permuter_bodies=args.permuter_bodies,
                probe_tool=probe_tool, summary=summary, examples_count=args.examples,
                owner_seconds=args.owner_seconds,
            )
        # Belt-and-braces: process_owner/process_owner_permuter_only already
        # fold a "time_cap" owner's running timer into elapsed_seconds on
        # that path, but every other terminal status (accepted, plateau,
        # budget_expired, terminated, ...) also ends this run's attempt at
        # the owner -- freeze here unconditionally so a later --resume
        # always adds to a self-contained total regardless of which status
        # actually stopped it.
        _owner_freeze_elapsed(owner_state)
        summary["iteration_counts"][owner] = owner_state["iterations"]
        summary["best_per_owner"][owner] = owner_state["best_similarity"]
        if status == "accepted":
            summary["matched"].append(owner)
        # Tie pool (docs/REGISTER_TIES.md) and region notes (AGENTS.md §2
        # rule 11/§4): both keyed off the owner's actual terminal status
        # this run, not which mode produced it, so a permuter-only pass
        # over a tie pool records/updates the same durable knowledge a full
        # run's plateau does. "time_cap" (--owner-seconds) is recorded the
        # same way as "plateau" -- region note, tie-pool check, best
        # candidates already kept for seeding. Tie pool first: the
        # plateau/time-cap note's own "tie-pool yes/no" line reads
        # owner_state["tie_pool"].
        if status in ("plateau", "time_cap"):
            record_tie_pool(out_dir, owner, source_rel, owner_state, logger=logger)
        if status in ("accepted", "plateau", "time_cap"):
            record_region_note(out_dir, source_rel, owner, owner_state, status=status, logger=logger)
        _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir, summary=summary)
        if status == "budget_expired":
            stopped_reason = "budget_expired"
            break
        if status == "generator_exhausted":
            stopped_reason = "generator_exhausted"
            break
        if status == "terminated":
            stopped_reason = "terminated"
            break

    _finalize_run(summary, out_dir, stopped_reason, started, repo_dir=repo_dir)
    logger.log(f"done: matched={summary['matched']} stopped_reason={stopped_reason}")
    if stopped_reason == "terminated":
        return 143
    return 3 if stopped_reason == "generator_exhausted" else 0


if __name__ == "__main__":
    raise SystemExit(main())
