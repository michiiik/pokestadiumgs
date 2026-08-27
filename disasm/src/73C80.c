#include "global.h"


#ifdef VERSION_US
void func_80073080(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    u8 *temp_v0;

    temp_v0 = (u8 *)((u32)arg0 + (arg1 * 0x1DC));
    temp_v0[0x1D4] = arg2;
    temp_v0[0x1D5] = arg3;
    temp_v0[0x1D6] = arg4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/73C80/func_800730BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/73C80/func_80073208.s")

typedef struct Copy73394 {
    s32 words[17];
} Copy73394;

void func_80073394(u8 *arg0, u8 *arg1, u8 arg2, u8 arg3) {
    u8 *src;
    u8 *dst;

    src = (u8 *)((u32)arg1 + (arg3 * 0x1DC));
    dst = (u8 *)((u32)arg0 + (arg2 * 0x4E0));
    *(Copy73394 *)(dst + 0x49C) = *(Copy73394 *)(src + 0x190);
    dst[0x49A] = 0xFF;
}
#endif
