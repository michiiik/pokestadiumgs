#!/usr/bin/env python3
"""Host-side merge step for the containerised per-file agent (issue #39).

The container (see ``docs/CONTAINER_AGENT.md``) never commits. It writes its
results to a mounted output directory:

    <out>/state.json               owner -> {best_similarity, iterations,
                                              history[], status}
    <out>/accepted/<owner>.json    a fleet_probe batch JSON with a single
                                    accepted candidate plus declarations /
                                    companion_edits
    <out>/accepted/<owner>.patch
    <out>/log.txt
    <out>/summary.json             owners attempted, matched, best per
                                    owner, iteration counts, wall time
    <out>/probe-stats/probe-stats.jsonl
                                    a copy of the probe-stats history the
                                    container's own runner wrote during the
                                    run (see "import-stats" below)

This script is the "separate, deliberate step" the issue asks for: it never
trusts the container's own verdict. For each ``<out>/accepted/<owner>.json``
it re-runs the real oracle -- ``tools/fleet_probe.py <json> --gate`` -- against
*this* checkout, and only a candidate the host itself just gated is eligible
to be committed. A container that ran against a stale or tampered tree cannot
talk its way past this.

``merge`` itself writes back into ``<out>``:

    <out>/merge-results/<owner>.json
                                    the raw fleet_probe --gate --json result
                                    for each owner, kept (not deleted) so a
                                    failed re-gate can be inspected
    <out>/merge-report.json        owner -> status, plus cc_check_bypassed
                                    and fresh_history flags for this run
    <out>/merge-history.jsonl      only with --fresh-history: this run's own
                                    probe-stats history (see --fresh-history
                                    below)

Two flags work around problems seen on the first real merge (see the
"merge" section of ``docs/CONTAINER_AGENT.md`` for the full story):

* ``--no-cc-check`` sets ``PRAGMA_GATE_CC_CHECK=0`` for the re-gate, so an
  unrelated file failing the host's clang syntax check cannot make every
  re-gate report ``compare_rejected`` regardless of the candidate. Loud by
  design: prints a warning and records ``cc_check_bypassed: true`` in
  ``merge-report.json``.
* ``--fresh-history`` points ``PRAGMA_PROBE_STATS`` at a per-run history
  file so a prior host attempt on record can never trip the runner's own
  "already rejected" preflight; a successful accept is then folded into
  the host's real probe-stats history so the provenance pre-commit hook
  still sees it.

Usage:
    python3 tools/container_merge.py merge /abs/out
    python3 tools/container_merge.py merge /abs/out --commit
    python3 tools/container_merge.py merge /abs/out --repo . --dry-run
    python3 tools/container_merge.py merge /abs/out --commit --no-cc-check --fresh-history
    python3 tools/container_merge.py summary /abs/out
    python3 tools/container_merge.py import-stats /abs/out
    python3 tools/container_merge.py import-stats /abs/out --repo . --dry-run
"""

from __future__ import annotations

import argparse
import dataclasses
import json
import os
import subprocess
import sys
import tempfile
from pathlib import Path

# Environment variables ``.githooks/pre-commit`` exports for its own
# temporary index; inheriting them here would point a subprocess git call at
# the hook's index instead of this checkout's real one (AGENTS.md Sec 1.3,
# and the same stripping tools/integrate_fleet.py does).
_GIT_ENV_POISON = {"GIT_DIR", "GIT_INDEX_FILE", "GIT_WORK_TREE", "GIT_OBJECT_DIRECTORY"}


def _clean_env() -> dict[str, str]:
    return {k: v for k, v in os.environ.items() if k not in _GIT_ENV_POISON}


@dataclasses.dataclass
class MergeRow:
    owner: str
    source: str | None
    function: str
    status: str  # "accepted" | "rejected" | "error"
    detail: str
    committed: bool
    commit_detail: str


def load_accepted_batch(path: Path) -> dict[str, object]:
    """Parse one ``accepted/<owner>.json`` fleet_probe batch file."""
    payload = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(payload, dict):
        raise ValueError("top-level JSON value must be an object")
    return payload


def batch_source(payload: dict[str, object]) -> str | None:
    source = payload.get("source")
    return source if isinstance(source, str) and source else None


