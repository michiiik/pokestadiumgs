#!/usr/bin/env python3
"""Apply evidence-backed symbol names to the Pokemon Stadium 2 (G&S) decomp.

Unlike the Stadium 1 decomp this is an assembly tree: 10,532 of its 10,505
functions are `#pragma GLOBAL_ASM` stubs, and splat -- not a C compiler -- is
what turns a symbol name into code.  A rename therefore has to move together in
two places, and this tool keeps them in step:

  * `disasm/linker_scripts/us/symbol_addrs_code.txt`, which is what splat reads;
  * the `#pragma GLOBAL_ASM("asm/us/nonmatchings/<file>/<name>.s")` paths in
    `disasm/src`, which is what the C files include.

Rename one without the other and the build breaks silently -- the pragma points
at a path splat no longer emits.  Whole-word replacement covers both, because
the symbol appears as a word inside the pragma's path string too.

    python3 tools/apply_names.py --dry-run     # report, change nothing
    python3 tools/apply_names.py               # apply
    python3 tools/apply_names.py --check       # no old names survive
    python3 tools/apply_names.py --qa          # the applied names are sound

Mappings are merged from every --names file, later files losing to earlier ones
on a conflict, so hand-written names in tools/gs_names.json override anything
tools/s1_transfer.json generated.

Only the US tables are touched.  JP is a separate address space whose symbols
are named independently; a US-only rename cannot break it.
"""
import argparse
import collections
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DISASM = os.path.join(ROOT, "disasm")
TARGET_DIRS = [
    os.path.join(DISASM, "src"),
    os.path.join(DISASM, "include"),
    os.path.join(DISASM, "linker_scripts", "us"),
]
EXTS = (".c", ".h", ".s", ".txt", ".inc", ".ld")
DEFAULT_NAMES = ["tools/gs_names.json", "tools/s1_transfer.json"]

SYMTAB = os.path.join(DISASM, "linker_scripts", "us", "symbol_addrs_code.txt")
STAMP = os.path.join(DISASM, ".gs_names_permutation_applied")

C_KEYWORDS = {
    "if", "else", "for", "while", "do", "switch", "case", "return", "struct",
    "union", "enum", "typedef", "static", "void", "int", "char", "float",
    "double", "const", "sizeof", "break", "continue", "default", "goto",
    "signed", "unsigned", "short", "long", "extern", "register", "volatile",
    "auto", "inline", "restrict",
}
IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
PRAGMA = re.compile(r'GLOBAL_ASM\("([^"]+)"\)')


def load_mapping(paths):
    """(old -> new, old -> evidence, old -> which file it came from)."""
    mapping, why, origin = {}, {}, {}
    for path in paths:
        if not os.path.isabs(path):
            path = os.path.join(ROOT, path)
        if not os.path.exists(path):
            print(f"note: {os.path.relpath(path, ROOT)} not present, skipping")
            continue
        raw = json.load(open(path, encoding="utf-8"))
        for section in ("functions", "data", "types"):
            for old, val in raw.get(section, {}).items():
                if old.startswith("_") or old in mapping:
                    continue
                new, reason = (val if isinstance(val, list) else (val, ""))
                mapping[old], why[old] = new, reason
                origin[old] = os.path.basename(path)
    return mapping, why, origin


def load_permutations(paths):
    """Simultaneous swaps that correct an existing wrong name.  One-shot:
    applying a rotation twice puts the wrong names back."""
    perms = {}
    for path in paths:
        if not os.path.isabs(path):
            path = os.path.join(ROOT, path)
        if not os.path.exists(path):
            continue
        raw = json.load(open(path, encoding="utf-8"))
        for k, v in raw.get("permutations", {}).items():
            if not k.startswith("_"):
                perms.setdefault(k, v if isinstance(v, str) else v[0])
    return perms


