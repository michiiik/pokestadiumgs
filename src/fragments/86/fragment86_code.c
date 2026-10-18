#include "global.h"

#ifdef VERSION_US
extern u32 func_8003570C(void);
extern u8 func_844001E0(u8 *);
extern s32 func_80061B88(s32, u16);
extern s32 func_8004B7A4(s32);
extern s8 *HAL_Strcpy(s8 *, s8 *);
extern void func_800619E8(u8 *);
extern void func_80061F44(u8 *);
extern u8 *D_84400B28[];
const char D_84400C40[] = "SATORU";
extern u8 func_80062E10(u8);
extern u8 MoveSelection_ChooseSlot_fragment86(u8 *, u8 *, u8);

// Seven bytes copied from the original trainer-name string "SATORU".
typedef struct Fragment86TrainerPrefix {
    u8 bytes[7];
} Fragment86TrainerPrefix;
#endif

#ifdef VERSION_US
extern u8 D_84400B3F[];
s32 fragment86_main(u8 arg0) { s32 result = 0xA0; if (arg0 > 0 && arg0 < 0xFC) { result = (D_84400B3F[arg0] & 0xE0) & 0xFF; } return result; }
#endif

#ifdef VERSION_US
s32 func_84400058(u8 arg0) { s32 result = 0; if (arg0 > 0 && arg0 < 0xFC) { result = (D_84400B3F[arg0] & 0x1F) & 0xFF; } return result; }
#endif

#ifdef VERSION_US
void func_84400090(u8 *arg0) {
    *arg0 = 0;
}
#endif

#ifdef VERSION_US
void func_84400098(u8 *arg0, u8 arg1) {
    if (arg0 != NULL) {
        arg0[++arg0[0]] = arg1;
    }
}
#endif

