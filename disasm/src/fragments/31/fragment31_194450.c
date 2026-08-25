#include "global.h"


#ifdef VERSION_US
extern void func_80049ED8(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_882211D0(void) {
    func_80049ED8(D_80087200);
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194450/func_882211F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194450/func_8822123C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194450/func_8822128C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194450/func_8822157C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194450/func_882215A8.s")
#endif
