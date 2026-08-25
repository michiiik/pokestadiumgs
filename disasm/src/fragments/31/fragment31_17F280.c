#include "global.h"


#ifdef VERSION_US
extern void func_800033DC(s32);
extern void func_8821CE40(s32);
extern void main_pool_pop_state(s32);
extern s32 D_88234560;
extern s32 D_88234564;

void func_8820C000(void) {
    func_800033DC(D_88234564);
    main_pool_pop_state(0x41525249);
    func_8821CE40(3);
    D_88234560 = 5;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C114.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C258.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C65C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C798.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C800.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C8A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C94C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CA50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CAE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CB74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CCA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CE2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CF8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820E450.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820E580.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820E6A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820E9BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820EB14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820ECE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820ED44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820F74C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820F7EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820FC78.s")

extern void func_8820FC78();
void func_8820FD58(void) { func_8820FC78(0); func_8820FC78(1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820FD80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820FDF8.s")
#endif
