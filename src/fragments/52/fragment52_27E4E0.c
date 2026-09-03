#include "global.h"


void func_86400020(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86400028.s")
#endif

#ifdef VERSION_US
extern f32 func_87D00720(void *, void *, void *, f32 *, f32 *);
extern s32 func_87D00670(void *, void *, f32 *, void *, void *, f32 *);

s32 func_86400114(void *arg0, f32 arg1, void *arg2, void *arg3, void *arg4, f32 *arg5) {
    f32 sp30[2];
    f32 sp2C;
    s32 sp28;
    f32 sp24;
    f32 sp20;

    sp28 = 0;
    func_87D00720(arg0, arg2, arg3, sp30, &sp2C);
    if ((sp2C < arg1) &&
        (func_87D00670(arg0, arg4, &sp24, arg2, arg3, &sp20) != 0) &&
        (sp20 >= 0.0f) && (sp20 <= 1.0f)) {
        *arg5 = arg1 - sp2C;
        sp28 = 1;
    }
    return sp28;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864001E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864002CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864004B4.s")
#endif

#ifdef VERSION_US
extern void func_87F05FB0(s32, s32, s32, s32, s32);
extern s32 D_80094908;
void func_864007B8(s32 arg0, s32 arg1) {
    if (arg0 == 2) {
        func_87F05FB0(arg1 + 0x60, D_80094908 + 0x64, arg1 + 0x24, arg1 + 0x1E, arg1 + 0x30);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86400804.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864009D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86400DDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864012A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864013A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86401550.s")
#endif

#ifdef VERSION_US
extern void func_8002781C(s32, u8, void *);
extern f32 D_864099C0;
void func_864018B0(u8 *arg0, u8 *arg1) {
    if (!(*(s32 *)(arg0 + 0xC) & 0x20000000)) {
        *(s32 *)(arg1 + 0x38) = 0x14;
        *(f32 *)(arg1 + 0x1C) = 0.0f;
        *(s32 *)(arg0 + 0xC) |= 0x20000000;
        *(f32 *)(arg0 + 0x14) = D_864099C0;
        func_8002781C(0x5F03, *(u8 *)(arg1 + 3), arg1 + 0x58);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86401920.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86401D1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86401DBC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86401F60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86402158.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86402304.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86402688.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864028B8.s")
#endif

#ifdef VERSION_US
extern f32 D_86409A40;
extern f32 D_86409A44;
extern f64 D_86409A48;
extern f32 D_86409A50;
extern f32 D_86409A54;
extern f32 D_86409A58;

void func_86402A2C(u8 *arg0) {
    s32 flags = *(s32 *)(arg0 + 0xC);

    if ((flags & 0x80000000) && !(flags & 0x40000)) {
        if (*(f32 *)(arg0 + 0x4C) < D_86409A40) {
            *(f32 *)(arg0 + 0x14) = *(f32 *)(arg0 + 0x14) + D_86409A44;
            if ((f64)D_86409A48 < (f64)*(f32 *)(arg0 + 0x14)) {
                *(f32 *)(arg0 + 0x14) = D_86409A50;
            }
        } else {
            *(f32 *)(arg0 + 0x14) = *(f32 *)(arg0 + 0x14) - D_86409A54;
        }
    } else {
        *(f32 *)(arg0 + 0x14) = *(f32 *)(arg0 + 0x14) - D_86409A58;
    }
    *(f32 *)(arg0 + 0x4C) = *(f32 *)(arg0 + 0x14) + *(f32 *)(arg0 + 0x4C);
    if (*(f32 *)(arg0 + 0x4C) < 0.0f) {
        *(f32 *)(arg0 + 0x4C) = 0.0f;
        *(f32 *)(arg0 + 0x14) = *(f32 *)(arg0 + 0x14) * -0.75f;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86402B1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864033AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86403550.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_8640377C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864037C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86403B3C.s")
#endif

#ifdef VERSION_US
extern u8 *D_86416C00;
void func_86403CB4(void) { void *node; node = *(void **)(D_86416C00 + 0xE0C); while (node != NULL) { node = *(void **)((u8 *)node + 4); } }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86403CDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86403F5C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86404724.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86404824.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86404A0C.s")
#endif

#ifdef VERSION_US
void func_86404D48(u8 *arg0, u8 *arg1) {
    *(f32 *)(arg0 + 0x48) += *(f32 *)(arg1 + 0x2C);
    *(f32 *)(arg0 + 0x4C) += *(f32 *)(arg1 + 0x30);
    *(f32 *)(arg0 + 0x50) += *(f32 *)(arg1 + 0x34);
    *(f32 *)(arg1 + 0x2C) = 0.0f;
    *(f32 *)(arg1 + 0x30) = 0.0f;
    *(f32 *)(arg1 + 0x34) = 0.0f;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86404D8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86405138.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_8640533C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864055CC.s")
#endif

#ifdef VERSION_US
extern void func_86404D8C();
extern void func_8640533C();
extern void func_864055CC();
void func_86405778(void) {
    s32 temp_v0;

    temp_v0 = (*(s32 *)((u8 *)(D_86416C00) + (0x10)));
    switch (temp_v0) {                              /* irregular */
    case 3:
        func_864055CC();
        return;
    case 4:
        func_86404D8C();
        return;
    default:
        func_8640533C();
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864057E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86405BEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86405CB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86405E08.s")
#endif

#ifdef VERSION_US
extern u8 *D_86416C00;
extern void func_87C037C0(u8 *, s32);
extern s32 StageContext_GetFadeMode(void);
extern void func_86407034(void);
extern void func_864057E0(void);
extern void func_80007AEC(s32);
extern void func_87F00688(void);
extern void func_87F0277C(u8 *);

void func_86405EA4(void) {
    func_87C037C0(D_86416C00 + 0xCEC8, *(s32 *)(*(u8 **)(D_86416C00 + 0xB4) + 0xC));
    if (StageContext_GetFadeMode() == 1) {
        func_86407034();
        func_864057E0();
        func_80007AEC(0x14);
        *(s32 *)(D_86416C00 + 0x10) = 3;
        func_87F00688();
    }
    func_87F0277C(D_86416C00 + 0xE0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86405F28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_8640633C.s")
#endif

#ifdef VERSION_US
extern void *func_87F0A3E8(void *);
extern void func_8002781C(s32, u8, void *);
extern f32 D_864099C0;
extern void func_86406660(s32 arg0);
extern void func_864066B4(void);
void func_864064DC(void) {
    u8 *v0;
    void *v1;

    func_864066B4();
    v1 = func_87F0A3E8(D_86416C00 + 0x724);
    if (v1 != NULL) {
        v0 = D_86416C00;
        if (*(u8 *)(*(u8 **)(v0 + 0x70) + 0x2180) == 1) {
            func_86406660(2);
        } else {
            *(s32 *)(v0 + 0x10) = 6;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86406544.s")
#endif

#ifdef VERSION_US
extern void StageFade_StartFromTransparent(s32);
extern void func_800088A4(s32);
void func_86406660(s32 arg0) {
    (*(s32 *)((u8 *)(D_86416C00) + (0xCEB4))) = arg0;
    (*(s32 *)((u8 *)(D_86416C00) + (0x10))) = 7;
    (*(s32 *)((u8 *)(D_86416C00) + (0x68))) = 8;
    func_800088A4(0xFFFF);
    StageFade_StartFromTransparent(0xA);
}
#endif

#ifdef VERSION_US
extern void func_86405778(void);
extern void func_87F0277C(u8 *);
extern void func_86409260(u8 *);
extern void func_86401550(void);
void func_864066B4(void) {
    func_86405778();
    func_87F0277C(D_86416C00 + 0xE00);
    func_87F0277C(D_86416C00 + 0x3334);
    func_86409260(D_86416C00 + 0xB554);
    func_86401550();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86406710.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864068A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_864069DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86406C6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86406CF8.s")
#endif
