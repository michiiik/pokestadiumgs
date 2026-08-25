#include "global.h"


#ifdef VERSION_US
extern u8 *D_87F15B90;
extern u8 D_87F15B98[];
extern void func_8004C8C0(s32);
void func_87F0C980(void) {
    D_87F15B90 = D_87F15B98;
    *(s32 *)(D_87F15B90 + 0) = 0;
    *(s32 *)(D_87F15B90 + 4) = 0;
    *(s32 *)(D_87F15B90 + 0x10) = 0;
    *(s32 *)(D_87F15B90 + 0x14) = 0;
    func_8004C8C0(0x1B9);
}

extern u32 func_8003570C(void);
void func_87F0C9D0(s32 arg0) {
    if (*(s32 *)(D_87F15B90 + 0x10) != 0 && arg0 == 0) {
        (*(s32 *)(D_87F15B90 + 0))++;
        *(s32 *)(D_87F15B90 + 4) = func_8003570C() % 100;
    }
}

void func_87F0CA30(void) {
    *(s32 *)(D_87F15B90 + 0) = 0;
    *(s32 *)(D_87F15B90 + 4) = 0;
    *(s32 *)(D_87F15B90 + 0x10) = 1;
}

void func_87F0CA58(void) {
    *(s32 *)(D_87F15B90 + 0x10) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32F5F0/func_87F0CA68.s")

void func_87F0CB24(void) {
    *(s32 *)(D_87F15B90 + 0x14) = 1;
    *(f32 *)(D_87F15B90 + 8) = 320.0f;
    *(f32 *)(D_87F15B90 + 0xC) = 0.0f;
}

void func_87F0CB58(void) {
    *(s32 *)(D_87F15B90 + 0x14) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32F5F0/func_87F0CB68.s")
#endif
