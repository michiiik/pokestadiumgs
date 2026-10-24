#include "global.h"


#ifdef VERSION_US
typedef struct { f32 x, y, z; } OwnerTrailVec3f;
typedef struct {
    u8 alpha;
    f32 scale;
    f32 angle;
    OwnerTrailVec3f position;
    OwnerTrailVec3f velocity;
    f32 previous_scale;
    f32 previous_angle;
    OwnerTrailVec3f previous_position;
    OwnerTrailVec3f previous_velocity;
} OwnerTrailSample;
typedef struct {
    s16 active;
    s16 age;
    s16 lifetime;
    s16 direction;
    u8 color[3];
    f32 scale_limit;
    f32 angle_step;
    f32 marker_rotation_z;
    Vtx *vertices;
    OwnerTrailVec3f anchor;
    u8 unk28[12];
    u8 *particle;
    OwnerTrailSample samples[15];
} OwnerTrailStream;
extern u8 *D_84187B70;
void OwnerLinkedFourStream_Init(void) {
    OwnerTrailStream *stream;
    OwnerTrailSample *sample;
    s32 i;
    s32 j;

    stream = (OwnerTrailStream *)D_84187B70;
    for (i = 0; i < 4; i++, stream++) {
        stream->active = 0;
        stream->age = 0;
        stream->lifetime = 0;
        sample = stream->samples;
        j = 0;
        while (j != 15) {
            sample->alpha = 0;
            sample->scale = 1.0f;
            sample->angle = 0.0f;
            sample->position.x = 0.0f;
            sample->position.y = 0.0f;
            sample->position.z = 0.0f;
            sample->velocity.x = 0.0f;
            sample->velocity.y = 0.0f;
            sample->velocity.z = 0.0f;
            sample++;
            j++;
        }
    }
}

extern u8 *func_84109B88(OwnerTrailVec3f, u8);
extern void func_84109BA4(u8 *, OwnerTrailVec3f);
extern s16 MathUtil_Atan2s(f32, f32);
void OwnerLinkedFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   f32 arg10, f32 arg11, f32 arg12, s16 arg13) {
    s32 i;
    s32 j;
    OwnerTrailStream* var_v1;
    OwnerTrailSample* var_s0;
    OwnerTrailVec3f sp64;
    OwnerTrailVec3f sp58;

    sp64.x = arg0;
    sp64.y = arg1;
    sp64.z = arg2;

    sp58.x = arg3;
    sp58.y = arg4;
    sp58.z = arg5;

    var_v1 = (OwnerTrailStream *)D_84187B70;
    for (i = 0; i < 4; i++, var_v1++) {
        if (var_v1->active == 0) {
            var_v1->active = 1;
            var_v1->age = 0;
            var_v1->lifetime = arg13;
            var_v1->color[0] = arg6;
            var_v1->color[1] = arg7;
            var_v1->color[2] = arg8;
            var_v1->anchor = sp64;
            var_v1->scale_limit = arg12;
            var_v1->angle_step = arg10;
            var_v1->particle = func_84109B88(sp64, 2);

            if (arg3 < 0.0) {
                var_v1->direction = -1;
            } else {
                var_v1->direction = 1;
            }

            var_s0 = &var_v1->samples[0];
            for (j = 0; j < 15; j++, var_s0++) {
                var_s0->alpha = (arg9 * (14 - j)) / 15;
                var_s0->scale = arg11;
                var_s0->angle = (((s32)guRandom() % 120) * 6.2831855f) / 120.0;
                var_s0->position = sp64;
                var_s0->velocity = sp58;
            }
            break;
        }
    }
}

