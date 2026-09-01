#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A00020.s")
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_86A000DC(s32 arg0, void *arg1) {
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
s32 func_86A00144(s32 arg0, void *arg1) {
    s16 pad;
    s32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &sp28, &sp26, &sp24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(-0x2000 - sp26);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(sp24 + 0x6000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A001B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A003A8.s")
#endif

void func_86A004AC(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A004B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A012D4.s")
#endif

#ifdef VERSION_US
extern u8 *D_86A46548;
extern void StageContext_SetClearColor(s32);
extern void StageFade_StartFromTransparent(s32);
void func_86A01480(s32 arg0) {
    *(s32 *)(D_86A46548 + 0x18) = arg0;
    *(s32 *)D_86A46548 = 8;
    *(s32 *)(D_86A46548 + 4) = 9;
    StageContext_SetClearColor((u16)0xFFFF);
    StageFade_StartFromTransparent(0xA);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A014D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0167C.s")
#endif

#ifdef VERSION_US
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_86A0167C(void);
extern void func_86A012D4(void);
extern u8 *D_86A46548;
void func_86A01C5C(void) {
    func_800086A4(2);
    StageFade_StartFromOpaque(0xA);
    do {
        func_80064D28();
        func_86A0167C();
        func_86A012D4();
    } while (*(s32 *)D_86A46548 != 9);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A01CC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A01EF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A02A9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A03234.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A036F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A03B10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A03D0C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A03DDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A03F48.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0405C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A04100.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A041D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A046A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A04C04.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A05344.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A05504.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A05678.s")
#endif

#ifdef VERSION_US
s32 func_86A0585C(f32 arg0, f32 arg1) {
    if (arg1 < -140.0f) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0588C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A059AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A05AAC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A05B4C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A05C94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A05DCC.s")
#endif

#ifdef VERSION_US
extern s16 D_86A45264[];
extern s32 MathUtil_Atan2s(f32, f32);
void func_86A0638C(s32 arg0, f32 arg1, f32 arg2) {
    if ((arg1 != 0.0f) || (arg2 != 0.0f)) {
        D_86A45264[arg0] = (s16)((MathUtil_Atan2s(arg1, -arg2) + 0x3FFF) % 0xFFFF);
    }
}
#endif

#ifdef VERSION_US
extern s16 D_86A45254[];
extern s32 MathUtil_Atan2s(f32, f32);
void func_86A06400(s32 arg0, f32 arg1, f32 arg2) {
    if ((arg1 != 0.0f) || (arg2 != 0.0f)) {
        D_86A45254[arg0] = (s16)((MathUtil_Atan2s(arg1, -arg2) + 0x3FFF) % 0xFFFF);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A06474.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A06650.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A066F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A06740.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A06A1C.s")
#endif

#ifdef VERSION_US
extern u8 D_86A443F0[];
void func_86A06BDC(s32 arg0) {
    u8 *p4 = D_86A443F0 + (arg0 << 2);
    u8 *p8 = D_86A443F0 + (arg0 << 3);
    if (*(s32 *)(p4 + 0x64)) {
        *(f32 *)(p8 + 0x44) += *(f32 *)(p8 + 0x74) + *(f32 *)(p8 + 0x94);
        *(f32 *)(p8 + 0x48) += *(f32 *)(p8 + 0x78) + *(f32 *)(p8 + 0x98);
        *(s32 *)(p4 + 0x64) = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A06C3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A06D04.s")
#endif

#ifdef VERSION_US
extern void func_87F0277C(s32 *);
extern u8 D_86A0FEA0;
extern u8 D_86A104F0;
extern u8 D_86A10B38;
extern u8 D_86A11190;
extern u8 D_86A1AAD0;
extern u8 D_86A2DD40;
extern u8 D_86A40FA0;
extern s32 D_86A4459C;
void func_86A06D88(void) {
    (*(s32 *)((u8 *)(D_86A443F0) + (0xEC0))) = 0;
    (*(s32 *)((u8 *)(D_86A443F0) + (0x1680))) = 0;
    func_87F0277C(&D_86A11190);
    D_86A4459C = 0;
    func_87F0277C(&D_86A1AAD0);
    func_87F0277C(&D_86A2DD40);
    func_87F0277C(&D_86A40FA0);
    func_87F0277C(&D_86A104F0);
    func_87F0277C(&D_86A0FEA0);
    func_87F0277C(&D_86A10B38);
}
#endif

void func_86A06E0C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A06E14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A07124.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A07334.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A095A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0B49C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0B5CC.s")
#endif

#ifdef VERSION_US
extern void func_87F026E8(s32, void *);
extern s32 D_87F119D8;
extern void *D_87F119DC;
void func_86A0B66C(void) {
    f32 temp_fv0;
    s32 var_v0;

    var_v0 = 0;
    (*(f32 *)((u8 *)(D_87F119DC) + (0x48))) = (f32) ((*(f32 *)((u8 *)(D_87F119DC) + (0x10))) + (*(f32 *)((u8 *)(D_87F119DC) + (0x48))));
    temp_fv0 = (*(f32 *)((u8 *)(D_87F119DC) + (0x48)));
    if ((temp_fv0 < -270.0f) || (temp_fv0 > 270.0f)) {
        var_v0 = 1;
    }
    if (var_v0 != 0) {
        func_87F026E8(D_87F119D8, D_87F119DC);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0B6F8.s")
#endif

#ifdef VERSION_US
extern u8 D_86A42D70;
extern void *D_87F119DC;
void func_86A0B7A0(void)
{
  s32 new_var;
  void *temp_a0;
  new_var = *((s32 *) (((u8 *) D_87F119DC) + 0x20));
  temp_a0 = (new_var * 0x168) + (&D_86A42D70);
  *((f32 *) (((u8 *) D_87F119DC) + 0x48)) = (f32) (*((f32 *) (((u8 *) temp_a0) + 0x24)));
  *((f32 *) (((u8 *) D_87F119DC) + 0x50)) = (f32) (*((f32 *) (((u8 *) temp_a0) + 0x2C)));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0B7F0.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
extern s32 D_86A104EC;
void func_86A0B8A4(s32 arg0, s32 arg1) {
    s32 pad[2];
    s32 temp_v0;

    if (arg0 == 5) {
        temp_v0 = func_8004C990(0x133, 0);
        gDPPipeSync(D_800D0510++);
        gDPSetEnvColor(D_800D0510++, 0, 0, 0, 0x80);
        gDPSetCombine(D_800D0510++, 0xFCFFD3FF, 0xFFFEFE38);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60((u8 *)temp_v0));
        gSPDisplayList(D_800D0510++, D_86A104EC);
        func_8003CD84();
    }
}
#endif

#ifdef VERSION_US
extern f32 D_86A0F814;
void func_86A0B98C(void) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    s32 temp_v1;
    s32 var_a0;

    var_a0 = 0;
    *(f32 *)((u8 *)D_87F119DC + 0x48) =
        *(f32 *)&D_86A443F0[(*(s32 *)((u8 *)D_87F119DC + 0x20) << 3) + 4];
    *(f32 *)((u8 *)D_87F119DC + 0x50) =
        *(f32 *)&D_86A443F0[(*(s32 *)((u8 *)D_87F119DC + 0x20) << 3) + 8];
    temp_v1 = *(s32 *)((u8 *)D_87F119DC + 0x1C);
    if (temp_v1 < 0x14) {
        temp_fv0 = (f32)temp_v1 * D_86A0F814;
        *(f32 *)((u8 *)D_87F119DC + 0x5C) = temp_fv0;
        *(f32 *)((u8 *)D_87F119DC + 0x58) = temp_fv0;
        *(f32 *)((u8 *)D_87F119DC + 0x54) = temp_fv0;
    } else {
        *(f32 *)((u8 *)D_87F119DC + 0x5C) = 1.0f;
        temp_fv0_2 = *(f32 *)((u8 *)D_87F119DC + 0x5C);
        *(f32 *)((u8 *)D_87F119DC + 0x58) = temp_fv0_2;
        *(f32 *)((u8 *)D_87F119DC + 0x54) = temp_fv0_2;
    }
    if (*(s32 *)&D_86A443F0[(*(s32 *)((u8 *)D_87F119DC + 0x20) << 2) + 0xE8] != 5) {
        var_a0 = 1;
    }
    if (var_a0 != 0) {
        func_87F026E8(D_87F119D8, D_87F119DC);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0BA80.s")
#endif

#ifdef VERSION_US
extern void *D_8009491C;
extern u32 D_86A11184;
extern u8 *D_86A11188;
void func_86A0BB40(s32 arg0, s32 arg1) {
    void *context;
    s32 temp_v0;

    if (arg0 == 5) {
        context = D_8009491C;
        temp_v0 = *(s32 *)((u8 *)context + 0x14);
        switch (temp_v0) {
        case 0:
            gDPSetPrimColor(D_800D0510++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
            gDPSetEnvColor(D_800D0510++, 0, 0, 0x9B, 0xFF);
            break;
        case 1:
            gDPSetPrimColor(D_800D0510++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
            gDPSetEnvColor(D_800D0510++, 0, 0x82, 0, 0xFF);
            break;
        case 2:
            gDPSetPrimColor(D_800D0510++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
            gDPSetEnvColor(D_800D0510++, 0x9B, 0, 0, 0xFF);
            break;
        case 3:
            gDPSetPrimColor(D_800D0510++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
            gDPSetEnvColor(D_800D0510++, 0xC3, 0x64, 0, 0xFF);
            break;
        }
        gDPSetCombine(D_800D0510++, 0x30B3FF, 0x5FFEFE38);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60(D_86A11188));
        gSPDisplayList(D_800D0510++, D_86A11184);
        func_8003CD84();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0BD34.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0C7B4.s")
#endif

#ifdef VERSION_US
typedef struct {
    f32 unk0;
    f32 unk4;
} Pair;
typedef struct {
    s32 pad;
    Pair pair;
} Local;
extern f32 D_86A443F4[];
extern u8 D_86A0F004[];
extern u8 D_800CE060[];
extern s32 func_86A0C9B4(s32, s32);
extern void func_86A0CED8(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3);
void func_86A0C8DC(s32 arg0) {
    Local local;
    s32 temp_v0;
    if (*(f32 *)((u8 *)D_86A443F4 + (arg0 << 3)) > 0.0f) {
        temp_v0 = func_86A0C9B4(arg0, 1);
        local.pair = *(Pair *)((u8 *)D_86A0F004 + (temp_v0 << 3));
    } else {
        temp_v0 = func_86A0C9B4(arg0, 1);
        local.pair = *(Pair *)((u8 *)D_86A0F004 + (temp_v0 << 3) + 0x48);
    }
    func_86A0CED8(
        (f32 *)((u8 *)D_800CE060 + (arg0 * 0x28) + 0x18),
        (f32 *)((u8 *)D_800CE060 + (arg0 * 0x28) + 0x1C),
        local.pair.unk0,
        local.pair.unk4
    );
}
#endif

#ifdef VERSION_US
void func_86A0C9AC(u8 *arg0) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0C9B4.s")
#endif

#ifdef VERSION_US
extern f32 D_86A0F878;
void func_86A0CED8(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3) {
    f32 var_fv1;
    f64 temp_fv0;

    if ((arg2 == 0.0f) && (arg3 == 0.0f)) {
        *arg0 = 0.0f;
        *arg1 = 0.0f;
        return;
    }
    var_fv1 = sqrtf((arg2 * arg2) + (arg3 * arg3));
    if (var_fv1 < D_86A0F878) {
        var_fv1 = D_86A0F878;
    }
    temp_fv0 = (f64) var_fv1;
    *arg0 = (f32) (((f64) arg2 * 64.0) / temp_fv0);
    *arg1 = (f32) -(((f64) arg3 * 64.0) / temp_fv0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0CF80.s")
#endif
