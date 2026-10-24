#include "global.h"


#ifdef VERSION_US
// Translation unit for the 26-record trail pool (Stadium 1 counterpart:
// src/fragments/battle_engine/battle_engine_354CD0.c). Its .text starts at 0x84166130 and its
// .rodata at the 16-byte-aligned 0x8418C8E0; the three zero words that end
// fragment79_3D4DA0.c's .rodata (after func_84165CC0's constants) pad up to that boundary.
typedef struct { f32 x, y, z; } AnchorTrailVec3f;
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
extern TrailPoolRecord D_8419F070[];
extern s16 D_841A4DB4, D_841A4DB2;

// Unlike Stadium 1's fifty-record pool, GS initializes twenty-six records.
void TrailEffectPool_Init(void) {
    TrailPoolRecord* var_v0 = &D_8419F070[0];
    TrailPoolSample* var_a0;
    s32 i;
    s32 j;

    D_841A4DB4 = 0;
    D_841A4DB2 = 0;

    for (i = 0; i < 26; i++, var_v0++) {
        var_v0->active = 0;
        var_v0->unk004 = 0;
        var_v0->unk006 = 0;

        var_a0 = &var_v0->samples[0];

        for (j = 0; j < 10; j++, var_a0++) {
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

extern f32 func_84109544(void);
void TrailEffectPool_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   f32 argA, f32 argB, f32 argC, s16 argD) {
    TrailPoolRecord* var_v1;
    TrailPoolSample* var_s0;
    s32 i;
    s32 j;
    AnchorTrailVec3f sp7C;
    AnchorTrailVec3f sp70;
    AnchorTrailVec3f sp64;
    f32 temp_fv1;

    if (D_841A4DB4 == 2) {
        return;
    }

    temp_fv1 = func_84109544() * 0.5f;

    sp7C.x = arg0;
    sp7C.y = (80.0f * temp_fv1) + arg1;
    sp7C.z = arg2;

    sp70.x = arg3;
    sp70.y = arg4;
    sp70.z = arg5;

    sp64.x = 0.0f;
    sp64.y = temp_fv1 * -2.0;
    sp64.z = 0.0f;

    var_v1 = &D_8419F070[0];

    for (i = 0; i < 26; i++, var_v1++) {
        if (var_v1->active == 0) {
            var_v1->active = 1;
            var_v1->age = 0;
            var_v1->unk004 = 0;
            var_v1->unk006 = argD;
            var_v1->color[0] = arg6;
            var_v1->color[1] = arg7;
            var_v1->color[2] = arg8;
            var_v1->unk024 = sp7C;
            var_v1->unk018 = argC;
            var_v1->unk010 = argA;
            var_v1->unk014 = temp_fv1;

            if (arg0 > 0.0) {
                var_v1->unk008 = -1;
            } else {
                var_v1->unk008 = 1;
            }

            var_s0 = var_v1->samples;
            for (j = 0; j < 10; j++, var_s0++) {
                var_s0->alpha = (arg9 * (9 - j)) / 10;
                var_s0->scale = argB;
                var_s0->angle = ((guRandom() % 120) * 6.2831855f) / 120.0;
                var_s0->position = sp7C;
                var_s0->velocity = sp70;
                var_s0->acceleration = sp64;
            }
            break;
        }
    }
}

void func_8416654C(f32 arg0, f32 *arg1, f32 arg2) {
    f32 sp30[4][4];
    f32 angle = (arg0 * 360.0) / 6.2831854820251465;
    guRotateRPYF(sp30, 90.0f, angle, angle);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D59C0/func_841665D4.s")

extern u32 func_841094EC(void);
extern s16 D_841A4DB0;
extern void func_841665D4(TrailPoolRecord *);
s32 TrailEffectPool_IsComplete(void) {
    s32 i;
    TrailPoolRecord *stream;
    s32 state_flag;

    D_841A4DB2++;
    // Setup routines initialize this flag to 0 or 1; its getter returns u32.
    //@src/fragments/79/fragment79_377F80.c
    state_flag = func_841094EC();
    if (state_flag == 1 && D_841A4DB4 == 0) {
        D_841A4DB0 = D_841A4DB2 + 70;
        D_841A4DB4 = 1;
    } else if (D_841A4DB4 == 1) {
        if (D_841A4DB0 - 50 < D_841A4DB2) {
            D_841A4DB4 = 2;
        }
    } else if (D_841A4DB4 == 2) {
        if (D_841A4DB0 < D_841A4DB2) {
            return -1;
        }
    }
    stream = &D_8419F070[0];
    for (i = 0; i < 26; i++, stream++) {
        if (stream->active == 1) {
            stream->unk004++;
            if (stream->age == 1 && stream->unk006 < stream->unk004) {
                stream->active = 0;
            } else {
                func_841665D4(stream);
            }
        }
    }
    return 0;
}

extern u8 *D_8418CA20[256];
extern Gfx D_84187C30[];
extern Gfx D_84187CC0[];
extern void *Gfx_AllocDisplayList(s32);
extern void func_8007D454(void *, f32, f32, f32);
// Draws the 26 pooled trails with texture D_8418CA20[arg1]: an unk014-scaled marker at each
// active record's head sample, then a 20-vertex strip from its 10 samples. Same body as Pokemon
// Stadium 1 Trail50Effect_Draw (src/fragments/battle_engine/battle_engine_354CD0.c there),
// which draws 50 records with a fixed, wrapping texture.
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D59C0/func_84166A64.s")

#endif
