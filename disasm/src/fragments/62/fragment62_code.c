#include "global.h"


#ifdef VERSION_US
extern u8 D_86C00350[];
extern void fragment3_main(void *);
extern void func_81A005F0(void *);
extern void func_8005A0B4(s32);
void func_86C00020(void) {
    fragment3_main(D_86C00350);
    func_81A005F0(D_86C00350);
    func_8005A0B4(0);
    func_8005A0B4(1);
    func_8005A0B4(2);
    func_8005A0B4(3);
}

extern u8 D_800D0510[];
extern void func_800088DC(void);
extern void GfxImage_FillCurrent(void *, s32);
extern void func_81A0022C(void *);
extern void func_80008648(void);
void func_86C00070(void) {
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 0x8421);
    func_81A0022C(&D_86C00350);
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/62/fragment62_code/func_86C000B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/62/fragment62_code/func_86C00148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/62/fragment62_code/func_86C001CC.s")

s32 func_81A00074(u8 *, s32);
extern s8 D_86C00320;
extern s8 D_86C00330;
extern s8 D_86C00340;
s32 func_86C002C4(void) {
    s32 sp18;
    s32 temp_v0;

    osSyncPrintf(&D_86C00320);
    temp_v0 = func_81A00074(D_86C00350, 0);
    sp18 = temp_v0;
    osSyncPrintf(&D_86C00330, temp_v0);
    osSyncPrintf(&D_86C00340);
    return temp_v0;
}
#endif
