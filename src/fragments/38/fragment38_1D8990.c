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

extern u8 *D_889041B0;
extern s32 D_880068B8;
void func_88903B00(void) {
    s32 *temp_v0;

    temp_v0 = (*(s32 **)((u8 *)(D_889041B0) + (0x240)));
    if (temp_v0 == NULL) {
        D_880068B8 = 0;
        return;
    }
    *temp_v0 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8990/func_88903B2C.s")

extern void func_88004990(u8, s32);
extern void *D_80087200;
void func_88903BB4(void) {
    s32 *temp_v0;

    if ((*(u16 *)((u8 *)(D_80087200) + (8))) & 0xC000) {
        func_88004990(*(*(u8 **)((u8 *)(D_889041B0) + (0))), 0);
        temp_v0 = (*(s32 **)((u8 *)(D_889041B0) + (0x240)));
        if (temp_v0 != NULL) {
            *temp_v0 = 1;
            return;
        }
        D_880068B8 = 1;
    }
}

extern void func_889033A0(void *arg0);
void func_88903C28(void) {
    func_889033A0(D_889041B0 + 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D8990/func_88903C50.s")
#endif
