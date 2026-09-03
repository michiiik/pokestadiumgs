#include "global.h"


#ifdef VERSION_US
extern void *D_87E1EB90;
s32 func_87E05400(u32 arg0) {
    s32 var_v1;
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(D_87E1EB90) + (0x158)));
    var_v1 = (*(s32 *)((u8 *)(temp_v0) + (0x98))) == 0;
    if ((arg0 >= 2U) && (var_v1 == 0) && ((u32) (*(u32 *)((u8 *)(temp_v0) + (0x80))) >= (u32) ((u32) (*(u32 *)((u8 *)(temp_v0) + (0x84))) / arg0))) {
        var_v1 = 1;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E05458.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E055B0.s")

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84();
void func_87E05874(s32 arg0, s32 arg1) {
    u8 *context;
    void *temp_v0;

    if (arg0 == 5) {
        context = (u8 *)D_8009491C;
        temp_v0 = *(void **)(context + 0x14);
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
        gSPSegment(D_800D0510++, 0xF,
                   func_8004CA60(*(u8 **)((u8 *)temp_v0 + 0xC)));
        gSPDisplayList(D_800D0510++, *(void **)((u8 *)temp_v0 + 0x10));
        func_8003CD84();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E05944.s")

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern void func_8003CD84();
void func_87E059F4(s32 arg0, s32 arg1) {
    u8 *context;
    void *temp_v0;
    void *temp_a0;
    if (arg0 == 5) {
        context = (u8 *)D_8009491C;
        temp_v0 = *(void **)(context + 0x14);
        temp_a0 = *(void **)((u8 *)temp_v0 + 0x20);
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
        gSPSegment(D_800D0510++, 0xF,
                   *(void **)((u8 *)(*(void **)((u8 *)temp_a0 + 4)) + 8));
        gSPDisplayList(D_800D0510++, *(void **)temp_a0);
        func_8003CD84(temp_a0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E05AB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E05BF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E05CE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E05D74.s")

extern void func_87F0252C(u8 *, s32, s32, s32);
extern u8 D_80126420;
void func_87F024CC(void);
extern u8 D_87E1B9C0;
s32 main_pool_alloc(s32 arg0, s32 arg1);
extern u8 D_87E1B9D8;
void func_87F024CC(void);
s32 main_pool_alloc(s32 arg0, s32 arg1);
void func_87E06068(s32 arg0) {
    func_87F024CC();
    func_87F0252C(&D_87E1B9C0, arg0 + 0x18, main_pool_alloc(0x141C, 0), 0xD);
    func_87F0252C(&D_80126420, arg0 + 0x2C, main_pool_alloc(0x318, 0), 2);
    func_87F0252C(&D_87E1B9D8, arg0 + 0x40, main_pool_alloc(0x318, 0), 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06100.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E0664C.s")

u32 func_87E067F0(s32 arg0, s32 arg1) {
    extern u32 D_87E19B4C[];
    return D_87E19B4C[arg0];
}

extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern void func_80007328(Gfx **, s32);
extern void GfxImage_FillCurrent(Gfx **, u16);
extern s32 func_8004C990(s32, s32);
extern void func_8004D19C(s32, s32, s32, s32, s32);
void func_87E06808(s32 arg0) {
    u8 *var_s1;
    s32 var_s2;

    var_s1 = *(u8 **)((u8 *)arg0 + 0x150);
    for (var_s2 = 0; var_s2 != 0xC; var_s2 += 1, var_s1 += 0x9C) {
        func_80007328(&D_800D0510, *(s32 *)(var_s1 + 0x90));
        GfxImage_FillCurrent(&D_800D0510, 0xFFFE);
        gSPDisplayList(D_800D0510++, D_80094E38);
        gDPSetRenderMode(D_800D0510++, 0x0F0A7008, 0);
        func_8004D19C(0, 0, func_8004C990(0x172, func_87E067F0(var_s2, *(s32 *)(var_s1 + 0x88))), 0, 0);
    }
}

extern void func_8004C8C0(s32);
void func_87E06908(s32 arg0) {
    func_8004C8C0(0x18B);
    func_8004C8C0(0x177);
    func_8004C8C0(0x176);
    func_8004C8C0(0x17F);
    func_8004C8C0(0x184);
    func_8004C8C0(0x193);
    func_8004C8C0(0x18C);
    func_8004C8C0(0x190);
    func_8004C8C0(0x195);
    func_8004C8C0(0x198);
    func_8004C8C0(0x19B);
    func_8004C8C0(0x1A1);
    func_8004C8C0(0x172);
    func_8004C8C0(0x1BF);
    func_8004C8C0(0x169);
    func_8004C8C0(0x1B2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E069A4.s")

s32 func_800071A4(s32, s32, s32, s32, s32);

void func_87E06B18(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + (0x5C))) = func_800071A4(0, 2, 0x102, 0x17, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06B54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06BCC.s")

extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(s32);
extern s32 func_80040E80(s32, void *);
extern u8 D_87E19B18;
extern s32 func_87F08E3C(s32, s32);
extern s32 func_87F08DF8(s32, s32, s32, s32);
extern s32 func_8004C990(s32, s32);
void func_87E06CB4(void *arg0) {
    s32 state;

    state = MainPool_AllocState(main_pool_get_available(), 0);
    *(s32 *)((u8 *)arg0 + 0x168) = func_80040E80(state, &D_87E19B18);
    MainPool_FinalizeAllocation(state);
    state = main_pool_alloc(0x138, 0);
    *(s32 *)((u8 *)arg0 + 0x158) = state;
    *(s32 *)(state + 0) = 0;
    *(s32 *)(state + 0xC) = func_8004C990(0x1B2, 1);
    *(s32 *)(state + 0x10) = func_87F08E3C(*(s32 *)(state + 0xC), 0x0F000000);
    state = *(s32 *)((u8 *)arg0 + 0x158);
    state += 0x9C;
    *(s32 *)(state + 0) = 1;
    *(s32 *)(state + 0xC) = func_8004C990(0x169, 0);
    *(s32 *)(state + 0x10) = func_87F08DF8(*(s32 *)(state + 0xC), 0x41000000, 0xC1180000, 0x0F000000);
}

void func_87E06D84(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06D8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06EC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E07040.s")

extern void func_87E07040(s32, void *, s32);
extern void func_87F0B24C(s32, u8 *, f32, f32, f32, s32, s32);
void func_87E07194(void *arg0) {
    u8 *var_s0;
    s32 temp_v0;
    f32 temp_f0;

    var_s0 = *(u8 **)((u8 *)arg0 + 0x24);
    if (var_s0 != NULL) {
        do {
            temp_v0 = *(s32 *)(var_s0 + 0xC);
            if (temp_v0 & 0x20000000) {
                func_87E07040(*(s32 *)(var_s0 + 0x20), var_s0, 0xF);
            } else if (temp_v0 & 0x10000000) {
                func_87E07040(*(s32 *)(var_s0 + 0x20) + 8, var_s0, 0xF);
            }
            var_s0 = *(u8 **)(var_s0 + 4);
        } while (var_s0 != NULL);
    }
    var_s0 = *(u8 **)((u8 *)arg0 + 0x38);
    if (var_s0 != NULL) {
        temp_f0 = 0.0f;
        do {
            func_87F0B24C(*(s32 *)(var_s0 + 0x20) + 8,
                          var_s0 + 0x54, 0.0f, 0.0f, temp_f0, 0xF, 0);
            var_s0 = *(u8 **)(var_s0 + 4);
        } while (var_s0 != NULL);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E07278.s")

void func_87E072FC(void *a, u16 b) {
    u8 *p;
    p = *(u8 **)((u8 *)a + 368);
    *(u16 *)(p + 8692) |= b;
    p = *(u8 **)((u8 *)a + 368);
    if (*(u16 *)(p + 8692) == 0xFFF)
        *(u16 *)(p + 8692) = 0;
}

extern void func_87E0168C(s32, s32, s32);
extern void func_87E06EC0();

void func_87E07330(void *arg0) {
    func_87E06EC0();
    (*(s32 *)((u8 *)(arg0) + (4))) = 2;
    func_87E0168C(0, 0x64, -1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E0736C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E074BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E076E0.s")

extern s32 func_87E06E48(void *);
extern void func_87E0736C(void *);
extern void func_87E076E0(void *);
extern void func_87F0277C(void *);
s32 func_87E078DC(s32 arg0) {
    s32 temp_v0;
    s32 sp20;

    sp20 = 2;
    D_87E1EB90 = arg0;
    func_87F0277C(arg0 + 0x18);
    func_87F0277C(arg0 + 0x2C);
    func_87F0277C(arg0 + 0x40);
    temp_v0 = *(s32 *)(arg0 + 4);
    switch (temp_v0) {
    case 0:
        if (func_87E06E48((void *)arg0) != 0) *(s32 *)(arg0 + 4) = 1;
        break;
    case 1: {
        s32 temp_v0_2;
        temp_v0_2 = *(s32 *)(arg0 + 0x174);
        switch (temp_v0_2) {
        case 0:
            func_87E0736C((void *)arg0);
            break;
        case 1:
            func_87E076E0((void *)arg0);
            break;
        }
        break;
    }
    case 2:
        if (func_87E06E48((void *)arg0) != 0) {
            sp20 = 0;
            *(u8 *)(*(s32 *)(arg0 + 0x170) + 0x2183) = *(s32 *)(arg0 + 8);
        }
        break;
    case 3:
        if (func_87E06E48((void *)arg0) != 0) {
            sp20 = 1;
            *(u8 *)(*(s32 *)(arg0 + 0x170) + 0x2183) = *(s32 *)(arg0 + 8);
        }
        break;
    }
    *(s32 *)(arg0 + 0) = *(s32 *)(arg0 + 0) + 1;
    return sp20;
}

extern void func_800088DC();
extern void func_87E0664C();
extern void func_87E06808(s32);

void func_87E079FC(s32 arg0) {
    func_87E0664C();
    func_87E06808(arg0);
    func_800088DC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E07A2C.s")

extern void func_87E06290(u8 *);
extern s32 func_87E07A2C(u8 *);
extern u32 func_8003570C(void);
void func_87E07AC4(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0) = 0;
    *(s32 *)(arg0 + 8) = (s32)*(s8 *)((u8 *)*(void **)(arg0 + 0x170) + 0x2183);
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 0x188) = 0;
    *(s32 *)(arg0 + 0x17C) = 0;
    *(s32 *)(arg0 + 0x180) = 0;
    *(s32 *)(arg0 + 0x184) = (func_8003570C() % 13U) + 6;
    *(s32 *)(arg0 + 0x178) = arg1;
    *(s32 *)(arg0 + 0xC) = func_87E07A2C(arg0);
    if (*(u8 *)((u8 *)*(void **)(arg0 + 0x170) + 0x2180) == 0) {
        *(s32 *)(arg0 + 0x174) = 1;
    } else if (*(s8 *)((u8 *)*(void **)(arg0 + 0x170) + 0x218F) == 0) {
        *(s32 *)(arg0 + 0x174) = 0;
    } else {
        *(s32 *)(arg0 + 0x174) = 1;
    }
    func_87E06290(arg0);
}

extern void func_87F02684(s32);
extern void func_87E01628(void);
extern void main_pool_pop_state(s32);
void func_87E07B74(s32 arg0) {
    func_87F02684(arg0 + 0x18);
    func_87F02684(arg0 + 0x2C);
    func_87F02684(arg0 + 0x40);
    func_87E01628();
    main_pool_pop_state(0x4D474753);
}
#endif
