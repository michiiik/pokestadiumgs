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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_881000B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_8810013C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_88100264.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_88100C80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_8810106C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_88101184.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_881014E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_881015A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_8810179C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_88102234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_88102338.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_881023CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_881024F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_16D4F0/func_88102E78.s")
#endif