def owner_function_name(owner: str, payload: dict[str, object]) -> str:
    """The candidate's owning function, falling back to the file stem."""
    candidates = payload.get("candidates")
    if isinstance(candidates, list) and candidates:
        first = candidates[0]
        if isinstance(first, dict):
            function = first.get("function")
            if isinstance(function, str) and function:
                return function
    return owner


def _first_line(text: str) -> str:
    return text.strip().splitlines()[0] if text and text.strip() else ""


# ---------------------------------------------------------------------------
# The two invocations that leave this process: kept as small, single-purpose
# functions so tests can stub each one independently rather than mocking
# subprocess.run generically.
# ---------------------------------------------------------------------------


def run_fleet_probe_gate(
    batch_path: Path,
    *,
    repo_root: Path,
    python_bin: str = sys.executable,
    timeout: int = 1800,
    extra_env: dict[str, str] | None = None,
    result_path: Path | None = None,
) -> dict[str, object]:
    """Re-gate one accepted-candidate batch against ``repo_root``.

    Runs ``tools/fleet_probe.py <batch_path> --gate --json <result>`` and
    returns ``{"returncode", "result", "stdout", "stderr"}``, where
    ``result`` is the parsed raw runner payload (``{}`` if the subprocess
    never wrote one, e.g. an argument-parsing failure).

    ``extra_env`` is overlaid on a cleaned copy of the current environment
    (see ``_clean_env``) before the subprocess runs -- ``merge --no-cc-check``
    and ``merge --fresh-history`` use it to set ``PRAGMA_GATE_CC_CHECK`` /
    ``PRAGMA_PROBE_STATS`` for this one gate call without touching this
    process's own environment.

    ``result_path`` names where the runner's ``--json`` output should land.
    When given, that file is written and **kept** (its parent directory is
    created if needed) so a failed re-gate can be inspected afterward --
    used by ``merge`` to write ``<out>/merge-results/<owner>.json``. When
    omitted, a throwaway temp file is used and deleted before returning.
    """
    if result_path is not None:
        result_path.parent.mkdir(parents=True, exist_ok=True)
        managed_result_path = result_path
        cleanup = False
    else:
        handle = tempfile.NamedTemporaryFile(
            prefix="container_merge_", suffix=".json", delete=False
        )
        managed_result_path = Path(handle.name)
        handle.close()
        cleanup = True
    env = _clean_env()
    if extra_env:
        env.update(extra_env)
    try:
        proc = subprocess.run(
            [
                python_bin,
                str(repo_root / "tools" / "fleet_probe.py"),
                str(batch_path),
                "--gate",
                "--json",
                str(managed_result_path),
            ],
            cwd=repo_root,
            capture_output=True,
            text=True,
            timeout=timeout,
            env=env,
        )
        result: dict[str, object] = {}
        if managed_result_path.exists() and managed_result_path.stat().st_size:
            try:
                parsed = json.loads(managed_result_path.read_text(encoding="utf-8"))
            except json.JSONDecodeError:
                parsed = None
            if isinstance(parsed, dict):
                result = parsed
        return {
            "returncode": proc.returncode,
            "result": result,
            "stdout": proc.stdout or "",
            "stderr": proc.stderr or "",
        }
    finally:
        if cleanup:
            managed_result_path.unlink(missing_ok=True)


def git_commit_only(source: str, message: str, *, repo_root: Path) -> tuple[bool, str]:
    """``git commit --only <source> -m <message>`` in ``repo_root``.

    AGENTS.md Sec 1.3: the git index is shared by every process in a
    checkout, so a plain ``git add && git commit`` would also commit
    whatever another session has staged. ``--only`` builds a temporary index
    from HEAD plus the named path and leaves everything else untouched.
    """
    proc = subprocess.run(
        ["git", "commit", "--only", source, "-m", message],
        cwd=repo_root,
        capture_output=True,
        text=True,
        env=_clean_env(),
    )
    output = ((proc.stdout or "") + (proc.stderr or "")).strip()
    return proc.returncode == 0, output


# ---------------------------------------------------------------------------
# merge
# ---------------------------------------------------------------------------


