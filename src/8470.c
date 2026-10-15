#include "global.h"


#ifdef VERSION_US
extern s32 D_800D0554;
extern Gfx *D_800D0510;
extern Gfx D_800872D8[];
void StageFade_Update(void) {
    u8 alpha, red, green, blue;
    if (((u8 *)(u32)D_800D0554)[0x11] != 0) {
        red = (*(u16 *)(((u8 *)(u32)D_800D0554) + 0x14) & 0xF800) >> 11;
        green = (*(u16 *)(((u8 *)(u32)D_800D0554) + 0x14) & 0x7C0) >> 6;
        blue = (*(u16 *)(((u8 *)(u32)D_800D0554) + 0x14) & 0x3E) >> 1;
        red = (red << 3) | (red >> 2);
        green = (green << 3) | (green >> 2);
        blue = (blue << 3) | (blue >> 2);
        switch (((u8 *)(u32)D_800D0554)[0x11]) {
            case 1: alpha = 255; break;
            case 2: alpha = 255 - (((u8 *)(u32)D_800D0554)[0x13] * 255) / ((u8 *)(u32)D_800D0554)[0x12]; break;
            case 3: alpha = (((u8 *)(u32)D_800D0554)[0x13] * 255) / ((u8 *)(u32)D_800D0554)[0x12]; break;
        }
        if (alpha != 0) {
            gDPSetEnvColor(D_800D0510++, red, green, blue, alpha);
            gSPDisplayList(D_800D0510++, D_800872D8);
        }
        if (((u8 *)(u32)D_800D0554)[0x11] != 1) {
            ((u8 *)(u32)D_800D0554)[0x13]++;
            if (((u8 *)(u32)D_800D0554)[0x12] == ((u8 *)(u32)D_800D0554)[0x13]) {
                if (((u8 *)(u32)D_800D0554)[0x11] == 2) { ((u8 *)(u32)D_800D0554)[0x11] = 0; } else { ((u8 *)(u32)D_800D0554)[0x11] = 1; }
            }
        }
    }
}

s32 StageFade_Start(s32 duration) {
    s32 result = 0;
    s32 one = 1;
    u8 *fade = (u8 *)(u32)D_800D0554;
    s32 mode;
    if (fade != 0) {
        mode = fade[0x11];
        if (one == mode || mode == 0) {
            if (one == mode) { fade[0x11] = 2; } else { fade[0x11] = 3; }
            ((u8 *)(u32)D_800D0554)[0x13] = 0;
            ((u8 *)(u32)D_800D0554)[0x12] = duration;
            result = 1;
        }
    }
    return result;
}

s32 StageFade_StartFromOpaque(s32 duration) {
    s32 result = 0;
    if ((D_800D0554 != 0) && (*(u8 *)((u8 *)(u32)D_800D0554 + 0x11) == 1)) {
        result = StageFade_Start(duration);
    }
    return result;
}

s32 StageFade_StartFromTransparent(s32 duration) {
    s32 var_v1;

    var_v1 = 0;
    if ((D_800D0554 != 0) && ((*(u8 *)((u8 *)(D_800D0554) + (0x11))) == 0)) {
        var_v1 = StageFade_Start(duration);
    }
    return var_v1;
}

void StageFade_SetMode(s32 arg0) {
    if (D_800D0554 != 0) {
        ((u8 *)(u32)D_800D0554)[0x11] = arg0;
        ((u8 *)(u32)D_800D0554)[0x13] = 0;
        ((u8 *)(u32)D_800D0554)[0x12] = 0;
    }
}

void Profiler_SetDisplayModes(s32 arg0, s32 arg1) { extern s32 D_80087230; extern s32 D_80087234; if ((u32)arg0 < 3) D_80087230 = arg0; if ((u32)arg1 < 2) D_80087234 = arg1; }

void Gfx_SetDefaultRenderState(void) {
    gDPPipeSync(D_800D0510++);
    gDPPipelineMode(D_800D0510++, G_PM_1PRIMITIVE);
    gDPSetTextureLOD(D_800D0510++, G_TL_TILE);
    gDPSetTextureLUT(D_800D0510++, G_TT_NONE);
    gDPSetTextureDetail(D_800D0510++, G_TD_CLAMP);
    gDPSetTexturePersp(D_800D0510++, G_TP_PERSP);
    gDPSetTextureFilter(D_800D0510++, G_TF_BILERP);
    gDPSetTextureConvert(D_800D0510++, G_TC_FILT);
    gDPSetCombineKey(D_800D0510++, G_CK_NONE);
    gDPSetAlphaCompare(D_800D0510++, G_AC_NONE);
    gDPSetColorDither(D_800D0510++, G_CD_MAGICSQ);
    gDPSetAlphaDither(D_800D0510++, G_AD_PATTERN);
    gDPSetCycleType(D_800D0510++, G_CYC_1CYCLE);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFE793C);
    gDPPipeSync(D_800D0510++);
  }

