#include "global.h"


#ifdef VERSION_US
typedef struct Strip400Node_79 {
    f32 unk_00;
    f32 unk_04;
    f32 unk_08;
    f32 unk_0C;
} Strip400Node_79;
typedef struct { u8 r, g, b; } Fragment79StripRGB;
typedef struct Strip400State_79 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    f32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    s16 unk_28;
    s16 unk_2A;
    Vtx *vertices;
    Fragment79StripRGB color;
    Fragment79StripRGB environment_color;
    u8 unknown_36[2];
    Strip400Node_79 nodes[400];
} Strip400State_79;
extern Strip400State_79 *D_84187498;
void Strip400_Initialize(f32 x, f32 y, f32 z, f32 scale, u8 r, u8 g, u8 b, u8 er, u8 eg, u8 eb) {
    Strip400State_79 *state;
    Strip400Node_79 *node;
    s32 i;

    state = D_84187498;
    state->unk_00 = 0;
    state->unk_02 = 0;
    state->unk_04 = 0;
    state->unk_06 = 70;
    state->unk_08 = x;
    state->unk_0C = y;
    state->unk_10 = z;
    state->unk_14 = scale * 40.0;
    state->unk_18 = scale * 20.0;
    state->unk_1C = 0.0f;
    state->unk_20 = scale;
    state->unk_24 = 1.0f;
    state->unk_28 = 0;
    state->unk_2A = 0;
    state->color.r = r;
    state->color.g = g;
    state->color.b = b;
    state->environment_color.r = er;
    state->environment_color.g = eg;
    state->environment_color.b = eb;
    node = state->nodes;
    for (i = 0; i < 400; i++) {
        node->unk_00 = x;
        node->unk_04 = y;
        node->unk_08 = z;
        node->unk_0C = state->unk_14;
        node++;
    }
}

f32 func_8415BCD8(void) {
    Strip400State_79 *ptr;
    f32 tmp;
    s32 tmp2;
    ptr = D_84187498;
    tmp2 = ptr->unk_00;
    if (tmp2 < (ptr->unk_06 - 0x34)) {
        return 1.0f;
    }
    if (ptr->unk_18 == 0.0f) {
        return 1.0f;
    }
    tmp = (ptr->nodes[0].unk_0C * 2.0f) / (ptr->unk_14 + ptr->unk_18);
    return tmp;
}

typedef struct { f32 x; f32 y; f32 z; } Fragment79StripAnchor;
extern f32 __sinf(f32);
extern f32 __cosf(f32);
extern void func_8410971C(s32);
extern void func_84109B1C(s32);
s32 Strip400_Update(s32 alternate_anchor) {
    s32 section;
    f32 vertex_x;
    f32 center_y;
    f32 primary_angle;
    f32 secondary_angle;
    f32 vertex_z;
    f32 y_delta;
    Strip400Node_79 * node;
    Strip400State_79 *state = D_84187498;
    f32 anchor_x;
    f32 anchor_y;
    f32 anchor_z;
    f32 extent;
    s16 age;
    Fragment79StripAnchor anchor;

    state->unk_00++;
    if (state->unk_06 < state->unk_00) {
        return -1;
    }

    if ((state->unk_06 - 40) < state->unk_00) {
        state->unk_00 = state->unk_06 - 52;
        state->unk_02++;
        if (state->unk_02 >= 21) {
            return -1;
        }
    } else if (state->unk_00 < 30) {
        state->unk_2A += 10;
        if (state->unk_2A > 200) {
            state->unk_2A = 200;
        }
    }

    if (alternate_anchor == 0) {
        func_8410971C((s32)&anchor);
    } else {
        func_84109B1C((s32)&anchor);
    }
    anchor_x = anchor.x;
    anchor_y = anchor.y;
    anchor_z = anchor.z;

    state->unk_28 += 6;
    if (state->unk_28 > 200) {
        state->unk_28 = 200;
    }

    if (((state->unk_06 - 52) < state->unk_00) && (state->unk_00 < (state->unk_06 - 40))) {
        state->unk_24 -= 0.1;
        if (state->unk_24 < 0.25) {
            state->unk_24 = 0.25f;
        }
    }

    node = state->nodes;

    for (section = 0; section < state->unk_28; section++) {
        age = state->unk_00;

        if ((state->unk_06 - 40) < age) {
            node->unk_0C -= 6.0;
            if (node->unk_0C < state->unk_18) {
                node->unk_0C = state->unk_18;
            }
            // M_PI * 80
            y_delta = __sinf((((state->unk_00 + section) % 200) * 251.327419281005859) / 200.0) * 0.1;
        } else if ((state->unk_06 - 45) < age) {
            y_delta = __sinf((((state->unk_00 + section) % 200) * 251.327419281005859) / 200.0) + 2.0;
            node->unk_0C += y_delta;
        } else if ((state->unk_06 - 52) < age) {
            node->unk_0C -= 8.0;
            if (node->unk_0C < state->unk_18) {
                node->unk_0C = state->unk_18;
            }
            y_delta = __sinf((((state->unk_00 + section) % 200) * 251.327419281005859) / 200.0) * 0.1;
        } else {
            // M_PI * 60
            y_delta = __sinf((((state->unk_00 + section) % 200) * 188.495564460754395) / 200.0);
            node->unk_0C += y_delta;
        }

        extent = node->unk_0C;

        // M_PI * 22
        primary_angle = (((age + section) % 200) * 69.1150403022766113) / 200.0;
        // M_PI * 4
        secondary_angle = (((age + section) % 200) * 12.566370964050293) / 200.0;

        vertex_x = (__sinf(primary_angle) * extent) + anchor_x;
        center_y = (__sinf(secondary_angle) * (0.7 * extent)) + anchor_y;
        vertex_z = __cosf(primary_angle) * extent + anchor_z;

        node->unk_08 = vertex_z;
        node->unk_04 = center_y + y_delta;
        node->unk_00 = vertex_x;
        node++;

        node->unk_00 = vertex_x;
        node->unk_04 = (2.0 * __sinf(secondary_angle * 3.0)) + center_y + y_delta;
        node->unk_08 = vertex_z;
        node++;
    }

    return 0;
}

