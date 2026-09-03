#include "global.h"


#ifdef VERSION_US
extern void Util_Free(s32);
extern void func_8821CE40(s32);
extern void main_pool_pop_state(s32);
extern s32 D_88234560;
extern s32 D_88234564;

void func_8820C000(void) {
    Util_Free(D_88234564);
    main_pool_pop_state(0x41525249);
    func_8821CE40(3);
    D_88234560 = 5;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C114.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C258.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C65C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C798.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C800.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C8A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C94C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CA50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CAE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CB74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CCA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CE2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CF8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820E450.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820E580.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820E6A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820E9BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820EB14.s")

extern u8 func_8006378C(u8);
extern void *Color_SetRGB(void *, u8, u8, u8);
extern void func_880006E0(void *);
extern u8 D_88005FA0[];
void func_8820ECE8(u8 arg0, u8 *arg1) {
    u8 sp1C[4];

    if (arg0 == func_8006378C(*arg1)) {
        func_880006E0(D_88005FA0);
        return;
    }
    func_880006E0(Color_SetRGB(sp1C, 0x96, 0x96, 0x96));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820ED44.s")

extern s32 func_88202158(u8 *, s32);
extern void func_800496A4(s32, s32);
extern void func_800495F8(s32, s32, s32, void *, s32);
extern u8 D_88233F50[];
extern void *D_8800687C;
extern void *func_88A00938(u8 *);
extern void func_80048E30(void *, s16, s16, void *, s32);
void func_8820F74C(s16 arg0, s16 arg1, u8 *arg2, u8 arg3) {
    if (func_88202158(arg2, 1) == 0) {
        func_800496A4(4, 1);
        func_800495F8((s32)arg0 + 0xD3, (s32)arg1 + 4, 2, D_88233F50, (s32)arg3);
    }
    func_800496A4(8, 2);
    func_80048E30(D_8800687C, arg0, arg1, func_88A00938(arg2), 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820F7EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820FC78.s")

extern void func_8820FC78();
void func_8820FD58(void) { func_8820FC78(0); func_8820FC78(1); }

extern void func_80049064(s32, s32, s32, s32);
extern void func_800496A4(s32, s32);
s32 func_8004C874(s32, s16);
extern void *D_88234710;

void func_8820FD80(void) {
    func_800496A4(4, 2);
    func_80049064(0x140, 0x1A4, 1, func_8004C874(0x21, 0x1F));
    func_800496A4(0x10, 2);
    func_80049064(0x140, 0x183, 1, func_8004C874(0x21, (*(s16 *)((u8 *)(D_88234710) + (8)))));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820FDF8.s")
#endif
