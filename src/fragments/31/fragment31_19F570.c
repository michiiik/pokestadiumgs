#include "global.h"


#ifdef VERSION_US
extern s32 D_880068B8;
void func_8822C2F0(void) {
    D_880068B8 = 0;
}

void func_8822C2FC(void) {
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822C30C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822C374.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822C4A0.s")

extern void Input_SetRepeatController(void *);
extern void *D_80087200;
extern s32 D_88234714;
void func_8822C53C(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
    D_88234714 = 1;
}

extern void Util_Free(s32);
extern s32 D_880068B4;
extern u8 **D_88234920;
void func_8822C570(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B4 = 1;
    Util_Free(*(volatile void **)(&D_88234920));
}

extern void func_88004990(u8, s32);

void func_8822C5AC(void) {
    func_88004990(**D_88234920, 0);
    D_880068B8 = 1;
    D_88234714 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822C5EC.s")

extern void func_889033FC(void *, void *);
void func_8822C6AC(void) {
    func_889033FC(*D_88234920, (u8 *)D_88234920 + 0x18);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822C6D8.s")

extern void * D_80087200;
void func_8822C8E0(void) {
    Input_SetRepeatController(D_80087200);
}

extern void func_88001900();
extern s32 D_88234930;

void func_8822C904(void) {
    func_88001900();
    D_880068B4 = 1;
    Util_Free(D_88234930);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822C93C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822CC50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822CED0.s")
#endif
