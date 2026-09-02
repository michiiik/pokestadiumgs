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


def _save_state(state: dict, state_path: Path, *, repo_dir: Path, out_dir: Path) -> None:
    """``save_json(state_path, state)`` plus a probe-stats export snapshot --
    the "every state save" half of the probe-stats export contract (the
    other half is ``_finalize_run``)."""
    save_json(state_path, state)
    export_probe_stats(repo_dir, out_dir)


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
    }


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


def filter_declarations(batch: dict, source_text: str) -> tuple[dict, list[str]]:
    """Drop top-level ``declarations`` statements that redeclare a name the
    source file already declares or defines.

    Returns ``(filtered_batch, dropped_statements)``; ``filtered_batch`` is a
    shallow copy of ``batch`` with a (possibly empty) ``declarations`` string
    when anything was dropped, or ``batch`` unchanged when nothing was.
    """
    statements = _split_declaration_statements(batch.get("declarations") or "")
    if not statements:
        return batch, []
    kept: list[str] = []
    dropped: list[str] = []
    for statement in statements:
        name = _declaration_statement_name(statement)
        if name and _name_declared_in_source(name, source_text):
            dropped.append(statement)
            continue
        kept.append(statement)
    if not dropped:
        return batch, []
    filtered = dict(batch)
    filtered["declarations"] = "\n".join(kept)
    return filtered, dropped


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
  run make, fleet_probe.py, the permuter, or write into disasm/src yourself.
"""

PROBE_TOOL_RULE_OFF = """\
- Do NOT compile, assemble, run make, probes or the permuter yourself: the
  driver probes every candidate against the ROM right after you write the
  file and feeds the diagnostics back. Spend your time on the C, not on
  building a toolchain loop.
