#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/78D0/func_80006CD0.s")

extern void *D_800D0518;
extern void *D_800D051C;
extern void func_800029E0();
void func_80006D3C(void) { func_800029E0(D_800D051C); func_800029E0(D_800D0518); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/78D0/func_80006D6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/78D0/func_80006DAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/78D0/func_80006DEC.s")

extern s32 D_800D0520;
extern s32 D_800D0510;
s32 func_80006E2C(void) { return D_800D0520 - D_800D0510; }
#endif
