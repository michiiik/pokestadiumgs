#include "global.h"


#ifdef VERSION_US
extern s32 D_80126F40;

s32 func_80042B00(s32 arg0, s32 arg1) {
    if (!arg0) {
        D_80126F40 = arg1;
    }
    return 0;
}

void func_80042B14(u8 *arg0) {
    *(u16 *)(arg0 + 0) = 0;
    *(u32 *)(arg0 + 4) = 0;
}

extern s32 func_80064728();
extern void func_8003F5AC();
void func_80042B20(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4) {
    if (arg1 != 0) {
        *arg3 = func_80064728(arg2);
        *(u16 *)(arg0 + 0) |= 1;
        func_8003F5AC(arg4, arg2);
    } else {
        *arg3 = arg2;
        *(u16 *)(arg0 + 0) &= 0xFFFE;
        *arg4 = 0;
    }
    *(u16 *)(arg0 + 0) |= 2;
    *(s32 *)(arg0 + 4) = arg2;
}

void func_80042BB0(u16 *arg0) {
    *arg0 &= (u16)~2;
}

extern u8 D_80094C64;
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState();
extern s32 process_geo_layout();
extern void MainPool_FinalizeAllocation();
extern void GeoCamera_SetViewport(void *, s16, s16, s16, s32);
extern void GeoCamera_SetPerspective(void *, f32, f32, f32);
void func_80042BC0(u8 *arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4) {
    s32 temp;
    temp = MainPool_AllocState(main_pool_get_available(), 0);
    *(s32 *)(arg0 + 0x18) = process_geo_layout(temp, &D_80094C64);
    *(s32 *)(arg0 + 0x1C) = D_80126F40;
    MainPool_FinalizeAllocation(temp);
    GeoCamera_SetViewport((void *)(u32)*(u32 *)((u8 *)(u32)*(u32 *)(arg0 + 0x18) + 0xC), arg1, arg2, arg3, arg4);
    GeoCamera_SetPerspective((void *)(u32)*(u32 *)((u8 *)(u32)*(u32 *)(arg0 + 0x18) + 0xC), 30.0f, 100.0f, 12800.0f);
}

typedef struct ModelPreviewState {
    u16 flags, clearColor;
    s16 width, height;
    void *callback;
    s16 countdown, rotationStep;
    f32 scale;
    void *resource;
    void *layout;
    u8 *model;
    u8 *image;
    u8 *depth;
    u8 selection[8];
} ModelPreviewState;
extern void *main_pool_alloc(s32, s32);
extern void *func_800071A4(s32, s32, s32, s32, s32);
extern void GfxImage_AttachDepthBuffer(u8 *, u8 *);
ModelPreviewState *ModelPreview_Create(void *resource, s32 width, s32 height) {
    ModelPreviewState *state;

    state = main_pool_alloc(sizeof(ModelPreviewState), 0);
    if (state != NULL) {
        state->flags = 0x106;
        state->clearColor = 1;
        state->callback = NULL;
        state->countdown = 0;
        state->rotationStep = 0;
        state->width = width;
        state->height = height;
        state->scale = 1.0f;
        state->resource = resource;
        state->layout = NULL;
        state->model = NULL;
        state->image = func_800071A4(0, 2, width, height, 0);
        state->depth = func_800071A4(0, 2, width, height, 1);
        GfxImage_AttachDepthBuffer(state->image, state->depth);
        func_80042BC0((u8 *)state, 0, 0, width, height);
        func_80042B14(state->selection);
    }
    return state;
}

s32 func_80042D54(u8 *arg0, u16 arg1) { s32 result = 0; if (arg0 != NULL) { *(u16 *)(arg0 + 2) = arg1; result = 1; } return result; }

s32 func_80042D74(u8 *arg0, s32 arg1) { s32 result = 0; if (arg0 != NULL) { *(s32 *)(arg0 + 8) = arg1; result = 1; } return result; }

