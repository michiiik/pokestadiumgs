#include "global.h"


#ifdef VERSION_US
extern s32 D_8620E198;
extern void func_8003F210(u8 *, s16);
extern void ModelAnim_SetFrame(u8 *, s16);
extern void func_862055F0(u8 *, s32, s32);
extern s32 func_8002781C(s32, u8, u8 *);
extern u8 *D_87F119DC;
extern s32 ModelAnim_IsFinished(u8 *);
extern s32 func_8003EC54(u8 *);
extern void func_87F02684(s32);
extern void func_8620581C(s32, u8 *, u8 *);
extern f32 D_862090C0[];
extern void func_87C03B60(u8 *, f32 *, f32 *);
extern void func_86205F34(u8 *);


void SceneModel_InitPlayerAttachment(u8 *source, s32 player_index) {
    u8 *flag_model;
    u8 *attachment_link;
    u8 *attachment_rotation;
    u8 *scale_model;
    u8 *attachment_color;

    flag_model = *(u8 **)((u8 *)(u32)D_8620E198 + 469180) + player_index * 396;
    *(u32 *)(flag_model + 12) &= ~0x10000000;
    attachment_link = *(u8 **)((u8 *)(u32)D_8620E198 + 469184) + player_index * 24;
    *(u8 **)attachment_link = source + 36;
    attachment_rotation = *(u8 **)((u8 *)(u32)D_8620E198 + 469184) + player_index * 24;
    *(f32 *)(attachment_rotation + 4) = 0.0f;
    *(f32 *)(attachment_rotation + 12) = 0.0f;
    *(f32 *)(attachment_rotation + 8) = 180.0f;
    scale_model = *(u8 **)((u8 *)(u32)D_8620E198 + 469180) + player_index * 396;
    *(f32 *)(scale_model + 84) = 4.0f;
    *(f32 *)(scale_model + 88) = 4.0f;
    *(f32 *)(scale_model + 92) = 4.0f;
    attachment_color = *(u8 **)((u8 *)(u32)D_8620E198 + 469184) + player_index * 24;
    attachment_color[18] = 255;
    attachment_color[19] = 255;
    attachment_color[20] = 255;
    attachment_color[21] = 150;
}
#endif

