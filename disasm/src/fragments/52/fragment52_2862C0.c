#include "global.h"


#ifdef VERSION_US
void func_86407E00(u8 *arg0, f32 arg1, f32 arg2) {
    *(s32 *)(arg0 + 0x18) = 0;
    *(s32 *)(arg0 + 0x1C) = 0;
    *(f32 *)(arg0 + 0x00) = arg1;
    *(f32 *)(arg0 + 0x08) = arg1;
    *(f32 *)(arg0 + 0x10) = arg1;
    *(f32 *)(arg0 + 0x04) = arg2;
    *(f32 *)(arg0 + 0x0C) = arg2;
    *(f32 *)(arg0 + 0x14) = arg2;
}

void func_86407E2C(u8 *arg0, f32 arg1, f32 arg2, s32 arg3) {
    *(s32 *)(arg0 + 0x18) = 0;
    *(s32 *)(arg0 + 0x1C) = arg3;
    *(f32 *)(arg0 + 0x10) = arg1;
    *(f32 *)(arg0 + 0x08) = *(f32 *)(arg0 + 0x00);
    *(f32 *)(arg0 + 0x14) = arg2;
    *(f32 *)(arg0 + 0x0C) = *(f32 *)(arg0 + 0x04);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2862C0/func_86407E58.s")

extern u8 *D_86416C00;
extern void func_86407E58(u8 *);
void func_86408048(void) {
    u8 *temp = D_86416C00 + 0xCE00;
    func_86407E58(temp + 0x0C);
    func_86407E58(temp + 0x2C);
    func_86407E58(temp + 0x4C);
    func_86407E58(temp + 0x6C);
    func_86407E58(temp + 0x8C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2862C0/func_864080A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2862C0/func_86408148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2862C0/func_864081E8.s")

void func_8640826C(void) {
    u8 *temp = D_86416C00 + 0xCE00;
    func_86407E2C(temp + 0x8C, -70.0f, 86.0f, 0x14);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_2862C0/func_864082A8.s")
#endif
