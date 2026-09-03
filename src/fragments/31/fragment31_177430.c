#include "global.h"


#ifdef VERSION_US
extern void func_800226C0(s32);
extern u8 D_88234680;

void func_882041B0(void) {
    (*(s32 *)((u8 *)(&D_88234680) + (0x2C))) = (s32) (*(s32 *)((u8 *)(&D_88234680) + (0x28)));
    func_800226C0(0x132);
}

extern s32 D_882346AC;
void func_882041E0(void) {
    D_882346AC = 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_177430/func_882041F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_177430/func_88204400.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_177430/func_88205114.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_177430/func_88205200.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_177430/func_882052F8.s")

s32 func_88205D7C(void) {
    return (D_882346AC == 3) ? 1 : 0;
}
#endif
