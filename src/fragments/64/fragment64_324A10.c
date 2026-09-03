#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324A10/func_87F01DA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324A10/func_87F01E8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324A10/func_87F01F34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324A10/func_87F02104.s")

extern u8 *D_87F11980; extern void func_87F08FA0(u8); extern void func_800503A4(void *); void func_87F022F0(void) { func_87F08FA0(D_87F11980[0x28]); func_800503A4(*(void **)(D_87F11980 + 4)); }

extern u8 *D_87F11980; void func_87F02328(void) { D_87F11980[0x28] = 0; }
#pragma C_FUNCTION_PADDING(8)
#endif
