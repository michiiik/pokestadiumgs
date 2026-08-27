#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/78D0/func_80006CD0.s")

extern void *D_800D0518;
extern void *D_800D051C;
extern void main_pool_try_free();
void Gfx_FreeDisplayListBuffers(void) { main_pool_try_free(D_800D051C); main_pool_try_free(D_800D0518); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/78D0/func_80006D6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/78D0/func_80006DAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/78D0/func_80006DEC.s")

extern s32 D_800D0520;
extern s32 D_800D0510;
s32 Gfx_GetDisplayListRemaining(void) { return D_800D0520 - D_800D0510; }
#endif
