#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(void *);
extern void *D_80087200;
extern s32 D_880068B8;

void func_882243C0(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void Util_Free(s32);
extern s32 D_880068B4;
extern u32 D_88234860;
void func_882243E8(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B4 = 1;
    Util_Free(D_88234860);
}

extern void func_88004990(u8, s32);
extern u32 D_88234860;
void func_88224424(void) {
    func_88004990(*(*(u8 **)((u8 *)(D_88234860) + 0)), 0);
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_8822445C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_882244B0.s")

extern void func_880022B4(s32, s32, s32);
void func_882244F8(s32 arg0) {
    (*(s32 *)((u8 *)(D_88234860) + (0x30))) = arg0;
    if (arg0 != 0) {
        func_880022B4(D_88234860 + 4, 0xF00, 0);
        return;
    }
    func_880022B4(D_88234860 + 4, 0xF00, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88224554.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88224688.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_882246FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_8822497C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_882254B8.s")

void func_88225B70(void) {
    D_880068B8 = 0;
}

extern u8 D_8823474C;
void func_88225B7C(void) { D_880068B8 = 1; D_8823474C = 2; }

extern void func_888002DC(void);
void func_88225B98(void) { D_880068B4 = 1; func_888002DC(); }

extern void func_88800020();
s32 func_88802DCC(s32, s32, void (*)(), void (*)(), void (*)(), s32 *, s32, s32);
extern u8 func_882313A4;

void func_88225BC0(s32 arg0) {
    func_88800020();
    func_88802DCC(0, arg0, func_88225B70, func_88225B98, func_88225B7C, &func_882313A4, 2, 0);
}

void func_88225C20(void) { Input_SetRepeatController(D_80087200); D_880068B8 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88225C48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88225D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88225EA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88225EEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88225F38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88225FA8.s")

void func_88226058(u8 *arg0, u8 arg1) { arg0[1] = arg1 ? 1 : -1; }

void func_88226080(void *arg0) {
    s8 temp_v0;
    s8 temp_v0_2;
    s8 temp_v0_3;

    temp_v0 = (*(s8 *)((u8 *)(arg0) + (1)));
    if (temp_v0 > 0) {
        (*(s8 *)((u8 *)(arg0) + (0))) = (s8) ((*(s8 *)((u8 *)(arg0) + (0))) + 1);
        temp_v0_2 = (*(s8 *)((u8 *)(arg0) + (0)));
        if (temp_v0_2 == 0) {
            (*(s8 *)((u8 *)(arg0) + (1))) = 0;
            return;
        }
        if (temp_v0_2 == 2) {
            (*(s8 *)((u8 *)(arg0) + (1))) = -1;
        }
    } else if (temp_v0 < 0) {
        (*(s8 *)((u8 *)(arg0) + (0))) = (s8) ((*(s8 *)((u8 *)(arg0) + (0))) - 1);
        temp_v0_3 = (*(s8 *)((u8 *)(arg0) + (0)));
        if (temp_v0_3 == 0) {
            (*(s8 *)((u8 *)(arg0) + (1))) = 0;
            return;
        }
        if (temp_v0_3 == -2) {
            (*(s8 *)((u8 *)(arg0) + (1))) = 1;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88226100.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_882261CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88226378.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88226918.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88227224.s")

void func_882277D0(void) { Input_SetRepeatController(D_80087200); D_880068B8 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_882277F8.s")

extern void func_88001900();
extern void func_882277F8();
extern void *D_88234880;

void func_882278EC(void) {
    func_88001900();
    D_880068B4 = (*(s32 *)((u8 *)(D_88234880) + (0x64)));
    func_882277F8();
}

extern void func_88004990(u8, s32);
void func_88227924(void) {
    func_88004990(*(*(u8 **)((u8 *)(D_88234880) + (0))), 0);
    func_88004990(*(*(u8 **)((u8 *)(D_88234880) + (4))), 0);
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88227974.s")

extern void func_800226C0(s32);
extern void func_882017F8(s32, void *, s8);
extern void func_88227924();
extern void func_882310A0();
extern s32 D_882345F4;
extern s8 D_88234746;
void func_88227A04(void *arg0) {
    func_800226C0(0x5D);
    func_800226C0(0x63);
    D_88234746 = 0;
    func_882310A0();
    func_882017F8(D_882345F4, arg0, (*(s8 *)((u8 *)(arg0) + (0x15))));
    (*(s32 *)((u8 *)(D_88234880) + (0x64))) = 0;
    func_88227924();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88227A60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88227EE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_197640/func_88228390.s")
#endif
