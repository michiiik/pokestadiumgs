#include "global.h"


#ifdef VERSION_US
extern void func_81600A34(void *, void *, s32, s32, s32, s32, s32);
extern u8 *D_81407BB0;
void func_81400020(s32 arg0) {
    func_81600A34((void *)arg0, D_81407BB0, 0, 0, 0, 0x280, 0x1E0);
    func_81600A34((void *)arg0, D_81407BB0 + 1, 1, 0, 0x1A1, 0x230, 0x3F);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400098.s")

s32 func_80002B24();
s32 func_800030D0(s32, s32);
extern void func_80003120(s32);
extern void func_81406AAC(s32 *, s32);
extern void func_81406EA8(s32 *);
s32 func_81600E28(s32, s32, s32);
extern s32 D_814077A0;
extern s32 D_814077AC;
extern u8 D_81407BB8;
void func_81400124(void) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = func_800030D0(func_80002B24(), 0);
    sp1C = temp_v0;
    D_814077A0 = func_81600E28(temp_v0, 1, 0x12);
    func_80003120(sp1C);
    func_81406AAC(&D_81407BB8, D_814077AC);
    func_81406EA8(&D_81407BB8);
}

extern void func_80008648();
extern void func_800088DC();
extern void func_81400098(s32);
extern void func_81407118(u8 *, s32);
extern s32 D_814077B4;
extern s32 D_814077B8;
void func_81400194(void) {
    s32 temp_v0;

    func_800088DC();
    temp_v0 = func_8000731C();
    D_814077B4 = D_814077B8;
    if (temp_v0 != 0) {
        D_814077B8 = (*(s32 *)((u8 *)(temp_v0) + (8)));
    } else {
        D_814077B8 = D_814077B4;
    }
    func_81400098(D_814077A0);
    func_81407118(&D_81407BB8, D_814077A0);
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400218.s")

extern void func_81400020(s32);
extern void func_81400194();
s32 func_81400218(s32);
extern void func_81406F44(u8 *, s32);
extern void func_81600954(s32);
extern void func_81600B30(s32);
extern void func_816018CC(s32);
void func_814002E8(void) {
    s32 temp_v0;
    s32 var_s1;

    var_s1 = 0;
    func_800086A4(2);
    func_80007AEC(3);
    func_80021ED8(0x1C);
    do {
        func_80064D28();
        func_816018CC(1);
        func_81600954(D_814077A0);
        func_81400020(D_814077A0);
        func_81406F44(&D_81407BB8, D_814077A0);
        func_81600B30(D_814077A0);
        func_81400194();
        temp_v0 = func_81400218(var_s1);
        var_s1 = temp_v0;
    } while (temp_v0 != 3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400398.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400468.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814005B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400884.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400A50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400C24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400DE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81400FA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81401178.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814011B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81401394.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81401404.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814014C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814018F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_81401DB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_8140225C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814024B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/12/fragment12_E5330/func_814025E8.s")

s32 func_814028A0(s32 arg0) {
    return (s32) (((((f32) arg0 + 0.5f) * 22.0f) + 17.0f) - 6.0f);
}
#endif
