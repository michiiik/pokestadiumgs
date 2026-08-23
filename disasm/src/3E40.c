#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_80003240.s")

void Util_Memcpy(u32 *dst, const u32 *src, s32 wordCount) {
    while (wordCount-- > 0) {
        *dst++ = *src++;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/Util_InitMainPools.s")

u32 func_8000339C(void) {
    return *(u32 *)0x800871F4;
}

u32 func_800033A8(void) {
    return *(u32 *)0x800871F0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/Util_Malloc.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/Util_Free.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/Util_DrawRect.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_800034E4.s")

void Util_Memclear(u32 *dst, u32 count) {
    while (count-- != 0) {
        *dst++ = 0xFFFFFFFF;
        *dst++ = 0xFFFFFFFF;
    }
}

s32 Util_CheckStubMemArea(const u32 *pairs) {
    s32 count = 0;

    while (pairs[0] == 0x80400000 && pairs[1] == 0x80400000) {
        pairs += 2;
        count++;
    }
    return count * 8;
}
#endif
