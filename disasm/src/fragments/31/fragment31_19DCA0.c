#include "global.h"


#ifdef VERSION_US
extern void func_88001900();
extern s32 D_880068B4;
extern s32 D_889041B4;

void func_8822AA20(void) {
    func_88001900();
    D_889041B4 = 1;
    D_880068B4 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DCA0/func_8822AA50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DCA0/func_8822AA9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DCA0/func_8822AB28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19DCA0/func_8822ABE8.s")
#endif