void Gfx_SetDefaultGeometryState(void) {
    gSPClearGeometryMode(D_800D0510++, 0x3F0604);
    gSPSetGeometryMode(D_800D0510++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK);
    gSPTexture(D_800D0510++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
}

extern void GfxImage_ResetCurrent(void);
extern s32 func_8000339C(void);
extern void Memmap_SetSegmentMap(s32, s32, s32);
extern void func_80002178(void *);
extern void Gfx_SetDefaultRenderState(void);
extern void Gfx_SetDefaultGeometryState(void);
void func_80007E18(void) {
    GfxImage_ResetCurrent();
    Memmap_SetSegmentMap(0, 0x80000000, func_8000339C());
    func_80002178(&D_800D0510);
    Gfx_SetDefaultRenderState();
    Gfx_SetDefaultGeometryState();
}

extern Mtx D_800D0558;
extern Mtx D_80087238;
extern Vp D_80087278;
extern Vp D_80087288;
extern s32 D_80087230;
extern s32 D_80087234;
extern void GfxImage_SetRenderTarget(Gfx **, s32);
extern void Gfx_SetScissorRect(Gfx **, s32, s32, s32, s32);
extern void StageFade_Update(void);
extern void func_8000B0F0(void);
extern void TextRenderer_FlushQueuedStrings(Gfx **, s32);
extern void draw_profiler(s32);
extern void func_800034E4(Gfx **);
extern u32 Gfx_AllocDisplayList(s32);
extern s32 StageContext_IsHighResolution(void);
void StageLoader_SetupFrame(void) {
    GfxImage_SetRenderTarget(&D_800D0510, ((s32 *)((u8 *)(u32)D_800D0554 + 0x18))[*(s8 *)((u8 *)(u32)D_800D0554 + 0x16)]);
    guOrtho(&D_800D0558, 0.0f, 320.0f, 0.0f, 240.0f, -2.0f, 2.0f, 1.0f);
    Gfx_SetDefaultRenderState();
    Gfx_SetDefaultGeometryState();
    gSPMatrix(D_800D0510++, (u32)&D_80087238 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(D_800D0510++, (u32)&D_800D0558 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPPerspNormalize(D_800D0510++, 0xFFFF);
    if (*(s8 *)((u8 *)(u32)D_800D0554 + 0xC) == 1) {
        gSPViewport(D_800D0510++, (u32)&D_80087288 & 0x1FFFFFFF);
    } else {
        gSPViewport(D_800D0510++, (u32)&D_80087278 & 0x1FFFFFFF);
    }
    Gfx_SetScissorRect(&D_800D0510, 0, 0, *(s16 *)((u8 *)(u32)D_800D0554), *(s16 *)((u8 *)(u32)D_800D0554 + 2));
    StageFade_Update();
    if (D_80087230 != 0) { func_8000B0F0(); }
    TextRenderer_FlushQueuedStrings(&D_800D0510, StageContext_IsHighResolution());
    if (D_80087230 != 0) { draw_profiler(D_80087230 - 1); }
    if (D_80087230 != 0) { if (D_80087234 != 0) { func_800034E4(&D_800D0510); } }
    gDPFullSync(D_800D0510++);
    gSPEndDisplayList(D_800D0510++);
    Gfx_AllocDisplayList(0);
}

void StageLoader_SwapDisplayListAndReset(void) { Gfx_SwapDisplayListBuffer(); func_80007E18(); }

extern s32 D_800D0540;
extern s32 D_800D0544;
extern s32 D_800D0548;
extern void StageLoader_SetupFrame(void);
extern void Gfx_GetDisplayListRange(void **, s32 *);
void StageLoader_BeginFrame(void) {
    u8 *context;
    u8 *request;
    StageLoader_SetupFrame();
    context = (u8 *)(u32)D_800D0554;
    request = (u8 *)&D_800D0540;
    request[0] = *(s8 *)(context + 0x10);
    request[1] = *(s8 *)(context + 0xC);
    request[2] = *(s8 *)(context + 0xD);
    request[3] = *(s8 *)(context + 0x16);
    *(s32 *)((u8 *)&D_800D0540 + 0xC) = ((s32 *)(context + 0x18))[*(s8 *)(context + 0x16)];
    Gfx_GetDisplayListRange((void **)&D_800D0544, &D_800D0548);
    (*(s8 *)((u8 *)(u32)D_800D0554 + 0x16))++;
    if (*(s8 *)((u8 *)(u32)D_800D0554 + 0xE) == *(s8 *)((u8 *)(u32)D_800D0554 + 0x16)) {
        *(s8 *)((u8 *)(u32)D_800D0554 + 0x16) = 0;
    }
}

extern void BgStage_DrawFrame(void);
void func_80008188(void) {
    typedef struct { s16 width, height; s16 left, right, top, bottom; } ClearFrameRect;
    BgStage_DrawFrame();
    gDPPipeSync(D_800D0510++);
    gDPSetCycleType(D_800D0510++, G_CYC_FILL);
    gDPSetRenderMode(D_800D0510++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetAlphaCompare(D_800D0510++, G_AC_NONE);
    gDPSetFillColor(D_800D0510++, *(u16 *)((u8 *)(u32)D_800D0554 + 0x14) | (*(u16 *)((u8 *)(u32)D_800D0554 + 0x14) << 16));
    gDPFillRectangle(D_800D0510++, ((ClearFrameRect *)(u32)D_800D0554)->left, ((ClearFrameRect *)(u32)D_800D0554)->top, ((ClearFrameRect *)(u32)D_800D0554)->right, ((ClearFrameRect *)(u32)D_800D0554)->bottom);
    gDPPipeSync(D_800D0510++);
    gDPSetCycleType(D_800D0510++, G_CYC_1CYCLE);
}

typedef struct {
    s16 width, height, left, right, top, bottom;
    s8 resolution, mode, imageCount, depthFlag, type;
    u8 fadeMode, duration, progress;
    u16 clearColor;
    s8 currentImage, status;
    s32 images[3];
} StageContextRecord;
extern s32 main_pool_alloc(s32, s32);
extern s32 Display_GetFramebufferClearColor(void);
extern s32 func_800071A4(s32, s32, s32, s32, s32);
extern void GfxImage_AttachDepthBuffer(u8 *, u8 *);
StageContextRecord *StageContext_Allocate(s8 resolution, s8 mode, s8 imageCount, s8 depthFlag, s8 type, s32 allocate) {
    StageContextRecord *context;
    s32 index;
    s32 depth;
    context = (StageContextRecord *)(u32)main_pool_alloc(0x24, 0);
    if (context != 0) {
        if (resolution == 1) { context->width = 640; context->height = 480; }
        else { context->width = 320; context->height = 240; }
        context->fadeMode = 1;
        context->resolution = resolution;
        context->mode = mode;
        context->imageCount = imageCount;
        context->depthFlag = depthFlag;
        context->type = type;
        context->clearColor = Display_GetFramebufferClearColor();
        context->currentImage = 0;
        context->status = type;
        context->left = 0;
        context->right = context->width - 1;
        context->top = 0;
        context->bottom = context->height - 1;
        context->images[0] = 0;
        context->images[1] = 0;
        context->images[2] = 0;
        if (allocate != 0) {
            index = 0;
            while (index < context->imageCount) {
                context->images[index] = func_800071A4(0, 2, context->width, context->height, 1);
                index++;
            }
            if (context->depthFlag == 1) {
                depth = func_800071A4(0, 2, context->width, context->height, 0);
                index = 0;
                while (index < context->imageCount) {
                    GfxImage_AttachDepthBuffer((u8 *)(u32)context->images[index], (u8 *)(u32)depth);
                    index++;
                }
            }
        }
    }
    return context;
}


s32 func_80008494(void) {
    return D_800D0554;
}


u8 StageContext_GetFadeMode(void) {
    return ((u8 *)(u32)D_800D0554)[0x11];
}

void StageContext_SaveAndSwitch(void *arg0) {
    s8 temp_v0;

    (*(u8 *)((u8 *)(arg0) + (0x11))) = (u8) (*(u8 *)((u8 *)(D_800D0554) + (0x11)));
    (*(u8 *)((u8 *)(arg0) + (0x12))) = (u8) (*(u8 *)((u8 *)(D_800D0554) + (0x12)));
    (*(u8 *)((u8 *)(arg0) + (0x13))) = (u8) (*(u8 *)((u8 *)(D_800D0554) + (0x13)));
    (*(u16 *)((u8 *)(arg0) + (0x14))) = (u16) (*(u16 *)((u8 *)(D_800D0554) + (0x14)));
    temp_v0 = (*(s8 *)((u8 *)(D_800D0554) + (0x16)));
    if (temp_v0 < (*(s8 *)((u8 *)(arg0) + (0xE)))) {
        (*(s8 *)((u8 *)(arg0) + (0x16))) = temp_v0;
    } else {
        (*(s8 *)((u8 *)(arg0) + (0x16))) = 0;
    }
    D_800D0554 = (s32) arg0;
}

extern void func_8003539C(void);
extern void Display_QueueFramebufferRequest(s32);
extern void Display_WaitForCompletion(void);
extern u8 func_80002014(void);
extern void Display_ClearFramebufferLine(u16);
void func_80008514(s32 arg0) {
    D_800D0554 = arg0;
    func_8003539C();
    Display_QueueFramebufferRequest(0);
    Display_WaitForCompletion();
    *(u8 *)((u8 *)(u32)D_800D0554 + 0x17) = func_80002014();
    Display_ClearFramebufferLine(*(u16 *)((u8 *)(u32)arg0 + 0x14));
    StageLoader_SwapDisplayListAndReset();
}

extern void func_80008188(void);
extern void StageLoader_BeginFrame(void);
extern void Display_WaitForFrames(s32);
void func_80008574(void) {
    if (D_800D0554 != 0) {
        func_80008188();
        StageLoader_BeginFrame();
        func_8003539C();
        Display_QueueFramebufferRequest((s32)&D_800D0540);
        Display_WaitForCompletion();
        *(u8 *)((u8 *)(u32)D_800D0554 + 0x17) = func_80002014();
        Display_WaitForFrames(2);
        D_800D0554 = 0;
    }
}

s32 func_8000204C();

void StageLoader_WaitForRetrace(void) {
    if (func_8000204C() == 0) {
        do {

        } while (func_8000204C() == 0);
    }
}

extern Gfx *D_800D0510; void func_80008624(void) { func_80002178(&D_800D0510); }

s32 func_80008648(void) {
    StageLoader_BeginFrame();
    func_8003539C();
    Display_QueueFramebufferRequest((s32)&D_800D0540);
    Display_WaitForCompletion();
    *(u8 *)((u8 *)(u32)D_800D0554 + 0x17) = func_80002014();
    StageLoader_SwapDisplayListAndReset();
    return *(s8 *)((u8 *)(u32)D_800D0554 + 0x17);
}

extern void StageLoader_SwapDisplayListAndReset(void);
void func_800086A4(s32 frames) {
    s32 *request;
    while (frames-- > 0) {
        request = &D_800D0540;
        func_80008188();
        StageLoader_BeginFrame();
        func_8003539C();
        Display_QueueFramebufferRequest((s32)request);
        Display_WaitForCompletion();
        ((u8 *)(u32)D_800D0554)[0x17] = func_80002014();
        StageLoader_SwapDisplayListAndReset();
    }
}

s32 BgStage_RunUntilCondition(u32 frames, s32 (*callback)(s32)) {
    s32 result = 0;
    if (frames == 0) {
        do {
            result = callback(((u8 *)(u32)D_800D0554)[0x11]);
            func_80008648();
        } while (result == 0);
    } else {
        while (frames-- > 0) {
            result = callback(((u8 *)(u32)D_800D0554)[0x11]);
            func_80008648();
            if (result != 0) break;
        }
    }
    return result;
}

s32 BgStage_WaitForCondition(s32 (*callback)(s32), s32 opaqueFrames, s32 transparentFrames) {
    s32 result = 0;
    s32 active = 1;
    s32 value;
    StageFade_StartFromOpaque(opaqueFrames);
    while (active) {
        value = callback(((u8 *)(u32)D_800D0554)[0x11]);
        if (result == 0) {
            if (value != 0) {
                result = value;
                StageFade_StartFromTransparent(transparentFrames);
            }
        } else {
            if (((u8 *)(u32)D_800D0554)[0x11] == 1) active = 0;
        }
        func_80008648();
    }
    return result;
}

void StageContext_SetClearColor(u16 arg0) {
    if (D_800D0554 != 0) {
        *(u16 *)((u8 *)(u32)D_800D0554 + 0x14) = arg0 | 1;
        Display_ClearFramebufferLine(arg0);
    }
}

void BgStage_DrawFrame(void) {
    u8 *context = (u8 *)(u32)D_800D0554;
    if (context != 0) {
        GfxImage_SetRenderTarget(&D_800D0510, ((s32 *)(context + 0x18))[*(s8 *)(context + 0x16)]);
        gDPSetCycleType(D_800D0510++, G_CYC_1CYCLE);
    }
}

typedef struct {
    u8 pad16[0x16];
    s8 index16;
} Func80008944State;
s32 StageContext_GetCurrentImage(void) {
    s32 result = 0;
    if (D_800D0554 != 0) {
        Func80008944State *p = (Func80008944State *)(u32)D_800D0554;
        result = *(s32 *)((u8 *)p + (p->index16 << 2) + 0x18);
    }
    return result;
}

s32 func_80008970(void) { s32 value = 0; if (D_800D0554 != 0) { value = *(s8 *)((u8 *)(u32)D_800D0554 + 0x17); } return value; }

s32 StageContext_IsHighResolution(void) { extern s32 D_800D0554; s32 value = 0; if (D_800D0554 != 0) { value = ((s8 *)((u8 *)(u32)D_800D0554))[0xC] == 1; } return value; }
#endif
