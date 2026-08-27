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

extern void StageFade_StartFromTransparent(s32);
s32 StageContext_GetFadeMode();
extern void func_800225C4(s32);
s32 func_8002806C();

s32 func_8AB0B74C(s32 arg0) {
    s32 sp1C;

    sp1C = 0x2F;
    switch (arg0) {                                 /* irregular */
    case 0:
        StageFade_StartFromTransparent(5);
        if (func_8002806C() != 0x48) {
            func_800225C4(5);
        }
        break;
    case 1:
        if (StageContext_GetFadeMode() == 1) {
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

extern void *D_8AB16E30;
extern void *D_8AB16E34;
extern void *D_8AB16E38;
extern u8 *D_8AB16E40;
extern u8 *D_8AB16E44;
extern u8 *D_8AB16E48;
extern s16 D_8AB16F96;
void func_8AB0CBCC(void) {
    (*(u16 *)((u8 *)(D_8AB16E30) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E30) + (2))) & 0xFFFE);
    (*(u16 *)((u8 *)(D_8AB16E34) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E34) + (2))) & 0xFFFE);
    (*(u16 *)((u8 *)(D_8AB16E38) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E38) + (2))) & 0xFFFE);
    func_8AB00B98(D_8AB16E40, -1U);
    func_8AB00B98(D_8AB16E44, -1U);
    func_8AB00B98(D_8AB16E48, -1U);
    switch (D_8AB16F96) {                           /* irregular */
    case 0:
        (*(u16 *)((u8 *)(D_8AB16E30) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E30) + (2))) | 1);
        func_8AB00B98(D_8AB16E40, 0xFFFF00FFU);
        return;
    case 1:
        (*(u16 *)((u8 *)(D_8AB16E34) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E34) + (2))) | 1);
        func_8AB00B98(D_8AB16E44, 0xFFFF00FFU);
        return;
    case 2:
        (*(u16 *)((u8 *)(D_8AB16E38) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16E38) + (2))) | 1);
        func_8AB00B98(D_8AB16E48, 0xFFFF00FFU);
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0CD00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0D08C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22FAD0/func_8AB0D20C.s")
#endif
