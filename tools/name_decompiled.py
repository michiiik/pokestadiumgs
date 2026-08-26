#!/usr/bin/env python3
"""Apply evidence-backed names at the moment a function becomes decompiled.

`tools/apply_names.py` renames any symbol its mapping files know about,
whether or not the symbol still owns a `#pragma GLOBAL_ASM` stub.  That is
fine for the historical bulk transfer, but the day-to-day workflow is the
opposite problem: `tools/s1_transfer.json` and `tools/gs_names.json` between
them carry hundreds of evidence-backed names for functions that have since
been decompiled to C -- and are still called `func_XXXXXXXX`, because nobody
renamed them *at the moment they were decompiled* (see DECOMP_SETUP.md,
"Renaming a function symbol deletes its assembly": renaming a symbol that
still owns a pragma breaks the build, so it never happens automatically).

This tool closes that specific gap.  A function is in scope only when all
three hold:

  * it has a name in `tools/gs_names.json` or `tools/s1_transfer.json`;
  * it has NO `#pragma GLOBAL_ASM` owner anywhere under `disasm/src` (i.e. a
    real C body exists for it -- it is decompiled);
  * it is still named `func_XXXXXXXX` in
    `disasm/linker_scripts/us/symbol_addrs_code.txt`.

Unlike `apply_names.py`, a rename here also has to reach the standalone
`disasm/asm/us/**/*.s` tree: those files are not regenerated from the
symbol table automatically, so a `jal func_X`/`%hi(func_X)`/`.word func_X`
reference in another translation unit's still-`GLOBAL_ASM` assembly would
otherwise go stale and fail to link.

    python3 tools/name_decompiled.py plan
    python3 tools/name_decompiled.py apply --dry-run
    python3 tools/name_decompiled.py apply --only func_80001234,func_80005678
    python3 tools/name_decompiled.py apply --verify
    python3 tools/name_decompiled.py debt

Library API for a runner to call right after a batch installs accepted
owners: `name_after_accept(functions) -> list[(old, new)]`.  See
`tools/try_pragma_compare.py`'s `PRAGMA_NAME_ON_ACCEPT` opt-in call site.

`naming_debt(repo_root, revision)` computes the same named/unnamed-decompiled
counts as `plan`, but against a committed git revision (like
`update_coverage.py`'s `committed_counts`) rather than the working tree, so a
future coverage report can fold it in without racing concurrent MCP edits.
"""
from __future__ import annotations

import argparse
import collections
import datetime
import json
import os
import re
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DEFAULT_NAMES_FILES = ["tools/gs_names.json", "tools/s1_transfer.json"]

FUNC_RE = re.compile(r"\bfunc_[0-9A-Fa-f]{6,8}\b")
FULL_FUNC_RE = re.compile(r"^func_[0-9A-Fa-f]{6,8}$")
# Only US pragma paths are in scope (docs/NAMING.md: "US tables only"); a JP
# path uses a different address space and is named independently.
PRAGMA_RE = re.compile(r'GLOBAL_ASM\("(asm/us/[^"]+)"\)')
SYM_LINE_RE = re.compile(
    r"^(?P<indent>\s*)(?P<name>[A-Za-z_]\w*)(?P<eq>\s*=\s*)"
    r"(?P<addr>0x[0-9A-Fa-f]+)(?P<semi>\s*;)(?P<rest>.*)$"
)
# The DECOMP_SETUP.md convention for recording an intended name ahead of the
# rename itself: `func_X = 0x...; // type:func ProposedName`.
TYPE_FUNC_NAME_RE = re.compile(r"^(\s*//\s*type:func)(\s+)([A-Za-z_]\w*)\s*$")
SRC_EXTS = (".c", ".h", ".inc")


def _default_paths(repo_root: Path):
    disasm = repo_root / "disasm"
    return {
        "src_dir": disasm / "src",
        "include_dir": disasm / "include",
        "symtab_path": disasm / "linker_scripts" / "us" / "symbol_addrs_code.txt",
        "linker_us_dir": disasm / "linker_scripts" / "us",
        "asm_root": disasm / "asm" / "us",
        "renames_log": disasm / "probe-stats" / "renames.jsonl",
    }