def process_owner(
    json_path: Path,
    *,
    repo_root: Path,
    commit: bool,
    dry_run: bool,
    out_dir: Path | None = None,
    extra_env: dict[str, str] | None = None,
) -> MergeRow:
    owner = json_path.stem
    try:
        payload = load_accepted_batch(json_path)
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        return MergeRow(owner, None, owner, "error", f"invalid batch: {exc}", False, "")

    source = batch_source(payload)
    function = owner_function_name(owner, payload)

    result_path = out_dir / "merge-results" / f"{owner}.json" if out_dir is not None else None
    gate = run_fleet_probe_gate(
        json_path, repo_root=repo_root, extra_env=extra_env, result_path=result_path
    )
    result = gate.get("result")
    result = result if isinstance(result, dict) else {}
    accepted_functions = result.get("accepted")
    accepted = isinstance(accepted_functions, list) and function in accepted_functions

    if not accepted:
        batch_status = result.get("batch_status") or f"exit={gate.get('returncode')}"
        detail = f"host re-gate did not accept ({batch_status})"
        stderr_line = _first_line(str(gate.get("stderr") or ""))
        if stderr_line:
            detail += f"; {stderr_line}"
        return MergeRow(owner, source, function, "rejected", detail, False, "")

    if not commit or dry_run:
        return MergeRow(owner, source, function, "accepted", "host re-gate accepted", False, "")

    if not source:
        return MergeRow(
            owner, source, function, "accepted",
            "host re-gate accepted but batch has no 'source' to commit",
            False, "commit skipped: missing source",
        )

    message = f"Land container match for {owner}"
    ok, commit_detail = git_commit_only(source, message, repo_root=repo_root)
    return MergeRow(
        owner, source, function, "accepted", "host re-gate accepted",
        ok, commit_detail or ("committed" if ok else "commit failed"),
    )


COLUMNS = [
    ("OWNER", 22),
    ("SOURCE", 32),
    ("STATUS", 10),
    ("COMMITTED", 9),
    ("DETAIL", 60),
]


def _cell(value: str, width: int) -> str:
    if len(value) > width:
        value = value[: width - 1] + "…"
    return f"{value:<{width}}"


def format_table(rows: list[MergeRow]) -> str:
    header = " ".join(_cell(name, width) for name, width in COLUMNS)
    lines = [header, "-" * len(header)]
    for row in rows:
        detail = row.detail
        if row.commit_detail:
            detail = f"{detail} [{row.commit_detail}]"
        values = [
            row.owner,
            row.source or "-",
            row.status,
            "yes" if row.committed else "no",
            detail,
        ]
        lines.append(" ".join(_cell(v, w) for v, (_, w) in zip(values, COLUMNS)))
    return "\n".join(lines)


def build_gate_env(out_dir: Path, *, no_cc_check: bool, fresh_history: bool) -> dict[str, str]:
    """Extra environment for each owner's ``fleet_probe.py --gate`` call.

    ``--no-cc-check`` -> ``PRAGMA_GATE_CC_CHECK=0``, skipping
    ``disasm/Makefile``'s host clang syntax check (``RUN_CC_CHECK=1
    CC_CHECK_COMP=gcc``, which is clang on macOS) -- see this module's
    module docstring / the "merge" section of ``docs/CONTAINER_AGENT.md``
    for why an unrelated fragment can fail that check for every owner
    regardless of the candidate. This only ever reaches the one
    ``fleet_probe`` subprocess, never this process's own environment.

    ``--fresh-history`` -> ``PRAGMA_PROBE_STATS=<out>/merge-history.jsonl``,
    a history file dedicated to this merge run (created empty here if it
    does not already exist), so the runner's own preflight ("already
    rejected") only ever sees attempts *this run* made, never a prior host
    re-gate recorded in the real, shared probe-stats history.
    """
    env: dict[str, str] = {}
    if no_cc_check:
        env["PRAGMA_GATE_CC_CHECK"] = "0"
    if fresh_history:
        history_path = out_dir / "merge-history.jsonl"
        history_path.parent.mkdir(parents=True, exist_ok=True)
        if not history_path.exists():
            history_path.touch()
        env["PRAGMA_PROBE_STATS"] = str(history_path)
    return env


