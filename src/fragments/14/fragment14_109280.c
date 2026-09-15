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

/* Tail (last 2 entries) of the jump table used by the still-GLOBAL_ASM
 * func_81311AAC's own switch, immediately above. Not referenced from C: it
 * exists only so this file's own .rodata subsegment starts at a
 * 16-byte-aligned ROM address (0x81312A10) while still landing
 * func_81311B98's own jump table (jtbl_81312A18) at its real retail
 * address right below. */
const u32 D_81312A10[2] = {0x81311B14, 0x81311B24};

extern void func_813110F0(u8 *arg0, void *arg1, s32 arg2, s32 arg3);
void func_81311B98(u8 *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 sp20 = arg2;

    func_813110F0(arg0, arg1, arg3, arg3);
    switch (arg0[0x18]) {
        case 2:
            *(f32 *)(arg0 + 4) = 16.0f;
            return;
        case 0:
        case 4:
            *(f32 *)(arg0 + 4) = 0.0f;
            break;
        case 1:
        case 3:
            break;
    }
    arg0[0x18] = 1;
    arg0[0x19] = 0;
    arg0[0x1A] = sp20;
}

void func_81311C18(u8 *arg0) {
    *(s8 *)(arg0 + 0x19) = -1;
    switch (arg0[0x18]) {
        case 0:
        case 4:
            *(f32 *)(arg0 + 4) = 0.0f;
            return;
        case 2:
            *(f32 *)(arg0 + 4) = 16.0f;
            break;
        case 1:
        case 3:
            break;
    }
    arg0[0x18] = 3;
}

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
s32 func_81311C70(void *arg0, void *arg1, s32 arg2, s32 arg3) {
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
        func_81311B98(arg0, arg1, arg2, arg3);
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
