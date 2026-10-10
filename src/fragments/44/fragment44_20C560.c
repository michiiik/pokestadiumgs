#include "global.h"


#ifdef VERSION_US
s32 func_8AF1E2F0(u8 arg0, u8 arg1) {
    s32 nibble = arg1 & 0xF;
    if ((nibble == (arg0 & 0xF)) || (nibble == ((arg0 & 0xF0) >> 4))) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20C560/func_8AF1E32C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20C560/func_8AF1E45C.s")
#endif

void func_8AF1E4B0(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20C560/func_8AF1E4B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20C560/func_8AF1E54C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20C560/func_8AF1E840.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20C560/func_8AF1E8E4.s")
#endif
