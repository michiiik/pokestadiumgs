#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_882219B0(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void Util_Free(void *);
extern s32 D_880068B4;
extern s16 D_8823474A;
extern void *D_88234830;
void func_882219D8(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B4 = (*(s32 *)((u8 *)(D_88234830) + (0x130)));
    if ((*(s8 *)((u8 *)(D_88234830) + (0x12D))) == 1) {
        D_8823474A = (*(s16 *)((u8 *)(D_88234830) + (0x2C)));
    }
    Util_Free(D_88234830);
}

extern void func_88004990(u8, s32);
void func_88221A34(s32 (*arg0)()) {
    func_88004990(*(*(u8 **)((u8 *)(D_88234830) + (0))), 0);
    D_880068B8 = 1;
    (*(s32 *)((u8 *)(D_88234830) + (0x130))) = 0;
    arg0();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194C30/func_88221A8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194C30/func_88221AF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194C30/func_88221C54.s")

extern void func_889033FC(void *, void *);
void func_88221F28(void) {
    func_889033FC(*(void **)D_88234830, (u8 *)D_88234830 + 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194C30/func_88221F54.s")
#endif