extern void *Gfx_AllocDisplayList(s32);
extern Gfx D_841874A0[];
Gfx *Strip400_Draw(Gfx *display_list) {
    s32 i;
    Vtx *vertex;
    Strip400Node_79 *node;
    Strip400State_79 *state;

    state = D_84187498;
    if (state->unk_28 < 2) {
        return display_list;
    }
    vertex = Gfx_AllocDisplayList(state->unk_28 * 2 * sizeof(Vtx));
    state->vertices = vertex;
    node = state->nodes;
    for (i = 0; i < state->unk_28; i++) {
        vertex->v.ob[0] = node->unk_00;
        if (node->unk_04 > 0.0) {
            vertex->v.ob[1] = node->unk_04;
        } else {
            vertex->v.ob[1] = 0;
        }
        vertex->v.ob[2] = node->unk_08;
        vertex->v.tc[0] = (i * 8) << 5;
        vertex->v.tc[1] = 0;
        vertex++;
        node++;

        vertex->v.ob[0] = node->unk_00;
        if (node->unk_04 > 0.0) {
            vertex->v.ob[1] = node->unk_04;
        } else {
            vertex->v.ob[1] = 0;
        }
        vertex->v.ob[2] = node->unk_08;
        vertex->v.tc[0] = (i * 8) << 5;
        vertex->v.tc[1] = 512;
        vertex++;
        node++;
    }
    gSPDisplayList(display_list++, D_841874A0);
    gDPSetPrimColor(display_list++, 0, 0, state->color.r, state->color.g, state->color.b, 200);
    gDPSetEnvColor(display_list++, state->environment_color.r, state->environment_color.g, state->environment_color.b, 0);
    vertex = state->vertices;
    for (i = 0; i < state->unk_28 - 1; i++) {
        gSPVertex(display_list++, vertex, 4, 0);
        gSP2Triangles(display_list++, 0, 2, 1, 0, 2, 3, 1, 0);
        vertex += 2;
    }
    return display_list;
}

typedef struct Radial20Node_79 { f32 unk_00; u8 unk_04; u8 pad_05[3]; f32 unk_08; f32 unk_0C; f32 unk_10; f32 unk_14; f32 unk_18; f32 unk_1C; f32 unk_20; f32 unk_24; u8 pad_28[0x20]; } Radial20Node_79;
typedef struct Radial20_79 { s16 unk_000; s16 unk_002; s16 unk_004; s16 unk_006; u8 pad_008[0x40]; Radial20Node_79 unk_048[20]; } Radial20_79;
extern u8 *D_84187530; extern s16 func_84169BA8(void);
void func_8415C530(void) {
    s16 temp_v0; s32 i; s32 j; Radial20_79 *var_a2; Radial20Node_79 *var_v1;
    temp_v0=func_84169BA8(); var_a2=(Radial20_79 *)(D_84187530+0x3C8);
    for(i=0;i<10;i++) {
        var_a2->unk_000=0; var_a2->unk_004=0; var_a2->unk_006=0; var_v1=&var_a2->unk_048[0];
        for(j=0;j<20;j++,var_v1++) {
            var_v1->unk_00=0.0f; var_v1->unk_04=0; var_v1->unk_08=1.0f; var_v1->unk_0C=0.0f;
            var_v1->unk_10=0.0f; var_v1->unk_14=0.0f; var_v1->unk_18=0.0f; var_v1->unk_1C=0.0f;
            var_v1->unk_20=0.0f; var_v1->unk_24=0.0f;
        }
        var_a2->unk_002=temp_v0;
        var_a2++;
    }
}

