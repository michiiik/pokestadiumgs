#include "global.h"


#ifdef VERSION_US
/* Original debug strings preceding the trainer name and jump tables. */
const char D_84302A80[] = "ChkTasteWaza\n";
const char D_84302A90[] = "SetupPokeMonList\n";
const char D_84302AA4[] = "SetPokeMon\n";
const char D_84302AB0[] = "SetWaza1\n";
const char D_84302ABC[] = "SetWaza2\n";
const char D_84302AC8[] = "SetWaza3\n";
const char D_84302AD4[] = "SetWaza4\n";
const char D_84302AE0[] = "SetItem\n";
const char D_84302AEC[] = "SetupLearnWaza\n";
const char D_84302AFC[] = "ShuffleWaza\n";
const char D_84302B0C[] = "SetPP\n";
const char D_84302B14[] = "ShufflePokeMon\n";
const char D_84302B24[] = "SetPokeMonData\n";

extern u32 func_8003570C(void);
u8 HeldItem_ForSpecies_fragment81(u8 species) {
    u8 item = 0;

    switch (species) {
    case 113:
        item = 30;
        break;
    case 83:
        item = 105;
        break;
    case 104:
    case 105:
        item = 118;
        break;
    case 25:
        item = 163;
        break;
    case 132:
        item = 35;
        break;
    }
    return item;
}

extern u8 D_843023A8[]; u8 func_8430009C(void) { return D_843023A8[(func_8003570C() & 3)]; }

u8 HeldItem_ForMoveType_fragment81(u8 type) {
    u8 item = 0;

    switch (type) {
    case 0:
        if (func_8003570C() & 1) {
            item = 104;
        } else {
            item = 170;
        }
        break;
    case 1:
        item = 98;
        break;
    case 2:
        item = 77;
        break;
    case 3:
        item = 81;
        break;
    case 4:
        item = 76;
        break;
    case 5:
        item = 125;
        break;
    case 7:
        item = 88;
        break;
    case 8:
        item = 113;
        break;
    case 20:
        item = 138;
        break;
    case 21:
        item = 95;
        break;
    case 22:
        item = 117;
        break;
    case 23:
        item = 108;
        break;
    case 24:
        item = 96;
        break;
    case 25:
        item = 107;
        break;
    case 26:
        if (func_8003570C() & 1) {
            item = 144;
        } else {
            item = 151;
        }
        break;
    case 27:
        item = 102;
        break;
    case 9:
        item = 143;
        break;
    }
    return item;
}

extern u8 D_843023AC[]; u8 func_843001CC(void) { u32 value = func_8003570C(); u32 remainder = value % 10; return D_843023AC[remainder]; }

void func_84300200(u8 *arg0, u8 arg1) {
    if (arg0 != 0) {
        arg0[(u8)++arg0[0]] = arg1;
    }
}

u8 ByteList_ChooseRandom_fragment81(u8 *list) {
    u32 count;
    f32 fraction;
    u8 index;
    u32 offset;

    fraction = (f32)((f64)func_8003570C() / 4294967296.0);
    //!bug The count is read before the null-pointer guard.
    count = list[0];
    offset = (u32)((f32)count * fraction);
    index = offset + 1;
    if (count == 0 || list == NULL) {
        return 0;
    }
    return list[index];
}

u8 func_84300348(u8 *arg0) {
    return *arg0;
}

void ByteList_RemoveFirst_fragment81(u8 *list, u8 value) {
    s32 i;
    s32 j;

    if (list[0] > 0) {
        for (i = 1; i <= list[0]; i++) {
            if (list[i] == value) {
                list[i] = 0;
                list[0]--;
                break;
            }
        }
        for (j = i; j <= list[0]; j++) {
            list[j] = list[j + 1];
        }
    }
}

s32 func_843003E0(u8 *arg0, u8 arg1) {
    s32 i;

    for (i = 1; i <= arg0[0]; i++) {
        if (arg0[i] == arg1) {
            return (u8)i;
        }
    }
    return 0;
}

extern void func_84300200(u8 *, u8);
extern s32 func_843003E0(u8 *, u8);
void func_8430042C(u8 *arg0, u8 *arg1) {
    s32 i;

    if (func_843003E0(arg0, arg1[1]) != 0) {
        i = 0;
        if (arg1[2] > 0) {
            do {
                func_84300200(arg0, arg1[1]);
                i++;
            } while (i < arg1[2]);
        }
    }
}