void OwnerLinkedFourStream_Update(f32 arg0, f32 *arg1, f32 arg2) {
    UNUSED f32 pad[16]; // FAKE: inherited unused matrix-sized storage.
    f32 sp30[4][4];
    UNUSED s32 pad2[2]; // FAKE: inherited unused local; helper cleanup is unresolved.
    guRotateF(sp30, (arg0 * 360.0) / 6.2831854820251465, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

void OwnerLinkedFourStream_UpdateNodeChain(OwnerTrailStream *arg0) {
    OwnerTrailSample* var_s0 = &arg0->samples[0];
    s32 i;
    f32 var_ft4;

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

            if (arg0->age < 10) {
                f32 tmp1 = (((10 - arg0->age) * 0.01) / 10.0);
                f32 tmp2 = ((arg0->age * 0.07) / 10.0);

                var_s0->velocity.y += (arg0->anchor.y - var_s0->position.y) * tmp1;
                var_ft4 = (arg0->anchor.y - var_s0->position.y) * tmp2;
            } else {
                var_s0->velocity.y += ((arg0->anchor.y - var_s0->position.y) * 0.01);
                var_ft4 = (arg0->anchor.y - var_s0->position.y) * 0.07;
            }
            var_s0->position.y += var_ft4;
            arg0->marker_rotation_z = (MathUtil_Atan2s(var_s0->velocity.x, var_s0->velocity.y + var_ft4) * 360.0) / 65535.0;

            func_84109BA4(arg0->particle, var_s0->position);

            if (arg0->age == 1) {
                func_84109B88(var_s0->position, 1);
            }

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

extern void func_84109B9C(u8 *);
s32 OwnerLinkedFourStream_IsComplete(void) {
    OwnerTrailStream *ptr = (OwnerTrailStream *)D_84187B70;
    s32 i = 0;
    do {
        if (ptr->active == 1) {
            ptr->age += 1;
            if (ptr->lifetime < ptr->age) {
                ptr->active = 0;
                func_84109B9C(ptr->particle);
            } else {
                OwnerLinkedFourStream_UpdateNodeChain(ptr);
            }
        }
        i++;
        ptr++;
    } while (i != 4);
    return 0;
}

extern Gfx D_84187B78[];
extern Gfx D_84188A70[];
extern void *Gfx_AllocDisplayList(s32);
extern void func_8007D454(void *, f32, f32, f32);
// Draws each active owner-linked stream: a 0.09-scale marker (D_84188A70) at the head sample,
// then a 30-vertex strip from the 15 samples. Same body as Pokemon Stadium 1
// OwnerLinkedFourStream_Draw (src/fragments/battle_engine/battle_engine_353370.c there).
Gfx *func_841650A8(Gfx *arg0) {
    s32 i;
    s32 j;
    s32 k;
    OwnerTrailStream *var_s5;
    OwnerTrailSample *temp_s0;
    Mtx *temp_v0;
    OwnerTrailVec3f sp154;
    UNUSED s32 pad[14]; // FAKE: unused stack space (also in Stadium 1); sets the frame layout.
    s16 var_s3;
    Vtx *var_s0;
    Mtx spD0;
    Mtx sp90;
    UNUSED s32 pad2; // FAKE

    var_s5 = (OwnerTrailStream *)D_84187B70;
    for (i = 0; i < 4; i++, var_s5++) {
        if (var_s5->active == 1) {
            temp_s0 = &var_s5->samples[0];
            if (temp_s0->position.y > 0.0f) {
                temp_v0 = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
                guTranslate(temp_v0, temp_s0->position.x, temp_s0->position.y, temp_s0->position.z);
                func_8007D454(&spD0, (temp_s0->angle * -360.0f * var_s5->direction) / 6.2831854820251465, 0.0f,
                              var_s5->marker_rotation_z);
                guMtxCatL(&spD0, temp_v0, temp_v0);
                guScale(&sp90, 0.09f, 0.09f, 0.09f);
                guMtxCatL(&sp90, temp_v0, temp_v0);

                gSPMatrix(arg0++, temp_v0, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                gSPDisplayList(arg0++, D_84188A70);
                gSPPopMatrix(arg0++, G_MTX_MODELVIEW);
            }

            var_s5->vertices = Gfx_AllocDisplayList(sizeof(Vtx) * 30);
            var_s0 = var_s5->vertices;

            for (j = 0; j < 15; j++) {
                OwnerLinkedFourStream_Update(temp_s0->angle, &sp154.x, temp_s0->scale);

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

                OwnerLinkedFourStream_Update(temp_s0->angle + 3.1415927f, &sp154.x, temp_s0->scale);

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

            gSPDisplayList(arg0++, D_84187B78);

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
