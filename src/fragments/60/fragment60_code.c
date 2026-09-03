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
extern void func_800088A4(s32);
extern void StageFade_StartFromTransparent(s32);
void func_86A01480(s32 arg0) {
    *(s32 *)(D_86A46548 + 0x18) = arg0;
    *(s32 *)D_86A46548 = 8;
    *(s32 *)(D_86A46548 + 4) = 9;
    func_800088A4((u16)0xFFFF);
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A01C5C.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0638C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A06400.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0B66C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0B6F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0B7A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0B7F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0B8A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0B98C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0BA80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0BB40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0BD34.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0C7B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/60/fragment60_code/func_86A0C8DC.s")
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