typedef struct { f32 x; f32 y; f32 z; } Fragment79RadialVector;
typedef struct {
    f32 ordinal;
    u8 alpha;
    u8 unknown_05[3];
    f32 scale;
    f32 angle;
    Fragment79RadialVector position;
    Fragment79RadialVector velocity;
    u8 unknown_28[0x20];
} Fragment79RadialNode;
typedef struct {
    s16 active;
    s16 resource;
    s16 age;
    s16 duration;
    s16 type;
    u8 r, g, b, a, er, eg, eb;
    u8 unknown_11[3];
    f32 field_14;
    f32 field_18;
    u8 unknown_1C[0x1C];
    s32 field_38[3];
    u8 unknown_44[4];
    Fragment79RadialNode nodes[20];
} Fragment79RadialState;
extern u8 *D_84187530;
void Radial20_StartStraight(f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz, s16 type, u8 r, u8 g, u8 b, u8 alpha, f32 field_18, f32 scale, f32 field_14, s16 duration) {
    Fragment79RadialState *state;
    Fragment79RadialNode *node;
    s32 i;
    s32 j;
    Fragment79RadialVector position;
    Fragment79RadialVector velocity;

    position.x = x;
    position.y = y;
    position.z = z;
    velocity.x = vx;
    velocity.y = vy;
    velocity.z = vz;
    state = (Fragment79RadialState *)(D_84187530 + 0x3C8);
    for (i = 0; i < 10; i++, state++) {
        if (state->active == 0) {
            state->active = 1;
            state->age = 0;
            state->duration = duration;
            state->type = type;
            state->r = r;
            state->g = g;
            state->b = b;
            state->a = alpha;
            state->field_14 = field_14;
            state->field_18 = field_18;
            for (j = 0; j < 3; j++) state->field_38[j] = 0;
            node = state->nodes;
            for (j = 0; j < 20; j++) {
                node->ordinal = j;
                if (j == 0) {
                    node->alpha = 255;
                } else {
                    node->alpha = (alpha * (19 - j)) / 20;
                }
                node->scale = scale;
                node->angle = 0.0f;
                node->position = position;
                node->velocity = velocity;
                node++;
            }
            return;
        }
    }
}

extern u8 * D_84187530;
void Radial20_StartYVelocityWave(
    f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz,
    s16 type, u8 r, u8 g, u8 b, u8 alpha, u8 er,
    u8 eg, u8 eb, f32 field_18, f32 scale, f32 field_14, s16 duration) {
    Fragment79RadialState *state;
    Fragment79RadialNode *node;
    s32 i;
    s32 j;
    Fragment79RadialVector position;
    Fragment79RadialVector velocity;
    s32 phase1;
    s32 period1;
    s32 seed2;
    s32 phase2;
    s32 period2;
    s32 seed1;
    f32 sine;

    position.x = x;
    position.y = y;
    position.z = z;
    velocity.x = vx;
    velocity.y = vy;
    velocity.z = vz;
    state = (Fragment79RadialState *)(D_84187530 + 0x3C8);
    for (i = 0; i < 10; i++, state++) {
        if (state->active == 0) {
            state->active = 1;
            state->age = 0;
            state->duration = duration;
            state->type = type;
            state->r = r;
            state->g = g;
            state->b = b;
            state->a = alpha;
            state->er = er;
            state->eg = eg;
            state->eb = eb;
            state->field_14 = field_14;
            state->field_18 = field_18;
            node = state->nodes;
            seed1 = (guRandom() % 20) + 2;
            period1 = (guRandom() % 10) + 4;
            seed2 = (guRandom() % 20) + 2;
            period2 = (guRandom() % 10) + 4;
            phase1 = seed1;
            for (j = 0, phase2 = seed2; j < 20; j++, phase2++, phase1++, node++) {
                node->ordinal = j;
                node->alpha = alpha;
                node->scale = scale;
                node->angle = 0.0f;
                node->position = position;
                node->velocity = velocity;
                sine = __sinf(((phase2 % (period2 + 20)) * 6.2831854820251465) / (period2 + 20));
                node->velocity.y += 2.0 * __sinf(((phase1 % period1) * 6.2831854820251465) / period1) * sine;
                node->velocity.z += 0.5 * __sinf(((phase2 % period2) * 6.2831854820251465) / period2);
                node->position.x += node->velocity.x * ((j * 0.5) - (s32)(j * 0.5));
            }
            break;
        }
    }
}

