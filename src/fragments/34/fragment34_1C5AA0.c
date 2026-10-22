#include "global.h"


#ifdef VERSION_US
extern u8 D_88523100[];
void func_88508490(void){s32 i=0;u8 *p=D_88523100;do{i++;p+=0x24;*(s32 *)(p-0x24)=0;*(s16 *)(p-0x20)=0;*(s16 *)(p-0x1E)=0;*(s16 *)(p-0x1C)=0;*(s16 *)(p-0x1A)=0;*(s16 *)(p-0x18)=0;*(s16 *)(p-0x16)=0;*(s16 *)(p-0x14)=0;*(s16 *)(p-0x12)=0;*(s16 *)(p-0x10)=0;*(f32 *)(p-0xC)=0.0f;*(f32 *)(p-8)=0.0f;*(f32 *)(p-4)=0.0f;}while(i!=2);}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_885084EC.s")

extern u8 D_88523100[];
extern s16 D_88523034;
extern u8 D_88523030[];
extern f32 D_80087E50[];
s32 func_8850CED8(s32);
extern void func_8850A0EC(s32);
void func_885084EC(s32, s32);
void func_88508780(u8 *arg0) {
    *(s16 *)(arg0 + 8) = *(s16 *)(arg0 + 8) - 2;
    if (*(s16 *)(arg0 + 8) < 0xBF) {
        func_885084EC((u8)((arg0 - D_88523100) / 0x24), 2);
    }
}

/* mkdraft:func_885087D4 begin */
typedef struct { s32 unk_00; s16 unk_02; s16 unk_04; s16 unk_06; s16 unk_08; s16 unk_0A; s16 unk_0C; s16 unk_0E; s16 unk_10; s16 unk_12; f32 unk_14; f32 unk_18; f32 unk_1C; } unk_D_88523100;
extern f32 D_80087E50[];
extern f32 D_8850D56C;

