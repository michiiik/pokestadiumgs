#include "global.h"


#ifdef VERSION_US
s32 func_80071210(u8 *arg0) { return arg0 ? ((*(u32 *)(arg0 + 0x40) << 1) >> 31) : 0; }

s32 func_80071230(u8 *arg0) { return arg0 ? ((*(u32 *)(arg0 + 0x40) << 2) >> 31) : 0; }

s32 func_80071250(u8 *arg0) {
    s16 value = *(s16 *)(arg0 + 0x34);

    return value > 0 && value < 5;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/71E10/func_8007126C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/71E10/func_800712DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/71E10/func_8007131C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/71E10/func_800714E8.s")

s32 func_80071890(void *arg0, s32 arg1) {
    u16 temp_v1;

    if ((arg0 == NULL) || (temp_v1 = (*(u16 *)((u8 *)(arg0) + (0x38))), (temp_v1 == 0))) {
        return 1;
    }
    return (s32) temp_v1 >= arg1;
}

s32 func_800718B8(s32 arg0) { extern s32 D_8009F828[]; if (arg0 < 0 || arg0 >= 0xF) return 0; return D_8009F828[arg0]; }

s32 func_800718E4(u8 *arg0) { return func_8004D690(arg0 != NULL ? *(u16 *)(arg0 + 0x3A) : 8); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/71E10/func_80071914.s")
#endif
