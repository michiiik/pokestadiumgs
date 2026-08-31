#!/usr/bin/env python3
"""Shared home for the MCP candidate runner's probe-stats JSONL history.

The runner's probe statistics file is the process's only memory of what has
already been tried against a given owner.  It used to live at the gitignored
``disasm/build/probe-stats.jsonl``, which a build clean (``make clean``)
wipes -- every batch's history was lost with it.  This module owns:

* where the *active* file lives (``stats_path``) -- now
  ``disasm/probe-stats/probe-stats.jsonl``, a sibling of ``disasm/build/``
  rather than a child of it, so a build clean cannot touch it;
* where the *old* file lives (``legacy_stats_paths``), so a reader still
  sees history recorded before this move;
* reading across the active file, any legacy file, and any rotated sibling
  of either (``iter_batches``/``iter_attempts``), tolerating corrupt lines
  from a concurrent writer;
* shaping one attempt dict before it is persisted (``shape_attempt_row``):
  ``assembly_diff``/``assembly_diff_truncated`` are runtime-only diagnostics
  and must never be written to disk, and ``diagnostic`` is bounded so one
  verbose compiler error cannot dominate the file;
* keeping any single file bounded (``rotate_if_needed``); and
* a one-time, idempotent copy of the legacy file into the new location
  (``migrate_legacy``, also usable as ``python3 tools/probe_stats.py
  migrate``), retaining a canonical raw-batch hash so readers can deduplicate
  the shaped copy against its exact legacy source without conflating rows;

Every batch row written through this module carries ``schema_version: 2``,
an ISO-8601 UTC ``timestamp``, a ``batch_id`` (uuid4 hex), the ``worktree``
path, and a best-effort short ``git_head``.  Old rows (schema 1, with none
of these fields) are still read by ``iter_batches``/``iter_attempts`` --
this module never rejects a row for missing metadata.
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import subprocess
import sys
import uuid
from collections.abc import Callable, Iterable, Iterator
from datetime import datetime, timezone
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent

DEFAULT_STATS_PATH = REPO_ROOT / "disasm" / "probe-stats" / "probe-stats.jsonl"
LEGACY_STATS_PATH = REPO_ROOT / "disasm" / "build" / "probe-stats.jsonl"
MIGRATION_MARKER_NAME = ".migrated-from-legacy"
MIGRATION_PROVENANCE_KEY = "_probe_stats_migration"

SCHEMA_VERSION = 2
DIAGNOSTIC_MAX_CHARS = 2000
DEFAULT_MAX_BYTES = 64 * 1024 * 1024

_ROTATED_RE_CACHE: dict[tuple[str, str], re.Pattern[str]] = {}


def raw_batch_sha256(batch: dict[str, object]) -> str:
    """Return a stable identity for one unmodified legacy JSON batch."""
    encoded = json.dumps(batch, sort_keys=True, separators=(",", ":")).encode("utf-8")
    return hashlib.sha256(encoded).hexdigest()


def stats_path() -> Path | None:
    """Resolve the active probe-stats file from ``PRAGMA_PROBE_STATS``.

    Unset -> the new default location, outside ``disasm/build/`` so a build
    clean cannot remove stats history.  Empty string -> disabled (``None``):
    a caller that gets ``None`` back must skip writing metrics entirely, the
    same contract the runner already documented for this variable.  Any
    other value -> that path, expanded (``~`` and env vars).
    """
    value = os.environ.get("PRAGMA_PROBE_STATS")
    if value == "":
        return None
    if value is None:
        return DEFAULT_STATS_PATH
    return Path(os.path.expandvars(value)).expanduser()


def legacy_stats_paths() -> list[Path]:
    """Old ``disasm/build/probe-stats.jsonl`` location(s), for readers only."""
    return [LEGACY_STATS_PATH]


def _default_paths() -> list[Path]:
    paths: list[Path] = []
    active = stats_path()
    if active is not None:
        paths.append(active)
    for legacy in legacy_stats_paths():
        if legacy not in paths:
            paths.append(legacy)
    return paths


def _rotated_pattern(stem: str, suffix: str) -> re.Pattern[str]:
    key = (stem, suffix)
    cached = _ROTATED_RE_CACHE.get(key)
    if cached is not None:
        return cached
    pattern = re.compile(rf"^{re.escape(stem)}\.(\d+){re.escape(suffix)}$")
    _ROTATED_RE_CACHE[key] = pattern
    return pattern


def _expand_with_rotations(path: Path) -> list[Path]:
    """``path`` plus any ``<stem>.<N><suffix>`` rotated sibling, oldest first."""
    parent = path.parent
    if not parent.is_dir():
        return [path]
    pattern = _rotated_pattern(path.stem, path.suffix)
    rotated: list[tuple[int, Path]] = []
    for candidate in parent.iterdir():
        match = pattern.match(candidate.name)
        if match:
            rotated.append((int(match.group(1)), candidate))
    rotated.sort(key=lambda item: item[0])
    return [path] + [item[1] for item in rotated]


def resolve_paths(paths: Iterable[Path] | None = None) -> list[Path]:
    """Expand ``paths`` (default: active + legacy) into existing files.

    Every returned path exists on disk.  ``paths=None`` uses the active
    file (unless disabled) plus every legacy file; an explicit ``paths``
    iterable is used as given, without also pulling in legacy files, so a
    caller that wants exactly one file (a test's temp-directory stats
    fixture, a user-provided ``--stats`` path) is never surprised by a real
    checkout's own history bleeding in.  Either way, every base path is
    expanded to include its own rotated ``<stem>.<N><suffix>`` siblings.
    """
    bases = _default_paths() if paths is None else [Path(item) for item in paths]
    resolved: list[Path] = []
    seen: set[Path] = set()
    for base in bases:
        for candidate in _expand_with_rotations(base):
            if not candidate.exists():
                continue
            key = candidate.resolve()
            if key in seen:
                continue
            seen.add(key)
            resolved.append(candidate)
    return resolved


def iter_batches_with_paths(
    paths: Iterable[Path] | None = None,
) -> Iterator[tuple[Path, dict[str, object]]]:
    """Yield ``(source path, batch)`` for every valid JSONL record.

    A corrupt or partial line (a concurrent writer's append can race a
    reader) is skipped rather than raised.
    """
    for path in resolve_paths(paths):
        try:
            with path.open("r", encoding="utf-8", errors="replace") as handle:
                for line in handle:
                    line = line.strip()
                    if not line:
                        continue
                    try:
                        record = json.loads(line)
                    except json.JSONDecodeError:
                        continue
                    if isinstance(record, dict):
                        yield path, record
        except OSError:
            continue


def iter_batches(paths: Iterable[Path] | None = None) -> Iterator[dict[str, object]]:
    """Yield one batch dict per JSONL line across ``resolve_paths(paths)``."""
    for _, batch in iter_batches_with_paths(paths):
        yield batch


def iter_attempts(paths: Iterable[Path] | None = None) -> Iterator[dict[str, object]]:
    """Yield every attempt dict across ``iter_batches(paths)``."""
    for batch in iter_batches(paths):
        attempts = batch.get("attempts")
        if not isinstance(attempts, list):
            continue
        for attempt in attempts:
            if isinstance(attempt, dict):
                yield attempt


def shape_attempt_row(
    attempt: dict[str, object], *, diagnostic_max_chars: int = DIAGNOSTIC_MAX_CHARS
) -> dict[str, object]:
    """Drop runtime-only fields and bound ``diagnostic`` before persisting.

    ``assembly_diff``/``assembly_diff_truncated`` are runtime-only per
    AGENTS.md and must never reach the stats file -- they dominated the size
    of the old file (roughly 55%) for no lasting benefit.  ``diagnostic`` is
    truncated to its first ``diagnostic_max_chars`` characters.  ``candidate``
    is always kept: the accepted candidate text is the whole point of the
    file (``pragma_targets.solved_shapes``/``template_transfer.py`` reuse it).
    """
    row = dict(attempt)
    row.pop("assembly_diff", None)
    row.pop("assembly_diff_truncated", None)
    diagnostic = row.get("diagnostic")
    if isinstance(diagnostic, str) and len(diagnostic) > diagnostic_max_chars:
        row["diagnostic"] = diagnostic[:diagnostic_max_chars]
    return row


def shape_legacy_batch(batch: dict[str, object]) -> dict[str, object]:
    """Return the exact lossy batch shape written by ``migrate_legacy``."""
    shaped = dict(batch)
    attempts = shaped.get("attempts")
    if isinstance(attempts, list):
        shaped["attempts"] = [
            shape_attempt_row(attempt) for attempt in attempts if isinstance(attempt, dict)
        ]
    return shaped


def _git_head(repo_root: Path) -> str | None:
    try:
        result = subprocess.run(
            ["git", "rev-parse", "--short", "HEAD"],
            cwd=repo_root,
            text=True,
            encoding="utf-8",
            errors="replace",
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            timeout=5,
        )
    except (OSError, subprocess.SubprocessError):
        return None
    if result.returncode != 0:
        return None
    head = result.stdout.strip()
    return head or None


def new_batch_row(
    source: str,
    attempts: list[dict[str, object]],
    *,
    counts: dict[str, int] | None = None,
    timing: dict[str, object] | None = None,
    batch_status: str | None = None,
    families: dict[str, str] | None = None,
    family_lookup: Callable[[str], str | None] | None = None,
    diagnostic_max_chars: int = DIAGNOSTIC_MAX_CHARS,
) -> dict[str, object]:
    """Build one schema-2 batch row, shaping and annotating every attempt.

    An attempt that already carries a ``family`` keeps it.  Otherwise
    ``families`` (a ``function -> family`` mapping the caller already knows,
    e.g. from a sweep listing) is consulted, then ``family_lookup`` (a
    fallback callable a caller can set when threading a mapping through
    every call site is awkward). Either source is optional and best-effort:
    a missing family is left out rather than guessed.
    """
    shaped: list[dict[str, object]] = []
    for attempt in attempts:
        row = shape_attempt_row(attempt, diagnostic_max_chars=diagnostic_max_chars)
        function = row.get("function")
        if row.get("family") is None and isinstance(function, str):
            family: str | None = None
            if families is not None:
                family = families.get(function)
            if family is None and family_lookup is not None:
                try:
                    family = family_lookup(function)
                except Exception:
                    family = None
            if family is not None:
                row["family"] = family
        shaped.append(row)
    return {
        "schema_version": SCHEMA_VERSION,
        "timestamp": datetime.now(timezone.utc).isoformat(timespec="seconds").replace("+00:00", "Z"),
        "batch_id": uuid.uuid4().hex,
        "worktree": str(REPO_ROOT),
        "git_head": _git_head(REPO_ROOT),
        "source": source,
        "counts": counts,
        "timing": timing,
        "batch_status": batch_status,
        "attempts": shaped,
    }


def rotate_if_needed(path: Path, max_bytes: int = DEFAULT_MAX_BYTES) -> Path | None:
    """Rename ``path`` to the next ``<stem>.<N><suffix>`` once it exceeds ``max_bytes``.

    Called before an append so the active file never grows unbounded.
    Returns the rotated path, or ``None`` if no rotation happened (the file
    is missing, under the limit, or the rename itself failed).  A reader
    always sees a rotated file too: ``resolve_paths``/``iter_batches`` expand
    every base path to include its ``<stem>.<N><suffix>`` siblings.
    """
    try:
        if not path.exists() or path.stat().st_size < max_bytes:
            return None
    except OSError:
        return None
    stem = path.stem
    suffix = path.suffix
    index = 1
    while True:
        candidate = path.with_name(f"{stem}.{index}{suffix}")
        if not candidate.exists():
            break
        index += 1
    try:
        path.rename(candidate)
    except OSError:
        return None
    return candidate


def append_batch(
    row: dict[str, object], *, path: Path | None = None, max_bytes: int = DEFAULT_MAX_BYTES
) -> Path | None:
    """Append one batch row as a JSON line, rotating first if needed.

    ``path`` defaults to ``stats_path()``; when that resolves to ``None``
    (``PRAGMA_PROBE_STATS=""``), this is a no-op and returns ``None``. Any
    ``OSError`` while writing is swallowed -- metrics must never turn a
    valid candidate transaction into a failure -- and also reported as
    ``None``.
    """
    target = stats_path() if path is None else path
    if target is None:
        return None
    try:
        target.parent.mkdir(parents=True, exist_ok=True)
        rotate_if_needed(target, max_bytes=max_bytes)
        with target.open("a", encoding="utf-8") as handle:
            handle.write(json.dumps(row, sort_keys=True) + "\n")
    except OSError:
        return None
    return target


def migrate_legacy(
    *,
    legacy_path: Path | None = None,
    target_path: Path | None = None,
    marker_path: Path | None = None,
) -> dict[str, object]:
    """Copy the legacy ``disasm/build/probe-stats.jsonl`` into the new location, once.

    Every copied attempt is passed through ``shape_attempt_row`` first, so a
    legacy row's ``assembly_diff``/oversized ``diagnostic`` does not survive
    the move. The migrated batch records a namespaced hash of the canonical
    raw row computed before that lossy shaping. Idempotent: a marker file next
    to the target records that the migration ran (successfully, or because
    there was nothing to migrate),
    and a later call is a no-op until the marker is removed.
    """
    legacy = legacy_path if legacy_path is not None else LEGACY_STATS_PATH
    target = target_path if target_path is not None else DEFAULT_STATS_PATH
    marker = marker_path if marker_path is not None else target.parent / MIGRATION_MARKER_NAME

    if marker.exists():
        return {"migrated": False, "reason": "already migrated", "marker": str(marker)}

    marker.parent.mkdir(parents=True, exist_ok=True)
    if not legacy.exists():
        marker.write_text(f"no legacy file found at {legacy}\n", encoding="utf-8")
        return {"migrated": False, "reason": "no legacy file", "marker": str(marker)}

    copied_batches = 0
    copied_attempts = 0
    with target.open("a", encoding="utf-8") as out:
        for line in legacy.read_text(encoding="utf-8", errors="replace").splitlines():
            line = line.strip()
            if not line:
                continue
            try:
                batch = json.loads(line)
            except json.JSONDecodeError:
                continue
            if not isinstance(batch, dict):
                continue
            raw_sha256 = raw_batch_sha256(batch)
            batch = shape_legacy_batch(batch)
            attempts = batch.get("attempts")
            if isinstance(attempts, list):
                copied_attempts += len(attempts)
            batch[MIGRATION_PROVENANCE_KEY] = {
                "kind": "legacy_raw_batch_sha256",
                "sha256": raw_sha256,
            }
            out.write(json.dumps(batch, sort_keys=True) + "\n")
            copied_batches += 1

    marker.write_text(
        f"migrated {copied_batches} batches ({copied_attempts} attempts) from {legacy} to "
        f"{target} on {datetime.now(timezone.utc).isoformat(timespec='seconds')}Z\n",
        encoding="utf-8",
    )
    return {
        "migrated": True,
        "batches": copied_batches,
        "attempts": copied_attempts,
        "legacy": str(legacy),
        "target": str(target),
        "marker": str(marker),
    }


def _cli(argv: list[str] | None = None) -> int:
    argv = sys.argv[1:] if argv is None else argv
    if not argv or argv[0] != "migrate":
        print("usage: python3 tools/probe_stats.py migrate", file=sys.stderr)
        return 2
    result = migrate_legacy()
    print(json.dumps(result, indent=2, sort_keys=True))
    return 0


if __name__ == "__main__":
    raise SystemExit(_cli())
