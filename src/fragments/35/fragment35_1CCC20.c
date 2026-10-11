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
