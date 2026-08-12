#!/usr/bin/env python3
"""Re-apply the post-generation patches that a regenerate always drops.

  - stadium2-exclude-rom-tail-section.patch: removes the bogus trailing
    section (rom 0x00437610, size 0x03BC89F0 — 62 MB, past the ROM).
  - stadium2-generated-callback-guard.patch: guards the two wild stores in
    func_80015A40.

Matched by content, not line number, so it survives symbol renaming and the
section-count growth from the decompressed-pattern synthesis.

ALSO RUN tools/wire_ai_submit.py after a regenerate — it patches the generated
sources too (the AI submission call at 0x80019624) and there is no sound
without it. It is idempotent and kept separate because it also touches
recomp.h and librecomp/src/ai.cpp.
"""
import glob
import os
import shutil

def _find(root, marker):
    """Regeneration reshuffles functions between funcs_N.c files, so locate
    the file by content rather than by a hardcoded name."""
    for path in sorted(glob.glob(os.path.join(root, "funcs_*.c"))):
        with open(path, encoding="utf-8", newline="") as fh:
            if marker in fh.read():
                return path
    raise SystemExit("FAIL: no generated file contains " + marker)


import sys

ROOTS = [
    "/Users/michaegg/ps2-recomp-build/runtime/generated",
    "/Users/michaegg/ps2-recomp-build/recomp-jal2/generated",
]

TAIL_MARKER = ".rom_addr = 0x00437610,"

GUARD_OLD = "    MEM_W(-0X590, ctx->r1) = ctx->r4;"
GUARD_NEW = """    if (U32(ctx->r4) == 0 ||
        (U32(ctx->r4) >= 0x80000000u && U32(ctx->r4) < 0x90000000u)) {
        MEM_W(-0X590, ctx->r1) = ctx->r4;
    }"""

for root in ROOTS:
    # 1. Drop the invalid ROM-tail section entry.
    inl = os.path.join(root, "recomp_overlays.inl")
    lines = open(inl, encoding="utf-8", newline="").read().split("\n")
    keep = [l for l in lines if TAIL_MARKER not in l]
    dropped = len(lines) - len(keep)
    if dropped:
        if not os.path.exists(inl + ".pretailfix"):
            shutil.copy2(inl, inl + ".pretailfix")
        open(inl, "w", encoding="utf-8", newline="").write("\n".join(keep))
    print("%s: dropped %d rom-tail section line(s)" % (inl, dropped))

    # 2. Guard the wild stores in func_80015A40.
    src = _find(root, "func_80015A40")
    text = open(src, encoding="utf-8", newline="").read()
    if "0x90000000u" in text:
        print("%s: callback guard already present" % src)
        continue
    n = text.count(GUARD_OLD)
    if n == 0:
        print("FAIL: no store to guard in %s" % src)
        sys.exit(1)
    if not os.path.exists(src + ".preguard"):
        shutil.copy2(src, src + ".preguard")
    open(src, "w", encoding="utf-8", newline="").write(text.replace(GUARD_OLD, GUARD_NEW))
    print("%s: guarded %d store(s)" % (src, n))
