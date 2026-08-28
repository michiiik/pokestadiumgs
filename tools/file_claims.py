#!/usr/bin/env python3
"""A file-claim registry so two live runner sessions never share a source file.

Two fleet coordinators in one checkout collided on 2026-08-28: one committed
with a broad stage (``git add -A`` / ``git commit -a``) and swept the other
fleet's uncommitted, runner-installed edits into its own commit (``0525ec9``,
see AGENTS.md 1.1/1.2). ``git log --since`` only sees *committed* history, so
it cannot tell a coordinator that a file is mid-edit in someone else's
working tree right now. This module is the missing piece: a small registry
(``disasm/probe-stats/claims.json``, gitignored -- see ``.gitignore``) that
records which live session is editing which source, so the runner can refuse
to install into a file another session holds (``try_pragma_compare.py``'s
``_claim_or_refuse``) and the pre-commit hook can refuse to commit one
(``check_file_claims.py``).

Registry format (one JSON object, source path -> entry)::

    {
      "disasm/src/229E0.c": {
        "owner": "<pid>@<hostname>:<session tag>",
        "claimed_at": <epoch seconds>,
        "expires_at": <epoch seconds>,
        "last_touch": <epoch seconds>
      }
    }

``owner`` identifies a live *session*, not just a process: ``<session tag>``
is ``$CLAUDE_JOB_DIR`` (one per agent job) or, failing that, ``$PPID`` (the
parent shell/harness), so two calls from the same fleet agent agree on an
owner even across separate ``tools/try_pragma_compare.py`` invocations,
while two different agents sharing one MCP server process (same pid) still
get distinct owners. ``CLAIMS_OWNER`` overrides this computation entirely --
set it in a test for a stable fake identity, or by a coordinator committing
on behalf of one of its agents so the commit is recognized as that agent's
own session rather than a foreign one.

A claim is *live* unless it is past ``expires_at`` (default TTL: 90 minutes,
refreshed by every ``claim``/``touch``) or, when it was recorded on this same
host, its pid is no longer running (see ``is_live``). An expired or dead
claim never blocks a new one; ``expire()`` sweeps them out entirely.

All registry writes take an exclusive file lock (``fcntl.flock`` on a lock
file under the OS temp dir, keyed by repo root -- the same pattern
``try_pragma_compare._candidate_transaction_lock`` uses for the runner's
transaction lock) and write via a temp-file-plus-rename so a reader never
sees a partial file.

CLI:
    python3 tools/file_claims.py list
    python3 tools/file_claims.py claim disasm/src/229E0.c [--ttl SECONDS]
    python3 tools/file_claims.py release disasm/src/229E0.c [--force]
    python3 tools/file_claims.py expire
    python3 tools/file_claims.py free [--exclude-recent HOURS] [--fragments]

``free`` replaces the manual ``git log --since="4 hours ago" --format=
--name-only -- disasm/src`` check AGENTS.md 1.1 asks a fleet coordinator to
run before assigning a file: it lists remaining-owner source files that have
no live claim right now *and* were not touched in that recent git history,
so a coordinator does not hand out a file someone is mid-edit on just
because they have not committed yet.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import socket
import subprocess
import sys
import tempfile
import time
from contextlib import contextmanager
from datetime import datetime, timezone
from pathlib import Path

try:
    import fcntl
except ImportError:  # pragma: no cover - the supported host is POSIX/macOS
    fcntl = None

REPO_ROOT = Path(__file__).resolve().parent.parent
DISASM_ROOT = REPO_ROOT / "disasm"

# Mirrors variant_policy.default_stats_paths()'s root resolution: a
# gitignored directory (see .gitignore's "disasm/probe-stats/") that is a
# sibling of disasm/build/ so a build clean cannot wipe it. Unlike the
# probe-stats history, this file is per-checkout on purpose -- a worktree
# has its own working tree and thus its own live edits to claim -- but
# PRAGMA_CLAIMS_REGISTRY can point a worktree at the main checkout's copy
# when a coordinator wants one shared view across worktrees.
DEFAULT_REGISTRY_PATH = DISASM_ROOT / "probe-stats" / "claims.json"

DEFAULT_TTL_SECONDS = 90 * 60

_OWNER_RE = re.compile(r"^(?P<pid>\d+)@(?P<host>[^:]+):(?P<session>.*)$")

# Paths this process has already claimed (as opposed to touched); see
# _claim_or_refuse in try_pragma_compare.py.
_CLAIMED_THIS_PROCESS: set[str] = set()


# ---------------------------------------------------------------------------
# Registry path and owner identity
# ---------------------------------------------------------------------------


def registry_path() -> Path:
    """Resolve the claims registry file.

    ``PRAGMA_CLAIMS_REGISTRY`` overrides the default (expanded like
    ``PRAGMA_PROBE_STATS``: ``~`` and env vars); tests point this at a
    tempdir fixture instead of touching a real checkout's registry.
    """
    value = os.environ.get("PRAGMA_CLAIMS_REGISTRY")
    if value:
        return Path(os.path.expandvars(value)).expanduser()
    return DEFAULT_REGISTRY_PATH


def _session_tag() -> str:
    return os.environ.get("CLAUDE_JOB_DIR") or str(os.getppid())


def default_owner() -> str:
    """This process's computed claim identity: ``<pid>@<hostname>:<session tag>``."""
    return f"{os.getpid()}@{socket.gethostname()}:{_session_tag()}"


