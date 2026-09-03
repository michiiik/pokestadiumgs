#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4060/func_841647D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4060/func_84164924.s")

extern f64 D_8418C858;
extern f64 D_8418C860;
void OwnerLinkedFourStream_Update(f32 arg0, f32 *arg1, f32 arg2) {
    UNUSED f32 pad[16];
    f32 sp30[4][4];
    UNUSED s32 pad2[2];
    guRotateF(sp30, (arg0 * D_8418C858) / D_8418C860, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4060/func_84164C28.s")

extern u8 *D_84187B70;
extern void func_84109B9C(u8 *);
extern void func_84164C28(u8 *);
s32 OwnerLinkedFourStream_IsComplete(void) {
    u8 *ptr = D_84187B70;
    s32 i = 0;
    do {
        if (*(s16 *)ptr == 1) {
            *(s16 *)(ptr + 2) = *(s16 *)(ptr + 2) + 1;
            if (*(s16 *)(ptr + 4) < *(s16 *)(ptr + 2)) {
                *(s16 *)ptr = 0;
                func_84109B9C(*(u8 **)(ptr + 0x34));
            } else {
                func_84164C28(ptr);
            }
        }
        i++;
        ptr += 0x434;
    } while (i != 4);
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4060/func_841650A8.s")
#endif
