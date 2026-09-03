#include "global.h"


#ifdef VERSION_US
extern s32 D_83F003F0;
void func_83F00020(void) {
    D_83F003F0 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/15/fragment15_code/func_83F0002C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/15/fragment15_code/func_83F0012C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/15/fragment15_code/func_83F001A8.s")

extern void func_83F0002C();
s32 func_83F001A8(s32);
void func_83F00298(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(0xA);
    func_80007AEC(1);
    do {
        func_80064D28();
        func_83F0002C();
        temp_v0 = func_83F001A8(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/15/fragment15_code/func_83F002F4.s")
#endif
