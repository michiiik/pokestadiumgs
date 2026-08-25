#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_80072030.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_80072070.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_800720A8.s")

extern u8 D_8012B3F6;
void func_8007214C(s8 arg0) {
    D_8012B3F6 = 1 << arg0;
}

void func_8007216C(s32 *arg0) {
    arg0[0] = 0;
    arg0[1] = 0;
    arg0[2] = 1;
    arg0[3] = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_80072184.s")

void func_800721D8(u8 *arg0) {
    *(s16 *)(arg0 + 0) = 4;
    arg0[0xE] = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_800721EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_80072264.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_800723C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_800723FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_80072650.s")

s32 (*func_80003240(s32 *))(s32 *);
extern u8 D_801291E0;
extern u8 func_87F0EE0C;
void func_80072740(s32 arg0) {
    func_80003240(&func_87F0EE0C)(&D_801291E0);
}

extern u8 func_87F0F390;
void func_80072774(s32 arg0) {
    func_80003240(&func_87F0F390)(arg0);
}

extern u8 func_87F0F3E4;
void func_800727A4(s32 arg0) {
    func_80003240(&func_87F0F3E4)(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_800727D4.s")
#endif
