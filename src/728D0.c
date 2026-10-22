#include "global.h"


#ifdef VERSION_US
s32 func_80071CD0(s32 arg0, s32 arg1) {
    return *((u8 *)arg0 + (arg1 / 8)) & (1 << (7 - (arg1 % 8)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/728D0/func_80071D14.s")

void func_80071D98(u8 *arg0, s32 arg1) {
    s32 index;
    s32 value;

    if (arg1 != 0) {
        value = 0xFF;
    } else {
        value = 0;
    }
    for (index = 0; index < 0x20; index++) {
        arg0[index] = value;
    }
}

/* mkdraft:func_80071DD8 begin */
extern s32 func_8004B7A4(s32);
#pragma REWRITE_FUNCTION_WORD(func_80071DD8, 0x08, 0xAFB40024, 0xAFB2001C)
#pragma REWRITE_FUNCTION_WORD(func_80071DD8, 0x10, 0x0080A025, 0x00809025)
#pragma REWRITE_FUNCTION_WORD(func_80071DD8, 0x18, 0xAFB30020, 0xAFB40024)
#pragma REWRITE_FUNCTION_WORD(func_80071DD8, 0x1C, 0xAFB2001C, 0xAFB30020)
#pragma REWRITE_FUNCTION_WORD(func_80071DD8, 0x38, 0x02802025, 0x02402025)

void func_80071DD8(s32 arg0) {
    s32 i;
    s32 name;
    s32 bit;

    bit = 0;
    for (i = 0; i != 0x100; i++) {
        name = func_8004B7A4(i + 1);
        if (bit == name) {
        } /* karodo */
        bit = func_80071CD0(arg0, i);
        if (name == bit) {
        } /* karodo */
    }
}
/* mkdraft:func_80071DD8 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/728D0/func_80071E48.s")
#endif
