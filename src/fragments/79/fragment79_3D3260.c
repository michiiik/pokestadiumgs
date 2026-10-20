#include "global.h"


#ifdef VERSION_US
typedef struct { f32 x, y, z; } TrailVec3f;
typedef struct {
    u8 alpha;
    f32 scale;
    f32 angle;
    TrailVec3f position;
    TrailVec3f velocity;
    f32 previous_scale;
    f32 previous_angle;
    TrailVec3f previous_position;
    TrailVec3f previous_velocity;
} TrailSample;
typedef struct {
    s16 active;
    s16 age;
    s16 lifetime;
    s16 direction;
    u8 color[3];
    f32 scale;
    f32 scale_limit;
    f32 angle_step;
    Vtx *vertices;
    TrailVec3f anchor;
    u8 unk28[12];
    TrailSample samples[15];
} TrailStream;
extern u8 *D_84187A70;
extern f32 func_84109544(void);
void FourStreamTrail_Init(void) {
    f32 scale;
    TrailStream *stream;
    TrailSample *sample;
    s32 i;
    s32 j;

    scale = func_84109544() * 0.75f;
    stream = (TrailStream *)D_84187A70;
    for (i = 0; i < 4; i++, stream++) {
        stream->active = 0;
        stream->age = 0;
        stream->lifetime = 0;
        stream->scale = scale;
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

void FourStreamTrail_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   f32 argA, f32 argB, f32 argC, s16 argD) {
    TrailStream* var_v1;
    TrailSample* var_s0;
    s32 i;
    s32 j;
    TrailVec3f sp64;
    TrailVec3f sp58;

    sp64.x = arg0;
    sp64.y = arg1;
    sp64.z = arg2;
    var_v1 = (TrailStream *)D_84187A70;

    for (i = 0; i < 4; i++, var_v1++) {
        if (var_v1->active == 0) {
            f32 tmp = var_v1->scale;

            var_v1->active = 1;
            var_v1->age = 0;

            var_v1->lifetime = argD;
            var_v1->color[0] = arg6;
            var_v1->color[1] = arg7;
            var_v1->color[2] = arg8;
            var_v1->anchor = sp64;
            var_v1->scale_limit = argC;
            var_v1->angle_step = argA;

            sp58.x = arg3;
            sp58.y = arg4 * tmp;
            sp58.z = arg5 * tmp;

            if (arg3 < 0.0) {
                var_v1->direction = -1;
            } else {
                var_v1->direction = 1;
            }

            var_s0 = &var_v1->samples[0];
            for (j = 0; j < 15; j++, var_s0++) {
                var_s0->alpha = (arg9 * (14 - j)) / 15;
                var_s0->scale = argB;
                var_s0->angle = (((s32)guRandom() % 120) * 6.2831855f) / 120.0;
                var_s0->position = sp64;
                var_s0->velocity = sp58;
            }
            break;
        }
    }
}

void FourStreamTrail_Update(f32 arg0, f32 *arg1, f32 arg2, f32 arg3) {
    f32 spB0[4][4];
    f32 sp70[4][4];
    f32 sp30[4][4];
    UNUSED s32 pad2[2]; // FAKE: inherited unused local; removal changes this helper's original stack offsets.
    guScaleF(sp30, arg3, arg3, arg3);
    guRotateF(sp70, (arg0 * 360.0) / 6.2831854820251465, 1.0f, 0.0f, 0.0f);
    guMtxCatF(sp30, sp70, spB0);
    guMtxXFMF(spB0, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

void FourStreamTrail_UpdateNodeChain(TrailStream *arg0) {
    TrailSample* var_v0 = &arg0->samples[0];
    s32 i;
    f32 temp_fa0;
    f32 temp_fa1;

    for (i = 0; i < 15; i++, var_v0++) {
        if (i == 0) {
            var_v0->previous_scale = var_v0->scale;
            var_v0->previous_angle = var_v0->angle;
            var_v0->previous_position = var_v0->position;
            var_v0->previous_velocity = var_v0->velocity;

            var_v0->position.x += var_v0->velocity.x;
            var_v0->position.y += var_v0->velocity.y;
            var_v0->position.z += var_v0->velocity.z;

            var_v0->angle += arg0->angle_step;
            if (arg0->direction < 0) {
                var_v0->velocity.x += 1.5;
                if (var_v0->velocity.x > 20.0) {
                    var_v0->velocity.x = 20.0f;
                }
            } else {
                var_v0->velocity.x -= 1.5;
                if (var_v0->velocity.x < -20.0) {
                    var_v0->velocity.x = -20.0f;
                }
            }

            if (arg0->age < 15) {
                temp_fa0 = ((15 - arg0->age) * 0.03) / 15.0;
                temp_fa1 = (arg0->age * 0.15) / 15.0;
                var_v0->velocity.y += (arg0->anchor.y - var_v0->position.y) * temp_fa0;
                var_v0->velocity.z += (arg0->anchor.z - var_v0->position.z) * temp_fa0;
                var_v0->position.y += (arg0->anchor.y - var_v0->position.y) * temp_fa1;
                var_v0->position.z += (arg0->anchor.z - var_v0->position.z) * temp_fa1;
            } else {
                var_v0->velocity.y += (arg0->anchor.y - var_v0->position.y) * 0.03;
                var_v0->velocity.z += (arg0->anchor.z - var_v0->position.z) * 0.03;
                var_v0->position.y += (arg0->anchor.y - var_v0->position.y) * 0.15;
                var_v0->position.z += (arg0->anchor.z - var_v0->position.z) * 0.15;
            }

            var_v0->scale += 2.0;
            if (arg0->scale_limit < var_v0->scale) {
                var_v0->scale = arg0->scale_limit;
            }
        } else {
            var_v0->previous_scale = var_v0->scale;
            var_v0->previous_angle = var_v0->angle;

            var_v0->previous_position = var_v0->position;
            var_v0->previous_velocity = var_v0->velocity;

            var_v0->position = var_v0[-1].previous_position;
            var_v0->angle = var_v0[-1].previous_angle;
            var_v0->velocity = var_v0[-1].previous_velocity;
            var_v0->scale = var_v0[-1].previous_scale;
        }
    }
}

s32 FourStreamTrail_IsComplete(void) {
    TrailStream *ptr = (TrailStream *)D_84187A70;
    s32 i = 0;
    while (i != 4) {
        if (ptr->active == 1) {
            ptr->age += 1;
            if (ptr->age > ptr->lifetime) {
                ptr->active = 0;
            } else {
                FourStreamTrail_UpdateNodeChain(ptr);
            }
        }
        i++;
        ptr++;
    }
    return 0;
}

extern void *D_8418CAB4;
extern Gfx D_84187AB8[];
extern Gfx D_84187B20[];
extern void *Gfx_AllocDisplayList(s32);
Gfx* FourStreamTrail_Draw(Gfx* arg0) {
    s32 i;
    s32 j;
    s32 k;
    TrailStream* var_s4;
    TrailSample* temp_s0;
    Mtx* temp_v0;
    TrailVec3f sp134;
    Vtx* var_s0;
    Mtx spF0;
    Mtx spB0;
    s16 var_s3;
    Gfx *strip_display_list;

    gDPPipeSync(arg0++);
    gDPLoadTextureBlock_4b(arg0++, D_8418CAB4, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    var_s4 = (TrailStream *)D_84187A70;
    for (i = 0; i < 4; i++, var_s4++) {
        if (var_s4->active == 1) {
            guScale(&spB0, var_s4->scale, var_s4->scale, var_s4->scale);
            temp_s0 = &var_s4->samples[0];

            if (temp_s0->position.y > 0.0f) {
                temp_v0 = Gfx_AllocDisplayList(sizeof(Mtx));
                guTranslate(temp_v0, temp_s0->position.x, temp_s0->position.y, temp_s0->position.z);
                guRotateRPY(&spF0, (temp_s0->angle * -360.0f * var_s4->direction) / 6.2831854820251465,
                            (var_s4->direction * 90) + 90, 0.0f);
                guMtxCatL(&spF0, temp_v0, temp_v0);
                guMtxCatL(&spB0, temp_v0, temp_v0);

                gSPMatrix(arg0++, temp_v0, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                gSPDisplayList(arg0++, D_84187AB8);
                gSPPopMatrix(arg0++, G_MTX_MODELVIEW);
            }

            var_s4->vertices = Gfx_AllocDisplayList(sizeof(Vtx) * 30);
            var_s0 = var_s4->vertices;

            for (j = 0; j < 15; j++) {
                FourStreamTrail_Update(temp_s0->angle, &sp134.x, temp_s0->scale, var_s4->scale);
                var_s3 = temp_s0->position.y + sp134.y;
                if (var_s3 < 0) {
                    var_s3 = 0;
                }

                var_s0->v.ob[0] = temp_s0->position.x + sp134.x;
                var_s0->v.ob[1] = var_s3;
                var_s0->v.ob[2] = temp_s0->position.z + sp134.z;
                var_s0->v.cn[0] = var_s4->color[0];
                var_s0->v.cn[1] = var_s4->color[1];
                var_s0->v.cn[2] = var_s4->color[2];
                var_s0->v.cn[3] = temp_s0->alpha;
                var_s0++;

                FourStreamTrail_Update(temp_s0->angle + 3.1415927f, &sp134.x, temp_s0->scale, var_s4->scale);

                var_s3 = temp_s0->position.y + sp134.y;
                if (var_s3 < 0) {
                    var_s3 = 0;
                }
                var_s0->v.ob[0] = temp_s0->position.x + sp134.x;
                var_s0->v.ob[1] = var_s3;
                var_s0->v.ob[2] = temp_s0->position.z + sp134.z;
                var_s0->v.cn[0] = var_s4->color[0];
                var_s0->v.cn[1] = var_s4->color[1];
                var_s0->v.cn[2] = var_s4->color[2];
                var_s0->v.cn[3] = temp_s0->alpha;
                var_s0++;

                temp_s0++;
            }

            var_s0 = var_s4->vertices;

            strip_display_list = D_84187B20;
            gSPDisplayList(arg0++, strip_display_list);

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
