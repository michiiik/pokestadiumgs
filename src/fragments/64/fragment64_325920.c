#include "global.h"


#ifdef VERSION_US
extern void func_87F02CE0(s32 *, s32, s32);
extern u8 D_80126420;

void func_87F02CB0(s32 arg0, s32 arg1) {
    func_87F02CE0(&D_80126420, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_325920/func_87F02CE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_325920/func_87F02F00.s")

void func_87F03204(void *arg0, void *arg1)
{
  u8 temp_v0;
  temp_v0 = *((u8 *) (((u8 *) arg1) + 0xC));
  switch (temp_v0)
  {
    case 0:
      *((f32 *) (((u8 *) arg1) + 0x18)) = 1.0f;
      *((s16 *) (((u8 *) arg1) + 0x1C)) = 0x1FF;
      return;

    case 1:
      *((f32 *) (((u8 *) arg0) + 0x14)) = (f32) (-(*((f32 *) (((u8 *) arg1) + 0))));
      *((s16 *) (((u8 *) arg1) + 0x1C)) = 0x1FF;
      *((f32 *) (((u8 *) arg1) + 0x18)) = 1.0f;
      return;

    case 2:

    case 3:
      *((s16 *) (((u8 *) arg1) + 0x1C)) = 0x2FF;
      *((f32 *) (((u8 *) arg1) + 0x18)) = 1.0f;
      return;

  }

}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_325920/func_87F0328C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_325920/func_87F0339C.s")

extern void func_87F02684();

void func_87F034CC(void) {
    func_87F02684();
}
#endif
