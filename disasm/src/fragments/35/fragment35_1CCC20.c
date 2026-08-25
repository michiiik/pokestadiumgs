#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCC20/func_88600020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCC20/func_88600074.s")

s32 func_886000C8(s32 arg0) {
    s32 *ptr = &arg0;
    s32 temp = *ptr & 0xFFFF;
    if (temp == 0xC9) {
        temp = 1;
    } else {
        temp -= 0xFC;
    }
    return temp & 0xFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCC20/func_886000F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCC20/func_88600170.s")
#endif
