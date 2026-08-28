#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_88223320(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void Util_Free(s32);
extern s32 D_880068B4;
extern s32 D_88234850;
void func_88223348(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B4 = 1;
    Util_Free(D_88234850);
}

extern void func_88004990(u8, s32);
void func_88223384(void) {
    func_88004990(*(*(u8 **)((u8 *)(D_88234850) + 0)), 0);
    D_880068B8 = 1;
}

extern void func_880022B4(s32, s32, s32);
void func_882233BC(s32 arg0) {
    (*(s32 *)((u8 *)(D_88234850) + (0x30))) = arg0;
    if (arg0 != 0) {
        func_880022B4(D_88234850 + 4, 0xF00, 0);
        return;
    }
    func_880022B4(D_88234850 + 4, 0xF00, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_88223418.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_88223554.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_882235CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_88223850.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1965A0/func_882241B8.s")
#endif
