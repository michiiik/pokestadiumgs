#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F500020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F500130.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F5002F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F500414.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F500544.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F500774.s")

extern void func_80007AEC(s32);
extern void func_800086A4(s32);
extern void func_80064D28();
extern void func_8F500414();
s32 func_8F500774(s32);
void func_8F500810(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    func_80007AEC(5);
    do {
        func_80064D28();
        func_8F500414();
        temp_v0 = func_8F500774(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F50086C.s")
#endif
