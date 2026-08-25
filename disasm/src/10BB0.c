#include "global.h"


#ifdef VERSION_US
extern f32 D_8011EA8C; f32 func_8000FFB0(f32 arg0) { return 256.0f * D_8011EA8C / arg0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_8000FFCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80010110.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800101D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800102BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80010334.s")

extern void func_80019580(s32); s32 func_800103C8(s32 arg0) { func_80019580(arg0); arg0 += 0x20000000; return arg0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800103F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80010448.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800104A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800104D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80010510.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_8001056C.s")

#define ALIGN16(val) (((val) + 0xFu) & ~0xFu)
typedef struct S1_unk_func_81206FA0 S1_unk_func_81206FA0;
struct S1_unk_func_81206FA0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
};
s32 func_800105B8(S1_unk_func_81206FA0* arg0, s32 arg1) {
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

void func_80010610(u8 *arg0, s32 arg1, s32 arg2) {
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800107CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_8001082C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800108B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80010934.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800109F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80010ABC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80011250.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800124A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012528.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012598.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012630.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_8001291C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012A90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012B80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012BC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012C64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012CA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012DF0.s")

extern s32 D_800D12F0;extern void func_80012F08(s32,s32);void func_80012EAC(s32 arg0){D_800D12F0=0;func_80012F08(0,arg0);}

void func_80012ED8(s32 arg0){D_800D12F0=1;func_80012F08(1,arg0);}

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80012F08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80013174.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_80013210.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/10BB0/func_800137AC.s")
#endif
