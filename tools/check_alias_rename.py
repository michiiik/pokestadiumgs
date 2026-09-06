#!/usr/bin/env python3
"""Guard: a symbol_addrs_code.txt rename needs a matching aliases.ld alias.

Real incident (PR #58, 2026-09-02): a container's pre-extracted asm tree
still called a just-decompiled function by its old ``func_XXXXXXXX`` name
via a hard-coded relocation. The fix that keeps that working is
``disasm/linker_scripts/us/aliases.ld``'s compatibility alias
(``old = new;``); ``tools/container_merge.py``'s ``merge()`` implements the
convention correctly (see its own comments and ``append_name_alias``): the
address-keyed entry in ``disasm/linker_scripts/us/symbol_addrs_code.txt``
stays byte-for-byte unchanged, and the rename is expressed only as an
appended ``aliases.ld`` line, alongside the actual C rename.

Nothing stops a caller from bypassing that wrapper -- e.g. running
``tools/name_decompiled.py apply --hard-rename``, or hand-editing the
symtab -- and landing a hard rename with no alias, which breaks the link
for anything that still references the old name (confirmed for real this
session: ``undefined reference to 'func_84115E28'`` in a from-scratch
relink, caught only because CI's real link step still ran). This script
closes that gap at commit time, independent of which tool produced the
diff: it fails a commit whose staged diff renames an existing
address-keyed entry in ``symbol_addrs_code.txt`` (same address, old name
removed, new name added -- as opposed to a brand new entry, or the same
name's address value changing) without the same commit also adding a
matching ``<old> = <new>;`` line to ``aliases.ld``.

Usage:
    tools/check_alias_rename.py --staged

Set ``ALIAS_RENAME_SKIP=1`` to bypass with justification (e.g. a rename of
a placeholder that provably has zero remaining references anywhere, or a
deliberate ``--hard-rename`` where the alias was added by hand under a
different, already-reviewed line shape).
"""

from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent

SYMTAB_PATH = "disasm/linker_scripts/us/symbol_addrs_code.txt"
ALIASES_LD_PATH = "disasm/linker_scripts/us/aliases.ld"

# A `Name = 0xADDR ...;` address-keyed symtab line (name side only matters
# here; the trailing `// type:func ...` comment, if any, is irrelevant to
# rename detection).
_SYM_LINE_RE = re.compile(r"^\s*(?P<name>[A-Za-z_]\w*)\s*=\s*(?P<addr>0[xX][0-9A-Fa-f]+)\s*;")

# A bare `Lhs = Rhs;` alias assignment line, as added to aliases.ld.
_ALIAS_LINE_RE = re.compile(r"^\s*(?P<lhs>[A-Za-z_]\w*)\s*=\s*(?P<rhs>[A-Za-z_]\w*)\s*;\s*$")


def _file_diff(repo_root: Path, path: str, *, staged: bool) -> str:
    args = ["git", "diff"]
    if staged:
        args.append("--staged")
    args += ["--no-color", "-U0", "--", path]
    result = subprocess.run(args, cwd=repo_root, text=True, capture_output=True)
    if result.returncode != 0:
        raise RuntimeError(f"git diff failed for {path}: {result.stderr.strip()}")
    return result.stdout


def _plusminus_lines(diff_text: str):
    """Yield (sign, body) for every added/removed content line in a `-U0`
    unified diff -- sign is '+' or '-', body has the marker stripped. Diff
    metadata (`diff --git`, `@@ ...`, and the `+++`/`---` file headers,
    which also start with `+`/`-`) is excluded."""
    for line in diff_text.splitlines():
        if line.startswith("+++ ") or line.startswith("--- "):
            continue
        if line.startswith("diff --git") or line.startswith("@@") or line.startswith("index "):
            continue
        if line.startswith("+"):
            yield "+", line[1:]
        elif line.startswith("-"):
            yield "-", line[1:]


