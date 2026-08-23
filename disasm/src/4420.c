#include "global.h"


#ifdef VERSION_US
u16 func_80003820(const u8 *arg0) {
    return (u16)((arg0[0] << 8) | arg0[1]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003838.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800039C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003A78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003AB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003AF0.s")

void func_80003CD0(void) { extern OSMesgQueue D_800CD000; extern OSMesg D_800CD018[]; osCreateMesgQueue(&D_800CD000, D_800CD018, 1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003D00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003DD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003E84.s")

s32 func_80003F54(s32 arg0) { return osFlashSectorErase(arg0 << 7); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80003F74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004024.s")

s32 func_800040C4(u8 *arg0) {
    return *(s32 *)(arg0 + 0xC) + 0x100;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800040D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800041E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004254.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800042C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004458.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800045E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004638.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800046C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004718.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800047B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800047F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_8000484C.s")

void func_800049B8(void) { func_800029E0(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_800049D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004B4C.s")

void func_80004B78(void) { func_80004A40(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4420/func_80004B98.s")
#endif
