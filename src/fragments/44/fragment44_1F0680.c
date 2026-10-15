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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02410.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02C28.s")

extern void func_8AF02C28(s32, s32, void *, s32);
extern s32 D_8AF2BE10;
void func_8AF02DA4(s32 arg0, s32 arg1) {
    func_8AF02C28(arg0, arg1, &D_8AF2BE10, 0x4943414C);
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
