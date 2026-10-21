#include "global.h"


#ifdef VERSION_US
s32 func_88100020(void)
{
  unsigned int new_var2;
  s32 temp_v0;
  unsigned int new_var;
  s32 var_s0;
  s32 var_s1;
  var_s1 = 0;
  var_s0 = 0;
  do
  {
    new_var = 1;
    temp_v0 = func_8005D8CC(var_s0);
    new_var2 = 4;
    var_s0 += new_var;
    if ((temp_v0 != new_var) && (temp_v0 != new_var2))
    {
      var_s1 = (var_s1 + new_var) & 0xFF;
    }
  }
  while (var_s0 != 4);
  return var_s1;
}

extern u8 *D_88104E80;
void func_8810009C(s32 arg0, s32 arg1) {
    *(u16 *)(D_88104E80 + 0) = arg0;
    *(u16 *)(D_88104E80 + 2) = arg1;
}

typedef struct unk_func_881000B8 {
    s16 unk_00;
    s16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
} unk_func_881000B8;

void func_881000B8(void) {
    if ((((unk_func_881000B8*)D_88104E80)->unk_00 == 3) &&
        (((unk_func_881000B8*)D_88104E80)->unk_02 == 0)) {
        ((unk_func_881000B8*)D_88104E80)->unk_05 = ((unk_func_881000B8*)D_88104E80)->unk_06;
        ((unk_func_881000B8*)D_88104E80)->unk_06 = 0;
    } else if ((((unk_func_881000B8*)D_88104E80)->unk_00 == 3) &&
               (((unk_func_881000B8*)D_88104E80)->unk_02 == 1)) {
        ((unk_func_881000B8*)D_88104E80)->unk_06 = 0;
    } else {
        ((unk_func_881000B8*)D_88104E80)->unk_04 = 0;
    }
    func_8810009C(3, 2);
}


