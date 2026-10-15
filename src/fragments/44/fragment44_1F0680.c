#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02584.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02684.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02750.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF0282C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF0299C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF02A34.s")

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
extern void func_8AF02A34(void *);
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
            func_8AF02A34(arg0);
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
        func_8AF02A34(arg0);
    }
    (*(s16 *)(state + 0x10))++;
    func_8AF00130(0xC4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F0680/func_8AF0326C.s")
#endif
