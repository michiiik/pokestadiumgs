#include "global.h"


#ifdef VERSION_US
extern s32 D_880068B8;
void func_8822AD40(void) {
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DFC0/func_8822AD4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DFC0/func_8822ADB0.s")

extern u32 D_882348F0;
extern void func_889033A0(s32);
void func_8822AE04(void) { func_889033A0((D_882348F0 + 4)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DFC0/func_8822AE2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DFC0/func_8822AF00.s")

void func_8822B240(void) {
    D_880068B8 = 0;
}

extern void func_800033DC(s32);
extern void func_88001900();
extern s32 D_880068B4;
extern s32 D_88234900;

void func_8822B24C(void) {
    func_88001900();
    D_880068B4 = 1;
    func_800033DC(D_88234900);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DFC0/func_8822B284.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DFC0/func_8822B2D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DFC0/func_8822B43C.s")
#endif
