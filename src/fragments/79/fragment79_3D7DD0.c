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

typedef struct { u8 pad_00[0xA8]; f32 eye[3]; } unk_func_84168B00;

extern u32 func_841094A4(void);
extern void Vec3f_CrossProductComponents(f32, f32, f32, f32, f32, f32, f32*, f32*, f32*);
extern void func_80070C14(f32*, f32*, f32*);

void BattleAnim_SixSlotTrail_ComputeCameraRelativeOffset(s32 arg0, f32* arg1, f32* arg2, f32* arg3, f32 arg4, UNUSED f32 arg5, UNUSED f32 arg6,
                   UNUSED f32 arg7) {
    UNUSED s32 pad[36];
    unk_func_84168B00* temp_v0 = (unk_func_84168B00*)func_841094A4();
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp60;
    f32 sp5C;
    f32 sp58;

    sp60 = arg2[0] - temp_v0->eye[0];
    sp5C = arg2[1] - temp_v0->eye[1];
    sp58 = arg2[2] - temp_v0->eye[2];

    sp6C = arg1[0];
    sp68 = arg1[1];
    sp64 = arg1[2];

    Vec3f_CrossProductComponents(sp6C, sp68, sp64, sp60, sp5C, sp58, &sp54, &sp50, &sp4C);

    func_80070C14(&sp54, &sp50, &sp4C);

    switch (arg0) {
        case 0:
            arg3[0] = arg4 * sp54;
            arg3[1] = arg4 * sp50;
            arg3[2] = arg4 * sp4C;
            break;

        case 1:
            arg3[0] = -arg4 * sp54;
            arg3[1] = -arg4 * sp50;
            arg3[2] = -arg4 * sp4C;
            break;
    }
}
void BattleAnim_SixSlotTrail_ComputeRotatedOffset(f32 arg0, f32* arg1, f32* arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    UNUSED Mtx sp70;
    Mtx sp30;
    UNUSED s32 pad;

    guRotateF(&sp30, (360.0f * arg0) / 6.2831855f, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(&sp30, 0.0f, 0.0f, arg3, &arg2[0], &arg2[1], &arg2[2]);
}

extern void func_84109780(void *);
extern f32 __sinf(f32);
void BattleAnim_SixSlotTrail_UpdateSlot(S1_unk_D_843C3508* trail) {
    S1_unk_D_843C3508_0A4* node;
    s32 phase; //!bug Retail reads this phase local without initializing it.
    s32 i;
    S1_Vec3f anchor;
    S1_Vec3f *anchor_pointer;
    f32 vertical_modulation;
    f32 depth_offset;
    f32 vertical_offset;
    s32 depth_period;
    s32 modulation_period;
    s32 modulation_shift;
    s32 depth_shift;

    anchor_pointer = &anchor;
    node = &trail->unk_0A4[0];
    for (i = 0; i < 20; i++, node++) {
        if (node->unk_00 > 0.0) {
            modulation_shift = (guRandom() % 20) + 2;
            modulation_period = (guRandom() % 10) + 4;
            depth_shift = (guRandom() % 20) + 2;
            depth_period = (guRandom() % 10) + 4;

            vertical_modulation = __sinf((((phase + modulation_shift) % modulation_period) * 6.2831854820251465) / modulation_period);
            vertical_offset =
                __sinf((((phase + depth_shift) % (depth_period + 20)) * 6.2831854820251465) / (depth_period + 20)) * (10.0 * vertical_modulation);
            depth_offset = __sinf((((phase + depth_shift) % depth_period) * 6.2831854820251465) / depth_period) * 10.0;
            func_84109780(anchor_pointer);
            node->unk_0C.x = anchor.x;
            node->unk_0C.y = anchor.y + vertical_offset;
            node->unk_0C.z = anchor.z + depth_offset;
            node->unk_00 -= 1.0;
        } else {
            node->unk_0C.x += node->unk_18.x;
            node->unk_0C.y += node->unk_18.y;
            node->unk_0C.z += node->unk_18.z;
            node->unk_08 += trail->unk_084;
            node->unk_04 += 3.0f;
            if (trail->unk_080 < node->unk_04) {
                node->unk_04 = trail->unk_080;
            }
        }
    }
}

extern s16 D_841A4DC0;
extern u32 func_841094EC(void);
s32 BattleAnim_SixSlotTrail_UpdateAll(void) {
    f32 fade_fraction;
    s32 i;
    s32 active_count;
    S1_unk_D_843C3508 *trail;
    s32 state_flag;

    trail = (S1_unk_D_843C3508 *)(D_84187DC0 + 2304);
    D_841A4DC2++;
    state_flag = func_841094EC();
    if (state_flag == 1 && D_841A4DC4 == 0) {
        D_841A4DC4 = 1;
        D_841A4DC0 = D_841A4DC2 + 50;
    }
    active_count = 0;
    for (i = 0; i < 6; i++, trail++) {
        if (trail->unk_000 == 1) {
            trail->unk_004++;
            if (trail->unk_006 < trail->unk_004) {
                trail->unk_000 = 0;
            } else {
                BattleAnim_SixSlotTrail_UpdateSlot(trail);
                active_count++;
            }
            if (D_841A4DC4 == 1) {
                if (D_841A4DC0 < D_841A4DC2) {
                    return -1;
                }
                if (D_841A4DC0 - 20 < D_841A4DC2) {
                    s16 fade_tick = D_841A4DC2 - D_841A4DC0 + 20;
                    fade_fraction = fade_tick * 0.05f;
                    trail->unk_014 = 1.0f - fade_fraction;
                    trail->unk_018 = 1.0f - fade_fraction;
                    if (fade_fraction > 1.0f) {
                        trail->unk_014 = 0.0f;
                    }
                    if (trail->unk_018 < 0.0f) {
                        trail->unk_018 = 0.0f;
                    }
                }
            }
        }
    }
    if (active_count > 0) {
        return 0;
    }
    return -1;
}

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

extern Gfx D_84187DD0[];
extern void *Gfx_AllocDisplayList(s32);
extern void Gfx_SetCombineMode(Gfx *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
// Builds and draws each active six-slot trail: 40 vertices from the 20 points (offsets from
// BattleAnim_SixSlotTrail_ComputeRotatedOffset in mode 0, the camera-relative variant in mode
// 1), then the D_84187DD0 render state, combiner, prim/env colors, textures and segments.
// Same body as Pokemon Stadium 1 BattleAnim_SixSlotTrail_DrawAll
// (src/fragments/battle_engine/battle_engine_357C30.c there).
Gfx *func_84169618(Gfx *arg0) {
    s32 i;
    S1_unk_D_843C3508 *var_s6;
    S1_unk_D_843C3508_0A4 *var_s0;
    s32 j;
    s32 k;
    S1_Vec3f spF0;
    Vtx *var_s1;
    s32 pad[12]; // FAKE: unused stack space (also in Stadium 1); sets the frame layout.

    func_841094A4();

    var_s6 = (S1_unk_D_843C3508 *)(D_84187DC0 + 2304);
    for (i = 0; i < 6; i++, var_s6++) {
        if (var_s6->unk_000 == 1) {
            var_s0 = &var_s6->unk_0A4[0];

            var_s6->unk_088 = Gfx_AllocDisplayList(sizeof(Vtx) * 40);
            var_s1 = var_s6->unk_088;

            for (j = 0; j < 20; j++, var_s0++) {
                for (k = 0; k < 2; k++) {
                    switch (var_s6->unk_002) {
                        case 0:
                            if (var_s0->unk_00 <= 0.0) {
                                BattleAnim_SixSlotTrail_ComputeRotatedOffset(var_s0->unk_08 + ((k % 2) * 3.1415927f), &var_s0->unk_18.x, &spF0.x,
                                              var_s0->unk_04, 1.0f, 0.0f, 0.0f);
                            }
                            break;

                        case 1:
                            if (var_s0->unk_00 <= 0.0) {
                                BattleAnim_SixSlotTrail_ComputeCameraRelativeOffset(k % 2, &var_s0->unk_18.x, &var_s0->unk_0C.x, &spF0.x, var_s0->unk_04, 1.0f,
                                              0.0f, 0.0f);
                            }
                            break;
                    }

                    var_s1->v.ob[0] = var_s0->unk_0C.x + spF0.x;
                    var_s1->v.ob[1] = var_s0->unk_0C.y + spF0.y;
                    var_s1->v.ob[2] = var_s0->unk_0C.z + spF0.z;

                    var_s1->v.tc[0] = (k % 2) << 10;
                    var_s1->v.tc[1] = (j * 0x400) / 20;

                    var_s1->v.cn[0] = 0xFF;
                    var_s1->v.cn[1] = 0xFF;
                    var_s1->v.cn[2] = 0xFF;
                    var_s1->v.cn[3] = 0x40;
                    var_s1++;
                }
            }

            gSPDisplayList(arg0++, D_84187DD0);

            Gfx_SetCombineMode(
                arg0++, var_s6->unk_028.unk_00, var_s6->unk_028.unk_04, var_s6->unk_028.unk_08, var_s6->unk_028.unk_0C,
                var_s6->unk_028.unk_10, var_s6->unk_028.unk_14, var_s6->unk_028.unk_18, var_s6->unk_028.unk_1C,
                var_s6->unk_048.unk_00, var_s6->unk_048.unk_04, var_s6->unk_048.unk_08, var_s6->unk_048.unk_0C,
                var_s6->unk_048.unk_10, var_s6->unk_048.unk_14, var_s6->unk_048.unk_18, var_s6->unk_048.unk_1C);

            gDPSetPrimColor(arg0++, 0, var_s6->unk_008.unk_04, var_s6->unk_008.unk_00.r, var_s6->unk_008.unk_00.g,
                            var_s6->unk_008.unk_00.b, (u8)(var_s6->unk_008.unk_00.a * var_s6->unk_014));
            gDPSetEnvColor(arg0++, var_s6->unk_00D.unk_00.r, var_s6->unk_00D.unk_00.g, var_s6->unk_00D.unk_00.b,
                           (u8)(var_s6->unk_00D.unk_00.a * var_s6->unk_018));

            arg0 = BattleAnim_SixSlotTrail_LoadTextures(arg0, var_s6);

            gDPPipeSync(arg0++);

            arg0 = BattleAnim_SixSlotTrail_DrawSegments(arg0, (Func84169214State *)var_s6);
        }
    }

    return arg0;
}

#endif
