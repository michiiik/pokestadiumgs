#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B6E40/func_88305B30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B6E40/func_88305B84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B6E40/func_88305CA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B6E40/func_8830602C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B6E40/func_8830609C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B6E40/func_8830610C.s")

extern void func_8830610C(s16, s16, u16, u16);
extern u8 D_88308E38;
void func_8830639C(void) {
    s32 var_s1;
    u8 *var_s0;

    var_s0 = &D_88308E38;
    var_s1 = 0;
    do {
        if ((*(u8 *)((u8 *)(var_s0) + (4))) != 0) {
            func_8830610C((*(s16 *)((u8 *)(var_s0) + (6))), (*(s16 *)((u8 *)(var_s0) + (8))), (*(u16 *)((u8 *)(var_s0) + (0xA))), (*(u16 *)((u8 *)(var_s0) + (0xC))));
        }
        var_s1 += 1;
        var_s0 += 0x18;
    } while (var_s1 != 4);
}


void func_88306404(s32 arg0) {
    void *temp_v0;

    temp_v0 = (arg0 * 0x18) + &D_88308E38;
    (*(s32 *)((u8 *)(temp_v0) + (0))) = 2;
    (*(s8 *)((u8 *)(temp_v0) + (4))) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B6E40/func_88306430.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B6E40/func_883064C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B6E40/func_883067C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/32/fragment32_1B6E40/func_88306B24.s")
#endif
