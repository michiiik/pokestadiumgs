#!/usr/bin/env python3
"""Guard: a commit that drops a ``GLOBAL_ASM`` pragma must have run the MCP runner.

AGENTS.md requires every C replacement for a pragma-backed owner to go
through the MCP candidate runner's isolated probe plus the full ``COMPARE=1``
gate, never a manual source edit standing in for that.  This is the
mechanical half of that rule: ``.githooks/pre-commit`` runs it on every
commit (``git config core.hooksPath .githooks``), and it fails the commit if
a staged diff under ``disasm/src`` removes a

    #pragma GLOBAL_ASM("asm/us/nonmatchings/.../<func>.s")

line for a function that has no ``accepted`` attempt recorded anywhere in
the probe-stats history (the active file, the legacy ``disasm/build/`` file,
and any rotated sibling of either -- see ``tools/probe_stats.py``).

Usage:
    tools/check_decomp_provenance.py --staged

Set ``DECOMP_PROVENANCE_SKIP=1`` to bypass with justification (e.g. a
documentation-only change that happens to touch a pragma comment, or a
post-MCP cleanup AGENTS.md already allows as a manual edit).

Performance: a stats history can run tens of megabytes.  ``accepted_functions``
does a cheap substring check for ``"accepted"`` on every line before ever
calling ``json.loads``, since only a small fraction of rows are ever an
accepted attempt.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
from pathlib import Path

import probe_stats
import try_pragma_compare

REPO_ROOT = Path(__file__).resolve().parent.parent

# A removed line (unified diff, leading ``-``) naming the pragma for a
# tracked owner. Matches ``try_pragma_compare``'s/``pragma_targets``'s own
# pragma pattern.
_PRAGMA_LINE_RE = re.compile(
    r'^#pragma GLOBAL_ASM\("asm/us/nonmatchings/[^"]+/([A-Za-z_]\w*)\.s"\)\s*$'
)


def removed_pragma_functions(diff_text: str) -> list[str]:
    """Functions whose ``GLOBAL_ASM`` pragma line was removed under ``disasm/src``.

    Order-preserving, de-duplicated. Only lines removed from a file under
    ``disasm/src`` count -- a pragma appearing in, say, a comment inside a
    tool script is out of scope.
    """
    functions: list[str] = []
    seen: set[str] = set()
    current_file: str | None = None
    for line in diff_text.splitlines():
        if line.startswith("+++ "):
            current_file = line[4:]
            if current_file.startswith("b/"):
                current_file = current_file[2:]
            continue
        if line.startswith("diff --git") or line.startswith("--- "):
            continue
        if current_file is None or not current_file.startswith("disasm/src/"):
            continue
        if not line.startswith("-") or line.startswith("---"):
            continue
        match = _PRAGMA_LINE_RE.match(line[1:].strip())
        if match is None:
            continue
        function = match.group(1)
        if function not in seen:
            seen.add(function)
            functions.append(function)
    return functions


def staged_diff(repo_root: Path) -> str:
    result = subprocess.run(
        ["git", "diff", "--staged", "--no-color", "-U0", "--", "disasm/src"],
        cwd=repo_root,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    if result.returncode != 0:
        raise RuntimeError(f"git diff --staged failed: {result.stderr.strip()}")
    return result.stdout


def accepted_functions(
    paths: list[Path] | None = None, repo_root: Path | None = None
) -> set[str]:
    """Functions with at least one ``accepted`` attempt on file.

    Scans every resolved stats file (active + legacy + rotated, unless
    ``paths`` overrides that) with a substring check for ``"accepted"``
    before ``json.loads``-ing a line: most lines in a large history are not
    an accepted attempt at all, and skipping the parse for them is what
    keeps this fast on a 50 MB file.

    ``paths=None`` resolves through ``try_pragma_compare``'s own
    ``_probe_stats_history_paths`` -- the same primary-checkout-first
    resolution the runner itself writes through -- rather than
    ``probe_stats.resolve_paths(None)``'s plain local-worktree default.  A
    linked worktree (``git worktree add``) has no local
    ``disasm/probe-stats/``, since new accepted attempts land in the
    primary checkout's shared ledger; reading through the plain default
    here made this check unsatisfiable from any linked worktree, even for
    a real MCP-verified accept (see PR #364's history).
    """
    accepted: set[str] = set()
    resolved_paths = (
        list(try_pragma_compare._probe_stats_history_paths(repo_root))
        if paths is None
        else probe_stats.resolve_paths(paths)
    )
    for path in resolved_paths:
        try:
            text = path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        for line in text.splitlines():
            if '"accepted"' not in line:
                continue
            try:
                batch = json.loads(line)
            except json.JSONDecodeError:
                continue
            if not isinstance(batch, dict):
                continue
            attempts = batch.get("attempts")
            if not isinstance(attempts, list):
                continue
            for attempt in attempts:
                if not isinstance(attempt, dict):
                    continue
                if attempt.get("status") != "accepted":
                    continue
                function = attempt.get("function")
                if isinstance(function, str):
                    accepted.add(function)
    return accepted


def check_staged(repo_root: Path) -> list[str]:
    """Return the list of owners removed from ``disasm/src`` without an accepted attempt."""
    diff_text = staged_diff(repo_root)
    removed = removed_pragma_functions(diff_text)
    if not removed:
        return []
    accepted = accepted_functions(repo_root=repo_root)
    return [function for function in removed if function not in accepted]


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--staged", action="store_true", help="check the staged diff (the pre-commit hook's use)")
    parser.add_argument("--repo-root", type=Path, default=REPO_ROOT)
    args = parser.parse_args(argv)

    if os.environ.get("DECOMP_PROVENANCE_SKIP") == "1":
        print("check_decomp_provenance: DECOMP_PROVENANCE_SKIP=1 set, bypassing", file=sys.stderr)
        return 0

    if not args.staged:
        parser.error("pass --staged (the only supported mode)")

    try:
        missing = check_staged(args.repo_root)
    except RuntimeError as error:
        print(f"check_decomp_provenance: {error}", file=sys.stderr)
        return 1

    if not missing:
        return 0

    print(
        "check_decomp_provenance: this commit removes the GLOBAL_ASM pragma for the "
        "following owner(s) without an accepted MCP candidate on file in the "
        "probe-stats history:",
        file=sys.stderr,
    )
    for function in missing:
        print(f"  {function}", file=sys.stderr)
    print(
        "\nRun the candidate through the MCP runner (try_pragma_candidates) so an "
        "accepted attempt is recorded, or set DECOMP_PROVENANCE_SKIP=1 to bypass "
        "with justification (e.g. a documentation-only edit, or a post-MCP cleanup "
        "AGENTS.md already allows as a manual change).",
        file=sys.stderr,
    )
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
