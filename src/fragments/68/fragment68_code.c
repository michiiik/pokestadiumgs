#include "global.h"


#ifdef VERSION_US
extern void* func_80041C98(s32 arg0);
extern void func_80041E2C(void);
extern u16* func_80042C68(void* arg0, s32 arg1, s32 arg2);
extern u16* D_8F000924;
extern s32 D_8F00092C;
extern s32 D_8F000920;

void func_8F000020(s32 arg0) {
    void* var_v0;

    var_v0 = func_80041C98(5);
    func_80041E2C();
    D_8F000924 = func_80042C68(var_v0, 128, 128);
    *D_8F000924 &= 0xFEFF;
    D_8F00092C = 0;
    D_8F000920 = 0;
    if (arg0 != 0) {
        D_8F000920 = arg0 - 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/68/fragment68_code/func_8F000098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/68/fragment68_code/func_8F000284.s")

extern void func_80008648();
extern void func_800088DC();
extern void func_8F000098();
extern void func_8F000284();

void func_8F0004EC(void) {
    func_800088DC();
    func_8F000284();
    func_8F000098();
    func_80008648();
}

extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromTransparent(s32);
extern void func_800226C0(s32);
extern void* D_80087200;

s32 func_8F000524(s32 incoming) {
    s32 state = incoming;
    s32 previous = D_8F000920;
    s32 leaving = 0;

    switch (incoming) {
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            state = 1;
        }
        break;
    case 1:
        if (*(u16*)((u8*)D_80087200 + 0xC) & 0x800) {
            if (--D_8F000920 < 0) {
                D_8F000920 = 15;
            }
        }
        if (*(u16*)((u8*)D_80087200 + 0xC) & 0x400) {
            if (++D_8F000920 >= 16) {
                D_8F000920 = 0;
            }
        }
        if (previous != D_8F000920) {
            func_800226C0(1);
        }
        if (*(u16*)((u8*)D_80087200 + 8) & 0x8000) {
            leaving = 1;
            func_800226C0(2);
        } else if (*(u16*)((u8*)D_80087200 + 8) & 0x4000) {
            D_8F000920 = -1;
            leaving = 1;
            func_800226C0(3);
        }
        if (leaving) {
            state = 2;
            StageFade_StartFromTransparent(5);
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

/* Raw six-byte state at offset 0x1E of the node behind object offset 0x1C. */
typedef struct F68SavedVector {
    u16 values[3];
} F68SavedVector;
extern s32 D_8F000910;
extern s32 D_8F000928;
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_80042FBC(void*, s32);
extern void func_80064D28(void);
extern s32 func_80043064(void*);
extern s32 func_80043678(void*);

void func_8F00068C(void) {
    s32 state = 0;
    s32 remaining;
    F68SavedVector saved;

    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        saved = *(F68SavedVector*)(*(u8**)((u8*)D_8F000924 + 0x1C) + 0x1E);
        remaining = D_8F00092C;
        if (remaining == 0) {
            D_8F00092C = 150;
            func_80042FBC(D_8F000924, D_8F000910);
            if (++D_8F000910 >= 252) {
                D_8F000910 = 0;
            }
        } else {
            D_8F00092C = remaining - 1;
        }
        func_80064D28();
        if (func_80043064(D_8F000924)) {
            *(F68SavedVector*)(*(u8**)((u8*)D_8F000924 + 0x1C) + 0x1E) = saved;
        }
        D_8F000928 = func_80043678(D_8F000924);
        func_8F0004EC();
        state = func_8F000524(state);
    } while (state != 3);
}

s32 func_8F0007C8(void) {
    s32 result = 0;
    if (D_8F000920 >= 0) result = D_8F000920 + 1;
    return result;
}

extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern s32 func_8004C09C(s32);
extern s32 func_8004C4B0(s32);
extern u8* func_80047588(s32, s32);
extern u8* Asset_LoadToSegment(s32, u8*, u8*, s32);
extern u8 D_1000000[], D_446E30[], D_447D00[];
extern void func_80006148(void*);
extern void func_80008514(s32);
extern void func_80008574(void);
extern void func_80006158(void);
extern void func_80047610(void);
extern void func_8004C398(void);

/* Both incoming words have stack homes in the original entry-point ABI. */
s32 fragment68_main(s32 selection, s32 unused) {
    s32 configuration;

    main_pool_push_state(0x4442534C);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    configuration = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(3);
    func_8004C4B0(0x42);
    func_80047588(0x1B, 0);
    Asset_LoadToSegment(((u32)D_1000000 & 0x0F000000) >> 24, D_446E30, D_447D00, 0);
    func_80006148(D_80087200);
    func_8F000020(selection);
    func_80008514(configuration);
    func_8F00068C();
    func_80008574();
    func_80006158();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4442534C);
    return func_8F0007C8();
}
#endif
