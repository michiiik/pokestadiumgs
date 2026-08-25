#include "global.h"


#ifdef VERSION_US
void func_80019540(void *arg0, s32 arg1) {
    u32 sp1C;

    sp1C = osSetIntMask(1U);
    osInvalDCache(arg0, arg1);
    osSetIntMask(sp1C);
}

void func_80019580(void *arg0, s32 arg1) {
    u32 sp1C;

    sp1C = osSetIntMask(1U);
    osWritebackDCache(arg0, arg1);
    osSetIntMask(sp1C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A140/func_800195C0.s")

extern u8 D_8008FAB8;
extern u8 D_8008FB28;
extern void *D_8008FC18;
extern void *D_8008FC1C;

void func_80019634(s32 arg0) {
    D_8008FC18 = (arg0 * 0x22) + &D_8008FB28;
    D_8008FC1C = (arg0 * 0x10) + &D_8008FAB8;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A140/func_80019670.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A140/func_800196E0.s")
#endif