def current_owner() -> str:
    """The owner identity for this process's claims (and, for the hook, this commit).

    ``CLAIMS_OWNER`` overrides ``default_owner()`` -- see the module
    docstring.
    """
    override = os.environ.get("CLAIMS_OWNER")
    if override:
        return override
    return default_owner()


def owner_session(owner: str) -> str:
    """The session-identity portion of ``owner``, for cross-process comparison.

    A runner call and a later ``git commit`` from the same fleet agent are
    different OS processes (different pid), so comparing whole owner
    strings would call them different even when they are "the same
    session". For a well-formed ``<pid>@<host>:<session>`` owner this
    returns the ``host:session`` suffix (pid-independent); for a freeform
    string (a test's or coordinator's ``CLAIMS_OWNER``, with no pid/host)
    it returns the string unchanged, so two matching freeform overrides
    still compare equal.
    """
    match = _OWNER_RE.match(owner)
    if not match:
        return owner
    return f"{match.group('host')}:{match.group('session')}"


def same_session(owner_a: str, owner_b: str) -> bool:
    """Whether ``owner_a`` and ``owner_b`` name the same live session."""
    return owner_session(owner_a) == owner_session(owner_b)


def _owner_pid_host(owner: str) -> tuple[int | None, str | None]:
    match = _OWNER_RE.match(owner)
    if not match:
        return None, None
    return int(match.group("pid")), match.group("host")


def _pid_running(pid: int) -> bool:
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        return False
    except PermissionError:
        return True  # exists, just not owned by us
    except OSError:
        return False
    return True


def is_live(entry: dict[str, object], *, now: float | None = None) -> bool:
    """Whether a claims-registry ``entry`` still holds.

    Expired (past ``expires_at``) is never live. Otherwise, when the
    owner's hostname matches this host, a pid that is no longer running
    also means not live -- a crashed process leaks no claim past its own
    check-in. A claim recorded on another host cannot be confirmed dead
    locally, so it lives out its TTL; ``expire()`` (or the next
    ``claim()``/``touch()`` cycle) eventually reclaims it. A malformed or
    freeform owner (no ``pid@host:session`` shape, e.g. a test's
    ``CLAIMS_OWNER``) has no pid to check either, so only the TTL applies.
    """
    if now is None:
        now = time.time()
    expires_at = entry.get("expires_at")
    if isinstance(expires_at, (int, float)) and now >= expires_at:
        return False
    owner = entry.get("owner")
    if not isinstance(owner, str):
        return True
    pid, host = _owner_pid_host(owner)
    if pid is None or host != socket.gethostname():
        return True
    return _pid_running(pid)


# ---------------------------------------------------------------------------
# Path normalization
# ---------------------------------------------------------------------------


def registry_key(path: str | Path, *, repo_root: Path = REPO_ROOT) -> str:
    """Public alias of ``_normalize_path`` for a caller that needs the exact
    registry key (e.g. ``try_pragma_compare._claim_or_refuse``'s per-process
    already-claimed cache) without duplicating the normalization rule."""
    return _normalize_path(path, repo_root=repo_root)


