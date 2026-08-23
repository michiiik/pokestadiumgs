#!/usr/bin/env python3
"""Find candidate dispatch tables (jump tables and function-pointer tables) in
the Stadium 2 ROM's data segments and resolve their entries against the symbol
table.

Why whole tables: experience from the sister project's naming pass is that
naming functions reached through a dispatch table one body at a time produced
four wrong names out of five -- the individual bodies are often tiny stubs that
all look alike.  A table, read as a unit, gives the real structure (number of
states/commands, ordering, siblings), so the audit unit is the table, not the
entry.  This tool only surveys: it renames nothing and writes nothing.

Two table classes are reported:

  jtbl       switch-statement jump table.  Heuristic: the table sits in a
             rodata subsegment (splat places compiler jump tables next to the
             code that uses them), or a jtbl_ symbol in the code symbol table
             points exactly at the run start.
  proctable  runtime function-pointer dispatch table.  Heuristic: the table
             sits in a data subsegment.

A candidate table is a maximal run of >= N (default 4) aligned big-endian
32-bit words, inside one data/rodata subsegment, where every word is exactly
the vram of a function-start symbol from symbol_addrs_code.txt.

Usage:

    python3 tools/find_dispatch_tables.py                # full dump
    python3 tools/find_dispatch_tables.py --summary      # one line per table
    python3 tools/find_dispatch_tables.py --min 6        # longer runs only
"""
import argparse
import bisect
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import xmatch_stadium1 as X

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ROM_PATH = os.path.join(ROOT, "disasm", "baseroms", "us", "baserom.z64")
YAML_PATHS = [os.path.join(ROOT, "disasm", "yamls", "us", "rom.yaml")]
LD_DIR = os.path.join(ROOT, "disasm", "linker_scripts", "us")
CODE_SYMS = [os.path.join(LD_DIR, "symbol_addrs_code.txt")]
DATA_SYMS = [os.path.join(LD_DIR, "symbol_addrs.txt")]

SYMLINE = re.compile(
    r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")


def parse_all_syms(paths):
    """vram -> name for every symbol in the files, regardless of type."""
    out = {}
    for path in paths:
        if not os.path.exists(path):
            continue
        for line in open(path, encoding="utf-8", errors="replace"):
            m = SYMLINE.match(line)
            if m:
                out[int(m.group(2), 0)] = m.group(1)
    return out


def data_rodata_ranges(subs, rom_size):
    """[(rom_lo, rom_hi, kind)] for every data/rodata subsegment."""
    out = []
    for i, (off, kind) in enumerate(subs):
        if kind not in ("data", "rodata"):
            continue
        end = subs[i + 1][0] if i + 1 < len(subs) else rom_size
        end = min(end, rom_size)
        if end > off:
            out.append((off, end, kind))
    return out


def find_tables(rom, ranges, func_vrams, vmap, min_run):
    """Scan for maximal runs of words that are all function-start vrams."""
    tables = []
    for lo, hi, kind in ranges:
        lo4 = (lo + 3) & ~3
        run_start = None
        off = lo4
        while off + 4 <= hi:
            (w,) = struct.unpack(">I", rom[off:off + 4])
            if w in func_vrams:
                if run_start is None:
                    run_start = off
            else:
                if run_start is not None and (off - run_start) // 4 >= min_run:
                    tables.append((run_start, off, kind))
                run_start = None
            off += 4
        if run_start is not None and (hi - run_start) // 4 >= min_run:
            tables.append((run_start, hi & ~3, kind))
    return tables


def classify(kind, vram, jtbl_vrams):
    if vram in jtbl_vrams or kind == "rodata":
        return "jtbl"
    return "proctable"


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--summary", action="store_true",
                    help="one line per table instead of a full entry dump")
    ap.add_argument("--min", type=int, default=4, metavar="N",
                    help="minimum run length in entries (default 4)")
    a = ap.parse_args()

    rom = open(ROM_PATH, "rb").read()
    vmap = X.build_vram_map(X.parse_segments(YAML_PATHS))
    subs = X.parse_subsegments(YAML_PATHS)
    funcs = X.parse_syms(CODE_SYMS)
    func_vrams = set(funcs.values())
    by_vram = {}
    for name, vram in funcs.items():
        # Prefer the meaningful name if two symbols share one address.
        if vram not in by_vram or not X.is_named(by_vram[vram]):
            by_vram[vram] = name
    data_syms = parse_all_syms(DATA_SYMS + CODE_SYMS)
    data_addrs = sorted(data_syms)
    jtbl_vrams = {v for n, v in funcs.items() if n.startswith("jtbl_")}

    ranges = data_rodata_ranges(subs, len(rom))
    print(f"{len(ranges)} data/rodata subsegments, "
          f"{sum(h - l for l, h, _ in ranges)} bytes, "
          f"{len(func_vrams)} function vrams", file=sys.stderr)

    tables = find_tables(rom, ranges, func_vrams, vmap, a.min)
    print(f"{len(tables)} candidate tables (>= {a.min} entries)", file=sys.stderr)

    total_named = total_entries = 0
    hist = {}
    for rom_lo, rom_hi, kind in tables:
        n = (rom_hi - rom_lo) // 4
        words = struct.unpack(f">{n}I", rom[rom_lo:rom_hi])
        names = [by_vram[w] for w in words]
        named = sum(1 for x in names if X.is_named(x))
        total_named += named
        total_entries += n
        hist[n] = hist.get(n, 0) + 1
        _, segname = None, None
        for vlo, vhi, rlo, sname in vmap:
            if rlo <= rom_lo < vhi - vlo + rlo:
                vram = vlo + (rom_lo - rlo)
                segname = sname
                break
        else:
            vram, segname = 0, "?"
        cls = classify(kind, vram, jtbl_vrams)
        # Nearest preceding data symbol within 0x40 bytes.
        i = bisect.bisect_right(data_addrs, vram) - 1
        pre = ""
        if i >= 0 and vram - data_addrs[i] <= 0x40:
            pre = f" after {data_syms[data_addrs[i]]}"
        if a.summary:
            print(f"{cls:<9} {segname:<24} vram 0x{vram:08X} len {n:<4} "
                  f"named {named}/{n}{pre}")
        else:
            print(f"\n== {cls} table in segment {segname} "
                  f"(rom 0x{rom_lo:X}, vram 0x{vram:08X}), "
                  f"{n} entries, {named} named{pre} ==")
            for j, (w, name) in enumerate(zip(words, names)):
                print(f"  [{j:3}] 0x{w:08X} {name}")

    print(f"\n{len(tables)} tables, {total_entries} entries, "
          f"{total_named} ({total_named * 100 // max(total_entries, 1)}%) "
          f"resolve to already-named functions", file=sys.stderr)
    print("size distribution (len: count): " + ", ".join(
        f"{k}:{hist[k]}" for k in sorted(hist)), file=sys.stderr)


if __name__ == "__main__":
    main()