void Radial20_StartZVelocityWave(
    f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz,
    s16 type, u8 r, u8 g, u8 b, u8 alpha, u8 er,
    u8 eg, u8 eb, f32 field_18, f32 scale, f32 field_14, s16 duration) {
    Fragment79RadialState *state;
    Fragment79RadialNode *node;
    s32 i;
    s32 j;
    Fragment79RadialVector position;
    Fragment79RadialVector velocity;
    s32 phase1;
    s32 period1;
    s32 seed2;
    s32 phase2;
    s32 period2;
    s32 seed1;
    f32 sine;

    position.x = x;
    position.y = y;
    position.z = z;
    velocity.x = vx;
    velocity.y = vy;
    velocity.z = vz;
    state = (Fragment79RadialState *)(D_84187530 + 0x3C8);
    for (i = 0; i < 10; i++, state++) {
        if (state->active == 0) {
            state->active = 1;
            state->age = 0;
            state->duration = duration;
            state->type = type;
            state->r = r;
            state->g = g;
            state->b = b;
            state->a = alpha;
            state->er = er;
            state->eg = eg;
            state->eb = eb;
            state->field_14 = field_14;
            state->field_18 = field_18;
            node = state->nodes;
            seed1 = (guRandom() % 20) + 2;
            period1 = (guRandom() % 10) + 4;
            seed2 = (guRandom() % 20) + 2;
            period2 = (guRandom() % 10) + 4;
            phase1 = seed1;
            for (j = 0, phase2 = seed2; j < 20; j++, phase2++, phase1++, node++) {
                node->ordinal = j;
                node->alpha = alpha;
                node->scale = scale;
                node->angle = 0.0f;
                node->position = position;
                node->velocity = velocity;
                sine = __sinf(((phase2 % (period2 + 20)) * 6.2831854820251465) / (period2 + 20));
                node->velocity.z += 2.5 * __sinf(((phase1 % period1) * 6.2831854820251465) / period1) * sine;
                node->velocity.y += 0.5 * __sinf(((phase2 % period2) * 6.2831854820251465) / period2);
                node->position.x += node->velocity.x * ((j * 0.5) - (s32)(j * 0.5));
            }
            break;
        }
    }
}

void Radial20_StartPositionWaves(
    f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz,
    s16 type, u8 r, u8 g, u8 b, u8 alpha, f32 field_18,
    f32 scale, f32 field_14, s16 duration) {
    Fragment79RadialState *state;
    Fragment79RadialNode *node;
    s32 i;
    s32 j;
    Fragment79RadialVector position;
    Fragment79RadialVector velocity;
    s32 period2;
    s32 seed1;
    s32 seed2;
    s32 period1;

    position.x = x;
    position.y = y;
    position.z = z;
    velocity.x = vx;
    velocity.y = vy;
    velocity.z = vz;
    state = (Fragment79RadialState *)(D_84187530 + 0x3C8);
    for (i = 0; i < 10; i++, state++) {
        if (state->active == 0) {
            node = state->nodes;
            state->active = 1;
            state->age = 0;
            state->duration = duration;
            state->type = type;
            state->r = r;
            state->g = g;
            state->b = b;
            state->field_14 = field_14;
            state->field_18 = field_18;
            seed1 = (guRandom() % 20) + 2;
            period1 = (guRandom() % 10) + 4;
            seed2 = (guRandom() % 20) + 2;
            period2 = (guRandom() % 10) + 4;
            for (j = 0; j < 20; j++) {
                node->ordinal = j;
                node->alpha = alpha;
                node->scale = scale;
                node->angle = 0.0f;
                node->position = position;
                node->position.y += 5.0 * __sinf((((seed1 + j) % period1) * 6.2831854820251465) / period1) * __sinf((((seed2 + j) % (period2 + 20)) * 6.2831854820251465) / (period2 + 20));
                node->position.z += 5.0 * __cosf((((seed1 + j) % period1) * 6.2831854820251465) / period1) * __cosf((((seed2 + j) % (period2 + 20)) * 6.2831854820251465) / (period2 + 20));
                node->velocity = velocity;
                node->position.x += node->velocity.x * ((j * 0.5) - (s32)(j * 0.5));
                node++;
            }
            break;
        }
    }
}

void Radial20_RotateVertexOffset(f32 arg0, f32 *arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    UNUSED f32 pad[16];
    f32 sp30[4][4];
    UNUSED s32 pad2[2];
    guRotateF(sp30, (arg0 * 360.0) / 6.2831854820251465, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg3, &arg2[0], &arg2[1], &arg2[2]);
}