typedef struct { f32 x, y, z; } FleetVec3f4C2E0;
typedef struct { s16 x, y, z; } PreviewRotation;
typedef struct PreviewSelectionRecord { u16 flags, unknown02; u32 value; } PreviewSelectionRecord;
typedef struct { u8 unknown00[8]; void **models; } PreviewResourceModel;
typedef struct { u8 unknown00[56]; PreviewResourceModel *model; } PreviewResourceView;
typedef struct { u8 unknown00[64]; void *loadedCurve; } SceneAnimationResource;
extern PreviewRotation D_800948DC;
extern s32 func_80064728(u8 *);
extern f32 func_8004B888(s32);
extern s32 func_8004B7E0(s32, FleetVec3f4C2E0 *);
extern void func_8003F1DC(void *);
extern void func_8003F114(u8 *, s16, s16, void *);
extern s32 SceneObject_SetModelVariant(u8 *, s32, u16);
extern s32 ModelAnim_SetResourceAnimation(SceneAnimationResource *, u8 *, s32);
// Resolve the pending record/species selection into the preview display object.
void ModelPreview_RefreshSelection(void *state) {
    PreviewSelectionRecord *selection = (PreviewSelectionRecord *)((ModelPreviewState *)state)->selection;
    u8 *record;
    s32 species;
    u16 variant;
    if (selection->flags & 1) {
        record = (u8 *)selection->value;
        species = func_80064728(record);
        variant = *(u16 *)(record + 0x16);
    } else {
        species = selection->value;
        variant = 0;
    }
    ((ModelPreviewState *)state)->rotationStep = 256;
    ((ModelPreviewState *)state)->countdown = 0;
    ((ModelPreviewState *)state)->scale = func_8004B888(species);
    func_8004B7E0(species, (FleetVec3f4C2E0 *)(((ModelPreviewState *)state)->model + 0x24));
    *(PreviewRotation *)(((ModelPreviewState *)state)->model + 0x1E) = D_800948DC;
    func_8003F1DC(((ModelPreviewState *)state)->model);
    func_8003F114(((ModelPreviewState *)state)->model, 0, (s16)species, ((PreviewResourceView *)((ModelPreviewState *)state)->resource)->model->models[0]);
    SceneObject_SetModelVariant(((ModelPreviewState *)state)->model, species, variant);
    ModelAnim_SetResourceAnimation((SceneAnimationResource *)((ModelPreviewState *)state)->resource, ((ModelPreviewState *)state)->model, 1);
    ((ModelPreviewState *)state)->model[2] &= ~0x40;
    ((ModelPreviewState *)state)->model[2] |= 0x80;
    func_80042BB0((u16 *)selection);
}

typedef union { s32 word; s8 bytes[4]; } Func80041FA0State;
extern s32 func_80041FD0(s32, u16, Func80041FA0State, s32);
extern s32 func_8006456C(s32);
extern void func_800428F8(s32);
extern void func_80042B20(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4);
s32 ModelPreview_SetSelection(u8 *root, s32 from_record, s32 value, s32 load) {
    s32 result = 0;
    s32 species;
    Func80041FA0State adjustment;
    u8 *selection;
    s32 variant;
    selection = root + 0x28;
    if ((*(u16 *)selection & 2) == 0) {
        variant = 0;
        func_80042B20(selection, from_record, value, &species, &adjustment.word);
        if (from_record != 0) {
            variant = func_8006456C(*(u16 *)((u8 *)value + 0x16));
        }
        if (load != 0) {
            result = func_80041FD0((s32)((ModelPreviewState *)root)->resource, (u16)species, adjustment, variant);
        } else {
            result = 1;
        }
        if (((ModelPreviewState *)root)->flags & 0x100) {
            if (load != 0) {
                func_800428F8((s32)((ModelPreviewState *)root)->resource);
            }
            ModelPreview_RefreshSelection(root);
        }
    }
    return result;
}

void func_80042F94(void* arg0, void* arg1) {
    ModelPreview_SetSelection(arg0, 1, arg1, 1);
}

void func_80042FBC(void* arg0, void* arg1) {
    ModelPreview_SetSelection(arg0, 0, arg1, 1);
}

void func_80042FE4(void* arg0, void* arg1) {
    ModelPreview_SetSelection(arg0, 0, arg1, 0);
}

