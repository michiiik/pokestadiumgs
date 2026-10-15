#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F500020.s")

extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void Font_EnableTwoCycleTexturing(void);
extern void Font_DisableTwoCycleTexturing(void);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800497E4(s32, s32, s32, s32);
extern void* func_8004C874(s32, s32);
extern void func_800495F8(s32, s32, s32, const char*, ...);
extern s32 func_8004C594(s32, s32);
extern void* func_8004C8A0(void*, s32, s32, s32);
extern void func_800495BC(s32, s32, const char*, ...);
extern void func_8004989C(s32);
extern void func_800499EC(void);
extern s16 D_8F500980[];
extern s16 D_8F5009A8;
extern s16 D_8F5009AA;
extern s16 D_8F5009AC;
void func_8F500130(void) {
    s16* selected;
    s32 y;
    s16* item;
    char buffer[64];
    s32 i;
    s32 footerEntry;

    func_800498C4();
    selected = &D_8F5009A8;
    func_800496A4(16, 0);
    Font_EnableTwoCycleTexturing();
    func_8004972C(0, 0, 255, 255);
    func_800497E4(255, 255, 255, 255);
    func_800495F8(320, 120, 1, func_8004C874(0x42, 9));
    Font_DisableTwoCycleTexturing();
    func_800496A4(8, 0);
    func_8004C594(3, D_8F5009AC);
    for (i = 0, item = D_8F500980, y = 190; i < 2; i++, item++) {
        if (i == *selected) {
            func_8004972C(255, 255, 0, 255);
        } else {
            func_8004972C(255, 255, 255, 255);
        }
        func_800495BC(160, y, func_8004C8A0(buffer, 64, 0x42, *item));
        y += 24;
    }
    func_800496A4(8, 0);
    func_8004972C(255, 255, 255, 255);
    selected = &D_8F5009AA;
    func_8004C594(3, *selected);
    func_8004989C(22);
    footerEntry = *selected != 0 ? 0x2A : 0x2B;
    func_800495F8(320, 280, 3, func_8004C8A0(buffer, 64, 0x42, footerEntry));
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F5002F4.s")

extern u8* D_8F5009B8;
extern void* D_8F5009B4;
extern s16 D_8F5009B0;
extern s32 D_8F5009BC;
extern s32 ModelAnim_IsFinished(void*);
extern void func_8003F2C4(void*, void*, s32);
extern s32 func_80043678(void*);
extern void BgStage_DrawFrame(void);
extern void func_800468A0(s32);
extern void func_8F5002F4(void);
extern Gfx* D_800D0510;
extern Gfx D_80094E38[];
extern void Ui_DrawAnimatedTextureMarker(s16, s16);
extern void func_80008648(void);
extern s32 D_8F5009A0;
void func_8F500414(void) {
    s16* animation;
    u8* node = *(u8**)(D_8F5009B8 + 0x1C);

    animation = &D_8F5009B0;
    if (ModelAnim_IsFinished(node)) {
        if (*animation == 0) {
            if (D_8F5009AA != 0) {
                *animation = 7;
            }
        } else {
            if (D_8F5009AA == 0) {
                *animation = 0;
            }
        }
        func_8003F2C4(D_8F5009B4, node, -1);
        func_8003F2C4(D_8F5009B4, node, *animation);
    }
    D_8F5009BC = func_80043678(D_8F5009B8);
    BgStage_DrawFrame();
    func_800468A0(D_8F5009A0);
    func_8F5002F4();
    func_8F500130();
    gSPDisplayList(D_800D0510++, D_80094E38);
    Ui_DrawAnimatedTextureMarker(120, D_8F5009A8 * 24 + 194);
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/73/fragment73_code/func_8F500544.s")

extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromTransparent(s32);
extern void func_80035424(s32);
extern s32 func_8F500544(void);
s32 func_8F500774(s32 incoming) {
    s32 state = incoming;
    switch (incoming) {
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            state = 1;
        }
        break;
    case 1:
        if (func_8F500544() != 0) {
            state = 2;
            StageFade_StartFromTransparent(5);
            func_80035424(10);
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

extern void StageFade_StartFromOpaque(s32);
extern void func_800086A4(s32);
extern void func_80064D28();
void func_8F500810(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        func_80064D28();
        func_8F500414();
        temp_v0 = func_8F500774(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 3);
}

extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern s32 func_8004C09C(s32);
extern s32 func_8004C8C0(u16);
extern s32 func_8004C4B0(s32);
extern s32 func_8004D690(s32);
extern u8* func_80047588(s32, s32);
extern u8* Asset_LoadToSegment(s32, u8*, u8*, s32);
extern u8 D_1000000[], D_446E30[], D_447D00[];
extern s32 D_8F5009A0;
extern void func_8F500020(void);
extern void func_80008514(s32);
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_8004C398(void);
s32 fragment73_main(s32 arg0, s32 arg1) {
    s32 configuration;
    main_pool_push_state(0x42474D50);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    configuration = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(7);
    func_8004C8C0(0x79);
    func_8004C4B0(0x42);
    D_8F5009A0 = func_8004D690(0x16);
    func_80047588(0x18, 0);
    Asset_LoadToSegment(((u32)D_1000000 & 0x0F000000) >> 24, D_446E30, D_447D00, 0);
    func_8F500020();
    func_80008514(configuration);
    func_8F500810();
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x42474D50);
    return 0;
}
#endif
