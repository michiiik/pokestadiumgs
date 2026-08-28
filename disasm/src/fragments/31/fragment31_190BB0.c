#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821D930.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821DA70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821DAC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821DC48.s")

extern u32 D_882347F0;
extern void func_8821E0BC(void);
void func_8821DE04(void) {
    if ((*(s32 *)((u8 *)(D_882347F0) + 0)) == 0) {
        func_8821E0BC();
        return;
    }
    (*(s32 *)((u8 *)(D_882347F0) + 4)) = 1;
    (*(s32 *)((u8 *)(*(void **)((u8 *)(D_882347F0) + 8)) + 0x2C)) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821DE58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821E0BC.s")

extern void func_88216EFC(s32);
extern s32 D_880068B4;
extern s8 D_889041B8;

void func_8821E13C(s32 arg0) {
    D_880068B4 = 0;
    D_889041B8 = 2;
    if (arg0 == 0) {
        func_88216EFC(0);
    }
}

extern u32 D_882347F0;
extern void func_8821DE58(void);
extern void func_88001900(void);
extern s32 D_889041B4;
void func_8821E174(s32 arg0) {
    D_889041B4 = 0;
    (*(s32 *)((u8 *)(*(void **)((u8 *)(D_882347F0) + 8)) + 0x2C)) = 1;
    (*(s32 *)((u8 *)(*(void **)((u8 *)(D_882347F0) + 8)) + 0x30)) = 1;
    (*(s32 *)((u8 *)(*(void **)((u8 *)(D_882347F0) + 8)) + 0x34)) = 1;
    if (arg0 != 0) {
        func_8821DE58();
        return;
    }
    (*(s32 *)((u8 *)(D_882347F0) + 4)) = 1;
    func_88001900();
}

extern void func_88004990(u8, s32);
extern u32 D_882347F0;
extern s32 D_880068B8;
void func_8821E1E4(void) {
    func_88004990(*(*(u8 **)((u8 *)(D_882347F0) + (8))), 0);
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821E21C.s")

extern void *D_80087200;
extern void Input_SetRepeatController(void *);
void func_8821E490(void) { Input_SetRepeatController(D_80087200); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821E4B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821E5F8.s")

extern void func_889033FC(void *arg0, void *arg1);
void func_8821E710(void) {
    func_889033FC((*(void **)((u8 *)(D_882347F0) + (0x14))), D_882347F0 + 0x18);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821E73C.s")

void func_8821E8C8(void) { Input_SetRepeatController(D_80087200); }

extern u32 D_882347F0;
extern void func_8821E0BC(void);
void func_8821E8EC(void) {
    s32 state_mode;

    if ((*(s32 *)((u8 *)(D_882347F0) + 0x68) != 0) &&
        ((state_mode = *(s32 *)((u8 *)(D_882347F0) + 4), (state_mode == 3) || (state_mode == 4)))) {
        if (*(s32 *)((u8 *)(D_882347F0) + 0) == 0) {
            func_8821E0BC();
            return;
        }
        (*(s32 *)((u8 *)(D_882347F0) + 4)) = 1;
        (*(s32 *)((u8 *)(*(void **)((u8 *)(D_882347F0) + 8)) + 0x2C)) = 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821E964.s")

extern void func_889035FC(s32);
void func_8821EAD8(void) { func_889035FC((D_882347F0 + 88)); }

extern u32 D_882347F0;
extern s32 D_882345F4;
extern u8 D_8800ED50[];
extern void func_889035A0(void *, void *, s16, s16);
extern s32 func_88004804(s32,s32,s16,s16,s32,s32,s32,s32,s32,
                          void (*)(void),void (*)(void),void (*)(void),
                          void (*)(void),s32,s32);
extern void func_8821E964(void);
extern void func_8821EAD8(void);
extern void func_8821E8C8(void);
extern void func_8821E8EC(void);
void func_8821EB00(void) {
    u32 *global;
    s32 result;

    func_889035A0((void *)((u8 *)(D_882347F0) + 0x58),
                  (void *)((u8 *)(D_882345F4) + 8), 0x3D, 9);
    result = func_88004804(0, 3, 0x190, 0xA1, 0, 1, 0xDC, 0xDC, 0xB4,
                           func_8821E964, func_8821EAD8,
                           func_8821E8C8, func_8821E8EC, 0, 1);
    global = &D_882347F0;
    (*(void **)((u8 *)(*global) + 0x58)) = D_8800ED50 + (result * 0x4C);
    (*(s16 *)((u8 *)(*(void **)((u8 *)(*global) + 0x58)) + 0x10)) = 0xBE;
    (*(s16 *)((u8 *)(*(void **)((u8 *)(*global) + 0x58)) + 0x12)) = 0xC5;
    (*(s32 *)((u8 *)(*(void **)((u8 *)(*global) + 8)) + 0x2C)) = 0;
}

extern void func_88001900(void);
void func_8821EC10(void) {
    func_88001900();
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821EC34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821EE00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821F01C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821FFB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_88220050.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_88220248.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_882202E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_88220400.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_882204F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_882206A0.s")
#endif
