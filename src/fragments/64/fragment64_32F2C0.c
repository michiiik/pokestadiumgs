#include "global.h"


#ifdef VERSION_US
extern void func_8004C8C0(s32);
extern void func_8004C4B0(s32);
void func_87F0C650(void *arg0) {
    struct State {
        s32 first, second;
        u8 active : 1;
        u8 pending : 1;
        u8 other : 6;
    };
    struct State *state = arg0;
    state->first = 0;
    state->second = 0;
    state->active = 0;
    state->pending = 0;
    func_8004C8C0(0x139);
    func_8004C4B0(0x16);
}

extern s32 func_80001FF0(void);
void func_87F0C694(void *arg0, s32 arg1) {
    struct State {
        s32 first, second;
        u8 active : 1;
        u8 pending : 1;
        u8 other : 6;
    };
    struct State *state = arg0;
    state->first = 0;
    state->second = (func_80001FF0() * arg1) / 2;
    state->active = 1;
    state->pending = 0;
}

typedef struct FadeTimer {
    /* 0x00 */ s32 elapsed;
    /* 0x04 */ s32 limit;
    /* 0x08:31 */
    u32 active : 1;
    /* 0x08:30 */
    u32 pending : 1;
    u32 reserved : 30;
} FadeTimer;
typedef struct FadeInput {
    u8 pad00[6];
    /* 0x06 */ u16 pressed;
} FadeInput;
extern FadeInput* D_80087200;
extern Gfx* D_800D0510;
extern Gfx D_80094E38[], D_80094F50[];
extern u8 StageContext_GetFadeMode(void);
extern void StageContext_SetClearColor(u16);
extern s32 StageFade_StartFromTransparent();
extern s32 func_800061EC(void);
extern const char* func_8004C874(s32, s32);
extern s32 func_80049148(s32, s32, const char*, ...);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800495BC(s32, s32, const char*, ...);
extern void func_800499EC(void);
extern void* func_8004C990(s32, s32);
extern s32 func_8004D19C(s32, s32, void*, s32, s32);
extern void func_87F0C930(FadeTimer*);
extern void func_87F0C7B0(FadeTimer*);
s32 func_87F0C6F4(FadeTimer* timer) {
    s32 result = 0;
    s32 finished;
    if (timer->pending) {
        if (StageContext_GetFadeMode() == 1) result = 1;
    } else if (StageContext_GetFadeMode() == 0) {
        if (timer->active) {
            timer->elapsed = timer->elapsed + 1;
            finished = 0;
            if (timer->elapsed >= timer->limit) {
                timer->elapsed = timer->limit;
                finished = 1;
            }
            if (D_80087200->pressed & 0xD000) finished = 1;
            if (finished) func_87F0C930(timer);
        }
    }
    return result;
}

void func_87F0C7B0(FadeTimer* unused) {
    static s32 scrollPosition = 0xA0;
    const char* text;
    s32 width;
    if (func_800061EC() == 0) {
        text = (const char*)func_8004C874(0x16, 0);
        width = func_80049148(2, 0, text);
        scrollPosition = scrollPosition - 1;
        if (scrollPosition < -width) scrollPosition = scrollPosition + width + 0x3C;
        func_800498C4();
        func_800496A4(2, 0);
        func_8004972C(0xFF, 0xFF, 0xFF, 0xFF);
        func_800495BC(scrollPosition, 0xAA, text);
        func_800495BC(width + scrollPosition + 0x3C, 0xAA, text);
        func_800499EC();
    }
}
void func_87F0C88C(FadeTimer* timer) {
    if ((*(u32*)((u8*)timer + 8) >> 31)) {
        gSPDisplayList(D_800D0510++, D_80094E38);
        func_8004D19C(0xC7, 0xB6, func_8004C990(0x139, 0), 0, 0);
        gSPDisplayList(D_800D0510++, D_80094F50);
        func_87F0C7B0(timer);
    }
}

void func_87F0C930(FadeTimer* timer) {
    if (!(timer->pending)) {
        timer->pending = 1;
        StageContext_SetClearColor(1);
        StageFade_StartFromTransparent(0x14);
    }
}
#pragma C_FUNCTION_PADDING(12)
#endif
