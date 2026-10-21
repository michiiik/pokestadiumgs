#include "global.h"

#ifdef VERSION_US
extern void Vec3f_CrossProductComponents(f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);
extern void FlatGrid16_RecomputeNormal(s32, s32);
extern f32 sqrtf(f32);
extern f32 __sinf(f32);
extern const f64 D_8418C780, D_8418C790;
extern const f32 D_8418C788;
extern void *D_8418CAB0;
extern Gfx D_841877C0[];
extern void FlatGrid16_BuildViewMatrix(void);
extern void * Gfx_AllocDisplayList(s32);
typedef struct {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
} S1_Color_RGB8;
typedef struct S1_Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} S1_Vec3f;
typedef struct S1_TexturedRibbonSheetNode {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ S1_Vec3f unk_0C;
    /* 0x18 */ S1_Vec3f unk_18;
    /* 0x24 */ S1_Vec3f unk_24;
    /* 0x30 */ Vtx unk_30[2];
} S1_TexturedRibbonSheetNode;
typedef struct S1_TexturedRibbonSheet {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ S1_Color_RGB8 unk_00A;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ char unk01C[0x1C];
    /* 0x038 */ S1_TexturedRibbonSheetNode unk_038[10];
} S1_TexturedRibbonSheet;
typedef struct {
    f32 x, y, z;
    f32 nx, ny, nz;
    s16 s, t;
} Fragment79FlatGridNode;
typedef struct {
    s16 age, duration, alpha;
    u8 unk_06[2];
    f32 amplitude;
    Vtx *vertices;
    Mtx *matrix;
    Fragment79FlatGridNode nodes[16][16];
} Fragment79FlatGridState;
typedef struct { f32 x, y, z; } Fragment79FlatGridVector;
typedef struct {
    u8 unk_00[44];
    f32 fovy;
    u8 unk_30[120];
    Fragment79FlatGridVector eye, at;
} Fragment79FlatGridCamera;
extern Fragment79FlatGridState *D_84187790;
extern s16 D_841A4D90;
extern s16 D_841A4DA0, D_841A4DA2, D_841A4DA4;
extern struct S1_TexturedRibbonSheet *D_84187840;
extern void *Gfx_AllocDisplayList(s32);
extern void func_80070C14(f32 *, f32 *, f32 *);
extern void func_80070C68(Mtx *, f32, f32, f32, f32, f32, f32);
extern u32 func_841094A4(void);
extern u32 func_841094EC(void);
void FlatGrid16_Initialize(s16 duration) {
    s32 row;
    s32 column;
    s16 texture_row;
    Fragment79FlatGridNode *node;

    D_84187790->age = 0;
    D_84187790->duration = duration;
    D_84187790->alpha = 0;
    D_84187790->amplitude = 0.0f;
    D_841A4D90 = 0;
    node = &D_84187790->nodes[0][0];
    for (row = 0; row < 16; row++) {
        for (column = 0; column < 16; column++) {
            texture_row = row * 0x20;
            node->x = row * 6.75f - 54.0f;
            node->y = 1.0f;
            node->z = column * 5.25f - 42.0f;
            node->s = texture_row * 0x10;
            node->t = (s16)(column * 0x20) * 0x10;
            node++;
        }
    }
}

