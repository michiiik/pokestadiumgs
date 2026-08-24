#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/208A0/func_8001FCA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/208A0/func_8001FD50.s")

u32 func_8001FFB0(u8 *arg0, u32 arg1) {
    u32 temp_v0;
    u32 var_a2;
    if (*(s8 *)(arg0 + 0x25D1) == 3) {
        temp_v0 = *(u32 *)(arg0 + 0x25CC) - *(s32 *)(arg0 + 0x25C8);
        if (arg1 < temp_v0) var_a2 = arg1;
        else {
            var_a2 = temp_v0;
            if (*(u16 *)(arg0 + 0x2598) <= 0) *(s8 *)(arg0 + 0x25D1) = 4;
        }
        *(s32 *)(arg0 + 0x25C8) += var_a2;
        return var_a2;
    }
    return 0;
}

void func_80020018(u8 *arg0) { if (*(s8 *)(arg0 + 0x25D1) == 2) { arg0[0x25D1] = 3; } }

void func_80020038(u8 *arg0) {
    arg0[0x25D1] = 4;
}
#endif
