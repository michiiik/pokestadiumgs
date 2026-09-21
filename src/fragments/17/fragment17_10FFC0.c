#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82200600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82200694.s")

typedef struct F822006CC_Particle {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    s16 unk8;
    s16 unkA;
} F822006CC_Particle;
extern f32 D_8220E0C8;
extern f32 D_8220E0CC;
extern f32 D_80088E50[];
extern f32 D_80087E50[];
void func_822006CC(F822006CC_Particle *arg0, s32 arg1, s32 arg2) {
    u16 angle;
    f32 radius;
    s32 index;

    angle = guRandom() & 0xFFFF;
    radius = (s32)guRandom() % 33;
    arg0->unk0 = 1;
    arg0->unk2 = 0;
    arg0->unk4 = ((f32)((s32)guRandom() % 101) * D_8220E0C8) / 100.0f + D_8220E0CC;
    index = (s32)angle >> 4;
    arg0->unk8 = (s16)(s32)(D_80088E50[index] * radius + (f32)arg1);
    arg0->unkA = (s16)(s32)(D_80087E50[index] * radius + (f32)arg2);
}

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

extern s32 func_82200CEC(s32 a0);
void func_82200D8C(u8 *arg0, u8 arg1) { s32 result = func_82200CEC(arg1); *(u16 *)(arg0 + 4) = arg1; if (result != 0 && *(s16 *)arg0 == 1) { *(s16 *)arg0 = 2; *(s16 *)(arg0 + 2) = 0; *(s16 *)(arg0 + 8) = *(s16 *)(arg0 + 6); *(s16 *)(arg0 + 12) = *(s16 *)(arg0 + 10); *(f32 *)(arg0 + 20) = *(f32 *)(arg0 + 16); _bzero(arg0 + 36, 0x168); } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82200E04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822011AC.s")

typedef struct Func82201460Record {
    s16 active;
    s16 unk02;
    u16 flags;
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s16 x;
    s16 y;
    s16 dx;
    s16 dy;
} Func82201460Record;
extern void func_822011AC(s16, s16, s32, s16, s32);
extern void func_82200918(void *, u16);
void func_82201460(Func82201460Record *arg0) {
    s16 x;
    s16 y;
    if (arg0->active != 0) {
        x = arg0->x + arg0->dx;
        y = arg0->y + arg0->dy;
        func_822011AC(x, y, arg0->unk10, arg0->unk0A, arg0->flags);
        func_82200918(arg0, arg0->flags);
    }
}

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

s32 func_82201518(u8 *arg0) { s32 result; if (arg0[1] != 0) { if (arg0[0] == 0) { if (arg0[3] != 0) result = 0; else result = 3; } else result = 4; } else if (arg0[0] == 2) result = 5; else if (arg0[4] != 0) result = 1; else result = 2; return result; }

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

typedef struct { s16 x; s16 y; } F82201C70_Pair;
typedef struct { s16 x; s16 y; s16 w; s16 h; } F82201C70_Rect;
typedef struct { s16 mode; s16 flags; F82201C70_Rect current; F82201C70_Rect saved; s16 k0; s16 k1; s16 k2; s16 k3; F82201C70_Pair currentPair; F82201C70_Pair savedPair; s16 z0; s16 z1; } F82201C70_State;
typedef struct { u8 pad00[8]; F82201C70_Rect rect; u8 pad10[0x18]; F82201C70_Pair pair; } F82201C70_Input;
typedef struct { F82201C70_Pair origin; s16 w; s16 h; } F82201C70_NestedRect;
typedef struct { s16 mode; s16 flags; F82201C70_NestedRect current; F82201C70_NestedRect saved; s16 k0; s16 k1; s16 k2; s16 k3; F82201C70_Pair currentPair; F82201C70_Pair savedPair; s16 z0; s16 z1; } F82201C70_NestedState;
void func_82201C70(F82201C70_State *arg0, F82201C70_Input *arg1) {
    arg0->mode = 1;
    arg0->flags = 0;
    arg0->current.x = arg1->rect.x;
    arg0->current.y = arg1->rect.y;
    arg0->current.w = arg1->rect.w;
    arg0->current.h = arg1->rect.h;
    *(F82201C70_Pair *)&arg0->saved = *(F82201C70_Pair *)&arg0->current;
    arg0->saved.w = arg0->current.w;
    arg0->saved.h = arg0->current.h;
    arg0->k0 = 0x3B;
    arg0->k1 = 0x16B;
    arg0->k2 = 0x1F4;
    arg0->k3 = 0x55;
    arg0->currentPair.x = arg1->pair.x;
    arg0->currentPair.y = arg1->pair.y;
    arg0->savedPair.x = arg0->currentPair.x;
    arg0->savedPair.y = arg0->currentPair.y;
    arg0->z0 = 0;
    arg0->z1 = 0;
}

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

extern s32 func_82202628(s32 arg0);
s32 func_8220268C(s32 arg0, s32 arg1) {
    s32 sp1C = 4;

    switch (arg0) {
        case 1:
            sp1C = 10;
            break;
        case 2:
            sp1C = 6;
            break;
        case 3:
            sp1C = 0;
            break;
        case 4:
            sp1C = 14;
            break;
        case 5:
            sp1C = 8;
            break;
        case 6:
            sp1C = 12;
            break;
        case 7:
            sp1C = 2;
            break;
    }

    if (arg1 != 0) {
        sp1C = func_82202628(arg0);
    }

    return sp1C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82202718.s")

extern void func_800504BC(s16 *arg0);
extern u8 D_8220E315[];
extern u8 D_8220E36A[];

s32 func_82202A84(s32 arg0, u8 *arg1) {
    void *sp1C; s32 temp_v1; void *temp_v0; s32 sp30; s32 pad0; s32 pad1;
    temp_v1 = *(s32 *)(arg1 + 0x20);
    if (arg0 != 0) {
        if (arg0 == 1) {
            if (D_8220E315[temp_v1 * 0x14] != 2) {
                temp_v0 = (u8 *)&D_8220E378 + (temp_v1 * 0x3C);
                sp1C = temp_v0;
                sp30 = temp_v1;
                func_800504BC((s16 *)((u8 *)temp_v0 + 0x30));
                *(s16 *)((u8 *)temp_v0 + 0x30) = *(s16 *)((u8 *)arg1 + 8) + *(s16 *)((u8 *)temp_v0 + 0x30) + 9;
                *(s16 *)((u8 *)temp_v0 + 0x32) = *(s16 *)((u8 *)arg1 + 0xA) + *(s16 *)((u8 *)temp_v0 + 0x32) + 0xE;
                if (D_8220D788 < *(s16 *)(D_8220E36A + (sp30 * 4))) {
                    *(u16 *)((u8 *)arg1 + 2) = *(u16 *)((u8 *)arg1 + 2) | 2;
                } else {
                    *(u16 *)((u8 *)arg1 + 2) = *(u16 *)((u8 *)arg1 + 2) & 0xFFFD;
                }
            } else {
                *(u16 *)((u8 *)arg1 + 2) = *(u16 *)((u8 *)arg1 + 2) & 0xFFFD;
            }
        }
    }
    return 0;
}

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

extern u8 D_8220E310[];
extern u8 *func_8004C874(s32, s32);
extern void func_8004C54C(s32, void *);
typedef struct F82202FC8_Record { u8 pad0[5]; u8 type; u8 pad6[2]; u8 payload[12]; } F82202FC8_Record;
extern u16 D_8220E4C0;
s32 func_82202FC8(s32 arg0, u8 *arg1) {
    s32 index = *(s32 *)(arg1 + 0x20);
    u8 *data = NULL;
    u8 *record;
    s32 type;

    switch (arg0) {
        case 0:
            break;
        case 1:
            record = D_8220E310 + index * 0x14;
            type = record[5];
            switch (type) {
                case 0:
                case 3:
                    data = record + 8;
                    break;
                case 4:
                case 5:
                    data = func_8004C874(0x17, 0x40);
                    break;
            }
            if (data != NULL) {
                func_8004C54C(0x15, data);
                if (D_8220E4C0 & 8) {
                    *(u16 *)(arg1 + 2) |= 2;
                } else {
                    *(u16 *)(arg1 + 2) &= 0xFFFD;
                }
            } else {
                *(u16 *)(arg1 + 2) &= 0xFFFD;
            }
            break;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822030BC.s")

extern u8 *D_8220E4D0[];
s32 func_822031D0(s32 arg0, u8 *arg1) {
    s32 temp_v0 = *(s32 *)(arg1 + 0x20);
    switch (arg0) {
    case 0:
        *(u16 *)(arg1 + 2) &= 0xFFFD;
        D_8220E4D0[temp_v0] = arg1;
        break;
    case 1:
        break;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_82203210.s")

extern Gfx *D_800D0510;
s32 func_8220336C(s32 arg0, s32 arg1) { gDPPipeSync(D_800D0510++); gDPSetEnvColor(D_800D0510++, 0xFF, 0xFF, 0, 0xFF); return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822033BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_10FFC0/func_822037E4.s")

extern void *StageContext_GetCurrentImage(void);
extern void func_800088DC(void);
extern void func_81600F0C(s32, s16, s16, s16, s32);
extern void func_80006F70(Gfx **, s32, s32, s16, s32);
extern void func_800503A4(u8 *);
extern void func_822037E4(void);
extern s32 func_80008648(void);
extern s32 D_8220D770;
extern void *D_8220E360;
extern u8 *D_8220E364;
extern s16 D_8220E4CA;
extern s16 D_8220E4CC;
extern s16 D_8220E4CE;
extern Gfx * D_800D0510;
extern u8 D_8220E4C8[];
void func_822039C8(void) {
    s32 pad;
    u8 *image;

    image = StageContext_GetCurrentImage();
    func_800088DC();
    func_81600F0C(((s32 *)D_8220E360)[1], *(s16 *)D_8220E4C8, D_8220E4CA, D_8220E4CC, D_8220E4CE);
    func_80006F70(&D_800D0510, 0, 0, *(s16 *)(image + 4), *(u16 *)(image + 6));
    func_800503A4(D_8220E364);
    func_800503A4(*(u8 **)((u8 *)D_8220E360 + 0x1C));
    func_822037E4();
    func_80008648();
    D_8220D770 += 1;
}

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

/* func_82203E70 is still GLOBAL_ASM, but its .s is hand-maintained (not the
 * splat-generated asm/us/nonmatchings/.../func_82203E70.s) so that it can
 * also carry jtbl_8220E10C's first entry (4 bytes) in a .late_rodata block
 * ahead of its .text. That word has to land immediately after
 * func_8220268C's own compiler-generated jump table (jtbl_8220E0F0) to
 * satisfy this fragment's SUBALIGN(16); a plain C global here would instead
 * be emitted by IDO BEFORE func_8220268C's switch table (IDO always emits
 * named/array rodata ahead of switch-table "late" rodata within one
 * compilation), landing at the wrong address. Placing it in a GLOBAL_ASM
 * .late_rodata block instead makes asm-processor position it correctly:
 * after all first-pass rodata and after func_8220268C's own late-rodata
 * jump table, matching retail. jtbl_8220E10C's remaining entries keep
 * coming from the unmodified data blob at their real retail addresses. */
#pragma GLOBAL_ASM("hand_asm/fragments/17/func_82203E70_manual.s")

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
