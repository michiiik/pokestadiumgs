#!/usr/bin/env python3
import os
import shutil

P = "/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime/librecomp/src/overlays.cpp"
t = open(P, encoding="utf-8", newline="").read()
nl = "\r\n" if "\r\n" in t else "\n"

old = "static constexpr uint32_t kSyntheticPoolEnd   = 0xE0000000u;"
assert t.count(old) == 1, t.count(old)

comment = [
    "// Pool end raised from 0xE0000000 (512 buckets) to 0xF0000000 (768) for",
    "// Pokemon Stadium 2, whose 0x8FF00000 stream synthesizes 651 variants",
    "// against Stadium 1's ~279. Variants past the end are invisible to",
    "// is_synthetic_addr, so their sections never become registration",
    "// candidates and the fragment is left unregistered. Widening is backward",
    "// compatible: existing synthetic addresses keep their slot index.",
    "static constexpr uint32_t kSyntheticPoolEnd   = 0xF0000000u;",
]
new = nl.join(comment)

if not os.path.exists(P + ".pool.orig"):
    shutil.copy2(P, P + ".pool.orig")
open(P, "w", encoding="utf-8", newline="").write(t.replace(old, new, 1))
print("OK synthetic pool widened to 768 buckets")
