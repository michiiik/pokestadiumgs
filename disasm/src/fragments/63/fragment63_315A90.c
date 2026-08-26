#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E12120.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E121AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E123B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E12568.s")

extern void func_8004C8C0(s32);
extern void func_87E12568(s32);
void func_87E12674(s32 arg0, s32 arg1) {
    *(s32 *)arg0 = arg1;
    func_8004C8C0(0x167);
    func_8004C8C0(0x1BB);
    func_8004C8C0(0x175);
    func_87E12568(arg0);
}

extern void func_87F0277C(s32);
void func_87E126B4(s32 arg0) { func_87F0277C((arg0 + 4)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E126D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E127B8.s")

extern u32 D_87E1ABC4;
extern void func_87E126D4(s32, void *, s32, s32, s32);
void func_87E127FC(s32 arg0) { func_87E126D4(arg0, &D_87E1ABC4, 0, 30, 4096); }

extern f32 D_87E1B824;
extern f32 D_87E1B828;
extern f32 D_87E1B82C;
s32 func_80001FF0(void);
extern f32 D_87E1B830;
extern f32 D_87E1B834;
extern f32 D_87E1B838;
extern f32 D_87E1B83C;
extern f32 D_87E1B840;
extern f32 D_87E1B844;
extern f32 D_87E1B824;
extern f32 D_87E1B828;
extern f32 D_87E1B82C;
s32 func_80001FF0(void);
void func_87E12830(s32 arg0) {
    s32 var_a3;

    if (((f32) func_80001FF0() * D_87E1B824) >= 0.0f) {
        var_a3 = (s32) (((f32) func_80001FF0() * D_87E1B828) + 0.5f);
    } else {
        var_a3 = (s32) (((f32) func_80001FF0() * D_87E1B82C) - 0.5f);
    }
    func_87E126D4(arg0, &D_87E1ABC4, 2, var_a3, 0x5000);
}

extern f32 D_87E1B830;
extern f32 D_87E1B834;
extern f32 D_87E1B838;
s32 func_80001FF0(void);
void func_87E12900(s32 arg0) {
    s32 var_a3;

    if (((f32) func_80001FF0() * D_87E1B830) >= 0.0f) {
        var_a3 = (s32) (((f32) func_80001FF0() * D_87E1B834) + 0.5f);
    } else {
        var_a3 = (s32) (((f32) func_80001FF0() * D_87E1B838) - 0.5f);
    }
    func_87E126D4(arg0, &D_87E1ABC4, 1, var_a3, 0x5000);
}

extern f32 D_87E1B83C;
extern f32 D_87E1B840;
extern f32 D_87E1B844;
s32 func_80001FF0(void);
void func_87E129D0(s32 arg0) {
    s32 var_a3;

    if (((f32) func_80001FF0() * D_87E1B83C) >= 0.0f) {
        var_a3 = (s32) (((f32) func_80001FF0() * D_87E1B840) + 0.5f);
    } else {
        var_a3 = (s32) (((f32) func_80001FF0() * D_87E1B844) - 0.5f);
    }
    func_87E126D4(arg0, &D_87E1ABC4, 3, var_a3, 0x5000);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E12AA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E12B34.s")

extern u32 D_87E1AB64;
void func_87E12BE8(s32 arg0) { func_87E126D4(arg0, &D_87E1AB64, 0, 15, 8192); }

void func_87E12C1C(s32 arg0) { func_87E126D4(arg0, &D_87E1AB64, 2, 15, 8192); }

void func_87E12C50(s32 arg0) { func_87E126D4(arg0, &D_87E1AB64, 1, 15, 8192); }

void func_87E12C84(s32 arg0) { func_87E126D4(arg0, &D_87E1AB64, 3, 15, 8192); }

void func_87E12CB8(s32 arg0) {
    s32 i;
    for (i = 0; i != 8; ++i) {
        func_87E126D4(arg0, &D_87E1AB64, i, 30, 8192);
    }
}

extern void func_87F02684(s32);
void func_87E12D28(s32 arg0) { func_87F02684((arg0 + 4)); }

s32 func_87E12D48(u8 *arg0) {
    s32 result = 1;
    u8 *node = *(u8 **)(arg0 + 0x10);
    while (node != 0) {
        u8 *entry = *(u8 **)(node + 0x38);
        if (*(u8 **)(entry + 0x90) != 0) {
            result = 0;
        }
        node = *(u8 **)(node + 4);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E12D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E130F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E131D8.s")

void func_87E13248(void) { func_8004C8C0(361); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E13268.s")

s32 func_80040E80(s32, s32 *);
extern u8 D_87E1AC40;
extern u8 D_87E1EBC0;
extern void func_80037E9C(s32, void *);
extern s32 func_800030D0(s32, s32);
s32 func_80002B24(void);
extern void func_80003120(s32);
void func_87E1331C(void *arg0) {
    s32 sp1C;
    s32 temp_v0;

    func_80037E9C(0, &D_87E1EBC0);
    temp_v0 = func_800030D0(func_80002B24(), 0);
    sp1C = temp_v0;
    (*(s32 *)((u8 *)(arg0) + (0x28))) = func_80040E80(temp_v0, &D_87E1AC40);
    func_80003120(sp1C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E13380.s")

extern u8 *D_87E1EBD8;
void func_87E133F0(void) {
    func_87F0277C((s32) (D_87E1EBD8 + 0x2C));
    if ((*(s32 *)((u8 *)(D_87E1EBD8) + (0))) & 4) {
        (*(u32 *)((u8 *)(D_87E1EBD8) + (0x268))) = (u32) ((*(u32 *)((u8 *)(D_87E1EBD8) + (0x268))) + 1);
        if ((u32) (*(u32 *)((u8 *)(D_87E1EBD8) + (0x268))) >= 0xFFFFFF01U) {
            (*(u32 *)((u8 *)(D_87E1EBD8) + (0x268))) = 0U;
        }
    }
}

extern u8 *D_87E1EBD8;
extern void func_8003C6B8(s32);
void func_87E13458(void) { func_8003C6B8(*(s32 *)(D_87E1EBD8 + 0x28)); }

void func_87E13480(u8 *arg0) { extern u8 *D_87E1EBD8; *(u8 **)(D_87E1EBD8 + 4) = arg0; }

extern u8 *D_87E1EBD8;
void func_87E13490(void) {
    *(u32 *)D_87E1EBD8 |= 1;
    *(u32 *)D_87E1EBD8 &= 0xFFFFFFFD;
}

void func_87E134C0(void) {
    *(u32 *)D_87E1EBD8 &= 0xFFFFFFFE;
    *(u32 *)(D_87E1EBD8 + 0xC) = 0;
}

extern void func_87F0B1A4(u8 *, u8 *, f32, s32, f32, s32, s32);
extern u8 *D_87E1EBD8;
void func_87E134E8(void) {
    func_87F0B1A4(D_87E1EBD8 + 0x1CC, D_87E1EBD8 + 0x88, (*(f32 *)((u8 *)(D_87E1EBD8) + (0x88))) + -520.0f, (*(s32 *)((u8 *)(D_87E1EBD8) + (0x8C))), (*(f32 *)((u8 *)(D_87E1EBD8) + (0x90))), 0xF, 0x2000);
    (*(s32 *)((u8 *)(D_87E1EBD8) + (0))) = (s32) ((*(s32 *)((u8 *)(D_87E1EBD8) + (0))) | 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E13558.s")

void func_87E13654(void) {
    extern u8 *D_87E1EBD8;
    *(u32 *)D_87E1EBD8 |= 4;
}

void func_87E1366C(void) {
    extern u8 *D_87E1EBD8;
    *(u32 *)D_87E1EBD8 &= 0xFFFFFFFB;
}

s32 func_87E13688(void) {
    return *(s32 *)(D_87E1EBD8 + 0x250) == 0;
}

s32 func_87E1369C(void) {
    s32 result = *(s32 *)(D_87E1EBD8 + 0x250) == 0;
    if ((result == 0) && (*(s32 *)(D_87E1EBD8 + 0x23C) / 2 < *(s32 *)(D_87E1EBD8 + 0x238))) {
        result = 1;
    }
    return result;
}
#endif