# --------------------------------------------------------------------------
# Name mapping (tools/gs_names.json, tools/s1_transfer.json)
# --------------------------------------------------------------------------

def load_names(paths, repo_root: Path):
    """(old -> new, old -> evidence, old -> origin file), functions section
    only.  Earlier files win a conflict, mirroring apply_names.py so that
    tools/gs_names.json (hand-written) overrides tools/s1_transfer.json
    (machine-transferred) when both name the same function."""
    mapping, why, origin = {}, {}, {}
    for raw_path in paths:
        p = Path(raw_path)
        if not p.is_absolute():
            p = repo_root / p
        if not p.exists():
            continue
        data = json.loads(p.read_text(encoding="utf-8"))
        for old, val in data.get("functions", {}).items():
            if old.startswith("_") or old in mapping:
                continue
            if isinstance(val, list):
                new = val[0]
                reason = val[1] if len(val) > 1 else ""
            else:
                new, reason = val, ""
            mapping[old] = new
            why[old] = reason
            origin[old] = p.name
    return mapping, why, origin


# --------------------------------------------------------------------------
# Source-tree analysis: pragma owners and real C definitions
# --------------------------------------------------------------------------

def _strip_string_literals(text: str) -> str:
    """Blank out the contents of "..." string literals (same length), so a
    GLOBAL_ASM path's basename does not get mistaken for a C definition or
    call site of the function it names."""
    out = []
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == '"':
            out.append(" ")
            i += 1
            while i < n and text[i] != '"':
                if text[i] == "\\" and i + 1 < n:
                    out.append("  ")
                    i += 2
                    continue
                out.append(" ")
                i += 1
            if i < n:
                out.append(" ")
                i += 1
            continue
        out.append(c)
        i += 1
    return "".join(out)


def _definitions_in_text(text: str) -> set:
    """Names that are real C function definitions in this text: a func_
    identifier directly followed by a balanced (...) parameter list and then
    an opening `{`.  A prototype/extern (followed by `;`) or a call site
    (also followed by `;`, but preceded by other code) does not count."""
    stripped = _strip_string_literals(text)
    defs = set()
    for m in FUNC_RE.finditer(stripped):
        name = m.group(0)
        j = m.end()
        while j < len(stripped) and stripped[j].isspace():
            j += 1
        if j >= len(stripped) or stripped[j] != "(":
            continue
        depth = 0
        while j < len(stripped):
            if stripped[j] == "(":
                depth += 1
            elif stripped[j] == ")":
                depth -= 1
                if depth == 0:
                    j += 1
                    break
            j += 1
        while j < len(stripped) and stripped[j].isspace():
            j += 1
        if j < len(stripped) and stripped[j] == "{":
            defs.add(name)
    return defs


def _iter_files(root: Path, suffixes):
    if not root.exists():
        return
    for p in sorted(root.rglob("*")):
        if p.is_file() and p.suffix in suffixes:
            yield p


def analyze_source_tree(src_dir: Path):
    """(pragma_owned: set[str], definitions: dict[str, list[Path]]) over
    every .c file under src_dir, read from the filesystem."""
    pragma_owned = set()
    definitions = collections.defaultdict(list)
    for path in _iter_files(src_dir, (".c",)):
        text = path.read_text(encoding="utf-8", errors="replace")
        for m in PRAGMA_RE.finditer(text):
            pragma_owned.add(Path(m.group(1)).stem)
        for name in _definitions_in_text(text):
            definitions[name].append(path)
    return pragma_owned, dict(definitions)


def _git(repo_root: Path, *args):
    result = subprocess.run(
        ["git", "-C", str(repo_root), *args],
        check=False, capture_output=True, text=True,
    )
    return result


