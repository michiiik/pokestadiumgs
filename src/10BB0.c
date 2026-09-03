#include "global.h"


#ifdef VERSION_US
extern f32 D_8011EA8C; f32 func_8000FFB0(f32 arg0) { return 256.0f * D_8011EA8C / arg0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_8000FFCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80010110.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800101D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800102BC.s")

extern u8 D_8011BE90[];
extern void func_8001CA3C(s32);
void func_80010334(s32 arg0)
{
  s32 index;
  index = 0;
  if ((*((s16 *) (D_8011BE90 + 0x2BF0))) > 0)
  {
    do
    {
      if (((((u32) (*((s32 *) (D_8011BE90 + (index * 0x160) + 0x346C)))) >> 31) != 0) && (arg0 == *((u8 *) (D_8011BE90 + (index * 0x160) + 0x3470))))
      {
        func_8001CA3C(*((s32 *) ((D_8011BE90 + (index * 4)) + 0x604C)));
      }
      index++;
    }
    while (index < (*((s16 *) (D_8011BE90 + 0x2BF0))));
  }
}

extern void func_80019580(s32); s32 func_800103C8(s32 arg0) { func_80019580(arg0); arg0 += 0x20000000; return arg0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800103F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80010448.s")

s32 GbApu_Alloc();
s32 func_80010510();
s32 func_800104A0(void *arg0, s32 arg1) {
    s32 func_800103C8();
    s32 result = GbApu_Alloc(arg0, arg1);
    if (result != 0) {
        result = func_800103C8(result, arg1);
    }
    return result;
}

s32 func_800104D8(void *arg0, s32 arg1) {
    s32 func_800103C8();
    s32 result = func_80010510(arg0, arg1);
    if (result != 0) {
        result = func_800103C8(result, arg1);
    }
    return result;
}

s32 func_80010510(u8 *arg0, s32 arg1) {
    s32 temp_v0;
    u8 *var_v1;
    temp_v0 = GbApu_Alloc(arg0, arg1);
    if (temp_v0 != 0) {
        var_v1 = (u8 *)temp_v0;
        if ((u32)temp_v0 < *(u32 *)(arg0 + 4)) {
            do {
                *var_v1 = 0;
                var_v1 += 1;
            } while ((u32)var_v1 < *(u32 *)(arg0 + 4));
        }
    }
    return temp_v0;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} T_1056C_A;
s32 func_8001056C(T_1056C_A *arg0, s32 arg1) {
    s32 saved;
    s32 result;
    saved = arg0->unk4;
    result = GbApu_Alloc(arg0, arg1);
    if (result != 0) {
        arg0->unk4 = saved;
        arg0->unkC -= 1;
    }
    return result;
}

#define ALIGN16(val) (((val) + 0xFu) & ~0xFu)
typedef struct S1_unk_func_81206FA0 S1_unk_func_81206FA0;
struct S1_unk_func_81206FA0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
};
s32 GbApu_Alloc(S1_unk_func_81206FA0* arg0, s32 arg1) {
  s32 temp_a2;
  u32 temp_v0;

  temp_v0 = ALIGN16(arg1);
  temp_a2 = arg0->unk_04;
  if ((arg0->unk_00 + arg0->unk_08) >= (arg0->unk_04 + temp_v0)) {
      arg0->unk_04 = temp_v0 + temp_a2;
  } else {
      return 0;
  }
  arg0->unk_0C++;
  return temp_a2;
}

void GbApu_InitAllocator(u8 *arg0, s32 arg1, s32 arg2) {
    s32 aligned = (arg1 + 0xF) & ~0xF;
    *(s32 *)(arg0 + 0) = aligned;
    *(s32 *)(arg0 + 4) = aligned;
    *(s32 *)(arg0 + 8) = arg2 - (arg1 & 0xF);
    *(s32 *)(arg0 + 0xC) = 0;
}

void func_80010638(u8 *arg0) { *(s32 *)(arg0 + 0x10) = 0; *(s32 *)arg0 = 0; *(s32 *)(arg0 + 8) = *(s32 *)(arg0 + 4); }

void func_8001064C(void *arg0)
{
  u8 *p = arg0;
  s32 value = *((s32 *) (p + 4));
  *((s32 *) (p + 0x10)) = 0;
  *((s32 *) (p + 0x00)) = 0;
  *((s32 *) (p + 0x20)) = value;
  *((s32 *) (p + 0x20)) += *((s32 *) (p + 0x0C));
  *((s16 *) (p + 0x1E)) = -1;
  *((s16 *) (p + 0x2A)) = -1;
  *((s32 *) (p + 0x08)) = value;
  *((s32 *) (p + 0x14)) = value;
}

void func_8001067C(u8 *arg0) { *(s32 *)(arg0 + 0xC) = 0; *(s32 *)(arg0 + 4) = *(s32 *)arg0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_8001068C.s")

extern u8 D_8011EBC0;
extern u8 D_8011EBE0;
extern s32 D_8011F2F0;
extern u8 D_8011BE90[];
extern s32 D_8011EBD0;

void func_800107CC(s32 arg0) {
    GbApu_InitAllocator(&D_8011EBE0, D_8011F2F0, arg0);
    GbApu_InitAllocator(&D_8011EBC0, (*(s32 *)((u8 *)(D_8011BE90) + (0x3460))) + arg0, (*(s32 *)((u8 *)(D_8011BE90) + (0x3464))) - arg0);
    D_8011EBD0 = 0;
}

extern u8 D_8011EBF0;
extern S1_unk_func_81206FA0 D_8011EC20;
u8 *func_80012630();
u8 *func_80012BC4();
void func_8001082C(void *arg0) {
    *(s32 *)(D_8011BE90 + 0x2D34) = *(s32 *)(D_8011BE90 + 0x2D30);
    GbApu_InitAllocator(&D_8011EBF0, GbApu_Alloc(&D_8011EBC0, *(s32 *)((u8 *)arg0 + 0)), *(s32 *)((u8 *)arg0 + 0));
    GbApu_InitAllocator((u8 *)&D_8011EC20, GbApu_Alloc(&D_8011EBC0, *(s32 *)((u8 *)arg0 + 0xC)), *(s32 *)((u8 *)arg0 + 0xC));
}

extern u8 D_8011EC30;
extern u8 D_8011EC40;
void func_800108B0(void *arg0) {
    (*(s32 *)((u8 *)(D_8011BE90) + (0x2D94))) = (s32) (*(s32 *)((u8 *)(D_8011BE90) + (0x2D90)));
    GbApu_InitAllocator(&D_8011EC30, GbApu_Alloc(&D_8011EC20, (*(s32 *)((u8 *)(arg0) + (0)))), (*(s32 *)((u8 *)(arg0) + (0))));
    GbApu_InitAllocator(&D_8011EC40, GbApu_Alloc(&D_8011EC20, (*(s32 *)((u8 *)(arg0) + (4)))), (*(s32 *)((u8 *)(arg0) + (4))));
}

extern u8 D_8011EC50;
extern u8 D_8011EC54;
extern u8 D_8011ED60;
extern u8 D_8011ED64;
extern u8 D_8011EE70;
extern u8 D_8011EE74;
extern u8 D_8011ED24;
extern u8 D_8011ED28;
extern u8 D_8011EE34;
extern u8 D_8011EE38;
extern u8 D_8011EF44;
extern u8 D_8011EF48;
void func_80010934(void *arg0) {
    *(s32 *)(D_8011BE90 + 0x2DA4) = *(s32 *)(D_8011BE90 + 0x2DA0);
    GbApu_InitAllocator(&D_8011EC54, GbApu_Alloc(&D_8011EC30, *(s32 *)((u8 *)arg0 + 0)), *(s32 *)((u8 *)arg0 + 0));
    GbApu_InitAllocator(&D_8011ED64, GbApu_Alloc(&D_8011EC30, *(s32 *)((u8 *)arg0 + 4)), *(s32 *)((u8 *)arg0 + 4));
    GbApu_InitAllocator(&D_8011EE74, GbApu_Alloc(&D_8011EC30, *(s32 *)((u8 *)arg0 + 8)), *(s32 *)((u8 *)arg0 + 8));
    func_80010638(&D_8011EC50);
    func_80010638(&D_8011ED60);
    func_80010638(&D_8011EE70);
}

void func_800109F8(void *arg0) {
    *(s32 *)(D_8011BE90 + 0x2DB4) = *(s32 *)(D_8011BE90 + 0x2DB0);
    GbApu_InitAllocator(&D_8011ED28, GbApu_Alloc(&D_8011EC40, *(s32 *)((u8 *)arg0 + 0)), *(s32 *)((u8 *)arg0 + 0));
    GbApu_InitAllocator(&D_8011EE38, GbApu_Alloc(&D_8011EC40, *(s32 *)((u8 *)arg0 + 4)), *(s32 *)((u8 *)arg0 + 4));
    GbApu_InitAllocator(&D_8011EF48, GbApu_Alloc(&D_8011EC40, *(s32 *)((u8 *)arg0 + 8)), *(s32 *)((u8 *)arg0 + 8));
    func_8001064C(&D_8011ED24);
    func_8001064C(&D_8011EE34);
    func_8001064C(&D_8011EF44);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80010ABC.s")

s32 func_800112A8();
s32 func_8001244C();
void func_8001291C();
s32 func_80011250(s32 arg0, s32 arg1, s32 arg2) {
    s32 result = func_8001244C(arg0, arg2);
    if (result != 0) {
        return result;
    }
    if (arg1 == 3) {
        return 0;
    }
    return func_800112A8(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800112A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800113B4.s")

void func_80011788(void *arg0) { s32 var_v0 = 0; u8 *var_v1 = (u8 *)arg0; do { var_v0 += 4; *(s16 *)(var_v1 + 2) = 0; *(s16 *)(var_v1 + 4) = 0; *(s16 *)(var_v1 + 6) = 0; var_v1 += 8; *(s16 *)(var_v1 - 8) = 0; } while (var_v0 != 8); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800117B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_8001180C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80011864.s")

void func_80011A40(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80011A48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80011B0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80011B78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80011E7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_8001244C.s")

extern S1_unk_func_81206FA0 D_8011EF80;
extern s32 D_8011EF8C;
s32 func_800124A4(s32 arg0, s32 arg1, s32 arg2)
{
  s32 locals[2];
  s32 result;
  locals[0] = D_8011EF8C;
  result = GbApu_Alloc(&D_8011EF80, arg2);
  *((s32 *) ((D_8011BE90 + (locals[0] * 0xC)) + 0x3100)) = result;
  if (result == 0)
  {
    return 0;
    return result;
  }
  *((s16 *) ((D_8011BE90 + (locals[0] * 0xC)) + 0x3108)) = arg0;
  *((s16 *) ((D_8011BE90 + (locals[0] * 0xC)) + 0x310A)) = arg1;
  *((s32 *) ((D_8011BE90 + (locals[0] * 0xC)) + 0x3104)) = arg2;
}

s32 func_80012528(s32 arg0, s32 arg1, s32 arg2, s8 arg3, s32 arg4) {
    u8 *result;
    if (arg4 == 0) {
        result = func_80012630(arg0);
    } else {
        result = func_80012BC4(arg0);
    }
    if (result != NULL) {
        result[2] = arg1;
        *(s32 *)(result + 0xC) = arg2;
        result[1] = arg3;
        return *(s32 *)(result + 8);
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012598.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012630.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_8001291C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012A90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012B80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012BC4.s")

void func_80012C64(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 value = arg0[2];
    if ((arg1 == value) || (arg2 == value) || (value == 0)) {
        func_8001291C(arg0, arg3);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012CA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012DF0.s")

extern s32 D_800D12F0;extern void func_80012F08(s32,s32);void func_80012EAC(s32 arg0){D_800D12F0=0;func_80012F08(0,arg0);}

void func_80012ED8(s32 arg0){D_800D12F0=1;func_80012F08(1,arg0);}

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012F08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80013174.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80013210.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800137AC.s")
#endif
