#include "global.h"


#ifdef VERSION_US
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
    /* 0x006 */ s16 unk_006;
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
// Four 0x41C-byte streams, each retaining fifteen current/previous samples.
typedef struct { f32 x, y, z; } AnchorTrailVec3f;
typedef struct {
    u8 alpha;
    f32 scale;
    f32 angle;
    AnchorTrailVec3f position;
    AnchorTrailVec3f velocity;
    f32 previous_scale;
    f32 previous_angle;
    AnchorTrailVec3f previous_position;
    AnchorTrailVec3f previous_velocity;
} AnchorTrailSample;
typedef struct {
    s16 active, age, lifetime, direction;
    u8 color[3];
    f32 scale_limit;
    f32 angle_step;
    Vtx *vertices;
    u8 *particle;
    AnchorTrailSample samples[15];
    f32 marker_scale;
} AnchorTrailStream;
// GS adds a live scalar at 0x0C before the pool node's position.
//@src/fragments/79/fragment79_3C60B0.c
typedef struct {
    u8 alpha;
    f32 scale;
    f32 angle;
    f32 unk0C;
    AnchorTrailVec3f position;
    AnchorTrailVec3f velocity;
    AnchorTrailVec3f acceleration;
    f32 previous_scale;
    AnchorTrailVec3f previous_position;
    AnchorTrailVec3f previous_velocity;
} TrailPoolSample;
typedef struct {
    s16 active, age, unk004, unk006, unk008;
    u8 color[3];
    f32 unk010, unk014, unk018;
    u8 unk01C[4];
    Vtx *vertices;
    AnchorTrailVec3f unk024;
    u8 unk030[16];
    TrailPoolSample samples[10];
} TrailPoolRecord;
extern u8 *D_84187BD0;
extern TrailPoolRecord D_8419F070[];
extern s16 D_841A4DB4, D_841A4DB2;
extern s32 BattleAnim_GetSecondaryOwnerSpecies(void);
extern u8 *func_84109B88(AnchorTrailVec3f, u8);
extern void func_84109BA4(u8 *, AnchorTrailVec3f);

void OwnerAnchoredFourStream_Init(void) {
    s32 i;
    s32 j;
    AnchorTrailStream* var_v0 = (AnchorTrailStream *)D_84187BD0;
    AnchorTrailSample* var_a0;

    for (i = 0; i < 4; i++, var_v0++) {
        var_v0->active = 0;
        var_v0->age = 0;
        var_v0->lifetime = 0;
        var_v0->marker_scale = 0.16f;

        var_a0 = &var_v0->samples[0];
        for (j = 0; j < 15; j++, var_a0++) {
            var_a0->alpha = 0;
            var_a0->scale = 1.0f;
            var_a0->angle = 0.0f;
            var_a0->position.x = 0.0f;
            var_a0->position.y = 0.0f;
            var_a0->position.z = 0.0f;
            var_a0->velocity.x = 0.0f;
            var_a0->velocity.y = 0.0f;
            var_a0->velocity.z = 0.0f;
        }
    }
}

void OwnerAnchoredFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   f32 argA, f32 argB, f32 argC, s16 argD) {
    s32 i;
    s32 j;
    AnchorTrailStream* var_v1;
    AnchorTrailSample* var_s0;
    AnchorTrailVec3f sp64;
    AnchorTrailVec3f sp58;

    sp64.x = arg0;
    sp64.y = arg1;
    sp64.z = arg2;
    sp58.x = arg3;
    sp58.y = arg4;
    sp58.z = arg5;

    var_v1 = (AnchorTrailStream *)D_84187BD0;
    for (i = 0; i < 4; i++, var_v1++) {
        if (var_v1->active == 0) {
            var_v1->active = 1;
            var_v1->age = 0;
            var_v1->lifetime = argD;
            var_v1->color[0] = arg6;
            var_v1->color[1] = arg7;
            var_v1->color[2] = arg8;
            var_v1->angle_step = argA;

            if (BattleAnim_GetSecondaryOwnerSpecies() == 0xD) {
                var_v1->marker_scale = 0.08f;
                var_v1->scale_limit = argC * 0.5f;
            } else {
                var_v1->marker_scale = 0.16f;
                var_v1->scale_limit = argC;
            }

            var_v1->particle = func_84109B88(sp64, 2);
            if (arg3 < 0.0) {
                var_v1->direction = -1;
            } else {
                var_v1->direction = 1;
            }

            var_s0 = &var_v1->samples[0];
            for (j = 0; j < 15; j++, var_s0++) {
                var_s0->alpha = (arg9 * (0xE - j)) / 15;
                var_s0->scale = argB;
                var_s0->angle = ((guRandom() % 120) * 6.2831855f) / 120.0;
                var_s0->position = sp64;
                var_s0->velocity = sp58;
            }
            break;
        }
    }
}

