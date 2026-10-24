#include "global.h"


#ifdef VERSION_US
typedef struct { f32 x; f32 y; f32 z; } Vec3Local;
typedef struct {
    s16 active; u8 pad_02[2];
    Vec3Local position; Vec3Local velocity; Vec3Local scale;
    s16 misc; u8 pad_2A[2];
} Func81003E60State;
extern Vec3Local D_8100614C;
extern Vec3Local D_81006158;
extern Vec3Local D_81006164;
void func_81003E60(Func81003E60State *arg0) {
    arg0->active = 0;
    arg0->position = D_8100614C;
    arg0->velocity = D_81006158;
    arg0->scale = D_81006164;
    arg0->misc = 0;
}

typedef struct {
    u8 pad[8];
    u8 *pool;
} Func81003ECCHeaderRetry;
typedef struct {
    s16 active;
    u8 pad_02[2];
    u8 data[0x28];
} Func81003E60StateRetry;
extern Func81003ECCHeaderRetry *D_8100678C;
extern Func81003E60StateRetry *D_81006780;
extern void *func_8003F54C(void *);
extern void func_81003E60();
void func_81003ECC(void *context) {
    s32 i;
    D_8100678C = func_8003F54C(context);
    if (D_8100678C != NULL) {
        D_81006780 = (Func81003E60StateRetry *)D_8100678C->pool;
        if (D_81006780 != NULL) {
            for (i = 0; i < 10; i++) {
                func_81003E60(D_81006780);
                D_81006780++;
            }
        }
    }
}

extern s32 D_81006784, D_81006788;

void func_81003F44(void) {
    D_81006784 = 0;
    D_81006788 = 0;
}

typedef struct {
    u8 unknown[6];
    s16 enabled;
    u8 *pool;
} ParticlePoolHeader26;
typedef struct {
    u8 unknown[0x1A];
    s16 model_id;
    u8 unknown_1C;
    u8 opacity;
    u8 unknown_1E[0x12];
    Vec3Local scale;
    u8 unknown_3C[4];
    s16 animation_id;
    u8 unknown_42[6];
    s32 frame_fixed;
} ParticleEffectModel26;
typedef struct {
    s16 frames[6];
} ParticleTriggerFrames26;
extern ParticleEffectModel26 *D_8009491C;
extern ParticleTriggerFrames26 D_81006020[];
extern s16 D_810060F8[];
extern Vec3Local D_81006188;
extern f32 D_8100611C[];
extern void *func_8003936C(s32);
// Initializes an inactive slot from the current and parent matrix origins.
// Species select particle scale, position jitter, velocity, and slot count.
void Particle31_SpawnSpeciesEffect(Func81003E60State *slot) {
    s32 i;
    Vec3Local origin;
    Vec3Local position;
    Vec3Local direction;
    s32 limit;
    f32 length;
    Vec3Local scale = D_81006188;
    f32 sx;
    f32 sy;
    f32 sz;
    ParticleEffectModel26 *model;
    void *matrix;
    f32 speed;

    limit = 10;
    matrix = func_8003936C(-1);
    guMtxXFMF(matrix, 0, 0, 0, &origin.x, &origin.y, &origin.z);
    matrix = func_8003936C(0);
    guMtxXFMF(matrix, 0, 0, 0, &position.x, &position.y, &position.z);
    model = D_8009491C;
    sx = model->scale.x;
    sy = model->scale.y;
    sz = model->scale.z;
    switch (model->model_id) {
    case 109:
    case 110:
        speed = 0.5f;
        scale.x = 1.0f;
        scale.y = 1.0f;
        scale.z = 1.0f;
        break;
    case 146:
        speed = 1.0f;
        scale.x = 0.1f;
        scale.y = 0.1f;
        scale.z = 0.1f;
        position.x += (f32) ((guRandom() % 10) - 5) * sx;
        position.y += (f32) ((guRandom() % 10) - 5) * sy;
        position.z += (f32) ((guRandom() % 10) - 5) * sz;
        break;
    case 77:
        speed = 0.5f;
        scale.x = 0.002f;
        scale.y = 0.002f;
        scale.z = 0.002f;
        position.x += (f32) ((guRandom() % 20) - 10) * sx;
        position.y += (f32) ((guRandom() % 20) - 10) * sy;
        position.z += (f32) ((guRandom() % 20) - 10) * sz;
        break;
    case 78:
        speed = 0.5f;
        scale.x = 0.002f;
        scale.y = 0.002f;
        scale.z = 0.002f;
        position.x += (f32) ((guRandom() % 20) - 10) * sx;
        position.y += (f32) ((guRandom() % 10) - 5) * sy;
        position.z += (f32) ((guRandom() % 20) - 10) * sz;
        break;
    case 144:
        speed = 0.0f;
        scale.x = D_8100611C[0];
        scale.y = D_8100611C[0];
        scale.z = D_8100611C[0];
        position.x += (f32) ((guRandom() % 20) - 10) * sx;
        position.y += (f32) ((guRandom() % 20) - 10) * sy;
        position.z += (f32) ((guRandom() % 20) - 10) * sz;
        break;
    case 134:
        speed = 0.0f;
        scale.x = D_8100611C[0];
        scale.y = D_8100611C[0];
        scale.z = D_8100611C[0];
        position.x += (f32) ((guRandom() % 60) - 30) * sx;
        position.y += (f32) ((guRandom() % 40) - 10) * sy;
        position.z += (f32) ((guRandom() % 60) - 30) * sz;
        break;
    case 92:
        speed = 0.0f;
        limit = 3;
        scale.x = 20.0f;
        scale.y = 20.0f;
        scale.z = 20.0f;
        break;
    default:
        speed = 0.0f;
        break;
    }
    for (i = 0; i < 10; i++) {
        if (i >= limit) {
            break;
        }
        if (slot->active == 0) {
            direction.x = position.x - origin.x;
            direction.y = position.y - origin.y;
            direction.z = position.z - origin.z;
            length = sqrtf((direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z));
            if (length > 0.0f) {
                direction.x /= length;
                direction.y /= length;
                direction.z /= length;
            }
            slot->velocity.x = (f32) (speed * direction.x);
            slot->velocity.y = (f32) (speed * direction.y);
            slot->velocity.z = (f32) (speed * direction.z);
            slot->position = position;
            slot->scale = scale;
            slot->misc = 0;
            slot->active = 1;
            break;
        }
        slot++;
    }
}

