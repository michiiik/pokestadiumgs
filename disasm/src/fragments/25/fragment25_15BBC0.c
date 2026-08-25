#include "global.h"


#ifdef VERSION_US
u8 *func_82101B80(u8 *arg0)
{
  return (arg0 + ((*((u32 *) (arg0 + 0x24))) * 8)) + ((0, 4));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82101B94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82101CB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82101D88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82101E70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82101FB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_821020B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82102190.s")

extern void func_82102444(s32, s32);
void func_821023F4(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = arg0;
    do {
        func_82102444(var_s1, var_s0);
        var_s0 += 1;
        var_s1 += 0x2C;
    } while (var_s0 != 3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15BBC0/func_82102444.s")
#endif
