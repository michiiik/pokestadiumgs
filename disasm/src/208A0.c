#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/208A0/func_8001FCA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/208A0/func_8001FD50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/208A0/func_8001FFB0.s")

void func_80020018(u8 *arg0) { if (*(s8 *)(arg0 + 0x25D1) == 2) { arg0[0x25D1] = 3; } }

void func_80020038(u8 *arg0) {
    arg0[0x25D1] = 4;
}
#endif
