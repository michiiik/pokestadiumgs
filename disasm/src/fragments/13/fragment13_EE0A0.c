#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE0A0/func_82400020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE0A0/func_82400108.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE0A0/func_82400154.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE0A0/func_824001C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE0A0/func_82400438.s")

void *func_82400520(void *arg0, void *arg1) {
    void *target = *(void **)((u8 *)arg1 + 0x14);
    if (arg0) { }
    *(void **)((u8 *)target + 0xCA8) = arg1;
    return target;
  }
#endif