def renamed_symtab_entries(diff_text: str) -> list[tuple[str, str, str]]:
    """[(old_name, new_name, addr)] for every address whose symtab entry's
    NAME changed between the removed and added side of this diff.

    An address that only appears on the added side (a brand new entry) or
    whose name is identical on both sides (only the address literal's
    formatting, or an unrelated part of the line, changed) is not a
    rename and is not reported. Nor is the same name's address value
    changing -- that has no bearing on the alias convention.
    """
    removed_by_addr: dict[str, str] = {}
    added_by_addr: dict[str, str] = {}
    for sign, body in _plusminus_lines(diff_text):
        m = _SYM_LINE_RE.match(body)
        if not m:
            continue
        addr = m.group("addr").lower()
        name = m.group("name")
        target = removed_by_addr if sign == "-" else added_by_addr
        target.setdefault(addr, name)

    renames = []
    for addr, old_name in removed_by_addr.items():
        new_name = added_by_addr.get(addr)
        if new_name is not None and new_name != old_name:
            renames.append((old_name, new_name, addr))
    return renames


def added_alias_pairs(diff_text: str) -> set[tuple[str, str]]:
    """{(lhs, rhs)} for every bare alias line ADDED by this diff."""
    pairs = set()
    for sign, body in _plusminus_lines(diff_text):
        if sign != "+":
            continue
        m = _ALIAS_LINE_RE.match(body)
        if m:
            pairs.add((m.group("lhs"), m.group("rhs")))
    return pairs


def check_diff(repo_root: Path, *, staged: bool = True) -> list[tuple[str, str, str]]:
    """Return the [(old, new, addr)] renames in this diff that have no
    matching `<old> = <new>;` line added to aliases.ld in the same diff."""
    symtab_diff = _file_diff(repo_root, SYMTAB_PATH, staged=staged)
    renames = renamed_symtab_entries(symtab_diff)
    if not renames:
        return []
    aliases_diff = _file_diff(repo_root, ALIASES_LD_PATH, staged=staged)
    added = added_alias_pairs(aliases_diff)
    return [(old, new, addr) for old, new, addr in renames if (old, new) not in added]


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "--staged", action="store_true", help="check the staged diff (the pre-commit hook's use)"
    )
    parser.add_argument("--repo-root", type=Path, default=REPO_ROOT)
    args = parser.parse_args(argv)

    if os.environ.get("ALIAS_RENAME_SKIP") == "1":
        print("check_alias_rename: ALIAS_RENAME_SKIP=1 set, bypassing", file=sys.stderr)
        return 0

    if not args.staged:
        parser.error("pass --staged (the only supported mode)")

    try:
        missing = check_diff(args.repo_root, staged=True)
    except RuntimeError as error:
        print(f"check_alias_rename: {error}", file=sys.stderr)
        return 1

    if not missing:
        return 0

    plural = "ies" if len(missing) != 1 else "y"
    print(
        f"check_alias_rename: this commit renames the following address-keyed "
        f"entr{plural} in {SYMTAB_PATH} without adding a matching compatibility "
        f"alias to {ALIASES_LD_PATH}:",
        file=sys.stderr,
    )
    for old, new, addr in missing:
        print(f"  {old} -> {new}  (at {addr})", file=sys.stderr)
    print(
        "\nRenaming an address-keyed entry in place breaks the link for any other "
        "checkout, container, or stale extracted asm tree that still references "
        "the old name by relocation (see PR #58/#59). Leave the symtab entry "
        "unchanged and append \"<old> = <new>;\" to "
        f"{ALIASES_LD_PATH} instead, alongside the actual C rename.\n"
        "tools/container_merge.py's merge() (see append_name_alias) is the tool "
        "that does this correctly for a container-matched owner; "
        "tools/name_decompiled.py apply now does the same by default (pass "
        "--hard-rename only if a true symtab hard rename is genuinely wanted, "
        "and add the alias yourself in that case). Set ALIAS_RENAME_SKIP=1 to "
        "bypass with justification.",
        file=sys.stderr,
    )
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
