#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/63CF0/func_800630F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/63CF0/func_800631B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/63CF0/func_80063270.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/63CF0/func_800632CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/63CF0/func_80063454.s")

extern u8 D_80097E90[];
u8 func_80063550(u8 arg0, u8 arg1) {
    u8 *entry;
    entry = D_80097E90;
    if (((arg0 == 0) || (arg0 == 1)) && (arg1 == 8)) {
        return 0;
    }
    while (entry[0] != 0xFF) {
        if ((arg0 == entry[0]) && (arg1 == entry[1])) {
            return entry[2];
        }
        entry += 3;
    }
    return 0xA;
}
#endif
