#include "global.h"


#ifdef VERSION_US
void func_87E191B0(u8 *arg0, s32 arg1) {
    *(s32 *)arg0 = arg1;
    arg0[4] &= 0xFF7F;
}

extern u8 *D_80087200;
extern void func_800279C4(s32);
void func_87E191C4(void *arg0) {
    struct State {
        u32 unused;
        u32 enabled : 1;
        u32 rest : 31;
    };
    struct State *state = arg0;

    if (*(u16 *)(D_80087200 + 8) & 0x1000) {
        state->enabled ^= 1;
        func_800279C4(0xCF02);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_31CB20/func_87E1921C.s")
#endif
