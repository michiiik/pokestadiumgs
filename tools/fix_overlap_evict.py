#!/usr/bin/env python3
"""Evict stale func_map entries over a newly claimed fragment range.

Fragments are evicted only when another load reuses the exact same base
(evict_prior_at_base) or when the same id reloads elsewhere (supersede by id).
Neither covers the common case: a DIFFERENT id loading at a different base
whose range overlaps a still-live fragment. Pokemon Stadium 2's battle/stadium
transition does exactly that — observed live:

    id=0x10 link=0x82000000 runtime=0x801451A0 size=0x2550   -> ..0x801476F0
    id=0x6  link=0x81600000 runtime=0x801451C0 size=0xD770   -> ..0x80152930
    id=0x12 link=0x82200000 runtime=0x801514D0 size=0x108A0  -> ..0x80161D70
    id=0x16 link=0x82600000 runtime=0x80147C40 size=0x17EB0  -> ..0x8015FAF0

After id=0x16 registers over ground still claimed by 0x6 and 0x12, a call into
the overlap can dispatch to a stale fragment's function. That code runs with its
own section base, so its RELOC_HI16 literals resolve against the wrong base and
it writes values whose low half is right and whose high half is garbage —
matching the corruption seen in the OS block:

    mq->msg   0x800CD9D0 -> 0xFFFFD9D0
    mq->first 0x00000008 -> 0xFFFF0008

The memory is about to be owned by the new fragment, so any func_map entry
inside the range is stale by definition. Erase the range before installing.
"""
import os
import shutil

P = "/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime/librecomp/src/overlays.cpp"
t = open(P, encoding="utf-8", newline="").read()
nl = "\r\n" if "\r\n" in t else "\n"


def fit(s):
    return s.replace("\n", nl)


assert "range now belongs to the incoming fragment" not in t, "already applied"

anchor = fit("""    // Register every FuncEntry at both the runtime address and the
    // section's link-time vram (mirroring load_overlay).""")
assert t.count(anchor) == 1, t.count(anchor)

insert = fit("""    // Any func_map entry inside [fragment_ptr, fragment_ptr + size) belongs to a
    // fragment that used to live here: the range now belongs to the incoming
    // fragment. evict_prior_at_base only clears sections loaded at this EXACT
    // base and the supersede path only clears the same id, so a different id
    // overlapping this range would otherwise keep dispatching its stale code,
    // which then resolves its RELOC_HI16 literals against the wrong section base
    // and writes wild values into whatever it computes.
    if (section.size != 0) {
        uint32_t stale = frag_range_erase((uint32_t)fragment_ptr, (uint32_t)section.size);
        if (stale != 0) {
            fprintf(stderr,
                "[reg-frag] id=0x%X claimed 0x%08X..0x%08X: erased %u stale "
                "func_map entries from overlapping fragments\\n",
                id, (uint32_t)fragment_ptr,
                (uint32_t)fragment_ptr + (uint32_t)section.size, stale);
            fflush(stderr);
        }
    }

""")

t = t.replace(anchor, insert + anchor, 1)
if not os.path.exists(P + ".overlap.orig"):
    shutil.copy2(P, P + ".overlap.orig")
open(P, "w", encoding="utf-8", newline="").write(t)
print("OK overlapping-range eviction added")
