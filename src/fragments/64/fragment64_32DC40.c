#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32DC40/func_87F0AFD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32DC40/func_87F0B0FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32DC40/func_87F0B154.s")

void func_87F0B18C(u8 *arg0) {
    arg0[0x68] &= 0xFF7F;
    arg0[0x68] &= 0xFFBF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32DC40/func_87F0B1A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32DC40/func_87F0B24C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32DC40/func_87F0B2F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32DC40/func_87F0B4AC.s")

extern void func_8004C8C0(s32);
void func_87F0BD10(void) {
    func_8004C8C0(447);
}

void func_87F0BD30(u8 *arg0, u16 arg1, u16 arg2, s32 arg3) {
    *(u16 *)(arg0 + 0) = arg1;
    *(u16 *)(arg0 + 2) = arg2;
    *(s32 *)(arg0 + 4) = arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32DC40/func_87F0BD48.s")
#endif
