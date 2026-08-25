#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_88203670.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_88203744.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_8820390C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_88203A18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_88203A58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_88203BE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_88203ED8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_88203FB4.s")

extern u8 D_88A01C40;

s32 func_88204050(void) {
    s32 var_v1;
    u8 *var_v0;

    var_v0 = &D_88A01C40;
    var_v1 = 0;
loop_1:
    if (*var_v0 != 0) {
        var_v1 += 1;
        var_v0 += 1;
        if (var_v1 != 0x1E) {
            goto loop_1;
        }
    }
    return var_v1 & 0xFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_88204080.s")
#endif
