#include "global.h"


#ifdef VERSION_US
extern Gfx* D_800D0510;
void ParticleGfx_SetPrimColor_fragment82(u8 r, u8 g, u8 b, u8 a) {
    gDPSetPrimColor(D_800D0510++, 0, 0, r, g, b, a);
}

void func_82D02AC8(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, (((((arg0 << 8) & 0xF800) | ((arg1 << 3) & 0x7C0) | ((arg2 >> 2) & 0x3E) | (arg3 & 1)) << 16) |
        (((arg0 << 8) & 0xF800) | ((arg1 << 3) & 0x7C0) | ((arg2 >> 2) & 0x3E) | (arg3 & 1))));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D02B44.s")

extern void func_8004C8C0(s32);
void func_82D02C98(void) {
    func_8004C8C0(0x153);
    func_8004C8C0(0xF7);
    func_8004C8C0(0x7C);
    func_8004C8C0(0x101);
    func_8004C8C0(0x102);
    func_8004C8C0(0x33);
    func_8004C8C0(0x79);
    func_8004C8C0(0x1B);
    func_8004C8C0(0x1C);
    func_8004C8C0(0xAF);
}

void func_82D02D00(void) { func_8004C4B0(0x43); }

void func_82D02D20(s32 arg0, s32 arg1)
{
  s32 temp_a2;
  s32 temp_a3;
  unsigned long long new_var;
  new_var = 0xFFFF;
  temp_a2 = arg0 & new_var;
  temp_a3 = arg1 & new_var;
  func_8004D1FC(func_8004C990(temp_a2, temp_a3, temp_a2, temp_a3));
}

