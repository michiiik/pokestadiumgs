#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B6E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B754.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B7A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B7E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B888.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B8E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B920.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B98C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B9E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BA34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BA70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BAE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BB58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BBA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BC6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BCBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BD28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BD78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BDB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BE18.s")

extern void func_80004024(s32 *, s32, s32);
s32 func_800356CC(s32);
extern u8 D_801270B0;

void func_8004BE50(void) {
    s32 temp_v0;

    temp_v0 = func_800356CC(0xA);
    func_80004024(&D_801270B0, temp_v0, temp_v0 + 0xFD0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BE84.s")

s32 func_8004B754(s32);
void func_8004BEEC(s32 arg0, s32 arg1, s16 arg2) {
    s32 temp_v0;

    temp_v0 = func_8004B754(arg1);
    if ((arg0 != 0) && (temp_v0 >= 0)) {
        (*(s16 *)((u8 *)(((temp_v0 * 0xC) + arg0)) + (2))) = arg2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BF3C.s")

void func_8004BFC4(s32 arg0, s32 arg1, s16 arg2) {
    s32 temp_v0;

    temp_v0 = func_8004B754(arg1);
    if ((arg0 != 0) && (temp_v0 >= 0)) {
        (*(s8 *)((u8 *)(((temp_v0 * 0xC) + arg0)) + (8))) = (s8) arg2;
    }
}
#endif