"""

BATCH_CONTRACT = """\
Write a JSON batch file to the path given below (create or overwrite it).
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
    probe_tool: bool = True,
) -> str:
    extern_names = _extern_block_symbol_names(file_brief)
    probe_rule = (PROBE_TOOL_RULE_ON if probe_tool else PROBE_TOOL_RULE_OFF).format(
        source_rel=source_rel, owner=owner,
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
        parts.append("")
        parts.append(BATCH_CONTRACT.format(
            source_rel=source_rel, owner=owner, batch_path=batch_path, probe_rule=probe_rule,
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
    """Run the external generator command once. Isolated so tests can stub it."""
    return subprocess.run(
        command, shell=True, cwd=cwd, capture_output=True, text=True, timeout=timeout,
    )


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
    """Run ``tools/fleet_probe.py`` once. Isolated so tests can stub it."""
    return subprocess.run(
        ["python3", "tools/fleet_probe.py", str(batch_path), "--json", str(result_path)],
        cwd=repo_dir, capture_output=True, text=True, timeout=timeout,
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
    try:
        process = invoke_permuter(
            repo_dir, owner, candidate_path, declarations_path,
            seconds=permuter_seconds, log_path=log_path,
        )
    except OSError as exc:
        logger.log(f"{owner}: permuter launch failed: {exc}")
        return None

    result = poll_permuter(repo_dir, owner, process, before, budget_seconds=permuter_seconds + 30.0)
    logger.log(
        f"{owner}: permuter iter {iteration}{label_suffix} finished timed_out={result['timed_out']} "
        f"outputs={len(result['outputs'])} best_score={(result['best'] or {}).get('score')}"
    )
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
        decl_filtered_batch, dropped_declarations = filter_declarations(batch, source_text)
        for statement in dropped_declarations:
            logger.log(
                f"{owner}: iter {iteration}: dropping already-declared statement: {statement!r}"
            )
        if dropped_declarations:
            batch = decl_filtered_batch
            save_json(batch_path, batch)

    if not (batch.get("candidates") or []):
        logger.log(f"{owner}: iter {iteration}: no candidates remain after dedup filtering; skipping probe")
        owner_state["plateau_count"] = owner_state.get("plateau_count", 0) + 1
        return "continue"

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
                if budget >= 10.0:
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
) -> str:
    if gen_failures is None:
        gen_failures = {"consecutive": 0}
    file_brief = file_brief_text(repo_dir, source_rel)
    asm_text = owner_asm_text(repo_dir, owner)
    m2c_draft = get_m2c_draft(repo_dir, owner, owner_state, logger=logger)
    # In-flight background permuter jobs (Part D), local to this owner's
    # loop: started right after a triggering probe result, polled at the
    # start of the next iteration's prompt build and again after that
    # iteration's probe, never blocking the generate/probe cycle in between.
    permuter_jobs: list[PermuterJob] = []

    while owner_state["iterations"] < max_iterations:
        if time.monotonic() >= deadline:
            owner_state["status"] = "budget_expired"
            return "budget_expired"

        poll_permuter_jobs(permuter_jobs, owner_state, logger=logger)

        iteration = owner_state["iterations"]
        batch_path = out_dir / "batches" / f"{owner}_iter{iteration}.json"
        prompt_path = out_dir / "prompts" / f"{owner}_iter{iteration}.txt"
        batch_path.parent.mkdir(parents=True, exist_ok=True)
        prompt_path.parent.mkdir(parents=True, exist_ok=True)

        prompt_text = build_prompt(
            owner=owner, source_rel=source_rel, file_brief=file_brief, asm_text=asm_text,
            best_candidates=owner_state["best_candidates"],
            permuter_seed=owner_state.get("permuter_seed"), batch_path=batch_path,
            tried_labels=owner_state.get("tried_labels"), m2c_draft=m2c_draft,
            probe_tool=probe_tool,
        )
        prompt_path.write_text(prompt_text, encoding="utf-8")

        remaining_budget = max(1.0, deadline - time.monotonic())
        gen_timeout = max(10.0, min(generator_timeout, remaining_budget))
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

        if gen_result is not None and gen_result.returncode != 0:
            logger.log(
                f"{owner}: iter {iteration}: generator exited {gen_result.returncode}: "
                f"{(gen_result.stderr or '').strip()[:500]}"
            )

        batch = load_json(batch_path)
        gen_ok = (not timed_out) and gen_result is not None and gen_result.returncode == 0 and batch is not None
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
            _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir)
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
        _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir)

        if status == "accepted":
            owner_state["status"] = "accepted"
            return "accepted"
        if status == "budget_expired":
            owner_state["status"] = "budget_expired"
            return "budget_expired"
        if owner_state["plateau_count"] >= plateau:
            owner_state["status"] = "plateau"
            return "plateau"

    owner_state["status"] = "max_iterations"
    return "max_iterations"


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
    _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir)

    summary["iteration_counts"][owner] = owner_state["iterations"]
    summary["best_per_owner"][owner] = owner_state["best_similarity"]
    if status == "accepted":
        summary["matched"].append(owner)
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
    parser.add_argument("--permuter-seconds", type=float, default=300.0)
    parser.add_argument(
        "--permuter-bodies", type=int, default=DEFAULT_PERMUTER_BODIES,
        help="on a trigger, run the permuter on up to this many distinct bodies from that "
             "iteration, each its own background process (default: 3)",
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

    source_rel = _resolve_source_rel(repo_dir, args.source)
    # --probe-tool wins when passed explicitly; otherwise fall back to the
    # PROBE_TOOL env var (entrypoint.sh sets it to "off" for the HTTP-only
    # AGENT values), defaulting to "on" when neither is set.
    probe_tool_arg = args.probe_tool or os.environ.get("PROBE_TOOL", "on")
    probe_tool = probe_tool_arg != "off"
    started = time.monotonic()
    deadline = started + args.budget_seconds

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

    if args.candidate_file:
        return run_test_mode(
            repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel,
            candidate_file=args.candidate_file, state=state, state_path=state_path,
            summary=summary, started=started, logger=logger,
        )

    if not args.generator_cmd:
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
        owner_state = state.setdefault(owner, _new_owner_state())
        if owner_state.get("status") in skip_statuses:
            logger.log(f"{owner}: resume: skipping (status={owner_state.get('status')})")
            summary["iteration_counts"][owner] = owner_state["iterations"]
            summary["best_per_owner"][owner] = owner_state["best_similarity"]
            if owner_state.get("status") == "accepted":
                summary["matched"].append(owner)
            continue
        summary["owners_attempted"].append(owner)
        status = process_owner(
            repo_dir=repo_dir, out_dir=out_dir, source_rel=source_rel, owner=owner,
            owner_state=owner_state, state=state, state_path=state_path, deadline=deadline,
            max_iterations=args.max_iterations, plateau=args.plateau,
            permuter_seconds=args.permuter_seconds, generator_cmd=args.generator_cmd, logger=logger,
            gen_failures=gen_failures, max_generator_failures=args.max_generator_failures,
            generator_timeout=args.generator_timeout, permuter_bodies=args.permuter_bodies,
            probe_tool=probe_tool,
        )
        summary["iteration_counts"][owner] = owner_state["iterations"]
        summary["best_per_owner"][owner] = owner_state["best_similarity"]
        if status == "accepted":
            summary["matched"].append(owner)
        _save_state(state, state_path, repo_dir=repo_dir, out_dir=out_dir)
        if status == "budget_expired":
            stopped_reason = "budget_expired"
            break
        if status == "generator_exhausted":
            stopped_reason = "generator_exhausted"
            break

    _finalize_run(summary, out_dir, stopped_reason, started, repo_dir=repo_dir)
    logger.log(f"done: matched={summary['matched']} stopped_reason={stopped_reason}")
    return 3 if stopped_reason == "generator_exhausted" else 0


if __name__ == "__main__":
    raise SystemExit(main())
