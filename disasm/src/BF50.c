#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/BF50/func_8000B350.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/BF50/func_8000B3B0.s")

s32 func_8000B524(void) { return guRandom() & 0xFFFF; }

f32 func_8000B548(void) { return (f32)func_8000B524() / 65536.0f; }
#endif
