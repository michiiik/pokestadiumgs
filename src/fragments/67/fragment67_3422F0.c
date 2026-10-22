#include "global.h"


#ifdef VERSION_US
extern s16 D_82919D2E;
extern s16 D_82919D30;
s32 func_829057F0(s32 arg0, u8 *arg1) {
    if (arg0 == 2) {
        arg1[0x18] = 0xFF;
        arg1[0x19] = 0xFF;
        arg1[0x1A] = 0xFF;
        *(s16 *)(arg1 + 0x1C) = D_82919D2E + 0x2000;
        *(s16 *)(arg1 + 0x1E) = D_82919D30 + 0x2000;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_82905830.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_82905A88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_82905CE4.s")

s32 func_82905EE4(s32 arg0, u8 *arg1) {
    arg1[0x18] = 100;
    arg1[0x19] = 100;
    arg1[0x1A] = 100;
    return 0;
}

extern s16 D_829199F8;
s32 func_82905F00(s32 arg0, u8 *arg1) { if (arg0 == 0) *(s16 *)(arg1 + 0x1A) = 0; if (arg0 == 2) { if (D_829199F8 >= 7) *(s16 *)(arg1 + 0x1A) = 1; else *(s16 *)(arg1 + 0x1A) = 0; } return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_82905F40.s")

/* mkdraft:func_829060BC begin */
extern s32 D_82919DC8;
extern u8 D_800D0510[];
extern void func_8000766C(u8 *, s32, s32, s32, s32);
extern void GfxImage_FillCurrent(u8 *, s32);
extern s32 func_82905F40(s32);

void func_829060BC(void) {
    s32 value = D_82919DC8;
    if (value == 0) {
        func_8000766C(D_800D0510, 0, 0, 0x140, 0xF0);
    } else if (value == -1) {
        GfxImage_FillCurrent(D_800D0510, 1);
    } else if ((u32)value < 0x10000) {
        s32 converted = func_82905F40(value & 0xFFFF);
        GfxImage_FillCurrent(D_800D0510, converted & 0xFFFF);
    } else {
        GfxImage_FillCurrent(D_800D0510, 1);
    }
}
/* mkdraft:func_829060BC end */

extern f32 D_80128C54[];

void func_82906164(f32 arg0) {
    D_80128C54[1] = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_3422F0/func_82906170.s")

extern s32 D_82919D24;
extern s32 D_82919DC0;
extern void *D_82919DC4;
extern s32 D_82919DC8;
extern u8 D_82912228[];
extern void func_82906170(u8, u8, u8, u8);
extern void *process_geo_layout(void *, void *);

void func_829061CC(s32 arg0, void *arg1, s32 (*arg2)(s32, s32)) {
    D_82919D24 = arg0;
    func_82906170(255, 255, 255, 0);
    func_82906164(1.0f);
    D_82919DC0 = arg2(0, 0);
    D_82919DC4 = process_geo_layout(arg1, D_82912228);
    D_82919DC8 = arg2(1, 0);
}

extern s32 D_82919DC0;
extern s32 D_82919DC8;
void func_82906264(s32 (*arg0)(s32, s32)) {
    D_82919DC0 = arg0(0, 0);
    D_82919DC8 = arg0(1, 0);
}
#endif
