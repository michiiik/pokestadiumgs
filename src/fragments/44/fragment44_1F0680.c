#include "global.h"


#ifdef VERSION_US
struct Fragment44RowJob {
    s32 tag;
    void *owner;
    u16 *pixels;
    s16 width;
    s16 rows;
    s16 position;
    s16 step;
    s32 active;
};
extern struct Fragment44RowJob D_8AF2BDF8;

extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_8AF26450;
extern u8 D_8AF26454;
extern char D_8AF28940[];
extern u8 *func_8004D878(u8 *, s32, u8 *);
extern void GfxImage_SetRenderTarget(Gfx **, void *);
extern s32 Ui_DrawGradientQuad(s32, s32, s32, s32, void *, void *);
extern void func_8004D998(s32, s32, u8 *, s32, s32);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern s32 func_800472B8(s32);
extern s32 func_8004B7A4(s32);
extern void func_800495F8(s32, s32, s32, const char *, ...);
extern void func_800499EC(void);
void Fragment44_RenderScrollRecord(u8 *buffer, void *record, s16 code, s16 index, s16 x, s16 y) {
    Gfx *cursor;
    u8 *image;
    s32 font_height;
    *(s16 *)record = 1;
    *(s16 *)((u8 *)record + 2) = index;
    *(s16 *)((u8 *)record + 4) = x;
    *(s16 *)((u8 *)record + 6) = y;
    *(s16 *)((u8 *)record + 8) = (s16)code;
    image = *(u8 **)((u8 *)record + 0xC);
    func_8004D878(buffer, (s16)code, NULL);
    GfxImage_SetRenderTarget(&D_800D0510, image);
    Ui_DrawGradientQuad(0, 0, *(u16 *)(image + 4), *(u16 *)(image + 6), &D_8AF26450, &D_8AF26454);
    cursor = D_800D0510++;
    gSPDisplayList(cursor, D_80094E38);
    func_8004D998((s32)*(u16 *)(image + 4) / 2, 4, buffer, 1, 0);
    func_800498C4();
    func_800496A4(4, 0);
    func_8004972C(255, 255, 255, 200);
    font_height = func_800472B8(4);
    func_800495F8((s32)*(u16 *)(image + 4) / 2, *(u16 *)(image + 6) - font_height, 1, D_8AF28940, (char *)func_8004B7A4((s16)code));
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02584.s")

void Fragment44_CullScrollRecordsAbove(void *arg0) {
    s32 i;
    u8 *entry;
    s16 limit;
    s16 step;

    step = *(s16 *)((u8 *)arg0 + 0x52);
    entry = (u8 *)arg0 + 0x74;
    limit = *(s16 *)((u8 *)arg0 + 0x72) + *(s32 *)((u8 *)arg0 + 0xC) - step;
    for (i = 0; i < 36; i++) {
        if (*(s16 *)entry == 1 && *(s16 *)(entry + 6) < limit) {
            *(s16 *)entry = 0;
        }
        entry += 0x10;
    }
}

void Fragment44_CullScrollRecordsBelow(void *arg0) {
    s32 i;
    u8 *entry;
    s16 limit;
    s16 step;

    step = *(s16 *)((u8 *)arg0 + 0x52);
    entry = (u8 *)arg0 + 0x74;
    limit = step * (*(s16 *)((u8 *)arg0 + 0x64) - 1) + (*(s16 *)((u8 *)arg0 + 0x72) + *(s32 *)((u8 *)arg0 + 0xC));
    for (i = 0; i < 36; i++) {
        if (*(s16 *)entry == 1 && *(s16 *)(entry + 6) > limit) {
            *(s16 *)entry = 0;
        }
        entry += 0x10;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF0282C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF0299C.s")

void Fragment44_PrepareTrailingScrollRow(void *arg0) {
    s16 count;
    s16 row;
    s16 step;
    s16 width;
    s16 *config;
    u16 *pixels;
    s16 position;

    config = (s16 *)((u8 *)arg0 + 0x44);
    step = *(s16 *)(config + 0x7);
    width = *(s16 *)(config + 0x9);
    count = *(s16 *)(config + 0x11) + *(s16 *)(config + 0x10);
    row = *(s16 *)(config + 0x14) + count;
    if (*(s32 *)(config + 0xa) >= row) {
        position = (s16)(*(s32 *)(config + 0xe) + *(s32 *)((u8 *)arg0 + 0xc) + step * count);
        pixels = *(u16 **)config + row * width;
        D_8AF2BDF8.tag = 0x4F474942;
        D_8AF2BDF8.owner = arg0;
        D_8AF2BDF8.width = width;
        D_8AF2BDF8.rows = 1;
        D_8AF2BDF8.position = position;
        D_8AF2BDF8.step = step;
        D_8AF2BDF8.active = 1;
        D_8AF2BDF8.pixels = pixels;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02AE0.s")

void Fragment44_ShiftActiveScrollRecords(void *arg0, s16 delta) {
    s32 i;
    u8 *entry;

    if (delta == 0) { return; }
    entry = (u8 *)arg0 + 0x74;
    i = 0;
    do {
        if (*(s16 *)entry == 1) {
            (*(s16 *)(entry + 6)) += delta;
        }
        entry += 0x10;
        i++;
    } while (i < 36);
}

extern void *func_800071A4(s32, s32, s32, s32, s32);
extern void func_8AF02AE0(void *, void *, s32);
void Fragment44_InitializeScrollList(s32 arg0, s32 arg1, void *job, s32 tag) {
    s32 config;
    u8 *saved_config;
    u8 *record;
    s16 value;
    s32 step;
    s32 stride;
    s16 visible;
    s32 last_row;
    s32 i;

    config = (s32)(saved_config = (u8 *)arg0 + 0x44);
    step = *(s32 *)(config + 0xC);
    stride = *(s32 *)(config + 0x10);
    visible = *(s16 *)(config + 0x20);
    record = (u8 *)arg0 + 0x74;
    *(s16 *)((u8 *)arg0 + 0x40) = 0;
    *(s16 **)config = (s16 *)arg1;
    *(s32 *)(config + 4) = 0;
    while (1) {
        value = *(s16 *)arg1;
        if (value < 0) { break; }
        (*(s32 *)(config + 4))++;
        arg1 += 2;
    }
    last_row = *(s32 *)(config + 4) / stride - 1;
    if (*(s32 *)(config + 4) % stride > 0) { last_row++; }
    *(s32 *)(config + 0x14) = last_row;
    *(s16 *)(config + 0x24) = last_row;
    *(s16 *)(config + 0x26) = (last_row - visible) * step;
    *(s16 *)(config + 0x2A) = visible + 1;
    if (*(s32 *)(config + 4) > 0) {
        *(s16 *)(config + 0x2C) = (visible + 2) * stride;
        if (*(s16 *)(config + 0x2C) > 36) { *(s16 *)(config + 0x2C) = 36; }
        i = 0;
        if (*(s16 *)(config + 0x2C) > 0) {
            do {
                *(s16 *)(record + 0) = 0;
                *(s16 *)(record + 2) = 0;
                *(s16 *)(record + 4) = 0;
                *(s16 *)(record + 6) = 0;
                *(s16 *)(record + 8) = 0;
                *(void **)(record + 0xC) = func_800071A4(0, 2, 0x50, 0x3C, 0);
                record += 0x10;
                i++;
            } while (i < *(s16 *)(saved_config + 0x2C));
        }
        func_8AF02AE0((void *)arg0, job, tag);
    }
}

extern void Fragment44_InitializeScrollList(s32, s32, void *, s32);
extern s32 D_8AF2BE10;
void func_8AF02DA4(s32 arg0, s32 arg1) {
    Fragment44_InitializeScrollList(arg0, arg1, &D_8AF2BE10, 0x4943414C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02DD0.s")

extern Gfx *D_800D0510;
extern u8 D_80094E00[];
extern u8 D_80094F50[];
extern void func_8AF02DD0(void *);
void func_8AF02F18(void *arg0) {
    s32 i;
    u8 *ptr;
    u8 *count_base;

    gSPDisplayList(D_800D0510++, D_80094E00);
    count_base = (u8 *)arg0 + 0x44;
    if (*(s16 *)(count_base + 0x2C) > 0) {
        ptr = (u8 *)arg0 + 0x74;
        i = 0;
        do {
            func_8AF02DD0(ptr);
            i++;
            ptr += 0x10;
        } while (i < *(s16 *)(count_base + 0x2C));
    }
    gSPDisplayList(D_800D0510++, D_80094F50);
}

extern void func_8AF0299C(void *);
extern void Fragment44_PrepareTrailingScrollRow(void *);
extern void func_8AF00130(s32);

void Fragment44_StepScrollUp(void *arg0) {
    u8 *state;
    u8 *config;

    state = (u8 *)arg0 + 0x28;
    if (*(s16 *)((u8 *)arg0 + 0x38) > 0) {
        if (*(s16 *)(state + 0xE) > 0) {
            (*(s16 *)(state + 0xE))--;
        } else {
            config = (u8 *)arg0 + 0x44;
            if (*(s32 *)(state + 8) < 0) {
                *(s32 *)(state + 8) += *(s32 *)(config + 0xC);
                if (*(s32 *)(state + 8) > 0) { *(s32 *)(state + 8) = 0; }
                *(s16 *)(state + 0x12) = 1;
                func_8AF0299C(arg0);
            }
        }
        (*(s16 *)(state + 0x10))--;
        func_8AF00130(1);
    }
}

void Fragment44_StepScrollDown(void *arg0) {
    u8 *state;
    u8 *config;

    state = (u8 *)arg0 + 0x28;
    config = (u8 *)arg0 + 0x44;
    if (*(s16 *)((u8 *)arg0 + 0x38) >= *(s16 *)(config + 0x24)) { return; }
    if (*(s16 *)(state + 0xE) < *(s16 *)(config + 0x20)) {
        (*(s16 *)(state + 0xE))++;
    } else {
        if (*(s32 *)(state + 8) > -*(s16 *)(config + 0x26)) {
            *(s32 *)(state + 8) -= *(s32 *)(config + 0xC);
            if (*(s32 *)(state + 8) < -*(s16 *)(config + 0x26)) { *(s32 *)(state + 8) = -*(s16 *)(config + 0x26); }
            *(s16 *)(state + 0x12) = 1;
            Fragment44_PrepareTrailingScrollRow(arg0);
        }
    }
    (*(s16 *)(state + 0x10))++;
    func_8AF00130(1);
}

void Fragment44_AlignAndStepScrollUp(void *arg0) {
    u8 *state;
    u8 *config;

    state = (u8 *)arg0 + 0x28;
    *(s16 *)((u8 *)arg0 + 0x38) = *(s16 *)((u8 *)arg0 + 0x38) - *(s16 *)((u8 *)arg0 + 0x36);
    if (*(s16 *)((u8 *)arg0 + 0x38) < 0) { *(s16 *)((u8 *)arg0 + 0x38) = 0; }
    *(s16 *)(state + 0xE) = 0;
    if (*(s16 *)(state + 0x10) > 0) {
        config = (u8 *)arg0 + 0x44;
        if (*(s32 *)(state + 8) < 0) {
            *(s32 *)(state + 8) += *(s32 *)(config + 0xC);
            if (*(s32 *)(state + 8) > 0) { *(s32 *)(state + 8) = 0; }
            *(s16 *)(state + 0x12) = 1;
            func_8AF0299C(arg0);
        }
        (*(s16 *)(state + 0x10))--;
        func_8AF00130(0xC4);
    }
}

void Fragment44_AlignAndStepScrollDown(void *arg0) {
    u8 *state;
    u8 *config;

    state = (u8 *)arg0 + 0x28;
    config = (u8 *)arg0 + 0x44;
    *(s16 *)((u8 *)arg0 + 0x38) = *(s16 *)((u8 *)arg0 + 0x38) + *(s16 *)(config + 0x20) - *(s16 *)((u8 *)arg0 + 0x36);
    if (*(s16 *)((u8 *)arg0 + 0x38) > *(s16 *)(config + 0x24)) { *(s16 *)((u8 *)arg0 + 0x38) = *(s16 *)(config + 0x24); }
    *(s16 *)(state + 0xE) = *(s16 *)(config + 0x20);
    if (*(s16 *)(state + 0x10) >= *(s16 *)(config + 0x24)) { return; }
    if (*(s32 *)(state + 8) > -*(s16 *)(config + 0x26)) {
        *(s32 *)(state + 8) -= *(s32 *)(config + 0xC);
        if (*(s32 *)(state + 8) < -*(s16 *)(config + 0x26)) { *(s32 *)(state + 8) = -*(s16 *)(config + 0x26); }
        *(s16 *)(state + 0x12) = 1;
        Fragment44_PrepareTrailingScrollRow(arg0);
    }
    (*(s16 *)(state + 0x10))++;
    func_8AF00130(0xC4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF0326C.s")
#endif
