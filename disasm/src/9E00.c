#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009200.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_800092C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009384.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_8000948C.s")

extern void *memcpy(void *, const void *, s32); void *func_80009750(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009774.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009830.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_800098B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009940.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009D98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009E04.s")

extern u8 D_800D05B0[];
void func_80009EB4(s32 arg0, s32 arg1, s32 arg2) {
    s32 *arg1p = &arg1;
    s32 *arg2p = &arg2;
    *(s32 *)(D_800D05B0 + 0x9CC) = arg0 | 0xA0000000;
    *(s16 *)(D_800D05B0 + 0x9D0) = *arg1p;
    *(s16 *)(D_800D05B0 + 0x9D2) = *arg2p;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/crash_screen_init.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009F80.s")
#endif
