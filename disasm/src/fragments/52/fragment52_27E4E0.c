#include "global.h"


void func_86400020(void) {
}

#ifdef VERSION_US
extern u8 D_86409668[];
extern u8 D_86409688[];
extern u8 D_864096E8[];
extern void func_87D00648(void *, void *, void *);
extern f32 func_87D0059C(f32 *, f32 *);
void func_86400028(void)
{
  u8 *var_s0;
  u8 *table;
  s32 var_s1;
  var_s0 = D_86409688;
  table = D_86409668;
 var_s1 = 0; do { u8 *temp_s2; u8 *temp_a1; u8 *temp_a2;
    temp_s2 = var_s0 + 0xC;
    temp_a1 = table + (var_s0[0] << 3);
    temp_a2 = table + (var_s0[1] << 3);
    *((f32 *) (var_s0 + 4)) = (*((f32 *) (temp_a2 + 0))) - (*((f32 *) (temp_a1 + 0)));
    *((f32 *) (var_s0 + 8)) = (*((f32 *) (temp_a2 + 4))) - (*((f32 *) (temp_a1 + 4)));
    func_87D00648(temp_s2, temp_a1, temp_a2);
    func_87D0059C((f32 *) temp_s2, (f32 *) (var_s0 + 0x10));
    var_s1 += 1;
    var_s0 += 0x18;
  }
  while (var_s1 < 4);
  var_s0 = D_864096E8;
  var_s1 = 0;
  do
  {
    u8 *temp_v0;
    temp_v0 = table + (var_s0[0] << 3);
    *((f32 *) (var_s0 + 4)) = *((f32 *) (temp_v0 + 0));
    *((f32 *) (var_s0 + 8)) = *((f32 *) (temp_v0 + 4));
    func_87D0059C((f32 *) (var_s0 + 4), (f32 *) (var_s0 + 8));
    var_s1 += 1;
    var_s0 += 0xC;
  }
  while (var_s1 != 4);
}
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
extern u8 *D_86416C00;
extern void func_864009D4(void);
extern u8 *func_87F025B8(void *, void *);
extern void func_8003F1DC(u8 *);
extern void func_8003F114(u8 *, s32, s32, s32);
void func_864012A0(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    u8 *object;
    u8 *child;
    u8 *base;

    object = func_87F025B8(D_86416C00 + 0xE00, (void *)func_864009D4);
    if (object != 0) {
        child = *(u8 **)(object + 0x20);
        *(u8 **)(object + 0x38) = object;
        base = object + 0x24;
        func_8003F1DC(base);
        func_8003F114(base, 0, -1, *(s32 *)(D_86416C00 + 0x7B4));
        *(s32 *)(object + 0x0C) |= 0x10000000;
        *(s32 *)(object + 0x1C) = 0;
        *(f32 *)(object + 0x48) = arg1;
        *(f32 *)(object + 0x4C) = arg2;
        *(f32 *)(object + 0x50) = arg3;
        *(s16 *)(object + 0x42) = -0x4000;
        *(f32 *)(object + 0x54) = 2.5f;
        *(f32 *)(object + 0x58) = 2.5f;
        *(f32 *)(object + 0x5C) = 2.5f;
        *(f32 *)(object + 0x10) = 0.0f;
        *(f32 *)(object + 0x14) = 0.0f;
        *(f32 *)(object + 0x18) = 0.0f;
        *(s32 *)(child + 0x00) = 0;
        *(u8 *)(child + 0x04) = *(s32 *)((u8 *)arg0 + 0x00);
        *(u8 *)(child + 0x05) = *(s32 *)((u8 *)arg0 + 0x0C);
        *(u8 *)(child + 0x06) = *(s32 *)((u8 *)arg0 + 0x04);
    }
}
void func_864012A0_padding(void) {
}
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
extern f32 D_864099DC; extern f32 D_864099E0; extern f32 D_864099E4; extern f32 D_864099E8; extern f32 D_864099EC; extern f32 D_864099F0; extern f32 D_864099F4; extern f32 D_864099F8;
s32 func_86401F60(void *arg0) {
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_v1;

    temp_fv0 = *(f32 *)((u8 *)arg0 + 0x48);
    var_v1 = 0;
    if (*(f32 *)((u8 *)arg0 + 0x48) <= D_864099DC) {
        var_v1 = 0x200;
    }
    if (D_864099E0 <= *(f32 *)((u8 *)arg0 + 0x48)) {
        var_v1 = (var_v1 | 0x100) & 0xFFFF;
    }
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x50);
    if (temp_fv1 <= D_864099E4) {
        var_v1 = (var_v1 | 0x800) & 0xFFFF;
    }
    if (D_864099E8 <= temp_fv1) {
        var_v1 = (var_v1 | 0x400) & 0xFFFF;
    }
    if ((*(f32 *)((u8 *)arg0 + 0x48) <= -148.0f) &&
        (D_864099EC <= *(f32 *)((u8 *)arg0 + 0x48)) &&
        (temp_fv1 > -92.5f) && (temp_fv1 < 92.5f)) {
        var_v1 = (var_v1 | 0x100) & 0xFFFF;
    }
    if ((*(f32 *)((u8 *)arg0 + 0x48) >= 148.0f) &&
        (*(f32 *)((u8 *)arg0 + 0x48) <= D_864099F0) &&
        (temp_fv1 > -92.5f) && (temp_fv1 < 92.5f)) {
        var_v1 = (var_v1 | 0x200) & 0xFFFF;
    }
    if ((temp_fv1 <= -92.5f) && (D_864099F4 <= temp_fv1) &&
        (*(f32 *)((u8 *)arg0 + 0x48) > -148.0f) &&
        (*(f32 *)((u8 *)arg0 + 0x48) < 148.0f)) {
        var_v1 = (var_v1 | 0x400) & 0xFFFF;
    }
    if ((temp_fv1 >= 92.5f) && (temp_fv1 <= D_864099F8) &&
        (*(f32 *)((u8 *)arg0 + 0x48) > -148.0f) &&
        (*(f32 *)((u8 *)arg0 + 0x48) < 148.0f)) {
        var_v1 = (var_v1 | 0x800) & 0xFFFF;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86402158.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86402304.s")
#endif

#ifdef VERSION_US
extern f32 D_86409A28;
extern f32 D_86409A2C;
extern s32 func_80001FF0(void);
void func_86402688(u8 *arg0, u16 arg1) {
    u8 *state;
    s32 random_value;
    s32 next_random;

    state = *(u8 **)(arg0 + 0x20);
    if (*(s32 *)(arg0 + 0x0C) & 0x02000000) {
        if ((((f32)func_80001FF0() / 60.0f) * 10.0f) >= 0.0f) {
            random_value = (s32)((((f32)func_80001FF0() / 60.0f) * 10.0f) + 0.5f);
        } else {
            random_value = (s32)((((f32)func_80001FF0() / 60.0f) * 10.0f) - 0.5f);
        }
        if (random_value < *(s32 *)(arg0 + 0x1C)) {
            *(s32 *)(arg0 + 0x0C) &= 0xFDFFFFFF;
        } else if (arg1 & 0x8000) {
            if ((((f32)func_80001FF0() / 60.0f) * 10.0f) >= 0.0f) {
                next_random = (s32)((((f32)func_80001FF0() / 60.0f) * 10.0f) + 0.5f);
            } else {
                next_random = (s32)((((f32)func_80001FF0() / 60.0f) * 10.0f) - 0.5f);
            }
            *(f32 *)(state + 0x18) += (D_86409A28 / (f32)func_80001FF0()) * D_86409A2C *
                                      (1.0f - ((f32)*(s32 *)(arg0 + 0x1C) / (f32)next_random));
            *(s32 *)(arg0 + 0x0C) &= 0xFDFFFFFF;
            *(s32 *)(state + 0x20) = 0x1E;
        }
    }
}
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
extern f32 func_87D0059C(f32 *, f32 *);
void func_8640377C(void *arg0, void *arg1) {
    f32 values[2];
    f32 *first = &values[0];
    f32 *second = &values[1];

    *first = *(f32 *)((u8 *)arg0 + 0x48) - *(f32 *)((u8 *)arg1 + 0);
    *second = *(f32 *)((u8 *)arg0 + 0x50) - *(f32 *)((u8 *)arg1 + 4);
    func_87D0059C(first, second);
}
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
extern u8 *D_86416C00;
extern void func_87F0277C(u8 *);
extern s32 func_87F08208(u8 *);
extern void StageContext_SetClearColor(s32);
extern void StageFade_StartFromTransparent(s32);
extern void func_800225C4(s32);
extern void func_800279C4(s32);
extern void func_86406660(s32);
extern void func_800226C0(s32);
void func_86405E08(void) {
    s32 state;

    func_87F0277C(D_86416C00 + 0xE0);
    state = func_87F08208(D_86416C00 + 0xA8);
    switch (state) {
    case 1:
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0x14);
        *(s32 *)(D_86416C00 + 0x10) = 2;
        func_800225C4(0x28);
        func_800279C4(0xCF0B);
        break;
    case 2:
        func_86406660(0);
        func_800226C0(3);
        break;
    }
}
#endif