void func_8810013C(void *arg0, void *arg1, s32 arg2)
{
  f32 temp_fa1;
  f32 temp_fv0;
  f32 temp_fv1;
  u8 *new_var2;
  u8 *new_var;
  f32 var_fa0_2;
  temp_fv0 = ((f32) (6 - (*(((u8 *) D_88104E80) + 7)))) / 6.0f;
  temp_fv1 = ((f32) ((*((u16 *) (((u8 *) arg1) + 4))) - 0x20)) * temp_fv0;
  if (temp_fv1 > 0.0f)
  {
    var_fa0_2 = 0.5f;
  }
  else
  {
    var_fa0_2 = -0.5f;
  }
  *((u16 *) (((u8 *) arg0) + 4)) = (u16) (((s32) (var_fa0_2 + temp_fv1)) + 0x20);
  temp_fa1 = ((f32) ((*((u16 *) (((u8 *) arg1) + 6))) - 0x20)) * temp_fv0;
  if (temp_fa1 > 0.0f)
  {
    var_fa0_2 = 0.5f;
  }
  else
  {
    var_fa0_2 = -0.5f;
  }
  temp_fv0 = var_fa0_2;
  new_var = ((u8 *) arg0) + 6;
  *((u16 *) new_var) = (u16) (((s32) (temp_fv0 + temp_fa1)) + 0x20);
  new_var2 = (u8 *) arg0;
  *((s16 *) (((u8 *) arg0) + 0)) = (s16) (((*((s16 *) (((u8 *) arg1) + 0))) + (((s32) (*((u16 *) (((u8 *) arg1) + 4)))) >> 1)) - (((s32) (*((u16 *) (new_var2 + 4)))) >> 1));
  *((s16 *) (((u8 *) arg0) + 2)) = (s16) (((*((s16 *) (((u8 *) arg1) + 2))) + (((s32) (*((u16 *) (((u8 *) arg1) + 6)))) >> 1)) - (((s32) (*((u16 *) new_var))) >> 1));
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_88100264.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_88100C80.s")

extern s32 func_8004D1FC(u8 *);
extern s32 func_8004D27C(u8 *, s32, s32);
extern void func_80044270(s16, s16, s16, s16, s16, s16, s16, s16, s32);
extern Gfx *D_800D0510;

void func_8810106C(u8 *arg0, u8 *arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7,
                   u8 arg8, u8 arg9, u8 arg10) {
    func_8004D1FC(arg0);
    func_8004D27C(arg1, 256, 1);
    gDPPipeSync(D_800D0510++);
    gDPSetPrimColor(D_800D0510++, 0, 0, arg4, arg5, arg6, arg7);
    gDPSetEnvColor(D_800D0510++, arg8, arg9, arg10, 255);
    func_80044270(arg2, arg3, *(s16 *)arg0, *(s16 *)(arg0 + 2), -16, -16, 1024, 1024, G_CYC_2CYCLE);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_88101184.s")

extern s32 D_880068B8;
extern s32 func_8004C990(s32, s32);
extern void func_88101184(s32, s32, s32, f32);
void func_881014E4(f32 arg0) {
    if (D_880068B8 != 0) {
        if (*(u8 *)(D_88104E80 + 4) != 0) {
            func_88101184(0x1A2, 0x24, func_8004C990(0xA3, 1), arg0);
        }
        if (*(u8 *)(D_88104E80 + 5) != 0) {
            func_88101184(0x1F5, 0x24, func_8004C990(0xA3, 0), arg0);
        }
    }
    if (*(u8 *)(D_88104E80 + 6) != 0) {
        func_88101184(0x1F5, 0x74, func_8004C990(0xA3, 0), arg0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_881015A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_8810179C.s")

/* mkdraft:func_88102234 begin */
extern s32 func_80001FF0(void);
extern void StageContext_SetClearColor(u16);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_8810179C(s32);
extern f32 D_88104E68;

void func_88102234(void) {
    s32 count;
    s32 i;

    count = (u32) (((f32)func_80001FF0() * D_88104E68) / 2) & 0xFFFF;
    StageContext_SetClearColor(1);
    StageFade_StartFromOpaque(count);
    i = 0;
    if (count != 0) {
        do {
            func_80064D28();
            func_8810179C(0);
            i += 1;
        } while (i != count);
    }
}
/* mkdraft:func_88102234 end */

extern void func_800226C0(s32);
extern void func_880040D4();
extern void func_88100264();
extern void func_8810179C(s32);
extern s32 D_88006860;
extern s8 D_8800EF40;
void func_88102338(void) {
    func_800226C0(4);
    if (D_88006860 == 7) {
        do {
            if (D_8800EF40 == -1) {
                func_80064D28();
            }
            func_88100264();
            func_880040D4();
            func_8810179C(1);
        } while (D_88006860 == 7);
    }
}

/* mkdraft:func_881023CC begin */
extern s32 func_80001FF0(void);
extern void func_80035424(s32);
extern void StageContext_SetClearColor(u16);
extern void StageFade_StartFromTransparent(s32);
extern void func_80064D28(void);
extern void func_8810179C(s32);
extern f32 D_88104E6C;



void func_881023CC(void) {
    s32 count;
    s32 i;

    count = (u32) (((f32)func_80001FF0() * D_88104E6C) / 2) & 0xFFFF;
    if (D_88006860 == 8) {
        func_80035424(count);
        StageContext_SetClearColor(0xFFFF);
    }
    *(s32 *)(D_88104E80 + 0x18) = 1;
    StageFade_StartFromTransparent(count);
    i = 0;
    if (count != 0) {
        do {
            func_80064D28();
            func_8810179C(2);
            i += 1;
        } while (i != count);
    }
}
/* mkdraft:func_881023CC end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_881024F8.s")

#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

M2C_UNK Gfx_FreeDisplayListBuffers();               /* extern */
M2C_UNK Gfx_InitDisplayListBuffers(M2C_UNK, M2C_UNK); /* extern */
M2C_UNK Util_Free(u8 *);                            /* extern */
s32 func_800082E0(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_80008514(s32);                         /* extern */
M2C_UNK func_80008574();                            /* extern */
s32 func_80047588(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_80047610();                            /* extern */
M2C_UNK func_8004C09C(M2C_UNK);                     /* extern */
M2C_UNK func_8004C398();                            /* extern */
void func_881023CC(void);                            /* extern */
M2C_UNK func_881024F8(s32);                         /* extern */
M2C_UNK main_pool_pop_state(M2C_UNK);               /* extern */
M2C_UNK main_pool_push_state(M2C_UNK);              /* extern */
extern s32 D_8800687C;

s32 func_88102E78(s32 arg0, M2C_UNK arg1) {
    s32 sp24;

    main_pool_push_state(0x4C41424F);
    Gfx_InitDisplayListBuffers(0x14000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(7);
    D_8800687C = func_80047588(0xC, 0);
    func_881024F8(arg0);
    func_80008514(sp24);
    func_88102234();
    func_88102338();
    func_881023CC();
    func_80008574();
    Util_Free(D_88104E80);
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4C41424F);
    return D_88006860;
}
#endif
