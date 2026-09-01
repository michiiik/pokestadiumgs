#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19E800/func_8822B580.s")

extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_8822B614(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern u32 D_88234910;
extern s8 D_889041B8;
void func_8822B63C(void) {
    if (*(s32 *)((u8 *)(D_88234910) + 0x18C) == 0) {
        Input_SetRepeatController(D_80087200);
        *(s32 *)((u8 *)(*(void **)((u8 *)(D_88234910) + 0)) + 0x2C) = 1;
        *(s32 *)((u8 *)(D_88234910) + 0x48) = 1;
        D_889041B8 = 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19E800/func_8822B6A4.s")

extern u32 D_88234910;
extern void func_8821D930(s32);
void func_8822B7E4(void) { func_8821D930((D_88234910 + 88)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19E800/func_8822B80C.s")

s32 func_8821C0B0();
extern void func_8822AF00(s32);
extern s32 D_882345F4;

void func_8822B8FC(void) {
    if (func_8821C0B0() == 0) {
        func_8822AF00(D_882345F4 + 0x3C);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19E800/func_8822B930.s")


void func_8822B9C4(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19E800/func_8822B9EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19E800/func_8822BAF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19E800/func_8822BC58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19E800/func_8822BE00.s")
#endif
