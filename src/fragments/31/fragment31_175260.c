#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_88201FE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_88202098.s")

extern u8 func_8006378C(u8);
s32 func_88202104(u8 arg0) {
    s32 result = 0;

    if (func_8006378C(arg0) == 2 || (arg0 >= 0xF3 && arg0 < 0xFA)) {
        result = 1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_88202158.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_882025B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_882026A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_882027F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_88202AA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_88202F0C.s")

extern void func_88202F0C(u8 *);
void func_88202FA0(void *a0, u8 *a1) {
    *(u8 *)((u8 *)a0 + 9) = *(u8 *)a1;
    *(s32 *)((u8 *)*(void **)a0 + 0xC) = 1;
    func_88202F0C(a1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_88202FD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_882033B0.s")
#endif