void FlatGrid16_RecomputeNormal(s32 row, s32 column) {
    f32 sum_x;
    f32 sum_y;
    f32 sum_z;
    f32 cross_x;
    f32 cross_y;
    f32 cross_z;
    f32 center_x;
    f32 center_y;
    f32 center_z;
    f32 first_x;
    f32 first_y;
    f32 first_z;
    f32 second_x;
    f32 second_y;
    f32 second_z;
    Fragment79FlatGridNode *node;
    s16 contribution_count;

    node = &D_84187790->nodes[row][column];
    center_x = node->x;
    center_y = node->y;
    center_z = node->z;
    sum_x = 0.0f;
    sum_y = 0.0f;
    sum_z = 0.0f;
    contribution_count = 0;

    if ((row > 0) && (column >= 1)) {
        node = &D_84187790->nodes[row - 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_84187790->nodes[row][column - 1];
        second_x = node->x - center_x;
        second_y = node->y - center_y;
        second_z = node->z - center_z;
        func_80070C14(&second_x, &second_y, &second_z);
        Vec3f_CrossProductComponents(first_x, first_y, first_z, second_x, second_y, second_z, &cross_x, &cross_y, &cross_z);
        func_80070C14(&cross_x, &cross_y, &cross_z);
        sum_x += cross_x;
        sum_y += cross_y;
        sum_z += cross_z;
        contribution_count = 1;
    }

    if ((0 < row) && (column < 15)) {
        node = &D_84187790->nodes[row - 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_84187790->nodes[row][column + 1];
        second_x = node->x - center_x;
        second_y = node->y - center_y;
        second_z = node->z - center_z;
        func_80070C14(&second_x, &second_y, &second_z);
        Vec3f_CrossProductComponents(first_x, first_y, first_z, second_x, second_y, second_z, &cross_x, &cross_y, &cross_z);
        func_80070C14(&cross_x, &cross_y, &cross_z);
        sum_x += cross_x;
        sum_y += cross_y;
        sum_z += cross_z;
        contribution_count += 1;
    }

    if ((row < 15) && (column >= 1)) {
        node = &D_84187790->nodes[row + 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_84187790->nodes[row][column - 1];
        second_x = node->x - center_x;
        second_y = node->y - center_y;
        second_z = node->z - center_z;
        func_80070C14(&second_x, &second_y, &second_z);
        Vec3f_CrossProductComponents(first_x, first_y, first_z, second_x, second_y, second_z, &cross_x, &cross_y, &cross_z);
        func_80070C14(&cross_x, &cross_y, &cross_z);
        sum_x += cross_x;
        sum_y += cross_y;
        sum_z += cross_z;
        contribution_count += 1;
    }

    if ((row < 15) && (column < 15)) {
        node = &D_84187790->nodes[row + 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_84187790->nodes[row][column + 1];
        second_x = node->x - center_x;
        second_y = node->y - center_y;
        second_z = node->z - center_z;
        func_80070C14(&second_x, &second_y, &second_z);
        Vec3f_CrossProductComponents(first_x, first_y, first_z, second_x, second_y, second_z, &cross_x, &cross_y, &cross_z);
        func_80070C14(&cross_x, &cross_y, &cross_z);
        sum_x -= cross_x;
        sum_y -= cross_y;
        sum_z -= cross_z;
        contribution_count += 1;
    }

    if (contribution_count != 0) {
        if ((sum_x == 0.0) && (sum_y == 0.0) && (sum_z == 0.0)) {
            sum_y = 1.0f;
        } else {
            func_80070C14(&sum_x, &sum_y, &sum_z);
        }
        node = &D_84187790->nodes[row][column];
        node->nx = sum_x;
        node->ny = sum_y;
        node->nz = sum_z;
    }
}

void FlatGrid16_FillVertex(Fragment79FlatGridNode* node, Vtx* vertex) {
    f32 normal_x;
    f32 normal_y;
    f32 normal_z;

    vertex->v.ob[0] = node->x;
    vertex->v.ob[1] = node->y;
    vertex->v.ob[2] = node->z;

    vertex->v.tc[0] = node->s;
    vertex->v.tc[1] = node->t;

    normal_x = node->nx;
    normal_y = node->ny;
    normal_z = node->nz;

    vertex->v.cn[0] = (s32)(normal_x * 120.0);
    vertex->v.cn[1] = (s32)(normal_y * 120.0);
    vertex->v.cn[2] = (s32)(normal_z * 120.0);
    vertex->v.cn[3] = D_84187790->alpha;
}

s32 FlatGrid16_Update(void) {
    Fragment79FlatGridNode* node;
    s32 row;
    s32 column;
    s32 status;
    f32 falloff;
    f32 height;
    f32 radial_extent;
    f64 cycle_radians;

    D_84187790->age++;
    status = (s32)func_841094EC();
    if ((status == 1) && (D_841A4D90 == 0)) {
        D_84187790->age = 0;
        D_84187790->duration = 25;
        D_841A4D90 = 1;
    }
    if (D_84187790->duration < D_84187790->age) {
        return -1;
    }
    if (D_841A4D90 == 0) {
        D_84187790->alpha += 10;
        if (D_84187790->alpha >= 81) {
            D_84187790->alpha = 80;
        }
    } else if (D_84187790->age >= 16) {
        D_84187790->alpha -= 8;
        if (D_84187790->alpha < 0) {
            D_84187790->alpha = 0;
        }
    }

    if (D_84187790->amplitude < 0.25) {
        D_84187790->amplitude += D_8418C780;
    }

    radial_extent = D_8418C788;
    cycle_radians = D_8418C790;
    node = &D_84187790->nodes[0][0];
    for (row = 0; row < 16; row++) {
        for (column = 0; column < 16; column++, node++) {
            falloff = 1.0 - (sqrtf(node->x * node->x + node->z * node->z) / radial_extent);
            height = __sinf((((f32)(D_84187790->age % 20) / 20.0) + (3.0 * falloff)) * cycle_radians) *
                  ((f64)D_84187790->amplitude * falloff);
            node->y = height;
        }
    }

    for (row = 0; row < 16; row++) {
        for (column = 0; column < 16; column++) {
            FlatGrid16_RecomputeNormal(row, column);
        }
    }

    return 0;
}

void FlatGrid16_BuildViewMatrix(void) {
    Fragment79FlatGridCamera * camera;
    f32 eye_x;
    f32 eye_y;
    f32 eye_z;
    f32 at_x;
    f32 at_y;
    f32 at_z;
    f32 direction_x;
    f32 direction_y;
    f32 direction_z;
    f32 fovy;
    f32 offset_y;
    f32 offset_z;
    f32 perspective_scale;
    f32 offset_x;

    D_84187790->matrix = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    camera = (Fragment79FlatGridCamera *)func_841094A4();

    at_x = camera->at.x;
    at_y = camera->at.y;
    at_z = camera->at.z;

    eye_x = camera->eye.x;
    eye_y = camera->eye.y;
    eye_z = camera->eye.z;

    fovy = camera->fovy;
    direction_x = at_x - eye_x;
    direction_y = at_y - eye_y;
    direction_z = at_z - eye_z;

    func_80070C14(&direction_x, &direction_y, &direction_z);

    perspective_scale = fovy / 30.0f;
    offset_x = (105.0f * direction_x) / perspective_scale;
    offset_y = (105.0f * direction_y) / perspective_scale;
    offset_z = (105.0f * direction_z) / perspective_scale;

    at_x += offset_x;
    at_y += offset_y;
    at_z += offset_z;

    eye_x += offset_x;
    eye_y += offset_y;
    eye_z += offset_z;

    func_80070C68(D_84187790->matrix, eye_x, eye_y, eye_z, at_x, at_y, at_z);
}

Gfx* FlatGrid16_Draw(Gfx* display_list) {
    s32 row;
    s32 column;
    Fragment79FlatGridNode* node;
    s32 triangle_parity;
    Vtx* vertex;
    s32 index;

    triangle_parity = 0;
    D_84187790->vertices = Gfx_AllocDisplayList(sizeof(Vtx) * 16 * 16);

    vertex = D_84187790->vertices;
    node = &D_84187790->nodes[0][0];
    for (row = 0; row < 16; row++) {
        for (column = 0; column < 16; column++) {
            FlatGrid16_FillVertex(node, vertex);
            node++;
            vertex++;
        }
    }

    FlatGrid16_BuildViewMatrix();

    gDPLoadTextureBlock(display_list++, D_8418CAB0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(display_list++, D_841877C0);
    gDPSetPrimColor(display_list++, 0, 0, 255, 255, 255, D_84187790->alpha);
    gSPMatrix(display_list++, D_84187790->matrix, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    vertex = D_84187790->vertices;
    for (row = 0; row < 15; row++) {
        for (column = 0; column < 15; column++) {
            index = row * 16 + column;

            gSPVertex(display_list++, &vertex[index], 1, 0);
            gSPVertex(display_list++, &vertex[index + 1], 1, 1);
            gSPVertex(display_list++, &vertex[(row + 1) * 16 + column], 1, 2);
            gSPVertex(display_list++, &vertex[index + 17], 1, 3);

            if (!(triangle_parity & 1)) {
                gSP2Triangles(display_list++, 1, 2, 0, 0, 1, 3, 2, 0);
            } else {
                gSP2Triangles(display_list++, 3, 2, 0, 0, 1, 3, 0, 0);
            }

            triangle_parity++;
        }
    }

    gSPPopMatrix(display_list++, G_MTX_MODELVIEW);
    return display_list;
}

void TexturedRibbonSheet_Init(void) {
    S1_TexturedRibbonSheet* record;
    S1_TexturedRibbonSheetNode* node;
    s32 record_index;
    s32 node_index;

    D_841A4DA4 = 0;
    D_841A4DA2 = 0;
    record = &D_84187840[0];
    for (record_index = 0; record_index < 14; record_index++, record++) {
        record->unk_000 = 0;
        record->unk_004 = 0;
        record->unk_006 = 0;

        node = &record->unk_038[0];
        for (node_index = 0; node_index < 10; node_index++, node++) {
            node->unk_00 = 0.0f;
            node->unk_04 = 0;
            node->unk_08 = 0.0f;
            node->unk_0C.z = node->unk_0C.y = node->unk_0C.x = 0.0f;
            node->unk_18.z = node->unk_18.y = node->unk_18.x = 0.0f;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162798.s")

extern f64 D_8418C7A8;
extern f64 D_8418C7B0;

void TexturedRibbonSheet_Update(f32 arg0, f32 *arg1, f32 arg2) {
    f32 sp30[4][4];
    f32 angle = (arg0 * D_8418C7A8) / D_8418C7B0;
    guRotateRPYF(sp30, 90.0f, angle, angle);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

void TexturedRibbonSheet_UpdateRecord(S1_TexturedRibbonSheet* arg0) {
    s32 i;
    s32 j;
    Vtx* var_a1;
    Vtx* var_a2;
    S1_TexturedRibbonSheetNode* var_v0;
    S1_TexturedRibbonSheetNode* var_v1;

    var_v0 = &arg0->unk_038[9];
    for (i = 0; i < 9; i++, var_v0--) {
        var_a1 = &var_v0[0].unk_30[0];
        var_a2 = &var_v0[-1].unk_30[0];
        for (j = 0; j < 2; j++) {
            *var_a1++ = *var_a2++;
        }
    }

    var_v1 = &arg0->unk_038[0];
    switch (arg0->unk_002) {
        case 0:
            var_v1->unk_0C.y += var_v1->unk_24.y;
            if (arg0->unk_004 >= 0xB) {
                arg0->unk_002 = 1;
            }
            var_v1->unk_08 += 2.0 * arg0->unk_014;
            break;

        case 1:
            var_v1->unk_0C.x += var_v1->unk_18.x;
            var_v1->unk_0C.y += var_v1->unk_18.y;
            var_v1->unk_0C.z += var_v1->unk_18.z;

            if (arg0->unk_008 > 0) {
                var_v1->unk_18.x += 2.0;
                if (var_v1->unk_18.x > 20.0) {
                    var_v1->unk_18.x = 20.0f;
                }
            } else {
                var_v1->unk_18.x -= 2.0;
                if (var_v1->unk_18.x < -20.0) {
                    var_v1->unk_18.x = -20.0f;
                }
            }
            var_v1->unk_08 += arg0->unk_014;
            break;
    }
}

s32 TexturedRibbonSheet_IsComplete(void) {
    s32 index;
    s32 status;
    s32 active_count;
    S1_TexturedRibbonSheet* record;

    D_841A4DA2++;
    status = (s32)func_841094EC();
    if ((status == 1) && (D_841A4DA4 == 0)) {
        D_841A4DA0 = D_841A4DA2 + 70;
        D_841A4DA4 = 1;
    } else if (D_841A4DA4 == 1) {
        if ((D_841A4DA0 - 50) < D_841A4DA2) {
            D_841A4DA4 = 2;
        }
    } else if (D_841A4DA4 == 2) {
        if (D_841A4DA0 < D_841A4DA2) {
            return -1;
        }
    }
    active_count = 0;
    record = &D_84187840[0];

    for (index = 0; index < 14; index++, record++) {
        if (record->unk_000 == 1) {
            record->unk_004 += 1;
            if ((record->unk_006 + 10) < record->unk_004) {
                record->unk_000 = 0;
            } else {
                TexturedRibbonSheet_UpdateRecord(record);
                active_count++;
            }
        }
    }

    if (active_count > 0) {
        return 0;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162DE8.s")
#endif
