#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/func_80002680.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/func_80002740.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/func_800027F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/func_8000290C.s")

extern s32 func_80002740(s32, s32);
extern OSMesgQueue D_800CCDB4;
s32 func_80002984(s32 arg0, s32 arg1) {
    s32 result;

    osRecvMesg(&D_800CCDB4, NULL, 1);
    result = func_80002740(arg0, arg1);
    osSendMesg(&D_800CCDB4, NULL, 0);
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/func_800029E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/func_80002A40.s")

extern s32 D_800CCDCC;
s32 func_80002B24(void) {
    s32 value = D_800CCDCC - 0x10;

    if (value < 0) {
        value = 0;
    }
    return value;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/main_pool_push_state.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/main_pool_pop_state.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/func_80002D20.s")

u8 *func_80002DD4(u8 *arg0, s32 arg1, s32 arg2) {
    arg0 -= 0x10;
    *(s32 *)(arg0 + 8) = arg2;
    *(s32 *)(arg0 + 0xC) = arg1;
    return arg0;
}

s32 func_80002DE4(u8 *arg0) { return *(s32 *)(arg0 - 0xC) - (s32)arg0; }

extern u8 D_800CCDB0[]; u8 *func_80002DF0(void) { return D_800CCDB0; }
#endif