def analyze_source_tree_at_revision(repo_root: Path, revision: str, subdir="disasm/src"):
    """Same as analyze_source_tree, but reads the committed tree at
    ``revision`` instead of the working tree (used by naming_debt)."""
    pragma_owned = set()
    definitions = collections.defaultdict(list)
    listing = _git(repo_root, "ls-tree", "-r", "--name-only", revision, "--", subdir)
    if listing.returncode not in (0, 1):
        raise RuntimeError(listing.stderr.strip() or "git ls-tree failed")
    for relpath in listing.stdout.splitlines():
        if not relpath.endswith(".c"):
            continue
        shown = _git(repo_root, "show", f"{revision}:{relpath}")
        if shown.returncode != 0:
            continue
        text = shown.stdout
        for m in PRAGMA_RE.finditer(text):
            pragma_owned.add(Path(m.group(1)).stem)
        for name in _definitions_in_text(text):
            definitions[name].append(Path(relpath))
    return pragma_owned, dict(definitions)


# --------------------------------------------------------------------------
# symbol_addrs_code.txt
# --------------------------------------------------------------------------

def still_func_named(symtab_path: Path) -> set:
    names = set()
    if not symtab_path.exists():
        return names
    for line in symtab_path.read_text(encoding="utf-8", errors="replace").splitlines():
        m = SYM_LINE_RE.match(line)
        if m and FULL_FUNC_RE.match(m.group("name")):
            names.add(m.group("name"))
    return names


def still_func_named_at_revision(repo_root: Path, revision: str,
                                  relpath="disasm/linker_scripts/us/symbol_addrs_code.txt") -> set:
    names = set()
    shown = _git(repo_root, "show", f"{revision}:{relpath}")
    if shown.returncode != 0:
        return names
    for line in shown.stdout.splitlines():
        m = SYM_LINE_RE.match(line)
        if m and FULL_FUNC_RE.match(m.group("name")):
            names.add(m.group("name"))
    return names


def existing_symbol_names(linker_us_dir: Path) -> set:
    names = set()
    if not linker_us_dir.exists():
        return names
    for path in sorted(linker_us_dir.glob("symbol_addrs*.txt")):
        for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
            m = SYM_LINE_RE.match(line)
            if m:
                names.add(m.group("name"))
    return names


IDENT_RE = re.compile(r"[A-Za-z_]\w*")


def build_identifier_index(*dirs_and_suffixes) -> set:
    """All identifier-shaped tokens across the given (dir, suffixes) pairs.
    Used for the C-identifier half of collision detection; a bare text scan
    is deliberately generous (it also catches names only used inside a
    string literal, e.g. another pragma path) since a false-positive refusal
    is much cheaper than a silent collision."""
    idents = set()
    for root, suffixes in dirs_and_suffixes:
        for path in _iter_files(Path(root), suffixes):
            idents.update(IDENT_RE.findall(path.read_text(encoding="utf-8", errors="replace")))
    return idents


# --------------------------------------------------------------------------
# Plan
# --------------------------------------------------------------------------

@dataclass
class PlanRow:
    old: str
    new: str
    evidence: str
    origin: str
    def_file: str


@dataclass
class PlanResult:
    rows: list = field(default_factory=list)
    unnamed_decompiled: list = field(default_factory=list)
    decompiled_count: int = 0
    pragma_owned_count: int = 0
    mapping_count: int = 0


def build_plan(*, repo_root: Path = ROOT, names_files=None, src_dir=None,
                symtab_path=None) -> PlanResult:
    repo_root = Path(repo_root)
    names_files = names_files or DEFAULT_NAMES_FILES
    defaults = _default_paths(repo_root)
    src_dir = Path(src_dir) if src_dir else defaults["src_dir"]
    symtab_path = Path(symtab_path) if symtab_path else defaults["symtab_path"]

    mapping, why, origin = load_names(names_files, repo_root)
    pragma_owned, definitions = analyze_source_tree(src_dir)
    decompiled = set(definitions) - pragma_owned
    func_named = still_func_named(symtab_path)

    rows = []
    for old in sorted(mapping):
        if old in decompiled and old in func_named:
            def_file = os.path.relpath(str(definitions[old][0]), str(repo_root))
            rows.append(PlanRow(old=old, new=mapping[old], evidence=why.get(old, ""),
                                 origin=origin.get(old, ""), def_file=def_file))

    unnamed = sorted(n for n in decompiled if n not in mapping)
    return PlanResult(rows=rows, unnamed_decompiled=unnamed,
                       decompiled_count=len(decompiled),
                       pragma_owned_count=len(pragma_owned),
                       mapping_count=len(mapping))


