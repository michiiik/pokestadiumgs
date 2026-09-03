#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_813110F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311368.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_813114B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311650.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311894.s")

extern f32 func_816092FC(void);
void func_813119E4(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 4) += step;
    if (*(f32 *)(arg0 + 4) >= 16.0f) {
        *(f32 *)(arg0 + 4) = 16.0f;
        arg0[0x18] = 2;
    }
}

void func_81311A3C(u8 *arg0) {
    f32 step = func_816092FC();
    *(f32 *)(arg0 + 4) -= step;
    if (*(f32 *)(arg0 + 4) <= 0.0f) {
        *(f32 *)(arg0 + 4) = 0.0f;
        arg0[0x18] = 4;
    }
}

void func_81311A90(u8 *arg0) {
    *(f32 *)(arg0 + 4) = 0.0f;
}

void func_81311A9C(u8 *arg0) {
    *(s32 *)(arg0 + 0) = 0;
    *(f32 *)(arg0 + 4) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311AAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311B98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_109280/func_81311C18.s")

extern void func_81311B98();

typedef struct {
    void *owner;
    u8 pad04[0x14];
    u8 status;
    s8 index;
} Frag14State;
typedef struct {
    u8 pad00[4];
    s16 value;
    u8 pad06[2];
} Frag14Entry;
typedef struct {
    u8 pad00[0x18];
    s16 fallback;
    u8 pad1A[6];
    Frag14Entry *entries;
} Frag14Record;
s32 func_81311C70(void *arg0, void *arg1) {
    Frag14State *state = arg0;
    Frag14Record *record = arg1;
    s16 result;
    s8 index;
    if ((record == state->owner) && (state->status == 4)) {
        index = state->index;
        state->status = 0;
        if (index >= 0) {
            result = record->entries[index].value;
        } else {
            result = record->fallback;
        }
        return (result << 16) >> 16;
    }
    if (state->status != 3) {
        func_81311B98();
    }
    return 0;
}

void func_81311CFC(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + (0))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x19))) = -1;
    (*(s8 *)((u8 *)(arg0) + (0x1A))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x18))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x10))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x12))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x14))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x16))) = 0;
    (*(f32 *)((u8 *)(arg0) + (4))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (8))) = 0.0f;
}
#endif