def _normalize_path(path: str | Path, *, repo_root: Path = REPO_ROOT) -> str:
    """Registry key for ``path``: repo-root-relative, forward-slashed.

    Matches the shape ``pragma_targets.Owner.source`` and ``git diff
    --name-only`` both already use, so a claim keyed off a
    ``try_pragma_compare`` source path and a lookup keyed off a staged
    git path agree without either side reformatting.
    """
    candidate = Path(path)
    if candidate.is_absolute():
        try:
            candidate = candidate.relative_to(repo_root)
        except ValueError:
            pass
    return candidate.as_posix()


# ---------------------------------------------------------------------------
# Locking and atomic I/O
# ---------------------------------------------------------------------------


@contextmanager
def _registry_lock(path: Path):
    """Serialize registry read-modify-write cycles across processes.

    Same pattern as ``try_pragma_compare._candidate_transaction_lock``: an
    ``flock``-held file under the OS temp dir, named from a hash of the
    repo root so unrelated checkouts never share a lock.
    """
    path.parent.mkdir(parents=True, exist_ok=True)
    repo_key = hashlib.sha256(str(REPO_ROOT).encode()).hexdigest()[:16]
    lock_path = Path(tempfile.gettempdir()) / f"pokemon_stadium_pragma_runner_{repo_key}_claims.lock"
    with lock_path.open("a+") as handle:
        if fcntl is not None:
            fcntl.flock(handle.fileno(), fcntl.LOCK_EX)
        try:
            yield
        finally:
            if fcntl is not None:
                fcntl.flock(handle.fileno(), fcntl.LOCK_UN)


def _load(path: Path) -> dict[str, dict[str, object]]:
    try:
        text = path.read_text(encoding="utf-8")
    except OSError:
        return {}
    if not text.strip():
        return {}
    try:
        data = json.loads(text)
    except json.JSONDecodeError:
        return {}
    return data if isinstance(data, dict) else {}


