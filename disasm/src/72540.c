#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/72540/func_80071940.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72540/func_80071984.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72540/func_80071A40.s")

s32 func_80071AA0(s32 arg0, s32 arg1)
{
  s32 temp_v1;
  int new_var2;
  s32 *new_var;
  if ((arg1 >= 0) && (arg1 < 0xE3))
  {
    temp_v1 = arg1 * 0xC;
    new_var = (s32 *) (((u8 *) (arg0 + temp_v1)) + 4);
    temp_v1 = *new_var;
    new_var2 = temp_v1 != 0;
    if (new_var2)
    {
      return temp_v1;
    }
  }
  return 0;
}

s32 func_80071ADC(s32 arg0, s32 arg1) {
    s32 value;

    if ((arg1 >= 0) && (arg1 < 0xE3)) {
        value = *(s32 *)((u8 *)arg0 + (arg1 * 0xC));
        if (value != 0) {
            return value;
        }
    }
    return 0;
}
#endif
