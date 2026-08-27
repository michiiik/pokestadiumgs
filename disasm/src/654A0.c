#include "global.h"


#ifdef VERSION_US
extern u8 D_8009DE50[]; u8 func_800648A0(u8 index) { return D_8009DE50[index]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/654A0/func_800648B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/654A0/func_80064940.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/654A0/func_80064980.s")

s32 func_800649CC(void) { return 2; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/654A0/func_800649D4.s")

extern void _bzero(s32 *, s32);
extern s8 D_80128B50;
extern u8 D_80128B58;

void func_800649E0(void) {
    D_80128B50 = 0;
    _bzero(&D_80128B58, 0x80);
}

extern u8 D_80128B5A;
u8 func_80064980(u8);
void func_80064A10(u8 arg0, u8 arg1) {
    (&D_80128B58)[(u8)D_80128B50 * 4] = arg0;
    (&D_80128B58)[(u8)D_80128B50 * 4 + 1] = arg1;
    (&D_80128B5A)[(u8)D_80128B50 * 4] = func_80064980(arg1);
    D_80128B50 = (u8)D_80128B50 + 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/654A0/func_80064A7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/654A0/func_80064AC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/654A0/func_80064B84.s")
#endif
