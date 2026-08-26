#!/usr/bin/env python3
"""Refresh the generated decompilation coverage block in README.md.

The post-commit hook reads the committed tree at ``HEAD`` rather than the
working tree.  This keeps concurrent MCP probe edits out of the reported
counts until they are actually committed.
"""

from __future__ import annotations

import argparse
import re
import subprocess
from pathlib import Path


BASELINE_COMMIT = "f477acf"
BASELINE_TOTAL = 10_532
START_MARKER = "<!-- AUTO_COVERAGE:START -->"
END_MARKER = "<!-- AUTO_COVERAGE:END -->"
PRAGMA_RE = re.compile(
    r'GLOBAL_ASM\("asm/us/nonmatchings/[^" ]+/([^"/]+)\.s"\)'
)


def _git_grep(repo_root: Path, revision: str) -> str:
    result = subprocess.run(
        [
            "git",
            "-C",
            str(repo_root),
            "grep",
            "--no-color",
            "-h",
            "-E",
            r'GLOBAL_ASM\("asm/us/nonmatchings/[^" ]+/[^"/]+\.s"\)',
            revision,
            "--",
            "disasm/src",
        ],
        check=False,
        capture_output=True,
        text=True,
    )
    if result.returncode not in (0, 1):
        raise RuntimeError(result.stderr.strip() or f"git grep failed: {result.returncode}")
    return result.stdout


def _owner_count(text: str) -> int:
    return len({match.group(1) for match in PRAGMA_RE.finditer(text)})


def committed_counts(repo_root: Path, revision: str = "HEAD") -> tuple[int, int, float]:
    """Return ``(covered, total, percentage)`` for a committed revision."""

    try:
        remaining = _owner_count(_git_grep(repo_root, revision))
    except RuntimeError:
        # A hook should still be useful in a shallow clone where the original
        # vendoring commit is unavailable.  The baseline total is immutable.
        remaining = BASELINE_TOTAL
    total = BASELINE_TOTAL
    covered = max(total - remaining, 0)
    percentage = (covered / total * 100.0) if total else 0.0
    return covered, total, percentage


def render_block(covered: int, total: int, percentage: float) -> str:
    remaining = total - covered
    return "\n".join(
        [
            START_MARKER,
            "- US functions with C implementations: "
            f"**{covered:,} / {total:,} ({percentage:.1f}%)**",
            f"- Remaining `GLOBAL_ASM` owners: **{remaining:,}**",
            f"- Baseline: `{BASELINE_COMMIT}` (vendored US pragma snapshot)",
            END_MARKER,
        ]
    )


def update_readme(readme: Path, block: str) -> bool:
    text = readme.read_text(encoding="utf-8")
    start = text.find(START_MARKER)
    end = text.find(END_MARKER)
    if (start < 0) != (end < 0) or (end >= 0 and end < start):
        raise ValueError(f"coverage markers are malformed in {readme}")

    if start >= 0:
        end += len(END_MARKER)
        replacement = block
        updated = text[:start] + replacement + text[end:]
    else:
        section = (
            "\n## Decompilation coverage\n\n"
            "The following block is refreshed by the repository post-commit hook.\n\n"
            f"{block}\n"
        )
        updated = text.rstrip() + "\n" + section

    if updated == text:
        return False
    readme.write_text(updated, encoding="utf-8")
    return True


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo-root", type=Path, default=None)
    parser.add_argument("--readme", type=Path, default=None)
    args = parser.parse_args()

    repo_root = (args.repo_root or Path(__file__).resolve().parent.parent).resolve()
    readme = (args.readme or repo_root / "README.md").resolve()
    covered, total, percentage = committed_counts(repo_root)
    changed = update_readme(readme, render_block(covered, total, percentage))
    print(
        f"coverage: {covered}/{total} ({percentage:.1f}%), "
        f"{total - covered} GLOBAL_ASM remaining"
        + (" [README updated]" if changed else " [unchanged]")
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
