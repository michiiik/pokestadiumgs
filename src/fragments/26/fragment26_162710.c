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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81003F58.s")

typedef struct {
    u8 unknown[6];
    s16 enabled;
    u8 *pool;
} ParticlePoolHeader26;
typedef struct {
    u8 unknown[0x1A];
    s16 model_id;
    u8 unknown_1C[0x24];
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
extern void func_81003F58(Func81003E60State *);
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
                    func_81003F58(slot);
                    return;
                }
                break;
            case 3:
                byte_offset = 0;
                frame_ptr = D_81006020[selection].frames;
                do {
                    if (frame == frame_ptr[2]) {
                        func_81003F58(slot);
                    }
                    byte_offset += 2;
                    frame_ptr++;
                } while (byte_offset != 6);
                return;
            case 2:
                if (frame == D_81006020[selection].frames[5]) {
                    func_81003F58(slot);
                    return;
                }
                break;
            default:
                if (frame == D_81006020[selection].frames[0]) {
                    func_81003F58(slot);
                    return;
                }
                return;
            }
        }
        break;
    case 146:
        if (guRandom() % 60 == 0) {
            func_81003F58(slot);
            return;
        }
        break;
    case 144:
        if (guRandom() % 30 == 0) {
            func_81003F58(slot);
            return;
        }
        break;
    case 134:
        if (guRandom() % 7 == 0) {
            func_81003F58(slot);
            return;
        }
        break;
    case 92:
        func_81003F58(slot);
        return;
    case 77:
    case 78:
        if (guRandom() % 7 == 0) {
            func_81003F58(slot);
        }
        break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81004818.s")

typedef struct { s16 active; u8 data[0x2A]; } Func81005480Slot;
extern Gfx *func_81004818(Gfx *, Func81005480Slot *, void *, s16);
Gfx *Particle31_BuildDisplayList(Gfx *gfx, Func81005480Slot *slots, void *arg2, s16 arg3) {
    s32 i;
    for (i = 0; i < 10; i++, slots++) {
        if (slots->active == 1) {
            gfx = func_81004818(gfx, slots, arg2, arg3);
        }
    }
    return gfx;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81005524.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81005628.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81005758.s")
#endif
