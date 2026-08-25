#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_8822E950.s")

extern void func_800033DC(void *);
extern void main_pool_pop_state(s32);
extern u8 **D_88234970;
void func_8822EA80(void) {
    func_800033DC(*(volatile void **)(&D_88234970));
    main_pool_pop_state(0x50495550);
}

extern u8 **D_88234970;

void func_8822EAB0(void) {
    *(u32 *)(*D_88234970 + 0x30) = 0;
}


void func_8822EAC4(void) {
    *(u32 *)(*D_88234970 + 0x30) = 1;
}

extern void func_8000612C();

void func_8822EADC(void) {
    func_8000612C();
    (*(s32 *)((u8 *)(*D_88234970) + (0x2C))) = 1;
}

s32 func_88802DCC(s32, s32, void (*)(), void (*)(), void (*)(), s32 *, s32, s32);
extern u8 func_882313A4;

void func_8822EB10(s32 arg0) {
    func_88802DCC(0, arg0, func_8822EAB0, func_8822EADC, func_8822EAC4, &func_882313A4, 0, 1);
    (*(s32 *)((u8 *)(*D_88234970) + (0x2C))) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_8822EB78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_8822EDA8.s")

extern void func_8000612C();
extern s32 D_880068B8;

void func_8822FA0C(void) {
    func_8000612C();
    D_880068B8 = 0;
}

extern void func_88001900();
extern s32 D_880068B4;

void func_8822FA30(void) {
    func_88001900();
    D_880068B4 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_8822FA58.s")

extern void func_80049ED8(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_8822FF80(void) {
    func_80049ED8(D_80087200);
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_8822FFA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_88230010.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_88230048.s")

extern u32 D_88234980;
extern void func_8821D930(s32);
void func_882300E4(void) { func_8821D930(D_88234980 + 4); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A1BD0/func_8823010C.s")
#endif
