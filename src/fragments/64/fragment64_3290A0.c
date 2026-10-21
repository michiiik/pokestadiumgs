#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3290A0/func_87F06430.s")

s32 func_87F064DC(s32 arg0, s32 arg1) {
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3290A0/func_87F064EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3290A0/func_87F065B4.s")

/* mkdraft:func_87F06734 begin */
void func_87F06734(s32 a0, u8 *out_base, u8 *src_base)
{
  s32 i = 0;
  const s32 count;
  u8 *new_var;
  const s32 flag_one = 1;
  u8 *out_ptr = out_base;
  u8 *flag_ptr = out_base;
  u8 *src_ptr = src_base;
  while (i != 4)
  {
    s32 idx = func_87F064EC(a0);
    u8 *entry = *((u8 **) ((new_var = src_ptr) + (idx << 2)));
    if ((*((s8 *) entry)) == 0)
    {
      s32 tmp = func_87F065B4(a0, i, (s32) (entry + 4));
      s32 res = func_8004C874(0x44, tmp);
      *((s32 *) (out_ptr + 0x14)) = res;
      *((s8 *) (flag_ptr + 0x24)) = 0;
    }
    else
    {
      *((s32 *) (out_ptr + 0x14)) = (s32) (entry + 0x38);
      *((s8 *) (flag_ptr + 0x24)) = flag_one;
      do
      {
      }
      while (0);
    }
    i++;
    src_ptr += 0x6C0;
    out_ptr += 4;
    flag_ptr += 1;
    if (i)
    {
    }
  }

}
/* mkdraft:func_87F06734 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3290A0/func_87F06804.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3290A0/func_87F0691C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3290A0/func_87F06AA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3290A0/func_87F06D24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3290A0/func_87F06EAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3290A0/func_87F0785C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3290A0/func_87F07FE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_3290A0/func_87F08208.s")
#endif