def _save(path: Path, data: dict[str, dict[str, object]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, tmp_name = tempfile.mkstemp(dir=str(path.parent), prefix=".claims-", suffix=".tmp")
    try:
        with os.fdopen(fd, "w", encoding="utf-8") as handle:
            json.dump(data, handle, indent=2, sort_keys=True)
            handle.write("\n")
        os.replace(tmp_name, path)
    except BaseException:
        try:
            os.unlink(tmp_name)
        except OSError:
            pass
        raise


# ---------------------------------------------------------------------------
# Public API
# ---------------------------------------------------------------------------


def claim(
    path: str | Path,
    owner: str | None = None,
    ttl: float | None = None,
    *,
    registry: Path | None = None,
) -> bool:
    """Claim ``path`` for ``owner`` (default ``current_owner()``).

    Fails (returns ``False``, registry unchanged) when a *different* live
    owner already holds it. Refreshes (extends ``expires_at``, keeps the
    original ``claimed_at``) when the same owner already holds it, live or
    not. Otherwise records a fresh claim.
    """
    key = _normalize_path(path)
    owner = owner or current_owner()
    ttl_seconds = DEFAULT_TTL_SECONDS if ttl is None else ttl
    reg_path = registry or registry_path()
    now = time.time()
    with _registry_lock(reg_path):
        data = _load(reg_path)
        entry = data.get(key)
        if entry is not None and is_live(entry, now=now) and entry.get("owner") != owner:
            return False
        same_owner_live = entry is not None and entry.get("owner") == owner and is_live(entry, now=now)
        claimed_at = entry.get("claimed_at") if same_owner_live else now
        data[key] = {
            "owner": owner,
            "claimed_at": claimed_at,
            "expires_at": now + ttl_seconds,
            "last_touch": now,
        }
        _save(reg_path, data)
    return True


def touch(
    path: str | Path,
    owner: str | None = None,
    ttl: float | None = None,
    *,
    registry: Path | None = None,
) -> bool:
    """Extend an existing claim's TTL. False if ``path`` isn't held by ``owner``."""
    key = _normalize_path(path)
    owner = owner or current_owner()
    ttl_seconds = DEFAULT_TTL_SECONDS if ttl is None else ttl
    reg_path = registry or registry_path()
    now = time.time()
    with _registry_lock(reg_path):
        data = _load(reg_path)
        entry = data.get(key)
        if entry is None or entry.get("owner") != owner:
            return False
        entry["last_touch"] = now
        entry["expires_at"] = now + ttl_seconds
        data[key] = entry
        _save(reg_path, data)
    return True


def release(
    path: str | Path,
    owner: str | None = None,
    *,
    force: bool = False,
    registry: Path | None = None,
) -> bool:
    """Remove ``path``'s claim. False if unheld, or held by another owner and not ``force``."""
    key = _normalize_path(path)
    reg_path = registry or registry_path()
    with _registry_lock(reg_path):
        data = _load(reg_path)
        entry = data.get(key)
        if entry is None:
            return False
        if not force and entry.get("owner") != (owner or current_owner()):
            return False
        del data[key]
        _save(reg_path, data)
    return True


def holder(path: str | Path, *, registry: Path | None = None) -> dict[str, object] | None:
    """The raw registry entry for ``path`` (live or not), or ``None``."""
    key = _normalize_path(path)
    data = _load(registry or registry_path())
    entry = data.get(key)
    return dict(entry) if isinstance(entry, dict) else None


def list_claims(*, registry: Path | None = None) -> dict[str, dict[str, object]]:
    """Every entry currently on file, keyed by source path."""
    return _load(registry or registry_path())


def expire(*, registry: Path | None = None) -> list[str]:
    """Drop every not-live entry from the registry; return the removed paths."""
    reg_path = registry or registry_path()
    with _registry_lock(reg_path):
        data = _load(reg_path)
        now = time.time()
        removed = [key for key, entry in data.items() if not is_live(entry, now=now)]
        for key in removed:
            del data[key]
        if removed:
            _save(reg_path, data)
    return removed


# ---------------------------------------------------------------------------
# Coordinator convenience: files free to assign right now
# ---------------------------------------------------------------------------


def is_fragment_source(source: str) -> bool:
    return "/fragments/" in source.replace("\\", "/")


# git-repo-location env vars a git hook subprocess exports for its own
# children (GIT_DIR/GIT_WORK_TREE/GIT_INDEX_FILE/...). This module can run
# from inside a pre-commit hook's own `tools/run_tests.sh` (20-tests.sh) or
# from a coordinator script git itself invoked; left inherited, they would
# redirect the `git log` call below off ``repo_root`` and onto whatever repo
# is actually being committed to. See AGENTS.md 1.3's "GIT_DIR trap" and
# test_update_coverage.py's ``_GitFixture``, which strip the same set.
_GIT_ENV_VARS_TO_STRIP = (
    "GIT_DIR", "GIT_WORK_TREE", "GIT_INDEX_FILE", "GIT_COMMON_DIR",
    "GIT_OBJECT_DIRECTORY", "GIT_ALTERNATE_OBJECT_DIRECTORIES",
)


def _clean_git_env() -> dict[str, str]:
    env = dict(os.environ)
    for var in _GIT_ENV_VARS_TO_STRIP:
        env.pop(var, None)
    return env


def _recently_touched(hours: float, *, repo_root: Path = REPO_ROOT) -> set[str]:
    """Paths under ``disasm/src`` touched by a commit in the last ``hours``.

    Mirrors AGENTS.md 1.1's manual ``git log --since="4 hours ago" --format=
    --name-only -- disasm/src`` check. A missing/failed git call yields an
    empty set (permissive) rather than raising -- this is a coordinator
    convenience listing, not a gate.
    """
    since = f"{hours:g} hours ago"
    try:
        result = subprocess.run(
            ["git", "log", f"--since={since}", "--format=", "--name-only", "--", "disasm/src"],
            cwd=repo_root,
            capture_output=True,
            text=True,
            check=False,
            env=_clean_git_env(),
        )
    except OSError:
        return set()
    if result.returncode != 0:
        return set()
    return {line.strip() for line in result.stdout.splitlines() if line.strip()}


def free_files(
    *,
    exclude_recent_hours: float = 4.0,
    fragments: bool = False,
    registry: Path | None = None,
    repo_root: Path = REPO_ROOT,
    source_root: Path | None = None,
) -> list[dict[str, object]]:
    """Remaining-owner source files with no live claim and no recent commit.

    Replaces the manual git-log check AGENTS.md 1.1 asks a fleet
    coordinator to run before assigning a file to an agent: a file with an
    uncommitted, still-live claim is exactly the file that check cannot
    see. Reuses ``pragma_targets.owner_index()`` for the remaining-owner
    count per file (imported lazily -- ``pragma_targets`` imports
    ``try_pragma_compare``, which imports this module inside its own
    ``_claim_or_refuse``, so importing it at module scope here would risk
    a cycle depending on import order). ``source_root`` lets a test point
    the scan at a temp-repo fixture instead of this checkout's real
    ``disasm/src``.
    """
    import pragma_targets  # local import: see docstring

    index_kwargs: dict[str, object] = {"repo_root": repo_root}
    if source_root is not None:
        index_kwargs["source_root"] = source_root
    remaining: dict[str, int] = {}
    for owner in pragma_targets.owner_index(**index_kwargs).values():
        remaining[owner.source] = remaining.get(owner.source, 0) + 1

    candidates = {
        source: count
        for source, count in remaining.items()
        if is_fragment_source(source) == fragments
    }

    recent = _recently_touched(exclude_recent_hours, repo_root=repo_root)
    claims = list_claims(registry=registry)
    now = time.time()

    rows: list[dict[str, object]] = []
    for source, count in candidates.items():
        if source in recent:
            continue
        entry = claims.get(source)
        if entry is not None and is_live(entry, now=now):
            continue
        rows.append({"source": source, "remaining_owners": count})
    rows.sort(key=lambda row: (-row["remaining_owners"], row["source"]))
    return rows


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------


def _iso(value: object) -> str:
    if not isinstance(value, (int, float)):
        return "?"
    return datetime.fromtimestamp(value, tz=timezone.utc).isoformat(timespec="seconds")


def _cli_list(args: argparse.Namespace) -> int:
    data = list_claims()
    now = time.time()
    if not data:
        print("no claims on file")
        return 0
    for key in sorted(data):
        entry = data[key]
        status = "live" if is_live(entry, now=now) else "expired"
        print(f"{key}\t{entry.get('owner')}\t{status}\texpires={_iso(entry.get('expires_at'))}")
    return 0


def _cli_claim(args: argparse.Namespace) -> int:
    owner = current_owner()
    if claim(args.path, owner=owner, ttl=args.ttl):
        print(f"claimed {args.path} as {owner}")
        return 0
    entry = holder(args.path)
    holder_owner = entry.get("owner") if entry else "unknown"
    print(f"refused: {args.path} is claimed by {holder_owner}", file=sys.stderr)
    return 1


def _cli_release(args: argparse.Namespace) -> int:
    if release(args.path, force=args.force):
        print(f"released {args.path}")
        return 0
    print(f"not released: {args.path} is not claimed by this owner", file=sys.stderr)
    return 1


def _cli_expire(args: argparse.Namespace) -> int:
    removed = expire()
    for key in removed:
        print(f"expired {key}")
    print(f"{len(removed)} claim(s) expired")
    return 0


def _cli_free(args: argparse.Namespace) -> int:
    rows = free_files(exclude_recent_hours=args.exclude_recent, fragments=args.fragments)
    print(json.dumps(rows, indent=2))
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    commands = parser.add_subparsers(dest="command", required=True)

    commands.add_parser("list", help="list every claim on file").set_defaults(func=_cli_list)

    claim_cmd = commands.add_parser("claim", help="claim a source path for this process")
    claim_cmd.add_argument("path")
    claim_cmd.add_argument("--ttl", type=float, default=None, help="seconds (default: 90 minutes)")
    claim_cmd.set_defaults(func=_cli_claim)

    release_cmd = commands.add_parser("release", help="release a claimed source path")
    release_cmd.add_argument("path")
    release_cmd.add_argument("--force", action="store_true", help="release regardless of owner")
    release_cmd.set_defaults(func=_cli_release)

    commands.add_parser("expire", help="drop every not-live claim").set_defaults(func=_cli_expire)

    free_cmd = commands.add_parser(
        "free", help="remaining-owner files with no live claim and no recent commit"
    )
    free_cmd.add_argument("--exclude-recent", type=float, default=4.0, dest="exclude_recent", metavar="HOURS")
    free_cmd.add_argument("--fragments", action="store_true", help="list fragment files instead of text-segment files")
    free_cmd.set_defaults(func=_cli_free)

    args = parser.parse_args(argv)
    return args.func(args)


if __name__ == "__main__":
    raise SystemExit(main())
