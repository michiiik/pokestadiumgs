#!/usr/bin/env python3
"""Guard: refuse to commit a ``disasm/src`` file another live session claims.

AGENTS.md 1.1/1.2 requires committing by explicit path and never sweeping a
foreign session's uncommitted edits into your own commit -- a broad stage
(``git add -A`` / ``git commit -a``) did exactly that on 2026-08-28
(``0525ec9``). ``tools/file_claims.py`` is the registry a runner install
writes into; this is the mechanical half that reads it at commit time:
``.githooks/pre-commit`` runs it on every commit (``git config core.hooksPath
.githooks``), and it fails the commit when the staged diff under
``disasm/src`` includes a file a *different*, still-live session holds.

Usage:
    tools/check_file_claims.py --staged

Set ``PRAGMA_CLAIMS_SKIP=1`` to bypass with justification (mirrors
``DECOMP_PROVENANCE_SKIP`` in ``check_decomp_provenance.py``).
``CLAIMS_OWNER`` overrides this process's own claim identity -- a
coordinator committing on behalf of one of its fleet agents sets it to that
agent's own claim owner, so the commit is recognized as the same session
that holds the claim rather than a foreign one; see
``file_claims.current_owner``.

Performance: one ``file_claims.list_claims()`` call loads the whole registry
once; a missing registry file reads back empty rather than erroring, so a
checkout that has never run a claiming runner sees no violations here.
"""

from __future__ import annotations

import argparse
import os
import subprocess
import sys
from pathlib import Path

import file_claims

REPO_ROOT = Path(__file__).resolve().parent.parent

# See file_claims._GIT_ENV_VARS_TO_STRIP / AGENTS.md 1.3's "GIT_DIR trap":
# a git hook subprocess exports these for its own children, and an
# unstripped call here would resolve against whatever repo GIT_DIR names
# instead of --repo-root when this script runs nested inside another git
# operation (e.g. this module's own test suite, mid-commit).
_GIT_ENV_VARS_TO_STRIP = (
    "GIT_DIR", "GIT_WORK_TREE", "GIT_INDEX_FILE", "GIT_COMMON_DIR",
    "GIT_OBJECT_DIRECTORY", "GIT_ALTERNATE_OBJECT_DIRECTORIES",
)


def _clean_git_env() -> dict:
    env = dict(os.environ)
    for var in _GIT_ENV_VARS_TO_STRIP:
        env.pop(var, None)
    return env


def staged_source_files(repo_root: Path) -> list[str]:
    result = subprocess.run(
        ["git", "diff", "--cached", "--name-only", "--diff-filter=ACMR", "--", "disasm/src"],
        cwd=repo_root,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        env=_clean_git_env(),
    )
    if result.returncode != 0:
        raise RuntimeError(f"git diff --staged failed: {result.stderr.strip()}")
    return [line.strip() for line in result.stdout.splitlines() if line.strip()]


def find_violations(
    staged_files: list[str],
    *,
    committer: str | None = None,
    registry: Path | None = None,
) -> tuple[dict[str, dict[str, object]], bool, dict[str, dict[str, object]]]:
    """Return ``(foreign, multi_owner, live_claims)`` for ``staged_files``.

    ``live_claims`` is every staged path with a currently-live claim.
    ``foreign`` is the subset whose owner is not ``committer``'s own
    session (``file_claims.same_session``). ``multi_owner`` is true when
    the staged set carries live claims from more than one distinct
    session -- a stronger signal that a broad stage swept multiple
    sessions' work together, independent of whether any single file's
    owner happens to match the committer.
    """
    committer = committer or file_claims.current_owner()
    data = file_claims.list_claims(registry=registry)
    live_claims = {
        path: data[path]
        for path in staged_files
        if path in data and file_claims.is_live(data[path])
    }
    foreign = {
        path: entry
        for path, entry in live_claims.items()
        if not file_claims.same_session(str(entry.get("owner", "")), committer)
    }
    distinct_sessions = {
        file_claims.owner_session(str(entry.get("owner", ""))) for entry in live_claims.values()
    }
    multi_owner = len(distinct_sessions) > 1
    return foreign, multi_owner, live_claims


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--staged", action="store_true", help="check the staged diff (the pre-commit hook's use)")
    parser.add_argument("--repo-root", type=Path, default=REPO_ROOT)
    args = parser.parse_args(argv)

    if os.environ.get("PRAGMA_CLAIMS_SKIP") == "1":
        print("check_file_claims: PRAGMA_CLAIMS_SKIP=1 set, bypassing", file=sys.stderr)
        return 0

    if not args.staged:
        parser.error("pass --staged (the only supported mode)")

    try:
        staged = staged_source_files(args.repo_root)
    except RuntimeError as error:
        print(f"check_file_claims: {error}", file=sys.stderr)
        return 1

    if not staged:
        return 0

    foreign, multi_owner, live_claims = find_violations(staged)
    if not foreign and not multi_owner:
        return 0

    reported = live_claims if multi_owner else foreign
    print(
        "check_file_claims: this commit stages source file(s) a live runner "
        "session is editing:",
        file=sys.stderr,
    )
    for path in sorted(reported):
        entry = reported[path]
        print(f"  {path}: claimed by {entry.get('owner')}", file=sys.stderr)
    if multi_owner:
        print(
            "  (claimed files from more than one live session are staged at once)",
            file=sys.stderr,
        )
    print(
        "\ncommit by explicit path; this file is being edited by another session. "
        "Set PRAGMA_CLAIMS_SKIP=1 to bypass (state the justification in the commit message).",
        file=sys.stderr,
    )
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
