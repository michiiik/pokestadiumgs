#!/usr/bin/env python3
"""Remove exact duplicate top-level ``extern`` declarations from decompiled sources.

Candidates arrive with their own ``extern`` lines, so a source that has
absorbed many batches repeats the same declaration several times.  Removing
an identical later duplicate cannot change generated code, but the full
``COMPARE=1`` gate is still run when ``--verify`` is given so the claim is
checked rather than assumed.

Usage:
    tools/dedupe_externs.py                     # report only
    tools/dedupe_externs.py --apply --verify    # rewrite clean files, run the ROM gate
    tools/dedupe_externs.py --apply disasm/src/fragments/79/fragment79_37A6E0.c

Files with uncommitted changes are skipped unless ``--include-dirty`` is
passed: another session may be mid-transaction in them.
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

import try_pragma_compare as runner

REPO_ROOT = Path(__file__).resolve().parent.parent
SOURCE_ROOT = REPO_ROOT / "disasm" / "src"
EXTERN_RE = re.compile(r"^\s*extern\b[^;{]*;\s*$")


def _code_only(line: str, state: dict[str, bool]) -> str:
    """Return the line with comments and string literals blanked out."""
    out: list[str] = []
    index = 0
    while index < len(line):
        if state["comment"]:
            end = line.find("*/", index)
            if end < 0:
                return "".join(out)
            state["comment"] = False
            index = end + 2
            continue
        two = line[index:index + 2]
        if two == "/*":
            state["comment"] = True
            index += 2
            continue
        if two == "//":
            break
        char = line[index]
        if char in "\"'":
            quote = char
            index += 1
            while index < len(line) and line[index] != quote:
                index += 2 if line[index] == "\\" else 1
            index += 1
            continue
        out.append(char)
        index += 1
    return "".join(out)


def dedupe_text(text: str) -> tuple[str, list[str]]:
    """Drop repeated identical top-level extern lines; return text and removals."""
    seen: set[str] = set()
    removed: list[str] = []
    kept: list[str] = []
    depth = 0
    state = {"comment": False}
    for line in text.splitlines(keepends=True):
        code = _code_only(line, state)
        if depth == 0 and EXTERN_RE.match(code):
            key = re.sub(r"\s+", " ", code.strip())
            if key in seen:
                removed.append(key)
                continue
            seen.add(key)
        depth += code.count("{") - code.count("}")
        kept.append(line)
    return "".join(kept), removed


def dirty_sources() -> set[Path]:
    result = subprocess.run(
        ["git", "status", "--porcelain", "--", "disasm/src"],
        cwd=REPO_ROOT,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.DEVNULL,
    )
    dirty: set[Path] = set()
    for line in result.stdout.splitlines():
        if len(line) > 3:
            dirty.add((REPO_ROOT / line[3:].strip()).resolve())
    return dirty


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("paths", nargs="*", type=Path, help="sources to process (default: all of disasm/src)")
    parser.add_argument("--apply", action="store_true", help="rewrite files (default: report only)")
    parser.add_argument("--verify", action="store_true", help="run the full COMPARE=1 gate after applying; restore on failure")
    parser.add_argument("--include-dirty", action="store_true", help="also process files with uncommitted changes")
    args = parser.parse_args()

    paths = [path.resolve() for path in args.paths] if args.paths else sorted(SOURCE_ROOT.rglob("*.c"))
    paths = [path for path in paths if not any(part.startswith(".pragma_probe_") for part in path.parts)]
    skipped = dirty_sources() if not args.include_dirty else set()

    originals: dict[Path, str] = {}
    total_removed = 0
    for path in paths:
        if path in skipped:
            print(f"skip (dirty): {path.relative_to(REPO_ROOT)}")
            continue
        text = path.read_text(encoding="utf-8")
        new_text, removed = dedupe_text(text)
        if not removed:
            continue
        total_removed += len(removed)
        print(f"{path.relative_to(REPO_ROOT)}: {len(removed)} duplicate extern line(s)")
        if args.apply:
            originals[path] = text
            path.write_text(new_text, encoding="utf-8")
    print(f"{total_removed} duplicate extern line(s) in {len(originals) if args.apply else '(report only)'} file(s)")

    if args.apply and args.verify and originals:
        with runner._candidate_transaction_lock():
            for path in originals:
                runner.rebuild_source_object(path)
            result = runner.compare_current_tree(REPO_ROOT)
        if result != 0:
            for path, text in originals.items():
                path.write_text(text, encoding="utf-8")
                runner.rebuild_source_object(path)
            print("COMPARE=1 failed after dedupe: all files restored", file=sys.stderr)
            return 1
        print("COMPARE=1 OK after dedupe")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
