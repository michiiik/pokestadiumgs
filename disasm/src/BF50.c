#include "global.h"


#ifdef VERSION_US
extern s16 D_8008CE50[0x401];
u16 func_8000B350(f32 y, f32 x) {
    u16 ret;

    if (x == 0) {
        ret = D_8008CE50[0];
    } else {
        ret = D_8008CE50[(s32)(y / x * 1024 + 0.5f)];
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/BF50/func_8000B3B0.s")

s32 func_8000B524(void) { return guRandom() & 0xFFFF; }

f32 func_8000B548(void) { return (f32)func_8000B524() / 65536.0f; }
#endif
