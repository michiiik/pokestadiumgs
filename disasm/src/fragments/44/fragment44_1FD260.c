#include "global.h"


#ifdef VERSION_US
extern void func_8004A858(s32, s32, u16, u16, s32 *, s32 *);
extern u8 D_8AF26450;
extern u8 D_8AF26454;
s32 func_8AF0EFF0(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0x18)));
    func_8004A858(0, 0, (*(u16 *)((u8 *)(temp_v0) + (4))), (*(u16 *)((u8 *)(temp_v0) + (6))), &D_8AF26450, &D_8AF26454);
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF0F040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF0F1A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF0F220.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF0F2EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1000C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1025C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF102AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1043C.s")

extern void func_80043E70(s32, s32);
extern s32 D_8AF26A44;

void func_8AF10540(void) {
    if (D_8AF26A44 != 0) {
        func_80043E70(D_8AF26A44, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1060C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF106A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10784.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10840.s")

extern void *D_8AF3011C;
extern void *D_8AF30120;
extern void *D_8AF30124;
extern void *D_8AF30128;
extern void *D_8AF3012C;
extern void *D_8AF30130;
void func_8AF108BC(void) {
    (*(u16 *)((u8 *)(D_8AF3011C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3011C) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30128) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30128) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30120) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30120) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF3012C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3012C) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30124) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30124) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30130) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30130) + (2))) | 2);
}

void func_8AF10938(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x28) = arg1;
    *(s32 *)(arg0 + 0x2C) = arg2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10944.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10AB8.s")

extern s16 D_8AF300C4;
extern s16 D_8AF30FF8;
extern s16 D_8AF30FFA;
extern s16 D_8AF30FFC;
extern s16 D_8AF30FFE;
extern s16 D_8AF31000;

void func_8AF10CD4(void) {
    D_8AF31000 = 0;
    D_8AF30FF8 = 0;
    D_8AF30FFC = 0;
    D_8AF30FFA = 0;
    D_8AF30FFE = 0;
    D_8AF300C4 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10D08.s")

void func_8AF11358(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (arg1 < value) {
        value -= arg2;
        if (value < arg1) value = arg1;
        *arg0 = value;
    }
}

void func_8AF11398(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (value < arg1) {
        value += arg2;
        if (arg1 < value) value = arg1;
        *arg0 = value;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF113D8.s")

extern void func_800498C4(void);
extern void func_800499EC(void);
void func_8AF12398(void) {
    func_800498C4();
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF123C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF12410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF124A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF125D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1271C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF127E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF129F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF12A4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF12E30.s")

extern void _bzero(s32 *, s32);
extern s32 D_8AF26F30;
extern s16 D_8AF316A4;
extern s16 D_8AF316A6;
extern u8 D_8AF316B8;

void func_8AF12E7C(void) {
    D_8AF316A4 = 0;
    D_8AF316A6 = 0;
    _bzero(&D_8AF316B8, 0xE);
    D_8AF26F30 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF12EB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF133C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF13718.s")
#endif
