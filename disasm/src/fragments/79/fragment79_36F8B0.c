#include "global.h"


#ifdef VERSION_US
void func_84100020(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x14) |= arg1;
}

void func_84100030(u8 *arg0, u32 arg1) {
    *(u32 *)(arg0 + 0x14) &= ~arg1;
}

void func_84100044(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x14) ^= arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100074.s")

void func_84100094(u8 *arg0) {
    arg0[0x92] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_8410009C.s")

extern u8 *D_8418C950;
extern u32 D_8418C954;
extern u8 *func_80002984(s32 arg0, s32 arg1);
void func_84100134(void) {
    D_8418C950 = func_80002984(0xB6D0, 0);
    _bzero(D_8418C950, 0xB6D0);
    D_8418C954 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100174.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100260.s")

extern void func_84100260(void);
void func_84100328(void) {
    func_84100260();
}

void func_84100348(u8 *arg0) {
    arg0[0x92] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100350.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841003AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_8410056C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841005E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100688.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100710.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100874.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841009D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100B3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100C68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100DE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101084.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_8410119C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841013F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101888.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101AF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101C00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84102750.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841027B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_8410291C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841029DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84102B3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84102D38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84102E84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841031F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841032F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84103394.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84103478.s")
#endif
