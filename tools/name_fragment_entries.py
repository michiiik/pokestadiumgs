#!/usr/bin/env python3
"""Name every fragment's real entry point fragmentN_main.

All 88 fragments begin with an 8-byte header trampoline: a `J` to the
fragment's real entry, plus its delay slot (game.toml declares all 88 as
manual_funcs for exactly this reason).  The header is a `textbin` subsegment,
so splat emits no symbol for it -- but the J target is a real, currently
address-named function.  That target is the fragment's entry point, the single
highest-value name in the fragment.

This tool decodes the J at each fragment's offset 0 and records the target as
fragmentN_main in tools/gs_names.json, with the evidence inline.  It is
idempotent and only ever touches its own fragmentN_main entries.

    python3 tools/name_fragment_entries.py --report   # print, change nothing
    python3 tools/name_fragment_entries.py            # update gs_names.json

Two fragments need more than the plain decode:

  * fragment26's header jumps to a table of further J instructions; the first
    of those lands on the already-named DisplayList_InitIndexedTextureSegment,
    so the fragment needs no new name.
  * fragment28 is linked at 0x80000000 but loaded at 0x8FE00000; its header J
    resolves in the loaded address space, so the target is looked up by ROM
    offset instead.
"""
import json
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
YAML = os.path.join(ROOT, "disasm", "yamls", "us", "rom.yaml")
SYMTAB = os.path.join(ROOT, "disasm", "linker_scripts", "us",
                      "symbol_addrs_code.txt")
ROM = os.path.join(ROOT, "disasm", "baseroms", "us", "baserom.z64")
OUT = os.path.join(ROOT, "tools", "gs_names.json")


def load_symbols():
    syms = {}
    for line in open(SYMTAB, encoding="utf-8"):
        m = re.match(r"(\w+) = (0x[0-9A-Fa-f]+)", line)
        if m:
            syms[int(m.group(2), 16)] = m.group(1)
    return syms


def fragment_headers():
    """[(n, rom_offset, vram)] for every fragment's textbin header."""
    blocks = re.split(r"\n  - name: ", open(YAML, encoding="utf-8").read())[1:]
    out = []
    for b in blocks:
        name = b.split("\n", 1)[0].strip()
        m = re.fullmatch(r"fragment(\d+)", name)
        if not m:
            continue
        tm = re.search(r"- \[(0x[0-9A-F]+),\s*textbin", b)
        vm = re.search(r"vram: (0x[0-9A-Fa-f]+)", b)
        if tm and vm:
            out.append((int(m.group(1)), int(tm.group(1), 16),
                        int(vm.group(1), 16)))
    return sorted(out)


def j_target(word, at):
    assert (word >> 26) == 2, f"not a J: {word:#010x}"
    return (at & 0xF0000000) | ((word & 0x03FFFFFF) << 2)


def main():
    if not os.path.exists(ROM):
        sys.exit(f"no baserom at {os.path.relpath(ROM, ROOT)}")
    rom = open(ROM, "rb").read()
    syms = load_symbols()

    entries, skipped = {}, []
    for n, romoff, vram in fragment_headers():
        word = struct.unpack(">I", rom[romoff:romoff + 4])[0]
        tgt = j_target(word, vram)
        sym = syms.get(tgt)
        if n == 28:
            # Linked at 0x80000000, loaded at 0x8FE00000: resolve the loaded
            # target back through the linked base.
            tgt = 0x80000000 + (tgt - 0x8FE00000)
            sym = syms.get(tgt)
        if sym is None and 0 <= tgt - vram < len(rom):
            # fragment26: header jumps into a table of J trampolines; follow
            # the first one.
            w2 = struct.unpack(">I", rom[romoff + (tgt - vram):][:4])[0]
            if (w2 >> 26) == 2:
                sym = syms.get(j_target(w2, tgt))
        if sym is None:
            skipped.append((n, f"no symbol at {tgt:#x}"))
            continue
        if not sym.startswith("func_"):
            skipped.append((n, f"already named {sym}"))
            continue
        new = f"fragment{n}_main"
        entries[sym] = [new,
                        f"fragment {n} entry: target of the J at offset 0 of "
                        f"the fragment header trampoline (rom {romoff:#x}, "
                        f"vram {vram:#010x})"]

    print(f"{len(entries)} fragment entry points to name, "
          f"{len(skipped)} skipped:", file=sys.stderr)
    for n, why in skipped:
        print(f"  fragment{n}: {why}", file=sys.stderr)

    if "--report" in sys.argv:
        for old, (new, _) in sorted(entries.items()):
            print(f"  {old} -> {new}")
        return

    raw = json.load(open(OUT, encoding="utf-8"))
    fns = raw.setdefault("functions", {})
    # Only our own fragmentN_main entries may be replaced; anything else that
    # collides is a human's work and stays.
    stale = [k for k, v in fns.items()
             if isinstance(v, list) and v[0].startswith("fragment")
             and v[0].endswith("_main")]
    for k in stale:
        if k not in entries:
            del fns[k]
    fns.update(entries)
    json.dump(raw, open(OUT, "w", encoding="utf-8"), indent=1,
              ensure_ascii=False)
    print(f"wrote {len(entries)} names to {os.path.relpath(OUT, ROOT)}",
          file=sys.stderr)


if __name__ == "__main__":
    main()
