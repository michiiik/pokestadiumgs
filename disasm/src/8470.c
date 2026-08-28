#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80007870.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80007A84.s")

extern s32 D_800D0554;
s32 func_80007A84();
s32 func_80007AEC(void) {
    s32 result = 0;
    if ((D_800D0554 != 0) && (*(u8 *)((u8 *)(u32)D_800D0554 + 0x11) == 1)) {
        result = func_80007A84();
    }
    return result;
}

s32 func_80007A84();
s32 StageFade_StartFromTransparent(void) {
    s32 var_v1;

    var_v1 = 0;
    if ((D_800D0554 != 0) && ((*(u8 *)((u8 *)(D_800D0554) + (0x11))) == 0)) {
        var_v1 = func_80007A84();
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

extern Gfx *D_800D0510;
void func_80007BD0(void) {
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

extern Gfx *D_800D0510;
void func_80007DB4(void) {
    gSPClearGeometryMode(D_800D0510++, 0x3F0604);
    gSPSetGeometryMode(D_800D0510++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK);
    gSPTexture(D_800D0510++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
}

extern void GfxImage_ResetCurrent(void);
extern s32 func_8000339C(void);
extern void Memmap_SetSegmentMap(s32, s32, s32);
extern void func_80002178(void *);
extern void func_80007BD0(void);
extern void func_80007DB4(void);
extern Gfx *D_800D0510;
void func_80007E18(void) {
    GfxImage_ResetCurrent();
    Memmap_SetSegmentMap(0, 0x80000000, func_8000339C());
    func_80002178(&D_800D0510);
    func_80007BD0();
    func_80007DB4();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80007E6C.s")

void StageLoader_SwapDisplayListAndReset(void) { func_80006D6C(); func_80007E18(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_800080E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80008188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_800082E0.s")


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

extern s32 D_800D0554;
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

extern s32 D_800D0554;
extern s32 D_800D0540;
extern void func_80008188(void);
extern void func_800080E0(void);
extern void func_8003539C(void);
extern void Display_QueueFramebufferRequest(s32);
extern void Display_WaitForCompletion(void);
extern u8 func_80002014(void);
extern void Display_WaitForFrames(s32);
void func_80008574(void) {
    if (D_800D0554 != 0) {
        func_80008188();
        func_800080E0();
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

extern s32 D_800D0540;
extern void func_800080E0(void);
extern void func_8003539C(void);
extern void Display_QueueFramebufferRequest(s32);
extern void Display_WaitForCompletion(void);
extern u8 func_80002014(void);
s32 func_80008648(void) {
    func_800080E0();
    func_8003539C();
    Display_QueueFramebufferRequest((s32)&D_800D0540);
    Display_WaitForCompletion();
    *(u8 *)((u8 *)(u32)D_800D0554 + 0x17) = func_80002014();
    StageLoader_SwapDisplayListAndReset();
    return *(s8 *)((u8 *)(u32)D_800D0554 + 0x17);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_800086A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80008734.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_800087E8.s")

extern s32 D_800D0554;
extern void Display_ClearFramebufferLine(u16);
void func_800088A4(u16 arg0) {
    if (D_800D0554 != 0) {
        *(u16 *)((u8 *)(u32)D_800D0554 + 0x14) = arg0 | 1;
        Display_ClearFramebufferLine(arg0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_800088DC.s")

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
