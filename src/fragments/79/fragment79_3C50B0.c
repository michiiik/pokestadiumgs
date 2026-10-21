#include "global.h"


#ifdef VERSION_US
typedef struct {
    u8 flags;
    u8 moves[4];
    u8 unk_05[6];
    u8 unk_0B;
    u8 unk_0C[2];
    u16 attack, defense, speed, special_attack, special_defense;
} MoveStatRecord;
typedef struct {
    u8 flags, phase, unk_02, moves[4], unk_07;
    u16 attack, defense, speed, special_attack, special_defense;
    MoveStatRecord records[12];
} MoveStatSide;
extern u8 *D_841951F8[];
extern u8 *D_84195200[];
extern u8 *D_84195208[];
extern u8 D_8419EE00[];
extern void func_84125508(u8 *, u16, u8);
void BattleMoveState_RefreshSelectedStats(u8 side) {
    u8 *stat_base;
    u8 selected_record;

    selected_record = D_841951F8[side][10];
    stat_base = (u8 *)((MoveStatSide *)D_8419EE00 + side) + selected_record * sizeof(MoveStatRecord);
    func_84125508((u8 *)&((MoveStatSide *)D_8419EE00 + side)->attack, *(u16 *)(stat_base + 32), D_84195208[side][30]);
    func_84125508((u8 *)&((MoveStatSide *)D_8419EE00 + side)->defense, *(u16 *)(stat_base + 34), D_84195208[side][31]);
    func_84125508((u8 *)&((MoveStatSide *)D_8419EE00 + side)->speed, *(u16 *)(stat_base + 36), D_84195208[side][32]);
    func_84125508((u8 *)&((MoveStatSide *)D_8419EE00 + side)->special_attack, *(u16 *)(stat_base + 38), D_84195208[side][33]);
    func_84125508((u8 *)&((MoveStatSide *)D_8419EE00 + side)->special_defense, *(u16 *)(stat_base + 40), D_84195208[side][34]);
    stat_base = (u8 *)((MoveStatSide *)D_8419EE00 + side);
    if (D_84195200[side][36] & 0x40) {
        *(u16 *)(stat_base + 12) >>= 2;
    }
    if (D_84195200[side][36] & 0x10) {
        *(u16 *)(stat_base + 8) >>= 1;
    }
    ((MoveStatSide *)D_8419EE00)[side].records[D_841951F8[side][10]].unk_0B = D_84195200[side][1];
    ((MoveStatSide *)D_8419EE00)[1 - side].records[D_841951F8[1 - side][10]].unk_0B = D_84195200[1 - side][1];
}
#endif

#ifdef VERSION_US
extern void BattleMoveState_RefreshSelectedStats(u8);
void func_84155A1C(void) {
    BattleMoveState_RefreshSelectedStats(0);
    BattleMoveState_RefreshSelectedStats(1);
}
#endif

