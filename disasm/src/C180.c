#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/C180/func_8000B580.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/C180/func_8000B5B0.s")

s32 func_8000B60C(const s8 *a, const s8 *b) { s8 ca = *a; s8 cb = *b; while (ca == cb) { if (ca == 0) return 0; ca = *++a; cb = *++b; } return ca - cb; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/C180/func_8000B650.s")
#endif