#ifdef VERSION_US
extern u8 *D_86416C00;
extern void func_87C037C0(u8 *, s32);
extern s32 StageContext_GetFadeMode(void);
extern void func_86407034(void);
extern void func_864057E0(void);
extern void StageFade_StartFromOpaque(s32);
extern void func_87F00688(void);
extern void func_87F0277C(u8 *);

void func_86405EA4(void) {
    func_87C037C0(D_86416C00 + 0xCEC8, *(s32 *)(*(u8 **)(D_86416C00 + 0xB4) + 0xC));
    if (StageContext_GetFadeMode() == 1) {
        func_86407034();
        func_864057E0();
        StageFade_StartFromOpaque(0x14);
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
extern void func_800088DC(void);
extern void GfxImage_FillCurrent(void *, u16);
extern void func_8000766C(void *, s32, s32, s32, s32);
extern s32 func_87F00930(void);
extern void GeoRender_AdvanceFrameCounter(void);
extern u8 D_800D0510;
extern u8 *D_86416C00;
extern void func_8003C6B8(s32);
extern void func_864082A8(void);
extern void func_87F0A5BC(u8 *);
extern void func_87F07FE8(u8 *);
extern void func_87F022F0(void);
extern void func_87F01D44(void);
extern void func_87F0C88C(u8 *);
extern void func_80008648(void);
void func_86406544(void) {
    s32 flags;

    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 0x401);
    func_8000766C(&D_800D0510, 0, 0, 0x140, 0xF0);
    if (func_87F00930() == 0) {
        GeoRender_AdvanceFrameCounter();
    }
    func_8003C6B8(*(s32 *)(D_86416C00 + 0x6C));
    func_864082A8();
    if (*(s32 *)(D_86416C00 + 0x10) == 5) {
        func_87F0A5BC(D_86416C00 + 0x724);
    }
    flags = *(s32 *)(D_86416C00 + 0xCEB0);
    if (flags & 1) {
        func_87F07FE8(D_86416C00 + 0xA8);
        flags = *(s32 *)(D_86416C00 + 0xCEB0);
    }
    if (flags & 2) {
        func_87F022F0();
    }
    if (func_87F00930() == 1) {
        func_87F01D44();
    }
    func_87F0C88C(D_86416C00 + 0x9C);
    func_80008648();
}
#endif

#ifdef VERSION_US
extern void StageFade_StartFromTransparent(s32);
extern void StageContext_SetClearColor(s32);
void func_86406660(s32 arg0) {
    (*(s32 *)((u8 *)(D_86416C00) + (0xCEB4))) = arg0;
    (*(s32 *)((u8 *)(D_86416C00) + (0x10))) = 7;
    (*(s32 *)((u8 *)(D_86416C00) + (0x68))) = 8;
    StageContext_SetClearColor(0xFFFF);
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
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_864069DC(void);
extern void func_86406544(void);
void func_86406C6C(void)
{
  struct Func86406C6CState {
    u8 pad0[0x10];
    s32 status;
    u8 pad1[0xCEAC - 0x14];
    s32 counter;
  };

  func_800086A4(2);
  StageFade_StartFromOpaque(0xA);
  do
  {
    ((struct Func86406C6CState *)D_86416C00)->counter =
        ((struct Func86406C6CState *)D_86416C00)->counter + 1;
    func_80064D28();
    func_864069DC();
    func_86406544();
  }
  while (((struct Func86406C6CState *)D_86416C00)->status != 8);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_27E4E0/func_86406CF8.s")
#endif
