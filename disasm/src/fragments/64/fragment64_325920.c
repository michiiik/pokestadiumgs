#include "global.h"


#ifdef VERSION_US
extern void func_87F02CE0(s32 *, s32, s32);
extern u8 D_80126420;

void func_87F02CB0(s32 arg0, s32 arg1) {
    func_87F02CE0(&D_80126420, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_325920/func_87F02CE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_325920/func_87F02F00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_325920/func_87F03204.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_325920/func_87F0328C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_325920/func_87F0339C.s")

extern void func_87F02684();

void func_87F034CC(void) {
    func_87F02684();
}
#endif
