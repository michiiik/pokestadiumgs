#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/1C2D0/func_8001B6D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1C2D0/func_8001B8D0.s")

extern f32 D_8008E994[];
f32 func_8001BA28(void *arg0) {
    struct State { u8 pad0[2]; u16 sum; u16 step; u8 pad6[2]; f32 scale; };
    struct State *state = arg0;
    u32 index;
    f32 one;
    f32 result;
    one = 1.0f;
    state->sum += state->step;
    index = (state->sum >> 8) & 0xFF;
    if (index >= 0x7F) {
        index = 0x7F;
        state->pad0[0] = 0;
    }
    result = (D_8008E994[index] - one) * state->scale + one;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1C2D0/func_8001BA84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1C2D0/func_8001BABC.s")

extern f32 func_8001BA28();
extern f32 func_8001BABC();
void func_8001BCA4(u8 *arg0) {
    u8 *state;
    state = arg0;
    if (state[0x80] != 0) {
        *(f32 *)(state + 0x38) = func_8001BA28(state + 0x80);
    }
    if (state[0xA0] != 0) {
        *(f32 *)(state + 0x3C) = func_8001BABC(state + 0x8C);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1C2D0/func_8001BD00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1C2D0/func_8001BDF0.s")

void func_8001BE1C(void *arg0, s32 arg1, s32 arg2) {
    (*(s8 *)((u8 *)(arg0) + (0))) = 0;
    (*(s16 *)((u8 *)(arg0) + (2))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x1C))) = arg1;
    (*(f32 *)((u8 *)(arg0) + (4))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (0x10))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (8))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (0xC))) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1C2D0/func_8001BE44.s")
#endif
