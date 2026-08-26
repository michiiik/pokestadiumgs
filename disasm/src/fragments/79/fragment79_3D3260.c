#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D3260/func_841639D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D3260/func_84163B4C.s")

extern f64 D_8418C818;
extern f64 D_8418C820;
void FourStreamTrail_Update(f32 arg0, f32 *arg1, f32 arg2, f32 arg3) {
    f32 spB0[4][4];
    f32 sp70[4][4];
    f32 sp30[4][4];
    UNUSED s32 pad2[2];
    guScaleF(sp30, arg3, arg3, arg3);
    guRotateF(sp70, (arg0 * D_8418C818) / D_8418C820, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp30, sp70, spB0);
    guMtxXFMF(spB0, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D3260/func_84163E60.s")

extern u8 *D_84187A70;
extern void func_84163E60(u8 *);
s32 FourStreamTrail_IsComplete(void) {
    u8 *ptr = D_84187A70;
    s32 i = 0;
    while (i != 4) {
        if (*(s16 *)ptr == 1) {
            *(s16 *)(ptr + 2) += 1;
            if (*(s16 *)(ptr + 2) > *(s16 *)(ptr + 4)) {
                *(s16 *)ptr = 0;
            } else {
                func_84163E60(ptr);
            }
        }
        i++;
        ptr += 0x430;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D3260/func_84164280.s")
#endif