def write_merge_report(
    out_dir: Path,
    rows: list[MergeRow],
    *,
    no_cc_check: bool,
    fresh_history: bool,
) -> Path:
    """Write ``<out>/merge-report.json``: owner -> status, plus the flags
    that shaped this run. ``cc_check_bypassed: true`` is the durable record
    that every accepted candidate in this run was NOT verified to compile
    cleanly by the host's own clang syntax check -- read this back before
    trusting a ``--no-cc-check`` run's results.
    """
    report_path = out_dir / "merge-report.json"
    payload = {
        "cc_check_bypassed": bool(no_cc_check),
        "fresh_history": bool(fresh_history),
        "owners": {row.owner: row.status for row in rows},
    }
    report_path.write_text(
        json.dumps(payload, indent=2, sort_keys=True) + "\n", encoding="utf-8"
    )
    return report_path


def merge(
    out_dir: Path,
    *,
    repo_root: Path,
    commit: bool,
    dry_run: bool,
    no_cc_check: bool = False,
    fresh_history: bool = False,
) -> int:
    accepted_dir = out_dir / "accepted"
    json_paths = (
        sorted(p for p in accepted_dir.glob("*.json") if p.is_file())
        if accepted_dir.is_dir()
        else []
    )
    if not json_paths:
        print(f"container_merge: no accepted candidates under {accepted_dir}")
        return 0

    if no_cc_check:
        print(
            "container_merge: *** WARNING --no-cc-check: the host clang syntax "
            "check (disasm/Makefile RUN_CC_CHECK) is DISABLED for this re-gate "
            "(PRAGMA_GATE_CC_CHECK=0). Any candidate accepted below was NOT "
            "verified to compile cleanly by the host's own check. ***"
        )

    extra_env = build_gate_env(out_dir, no_cc_check=no_cc_check, fresh_history=fresh_history)

    rows = [
        process_owner(
            path, repo_root=repo_root, commit=commit, dry_run=dry_run,
            out_dir=out_dir, extra_env=extra_env,
        )
        for path in json_paths
    ]

    print(format_table(rows))

    rejected = [row for row in rows if row.status != "accepted"]
    accepted_rows = [row for row in rows if row.status == "accepted"]
    commit_failures = [
        row for row in accepted_rows
        if commit and not dry_run and row.source and not row.committed
    ]

    print()
    print(f"accepted {len(accepted_rows)}/{len(rows)}, rejected {len(rejected)}/{len(rows)}")
    if commit and not dry_run:
        committed = sum(1 for row in rows if row.committed)
        print(f"committed {committed}/{len(accepted_rows)} accepted owner(s)")

    if rejected:
        print(
            f"container_merge: {len(rejected)} container-accepted candidate(s) "
            "failed the host re-gate", file=sys.stderr,
        )
    if commit_failures:
        print(
            f"container_merge: {len(commit_failures)} accepted candidate(s) "
            "failed to commit", file=sys.stderr,
        )

    report_path = write_merge_report(
        out_dir, rows, no_cc_check=no_cc_check, fresh_history=fresh_history
    )
    print()
    print(f"container_merge: wrote {report_path}")

    if fresh_history and accepted_rows:
        status_line = import_fresh_history_after_accept(out_dir, repo_root=repo_root)
        if status_line:
            print(status_line)

    print()
    print(
        "container_merge: reminder: run "
        f"'python3 tools/container_merge.py import-stats {out_dir}' to fold this run's "
        "probe-stats history into the host's"
    )

    return 1 if (rejected or commit_failures) else 0


# ---------------------------------------------------------------------------
# import-stats
#
# The container's runner (tools/fleet_probe.py / tools/try_pragma_compare.py,
# via tools/probe_stats.py) records every attempt it probes into a
# PRAGMA_PROBE_STATS-resolved JSONL history -- inside the container's own
# checkout, so it is lost once the container exits. tools/container_agent.py
# copies it out on every state save (see its own "Probe-stats export"
# section) to <out>/probe-stats/probe-stats.jsonl. This command folds that
# copy into *this* checkout's own history, the same way ``merge`` folds an
# accepted candidate into the tree: a deliberate, host-side step, never
# automatic.
#
# tools/probe_stats.py has no "merge two arbitrary JSONL files" helper (its
# own ``migrate_legacy`` is specific to one fixed legacy path) -- so this is
# a careful line-level append: read the host's current history once, skip
# any source line already present verbatim, and append only the rest. Exact
# duplicate lines are common (probe_stats.append_batch writes semantically
# stable ``json.dumps(row, sort_keys=True)`` rows, and re-running
# import-stats on the same out dir, or importing the same run twice from two
# out dirs, must not double-count).
# ---------------------------------------------------------------------------


