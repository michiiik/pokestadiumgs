#include "global.h"


#ifdef VERSION_US
typedef struct {
    u8 unk_00;
    u8 selected_side;
    u8 moves[2];
    u8 unk_04[6];
    u16 amount_0A[2];
    u16 amount_0E[2];
    u16 amount_12[2];
    u16 amount_16[2];
    u16 amount_1A[2];
    u8 unk_1E[0x34 - 0x1E];
    u32 scale_34[2];
} Fragment79EffectView;

extern void func_84149D54(void *, u8, u8);
extern void func_84149D0C(void *);
void func_8414CA00(s32 arg0, u8 arg1, u8 arg2) {
    u8 rec[0x20];
    u8 pad[8];

    func_84149D54(rec, arg1, arg2);
    func_84149D0C(rec);
    if (*(u16 *)(*(u8 **)(rec + 0x14) + 0x42) > 0) {
        *(u16 *)((u8 *)(u32)arg0 + arg1 * 2 + 0x1A) = *(s32 *)(rec + 0xC);
    } else {
        *(u16 *)((u8 *)(u32)arg0 + arg1 * 2 + 0xE) = *(s32 *)(rec + 0xC);
    }
}

typedef struct {
    u8 unk_00[12];
    s32 amount;
    const u8 *mon;
    const u8 *opponent;
    const u8 *side_record;
    const u8 *other_record;
} Fragment79DamageCalculation;
void BattleEffects_PlanCalculatedRecovery(void *state, u8 side, u8 move) {
    s32 half;
    s32 missing;
    Fragment79DamageCalculation calculation;
    u8 *selected;

    func_84149D54(&calculation, side, move);
    func_84149D0C(&calculation);
    half = calculation.amount >> 1;
    if (*(u16 *)(calculation.opponent + 0x42) == 0) {
        missing = *(u16 *)(calculation.mon + 0x2A) - *(u16 *)(calculation.mon + 0x28);
        selected = (u8 *)((u32)state + side * 2 + 4);
        *(u16 *)(selected + 0xA) = calculation.amount;
        if (half < missing) {
            *(u16 *)(selected + 0x12) = half;
        } else {
            *(u16 *)(selected + 0x12) = missing;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414CB10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414CB74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414CD18.s")

extern u8 *func_84154B64(u8);
extern u16 func_84148560(u16, u16, u8);
void func_8414CDB8(u8 *arg0, u8 arg1, u8 arg2) {
    u8 *value;
    value = func_84154B64(arg1);
    *(u16 *)(arg0 + arg1 * 2 + 0x16) =
        func_84148560(*(u16 *)(value + 0x28), *(u16 *)(value + 0x2A), arg2);
}

extern u8 * func_84154B64(u8);
void BattleEffects_PlanSharedHP(void *state, u8 side) {
    s32 own_hp;
    s32 other_hp;
    const u8 *opponent;
    const u8 *mon;
    Fragment79EffectView *view;
    s32 average;
    s32 target;
    s32 own_delta;
    s32 other_delta;

    mon = func_84154B64(side);
    opponent = func_84154B64((u8)(1 - side));
    view = (Fragment79EffectView *)((u8 *)state + 4);
    own_hp = *(u16 *)(mon + 0x28);
    other_hp = *(u16 *)(opponent + 0x28);
    average = (own_hp + other_hp) >> 1;
    if (average < *(u16 *)(mon + 0x2A)) {
        target = average;
    } else {
        target = *(u16 *)(mon + 0x2A);
    }
    own_delta = target - own_hp;
    if (average < *(u16 *)(opponent + 0x2A)) {
        target = average;
    } else {
        target = *(u16 *)(opponent + 0x2A);
    }
    other_delta = target - other_hp;
    if (own_delta > 0) {
        view->amount_12[side] = own_delta;
    } else {
        view->amount_1A[side] = -own_delta;
    }
    if (other_delta > 0) {
        view->amount_0E[side] = other_delta;
    } else {
        view->amount_0A[side] = -other_delta;
    }
}

void func_8414CEE0(s32 arg0, u8 arg1, u8 arg2) {
    u8 rec[0x20];
    u8 *value;

    func_84149D54(rec, arg1, arg2);
    func_84149D0C(rec);
    value = (u8 *)(u32)arg0 + arg1 * 2 + 4;
    if (*(u16 *)(*(u8 **)(rec + 0x14) + 0x42) > 0) {
        *(u16 *)(value + 0x16) = *(s32 *)(rec + 0xC);
    } else {
        *(u16 *)(value + 0xA) = *(s32 *)(rec + 0xC);
    }
    *(u16 *)(value + 0x1E) = *(s32 *)(rec + 0xC) >> 3;
}

void func_8414CF74(s32 arg0, u8 arg1, u8 arg2) {
    u8 rec[0x20];
    u8 *value;

    func_84149D54(rec, arg1, arg2);
    func_84149D0C(rec);
    value = (u8 *)(u32)arg0 + arg1 * 2 + 4;
    if (*(u16 *)(*(u8 **)(rec + 0x14) + 0x42) > 0) {
        *(u16 *)(value + 0x16) = *(s32 *)(rec + 0xC);
    } else {
        *(u16 *)(value + 0xA) = *(s32 *)(rec + 0xC);
    }
    *(u16 *)(value + 0x1A) = *(s32 *)(rec + 0xC) >> 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D008.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D198.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D348.s")

extern u8 func_80062D20(u8 arg0);
void func_8414D51C(s32 arg0, u8 arg1) {
    u8 *value;
    u8 move;

    value = func_84154B64(arg1);
    move = *((u8 *)(u32)arg0 + arg1 + 6);
    switch (func_80062D20(move)) {
        case 0x27:
        case 0x4B:
        case 0x97:
            if (value[0x17] & 0x10) {
                value[0x17] &= ~0x10;
            } else {
                value[0x17] |= 0x10;
            }
            break;
        case 0x9B:
            if (value[0x17] & 0x10) {
                value[0x17] &= ~0x70;
            } else {
                value[0x17] |= 0x10;
                switch (move) {
                    case 0x13:
                        value[0x17] |= 0x40;
                        break;
                    case 0x5B:
                        value[0x17] |= 0x20;
                        break;
                }
            }
            break;
    }
}

void func_8414D610(s32 arg0, u8 arg1) {
    u8 *value;
    s32 diff;

    value = func_84154B64(arg1);
    diff = *(u16 *)(value + 0x28) - *(u16 *)((u8 *)(u32)arg0 + arg1 * 2 + 0x26);
    if (diff < 0) {
        *(u16 *)(value + 0x28) = 0;
    } else if (diff > *(u16 *)(value + 0x2A)) {
        *(u16 *)(value + 0x28) = *(u16 *)(value + 0x2A);
    } else {
        *(u16 *)(value + 0x28) = diff;
    }
}

s32 func_84156618(u8 arg0, u8 arg1, u8 arg2);
u8 *func_84154B30(u8 arg0);
u8 func_80062D20(u8 arg0);
u8 func_84154B18(void);
s32 func_84156618(u8 arg0, u8 arg1, u8 arg2);
u8 *func_84154B30(u8 arg0);
u8 func_80062D20(u8 arg0);
u8 func_84154B18(void);
s32 func_8414D680(u8 arg0, u8 arg1) {
    s32 sp1C;
    u8 temp_v0;

    sp1C = 0;
    if (func_84156618(arg0, (*(u8 *)((u8 *)(func_84154B30(arg0)) + (1))), 0x10U) != 0) {
        temp_v0 = func_80062D20(arg1);
        switch (temp_v0) {                          /* irregular */
        case 0x27:
        case 0x4B:
        case 0x91:
            sp1C = 1;
            break;
        case 0x97:
            if (func_84154B18() != 2) {
                sp1C = 1;
            }
            break;
        }
    }
    return sp1C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D720.s")

extern u8 func_84154B24(void);
extern void func_8414FC30(void *, u8);
extern void func_84150268(void *, u8);
extern void func_8414D198(void *, u8);
extern void func_84153E28(void *, u8);
extern u8 func_80062D20(u8);
void BattleEffects_CopyOpposingMove(void *state) {
    u8 side;
    u8 other;
    const u8 *mon;
    Fragment79EffectView *view;

    side = func_84154B24();
    other = 1 - side;
    mon = func_84154B64(other);
    view = (Fragment79EffectView *)((u8 *)state + 4);

    if (view->selected_side == side) {
        view->moves[side] = mon[0x24];
    } else {
        view->moves[side] = view->moves[other];
    }
    func_8414FC30(state, side);
    func_84150268(state, side);
    func_8414D198(state, side);
    func_84153E28(state, side);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414D9B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414DA70.s")

extern s32 func_800630C0(u8);
extern s32 func_84155544(u8 *, u8);
void BattleEffects_AddMoveTypeResponse(Fragment79EffectView *view, u8 side) {
    u8 other;
    const u8 *selected;

    selected = (const u8 *)view + side;
    if (selected[2] == 0x44 && func_800630C0(view->moves[(u8)(1 - side)]) != 0) {
        other = 1 - side;
        if (func_84155544(func_84154B64(other), 0x8) == 0) {
            view->amount_1A[other] = view->amount_0A[other] * 2 + view->amount_1A[other];
            if (side == func_84154B24()) {
                view->unk_00 |= 2;
            }
        }
    } else if (selected[2] == 0xF3 && func_800630C0(view->moves[(u8)(1 - side)]) == 0) {
        other = 1 - side;
        if (func_84155544(func_84154B64(other), 0x1B) == 0) {
            view->amount_1A[other] = view->amount_0A[other] * 2 + view->amount_1A[other];
            if (side == func_84154B24()) {
                view->unk_00 |= 2;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414DC58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414DD94.s")

void BattleEffects_SetOpposingAmountFromHP(void *state) {
    u8 side;
    u8 other;
    const u8 *mon;
    const u8 *opponent;
    Fragment79EffectView *view;

    side = func_84154B24();
    other = 1 - side;
    mon = func_84154B64(side);
    opponent = func_84154B64(other);
    view = (Fragment79EffectView *)((u8 *)state + 4);

    if (view->selected_side == side) {
        if (*(u16 *)(mon + 0x28) < view->amount_0A[other]) {
            view->amount_1A[other] = *(u16 *)(opponent + 0x28);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414E2A8.s")

void BattleEffects_ClearInsufficientAmount(void *state) {
    u8 side;
    Fragment79EffectView *view;

    side = func_84154B24();
    view = (Fragment79EffectView *)((u8 *)state + 4);

    if (view->selected_side == side) {
        if (view->amount_0A[(u8)(1 - side)] < view->amount_1A[side]) {
            view->amount_0A[side] = 0;
        }
    } else {
        if (view->amount_0A[(u8)(1 - side)] * 2 < view->amount_1A[side]) {
            view->amount_0A[side] = 0;
        }
    }
}

void BattleEffects_DoubleConditionalScale(void *state) {
    u8 side;
    u8 other;
    const u8 *mon;
    Fragment79EffectView *view;

    side = func_84154B24();
    other = 1 - side;
    mon = func_84154B64(side);
    func_84154B64(other);
    view = (Fragment79EffectView *)((u8 *)state + 4);

    if (view->selected_side == side) {
        if (view->amount_12[side] + *(u16 *)(mon + 0x28) <
                *(u16 *)(mon + 0x2A) &&
            view->amount_0A[other] < view->amount_12[side]) {
            view->scale_34[side] *= 2;
        }
    }
}

extern u8 func_84154B24();
extern s32 func_841556C4(u8 *, u8);
void func_8414E658(s32 arg0)
{
  struct LocalState
  {
    u8 pad[0xA];
    u16 amount[2];
  };
  u8 current;
  u8 other;
  u8 *value;
  u8 *opponent;
  struct LocalState *state;
  current = func_84154B24();
  other = 1 - current;
  value = func_84154B64(current);
  opponent = func_84154B64(other);
  state = (struct LocalState *) (((((((u32) arg0) & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF) + 4);
  if (current == (*(((u8 *) ((u32) arg0)) + 5)))
  {
    if (state->amount[other] < (*((u16 *) (value + 0x28))))
    {
      if (func_841556C4(opponent, 0x6F) == 0)
      {
        state->amount[current] *= 3;
      }
    }
  }
  else
    if ((state->amount[other] * 2) < (*((u16 *) (value + 0x28))))
  {
    if (func_841556C4(opponent, 0x6F) == 0)
    {
      state->amount[current] *= 3;
    }
  }
}

void func_8414E760(s32 arg0) {
    u8 side;
    u8 other;
    u8 pad[4];
    u8 *rec;
    side = func_84154B24();
    other = 1 - side;
    func_84154B64(side);
    rec = func_84154B64(other);
    if (func_841556C4(rec, 0x6F) != 0 || func_841556C4(rec, 0x74) != 0)
        *(u8 *)((u8 *)(u32)arg0 + side + 0xA) = 0;
}

void BattleEffects_DoubleScaleForIncomingAmount(void *state) {
    u8 side;
    u8 other;
    const u8 *mon;
    Fragment79EffectView *view;

    side = func_84154B24();
    other = 1 - side;
    mon = func_84154B64(side);
    func_84154B64(other);
    view = (Fragment79EffectView *)((u8 *)state + 4);

    if (*(u16 *)(mon + 0x28) < view->amount_0A[other] ||
        (view->selected_side == other && *(u16 *)(mon + 0x28) < view->amount_0A[other] * 2)) {
        view->scale_34[side] *= 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414E880.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BC290/func_8414EA4C.s")

void BattleEffects_ApplyOpposingByteWeight(s32 state) {
    u8 side;
    u8 other;
    s32 divisor;

    side = func_84154B24();
    other = 1 - side;
    divisor = 255;
    *((u8 *)(u32)state + side + 0xA) =
        *((u8 *)(u32)state + side + 0xA) *
        (divisor - *((u8 *)(u32)state + other + 0xC)) / divisor;
}

extern void func_8414DC58(s32, u8);
extern void func_8414EA4C(s32);
extern void BattleEffects_ApplyOpposingByteWeight(s32);
void func_8414EC18(s32 arg0) {
    u8 current;
    u8 other;

    current = func_84154B24();
    other = 1 - current;
    func_84154B64(current);
    func_84154B64(other);
    switch (func_80062D20(*((u8 *)(u32)arg0 + other + 6))) {
    case 0x6F:
        BattleEffects_ApplyOpposingByteWeight(arg0);
        break;
    case 0x59:
    case 0x90:
        func_8414DC58(arg0, other);
        break;
    case 0x30:
        *(u16 *)((u8 *)(u32)arg0 + other * 2 + 0x1E) = 0;
        break;
    case 0x9B:
        func_8414EA4C(arg0);
        break;
    }
}

void BattleEffects_HalveAmountsForStatus(void *state) {
    u8 side;
    u8 other;
    const u8 *opponent;
    Fragment79EffectView *view;

    side = func_84154B24();
    other = 1 - side;
    func_84154B64(side);
    opponent = func_84154B64(other);
    view = (Fragment79EffectView *)((u8 *)state + 4);
    if (*(u16 *)(opponent + 0x26) & 0x27) {
        view->amount_0A[side] >>= 1;
        view->amount_16[side] >>= 1;
    }
}

extern void func_8414D720(s32, u8);
extern void func_8414E880(s32);
extern void func_8414EC18(s32);
u8 func_84154B24();
void func_8414ED5C(s32 arg0) {
    u8 sp1F;
    u8 sp1E;
    u8 temp_v0;

    temp_v0 = func_84154B24();
    sp1F = temp_v0;
    sp1E = 1 - temp_v0;
    func_8414E880(arg0);
    func_8414EC18(arg0);
    func_8414D720(arg0, sp1F);
    func_8414D720(arg0, sp1E);
}

void func_8414EDB4(s32 arg0) {
    u8 sp27;
    u8 sp26;
    u8 temp_v0;

    temp_v0 = func_84154B24();
    sp27 = temp_v0;
    sp26 = 1 - temp_v0;
    func_8414E880(arg0);
    func_8414EC18(arg0);
    BattleEffects_HalveAmountsForStatus(arg0);
    func_8414D720(arg0, sp27);
    func_8414D720(arg0, sp26);
}
#endif
