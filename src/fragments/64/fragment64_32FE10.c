#include "global.h"


#ifdef VERSION_US
u8 *func_87F0D1A0(u8 *arg0) {
    return arg0 + 8;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32FE10/func_87F0D1A8.s")

typedef struct { u8 *value; } Func87F0D44CArg;
extern u8 D_87F112F4[];
extern void func_87F0D1A8(void *, void *, s32, s32, s32);
void func_87F0D44C(Func87F0D44CArg arg0) {
    func_87F0D1A8(arg0.value + 8, D_87F112F4, 0x20, *(s32 *)(arg0.value + 4), 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32FE10/func_87F0D48C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32FE10/func_87F0D5B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32FE10/func_87F0D600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32FE10/func_87F0D96C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32FE10/func_87F0DA08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32FE10/func_87F0DB3C.s")
#endif
