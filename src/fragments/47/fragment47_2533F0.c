#include "global.h"


#ifdef VERSION_US
extern void func_87F0455C(void);
extern void func_8600BA50(void);
extern void func_8600AAD4(void);
extern void func_87F024CC(void);
extern void func_86004FDC(void *, s32);
extern void ModelRenderer_InitDisplayRoots(void);
extern void func_8600520C(void *);
extern u8 D_8600E110[];
void func_8600CDD0(s32 arg0) {
    func_87F0455C();
    func_8600BA50();
    func_8600AAD4();
    func_87F024CC();
    func_86004FDC(D_8600E110, arg0);
    ModelRenderer_InitDisplayRoots();
    func_8600520C(D_8600E110);
}

extern void func_800088DC(void);
extern void func_8000766C(void *, s32, s32, s32, s32);
extern void func_86006F20(void *);
extern void func_80008648(void);
extern u8 D_800D0510[];
void func_8600CE2C(s32 arg0) {
    func_800088DC();
    func_8000766C(D_800D0510, 0, 0, 0x140, 0xF0);
    func_86006F20(D_8600E110);
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_2533F0/func_8600CE80.s")

extern void StageFade_StartFromOpaque(s32);
extern void func_800086A4(s32);
extern void func_80064D28();
s32 func_8600CE80(s32);

void func_8600CF80(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(0xA);
    do {
        func_80064D28();
        func_8600CE2C(var_s0);
        temp_v0 = func_8600CE80(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/47/fragment47_2533F0/func_8600CFDC.s")
#endif
