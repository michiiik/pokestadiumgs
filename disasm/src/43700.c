#include "global.h"


#ifdef VERSION_US
extern s32 D_80126F40;

s32 func_80042B00(s32 arg0, s32 arg1) {
    if (!arg0) {
        D_80126F40 = arg1;
    }
    return 0;
}

void func_80042B14(u8 *arg0) {
    *(u16 *)(arg0 + 0) = 0;
    *(u32 *)(arg0 + 4) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042B20.s")

void func_80042BB0(u16 *arg0) {
    *arg0 &= (u16)~2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042BC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042C68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042D74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042D8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042EB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042F94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042FBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042FE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_8004300C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80043064.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_800430B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_8004335C.s")

s32 func_80043444(u8 *arg0) { return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80043450.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80043500.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_800435D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80043678.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_800436CC.s")

extern s32 D_80094C60;

s32 func_800436E8(void) {
    return D_80094C60;
}
#endif
