#include "global.h"


#ifdef VERSION_US
typedef struct F66ViewState {
    s32 value;
    s32 x;
    s32 y;
    s32 unused0C;
    s32 secondX;
    s32 secondY;
} F66ViewState;
extern F66ViewState D_82E06138;
extern s32 D_82E0713C;
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E00020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0048C.s")
#endif

#ifdef VERSION_US
/* Same storage as D_82E06138 (aliases.ld), with the callback's coordinate view.
 * Keep the direct scalar store separate from the following structured accesses. */
extern F66ViewState D_82E06138_view;
extern s32 D_82E05650;
s32 func_82E00700(s32 kind, u8* event) {
    switch (kind) {
    case 0:
        switch (*(u32*)(event + 0x20)) {
        case 0:
            D_82E06138.value = event[0x2B] + (event[0x2A] << 8);
            D_82E06138_view.x = *(s16*)(event + 8) - 160;
            D_82E06138_view.y = 120 - *(s16*)(event + 0xA);
            if (D_82E05650 == 0) {
                D_82E06138_view.value = (D_82E06138_view.value * 5) / 6;
            }
            *(u16*)(event + 2) &= 0xFFFE;
            break;
        case 1:
            D_82E06138_view.secondX = *(s16*)(event + 8) - 160;
            D_82E06138_view.secondY = 120 - *(s16*)(event + 0xA);
            *(u16*)(event + 2) &= 0xFFFE;
            break;
        }
        break;
    case 1:
        break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 D_82E075E4;
extern s32 D_82E05650;
extern s32 D_82E07130;
s32 func_82E007F0(s32 arg0, u8 *arg1) {
    switch (arg0) {
    case 0:
        D_82E075E4 = arg1[0x2B] + (arg1[0x2A] << 8);
        if (D_82E05650 == 0) {
            *(s32 *)((u8 *)&D_82E07130 + 0x4B4) = (*(s32 *)((u8 *)&D_82E07130 + 0x4B4) * 5) / 6;
        }
        *(u16 *)(arg1 + 2) &= ~1;
        break;
    case 1:
        break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E00868.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E00E5C.s")
#endif

#ifdef VERSION_US
extern s32 D_82E0710C, D_82E07110, D_82E07114, D_82E07118, D_82E0711C, D_82E07120, D_82E07124;
s32 func_82E017E0(s32 kind, u8* event) {
    switch (kind) {
    case 0:
        switch (*(u32*)(event + 0x20)) {
        case 0:
            D_82E0710C = *(s16*)(event + 8);
            D_82E07118 = event[0x28];
            break;
        case 1:
            D_82E07110 = *(s16*)(event + 8);
            D_82E0711C = event[0x28];
            break;
        case 2:
            D_82E07114 = *(s16*)(event + 8);
            break;
        case 3:
            D_82E07120 = event[0x28];
            break;
        case 4:
            D_82E07124 = event[0x28];
            break;
        }
        break;
    case 1:
        break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 D_82E05650;
s32 func_82E01898(s32 kind, u8* event) {
    s32 numerator = 5;
    s32 denominator = 6;
    switch (kind) {
    case 0:
        D_82E06138.value = event[0x29] + (event[0x28] << 8);
        D_82E0713C = event[0x2B] + (event[0x2A] << 8);
        if (D_82E05650 == 0) {
            D_82E06138.value = ((event[0x29] + (event[0x28] << 8)) * numerator) / denominator;
            D_82E0713C = ((event[0x2B] * numerator) / denominator) + (event[0x2A] << 8);
        }
        *(u16*)(event + 2) &= 0xFFFE;
        break;
    case 1:
        break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 D_82E07128;
extern s32 D_82E0615C;
s32 func_82E019B0(s32 arg0, u8 *arg1) {
    switch (arg0) {
        case 0:
            D_82E07128 = arg1[0x28];
            D_82E0615C = arg1[0x2B] + (arg1[0x2A] << 8);
            *(u16 *)(arg1 + 2) &= 0xFFFE;
            break;
        case 1:
            break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E01A00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E01CE8.s")
#endif

#ifdef VERSION_US
extern u8 *D_82E075E8;
extern u8 *D_82E075EC;
extern u8 *D_82E075F0;
extern s32 D_82E07614;
extern s32 D_82E07618;
s32 func_82E02378(s32 arg0, u8 *arg1) {
    switch (arg0) {
    case 0:
        switch (*(u32 *)(arg1 + 0x20)) {
        case 0:
            break;
        case 1:
            D_82E075E8 = arg1;
            *(u16 *)(arg1 + 2) &= ~1;
            break;
        case 2:
            D_82E075EC = arg1;
            *(u16 *)(arg1 + 2) &= ~1;
            break;
        case 3:
            D_82E075F0 = arg1;
            *(u16 *)(arg1 + 2) &= ~1;
            break;
        }
        break;
    case 1:
        if (arg1[0] == 3) {
            switch (*(u32 *)(arg1 + 0x20)) {
            case 0:
                *(s32 *)(arg1 + 0x2C) = D_82E07614 | 0xFFFFFF00;
                break;
            case 1:
            case 2:
            case 3:
                *(s32 *)(arg1 + 0x2C) = D_82E07618 | 0xFFFFFF00;
                break;
            }
        }
        break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s16 D_82E06158;
extern s32 D_82E05650;
s32 func_82E0248C(s32 arg0, u8 *arg1) {
    s32 mode;
    switch (arg0) {
    case 0:
        mode = 6;
        D_82E06158 = arg1[0x29] + (arg1[0x28] << 8);
        if (D_82E05650 == 0) {
            D_82E06158 = ((arg1[0x29] + (arg1[0x28] << 8)) * 5) / mode;
        }
        *(u16 *)(arg1 + 2) &= ~1;
        break;
    case 1:
        break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 func_80001FF0(void);
extern s32 main_pool_get_available(void);
extern void* MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(void*);
extern s32 process_geo_layout(void*, void*);
extern void* func_800071A4(s32, s32, s32, s32, s32);
extern void ModelRenderer_InitDisplayRoots(void);
extern void func_8003F018(void*);
extern s32 main_pool_push_state(s32);
extern void func_82E04040(s32);
extern void func_80021ED8(s32);
extern u8 D_82E04EB0[], D_82E04F1C[], D_82E04F50[];
extern u8 D_82E05660[], D_82E057C8[];
extern s32 D_82E05650, D_82E05654, D_82E05658, D_82E0565C;
extern s32 D_82E0543C;
extern void* D_82E07600;
extern void* D_82E07604;
extern void* D_82E07608;
void func_82E02508(void) {
    void* pool;
    if (func_80001FF0() == 60) {
        D_82E05650 = 1;
    } else {
        D_82E05650 = 0;
    }
    pool = MainPool_AllocState(main_pool_get_available(), 0);
    D_82E05654 = process_geo_layout(pool, D_82E04EB0);
    D_82E05658 = process_geo_layout(pool, D_82E04F1C);
    D_82E0565C = process_geo_layout(pool, D_82E04F50);
    MainPool_FinalizeAllocation(pool);
    D_82E07600 = func_800071A4(0, 2, 320, 240, 0);
    D_82E07604 = func_800071A4(0, 2, 320, 240, 0);
    D_82E07608 = func_800071A4(0, 2, 320, 240, 0);
    ModelRenderer_InitDisplayRoots();
    func_8003F018(D_82E05660);
    func_8003F018(D_82E057C8);
    main_pool_push_state(0x64617461);
    func_82E04040(D_82E0543C++);
    func_80021ED8(0x52);
}
#endif

#ifdef VERSION_US
extern void BgStage_DrawFrame(void);
extern void GfxImage_FillCurrent(Gfx **, s32);
extern void GfxImage_FillRectangle(Gfx **, s32, s32, s32, s32, s32);
extern void GfxImage_SetRenderTarget(Gfx **, void *);
extern void func_82E02CA4(s32);
extern s32 func_8004D690(s32);
extern s32 main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void GeoRender_AdvanceFrameCounter(void);
extern void Geo_RenderRootNode(s32);
extern void func_800503A4(void *);
extern void func_80008648(void);
extern void func_82E02EB0(s32, s32, s32);
extern void func_82E02F00(s32, s32, u8);
extern Gfx *D_800D0510;
extern s32 D_82E0543C;
extern s32 D_82E05654;
extern u8 D_82E06163;
extern s32 D_82E06164;
extern s32 D_82E07130;
extern s32 D_82E075F4;
extern u8 *D_82E0760C;
extern void *D_82E07600;
extern void *D_82E07604;
extern void *D_82E07608;
void func_82E02658(void) {
    BgStage_DrawFrame();
    if (D_82E0543C != 8) {
        GfxImage_FillCurrent(&D_800D0510, 1);
    } else {
        GfxImage_FillRectangle(&D_800D0510, 0x28, 0, 0x230, 0x1E0, 1);
    }
    if (D_82E07130 == 0) {
        GfxImage_SetRenderTarget(&D_800D0510, D_82E07600);
        func_82E02CA4(D_82E075F4);
    }
    if (D_82E0543C == 8) {
        if (D_82E07130 == 1) {
            main_pool_push_state(0x6A706567);
            D_82E075F4 = func_8004D690(0x21);
            GfxImage_SetRenderTarget(&D_800D0510, D_82E07604);
            func_82E02CA4(D_82E075F4);
            main_pool_pop_state(0x6A706567);
        } else if (D_82E07130 == 2) {
            main_pool_push_state(0x6A706567);
            D_82E075F4 = func_8004D690(0x1F);
            GfxImage_SetRenderTarget(&D_800D0510, D_82E07608);
            func_82E02CA4(D_82E075F4);
            main_pool_pop_state(0x6A706567);
        }
        BgStage_DrawFrame();
        func_82E02EB0(0xA0, 0x78, (*(s32 **)((u8 *)&D_82E07600 + (D_82E06164 * 4)))[2]);
        func_82E02F00(0xA0, 0x78, D_82E06163);
    }
    GeoRender_AdvanceFrameCounter();
    Geo_RenderRootNode(D_82E05654);
    func_800503A4(D_82E0760C);
    func_80008648();
}
#endif

#ifdef VERSION_US
extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromTransparent(s32);
extern void func_82E030B0(void);
extern void func_800225C4(s32);
extern s32 D_82E05440;

s32 func_82E02828(s32 arg0) {
    s32 state = arg0;
    switch (arg0) {
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            state = 1;
        }
        break;
    case 1:
        func_82E030B0();
        if (D_82E05440 != 0) {
            state = 2;
            StageFade_StartFromTransparent(5);
            func_800225C4(0xA);
        }
        break;
    case 2:
        if (StageContext_GetFadeMode() == 1) {
            state = 3;
        }
        break;
    }
    return state;
}
#endif

#ifdef VERSION_US
extern void StageFade_StartFromOpaque(s32);
extern void func_800086A4(s32);
extern void func_80064D28();
extern void func_82E02658();
s32 func_82E02828(s32);
void func_82E028D0(void) {
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        func_80064D28();
        var_s0 = func_82E02828(var_s0);
        func_82E02658();
    } while (var_s0 != 3);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0292C.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_82E05450[];
void Font_EndTexturedTextRendering_fragment66(void) { Gfx *temp_v1 = D_800D0510++; temp_v1->words.w0 = 0xDE000000; temp_v1->words.w1 = (u32)D_82E05450; }
#endif

void func_82E02A9C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02AA4.s")
#endif

#ifdef VERSION_US
extern void Font_EndTexturedTextRendering_fragment66();
extern void func_82E02AA4(s32);

void func_82E02CA4(s32 arg0) {
    Font_EndTexturedTextRendering_fragment66();
    func_82E02AA4(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02CCC.s")
#endif

#ifdef VERSION_US
extern void Font_EndTexturedTextRendering_fragment66(void);
extern void func_82E02CCC(s32, s32, s32);
void func_82E02EB0(s32 arg0, s32 arg1, s32 arg2) {
    Font_EndTexturedTextRendering_fragment66();
    func_82E02CCC(arg0, arg1, arg2);
}
void func_82E02EB0_padding(void) {}
void func_82E02EB0_padding2(void) {}
void func_82E02EB0_padding3(void) {}
#endif

#ifdef VERSION_US
extern Gfx D_82E05500[];
void func_82E02F00(s32 x, s32 y, u8 opacity) {
    gSPDisplayList(D_800D0510++, D_82E05500);
    gDPSetEnvColor(D_800D0510++, 0, 0, 0, 255 - opacity);
    gSPScisTextureRectangle(D_800D0510++, x << 2, y << 2,
                           (x + 320) << 2, (y + 240) << 2,
                           G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E030B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0393C.s")
#endif

#ifdef VERSION_US
extern void func_8003F1DC(void*);
extern s32 func_8004DC6C(s32);
extern void func_8004DCFC(u8*, s32*);
extern s32 func_8004EB58(s32, s32);
extern void func_82E0424C(s32);
extern void func_82E04734(void);
void func_82E04040(s32 scene) {
    void* allocation;
    u8* resource;
    /* Valid scene indices are 0..10, as in the original switch. */
    main_pool_pop_state(0x64617461);
    main_pool_push_state(0x64617461);
    func_8003F1DC(D_82E05660);
    func_8003F1DC(D_82E057C8);
    switch (scene) {
    case 0:
        D_82E075F4 = func_8004D690(0x22);
        resource = (u8*)(u32)func_8004DC6C(0xE4);
        break;
    case 1:
        D_82E075F4 = func_8004D690(0x23);
        resource = (u8*)(u32)func_8004DC6C(0xE8);
        break;
    case 2:
        D_82E075F4 = func_8004D690(0x24);
        resource = (u8*)(u32)func_8004DC6C(0xCD);
        break;
    case 3:
        D_82E075F4 = func_8004D690(0x25);
        resource = (u8*)(u32)func_8004DC6C(0xD0);
        break;
    case 4:
        D_82E075F4 = func_8004D690(0x26);
        resource = (u8*)(u32)func_8004DC6C(0xCF);
        break;
    case 5:
        D_82E075F4 = func_8004D690(0x27);
        resource = (u8*)(u32)func_8004DC6C(0xE9);
        break;
    case 6:
        D_82E075F4 = func_8004D690(0x28);
        resource = (u8*)(u32)func_8004DC6C(0x90);
        break;
    case 7:
        D_82E075F4 = func_8004D690(0x29);
        resource = (u8*)(u32)func_8004DC6C(0x97);
        break;
    case 8:
        D_82E075F4 = func_8004D690(0x2A);
        resource = (u8*)(u32)func_8004DC6C(0xCC);
        break;
    case 9:
        D_82E075F4 = func_8004D690(0x2B);
        resource = (u8*)(u32)func_8004DC6C(0x9E);
        break;
    case 10:
        resource = (u8*)(u32)func_8004DC6C(0x8F);
        break;
    }
    func_8004DCFC(resource, 0);
    allocation = MainPool_AllocState(main_pool_get_available(), 0);
    D_82E0760C = (u8*)(u32)func_8004EB58((s32)(u32)allocation, (s32)(u32)resource);
    MainPool_FinalizeAllocation(allocation);
    func_82E0424C(scene);
    func_82E04734();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0424C.s")
#endif

#ifdef VERSION_US
typedef struct F66Record {
    s32 state;
    s32 x;
    s32 adjusted;
    s32 old;
    s32 source;
} F66Record;
extern F66Record D_82E05968[100];
extern s32 D_82E05948, D_82E0594C;
void func_82E04734(void) {
    s32 i;
    for (i = 0; i < 100; i++) {
        D_82E05968[i].state = 0;
        D_82E05968[i].x = D_82E05948;
        D_82E05968[i].adjusted = D_82E05968[i].source - D_82E0594C;
        D_82E05968[i].old = D_82E05968[i].source;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E047C4.s")
#endif

#ifdef VERSION_US
extern void func_8003CD84();
extern void func_82E047C4(s32);
extern void *D_82E07600;
s32 func_82E04AE4(s32 arg0, s32 arg1) {
    if ((arg0 != 0) && (arg0 == 5)) {
        func_82E047C4((*(s32 *)((u8 *)(D_82E07600) + (8))));
        func_8003CD84();
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E04B28.s")
#endif

#ifdef VERSION_US
extern void func_82E04B28(s32);
s32 func_82E04E60(s32 arg0, s32 arg1) {
    if ((arg0 != 0) && (arg0 == 5)) {
        func_82E04B28((*(s32 *)((u8 *)(D_82E07600) + (8))));
        func_8003CD84();
    }
    return 0;
}
#endif
