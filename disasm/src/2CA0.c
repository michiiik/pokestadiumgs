#include "global.h"


#ifdef VERSION_US
extern u8 D_800CC5B0[]; void func_800020A0(s32 index, s32 value1, s32 value2) { *(s32 *)(D_800CC5B0 + index * 8) = value1; *(s32 *)(D_800CC5B0 + index * 8 + 4) = value2; }

extern u8 D_800CC5B0[]; s32 func_800020BC(s32 index) { return *(s32 *)(D_800CC5B0 + index * 8); }

extern u8 D_800CC5B0[];
u32 func_800020D0(u32 mask) {
    if ((mask >> 0x1C) == 0) {
        u32 id = (mask & 0x0F000000) >> 0x18;
        u32 value = mask & 0x00FFFFFF;
        if (*(u32 *)(D_800CC5B0 + id * 8) != 0) {
            mask = *(u32 *)(D_800CC5B0 + id * 8) + value;
        }
    }
    return mask;
}

s32 func_80002120(s32 arg0, s32 arg1) {
    u8 *ptr = D_800CC5B0 + arg0 * 8;
    u32 offset = (u32)arg1 - *(u32 *)(ptr + 0);
    if (offset >= *(u32 *)(ptr + 4)) return 0;
    return (arg0 << 24) | offset;
}

extern u8 D_800CC5B0[]; void func_8000215C(s32 index) { *(s32 *)(D_800CC5B0 + index * 8) = 0; *(s32 *)(D_800CC5B0 + index * 8 + 4) = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_80002178.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_80002210.s")

extern u8 D_800CC630[]; void func_80002470(s32 index, s32 value1, s32 value2) { *(s32 *)(D_800CC630 + index * 8) = value1; *(s32 *)(D_800CC630 + index * 8 + 4) = value2; }

extern u8 D_800CC630[]; s32 func_8000248C(s32 index) { return *(s32 *)(D_800CC630 + index * 8); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_800024A0.s")

extern u8 D_800CC630[];
s32 func_80002504(s32 arg0, s32 arg1) {
    u8 *ptr = D_800CC630 + arg0 * 8;
    u32 offset = (u32)arg1 - *(u32 *)(ptr + 0);
    if (offset >= *(u32 *)(ptr + 4)) return 0;
    return (((arg0 + 0x10) << 20) | 0x80000000) | offset;
}

extern u8 D_800CC630[]; void func_8000254C(s32 index) { *(s32 *)(D_800CC630 + index * 8) = 0; *(s32 *)(D_800CC630 + index * 8 + 4) = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_80002568.s")
#endif