void func_885087D4(unk_D_88523100 *arg0) {
    arg0->unk_04 = D_88523034 + arg0->unk_02;
    arg0->unk_06 = (s16)(D_80087E50[(u16)(arg0->unk_12) >> 4] * 3.0f + ((D_80087E50[(u16)(arg0->unk_12) >> 4] * 3.0f) > 0.0f ? 0.5f : -0.5f)) + 0xBE;

    arg0->unk_12 += 0x800;

    arg0->unk_1C -= D_8850D56C;
    if (arg0->unk_1C < 1.0f) {
        arg0->unk_1C = 1.0f;
    }
}
/* mkdraft:func_885087D4 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850889C.s")

void TradeCable_UpdateLightWaitPulse(unk_D_88523100 *arg0) {
    arg0->unk_04 = D_88523034 + arg0->unk_02;
    arg0->unk_06 = (s16)(2.0f * D_80087E50[(u16)(arg0->unk_12) >> 4] + ((2.0f * D_80087E50[(u16)(arg0->unk_12) >> 4]) > 0.0f ? 0.5f : -0.5f)) + 0xD2;

    arg0->unk_12 += 0x800;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508B98.s")

extern u8 D_88523100[];
extern u8 D_88523030[];
extern s32 MathUtil_Random16(void);
void func_88508BEC(u8 *arg0) {
    *(s16 *)(arg0 + 0x14) = *(s16 *)(arg0 + 0x14) + 1;
    *(s16 *)(arg0 + 8) = *(s16 *)(arg0 + 0x14) + *(s16 *)(arg0 + 8);
    if (*(s16 *)(arg0 + 8) >= 0xD2) {
        *(s32 *)(arg0 + 0) = 7;
        *(s16 *)(arg0 + 8) = 0xD2;
        *(f32 *)(arg0 + 0x1C) = (f32)(MathUtil_Random16() % 16);
        *(s16 *)(arg0 + 0x14) = MathUtil_Random16();
        if (((s32)(arg0 - D_88523100) / 0x24) == 0) {
            *(u16 *)(D_88523030 + 0xE) &= 0xFFDF;
        }
    }
}

void TradeCable_UpdateLightFlashPulse(unk_D_88523100 *arg0) {
    arg0->unk_04 = D_88523034 + arg0->unk_02;
    arg0->unk_06 = (s16)(2.0f * D_80087E50[(u16)(arg0->unk_12) >> 4] + ((2.0f * D_80087E50[(u16)(arg0->unk_12) >> 4]) > 0.0f ? 0.5f : -0.5f)) + 0xD2;

    arg0->unk_12 += 0x800;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508D34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508E34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508F78.s")

extern void Gfx_SetScissorRect(Gfx **, s32, s32, s32, s32);
extern void func_88508F78(s32, s32, s32, s16);
extern Gfx *D_800D0510;
extern u8 D_88523148;
extern u8 D_88523100[];
void func_88509290(void) {
    s32 changed = 0;
    s32 limit = 2;
    u8 *p; s32 i = 0; p = D_88523100; do {
        if (*(s32 *)(p + 0) != 0) {
            if ((*(s16 *)(p + 0xE) != 0) && (*(s16 *)(p + 0x10) != 0)) {
                *(s16 *)(p + 0xA) = *(s16 *)(p + 6) - 0x40;
                changed = 1;
                if (*(s16 *)(p + 0xA) < 0) {
                    *(s16 *)(p + 0xA) = 0;
                }
                Gfx_SetScissorRect(&D_800D0510, *(s16 *)(p + 0xA), *(s16 *)(p + 0xC), *(s16 *)(p + 0xE), *(s16 *)(p + 0x10));
            }
            func_88508F78(*(s16 *)(p + 6), *(s16 *)(p + 8), *(s32 *)(p + 0x18), (s16)(*(f32 *)(p + 0x1C) + ((0.0f < *(f32 *)(p + 0x1C)) ? 0.5f : -0.5f)));
        }
        i++;
        p += 0x24;
        if (i == limit) break;
    } while (1);
    if (changed != 0) {
        u8 *q = &D_88523148;
        Gfx_SetScissorRect(&D_800D0510, *(s16 *)(q + 0), *(s16 *)(q + 2), *(s16 *)(q + 4), *(s16 *)(q + 6));
    }
}

extern u8 D_88523050[];
void func_885093F0(void) { s32 i = 0; u8 *ptr = D_88523050; do { i += 1; ptr += 0x50; *(s32 *)(ptr - 0x50) = 0; } while (i != 2); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88509418.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88509538.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_885095EC.s")

typedef struct { s16 unk_00; s16 unk_02; s16 unk_04; } unk_D_88523050_012;
typedef struct { s32 unk_00; s16 unk_04; s16 unk_06; s16 unk_08; s16 unk_0A; s16 unk_0C; s16 unk_0E; s16 unk_10; unk_D_88523050_012 unk_12[10]; } unk_D_88523050;

void TradeCable_SpawnBallTrailGhost(unk_D_88523050 *arg0) {
    s32 i;
    unk_D_88523050_012 *var_v0 = NULL;

    for (i = 0; i < 10; i++) {
        if (arg0->unk_12[i].unk_04 == 0) {
            break;
        }
    }

    if (i < 10) {
        var_v0 = &arg0->unk_12[i];
    }

    if (var_v0 != NULL) {
        var_v0->unk_00 = arg0->unk_04;
        var_v0->unk_02 = arg0->unk_06;
        var_v0->unk_04 = 0x14;
        arg0->unk_10++;
    }
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850974C.s")

extern void func_8850974C(u8 *);
extern void TradeCable_SpawnBallTrailGhost(unk_D_88523050 *);
extern void func_885084EC(s32, s32);
void func_88509870(u8 *arg0) {
    s16 temp_v0;
    s16 temp_v0_2;

    if (*(s16 *)(arg0 + 0x10) > 0) {
        func_8850974C(arg0);
    }
    temp_v0 = *(s16 *)(arg0 + 4);
    if ((temp_v0 < 0xA0) || (temp_v0 >= 0x1C3)) {
        if (*(s16 *)(arg0 + 0x10) == 0) {
            *(s32 *)(arg0 + 0) = 0;
            func_885084EC((((s32)(arg0 - D_88523050) / 80) ^ 1) & 0xFF, 6);
        }
    } else {
        temp_v0_2 = *(s16 *)(arg0 + 8);
        if (temp_v0_2 > 0) {
            *(s16 *)(arg0 + 8) = temp_v0_2 - 1;
        }
        temp_v0_2 = *(s16 *)(arg0 + 8);
        if (temp_v0_2 == 0) {
            if (*(s16 *)(arg0 + 0x10) < 0xA) {
                TradeCable_SpawnBallTrailGhost((unk_D_88523050 *)arg0);
                *(s16 *)(arg0 + 8) = 2;
            }
        }
        if ((((s32)(arg0 - D_88523050) / 80) & 0xFF) != 0) {
            *(s16 *)(arg0 + 0xC) = *(s16 *)(arg0 + 0xC) - 1;
        } else {
            *(s16 *)(arg0 + 0xC) = *(s16 *)(arg0 + 0xC) + 1;
        }
        *(s16 *)(arg0 + 4) = *(s16 *)(arg0 + 0xC) + *(s16 *)(arg0 + 4);
    }
}

extern u8 D_88523050[];
extern s32 D_88523018;
extern u8 D_88523030[];
extern s32 func_8850CED8(s32);
extern void func_88509538(u8 *);
extern void func_885095EC(u8 *);
extern void func_88509870(u8 *);
extern void func_88509418(s32, s32);
extern void func_800226C0(s32);
void func_8850998C(void) {
    s32 i;
    u8 *ptr;
    s32 state;

    ptr = D_88523050;
    i = 0;
    do {
        state = *(s32 *)ptr;
        switch (state) {
        case 1:
            func_88509538(ptr);
            break;
        case 2:
            func_885095EC(ptr);
            break;
        case 3:
            func_88509870(ptr);
            break;
        }
        i += 1;
        ptr += 0x50;
    } while (i != 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88509A38.s")

extern u8 D_885230F0;
void func_8850A0A0(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_88509E74(void) {
    if (D_885230F0 == 0) {
        func_8850A0A0(0x200, 0xB9, 0x4C, 0x5A);
        return;
    }
    func_8850A0A0(0x2D, 0xB9, 0x4C, 0x5A);
}

extern u8 D_8850D6D8;
void func_8850A0A0(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
extern s32 D_880068B8;
extern void func_8004D878(s32, s32, s32);
void func_8850A0A0(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_88509EC8(void) {
    func_8850A0A0(0, 0, 0x280, 0x1E0);
    D_880068B8 = 1;
    if ((*(u8 *)((u8 *)(&D_885230F0) + (8))) != 0) {
        func_8004D878((s32) (((*(u8 *)((u8 *)(&D_885230F0) + (0))) * 0xA960) + 8 + &D_8850D6D8), 0, (*(s32 *)((u8 *)(&D_885230F0) + (4))));
    }
}

extern void func_88900494();
extern s32 D_880068B4;

void func_88509F40(void) {
    D_880068B4 = 1;
    func_88900494();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88509F68.s")

extern u8 D_88523148;
void func_8850A0A0(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    (*(s16 *)((u8 *)(&D_88523148) + (0))) = arg0;
    (*(s16 *)((u8 *)(&D_88523148) + (2))) = arg1;
    (*(s16 *)((u8 *)(&D_88523148) + (4))) = arg2;
    (*(s16 *)((u8 *)(&D_88523148) + (6))) = arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A0EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A2F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A3F0.s")

extern u8 D_88523100[];
extern s16 D_88523034;
extern u8 D_88523030[];
extern f32 D_80087E50[];
s32 func_8850CED8(s32);
extern void func_8850A0EC(s32);
void func_885084EC(s32, s32);
void func_8850A5CC(void) {
    s16 v = *(s16 *)(D_88523030 + 0x18);
    if (v > 0) {
        *(s16 *)(D_88523030 + 0x18) = v - 1;
    }
    if (func_8850CED8(4) != 0) {
        func_8850A0EC(6);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A614.s")

void func_8850A6C8(void) {
    s16 v = *(s16 *)(D_88523030 + 0x18);
    if (v > 0) {
        *(s16 *)(D_88523030 + 0x18) = v - 1;
    }
    if (func_8850CED8(5) != 0) {
        func_8850A0EC(9);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A710.s")

void func_8850A8BC(void) {
    if (D_88523018 == 1) {
        *(u16 *)(D_88523030 + 0xE) &= 0xFFF6;
    } else {
        *(u16 *)(D_88523030 + 0xE) |= 9;
    }
    if (func_8850CED8(7) != 0) {
        if ((*(u16 *)(D_88523030 + 0xE) & 0x20) == 0) {
            *(u16 *)(D_88523030 + 0xE) |= 0x20;
            func_88509418(0, 1);
            func_88509418(1, 1);
            func_800226C0(0x143);
        }
    }
}

extern void func_8850A0EC(s32);
s32 func_8850CED8(s32);

void func_8850A958(void) {
    if (func_8850CED8(7) != 0) {
        func_8850A0EC(5);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A988.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850AAA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850ABCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850ACD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850AEA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850AFDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850B2DC.s")

s32 func_8004C990(s32, s32);
extern void func_8850B2DC(s32, s32, s16, s16, f32, s32, s32, s32, s32, s32);

void func_8850B914(s16 arg0, s16 arg1, f32 arg2) {
    func_8850B2DC(func_8004C990(0x147, 0), 0, arg0, arg1, arg2, 0, 0xE4, 0, 0xE4, -0x10);
}

s32 func_8004C990(s32, s32);

void func_8850B980(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    func_8850B2DC(func_8004C990(0x148, 1), 0, arg0, arg1, arg2, (s32) arg3, (s32) arg4, (s32) arg5, 0x64, 0);
}

extern Gfx *D_800D0510;
extern u8 D_8850D300[];
extern s32 func_8004C990(s32, s32);
extern void func_8850B2DC(s32, s32, s16, s16, f32, s32, s32, s32, s32, s32);
void func_8850B9F4(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6) {
    s32 local[4];
    gSPDisplayList(D_800D0510++, D_8850D300);
    gDPSetPrimColor(D_800D0510++, 0, 0, 0x64, 0x64, 0xFF, arg6);
    local[0] = func_8004C990(0x148, 0);
    func_8850B2DC(local[0], func_8004C990(0x148, 1), arg0, arg1, arg2, arg3, arg4, arg5, 0x64, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850BACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850BDE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850C514.s")

s32 func_800071A4(s32, s32, s32, s32, s32);
extern void func_88508490();
extern s32 D_8852304C;

void func_8850C948(void) {
    func_8850A0EC(0);
    func_88508490();
    func_885093F0();
    D_8852304C = func_800071A4(0, 2, 0x20, 0x20, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850C998.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850CED8.s")
#endif