def print_plan(plan: PlanResult, limit=None):
    rows = plan.rows[:limit] if limit else plan.rows
    print(f"{'function':<16} {'new name':<40} {'source':<18} def file")
    for r in rows:
        print(f"{r.old:<16} {r.new:<40} {r.origin:<18} {r.def_file}")
    if limit and len(plan.rows) > limit:
        print(f"... ({len(plan.rows) - limit} more)")
    print()
    print(f"{len(plan.rows)} function(s) ready to rename "
          f"(evidence-backed, decompiled, still func_-named)")
    print(f"{plan.decompiled_count} decompiled functions total "
          f"({plan.pragma_owned_count} still have a GLOBAL_ASM owner)")
    print(f"{len(plan.unnamed_decompiled)} decompiled function(s) have no known name "
          f"(reverse coverage debt)")


# --------------------------------------------------------------------------
# Apply
# --------------------------------------------------------------------------

@dataclass
class ApplyResult:
    applied: list = field(default_factory=list)   # [(old, new)]
    refused: list = field(default_factory=list)    # [(old, new, reason)]
    symtab_lines_changed: int = 0
    src_files_changed: int = 0
    src_replacements: int = 0
    asm_files_changed: int = 0
    asm_replacements: int = 0


def _rewrite_symtab_line(line: str, old: str, new: str):
    m = SYM_LINE_RE.match(line)
    if not m or m.group("name") != old:
        return line, False
    rest = m.group("rest")
    tm = TYPE_FUNC_NAME_RE.match(rest)
    if tm and tm.group(3) == new:
        rest = tm.group(1)   # drop the now-redundant "// type:func Name"
    new_line = f'{m.group("indent")}{new}{m.group("eq")}{m.group("addr")}{m.group("semi")}{rest}'
    return new_line, True


def _whole_word_pattern(names):
    return re.compile(r"\b(" + "|".join(
        re.escape(n) for n in sorted(names, key=len, reverse=True)) + r")\b")


def _rewrite_files(paths, mapping):
    if not mapping:
        return 0, 0
    pattern = _whole_word_pattern(mapping.keys())
    changed = total = 0
    for path in paths:
        text = path.read_text(encoding="utf-8", errors="replace")
        new_text, n = pattern.subn(lambda m: mapping[m.group(1)], text)
        if n:
            path.write_text(new_text, encoding="utf-8", newline="")
            changed += 1
            total += n
    return changed, total