// Uses species-specific animation frames or random intervals to trigger particle creation.
void Particle31_UpdateSpeciesEffectTrigger(Func81003E60State *slot) {
    ParticleEffectModel26 *model;
    s16 animation;
    s32 frame;
    s16 selection;
    s32 byte_offset;
    s16 *frame_ptr;
    if (((ParticlePoolHeader26 *)D_8100678C)->enabled == 0) {
        return;
    }
    model = D_8009491C;
    frame = model->frame_fixed >> 16;
    switch (model->model_id) {
    case 109:
    case 110:
        if (D_81006788 < 18) {
            animation = model->animation_id;
            selection = D_810060F8[D_81006788];
            switch (animation) {
            case 4:
                if (frame == D_81006020[selection].frames[1]) {
                    Particle31_SpawnSpeciesEffect(slot);
                    return;
                }
                break;
            case 3:
                byte_offset = 0;
                frame_ptr = D_81006020[selection].frames;
                do {
                    if (frame == frame_ptr[2]) {
                        Particle31_SpawnSpeciesEffect(slot);
                    }
                    byte_offset += 2;
                    frame_ptr++;
                } while (byte_offset != 6);
                return;
            case 2:
                if (frame == D_81006020[selection].frames[5]) {
                    Particle31_SpawnSpeciesEffect(slot);
                    return;
                }
                break;
            default:
                if (frame == D_81006020[selection].frames[0]) {
                    Particle31_SpawnSpeciesEffect(slot);
                    return;
                }
                return;
            }
        }
        break;
    case 146:
        if (guRandom() % 60 == 0) {
            Particle31_SpawnSpeciesEffect(slot);
            return;
        }
        break;
    case 144:
        if (guRandom() % 30 == 0) {
            Particle31_SpawnSpeciesEffect(slot);
            return;
        }
        break;
    case 134:
        if (guRandom() % 7 == 0) {
            Particle31_SpawnSpeciesEffect(slot);
            return;
        }
        break;
    case 92:
        Particle31_SpawnSpeciesEffect(slot);
        return;
    case 77:
    case 78:
        if (guRandom() % 7 == 0) {
            Particle31_SpawnSpeciesEffect(slot);
        }
        break;
    }
}

typedef struct { s16 active; u8 data[0x2A]; } Func81005480Slot;

