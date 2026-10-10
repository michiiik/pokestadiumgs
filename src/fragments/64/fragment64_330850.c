#include "global.h"


#ifdef VERSION_US
void func_87F0DBE0(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x0) = 0;
    *(s32 *)(arg0 + 0x4) = arg1;
    arg0[0x10] = 0;
    arg0[0x12] &= 0xFF7F;
}

void func_87F0DBFC(u8 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    struct State {
        s32 value, unused, count, limit;
        u8 index, mode;
        u8 active : 1;
        u8 other : 7;
    };
    struct State *state = (struct State *)arg0;
    state->value = arg1;
    state->active = 1;
    state->index = 0;
    state->mode = arg2;
    state->count = 0;
    state->limit = arg3;
    if (arg3 == -1) {
        state->value = 0;
        state->limit = 1;
    }
}

void func_87F0DC3C(u8 *arg0) { arg0[0x12] &= 0xFF7F; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_330850/func_87F0DC4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_330850/func_87F0DFB4.s")
#endif
