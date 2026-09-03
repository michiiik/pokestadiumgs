#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82200600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82200694.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822006CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822007D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82200918.s")

extern void _bzero(void *, s32);
void func_82200C3C(u8* arg0) {
    _bzero(arg0 + 36, 360);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82200C60.s")

extern s32 func_8004C8C0(s32);
extern s32 D_8220E4E0;
void func_82200CB4(void) {
    _bzero(&D_8220E4E0, 0x630);
    func_8004C8C0(0x95);
    func_8004C8C0(0x93);
}

s32 func_82200CEC(s32 a0){s32 v1=0;volatile s32 *p=&a0;a0&=0xFF;if(a0==1||a0==2||a0==3||a0==4)v1=1;return v1;}

void func_82200D28(void *arg0, s32 arg1)
{
  if (func_82200CEC(arg1 & 0xFF) != 0)
  {
    *((s16 *) (((u8 *) arg0) + 0)) = 1;
    *((s16 *) (((u8 *) arg0) + 2)) = (s16) (guRandom() % 24U);
    *((s16 *) (((u8 *) arg0) + 0xA)) = 0x80;
    *((f32 *) (((u8 *) arg0) + 0x10)) = 1.5f;
  }
  if (!arg1)
  {
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82200D8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82200E04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822011AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82201460.s")

extern u8 D_8220E4C8[];
void func_822014D8(void) {
    *(u16 *)(D_8220E4C8 + 0) = 0;
    *(u16 *)(D_8220E4C8 + 2) = 0;
    *(u16 *)(D_8220E4C8 + 4) = 0x280;
    *(u16 *)(D_8220E4C8 + 6) = 0x1E0;
}

void func_822014FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    *(u16 *)(D_8220E4C8 + 0) = arg0;
    *(u16 *)(D_8220E4C8 + 2) = arg1;
    *(u16 *)(D_8220E4C8 + 4) = arg2;
    *(u16 *)(D_8220E4C8 + 6) = arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82201518.s")

s32 func_8220158C(void *arg0) {
    s32 var_v1;
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)(arg0) + (5)));
    var_v1 = 1;
    if ((temp_v0 == 1) || (temp_v0 == 2)) {
        var_v1 = 0;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822015B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822016C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822017B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82201834.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82201960.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82201AE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82201B70.s")

extern s16 D_8220E378;
extern s16 D_8220E3B4;
extern s16 D_8220E3F0;
extern s16 D_8220E42C;
s32 func_82201C14(void) {
    s32 var_v1;

    var_v1 = 1;
    if (D_8220E378 != 2) {
        var_v1 = 0;
    }
    if (D_8220E3B4 != 2) {
        var_v1 = 0;
    }
    if (D_8220E3F0 != 2) {
        var_v1 = 0;
    }
    if (D_8220E42C != 2) {
        var_v1 = 0;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82201C70.s")

s32 func_82201D08(void *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if ((*(s16 *)((u8 *)(arg0) + (0))) == 1) {
        var_v1 = 1;
        (*(s16 *)((u8 *)(arg0) + (0))) = 2;
        (*(s16 *)((u8 *)(arg0) + (2))) = 0;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82201D30.s")

extern void func_8004C990(u16, u16, u8 *);
extern s16 D_8220D788;
extern u8 D_8220E368[];
s32 func_82201EB4(s32 arg0, u8 *arg1) {
    s32 sp18;
    s32 temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;
    temp_v1 = *(s32 *)(arg1 + 0x20);
    switch (arg0) {
    case 0:
        if (temp_v1 == 0) {
            arg1[1] |= 4;
            sp18 = temp_v1;
            func_8004C990(*(u16 *)(arg1 + 0x24), *(u16 *)(arg1 + 0x26), arg1);
        } else {
            *(u16 *)(arg1 + 2) &= 0xFFFD;
        }
        temp_v0 = (u8 *)((u32)&D_8220E368 + temp_v1 * 4);
        *(s16 *)(temp_v0 + 0) = 0;
        *(s16 *)(temp_v0 + 2) = 0;
        *(s16 *)(temp_v0 + 8) = *(s16 *)(arg1 + 8);
        *(s16 *)(temp_v0 + 0xA) = *(s16 *)(arg1 + 0xA);
        break;
    case 1:
        temp_v0_2 = (u8 *)((u32)&D_8220E368 + (2 * temp_v1) * 2);
        if (D_8220D788 < *(s16 *)(temp_v0_2 + 2)) {
            *(s16 *)(arg1 + 8) = *(s16 *)(temp_v0_2 + 0) + *(s16 *)(temp_v0_2 + 8);
            *(s16 *)(arg1 + 0xA) = *(s16 *)(temp_v0_2 + 2) + *(s16 *)(temp_v0_2 + 0xA);
            *(u16 *)(arg1 + 2) |= 2;
        } else {
            *(u16 *)(arg1 + 2) &= 0xFFFD;
        }
        break;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82201FBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822023D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82202534.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82202628.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_8220268C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82202718.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82202A84.s")

extern u16 D_8220E4C0;
s32 func_82202B80(s32 arg0, u8 *arg1) {
    switch (arg0) {
    case 0:
        *(u16 *)(arg1 + 2) &= 0xFFFD;
        break;
    case 1:
        if (D_8220E4C0 & 4) {
            *(u16 *)(arg1 + 2) |= 2;
        } else {
            *(u16 *)(arg1 + 2) &= 0xFFFD;
        }
        break;
    default:
        break;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82202BE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82202E0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82202FC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822030BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822031D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82203210.s")

extern Gfx *D_800D0510;
s32 func_8220336C(s32 arg0, s32 arg1) { gDPPipeSync(D_800D0510++); gDPSetEnvColor(D_800D0510++, 0xFF, 0xFF, 0, 0xFF); return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822033BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822037E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822039C8.s")

extern s32 D_8220E4B8, D_8220D784;

void func_82203A84(void) {
    D_8220E4B8 = 0;
    D_8220D784 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82203A98.s")

extern void *D_80087200; extern void func_800226C0(s32);
s32 func_82203B3C(void) { s32 result = 0; if ((*(u16 *)((u8 *)D_80087200 + 8) & 0x8000) != 0) { func_800226C0(0x33); result = 1; } else if ((*(u16 *)((u8 *)D_80087200 + 8) & 0x4000) != 0) { func_800226C0(3); result = -1; } return result; }

extern s32 D_8220D784;
extern s32 D_8220E4BC;
extern u8 D_8220E468[];
extern u8 D_8220E490[];
extern s32 func_82201D08(void *);
void func_82203B98(void) {
    D_8220E4BC = 0;
    func_82201D08(D_8220E468);
    func_82201D08(D_8220E490);
    D_8220D784 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82203BD8.s")

extern void func_822014D8();
extern void StageFade_StartFromTransparent();
extern void func_80035424();
void func_82203E40(void) { func_822014D8(); StageFade_StartFromTransparent(5); func_80035424(15); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82203E70.s")

extern void StageFade_StartFromOpaque(s32);
extern void func_800086A4(s32);
extern void func_80064D28();
extern void func_822015B4();
extern void func_82201B70();
extern void func_822039C8();
s32 func_82203E70(s32);

void func_8220402C(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        func_80064D28();
        func_822015B4();
        func_82201B70();
        func_822039C8();
        temp_v0 = func_82203E70(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 5);
}
#endif