typedef struct Fragment81MoveWeight {
    u8 selected_move;
    u8 move;
    u8 copies;
} Fragment81MoveWeight;
extern u8 D_843029DC[];
extern void func_8430042C(u8 *, u8 *);
extern u8 D_84302CA2[];
extern u8 D_84302D06[];
extern u8 D_84302D56[];
extern u8 D_84302DA6[];
extern u8 D_84302DF6[];
extern u8 D_84302E46[];
extern u8 D_84302EA0[];
extern u8 D_84302EFA[];
extern u8 D_84302F54[];
extern u8 D_84302FAE[];
extern u8 D_84302FD2[];
// The move-selection routines pass their chosen move before selecting the next slot.
void MoveLists_ApplySelectionWeights_fragment81(u8 selected_move) {
    Fragment81MoveWeight *record = (Fragment81MoveWeight *)D_843029DC;

    for (; record->selected_move != 0; record++) {
        if (record->selected_move == selected_move) {
            break;
        }
    }
    if (record->move > 0) {
        func_8430042C(D_84302CA2, (u8 *)record);
        func_8430042C(D_84302D06, (u8 *)record);
        func_8430042C(D_84302D56, (u8 *)record);
        func_8430042C(D_84302DA6, (u8 *)record);
        func_8430042C(D_84302DF6, (u8 *)record);
        func_8430042C(D_84302E46, (u8 *)record);
        func_8430042C(D_84302EA0, (u8 *)record);
        func_8430042C(D_84302EFA, (u8 *)record);
        func_8430042C(D_84302F54, (u8 *)record);
        func_8430042C(D_84302FAE, (u8 *)record);
        func_8430042C(D_84302FD2, (u8 *)record);
    }
}

typedef struct Fragment81RulePrefix {
    u8 *types;
    u8 *effects;
} Fragment81RulePrefix;

extern Fragment81RulePrefix *D_84302C9C;
extern u8 func_80062D20(u8);
s32 MoveRules_MatchesEffect_fragment81(u8 move) {
    u8 *effects = D_84302C9C->effects;

    if (effects == NULL) {
        return 0;
    }
    while (*effects != 0xFF) {
        if (*effects == func_80062D20(move)) {
            return 1;
        }
        effects++;
    }
    return 0;
}

extern u8 func_80063838(u8, u8);
s32 func_84300648(u8 arg0) {
    u16 result = 0;
    s32 index;

    for (index = 0; index < 6; index++) {
        result += func_80063838(arg0, index);
    }
    return result;
}

