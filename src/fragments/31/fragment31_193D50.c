#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_193D50/func_88220AD0.s")

extern void func_88004990(u8, s32);
extern u8 **D_88234800;
extern s32 D_880068B8;
void func_88220B80(void) {
    func_88004990(**D_88234800, 0);
    D_880068B8 = 1;
}

extern void func_8000612C(void);
void func_88220BB8(void) {
    func_8000612C();
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_193D50/func_88220BDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_193D50/func_88220E08.s")

void func_88220F40(void) {
    D_880068B8 = 0;
}

extern void func_88220AD0(s16, s16);
extern s32 D_80087200;
extern s32 D_88234660;
extern u32 D_88234810;
void Input_SetRepeatController(s32 value);
void func_88001900(void);
extern s32 D_880068B4;
void Util_Free(s32 arg0);
void func_88220F4C(void) {
    if (D_88234660 != 0) {
        func_88220AD0((*(s16 *)((u8 *)(D_88234810) + (0x23C))), (*(s16 *)((u8 *)(D_88234810) + (0x23E))));
    } else {
        Input_SetRepeatController(D_80087200);
        func_88001900();
        D_880068B4 = 1;
    }
    Util_Free((s32) D_88234810);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_193D50/func_88220FB8.s")

extern void func_889033A0(s32);
void func_8822100C(void) { func_889033A0((D_88234810 + 4)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_193D50/func_88221034.s")
#endif
