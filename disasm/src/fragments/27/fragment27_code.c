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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/27/fragment27_code/func_81100054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/27/fragment27_code/func_81100074.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/27/fragment27_code/func_81100094.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/27/fragment27_code/func_811000F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/27/fragment27_code/func_81100120.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/27/fragment27_code/func_81100144.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/27/fragment27_code/func_81100168.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/27/fragment27_code/func_811001A0.s")

void func_8110020C(f32 *arg0, f32 *arg1) { arg0[0] = arg1[0]; arg0[1] = arg1[1]; arg0[2] = arg1[2]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/27/fragment27_code/func_81100228.s")
#endif