#ifdef VERSION_US
void BattleMoveState_CopySelectedMoves(u8 side) {
    u8 *base;
    u8 *current;
    u8 *selected;
    s32 i;

    base = D_8419EE00 + side * 0x132;
    current = base + 2;
    selected = base;
    selected += D_841951F8[side][0xA] * 0x18;
    selected += 0x12;
    for (i = 0; i < 4; i++) {
        current[i + 1] = selected[i + 1];
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_84155AC4.s")
#endif

#ifdef VERSION_US
extern u8 func_80062D20(u8);
extern void func_84155AC4(u8, u8, u8, u8);
extern void func_84156674(u8, u8, u8);
void BattleMoveState_ApplySelectedMoveEffects(u8 side, u8 move) {
    u8 effect;
    u8 other;
    u8 selected;
    u8 opposing;

    effect = func_80062D20(move);
    other = 1 - side;
    selected = D_841951F8[side][0xA];
    opposing = D_841951F8[other][0xA];
    switch (effect) {
        case 0x59:
            func_84156674(side, selected, 0x4);
            break;
        case 0x90:
            func_84156674(side, selected, 0x8);
            break;
        case 0x62:
            func_84156674(side, selected, 0x10);
            break;
    }
    func_84155AC4(side, selected, opposing, move);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_84155CB8.s")
#endif

#ifdef VERSION_US
extern u8 D_8419EE17[];
u8 func_84155D5C(u8 arg0, u8 arg1, u8 arg2) {
    return D_8419EE17[arg0 * 0x132 + arg1 * 0x18 + arg2];
}
#endif

#ifdef VERSION_US
extern u8 func_84154B24(void);
extern s32 func_800630C0(u8);
extern u8 func_80062D5C(u8);
extern u8 D_8419EE03[];
u8 BattleMoveState_FindStrongestMove(u8 side, u8 category) {
    u8 active_side;
    u16 best_power;
    u8 best_move;
    s32 slot;
    u8 move;

    active_side = func_84154B24();
    best_move = 0;
    best_power = 1;
    for (slot = 0; slot < 4; slot++) {
        if (active_side == side) {
            move = D_84195208[active_side][slot + 5];
        } else {
            move = ((MoveStatSide *)D_8419EE00)[side].moves[slot];
        }
        if (move != 0xFF) {
            switch (category) {
                case 0:
                    if (func_800630C0(move) && best_power < func_80062D5C(move)) {
                        best_power = func_80062D5C(move);
                        best_move = move;
                    }
                    break;
                case 1:
                    if (!func_800630C0(move) && best_power < func_80062D5C(move)) {
                        best_power = func_80062D5C(move);
                        best_move = move;
                    }
                    break;
            }
        }
    }
    return best_move;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_84155F28.s")
#endif

#ifdef VERSION_US
void BattleMoveState_RefreshSelectedMoves(u8 side) {
    u8 *base;
    u8 *current;
    u8 *selected;
    s32 i;

    base = D_8419EE00 + side * 0x132;
    current = base + 2;
    selected = base;
    selected += D_841951F8[side][0xA] * 0x18;
    selected += 0x12;
    for (i = 0; i < 4; i++) {
        current[i + 1] = selected[i + 1];
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C50B0/func_841562BC.s")
#endif

#ifdef VERSION_US
extern u8 D_8419EE01[];
extern void func_84155F28(u8, u8);
void func_84156464(u8 arg0) {
    s32 i;
    D_8419EE01[arg0 * 0x132] = 1;
    i = 0;
    while (i < D_841951F8[arg0][7]) {
        func_84155F28(arg0, i);
        i++;
    }
    BattleMoveState_RefreshSelectedMoves(arg0);
}
#endif

#ifdef VERSION_US
extern void func_84156464(u8);
void func_84156510(void) {
    s32 i;
    i = 0;
    while (i != 2) {
        func_84156464(i);
        i += 1;
    }
}
#endif

#ifdef VERSION_US
u8 *func_84156550(void) {
    return D_8419EE00;
}
#endif

#ifdef VERSION_US
u8 *func_8415655C(u8 arg0) {
    return D_8419EE00 + arg0 * 0x132;
}
#endif

#ifdef VERSION_US
u8 *func_84156590(u8 arg0, u8 arg1) {
    return D_8419EE00 + arg0 * 0x132 + arg1 * 0x18 + 0x12;
}
#endif

#ifdef VERSION_US
u8 *func_841565E0(u8 arg0) {
    return D_8419EE00 + arg0 * 0x132 + 2;
}
#endif

#ifdef VERSION_US
extern u8 D_8419EE12[];
s32 func_84156618(u8 arg0, u8 arg1, u8 arg2) {
    return (D_8419EE12[arg0 * 0x132 + arg1 * 0x18] & arg2) != 0;
}
#endif

#ifdef VERSION_US
void func_84156674(u8 arg0, u8 arg1, u8 arg2) {
    D_8419EE00[arg0 * 0x132 + arg1 * 0x18 + 0x12] |= arg2;
}
#endif

#ifdef VERSION_US
void func_841566D0(u8 arg0, u8 arg1, u8 arg2) {
    D_8419EE00[arg0 * 0x132 + arg1 * 0x18 + 0x12] &= ~arg2;
}
#endif

#ifdef VERSION_US
void func_84156730(u8 arg0, u8 arg1) {
    D_8419EE00[arg0 * 0x132] |= arg1;
}
#endif

#ifdef VERSION_US
s32 func_84156774(u8 arg0, u8 arg1) {
    return (D_8419EE00[arg0 * 0x132] & arg1) != 0;
}
#endif

#ifdef VERSION_US
void func_841567B8(u8 arg0, u8 arg1) {
    D_8419EE00[arg0 * 0x132] &= ~arg1;
}
#endif

#ifdef VERSION_US
s32 func_84156800(s32 arg0, s32 arg1) {
    return arg0;
}
#endif

void func_8415680C(void) {
}

#ifdef VERSION_US
void func_84156814(void) {}
#endif
