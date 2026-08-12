#!/usr/bin/env python3
"""Add dispatch aliases for the three sibling PC-relative helpers.

static_5_80021834 computes four local helper addresses ($ra+0x190/0x184/0x170/
0x164). Only 0x80021A2C had an alias; the other three fell through to the
lookup-miss self-heal, which works now that the entry switch exists but costs a
large last_error.log block per occurrence.
"""
import os
import shutil
import sys

SECTION_RAM = 0x80000400
HOST = "static_5_80021834"
VRAMS = (0x80021A44, 0x80021A54, 0x80021A6C)
SIBLING_ROW = "    { .func = dispatch_alias_s5_80021A2C, .offset = 0x0002162C, .rom_size = 0x00000000 },"
SIBLING_DECL = "void dispatch_alias_s5_80021A2C(uint8_t* rdram, recomp_context* ctx);"

for root in ("/Users/michaegg/ps2-recomp-build/runtime/generated",
             "/Users/michaegg/ps2-recomp-build/recomp-jal2/generated"):
    inl = os.path.join(root, "recomp_overlays.inl")
    aliases = os.path.join(root, "dispatch_aliases.c")
    hdr = os.path.join(root, "funcs.h")

    text = open(inl, encoding="utf-8", newline="").read()
    body = open(aliases, encoding="utf-8", newline="").read()
    head = open(hdr, encoding="utf-8", newline="").read()

    if text.count(SIBLING_ROW) != 1 or head.count(SIBLING_DECL) != 1:
        print("FAIL sibling anchors not unique in %s" % root)
        sys.exit(1)

    added = []
    rows, decls, bodies = [], [], []
    for v in VRAMS:
        name = "dispatch_alias_s5_%08X" % v
        if name in head:
            continue
        added.append(name)
        rows.append("    { .func = %s, .offset = 0x%08X, .rom_size = 0x00000000 },"
                    % (name, v - SECTION_RAM))
        decls.append("void %s(uint8_t* rdram, recomp_context* ctx);" % name)
        bodies.append(
            "\nRECOMP_FUNC void %s(uint8_t* rdram, recomp_context* ctx) {\n"
            "    uint32_t recomp_prev_dispatch_entry = ctx->dispatch_entry_target;\n"
            "    ctx->dispatch_entry_target = 0x%08Xu;\n"
            "    %s(rdram, ctx);\n"
            "    ctx->dispatch_entry_target = recomp_prev_dispatch_entry;\n"
            "}\n" % (name, v, HOST))

    if not added:
        print("SKIP all siblings already present: %s" % root)
        continue

    for p, orig in ((inl, text), (aliases, body), (hdr, head)):
        if not os.path.exists(p + ".presibling"):
            shutil.copy2(p, p + ".presibling")

    open(inl, "w", encoding="utf-8", newline="").write(
        text.replace(SIBLING_ROW, SIBLING_ROW + "\n" + "\n".join(rows), 1))
    open(hdr, "w", encoding="utf-8", newline="").write(
        head.replace(SIBLING_DECL, SIBLING_DECL + "\n" + "\n".join(decls), 1))
    open(aliases, "w", encoding="utf-8", newline="").write(body + "".join(bodies))
    print("%s: added %s" % (root, ", ".join(added)))
