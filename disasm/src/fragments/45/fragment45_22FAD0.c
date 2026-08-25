#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0A950.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B24C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B3F4.s")

extern void func_8AB0B67C(s32);
void func_8AB0B52C(void) { func_8AB0B67C(0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B54C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B5E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B67C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B6E0.s")

extern void func_80007B34(s32);
s32 func_800084A0();
extern void func_800225C4(s32);
s32 func_8002806C();

s32 func_8AB0B74C(s32 arg0) {
    s32 sp1C;

    sp1C = 0x2F;
    switch (arg0) {                                 /* irregular */
    case 0:
        func_80007B34(5);
        if (func_8002806C() != 0x48) {
            func_800225C4(5);
        }
        break;
    case 1:
        if (func_800084A0() == 1) {
            sp1C = 0;
        }
        break;
    }
    return sp1C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B7CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0B96C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0BACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0BE4C.s")

void func_8AB0BF70(u8 *arg0) {
    *(s32 *)(arg0 + 0xC) = 1;
    *(s16 *)(arg0 + 0x10) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0BF80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0C414.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0C5CC.s")

void func_8AB0C7C0(void *arg0, s32 arg1) {
    if ((*(s32 *)((u8 *)(arg0) + (0xC))) == 1) {
        (*(s16 *)((u8 *)(arg0) + (0x10))) = (s16) ((*(s16 *)((u8 *)(arg0) + (0x10))) - 1);
        if ((*(s16 *)((u8 *)(arg0) + (0x10))) <= 0) {
            (*(s16 *)((u8 *)(arg0) + (0x10))) = 0;
            (*(s32 *)((u8 *)(arg0) + (0xC))) = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0C7FC.s")

s32 func_8AB0C9B0(void) {
    return 0x37;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0C9B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0CA58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0CBCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0CD00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0D08C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0D20C.s")
#endif
