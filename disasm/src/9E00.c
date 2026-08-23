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

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009EB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/crash_screen_init.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/9E00/func_80009F80.s")
#endif
