#!/usr/bin/env python3
"""
add_rodata_subsegments.py - derive per-object `.rodata` subsegment offsets for
files that own jump tables, so that a C `switch` can link byte-identically.

Background
----------
In this repo every `jtbl_*` currently lives inside a *shared* data/rodata
subsegment (`asm/us/data/A23F0.rodata.s` for the main `text` segment,
`asm/us/data/fragments/NN/fragmentNN_data.data.s` for the overlays).  The owner
object therefore has no `.rodata` of its own and references the table as UND.
When such a function is rewritten as a C `switch`, IDO emits the jump table into
the object's own `.rodata`, which appends bytes that the ROM does not have at
that place -> `section_layout_drift`.

The fix is the pret pattern: give the owner object its own `.rodata` subsegment
covering exactly the bytes it owns.  splat then migrates the table into the
function's `nonmatchings/*.s` (as a `.late_rodata`/`.rodata` block that
asm-processor folds back into the object), and the linker script places
`build/src/<file>.o(.rodata)` at the right position.  Both the assembly build and
the C build then produce identical bytes.

Usage
-----
  # everything that would need doing, with risk flags
  python3 add_rodata_subsegments.py plan            --disasm /path/to/disasm

  # the exact yaml lines needed to unblock one jump table
  python3 add_rodata_subsegments.py for-jtbl jtbl_800A5470 --disasm /path/to/disasm

Only the main `text` segment is fully automatic.  Fragments are handled by
`for-jtbl` too, but see the caveats printed with the result.
"""

import argparse
import os
import re
import sys
from collections import defaultdict

LABEL_RE = re.compile(r"^(?:d|g|j)label\s+(\S+)")
ADDR_RE = re.compile(r"^\s*/\* ([0-9A-F]{6}) ([0-9A-F]{8})")
SUBSEG_RE = re.compile(r"^\s*-\s*\[0x([0-9A-Fa-f]+),\s*([A-Za-z_.][\w.]*)\s*(?:,\s*([^\],#]+?))?\s*\]")
SEGNAME_RE = re.compile(r"^\s*-\s*name:\s*(\S+)")
START_RE = re.compile(r"^\s*start:\s*0x([0-9A-Fa-f]+)")
VRAM_RE = re.compile(r"^\s*vram:\s*0x([0-9A-Fa-f]+)")
SYMREF_RE = re.compile(r"\b(?:jtbl_[0-9A-Fa-f]{8}|D_[0-9A-Fa-f]{8})\b")

ALIGN = 16  # every code segment in this repo is emitted with SUBALIGN(16)


class Segment:
    def __init__(self, name):
        self.name = name
        self.rom = None
        self.vram = None
        self.subs = []      # (rom_off, type, name)

    def rom_to_vram(self, rom):
        return self.vram + (rom - self.rom)

    def vram_to_rom(self, vram):
        return self.rom + (vram - self.vram)


def parse_yaml(path):
    """Very small, purpose-built reader for this repo's rom.yaml."""
    segs = []
    cur = None
    for line in open(path):
        m = SEGNAME_RE.match(line)
        if m:
            cur = Segment(m.group(1))
            segs.append(cur)
            continue
        if cur is None:
            continue
        m = START_RE.match(line)
        if m and cur.rom is None:
            cur.rom = int(m.group(1), 16)
            continue
        m = VRAM_RE.match(line)
        if m and cur.vram is None:
            cur.vram = int(m.group(1), 16)
            continue
        m = SUBSEG_RE.match(line)
        if m:
            off = int(m.group(1), 16)
            typ = m.group(2)
            nm = (m.group(3) or "").strip()
            cur.subs.append((off, typ, nm))
    return [s for s in segs if s.rom is not None and s.vram is not None]


def parse_asm_symbols(path):
    """[(vram, rom, name)] in file order for a splat-generated data/rodata .s."""
    out = []
    lines = open(path).read().split("\n")
    for i, line in enumerate(lines):
        m = LABEL_RE.match(line)
        if not m:
            continue
        for j in range(i + 1, min(i + 4, len(lines))):
            a = ADDR_RE.match(lines[j])
            if a:
                out.append((int(a.group(2), 16), int(a.group(1), 16), m.group(1)))
                break
    return out


def build_reference_index(disasm):
    """symbol name -> set of owner file keys (the nonmatchings subdirectory)."""
    refs = defaultdict(set)
    base = os.path.join(disasm, "asm/us/nonmatchings")
    for dirpath, _dirs, files in os.walk(base):
        rel = os.path.relpath(dirpath, base)
        parts = rel.split(os.sep)
        # nonmatchings/<file>/<func>.s  or  nonmatchings/fragments/NN/<file>/<func>.s
        if parts[0] == "fragments":
            if len(parts) != 3:
                continue
            key = "fragments/%s/%s" % (parts[1], parts[2])
        else:
            if len(parts) != 1 or parts[0] == ".":
                continue
            key = parts[0]
        for fn in files:
            if not fn.endswith(".s"):
                continue
            txt = open(os.path.join(dirpath, fn)).read()
            for n in set(SYMREF_RE.findall(txt)):
                refs[n].add(key)
    # decompiled C bodies reference their rodata directly
    for root, _d, files in os.walk(os.path.join(disasm, "src")):
        for fn in files:
            if not fn.endswith(".c"):
                continue
            p = os.path.join(root, fn)
            key = os.path.relpath(p, os.path.join(disasm, "src"))[:-2]
            txt = open(p, errors="ignore").read()
            for n in set(SYMREF_RE.findall(txt)):
                refs[n].add(key)
    return refs


