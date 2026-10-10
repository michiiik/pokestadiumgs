#include "global.h"


#ifdef VERSION_US
extern void func_8004C8C0(s32);
extern void func_8004C4B0(s32);
void func_87F0C650(void *arg0) {
    struct State {
        s32 first, second;
        u8 active : 1;
        u8 pending : 1;
        u8 other : 6;
    };
    struct State *state = arg0;
    state->first = 0;
    state->second = 0;
    state->active = 0;
    state->pending = 0;
    func_8004C8C0(0x139);
    func_8004C4B0(0x16);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32F2C0/func_87F0C694.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32F2C0/func_87F0C6F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32F2C0/func_87F0C7B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32F2C0/func_87F0C88C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32F2C0/func_87F0C930.s")
#endif
