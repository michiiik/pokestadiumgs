#!/usr/bin/env python3
"""Route Stadium 2's direct AI register writes into the host audio queue.

Stadium 2 does not link libultra's osAiSetNextBuffer -- the map has aigetlen.o,
aigetstat.o and aisetfreq.o but no aisetnextbuf.o. It has its own routine at
0x800195C0 that writes the AI registers itself:

    8001961C  sw $t2, 0x0($t3)     AI_DRAM_ADDR_REG = buffer (physical)
    80019624  sw $a1, 0x4($t4)     AI_LEN_REG       = byte count, starts the DMA

librecomp only intercepts osAiSetNextBuffer, so those stores went nowhere: a
guest store to 0xA4500000 resolves to rdram+0x24500000, in the mapping's slack.
The game synthesised audio every frame (2600+ tasks in 45 s) and never handed a
single buffer to the host -- ultramodern::queue_audio_buffer was never called.

Note the two AI paths cannot be distinguished by watching the mirror: ai.cpp's
publish_ai_len writes the remaining-byte count to the same AI_LEN address the
game writes its length to, so polling it cannot tell a submission from a
back-pressure refresh. The store site itself is the only unambiguous signal.

Applied to the generated sources rather than as a game.toml hook so this does
not require a full regeneration; tools/reapply_generated_patches.py re-runs it
if the tree is ever regenerated.
"""
import glob
import os
import shutil

RECOMP_H = "/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime/N64Recomp/include/recomp.h"
AI_CPP = "/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime/librecomp/src/ai.cpp"
GEN_GLOB = "/Users/michaegg/ps2-recomp-build/runtime/generated/funcs_*.c"

# ---- 1. declaration, next to the existing hook callee ---------------------
h = open(RECOMP_H).read()
if "recomp_ai_submit_buffer" not in h:
    anchor = "void recomp_register_runtime_fragment(uint8_t *rdram, uint32_t id,"
    assert h.count(anchor) == 1, h.count(anchor)
    decl = ("// Stadium 2 writes the AI registers directly instead of calling\n"
            "// osAiSetNextBuffer; its store site calls this to submit the buffer.\n"
            "void recomp_ai_submit_buffer(uint8_t *rdram, uint32_t guest_addr,\n"
            "                             uint32_t byte_count);\n\n")
    h = h.replace(anchor, decl + anchor, 1)
    if not os.path.exists(RECOMP_H + ".aisubmit.orig"):
        shutil.copy2(RECOMP_H, RECOMP_H + ".aisubmit.orig")
    open(RECOMP_H, "w").write(h)
    print("recomp.h: declared recomp_ai_submit_buffer")
else:
    print("recomp.h: already declared")

# ---- 2. implementation ---------------------------------------------------
a = open(AI_CPP).read()
if "recomp_ai_submit_buffer" not in a:
    anchor = 'extern "C" void osAiGetLength_recomp(uint8_t* rdram, recomp_context* ctx) {'
    assert a.count(anchor) == 1, a.count(anchor)
    impl = '''// Stadium 2 has no osAiSetNextBuffer: it stores to AI_DRAM_ADDR_REG and
// AI_LEN_REG itself, and a guest store to 0xA4500000 lands in the mapping's
// slack where nothing reads it. Its store site calls this instead, so the
// buffer reaches the host queue on the same path osAiSetNextBuffer would use.
extern "C" void recomp_ai_submit_buffer(uint8_t* rdram, uint32_t guest_addr,
                                        uint32_t byte_count) {
    if (byte_count == 0) {
        return;
    }
    ultramodern::queue_audio_buffer(rdram, (PTR(int16_t))guest_addr, byte_count);
    // Leave AI_LEN holding the remaining-byte count the game reads back.
    publish_ai_len(rdram);
}

'''
    a = a.replace(anchor, impl + anchor, 1)
    if not os.path.exists(AI_CPP + ".aisubmit.orig"):
        shutil.copy2(AI_CPP, AI_CPP + ".aisubmit.orig")
    open(AI_CPP, "w").write(a)
    print("ai.cpp: implemented recomp_ai_submit_buffer")
else:
    print("ai.cpp: already implemented")

# ---- 3. the generated store site -----------------------------------------
# Located by content: regeneration reshuffles which funcs_N.c holds a function.
ANCHOR = """    // 0x80019624: sw          $a1, 0x4($t4)
    MEM_W(0X4, ctx->r12) = ctx->r5;
"""
CALL = """    // Stadium 2's own osAiSetNextBuffer. The two AI register stores above go
    // to slack; hand the buffer to the host here. $v1 is the (possibly
    // 0x2000-adjusted) guest pointer, $a1 the byte count.
    recomp_ai_submit_buffer(rdram, (uint32_t)ctx->r3, (uint32_t)ctx->r5);
"""

patched = False
for path in sorted(glob.glob(GEN_GLOB)):
    t = open(path).read()
    if ANCHOR not in t:
        continue
    assert t.count(ANCHOR) == 1, "%s: %d anchors" % (path, t.count(ANCHOR))
    if "recomp_ai_submit_buffer" in t:
        print("%s: already patched" % os.path.basename(path))
        patched = True
        break
    if not os.path.exists(path + ".aisubmit.orig"):
        shutil.copy2(path, path + ".aisubmit.orig")
    open(path, "w").write(t.replace(ANCHOR, ANCHOR + CALL, 1))
    print("%s: AI submit call inserted" % os.path.basename(path))
    patched = True
    break

assert patched, "AI store site not found in generated sources"
