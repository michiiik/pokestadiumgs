#include "global.h"


#ifdef VERSION_US
typedef struct S1_unk_func_88316128 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ char unk09[0xD];
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ char unk18[0x14];
    /* 0x2C */ u8 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ u16 unk_32;
    /* 0x34 */ u16 unk_34;
    /* 0x36 */ u16 unk_36;
    /* 0x38 */ u8 unk_38;
    /* 0x39 */ char unk39[0xA];
    /* 0x43 */ u8 unk_43;
} S1_unk_func_88316128;
s32 LabPCList_CompareByPointer(S1_unk_func_88316128* arg0, S1_unk_func_88316128* arg1) {
    return (arg0 == arg1) ? 0 : (arg0 < arg1) ? -1 : 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_18F6D0/func_8821C47C.s")

extern void func_8821C47C(s32, s32, s32);
void func_8821C690(s32 arg0, s32 arg1) { func_8821C47C(arg0, arg1, 1); }

void func_8821C6B0(s32 arg0, s32 arg1) { func_8821C47C(arg0, arg1, 2); }

void func_8821C6D0(s32 arg0, s32 arg1) { func_8821C47C(arg0, arg1, 3); }

void func_8821C6F0(s32 arg0, s32 arg1) { func_8821C47C(arg0, arg1, 4); }

void func_8821C710(s32 arg0, s32 arg1) { func_8821C47C(arg0, arg1, 5); }

void func_8821C730(s32 arg0, s32 arg1) { func_8821C47C(arg0, arg1, 6); }

void func_8821C750(s32 arg0, s32 arg1) { func_8821C47C(arg0, arg1, 7); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_18F6D0/func_8821C770.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_18F6D0/func_8821C820.s")


typedef struct {
    u8 pad_00[8];
    u8 unk_08;
} Func8821C924Leaf;
typedef struct {
    Func8821C924Leaf *unk_00;
    u8 unk_04;
} Func8821C924Inner;
typedef struct {
    Func8821C924Inner *unk_00;
    s8 unk_04;
} Func8821C924Item;

s32 func_8821C924(Func8821C924Item *arg0, Func8821C924Item *arg1) {
    s32 result;
    result = arg0->unk_00->unk_00->unk_08 - arg1->unk_00->unk_00->unk_08;
    if (result == 0) {
        result = arg0->unk_00->unk_04 - arg1->unk_00->unk_04;
        if (result == 0) {
            result = arg0->unk_04 - arg1->unk_04;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_18F6D0/func_8821C970.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_18F6D0/func_8821CA24.s")

void func_8821CADC(s32 arg0, s32 arg1) { func_8821C47C(arg0, arg1, 13); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_18F6D0/func_8821CAFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_18F6D0/func_8821CB48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_18F6D0/func_8821CC0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_18F6D0/func_8821CCE8.s")
#endif
