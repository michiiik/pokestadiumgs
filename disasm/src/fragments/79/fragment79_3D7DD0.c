#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84168540.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84168680.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84168B00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84168C18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84168CA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169040.s")

typedef struct {
    u8 pad[0x88];
    Vtx *vertices;
} Func84169214State;
Gfx *BattleAnim_SixSlotTrail_DrawSegments(Gfx *arg0, Func84169214State *arg1) {
    s32 i;
    Vtx *temp_v0 = arg1->vertices;
    for (i = 0; i < 19; i++) {
        gSPVertex(arg0++, temp_v0, 4, 0);
        gSP2Triangles(arg0++, 0, 2, 1, 0, 1, 2, 3, 0);
        temp_v0 += 2;
    }
    return arg0;
}

typedef struct S1_unk_D_843C2C00_064 S1_unk_D_843C2C00_064;
typedef struct S1_unk_D_843C3508 S1_unk_D_843C3508;
typedef struct S1_unk_D_843C2C00_024 S1_unk_D_843C2C00_024;
typedef struct S1_unk_D_84389CE0 S1_unk_D_84389CE0;
typedef struct S1_unk_D_843C3508_0A4 S1_unk_D_843C3508_0A4;
typedef struct S1_Vec3f S1_Vec3f;
struct S1_unk_D_843C2C00_064 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
};
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
struct S1_Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
};
struct S1_unk_D_843C3508_0A4 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ S1_Vec3f unk_0C;
    /* 0x18 */ S1_Vec3f unk_18;
};
typedef struct {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} S1_Color_RGBA8;
struct S1_unk_D_84389CE0 {
    /* 0x00 */ S1_Color_RGBA8 unk_00;
    /* 0x04 */ u8 unk_04;
};
struct S1_unk_D_843C3508 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ S1_unk_D_84389CE0 unk_008;
    /* 0x00D */ S1_unk_D_84389CE0 unk_00D;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ s16 unk_01C;
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ s32 unk_024;
    /* 0x028 */ S1_unk_D_843C2C00_024 unk_028;
    /* 0x048 */ S1_unk_D_843C2C00_024 unk_048;
    /* 0x068 */ S1_unk_D_843C2C00_064 unk_068;
    /* 0x074 */ S1_unk_D_843C2C00_064 unk_074;
    /* 0x080 */ f32 unk_080;
    /* 0x084 */ f32 unk_084;
    /* 0x088 */ Vtx* unk_088;
    /* 0x08C */ char unk08C[0x18];
    /* 0x0A4 */ S1_unk_D_843C3508_0A4 unk_0A4[20];
};
extern u8* D_8418CA20[256];
Gfx* BattleAnim_SixSlotTrail_LoadTextures(Gfx* arg0, S1_unk_D_843C3508* arg1) {
    S1_unk_D_843C2C00_064* ptr;
    UNUSED s32 pad[2];

    ptr = &arg1->unk_068;
    gDPLoadTextureTile_4b(arg0++, D_8418CA20[arg1->unk_020], G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, ptr->unk_08, ptr->unk_0A);
    gDPSetTileSize(arg0++, G_TX_RENDERTILE, ptr->unk_00, ptr->unk_02, (ptr->unk_00 + 31) << 2, (ptr->unk_02 + 31) << 2);

    ptr = &arg1->unk_074;
    gDPLoadMultiTile_4b(arg0++, D_8418CA20[arg1->unk_024], 0x0100, 1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, ptr->unk_08, ptr->unk_0A);
    gDPSetTileSize(arg0++, 1, ptr->unk_00, ptr->unk_02, (ptr->unk_00 + 31) << 2, (ptr->unk_02 + 31) << 2);

    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169618.s")

extern u8 *D_84187E40;
void func_84169B80(void) {
    u8 *ptr = *(u8 **)&D_84187E40;
    s32 i = 0;
    while (i != 2) {
        i += 1;
        *(u16 *)ptr = 0;
        ptr += 0x1E4;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169BA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169C74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169DBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169F18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_8416A050.s")

void func_8416A140(void) {}
void func_8416A140_padding(void) {}

void *func_8416A150(void *arg0) { return arg0; }
#endif
