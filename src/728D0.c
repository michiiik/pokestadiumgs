#include "global.h"


#ifdef VERSION_US
s32 func_80071CD0(s32 arg0, s32 arg1) {
    return *((u8 *)arg0 + (arg1 / 8)) & (1 << (7 - (arg1 % 8)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/728D0/func_80071D14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/728D0/func_80071D98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/728D0/func_80071DD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/728D0/func_80071E48.s")
#endif
