#include "global.h"


#ifdef VERSION_US
extern void func_8AF00504(s32);
void func_8AF07160(void) { func_8AF00504(27); }

extern void *D_8AF263C0;

s32 func_8AF07180(void) {
    s32 var_v1;

    var_v1 = 2;
    if ((*(u16 *)((u8 *)(D_8AF263C0) + (8))) & 0x4000) {
        var_v1 = 1;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F53D0/func_8AF071A8.s")
#endif