def apply_plan(rows, *, repo_root: Path = ROOT, src_dir=None, include_dir=None,
                symtab_path=None, asm_root=None, renames_log=None,
                dry_run=False) -> ApplyResult:
    repo_root = Path(repo_root)
    defaults = _default_paths(repo_root)
    src_dir = Path(src_dir) if src_dir else defaults["src_dir"]
    include_dir = Path(include_dir) if include_dir else defaults["include_dir"]
    symtab_path = Path(symtab_path) if symtab_path else defaults["symtab_path"]
    linker_us_dir = symtab_path.parent
    asm_root = Path(asm_root) if asm_root else defaults["asm_root"]
    renames_log = Path(renames_log) if renames_log else defaults["renames_log"]

    result = ApplyResult()
    if not rows:
        return result

    # Collision detection: a target name already claimed by any symbol_addrs*
    # entry, or already used as a C identifier under disasm/src or
    # disasm/include.  Detected per-row so one collision does not block the
    # rest of an otherwise-clean batch.
    taken = existing_symbol_names(linker_us_dir) | build_identifier_index(
        (src_dir, SRC_EXTS), (include_dir, SRC_EXTS),
    )
    seen_new = {}
    accepted = []
    for row in rows:
        if row.new in taken:
            result.refused.append((row.old, row.new, f"{row.new!r} already exists"))
            continue
        if row.new in seen_new:
            result.refused.append(
                (row.old, row.new, f"{row.new!r} collides with {seen_new[row.new]!r} in this batch"))
            continue
        seen_new[row.new] = row.old
        accepted.append(row)

    if not accepted:
        return result

    mapping = {r.old: r.new for r in accepted}

    if dry_run:
        result.applied = [(r.old, r.new) for r in accepted]
        return result

    # 1. symbol_addrs_code.txt
    if symtab_path.exists():
        lines = symtab_path.read_text(encoding="utf-8", errors="replace").splitlines(keepends=True)
        out_lines = []
        changed = 0
        for line in lines:
            body = line[:-1] if line.endswith("\n") else line
            m = SYM_LINE_RE.match(body)
            if m and m.group("name") in mapping:
                new_body, did = _rewrite_symtab_line(body, m.group("name"), mapping[m.group("name")])
                if did:
                    changed += 1
                line = new_body + ("\n" if line.endswith("\n") else "")
            out_lines.append(line)
        if changed:
            symtab_path.write_text("".join(out_lines), encoding="utf-8", newline="")
        result.symtab_lines_changed = changed

    # 2. disasm/src/**/*.c and disasm/include/** (definitions, prototypes,
    #    externs, call sites).
    src_paths = list(_iter_files(src_dir, (".c",))) + list(_iter_files(include_dir, SRC_EXTS))
    result.src_files_changed, result.src_replacements = _rewrite_files(src_paths, mapping)

    # 3. disasm/asm/us/**/*.s (the standalone asm tree is not regenerated
    #    automatically), plus any stray .s tracked directly under disasm/src.
    asm_paths = list(_iter_files(asm_root, (".s",))) + list(_iter_files(src_dir, (".s",)))
    result.asm_files_changed, result.asm_replacements = _rewrite_files(asm_paths, mapping)

    # Log.
    renames_log.parent.mkdir(parents=True, exist_ok=True)
    now = datetime.datetime.now(datetime.timezone.utc).isoformat()
    with renames_log.open("a", encoding="utf-8") as fh:
        for r in accepted:
            fh.write(json.dumps({
                "old": r.old, "new": r.new, "evidence": r.evidence,
                "timestamp": now,
            }) + "\n")

    result.applied = [(r.old, r.new) for r in accepted]
    return result


def run_verify(repo_root: Path) -> int:
    proc = subprocess.run(["make", "-C", str(repo_root / "disasm"), "COMPARE=1"])
    return proc.returncode


# --------------------------------------------------------------------------
# Hook: call right after a batch installs accepted owners
# --------------------------------------------------------------------------

def name_after_accept(functions, *, repo_root: Path = ROOT, names_files=None,
                       quiet=True):
    """Given the function names a batch just installed C bodies for, rename
    every one of them that plan() would already pick (evidence-backed, no
    remaining pragma owner, still func_-named).  Returns the [(old, new)]
    pairs actually renamed.  Never raises for a function outside that set --
    it is simply not renamed.
    """
    repo_root = Path(repo_root)
    plan = build_plan(repo_root=repo_root, names_files=names_files)
    wanted = set(functions)
    rows = [r for r in plan.rows if r.old in wanted]
    if not rows:
        return []
    result = apply_plan(rows, repo_root=repo_root)
    if not quiet and result.applied:
        print(f"name_decompiled: renamed {len(result.applied)} function(s) after accept: "
              f"{', '.join(old + '->' + new for old, new in result.applied)}")
    if not quiet and result.refused:
        print(f"name_decompiled: refused {len(result.refused)} collision(s): "
              f"{', '.join(f'{old} -> {new} ({reason})' for old, new, reason in result.refused)}")
    return result.applied


# --------------------------------------------------------------------------
# Coverage-style debt metric (revision-based, for a future update_coverage.py
# integration -- see module docstring)
# --------------------------------------------------------------------------

def naming_debt(repo_root: Path = ROOT, revision: str = "HEAD",
                 names_files=None) -> dict:
    repo_root = Path(repo_root)
    names_files = names_files or DEFAULT_NAMES_FILES
    mapping, _why, _origin = load_names(names_files, repo_root)
    pragma_owned, definitions = analyze_source_tree_at_revision(repo_root, revision)
    decompiled = set(definitions) - pragma_owned
    func_named = still_func_named_at_revision(repo_root, revision)

    named = sorted(n for n in decompiled if n in mapping and n in func_named)
    unnamed = sorted(n for n in decompiled if n not in mapping)
    already_renamed = len(decompiled) - len(named) - len(unnamed)
    return {
        "revision": revision,
        "decompiled": len(decompiled),
        "named": len(named),                    # evidence exists, not yet applied
        "already_renamed": max(already_renamed, 0),
        "unnamed_decompiled": len(unnamed),
    }


