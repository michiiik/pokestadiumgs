#include "global.h"


#ifdef VERSION_US
typedef struct F67DisplayRecord {
    /* 0x00 */ s16 x, y;
    /* 0x04 */ s16 unused04, flags;
    /* 0x08 */ u8 unused08[4];
    /* 0x0C */ s16 selection;
    /* 0x0E */ u8 unused0E[4];
    /* 0x12 */ u8 foreground[3];
    /* 0x15 */ u8 background[3];
} F67DisplayRecord;
extern F67DisplayRecord D_8291BE80, D_8291BE98;

typedef struct F67UiRow {
    /* 0x00 */ s16 width, height;
    /* 0x04 */ u8 unused04[0x10];
    /* 0x14 */ s16 secondaryWidth, secondaryHeight;
    /* 0x18 */ u8 unused18[0x14];
    /* 0x2C */ s32 archive, entry, alternateArchive, alternateEntry;
    /* 0x3C */ u8* foreground;
    /* 0x40 */ u8* background;
} F67UiRow;
extern F67UiRow D_829172D8[];

typedef struct unk_func_8290FDB0 {
    u8 unk_00;
    u8 unk_01[3];
    s32 unk_04;
} unk_func_8290FDB0;

extern s32 func_80055948(s32 arg0);
extern void func_80054210(unk_func_8290FDB0* arg0);
extern void func_80054248(unk_func_8290FDB0* arg0);
extern void func_80051D64(s32 arg0, s32 arg1);
extern s32 func_80055028(void);