def _host_probe_stats_path(repo_root: Path) -> Path | None:
    """Resolve the host's probe-stats file the same way the runner does
    (``tools/probe_stats.py``'s ``stats_path()`` / ``tools/container_agent.py``'s
    ``_probe_stats_source_path``): ``PRAGMA_PROBE_STATS`` if set (``""``
    disables it), else ``<repo_root>/disasm/probe-stats/probe-stats.jsonl``.
    """
    value = os.environ.get("PRAGMA_PROBE_STATS")
    if value == "":
        return None
    if value is not None:
        return Path(os.path.expandvars(value)).expanduser()
    return repo_root / "disasm" / "probe-stats" / "probe-stats.jsonl"


def _line_has_accepted_attempt(line: str) -> bool:
    """Cheap-then-exact check: does this JSONL batch line record at least
    one ``attempts[].status == "accepted"`` entry?

    Mirrors ``tools/check_decomp_provenance.py``'s ``accepted_functions``:
    a substring check before ever parsing, since most lines in a history
    are not an accepted attempt at all.
    """
    if '"accepted"' not in line:
        return False
    try:
        batch = json.loads(line)
    except json.JSONDecodeError:
        return False
    if not isinstance(batch, dict):
        return False
    attempts = batch.get("attempts")
    if not isinstance(attempts, list):
        return False
    return any(
        isinstance(attempt, dict) and attempt.get("status") == "accepted"
        for attempt in attempts
    )


def append_history_lines(
    source_path: Path,
    target_path: Path,
    *,
    dry_run: bool = False,
    only_accepted: bool = False,
) -> tuple[int, int, int]:
    """Fold ``source_path``'s probe-stats JSONL lines into ``target_path``.

    A line already present verbatim in ``target_path`` (or repeated within
    ``source_path`` itself) is skipped -- careful line-level dedupe, not a
    blind concatenation, so re-running this against the same source, or
    against the same target from two different sources, never
    double-counts (``probe_stats.append_batch`` writes semantically stable
    ``json.dumps(row, sort_keys=True)`` rows, so an exact duplicate really
    is the same attempt recorded twice).

    ``only_accepted``, when set, considers only lines with at least one
    accepted attempt (see ``_line_has_accepted_attempt``) -- used to import
    evidence for a successful ``--fresh-history`` re-gate without also
    pulling rejected-attempt noise into the host's real history.

    Returns ``(considered, appended, duplicates)`` -- ``considered`` counts
    only lines that pass the ``only_accepted`` filter (when set).
    ``dry_run`` reports what would change but never touches ``target_path``.
    """
    existing_lines: set[str] = set()
    if target_path.is_file():
        for line in target_path.read_text(encoding="utf-8", errors="replace").splitlines():
            line = line.strip()
            if line:
                existing_lines.add(line)

    considered = 0
    new_lines: list[str] = []
    for line in source_path.read_text(encoding="utf-8", errors="replace").splitlines():
        line = line.strip()
        if not line:
            continue
        if only_accepted and not _line_has_accepted_attempt(line):
            continue
        considered += 1
        if line in existing_lines:
            continue
        new_lines.append(line)
        existing_lines.add(line)  # a duplicate within the source file itself only counts once

    duplicates = considered - len(new_lines)

    if not dry_run and new_lines:
        target_path.parent.mkdir(parents=True, exist_ok=True)
        with target_path.open("a", encoding="utf-8") as handle:
            for line in new_lines:
                handle.write(line + "\n")

    return considered, len(new_lines), duplicates


