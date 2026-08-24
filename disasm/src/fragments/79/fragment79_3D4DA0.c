#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84165510.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84165670.s")

extern f64 D_8418C8B0;
extern f64 D_8418C8B8;
void func_84165910(f32 arg0, f32 *arg1, f32 arg2) {
    UNUSED f32 pad[16];
    f32 sp30[4][4];
    UNUSED s32 pad2[2];
    guRotateF(sp30, (arg0 * D_8418C8B0) / D_8418C8B8, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_841659A0.s")

extern u8 *D_84187BD0;
extern void func_841659A0(u8 *);
s32 func_84165C2C(void) {
    u8 *ptr = D_84187BD0;
    s32 i = 0;
    do {
        if (*(s16 *)ptr == 1) {
            *(s16 *)(ptr + 2) = *(s16 *)(ptr + 2) + 1;
            if (*(s16 *)(ptr + 4) < *(s16 *)(ptr + 2)) {
                *(s16 *)ptr = 0;
            } else {
                func_841659A0(ptr);
            }
        }
        i++;
        ptr += 0x41C;
    } while (i != 4);
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84165CC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84166130.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84166270.s")

extern f64 D_8418C8E8;
extern f64 D_8418C8F0;
void func_8416654C(f32 arg0, f32 *arg1, f32 arg2) {
    f32 sp30[4][4];
    f32 angle = (arg0 * D_8418C8E8) / D_8418C8F0;
    guRotateRPYF(sp30, 90.0f, angle, angle);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_841665D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_8416691C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84166A64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84166F60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_841670A8.s")

extern f32 D_8418C910;
void func_84167438(f32 arg0, f32 *arg1, f32 arg2) {
    UNUSED f32 pad[16];
    f32 sp30[4][4];
    UNUSED s32 pad2[2];
    guRotateF(sp30, (360.0f * arg0) / D_8418C910, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_841674C0.s")

extern u8 *D_84187D40;
extern void func_841674C0(u8 *);
s32 func_841677C4(void) {
    u8 *ptr = D_84187D40;
    s32 i = 0;
    if (*(s16 *)(ptr + 6) == 2 && *(s16 *)(ptr + 0x94) < *(s16 *)(ptr + 2)) {
        return -1;
    }
    do {
        if (*(s16 *)ptr == 1) {
            *(s16 *)(ptr + 2) = *(s16 *)(ptr + 2) + 1;
            func_841674C0(ptr);
        }
        i++;
        ptr += 0x240;
    } while (i != 4);
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84167864.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84167D2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84168000.s")
#endif
