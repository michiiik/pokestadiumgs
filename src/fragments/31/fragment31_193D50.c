#include "global.h"


#ifdef VERSION_US
extern s32 func_88203FB4(void);
extern s32 func_8004C594(s32, s32);
extern void *func_8004C8A0(void *, s32, s32, s32);
extern void func_88903C50(void *, s16, s16, s32, u8, u8, u8, u8, u8,
                         s32 *, s32 *, void (*)(void), void (*)(void));
extern void func_88903B00(void);
extern void D_88000E4C(void);
extern s32 D_880068B4;
extern s32 D_880068B8;
extern s32 D_88234660;

void func_88220AD0(s16 arg0, s16 arg1) {
    u8 var_v0[512];

    func_8004C594(4, func_88203FB4());
    func_88903C50(func_8004C8A0(var_v0, 512, 31, 19), arg0, arg1, 4,
                 220, 220, 180, 2, 0, &D_880068B4, &D_880068B8,
                 func_88903B00, D_88000E4C);
    D_88234660 = 0;
}

extern void func_88004990(u8, u8);
extern u8 **D_88234800;
extern s32 D_880068B8;
void func_88220B80(void) {
    func_88004990(**D_88234800, 0);
    D_880068B8 = 1;
}

extern void func_8000612C(void);
void func_88220BB8(void) {
    func_8000612C();
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_193D50/func_88220BDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_193D50/func_88220E08.s")

void func_88220F40(void) {
    D_880068B8 = 0;
}

extern void func_88220AD0(s16, s16);
extern s32 D_80087200;
extern s32 D_88234660;
extern u32 D_88234810;
void Input_SetRepeatController(s32 value);
void func_88001900(void);
extern s32 D_880068B4;
void Util_Free(s32 arg0);
void func_88220F4C(void) {
    if (D_88234660 != 0) {
        func_88220AD0((*(s16 *)((u8 *)(D_88234810) + (0x23C))), (*(s16 *)((u8 *)(D_88234810) + (0x23E))));
    } else {
        Input_SetRepeatController(D_80087200);
        func_88001900();
        D_880068B4 = 1;
    }
    Util_Free((s32) D_88234810);
}

void func_88220FB8(void) {
    if (*(u16 *)((u8 *)D_80087200 + 8) & 0xC000) {
        func_88004990(**(u8 **)D_88234810, 0);
        D_880068B8 = 1;
    }
}

extern void func_889033A0(s32);
void func_8822100C(void) {
    func_889033A0((D_88234810 + 4));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_193D50/func_88221034.s")
#endif