def owner_runs(symbols, refs, seg_end_rom):
    """Collapse the symbol list into contiguous runs of a single owner.

    Returns [(rom_start, rom_end, owner_or_None, [symbols])].
    """
    runs = []
    for idx, (vram, rom, name) in enumerate(symbols):
        owners = sorted(refs.get(name, ()))
        owner = owners[0] if len(owners) == 1 else None
        end = symbols[idx + 1][1] if idx + 1 < len(symbols) else seg_end_rom
        if runs and runs[-1][2] == owner:
            runs[-1][1] = end
            runs[-1][3].append(name)
        else:
            runs.append([rom, end, owner, [name], len(owners)])
    return runs


def find_rodata_files(disasm, seg):
    """[(rom_start, rom_end, path, is_data_type)] for shared data/rodata blobs."""
    out = []
    subs = seg.subs
    for i, (off, typ, nm) in enumerate(subs):
        if typ not in ("rodata", "data"):
            continue
        end = subs[i + 1][0] if i + 1 < len(subs) else None
        name = nm if nm else "%X" % off
        path = os.path.join(disasm, "asm/us/data", "%s.%s.s" % (name, typ))
        if os.path.exists(path):
            out.append((off, end, path, typ == "data"))
    return out


def cmd_plan(args):
    disasm = args.disasm
    segs = parse_yaml(os.path.join(disasm, "yamls/us/rom.yaml"))
    refs = build_reference_index(disasm)
    total, risky = 0, 0
    for seg in segs:
        for (start, end, path, is_data) in find_rodata_files(disasm, seg):
            syms = parse_asm_symbols(path)
            if not any(s[2].startswith("jtbl_") for s in syms):
                continue
            seg_end = end if end is not None else max(s[1] for s in syms) + 4
            runs = owner_runs(syms, refs, seg_end)
            print("\n== %s  (%s, rom 0x%X..0x%X)" % (path, seg.name, start, seg_end))
            for (rs, re_, owner, names, nowners) in runs:
                jt = [n for n in names if n.startswith("jtbl_")]
                if not jt:
                    continue
                total += 1
                flags = []
                if owner is None:
                    flags.append("AMBIGUOUS-OWNER(%d refs)" % nowners)
                if rs % ALIGN or re_ % ALIGN:
                    flags.append("UNALIGNED -> widen to 0x%X..0x%X"
                                 % (rs & ~(ALIGN - 1), (re_ + ALIGN - 1) & ~(ALIGN - 1)))
                if is_data:
                    flags.append("inside a .data subsegment (needs a trailing `rodata` split)")
                if flags:
                    risky += 1
                print("   0x%06X..0x%06X  %-28s %s  %s"
                      % (rs, re_, owner or "?", ",".join(jt[:3]), "; ".join(flags)))
    print("\n%d jump-table runs, %d need manual attention" % (total, risky))


def cmd_for_jtbl(args):
    disasm = args.disasm
    segs = parse_yaml(os.path.join(disasm, "yamls/us/rom.yaml"))
    refs = build_reference_index(disasm)
    for seg in segs:
        for (start, end, path, is_data) in find_rodata_files(disasm, seg):
            syms = parse_asm_symbols(path)
            if not any(s[2] == args.jtbl for s in syms):
                continue
            seg_end = end if end is not None else max(s[1] for s in syms) + 4
            runs = owner_runs(syms, refs, seg_end)
            for (rs, re_, owner, names, nowners) in runs:
                if args.jtbl not in names:
                    continue
                lo = rs & ~(ALIGN - 1)
                hi = (re_ + ALIGN - 1) & ~(ALIGN - 1)
                if owner is None:
                    print("!! %s is referenced by %d files - cannot attribute it"
                          % (args.jtbl, nowners))
                    return 1
                print("segment %s, shared blob %s" % (seg.name, os.path.basename(path)))
                print("owner   %s" % owner)
                print("run     rom 0x%X..0x%X  (widened to 0x%X..0x%X for SUBALIGN(16))"
                      % (rs, re_, lo, hi))
                print("\nyaml (insert in ascending rom order inside `%s`):" % seg.name)
                print("    - [0x%X, .rodata, %s] # %s" % (lo, owner, args.jtbl))
                if hi < seg_end:
                    tail = "rodata" if not is_data else "rodata"
                    print("    - [0x%X, %s]" % (hi, tail))
                if is_data:
                    print("\nNOTE: the bytes came out of a `data` subsegment.  The tail"
                          "\n      subsegment MUST be typed `rodata` (not `data`) or it"
                          "\n      would be linked before the .rodata block.")
                print("\nthen: cat yamls/us/header.yaml yamls/us/rom.yaml > pokestadiumgs-us.yaml"
                      "\n      python3 -m splat split pokestadiumgs-us.yaml"
                      "\n      # re-apply the hand-written alias block in"
                      "\n      # linker_scripts/us/pokestadiumgs.ld (splat overwrites it)"
                      "\n      make COMPARE=1")
                return 0
    print("!! %s not found in any shared data/rodata blob" % args.jtbl)
    return 1


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--disasm", default="disasm")
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("plan")
    p = sub.add_parser("for-jtbl")
    p.add_argument("jtbl")
    args = ap.parse_args()
    return cmd_plan(args) if args.cmd == "plan" else cmd_for_jtbl(args)


if __name__ == "__main__":
    sys.exit(main() or 0)