extern void func_84109780(void *);
extern void Radial20_UpdateNodes(Fragment79RadialState *);
void Radial20_UpdateNodes(Fragment79RadialState *state) {
    Fragment79RadialVector *anchor_position;
    Fragment79RadialNode *node;
    s32 i;
    Fragment79RadialVector anchor;

    anchor_position = &anchor;
    func_84109780(anchor_position);
    switch (state->type) {
    case 0:
        node = state->nodes;
        for (i = 0; i < 20; i++, node++) {
            if (node->ordinal > 0.0) {
                node->ordinal -= 1.0;
            } else {
                node->position.x += node->velocity.x;
                node->position.y += node->velocity.y;
                node->position.z += node->velocity.z;
                node->angle += state->field_18;
                node->scale += 1.0;
                if (state->field_14 < node->scale) {
                    node->scale = state->field_14;
                }
            }
        }
        break;
    case 2:
        node = state->nodes;
        for (i = 0; i < 20; i++, node++) {
            if (node->ordinal > 0.0) {
                node->position = *anchor_position;
                node->ordinal -= 1.0;
            } else {
                node->position.x += node->velocity.x;
                node->position.y += node->velocity.y;
                node->position.z += node->velocity.z;
                node->angle += state->field_18;
                if (node->velocity.x > 1.0) {
                    node->velocity.x -= 0.1;
                }
                if (node->velocity.x < -1.0) {
                    node->velocity.x += 0.1;
                }
                node->velocity.y -= 0.2;
                if (node->velocity.y < -1.0) {
                    node->velocity.y = -1.0f;
                }
                if (node->position.y < 0.0) {
                    node->position.y = 0.0f;
                }
            }
        }
        break;
    case 1:
    case 3:
    default:
        node = state->nodes;
        for (i = 0; i < 20; i++, node++) {
            if (node->ordinal > 0.0) {
                node->position = *anchor_position;
                node->ordinal -= 1.0;
            } else {
                node->position.x += node->velocity.x;
                node->position.y = anchor_position->y;
                node->position.z = anchor_position->z;
                node->angle += state->field_18;
                node->scale += 1.0;
                if (state->field_14 < node->scale) {
                    node->scale = state->field_14;
                }
            }
        }
        break;
    case 4:
    case 5:
        node = state->nodes;
        for (i = 0; i < 20; i++, node++) {
            if (node->ordinal > 0.0) {
                node->ordinal -= 1.0;
            } else {
                node->position.x += node->velocity.x;
                node->position.y += node->velocity.y;
                node->position.z += node->velocity.z;
                node->angle += state->field_18;
                node->scale += 1.0;
                if (state->field_14 < node->scale) {
                    node->scale = state->field_14;
                }
            }
        }
        break;
    }
}

typedef struct Radial20Complete_79 { s16 unk_000; s16 unk_002; s16 unk_004; s16 unk_006; s16 unk_008; u8 pad_00A[0x3E]; Radial20Node_79 unk_048[20]; } Radial20Complete_79;
extern void func_84169DBC(s16);
s32 func_8415DAE4(void) {
    s32 i;
    s32 var_s2 = 0;
    Fragment79RadialState *var_s0 = (Fragment79RadialState *)(D_84187530 + 0x3C8);
    for (i = 0; i < 10; i++, var_s0++) {
        if (var_s0->active == 1) {
            var_s0->age++;
            if (var_s0->duration < var_s0->age) {
                var_s0->active = 0;
                if (var_s0->type == 5) {
                }
            } else {
                Radial20_UpdateNodes(var_s0);
                var_s2++;
            }
            func_84169DBC(var_s0->resource);
        }
    }
    if (var_s2 > 0) return 0;
    return -1;
}