void func_862055E8(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26BF40/func_862055F0.s")
#endif

#ifdef VERSION_US
void func_86205724(s32 index) {}
#endif

#ifdef VERSION_US
void func_8620572C(s32 index, f32 *origin, f32 *direction) {}
#endif

#ifdef VERSION_US

void func_8620573C(f32 *arg0, f32 *arg1) {
    f32 first;
    f32 third;

    first = *(f32 *)((u8 *)(u32)D_8620E198 + 0x18) * arg1[0];
    arg0[0] += first + first;
    arg0[1] += *(f32 *)((u8 *)(u32)D_8620E198 + 0x18) * 4.25f;
    third = *(f32 *)((u8 *)(u32)D_8620E198 + 0x18) * arg1[2];
    arg0[2] += third + third;
}
#endif

#ifdef VERSION_US
void SceneMotion_RemoveInwardVelocity(u8 *object, f32 *normal) {
    f32 dot;

    dot = *(f32 *)(object + 24) * normal[2] + (*(f32 *)(object + 20) * normal[1] + normal[0] * *(f32 *)(object + 16));
    if (dot < 0.0f) {
        *(f32 *)(object + 16) -= normal[0] * dot;
        *(f32 *)(object + 20) -= normal[1] * dot;
        *(f32 *)(object + 24) -= normal[2] * dot;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26BF40/func_8620581C.s")
#endif

#ifdef VERSION_US
void SceneMotion_ResolvePlayerContacts(void) {
    u8 *model;
    u8 *node;
    u8 *metadata;
    s32 player_index;

    model = (u8 *)(u32)D_8620E198 + 467576;
    for (player_index = 0; player_index < 4; player_index++, model += 396) {
        if (*(u32 *)(model + 12) & 0x20000000) {
            node = *(u8 **)((u8 *)(u32)D_8620E198 + 384);
            while (node != NULL) {
                metadata = *(u8 **)(node + 32);
                *(f32 *)(metadata + 32) = 0.0f;
                *(f32 *)(metadata + 28) = 0.0f;
                *(f32 *)(metadata + 24) = 0.0f;
                func_8620581C(player_index, model, node);
                *(f32 *)(node + 72) += *(f32 *)(metadata + 24);
                *(f32 *)(node + 76) += *(f32 *)(metadata + 28);
                *(f32 *)(node + 80) += *(f32 *)(metadata + 32);
                *(f32 *)(metadata + 24) = 0.0f;
                *(f32 *)(metadata + 28) = 0.0f;
                *(f32 *)(metadata + 32) = 0.0f;
                node = *(u8 **)(node + 4);
            }
        }
    }
}
#endif

#ifdef VERSION_US
void SceneModel_StartPlayerAction(s32 player_index) {
    u8 *model;
    u8 *metadata;

    model = (u8 *)(u32)D_8620E198 + player_index * 396 + 467576;
    if (!(*(u32 *)(model + 12) & 0x80000000)) {
        metadata = *(u8 **)(model + 32);
        if (!(*(u32 *)(model + 12) & 0x20000000)) {
            if (*(s32 *)(model + 28) > 6 * *(s32 *)((u8 *)(u32)D_8620E198 + 60) + 3 * *(s32 *)((u8 *)(u32)D_8620E198 + 60)) {
                *(s32 *)(model + 28) = 0;
                *(u32 *)(model + 12) |= 0x20000000;
                func_8003F210(model + 36, 2);
                ModelAnim_SetFrame(model + 36, 5);
                if (*(s32 *)(metadata + 8) != *(s32 *)(metadata + 4)) {
                    func_862055F0(model, player_index, *(s32 *)(metadata + 4));
                }
                func_8002781C(48896, (u8)player_index, metadata + 24);
            }
        }
    }
}
#endif

#ifdef VERSION_US
void SceneModel_SelectPlayerDirection(s32 player_index, s32 choice_index) {
    u8 *model;
    u8 *metadata;

    model = (u8 *)(u32)D_8620E198 + player_index * 396 + 467576;
    metadata = *(u8 **)(model + 32);
    if (!(*(u32 *)(model + 12) & 0x80000000) && choice_index != *(s32 *)(metadata + 4)) {
        if (*(u32 *)(model + 12) & 0x20000000) {
            if (!(*(u32 *)(model + 12) & 0x40000000) && (*(s32 *)(model + 108) >> 16) < 2 * *(s32 *)((u8 *)(u32)D_8620E198 + 60)) {
                *(s32 *)(metadata + 4) = choice_index;
                func_862055F0(model, player_index, choice_index);
                func_8003F210(model + 36, 2);
                ModelAnim_SetFrame(model + 36, 5);
                *(u32 *)(model + 12) |= 0x40000000;
            }
        } else {
            *(s32 *)(metadata + 8) = choice_index;
            if (*(s16 *)(model + 100) != 5) {
                func_8003F210(model + 36, 5);
            }
        }
    }
}
#endif

#ifdef VERSION_US
void SceneModel_UpdateAnimationState(u8 *metadata) {
    s32 ticks;

    switch (*(u16 *)(D_87F119DC + 100)) {
    case 5:
        if (ModelAnim_IsFinished(D_87F119DC + 36)) {
            *(s32 *)(metadata + 4) = *(s32 *)(metadata + 8);
            func_862055F0(D_87F119DC, *(s32 *)metadata, *(s32 *)(metadata + 8));
            func_8003F210(D_87F119DC + 36, 6);
        }
        break;
    case 0:
        if (ModelAnim_IsFinished(D_87F119DC + 36)) {
            func_8003F210(D_87F119DC + 36, 2);
        }
        break;
    case 2:
        if (func_8003EC54(D_87F119DC + 36) == 4) {
            func_8003F210(D_87F119DC + 36, 1);
        }
        if (ModelAnim_IsFinished(D_87F119DC + 36)) {
            func_8003F210(D_87F119DC + 36, 1);
        }
        ticks = *(s32 *)((u8 *)(u32)D_8620E198 + 60);
        if (*(s32 *)(D_87F119DC + 28) > 3 * ticks + 6 * ticks) {
            *(u32 *)(D_87F119DC + 12) &= 0x9EFFFFFF;
        }
        break;
    case 6:
        if (ModelAnim_IsFinished(D_87F119DC + 36)) {
            func_8003F210(D_87F119DC + 36, 1);
        }
        break;
    case 1:
        if (*(u32 *)(D_87F119DC + 12) & 0x80000000) {
            *(u32 *)(D_87F119DC + 12) &= 0x7FFFFFFF;
        }
        break;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26BF40/func_86205F34.s")
#endif

#ifdef VERSION_US
void SceneModel_UpdateAnimatedPosition(void) {
    u8 *metadata;
    f32 *rotation;
    u8 *attachment;
    s32 frame;

    metadata = *(u8 **)(D_87F119DC + 32);
    func_87C03B60((u8 *)(u32)D_8620E198 + 474308, (f32 *)(D_87F119DC + 72), (f32 *)(metadata + 24));
    if (*(s16 *)(D_87F119DC + 100) == 2) {
        frame = (*(s32 *)(D_87F119DC + 108) >> 16) - 4;
        frame = frame < 0 ? 0 : frame;
    } else {
        frame = 0;
    }
    rotation = D_862090C0 + frame * 3;
    *(f32 *)(metadata + 12) = rotation[0] + *(f32 *)(D_87F119DC + 72);
    *(f32 *)(metadata + 16) = rotation[1] + *(f32 *)(D_87F119DC + 76);
    *(f32 *)(metadata + 20) = rotation[2] + *(f32 *)(D_87F119DC + 80);
    attachment = *(u32 *)metadata * 24 + *(u8 **)((u8 *)(u32)D_8620E198 + 469184);
    *(f32 *)(attachment + 4) = rotation[0];
    *(f32 *)(attachment + 8) = rotation[1] + 180.0f;
    *(f32 *)(attachment + 12) = rotation[2];
    if (*(s32 *)((u8 *)(u32)D_8620E198 + 232) == 5) {
        func_86205F34(metadata);
    } else {
        SceneModel_UpdateAnimationState(metadata);
    }
}
#endif

#ifdef VERSION_US

void func_86206304(void) {
    func_87F02684(D_8620E198 + 0x72264);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26BF40/func_86206334.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/50/fragment50_26BF40/func_86206508.s")
#endif
