#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B00020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B00288.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B003B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B00690.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B00700.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B007A0.s")

typedef float S1_MtxF_t[4][4];
typedef union {
    S1_MtxF_t mf;
    struct {
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
} S1_MtxF;
void func_88B00FB8(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9,
                   f32 argA) {
    S1_MtxF sp20;

    guRotateF(sp20.mf, arg4, arg5, arg6, arg7);

    sp20.xx *= arg1;
    sp20.yx *= arg1;
    sp20.zx *= arg1;

    sp20.xy *= arg2;
    sp20.yy *= arg2;
    sp20.zy *= arg2;

    sp20.xz *= arg3;
    sp20.yz *= arg3;
    sp20.zz *= arg3;

    sp20.xw = arg8;
    sp20.yw = arg9;
    sp20.zw = argA;

    guMtxF2L(sp20.mf, arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B010A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B01438.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B01824.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B01A60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B01C54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B01FE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B038E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B039E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B03A70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B03B78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B04028.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B04170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/40/fragment40_1DC1F0/func_88B041C4.s")
#endif
