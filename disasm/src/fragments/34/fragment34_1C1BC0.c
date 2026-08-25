#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_885045B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88504704.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_885047B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88504828.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88504A54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88504AF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88504D9C.s")

extern s8 D_8852300C[];
s32 func_88504E94(u8 arg0) {
    return D_8852300C[arg0];
}

extern s32 D_880068B8;

void func_88504EAC(void) {
    D_880068B8 = 0;
}

extern s32 D_880068B4;
extern void *D_885229A0;
extern void func_800033DC(void *);
void func_88504EB8(void) {
    D_880068B4 = 1;
    func_800033DC(D_885229A0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88504EE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505038.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505264.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_885053E8.s")

extern void func_88505264(void);
void func_88505440(void) {
    func_88505264();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505460.s")

void func_88505514(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x16))) = (s16) ((*(s16 *)((u8 *)(arg0) + (0x16))) - 1);
    (*(s16 *)((u8 *)(arg0) + (0x1A))) = (s16) ((s32) ((*(s16 *)((u8 *)(arg0) + (0x16))) * 0xFF) / 8);
}

void func_88505544(void *arg0)
{
  s16 temp_v0;
  func_88505264();
 *((s16 *) (((u8 *) arg0) + 0x16)) = (s16) ((*((s16 *) (((u8 *) arg0) + 0x16))) - 1); temp_v0 = *((s16 *) (((u8 *) arg0) + 0x16));
  *((f32 *) (((u8 *) arg0) + 0x1C)) = (f32) (((f32) temp_v0) / 8);
  if (temp_v0 <= 0)
  {
    func_88505038(arg0, 0);
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_885055A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505718.s")

extern s8 D_8852300A;
extern void func_88505718(void);
extern void func_88504EE8(void);
void func_885057BC(void) {
    if (D_8852300A == 1) {
        func_88505718();
        func_88504EE8();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_885057F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_885059B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505A7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505B58.s")

extern void func_88505A7C();
extern u8 D_885229A8;

void func_88505E9C(void) {
    (*(s16 *)((u8 *)(&D_885229A8) + (4))) = (s16) ((*(s16 *)((u8 *)(&D_885229A8) + (4))) - 1);
    if ((*(s16 *)((u8 *)(&D_885229A8) + (4))) <= 0) {
        func_88505A7C();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88505EDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88506018.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1C1BC0/func_88506618.s")
#endif