def import_stats(out_dir: Path, *, repo_root: Path, dry_run: bool) -> int:
    source_path = out_dir / "probe-stats" / "probe-stats.jsonl"
    if not source_path.is_file():
        print(f"container_merge: no probe-stats file at {source_path}; nothing to import")
        return 0

    target_path = _host_probe_stats_path(repo_root)
    if target_path is None:
        print(
            "container_merge: host probe-stats is disabled (PRAGMA_PROBE_STATS=\"\"); "
            "nothing to import"
        )
        return 0

    total, new_count, duplicates = append_history_lines(source_path, target_path, dry_run=dry_run)
    print(
        f"container_merge: {source_path}: {total} line(s), {new_count} new, "
        f"{duplicates} already present in {target_path}"
    )

    if dry_run:
        print("container_merge: --dry-run, not writing")
        return 0
    if new_count == 0:
        return 0

    print(f"container_merge: appended {new_count} line(s) to {target_path}")
    return 0


def import_fresh_history_after_accept(out_dir: Path, *, repo_root: Path) -> str | None:
    """After a ``merge --fresh-history`` run where at least one owner's
    host re-gate accepted, fold that run's ``<out>/merge-history.jsonl``
    accepted line(s) into the host's real probe-stats history, using the
    same dedup-append logic as ``import-stats`` (see ``append_history_lines``).

    The host re-gate for ``--fresh-history`` runs against a dedicated,
    empty-per-run history file rather than the host's real one (so a prior
    host attempt can never trip its preflight), which means the accepted
    attempt this run just proved never lands in the host's real history on
    its own. Without this step, ``tools/check_decomp_provenance.py``'s
    pre-commit hook -- which requires an accepted attempt on record in that
    real history -- would refuse the very commit this merge just earned.

    Returns a human-readable status line, or ``None`` if there was nothing
    to do (no fresh-history file for this run).
    """
    source_path = out_dir / "merge-history.jsonl"
    if not source_path.is_file():
        return None

    target_path = _host_probe_stats_path(repo_root)
    if target_path is None:
        return (
            "container_merge: --fresh-history: host probe-stats is disabled "
            "(PRAGMA_PROBE_STATS=\"\"); not imported"
        )

    total, new_count, duplicates = append_history_lines(
        source_path, target_path, only_accepted=True
    )
    return (
        f"container_merge: --fresh-history: {source_path}: {total} accepted line(s), "
        f"{new_count} new, {duplicates} already present in {target_path}"
    )


# ---------------------------------------------------------------------------
# summary
# ---------------------------------------------------------------------------


def load_json_or_none(path: Path) -> object | None:
    if not path.is_file():
        return None
    try:
        payload = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError):
        return None
    return payload


def _fmt_number(value: object) -> str:
    if isinstance(value, bool):
        return str(value)
    if isinstance(value, (int, float)):
        return f"{value:.4f}" if isinstance(value, float) else str(value)
    return "-" if value is None else str(value)


def format_state(state: object) -> str:
    """``state.json``: owner -> {best_similarity, iterations, history[], status}."""
    if not isinstance(state, dict) or not state:
        return "(empty)"
    columns = [
        ("OWNER", 22), ("STATUS", 12), ("BEST_SIMILARITY", 16),
        ("ITERATIONS", 11), ("HISTORY_LEN", 12),
    ]
    lines = [" ".join(f"{name:<{w}}" for name, w in columns)]
    lines.append("-" * len(lines[0]))
    for owner in sorted(state):
        entry = state[owner]
        entry = entry if isinstance(entry, dict) else {}
        history = entry.get("history")
        row = [
            owner,
            str(entry.get("status", "-")),
            _fmt_number(entry.get("best_similarity")),
            str(entry.get("iterations", "-")),
            str(len(history)) if isinstance(history, list) else "-",
        ]
        lines.append(" ".join(_cell(v, w) for v, (_, w) in zip(row, columns)))
    return "\n".join(lines)