typedef struct { u8 r, g, b, a; } Fragment79RadialRenderRGBA;
typedef struct {
    s16 active, resource, age, duration, type;
    Fragment79RadialRenderRGBA color;
    Fragment79StripRGB environment_color;
    u8 unknown_11[3];
    f32 field_14, field_18;
    Vtx *vertices;
    u8 unknown_20[40];
    Fragment79RadialNode nodes[20];
} Fragment79RadialRenderState;
extern Gfx D_84187538[], D_841875C0[];
extern u8 D_84187610[], D_84187614[], D_84187618[];
extern f32 D_8418761C[];
extern void AuxiliaryEffect_Spawn(s16, f32, f32, f32, s16, f32);
extern Gfx *AuxiliaryEffect_Draw(s16, Gfx *);
extern void * Gfx_AllocDisplayList(s32);
extern void Radial20_RotateVertexOffset(f32 arg0, f32 *arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
Gfx *Radial20_Draw(Gfx *display_list) {
    s32 slot_index;
    s32 x;
    s32 j;
    s32 y;
    Fragment79RadialRenderState *state;
    Fragment79RadialNode *node;
    Vtx* vertex;
    Fragment79RadialVector offset;

    state = (Fragment79RadialRenderState *)(D_84187530 + 0x3C8);

    for (slot_index = 0; slot_index < 10; slot_index++) {
        if (state->active == 1) {
            node = &state->nodes[0];

            switch (state->type) {
                case 0:
                case 2:
                    vertex = Gfx_AllocDisplayList(sizeof(Vtx) * 40);
                    state->vertices = vertex;

                    for (j = 0; j < 20; j++, vertex++) {
                        Radial20_RotateVertexOffset(node->angle, &node->velocity.x, &offset.x, node->scale, 1.0f, 0.0f, 0.0f);

                        vertex->v.ob[0] = node->position.x + offset.x;
                        vertex->v.ob[1] = node->position.y + offset.y;
                        vertex->v.ob[2] = node->position.z + offset.z;
                        vertex->v.tc[0] = (j * 8) << 5;
                        vertex->v.tc[1] = 0;
                        vertex++;

                        if (node->ordinal <= 0.0) {
                            Radial20_RotateVertexOffset(node->angle + 3.14159274101257324f, &node->velocity.x, &offset.x, node->scale, 1.0f, 0.0f,
                                          0.0f);
                        }

                        vertex->v.ob[0] = node->position.x + offset.x;
                        vertex->v.ob[1] = node->position.y + offset.y;
                        vertex->v.ob[2] = node->position.z + offset.z;
                        vertex->v.tc[0] = (j * 8) << 5;
                        vertex->v.tc[1] = 0x200;
                        node++;
                    }
                    break;

                case 1:
                    vertex = Gfx_AllocDisplayList(sizeof(Vtx) * 60);
                    state->vertices = vertex;

                    for (j = 0; j < 20; j++, vertex++) {
                        Radial20_RotateVertexOffset(node->angle, &node->velocity.x, &offset.x, node->scale, 1.0f, 0.0f, 0.0f);

                        vertex->v.ob[0] = node->position.x + offset.x;
                        vertex->v.ob[1] = node->position.y + offset.y;
                        vertex->v.ob[2] = node->position.z + offset.z;
                        vertex->v.cn[0] = 0xFF;
                        vertex->v.cn[1] = 0x40;
                        vertex->v.cn[2] = 0x40;
                        vertex->v.cn[3] = node->alpha;
                        vertex++;

                        if (node->ordinal <= 0.0) {
                            Radial20_RotateVertexOffset(node->angle + 2.09439516067504883, &node->velocity.x, &offset.x, node->scale, 1.0f,
                                          0.0f, 0.0f);
                        }

                        vertex->v.ob[0] = node->position.x + offset.x;
                        vertex->v.ob[1] = node->position.y + offset.y;
                        vertex->v.ob[2] = node->position.z + offset.z;
                        vertex->v.cn[0] = 0;
                        vertex->v.cn[1] = 0xA0;
                        vertex->v.cn[2] = 0xFF;
                        vertex->v.cn[3] = node->alpha;
                        vertex++;

                        if (node->ordinal <= 0.0) {
                            Radial20_RotateVertexOffset(node->angle + 2.09439516067504883 * 2, &node->velocity.x, &offset.x, node->scale, 1.0f,
                                          0.0f, 0.0f);
                        }

                        vertex->v.ob[0] = node->position.x + offset.x;
                        vertex->v.ob[1] = node->position.y + offset.y;
                        vertex->v.ob[2] = node->position.z + offset.z;
                        vertex->v.cn[0] = 0xFF;
                        vertex->v.cn[1] = 0xFF;
                        vertex->v.cn[2] = 0;
                        vertex->v.cn[3] = node->alpha;
                        node++;
                    }
                    break;

                case 3:
                    vertex = Gfx_AllocDisplayList(sizeof(Vtx) * 60);
                    state->vertices = vertex;

                    for (j = 0; j < 20; j++, vertex++) {
                        Radial20_RotateVertexOffset(node->angle, &node->velocity.x, &offset.x, node->scale, 1.0f, 0.0f, 0.0f);

                        vertex->v.ob[0] = node->position.x + offset.x;
                        vertex->v.ob[1] = node->position.y + offset.y;
                        vertex->v.ob[2] = node->position.z + offset.z;
                        vertex->v.cn[0] = state->color.r;
                        vertex->v.cn[1] = state->color.g;
                        vertex->v.cn[2] = state->color.b;
                        vertex->v.cn[3] = node->alpha;
                        vertex++;

                        if (node->ordinal <= 0.0) {
                            Radial20_RotateVertexOffset(node->angle + 2.09439516067504883, &node->velocity.x, &offset.x, node->scale, 1.0f,
                                          0.0f, 0.0f);
                        }

                        vertex->v.ob[0] = node->position.x + offset.x;
                        vertex->v.ob[1] = node->position.y + offset.y;
                        vertex->v.ob[2] = node->position.z + offset.z;
                        vertex->v.cn[0] = state->color.r;
                        vertex->v.cn[1] = state->color.g;
                        vertex->v.cn[2] = state->color.b;
                        vertex->v.cn[3] = node->alpha;
                        vertex++;

                        if (node->ordinal <= 0.0) {
                            Radial20_RotateVertexOffset(node->angle + 2.09439516067504883 * 2, &node->velocity.x, &offset.x, node->scale, 1.0f,
                                          0.0f, 0.0f);
                        }

                        vertex->v.ob[0] = node->position.x + offset.x;
                        vertex->v.ob[1] = node->position.y + offset.y;
                        vertex->v.ob[2] = node->position.z + offset.z;
                        vertex->v.cn[0] = state->color.r;
                        vertex->v.cn[1] = state->color.g;
                        vertex->v.cn[2] = state->color.b;
                        vertex->v.cn[3] = node->alpha;
                        node++;
                    }
                    break;

                case 4:
                    vertex = Gfx_AllocDisplayList(sizeof(Vtx) * 20 * 6);
                    state->vertices = vertex;

                    for (j = 0; j < 20; j++, node++) {
                        for (x = 0; x < 6; x++) {
                            Radial20_RotateVertexOffset(node->angle + ((2.0 * x * 3.14159274101257324f) / 6.0), &node->velocity.x, &offset.x,
                                          node->scale, 1.0f, 0.0f, 0.0f);

                            vertex->v.ob[0] = node->position.x + offset.x;
                            vertex->v.ob[1] = node->position.y + offset.y;
                            vertex->v.ob[2] = node->position.z + offset.z;
                            vertex->v.cn[0] = state->color.r;
                            vertex->v.cn[1] = state->color.g;
                            vertex->v.cn[2] = state->color.b;
                            vertex->v.cn[3] = 0x64;
                            vertex++;
                        }
                    }
                    break;

                case 5:
                    vertex = Gfx_AllocDisplayList(sizeof(Vtx) * 20 * 3 * 3);
                    state->vertices = vertex;

                    for (j = 0; j < 20; j++, node++) {
                        for (x = 0; x < 3; x++) {
                            for (y = 0; y < 3; y++) {
                                f32 vertex_x, vertex_y, vertex_z;

                                Radial20_RotateVertexOffset(node->angle + ((6.2831854820251465f * y) / 12.0f) + ((6.2831854820251465f * x) / 3.0f),
                                              &node->velocity.x, &offset.x, D_8418761C[y] * node->scale, 1.0f, 0.0f, 0.0f);

                                vertex_x = node->position.x + offset.x;
                                vertex_y = node->position.y + offset.y;
                                vertex_z = node->position.z + offset.z;

                                vertex->v.ob[0] = vertex_x;
                                vertex->v.ob[1] = vertex_y;
                                vertex->v.ob[2] = vertex_z;

                                if ((y == 0) && (((s32)guRandom() % 100) == 0)) {
                                    AuxiliaryEffect_Spawn(state->resource, vertex_x, vertex_y, vertex_z, 10, 0.75f);
                                }

                                vertex->v.cn[0] = ((D_84187610[x] * (0xFF - node->alpha)) + (node->alpha * 0xFF)) / 255;
                                vertex->v.cn[1] = ((D_84187614[x] * (0xFF - node->alpha)) + (node->alpha * 0xFF)) / 255;
                                vertex->v.cn[2] = ((D_84187618[x] * (0xFF - node->alpha)) + (node->alpha * 0xFF)) / 255;
                                vertex->v.cn[3] = node->alpha;
                                vertex++;
                            }
                        }
                    }
                    break;

                default:
                    break;
            }

            vertex = state->vertices;
            for (x = 0; x < 19; x++) {
                switch (state->type) {
                    case 0:
                    case 2:
                        gSPDisplayList(display_list++, D_84187538);
                        gDPSetPrimColor(display_list++, 0, 0, state->color.r, state->color.g, state->color.b,
                                        state->color.a);
                        gDPSetEnvColor(display_list++, state->environment_color.r, state->environment_color.g, state->environment_color.b, 0);
                        gSPVertex(display_list++, vertex, 4, 0);
                        gSP2Triangles(display_list++, 0, 2, 1, 0, 2, 3, 1, 0);
                        vertex += 2;
                        break;

                    case 1:
                    case 3:
                    default:
                        gSPDisplayList(display_list++, D_841875C0);
                        gSPClearGeometryMode(display_list++, G_CULL_BOTH);
                        gSPSetGeometryMode(display_list++, G_CULL_FRONT);
                        gSPVertex(display_list++, vertex, 6, 0);
                        gSP2Triangles(display_list++, 0, 3, 1, 0, 3, 4, 1, 0);
                        gSP2Triangles(display_list++, 1, 4, 2, 0, 4, 5, 2, 0);
                        gSP2Triangles(display_list++, 2, 5, 0, 0, 5, 3, 0, 0);
                        vertex += 3;
                        break;

                    case 4:
                        gSPDisplayList(display_list++, D_841875C0);
                        gSPClearGeometryMode(display_list++, G_CULL_BOTH);
                        gSPSetGeometryMode(display_list++, G_CULL_FRONT);
                        gSPVertex(display_list++, vertex, 12, 0);

                        for (j = 0; j < 5; j++) {
                            gSP2Triangles(display_list++, j + 0, j + 6, j + 1, 0, j + 1, j + 6, j + 7, 0);
                        }

                        gSP2Triangles(display_list++, 5, 11, 0, 0, 0, 11, 6, 0);
                        vertex += 6;
                        break;

                    case 5:
                        gSPDisplayList(display_list++, D_841875C0);
                        gSPClearGeometryMode(display_list++, G_CULL_BOTH);
                        gSPSetGeometryMode(display_list++, G_CULL_FRONT);
                        gSPVertex(display_list++, vertex, 18, 0);

                        for (j = 0; j < 3; j++) {
                            u8 idx = j * 3;
                            gSP2Triangles(display_list++, idx + 0, idx + 9, idx + 1, 0, idx + 1, idx + 9, idx + 10, 0);
                            gSP2Triangles(display_list++, idx + 1, idx + 10, idx + 2, 0, idx + 2, idx + 10, idx + 11, 0);
                            gSP2Triangles(display_list++, idx + 2, idx + 11, idx + 0, 0, idx + 0, idx + 11, idx + 9, 0);
                        }

                        vertex += 9;
                        break;
                }
            }

            vertex = state->vertices;
            for (x = 0; x < 19; x++) {
                switch (state->type) {
                    case 0:
                    case 2:
                        break;

                    default:
                    case 1:
                    case 3:
                        gSPDisplayList(display_list++, D_841875C0);
                        gSPClearGeometryMode(display_list++, G_CULL_BOTH);
                        gSPSetGeometryMode(display_list++, G_CULL_BACK);
                        gSPVertex(display_list++, vertex, 6, 0);
                        gSP2Triangles(display_list++, 0, 3, 1, 0, 3, 4, 1, 0);
                        gSP2Triangles(display_list++, 1, 4, 2, 0, 4, 5, 2, 0);
                        gSP2Triangles(display_list++, 2, 5, 0, 0, 5, 3, 0, 0);
                        vertex += 3;
                        break;

                    case 4:
                        gSPDisplayList(display_list++, D_841875C0);
                        gSPClearGeometryMode(display_list++, G_CULL_BOTH);
                        gSPSetGeometryMode(display_list++, G_CULL_BACK);
                        gSPVertex(display_list++, vertex, 12, 0);

                        for (j = 0; j < 5; j++) {
                            gSP2Triangles(display_list++, j + 0, j + 6, j + 1, 0, j + 1, j + 6, j + 7, 0);
                        }

                        gSP2Triangles(display_list++, 5, 11, 0, 0, 0, 11, 6, 0);
                        vertex += 6;
                        break;

                    case 5:
                        gSPDisplayList(display_list++, D_841875C0);
                        gSPClearGeometryMode(display_list++, G_CULL_BOTH);
                        gSPSetGeometryMode(display_list++, G_CULL_BACK);
                        gSPVertex(display_list++, vertex, 18, 0);

                        for (j = 0; j < 3; j++) {
                            u8 idx = j * 3;
                            gSP2Triangles(display_list++, idx + 0, idx + 9, idx + 1, 0, idx + 1, idx + 9, idx + 10, 0);
                            gSP2Triangles(display_list++, idx + 1, idx + 10, idx + 2, 0, idx + 2, idx + 10, idx + 11, 0);
                            gSP2Triangles(display_list++, idx + 2, idx + 11, idx + 0, 0, idx + 0, idx + 11, idx + 9, 0);
                        }

                        vertex += 9;
                        break;
                }
            }

            vertex = state->vertices;
            switch (state->type) {
                case 5:
                    gSPDisplayList(display_list++, D_841875C0);
                    gSPClearGeometryMode(display_list++, G_CULL_BOTH);
                    gSPVertex(display_list++, vertex, 9, 0);
                    gSP2Triangles(display_list++, 2, 1, 0, 0, 5, 4, 3, 0);
                    gSP1Triangle(display_list++, 8, 7, 6, 0);
                    break;
            }
            display_list = AuxiliaryEffect_Draw(state->resource, display_list);
        }
        state++;
    }

    return display_list;
}
#endif