typedef struct PreviewSelectionPair {
    u32 first, second;
} PreviewSelectionPair;
typedef struct PreviewSelectionView {
    u8 unknown00[20];
    void *resource;
    u8 unknown18[16];
    PreviewSelectionPair selection;
} PreviewSelectionView;
// Reuse a selection only when both preview states share the same resource.
s32 ModelPreview_TryCopySelection(PreviewSelectionView *dest, PreviewSelectionView *source) {
    s32 result = 0;
    if (dest->resource == source->resource) {
        dest->selection = source->selection;
        dest->resource = source->resource;
        result = 1;
        ModelPreview_RefreshSelection(dest);
    }
    return result;
}

extern s32 func_800427B8();
s32 func_80043064(u8 *arg0) {
    s32 result = 0;
    if (func_800427B8(*(s32 *)(arg0 + 0x14), arg0) != 0) {
        result = *(u16 *)(u32)*(u32 *)((u8 *)(u32)*(u32 *)(arg0 + 0x14) + 0x38);
        ModelPreview_RefreshSelection(arg0);
    }
    return result;
}

extern s32 D_80094C60;
extern void *D_80087200;
// Modes 1-3 edit position, 4 edits rotationY, 5 scale, and 6 animation frame.
void ModelPreview_ApplyEditControls(ModelPreviewState *state) {
    state->flags &= ~4;
    state->model[2] &= ~0x20;
    *(s16 *)(state->model + 0x1E) = 0;
    switch (D_80094C60) {
    case 1:
        if (*(u16 *)((u8 *)D_80087200 + 6) & 0x200) {
            *(f32 *)(state->model + 0x24) -= 1.0f;
        }
        if (*(u16 *)((u8 *)D_80087200 + 6) & 0x100) {
            *(f32 *)(state->model + 0x24) += 1.0f;
        }
        break;
    case 2:
        if (*(u16 *)((u8 *)D_80087200 + 6) & 0x200) {
            *(f32 *)(state->model + 0x28) -= 1.0f;
        }
        if (*(u16 *)((u8 *)D_80087200 + 6) & 0x100) {
            *(f32 *)(state->model + 0x28) += 1.0f;
        }
        break;
    case 3:
        if (*(u16 *)((u8 *)D_80087200 + 6) & 0x200) {
            *(f32 *)(state->model + 0x2C) -= 1.0f;
        }
        if (*(u16 *)((u8 *)D_80087200 + 6) & 0x100) {
            *(f32 *)(state->model + 0x2C) += 1.0f;
        }
        break;
    case 4:
        if (*(u16 *)((u8 *)D_80087200 + 6) & 0x200) {
            *(s16 *)(state->model + 0x20) -= 64;
        }
        if (*(u16 *)((u8 *)D_80087200 + 6) & 0x100) {
            *(s16 *)(state->model + 0x20) += 64;
        }
        break;
    case 5:
        if (*(u16 *)((u8 *)D_80087200 + 6) & 0x200) {
            state->scale -= 0.1f;
        }
        if (*(u16 *)((u8 *)D_80087200 + 6) & 0x100) {
            state->scale += 0.1f;
        }
        break;
    case 6: {
        u8 *model = state->model;
        s16 maximum = *(u16 *)(*(u8 **)(model + 0x44) + 0xA) - 1;
        s16 frame = *(s32 *)(model + 0x48) >> 16;
        s32 buttons = *(u16 *)((u8 *)D_80087200 + 0xC);
        if ((buttons & 0x200) && frame > 0) {
            frame--;
        }
        if ((buttons & 0x100) && frame < maximum) {
            frame++;
        }
        *(s32 *)(model + 0x48) = frame << 16;
        break;
    }
    }
}

extern void *D_80087200;
s32 func_8004335C(s32 arg0, u8 *arg1) {
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0;
    s32 result;

    result = 0;
    if (arg0 == 0) {
        var_v0 = 0x800;
        var_a0 = 0x400;
        var_a1 = 0x200;
        var_a2 = 0x100;
    } else {
        var_v0 = 8;
        var_a0 = 4;
        var_a1 = 2;
        var_a2 = 1;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_v0) != 0) {
        result = 1;
        *(s16 *)(arg1 + 0) = *(s16 *)(arg1 + 0) + 0x400;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_a0) != 0) {
        result = 1;
        *(s16 *)(arg1 + 0) = *(s16 *)(arg1 + 0) - 0x400;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_a1) != 0) {
        result = 1;
        *(s16 *)(arg1 + 2) = *(s16 *)(arg1 + 2) + 0x400;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_a2) != 0) {
        result = 1;
        *(s16 *)(arg1 + 2) = *(s16 *)(arg1 + 2) - 0x400;
    }
    return result;
}

