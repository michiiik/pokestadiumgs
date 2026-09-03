#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B00020.s")
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_86B000F0(s32 arg0, void *arg1) {
    s16 pad;
    s32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &sp28, &sp26, &sp24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(sp26 + 0x2000);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(sp24 - 0x2000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B00158.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B001C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B007D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B00994.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B00A3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B014E8.s")
#endif

#ifdef VERSION_US
extern u8 *D_86B181C0;
extern void func_800088A4(s32);
extern void StageFade_StartFromTransparent(s32);
void func_86B01720(s32 arg0) {
    *(s32 *)(D_86B181C0 + 0x18) = arg0;
    *(s32 *)D_86B181C0 = 0xC;
    *(s32 *)(D_86B181C0 + 4) = 0xD;
    func_800088A4((u16)0xFFFF);
    StageFade_StartFromTransparent(0xA);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B01770.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B01A94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B02180.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B021E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B023FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B03228.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0355C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B03628.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B04500.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B04870.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B04970.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B05194.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B052BC.s")
#endif

#ifdef VERSION_US
extern void func_87F026E8(s32, void *);
extern s32 D_87F119D8;
extern void *D_87F119DC;
void func_86B05428(void) {
    s32 var_v0;

    var_v0 = 0;
    (*(s8 *)((u8 *)(D_87F119DC) + (0x41))) = (s8) (*(s32 *)((u8 *)(D_87F119DC) + (0x20)));
    if ((*(s32 *)((u8 *)(D_87F119DC) + (0x1C))) >= 0x18) {
        var_v0 = 1;
    }
    if (var_v0 != 0) {
        func_87F026E8(D_87F119D8, D_87F119DC);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B05484.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B05548.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B05610.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B05738.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B057B0.s")
#endif

#ifdef VERSION_US
s16 MathUtil_Atan2s(f32 y, f32 x);
s16 func_86B07D58(f32 arg0, f32 arg1) {
    return (s16) ((s32) (MathUtil_Atan2s(arg0, -arg1) + 0x3FFF) % 65535);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B07D94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B07FB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08088.s")
#endif

#ifdef VERSION_US
extern f32 D_86B0DFA8;
extern f64 D_86B0DFB0;
f32 func_86B080D4(f32 arg0, f32 arg1) {
    f32 var_fv1;

    if (arg1 <= arg0) {
        var_fv1 = arg0 - arg1;
    } else {
        var_fv1 = arg1 - arg0;
    }
    if (D_86B0DFA8 < var_fv1) {
        var_fv1 = (f32) (D_86B0DFB0 - (f64) var_fv1);
    }
    return var_fv1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08120.s")
#endif

#ifdef VERSION_US
extern void func_87F0277C(s32 *);
extern u8 D_86B0E1A8;
extern u8 D_86B0E7F8;
extern u8 D_86B0E9A0;
extern u8 D_86B0EE60;
extern u8 D_86B12AD0;
extern u8 D_86B13A68;
void func_86B081B4(void) {
    func_87F0277C(&D_86B0E9A0);
    func_87F0277C(&D_86B0EE60);
    func_87F0277C(&D_86B12AD0);
    func_87F0277C(&D_86B13A68);
    func_87F0277C(&D_86B0E1A8);
    func_87F0277C(&D_86B0E7F8);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08214.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08978.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08B74.s")
#endif

void func_86B08CEC(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08CF4.s")
#endif

void func_86B08E08(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08E10.s")
#endif

void func_86B08F18(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08F20.s")
#endif

void func_86B09378(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B09380.s")
#endif

void func_86B09478(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B09480.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0952C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B095B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B09834.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0990C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0B04C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0B500.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0B608.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0B6CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0B7B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0B9A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0BA28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0BB24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0BF2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0CB1C.s")
#endif
