#!/usr/bin/env python3
"""Map unnamed functions to their subsystem by way of the call graph.

Phase 1 of the naming pass named 763 functions.  Those names are anchors:
an unnamed function's callers and callees among the named set are the
cheapest evidence for what it does and which subsystem it belongs to.
This tool buckets every function by translation unit (the
`#pragma GLOBAL_ASM("asm/us/nonmatchings/<tu>/<symbol>.s")` path in
`disasm/src`) and reports, for each unnamed function, the named functions
it calls and the named functions that call it.

Read-only: it touches nothing outside this report.

    python3 tools/subsystem_map.py                    # full report to stdout
    python3 tools/subsystem_map.py --summary          # only the TU table
    python3 tools/subsystem_map.py --tu fragments/79/fragment79_3C60B0

Evidence standard: a call edge is a `jal` whose target is another
function's entry point -- certain.  Grouping by TU is certain (the pragma
path).  The *interpretation* of these lists still requires human review;
this is a triage aid, not a naming source.
"""
import argparse
import collections
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import xmatch_stadium1 as X

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

PRAGMA = re.compile(r'GLOBAL_ASM\("asm/us/nonmatchings/([^"]+)/([^"]+)\.s"\)')


def symbol_tus(src_dir, candidates):
    """symbol -> translation unit, from the checked-in pragma paths.

    A function with a C body instead of a stub has no pragma; its TU is the
    .c file that defines it, tagged "(C)".
    """
    out, texts = {}, []
    for dirpath, _, names in os.walk(src_dir):
        for n in names:
            if not n.endswith(".c"):
                continue
            path = os.path.join(dirpath, n)
            text = open(path, encoding="utf-8", errors="replace").read()
            texts.append((os.path.relpath(path, src_dir), text))
            for m in PRAGMA.finditer(text):
                out[m.group(2)] = m.group(1)
    for sym in candidates:
        if sym in out:
            continue
        for rel, text in texts:
            # Cheap definition heuristic: the symbol followed by "(" anywhere
            # in a file that has no pragma for it.  Only ~64 C bodies exist,
            # so a false positive costs nothing but a wrong TU tag.
            if sym + "(" in text:
                out[sym] = rel + " (C)"
                break
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--summary", action="store_true",
                    help="print only the TU table")
    ap.add_argument("--tu", metavar="NAME",
                    help="print only the section for this translation unit")
    a = ap.parse_args()

    rom = os.path.join(ROOT, "disasm", "baseroms", "us", "baserom.z64")
    funcs = X.load_functions(
        rom,
        [os.path.join(ROOT, "disasm", "yamls", "us", "rom.yaml")],
        [os.path.join(ROOT, "disasm", "linker_scripts", "us", f)
         for f in ("symbol_addrs_code.txt", "symbol_addrs_ultralib.txt")],
        "GS", src_dir=os.path.join(ROOT, "disasm", "src"))

    tus = symbol_tus(os.path.join(ROOT, "disasm", "src"), set(funcs))
    unmapped = sum(1 for n in funcs if n not in tus)
    print(f"TU map: {len(tus)} symbols with a pragma TU, "
          f"{unmapped} loaded functions without one", file=sys.stderr)

    # Call graph over function entry points.
    by_vram = {f["vram"]: n for n, f in funcs.items()}
    callees = {}   # A -> Counter of B (A calls B)
    callers = {}   # B -> Counter of A
    for n, f in funcs.items():
        for tv in X.call_targets(f):
            t = by_vram.get(tv)
            if t and t != n:
                callees.setdefault(n, collections.Counter())[t] += 1
                callers.setdefault(t, collections.Counter())[n] += 1
    print(f"call graph: {sum(sum(c.values()) for c in callees.values())} jal edges",
          file=sys.stderr)

    # Bucket by TU.
    tu_named = collections.defaultdict(list)
    tu_unnamed = collections.defaultdict(list)
    for n in funcs:
        tu = tus.get(n, "(unknown)")
        (tu_named if X.is_named(n) else tu_unnamed)[tu].append(n)

    rows = sorted(tu_named, key=lambda t: -len(tu_named[t]))
    if not rows:
        sys.exit("no named functions found -- is the tree renamed?")

    print("# Subsystem map: unnamed functions and their named neighbours\n")
    print("| Translation unit | named | unnamed |")
    print("|---|---|---|")
    for tu in rows:
        print(f"| `{tu}` | {len(tu_named[tu])} | {len(tu_unnamed[tu])} |")
    unknown = tu_unnamed.get("(unknown)", [])
    if unknown:
        print(f"| `(unknown, no pragma)` | 0 | {len(unknown)} |")

    if a.summary:
        return

    for tu in rows:
        named, unnamed = tu_named[tu], tu_unnamed[tu]
        if a.tu and tu != a.tu:
            continue
        if not unnamed:
            continue
        print(f"\n## `{tu}` -- {len(named)} named anchors, "
              f"{len(unnamed)} unnamed\n")
        # Most-connected first: the easiest names come first.
        def score(fn):
            return sum(v for c, v in callees.get(fn, {}).items()
                       if X.is_named(c)) + \
                   sum(v for c, v in callers.get(fn, {}).items()
                       if X.is_named(c))
        for fn in sorted(unnamed, key=lambda f: (-score(f), f)):
            calls = sorted(((c, v) for c, v in callees.get(fn, {}).items()
                            if X.is_named(c)), key=lambda x: -x[1])
            by = sorted(((c, v) for c, v in callers.get(fn, {}).items()
                         if X.is_named(c)), key=lambda x: -x[1])
            parts = []
            if calls:
                parts.append("calls " + ", ".join(
                    f"`{c}`" + (f" x{v}" if v > 1 else "") for c, v in calls))
            if by:
                parts.append("called by " + ", ".join(
                    f"`{c}`" + (f" x{v}" if v > 1 else "") for c, v in by))
            print(f"- `{fn}`" + (" -- " + "; ".join(parts) if parts else
                                   " -- no named neighbours"))


if __name__ == "__main__":
    main()
