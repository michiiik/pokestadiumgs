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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E05874.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E05944.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E059F4.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06808.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06CB4.s")

void func_87E06D84(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06D8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E06EC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E07040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E07194.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E078DC.s")

extern void func_800088DC();
extern void func_87E0664C();
extern void func_87E06808(s32);

void func_87E079FC(s32 arg0) {
    func_87E0664C();
    func_87E06808(arg0);
    func_800088DC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E07A2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_308D70/func_87E07AC4.s")

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
