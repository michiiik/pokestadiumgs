#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86000020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86000170.s")
#endif

void func_860002A0(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860002A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860003DC.s")
#endif

#ifdef VERSION_US
extern void * func_87C00160(void *, void *, void *);
extern f64 func_87C00D14(f64,f64);
f32 func_860004C8(void *arg0, void *arg1) {
    u8 value[0x18];
    func_87C00160(value, arg1, arg0);
    return (f32)func_87C00D14(*(f64 *)value, *(f64 *)(value + 0x10));
}
void func_860004C8_padding(void) {}
void func_860004C8_padding2(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_8600050C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_8600062C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86000AE0.s")
#endif

#ifdef VERSION_US
s32 func_86000B9C(u8 *arg0, s32 arg1, s32 arg2) {
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86000BB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86000C6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86000CCC.s")
#endif

#ifdef VERSION_US
extern void func_87C01CBC();
void func_86001838(s32 arg0, u8 *arg1) {
    s32 pad;
    u8 *obj = *(u8 **)(arg1 + 0x14);
    func_87C01CBC(obj + 0x16C);
    *(f32 *)(arg1 + 0x24) = (f32)*(f64 *)(obj + 0x198);
    *(f32 *)(arg1 + 0x28) = (f32)*(f64 *)(obj + 0x1A0);
    *(f32 *)(arg1 + 0x28) -= 26.0f;
    *(f32 *)(arg1 + 0x2C) = (f32)*(f64 *)(obj + 0x1A8);
}
#endif

#ifdef VERSION_US
extern void func_86007AF8(void *, f64);
extern void func_87F06430(f32 *, s32);
extern f32 D_8600D638;
void func_860018A8(void *arg0) {
    f32 values[3];
    f32 constant;

    *(s32 *)((u8 *)arg0 + 0x194) = 0;
    func_86007AF8((u8 *)arg0 + 0x198, 14.0);
    func_87F06430(values, *(s32 *)arg0);
    constant = D_8600D638;
    *(f64 *)((u8 *)arg0 + 0x198) = (f64)values[0];
    *(f64 *)((u8 *)arg0 + 0x1A0) = (f64)values[1];
    *(f64 *)((u8 *)arg0 + 0x1A8) = (f64)values[2];
    *(f32 *)((u8 *)arg0 + 0x34) = constant;
    *(f32 *)((u8 *)arg0 + 0x38) = constant;
    *(f32 *)((u8 *)arg0 + 0x3C) = constant;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86001924.s")
#endif

#ifdef VERSION_US
void func_86001A58(u8 *arg0, s32 arg1) {
    *(s32 *)arg0 = arg1;
}
#endif

#ifdef VERSION_US
extern u8 D_87F15B70[];
extern u8 D_8600D540[];
extern void func_8003F03C(void *, void *);
extern void func_8003F1DC(void *);
extern void func_8003F114(void *, s32, s32, s32);
extern void func_87C01888(void *, void *, void *);
extern void func_80037E3C(void *, void (*)(s32, u8 *), void *);
extern void func_86001838(s32, u8 *);
extern void func_86001B1C(u8 *);
void func_86001A60(u8 *arg0, s32 *arg1) {
    u8 *temp_s0 = arg0 + 4;
    func_8003F03C(temp_s0, D_87F15B70);
    func_8003F1DC(temp_s0);
    func_8003F114(temp_s0, 0, -1, arg1[*(s32 *)arg0]);
    func_87C01888(arg0 + 0x16C, temp_s0, D_8600D540);
    func_80037E3C(temp_s0, func_86001838, arg0);
    func_86001B1C(arg0);
}
#endif

#ifdef VERSION_US
extern void func_87C01A90(s32);
void func_86001AFC(s32 arg0) {
    func_87C01A90(arg0 + 364);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86001B1C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86001BFC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86001CE8.s")
#endif

#ifdef VERSION_US
void func_86001DBC(u8 *arg0) { arg0[0x1639] &= 0xFFFE; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86001DCC.s")
#endif

#ifdef VERSION_US
extern f32 __sinf(f32);
extern f32 __cosf(f32);
extern f64 D_8600DED8;
void func_86001F44(u8 *arg0) {
    struct Temp {
        u8 pad[8];
        f64 value;
    };
    struct Temp *temp;

    temp = (struct Temp *)(*(u8 **)(arg0 + 0x1870) + 0x6668);
    *(f64 *)arg0 = (f64)__sinf((f32)*(f64 *)(arg0 + 0x17D8)) *
        (temp->value + D_8600DED8);
    *(f64 *)(arg0 + 0x10) = (f64)__cosf((f32)*(f64 *)(arg0 + 0x17D8)) *
        (temp->value + D_8600DED8);
}
#endif

#ifdef VERSION_US
extern f64 func_86009C98(void *, f64, f64);
extern f64 D_8600DEE0;
extern f32 __cosf(f32);
extern void func_86001F44(u8 *arg0);
extern u8 D_8600DE30[];
void func_86001FCC(void *arg0) {
    u8 *base;

    base = *(u8 **)((u8 *)arg0 + 0x1870) + 0x6668;
    func_86001F44(arg0);
    *(f64 *)((u8 *)arg0 + 0x8) = func_86009C98(base, *(f64 *)arg0, *(f64 *)((u8 *)arg0 + 0x10));
    *(f64 *)((u8 *)arg0 + 0x18) = -*(f64 *)(D_8600DE30 + 0xB0) * (f64)__sinf((f32)*(f64 *)((u8 *)arg0 + 0x17D8));
    *(f64 *)((u8 *)arg0 + 0x20) = *(f64 *)(D_8600DE30 + 0xB8);
    *(f64 *)((u8 *)arg0 + 0x28) = -D_8600DEE0 * (f64)__cosf((f32)*(f64 *)((u8 *)arg0 + 0x17D8));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002070.s")
#endif

#ifdef VERSION_US
extern void func_86002070(void *, s32, f32, void *, void *);
extern void func_86003EFC(void *, s32);
extern f32 MathUtil_Random_ZeroOne(void);
extern f32 D_8600D668;
extern f32 D_8600D66C;
extern void func_87C01F6C(void *, f32);
void func_860021C4(u8 *arg0, s32 arg1, f32 arg2, void *arg3, void *arg4) { f32 random; func_86002070(arg0, arg1, arg2, arg3, arg4); func_86003EFC(arg0, 0); random = MathUtil_Random_ZeroOne(); func_87C01F6C(arg0 + 0x17A0, random * D_8600D668 + D_8600D66C); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002234.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860022F8.s")
#endif

#ifdef VERSION_US
extern f32 D_8600D670;
extern void func_86007B4C(void *, f64);
extern void *func_87C00308(void *, void *, void *, f64);
extern void *func_87C00160(void *, void *, void *);
extern void func_87C00718(void *, void *, f64);
extern void func_86007E4C(u8 *, s32, s32);
void func_860023CC(u8 *arg0, f64 arg1) {
    f32 value;
    f32 scaled;
    *(f64 *)(arg0 + 0x17C8) = arg1;
    func_86007B4C(arg0, arg1);
    value = (f32)(arg1 / 200.0);
    *(f32 *)(arg0 + 0x150) = value;
    *(f32 *)(arg0 + 0x154) = value;
    *(f32 *)(arg0 + 0x158) = value;
    scaled = value * D_8600D670;
    *(f32 *)(arg0 + 0x2B8) = scaled;
    *(f32 *)(arg0 + 0x2BC) = scaled;
    *(f32 *)(arg0 + 0x2C0) = scaled;
}
#endif

#ifdef VERSION_US
void func_86002444(u8 *arg0, s32 arg1) {
    if (arg1) {
        arg0[0x121] |= 1;
    } else {
        arg0[0x121] &= 0xFFFE;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002470.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002780.s")
#endif

#ifdef VERSION_US
extern void func_860043B4();
s32 func_8600297C(s32 arg0, u8 *arg1) {
    u8 *state = *(u8 **)(arg1 + 0x14);
    state[0x28A] |= 0x10;
    if (arg0 != 2) return 0;
    func_860043B4(state, arg1 + 0x60);
    return 1;
}
void func_8600297C_padding(void) {}
#endif

#ifdef VERSION_US
extern void func_86003EFC(); extern f64 func_87C00090(f64,f64,f64); extern f64 func_87C00D14(f64,f64); extern f64 D_8600E028;
void func_860029D0(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x1870);
    if (*(s32 *)(obj + 0x7518) == 3) {
        func_86003EFC(arg0, 1);
        return;
    }
    *(f64 *)(arg0 + 0x1860) = func_87C00090(
        *(f64 *)(arg0 + 0x1860), 0.0,
        *(f64 *)(obj + 0x6890) * D_8600E028);
    *(f64 *)(arg0 + 0x1858) = func_87C00D14(
        -*(f64 *)(arg0 + 0), -*(f64 *)(arg0 + 0x10));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002A58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002B20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002BF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002DA8.s")
#endif

#ifdef VERSION_US
extern f64 func_87C00090(f64, f64, f64);
extern f64 D_8600E028;
void func_86002F5C(u8 *arg0) {
    *(f64 *)(arg0 + 0x1860) = func_87C00090(
        *(f64 *)(arg0 + 0x1860), 0.0,
        *(f64 *)(*(u8 **)(arg0 + 0x1870) + 0x6890) * D_8600E028);
    *(f64 *)(arg0 + 0x1858) = 0.0;
}
#endif

#ifdef VERSION_US
extern u8 D_8600DE30[];
extern void func_86000AE0(void);
extern f64 func_87C00090(f64, f64, f64);
extern void *func_87C00160(void *, void *, void *);
extern f64 func_87C0068C(void *);
extern f64 fragment48_main(f64);
extern void func_860032DC(u8 *);
void func_86002FB4(u8 *arg0) {
    u8 sp28[0x18];
    *(void (**)(void))(arg0 + 0x1824) = func_86000AE0;
    *(f64 *)(arg0 + 0x1860) = func_87C00090(
        *(f64 *)(arg0 + 0x1860),
        *(f64 *)(D_8600DE30 + 0x88),
        *(f64 *)(D_8600DE30 + 0x1F8) * *(f64 *)(*(u8 **)(arg0 + 0x1870) + 0x6890));
    func_87C00160((u8 *)sp28 - 8, arg0, arg0 + 0x1878);
    *(f64 *)sp28 = 0.0;
    if (func_87C0068C((u8 *)sp28 - 8) < *(f64 *)(arg0 + 0x17C8) * 0.5) {
        func_86003EFC(arg0, 5);
    }
    *(f64 *)(arg0 + 0x1858) = fragment48_main(
        *(f64 *)(arg0 + 0x1860) + *(f64 *)(arg0 + 0x1858));
    func_860032DC(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003080.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003124.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860031C8.s")
#endif

#ifdef VERSION_US
extern f64 D_8600DED0;
extern s32 func_8600472C(u8 *);
extern s32 func_860047E8(u8 *);
extern void func_86001924(void *);
extern void func_800278C0(u16, u8, u8 *, f32);
void func_860032DC(u8 *arg0) {
    f32 value;
    u16 mode;
    value = -1.0f;
    if (*(s32 *)(arg0 + 0x1828) == 5) return;
    if (*(s32 *)(arg0 + 0x1828) == 7) return;
    if (*(s32 *)(arg0 + 0x1828) == 8) return;
    if (func_8600472C(arg0) != 0) value = 1.75f;
    else if (func_860047E8(arg0) != 0) value = 1.0f;
    else if (D_8600DED0 <= *(f64 *)(arg0 + 0x1860)) value = 1.25f;
    if (value > 0.0f) {
        mode = 0x4000;
        func_86001924(arg0);
        if (func_8600472C(arg0) != 0) mode = 0x4401;
        func_800278C0(mode, arg0[0x1813], arg0 + 0x1890, value);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860033E8.s")
#endif

#ifdef VERSION_US
void func_86003754(u8 *arg0) {}
#endif

#ifdef VERSION_US
void func_8600375C(u8 *arg0, u8 *arg1, f64 arg2) {
    u8 sp38[0x18];
    u8 sp20[0x18];
    func_87C00308(sp20, arg0, arg1, 0.5);
    func_87C00160(sp38, arg1, arg0);
    func_87C00718(sp38, sp38, arg2);
    func_86007E4C(arg1, (s32)sp20, (s32)sp38);
}
#endif

#ifdef VERSION_US
extern f64 D_8600DF18;
extern f64 D_8600DF20;
extern s32 func_8600472C(u8 *);
extern void func_87C01DB8();
void func_860037D8(u8 *arg0, u8 *arg1, s32 *arg2, f64 *arg3) {
    *arg2 = (*(s32 *)((u8 *)(arg1) + (0x1810)));
    if (func_8600472C(arg0) == 0) {
        func_87C01DB8(arg0 + 0x17A0, 7, 1);
        if (func_8600472C(arg1) != 0) {
            (*(s32 *)((u8 *)(arg0) + (0x1898))) = 1;
            *arg3 = D_8600DF18;
            return;
        }
        *arg3 = D_8600DF20;
        (*(s32 *)((u8 *)(arg0) + (0x1898))) = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003868.s")
#endif

#ifdef VERSION_US
extern u8 D_8600D5DC[];
extern void func_87C01E98(void *, f32, f32);
extern void func_87C01E30(void *, void *, s32);
void func_86003A0C(u8 *arg0) {
    *(s32 *)(arg0 + 0x1868) = 0;
    *(s32 *)(arg0 + 0x186C) = 0;
    func_87C01E30((u8 *)arg0 + 0x17A0, (u8 *)D_8600D5DC + (MathUtil_Random_ZeroOne() > 0.5f) * 0xA, 0);
    func_87C01E98((u8 *)arg0 + 0x17A0, MathUtil_Random_ZeroOne(), MathUtil_Random_ZeroOne());
}
#endif

#ifdef VERSION_US
extern u8 D_8600D5F0[];
extern f64 D_8600E020;
extern void func_86001924(void *);
extern void func_8002781C(s32, u8, void *);
extern void func_87C01E30(void *, void *, s32);
extern f64 func_87C00D14(f64, f64);
extern void func_86001FCC(void *);
void func_86003A98(u8 *arg0) {
    *(s32 *)(arg0 + 0x1868) = 0;
    *(s32 *)(arg0 + 0x186C) = 0;
    func_86001924(arg0);
    func_8002781C(0x4F06, arg0[0x1813], arg0 + 0x1890);
    func_87C01E30(arg0 + 0x17A0, &D_8600D5F0, 0);
    *(f64 *)(arg0 + 0x17D0) = D_8600E020;
    *(f64 *)(arg0 + 0x17D8) = func_87C00D14(*(f64 *)arg0, *(f64 *)(arg0 + 0x10));
    func_86001FCC(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003B10.s")
#endif

#ifdef VERSION_US
extern void func_87C01DB8(); extern void func_87C00120(void *,f64,f64,f64); extern f64 func_87C00D14(f64,f64); extern f64 D_8600DE68; extern f64 D_8600DE78;
void func_86003C68(u8 *arg0) {
    *(s32 *)(arg0+0x1868)=1;
    *(s32 *)(arg0+0x186C)=0;
    func_87C01DB8(arg0+0x17A0,0,0);
    *(f64 *)(arg0+0x1858)=func_87C00D14(-*(f64 *)arg0,-*(f64 *)(arg0+0x10));
    func_87C00120(arg0+0x30,0.0,D_8600DE78,0.0);
    *(f64 *)(arg0+0x17D0)=D_8600DE68;
    arg0[0x13D]=0x64;
}
#endif

#ifdef VERSION_US
extern void func_87C01DB8();
void func_86003CFC(u8 *arg0) {
    *(s32 *)(arg0 + 0x1868) = 1;
    *(s32 *)(arg0 + 0x186C) = 1;
    func_87C01DB8(arg0 + 0x17A0, 0, 0, arg0);
    arg0[0x13D] = 0xFF;
    *(f64 *)(arg0 + 0x17D0) = 0.0;
    *(f64 *)(arg0 + 0x17E0) = 0.0;
}
#endif

#ifdef VERSION_US
extern void func_87C01E30(void *, void *, s32);
extern u8 D_8600D5F4[];
void func_86003D54(u8 *arg0) {
    *(s32 *)(arg0 + 0x1868) = 0;
    *(s32 *)(arg0 + 0x186C) = 1;
    func_87C01E30(arg0 + 0x17A0, &D_8600D5F4, 0);
    arg0[0x13D] = 0xFF;
    *(f64 *)(arg0 + 0x1858) = 0.0;
}
#endif

#ifdef VERSION_US
extern void func_86000AE0(void);
void func_86003DAC(u8 *arg0) {
    *(s32 *)(arg0 + 0x1868) = 1;
    *(s32 *)(arg0 + 0x186C) = 1;
    arg0[0x13D] = 0xFF;
    *(void (**)(void))(arg0 + 0x1824) = func_86000AE0;
}
#endif

#ifdef VERSION_US
extern void func_87C01E30(void *,void *,s32); extern void func_87C00120(void *,f64,f64,f64); extern f64 D_8600D60C;
void func_86003DD0(u8 *arg0) {
    *(s32 *)(arg0+0x1868)=0;
    *(s32 *)(arg0+0x186C)=1;
    func_87C01E30(arg0+0x17A0,&D_8600D60C,0);
    func_87C00120(arg0+0x18,0.0,0.0,0.0);
    func_87C00120(arg0+0x30,0.0,0.0,0.0);
    arg0[0x13D]=0xFF;
}
#endif

#ifdef VERSION_US
extern void func_87C01E30(void *,void *,s32); extern void func_87C00120(void *,f64,f64,f64); extern f64 D_8600D60C;
void func_86003E5C(u8 *arg0) {
    *(s32 *)(arg0+0x1868)=1;
    *(s32 *)(arg0+0x186C)=1;
    func_87C01E30(arg0+0x17A0,&D_8600D60C,1);
    func_87C00120(arg0+0x18,0.0,0.0,0.0);
    func_87C00120(arg0+0x30,0.0,0.0,0.0);
    arg0[0x13D]=0xFF;
    *(f64 *)(arg0+0xC8) *= 3.0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003EFC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003FDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860041E8.s")
#endif

#ifdef VERSION_US
extern s32 func_86009F28(void *, void *, void *);
extern s32 func_8600A04C(void *, void *, void *);
extern void *func_87C008B0(void *);
extern void func_87C00814(void *, void *, void *);
extern void func_87C013CC(void *, void *);
typedef struct { f64 x; f64 y; f64 z; f64 w; } V4;
typedef struct { f64 x; f64 y; f64 z; } V3;
void func_860043B4(register u8 *arg0, void *arg1) {
    V3 sp40;
    V4 sp20;
    if (func_86009F28(*(u8 **)(arg0 + 0x1870) + 0x66B8, arg0, &sp40) != 0) {
        func_8600A04C(*(u8 **)(arg0 + 0x1870) + 0x66B8, arg0, &sp20);
    } else if (func_86009F28(*(u8 **)(arg0 + 0x1870) + 0x6668, arg0, &sp40) != 0) {
        func_8600A04C(*(u8 **)(arg0 + 0x1870) + 0x6668, arg0, &sp20);
    } else {
        func_87C008B0(&sp20);
        func_87C00814(*(u8 **)(arg0 + 0x1870) + 0x6848, arg0, &sp40);
    }
    func_87C013CC(&sp20, arg1);
    ((f32 *)((u8 *)arg1 + 0x30))[0]=(f32)sp40.x;
    ((f32 *)((u8 *)arg1 + 0x30))[1]=(f32)sp40.y;
    ((f32 *)((u8 *)arg1 + 0x30))[2]=(f32)sp40.z;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86004494.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86004544.s")
#endif

#ifdef VERSION_US
s32 func_8600472C(u8 *arg0) {
    s32 result = ((*(u32 *)(arg0 + 0x1828) ^ 3) < 1);
    if (result) {
        result = 0;
        if (0.0 < *(f64 *)(arg0 + 0x17E0)) {
            result = 1;
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
s32 func_8600476C(u8 *arg0) {
    s32 result = ((*(u32 *)(arg0 + 0x1828) ^ 3) < 1);
    if (result) {
        result = 0;
        if (0.0 < *(f64 *)(arg0 + 0x17D0)) {
            result = 1;
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
extern s32 func_8600472C(u8 *);
extern s32 func_8600476C(u8 *);
s32 func_860047AC(u8 *arg0) {
    s32 result = func_8600472C(arg0) == 0;
    if (result) {
        result = func_8600476C(arg0) == 0;
    }
    return result;
}
#endif

#ifdef VERSION_US
s32 func_860047E8(u8 *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if ((*(f64 *)((u8 *)(arg0) + (0x17E8))) > 0.0) {
        var_v1 = 1;
    }
    if (var_v1 != 0) {
        var_v1 = func_860047AC(arg0) != 0;
    }
    return var_v1;
}
#endif
