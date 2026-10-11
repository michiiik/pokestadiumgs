#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/69F70/func_80069370.s")

s32 func_80069750(s32 arg0) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    if ((*(volatile u32 *)0xA4600010 & 3) == 0) {
        if ((*(volatile u32 *)0xB0000504 & 0xFFFF) != 0xA460) {
            arg0 = -32;
        }
    }
    osSetIntMask(mask);
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/69F70/func_800697B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/69F70/func_80069868.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/69F70/func_80069900.s")
#endif
