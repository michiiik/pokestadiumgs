#include "global.h"


#ifdef VERSION_US
extern f32 Fragment14_InterpolatePanelRectangle(u8 *, u8 *);
extern void func_81609A90(u8 *, u8 *);
void func_81304BB0(u8 *arg0, s32 arg1) {
    u8 sp30[8];
    u8 sp28[8];
    f32 sp24;

    sp24 = *(f32 *)(arg0 + 0xC);
    *(f32 *)(arg0 + 0xC) = 0.0f;
    Fragment14_InterpolatePanelRectangle(arg0, sp30);
    *(f32 *)(arg0 + 0xC) = 16.0f;
    Fragment14_InterpolatePanelRectangle(arg0, sp28);
    if (arg1 != 0) {
        func_81609A90(sp30, sp28);
    } else {
        func_81609A90(sp28, sp30);
    }
    *(f32 *)(arg0 + 0xC) = sp24;
}

void func_81304C3C(u8 *arg0, s32 arg1, s32 arg2) {
    arg0[0x1A] = 0;
    *(s32 *)arg0 = arg1;
    arg0[0x19] = (u8)arg2;
    *(f32 *)(arg0 + 0x10) = 0.0f;
    *(f32 *)(arg0 + 0x0C) = 0.0f;
}

const u32 D_81312470[2] = {0x00220002, 0x00010000};

typedef struct {
    u8 unk[8];
} UnkStruct8_81304C58;

void func_81304C58(u8 *arg0, u8 *arg1) {
    if (arg1 == NULL) {
        *(s32 *)(arg0 + 0x14) = 0;
    } else {
        *(UnkStruct8_81304C58 *)(arg0 + 4) = *(UnkStruct8_81304C58 *)arg1;
    }
    switch (arg0[0x1A]) {
        case 0:
        case 5:
            *(f32 *)(arg0 + 0xC) = 0.0f;
            /* fall through */
        case 4:
            arg0[0x1A] = 1;
            arg0[0x18] = 0;
            break;
        case 1:
        case 2:
        case 3:
            break;
    }
    func_81304BB0(arg0, 1);
}

extern void *func_81609530(s32);
extern void func_8160945C(s16 *, s16 *, s16 *, f32);
f32 Fragment14_InterpolatePanelRectangle(u8 *arg0, u8 *arg1) {
    f32 progress;
    u8 *origin;

    origin = (u8 *)(arg0 + 4);
    progress = 1.0f;
    /* Keep the integer divisor: IDO lowers / 16.0f differently. */
    switch (arg0[0x1A]) {
    case 1:
        progress = *(f32 *)(arg0 + 0xC) / 16;
        break;
    case 0:
    case 3:
    case 4:
    case 5:
        progress = *(f32 *)(arg0 + 0xC) / 16;
        switch (arg0[0x18]) {
        case 0:
            origin = func_81609530(0);
            break;
        case 1:
        case 2:
            origin = func_81609530(1);
            break;
        case 3:
            origin = func_81609530(0);
            break;
        }
        break;
    case 2:
    default:
        break;
    }
    func_8160945C((s16 *)arg1, (s16 *)origin, func_81609530(2), progress > 0.5f ? 1.0f : progress + progress);
    return progress;
}

s32 func_81304E14(u8 *arg0) {
    *(f32 *)(arg0 + 0xC) = 0.0f;
    return 0;
}

f32 func_816092FC(void);
s32 func_81304E24(u8 *arg0) {
    *(f32 *)(arg0 + 0xC) += func_816092FC();
    if (*(f32 *)(arg0 + 0xC) >= 16.0f) {
        *(f32 *)(arg0 + 0xC) = 16.0f;
        arg0[0x1A] = 2;
    }
    return 1;
}

