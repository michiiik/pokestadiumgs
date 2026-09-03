#include "global.h"


#ifdef VERSION_US
extern void *D_87F119DC;
extern u8 D_87E1AC24[];
extern void func_87F0B4AC(void *, f32 *, f32 *, s16 *);
extern void func_87F0D1A8(void *, void *, s32, s32, s32);
void func_87E12120(void) {
    s32 temp_v1;
    s32 temp_v0;

    temp_v1 = *(s32 *)((u8 *)D_87F119DC + 0x38);
    func_87F0B4AC((void *)(temp_v1 + 0xC),
        (f32 *)((u8 *)D_87F119DC + 0x48),
        (f32 *)((u8 *)D_87F119DC + 0x54),
        (s16 *)((u8 *)D_87F119DC + 0x42));
    temp_v0 = *(s32 *)(temp_v1 + 0x0);
    if ((temp_v0 == 4) || (temp_v0 == 5) ||
        (temp_v0 == 6) || (temp_v0 == 7)) {
        func_87F0D1A8((u8 *)D_87F119DC + 0x60, &D_87E1AC24,
            6, *(s32 *)((u8 *)D_87F119DC + 0x1C), 10);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E121AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E123B8.s")

extern u8 D_87E1B9D8;
extern u8 D_87E1AB30;
extern s32 func_80040E80(s32, s32 *);
extern void func_87F0252C(void *, void *, void *, s32);
void func_87E12568(s32 arg0) {
    u8 *sp24;
    u8 *sp20;
    s32 sp1C;
    s32 temp_v0;
    s32 var_a1;
    u8 *var_a0;
    u8 *var_a2;
    u8 *var_a3;
    u8 *var_t0;
    u8 *var_v0;
    u8 *var_v1;
    extern void *main_pool_alloc(s32, s32);
    extern void func_87F0252C(void *, void *, void *, s32);
    extern s32 main_pool_get_available(void);
    extern s32 MainPool_AllocState(s32, s32);
    extern s32 func_80040E80(s32, s32 *);
    extern void MainPool_FinalizeAllocation(s32);
    extern void func_87E123B8(s32);

    sp24 = (u8 *)main_pool_alloc(0xC60, 0);
    sp20 = (u8 *)main_pool_alloc(0x4A0, 0);
    func_87F0252C(&D_87E1B9D8, (u8 *)(u32)arg0 + 4, sp24, 8);
    var_a0 = sp20;
    var_a1 = 0;
    var_v1 = sp24;
    var_v0 = sp20;
    var_a2 = sp20 + 0x94;
    var_a3 = sp20 + 0x128;
    var_t0 = sp20 + 0x1BC;
    do {
        *(u8 **)(var_v1 + 0x38) = var_a0;
        *(s32 *)(var_v0 + 0x4) = 0;
        *(s32 *)(var_v0 + 0x8) = 0;
        *(u8 **)(var_v1 + 0x1C4) = var_a2;
        *(s32 *)(var_v0 + 0x9C) = 0;
        *(s32 *)(var_v0 + 0x98) = 0;
        *(u8 **)(var_v1 + 0x350) = var_a3;
        *(s32 *)(var_v0 + 0x130) = 0;
        *(s32 *)(var_v0 + 0x12C) = 0;
        *(u8 **)(var_v1 + 0x4DC) = var_t0;
        var_a1 += 4;
        *(s32 *)(var_v0 + 0x1C4) = 0;
        *(s32 *)(var_v0 + 0x1C0) = 0;
        var_t0 += 0x250;
        var_a3 += 0x250;
        var_a2 += 0x250;
        var_a0 += 0x250;
        var_v1 += 0x630;
        var_v0 += 0x250;
    } while (var_a1 != 8);
    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    sp1C = temp_v0;
    *(s32 *)((u8 *)(u32)arg0 + 0x18) = func_80040E80(temp_v0, (s32 *)&D_87E1AB30);
    MainPool_FinalizeAllocation(sp1C);
    func_87E123B8(arg0);
}

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
void func_87E126B4(s32 arg0) {
    func_87F0277C((arg0 + 4));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E126D4.s")

void func_87E127B8(void *arg0, s32 arg1, void **arg2, void **arg3) {
    void *var_v0;
    void *temp_a0;
    s32 var_v1;

    *arg2 = 0;
    *arg3 = 0;
    var_v0 = *(void **)((u8 *)arg0 + 0xC);
    var_v1 = 0;
    while (var_v1 != 8) {
        temp_a0 = *(void **)((u8 *)var_v0 + 0x38);
        var_v1++;
        if (*(s32 *)temp_a0 == arg1) {
            *arg3 = temp_a0;
            *arg2 = var_v0;
            break;
        }
        var_v0 = (void *)((u8 *)var_v0 + 0x18C);
    }
}

extern u32 D_87E1ABC4;
extern void func_87E126D4(s32, void *, s32, s32, s32);
void func_87E127FC(s32 arg0) {
    func_87E126D4(arg0, &D_87E1ABC4, 0, 30, 4096);
}

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

extern void func_87F0B1A4(u8 *, u8 *, f32, s32, f32, s32, s32);
void func_87E12AA0(void *arg0, s32 arg1, void *arg2) {
    s32 sp2C;
    void *sp28;

    func_87E127B8(arg0, arg1 + 4, (void **)&sp2C, (void **)&sp28);
    if (sp2C != 0) {
        *(f32 *)((u8 *)sp2C + 0x50) = 1000.0f;
        func_87F0B1A4((u8 *)((u8 *)sp28 + 0xC),
            (u8 *)((u8 *)sp2C + 0x48),
            *(f32 *)((u8 *)arg2 + 0x48),
            *(s32 *)((u8 *)arg2 + 0x4C),
            *(f32 *)((u8 *)arg2 + 0x50) + 20.0f,
            (arg1 * 5) + 0xA,
            0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_315A90/func_87E12B34.s")

extern u32 D_87E1AB64;
void func_87E12BE8(s32 arg0) {
    func_87E126D4(arg0, &D_87E1AB64, 0, 15, 8192);
}

void func_87E12C1C(s32 arg0) {
    func_87E126D4(arg0, &D_87E1AB64, 2, 15, 8192);
}

void func_87E12C50(s32 arg0) {
    func_87E126D4(arg0, &D_87E1AB64, 1, 15, 8192);
}

void func_87E12C84(s32 arg0) {
    func_87E126D4(arg0, &D_87E1AB64, 3, 15, 8192);
}

void func_87E12CB8(s32 arg0) {
    s32 i;
    for (i = 0; i != 8; ++i) {
        func_87E126D4(arg0, &D_87E1AB64, i, 30, 8192);
    }
}

extern void func_87F02684(s32);
void func_87E12D28(s32 arg0) {
    func_87F02684((arg0 + 4));
}

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

extern void func_87E12D80(void);
extern void *func_87F025B8(void *, void (*)(void));
extern void func_8003F1DC(void *);
extern void func_8003F114(void *, s32, s32, s32);
void func_87E131D8(void *arg0) {
    void *temp_v0;
    void *temp_a0;

    temp_v0 = func_87F025B8((u8 *)arg0 + 0x2C, func_87E12D80);
    temp_a0 = (void *)((u8 *)temp_v0 + 0x24);
    if (temp_v0 != 0) {
        func_8003F1DC(temp_a0);
        func_8003F114(temp_a0, 0, -1, *(s32 *)((u8 *)arg0 + 0x254));
        *(void **)((u8 *)temp_v0 + 0x38) = arg0;
        *(u8 *)((u8 *)temp_v0 + 0x25) &= 0xFFFE;
    }
}

void func_87E13248(void) {
    func_8004C8C0(361);
}

extern s32 D_87E1ACA0;
extern s32 func_8004C990(s32, s32);
extern s32 func_87F08E3C(s32, s32);
extern void func_87F0252C(void *, void *, void *, s32);
extern void func_87E131D8(void *arg0);
typedef struct Func87E13268_State {
    u8 pad0[0x254];
    s32 field254;
    s32 field258;
    s32 field25C;
    s32 field260;
    s32 field264;
} Func87E13268_State;

void func_87E13268(Func87E13268_State *arg0) {
    s32 sp24;
    s32 temp_v0;
    extern u8 D_87E1EBC0;
    extern s32 func_80040E80(s32, s32 *);
    extern s32 MainPool_AllocState(s32, s32);
    extern s32 main_pool_get_available(void);
    extern void MainPool_FinalizeAllocation(s32);

    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    sp24 = temp_v0;
    arg0->field254 = func_80040E80(temp_v0, &D_87E1ACA0);
    MainPool_FinalizeAllocation(sp24);
    arg0->field258 = func_8004C990(0x169, 1);
    arg0->field25C = func_8004C990(0x169, 2);
    arg0->field260 = func_87F08E3C(arg0->field258, 0x0F000000);
    arg0->field264 = func_87F08E3C(arg0->field25C, 0x0F000000);
    func_87F0252C(&D_87E1EBC0, (u8 *)arg0 + 0x2C, (u8 *)arg0 + 0x40, 1);
    func_87E131D8(arg0);
}

s32 func_80040E80(s32, s32 *);
extern u8 D_87E1AC40;
extern u8 D_87E1EBC0;
extern void func_80037E9C(s32, void *);
extern s32 MainPool_AllocState(s32, s32);
s32 main_pool_get_available(void);
extern void MainPool_FinalizeAllocation(s32);
void func_87E1331C(void *arg0) {
    s32 sp1C;
    s32 temp_v0;

    func_80037E9C(0, &D_87E1EBC0);
    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    sp1C = temp_v0;
    (*(s32 *)((u8 *)(arg0) + (0x28))) = func_80040E80(temp_v0, &D_87E1AC40);
    MainPool_FinalizeAllocation(sp1C);
}

extern u8 *D_87E1EBD8;
extern void func_87E13248(void);
extern void func_87E1331C(void *arg0);
void func_87E13380(void *arg0) {
    D_87E1EBD8 = arg0;
    *(s32 *)((u8 *)arg0 + 0x00) = 4;
    *(s32 *)((u8 *)arg0 + 0x04) = 0;
    *(s32 *)((u8 *)arg0 + 0x0C) = 0;
    *(s32 *)((u8 *)arg0 + 0x268) = 0;
    *(s32 *)((u8 *)arg0 + 0x08) = 6;
    *(f32 *)((u8 *)arg0 + 0x18) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x14) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x10) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x24) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x20) = 0.0f;
    *(f32 *)((u8 *)arg0 + 0x1C) = 0.0f;
    func_87E13248();
    func_87E1331C(arg0);
    func_87E13268(arg0);
}

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

extern void func_8003C6B8(s32);
void func_87E13458(void) {
    func_8003C6B8(*(s32*)(D_87E1EBD8 + 0x28));
}

void func_87E13480(u8 *arg0) { extern u8 *D_87E1EBD8; *(u8 **)(D_87E1EBD8 + 4) = arg0; }

void func_87E13490(void) {
    *(u32 *)D_87E1EBD8 |= 1;
    *(u32 *)D_87E1EBD8 &= 0xFFFFFFFD;
}

void func_87E134C0(void) {
    *(u32 *)D_87E1EBD8 &= 0xFFFFFFFE;
    *(u32 *)(D_87E1EBD8 + 0xC) = 0;
}

extern void func_87F0B1A4(u8 *, u8 *, f32, s32, f32, s32, s32);
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
