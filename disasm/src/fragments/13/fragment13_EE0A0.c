#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE0A0/func_82400020.s")

extern void func_8003F018(s32);
void func_82400108(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = arg0;
    do {
        func_8003F018(var_s1);
        var_s0 += 0x168;
        var_s1 += 0x168;
    } while (var_s0 != 0xB40);
}

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
