#!/usr/bin/env python3
"""Add the missing interior-entry dispatch alias for 0x80021A2C.

0x80021A2C is a jump-table target inside static_5_80021834 (the function already
carries `case 0x80021A2Cu: goto L_80021A2C;`), but nothing registers it in
func_map. A dynamic call to it therefore misses, falls into the lookup-miss
trampoline, and returns into the same address — the two recurse until the stack
overflows and the process takes SIGSEGV (256 alternating frames of
static_5_80021834+800 in the tombstone).

The recompiler already emits 51794 aliases of exactly this shape; this one was
simply never seeded. Same construction, so it behaves identically.
"""
import os
import shutil
import sys

VRAM = 0x80021A2C
SECTION_RAM = 0x80000400
OFFSET = VRAM - SECTION_RAM  # 0x2162C
ALIAS = "dispatch_alias_s5_80021A2C"
HOST = "static_5_80021834"
ANCHOR_ROW = "    { .func = dispatch_alias_s5_80064CF8, .offset = 0x000648F8, .rom_size = 0x00000000 },"

for root in ("/Users/michaegg/ps2-recomp-build/runtime/generated",
             "/Users/michaegg/ps2-recomp-build/recomp-jal2/generated"):
    inl = os.path.join(root, "recomp_overlays.inl")
    aliases = os.path.join(root, "dispatch_aliases.c")
    hdr = os.path.join(root, "funcs.h")

    text = open(inl, encoding="utf-8", newline="").read()
    if ALIAS in text:
        print("SKIP already added: %s" % root)
        continue
    if text.count(ANCHOR_ROW) != 1:
        print("FAIL anchor row count %d in %s" % (text.count(ANCHOR_ROW), inl))
        sys.exit(1)
    row = "    { .func = %s, .offset = 0x%08X, .rom_size = 0x00000000 }," % (ALIAS, OFFSET)
    if not os.path.exists(inl + ".prealias"):
        shutil.copy2(inl, inl + ".prealias")
    open(inl, "w", encoding="utf-8", newline="").write(
        text.replace(ANCHOR_ROW, ANCHOR_ROW + "\n" + row, 1))
    print("%s: added FuncEntry row at offset 0x%X" % (inl, OFFSET))

    body = open(aliases, encoding="utf-8", newline="").read()
    if not os.path.exists(aliases + ".prealias"):
        shutil.copy2(aliases, aliases + ".prealias")
    body += (
        "\nRECOMP_FUNC void %s(uint8_t* rdram, recomp_context* ctx) {\n"
        "    uint32_t recomp_prev_dispatch_entry = ctx->dispatch_entry_target;\n"
        "    ctx->dispatch_entry_target = 0x%08Xu;\n"
        "    %s(rdram, ctx);\n"
        "    ctx->dispatch_entry_target = recomp_prev_dispatch_entry;\n"
        "}\n" % (ALIAS, VRAM, HOST))
    open(aliases, "w", encoding="utf-8", newline="").write(body)
    print("%s: added alias body" % aliases)

    # The declaration must land INSIDE funcs.h's `extern "C"` block, otherwise
    # the C++ TUs reference a mangled symbol that the C alias body never
    # defines. Anchor on a sibling declaration rather than appending at EOF.
    h = open(hdr, encoding="utf-8", newline="").read()
    if ALIAS not in h:
        sib = "void dispatch_alias_s5_80064CF8(uint8_t* rdram, recomp_context* ctx);"
        if h.count(sib) != 1:
            print("FAIL sibling declaration count %d in %s" % (h.count(sib), hdr))
            sys.exit(1)
        if not os.path.exists(hdr + ".prealias"):
            shutil.copy2(hdr, hdr + ".prealias")
        decl = "void %s(uint8_t* rdram, recomp_context* ctx);" % ALIAS
        open(hdr, "w", encoding="utf-8", newline="").write(
            h.replace(sib, sib + "\n" + decl, 1))
        print("%s: added declaration" % hdr)