typedef struct { f32 mf[4][4]; } ParticleMatrixF26;
typedef struct { u8 r, g, b; } ParticleRgb26;
// Rendering consumes the first eight texture frames (particle age 0 through 15).
// This view describes the accessed prefix of the callback's resource table.
typedef struct { u32 setup, geometry; u32 textures[8]; } ParticleRenderResources26;
typedef struct { u8 unknown[2]; u8 flags; } ParticleRenderFlags26;
typedef struct { u8 unknown[0x2C]; void *(*query)(s32, s32); } ParticleRenderController26;
extern u8 *D_80094920;
extern ParticleRgb26 D_81006194, D_81006198, D_8100619C, D_810061A0;
extern u8 *D_80094908;
extern void func_80070DEC(f32 [4][4], void *);
extern void MtxF_Copy(u32 *, u32 *);
extern u32 Gfx_AllocDisplayList(s32);
// Draws one species effect and advances its motion when the pool is enabled.
Gfx *Particle31_DrawAndUpdateSpeciesEffect(Gfx *gfx, Func81005480Slot *raw_slot, void *raw_resources, s16 legacy_slot) {
    Mtx *matrix_out;
    Mtx scale_matrix;
    Mtx translation;
    Mtx orientation;
    Mtx model_translation;
    s16 alpha;
    ParticleMatrixF26 view_rotation;
    ParticleMatrixF26 model_matrix;
    f32 curve_scale;
    f32 z;
    f32 y;
    f32 x;
    ParticleEffectModel26 *model;
    ParticleRgb26 primary = D_81006194;
    ParticleRgb26 environment = D_81006198;
    ParticleRgb26 alternate_primary = D_8100619C;
    ParticleRgb26 alternate_environment = D_810061A0;
    ParticleRgb26 *primary_color;
    ParticleRgb26 *environment_color;
    Func81003E60State *slot;
    ParticleRenderResources26 *resources;

    slot = (Func81003E60State *)raw_slot;
    resources = raw_resources;
    matrix_out = (Mtx *)Gfx_AllocDisplayList(64);
    func_80070DEC(view_rotation.mf, D_80094908 + 0x64);
    guMtxF2L(view_rotation.mf, &orientation);
    model = D_8009491C;
    guScale(&scale_matrix, model->scale.x * slot->scale.x * 0.1f,
            model->scale.y * slot->scale.y * 0.1f,
            model->scale.z * slot->scale.z * 0.1f);
    if (D_8009491C->model_id == 92) {
        MtxF_Copy((u32 *)&model_matrix, (u32 *)func_8003936C(0));
        guMtxXFMF(model_matrix.mf, 0, 0, 0, &x, &y, &z);
        guTranslate(&model_translation, x, y, z);
        guMtxCatL(&scale_matrix, &model_translation, matrix_out);
    } else {
        guTranslate(&translation, slot->position.x, slot->position.y, slot->position.z);
        guMtxCatL(&scale_matrix, &translation, matrix_out);
    }
    guMtxCatL(&orientation, matrix_out, matrix_out);
    gSPMatrix(gfx++, matrix_out, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, resources->setup);
    switch (D_8009491C->model_id) {
    case 109:
    case 110:
        gDPLoadTextureBlock_4b(gfx++, resources->textures[slot->misc / 2], G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetPrimColor(gfx++, 0, 0, 0x0A, 0x00, 0x00, 0xC8 - (slot->misc * 13));
        break;
    case 92:
        primary_color = &primary;
        environment_color = &environment;
        if (D_80094920 != NULL) {
            if (((ParticleRenderFlags26 *)(((ParticleRenderController26 *)D_80094920)->query(0, 0)))->flags & 0x80) {
                primary_color = &alternate_primary;
                environment_color = &alternate_environment;
            }
        }
        gDPLoadTextureBlock_4b(gfx++, resources->textures[slot->misc / 2], G_IM_FMT_I, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetEnvColor(gfx++, environment_color->r, environment_color->g, environment_color->b, 0);
        if (slot->misc < 10) {
            alpha = D_8009491C->opacity;
        } else {
            alpha = ((655 - slot->misc * 40) * D_8009491C->opacity) / 255;
        }
        gDPSetPrimColor(gfx++, 0, 0, primary_color->r, primary_color->g, primary_color->b, alpha);
        break;
    case 146:
    case 77:
    case 78:
        gDPLoadTextureBlock_4b(gfx++, resources->textures[slot->misc / 2], G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0x00, 0xFA - (slot->misc * 3));
        break;
    case 134:
    case 144:
        gDPLoadTextureBlock(gfx++, resources->textures[slot->misc / 2], G_IM_FMT_IA, G_IM_SIZ_16b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        if (slot->misc < 4) {
            gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, (slot->misc * 20) + 0xB4);
        } else {
            gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, 0x122 - (slot->misc * 10));
        }
        break;
    default:
        gDPLoadTextureBlock_4b(gfx++, resources->textures[slot->misc / 2], G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetPrimColor(gfx++, 0, 0, 0x0A, 0x00, 0x00, 0xC8 - (slot->misc * 13));
        break;
    }
    gSPDisplayList(gfx++, resources->geometry);
    gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
    if (((ParticlePoolHeader26 *)D_8100678C)->enabled == 1) {
        model = D_8009491C;
        switch (model->model_id) {
        case 109:
        case 110:
            slot->position.y += 0.5f * model->scale.y;
            slot->misc++;
            slot->scale.x += 0.1f;
            slot->scale.y += 0.1f;
            slot->scale.z += 0.1f;
            if (slot->misc >= 16) {
                slot->active = 0;
            }
            break;
        case 92:
            slot->misc += 2;
            if (slot->misc >= 16) {
                slot->active = 0;
            }
            break;
        case 146:
            slot->position.y += 1.5f * model->scale.y;
            slot->misc++;
            slot->scale.x += 0.005f;
            slot->scale.y += 0.005f;
            slot->scale.z += 0.005f;
            if (slot->misc >= 16) {
                slot->active = 0;
            }
            break;
        case 77:
            slot->position.y += 0.75f * model->scale.y;
            slot->misc++;
            slot->scale.x += 0.005f;
            slot->scale.y += 0.005f;
            slot->scale.z += 0.005f;
            if (slot->misc >= 16) {
                slot->active = 0;
            }
            break;
        case 78:
            slot->position.y += model->scale.y;
            slot->misc++;
            slot->scale.x += 0.005f;
            slot->scale.y += 0.005f;
            slot->scale.z += 0.005f;
            if (slot->misc >= 16) {
                slot->active = 0;
            }
            break;
        case 144:
            slot->position.y -= 0.5f * model->scale.y;
            slot->misc++;
            curve_scale = D_8100611C[slot->misc % 12];
            slot->scale.x = curve_scale;
            slot->scale.y = curve_scale;
            slot->scale.z = curve_scale;
            if ((slot->misc >= 12) || (slot->position.y < 0.0f)) {
                slot->active = 0;
            }
            break;
        case 134:
            slot->misc++;
            curve_scale = D_8100611C[slot->misc % 12];
            slot->scale.x = curve_scale;
            slot->scale.y = curve_scale;
            slot->scale.z = curve_scale;
            if ((slot->misc >= 12) || (slot->position.y < 0.0f)) {
                slot->active = 0;
            }
            break;
        default:
            slot->misc++;
            if (slot->misc >= 16) {
                slot->active = 0;
            }
            break;
        }
        slot->position.x = (f32) (slot->position.x + slot->velocity.x);
        slot->position.y = (f32) (slot->position.y + slot->velocity.y);
        slot->position.z = (f32) (slot->position.z + slot->velocity.z);
        slot->velocity.x *= 0.9f;
        slot->velocity.y *= 0.9f;
        slot->velocity.z *= 0.9f;
        D_81006784 += 1;
    }
    return gfx;
}

extern Gfx *Particle31_DrawAndUpdateSpeciesEffect(Gfx *, Func81005480Slot *, void *, s16);
Gfx *Particle31_BuildDisplayList(Gfx *gfx, Func81005480Slot *slots, void *arg2, s16 arg3) {
    s32 i;
    for (i = 0; i < 10; i++, slots++) {
        if (slots->active == 1) {
            gfx = Particle31_DrawAndUpdateSpeciesEffect(gfx, slots, arg2, arg3);
        }
    }
    return gfx;
}

typedef struct {
    u8 unknown[0x14];
    void *addresses;
    Gfx *gfx;
} ParticleDisplayListState26;
void Particle31_DisplayListCallback(s32 phase, ParticleDisplayListState26 *state) {
    ParticleEffectModel26 *context;
    Gfx *display_list;
    void *addresses;
    Gfx *gfx;
    u8 legacy_slot; //!bug Retail passes an uninitialized byte to the unused legacy argument.
    addresses = state->addresses;
    if (phase == 2) {
        context = D_8009491C;
        D_8100678C = func_8003F54C(context);
        if (D_8100678C != NULL) {
            D_81006780 = (Func81003E60StateRetry *)D_8100678C->pool;
            if (D_81006780 != NULL) {
                if (D_81006788 == 0) {
                    display_list = (Gfx *)Gfx_AllocDisplayList(1280);
                    state->gfx = display_list;
                } else {
                    display_list = (Gfx *)Gfx_AllocDisplayList(128);
                    state->gfx = display_list;
                }
                gfx = state->gfx;
                Particle31_UpdateSpeciesEffectTrigger((Func81003E60State *)D_81006780);
                if (D_81006788 == 0) {
                    gfx = Particle31_BuildDisplayList(gfx, (Func81005480Slot *)D_81006780, addresses, legacy_slot);
                }
                gSPEndDisplayList(gfx);
                D_81006788++;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81005628.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81005758.s")
#endif