s32 func_80043444(u8 *arg0) { return 0; }

extern s16 Math_StepToS(s16, s16, s16);
// Advance rotationY while damping rotationX back to zero.
void ModelPreview_UpdateAutoRotation(u8 *state) {
    s16 step;
    s16 increment;
    s16 *rotation = (s16 *)(*(u8 **)(state + 0x1C) + 0x1E);

    if (*(s16 *)(state + 0xE) < 256) {
        *(s16 *)(state + 0xE) += 16;
    }
    rotation[1] += *(s16 *)(state + 0xE);
    increment = *(s16 *)(state + 0xE);
    step = (rotation[0] < 0 ? -rotation[0] : rotation[0]) / 12;
    if (step < 8) {
        step = 8;
    }
    if (step < increment) {
        increment = step;
    }
    rotation[0] = Math_StepToS(rotation[0], 0, increment);
}

extern s32 D_80094C60;
extern s32 func_8004335C();
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
void func_80043500(u8 *arg0) {
    s32 result;
    u16 flags;
    s16 countdown;
    f32 scale;

    result = 0;
    if (D_80094C60 != 0) {
        ModelPreview_ApplyEditControls((ModelPreviewState *)arg0);
    }
    flags = *(u16 *)(arg0 + 0);
    if (*(u16 *)(arg0 + 0) & 2) {
        result = func_8004335C((*(u16 *)(arg0 + 0) & 1) != 0, *(s32 *)(arg0 + 0x1C) + 0x1E);
        if (result == 0) {
            result = func_80043444((u8 *)((u32)*(u32 *)(arg0 + 0x1C) + 0x1E));
        }
    }
    if (result != 0) {
        *(s16 *)(arg0 + 0xE) = 0;
        *(s16 *)(arg0 + 0xC) = 0x78;
    } else if (*(u16 *)(arg0 + 0) & 4) {
        countdown = *(s16 *)(arg0 + 0xC);
        if (countdown > 0) {
            *(s16 *)(arg0 + 0xC) = countdown - 1;
        } else {
            ModelPreview_UpdateAutoRotation(arg0);
        }
    }
    scale = *(f32 *)(arg0 + 0x10);
    Vec3f_SetComponentsDuplicate((f32 *)((u32)*(u32 *)(arg0 + 0x1C) + 0x30), scale, scale, scale);
}

extern Gfx *D_800D0510;
extern void GfxImage_FillCurrent();
extern void GfxImage_ClearDepthRectangle();
void func_800435D4(u8 *arg0) {
    void (*callback)();
    callback = *(void (**)())(arg0 + 8);
    if (callback == NULL) {
        GfxImage_FillCurrent(&D_800D0510, *(u16 *)(arg0 + 2));
    } else {
        callback(arg0);
        gDPPipeSync(D_800D0510++);
        gDPSetTexturePersp(D_800D0510++, G_TP_PERSP);
        GfxImage_ClearDepthRectangle(&D_800D0510, 0, 0, *(s16 *)(arg0 + 4), *(s16 *)(arg0 + 6));
    }
}

extern void func_80043500();
extern void GfxImage_SetRenderTarget();
extern void func_800435D4();
extern void GeoRender_AdvanceFrameCounter();
extern void Geo_RenderRootNode();
s32 func_80043678(u8 *arg0) {
    func_80043500(arg0);
    GfxImage_SetRenderTarget(&D_800D0510, *(s32 *)(arg0 + 0x20));
    func_800435D4(arg0);
    GeoRender_AdvanceFrameCounter();
    Geo_RenderRootNode(*(s32 *)(arg0 + 0x18));
    return *(s32 *)((u8 *)(u32)*(u32 *)(arg0 + 0x20) + 8);
}

void func_800436CC(s32 value) { if (value >= 0 && value < 7) D_80094C60 = value; }


s32 func_800436E8(void) {
    return D_80094C60;
}
#endif
