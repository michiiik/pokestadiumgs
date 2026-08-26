#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_88800020.s")

extern void Util_Free(void *);
extern void main_pool_pop_state(s32);
extern u8 *D_88804050;
void func_888002DC(void) {
    Util_Free(D_88804050);
    main_pool_pop_state(0x504D494E);
}

extern void *D_80087200;
s32 func_8880030C(void)
{
  u16 flags;
  s32 result = 0 * 0;
  if (((*((u16 *) (((u8 *) D_80087200) + 0x8))) & 1) != 0)
  {
    result = 1;
  }
  else
    if (((*((u16 *) (((u8 *) D_80087200) + 0x8))) & 4) != 0)
  {
    result = 2;
  }
  else
    if (((*((u16 *) (((u8 *) D_80087200) + 0x8))) & 2) != 0)
  {
    result = 3;
  }
  return result;
}

void func_88800354(void)
{
  unsigned int temp_a0;
  *((s32 *) (((u8 *) D_88804050) + 0)) = (s32) (*((s32 *) (((u8 *) D_88804050) + 4)));
  *((s8 *) (((u8 *) D_88804050) + 0x11)) = 2;
  *((s32 *) (((u8 *) D_88804050) + 0x14)) = 0;
  temp_a0 = *((s32 *) (((u8 *) D_88804050) + 0));
  if (temp_a0 == 1)
  {
    *((s8 *) (((u8 *) D_88804050) + 0x50)) = (s8) (((s32) (*((u8 *) (((u8 *) D_88804050) + 0x51)))) >> 1);
    return;
  }
  if (temp_a0 == 2)
  {
    Input_SetRepeatController(D_80087200);
  }
}

void func_888003CC(void) {
    *(s32 *)D_88804050 = 0;
    D_88804050[0x11] = 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_888003EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_88800714.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_88800A30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_88800B24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_88800D34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_88800DC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_88800EC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_888010B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_88801138.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_88801554.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/37/fragment37_code/func_88802DCC.s")
#endif
