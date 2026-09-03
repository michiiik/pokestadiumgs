#include "global.h"


#ifdef VERSION_US
extern void *D_81331970;
extern void func_81600A34(void *, void *, s32, s32, s32, s32, s32);
void func_81302390(void *arg0) {
    func_81600A34(arg0, D_81331970, 0, 0, 0, 0x280, 0x1E0);
    func_81600A34(arg0, (u8 *)D_81331970 + 2, 0, 0, 0xF0, 0x280, 0xF0);
    func_81600A34(arg0, (u8 *)D_81331970 + 1, 1, 0, 0, 0x280, 0x46);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FA520/func_81302438.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FA520/func_8130251C.s")

extern void *D_81331974;
extern u8 D_81317800[];
extern void func_800088DC(void);
extern void func_81302438(void *);
extern void func_813021B4(void *, void *);
extern void func_80008648(void);
void func_81302634(void) {
    func_800088DC();
    func_81302438(D_81331974);
    func_813021B4(D_81317800, D_81331974);
    func_80008648();
}

extern s32 func_8006CBB8(u16);
extern void StageContext_SetClearColor(s32);
void func_8130267C(u8 *arg0) {
    if (*(s16 *)(*(u8 **)(arg0 + 0x940) + 0x34) == 6) {
        s32 result = func_8006CBB8(*(u16 *)(arg0 + 0x952));
        if (result == 0 || result == 1 || result == 2)
            StageContext_SetClearColor(1);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FA520/func_813026D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FA520/func_81302854.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FA520/func_81302920.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FA520/func_813029F0.s")
#endif
