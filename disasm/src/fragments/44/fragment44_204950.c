#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF166E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF16774.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF16878.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF169A4.s")

extern void *D_8AF27150;
extern void *D_8AF263C0;
extern u16 D_8AF2BDC6;
extern s32 D_8AF340C0;
extern s32 D_8AF34138;
extern s32 D_8AF341B0;
extern s32 func_8AF0326C(void *);
extern void func_8AF00130(s32);
extern void func_8AC0686C(void *, s16);
extern void func_8AC0619C(s32 *, u16);
extern void func_8AC06220(s32 *, u16);
s16 func_8AF16D2C(void) {
    s16 result = 0x11;
    void *state = D_8AF27150;
    if (func_8AF0326C(state) == 0) {
        if ((*(u16 *)((u8 *)D_8AF263C0 + 8)) & 0x4000) {
            func_8AF00130(3);
            result = 0x10;
        }
    }
    func_8AC0686C(&D_8AF341B0, *(s16 *)((u8 *)state + 0x38));
    func_8AC0619C(&D_8AF340C0, D_8AF2BDC6);
    func_8AC06220(&D_8AF34138, D_8AF2BDC6);
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF16DC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF16E60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF16EB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF16EF0.s")

extern void func_8004C594(s32, s16);
extern void *D_8AF342E0;
extern s16 D_8AF34800;
extern s16 D_8AF34D64;
void func_8AF171D8(s32 arg0) {
    (*(s16 *)((u8 *)(D_8AF342E0) + (0x30))) = 0x3B;
    (*(s16 *)((u8 *)(D_8AF342E0) + (0x32))) = (s16) (D_8AF34D64 + 0xDB);
    func_8004C594(2, D_8AF34800);
}

extern void _bzero(s32 *, s32);
extern s16 D_8AF347F4;
extern s16 D_8AF347F6;
extern u8 D_8AF34808;

void func_8AF1722C(void) {
    D_8AF347F4 = 0;
    D_8AF347F6 = 0;
    _bzero(&D_8AF34808, 0xE);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF17264.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF174DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF176C4.s")
#endif
