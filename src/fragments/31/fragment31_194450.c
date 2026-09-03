#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_882211D0(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void Util_Free(void *);
extern void func_88001900();
extern s32 D_880068B4;
extern s16 D_88234748;
extern void *D_88234820;
void func_882211F8(void) {
    func_88001900();
    D_880068B4 = (*(s32 *)((u8 *)(D_88234820) + (0x130)));
    D_88234748 = (*(s16 *)((u8 *)(D_88234820) + (0x2C)));
    Util_Free(D_88234820);
}

extern void func_88004990(u8, s32);
void func_8822123C(s32 arg0) {
    func_88004990(*(*(u8 **)((u8 *)(D_88234820) + (0))), 0);
    D_880068B8 = 1;
    (*(s32 *)((u8 *)(D_88234820) + (0x130))) = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194450/func_8822128C.s")

extern void func_889033FC(void *, void *);
void func_8822157C(void) {
    func_889033FC(*(void **)D_88234820, (u8 *)D_88234820 + 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194450/func_882215A8.s")
#endif