# --------------------------------------------------------------------------
# CLI
# --------------------------------------------------------------------------

def _add_common_args(ap):
    ap.add_argument("--repo-root", type=Path, default=ROOT)
    ap.add_argument("--names", nargs="*", default=None,
                     help="override tools/gs_names.json / tools/s1_transfer.json")
    ap.add_argument("--src-dir", type=Path, default=None)
    ap.add_argument("--include-dir", type=Path, default=None)
    ap.add_argument("--symtab", type=Path, default=None)
    ap.add_argument("--asm-root", type=Path, default=None,
                     help="disasm/asm/us root; point this at another checkout's "
                          "populated tree if this worktree's disasm/asm is sparse")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                  formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="mode", required=True)

    plan_ap = sub.add_parser("plan", help="report the rename set, change nothing")
    _add_common_args(plan_ap)
    plan_ap.add_argument("--limit", type=int, default=None)
    plan_ap.add_argument("--only", default=None, help="comma-separated func_X list")

    apply_ap = sub.add_parser("apply", help="apply the rename set")
    _add_common_args(apply_ap)
    apply_ap.add_argument("--limit", type=int, default=None)
    apply_ap.add_argument("--only", default=None, help="comma-separated func_X list")
    apply_ap.add_argument("--dry-run", action="store_true")
    apply_ap.add_argument("--verify", action="store_true",
                           help="run `make -C disasm COMPARE=1` after applying")

    debt_ap = sub.add_parser("debt", help="naming_debt() against a git revision")
    debt_ap.add_argument("--repo-root", type=Path, default=ROOT)
    debt_ap.add_argument("--names", nargs="*", default=None)
    debt_ap.add_argument("--revision", default="HEAD")

    args = ap.parse_args(argv)

    if args.mode == "debt":
        debt = naming_debt(args.repo_root, args.revision, args.names)
        print(json.dumps(debt, indent=2))
        return 0

    plan = build_plan(repo_root=args.repo_root, names_files=args.names,
                       src_dir=args.src_dir, symtab_path=args.symtab)

    rows = plan.rows
    if args.only:
        wanted = set(x.strip() for x in args.only.split(",") if x.strip())
        rows = [r for r in rows if r.old in wanted]
    if args.limit:
        rows = rows[: args.limit]

    if args.mode == "plan":
        limited = PlanResult(rows=rows, unnamed_decompiled=plan.unnamed_decompiled,
                              decompiled_count=plan.decompiled_count,
                              pragma_owned_count=plan.pragma_owned_count,
                              mapping_count=plan.mapping_count)
        print_plan(limited, limit=None)
        return 0

    # apply
    result = apply_plan(rows, repo_root=args.repo_root, src_dir=args.src_dir,
                         include_dir=args.include_dir, symtab_path=args.symtab,
                         asm_root=args.asm_root, dry_run=args.dry_run)

    verb = "would rename" if args.dry_run else "renamed"
    print(f"{verb} {len(result.applied)} function(s)")
    for old, new in result.applied:
        print(f"  {old} -> {new}")
    if result.refused:
        print(f"refused {len(result.refused)} collision(s):")
        for old, new, reason in result.refused:
            print(f"  {old} -> {new}: {reason}")
    if not args.dry_run:
        print(f"symtab lines changed: {result.symtab_lines_changed}")
        print(f"src files changed: {result.src_files_changed} "
              f"({result.src_replacements} replacements)")
        print(f"asm files changed: {result.asm_files_changed} "
              f"({result.asm_replacements} replacements)")

    if args.verify and not args.dry_run:
        rc = run_verify(args.repo_root)
        print(f"COMPARE=1: {'OK' if rc == 0 else 'FAILED'} (exit {rc})")
        return rc

    return 0 if not result.refused else (0 if result.applied else 1)


if __name__ == "__main__":
    sys.exit(main())
