#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/74/fragment74_code/func_8F600020.s")

extern s16 D_8F600BFE;
void func_8F60009C(s16 *arg0, s32 arg1, s32 arg2) {
    arg0[0] = arg1;
    arg0[1] = arg2;
    if (D_8F600BFE == 0) {
        arg0[0] = arg0[0] / 2;
        arg0[1] = arg0[1] / 2;
    }
}

extern u8* func_8004CA60(u8*);
extern void func_800459AC(u8*, u8, u8, u16, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80044270(s16, s16, s16, s16, s16, s16, s16, s16, s32);
void func_8F6000EC(s32 x, s32 y, u8* image) {
    u8* pixels;
    s32 offset;
    s32 currentY;
    s32 currentX;

    if (image != NULL) {
        /* This setup grouping preserves IDO's matched prologue schedule. */
        currentX = (s16)x; pixels = func_8004CA60(image); for (offset = 0, currentY = y; offset < 128; offset += 64) {
            func_800459AC(pixels, image[4], image[5], *(u16*)image, 32, 1, 0, 2, 2, 0, 0, 0, 0);
            func_80044270((s16)currentX, (s16)currentY, (s16)(*(u16*)image * 2), 64, 0, 0, 512, 512, 0);
            pixels += 0x1000;
            currentY += 64;
        }
    }
}

extern Gfx D_80094E38[];
extern u8 D_8F600C08[];
extern s32 func_8004D19C(s32, s32, s32, s32, s32);
extern u8 D_800D0510[];
void func_8F6001FC(void) {
    Gfx* packet;
    s16 coordinates[2];

    packet = (*((Gfx**)&D_800D0510))++;
    gSPDisplayList(packet, D_80094E38);
    if (D_8F600BFE == 1) {
        func_8F6000EC(172, 240, D_8F600C08);
    }
    func_8F60009C(coordinates, 340, 240);
    func_8004D19C(coordinates[0], coordinates[1], (s32)D_8F600C08, 0, 0);
}

extern void func_800498C4(void);
extern void func_800496A4(s32,s32);
extern void Font_EnableTwoCycleTexturing(void);
extern void Font_DisableTwoCycleTexturing(void);
extern void func_8004972C(s32,s32,s32,s32);
extern void func_800497E4(s32,s32,s32,s32);
extern void* func_8004C874(s32,s32);
extern void func_800495F8(s32,s32,s32,const char*,...);
extern void func_800499EC(void);
extern s16 D_8F600BC0[];
extern s16 D_8F600BC8[];
extern s16 D_8F600BF4;
extern s16 D_8F600BF6;
extern s16 D_8F600BFA;
extern s16 D_8F600BFC;
extern s16 D_8F600C04;
extern s16 D_8F600C06;
extern char D_8F600BD0[];
extern char D_8F600BDC[];
void func_8F60028C(void) {
    s32 i;
    s32 y;
    s16* label;
    s16 coordinates[2];
    s16* mode;
    s32 font;

    func_800498C4();
    mode = &D_8F600BFE;
    font = *mode == 1 ? 16 : 2;
    func_800496A4(font, 0);
    Font_EnableTwoCycleTexturing();
    func_8004972C(255, 255, 255, 255);
    func_800497E4(0, 0, 255, 255);
    func_8F60009C(coordinates, 320, 40);
    func_800495F8(coordinates[0], coordinates[1], 1, func_8004C874(0x42, 10));
    Font_DisableTwoCycleTexturing();
    font = *mode == 1 ? 8 : 1;
    func_800496A4(font, 0);
    for (i = 0, y = 70, label = D_8F600BC0; i < 3; i++, y += 22, label++) {
        if (i != D_8F600BF6) {
            func_8004972C(255, 255, 255, 255);
        } else {
            func_8004972C(255, 255, 0, 255);
        }
        func_8F60009C(coordinates, 320, y);
        func_800495F8(coordinates[0], coordinates[1], 2, func_8004C874(0x42, *label));
        switch (i) {
        case 0:
            func_800495F8(coordinates[0], coordinates[1], 0, func_8004C874(0x42, D_8F600BC8[D_8F600BF4]));
            break;
        case 1:
            func_800495F8(coordinates[0], coordinates[1], 0, D_8F600BD0, D_8F600BFA, D_8F600C04 - 1);
            break;
        case 2:
            func_800495F8(coordinates[0], coordinates[1], 0, D_8F600BDC, D_8F600BFC, D_8F600C06 - 1);
            break;
        }
    }
    func_800499EC();
}

extern void BgStage_DrawFrame(void);
extern void GfxImage_FillCurrent(void *, s32);
extern void func_80008648(void);
void func_8F6004D4(void) {
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&D_800D0510, 0x5295);
    func_8F6001FC();
    func_8F60028C();
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/74/fragment74_code/func_8F60051C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/74/fragment74_code/func_8F600610.s")

extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromTransparent(s32);
extern s32 func_8F600610(void);
s32 func_8F600948(s32 arg0) {
    s32 sp1C;
    s32 temp_v0;

    sp1C = arg0;
    switch (arg0) {
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            sp1C = 1;
        }
        break;
    case 1:
        temp_v0 = func_8F600610();
        if (temp_v0 != 0) {
            if (temp_v0 == 1) {
                sp1C = 2;
            } else {
                sp1C = 3;
            }
            StageFade_StartFromTransparent(5);
        }
        break;
    case 2:
        if (StageContext_GetFadeMode() == 1) {
            sp1C = 4;
        }
        break;
    }
    return sp1C;
}

extern s32 StageContext_Allocate(s8, s8, s8, s8, s8, s32);
extern void func_80008514(s32);
extern void func_80008574(void);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_8F60051C(void);
extern s8 D_8F600BFF;
extern void main_pool_pop_state(s32);
extern s32 main_pool_push_state(s32);
void func_8F6009F0(void) {
    s32 state = 0;
    s32 repeat;
    s32 running;
    s8* mode;

    mode = &D_8F600BFF;
    do {
        main_pool_push_state(0x64697370);
        func_80008514(StageContext_Allocate(*mode, 0, 2, 0, 2, 1));
        func_800086A4(2);
        StageFade_StartFromOpaque(5);
        do {
            func_80064D28();
            func_8F60051C();
            func_8F6004D4();
            state = func_8F600948(state);

            switch (state) {
            case 3: running = 0; repeat = 1; state = 0; break;
            case 4: running = 0; repeat = 0; break;
            default: running = 1; repeat = 1; break;
            }
        } while (running);
        func_80008574();
        main_pool_pop_state(0x64697370);
    } while (repeat);
}

extern void Gfx_InitDisplayListBuffers(s32, s32);
extern s32 func_8004C09C(s32);
extern void func_8004C4B0(s32);
extern void func_80047588(s32, s32);
extern void Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern void func_8F600020(s32);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void Gfx_FreeDisplayListBuffers(void);
extern u8 D_1000000[];
extern u8 D_446E30[];
extern u8 D_447D00[];
s32 fragment74_main(s32 arg0, s32 arg1) {
    s32 sp1C;
    main_pool_push_state(0x54524E56);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp1C = func_8004C09C(0x43);
    func_8004C4B0(0x42);
    func_80047588(0x3F, 0);
    Asset_LoadToSegment((((u32)&D_1000000) & 0x0F000000) >> 24, &D_446E30, &D_447D00, 0);
    func_8F600020(sp1C);
    func_8F6009F0();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x54524E56);
    return 0;
}
#endif
