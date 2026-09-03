#include "global.h"


#ifdef VERSION_US
extern void Util_Free(s32);
extern void func_8821CE40(s32);
extern void func_8822EA80();
extern void func_888002DC();
extern void main_pool_pop_state(s32);
extern s32 D_88234560;
extern s32 D_88234564;
extern s32 D_88234720;
void func_88210480(void) {
    Util_Free(D_88234564);
    Util_Free(D_88234720);
    func_8822EA80();
    func_888002DC();
    main_pool_pop_state(0x41525242);
    func_8821CE40(2);
    D_88234560 = 5;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_882104DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_882105B0.s")

extern s32 func_880007B0(u8 *);
extern s32 func_80063754(s32);
extern s32 D_88A01C30;
s32 func_88210D48(void *arg0) {
    s32 result;
    s32 *ptr;
    u32 i;

    result = 0;
    ptr = *(s32 **)((u8 *)arg0 + 0x10);
    i = 0;
    if (*(u8 *)((u8 *)arg0 + 0x15) != 0) {
        do {
            if (func_880007B0((u8 *)(*ptr + 8)) == 0) {
                result = 1;
                break;
            }
            i += 1;
            ptr += 1;
        } while (i < *(u8 *)((u8 *)arg0 + 0x15));
    }
    return result;
}

s32 func_88210DC4(void *arg0) {
    s32 result;
    u8 **ptr;
    u32 i;

    result = 0;
    ptr = *(u8 ***)((u8 *)arg0 + 0x10);
    i = 0;
    if (*(u8 *)((u8 *)arg0 + 0x15) != 0) {
        do {
            if (func_80063754((*ptr)[9]) != 0) {
                result = 1;
                break;
            }
            i += 1;
            ptr += 1;
        } while (i < *(u8 *)((u8 *)arg0 + 0x15));
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_88210E40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_88210ECC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_88210FAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_88211018.s")

extern u8 *func_800534FC(s32);
extern s8 *HAL_Strcpy(s8 *, s8 *);
extern s32 func_8004C594(s32, s32);
extern s32 func_8004C8A0(void *, s32, s32, s32);
void *func_88211084(void *arg0, void *arg1) {
    if ((*(u8 **)((u8 *)arg0 + 0))[8] == 2) {
        HAL_Strcpy((s8 *)arg1, (s8 *)func_800534FC(*(u8 *)((u8 *)arg0 + 4)));
    } else {
        func_8004C594(2, *(u8 *)((u8 *)arg0 + 4) + 1);
        func_8004C8A0(arg1, 0x40, 0x41, 0);
    }
    return arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_882110FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_88211168.s")

extern void func_800226C0(s32);
extern s32 D_88234724;
void func_88001900(void);
extern s32 D_882346F0;
void func_882114EC(void) {
    s16 temp_v1;

    func_800226C0(0x5E);
    func_88001900();
    D_882346F0 = 0;
    D_88234724 = 0;
    temp_v1 = (*(s16 *)((u8 *)(D_88234720) + (8)));
    if ((temp_v1 == 1) || (temp_v1 == 3)) {
        (*(u8 *)((u8 *)(D_88234720) + (0))) = (u8) ((*(u8 *)((u8 *)(D_88234720) + (0))) ^ 1);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_88211550.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_88212440.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_882125C0.s")

extern void func_80047634(s32);
extern void func_80047650(s32);
extern void func_80048E30(s32, s16, s16, s32, s32);
extern void func_800496A4(s32, s32);
extern s32 D_8800687C;
void func_882129DC(s16 arg0, s16 arg1, s32 arg2) {
    func_800496A4(8, 2);
    func_80047634(1);
    func_80048E30(D_8800687C, arg0, arg1, arg2, 1);
    func_80047650(1);
}

extern void func_800495F8(s32, s32, s32, s32 *, s32);
extern u8 D_88233F60;
void func_88212A3C(s16 arg0, s16 arg1, u8 arg2) {
    func_800496A4(4, 1);
    func_800495F8(arg0 + 0xD3, arg1 + 4, 2, &D_88233F60, (s32) arg2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_88212A94.s")

extern s16 D_8800EF58;
extern s32 func_8004C874(s32, s32);
extern void func_80049064(s32, s32, s32, s32);
extern void func_80048E30(s32, s16, s16, s32, s32);
extern void func_800496A4(s32, s32);
void func_88212E00(void) {
    if (D_8800EF58 == 0 && D_882346F0 == 0) {
        func_800496A4(4, 2);
        func_80049064(0x247, 0x1A4, 2, func_8004C874(0x22, 0x17));
    }
    func_800496A4(0x10, 2);
    func_80048E30(D_8800687C, 0x39, 0x19C, func_8004C874(0x22, *(s16 *)((u8 *)D_88234720 + 8)), 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_183700/func_88212EA0.s")
#endif
