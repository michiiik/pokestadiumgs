#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/2/fragment2_code/func_81900020.s")

extern s32 D_81900718;
void func_81900154(void) {
    D_81900718 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/2/fragment2_code/func_81900164.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/2/fragment2_code/func_81900214.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/2/fragment2_code/func_8190037C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/2/fragment2_code/func_81900500.s")

extern void func_8003F1DC(void *);
extern s32 D_81900820;
extern s16 D_81900834;
extern s32 D_81900840;
extern s32 D_81900DE0;
void func_819006A0(void *arg0)
{
    u8 *var_s0;
    u8 *var_s1;
    // FAKE: the one-line layout below is load-bearing. as1 breaks prologue
    // scheduling ties by .loc line number; splitting the two initializations
    // and the loop head onto separate lines swaps the lui/addiu order of the
    // s0/s1/s2 address materialization.
    var_s1 = (u8 *) &D_81900820; var_s0 = (u8 *) &D_81900840; do { func_8003F1DC(var_s0);
        var_s0 += 360;
        var_s1 += 4;
        *((s32 *) (var_s1 - 4)) = 0;
    }
    while (var_s0 != ((u8 *) &D_81900DE0));
    D_81900834 = 0;
}
#endif
