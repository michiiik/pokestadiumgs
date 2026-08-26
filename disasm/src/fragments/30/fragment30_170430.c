#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170430/func_88102F60.s")

extern void *D_80087200;
extern void Input_SetRepeatController(void *);
extern s32 D_880068B8;
void func_88103058(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void *D_88104E90;
extern void Util_Free(void *);
extern s32 D_880068B4;
void func_88103080(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B4 = 1;
    Util_Free(D_88104E90);
}

extern void func_88004990(s32, s32);
void func_881030BC(void) {
    func_88004990(**(u8 **)(D_88104E90), 0);
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170430/func_881030F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170430/func_881033FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170430/func_881035C0.s")
#endif
