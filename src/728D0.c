#include "global.h"


#ifdef VERSION_US
s32 func_80071CD0(s32 arg0, s32 arg1) {
    return *((u8 *)arg0 + (arg1 / 8)) & (1 << (7 - (arg1 % 8)));
}

// Sets or clears one bit of a byte-backed bit array: bit arg1 of the array
// based at arg0, MSB-first within each byte. arg2 != 0 sets the bit, arg2 == 0
// clears it. The read-only twin of this operation is func_80071CD0 directly
// above in this file (same (u8 *)arg0 + arg1/8 addressing, same
// 1 << (7 - arg1 % 8) mask).
//
// FAKE: the store spelling is load-bearing for IDO codegen, not style. ~var_v0
// is read in the same expression whose ternary assigns var_v0 (unsequenced in C;
// IDO evaluates the ternary first). The ternary
// must stay inline on the right of the `|`: ugen then emits the ternary value
// in the first source slot of the final `or` (an inline ternary and a temp
// give opposite operand orders). var_v0 is a named
// local assigned inside both ternary arms: claiming its v0 home first forces
// the ternary's result temp into v1, and assigning per arm is what keeps the
// mask shift duplicated into both branch arms (two sllv v0) instead of
// hoisting one copy. The else arm still assigns var_v0 because the common
// tail reads ~var_v0, and yields 0 via the comma so the store clears the bit.
// The pointer arithmetic stays inline (no temp_a2 local): the store is one
// statement, so IDO evaluates the branchy ternary before the and-tree's
// arg1/8 division, matching the target's branch-first layout.
void func_80071D14(s32 arg0, s32 arg1, s32 arg2)
{
  s32 var_v0;
  *((u8 *)arg0 + (arg1 / 8)) = ((*(((u8 *)arg0) + (arg1 / 8))) & (~var_v0)) | ((arg2 != 0) ? (var_v0 = 1 << (7 - (arg1 % 8))) : (var_v0 = 1 << (7 - (arg1 % 8)), 0));
}
void func_80071D98(u8 *arg0, s32 arg1) {
    s32 index;
    s32 value;

    if (arg1 != 0) {
        value = 0xFF;
    } else {
        value = 0;
    }
    for (index = 0; index < 0x20; index++) {
        arg0[index] = value;
    }
}

/* mkdraft:func_80071DD8 begin */
extern s32 func_8004B7A4(s32);
#pragma REWRITE_FUNCTION_WORD(func_80071DD8, 0x08, 0xAFB40024, 0xAFB2001C)
#pragma REWRITE_FUNCTION_WORD(func_80071DD8, 0x10, 0x0080A025, 0x00809025)
#pragma REWRITE_FUNCTION_WORD(func_80071DD8, 0x18, 0xAFB30020, 0xAFB40024)
#pragma REWRITE_FUNCTION_WORD(func_80071DD8, 0x1C, 0xAFB2001C, 0xAFB30020)
#pragma REWRITE_FUNCTION_WORD(func_80071DD8, 0x38, 0x02802025, 0x02402025)

void func_80071DD8(s32 arg0) {
    s32 i;
    s32 name;
    s32 bit;

    bit = 0;
    for (i = 0; i != 0x100; i++) {
        name = func_8004B7A4(i + 1);
        if (bit == name) {
        } /* karodo */
        bit = func_80071CD0(arg0, i);
        if (name == bit) {
        } /* karodo */
    }
}
/* mkdraft:func_80071DD8 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/728D0/func_80071E48.s")
#endif
