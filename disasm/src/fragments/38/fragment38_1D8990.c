#include "global.h"


#ifdef VERSION_US
extern void func_80049064(s16, s16, s32, s32);
extern void func_800496A4(s32, s16);
extern void func_8004989C(s32);
extern void func_800498C4();
extern void func_800499EC();
void func_889033A0(void *arg0) {
    func_800498C4();
    func_800496A4((*(s32 *)((u8 *)(arg0) + (0x10))), (*(s16 *)((u8 *)(arg0) + (0x14))));
    func_8004989C(0x1A);
    func_80049064((*(s16 *)((u8 *)(arg0) + (0))), (*(s16 *)((u8 *)(arg0) + (2))), (*(s32 *)((u8 *)(arg0) + (4))), *(*(s32 **)((u8 *)(arg0) + (8))));
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8990/func_889033FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8990/func_889034DC.s")

void func_889035A0(void *arg0, u8 *arg1, s16 arg2, s16 arg3) {
    (*(s16 *)((u8 *)(arg0) + (4))) = arg2;
    (*(s16 *)((u8 *)(arg0) + (6))) = arg3;
    (*(u8 **)((u8 *)(arg0) + (8))) = arg1;
    (*(s16 *)((u8 *)(arg0) + (0xC))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0xE))) = func_88902B70(arg1);
    (*(s32 *)((u8 *)(arg0) + (0x10))) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8990/func_889035FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8990/func_88903B00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8990/func_88903B2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8990/func_88903BB4.s")

extern u8 *D_889041B0;
extern void func_889033A0(void *arg0);
void func_88903C28(void) {
    func_889033A0(D_889041B0 + 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8990/func_88903C50.s")
#endif