extern u8 D_800CE060[];
extern s32 func_81302290(void *);
extern void func_800226C0(s32);
s32 Fragment14_UpdatePanelInput(u8 *arg0) {
    u16 pressed;
    u8 *controller;

    controller = (u8 *)((u32)D_800CE060 + arg0[0x19] * 0x28);
    *(f32 *)(arg0 + 0xC) = 16.0f;
    pressed = *(u16 *)(controller + 0xC);
    if (pressed & 0x8000) {
        switch (arg0[0x18]) {
        case 0:
            if (func_81302290(*(void **)arg0) >= 10) {
                func_800226C0(5);
                arg0[0x1A] = 3;
                break;
            }
            /* fall through */
        case 1:
        case 2:
            func_800226C0(0xA3);
            arg0[0x1A] = 4;
            func_81304BB0(arg0, 0);
            break;
        case 3:
            func_800226C0(3);
            arg0[0x1A] = 4;
            func_81304BB0(arg0, 0);
            break;
        }
    } else if (pressed & 0x4000) {
        arg0[0x18] = 3;
        func_800226C0(3);
        arg0[0x1A] = 4;
        func_81304BB0(arg0, 0);
    } else if (pressed & 0x400) {
        if (arg0[0x18] < 3) {
            arg0[0x18]++;
            func_800226C0(1);
        }
    } else if (pressed & 0x800) {
        if (arg0[0x18] > 0) {
            arg0[0x18]--;
            func_800226C0(1);
        }
    }
    return 1;
}

extern s32 D_81311F40[];
extern s32 func_81311C70(s32, s32 *, u8, s32);
s32 func_8130500C(u8 *arg0) {
    s32 result;

    result = func_81311C70(*(s32 *)arg0 + 0x74, D_81311F40, arg0[0x19], -1);
    *(f32 *)(arg0 + 0xC) = 16.0f;
    if (result == 0) {
        goto done;
    }
    arg0[0x1A] = 2;
done:
    return 1;
}

s32 func_81305068(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (0xC))) = (f32) ((*(f32 *)((u8 *)(arg0) + (0xC))) - func_816092FC());
    if ((*(f32 *)((u8 *)(arg0) + (0xC))) <= 0.0f) {
        (*(f32 *)((u8 *)(arg0) + (0xC))) = 0.0f;
        (*(s8 *)((u8 *)(arg0) + (0x1A))) = 5;
    }
    return 1;
}

s32 func_813050C0(u8 *arg0) {
    *(f32 *)(arg0 + 0xC) = 0.0f;
    return 0;
}

extern void func_81600A34(void *, void *, s32, s32, s32, s32, s32);
void Fragment14_UpdatePanelState(u8 *arg0, void *arg1) {
    s16 rectangle[4];
    s32 active;

    active = 0;
    switch (arg0[0x1A]) {
    case 0:
        active = func_81304E14(arg0);
        break;
    case 1:
        active = func_81304E24(arg0);
        break;
    case 2:
        active = Fragment14_UpdatePanelInput(arg0);
        break;
    case 3:
        active = func_8130500C(arg0);
        break;
    case 4:
        active = func_81305068(arg0);
        break;
    case 5:
        active = func_813050C0(arg0);
        break;
    }
    Fragment14_InterpolatePanelRectangle(arg0, (u8 *)&rectangle);
    func_81600A34(arg1, arg0, active, rectangle[0], rectangle[1], rectangle[2], rectangle[3]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FCD40/func_813051B8.s")

extern s32 func_81600DA8(void *, void *);
extern void func_813051B8(u8 *, f32, s32, f32 *, void *);
void Fragment14_DrawSelectionPanel(u8 *arg0, void *arg1) {
    u8 rectangle[8];
    f32 progress;
    f32 opacity;

    if (arg0[0x1A] != 0 && func_81600DA8(arg1, arg0) != 0) {
        progress = Fragment14_InterpolatePanelRectangle(arg0, (u8 *)rectangle);
        if (progress > 0.5f) {
            opacity = (progress - 0.5f) * 2.0f;
        } else {
            opacity = 0.0f;
        }
        func_813051B8((u8 *)rectangle, opacity, arg0[0x18], (f32 *)(arg0 + 0x10),
            *(void **)(*(u8 **)(*(u8 **)arg0 + 0x1A148) + 0x940));
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FCD40/func_8130559C.s")
#endif
