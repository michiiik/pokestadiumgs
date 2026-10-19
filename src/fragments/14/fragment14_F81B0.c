#include "global.h"


#ifdef VERSION_US
/* Keep the original named rodata ahead of this file's seven switch tables. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/D_81312180.s")

typedef struct {
    u8 pad00000[0x1A138];
    s32 mode;
    u8 pad1A13C[4];
    u8 active;
    s8 requested;
    s8 slot;
    s8 selected;
    u8 pad1A144[4];
    u8 *data;
    u8 pad1A14C[0x18];
    char *title;
    s32 status;
    s32 pending;
} Fragment14SetupState;

typedef struct {
    u8 bytes[8];
} Fragment14Position;

extern void func_81310894(void *, s32);
extern s32 func_8131109C(void *);
extern void func_8130F7B8(s32, s32);
extern void func_81300E34(void *);
extern void func_813010B0(void *);
extern void _bzero(void *, s32);

extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
extern void func_80057908(u8);
extern s32 func_8005A0B4(s32);
void func_81300020(s32 arg0) {
    main_pool_pop_state(0x50504354);
    main_pool_push_state(0x50504354);
    func_80057908((u8)arg0);
    func_8005A0B4(arg0);
}

s32 func_81300064(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 4) && (func_8005D92C(arg0) == 7) && (func_800606F4(arg0) > 0)) {
        return 1;
    }
    return 0;
}

void func_813000BC(void *arg0, s32 arg1) {
    typedef struct {
        u8 pad_0[0x1A141];
        s8 flag;
        u8 pad_1[0x2A];
        s32 value;
    } State;
    State *state = (State *)arg0;
    state->flag = arg1;
    state->value = 1;
}

void func_813000DC(u8 *arg0) {}

s32 func_813000E4(void *arg0) {
    s32 var_v1;
    s8 temp_a0;
    s8 temp_a0_2;
    s8 temp_a0_3;
    s8 temp_a1;
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0x1A148)));
    var_v1 = 0;
    temp_a1 = (*(s8 *)((u8 *)(temp_v0) + (0x900)));
    if ((temp_a1 >= 0) && (temp_a1 < 4)) {
        var_v1 = 1;
    }
    temp_a0 = (*(s8 *)((u8 *)(temp_v0) + (0x901)));
    if ((temp_a0 >= 0) && (temp_a0 < 4)) {
        var_v1 += 1;
    }
    temp_a0_2 = (*(s8 *)((u8 *)(temp_v0) + (0x902)));
    if ((temp_a0_2 >= 0) && (temp_a0_2 < 4)) {
        var_v1 += 1;
    }
    temp_a0_3 = (*(s8 *)((u8 *)(temp_v0) + (0x903)));
    if ((temp_a0_3 >= 0) && (temp_a0_3 < 4)) {
        var_v1 += 1;
    }
    return var_v1 < 2;
}

extern s32 func_81700B8C(s32, char *);
extern s32 func_81700CDC(s32);
extern void *func_8004C874(s32, s32);
extern void Fragment14_UpdatePanelState(u8 *, void *);
extern s32 Fragment14_GetPanelResult(u8 *);
extern f32 Fragment14_InterpolatePanelRectangle(u8 *, u8 *);
void Fragment14_UpdateTitleText(void *arg0, s32 arg1) {
    char *text;

    if (arg1 != 0) {
        text = func_8004C874(0xF, 0x5D);
    } else {
        if ((*(u16 *)(*(u8 **)(((u8 *)arg0 + 0x18000) + 0x2148) + 0x950) & 0xFF00) == 0x200) {
            arg1 = *(s16 *)(*(u8 **)(*(u8 **)(((u8 *)arg0 + 0x18000) + 0x2148) + 0x940) +
                           0x3E);
            if (arg1 >= 0) {
                text = func_8004C874(0xF, arg1);
            } else {
                text = (char *)(*(u8 **)(*(u8 **)(((u8 *)arg0 + 0x18000) + 0x2148) + 0x940));
            }
        } else {
            text = func_8004C874(0xF, 0x2B);
        }
    }
    if (text != *(char **)(((u8 *)arg0 + 0x18000) + 0x2164)) {
        func_81700B8C(1, text);
        func_81700CDC(1);
        ((Fragment14SetupState *)arg0)->title = text;
    }
}

extern void Fragment14_ResetGrid(u8 *, s32, s32, s32, void *);
extern void func_81601A38(s32 *, s32);
extern void func_81601A78(s32 *, s32);
extern void func_81601B00(s32 *, s32, s32);
extern u8 D_81312A40;
void func_81300244(s32 arg0, s32 arg1, s32 arg2) {
    func_81601A38(&D_81312A40, 0);
    func_81601A78(&D_81312A40, 1);
    if ((arg1 < 4) && (arg1 >= 0)) {
        func_81601B00(&D_81312A40, arg1, 1);
    }
    Fragment14_ResetGrid((u8 *)(arg0 + 0xD18), 0x9B, 0xE1, arg2, &D_81312A40);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_813002D0.s")

s32 func_81300314(void *arg0, s32 arg1, s32 arg2) { u8 *base = (u8 *)arg0 + 0x18000; do { arg1 += arg2; if (arg1 < 0 || arg1 >= 4) break; if (*(s8 *)(*(u8 **)(base + 0x2148) + arg1 + 0x900) >= -1) break; } while (1); return arg1; }

extern void func_80057944(s32);

void func_81300350(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_80057944(var_s0 & 0xFF);
        var_s0 += 1;
    } while (var_s0 != 4);
}

extern u8 D_81312180;
extern void *func_81609530(s32);
extern s8 *HAL_Strcpy(s8 *, s8 *);
extern void func_81307DC0(void *, s32, s32, s32, void *);
extern void func_8005D9E0(s32, void *);
extern void func_81302EE4(void *, void *, void *, s32, void *, void *);
extern s32 func_8130A460(void *, s32, s32, void *);
extern s32 func_81304178(u8 *, s32, s32, s32);
extern s32 func_8160A844(void *, void *, s32, s32);
extern void Fragment14_AdvanceSelectionSlot(void *, s32);
extern void func_81300020(s32 arg0);
extern s32 func_81300064(s32 arg0);
extern void func_81300244(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_81302290(void *arg0);
void Fragment14_ConfigureControllerSelection(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    char name[16];
    s32 id;
    s64 info[2];

    if (arg2 < 4 && arg2 >= 0) {
        func_81300020(arg2);
        ((Fragment14SetupState *)arg0)->status = func_81300064(arg2);
    }
    func_81300244((s32)arg0, arg2, arg1);
    func_81307DC0((u8 *)arg0 + 0xDA8, (s32)arg0, arg1, arg2,
                  *(void **)((u8 *)arg0 + 0x1A14C));
    id = 0;
    name[0] = D_81312180;
    if (arg2 < 4 && arg2 >= 0) {
        func_8005D9E0(arg2, (s32 *)info);
        HAL_Strcpy((s8 *)name, (s8 *)info + 2);
        id = *(u16 *)info;
        if (func_81300064(arg2) != 0) {
            ((Fragment14SetupState *)arg0)->data[0x955] |= 1 << ((Fragment14SetupState *)arg0)->slot;
        } else {
            ((Fragment14SetupState *)arg0)->data[0x955] &= ~(1 << ((Fragment14SetupState *)arg0)->slot);
        }
    }
    if (arg3 != 0) {
        arg2 = 0;
    } else {
        arg2 = (s32)(((Fragment14SetupState *)arg0)->data +
                     ((Fragment14SetupState *)arg0)->slot * 0x240);
    }
    func_81302EE4((u8 *)arg0 + 0x15370, arg0, name, id, (void *)arg2, (u8 *)arg0 + 0x1A144);
    func_8130A460((u8 *)arg0 + 0xDA8, arg4, arg6, func_81609530(3));
    if (arg3 != 0) {
        arg2 = func_81302290(arg0);
    } else {
        arg2 = -1;
    }
    func_81304178((u8 *)arg0 + 0x15370, arg2, arg5, arg6);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300570.s")

extern void func_813000BC(void *arg0, s32 arg1);
extern s32 func_81300314(void *arg0, s32 arg1, s32 arg2);
void Fragment14_AdvanceSelectionSlot(void *arg0, s32 arg1) {
    s32 next;

    next = func_81300314(arg0, ((Fragment14SetupState *)arg0)->slot, arg1);
    if (next < 0) {
        func_813000BC(arg0, 8);
    } else if (next >= 4) {
        func_813000BC(arg0, 9);
    } else {
        ((Fragment14SetupState *)arg0)->slot = next;
        switch (*(u8 *)(((Fragment14SetupState *)arg0)->data + ((Fragment14SetupState *)arg0)->slot + 0x93C)) {
        case 4:
            _bzero(((Fragment14SetupState *)arg0)->data + ((Fragment14SetupState *)arg0)->slot * 0x240, 0x240);
            func_813000BC(arg0, 5);
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 6:
            func_813000BC(arg0, 1);
            break;
        default:
            func_813000BC(arg0, 0);
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300830.s")

void func_81300B48(u8 *arg0) {}

s32 Fragment14_GetSelectionExitStatus(void *arg0) {
    switch (((Fragment14SetupState *)arg0)->active) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 5:
        return 0;
    case 8:
        return -1;
    case 9:
        return 1;
    }
    return 0;
}

extern void func_8130A570(s32, s32);
extern void func_81304208(s32);
extern void func_81311C18(s32);
void func_81300BA0(s32 arg0) { func_8130A570(arg0 + 0xDA8, 0); func_81304208(arg0 + 0x15370); func_81311C18(arg0 + 0x74); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300BE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81300E34.s")

extern void Fragment14_UpdateTitleText(void *, s32);
extern s32 func_813002D0(void *);
extern s32 func_81300314(void *arg0, s32 arg1, s32 arg2);
extern void func_81300350(void);
extern void Fragment14_ConfigureControllerSelection(void *, s32, s32, s32, s32, s32, s32);
void Fragment14_InitSelectionAdvance(void *arg0) {
    s32 selected;
    s32 exhausted;

    selected = *(s8 *)(((Fragment14SetupState *)arg0)->data +
                      ((Fragment14SetupState *)arg0)->slot + 0x93C);
    exhausted = func_81300314(arg0, ((Fragment14SetupState *)arg0)->slot, 1) >= 4;
    Fragment14_UpdateTitleText(arg0, 0);
    func_81300350();
    ((Fragment14SetupState *)arg0)->status = 0;
    Fragment14_ConfigureControllerSelection(arg0, func_813002D0(arg0), selected, 0, 0, exhausted, exhausted);
    ((Fragment14SetupState *)arg0)->mode = 1;
}

extern void func_81304C3C(u8 *, s32, s32);
extern void func_81304C58(u8 *, u8 *);
extern void func_8130B220(void *, void *, s32, s32);
extern void func_8130B320(void *, void *, s32, s32);
void Fragment14_InitSelectionPreview(void *arg0) {
    Fragment14_UpdateTitleText(arg0, 1);
    func_81300350();
    ((Fragment14SetupState *)arg0)->status = 0;
    func_81304C3C(((u8 *)arg0 + 0xF630), (s32)arg0, func_813002D0(arg0));
    func_81304C58(((u8 *)arg0 + 0xF630), ((u8 *)arg0 + 0x1A15C));
    ((Fragment14SetupState *)arg0)->mode = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_813010B0.s")

void Fragment14_InitSelectedController(void *arg0) {
    Fragment14SetupState *state = arg0;
    s32 selected = state->selected;

    Fragment14_UpdateTitleText(arg0, 1);
    func_81300350();
    state->status = 0;
    if (selected >= 0 && selected < 4) {
        func_80057908(selected);
    }
    Fragment14_ConfigureControllerSelection(arg0, func_813002D0(arg0), selected, 1, 0, 1, 0);
    state->mode = 1;
}

extern s32 func_813000E4(void *arg0);
extern s32 func_81302290(void *);
s8 func_8130125C(void *arg0, s32 arg1) {
    s32 sp1C;
    s8 temp_v1;
    sp1C = func_81302290(arg0);
    if (func_813000E4(arg0) != 0) {
        temp_v1 = *(s8 *)((u8 *)(*(void **)((u8 *)arg0 + 0x1A148)) + 0x954);
        if ((temp_v1 >= 0) && (temp_v1 < sp1C)) {
            return temp_v1;
        }
    }
    return -1;
}

extern s8 func_8130125C(void *arg0, s32 arg1);
void Fragment14_InitSelectionPanelMode0(void *arg0) {
    s32 selected = 0;

    Fragment14_UpdateTitleText(arg0, 0);
    func_81300350();
    ((Fragment14SetupState *)arg0)->status = 0;
    if (((Fragment14SetupState *)arg0)->slot == 0 &&
        *(s8 *)(((Fragment14SetupState *)arg0)->data + ((Fragment14SetupState *)arg0)->slot + 0x93C) == 4) {
        selected = func_8130125C(arg0, (s32)(((Fragment14SetupState *)arg0)->data +
                                          ((Fragment14SetupState *)arg0)->slot * 0x240));
        if (selected < 0) {
            selected = 0;
        }
    }
    func_8130B220(((u8 *)arg0 + 0xD18), arg0, func_813002D0(arg0), selected);
    func_8130B320(((u8 *)arg0 + 0xD18), (u8 *)arg0 + 0x1A154, 0,
                 func_81300314(arg0, ((Fragment14SetupState *)arg0)->slot, 1) >= 4);
    ((Fragment14SetupState *)arg0)->mode = 0;
}

void Fragment14_InitSelectionPanelMode2(void *arg0) {
    func_81300350();
    ((Fragment14SetupState *)arg0)->status = 0;
    Fragment14_UpdateTitleText(arg0, 1);
    func_8130B220(((u8 *)arg0 + 0xD18), arg0, func_813002D0(arg0), 0);
    func_8130B320(((u8 *)arg0 + 0xD18), ((u8 *)arg0 + 0x1A154), 2, 0);
    ((Fragment14SetupState *)arg0)->mode = 0;
}

void Fragment14_InitSelectionPanelMode1(void *arg0) {
    Fragment14_UpdateTitleText(arg0, 1);
    func_81300350();
    ((Fragment14SetupState *)arg0)->status = 0;
    func_8130B220(((u8 *)arg0 + 0xD18), arg0, func_813002D0(arg0), 0);
    func_8130B320(((u8 *)arg0 + 0xD18), ((u8 *)arg0 + 0x1A154), 1, 0);
    ((Fragment14SetupState *)arg0)->mode = 0;
}

void func_813014D0(void *arg0) {
    s32 temp_a0;
    temp_a0 = (s32)arg0;
    Fragment14_UpdateTitleText(arg0, 0);
    func_81300350();
    *(s32 *)((u8 *)temp_a0 + 0x1A168) = 0;
}

void func_8130150C(void *arg0) {
    s32 temp_a0;
    temp_a0 = (s32)arg0;
    Fragment14_UpdateTitleText(arg0, 0);
    func_81300350();
    *(s32 *)((u8 *)temp_a0 + 0x1A168) = 0;
}

extern void func_813000BC(void *arg0, s32 arg1);
extern void Fragment14_AdvanceSelectionSlot(void *arg0, s32 arg1);
extern void func_8130F7B8(s32, s32);
extern void func_81310894(void *, s32);
extern s32 func_8131109C(void *);
void Fragment14_UpdateSlotDialog(void *arg0, s32 arg1) {
    s32 result;

    func_81310894(((u8 *)arg0 + 0xF64C), arg1);
    result = func_8131109C(((u8 *)arg0 + 0xF64C));
    func_8130F7B8((s32)((u8 *)arg0 + 0xF64C), (s32)((u8 *)arg0 + 0x1A154));
    switch (result) {
    case 4:
        func_813000BC(arg0, 5);
        break;
    case 5:
        func_813000BC(arg0, 2);
        break;
    case -1:
        *(s8 *)(*(u8 **)(((u8 *)arg0 + 0x18000) + 0x2148) +
                *(s8 *)(((u8 *)arg0 + 0x18000) + 0x2142) + 0x93C) = -1;
        Fragment14_AdvanceSelectionSlot(arg0, -1);
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 6:
        *(s8 *)(*(u8 **)(((u8 *)arg0 + 0x18000) + 0x2148) +
                *(s8 *)(((u8 *)arg0 + 0x18000) + 0x2142) + 0x93C) = result;
        func_813000BC(arg0, 1);
        break;
    case -2:
    default:
        break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_81301648.s")

extern void func_813000BC(void *arg0, s32 arg1);
extern void func_81311AAC(void *, s32);
void Fragment14_UpdateSelectionPreview(void *arg0, s32 arg1) {
    s32 result;

    Fragment14_UpdatePanelState((u8 *)arg0 + 0xF630, (void *)arg1);
    result = Fragment14_GetPanelResult(((u8 *)arg0 + 0xF630));
    if (result < 0) {
        func_813000BC(arg0, 0);
    } else if (result > 0) {
        switch (result) {
            case 1:
                func_813000BC(arg0, 3);
                break;
            case 2:
                func_813000BC(arg0, 6);
                break;
            case 3:
                func_813000BC(arg0, 7);
                break;
        }
    }
    Fragment14_InterpolatePanelRectangle(((u8 *)arg0 + 0xF630), (u8 *)arg0 + 0x1A154);
    func_81311AAC((u8 *)arg0 + 0x74, arg1);
}

extern void func_8130A044(void *, s32);
extern void func_81303EF4(void *, s32);
extern void Fragment14_UpdateGridState(u8 *, void *);
extern void func_81306F74(void *, void *);
extern s32 func_81304AD0(void *);
extern void func_8130F2C4(void *, s32);
void Fragment14_UpdateSelectionPage(void *arg0, s32 arg1) {
    u8 *panel;

    panel = (u8 *)arg0 + 0xDA8;
    func_8130A044(panel, arg1);
    func_81303EF4(((u8 *)arg0 + 0x15370), arg1);
    func_8130F2C4(arg0, arg1);
    Fragment14_UpdateGridState((u8 *)arg0 + 0xD18, (void *)arg1);
    func_81311AAC((u8 *)arg0 + 0x74, arg1);
    func_81306F74(panel, (u8 *)arg0 + 0x1A154);
    arg1 = func_81304AD0(((u8 *)arg0 + 0x15370));
    if (arg1 != 0) {
        if (arg1 > 0) {
            func_813000BC(arg0, 2);
        } else if (arg1 < 0) {
            func_813000BC(arg0, 3);
        }
    }
}

void Fragment14_UpdateControllerDialog(void *arg0, s32 arg1) {
    s32 result;

    func_81310894(((u8 *)arg0 + 0xF64C), arg1);
    result = func_8131109C(((u8 *)arg0 + 0xF64C));
    func_8130F7B8((s32)((u8 *)arg0 + 0xF64C), (s32)((u8 *)arg0 + 0x1A154));
    switch (result) {
    case -1:
        func_813000BC(arg0, 2);
        break;
    case 0:
    case 1:
    case 2:
    case 3:
        ((Fragment14SetupState *)arg0)->selected = result;
        func_813000BC(arg0, 4);
        break;
    case 6:
        ((Fragment14SetupState *)arg0)->selected = -1;
        func_813000BC(arg0, 4);
        break;
    case -2:
    default:
        break;
    }
}

extern void func_8130B3B8(void *, void *);
extern void func_8130C334(void *);
extern s32 func_8130CDD4(void *);
void Fragment14_UpdateSelectionCommit(void *arg0, s32 arg1) {
    s32 result;
    u8 *panel;

    panel = (u8 *)arg0 + 0xD18;
    func_8130C334(panel);
    func_81311AAC((u8 *)arg0 + 0x74, arg1);
    func_8130F2C4(arg0, arg1);
    func_8130B3B8(panel, (u8 *)arg0 + 0x1A154);
    result = func_8130CDD4(panel);
    if (result < 0) {
        if (func_813000E4(arg0) != 0 && ((Fragment14SetupState *)arg0)->slot == 0) {
            ((Fragment14SetupState *)arg0)->data[0x954] = 0;
        }
        func_813000BC(arg0, 0);
    } else if (result > 0) {
        if (func_813000E4(arg0) != 0 && ((Fragment14SetupState *)arg0)->slot == 0) {
            ((Fragment14SetupState *)arg0)->data[0x954] = result - 1;
        }
        if (func_8160A844(((Fragment14SetupState *)arg0)->data + ((Fragment14SetupState *)arg0)->slot * 0x240,
                         ((Fragment14SetupState *)arg0)->data + ((Fragment14SetupState *)arg0)->slot * 12 + 0x904,
                         *(s8 *)(((Fragment14SetupState *)arg0)->data + 0x944), result - 1) != 0) {
            ((Fragment14SetupState *)arg0)->data[0x955] |= 1 << ((Fragment14SetupState *)arg0)->slot;
        } else {
            ((Fragment14SetupState *)arg0)->data[0x955] &= ~(1 << ((Fragment14SetupState *)arg0)->slot);
        }
        if (*(s8 *)(((Fragment14SetupState *)arg0)->data + ((Fragment14SetupState *)arg0)->slot * 12 + 0x904) == 0) {
            HAL_Strcpy((s8 *)((Fragment14SetupState *)arg0)->data + ((Fragment14SetupState *)arg0)->slot * 12 + 0x904,
                       func_8004C874(0xF, *(s8 *)(((Fragment14SetupState *)arg0)->data + ((Fragment14SetupState *)arg0)->slot + 0x900) + 0x62));
        }
        ((Fragment14SetupState *)arg0)->data[((Fragment14SetupState *)arg0)->slot + 0x93C] = 4;
        Fragment14_AdvanceSelectionSlot(arg0, 1);
        ((Fragment14SetupState *)arg0)->mode = 1;
    }
}

void func_8130C334(void *);
void func_81311AAC(void *, s32);
void func_8130F2C4(void *, s32);
void func_8130B3B8(void *, void *);
s32 func_8130CDD4(void *);
void func_813000BC(void *, s32);
void func_81301BDC(s32 arg0, s32 arg1) {
    s32 sub = arg0 + 0xD18;
    func_8130C334((void *)sub);
    func_81311AAC((void *)(arg0 + 0x74), arg1);
    func_8130F2C4((void *)arg0, arg1);
    func_8130B3B8((void *)sub, (void *)(arg0 + 0x1A154));
    if (func_8130CDD4((void *)sub)) {
        func_813000BC((void *)arg0, 2);
    }
}

void func_81301C54(s32 arg0, s32 arg1) {
    s32 sub = arg0 + 0xD18;
    func_8130C334((void *)sub);
    func_81311AAC((void *)(arg0 + 0x74), arg1);
    func_8130F2C4((void *)arg0, arg1);
    func_8130B3B8((void *)sub, (void *)(arg0 + 0x1A154));
    if (func_8130CDD4((void *)sub)) {
        func_813000BC((void *)arg0, 2);
    }
}

void func_81301CCC(u8 *arg0, s32 arg1) {}

void func_81301CD8(u8 *arg0, s32 arg1) {}

extern void func_81311030(s32);
extern void func_8130F7B8(s32, s32);
void func_81301CE4(s32 arg0) {
    s32 temp_a0 = arg0 + 0xF64C;
    func_81311030(temp_a0);
    func_8130F7B8(temp_a0, arg0 + 0x1A154);
}

extern void func_8130881C(s32);
extern void func_8130302C(s32, s32);
extern void func_8130DEB8(s32, s32);
extern void func_813060C8(s32, s32);
extern void func_81311650(s32, s32);
void func_81301D28(s32 arg0, s32 arg1)
{
  func_8130881C(arg0 + 0xDA8);
  func_8130302C(arg0 + 0x15370, arg1);
  func_8130DEB8(arg0, arg1);
  func_813060C8(arg0 + 0xD18, arg1);
  func_81311650(arg0 + 0x74, arg1);
  if (!arg1)
  {
  }
}

void func_81301D94(s32 arg0) {
    s32 temp_a0 = arg0 + 0xF64C;
    func_81311030(temp_a0);
    func_8130F7B8(temp_a0, arg0 + 0x1A154);
}

extern void Fragment14_DrawSelectionPanel(u8 *, void *);

void func_81301DD8(s32 arg0, s32 arg1) {
    Fragment14_DrawSelectionPanel((u8 *)arg0 + 0xF630, (void *)arg1);
    func_81311650(arg0 + 0x74, arg1);
}

void func_81301E14(s32 arg0, s32 arg1)
{
  func_8130881C(arg0 + 0xDA8);
  func_8130302C(arg0 + 0x15370, arg1);
  if (arg1)
  {
  }
  func_8130DEB8(arg0, arg1);
  func_813060C8(arg0 + 0xD18, arg1);
  func_81311650(arg0 + 0x74, arg1);
 dummy_label_321312: ;
}

extern void func_8130CB5C(s32);
void func_81301E80(s32 arg0, s32 arg1) {
    func_8130CB5C(arg0 + 0xD18);
    func_81311650(arg0 + 0x74, arg1);
    func_8130DEB8(arg0, arg1);
}

void func_81301EC4(s32 arg0, s32 arg1) {
    func_8130CB5C(arg0 + 0xD18);
    func_81311650(arg0 + 0x74, arg1);
    func_8130DEB8(arg0, arg1);
}

void func_81301F08(s32 arg0, s32 arg1) {
    func_8130CB5C(arg0 + 0xD18);
    func_81311650(arg0 + 0x74, arg1);
    func_8130DEB8(arg0, arg1);
}

void func_81301F4C(u8 *arg0, s32 arg1) {}

void func_81301F58(u8 *arg0, s32 arg1) {}

void Fragment14_EnterSelectionState(void *arg0, s32 arg1) {
    ((Fragment14SetupState *)arg0)->pending = 0;
    ((Fragment14SetupState *)arg0)->requested = arg1;
    ((Fragment14SetupState *)arg0)->active = arg1;
    *(Fragment14Position *)((u8 *)arg0 + 0x1A15C) = *(Fragment14Position *)((u8 *)arg0 + 0x1A154);
    switch (((Fragment14SetupState *)arg0)->active) {
    case 0: func_81300E34(arg0); break;
    case 1: Fragment14_InitSelectionAdvance(arg0); break;
    case 2: Fragment14_InitSelectionPreview(arg0); break;
    case 3: func_813010B0(arg0); break;
    case 4: Fragment14_InitSelectedController(arg0); break;
    case 5: Fragment14_InitSelectionPanelMode0(arg0); break;
    case 6: Fragment14_InitSelectionPanelMode2(arg0); break;
    case 7: Fragment14_InitSelectionPanelMode1(arg0); break;
    case 8: func_813014D0(arg0); break;
    case 9: func_8130150C(arg0); break;
    default: break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_F81B0/func_8130209C.s")

void Fragment14_DrawSelectionState(void *arg0, s32 arg1) {
    switch (((Fragment14SetupState *)arg0)->active) {
    case 0: func_81301CE4((s32)arg0); break;
    case 1: func_81301D28((s32)arg0, arg1); break;
    case 2: func_81301DD8((s32)arg0, arg1); break;
    case 3: func_81301D94((s32)arg0); break;
    case 4: func_81301E14((s32)arg0, arg1); break;
    case 5: func_81301E80((s32)arg0, arg1); break;
    case 6: func_81301EC4((s32)arg0, arg1); break;
    case 7: func_81301F08((s32)arg0, arg1); break;
    case 8: func_81301F4C((u8 *)arg0, arg1); break;
    case 9: func_81301F58((u8 *)arg0, arg1); break;
    default: break;
    }
}

extern s32 func_80055A74(s32);
extern s32 Deck_FindFirstFreeTeamSlot(void);
s32 func_81302290(void *arg0) {
    s8 value = *(s8 *)((u8 *)(*(void **)((u8 *)arg0 + 0x1A148)) + 0x944);
    if (value < 0) {
        return 0;
    }
    func_80055A74(value);
    return Deck_FindFirstFreeTeamSlot();
}

s32 func_813022D8(void *arg0) {
    s8 value = *(s8 *)((u8 *)(*(void **)((u8 *)arg0 + 0x1A148)) + 0x944);
    return value >= 0;
}

extern s32 func_813022D8(void *);
extern void func_8160A270(void *);
extern void func_8160A384(void *, s32, s32, s32);
extern void func_80055028(void);
s32 func_813022F4(void *arg0, void *arg1) {
    typedef struct {
        u8 pad_0[0x1A13C];
        s32 status;
    } State;
    s32 sp1C;
    s8 value;
    if (func_813022D8(arg0) != 0) {
        sp1C = func_81302290(arg0);
        if (sp1C < 0xA) {
            func_8160A270(arg1);
            value = *(s8 *)((u8 *)(*(void **)((u8 *)arg0 + 0x1A148)) + 0x944);
            func_8160A384(arg1, value, sp1C, *(s32 *)((u8 *)arg0 + 0x1A168));
            ((State *)arg0)->status = 1;
            func_80055028();
            return 1;
        }
    }
    return 0;
}
#endif
