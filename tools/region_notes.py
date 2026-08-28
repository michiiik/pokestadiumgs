#!/usr/bin/env python3
"""Per-region notes: file-specific knowledge that does not belong in
``AGENTS.md`` (which only carries rules and heuristics that generalise
across the codebase).

A "region" is one ``disasm/src`` source file. Its notes live at
``docs/regions/<same relative path, with .md>`` -- e.g.
``disasm/src/fragments/79/fragment79_393CA0.c`` maps to
``docs/regions/fragments/79/fragment79_393CA0.md``, and
``disasm/src/4AC10.c`` maps to ``docs/regions/4AC10.md``. A directory-level
file (``docs/regions/fragments/79.md``) holds notes shared by every source
file in that directory -- one overlay, hand-authored or grown the same way.

``tools/file_brief.py`` prints ``load(source)`` at the top of its output (and
under a ``region_notes`` key in ``--json``) so an agent sees a file's
skip lists and proven spellings before it reads a line of assembly.

Usage:
    python3 tools/region_notes.py show disasm/src/4AC10.c
    python3 tools/region_notes.py append disasm/src/4AC10.c --text "..." \\
        [--heading "..."]
    python3 tools/region_notes.py list
"""

from __future__ import annotations

import argparse
import datetime
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
SRC_ROOT = REPO_ROOT / "disasm" / "src"
REGIONS_ROOT = REPO_ROOT / "docs" / "regions"


def _resolve(source: "str | Path") -> Path:
    path = Path(source)
    if not path.is_absolute():
        path = REPO_ROOT / path
    return path.resolve()


def _relative_source(source: "str | Path") -> Path:
    """Return ``source`` relative to ``disasm/src`` when possible.

    Falls back to relative-to-repo-root, and finally (for a path outside
    the repository entirely -- e.g. a synthetic test fixture under a
    tempdir) to just its filename, so callers always get a stable mapping
    instead of an exception.
    """
    resolved = _resolve(source)
    for root in (SRC_ROOT, REPO_ROOT):
        try:
            return resolved.relative_to(root)
        except ValueError:
            continue
    return Path(resolved.name)


def _display(path: Path) -> str:
    try:
        return path.resolve().relative_to(REPO_ROOT).as_posix()
    except ValueError:
        return path.as_posix()


def path_for(source: "str | Path") -> Path:
    """Return the file-level region-notes path for ``source``."""
    rel = _relative_source(source)
    return (REGIONS_ROOT / rel).with_suffix(".md")


def directory_path_for(source: "str | Path") -> "Path | None":
    """Return the directory-level (shared) region-notes path for ``source``,
    or ``None`` when ``source`` has no parent directory under the region
    tree (a top-level ``disasm/src`` file has no directory overlay)."""
    rel = _relative_source(source)
    parent = rel.parent
    if parent == Path("."):
        return None
    return (REGIONS_ROOT / parent).with_suffix(".md")


def load(source: "str | Path") -> str:
    """Concatenate the directory-level notes then the file-level notes for
    ``source``, each under a heading naming its origin. Empty string when
    neither exists."""
    blocks: list[str] = []

    dir_path = directory_path_for(source)
    if dir_path is not None and dir_path.exists():
        content = dir_path.read_text(encoding="utf-8").strip()
        if content:
            blocks.append(f"### Directory notes ({_display(dir_path)})\n\n{content}")

    file_path = path_for(source)
    if file_path.exists():
        content = file_path.read_text(encoding="utf-8").strip()
        if content:
            blocks.append(f"### File notes ({_display(file_path)})\n\n{content}")

    return "\n\n".join(blocks)


def append(source: "str | Path", text: str, *, heading: "str | None" = None) -> Path:
    """Append a dated section to ``source``'s file-level notes, creating the
    file with a standard header if it does not exist yet. Never rewrites
    existing content -- always adds after it."""
    file_path = path_for(source)
    file_path.parent.mkdir(parents=True, exist_ok=True)

    date = datetime.date.today().isoformat()
    title = heading.strip() if heading else date
    suffix = f" ({date})" if heading else ""
    section = f"## {title}{suffix}\n\n{text.strip()}\n"

    if not file_path.exists():
        display_source = _display(_resolve(source))
        header = (
            f"# Region notes -- {display_source}\n\n"
            "Per-file spellings, skip lists, and unsolved shapes for this "
            "source file. Delivered to agents by `tools/file_brief.py`; "
            "extend it with `tools/region_notes.py append`.\n\n"
        )
        file_path.write_text(header + section, encoding="utf-8")
    else:
        with file_path.open("a", encoding="utf-8") as handle:
            handle.write("\n" + section)

    return file_path


def list_regions() -> list[Path]:
    """Return every region-notes file (directory- and file-level), sorted."""
    if not REGIONS_ROOT.exists():
        return []
    return sorted(REGIONS_ROOT.rglob("*.md"))


def main(argv: "list[str] | None" = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)

    show_parser = sub.add_parser("show", help="print the region notes for a source file")
    show_parser.add_argument("source", help="repo-relative or absolute path to a disasm/src .c file")

    append_parser = sub.add_parser("append", help="append a dated note section")
    append_parser.add_argument("source", help="repo-relative or absolute path to a disasm/src .c file")
    append_parser.add_argument("--text", required=True, help="note text to append")
    append_parser.add_argument("--heading", help="section heading (defaults to today's date)")

    sub.add_parser("list", help="list every region-notes file")

    args = parser.parse_args(argv)

    if args.command == "show":
        text = load(args.source)
        if text:
            print(text)
        else:
            print(f"(no region notes for {args.source}; would live at {_display(path_for(args.source))})")
        return 0

    if args.command == "append":
        written = append(args.source, args.text, heading=args.heading)
        print(f"appended to {_display(written)}")
        return 0

    if args.command == "list":
        for path in list_regions():
            print(_display(path))
        return 0

    parser.error("unknown command")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
