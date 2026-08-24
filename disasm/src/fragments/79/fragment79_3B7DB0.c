#include "global.h"


#ifdef VERSION_US
u16 func_84148520(u16 arg0, u16 arg1, u8 arg2) {
    s32 result;
    arg1 >>= arg2;
    result = (arg0 < arg1) ? arg0 : arg1;
    return result;
}

u16 func_84148560(u16 arg0, u16 arg1, u8 arg2) {
    s32 result;
    arg0 = arg1 - arg0;
    arg1 >>= arg2;
    result = (arg0 < arg1) ? arg0 : arg1;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B7DB0/func_841485A4.s")
#endif
