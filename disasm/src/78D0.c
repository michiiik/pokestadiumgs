#include "global.h"


#ifdef VERSION_US
extern void *D_800D0518;
extern void *D_800D051C;
extern s32 D_800D0510;
extern s32 main_pool_alloc_with_func(s32, s32, s32, s32);
extern void Gfx_SwapDisplayListBuffer(void);
void Gfx_InitDisplayListBuffers(s32 arg0, s32 arg1) {
    *(s16 *)((u8 *)&D_800D0518 + 0x10) = 0;
    *(s32 *)((u8 *)&D_800D0518 + 0xC) = arg0;
    D_800D0518 = (void *)main_pool_alloc_with_func(arg0, arg1, 0x44594E30, 0);
    D_800D051C = (void *)main_pool_alloc_with_func(arg0, arg1, 0x44594E31, 0);
    Gfx_SwapDisplayListBuffer();
}

extern void *D_800D0518;
extern void *D_800D051C;
extern void main_pool_try_free();
void Gfx_FreeDisplayListBuffers(void) { main_pool_try_free(D_800D051C); main_pool_try_free(D_800D0518); }

void Gfx_SwapDisplayListBuffer(void) {
    struct DisplayListState {
        s32 entries[3];
        s32 size;
        s16 index;
    };
    struct DisplayListState *state = (struct DisplayListState *)&D_800D0518;
    s32 *entry;
    state->index = state->index ^ 1;
    entry = state->entries + state->index;
    state->entries[2] = *entry + state->size;
    D_800D0510 = *entry;
}

void Gfx_GetDisplayListRange(void **arg0, s32 *arg1) {
    struct DisplayListState {
        s32 entries[3];
        s32 size;
        s16 index;
    };
    struct DisplayListState *state = (struct DisplayListState *)&D_800D0518;
    *arg1 = D_800D0510 - state->entries[state->index];
    *arg0 = (void *)state->entries[state->index];
}

u32 Gfx_AllocDisplayList(s32 arg0) {
    struct DisplayListState { s32 entries[3]; s32 size; s16 index; };
    u32 value;
    u32 result = 0;
    arg0 = (arg0 + 7) & ~7;
    value = ((struct DisplayListState *)&D_800D0518)->entries[2] - arg0;
    if (value >= (u32)D_800D0510) {
        ((struct DisplayListState *)&D_800D0518)->entries[2] = value;
        result = value;
    }
    return result;
}

extern s32 D_800D0520;
extern s32 D_800D0510;
s32 Gfx_GetDisplayListRemaining(void) { return D_800D0520 - D_800D0510; }
#endif
