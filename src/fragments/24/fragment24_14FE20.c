#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_14FE20/func_82B00020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_14FE20/func_82B00098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_14FE20/func_82B002B8.s")

extern void func_800088DC();
extern void func_82B080D0();
extern void func_80008648();
void func_82B004FC(s32 arg0) {
    func_800088DC();
    func_82B080D0();
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_14FE20/func_82B0052C.s")

typedef struct Target82BState Target82BState;
struct Target82BState { u8 pad_0000[0x1A60]; s16 value; };
extern Target82BState D_82B107C0;
extern s16 D_82B12220;
s32 func_82B0069C(void) {
    s32 result = 1;
    volatile Target82BState *state = &D_82B107C0;
    D_82B12220 = state->value + 1;
    if (state->value < 2) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_14FE20/func_82B006D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_14FE20/func_82B00914.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_14FE20/func_82B00B78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_14FE20/func_82B00BE0.s")
#endif
