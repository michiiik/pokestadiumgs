#include "global.h"


#ifdef VERSION_US
const u32 D_800A5090[1] = { 0 };

s32 Type_IdToChartIndex(u8 arg0) {
    switch (arg0) {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        case 5:
            return 5;
        case 7:
            return 6;
        case 8:
            return 7;
        case 9:
            return 8;
        case 19:
            return 9;
        case 20:
            return 10;
        case 21:
            return 11;
        case 22:
            return 12;
        case 23:
            return 13;
        case 24:
            return 14;
        case 25:
            return 15;
        case 26:
            return 16;
        case 27:
            return 17;
    }
    return 0x12;
}
s32 Type_ChartIndexToId(s32 arg0) {
    switch (arg0) {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        case 5:
            return 5;
        case 6:
            return 7;
        case 7:
            return 8;
        case 8:
            return 9;
        case 9:
            return 19;
        case 10:
            return 20;
        case 11:
            return 21;
        case 12:
            return 22;
        case 13:
            return 23;
        case 14:
            return 24;
        case 15:
            return 25;
        case 16:
            return 26;
        case 17:
            return 27;
    }
    return 0;
}
extern s32 func_8004C874(s32, s32);
extern u8 D_80097FD8[];
s32 func_80063270(u8 arg0) {
    s32 result;
    if (arg0 < 0x1C) {
        result = func_8004C874(0xC, D_80097FD8[Type_IdToChartIndex(arg0)]);
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
