#include "global.h"


#ifdef VERSION_US
extern s32 D_8009DEC0;

void func_80065D90(s32 arg0) {
    D_8009DEC0 = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/66990/func_80065D9C.s")
#endif
