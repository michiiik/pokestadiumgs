#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_80003240.s")


void func_80003308(u32 *dst, const u32 *src, s32 wordCount) {
    while (wordCount-- > 0) {
        *dst++ = *src++;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/Util_InitMainPools.s")

extern u32 D_800871F4; u32 func_8000339C(void) { return D_800871F4; }

extern u32 D_800871F0; u32 func_800033A8(void) { return D_800871F0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_800033B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_800033DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_80003404.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3E40/func_800034E4.s")

void func_8000377C(u64 *dest, u32 size) {
    while (size-- > 0) {
        *(dest++) = -1;
    }
}

s32 func_800037B8(u64 *ptr) {
    s32 ret = 0;
    while (*(ptr++) == 0x8040000080400000ULL) {
        ret++;
    }
    return ret * sizeof(*ptr);
}
#endif
