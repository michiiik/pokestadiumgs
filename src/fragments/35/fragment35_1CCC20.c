#include "global.h"


#ifdef VERSION_US
typedef struct {
    u16 values[3];
} Value_88600020;

extern u8 *D_88601890;
void func_88600020(u8 *arg0) {
    *(s32 *)(D_88601890 + 8) = *(s32 *)(*(u8 **)(arg0 + 0x1C) + 0x48);
    *(Value_88600020 *)(D_88601890 + 0xC) = *(Value_88600020 *)(*(u8 **)(arg0 + 0x1C) + 0x1E);
    *(s16 *)(D_88601890 + 0x12) = *(s16 *)(arg0 + 0xE);
    *(s16 *)(D_88601890 + 0x14) = *(s16 *)(arg0 + 0xC);
}

void func_88600074(u8 *arg0) {
    *(s32 *)(*(u8 **)(arg0 + 0x1C) + 0x48) = *(s32 *)(D_88601890 + 8);
    *(Value_88600020 *)(*(u8 **)(arg0 + 0x1C) + 0x1E) = *(Value_88600020 *)(D_88601890 + 0xC);
    *(s16 *)(arg0 + 0xE) = *(s16 *)(D_88601890 + 0x12);
    *(s16 *)(arg0 + 0xC) = *(s16 *)(D_88601890 + 0x14);
}

s32 func_886000C8(u16 species) {
    s32 index = species;

    if (index == 201) {
        index = 1;
    } else {
        index -= 252;
    }
    return index & 0xFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCC20/func_886000F0.s")

extern s32 func_8004C990(s32, s32);
extern s32 func_8004D19C(s32, s32, s32, s32, s32);
void func_88600170(s32 x, s32 y, s8 type) {
    s32 texture_index;

    switch (type) {
    case 7:
        texture_index = 0;
        break;
    case 26:
        texture_index = 1;
        break;
    case 23:
        texture_index = 2;
        break;
    case 27:
        texture_index = 4;
        break;
    case 1:
        texture_index = 5;
        break;
    case 20:
        texture_index = 6;
        break;
    case 2:
        texture_index = 7;
        break;
    case 8:
        texture_index = 8;
        break;
    case 22:
        texture_index = 9;
        break;
    case 4:
        texture_index = 10;
        break;
    case 25:
        texture_index = 11;
        break;
    case 0:
        texture_index = 12;
        break;
    case 3:
        texture_index = 13;
        break;
    case 24:
        texture_index = 14;
        break;
    case 5:
        texture_index = 15;
        break;
    case 9:
        texture_index = 16;
        break;
    case 21:
        texture_index = 17;
        break;
    default:
        texture_index = 3;
        break;
    }
    func_8004D19C(x, y, func_8004C990(332, texture_index), 0, 0);
}
#endif
