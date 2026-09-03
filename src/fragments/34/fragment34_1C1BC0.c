#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_885045B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88504704.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_885047B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88504828.s")

extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32 arg0, s32 arg1);
extern s32 func_80040E80(s32 arg0, void *arg1);
extern void MainPool_FinalizeAllocation(s32 arg0);
extern s32 func_80064C88(void);
extern void func_88504828(void);
extern u8 D_8850D228;
extern u8 D_8850D25C;
extern s32 D_88523000;
extern s32 D_88523004;
extern u8 D_885229A8;
extern s8 D_8852300C[];
extern s8 D_88523009;
void func_88504A54(void) {
    s32 state;
    state = MainPool_AllocState(main_pool_get_available(), 0);
    D_88523000 = func_80040E80(state, &D_8850D25C);
    D_88523004 = func_80040E80(state, &D_8850D228);
    MainPool_FinalizeAllocation(state);
    *(s32 *)((u8 *)&D_885229A8 + 0) = 0;
    *(s16 *)((u8 *)&D_885229A8 + 4) = 0;
    D_8852300C[0] = func_80064C88();
    D_8852300C[1] = -1;
    D_88523009 = 0;
    func_88504828();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88504AF0.s")

extern void func_8004AF18(s32 arg0, s16 arg1);
extern u8 D_885229A8;
extern s8 D_88523009;
extern s8 D_8852300A;
extern u16 D_8850D2C0;
extern f32 D_80087E50[];
void func_88504D9C(void) {
    s16 sp1E;
    s16 sp1C;
    s32 active;
    active = 0;
    switch (*(s32 *)&D_885229A8) {
    case 1:
        if (D_88523009 != -1) {
            active = 1;
            sp1E = D_88523009 * 0x8E + 0x7B;
            sp1C = 0x13D;
        }
        break;
    case 3:
        active = 1;
        sp1E = 0xEA;
        sp1C = (D_8852300A << 5) + 0x122;
        break;
    }
    if (active != 0) {
        func_8004AF18((s16)(D_80087E50[D_8850D2C0 >> 4] * 3.0f) + sp1E, sp1C);
    }
    *(s16 *)&D_8850D2C0 = (s16)D_8850D2C0 + 0x1000;
}

extern s8 D_8852300C[];
s32 func_88504E94(u8 arg0) {
    return D_8852300C[arg0];
}

extern s32 D_880068B8;

void func_88504EAC(void) {
    D_880068B8 = 0;
}

extern s32 D_880068B4;
extern void *D_885229A0;
extern void Util_Free(void *);
void func_88504EB8(void) {
    D_880068B4 = 1;
    Util_Free(D_885229A0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88504EE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505038.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505264.s")

extern void func_88505038(void *arg0, s32 arg1);
void func_885053E8(void *arg0) {
    s16 value;
    *(s16 *)((u8 *)arg0 + 0x16) = *(s16 *)((u8 *)arg0 + 0x16) - 1;
    value = *(s16 *)((u8 *)arg0 + 0x16);
    *(f32 *)((u8 *)arg0 + 0x1C) = (f32)(8 - value) / 8;
    if (value <= 0) {
        func_88505038(arg0, 3);
    }
}

extern void func_88505264(void);
void func_88505440(void) {
    func_88505264();
}

extern void func_88505038(void *arg0, s32 arg1);
extern s8 D_8852300D;
void func_88505460(void *arg0) {
    s16 value;
    *(s16 *)((u8 *)arg0 + 0x16) = *(s16 *)((u8 *)arg0 + 0x16) - 1;
    value = *(s16 *)((u8 *)arg0 + 0x16);
    *(s16 *)((u8 *)arg0 + 0x0C) = (s16)(0x207 - ((0x207 - *(s16 *)((u8 *)arg0 + 0x10)) * value) / 8);
    *(s16 *)((u8 *)arg0 + 0x0E) = (s16)(0xB2 - (value * -0xB3) / 8);
    if (value <= 0) {
        func_88505038(arg0, 1);
        D_8852300D = *(s16 *)((u8 *)arg0 + 4);
    }
}

void func_88505514(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x16))) = (s16) ((*(s16 *)((u8 *)(arg0) + (0x16))) - 1);
    (*(s16 *)((u8 *)(arg0) + (0x1A))) = (s16) ((s32) ((*(s16 *)((u8 *)(arg0) + (0x16))) * 0xFF) / 8);
}

void Trade_UpdateBoxSlotShrink(void *arg0)
{
  s16 temp_v0;
  func_88505264();
 *((s16 *) (((u8 *) arg0) + 0x16)) = (s16) ((*((s16 *) (((u8 *) arg0) + 0x16))) - 1); temp_v0 = *((s16 *) (((u8 *) arg0) + 0x16));
  *((f32 *) (((u8 *) arg0) + 0x1C)) = (f32) (((f32) temp_v0) / 8);
  if (temp_v0 <= 0)
  {
    func_88505038(arg0, 0);
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_885055A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505718.s")

extern s8 D_8852300A;
extern void func_88505718(void);
extern void func_88504EE8(void);
void func_885057BC(void) {
    if (D_8852300A == 1) {
        func_88505718();
        func_88504EE8();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_885057F4.s")

extern void func_800498C4(void);
extern void func_800496A4(s32 arg0, s32 arg1);
extern s32 func_8004C874(s32 arg0, s32 arg1);
extern void func_80048E30(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_800499EC(void);
extern void func_88504D9C(void);
extern s32 D_8800687C;
void func_885059B8(void) {
    s32 i;
    s32 value;
    s32 result;
    func_800498C4();
    func_800496A4(0x10, 1);
    result = func_8004C874(0x34, 6);
    func_80048E30(D_8800687C, 0xD8, 0xFE, result, 1);
    i = 0;
    value = 0x122;
    do {
        result = func_8004C874(0x34, i + 7);
        func_80048E30(D_8800687C, 0x112, value, result, 1);
        i++;
        value += 0x20;
    } while (i != 2);
    func_800499EC();
    func_88504D9C();
}

extern void func_880048D4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, void (*arg9)(void), void (*arg10)(void), void *arg11, void (*arg12)(void), s32 arg13, s32 arg14, s32 arg15);
extern void func_885057F4(void);
extern void func_885059B8(void);
extern void func_885057BC(void);
extern void *D_885229A0;
extern u8 D_885229A8;
extern s8 D_8852300A;
extern u8 D_88000E4C;
extern u8 D_8800EE34;
void func_88505A7C(void) {
    *(s32 *)((u8 *)&D_885229A8 + 0) = 3;
    D_8852300A = 0;
    func_880048D4(0, 3, 0xC5, 0xF1, 0, 1, 0xE6, 0xFF, 0xF0, func_885057F4, func_885059B8, &D_88000E4C, func_885057BC, 0, 0, 3);
    *(void **)((u8 *)D_885229A0 + 0x0C) = &D_8800EE34;
    *(s16 *)((u8 *)*(void **)((u8 *)D_885229A0 + 0x0C) + 0x10) = 0xF9;
    *(s16 *)((u8 *)*(void **)((u8 *)D_885229A0 + 0x0C) + 0x12) = 0x79;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505B58.s")

extern void func_88505A7C();
extern u8 D_885229A8;

void func_88505E9C(void) {
    (*(s16 *)((u8 *)(&D_885229A8) + (4))) = (s16) ((*(s16 *)((u8 *)(&D_885229A8) + (4))) - 1);
    if ((*(s16 *)((u8 *)(&D_885229A8) + (4))) <= 0) {
        func_88505A7C();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505EDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88506018.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88506618.s")
#endif
