#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E00020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0048C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E00700.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E007F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E00868.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E00E5C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E017E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E01898.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E019B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E01A00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E01CE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02378.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0248C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02508.s")
#endif

#ifdef VERSION_US
extern void func_800088DC(void);
extern void GfxImage_FillCurrent(Gfx **, s32);
extern void func_80007444(Gfx **, s32, s32, s32, s32, s32);
extern void func_80007328(Gfx **, void *);
extern void func_82E02CA4(s32);
extern s32 func_8004D690(s32);
extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void GeoRender_AdvanceFrameCounter(void);
extern void func_8003C6B8(s32);
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
    func_800088DC();
    if (D_82E0543C != 8) {
        GfxImage_FillCurrent(&D_800D0510, 1);
    } else {
        func_80007444(&D_800D0510, 0x28, 0, 0x230, 0x1E0, 1);
    }
    if (D_82E07130 == 0) {
        func_80007328(&D_800D0510, D_82E07600);
        func_82E02CA4(D_82E075F4);
    }
    if (D_82E0543C == 8) {
        if (D_82E07130 == 1) {
            main_pool_push_state(0x6A706567);
            D_82E075F4 = func_8004D690(0x21);
            func_80007328(&D_800D0510, D_82E07604);
            func_82E02CA4(D_82E075F4);
            main_pool_pop_state(0x6A706567);
        } else if (D_82E07130 == 2) {
            main_pool_push_state(0x6A706567);
            D_82E075F4 = func_8004D690(0x1F);
            func_80007328(&D_800D0510, D_82E07608);
            func_82E02CA4(D_82E075F4);
            main_pool_pop_state(0x6A706567);
        }
        func_800088DC();
        func_82E02EB0(0xA0, 0x78, (*(s32 **)((u8 *)&D_82E07600 + (D_82E06164 * 4)))[2]);
        func_82E02F00(0xA0, 0x78, D_82E06163);
    }
    GeoRender_AdvanceFrameCounter();
    func_8003C6B8(D_82E05654);
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E02F00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E030B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0393C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E04040.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E0424C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/66/fragment66_code/func_82E04734.s")
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
