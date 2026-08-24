#include "global.h"


#ifdef VERSION_US
void func_81100020(u32 *arg0, u32 arg1) {
    *arg0 |= arg1;
}

void func_81100030(u32 *arg0, u32 arg1) {
    *arg0 &= ~arg1;
}

void func_81100044(u32 *arg0, u32 arg1) {
    *arg0 ^= arg1;
}

s32 func_81100054(s32 *arg0, s32 arg1) { s32 result = 0; if (*arg0 & arg1) { result = 1; } return result; }

s32 func_81100074(u32 *arg0, u32 arg1) { s32 result = 0; if (!(*arg0 & arg1)) { result = 1; } return result; }

extern u32 D_80128C00;
s32 func_81100094(s32 arg0) {
    u32 temp_a0 = guRandom() + D_80128C00;
    s32 var_v1;
    if (arg0 == 0) {
        var_v1 = 0;
    } else {
        var_v1 = (temp_a0 / 10) % arg0;
    }
    return var_v1;
}

extern s32 func_81100094(s32 arg0);
s32 func_811000F8(s32 arg0) {
    return func_81100094(arg0 * 2) - arg0;
}

extern s32 func_81100094(s32 arg0);
s32 func_81100120(s32 arg0, s32 arg1) {
    return func_81100094(arg0) + arg1;
}


extern s32 func_811000F8(s32 arg0);
s32 func_81100144(s32 arg0, s32 arg1) {
    return func_811000F8(arg0) + arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/27/fragment27_code/func_81100168.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/27/fragment27_code/func_811001A0.s")

void func_8110020C(f32 *arg0, f32 *arg1) { arg0[0] = arg1[0]; arg0[1] = arg1[1]; arg0[2] = arg1[2]; }

void func_81100228(s16 *arg0, const s16 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
}
#pragma C_FUNCTION_PADDING(12)
#endif