void func_82D02D5C(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    s32 value = func_8004C990((s32)arg2, (s32)arg3);
    func_8004D19C((s32)arg0, (s32)arg1, value, 0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D02DA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D02F78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D03144.s")

void func_82D03324(s16 arg0, s16 arg1, s32 arg2) {
    func_80044270((s32)arg0, (s32)arg1, (s16)arg2, 0x28, 0, 0, 0x400, 0x400, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D03380.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D03598.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D03778.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D03830.s")

extern void func_82D03598(s16, s16, u16, u16);
extern void func_82D03778(s16, s16, s32, s32);
void func_82D0396C(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    func_82D03778((s16) (arg0 + 3), (s16) (arg1 + 3), (arg2 - 6) & 0xFFFF, (arg3 - 6) & 0xFFFF);
    func_82D03598(arg0, arg1, arg2, arg3);
}

extern void func_82D03830(s16, s16, s32, s32);
void func_82D039E4(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    func_82D03830((s16) (arg0 + 3), (s16) (arg1 + 3), (arg2 - 5) & 0xFFFF, (arg3 - 6) & 0xFFFF);
    func_82D03598(arg0, arg1, arg2, arg3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D03A5C.s")

extern f32 D_80087E50[];
extern u16 D_82D07280;
extern void func_82D02D5C(s16, s16, u16, u16);
extern int func_80044270(s32, s32, int, int, int, int, int, int, int);
void func_82D03BEC(s16 arg0, s16 arg1, u16 arg2) {
    s32 sp34;
    sp34 = (s32)(D_80087E50[(s32)D_82D07280 >> 4] * 2);
    D_82D07280 += 0x2000;
    func_82D02D5C(arg0, (s16)(arg1 - sp34), 0x1C, 0);
    func_80044270(arg0, (s16)(arg1 + arg2 + sp34), 0x20, 0xA, 0, 0x120, 0x400, -0x400, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D03CC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D049A0.s")

extern s32 func_80049064(s32, s32, s32, s32);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800499EC(void);
extern u8 D_82D071D8[];
extern void func_82D02D20(s32 arg0, s32 arg1);
void func_82D04B84(void *arg0) {
    gSPDisplayList(D_800D0510++, D_82D071D8);
    ParticleGfx_SetPrimColor_fragment82(
        *(u8 *)((u8 *)arg0 + 0x20),
        *(u8 *)((u8 *)arg0 + 0x21),
        *(u8 *)((u8 *)arg0 + 0x22),
        *(u8 *)((u8 *)arg0 + 0x23));
    func_82D02D20(0xF7, 0);
    func_82D03324(
        *(s16 *)((u8 *)arg0 + 0x14),
        *(s16 *)((u8 *)arg0 + 0x16),
        *(u16 *)((u8 *)arg0 + 0x18));
    func_800498C4();
    func_800496A4(0x10, 0);
    func_80049064(
        *(s16 *)((u8 *)arg0 + 0x14) + 0x40,
        *(s16 *)((u8 *)arg0 + 0x16) + 4,
        0,
        func_8004C874(0x43, 0));
    func_800499EC();
}

extern void func_8004972C(s32, s32, s32, s32);
extern void Ui_DrawAnimatedTextureMarker(s32, s32);
extern s32 func_80049064(s32, s32, s32, s32);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800499EC(void);
extern u8 D_82D071D8[];
extern void func_82D02D20(s32 arg0, s32 arg1);
void func_82D04C44(void *arg0) {
    u8 *sp24;

    sp24 = *(u8 **)((u8 *)arg0 + 0x10);
    gSPDisplayList(D_800D0510++, D_82D071D8);
    ParticleGfx_SetPrimColor_fragment82(
        *(u8 *)((u8 *)arg0 + 0x20),
        *(u8 *)((u8 *)arg0 + 0x21),
        *(u8 *)((u8 *)arg0 + 0x22),
        *(u8 *)((u8 *)arg0 + 0x23));
    func_82D02D20(0xF7, 0);
    func_82D03324(
        *(s16 *)((u8 *)arg0 + 0x14),
        *(s16 *)((u8 *)arg0 + 0x16),
        *(u16 *)((u8 *)arg0 + 0x18));
    func_800498C4();
    func_800496A4(0x10, 0);
    if (sp24[0] == 0) {
        if (*(s8 *)(sp24 + 1) == *(u8 *)((u8 *)arg0 + 1)) {
            func_8004972C(0xFF, 0xFF, 0, *(u8 *)((u8 *)arg0 + 0x27));
        } else {
            func_8004972C(0xFF, 0xFF, 0xFF, *(u8 *)((u8 *)arg0 + 0x27));
        }
    } else {
        func_8004972C(0xFF, 0xFF, 0xFF, *(u8 *)((u8 *)arg0 + 0x27));
    }
    func_80049064(
        *(s16 *)((u8 *)arg0 + 0x14) + 0x40,
        *(s16 *)((u8 *)arg0 + 0x16) + 4,
        0,
        func_8004C874(0x43, *(u8 *)((u8 *)arg0 + 1) + 1));
    func_800499EC();
    if (*(u8 *)((u8 *)arg0 + 0xB) == 0 &&
        *(s8 *)(sp24 + 1) == *(u8 *)((u8 *)arg0 + 1) &&
        sp24[0] == 0) {
        Ui_DrawAnimatedTextureMarker(
            (s16)(*(s16 *)((u8 *)arg0 + 0x14) + 0x18),
            (s16)(*(s16 *)((u8 *)arg0 + 0x16) + 4));
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D04DC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D0599C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D05BD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D05C90.s")

extern u8 D_82D07184;
typedef struct { u8 pad0[2]; s16 value2; u8 pad4[2]; s16 value6; u8 pad8[2]; u8 flagsA; u8 valueB; u8 countC; u8 padD[7]; s16 output14; } Fragment82BaseRateState;
void func_82D05CF4(Fragment82BaseRateState *arg0) {
    if (D_82D07184 >= arg0->countC) {
        arg0->flagsA |= 1;
        arg0->output14 = arg0->value2 + (arg0->value6 * arg0->countC) / D_82D07184;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D05D74.s")

extern u8 D_82D07184;
extern u8 D_82D07188;
typedef struct { u8 pad0[6]; s16 value6; u8 pad8[2]; u8 flagsA; u8 valueB; u8 countC; u8 padD[7]; s16 output14; } Fragment82State;
void func_82D05E38(Fragment82State *arg0) {
    if (D_82D07188 >= arg0->countC) {
        arg0->flagsA |= 1;
        arg0->output14 = (-arg0->value6 * arg0->countC) / D_82D07184;
    }
}

extern u8 D_82D06F97;
extern u8 D_82D07188;
typedef struct { u8 pad0[6]; s16 value6; u8 pad8[2]; u8 flagsA; u8 valueB; u8 countC; u8 padD[0x16]; u8 output23; } Fragment82RateState;
void func_82D05EB4(Fragment82RateState *arg0) {
    if (D_82D07188 >= arg0->countC) {
        if (arg0->countC == 0) {
            arg0->output23 = D_82D06F97;
            return;
        }
        arg0->output23 = (arg0->countC * D_82D06F97) / D_82D07188;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D05F30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D06040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D06150.s")

extern u8 D_82D0716C[]; extern u8 D_82D07174[]; extern u8 D_82D07190; void func_82D062CC(u8 *arg0) { func_82D06150(arg0, D_82D0716C, D_82D07174, D_82D07190); }

extern u8 D_82D07174[]; extern u8 D_82D0716C[]; extern u8 D_82D07190; void func_82D06300(u8 *arg0) { func_82D06150(arg0, D_82D07174, D_82D0716C, D_82D07190); }

extern u8 D_82D07174[]; extern u8 D_82D0717C[]; extern u8 D_82D07190; void func_82D06334(u8 *arg0) { func_82D06150(arg0, D_82D07174, D_82D0717C, D_82D07190); }

extern u8 D_82D0717C[]; extern u8 D_82D07174[]; extern u8 D_82D07190; void func_82D06368(u8 *arg0) { func_82D06150(arg0, D_82D0717C, D_82D07174, D_82D07190); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D0639C.s")

extern u8 D_82D07194;
typedef struct { s16 field0; u8 pad2[2]; s16 field4; } Fragment82GlobalState;
extern Fragment82GlobalState D_82D07198;
typedef struct { u8 pad0[2]; s16 value2; u8 pad4[2]; s16 value6; u8 pad8[2]; u8 flagsA; u8 valueB; u8 countC; u8 padD[7]; s16 output14; u8 pad16[2]; s16 value18; } Fragment82OffsetState;
void func_82D06488(Fragment82OffsetState *arg0) {
    if (D_82D07194 >= arg0->countC) {
        arg0->flagsA |= 1;
        arg0->output14 = arg0->value2 - ((D_82D07194 - arg0->countC) * 0x2D);
        D_82D07198.field0 = arg0->output14 + arg0->value18;
        if (arg0->countC == 0) {
            D_82D07198.field0 = 0;
            D_82D07198.field4 = 0x280;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D06514.s")

extern void func_82D02B44(s16, s16, u16, u16);
extern void func_82D05BD8(u8 *);
extern void func_82D05D74(u8 *);
extern void func_82D06040(u8 *);
extern u8 D_82D06FB4[];
extern void func_82D05EB4(Fragment82RateState *arg0);
extern void func_82D06488(Fragment82OffsetState *arg0);
void func_82D065C0(u8 *arg0) {
    s32 count;

    switch (arg0[0]) {
    case 2:
        func_82D05D74(arg0);
        break;
    case 3:
        func_82D05EB4((Fragment82RateState *)arg0);
        break;
    case 5:
        func_82D06488((Fragment82OffsetState *)arg0);
        break;
    case 4:
        func_82D06040(arg0);
        break;
    }
    count = arg0[0xC];
    if (count == 0) {
        arg0[0xB] = 0;
        arg0[0xA] &= 0xFFFE;
        return;
    }
    arg0[0xC] = count - 1;
}

void func_82D06670(u8 *arg0)
{
  u8 temp_v0;
  if ((*((u8 *) (((u8 *) arg0) + 0))) == 4)
  {
    func_82D062CC(arg0);
  }
  ;
  if ((*((u8 *) (((u8 *) arg0) + 0xC))) == 0)
  {
    *((s8 *) (((u8 *) arg0) + 0xB)) = 0;
    return;
  }
  *((u8 *) (((u8 *) arg0) + 0xC)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xC))) - 1);
}

void func_82D066BC(u8 *arg0)
{
  u8 temp_v0;
 do { if ((*((u8 *) (((u8 *) arg0) + 0))) == 4) { func_82D06300(arg0); } temp_v0 = *((u8 *) (((u8 *) arg0) + 0xC)); } while (0);
  if (temp_v0 == 0)
  {
    *((s8 *) (((u8 *) arg0) + 0xB)) = 0;
    return;
  }
  *((u8 *) (((u8 *) arg0) + 0xC)) = (u8) (temp_v0 - 1);
}

void func_82D06708(u8 *arg0)
{
  u8 *new_var;
  u8 temp_v0;
  new_var = arg0;
  if (4 == (*((u8 *) (((u8 *) new_var) + 0))))
  {
    func_82D06334(new_var);
  }
  temp_v0 = *((u8 *) (((u8 *) new_var) + 0xC));
  if (!temp_v0)
  {
    *((s8 *) (((u8 *) arg0) + 0xB)) = 0;
    return;
  }
  *((u8 *) (((u8 *) new_var) + 0xC)) = (u8) (temp_v0 + -1);
}

void func_82D06754(u8 *arg0)
{
  u8 temp_v0;
  if ((*((u8 *) (((u8 *) arg0) + 0))) == 4)
  {
    func_82D06368(arg0);
  }
  ;
  if ((*((u8 *) (((u8 *) arg0) + 0xC))) == 0)
  {
    *((s8 *) (((u8 *) arg0) + 0xB)) = 0;
    return;
  }
  *((u8 *) (((u8 *) arg0) + 0xC)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xC))) - 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D067A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D068A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D068F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D0697C.s")

void func_82D06A54(void *arg0, s32 arg1)
{
  if ((*((u8 *) (((u8 *) arg0) + 0))) == 4)
  {
    *((s8 *) (((u8 *) arg0) + 0xC)) = (s8) (D_82D07190 + arg1);
  }
  *((u8 *) (((u8 *) arg0) + 0xA)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xA))) | 2);
  *((s8 *) (((u8 *) arg0) + 0xB)) = 3;
}

void func_82D06A8C(void *arg0, s32 arg1)
{
  if (((unsigned long) (*((u8 *) (((u8 *) arg0) + 0)))) == 4)
  {
    *((s8 *) (((u8 *) arg0) + 0xC)) = (s8) (D_82D07190 + arg1);
  }
  *((u8 *) (((u8 *) arg0) + 0xA)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xA))) | 2);
  *((s8 *) (((u8 *) arg0) + 0xB)) = 4;
}

void func_82D06AC4(void *arg0, s32 arg1)
{
  if ((*((u8 *) (((u8 *) arg0) + 0))) == 4)
  {
    *((s8 *) (((u8 *) arg0) + 0xC)) = (s8) (D_82D07190 + arg1);
  }
  *((u8 *) (((u8 *) arg0) + 0xA)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xA))) | 2);
  *((s8 *) (((u8 *) arg0) + 0xB)) = 5;
}

void func_82D06AFC(void *arg0, s32 arg1)
{
  if ((*((u8 *) (((u8 *) arg0) + 0))) == 4)
  {
    *((s8 *) (((u8 *) arg0) + 0xC)) = (s8) (D_82D07190 + arg1);
  }
  *((u8 *) (((u8 *) arg0) + 0xA)) = (u8) ((*((u8 *) (((u8 *) arg0) + 0xA))) | 2);
  *((s8 *) (((u8 *) arg0) + 0xB)) = 6;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D06B34.s")

extern u8 D_82D06FC4[];
void func_82D06C9C(u8 arg0, s32 arg1) { *(s32 *)(D_82D06FC4 + (arg0 * 0x28)) = arg1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D06CC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_4238F0/func_82D06D50.s")
#endif