void func_8290FDB0(s16 arg0) {
    unk_func_8290FDB0 var_sp18;

    func_80055948(3);
    func_80054210(&var_sp18);
    var_sp18.unk_00 = arg0 + 1;
    func_80054248(&var_sp18);
    func_80051D64(20, 0);
    func_80055028();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_8290FE04.s")

typedef struct F67ColorRow {
    u8* color;
    u8 unused[0x40];
} F67ColorRow;
extern F67ColorRow D_82917318[], D_82917314[];
extern s16 D_8291BE8C;
extern u8 D_829172D0[3], D_829172D4[3];
extern s32 Math_StepToS32(s32, s32, s32, s32);

void func_8290FF14(F67DisplayRecord* state) {
    switch (state->flags) {
        case 1:
            state->background[0] = Math_StepToS32(state->background[0], D_82917318[D_8291BE8C].color[0], 50, 50);
            state->background[1] = Math_StepToS32(state->background[1], D_82917318[D_8291BE8C].color[1], 50, 50);
            state->background[2] = Math_StepToS32(state->background[2], D_82917318[D_8291BE8C].color[2], 50, 50);
            state->foreground[0] = Math_StepToS32(state->foreground[0], D_82917314[D_8291BE8C].color[0], 50, 50);
            state->foreground[1] = Math_StepToS32(state->foreground[1], D_82917314[D_8291BE8C].color[1], 50, 50);
            state->foreground[2] = Math_StepToS32(state->foreground[2], D_82917314[D_8291BE8C].color[2], 50, 50);
            if (state->background[0] == D_829172D8[D_8291BE8C].background[0] &&
                state->background[1] == D_829172D8[D_8291BE8C].background[1] &&
                state->background[2] == D_829172D8[D_8291BE8C].background[2] &&
                state->foreground[0] == D_829172D8[D_8291BE8C].foreground[0] &&
                state->foreground[1] == D_829172D8[D_8291BE8C].foreground[1] &&
                state->foreground[2] == D_829172D8[D_8291BE8C].foreground[2]) {
                state->flags = 0;
            }
            break;
        case 2:
            state->background[0] = Math_StepToS32(state->background[0], D_829172D0[0], 50, 50);
            state->background[1] = Math_StepToS32(state->background[1], D_829172D0[1], 50, 50);
            state->background[2] = Math_StepToS32(state->background[2], D_829172D0[2], 50, 50);
            state->foreground[0] = Math_StepToS32(state->foreground[0], D_829172D4[0], 50, 50);
            state->foreground[1] = Math_StepToS32(state->foreground[1], D_829172D4[1], 50, 50);
            state->foreground[2] = Math_StepToS32(state->foreground[2], D_829172D4[2], 50, 50);
            if (D_829172D0[0] == state->background[0] &&
                D_829172D0[1] == state->background[1] &&
                D_829172D0[2] == state->background[2] &&
                D_829172D4[0] == state->foreground[0] &&
                D_829172D4[1] == state->foreground[1] &&
                D_829172D4[2] == state->foreground[2]) {
                state->flags = 1;
            }
            break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910258.s")

extern Gfx D_80094E78[];
extern Gfx* D_800D0510;
extern s32 func_8004C990(s32, s32);
extern s32 func_8004D1FC(u8*);
extern void func_80044270(s16, s16, s16, s16, s16, s16, s16, s16, s32);
void func_82910510(F67DisplayRecord* state, s16 x, s16 y, s32 width, s32 height) {
    struct {
        u16* texture;
        f32 scale;
        f32 derivative;
        f32 bias;
        s32 interiorWidth;
        s32 heightWork;
        s32 drawX;
        s32 drawY;
    } work;
    work.texture = (u16*)(u32)func_8004C990(0x52, 1);
    if (work.texture != NULL) {
        work.interiorWidth = width - 10;
        work.heightWork = height - 10;
        work.scale = (f32)work.interiorWidth / (f32)(u32)work.texture[0];
        if ((work.scale > 0.0f) && (work.interiorWidth > 0) && (work.heightWork > 0)) {
            gSPDisplayList(D_800D0510++, D_80094E78);
            gDPSetRenderMode(D_800D0510++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
            func_8004D1FC((u8*)work.texture);
            gDPPipeSync(D_800D0510++);
            work.heightWork = 10;
            work.derivative = 1024.0f / work.scale;
            gDPSetColor(D_800D0510++, G_SETPRIMCOLOR, (_SHIFTL(state->foreground[1], 16, 8) | _SHIFTL(state->foreground[2], 8, 8) | _SHIFTL(state->foreground[0], 24, 8) | _SHIFTL(255, 0, 8)));
            gDPSetColor(D_800D0510++, G_SETENVCOLOR, (_SHIFTL(state->background[1], 16, 8) | _SHIFTL(state->background[2], 8, 8) | _SHIFTL(state->background[0], 24, 8) | _SHIFTL(255, 0, 8)));
            if (work.derivative > 0.0f) {
                work.bias = 0.5f;
            } else {
                work.bias = -0.5f;
            }
            work.drawX = x + 5;
            work.drawY = y + 5;
            func_80044270((s16)work.drawX, (s16)work.drawY, (s16)(width - work.heightWork), (s16)(height - work.heightWork), 0, 0, (s32)(work.bias + work.derivative), 1024, 0);
        }
    }
}

void func_82910740(F67DisplayRecord* state, s32 x, s32 y, s32 width, s32 height) {
    s16 originX, originY;
    s32 stripWidth;
    s32 textureHeight;
    u16* texture;
    texture = (u16*)(u32)func_8004C990(0x51, 1);
    stripWidth = (s32)texture[0] / 4;
    textureHeight = texture[1];
    if (texture != NULL) {
        gSPDisplayList(D_800D0510++, D_80094E78);
        gDPSetRenderMode(D_800D0510++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        func_8004D1FC((u8*)texture);
        gDPPipeSync(D_800D0510++);
        gDPSetColor(D_800D0510++, G_SETPRIMCOLOR, (_SHIFTL(state->foreground[1], 16, 8) | _SHIFTL(state->foreground[2], 8, 8) | _SHIFTL(state->foreground[0], 24, 8) | _SHIFTL(255, 0, 8)));
        gDPSetColor(D_800D0510++, G_SETENVCOLOR, (_SHIFTL(state->background[1], 16, 8) | _SHIFTL(state->background[2], 8, 8) | _SHIFTL(state->background[0], 24, 8) | _SHIFTL(255, 0, 8)));
        originX = (s16)x;
        originY = (s16)y;
        func_80044270((s16)originX, (s16)originY, (s16)stripWidth, (s16)textureHeight, 0, 0, 1024, 1024, 0);
        func_80044270((s16)(originX + stripWidth), (s16)originY, (s16)(width - stripWidth * 2), (s16)textureHeight, (s16)(stripWidth << 5), 0, 0, 1024, 0);
        func_80044270((s16)(originX + width - stripWidth), (s16)originY, (s16)stripWidth, (s16)textureHeight, (s16)(stripWidth << 5), 0, 1024, 1024, 0);
        func_80044270((s16)originX, (s16)(originY + textureHeight), (s16)stripWidth, (s16)(height - textureHeight * 2), (s16)((stripWidth * 2) << 5), 0, 1024, 0, 0);
        func_80044270((s16)originX, (s16)(originY + height - textureHeight), (s16)stripWidth, (s16)textureHeight, (s16)((stripWidth * 2) << 5), 0, 1024, 1024, 0);
        func_80044270((s16)(originX + stripWidth), (s16)(originY + height - textureHeight), (s16)(width - stripWidth * 2), (s16)textureHeight, (s16)((stripWidth * 3) << 5), 0, 0, 1024, 0);
        func_80044270((s16)(originX + width - stripWidth), (s16)(originY + height - textureHeight), (s16)stripWidth, (s16)textureHeight, (s16)((stripWidth * 3) << 5), 0, 1024, 1024, 0);
        func_80044270((s16)(originX + width - stripWidth), (s16)(originY + textureHeight), (s16)stripWidth, (s16)(height - textureHeight * 2), (s16)((stripWidth * 3) << 5), 0, 1024, 0, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910B30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34C8B0/func_82910FC8.s")

typedef struct F67TextRow {
    s32 id;
    u8 padding[0x40];
} F67TextRow;
extern F67TextRow D_829172F8[], D_829172FC[], D_82917300[];
extern u8 D_8291BEB0[];
const char D_829177C0[] = "%s";
const char D_829177C4[] = "%s";
const char D_829177C8[] = "%s";
extern s32 func_800476FC(s32, s32);
extern s32 func_80047738(s32, s32, s32, s32);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void* func_8004C874(s32, s32);
extern void func_800495F8(s32, s32, s32, const char*, ...);
extern void func_800499EC(void);

void func_82911418(void) {
    func_800476FC((s32)D_8291BEB0, 4);
    func_80047738(0, func_8004C990(0x38, 5), 0, 0);
    func_80047738(1, func_8004C990(0x38, 1), 0, 0);
    func_80047738(2, func_8004C990(0x38, 7), 0, 0);
    func_80047738(3, func_8004C990(0x33, 5), 0, 0);
    func_800498C4();
    func_800496A4(8, 0);
    func_8004972C(255, 255, 255, 255);
    func_800495F8(D_8291BE98.x + 0xCE, D_8291BE98.y + 0xC, 1, D_829177C0, func_8004C874(0x1C, D_829172F8[D_8291BE80.selection].id));
    func_800495F8(D_8291BE80.x + 0x116, D_8291BE80.y + 0x26, 1, D_829177C4, func_8004C874(0x1C, D_829172FC[D_8291BE80.selection].id));
    func_800495F8(D_8291BE80.x + 0x114, D_8291BE80.y + 0x4E, 1, D_829177C8, func_8004C874(0x1C, D_82917300[D_8291BE80.selection].id));
    func_800499EC();
}

extern s16 D_8291BE7A;
extern Gfx D_80094E38[];
extern s32 D_8291BE74;
extern void func_800468A0(s32);
extern s32 func_8004D19C(s32, s32, s32, s32, s32);
extern void func_82910B30(void);
extern void func_82910FC8(void);
void func_829115E0(void) {
    func_800468A0(D_8291BE74);
    gSPDisplayList(D_800D0510++, D_80094E38);
    func_8004D19C(0x191, 0x111, func_8004C990(0x12F, 0), 0, 0);
    if (D_8291BE7A != 0) {
        gSPDisplayList(D_800D0510++, D_80094E38);
        func_8004D19C(0x13D, 0xEF, func_8004C990(D_829172D8[D_8291BE80.selection].alternateArchive, D_829172D8[D_8291BE80.selection].alternateEntry), 0, 0);
    } else if (D_8291BE80.selection == 1) {
        gSPDisplayList(D_800D0510++, D_80094E38);
        func_8004D19C(0x13D, 0xEF, func_8004C990(D_829172D8[D_8291BE80.selection].archive, D_829172D8[D_8291BE80.selection].entry), 0, 0);
    }
    func_82910510(&D_8291BE98, D_8291BE98.x, D_8291BE98.y, D_829172D8[D_8291BE80.selection].secondaryWidth, D_829172D8[D_8291BE80.selection].secondaryHeight);
    func_82910740(&D_8291BE98, D_8291BE98.x, D_8291BE98.y, D_829172D8[D_8291BE80.selection].secondaryWidth, D_829172D8[D_8291BE80.selection].secondaryHeight);
    func_82910510(&D_8291BE80, D_8291BE80.x, D_8291BE80.y, D_829172D8[D_8291BE80.selection].width, D_829172D8[D_8291BE80.selection].height);
    func_82910740(&D_8291BE80, D_8291BE80.x, D_8291BE80.y, D_829172D8[D_8291BE80.selection].width, D_829172D8[D_8291BE80.selection].height);
    func_82910B30();
    func_82910FC8();
    func_82911418();
}

extern void func_800088DC(void);
extern void func_80008648(void);
void func_82911850(void) {
    func_800088DC();
    func_829115E0();
    func_80008648();
}

extern void StageFade_StartFromOpaque(s32);
extern s32 D_8291BE70;
void func_82911880(void) {
    s32 var_s0;

    StageFade_StartFromOpaque(0xC);
    var_s0 = 0;
    do {
        func_82911850();
        var_s0 += 1;
    } while (var_s0 != 0xC);
    D_8291BE70 = 1;
}

extern void func_80064D28();
extern void func_82910258();
void func_829118D4(void) {
    if (D_8291BE70 != 0) {
        do {
            func_80064D28();
            func_82910258();
            func_82911850();
        } while (D_8291BE70 != 0);
    }
}

extern void StageFade_StartFromTransparent(s32);
void func_8291192C(void) {
    s32 var_s0;

    StageFade_StartFromTransparent(0x10);
    var_s0 = 0;
    do {
        func_82911850();
        var_s0 += 1;
    } while (var_s0 != 0x10);
}

extern void func_8290FE04(s16);

void func_82911974(s16 arg0) {
    func_8290FE04(arg0);
}

extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern u8* func_80047588(s32, s32);
extern s32 func_8004C09C(s32);
extern s32 func_8004D690(s32);
extern s32 func_8004C8C0(u16);
extern s32 func_8004C4B0(s32);
extern u8* Asset_LoadToSegment(s32, u8*, u8*, s32);
extern void func_80008514(s32);
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_8004C398(void);
extern s32 D_8291BE74;
extern u8 D_1000000[], D_446E30[], D_447D00[];

s32 func_8291199C(s32 arg0, s32 selection) {
    s32 configuration;

    main_pool_push_state(0x474244);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    configuration = func_800082E0(1, 0, 2, 0, 2, 1);
    func_80047588(12, 0);
    func_8004C09C(7);
    D_8291BE74 = func_8004D690(2);
    func_8004C8C0(0x52);
    func_8004C8C0(0x51);
    func_8004C8C0(0x12A);
    func_8004C8C0(0x12B);
    func_8004C8C0(0x38);
    func_8004C8C0(0x33);
    func_8004C8C0(0x126);
    func_8004C8C0(0x128);
    func_8004C8C0(0x127);
    func_8004C8C0(0x12F);
    func_8004C4B0(0x1C);
    Asset_LoadToSegment((((u32)D_1000000 & 0x0F000000) >> 24), D_446E30, D_447D00, 0);
    func_82911974((s16)selection);
    func_80008514(configuration);
    func_82911880();
    func_829118D4();
    func_8291192C();
    func_80008574();
    func_80047610();
    Gfx_FreeDisplayListBuffers();
    func_8004C398();
    main_pool_pop_state(0x474244);
    return 0;
}
#endif
