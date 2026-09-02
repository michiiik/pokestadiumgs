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

This script is the "separate, deliberate step" the issue asks for: it never
trusts the container's own verdict. For each ``<out>/accepted/<owner>.json``
it re-runs the real oracle -- ``tools/fleet_probe.py <json> --gate`` -- against
*this* checkout, and only a candidate the host itself just gated is eligible
to be committed. A container that ran against a stale or tampered tree cannot
talk its way past this.

Usage:
    python3 tools/container_merge.py merge /abs/out
    python3 tools/container_merge.py merge /abs/out --commit
    python3 tools/container_merge.py merge /abs/out --repo . --dry-run
    python3 tools/container_merge.py summary /abs/out
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
) -> dict[str, object]:
    """Re-gate one accepted-candidate batch against ``repo_root``.

    Runs ``tools/fleet_probe.py <batch_path> --gate --json <tmp>`` and
    returns ``{"returncode", "result", "stdout", "stderr"}``, where
    ``result`` is the parsed raw runner payload (``{}`` if the subprocess
    never wrote one, e.g. an argument-parsing failure).
    """
    handle = tempfile.NamedTemporaryFile(
        prefix="container_merge_", suffix=".json", delete=False
    )
    result_path = Path(handle.name)
    handle.close()
    try:
        proc = subprocess.run(
            [
                python_bin,
                str(repo_root / "tools" / "fleet_probe.py"),
                str(batch_path),
                "--gate",
                "--json",
                str(result_path),
            ],
            cwd=repo_root,
            capture_output=True,
            text=True,
            timeout=timeout,
        )
        result: dict[str, object] = {}
        if result_path.exists() and result_path.stat().st_size:
            try:
                parsed = json.loads(result_path.read_text(encoding="utf-8"))
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
        result_path.unlink(missing_ok=True)


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
) -> MergeRow:
    owner = json_path.stem
    try:
        payload = load_accepted_batch(json_path)
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        return MergeRow(owner, None, owner, "error", f"invalid batch: {exc}", False, "")

    source = batch_source(payload)
    function = owner_function_name(owner, payload)

    gate = run_fleet_probe_gate(json_path, repo_root=repo_root)
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


def merge(out_dir: Path, *, repo_root: Path, commit: bool, dry_run: bool) -> int:
    accepted_dir = out_dir / "accepted"
    json_paths = (
        sorted(p for p in accepted_dir.glob("*.json") if p.is_file())
        if accepted_dir.is_dir()
        else []
    )
    if not json_paths:
        print(f"container_merge: no accepted candidates under {accepted_dir}")
        return 0

    rows = [
        process_owner(path, repo_root=repo_root, commit=commit, dry_run=dry_run)
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

    return 1 if (rejected or commit_failures) else 0


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

    p_summary = sub.add_parser(
        "summary", help="print summary.json / state.json from a container output directory"
    )
    p_summary.add_argument("out_dir", type=Path)

    args = parser.parse_args(argv)

    if args.command == "merge":
        return merge(
            args.out_dir,
            repo_root=args.repo.resolve(),
            commit=args.commit,
            dry_run=args.dry_run,
        )
    if args.command == "summary":
        return summary_command(args.out_dir)

    parser.error(f"unknown command {args.command!r}")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
