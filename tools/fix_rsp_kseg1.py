#!/usr/bin/env python3
"""Make the RSP DMA resolve KSEG1 addresses the way the CPU does.

SP_DRAM_ADDR holds a physical address on hardware, where KSEG0 and KSEG1 alias
the same RAM. This runtime does not alias them: MEM_* resolves a guest address
as (addr - 0x80000000) & 0x3FFFFFFF, so an uncached KSEG1 pointer lands
0x20000000 above the cached one, inside the allocation's slack.

Pokemon Stadium 2 hands the audio task its Acmd list through a KSEG1 pointer
(task->data_ptr = 0xA00DF2B0). The recompiled aspMain therefore DMA'd 968 bytes
of zeros from physical 0x0DF2B0 and dispatched on opcode 0 forever, while the
list the game actually built sat at rdram+0x200DF2B0.

Only KSEG1 changes; every other address keeps the existing physical path. The
in-loop wrap masks widen from 16 MB to the full mapped range so a resolved KSEG1
offset is not truncated back down.
"""
import os
import shutil

P = "/Users/michaegg/psr-recomp-build/work/lib/N64ModernRuntime/librecomp/include/librecomp/rsp.hpp"
t = open(P).read()
assert "rsp_dram_offset" not in t, "already applied"

anchor = ("static inline void dma_rdram_to_dmem(uint8_t* rdram, uint32_t dmem_addr, "
          "uint32_t dram_addr, uint32_t rd_len) {")
assert t.count(anchor) == 1, t.count(anchor)

helper = '''// SP_DRAM_ADDR holds a physical address on hardware, where KSEG0 and KSEG1
// alias the same RAM. This runtime does not alias them: MEM_* resolves a guest
// address as (addr - 0x80000000) & 0x3FFFFFFF, so an uncached KSEG1 pointer
// lands 0x20000000 above the cached one. Truncating to a physical address here
// therefore reads a region the CPU never wrote.
//
// Pokemon Stadium 2 hands the audio task its Acmd list through a KSEG1 pointer
// (task->data_ptr = 0xA00DF2B0), so aspMain read 968 bytes of zeros and
// dispatched on opcode 0 forever. Resolve KSEG1 the way the CPU does and leave
// every other address on the existing physical path.
static inline uint32_t rsp_dram_offset(uint32_t dram_addr) {
    if ((dram_addr & 0xE0000000u) == 0xA0000000u) {
        return (dram_addr - 0x80000000u) & 0x3FFFFFFFu;
    }
    return dram_addr & 0x00FFFFFFu;
}

'''
t = t.replace(anchor, helper + anchor, 1)

old_init = "    uint32_t cur_dram = dram_addr & 0xFFFFF8u;"
assert t.count(old_init) == 2, t.count(old_init)
t = t.replace(old_init, "    uint32_t cur_dram = rsp_dram_offset(dram_addr) & ~7u;")

old_wrap = "        cur_dram = (cur_dram + block_len) & 0xFFFFF8u;"
assert t.count(old_wrap) == 2, t.count(old_wrap)
t = t.replace(old_wrap, "        cur_dram = (cur_dram + block_len) & 0x3FFFFFF8u;")

old_skip = "            cur_dram = (cur_dram + skip) & 0xFFFFF8u;"
assert t.count(old_skip) == 2, t.count(old_skip)
t = t.replace(old_skip, "            cur_dram = (cur_dram + skip) & 0x3FFFFFF8u;")

if not os.path.exists(P + ".kseg1.orig"):
    shutil.copy2(P, P + ".kseg1.orig")
open(P, "w").write(t)
print("rsp.hpp: RSP DMA now resolves KSEG1 the way the CPU does")