def format_summary(summary: object) -> str:
    """Best-effort readable rendering of ``summary.json``.

    The driver's exact schema (owners attempted, matched, best per owner,
    iteration counts, wall time) lives in ``tools/container_agent.py``, owned
    elsewhere; this stays schema-tolerant rather than pinning field names.
    """
    if not isinstance(summary, dict) or not summary:
        return "(empty)"
    lines: list[str] = []
    scalars = {k: v for k, v in summary.items() if not isinstance(v, (dict, list))}
    if scalars:
        width = max(len(str(k)) for k in scalars) + 1
        for key, value in scalars.items():
            lines.append(f"{(str(key) + ':'):<{width}} {value}")
    for key, value in summary.items():
        if isinstance(value, dict) and value:
            lines.append("")
            lines.append(f"{key}:")
            sub_width = max(len(str(k)) for k in value) + 1
            for sub_key, sub_value in value.items():
                lines.append(f"  {(str(sub_key) + ':'):<{sub_width}} {sub_value}")
        elif isinstance(value, list) and value:
            lines.append("")
            lines.append(f"{key}: [{len(value)} item(s)]")
            for item in value[:20]:
                lines.append(f"  - {item}")
            if len(value) > 20:
                lines.append(f"  ... {len(value) - 20} more")
    return "\n".join(lines) if lines else "(empty)"


def summary_command(out_dir: Path) -> int:
    summary_path = out_dir / "summary.json"
    state_path = out_dir / "state.json"
    summary = load_json_or_none(summary_path)
    state = load_json_or_none(state_path)

    if summary is None and state is None:
        print(
            f"container_merge: neither {summary_path} nor {state_path} "
            "found or parseable", file=sys.stderr,
        )
        return 1

    print(f"=== {summary_path} ===")
    print(format_summary(summary) if summary is not None else "(missing)")
    print()
    print(f"=== {state_path} ===")
    print(format_state(state) if state is not None else "(missing)")
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    sub = parser.add_subparsers(dest="command", required=True)

    p_merge = sub.add_parser(
        "merge", help="re-gate accepted container candidates and optionally commit them"
    )
    p_merge.add_argument(
        "out_dir", type=Path,
        help="container output directory (contains accepted/, state.json, summary.json)",
    )
    p_merge.add_argument(
        "--repo", type=Path, default=Path("."), help="host checkout to re-gate/commit against"
    )
    p_merge.add_argument(
        "--commit", action="store_true",
        help="git commit --only <source> for each owner the host re-gate accepts",
    )
    p_merge.add_argument(
        "--dry-run", action="store_true", help="re-gate only; never commit even with --commit"
    )
    p_merge.add_argument(
        "--no-cc-check", action="store_true",
        help=(
            "set PRAGMA_GATE_CC_CHECK=0 for the re-gate, skipping the host clang "
            "syntax check (disasm/Makefile RUN_CC_CHECK); use only to work around "
            "an unrelated file failing that check. Recorded as "
            "cc_check_bypassed: true in <out>/merge-report.json"
        ),
    )
    p_merge.add_argument(
        "--fresh-history", action="store_true",
        help=(
            "point PRAGMA_PROBE_STATS at <out>/merge-history.jsonl for the re-gate "
            "so a prior host attempt on record can never trip the runner's "
            "'already rejected' preflight; a successful accept is then folded "
            "into the host's real probe-stats history"
        ),
    )

    p_summary = sub.add_parser(
        "summary", help="print summary.json / state.json from a container output directory"
    )
    p_summary.add_argument("out_dir", type=Path)

    p_import_stats = sub.add_parser(
        "import-stats",
        help="append this run's <out>/probe-stats/probe-stats.jsonl into the host's probe-stats history",
    )
    p_import_stats.add_argument(
        "out_dir", type=Path,
        help="container output directory (contains probe-stats/probe-stats.jsonl)",
    )
    p_import_stats.add_argument(
        "--repo", type=Path, default=Path("."), help="host checkout whose probe-stats history to append to"
    )
    p_import_stats.add_argument(
        "--dry-run", action="store_true", help="count lines only; never write to the host history"
    )

    args = parser.parse_args(argv)

    if args.command == "merge":
        return merge(
            args.out_dir,
            repo_root=args.repo.resolve(),
            commit=args.commit,
            dry_run=args.dry_run,
            no_cc_check=args.no_cc_check,
            fresh_history=args.fresh_history,
        )
    if args.command == "summary":
        return summary_command(args.out_dir)
    if args.command == "import-stats":
        return import_stats(args.out_dir, repo_root=args.repo.resolve(), dry_run=args.dry_run)

    parser.error(f"unknown command {args.command!r}")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
