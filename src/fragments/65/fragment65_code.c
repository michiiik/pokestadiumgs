#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/65/fragment65_code/func_87D00020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/65/fragment65_code/func_87D001A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/65/fragment65_code/func_87D00354.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/65/fragment65_code/func_87D00438.s")

f32 func_87D0059C(f32 *arg0, f32 *arg1) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv1 = *arg1;
    temp_fa0 = *arg0;
    temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0));
    if (temp_fv0 != 0.0f) {
        *arg0 = temp_fa0 / temp_fv0;
        *arg1 /= temp_fv0;
    }
    return temp_fv0;
}

f32 func_87D005E8(f32 *a, f32 *b, f32 *c) {
    f32 r = sqrtf((*a) * (*a) + (*b) * (*b) + (*c) * (*c));
    if (r) {
        *a /= r;
        *b /= r;
        *c /= r;
    }
    return r;
}

void func_87D00648(void *arg0, void *arg1, void *arg2) {
    (*(f32 *)((u8 *)(arg0) + (0))) = (f32) -((*(f32 *)((u8 *)(arg2) + (4))) - (*(f32 *)((u8 *)(arg1) + (4))));
    (*(f32 *)((u8 *)(arg0) + (4))) = (f32) ((*(f32 *)((u8 *)(arg2) + (0))) - (*(f32 *)((u8 *)(arg1) + (0))));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/65/fragment65_code/func_87D00670.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/65/fragment65_code/func_87D00720.s")
#endif
