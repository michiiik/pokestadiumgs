#include "global.h"


#ifdef VERSION_US
s32 func_8130CE30(u8 *arg0) {
    return *(s32 *)(arg0 + 0x5C) != 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130CE3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130CEAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130CEF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D1FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D340.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D45C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D4E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130D6A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130DA04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130DEB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130E99C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130EA8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130EB04.s")

void func_8130EC94(u8 *arg0) {
    *(u32 *)(arg0 + 0x6C) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130EC9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130EF88.s")

extern f32 func_816092FC(void);
extern s32 func_8130CE30(u8 *arg0);
void func_8130F09C(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 0x2C) += step;
    if (*(f32 *)(arg0 + 0x2C) >= 1.0f) {
        *(f32 *)(arg0 + 0x2C) = 1.0f;
        arg0[0x34] = 1;
        *(s8 *)(arg0 + 0x38) = -1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130F0FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130F184.s")

void func_8130F218(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 0x30) += step;
    if (*(f32 *)(arg0 + 0x30) >= 12.0f) {
        *(f32 *)(arg0 + 0x30) = 12.0f;
        arg0[0x34] = 6;
    }
}

void func_8130F270(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 0x30) -= step;
    if (*(f32 *)(arg0 + 0x30) <= 0.0f) {
        arg0[0x34] = 1;
        *(f32 *)(arg0 + 0x30) = 0.0f;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130F2C4.s")

s16 func_8130F578(u8 *arg0, s32 *arg1) {
    s16 result = 0;
    if (arg1 != NULL) {
        *arg1 = arg0[0x39];
    }
    if (arg0[0x34] == 0) {
        result = *(s8 *)(arg0 + 0x36) + 1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_104FC0/func_8130F5AC.s")
#endif
