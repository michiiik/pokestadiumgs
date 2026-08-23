#include "global.h"


#ifdef VERSION_US
/* Initialize the per-entry display attributes at the end of a 0x1DC-byte
 * record.  The low-byte index is intentional: the original ABI masks it. */
void func_80073080(void *records, s32 index, u8 first, u8 second, u8 third) {
    u8 *entry = (u8 *)records + ((u8)index * 0x1DC);

    entry[0x1D4] = first;
    entry[0x1D5] = second;
    entry[0x1D6] = third;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/73C80/func_800730BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/73C80/func_80073208.s")

/* Copy the six three-word battle-display entries and the trailing pair of
 * words from one indexed record into another. */
void func_80073394(void *destBase, void *srcBase, s32 destIndex, s32 srcIndex) {
    u8 *dest = (u8 *)destBase + ((u8)destIndex * 0x4E0);
    u8 *src = (u8 *)srcBase + ((u8)srcIndex * 0x1DC) + 0x3C;
    s32 i;

    for (i = 0; i < 6; i++) {
        *(u32 *)(dest + 0x49C) = *(u32 *)(src + 0x190);
        *(u32 *)(dest + 0x4A0) = *(u32 *)(src + 0x188);
        *(u32 *)(dest + 0x4A4) = *(u32 *)(src + 0x18C);
        dest += 0x0C;
        src += 0x0C;
    }
    *(u32 *)(dest + 0x49C) = *(u32 *)(src + 0x190);
    *(u32 *)(dest + 0x4A0) = *(u32 *)(src + 0x194);
    *(u8 *)((u8 *)destBase + ((u8)destIndex * 0x4E0) + 0x49A) = 0xFF;
#endif
