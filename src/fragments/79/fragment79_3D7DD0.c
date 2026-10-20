#include "global.h"


#ifdef VERSION_US
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
extern u8 *D_84187DC0;
extern S1_unk_D_84389CE0 D_84187DC4;
extern s16 D_841A4DC2, D_841A4DC4;
typedef struct {
    s16 unk_00, unk_02, unk_04, unk_06;
    f32 unk_08;
    S1_Vec3f unk_0C;
} AuxiliaryEffectNode;
typedef struct {
    s16 unk_000;
    u8 unk002[2];
    AuxiliaryEffectNode unk_004[20];
} AuxiliaryEffect;
extern u8 *D_84187E40;
void BattleAnim_SixSlotTrail_ResetPool(void) {
    s32 i;
    s32 j;
    S1_unk_D_843C3508* var_v0;
    S1_unk_D_843C3508_0A4* var_a0;
    S1_unk_D_84389CE0 sp0 = D_84187DC4;

    D_841A4DC4 = 0;
    D_841A4DC2 = 0;

    var_v0 = (S1_unk_D_843C3508 *)(D_84187DC0 + 2304);
    for (i = 0; i < 6; i++, var_v0++) {
        var_v0->unk_000 = 0;
        var_v0->unk_004 = 0;
        var_v0->unk_006 = 0;
        var_v0->unk_008 = sp0;
        var_v0->unk_00D = sp0;

        var_a0 = &var_v0->unk_0A4[0];
        for (j = 0; j < 20; j++, var_a0++) {
            var_a0->unk_00 = 0.0f;
            var_a0->unk_04 = 1.0f;
            var_a0->unk_08 = 0.0f;
            var_a0->unk_0C.x = 0.0f;
            var_a0->unk_0C.y = 0.0f;
            var_a0->unk_0C.z = 0.0f;
            var_a0->unk_18.x = 0.0f;
            var_a0->unk_18.y = 0.0f;
            var_a0->unk_18.z = 0.0f;
        }
    }
}

void BattleAnim_SixSlotTrail_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, u8 arg8, u8 arg9,
                   u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, f32 arg10, f32 arg11, f32 arg12, s16 arg13,
                   s32 arg14, s32 arg15, s16 arg16, s16 arg17, s16 arg18, s16 arg19, s16 arg1A, s16 arg1B, s16 arg1C,
                   s16 arg1D, S1_unk_D_843C2C00_024* arg1E, S1_unk_D_843C2C00_024* arg1F) {
    S1_unk_D_843C3508* var_v0;
    S1_unk_D_843C3508_0A4* var_v1_2;
    s32 i;
    s32 j;
    S1_Vec3f spC;
    S1_Vec3f sp0;

    spC.x = arg1;
    spC.y = arg2;
    spC.z = arg3;
    sp0.x = arg4;
    sp0.y = arg5;
    sp0.z = arg6;
    var_v0 = (S1_unk_D_843C3508 *)(D_84187DC0 + 2304);

    for (i = 0; i < 6; i++, var_v0++) {
        if (var_v0->unk_000 == 0) {
            var_v0->unk_000 = 1;
            var_v0->unk_002 = arg0;
            var_v0->unk_004 = 0;
            var_v0->unk_006 = arg13;
            var_v0->unk_080 = arg12;
            var_v0->unk_084 = arg10;
            var_v0->unk_020 = arg14;
            var_v0->unk_024 = arg15;
            var_v0->unk_068.unk_00 = 0;
            var_v0->unk_068.unk_02 = 0;
            var_v0->unk_074.unk_00 = 0;
            var_v0->unk_074.unk_02 = 0;
            var_v0->unk_068.unk_04 = arg16;
            var_v0->unk_068.unk_06 = arg17;
            var_v0->unk_074.unk_04 = arg1A;
            var_v0->unk_074.unk_06 = arg1B;
            var_v0->unk_068.unk_08 = arg18;
            var_v0->unk_068.unk_0A = arg19;
            var_v0->unk_074.unk_08 = arg1C;
            var_v0->unk_074.unk_0A = arg1D;
            var_v0->unk_028 = *arg1E;
            var_v0->unk_048 = *arg1F;
            var_v0->unk_01C = 0x46;
            var_v0->unk_014 = 1.0f;
            var_v0->unk_018 = 1.0f;
            var_v0->unk_008.unk_00.r = arg7;
            var_v0->unk_008.unk_00.g = arg8;
            var_v0->unk_008.unk_00.b = arg9;
            var_v0->unk_008.unk_00.a = argA;
            var_v0->unk_008.unk_04 = argB;
            var_v0->unk_00D.unk_00.r = argC;
            var_v0->unk_00D.unk_00.g = argD;
            var_v0->unk_00D.unk_00.b = argE;
            var_v0->unk_00D.unk_00.a = argF;

            var_v1_2 = &var_v0->unk_0A4[0];
            for (j = 0; j < 20; j++, var_v1_2++) {
                var_v1_2->unk_00 = 2.0f * j;
                var_v1_2->unk_04 = arg11;
                var_v1_2->unk_08 = 0.0f;
                var_v1_2->unk_0C = spC;
                var_v1_2->unk_18 = sp0;
            }
            break;
        }
    }
}

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

