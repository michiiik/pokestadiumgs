#include "global.h"


#ifdef VERSION_US
typedef struct { s16 a; s16 b; } Pair16_b2;
extern s16 D_822105F0;
extern s16 D_822105F4;
extern s16 D_822106B2;
extern s16 D_822106B4;
extern s16 D_822106CC, D_822106CE;
extern s16 D_822106BA;
extern f32 D_822106C4;
extern f32 D_822106C8;
extern void func_800226C0(s32);
extern u16 D_822106B6;
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern s16 D_82210640;
extern s16 D_82210642;
extern s16 D_82210644;
extern s16 D_82210646;
extern s32 func_8220D67C(void);
void func_822040A0(s16 *arg0) {
    s16 *v0 = &D_822105F0;
    v0[0] = 1;
    v0[1] = 0;
    v0[8] = arg0[4];
    v0[9] = arg0[5];
    v0[10] = arg0[6];
    v0[11] = arg0[7];
    v0[12] = arg0[6] - arg0[0x14];
    v0[13] = arg0[7] - arg0[0x15];
    *(Pair16_b2 *)&D_822105F4 = *(Pair16_b2 *)&v0[8];
    v0[4] = v0[10];
    v0[5] = v0[11];
    v0[6] = v0[4] - v0[12];
    v0[7] = v0[5] - v0[13];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82204148.s")

extern s16 D_822105F0;

void func_82204430(s32 arg0) {
    D_822105F0 = arg0;
    ((s16 *)&D_822105F0)[1] = 0;
}

extern void func_800503A4(s32);
extern s32 D_8220DA18;
extern s32 D_8220DA1C;
void func_82204444(void) {
    func_800503A4(D_8220DA18);
    if (D_822105F0 == 2) {
        func_800503A4(D_8220DA1C);
    }
}

void func_82204488(s16 *arg0) {
    arg0[0] = 0;
    arg0[1] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82204494.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82204744.s")

s32 func_82204780(s32 arg0, s32 arg1) {
    return (arg1 / arg0) & ~1;
}

s32 func_822047BC(s32 arg0, s32 arg1) {
    s32 temp_lo;
    s32 var_v1;

    temp_lo = arg0 / arg1;
    var_v1 = temp_lo;
    if ((arg0 % arg1) > 0) {
        var_v1 = temp_lo + 1;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82204804.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_8220510C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822056C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82205A14.s")

extern s32 D_8220DA10;
s32 func_82205A48(s32 arg0, void *arg1) {
    if (arg0 != 0 && arg0 == 1) {
        if (D_8220DA10 != 0) {
            *(u16 *)((u8 *)arg1 + 2) |= 2;
        } else {
            *(u16 *)((u8 *)arg1 + 2) &= 0xFFFD;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82205A8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82205B00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82205C14.s")

extern s16 D_822105F0;
extern s16 D_822105F4;
extern s16 D_822105F6;
extern s16 D_822105F8;
extern s16 D_822105FA;
extern s16 D_822105FC;
extern s16 D_822105FE;
s32 func_82205CE8(s32 arg0, void *arg1) { if (arg0 != 0 && arg0 == 1) { *(s16 *)((u8 *)arg1 + 8) = D_822105F4; *(s16 *)((u8 *)arg1 + 10) = D_822105F6; *(s16 *)((u8 *)arg1 + 12) = D_822105F8; *(s16 *)((u8 *)arg1 + 14) = D_822105FA; *(s16 *)((u8 *)arg1 + 40) = D_822105FC; *(s16 *)((u8 *)arg1 + 42) = D_822105FE; if (D_822105F0 != 2) { *(u16 *)((u8 *)arg1 + 2) |= 2; } else { *(u16 *)((u8 *)arg1 + 2) &= 0xFFFD; } } return 0; }

extern s16 D_822105F0;
extern u8 D_8220D8D2[];
extern s32 func_8220AD10(void);
s32 func_82205D78(s32 arg0, void *arg1) {
    s32 temp_v0;

    temp_v0 = func_8220AD10();
    if ((arg0 != 0) && (arg0 == 1)) {
        if (D_822105F0 == 1) {
            *(u16 *)((u8 *)arg1 + 2) |= 2;
            *(s16 *)((u8 *)arg1 + 0x32) =
                *(s16 *)(D_8220D8D2 + temp_v0 * 0x34);
        } else {
            *(u16 *)((u8 *)arg1 + 2) &= 0xFFFD;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82205E04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82205F2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82206124.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822061A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82206304.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82206400.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822064DC.s")

extern s32 D_8220EB90;

void func_822067C4(s32 arg0, void *arg1) {
    if ((arg0 != 0) && (arg0 == 1)) {
        if (D_8220EB90 != 0) {
            (*(u16 *)((u8 *)(arg1) + (2))) = (u16) ((*(u16 *)((u8 *)(arg1) + (2))) | 2);
            return;
        }
        (*(u16 *)((u8 *)(arg1) + (2))) = (u16) ((*(u16 *)((u8 *)(arg1) + (2))) & 0xFFFD);
    }
}

extern void func_82204494(s16 *);
extern s16 D_822105E8;
void func_82206804(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0:
        func_82204488(&D_822105E8);
        return;
    case 1:
        func_82204494(&D_822105E8);
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82206854.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822068E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82206950.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822069A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82206A2C.s")

s32 func_82206B64(s32 arg0) {
    return (0x800 / arg0) & ~1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82206BA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82206EB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82206FBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822071E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822072D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82207414.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822075D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82207714.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_8220792C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822083C4.s")

extern void func_80008648();
extern void func_800088DC();
extern void func_8003C6B8(s32);
extern void func_822069A4();
extern void func_82206A2C();
extern void func_822083C4();
extern void func_8220B478();
extern void func_8220B984();
extern void func_8220D560();
extern void *D_8220DA08;
extern s32 D_8220DA14;
extern s16 D_8220DA40;
extern s16 D_8220DA94;
extern s16 D_8220DAD8;
extern u16 D_8220EB82;
extern s32 D_82210578;
void func_82208518(void) {
    func_800088DC();
    func_82206A2C();
    func_800503A4(D_8220DA14);
    func_8003C6B8(D_82210578);
    func_822069A4();
    func_82204444();
    func_8220B984();
    func_8220B478();
    func_822083C4();
    func_800503A4((*(s32 *)((u8 *)(D_8220DA08) + (0x1C))));
    func_8220D560();
    if (D_8220EB82 & 1) {
        D_8220DA40 += 0x200;
        D_8220DA94 += 0x400;
        D_8220DAD8 += 0x400;
    }
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822085EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82208678.s")

extern s32 func_8220D670(void);
extern void *D_8220DA08;
s32 func_822088FC(void) { s32 result = 0; s32 value = func_8220D670(); if (value != -1) { result = 1; if (value == 0) { *(s16 *)((u8 *)D_8220DA08 + 0x24) = 0; } else { *(s16 *)((u8 *)D_8220DA08 + 0x24) = 1; } } return result; }

extern u8 D_8220D8D0[];
extern s16 D_8220EB84;
extern void func_8220AD1C(s16 *);
extern void func_8220B7A0(s16, s16, u8 *, u8 *);
void func_82208954(s32 arg0) {
    s16 coords[2];
    s32 pad[2];
    u8 *record;

    record = D_8220D8D0 + arg0 * 0x34;
    D_8220EB84 = 0;
    if (*(s16 *)(record + 4) != 0) {
        func_8220AD1C(coords);
        func_8220B7A0(coords[0], coords[1], record + 0x24, record + 0x27);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822089C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82208A1C.s")

extern s32 StageContext_GetFadeMode(void); extern void func_800086A4(s32); extern void StageFade_StartFromOpaque(s32); extern void func_80064D28(void); extern void func_8220B930(void); extern void func_8220C340(void); extern void func_82204148(void); extern s32 func_82208A1C(s32); extern void func_800548C4(void *); extern void func_80051D64(s32, s32); extern s32 D_8220DA0C; extern u8 D_8220EC28[];
extern void func_82208518(void);
void func_82208DCC(void) {
    s32 temp_v0;
    s16 temp_v0_2;
    s32 var_s0;
    s32 var_s1;
    s32 new_var;

    var_s0 = 1;
    new_var = StageContext_GetFadeMode();
    if (new_var != 0) {
        var_s0 = 0;
        func_800086A4(2);
        StageFade_StartFromOpaque(5);
    }
    var_s1 = 9;
    do {
        func_80064D28();
        func_8220B930();
        func_8220C340();
        func_82204148();
        func_82208518();
        temp_v0 = func_82208A1C(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != var_s1);
    ;
    if (D_8220DA0C != (*((s16 *) (*((u8 **) (((u8 *) D_8220DA08) + 0x20)))))) {
        if ((*((s16 *) (*((u8 **) (((u8 *) D_8220DA08) + 0x20))))) == 0) {
            *((u16 *) (D_8220EC28 + 2)) &= 0xFFFE;
        } else {
            *((u16 *) (D_8220EC28 + 2)) |= 1;
        }
        func_800548C4((void *) D_8220EC28);
    }
    func_80051D64(0x14, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82208EB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82209000.s")

f32 func_822091E0(f32 arg0) {
    return 1.5f - arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822091F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82209360.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_822094C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_8220980C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82209974.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82209BA4.s")

extern f32 D_822106B0[];

void func_82209E90(void) {
    D_822106B0[5] = 0.0f;
    D_822106B0[6] = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82209EA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_82209F50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_8220A098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_8220A154.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_8220A1C4.s")

extern void func_8003CD84();
extern void func_8220A1C4(s32);
extern s32 D_82210844;
s32 func_8220A5BC(s32 arg0, s32 arg1) {
    if ((arg0 != 0) && (arg0 == 5) && (D_82210844 != 0)) {
        func_8220A1C4(D_82210844);
        func_8003CD84();
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_8220A608.s")

extern void func_8220A608(s32);
extern s32 D_822109B4;
s32 func_8220AA08(s32 arg0, s32 arg1) {
    if ((arg0 != 0) && (arg0 == 5) && (D_822109B4 != 0)) {
        func_8220A608(D_822109B4);
        func_8003CD84();
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_8220AA54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_8220AC38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_113A60/func_8220AC64.s")

extern s16 D_822106BA;

void func_8220ACF4(void) {
    D_822106BA = -1;
}

s32 func_8220AD04(void) {
    return D_822106BA;
}

extern s16 D_822106B8;
s32 func_8220AD10(void) {
    return D_822106B8;
}

extern s16 D_822106CC, D_822106CE;

void func_8220AD1C(s16 *arg0) {
    arg0[0] = D_822106CC;
    arg0[1] = D_822106CE;
}

extern u8 D_8220DEF4;

void func_8220AD38(s32 arg0, void *arg1) {
    void *temp_v0;

    if (arg0 < 6) {
        temp_v0 = (arg0 * 0x1C) + &D_8220DEF4;
        (*(s16 *)((u8 *)(temp_v0) + (0xC))) = (s16) (*(s16 *)((u8 *)(arg1) + (0)));
        (*(s16 *)((u8 *)(temp_v0) + (0xE))) = (s16) (*(s16 *)((u8 *)(arg1) + (2)));
    }
}


void func_8220AD70(s32 arg0, void *arg1) {
    void *temp_v0;

    if (arg0 < 6) {
        temp_v0 = (arg0 * 0x1C) + &D_8220DEF4;
        (*(s16 *)((u8 *)(arg1) + (0))) = (s16) (*(s16 *)((u8 *)(temp_v0) + (0xC)));
        (*(s16 *)((u8 *)(arg1) + (2))) = (s16) (*(s16 *)((u8 *)(temp_v0) + (0xE)));
    }
}


void func_8220ADA8(s32 arg0, void *arg1) {
    void *temp_v0;

    if (arg0 < 6) {
        temp_v0 = (arg0 * 0x1C) + &D_8220DEF4;
        (*(s16 *)((u8 *)(temp_v0) + (0x10))) = (s16) (*(s16 *)((u8 *)(arg1) + (0)));
        (*(s16 *)((u8 *)(temp_v0) + (0x12))) = (s16) (*(s16 *)((u8 *)(arg1) + (2)));
    }
}

extern u8 D_8220DEF8[];
s32 func_8220ADE0(s32 arg0) {
    s32 result = 0;
    if ((arg0 >= 0) && (arg0 < 6)) {
        result = *(s32 *)(D_8220DEF8 + (arg0 * 0x1C));
    }
    return result;
}

extern s16 D_822106B2;

s32 func_8220AE10(void) {
    return D_822106B2 == 3;
}
#endif
