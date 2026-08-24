#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80002E00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80002E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80002EB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80002F90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_800030D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80003120.s")

u8 *func_80003164(u8 *arg0, s32 arg1) {
    s32 value = (arg1 & ~3) - 0x10;
    u8 *ptr = arg0 + 0x10;
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 0) = value;
    *(u8 **)(arg0 + 8) = ptr;
    *(u8 **)(arg0 + 0xC) = ptr;
    return arg0;
}

typedef struct { s32 freeSpace; s32 listHeadL; s32 listHeadR; s32 prev; } MainPoolState;
s32 func_8000318C(MainPoolState *state, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_a3;
    s32 var_v0;
    s32 ret = 0;
    if (arg2 > 0) var_v0 = ((state->prev + arg2) - 1) & ~(arg2 - 1);
    else var_v0 = state->prev;
    temp_a2 = (var_v0 - state->prev) + arg1;
    if (temp_a2 > 0) {
        temp_a3 = state->listHeadL + temp_a2;
        if (state->freeSpace >= temp_a3) {
            ret = var_v0;
            state->prev += temp_a2;
            state->listHeadL = temp_a3;
        }
    }
    return ret;
}

void func_800031FC(u8 *arg0, s32 arg1) { if (*(s32 *)(arg0 + 0) >= arg1) { *(s32 *)(arg0 + 4) = arg1; *(s32 *)(arg0 + 0xC) = *(s32 *)(arg0 + 8) + arg1; } }

void func_80003224(u8 *arg0) {
    u8 *ptr = arg0 + 0x10;
    *(s32 *)(arg0 + 4) = 0;
    *(u8 **)(arg0 + 8) = ptr;
    *(u8 **)(arg0 + 0xC) = ptr;
}
#endif
