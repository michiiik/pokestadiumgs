#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_813110F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311368.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_813114B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311650.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311894.s")

extern f32 func_816092FC(void);
void func_813119E4(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 4) += step;
    if (*(f32 *)(arg0 + 4) >= 16.0f) {
        *(f32 *)(arg0 + 4) = 16.0f;
        arg0[0x18] = 2;
    }
}

void func_81311A3C(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 4) -= step;
    if (*(f32 *)(arg0 + 4) <= 0.0f) {
        *(f32 *)(arg0 + 4) = 0.0f;
        arg0[0x18] = 4;
    }
}

void func_81311A90(u8 *arg0) {
    *(f32 *)(arg0 + 4) = 0.0f;
}

void func_81311A9C(u8 *arg0) {
    *(s32 *)(arg0 + 0) = 0;
    *(f32 *)(arg0 + 4) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311AAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311B98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311C18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311C70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311CFC.s")
#endif
