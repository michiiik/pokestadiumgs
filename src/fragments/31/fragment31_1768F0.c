#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_88203670.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_88203744.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1768F0/func_8820390C.s")

/* mkdraft:func_88203A18 begin */
#pragma REWRITE_FUNCTION_WORD(func_88203A18, 0x00, 0x90A60001, 0x90A20001)
#pragma REWRITE_FUNCTION_WORD(func_88203A18, 0x08, 0x50C0000B, 0x5040000B)
#pragma REWRITE_FUNCTION_WORD(func_88203A18, 0x10, 0x8CA20004, 0x8CA60004)
#pragma REWRITE_FUNCTION_WORD(func_88203A18, 0x14, 0x54820004, 0x54860004)
#pragma REWRITE_FUNCTION_WORD(func_88203A18, 0x28, 0x0066082B, 0x0062082B)
#pragma REWRITE_FUNCTION_WORD(func_88203A18, 0x30, 0x24420076, 0x24C60076)

s32 func_88203A18(s32 arg0, void *arg1) {
    u32 var_v1;
    u8 temp_v0;
    s32 var_a2;

    temp_v0 = *(u8 *)((u8 *)arg1 + 1);
    var_v1 = 0;
    if (temp_v0 != 0) {
        var_a2 = *(s32 *)((u8 *)arg1 + 4);
        do {
            if (arg0 == var_a2) {
                return var_v1 & 0xFF;
            }
            var_v1 += 1;
            var_a2 += 0x76;
        } while (var_v1 < temp_v0);
    }
    return var_v1 & 0xFF;
}
/* mkdraft:func_88203A18 end */

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
