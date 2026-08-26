#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508490.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_885084EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508780.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_885087D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850889C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508B10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508B98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508BEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508CAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508D34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508E34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88508F78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88509290.s")

extern u8 D_88523050[];
void func_885093F0(void) { s32 i = 0; u8 *ptr = D_88523050; do { i += 1; ptr += 0x50; *(s32 *)(ptr - 0x50) = 0; } while (i != 2); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88509418.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88509538.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_885095EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_885096E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850974C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88509870.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850998C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88509A38.s")

extern u8 D_885230F0;
void func_8850A0A0(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_88509E74(void) {
    if (D_885230F0 == 0) {
        func_8850A0A0(0x200, 0xB9, 0x4C, 0x5A);
        return;
    }
    func_8850A0A0(0x2D, 0xB9, 0x4C, 0x5A);
}

extern u8 D_8850D6D8;
void func_8850A0A0(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
extern s32 D_880068B8;
extern void func_8004D878(s32, s32, s32);
void func_8850A0A0(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_88509EC8(void) {
    func_8850A0A0(0, 0, 0x280, 0x1E0);
    D_880068B8 = 1;
    if ((*(u8 *)((u8 *)(&D_885230F0) + (8))) != 0) {
        func_8004D878((s32) (((*(u8 *)((u8 *)(&D_885230F0) + (0))) * 0xA960) + 8 + &D_8850D6D8), 0, (*(s32 *)((u8 *)(&D_885230F0) + (4))));
    }
}

extern void func_88900494();
extern s32 D_880068B4;

void func_88509F40(void) {
    D_880068B4 = 1;
    func_88900494();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_88509F68.s")

extern u8 D_88523148;
void func_8850A0A0(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    (*(s16 *)((u8 *)(&D_88523148) + (0))) = arg0;
    (*(s16 *)((u8 *)(&D_88523148) + (2))) = arg1;
    (*(s16 *)((u8 *)(&D_88523148) + (4))) = arg2;
    (*(s16 *)((u8 *)(&D_88523148) + (6))) = arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A0EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A2F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A3F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A5CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A614.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A6C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A710.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A8BC.s")

extern void func_8850A0EC(s32);
s32 func_8850CED8(s32);

void func_8850A958(void) {
    if (func_8850CED8(7) != 0) {
        func_8850A0EC(5);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850A988.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850AAA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850ABCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850ACD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850AEA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850AFDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850B2DC.s")

s32 func_8004C990(s32, s32);
extern void func_8850B2DC(s32, s32, s16, s16, f32, s32, s32, s32, s32, s32);

void func_8850B914(s16 arg0, s16 arg1, f32 arg2) {
    func_8850B2DC(func_8004C990(0x147, 0), 0, arg0, arg1, arg2, 0, 0xE4, 0, 0xE4, -0x10);
}

s32 func_8004C990(s32, s32);

void func_8850B980(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    func_8850B2DC(func_8004C990(0x148, 1), 0, arg0, arg1, arg2, (s32) arg3, (s32) arg4, (s32) arg5, 0x64, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850B9F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850BACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850BDE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850C514.s")

s32 func_800071A4(s32, s32, s32, s32, s32);
extern void func_88508490();
extern s32 D_8852304C;

void func_8850C948(void) {
    func_8850A0EC(0);
    func_88508490();
    func_885093F0();
    D_8852304C = func_800071A4(0, 2, 0x20, 0x20, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850C998.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C5AA0/func_8850CED8.s")
#endif