void func_84169B80(void) {
    u8 *ptr = *(u8 **)&D_84187E40;
    s32 i = 0;
    while (i != 2) {
        i += 1;
        *(u16 *)ptr = 0;
        ptr += 0x1E4;
    }
}

s16 AuxiliaryEffect_Alloc(void) {
    AuxiliaryEffect* var_a0;
    AuxiliaryEffectNode* var_v1;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        var_a0 = &((AuxiliaryEffect *)D_84187E40)[i];
        if (var_a0->unk_000 == 0) {
            var_v1 = &var_a0->unk_004[0];
            for (j = 0; j < 20; j++, var_v1++) {
                var_v1->unk_00 = 0;
                var_v1->unk_04 = 0;
                var_v1->unk_08 = 1.0f;
                var_v1->unk_0C.x = 0.0f;
                var_v1->unk_0C.y = 0.0f;
                var_v1->unk_0C.z = 0.0f;
            }
            var_a0->unk_000 = 1;
            return i;
        }
    }
    return -1;
}

void AuxiliaryEffect_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5) {
    s32 i;
    AuxiliaryEffect* temp_v0 = &((AuxiliaryEffect *)D_84187E40)[arg0];
    AuxiliaryEffectNode* var_v1;

    if (temp_v0->unk_000 != 0) {
        var_v1 = &temp_v0->unk_004[0];
        for (i = 0; i < 20; i++, var_v1++) {
            if (var_v1->unk_00 == 0) {
                var_v1->unk_00 = 1;
                var_v1->unk_04 = 0;
                var_v1->unk_06 = arg4;
                var_v1->unk_08 = arg5;
                var_v1->unk_0C.x = arg1;
                var_v1->unk_0C.y = arg2;
                var_v1->unk_0C.z = arg3;
                return;
            }
        }
    }
}

void AuxiliaryEffect_Update(s16 arg0) {
    AuxiliaryEffect* temp_v0 = &((AuxiliaryEffect *)D_84187E40)[arg0];
    AuxiliaryEffectNode* var_v1;
    s32 i;

    if (temp_v0->unk_000 != 0) {
        var_v1 = &temp_v0->unk_004[0];
        for (i = 0; i < 20; i++, var_v1++) {
            if (var_v1->unk_00 == 1) {
                var_v1->unk_04++;
                if (var_v1->unk_06 < var_v1->unk_04) {
                    var_v1->unk_00 = 0;
                }
                var_v1->unk_0C.y -= 0.75f;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_84169F18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D7DD0/func_8416A050.s")

void func_8416A140(void) {}
void func_8416A140_padding(void) {}

void *func_8416A150(void *arg0) { return arg0; }
#endif
