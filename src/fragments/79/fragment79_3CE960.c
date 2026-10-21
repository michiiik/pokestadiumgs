#include "global.h"

#ifdef VERSION_US
typedef struct {
    f32 x, y, z;
    f32 nx, ny, nz;
    s16 s, t;
} Fragment79GridNode;
typedef struct {
    s16 age, duration, alpha;
    u8 unknown_06[2];
    f32 amplitude;
    Vtx *vertices;
    Mtx *matrix;
    Fragment79GridNode nodes[16][16];
} Fragment79GridState;
typedef struct { f32 x, y, z; } Fragment79GridVector;
typedef struct {
    u8 unknown_00[44];
    f32 fovy;
    u8 unknown_30[120];
    Fragment79GridVector eye, at;
} Fragment79GridCamera;
extern Fragment79GridState *D_84187630;
extern s16 D_841A4D70;
extern void *Gfx_AllocDisplayList(s32);
extern void func_80070C14(f32 *, f32 *, f32 *);
extern void Vec3f_CrossProductComponents(f32, f32, f32, f32, f32, f32, f32 *, f32 *, f32 *);
extern void func_80070C68(Mtx *, f32, f32, f32, f32, f32, f32);
extern u32 func_841094A4(void);
extern s16 D_841A4D70;
void RippleGrid16_Initialize(s16 duration) {
    s32 row;
    s32 column;
    s16 row_uv;
    s16 column_uv;
    Fragment79GridNode* node;

    D_84187630->age = 0;
    D_84187630->duration = duration;
    D_84187630->alpha = 0;
    D_84187630->amplitude = 0.01f;
    D_841A4D70 = 0;
    node = &D_84187630->nodes[0][0];

    for (row = 0; row < 16; row++) {
        for (column = 0; column < 16; column++) {
            row_uv = row * 32;

            node->x = (row * 6.75f) - 54.0f;
            node->y = 1.0f;
            node->z = (column * 5.25f) - 42.0f;

            node->s = row_uv * 16;
            column_uv = column * 32;
            node->t = column_uv * 16;

            node++;
        }
    }
}

void RippleGrid16_RecomputeNormal(s32 row, s32 column) {
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
    Fragment79GridNode *node;
    s16 contribution_count;

    node = &D_84187630->nodes[row][column];
    center_x = node->x;
    center_y = node->y;
    center_z = node->z;
    sum_x = 0.0f;
    sum_y = 0.0f;
    sum_z = 0.0f;
    contribution_count = 0;

    if ((row > 0) && (column >= 1)) {
        node = &D_84187630->nodes[row - 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_84187630->nodes[row][column - 1];
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
        node = &D_84187630->nodes[row - 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_84187630->nodes[row][column + 1];
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
        node = &D_84187630->nodes[row + 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_84187630->nodes[row][column - 1];
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
        node = &D_84187630->nodes[row + 1][column];
        first_x = node->x - center_x;
        first_y = node->y - center_y;
        first_z = node->z - center_z;
        func_80070C14(&first_x, &first_y, &first_z);
        node = &D_84187630->nodes[row][column + 1];
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
        node = &D_84187630->nodes[row][column];
        node->nx = sum_x;
        node->ny = sum_y;
        node->nz = sum_z;
    }
}

void RippleGrid16_FillVertex(Fragment79GridNode* node, Vtx* vertex) {
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
    vertex->v.cn[3] = D_84187630->alpha;
}

extern u32 func_841094EC(void);
extern f32 sqrtf(f32);
extern f32 __sinf(f32);
s32 RippleGrid16_Update(void) {
    Fragment79GridNode* node;
    s32 row;
    s32 column;
    s32 status;
    f32 falloff;
    f32 height;

    D_84187630->age++;
    status = (s32)func_841094EC();
    if ((status == 1) && (D_841A4D70 == 0)) {
        D_84187630->age = 0;
        D_84187630->duration = 25;
        D_841A4D70 = 1;
    }
    if (D_84187630->duration < D_84187630->age) {
        return -1;
    }
    if (D_841A4D70 == 0) {
        D_84187630->alpha += 10;
        if (D_84187630->alpha >= 129) {
            D_84187630->alpha = 128;
        }
    } else if (D_84187630->age >= 16) {
        D_84187630->alpha -= 12;
        if (D_84187630->alpha < 0) {
            D_84187630->alpha = 0;
        }
    }

    if (D_84187630->amplitude < 1.0) {
        D_84187630->amplitude += 0.05;
    }

    node = &D_84187630->nodes[0][0];
    for (row = 0; row < 16; row++) {
        for (column = 0; column < 16; column++, node++) {
            falloff = 1.0 - (sqrtf(node->x * node->x + node->z * node->z) / 76.3667984f);
            height = __sinf((((f32)(D_84187630->age % 20) / 20.0) + (3.0 * falloff)) * 6.2831854820251465) *
                  ((f64)D_84187630->amplitude * falloff);
            node->y = height;
        }
    }

    for (row = 0; row < 16; row++) {
        for (column = 0; column < 16; column++) {
            RippleGrid16_RecomputeNormal(row, column);
        }
    }

    return 0;
}

void RippleGrid16_BuildViewMatrix(void) {
    Fragment79GridCamera * camera;
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

    D_84187630->matrix = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    camera = (Fragment79GridCamera *)func_841094A4();

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

    func_80070C68(D_84187630->matrix, eye_x, eye_y, eye_z, at_x, at_y, at_z);
}

extern void *D_8418CAB8;
extern Gfx D_84187660[];
extern void * Gfx_AllocDisplayList(s32);
Gfx* RippleGrid16_Draw(Gfx* display_list) {
    s32 row;
    s32 column;
    Fragment79GridNode* node;
    s32 triangle_parity;
    Vtx* vertex;
    s32 index;

    triangle_parity = 0;
    D_84187630->vertices = Gfx_AllocDisplayList(sizeof(Vtx) * 16 * 16);

    vertex = D_84187630->vertices;
    node = &D_84187630->nodes[0][0];
    for (row = 0; row < 16; row++) {
        for (column = 0; column < 16; column++) {
            RippleGrid16_FillVertex(node, vertex);
            node++;
            vertex++;
        }
    }

    RippleGrid16_BuildViewMatrix();

    gDPLoadTextureBlock(display_list++, D_8418CAB8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(display_list++, D_84187660);
    gDPSetPrimColor(display_list++, 0, 0, 255, 255, 255, D_84187630->alpha);
    gSPMatrix(display_list++, D_84187630->matrix, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    vertex = D_84187630->vertices;
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
#endif
