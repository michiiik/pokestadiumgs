#include "global.h"


#ifdef VERSION_US
extern void func_80049ED8(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_88229EE0(void) {
    func_80049ED8(D_80087200);
    D_880068B8 = 0;
}

extern void func_800033DC(s32);
extern s32 D_880068B4;
extern s32 D_882348D0;

void func_88229F08(void) {
    func_80049ED8(D_80087200);
    D_880068B4 = 1;
    func_800033DC(D_882348D0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19D160/func_88229F44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19D160/func_88229FB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19D160/func_8822A2B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19D160/func_8822A534.s")
#endif
