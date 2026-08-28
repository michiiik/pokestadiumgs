#include "global.h"


#ifdef VERSION_US
s32 *func_8004C874(s32, s32, ...);
extern u8 D_8AF29BB0;

s32 *func_8AF19880(s16 arg0) {
    s32 *temp_v0;
    s32 *var_v1;

    temp_v0 = func_8004C874(8, arg0 - 1, arg0);
    var_v1 = temp_v0;
    if (temp_v0 == NULL) {
        var_v1 = &D_8AF29BB0;
    }
    return var_v1;
}

s32 *func_8004C874(s32, s32, ...);
extern u8 D_8AF29BC0;

s32 *func_8AF198C4(s16 arg0) {
    s32 *temp_v0;
    s32 *var_v1;

    temp_v0 = func_8004C874(0xA, arg0 - 1, arg0);
    var_v1 = temp_v0;
    if (temp_v0 == NULL) {
        var_v1 = &D_8AF29BC0;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19908.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19970.s")

s32 *func_8004C874(s32, s32, ...);
extern u8 D_8AF29BF8;

s32 *func_8AF199D8(s16 arg0) {
    s32 *temp_v0;
    s32 *var_v1;

    temp_v0 = func_8004C874(7, arg0 - 1, arg0);
    var_v1 = temp_v0;
    if (temp_v0 == NULL) {
        var_v1 = &D_8AF29BF8;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19A1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19AC4.s")

extern u8 func_80063014(u8);
s32 func_8AF19B40(u8 arg0) {
    u8 temp_v0;
    s32 result = 0;

    if (arg0 >= 0xC9) {
        temp_v0 = func_80063014(arg0 - 0xC8);
        result = temp_v0 & 0xFF;
    } else if (arg0 >= 0xC4) {
        temp_v0 = func_80063014(arg0 - 0x91);
        result = temp_v0 & 0xFF;
    }
    return result;
}

s32 func_8AF19BA0(s32 arg0) {
    volatile s32 *p = &arg0;
    arg0 &= 0xFF;
    if (arg0 == 0x46 || arg0 == 0x73 || arg0 == 0x74 || arg0 == 0x81) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19BDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19CB0.s")

extern void func_8AF19CB0(s16, s32);

void func_8AF19E24(s16 arg0) {
    func_8AF19CB0(arg0, 6);
}


void func_8AF19E50(s16 arg0) {
    func_8AF19CB0(arg0, 0xC);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19E7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF19FAC.s")

extern s16 func_8AF19A1C(s32);
extern u8 *func_8AF19E7C(u8 *, s32, s32, s16);
extern s8 D_8AF29D44;
extern s32 D_8AF2BAAC;
extern s16 D_8AF35050;
extern s8 D_8AF354A8;
extern s32 D_8AF357D0;
extern void _bzero(s32 *, s32);
extern s32 * func_8004C874(s32, s32, ...);
void func_8AF1A0DC(s16 arg0) {
    s16 *p = &arg0;
    s32 padding[4];
    s16 sp22;
    s32 sp1C;
    u8 *temp_v0;
    s16 value;

    sp1C = D_8AF2BAAC;
    D_8AF35050 = 2;
    sprintf(&D_8AF354A8, &D_8AF29D44,
            func_8004C874(0x3B, *p + 0xD2));
    sp22 = func_8AF19A1C(6);
    _bzero(&D_8AF357D0, 0x1758);
    value = *p;
    if (value == 1) {
        temp_v0 = func_8AF19E7C(&D_8AF357D0, sp1C, 0x4000, sp22);
        temp_v0[0] = 0xFF;
        temp_v0[0xC] = 0xFF;
        func_8AF19E7C(temp_v0 + 0x18, sp1C, 0x100, sp22);
        return;
    }
    func_8AF19E7C(&D_8AF357D0, sp1C, (0x8000 >> value) & 0xFFFF, sp22);
}

extern u8 *func_8AF19FAC(u8 *, s32, s32, s16);
extern s8 D_8AF29DA0;
extern s32 D_8AF2BAC4;
extern s32 * func_8004C874(s32, s32, ...);
void func_8AF1A1B8(s16 arg0, s16 arg1) {
    s16 *p0 = &arg0;
    s32 padding[4];
    s16 sp22;
    s32 temp_s0;
    u8 *temp_v0;
    s16 value;

    temp_s0 = D_8AF2BAC4;
    D_8AF35050 = 2;
    sprintf(&D_8AF354A8, &D_8AF29DA0, func_8004C874(0x3B, arg1));
    sp22 = func_8AF19A1C(0xC);
    _bzero(&D_8AF357D0, 0x1758);
    value = *p0;
    switch (value) {
    case 0:
        temp_v0 = func_8AF19FAC(&D_8AF357D0, temp_s0, 0x8000, sp22);
        temp_v0[0] = 0xFF;
        temp_v0[0xC] = 0xFF;
        func_8AF19FAC(temp_v0 + 0x18, temp_s0, 0x200, sp22);
        return;
    case 4:
        func_8AF19FAC(&D_8AF357D0, temp_s0, 0x400, sp22);
        return;
    default:
        func_8AF19FAC(&D_8AF357D0, temp_s0, (0x8000 >> value) & 0xFFFF, sp22);
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1A2B8.s")

extern void _bzero(s32 *, s32);
extern s16 D_8AF357AC;
extern s16 D_8AF357AE;
extern u8 D_8AF357C0;

void func_8AF1A72C(void) {
    D_8AF357AC = 0;
    D_8AF357AE = 0;
    _bzero(&D_8AF357C0, 0xE);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1A764.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1AE30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1B23C.s")

void func_8AF1B4D0(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x28) = arg1;
    *(s32 *)(arg0 + 0x2C) = arg2;
}

extern u8 *D_8AF371F4;
extern u8 *D_8AF371F8;
extern u8 *D_8AF37204;
extern u8 *D_8AF37208;
extern s16 D_8AF3720C;
extern void func_8AF1B4D0(u8 *, s32, s32);
void func_8AF1B4DC(void) {
    *(u16 *)(D_8AF371F4 + 2) &= 0xFFFE;
    *(u16 *)(D_8AF371F8 + 2) &= 0xFFFE;
    func_8AF1B4D0(D_8AF37204, 0xC3A05AFF, 0xE1C38CFF);
    func_8AF1B4D0(D_8AF37208, 0xC3A05AFF, 0xE1C38CFF);
    switch (D_8AF3720C) {
    case 0:
        *(u16 *)(D_8AF371F4 + 2) |= 1;
        func_8AF1B4D0(D_8AF37204, 0xFFFF00FF, 0xFFFF00FF);
        break;
    case 1:
        *(u16 *)(D_8AF371F8 + 2) |= 1;
        func_8AF1B4D0(D_8AF37208, 0xFFFF00FF, 0xFFFF00FF);
        break;
    }
}

extern s16 D_8AF3720C;
void func_8AF1B5D4(void) {
    D_8AF3720C = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1B5E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_207AF0/func_8AF1B770.s")

extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800499EC(void);
void func_8AF1B910(void) {
    func_800498C4();
    func_800496A4(0x10, 0);
    func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
    func_800499EC();
}
#endif
