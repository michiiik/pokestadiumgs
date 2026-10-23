#include "global.h"


#ifdef VERSION_US
typedef void *SceneModelResources[4][2];
extern u8 *D_87F119DC;
extern u32 func_8003570C(void);
extern void func_8003F1DC(void *);
extern void func_8003F114(u8 *, s16, s16, void *);
extern s32 ModelAnim_SetAnimation(void *, s32);
extern void ModelAnim_SetFrame(u8 *, s16);
extern u8 *func_87F025B8(void *, void (*)(void));
extern void func_87F06430(f32 *, s32);
extern u8 *D_8620E198;
extern void func_87F02684(void *);
extern void func_87F0277C(void *);
extern u8 D_87F15B70[];
extern s32 func_8004DDF4(s32);
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern s32 WidgetTree_RunMessagePanelSilent(s32, s32);
extern void MainPool_FinalizeAllocation(s32);
extern void func_87F0252C(void *, void *, void *, s32);

void SceneModels_SelectAlternateAnimation(void) {
    switch (*(s32 *)(D_8620E198 + 232)) {
    case 1: break;
    case 2:
        if (*(s16 *)(D_87F119DC + 100) == 0) {
            func_8003F1DC(D_87F119DC + 36);
            func_8003F114(D_87F119DC + 36, 0, -1, (*(SceneModelResources *)(D_8620E198 + 332))[*(s32 *)(D_87F119DC + 32)][1]);
            if (func_8003570C() % 5 == 0) {
                ModelAnim_SetAnimation(D_87F119DC + 36, 4);
                ModelAnim_SetFrame(D_87F119DC + 36, 7);
            } else {
                ModelAnim_SetAnimation(D_87F119DC + 36, 3);
                ModelAnim_SetFrame(D_87F119DC + 36, 7);
            }
        }
        break;
    }
}

void func_8620736C(void) {
    func_87F02684(D_8620E198 + 0x728C8);
}

void func_8620739C(void) {
    func_87F0277C(D_8620E198 + 0x728C8);
}

void SceneModels_CreatePairs(void) {
    s32 index;
    u8 *item;
    for (index = 0; index < 4; index++) {
        item = func_87F025B8(D_8620E198 + 469192, SceneModels_SelectAlternateAnimation);
        if (item != 0) {
            func_8003F1DC(item + 36);
            func_8003F114(item + 36, 0, -1, (*(SceneModelResources *)(D_8620E198 + 332))[index][0]);
            ModelAnim_SetAnimation(item + 36, 0);
            ModelAnim_SetFrame(item + 36, func_8003570C() % (*(u16 *)(*(u8 **)(item + 104) + 10) + 1));
            func_87F06430((f32 *)(item + 72), index);
            *(f32 *)(item + 92) = 0.08f;
            *(f32 *)(item + 88) = 0.08f;
            *(f32 *)(item + 84) = 0.08f;
            *(f32 *)(item + 76) -= 7.0f;
            *(s32 *)(item + 32) = index;
        }
        item = func_87F025B8(D_8620E198 + 469192, 0);
        if (item != 0) {
            func_8003F1DC(item + 36);
            func_8003F114(item + 36, 0, -1, *(void **)(D_8620E198 + 364));
            func_87F06430((f32 *)(item + 72), index);
            *(f32 *)(item + 92) = 0.125f;
            *(f32 *)(item + 88) = 0.125f;
            *(f32 *)(item + 84) = 0.125f;
            *(f32 *)(item + 72) += 2.5f;
            *(f32 *)(item + 76) -= 23.0f;
        }
    }
}

void func_862075BC(void) {
    s32 handle;
    func_8004DDF4(0xB7);
    handle = MainPool_AllocState(main_pool_get_available(), 0);
    *(s32 *)(D_8620E198 + 0x16C) = WidgetTree_RunMessagePanelSilent(handle, 0xB7);
    MainPool_FinalizeAllocation(handle);
    func_87F0252C(D_87F15B70, D_8620E198 + 0x728C8, D_8620E198 + 0x728DC, 8);
}
#endif
