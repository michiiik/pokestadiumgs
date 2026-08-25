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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822C53C.s")

extern void *D_80087200;
extern void func_80049ED8(void *);
extern void func_800033DC(s32);
extern s32 D_880068B4;
extern u8 **D_88234920;
void func_8822C570(void) {
    func_80049ED8(D_80087200);
    D_880068B4 = 1;
    func_800033DC(*(volatile void **)(&D_88234920));
}

extern void func_88004990(u8, s32);
extern s32 D_88234714;
extern u8 **D_88234920;

void func_8822C5AC(void) {
    func_88004990(**D_88234920, 0);
    D_880068B8 = 1;
    D_88234714 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822C5EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822C6AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822C6D8.s")

extern void * D_80087200;
extern void func_80049ED8(void *);
void func_8822C8E0(void) { func_80049ED8(D_80087200); }

extern void func_800033DC(s32);
extern void func_88001900();
extern s32 D_880068B4;
extern s32 D_88234930;

void func_8822C904(void) {
    func_88001900();
    D_880068B4 = 1;
    func_800033DC(D_88234930);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822C93C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822CC50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19F570/func_8822CED0.s")
#endif
