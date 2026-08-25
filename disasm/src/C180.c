#include "global.h"


#ifdef VERSION_US
s8 *func_8000B580(s8 *arg0, s8 *arg1) {
    s8 *var_v1;
    s8 temp_v0;
    s8 temp_v0_2;
    temp_v0 = *arg1;
    var_v1 = arg0 + 1;
    arg1 += 1;
    *arg0 = temp_v0;
    if (temp_v0 != 0) {
        do {
            temp_v0_2 = *arg1;
            var_v1 += 1;
            arg1 += 1;
            var_v1[-1] = temp_v0_2;
        } while (temp_v0_2 != 0);
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/C180/func_8000B5B0.s")

s32 func_8000B60C(const s8 *a, const s8 *b) { s8 ca = *a; s8 cb = *b; while (ca == cb) { if (ca == 0) return 0; ca = *++a; cb = *++b; } return ca - cb; }

char *func_8000B650(char *dest, s32 c, u32 nsize) {
    char *newDest = dest;
    while (nsize-- > 0) *newDest++ = c;
    return dest;
}
#endif
