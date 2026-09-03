#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84165510.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84165670.s")

extern f64 D_8418C8B0;
extern f64 D_8418C8B8;
void OwnerAnchoredFourStream_Update(f32 arg0, f32 *arg1, f32 arg2) {
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
void DoubleTextureTrail_RotateVertexOffset(f32 arg0, f32 *arg1, f32 arg2) {
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

typedef struct S1_unk_D_843C2C00_064 S1_unk_D_843C2C00_064;
typedef struct S1_DoubleTextureTrail S1_DoubleTextureTrail;
typedef struct S1_unk_D_843C2C00_024 S1_unk_D_843C2C00_024;
typedef struct S1_unk_D_84389CE0 S1_unk_D_84389CE0;
typedef struct S1_unk_D_843C2C00_0B0 S1_unk_D_843C2C00_0B0;
typedef struct S1_Vec3f S1_Vec3f;
struct S1_unk_D_843C2C00_064 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
};
typedef struct {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} S1_Color_RGBA8;
struct S1_unk_D_843C2C00_024 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
};
struct S1_unk_D_84389CE0 {
    /* 0x00 */ S1_Color_RGBA8 unk_00;
    /* 0x04 */ u8 unk_04;
};
struct S1_Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
};
struct S1_unk_D_843C2C00_0B0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ S1_Vec3f unk_10;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
};
struct S1_DoubleTextureTrail {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x008 */ f32 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ s32 unk_01C;
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ S1_unk_D_843C2C00_024 unk_024;
    /* 0x044 */ S1_unk_D_843C2C00_024 unk_044;
    /* 0x064 */ S1_unk_D_843C2C00_064 unk_064;
    /* 0x070 */ S1_unk_D_843C2C00_064 unk_070;
    /* 0x07C */ S1_unk_D_84389CE0 unk_07C;
    /* 0x081 */ S1_unk_D_84389CE0 unk_081;
    /* 0x086 */ S1_Color_RGBA8 unk_086;
    /* 0x08C */ f32 unk_08C;
    /* 0x090 */ f32 unk_090;
    /* 0x094 */ s16 unk_094;
    /* 0x096 */ char unk096[0x1A];
    /* 0x0B0 */ S1_unk_D_843C2C00_0B0 unk_0B0[10];
};
extern u8* D_8418CA20[256];
Gfx* DoubleTextureTrail_LoadTextures(Gfx* arg0, S1_DoubleTextureTrail* arg1) {
    S1_unk_D_843C2C00_064* ptr;

    ptr = &arg1->unk_064;
    gDPLoadTextureTile_4b(arg0++, D_8418CA20[arg1->unk_01C], G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, ptr->unk_08, ptr->unk_0A);
    gDPSetTileSize(arg0++, G_TX_RENDERTILE, ptr->unk_00, ptr->unk_02, (ptr->unk_00 + 31) << 2, (ptr->unk_02 + 31) << 2);

    ptr = &arg1->unk_070;
    gDPLoadMultiTile_4b(arg0++, D_8418CA20[arg1->unk_020], 0x0100, 1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, ptr->unk_08, ptr->unk_0A);
    gDPSetTileSize(arg0++, 1, ptr->unk_00, ptr->unk_02, (ptr->unk_00 + 31) << 2, (ptr->unk_02 + 31) << 2);

    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D4DA0/func_84168000.s")
#endif