#ifdef VERSION_US
u8 ByteList_ChooseRandom_fragment86(u8 *list) {
    u32 count;
    f32 fraction;
    u8 index;

    fraction = (f32)((f64)func_8003570C() / 4294967296.0);
    //!bug The count is read before the null-pointer guard.
    count = list[0];
    index = (u32)((f32)count * fraction) + 1;
    if (count == 0 || list == NULL) {
        return 0;
    }
    return list[index];
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_844001E0.s")
#endif

#ifdef VERSION_US
u8 func_84400338(u8 *arg0) {
    return *arg0;
}
#endif

void func_84400340(void) {
}

#ifdef VERSION_US
s32 ByteList_FindIndex_fragment86(u8 *list, u8 value) {
    s32 i;

    for (i = 1; i <= list[0]; i++) {
        if (list[i] == value) {
            return (u8)i;
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_84400394.s")
#endif

#ifdef VERSION_US
extern u8 func_80062D20(u8);
extern u8 func_80062D98(u8);
extern u8 func_8006397C(u8);
extern u8 func_800639C0(u8);
extern u8 func_80063454(u8, u8, u8, s32);
extern u32 D_84400F30;
extern u8 D_84400F38[];
extern u8 D_84401038[];
extern u8 D_84401138[];
extern s32 ByteList_FindIndex_fragment86(u8 *list, u8 value);
extern s32 func_84400058(u8 arg0);
extern void func_84400098(u8 *arg0, u8 arg1);
// Route unused moves into preferred or fallback pools using effect and type effectiveness.
void MovePools_ClassifyCandidate_fragment86(u8 move, u8 *mon) {
    u8 effect;
    u8 move_type;
    u8 first_type;
    u8 second_type;
    u8 effectiveness;
    u8 selected;

    effect = func_80062D20(move);
    move_type = func_80062D98(move);
    first_type = func_8006397C(mon[0]);
    second_type = func_800639C0(mon[0]);
    effectiveness = func_80063454(move_type, first_type, second_type, 1);
    selected = 0;
    if (((1U << func_84400058(move)) & D_84400F30) == 0 && ByteList_FindIndex_fragment86(D_84401138, move) == 0) {
        switch (effect) {
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 17:
        case 26:
        case 27:
        case 28:
        case 29:
        case 31:
        case 33:
        case 34:
        case 36:
        case 39:
        case 40:
        case 41:
        case 42:
        case 44:
        case 45:
        case 48:
        case 66:
        case 68:
        case 69:
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 77:
        case 80:
        case 81:
        case 84:
        case 87:
        case 88:
        case 92:
        case 99:
        case 101:
        case 103:
        case 104:
        case 105:
        case 107:
        case 108:
        case 117:
        case 119:
        case 121:
        case 122:
        case 123:
        case 125:
        case 126:
        case 128:
        case 129:
        case 138:
        case 139:
        case 140:
        case 145:
        case 146:
        case 147:
        case 149:
        case 150:
        case 151:
        case 152:
        case 155:
            if (effectiveness >= 10) {
                func_84400098(D_84400F38, move);
                selected = 1;
            }
            break;
        case 38:
        case 67:
        case 89:
        case 91:
        case 106:
        case 144:
            if (effectiveness > 0) {
                func_84400098(D_84400F38, move);
                selected = 1;
            }
            break;
        default:
            func_84400098(D_84400F38, move);
            selected = 1;
            break;
        }
    }
    if (selected == 0) {
        func_84400098(D_84401038, move);
    }
}
#endif

#ifdef VERSION_US
extern u8 ByteList_ChooseRandom_fragment86(u8 *list);
extern s32 fragment86_main(u8 arg0);
extern s32 func_800643CC(s32, s32, s32);
extern void func_84400090(u8 *arg0);
extern u8 func_84400338(u8 *arg0);
extern void MovePools_ClassifyCandidate_fragment86(u8 move, u8 *mon);
// Prefer eligible moves for this slot, then record the chosen move and its group.
u8 MoveSelection_ChooseSlot_fragment86(u8 *mon, u8 *other, u8 slot) {
    s32 i;
    u8 move;
    s32 group;

    func_84400090(D_84400F38);
    func_84400090(D_84401038);
    for (i = 1; i < 252; i++) {
        move = i;
        if (func_800643CC(mon[0], move & 0xFF, mon[29]) != 0) {
            switch (fragment86_main(move)) {
            case 0x20:
                if (slot == 0) MovePools_ClassifyCandidate_fragment86(move, other);
                else func_84400098(D_84401038, move);
                break;
            case 0x40:
                if (slot != 0) MovePools_ClassifyCandidate_fragment86(move, other);
                else func_84400098(D_84401038, move);
                break;
            case 0:
                MovePools_ClassifyCandidate_fragment86(move, other);
                break;
            case 0x60:
            case 0x80:
                func_84400098(D_84401038, move);
                break;
            }
        }
    }
    if (func_84400338(D_84400F38) > 0) {
        i = ByteList_ChooseRandom_fragment86(D_84400F38);
    } else {
        i = ByteList_ChooseRandom_fragment86(D_84401038);
    }
    if (i != 0) {
        move = i;
        group = func_84400058(move);
        if (group != 0) {
            D_84400F30 |= 1U << (u8)group;
        }
        func_84400098(D_84401138, move);
    }
    return i;
}
#endif

#ifdef VERSION_US
void MoveSelection_AssignThree_fragment86(u8 *mon, u8 *other) {
    s32 i;
    u8 *p;
    u8 result;

    switch (mon[0]) {
    case 132:
        mon[2] = 144;
        mon[3] = 0;
        mon[4] = 0;
        mon[5] = 0;
        break;
    case 201:
        mon[2] = 237;
        mon[3] = 0;
        mon[4] = 0;
        mon[5] = 0;
        break;
    default:
        mon[2] = MoveSelection_ChooseSlot_fragment86(mon, other, 0);
        mon[3] = MoveSelection_ChooseSlot_fragment86(mon, other, 1);
        mon[4] = MoveSelection_ChooseSlot_fragment86(mon, mon, 2);
        mon[5] = 0;
        break;
    }
    p = mon;
    for (i = 0; i != 3; i++) {
        result = func_80062E10(p[2]);
        p++;
        p[23] = result;
    }
}
#endif

#ifdef VERSION_US
void Pokemon_GenerateLevel100_fragment86(u8 *mon, u8 group) {
    mon[0] = func_844001E0(D_84400B28[group]);
    mon[29] = 100;
    *(u32 *)(mon + 8) = func_80061B88(mon[0], mon[29]);
    *(u16 *)(mon + 12) = 0xFFFF;
    *(u16 *)(mon + 14) = 0;
    *(u16 *)(mon + 16) = 0xFFFF;
    *(u16 *)(mon + 18) = 0;
    *(u16 *)(mon + 20) = 0;
    *(u16 *)(mon + 22) = func_8003570C() & 0x7FFF;
    mon[28] = 0xFF;
    HAL_Strcpy((s8 *)(mon + 52), (s8 *)func_8004B7A4(mon[0]));
    *(Fragment86TrainerPrefix *)(mon + 64) = *(Fragment86TrainerPrefix *)D_84400C40;
    func_800619E8(mon);
    func_80061F44(mon);
    if (mon[0] == 25 && (func_8003570C() & 3) == 0) {
        mon[30] |= 2;
    }
}
#endif

#ifdef VERSION_US
extern void func_80035700(u32);
extern s32 func_84400394(u32);
extern void MoveSelection_AssignThree_fragment86(u8 *mon, u8 *other);
extern void Pokemon_GenerateLevel100_fragment86(u8 *mon, u8 group);
// Generate two three-Pokemon teams, then choose moves against the opposing team.
void Teams_GenerateLevel100_fragment86(u8 *teams, u32 selector) {
    s32 j;
    s32 i;
    u8 group;
    u8 *team;
    u8 *other;

    func_80035700(osGetCount() ^ guRandom());
    group = func_84400394(selector);
    D_84400F30 = 0;
    func_84400090(D_84401138);
    for (i = 0; i < 2; i++) {
        team = teams + i * 1248;
        team[2] = 1;
        team[7] = 3;
        team[8] = 3;
        team[9] = 3;
        team[3] = 3;
        for (j = 0; j < 3; j++) {
            Pokemon_GenerateLevel100_fragment86(team + 24 + j * 88, group);
        }
    }
    team = teams;
    other = teams + 1272;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            MoveSelection_AssignThree_fragment86(team + 24 + j * 88, other + j * 88);
        }
        team += 1248;
        other -= 1248;
    }
}
#endif
