#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_31BD80/func_87E18410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_31BD80/func_87E18504.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_31BD80/func_87E18738.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_31BD80/func_87E18828.s")

extern void func_87E01628();
extern void main_pool_pop_state(s32);

void func_87E189E8(s32 arg0) {
    func_87E01628();
    main_pool_pop_state(0x4D51414C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_31BD80/func_87E18A14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_31BD80/func_87E18B0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_31BD80/func_87E18D20.s")

s32 func_87E18ECC(void *arg0)
{
  u8 *new_var;
  s32 var_v1;
  void *var_v0;
  var_v0 = *((void **) (((u8 *) arg0) + 0x18));
  var_v1 = 1;
  if (var_v0 != 0)
  {
    do
    {
      new_var = (u8 *) (*((void **) (((u8 *) (*((void **) (((u8 *) var_v0) + 0x38)))) + 0xC)));
      if ((*((s32 *) (new_var + 0x8C))) != 0)
      {
        var_v1 = 0;
      }
      var_v0 = *((void **) (((u8 *) var_v0) + 4));
    }
    while (var_v0 != 0);
  }
  return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_31BD80/func_87E18F08.s")

extern void func_87F0AF4C(s32);
void func_87E1918C(s32 arg0) {
    func_87F0AF4C(arg0 + 12);
}
#endif
