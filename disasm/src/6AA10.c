#include "global.h"


/* Intentional no-op hook; the US body is a single jr $ra / nop pair. */
void func_80069E10(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA10/Game_State18_Run.s")
#endif
