#!/usr/bin/env python3
"""Locate Stadium 2's Memmap_RelocateFragment by instruction-shape matching
against Stadium 1's, whose symbol is known (0x80001E50, size 0x260).

Immediates and jump targets differ between the two games, so each instruction
is reduced to a shape: opcode + register fields, with immediates/targets
zeroed. R-type words keep their function field.
"""
import struct
import sys

S1 = "/Users/michaegg/psr-recomp-build/work/baserom.z64"
S2 = "/Users/michaegg/ps2-recomp-build/runtime/baserom.z64"

# Both games' resident code section: ROM 0x1000 <-> vram 0x80000400.
ROM_BASE, VRAM_BASE = 0x1000, 0x80000400


def vram_to_rom(v):
    return v - VRAM_BASE + ROM_BASE


def shape(w):
    op = w >> 26
    if op == 0 or op == 0x1C:          # SPECIAL / SPECIAL2: full R-type word
        return w
    if op in (2, 3):                   # J / JAL: target differs between games
        return op << 26
    if op == 0x11:                     # COP1: keep whole (fmt/func matter)
        return w
    return w & 0xFFFF0000              # I-type: drop the immediate


def shapes(buf, off, n_words):
    return [shape(struct.unpack_from(">I", buf, off + 4 * i)[0]) for i in range(n_words)]


def main():
    s1 = open(S1, "rb").read()
    s2 = open(S2, "rb").read()

    src_rom = vram_to_rom(0x80001E50)
    n_words = 0x260 // 4
    print("Stadium 1 Memmap_RelocateFragment: vram 0x80001E50 -> ROM 0x%X, %d instrs"
          % (src_rom, n_words))
    first = struct.unpack_from(">I", s1, src_rom)[0]
    print("  first instruction: %08X %s" % (
        first, "(addiu sp,sp,-N prologue)" if (first >> 16) == 0x27BD else "(unexpected)"))

    needle = shapes(s1, src_rom, n_words)

    # Scan Stadium 2's resident text. Score every 4-byte-aligned position.
    text_start, text_size = ROM_BASE, 0xA7A80
    best = []
    end = text_start + text_size - 4 * n_words
    for off in range(text_start, end, 4):
        hits = 0
        for i in range(n_words):
            w = struct.unpack_from(">I", s2, off + 4 * i)[0]
            if shape(w) == needle[i]:
                hits += 1
            elif hits < i * 0.75:       # bail early on hopeless positions
                break
        best.append((hits, off))
    best.sort(reverse=True)

    print("\ntop shape matches in Stadium 2 resident text (of %d instrs):" % n_words)
    for hits, off in best[:8]:
        vram = off - ROM_BASE + VRAM_BASE
        print("  %5.1f%%  ROM 0x%06X  vram 0x%08X  first=%08X"
              % (100.0 * hits / n_words, off, vram,
                 struct.unpack_from(">I", s2, off)[0]))

    top_hits, top_off = best[0]
    if top_hits < n_words * 0.6:
        print("\nNo confident match (best %.1f%%). The function likely diverges "
              "between the two games; fall back to call-site analysis."
              % (100.0 * top_hits / n_words))
        return 1
    print("\nBEST: vram 0x%08X (%.1f%% instruction-shape match)"
          % (top_off - ROM_BASE + VRAM_BASE, 100.0 * top_hits / n_words))
    return 0


sys.exit(main())
