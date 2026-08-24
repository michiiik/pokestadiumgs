#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_841614E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84161670.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84161CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84161DAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162078.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_841621A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162660.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162798.s")

extern f64 D_8418C7A8;
extern f64 D_8418C7B0;

void func_84162A40(f32 arg0, f32 *arg1, f32 arg2) {
    f32 sp30[4][4];
    f32 angle = (arg0 * D_8418C7A8) / D_8418C7B0;
    guRotateRPYF(sp30, 90.0f, angle, angle);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162AC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162C88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162DE8.s")
#endif
