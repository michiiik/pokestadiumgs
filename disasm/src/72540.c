#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/72540/func_80071940.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72540/func_80071984.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72540/func_80071A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72540/func_80071AA0.s")

s32 func_80071ADC(s32 arg0, s32 arg1) {
    s32 value;

    if ((arg1 >= 0) && (arg1 < 0xE3)) {
        value = *(s32 *)((u8 *)arg0 + (arg1 * 0xC));
        if (value != 0) {
            return value;
        }
    }
    return 0;
}
#endif
