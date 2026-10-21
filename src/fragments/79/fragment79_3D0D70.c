#include "global.h"

#ifdef VERSION_US
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84161670.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84161DAC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_841621A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162660.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162798.s")

extern f64 D_8418C7A8;
extern f64 D_8418C7B0;

void TexturedRibbonSheet_Update(f32 arg0, f32 *arg1, f32 arg2) {
    f32 sp30[4][4];
    f32 angle = (arg0 * D_8418C7A8) / D_8418C7B0;
    guRotateRPYF(sp30, 90.0f, angle, angle);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

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
