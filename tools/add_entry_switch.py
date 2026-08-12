#!/usr/bin/env python3
"""Give static_5_80021834 the interior-entry switch it was never emitted.

The recompiler emits an entry switch (`if (ctx->dispatch_entry_target != 0)
{...}`) for functions whose `dispatch_entry_vrams` is populated by
register_interior_dispatch_aliases. That pass runs before the per-section
statics loop synthesizes the `static_*` functions, so late-synthesized statics
— which is all of section 5's hand-written resident code — never get it.

Without the switch, dispatch_alias_s5_80021A2C sets dispatch_entry_target and
calls the function, which ignores it, runs from the prologue, and reaches the
same `jalr $t3` unconditionally: infinite recursion (measured depth 100000),
two host frames per level, until the stack dies.

The routine has four PC-relative helpers ($ra+0x190/0x184/0x170/0x164):
0x80021A2C, 0x80021A44, 0x80021A54, 0x80021A6C. All four labels already exist
in the generated body, so all four are wired here.

This is the interim fix; the real one belongs in the emitter driver
(call the pass inside the statics loop, before recompiling each static).
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



ENTRIES = (0x80021A2C, 0x80021A44, 0x80021A54, 0x80021A6C)

ANCHOR = """RECOMP_FUNC void static_5_80021834(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
L_80021834:"""

cases = "\n".join(
    "        case 0x%08Xu: goto L_%08X;" % (v, v) for v in ENTRIES)

REPLACEMENT = """RECOMP_FUNC void static_5_80021834(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    int c1cs = 0;
    if (ctx->dispatch_entry_target != 0) {
        uint32_t recomp_dispatch_entry = ctx->dispatch_entry_target;
        ctx->dispatch_entry_target = 0;
        switch (recomp_dispatch_entry) {
%s
        default:
            ctx->dispatch_entry_rejected = 1;
            ctx->dispatch_entry_rejected_target = recomp_dispatch_entry;
            return;
        }
    }
L_80021834:""" % cases

for root in ("/Users/michaegg/ps2-recomp-build/runtime/generated",
             "/Users/michaegg/ps2-recomp-build/recomp-jal2/generated"):
    p = _find(root, "static_5_80021834")
    t = open(p, encoding="utf-8", newline="").read()
    if "recomp_dispatch_entry" in t and "static_5_80021834" in t.split("recomp_dispatch_entry")[0][-400:]:
        pass
    if t.count(ANCHOR) != 1:
        print("FAIL anchor count %d in %s" % (t.count(ANCHOR), p))
        raise SystemExit(1)
    if REPLACEMENT in t:
        print("SKIP already applied: %s" % p)
        continue
    if not os.path.exists(p + ".preentry"):
        shutil.copy2(p, p + ".preentry")
    open(p, "w", encoding="utf-8", newline="").write(t.replace(ANCHOR, REPLACEMENT, 1))
    print("added entry switch (%d targets) to %s" % (len(ENTRIES), p))
