#include "global.h"


#ifdef VERSION_US
/* mkdraft:func_8AF1C3A0 begin */
extern void func_800504BC(s16 *);
extern void func_8AC015B0(s16, s16, s32, s32, s16);
extern u8 D_8AF274A0[];
extern s16 D_8AF27920;
extern s16 D_8AF37798;

s32 func_8AF1C3A0(s32 mode, void *record) {
    s16 x;
    s16 y;
    void *preserved;
    s16 values[2];

    preserved = record;
    switch (mode) {
    case 0:
        *(u16 *)((u8 *)preserved + 2) &= 0xFFFD;
        break;
    case 1:
        func_800504BC(values);
        x = *(s16 *)((u8 *)preserved + 8) + values[0];
        y = *(s16 *)((u8 *)preserved + 0xA) + values[1];
        func_8AC015B0(x, y, (s32)(D_8AF274A0), D_8AF27920, D_8AF37798);
        break;
    }
    return 0;
}
/* mkdraft:func_8AF1C3A0 end */

/* mkdraft:func_8AF1C43C begin */
extern void func_800504BC(s16 *);
extern void func_8AC015B0(s16, s16, s32, s32, s16);
extern u8 D_8AF275E0[];
extern s16 D_8AF27928;
extern s16 D_8AF3779C;

s32 func_8AF1C43C(s32 mode, void *record) {
    s16 x;
    s16 y;
    void *preserved;
    s16 values[2];

    preserved = record;
    switch (mode) {
    case 0:
        *(u16 *)((u8 *)preserved + 2) &= 0xFFFD;
        break;
    case 1:
        func_800504BC(values);
        x = *(s16 *)((u8 *)preserved + 8) + values[0];
        y = *(s16 *)((u8 *)preserved + 0xA) + values[1];
        func_8AC015B0(x, y, (s32)(D_8AF275E0), D_8AF27928, D_8AF3779C);
        break;
    }
    return 0;
}
/* mkdraft:func_8AF1C43C end */

/* mkdraft:func_8AF1C4D8 begin */
extern void func_800504BC(s16 *);
extern void func_8AC015B0(s16, s16, s32, s32, s16);
extern u8 D_8AF277E0[];
extern s16 D_8AF27924;
extern s16 D_8AF3779A;

s32 func_8AF1C4D8(s32 mode, void *record) {
    s16 x;
    s16 y;
    void *preserved;
    s16 values[2];

    preserved = record;
    switch (mode) {
    case 0:
        *(u16 *)((u8 *)preserved + 2) &= 0xFFFD;
        break;
    case 1:
        func_800504BC(values);
        x = *(s16 *)((u8 *)preserved + 8) + values[0];
        y = *(s16 *)((u8 *)preserved + 0xA) + values[1];
        func_8AC015B0(x, y, (s32)(D_8AF277E0), D_8AF27924, D_8AF3779A);
        break;
    }
    return 0;
}
/* mkdraft:func_8AF1C4D8 end */

/* mkdraft:func_8AF1C574 begin */
extern void *D_8AF37778;
extern void *D_8AF37784;
extern void *D_8AF3777C;
extern void *D_8AF37788;
extern void *D_8AF37780;
extern void *D_8AF3778C;

void func_8AF1C574(void) {
    *(u16 *)((u8 *)D_8AF37778 + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF37784 + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF3777C + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF37788 + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF37780 + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF3778C + 2) &= ~2;
}
/* mkdraft:func_8AF1C574 end */

extern void *D_8AF37778;
extern void *D_8AF3777C;
extern void *D_8AF37780;
extern void *D_8AF37784;
extern void *D_8AF37788;
extern void *D_8AF3778C;
void func_8AF1C5F0(void) {
    (*(u16 *)((u8 *)(D_8AF37778) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF37778) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF37784) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF37784) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF3777C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3777C) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF37788) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF37788) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF37780) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF37780) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF3778C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3778C) + (2))) | 2);
}

void func_8AF1C66C(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x28) = arg1;
    *(s32 *)(arg0 + 0x2C) = arg2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20A610/func_8AF1C678.s")

extern s16 D_8AF37754;
extern s16 D_8AF37798;
extern s16 D_8AF3779A;
extern s16 D_8AF3779C;
extern s16 D_8AF3779E;

void func_8AF1C804(void) {
    D_8AF3779E = 0;
    D_8AF37798 = 0;
    D_8AF3779C = 0;
    D_8AF3779A = 0;
    D_8AF37754 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20A610/func_8AF1C830.s")

void func_8AF1CDAC(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (arg1 < value) {
        value -= arg2;
        if (value < arg1) value = arg1;
        *arg0 = value;
    }
}

void func_8AF1CDEC(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (value < arg1) {
        value += arg2;
        if (arg1 < value) value = arg1;
        *arg0 = value;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20A610/func_8AF1CE2C.s")

void func_8AF1DB30(void) {

}
#endif
