#include "global.h"

#ifdef VERSION_US
typedef struct { f32 x, y, z; } AuxiliaryVec3f;
typedef struct {
    s16 unk_00, unk_02, unk_04, unk_06;
    f32 unk_08;
    AuxiliaryVec3f unk_0C;
} AuxiliaryEffectNode;
typedef struct {
    s16 unk_000;
    u8 unk002[2];
    AuxiliaryEffectNode unk_004[20];
} AuxiliaryEffect;
extern u8 *D_84187E40;
extern f32 __sinf(f32);
void func_84169B80(void) {
    u8 *ptr = *(u8 **)&D_84187E40;
    s32 i = 0;
    while (i != 2) {
        i += 1;
        *(u16 *)ptr = 0;
        ptr += 0x1E4;
    }
}

s16 AuxiliaryEffect_Alloc(void) {
    AuxiliaryEffect* var_a0;
    AuxiliaryEffectNode* var_v1;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        var_a0 = &((AuxiliaryEffect *)D_84187E40)[i];
        if (var_a0->unk_000 == 0) {
            var_v1 = &var_a0->unk_004[0];
            for (j = 0; j < 20; j++, var_v1++) {
                var_v1->unk_00 = 0;
                var_v1->unk_04 = 0;
                var_v1->unk_08 = 1.0f;
                var_v1->unk_0C.x = 0.0f;
                var_v1->unk_0C.y = 0.0f;
                var_v1->unk_0C.z = 0.0f;
            }
            var_a0->unk_000 = 1;
            return i;
        }
    }
    return -1;
}

void AuxiliaryEffect_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5) {
    s32 i;
    AuxiliaryEffect* temp_v0 = &((AuxiliaryEffect *)D_84187E40)[arg0];
    AuxiliaryEffectNode* var_v1;

    if (temp_v0->unk_000 != 0) {
        var_v1 = &temp_v0->unk_004[0];
        for (i = 0; i < 20; i++, var_v1++) {
            if (var_v1->unk_00 == 0) {
                var_v1->unk_00 = 1;
                var_v1->unk_04 = 0;
                var_v1->unk_06 = arg4;
                var_v1->unk_08 = arg5;
                var_v1->unk_0C.x = arg1;
                var_v1->unk_0C.y = arg2;
                var_v1->unk_0C.z = arg3;
                return;
            }
        }
    }
}

void AuxiliaryEffect_Update(s16 arg0) {
    AuxiliaryEffect* temp_v0 = &((AuxiliaryEffect *)D_84187E40)[arg0];
    AuxiliaryEffectNode* var_v1;
    s32 i;

    if (temp_v0->unk_000 != 0) {
        var_v1 = &temp_v0->unk_004[0];
        for (i = 0; i < 20; i++, var_v1++) {
            if (var_v1->unk_00 == 1) {
                var_v1->unk_04++;
                if (var_v1->unk_06 < var_v1->unk_04) {
                    var_v1->unk_00 = 0;
                }
                var_v1->unk_0C.y -= 0.75f;
            }
        }
    }
}

extern u32 Gfx_AllocDisplayList(s32);
extern Gfx D_84188690[];
extern u8 *D_80094908;
extern void func_80070DEC(f32 [4][4], void *);
Gfx* AuxiliaryEffect_DrawOne(Gfx* gfx, AuxiliaryEffectNode* node, Mtx* billboard_matrix) {
    f32 x;
    f32 y;
    f32 z;
    f32 scale;
    Mtx* model_matrix;
    Mtx translation_matrix;
    Mtx scale_matrix;

    x = node->unk_0C.x;
    y = node->unk_0C.y;
    z = node->unk_0C.z;
    scale = node->unk_08;
    scale *= __sinf((node->unk_04 * 3.1415927f) / 10.0f);

    guScale(&scale_matrix, scale, scale, scale);
    guTranslate(&translation_matrix, x, y, z);
    model_matrix = (Mtx *)Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    guMtxCatL(&scale_matrix, &translation_matrix, model_matrix);
    guMtxCatL(billboard_matrix, model_matrix, model_matrix);

    gSPMatrix(gfx++, model_matrix, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 200);
    gSPDisplayList(gfx++, D_84188690);
    gSPPopMatrix(gfx++, G_MTX_MODELVIEW);

    return gfx;
}

Gfx* AuxiliaryEffect_Draw(s16 slot, Gfx* gfx) {
    AuxiliaryEffect* effect = &((AuxiliaryEffect *)D_84187E40)[slot];
    AuxiliaryEffectNode* node;
    s32 i;
    Mtx *billboard_matrix;
    f32 float_matrix[4][4];
    Mtx fixed_matrix;

    if (effect->unk_000 == 0) {
        return gfx;
    }

    billboard_matrix = &fixed_matrix;
    func_80070DEC(float_matrix, D_80094908 + 100);
    guMtxF2L(float_matrix, &fixed_matrix);

    node = &effect->unk_004[0];
    for (i = 0; i < 20; i++, node++) {
        if (node->unk_00 == 1) {
            gfx = AuxiliaryEffect_DrawOne(gfx, node, billboard_matrix);
        }
    }

    return gfx;
}

void func_8416A140(void) {}
void func_8416A140_padding(void) {}

void *func_8416A150(void *arg0) { return arg0; }
#endif
