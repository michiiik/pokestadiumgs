#include "global.h"


#ifdef VERSION_US
extern void func_88004EB0();
extern s32 D_880068B8;

void func_88222690(void) {
    func_88004EB0();
    D_880068B8 = 0;
}

extern void func_800033DC(s32);
extern void func_80049ED8(s32);
extern s32 D_80087200;
extern s32 D_880068B4;
extern s32 D_88234840;

void func_882226B4(void) {
    func_80049ED8(D_80087200);
    D_880068B4 = 1;
    func_800033DC(D_88234840);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_195910/func_882226F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_195910/func_88222CBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_195910/func_88223120.s")
#endif
