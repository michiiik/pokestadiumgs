#!/usr/bin/env python3
"""Disassemble a function (or address range) from the US baserom by symbol name.

Usage:
    tools/disasm_func.py Game_Thread
    tools/disasm_func.py 0x80064FB0
    tools/disasm_func.py 0x80064FB0 0x80065100   # explicit range

Resolves j/jal targets and bal offsets against the US symbol tables so the
output reads like the extracted nonmatchings .s files. Only covers segments
that map 1:1 into the ROM (text, and fragments via fragments_relocatable.txt
link bases are NOT handled yet — text only).

Requires: capstone (tools venv), baserom at build-mac/ninja/baserom.z64.
"""
import re
import sys
from pathlib import Path

from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS64, CS_MODE_BIG_ENDIAN

ROOT = Path(__file__).resolve().parent.parent
ROM_PATH = ROOT / "build-mac/ninja/baserom.z64"
SYMBOL_FILES = [
    ROOT / "disasm/linker_scripts/us/symbol_addrs_code.txt",
    ROOT / "disasm/linker_scripts/us/symbol_addrs.txt",
]

# text segment: rom 0x1000 == vram 0x80000400 (see disasm/yamls/us/rom.yaml)
TEXT_VRAM = 0x80000400
TEXT_ROM = 0x1000


def load_symbols():
    by_addr = {}
    by_name = {}
    for path in SYMBOL_FILES:
        if not path.exists():
            continue
        for line in path.read_text().splitlines():
            m = re.match(r"(\w+)\s*=\s*0x([0-9A-Fa-f]+)", line.strip())
            if m:
                name, addr = m.group(1), int(m.group(2), 16)
                typ = "func" if "type:func" in line else "data"
                by_addr.setdefault(addr, (name, typ))
                by_name.setdefault(name, (addr, typ))
    return by_addr, by_name


def vram_to_rom(addr):
    if TEXT_VRAM <= addr < TEXT_VRAM + 0x200000:
        return addr - TEXT_VRAM + TEXT_ROM
    return None


def main():
    args = sys.argv[1:]
    if not args:
        sys.exit(__doc__)
    by_addr, by_name = load_symbols()

    if args[0].startswith("0x"):
        start = int(args[0], 16)
    else:
        if args[0] not in by_name:
            sys.exit(f"unknown symbol: {args[0]}")
        start = by_name[args[0]][0]

    if len(args) > 1:
        end = int(args[1], 16)
    else:
        # next function symbol after start
        later = sorted(a for a, (n, t) in by_addr.items() if a > start and t == "func")
        end = later[0] if later else start + 0x400
        end = min(end, start + 0x4000)

    rom_off = vram_to_rom(start)
    rom_end = vram_to_rom(end)
    if rom_off is None or rom_end is None:
        sys.exit(f"range {start:#x}..{end:#x} is outside the text segment")
    rom = ROM_PATH.read_bytes()
    code = rom[rom_off:rom_end]

    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS64 | CS_MODE_BIG_ENDIAN)
    md.detail = False
    for insn in md.disasm(code, start):
        tgt = ""
        if insn.mnemonic in ("j", "jal", "b", "bal"):
            try:
                a = int(insn.op_str, 0)
                if a in by_addr:
                    tgt = f"  <{by_addr[a][0]}>"
            except ValueError:
                pass
        elif insn.mnemonic in ("beq", "bne", "beqz", "bnez", "blez", "bgtz",
                               "bltz", "bgez", "bltzal", "bgezal"):
            a = int(insn.op_str.split(",")[-1].strip(), 0)
            if a in by_addr:
                tgt = f"  <{by_addr[a][0]}>"
        if start <= insn.address < start + 4:
            name = by_addr.get(start, (f"func_{start:08X}", ""))[0]
            print(f"{name}:")
        print(f"  {insn.address:08X}: {insn.mnemonic:10s} {insn.op_str}{tgt}")


if __name__ == "__main__":
    main()
