#include "global.h"


#ifdef VERSION_US
void func_86206790(f32 *arg0, f32 *arg1, s32 *arg2, s32 *arg3) {
    f32 temp_fv0;
    s32 temp_v0;

    temp_fv0 = *arg0;
    *arg0 = *arg1;
    *arg1 = temp_fv0;
    temp_v0 = *arg2;
    *arg2 = *arg3;
    *arg3 = temp_v0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26D1D0/func_862067B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26D1D0/func_86206920.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26D1D0/func_86206C34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26D1D0/func_86206D20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26D1D0/func_86206EF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26D1D0/func_862070B0.s")
#endif
