#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/63CF0/func_800630F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/63CF0/func_800631B4.s")

extern s32 func_800630F0(s32);
extern s32 func_8004C874(s32, s32);
extern u8 D_80097FD8[];
extern u8 D_800A5090[];
s32 func_80063270(u8 arg0) {
    s32 result;
    if (arg0 < 0x1C) {
        result = func_8004C874(0xC, D_80097FD8[func_800630F0(arg0)]);
        if (result != 0) {
            return result;
        }
    }
    return (s32)D_800A5090;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/63CF0/func_800632CC.s")

extern u8 D_80097E90[];
u8 func_80063454(u8 arg0, u8 arg1, u8 arg2, s32 arg3) {
    u16 result = 10;
    u8 *entry = D_80097E90;
    if (((arg3 == 0) && ((arg0 == 0) || (arg0 == 1))) && ((arg1 == 8) || (arg2 == 8))) {
        if (!arg0) {
        }
        return 0;
    }
    while (entry[0] != 0xFF) {
        if ((arg0 == entry[0]) && ((arg1 == entry[1]) || (arg2 == entry[1]))) {
            result *= entry[2];
            result &= 0xFFFF;
            result /= 10;
        }
        entry += 3;
    }
    return result;
}

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
