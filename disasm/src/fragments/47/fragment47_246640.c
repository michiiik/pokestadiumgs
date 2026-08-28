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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860004C8.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860018A8.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86001A60.s")
#endif

#ifdef VERSION_US
extern void func_87C01A90(s32);
void func_86001AFC(s32 arg0) { func_87C01A90(arg0 + 364); }
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86001F44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86001FCC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002070.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860021C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002234.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860022F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860023CC.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002F5C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86002FB4.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860032DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860033E8.s")
#endif

#ifdef VERSION_US
void func_86003754(u8 *arg0) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_8600375C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860037D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003868.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003A0C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003A98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003B10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003C68.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_86003D54.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_246640/func_860043B4.s")
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
