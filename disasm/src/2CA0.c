#include "global.h"


#ifdef VERSION_US
extern u8 D_800CC5B0[]; void func_800020A0(s32 index, s32 value1, s32 value2) { *(s32 *)(D_800CC5B0 + index * 8) = value1; *(s32 *)(D_800CC5B0 + index * 8 + 4) = value2; }

extern u8 D_800CC5B0[]; s32 func_800020BC(s32 index) { return *(s32 *)(D_800CC5B0 + index * 8); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_800020D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_80002120.s")

extern u8 D_800CC5B0[]; void func_8000215C(s32 index) { *(s32 *)(D_800CC5B0 + index * 8) = 0; *(s32 *)(D_800CC5B0 + index * 8 + 4) = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_80002178.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_80002210.s")

extern u8 D_800CC630[]; void func_80002470(s32 index, s32 value1, s32 value2) { *(s32 *)(D_800CC630 + index * 8) = value1; *(s32 *)(D_800CC630 + index * 8 + 4) = value2; }

extern u8 D_800CC630[]; s32 func_8000248C(s32 index) { return *(s32 *)(D_800CC630 + index * 8); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_800024A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_80002504.s")

extern u8 D_800CC630[]; void func_8000254C(s32 index) { *(s32 *)(D_800CC630 + index * 8) = 0; *(s32 *)(D_800CC630 + index * 8 + 4) = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/2CA0/func_80002568.s")
#endif
