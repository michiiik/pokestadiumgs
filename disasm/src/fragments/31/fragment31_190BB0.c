#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821D930.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821DA70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821DAC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821DC48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821DE04.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821E174.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821E8EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821E964.s")

extern void func_889035FC(s32);
void func_8821EAD8(void) { func_889035FC((D_882347F0 + 88)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_190BB0/func_8821EB00.s")

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