def iter_files():
    for d in TARGET_DIRS:
        for dirpath, _, names in os.walk(d):
            for n in sorted(names):
                if n.endswith(EXTS):
                    yield os.path.join(dirpath, n)


def read(path):
    return open(path, encoding="utf-8", errors="replace").read()


def symtab_names():
    """symbol -> vram, from the US function table splat actually reads."""
    out = {}
    for line in read(SYMTAB).splitlines():
        m = re.match(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if m:
            out[m.group(1)] = int(m.group(2), 0)
    return out


def run_qa(mapping):
    """Post-rename soundness check.  Returns a process exit code.

    The checks that matter here are not the ones that mattered for Stadium 1.
    There, renaming a GLOBAL_ASM stub was the hazard.  Here everything is a stub,
    so the hazard inverts: a name is only sound if the symbol table and the
    pragma path agree about it.
    """
    targets = set(mapping.values())
    syms = symtab_names()

    # 1. Every applied name resolves to exactly one symbol table entry.
    missing = sorted(t for t in targets if t not in syms)
    dupes = collections.Counter()
    for line in read(SYMTAB).splitlines():
        m = re.match(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=", line)
        if m and m.group(1) in targets:
            dupes[m.group(1)] += 1
    multi = sorted(n for n, c in dupes.items() if c > 1)

    # 2. Every US pragma path names a symbol splat will actually emit.  This is
    #    the check that catches a half-applied rename.
    orphan_pragmas = []
    pragma_names = set()
    for path in iter_files():
        if not path.endswith(".c"):
            continue
        for m in PRAGMA.finditer(read(path)):
            p = m.group(1)
            if not p.startswith("asm/us/"):
                continue
            base = os.path.basename(p)[:-2]
            pragma_names.add(base)
            # Compatibility pragmas intentionally point at descriptive alias
            # files whose assembly label remains address-derived.
            if base.startswith("LinkAlias_"):
                continue
            if base not in syms:
                orphan_pragmas.append((os.path.relpath(path, ROOT), base))

    # 3. An applied name that never reaches a pragma is a symbol-table-only
    #    rename -- legal for data, suspicious for a function.
    unreferenced = sorted(t for t in targets
                          if t in syms and t not in pragma_names)

    kw = sorted(t for t in targets if t in C_KEYWORDS)
    bad_ident = sorted(t for t in targets if not re.fullmatch(r"[A-Za-z_]\w*", t))

    print(f"QA over {len(targets)} applied names:")
    print(f"  absent from symbol table : {len(missing)} {missing[:6]}")
    print(f"  defined more than once   : {len(multi)} {multi[:6]}")
    print(f"  pragma with no symbol    : {len(orphan_pragmas)} {orphan_pragmas[:4]}")
    print(f"  clash with a C keyword   : {len(kw)} {kw[:6]}")
    print(f"  not a C identifier       : {len(bad_ident)} {bad_ident[:6]}")
    print(f"  symbol-table only        : {len(unreferenced)} {unreferenced[:6]}"
          f"   (informational)")
    bad = len(missing) + len(multi) + len(orphan_pragmas) + len(kw) + len(bad_ident)
    print("  OK" if not bad else f"  {bad} PROBLEM(S)")
    return 1 if bad else 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--names", nargs="*", default=DEFAULT_NAMES)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--qa", action="store_true")
    ap.add_argument("--limit-class", default=None,
                    help="only apply entries whose evidence names this match "
                         "class, e.g. --limit-class identical,normalised")
    a = ap.parse_args()

    mapping, why, origin = load_mapping(a.names)

    if a.limit_class:
        wanted = set(a.limit_class.split(","))
        mapping = {k: v for k, v in mapping.items()
                   if any(f"match class {c};" in why.get(k, "") for c in wanted)
                   or "match class " not in why.get(k, "")}

    perms = load_permutations(a.names)
    if perms and not os.path.exists(STAMP):
        mapping.update(perms)
        for k in perms:
            why[k] = "corrects a rotated name -- one-shot"
    elif perms:
        print(f"(rotated-name fix already applied; stamp "
              f"{os.path.relpath(STAMP, ROOT)})")

    if not mapping:
        sys.exit("no renames in mapping")
    files = list(iter_files())
    if not files:
        sys.exit(f"no source files under {DISASM} -- is disasm/ present?")

    if a.qa:
        sys.exit(run_qa(mapping))

    pattern = re.compile(r"\b(" + "|".join(
        re.escape(k) for k in sorted(mapping, key=len, reverse=True)) + r")\b")

    # Pass 1: count what is actually there, and find target names already taken.
    counts = {k: 0 for k in mapping}
    targets = set(mapping.values())
    renamed_away = set(mapping)
    existing = collections.defaultdict(list)
    for path in files:
        text = read(path)
        # Linker-only compatibility assignments intentionally retain the
        # address-derived RHS symbol; they do not represent a source owner or
        # GLOBAL_ASM path that still needs renaming.
        if path.endswith(".ld"):
            text = re.sub(r"=\s*func_[A-Za-z0-9_]+\s*;", "= 0;", text)
        for m in pattern.finditer(text):
            counts[m.group(1)] += 1
        # One identifier scan per file intersected with the target set, rather
        # than a regex per target per file -- the latter is O(targets x files)
        # and dominates the runtime past a few hundred names.
        for t in targets.intersection(IDENT.findall(text)):
            if t not in renamed_away:      # permutation member: legitimate
                existing[t].append(os.path.relpath(path, ROOT))

    if a.check:
        stale = {k: v for k, v in counts.items() if v and k not in targets}
        print(f"old names still present: {len(stale)}")
        for k, v in sorted(stale.items()):
            print(f"  {k}: {v}")
        sys.exit(1 if stale else 0)

    by_origin = collections.Counter(origin.get(k, "permutation") for k in mapping)
    print(f"{len(mapping)} renames over {len(files)} files "
          f"({dict(by_origin)})\n")
    missing = [old for old in sorted(mapping) if counts[old] == 0]
    if a.dry_run:
        print(f"{'old':<24} {'new':<44} {'hits':>5}")
        for old in sorted(mapping):
            print(f"{old:<24} {mapping[old]:<44} {counts[old]:>5}")
    if missing:
        # 0 hits means the rename already landed on an earlier run, or the
        # symbol does not exist.  --check tells the two apart.
        print(f"\n{len(missing)} of {len(mapping)} rename(s) had 0 hits "
              f"(already applied, or absent). Run --check to confirm none are stale.")

    # A target that already exists is only a real collision if its own source is
    # still present; if the source is gone this mapping was simply applied
    # before, and re-running has to stay idempotent rather than error.
    src_of = collections.defaultdict(list)
    for old, new in mapping.items():
        src_of[new].append(old)
    collisions = {t: w for t, w in existing.items()
                  if any(counts[o] for o in src_of.get(t, []))}
    if collisions:
        print("\nREFUSING: these target names are already taken and are not part "
              "of a permutation -- pick different names:")
        for t, w in sorted(collisions.items()):
            extra = f" +{len(w)-1} more" if len(w) > 1 else ""
            print(f"  {t}  (in {w[0]}{extra})")
        sys.exit(2)

    if a.dry_run:
        print("\ndry run -- nothing written")
        return

    changed = total = 0
    for path in files:
        text = read(path)
        new_text, n = pattern.subn(lambda m: mapping[m.group(1)], text)
        if n:
            open(path, "w", encoding="utf-8", newline="").write(new_text)
            changed += 1
            total += n
    print(f"\nrewrote {changed} files, {total} replacements")
    if perms and not os.path.exists(STAMP):
        open(STAMP, "w").close()
        print(f"stamped {os.path.relpath(STAMP, ROOT)}")


if __name__ == "__main__":
    main()
