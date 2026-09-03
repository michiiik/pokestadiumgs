#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100020.s")
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_8F10008C(s32 arg0, void *arg1) {
    s16 pad;
    s32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &sp28, &sp26, &sp24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(sp26 + 0x2000);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(sp24 - 0x2000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_8F1000F4(s32 arg0, void *arg1) {
    s16 pad;
    s32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &sp28, &sp26, &sp24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(-0x2000 - sp26);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(sp24 + 0x6000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100160.s")
#endif

#ifdef VERSION_US
extern u8 D_8F1DF270[];
s32 func_8F10018C(s32 arg0)
{
  s16 *entry = (s16 *) (D_8F1DF270 + (arg0 * 6));
  s16 value;
  s32 result = 0;
  if (((*entry) == 0) || ((*entry) == 6))
  {
    *entry = 1;
    result = 1;
  }
  return result;
}
#endif

#ifdef VERSION_US
s32 func_8F1001D0(s32 arg0)
{
  s16 *temp_v0;
  s16 temp_a1;
  s32 var_v1;
  temp_v0 = (arg0 * 6) + D_8F1DF270;
  ;
  var_v1 = 0;
  if (((*temp_v0) == 3) || ((*temp_v0) == 4))
  {
    *temp_v0 = 5;
    var_v1 = 1;
  }
  return var_v1;
}
#endif

void func_8F100218(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100220.s")
#endif

#ifdef VERSION_US
extern u8 D_8F1DF274[];
void func_8F100274(s32 arg0) { struct Rec { s16 value[3]; }; ((struct Rec *)D_8F1DF274)[arg0].value[0] = 0; }
#endif

#ifdef VERSION_US
void func_8F100290(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (2))) = (s16) ((*(s16 *)((u8 *)(arg0) + (2))) + 1);
    if ((*(s16 *)((u8 *)(arg0) + (2))) >= 8) {
        (*(s16 *)((u8 *)(arg0) + (0))) = 2;
        (*(s16 *)((u8 *)(arg0) + (2))) = 8;
    }
}
#endif

#ifdef VERSION_US
void func_8F1002C4(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (2))) = (s16) ((*(s16 *)((u8 *)(arg0) + (2))) - 1);
    if ((*(s16 *)((u8 *)(arg0) + (2))) <= 0) {
        (*(s16 *)((u8 *)(arg0) + (0))) = 6;
        (*(s16 *)((u8 *)(arg0) + (2))) = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1002F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1003EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F10049C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100594.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100740.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1008EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100B54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100C64.s")
#endif

#ifdef VERSION_US
extern s32 func_8004B7E0(s32, void *);
extern s32 func_8004B8E4(s32);
typedef struct { f32 x; f32 y; f32 z; } Func8F100D58Vec3f;

void func_8F100D58(s32 arg0, void *arg1) {
    Func8F100D58Vec3f sp1C;

    func_8004B7E0(arg0, &sp1C);
    if (sp1C.y > -150.0f) {
        *(f32 *)((u8 *)arg1 + 4) = (f32)(func_8004B8E4(arg0) * 4);
        return;
    }
    *(f32 *)((u8 *)arg1 + 4) = 0.0f;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100DCC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F100E78.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_8F1040A0[];
extern s32 D_8F1DEE24;
extern void Gfx_DrawTextureRgba16(s16, s16, s16, s16, u8 *, s16, s32);
void func_8F10128C(void) {
    u8 *texture;

    texture = D_8F1040A0 + D_8F1DEE24 * 0xC80;
    gSPDisplayList(D_800D0510++, D_80094E38);
    Gfx_DrawTextureRgba16(0xA0, 0x1E, 0x28, 0x28, texture, 0x28, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F101318.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F101CDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F101DA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F101FF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1020A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102394.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102488.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102618.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102708.s")
#endif

#ifdef VERSION_US
extern void Dma_CopyChunks(s32 *, s32, s32);
s32 func_800356CC(s32);
extern u8 D_8F1DEE68;

void func_8F1027F8(void) {
    s32 temp_v0;

    temp_v0 = func_800356CC(9);
    Dma_CopyChunks(&D_8F1DEE68, temp_v0, temp_v0 + 0x408);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F10282C.s")
#endif

#ifdef VERSION_US
extern void *D_80087200;
extern u8 D_8F1DECA8;
void func_8F1029CC(void) {
    if ((*(u16 *)((u8 *)(D_80087200) + (0xC))) & 0x200) {
        (*(u8 *)((u8 *)(&D_8F1DECA8) + (0x1D))) = (u8) ((*(u8 *)((u8 *)(&D_8F1DECA8) + (0x1D))) - 1);
    }
    if ((*(u16 *)((u8 *)(D_80087200) + (0xC))) & 0x100) {
        (*(u8 *)((u8 *)(&D_8F1DECA8) + (0x1D))) = (u8) ((*(u8 *)((u8 *)(&D_8F1DECA8) + (0x1D))) + 1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102A20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102A98.s")
#endif

#ifdef VERSION_US
void func_8F102B48(void) {
    if ((*(u16 *)((u8 *)(D_80087200) + (0xC))) & 0x200) {
        (*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) = (s8) ((*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) - 1);
        if ((*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) < 0) {
            (*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) = 0;
        }
    }
    if ((*(u16 *)((u8 *)(D_80087200) + (0xC))) & 0x100) {
        (*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) = (s8) ((*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) + 1);
        if ((*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) >= 0x10) {
            (*(s8 *)((u8 *)(&D_8F1DECA8) + (0xA6))) = 0xF;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102BC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102D98.s")
#endif

#ifdef VERSION_US
extern u8 D_8F1DF270[];
extern s32 func_8F100220(s32);
extern void func_8004BE50(void);
s32 func_8F102F58(void) {
    s32 var_v1;

    var_v1 = func_8F100220(1);
    if (var_v1 == 1) {
        func_8004BE50();
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
extern s32 func_8F100220(s32 arg0);
void func_8F102F94(void) {
    func_8F100220(2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F102FB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F103194.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F103478.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1036F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/69/fragment69_code/func_8F1037C4.s")
#endif
