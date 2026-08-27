#include "global.h"


#ifdef VERSION_US
extern void *D_800D0518;
extern void *D_800D051C;
extern s32 D_800D0510;
extern s32 main_pool_alloc_with_func(s32, s32, s32, s32);
extern void func_80006D6C(void);
void func_80006CD0(s32 arg0, s32 arg1) {
    *(s16 *)((u8 *)&D_800D0518 + 0x10) = 0;
    *(s32 *)((u8 *)&D_800D0518 + 0xC) = arg0;
    D_800D0518 = (void *)main_pool_alloc_with_func(arg0, arg1, 0x44594E30, 0);
    D_800D051C = (void *)main_pool_alloc_with_func(arg0, arg1, 0x44594E31, 0);
    func_80006D6C();
}

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
