#include "global.h"


#ifdef VERSION_US
extern s32 D_84190170;
void func_84107CE0(void) {
    D_84190170 = 0;
}

extern s32 D_84190178;
void func_84107CEC(void) {
    D_84190178 = 0;
    D_84190170 += 4;
}

extern s32 D_84190170;
void func_84107D0C(void) {
    D_84190170 += 4;
}

extern s32 D_84190174;
extern s32 D_84190178;
void func_84107D24(void) {
    D_84190174 = 0;
    D_84190178 = 0;
    D_84190170 += 4;
}

extern s32 D_84190170;
void func_84107D4C(void) {
    u8 *ptr = (u8 *)(u32)D_84190170;
    (*(void (**)(s32, s32))(ptr + 4))(*(s32 *)(ptr + 8), *(s32 *)(ptr + 0xC));
    D_84190170 += 0x10;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_84107D90.s")

extern s32 D_84190170;
void func_84107E08(void) {
    D_84190170 += 4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_84107E20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_84107E70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_84107F18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_84107FC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_84108060.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_841080F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_84108190.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_84108228.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_841082C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_84108358.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_841083B0.s")

extern s32 D_84190178;
void func_84108630(void) {
    D_84190178 = 1;
    D_84190170 += 4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377570/func_84108654.s")
#endif
