#include "global.h"


#ifdef VERSION_US
void func_87F0DBE0(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x0) = 0;
    *(s32 *)(arg0 + 0x4) = arg1;
    arg0[0x10] = 0;
    arg0[0x12] &= 0xFF7F;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_330850/func_87F0DBFC.s")

void func_87F0DC3C(u8 *arg0) { arg0[0x12] &= 0xFF7F; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_330850/func_87F0DC4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_330850/func_87F0DFB4.s")
#endif
