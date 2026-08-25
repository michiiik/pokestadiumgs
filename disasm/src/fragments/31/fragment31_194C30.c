#include "global.h"


#ifdef VERSION_US
extern void func_80049ED8(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_882219B0(void) {
    func_80049ED8(D_80087200);
    D_880068B8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194C30/func_882219D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194C30/func_88221A34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194C30/func_88221A8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194C30/func_88221AF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194C30/func_88221C54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194C30/func_88221F28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_194C30/func_88221F54.s")
#endif
