#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0A340.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0A3A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0A4AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0A6E4.s")

extern void func_8004A858(s32, s32, u16, u16, s32 *, s32 *);
extern u8 D_8AF26450;
extern u8 D_8AF26454;
s32 func_8AF0A800(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0x20)));
    func_8004A858(0, 0, (*(u16 *)((u8 *)(temp_v0) + (4))), (*(u16 *)((u8 *)(temp_v0) + (6))), &D_8AF26450, &D_8AF26454);
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0A850.s")

s32 func_8004C990(s32, s32);
extern s32 D_8AF2D428;
extern s32 D_8AF2D42C;
extern s32 D_8AF2D430;
extern s32 D_8AF2D434;
extern s32 D_8AF2D438;

void func_8AF0A888(void) {
    D_8AF2D428 = func_8004C990(0xAD, 0);
    D_8AF2D42C = func_8004C990(0xAD, 1);
    D_8AF2D430 = func_8004C990(0xAD, 2);
    D_8AF2D434 = func_8004C990(0xAD, 3);
    D_8AF2D438 = func_8004C990(0xAD, 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0A900.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0AAF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0AB84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0ACDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0B544.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0B724.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0B7BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0B850.s")

extern void func_80043E70(s32, s32);
extern s32 D_8AF2694C;

void func_8AF0BB04(void) {
    if (D_8AF2694C != 0) {
        func_80043E70(D_8AF2694C, 0);
    }
}
#endif
