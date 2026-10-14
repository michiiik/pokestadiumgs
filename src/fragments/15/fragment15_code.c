#include "global.h"


#ifdef VERSION_US
extern s32 D_83F003F0;
void func_83F00020(void) {
    D_83F003F0 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/15/fragment15_code/func_83F0002C.s")

extern OSTime D_83F00400;

s32 func_83F0012C(void) {
    s32 var_v0;

    var_v0 = 0;
    if ((u32)OS_CYCLES_TO_USEC(osGetTime() - D_83F00400) >= 1000000) {
        var_v0 = 1;
    }
    return var_v0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/15/fragment15_code/func_83F001A8.s")

extern void func_83F0002C();
s32 func_83F001A8(s32);
void func_83F00298(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(0xA);
    StageFade_StartFromOpaque(1);
    do {
        func_80064D28();
        func_83F0002C();
        temp_v0 = func_83F001A8(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/15/fragment15_code/func_83F002F4.s")
#endif
