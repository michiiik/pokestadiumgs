#!/usr/bin/env python3
import os
import shutil

P = "/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime/librecomp/src/overlays.cpp"
t = open(P, encoding="utf-8", newline="").read()
nl = "\r\n" if "\r\n" in t else "\n"

old = "                frag_size_in_ram = rd_be32_h(0x1C);"
assert t.count(old) == 1, t.count(old)

new = nl.join([
    "                // Bound by the LARGER of the header's size (+0x18) and",
    "                // sizeInRam (+0x1C). +0x1C is not reliably the total extent:",
    "                // Pokemon Stadium 2's id=0 fragment has +0x18=0x73A0 (which",
    "                // matches its recompiled section exactly) but +0x1C=0x6790,",
    "                // tracking relocOffset instead. Bounding by +0x1C alone",
    "                // rejected the correct variant as 'oversized' and left the",
    "                // fragment unregistered. Taking the max keeps the guard's",
    "                // intent - reject sections bigger than the loaded fragment -",
    "                // while using the field that actually states the extent.",
    "                const uint32_t hdr_size  = rd_be32_h(0x18);",
    "                const uint32_t hdr_inram = rd_be32_h(0x1C);",
    "                frag_size_in_ram = hdr_size > hdr_inram ? hdr_size : hdr_inram;",
])

if not os.path.exists(P + ".extent.orig"):
    shutil.copy2(P, P + ".extent.orig")
open(P, "w", encoding="utf-8", newline="").write(t.replace(old, new, 1))
print("OK extent bound fixed")
