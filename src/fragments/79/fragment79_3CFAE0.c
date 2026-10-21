#include "global.h"

#ifdef VERSION_US
typedef struct {
    f32 x, y, z;
    f32 nx, ny, nz;
    s16 s, t;
    f32 phase;
} Fragment79PhaseGridNode;
typedef struct {
    s16 age, duration, alpha;
    u8 unk_06[2];
    f32 amplitude;
    Vtx *vertices;
    Mtx *matrix;
    Fragment79PhaseGridNode nodes[16][16];
} Fragment79PhaseGridState;
typedef struct { f32 x, y, z; } Fragment79PhaseGridVector;
typedef struct {
    u8 unk_00[44];
    f32 fovy;
    u8 unk_30[120];
    Fragment79PhaseGridVector eye, at;
} Fragment79PhaseGridCamera;
extern Fragment79PhaseGridState *D_841876E0;
extern s16 D_841A4D80;
extern void *Gfx_AllocDisplayList(s32);
extern void func_80070C14(f32 *, f32 *, f32 *);
extern void Vec3f_CrossProductComponents(f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);
extern void func_80070C68(Mtx *, f32, f32, f32, f32, f32, f32);
extern u32 func_841094A4(void);
extern u32 func_841094EC(void);
extern f32 sqrtf(f32);
extern f32 __sinf(f32);
extern void PhaseGrid16_RecomputeNormal(s32, s32);
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CFAE0/func_84160250.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CFAE0/func_841603A0.s")

void PhaseGrid16_RecomputeNormal(s32 row, s32 column) {
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
    Fragment79PhaseGridNode *node;
    s16 contribution_count;

    node = &D_841876E0->nodes[row][column];
    center_x = node->x;
    center_y = node->y;
    center_z = node->z;
    sum_x = 0.0f;
    sum_y = 0.0f;
    sum_z = 0.0f;
    contribution_count = 0;

    if ((row > 0) && (column >= 1)) {
        node = &D_841876E0->nodes[row - 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_841876E0->nodes[row][column - 1];
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
        node = &D_841876E0->nodes[row - 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_841876E0->nodes[row][column + 1];
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
        node = &D_841876E0->nodes[row + 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_841876E0->nodes[row][column - 1];
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
        node = &D_841876E0->nodes[row + 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_841876E0->nodes[row][column + 1];
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
        node = &D_841876E0->nodes[row][column];
        node->nx = sum_x;
        node->ny = sum_y;
        node->nz = sum_z;
    }
}

void PhaseGrid16_FillVertex(Fragment79PhaseGridNode* node, Vtx* vertex) {
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
    vertex->v.cn[3] = D_841876E0->alpha;
}

s32 PhaseGrid16_Update(void) {
    Fragment79PhaseGridNode* node;
    s32 row;
    s32 column;
    s32 status;

    D_841876E0->age++;
    status = (s32)func_841094EC();
    if ((status == 1) && (D_841A4D80 == 0)) {
        D_841876E0->age = 0;
        D_841876E0->duration = 25;
        D_841A4D80 = 1;
    }
    if (D_841876E0->duration < D_841876E0->age) {
        return -1;
    }
    if (D_841A4D80 == 0) {
        D_841876E0->alpha += 10;
        if (D_841876E0->alpha >= 129) {
            D_841876E0->alpha = 128;
        }
    } else if (D_841876E0->age >= 16) {
        D_841876E0->alpha -= 12;
        if (D_841876E0->alpha < 0) {
            D_841876E0->alpha = 0;
        }
    }

    if (D_841876E0->amplitude < 0.5) {
        D_841876E0->amplitude += 0.05;
    }

    node = &D_841876E0->nodes[0][0];
    for (row = 0; row < 16; row++) {
        for (column = 0; column < 16; column++) {
            node->y = (__sinf(node->phase) * 0.5) + 1.0;
            node->phase += 0.1;

            node++;
        }
    }

    for (row = 0; row < 16; row++) {
        for (column = 0; column < 16; column++) {
            PhaseGrid16_RecomputeNormal(row, column);
        }
    }

    return 0;
}

void PhaseGrid16_BuildViewMatrix(void) {
    Fragment79PhaseGridCamera * camera;
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

    D_841876E0->matrix = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    camera = (Fragment79PhaseGridCamera *)func_841094A4();

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

    func_80070C68(D_841876E0->matrix, eye_x, eye_y, eye_z, at_x, at_y, at_z);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CFAE0/func_84161018.s")
#endif
