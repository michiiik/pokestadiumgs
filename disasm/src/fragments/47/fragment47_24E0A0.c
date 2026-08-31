#include "global.h"


#ifdef VERSION_US
extern void *func_87C00120(void *, f64, f64, f64);
void func_86007A80(void *arg0, f64 arg1) {
    f64 t = (2.0 * arg1) / 3.0;
    f64 value = *(f64 *)((u8 *)arg0 + 0xC8);
    f64 result = t * value * value * 5.0;
    *(f64 *)((u8 *)arg0 + 0xE0) = arg1;
    func_87C00120((u8 *)arg0 + 0x60, result, result, result);
}

extern u8 D_8600DE30[];
extern void func_86007B4C(void *, f64);
extern void func_86007BE4(void *, s32);
void func_86007AF8(void *arg0, f64 arg1) {
    *(f64 *)((u8 *)arg0 + 0xE0) = *(f64 *)(D_8600DE30 + 0x10);
    *(f64 *)((u8 *)arg0 + 0xE8) = *(f64 *)(D_8600DE30 + 0x70);
    func_86007B4C(arg0, arg1);
    func_86007BE4(arg0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86007B4C.s")

extern void func_87C00908(void *, f64, f64, f64);
extern void func_86007EB4(void *arg0);
void func_86007BE4(void *arg0, s32 arg1) {
    func_87C00120((u8 *)arg0 + 0x18, 0.0, 0.0, 0.0);
    func_87C00120(arg0, 0.0, 0.0, 0.0);
    func_87C00120((u8 *)arg0 + 0x30, 0.0, 0.0, 0.0);
    func_87C00908((u8 *)arg0 + 0x78, 0.0, 0.0, 0.0);
    func_86007EB4(arg0);
    func_87C00120((u8 *)arg0 + 0xF0, 0.0, 0.0, 0.0);
    func_87C00120((u8 *)arg0 + 0x108, 0.0, 0.0, 0.0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86007CB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86007D98.s")

extern void func_87C00198();
extern void *func_87C00160(u8 *, s32, u8 *);
extern s32 func_87C00238(u8 *, u8 *, s32);
void func_86007E4C(u8 *arg0, s32 arg1, s32 arg2) {
    u8 temp0[0x18];
    u8 temp1[0x18];
    s32 value;
    func_87C00198(arg0 + 0xF0, arg0 + 0xF0);
    func_87C00160(temp0, arg1, arg0 + 0xB0);
    value = func_87C00238(temp1, temp0, arg2);
    func_87C00198(arg0 + 0x108, arg0 + 0x108, value);
}

extern void func_87C00AE4(void *, void *);
extern void func_87C015E4(void *, void *);
extern void *func_87C002A8(void *, void *, f64);
void func_86007EB4(void *arg0) {
    f64 vec[3];
    func_87C00AE4((u8 *)arg0 + 0x78, (u8 *)arg0 + 0x78);
    func_87C015E4((u8 *)arg0 + 0x78, (u8 *)arg0 + 0x48);
    func_87C00198((u8 *)arg0 + 0xB0, arg0, func_87C002A8(vec, (u8 *)arg0 + 0x48, *(f64 *)((u8 *)arg0 + 0xD8)));
    func_87C00198((u8 *)arg0 + 0x98, arg0, func_87C002A8(vec, (u8 *)arg0 + 0x48, *(f64 *)((u8 *)arg0 + 0xD0) + *(f64 *)((u8 *)arg0 + 0xC8)));
}

f64 func_86007F50(void *arg0, s32 arg1, s32 arg2) {
    f64 temp_fv1;

    temp_fv1 = (*(f64 *)((u8 *)(arg0) + (0xC8)));
    return (temp_fv1 * temp_fv1) / (*(f64 *)((u8 *)(arg0) + (0x60)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86007F6C.s")

extern f64 D_8600DE78;
extern void func_87C003BC(void *, void *, void *);
extern void func_87C00718(void *, void *, f64);
extern void *func_87C002DC(void *, void *);
extern f64 func_86007F6C(void *, void *, s32, s32, void *, s32, f64);
extern void func_86007E4C(u8 *arg0, s32 arg1, s32 arg2);
extern void * func_87C00160(u8 *, s32, u8 *);
extern void func_87C00198();
extern s32 func_87C00238(u8 *, u8 *, s32);
extern void * func_87C002A8(void *, void *, f64);
f64 func_86008038(u8 *arg0, u8 *arg1, void *arg2, s32 arg3, f64 arg4, s32 arg5, s32 arg6, f64 arg7) {
    f64 result;
    u8 sp100[0x18];
    u8 spE8[0x18];
    u8 spD0[0x18];
    u8 spB8[0x18];
    u8 spA0[0x18];
    u8 sp88[0x18];
    u8 sp70[0x18];
    u8 sp58[0x18];
    u8 sp40[0x18];
    func_87C00120(sp40, 0.0, D_8600DE78, 0.0);
    func_87C00238(sp70, sp40, func_87C00160(spE8, arg3, arg0 + 0xB0));
    func_87C00198(sp70, sp70, arg0 + 0x18);
    func_87C00238(sp58, sp40, func_87C00160(spE8, arg3, arg1 + 0xB0));
    func_87C00198(sp58, sp58, arg1 + 0x18);
    func_87C00160(spA0, (s32)sp58, sp70);
    func_87C003BC(sp100, spA0, arg2);
    func_87C00718(sp100, sp100, 1.0);
    result = func_86007F6C(arg0, arg1, arg5, arg6, arg2, arg3, arg4);
    if (result < *(f64 *)(D_8600DE30 + 0x20)) result = *(f64 *)(D_8600DE30 + 0x20);
    if ((0.0 < *(f64 *)(D_8600DE30 + 0x30)) && (*(f64 *)(D_8600DE30 + 0x30) < result)) result = *(f64 *)(D_8600DE30 + 0x30);
    func_87C00198(sp88, func_87C002A8(spD0, arg2, result), func_87C002A8(spB8, sp100, arg7 * result));
    func_86007E4C(arg0, arg3, (s32)sp88);
    func_86007E4C(arg1, arg3, func_87C002DC(spE8, sp88));
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86008224.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_8600853C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_860086A4.s")

extern f64 func_87C00664(void *);
extern f64 func_87C00208(void *, void *);
s32 func_86008820(f64 *arg0, f64 *arg1, void *arg2, void *arg3, void *arg4) {
    volatile u8 frame_pad[8];
    f64 sp38;
    f64 sp30;
    f64 sp28;
    f64 denominator;
    f64 temp_fv0;
    f64 temp_fs1;

    temp_fs1 = func_87C00664(arg2);
    sp38 = func_87C00664(arg3);
    sp30 = func_87C00208(arg2, arg3);
    sp28 = func_87C00208(arg3, arg4);
    temp_fv0 = func_87C00208(arg4, arg2);
    denominator = temp_fs1 * sp38 - sp30 * sp30;
    if (denominator == 0.0) {
        return 0;
    }
    *arg0 = ((sp30 * temp_fv0) - (temp_fs1 * sp28)) / denominator;
    *arg1 = ((sp30 * sp28) - (sp38 * temp_fv0)) / denominator;
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86008904.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86008BB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86008D2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86008E64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86008F4C.s")

extern f64 func_86008F4C(void *, s32, f64, s32, f64, s32);
f64 func_860091F4(void *arg0, f64 arg1, s32 arg2, f64 arg3, s32 arg4) {
    f64 result = func_86008F4C(arg0, 1, arg1, arg2, arg3, arg4);
    if (result > 0.0) {
        return result;
    }
    return 0.0;
}

extern f64 func_87C00664(void *);
extern void func_86008D2C(void *, s32, void *, void *, f64, void *);
void func_86009260(void *arg0, f64 arg1, void *arg2, s32 arg3, void *arg4) {
    s32 i;

    for (i = 0; i < arg3; i++) {
        if (func_87C00664((u8 *)arg2 + i * 0x40) > 0.0) {
            func_86008D2C(arg0, 1, arg0, (u8 *)arg2 + i * 0x40, arg1, arg4);
        }
    }
}

extern f64 func_87C00664(void *);
extern void func_86008E64(void *, s32, void *, void *);
void func_86009318(void *arg0, void *arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < arg2; i++) {
        if (func_87C00664((u8 *)arg1 + i * 0x40) > 0.0) {
            func_86008E64(arg0, 1, arg0, (u8 *)arg1 + i * 0x40);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_860093AC.s")

extern void func_86007EB4(void *);
void func_860095B8(void *arg0, f64 arg1) { func_86007EB4(arg0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_860095DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86009674.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_860098A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86009934.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86009A90.s")

extern s32 MainPool_AllocAligned(s32, s32, s32);
s32 func_86009BE0(s32 arg0, s32 arg1) {
    return MainPool_AllocAligned(arg0, 8, 4);
}

s32 func_86009C08(void *arg0, void *arg1) {
    f64 x = *(f64 *)((u8 *)arg0 + 0x10) - *(f64 *)((u8 *)arg1 + 0x0);
    f64 y = *(f64 *)((u8 *)arg0 + 0x20) - *(f64 *)((u8 *)arg1 + 0x10);
    f64 radius = *(f64 *)((u8 *)arg0 + 0x8);

    return ((x * x) + (y * y)) < (radius * radius);
}

extern f64 func_87C0068C(void *);
f64 func_86009C58(void *arg0, u8 *arg1) {
    u8 data[0x18];
    func_87C00160(data, (s32)((u8 *)arg0 + 0x10), arg1);
    return *(f64 *)arg0 - func_87C0068C(data);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86009C98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86009D7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86009E54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86009EF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_86009F28.s")

extern void func_87C00718(void *, void *, f64);
extern s32 func_86009C08(void *arg0, void *arg1);
extern void * func_87C00160(u8 *, s32, u8 *);
s32 func_86009FB8(void *arg0, void *arg1, void *arg2) {
    void *result;
    f64 sign;

    if (func_86009C08(arg0, arg1) != 0) {
        result = func_87C00160(arg2, (s32)arg1, (u8 *)arg0 + 0x10);
        if (*(s32 *)((u8 *)arg0 + 0x48) != 0) {
            sign = 1.0;
        } else {
            sign = -1.0;
        }
        func_87C00718(arg2, result, sign);
        return 1;
    }
    return 0;
}

typedef struct Copy8600A04C {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
} Copy8600A04C;
extern Copy8600A04C D_8600D970;
extern void func_87C010AC(void *, void *, void *);
extern s32 func_86009FB8(void *arg0, void *arg1, void *arg2);
s32 func_8600A04C(void *arg0, void *arg1, void *arg2) {
    Copy8600A04C sp30;
    Copy8600A04C sp18;

    if (func_86009FB8(arg0, arg1, &sp30) != 0) {
        sp18 = D_8600D970;
        func_87C010AC(arg2, &sp18, &sp30);
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_8600A0C8.s")

f64 func_8600A144(u8 *arg0) {
    f64 ratio;
    f64 base;
    s32 flag;
    s32 sign;
    flag = *(s32 *)(arg0 + 0x48);
    if (flag != 0) return *(f64 *)arg0 + *(f64 *)(arg0 + 0x18);
    base = *(f64 *)arg0;
    ratio = *(f64 *)(arg0 + 8) / base;
    if (flag != 0) sign = 1; else sign = -1;
    return *(f64 *)(arg0 + 0x18) + ((f64)sqrtf((f32)(1.0 - ratio * ratio)) * ((f64)sign * base));
}

extern f32 D_8600D9DC;
s32 func_8600A1C0(f32 arg0) {
    s32 temp_v1;

    temp_v1 = (s32) arg0 & 0x1F;
    return ((temp_v1 << 0xA) + (s32) (((arg0 - (f32) temp_v1) + D_8600D9DC) * 1024.0f)) & 0xFFFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_8600A20C.s")

extern u8 *func_8004CA60(u8 *);
extern s32 func_8004CA38(u8 *);
extern s32 func_8004CA4C(u8 *);
extern void func_8600A20C(s16, s16, u16, u16, s32, s32, u8 *, s32, s32, s32);
extern s32 func_8004CA10(void *);
extern s32 func_8004CA24(void *);
void func_8600A5B0(s16 arg0, s16 arg1, u16 arg2, u16 arg3, void *arg4) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp24 = 1;
    u8 *sp34;

    sp44 = func_8004CA10((u16 *)arg4);
    sp40 = func_8004CA24((u16 *)arg4);
    sp34 = func_8004CA60((u8 *)arg4);
    sp3C = func_8004CA38((u8 *)arg4);
    func_8600A20C(arg0, arg1, arg2, arg3, sp44, sp40, sp34, sp3C, func_8004CA4C((u8 *)arg4), sp24);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_8600A650.s")

extern u8 D_8600D3F0[];
extern u8 D_8600D400;
u8 *func_8600AAA4(s32 arg0) {
    u8 *result;
    if (arg0 >= 0 && arg0 < 4) {
        result = D_8600D3F0 + (arg0 * 4);
    } else {
        result = &D_8600D400;
    }
    return result;
}

extern void func_8004C8C0(s32);
s32 func_8004C990(s32, s32);
extern s32 D_8600DE10;
extern s32 D_8600DE14;
extern s32 D_8600DE18;
extern s32 D_8600DE1C;
extern s32 D_8600DE20;
void func_8600AAD4(void) {
    func_87F061D0();
    func_8004C8C0(0x1B2);
    func_8004C8C0(0x191);
    func_8004C8C0(0x192);
    D_8600DE10 = func_8004C990(0x191, 0);
    D_8600DE14 = func_8004C990(0x191, 1);
    D_8600DE18 = func_8004C990(0x191, 2);
    D_8600DE1C = func_8004C990(0x191, 3);
    D_8600DE20 = func_8004C990(0x191, 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_8600AB6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_8600ACC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_8600AE6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_8600B100.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_24E0A0/func_8600B328.s")

void func_8600B468(u8 *arg0, s32 arg1) {}

extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_80094F50[];
extern void func_8600B100(void *);
extern void func_8600B328(void *);
extern void func_87F061F0(void);
extern void func_8600ACC4(void *, s32, s32, void *, void *);
extern u8 D_8600D43C[];
extern u8 D_8600D440[];
void func_8600B474(void *arg0, void *arg1) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    func_8600B100(arg1);
    func_8600B328(arg1);
    gSPDisplayList(D_800D0510++, D_80094F50);
    func_87F061F0();
    func_8600ACC4(arg0, 0x86, 0x10, D_8600D440, D_8600D43C);
}

extern s32 func_8004C990(s32, s32);
extern void func_8004D1FC(void *);
extern s32 func_8004CA10(void *);
extern s32 func_8004CA24(void *);
extern void func_8600A650(f32, f32, f32, f32, s32, s32, f32, f32);
void func_8600B51C(s32 arg0, s32 arg1) {
    volatile u8 frame_pad[8];
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    u8 *temp_v0;

    temp_v0 = func_8004C990(0x191, 0);
    func_8004D1FC(temp_v0);
    sp34 = func_8004CA10(temp_v0);
    sp38 = func_8004CA24(temp_v0);
    sp3C = func_8004CA10(temp_v0);
    func_8600A650(
        (f32)(arg0 - sp34 / 2),
        (f32)(arg1 - sp38 / 2),
        (f32)sp3C,
        (f32)func_8004CA24(temp_v0),
        0, 0, 1.0f, 1.0f
    );
}
#endif