void OwnerAnchoredFourStream_Update(f32 arg0, f32 *arg1, f32 arg2) {
    UNUSED f32 pad[16]; // FAKE: inherited unused matrix-sized storage.
    f32 sp30[4][4];
    UNUSED s32 pad2[2]; // FAKE: inherited unused local; cleanup remains unresolved.
    guRotateF(sp30, (arg0 * 360.0) / 6.2831854820251465, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

void OwnerAnchoredFourStream_UpdateNodeChain(u8 *data) {
    AnchorTrailStream *arg0 = (AnchorTrailStream *)data;
    s32 i;
    AnchorTrailSample* var_s0 = &arg0->samples[0];

    for (i = 0; i < 15; i++, var_s0++) {
        if (i == 0) {
            var_s0->previous_scale = var_s0->scale;
            var_s0->previous_angle = var_s0->angle;

            var_s0->previous_position = var_s0->position;
            var_s0->previous_velocity = var_s0->velocity;

            var_s0->position.x += var_s0->velocity.x;
            var_s0->position.y += var_s0->velocity.y;
            var_s0->position.z += var_s0->velocity.z;

            var_s0->angle += arg0->angle_step;
            if (arg0->direction > 0) {
                var_s0->velocity.x += 0.4;
                if (var_s0->velocity.x > 20.0) {
                    var_s0->velocity.x = 20.0f;
                }
            } else {
                var_s0->velocity.x -= 0.4;
                if (var_s0->velocity.x < -20.0) {
                    var_s0->velocity.x = -20.0f;
                }
            }

            func_84109BA4(arg0->particle, var_s0->position);

            var_s0->scale += 2.0;
            if (arg0->scale_limit < var_s0->scale) {
                var_s0->scale = arg0->scale_limit;
            }
        } else {
            var_s0->previous_scale = var_s0->scale;
            var_s0->previous_angle = var_s0->angle;

            var_s0->previous_position = var_s0->position;
            var_s0->previous_velocity = var_s0->velocity;

            var_s0->position = var_s0[-1].previous_position;
            var_s0->angle = var_s0[-1].previous_angle;
            var_s0->velocity = var_s0[-1].previous_velocity;
            var_s0->scale = var_s0[-1].previous_scale;
        }
    }
}

s32 func_84165C2C(void) {
    u8 *ptr = D_84187BD0;
    s32 i = 0;
    do {
        if (*(s16 *)ptr == 1) {
            *(s16 *)(ptr + 2) = *(s16 *)(ptr + 2) + 1;
            if (*(s16 *)(ptr + 4) < *(s16 *)(ptr + 2)) {
                *(s16 *)ptr = 0;
            } else {
                OwnerAnchoredFourStream_UpdateNodeChain(ptr);
            }
        }
        i++;
        ptr += 0x41C;
    } while (i != 4);
    return 0;
}

extern Gfx D_84187BD8[];
extern Gfx D_84188A70[];
extern u32 Gfx_AllocDisplayList(s32);
extern void func_8007D454(void *, f32, f32, f32);
// Draws each active owner-anchored stream: a marker_scale-scaled marker at the head sample,
// then a 30-vertex strip from the 15 samples. Same body as Pokemon Stadium 1
// OwnerAnchoredFourStream_Draw (src/fragments/battle_engine/battle_engine_3540B0.c there).
Gfx *func_84165CC0(Gfx *arg0) {
    s32 i;
    s32 j;
    s32 k;
    AnchorTrailSample *temp_s0;
    AnchorTrailStream *var_s5;
    Vtx *var_s0;
    AnchorTrailVec3f sp154;
    UNUSED s32 pad[15]; // FAKE: unused stack space (also in Stadium 1); sets the frame layout.
    Mtx *temp_v0;
    Mtx sp100;
    Mtx spC0;
    s16 var_s3;

    var_s5 = (AnchorTrailStream *)D_84187BD0;
    for (i = 0; i < 4; i++, var_s5++) {
        if (var_s5->active == 1) {
            temp_s0 = &var_s5->samples[0];
            if (temp_s0->position.y > 0.0f) {
                temp_v0 = (Mtx *)Gfx_AllocDisplayList(sizeof(Mtx) * 1);
                guTranslate(temp_v0, temp_s0->position.x, temp_s0->position.y, temp_s0->position.z);
                func_8007D454(&sp100, (temp_s0->angle * -360.0f * var_s5->direction) / 6.2831854820251465,
                              90 - (var_s5->direction * 90), 0.0f);
                guMtxCatL(&sp100, temp_v0, temp_v0);
                guScale(&spC0, var_s5->marker_scale, var_s5->marker_scale, var_s5->marker_scale);
                guMtxCatL(&spC0, temp_v0, temp_v0);

                gSPMatrix(arg0++, temp_v0, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                gSPDisplayList(arg0++, D_84188A70);
                gSPPopMatrix(arg0++, G_MTX_MODELVIEW);
            }

            var_s5->vertices = (Vtx *)Gfx_AllocDisplayList(sizeof(Vtx) * 30);

            var_s0 = var_s5->vertices;
            for (j = 0; j < 15; j++) {
                OwnerAnchoredFourStream_Update(temp_s0->angle, &sp154.x, temp_s0->scale);

                var_s3 = temp_s0->position.y + sp154.y;
                if (var_s3 < 0) {
                    var_s3 = 0;
                }

                var_s0->v.ob[0] = temp_s0->position.x + sp154.x;
                var_s0->v.ob[1] = var_s3;
                var_s0->v.ob[2] = temp_s0->position.z + sp154.z;
                var_s0->v.cn[0] = var_s5->color[0];
                var_s0->v.cn[1] = var_s5->color[1];
                var_s0->v.cn[2] = var_s5->color[2];
                var_s0->v.cn[3] = temp_s0->alpha;
                var_s0++;

                OwnerAnchoredFourStream_Update(temp_s0->angle + 3.1415927f, &sp154.x, temp_s0->scale);

                var_s3 = temp_s0->position.y + sp154.y;
                if (var_s3 < 0) {
                    var_s3 = 0;
                }

                var_s0->v.ob[0] = temp_s0->position.x + sp154.x;
                var_s0->v.ob[1] = var_s3;
                var_s0->v.ob[2] = temp_s0->position.z + sp154.z;
                var_s0->v.cn[0] = var_s5->color[0];
                var_s0->v.cn[1] = var_s5->color[1];
                var_s0->v.cn[2] = var_s5->color[2];
                var_s0->v.cn[3] = temp_s0->alpha;
                var_s0++;

                temp_s0++;
            }

            var_s0 = var_s5->vertices;

            gSPDisplayList(arg0++, D_84187BD8);

            for (k = 0; k < 14; k++) {
                gSPVertex(arg0++, var_s0, 4, 0);
                gSP2Triangles(arg0++, 0, 2, 1, 0, 2, 3, 1, 0);
                var_s0 += 2;
            }
        }
    }

    return arg0;
}

#endif