extern u8 func_8006397C(u8);
extern u8 func_800639C0(u8);
u8 HeldItem_IsRedundantForType_fragment81(u8 species, u8 held_item) {
    switch (held_item) {
    case 74: // PSNCUREBERRY: reject for Poison or Steel typing.
        if (func_8006397C(species) == 3 || func_800639C0(species) == 3) {
            return 1;
        }
        if (func_8006397C(species) == 9 || func_800639C0(species) == 9) {
            return 1;
        }
        break;
    case 80: // ICE_BERRY: reject for Fire typing.
        if (func_8006397C(species) == 20 || func_800639C0(species) == 20) {
            return 1;
        }
        break;
    case 79: // BURNT_BERRY: reject for Ice typing.
        if (func_8006397C(species) == 25 || func_800639C0(species) == 25) {
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 HeldItem_IsRedundantForType_fragment81(u8, u8);
extern u8 *D_84302C80;
// The initializer clears this 24-byte N64 state. Its caller passes the
// rule-table flag as 0/1; see func_82601298.
//@src/fragments/20/fragment20_128B10.c
typedef struct Fragment81SelectionState {
    u8 count;
    u8 selector;
    u8 unk_02;
    u8 unk_03;
    s32 unk_04;
    s32 use_rule_table;
    u16 unk_0C;
    u16 stat_limit;
    u32 used_types;
    Fragment81RulePrefix *rules;
} Fragment81SelectionState;

extern Fragment81SelectionState D_84302C88;
u8 func_843007BC(u8 arg0, u8 arg1) {
    s32 i;
    u8 *p;

    if (arg1 == 0) {
        return 1;
    }
    if (HeldItem_IsRedundantForType_fragment81(arg0, arg1) != 0) {
        return 1;
    }
    p = D_84302C80;
    for (i = 0; i < D_84302C88.count; i++) {
        if (p[0] != 0 && p[1] == arg1) {
            return 1;
        }
        p += 0x58;
    }
    return 0;
}

extern u8 *D_84302C80;
extern Fragment81SelectionState D_84302C88;
s32 func_84300858(u8 arg0) {
    u8 *p;
    s32 i;

    p = D_84302C80;
    i = 0;
    while (i < D_84302C88.count) {
        if (*p != 0 && *p == arg0) {
            return 0;
        }
        i++;
        p += 0x58;
    }
    return 1;
}

s32 Type_IdToChartIndex(s32);
extern s32 D_84302C98;
u8 func_8006397C(u8 arg0);
u8 func_800639C0(u8 arg0);
s32 func_843008B0(u8 arg0) {
    s32 var_v1;

    var_v1 = ((1 << Type_IdToChartIndex(func_8006397C(arg0) & 0xFF)) & D_84302C98) != 0;
    if (var_v1 == 0) {
        var_v1 = ((1 << Type_IdToChartIndex(func_800639C0(arg0) & 0xFF)) & D_84302C98) != 0;
    }
    return var_v1;
}

extern u8 * D_84302C80;
extern Fragment81SelectionState D_84302C88;
s32 func_84300928(u8 arg0) {
    u8 *p;
    u8 *q;
    s32 i;
    s32 j;
    p = D_84302C80;
    i = 0;
    while (i < D_84302C88.count) {
        j = 0;
        q = p;
        while (j < 4) {
            if (q[2] == 0) { break; }
            if (q[2] == arg0) { return 0; }
            j++;
            q++;
        }
        i++;
        p += 0x58;
    }
    return 1;
}

typedef struct {
    u16 value;
    u8 tail[0x92];
} Fragment81Row;
extern u8 D_84302566[];
extern Fragment81SelectionState D_84302C88;
extern u8 D_84303008[];
extern u8 D_84303108[];
extern s32 func_84300648(u8);
extern void func_84300200(u8 *, u8);
void func_843009A4(u8 arg0) {
    s32 result;
    s32 first;
    s32 limit;

    if (arg0 > 0 && arg0 < 0xFC) {
        result = func_84300648(arg0);
        first = ((Fragment81Row *)D_84302566)[D_84302C88.selector].value;
        limit = D_84302C88.stat_limit;
        if ((first < limit && result < limit) || (first >= limit && result >= limit)) {
            func_84300200(D_84303008, arg0);
        } else {
            func_84300200(D_84303108, arg0);
        }
    }
}

typedef struct Fragment81TypeEntry {
    u8 count;
    u8 *species;
} Fragment81TypeEntry;
typedef struct Fragment81TypeRow {
    u8 level;
    u8 unk_01;
    u16 stat_cutoff;
    Fragment81TypeEntry types[18];
} Fragment81TypeRow;
extern Fragment81TypeRow D_84302564[];
void SpeciesCandidates_AddType_fragment81(u8 type, s32 force) {
    Fragment81TypeRow *row = &D_84302564[D_84302C88.selector];
    s32 i;
    u8 species;

    if (row->types[type].species != NULL) {
        for (i = 0; i < row->types[type].count; i++) {
            species = row->types[type].species[i];
            if (func_84300858(species) && (force || !func_843008B0(species))) {
                func_843009A4(species);
            }
        }
    }
}

void SpeciesCandidates_PopulateTypes_fragment81(u8 species) {
    s32 type;
    u8 mapped_type;

    for (type = 0; type != 18; type++) {
        if (D_84302C88.rules->types != NULL && (mapped_type = D_84302C88.rules->types[species]) != 0xFF) {
            if (mapped_type == type) {
                SpeciesCandidates_AddType_fragment81(type, 1);
            }
        } else if (!(D_84302C88.used_types & (1 << type))) {
            SpeciesCandidates_AddType_fragment81(type, 0);
        }
    }
}

extern u8 ByteList_ChooseRandom_fragment81(u8 *);
// Count-prefixed move pools follow the selected species' base-stat total.
typedef struct Fragment81MovePoolsPrefix {
    u16 base_stat_total;
    u8 effects[100];
    u8 primary[80];
    u8 secondary[80];
    u8 physical[80];
    u8 special[80];
    u8 group2_primary[90];
    u8 group2_secondary[90];
    u8 group2_physical[90];
    u8 group2_special[90];
} Fragment81MovePoolsPrefix;
extern Fragment81MovePoolsPrefix D_84302CA0;
extern s32 Type_IdToChartIndex(s32);
extern u8 func_8006397C(u8 arg0);
extern u8 func_800639C0(u8 arg0);
extern u8 func_84300348(u8 *arg0);
extern s32 func_84300648(u8);
extern Fragment81SelectionState D_84302C88;
extern u8 D_84303008[];
extern u8 D_84303108[];
u8 func_84300BE8(void) {
    u8 result;
    result = 0;
    if (func_84300348(D_84303008) > 0) result = ByteList_ChooseRandom_fragment81(D_84303008);
    else if (func_84300348(D_84303108) > 0) result = ByteList_ChooseRandom_fragment81(D_84303108);
    if (result != 0) {
        D_84302CA0.base_stat_total = func_84300648(result);
        D_84302C88.used_types |= 1 << Type_IdToChartIndex(func_8006397C(result) & 0xFF);
        D_84302C88.used_types |= 1 << Type_IdToChartIndex(func_800639C0(result) & 0xFF);
    }
    return result;
}

u8 MoveSelection_ChooseFirst_fragment81(void) {
    u8 move = 0;

    if (func_84300348(D_84302D06) > 0 && (func_8003570C() & 1)) {
        move = ByteList_ChooseRandom_fragment81(D_84302D06);
        ByteList_RemoveFirst_fragment81(D_84302D06, move);
        ByteList_RemoveFirst_fragment81(D_84302E46, move);
    } else if (func_84300348(D_84302D56) > 0) {
        move = ByteList_ChooseRandom_fragment81(D_84302D56);
        ByteList_RemoveFirst_fragment81(D_84302D56, move);
        ByteList_RemoveFirst_fragment81(D_84302EA0, move);
    } else if (func_84300348(D_84302D06) > 0) {
        move = ByteList_ChooseRandom_fragment81(D_84302D06);
        ByteList_RemoveFirst_fragment81(D_84302D06, move);
        ByteList_RemoveFirst_fragment81(D_84302E46, move);
    } else if (func_84300348(D_84302E46) > 0 && (func_8003570C() & 1)) {
        move = ByteList_ChooseRandom_fragment81(D_84302E46);
        ByteList_RemoveFirst_fragment81(D_84302D06, move);
        ByteList_RemoveFirst_fragment81(D_84302E46, move);
    } else if (func_84300348(D_84302EA0) > 0) {
        move = ByteList_ChooseRandom_fragment81(D_84302EA0);
        ByteList_RemoveFirst_fragment81(D_84302D56, move);
        ByteList_RemoveFirst_fragment81(D_84302EA0, move);
    } else if (func_84300348(D_84302E46) > 0) {
        move = ByteList_ChooseRandom_fragment81(D_84302E46);
        ByteList_RemoveFirst_fragment81(D_84302D06, move);
        ByteList_RemoveFirst_fragment81(D_84302E46, move);
    } else if (func_84300348(D_84302DA6) > 0 && (func_8003570C() & 1)) {
        move = ByteList_ChooseRandom_fragment81(D_84302DA6);
        ByteList_RemoveFirst_fragment81(D_84302DA6, move);
        ByteList_RemoveFirst_fragment81(D_84302EFA, move);
    } else if (func_84300348(D_84302DF6) > 0) {
        move = ByteList_ChooseRandom_fragment81(D_84302DF6);
        ByteList_RemoveFirst_fragment81(D_84302DF6, move);
        ByteList_RemoveFirst_fragment81(D_84302F54, move);
    } else if (func_84300348(D_84302DA6) > 0) {
        move = ByteList_ChooseRandom_fragment81(D_84302DA6);
        ByteList_RemoveFirst_fragment81(D_84302DA6, move);
        ByteList_RemoveFirst_fragment81(D_84302EFA, move);
    } else if (func_84300348(D_84302EFA) > 0 && (func_8003570C() & 1)) {
        move = ByteList_ChooseRandom_fragment81(D_84302EFA);
        ByteList_RemoveFirst_fragment81(D_84302DA6, move);
        ByteList_RemoveFirst_fragment81(D_84302EFA, move);
    } else if (func_84300348(D_84302F54) > 0) {
        move = ByteList_ChooseRandom_fragment81(D_84302F54);
        ByteList_RemoveFirst_fragment81(D_84302DF6, move);
        ByteList_RemoveFirst_fragment81(D_84302F54, move);
    } else if (func_84300348(D_84302EFA) > 0) {
        move = ByteList_ChooseRandom_fragment81(D_84302EFA);
        ByteList_RemoveFirst_fragment81(D_84302DA6, move);
        ByteList_RemoveFirst_fragment81(D_84302EFA, move);
    }
    MoveLists_ApplySelectionWeights_fragment81(move);
    return move;
}

extern u8 func_80062D98(u8);
u8 MoveSelection_ChooseSecond_fragment81(u8 *mon) {
    s32 i;
    u8 chosen;
    u8 first_type;
    u8 species;
    u8 candidates[256];

    chosen = 0;
    first_type = func_80062D98(mon[2]);
    species = mon[0];
    if (func_8006397C(species) != func_800639C0(species)) {
        if (func_80062D98(mon[2]) == func_800639C0(species)) {
            if (func_84300348(D_84302E46) > 0) {
                chosen = ByteList_ChooseRandom_fragment81(D_84302E46);
                ByteList_RemoveFirst_fragment81(D_84302D06, chosen);
                ByteList_RemoveFirst_fragment81(D_84302E46, chosen);
            }
        } else if (func_80062D98(mon[2]) == func_8006397C(species) && func_84300348(D_84302EA0) > 0) {
            chosen = ByteList_ChooseRandom_fragment81(D_84302EA0);
            ByteList_RemoveFirst_fragment81(D_84302D56, chosen);
            ByteList_RemoveFirst_fragment81(D_84302EA0, chosen);
        }
    }
    if (chosen == 0) {
        candidates[0] = 0;
        for (i = 1; i <= func_84300348(D_84302DA6); i++) {
            if (first_type != func_80062D98(D_84302CA0.physical[i])) {
                func_84300200(candidates, D_84302CA0.physical[i]);
            }
        }
        for (i = 1; i <= func_84300348(D_84302DF6); i++) {
            if (first_type != func_80062D98(D_84302CA0.special[i])) {
                func_84300200(candidates, D_84302CA0.special[i]);
            }
        }
        if (func_84300348(candidates) > 0) {
            chosen = ByteList_ChooseRandom_fragment81(candidates);
        } else if ((func_8003570C() & 1) && func_84300348(D_84302DA6) > 0) {
            chosen = ByteList_ChooseRandom_fragment81(D_84302DA6);
            ByteList_RemoveFirst_fragment81(D_84302DA6, chosen);
            ByteList_RemoveFirst_fragment81(D_84302EFA, chosen);
        }
        if (chosen == 0) {
            if (func_84300348(D_84302DF6) > 0) {
                chosen = ByteList_ChooseRandom_fragment81(D_84302DF6);
                ByteList_RemoveFirst_fragment81(D_84302DF6, chosen);
                ByteList_RemoveFirst_fragment81(D_84302F54, chosen);
            } else if (func_84300348(D_84302DA6) > 0) {
                chosen = ByteList_ChooseRandom_fragment81(D_84302DA6);
                ByteList_RemoveFirst_fragment81(D_84302DA6, chosen);
                ByteList_RemoveFirst_fragment81(D_84302EFA, chosen);
            }
        }
    }
    MoveLists_ApplySelectionWeights_fragment81(chosen);
    return chosen;
}

extern void ByteList_RemoveFirst_fragment81(u8 *, u8);
extern void MoveLists_ApplySelectionWeights_fragment81(u8);
extern u8 D_84302CA2[];
extern u8 D_84302FAE[];
extern u8 D_84302FD2[];
extern u8 ByteList_ChooseRandom_fragment81(u8 *);
extern u8 func_84300348(u8 *arg0);
extern s32 func_84300928(u8 arg0);
u8 func_843013A4(u8 *arg0) {
    u8 result;

    result = 0;
    if (func_84300348(D_84302CA2) > 0) {
        result = ByteList_ChooseRandom_fragment81(D_84302CA2);
        ByteList_RemoveFirst_fragment81(D_84302CA2, result);
    } else if (func_84300348(D_84302FAE) > 0) {
        result = ByteList_ChooseRandom_fragment81(D_84302FAE);
        if (func_84300928(result) == 0) {
            result = ByteList_ChooseRandom_fragment81(D_84302FAE);
        }
        ByteList_RemoveFirst_fragment81(D_84302FAE, result);
    } else if (func_84300348(D_84302FD2) > 0) {
        result = ByteList_ChooseRandom_fragment81(D_84302FD2);
        ByteList_RemoveFirst_fragment81(D_84302FD2, result);
    }
    MoveLists_ApplySelectionWeights_fragment81(result);
    return result;
}

extern u8 Pokemon_GetBaseStat(u8, u8);
u8 MoveSelection_ChooseFourth_fragment81(u8 *mon) {
    s32 i;
    u8 species;
    u8 chosen;
    u8 scanned_move;
    u8 current_type;
    u8 first_type;
    u8 second_type;
    u8 attack;
    u8 special_attack;
    u8 candidates[256];

    species = mon[0];
    chosen = 0;
    first_type = func_80062D98(mon[2]);
    second_type = func_80062D98(mon[3]);
    attack = Pokemon_GetBaseStat(species, 1);
    special_attack = Pokemon_GetBaseStat(species, 4);
    candidates[0] = 0;
    if (attack >= special_attack || func_84300348(D_84302F54) == 0) {
        for (i = 1; func_84300348(D_84302EFA) >= i; i++) {
            scanned_move = D_84302CA0.group2_physical[i];
            current_type = func_80062D98(scanned_move);
            if (current_type != first_type && current_type != second_type) {
                func_84300200(candidates, scanned_move);
            }
        }
    }
    if (special_attack >= attack || func_84300348(D_84302EFA) == 0) {
        for (i = 1; func_84300348(D_84302F54) >= i; i++) {
            scanned_move = D_84302CA0.group2_special[i];
            current_type = func_80062D98(scanned_move);
            if (current_type != first_type && current_type != second_type) {
                func_84300200(candidates, scanned_move);
            }
        }
    }
    if (func_84300348(candidates) > 0 && (func_8003570C() & 1)) {
        chosen = ByteList_ChooseRandom_fragment81(candidates);
    }
    if (chosen == 0) {
        if (func_84300348(D_84302FD2) > 0) {
            chosen = ByteList_ChooseRandom_fragment81(D_84302FD2);
            //!bug Removes the last scanned move instead of the choice; empty scans leave it unset.
            ByteList_RemoveFirst_fragment81(D_84302FD2, scanned_move);
        } else if (func_84300348(candidates) > 0) {
            chosen = ByteList_ChooseRandom_fragment81(candidates);
        }
    }
    return chosen;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_843016CC.s")

extern s32 D_84302C8C;
extern s32 func_8006443C(u8, u8, u8);
extern s32 func_80064404(u8, u8, u8);
s32 func_84301838(u8 arg0, u8 arg1, u8 arg2) {
    if (D_84302C8C != 0) {
        return func_8006443C(arg0, arg1, arg2);
    } else {
        return func_80064404(arg0, arg1, arg2);
    }
}

extern s32 func_800630C0(u8);
extern u8 D_84302380[];
extern u8 D_8430232C[];
extern u8 D_84302350[];
extern u8 D_84302280[];
extern u8 D_843022D0[];
void MovePools_ClassifyLearnable_fragment81(u8 species) {
    u8 primary;
    u8 secondary;
    u8 move;
    u8 move_type;
    u8 level;
    s32 i;

    level = D_84302564[D_84302C88.selector].level;
    primary = func_8006397C(species);
    secondary = func_800639C0(species);
    for (i = 1; i != 252; i++) {
        move = i;
        if (func_843003E0(D_84302380, move) == 0 && func_84301838(species, move, level) != 0) {
            move_type = func_80062D98(move);
            if (MoveRules_MatchesEffect_fragment81(move)) {
                func_84300200(D_84302CA2, move);
            } else if (func_843003E0(D_8430232C, move)) {
                func_84300200(D_84302FAE, move);
            } else if (func_843003E0(D_84302350, move)) {
                func_84300200(D_84302FD2, move);
            } else {
                if (func_843003E0(D_84302280, move)) {
                    if (move_type == primary) {
                        func_84300200(D_84302D06, move);
                    } else if (move_type == secondary) {
                        func_84300200(D_84302D56, move);
                    } else if (func_800630C0(move)) {
                        func_84300200(D_84302DA6, move);
                    } else {
                        func_84300200(D_84302DF6, move);
                    }
                }
                if (func_843003E0(D_843022D0, move)) {
                    if (move_type == primary) {
                        func_84300200(D_84302E46, move);
                    } else if (move_type == secondary) {
                        func_84300200(D_84302EA0, move);
                    } else if (func_800630C0(move)) {
                        func_84300200(D_84302EFA, move);
                    } else {
                        func_84300200(D_84302F54, move);
                    }
                }
            }
        }
    }
}

void Pokemon_ShuffleMoves_fragment81(u8 *mon) {
    u8 count = 0;
    s32 i;
    u8 index;
    u8 temp;

    //!bug The move byte is read before the bound, including mon[6] at count 4.
    while ((mon + 2)[count] != 0 && count < 4) {
        count++;
    }
    if (count >= 2) {
        for (i = 0; i < 3; i++) {
            index = func_8003570C() % count;
            temp = (mon + 2)[index];
            (mon + 2)[index] = mon[2];
            mon[2] = temp;
        }
    }
}

extern void MovePools_ClassifyLearnable_fragment81(u8);
extern u8 MoveSelection_ChooseFirst_fragment81(void);
extern u8 MoveSelection_ChooseSecond_fragment81(u8 *);
extern u8 func_843013A4(u8 *);
extern u8 MoveSelection_ChooseFourth_fragment81(u8 *);
void func_84301BA4(u8 *arg0) {
    u8 value;

    value = arg0[0];
    switch (value) {
    case 0x84:
        arg0[2] = 0x90;
        arg0[3] = 0;
        arg0[4] = 0;
        arg0[5] = 0;
        return;
    case 0xCA:
        arg0[2] = 0x44;
        arg0[3] = 0xF3;
        arg0[4] = 0xDB;
        arg0[5] = 0xC2;
        return;
    default:
        MovePools_ClassifyLearnable_fragment81(value);
        arg0[2] = MoveSelection_ChooseFirst_fragment81();
        arg0[3] = MoveSelection_ChooseSecond_fragment81(arg0);
        arg0[4] = func_843013A4(arg0);
        arg0[5] = MoveSelection_ChooseFourth_fragment81(arg0);
        return;
    }
}

extern u8 func_80062E10(u8);
void func_84301C58(u8 *arg0) {
    s32 i;
    u8 *p;
    u8 value;
    u8 result;

    p = arg0;
    i = 0;
    do {
        value = p[2];
        if (value == 0) {
            return;
        }
        result = func_80062E10(value);
        i++;
        p++;
        p[0x17] = result;
    } while (i != 4);
}

typedef struct Fragment81PokemonRecord {
    u32 words[22];
} Fragment81PokemonRecord;
void TeamRoster_Shuffle_fragment81(void) {
    u32 value;
    u8 index;
    Fragment81PokemonRecord saved;
    s32 i;

    i = 10;
    while (i-- > 0) {
        value = func_8003570C();
        saved = ((Fragment81PokemonRecord *)D_84302C80)[0];
        index = value % 6;
        ((Fragment81PokemonRecord *)D_84302C80)[0] = ((Fragment81PokemonRecord *)D_84302C80)[index];
        ((Fragment81PokemonRecord *)D_84302C80)[index] = saved;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84301DEC.s")

extern s32 func_8006A388(void);
extern s32 func_8006A3E0(void);
s32 func_843020F0(void) {
    s32 mode;

    if (func_8006A388() != 0) {
        return 1;
    }
    mode = func_8006A3E0() & 0xFF00;
    if ((mode == 0x100) || (mode == 0x200)) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84302148.s")
#endif
