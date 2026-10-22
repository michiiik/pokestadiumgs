#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0A340.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0A3A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0A4AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0A6E4.s")

extern void Ui_DrawGradientQuad(s32, s32, u16, u16, s32 *, s32 *);
extern u8 D_8AF26450;
extern u8 D_8AF26454;
s32 func_8AF0A800(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0x20)));
    Ui_DrawGradientQuad(0, 0, (*(u16 *)((u8 *)(temp_v0) + (4))), (*(u16 *)((u8 *)(temp_v0) + (6))), &D_8AF26450, &D_8AF26454);
    return 0;
}

extern void func_800504BC(s16 *arg0);
s32 func_8AF0A850(s32 arg0, void *arg1) {
    struct { s32 pad[2]; s16 angles[2]; } scratch;
    if ((arg0 != 0) && (arg0 == 1)) {
        func_800504BC(scratch.angles);
    }
    return 0;
}

s32 func_8004C990(s32, s32);
extern s32 D_8AF2D428;
extern s32 D_8AF2D42C;
extern s32 D_8AF2D430;
extern s32 D_8AF2D434;
extern s32 D_8AF2D438;

void func_8AF0A888(void) {
    D_8AF2D428 = func_8004C990(0xAD, 0);
    D_8AF2D42C = func_8004C990(0xAD, 1);
    D_8AF2D430 = func_8004C990(0xAD, 2);
    D_8AF2D434 = func_8004C990(0xAD, 3);
    D_8AF2D438 = func_8004C990(0xAD, 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0A900.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0AAF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0AB84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0ACDC.s")

s32 func_8AC006F4();
s32 func_8AC007FC();
s32 func_8AC063AC(s32 *, u16, s16);
s32 func_8AF00130(s32);
extern void *D_8AF263C0;
extern s32 D_8AF2694C;
extern s16 D_8AF2BAC8;
extern u16 D_8AF2BDC6;
extern s16 D_8AF2D300;
extern s16 D_8AF2D304;
extern void *D_8AF2D3C4;
extern void *D_8AF2D3C8;
extern s32 D_8AF2D490;
extern s16 D_8AF2D508;

s16 func_8AF0B544(void)
{
  s16 var_a2;
  u16 temp_v0;
  func_8AC007FC();
  var_a2 = 0xA;
  if (D_8AF2D508 >= 5)
  {
    D_8AF2D508 = 4;
    temp_v0 = *((u16 *) (((u8 *) D_8AF263C0) + 8));
    if (temp_v0 & 0x8000)
    {
      switch (D_8AF2D304)
      {
        case 0:
          func_8AF00130(0xC2);
          var_a2 = 0xC;
          D_8AF2694C = 0;
          break;

        case 1:
          func_8AF00130(0xC2);
          var_a2 = 0xB;
          D_8AF2694C = 0;
          break;

      }

    }
    else
      if (temp_v0 & 0x4000)
    {
      func_8AF00130(3);
      func_8AC006F4();
      var_a2 = D_8AF2D300;
      D_8AF2694C = 0;
    }
    else
      if (temp_v0 & 0x100)
    {
      if (D_8AF2D304 != 0)
      {
        var_a2 = 0xA;
        func_8AF00130(1);
        var_a2 = 0xA;
      }
      D_8AF2D304 = 0;
    }
    else
      if (temp_v0 & 0x200)
    {
      if (D_8AF2D304 != 1)
      {
        var_a2 = 0xA;
        func_8AF00130(1);
        var_a2 = 0xA;
      }
      D_8AF2D304 = 1;
    }
  }
  if (var_a2 != 0xA)
  {
    D_8AF2BAC8 = 0;
  }
  if (D_8AF2D304 == 1)
  {
    *((u16 *) (((u8 *) D_8AF2D3C4) + 2)) = (u16) ((*((u16 *) (((u8 *) D_8AF2D3C4) + 2))) | 1);
    *((u16 *) (((u8 *) D_8AF2D3C8) + 2)) = (u16) ((*((u16 *) (((u8 *) D_8AF2D3C8) + 2))) & 0xFFFE);
  }
  else
  {
    *((u16 *) (((u8 *) D_8AF2D3C4) + 2)) = (u16) ((*((u16 *) (((u8 *) D_8AF2D3C4) + 2))) & 0xFFFE);
    *((u16 *) (((u8 *) D_8AF2D3C8) + 2)) = (u16) ((*((u16 *) (((u8 *) D_8AF2D3C8) + 2))) | 1);
  }
  var_a2 = var_a2;
  func_8AC063AC(&D_8AF2D490, D_8AF2BDC6, var_a2);
  D_8AF2D508 += 1;
  return var_a2;
}

extern s32 D_8AF2694C;
extern Gfx *D_800D0510;

void func_8AF0B724(s32 arg0, s32 arg1) {
    gSPTextureRectangle(D_800D0510++, arg0 << 2, arg1 << 2,
                        (arg0 + 20) << 2, (arg1 + 20) << 2,
                        G_TX_RENDERTILE, 0, 0, 1024, 1024);
}

void func_8AF0B724(s32 arg0, s32 arg1);
s32 func_8AF0AB84(s32);
extern s16 D_8AF2D3D8;

void func_8AF0B7BC(s16 arg0)
{
  int new_var;
  s16 *var_s1;
  s32 var_s0;
  func_8AF0AB84(arg0 & 0xFF);
  var_s1 = &D_8AF2D3D8;
  var_s0 = 0;
  do
  {
    if (arg0 == (*var_s1))
    {
      func_8AF0B724((var_s0 * 0x14) + 0xC8, 0x170 & 0xFFFF);
    }
    new_var = 2;
    new_var = 1;
    var_s0 += new_var;
    var_s1 += new_var;
  }
  while (var_s0 != 0x11);
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F85B0/func_8AF0B850.s")

extern void func_80043E70(s32, s32);
extern s32 D_8AF2694C;

void func_8AF0BB04(void) {
    if (D_8AF2694C != 0) {
        func_80043E70(D_8AF2694C, 0);
    }
}
#endif
