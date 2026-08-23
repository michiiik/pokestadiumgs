#include "global.h"

extern s32 D_80128C00;

/* Returns the current decoded frame counter used by the state-5 helpers. */
s32 func_8006D424(void) {
    return D_80128C00;
}

/* These hooks are intentionally empty; their argument is only present in the
 * original ABI and is saved into the caller's outgoing argument area. */
void func_8006D430(s32 arg0) {
    (void)arg0;
}

void func_8006D438(s32 arg0) {
    (void)arg0;
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6DEC0/func_8006D2C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6DEC0/Game_State05_Run.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6DEC0/Game_State19_Run.s")
#endif
