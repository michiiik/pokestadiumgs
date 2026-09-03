#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_379450/func_84109BC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_379450/func_84109E18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_379450/func_8410A074.s")

s32 func_8410A274(u8 *arg0, s32 arg1) {
    return 0;
}

extern u8 *D_80094910;
s32 func_8410A284(s32 arg0, s32 arg1) {
    u8 *ptr = D_80094910;
    if (arg0 == 2) {
        *(s16 *)(ptr + 0x18) = 3;
    }
    return 0;
}

s32 func_8410A2A8(s32 arg0, s32 arg1) {
    u8 *ptr = D_80094910;
    if (arg0 == 2) {
        *(s16 *)(ptr + 0x18) = 0;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_379450/func_8410A2C8.s")

extern s32 D_84190204;
extern u8 D_800D0510[];
extern void func_8000766C(u8 *, s32, s32, s32, s32);
extern void GfxImage_FillCurrent(u8 *, s32);
extern s32 func_8410A2C8(s32);
void func_8410A444(void) {
    s32 value = D_84190204;
    if (value == 0) {
        func_8000766C(D_800D0510, 0, 0, 0x140, 0xF0);
    } else if (value == -1) {
        GfxImage_FillCurrent(D_800D0510, 1);
    } else if ((u32)value < 0x10000) {
        s32 converted = func_8410A2C8(value & 0xFFFF);
        GfxImage_FillCurrent(D_800D0510, converted & 0xFFFF);
    } else {
        GfxImage_FillCurrent(D_800D0510, 1);
    }
}

extern f32 D_80128C54[];
void func_8410A4EC(f32 arg0) {
    D_80128C54[1] = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_379450/func_8410A4F8.s")

extern s32 D_84190200;
extern s32 D_84190208;
extern s32 D_8419020C;
extern u8 D_84183548[];
extern void func_8410A4F8(u8, u8, u8, u8);
extern void func_8410A4EC(f32);
extern s32 func_80040E80(s32, u8 *);
void func_8410A524(s32 arg0, s32 arg1, s32 (*arg2)(s32, s32)) {
    D_84190208 = arg0;
    func_8410A4F8(0xFF, 0xFF, 0xFF, 0);
    func_8410A4EC(1.0f);
    D_84190200 = arg2(0, 0);
    D_8419020C = func_80040E80(arg1, D_84183548);
    D_84190204 = arg2(1, 0);
}

extern s32 D_84190210;
extern u8 D_84183610[];
void func_8410A5BC(s32 arg0, s32 arg1, s32 arg2) {
    D_84190210 = func_80040E80(arg1, D_84183610);
}
#endif
