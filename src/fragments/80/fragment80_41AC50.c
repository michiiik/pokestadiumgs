#include "global.h"


#ifdef VERSION_US
/* Original debug text preceding this translation unit's move-effect table. */
const char D_84203890[] = "GuessMaxDamage\n";
const char D_842038A0[] = "CalcBattleValue\n";
const char D_842038B4[] = "%15s:%10d::";
const char D_842038C0[] = "prob %3d atk %3d(%3d) dmg %3d(%3d) sp %5d\n";
const char D_842038EC[] = "CalcPokeMonEntryValue\n";
const char D_84203904[] = "%11s vs";
const char D_8420390C[] = " %11s\n";
const char D_84203914[] = "value = %11d\n";
const char D_84203924[] = "CalcEntryValue\n";
const char D_84203934[] = "[%d/%d]:(";
const char D_84203940[] = "%d:Lv%3d";
const char D_8420394C[] = "%11s(%12d)R%d ";
const char D_8420395C[] = ") %10d\n";
const char D_84203964[] = "CalcEntryList\n";
const char D_84203974[] = "(%d)'s First %d\n";
const char D_84203988[] = "%d:(%15s) ";
const char D_84203994[] = "\n";
const char D_84203998[] = "select party %d\n";

typedef struct {
    u8 flags;
    u8 rank;
    u8 unk02[2];
    s32 unk04;
    s32 score;
} F84202744Entry;
extern F84202744Entry D_84203A88[];
typedef struct {
    u8 unk00;
    u8 unk01;
    u8 count;
    u8 indices[9];
    s32 total;
} F84202744State;
typedef struct F842029A8State {
    u8 active;
    u8 pad01[4];
    u8 selected;
    u8 count;
    u8 indices[9];
    s32 total;
    F84202744State other_entries[7];
} F842029A8State;
typedef struct F842029A8Record {
    u8 unk00[7];
    u8 roster_count;
    u8 count;
    u8 unk09[0x43];
    u8 mons[6][0x58];
    u8 unk25C[0x284];
} F842029A8Record;
extern F842029A8State D_84203AD0;
extern F842029A8Record *D_84203B54;
extern u32 D_84203A40;
extern u8 TeamCandidate_SelectLead_fragment80(F84202744State *);
extern u8 D_15833A0[], D_1587718[];
extern void func_80003F74(u8 *, u8 *, u8 *, s32);
extern void _bcopy(const void *, void *, s32);
void TeamParameters_Load_fragment80(u8 arg0) {
    s32 offset = arg0 * 0x4E0;
    u8 mode = ((u8 *)D_84203B54 + offset)[0x49A];
    u8 *end;
    u32 buffer;
    /* Whole u64s provide the minimum aligned capacity for the 68-byte DMA. */
    u64 scratch[(0x44 + sizeof(u64) - 1) / sizeof(u64)];
    u8 *start;
    end = D_15833A0 + mode * 0x44;
    buffer = ((u32)scratch & ~7U);
    start = end - 0x44;
    func_80003F74((u8 *)buffer, start, end, 0);
    if (start != D_1587718) {
        _bcopy((u8 *)buffer, (u8 *)D_84203B54 + offset + 0x49C, 0x44);
    }
    _bcopy((u8 *)D_84203B54 + offset + 0x49C, &D_84203A40, 0x44);
}

typedef struct Fragment80CandidateList {
    u8 count, unk01[3];
    F84202744State entries[8];
} Fragment80CandidateList;
typedef char Fragment80CandidateListSizeCheck[sizeof(Fragment80CandidateList)==132 ? 1 : -1];
extern void _bzero(void *, s32);
extern s32 TeamMember_SumMatchupValues_fragment80(u8, u8, u8);
extern u8 *func_842034B0(u8 *, u8 *);
extern u32 func_8003570C(void);
void TeamCandidates_Reset_fragment80(void) {
    s32 i;
    _bzero(((Fragment80CandidateList *)&D_84203AD0), sizeof(Fragment80CandidateList));
    for (i = 0; i < 8; i++) {
        ((Fragment80CandidateList *)&D_84203AD0)->entries[i].total = -2147483647 - 1;
    }
}

s32 MoveEffect_UsesDamageSimulation_fragment80(u8 effect) {
    switch (effect) {
    case 3:
    case 7:
    case 8:
    case 26:
    case 38:
    case 39:
    case 80:
    case 145:
    case 148:
    case 154:
        return 0;
    default:
        return 1;
    }
}

typedef struct unk_func_842016BC {
    u8 move_id, effect, power, type, accuracy;
    u8 level;
    u8 unk06[6];
    s32 damage, score;
} unk_func_842016BC;
typedef struct F80BattleParameters {
    u32 flags;
    u8 unk04[4];
    u8 damage_weight, threat_weight, special_weight;
    u8 unk0B[0x39];
} F80BattleParameters;
typedef char F80BattleParametersSize[sizeof(F80BattleParameters)==0x44 ? 1 : -1];
typedef struct Fragment80DamageContext {
    unk_func_842016BC move;
    F80BattleParameters *parameters;
    u8 *attacker, *defender;
} Fragment80DamageContext;
typedef char Fragment80DamageContextSize[sizeof(Fragment80DamageContext)==32 ? 1 : -1];
extern void func_842016BC(u8, unk_func_842016BC *);
extern void func_8420168C(void *);

extern u16 func_8420199C(u8 *, u8 *);
extern u8 Ratio_ScaleToByte_fragment80(u16, u16);
extern void func_84200970(void *);
extern u8 func_84203440(void);
extern u8 func_8420344C(void);
extern u8 func_80062D20(u8);
extern s32 *func_80062CE0(u8);
typedef struct Fragment80MatchupRecord { u32 words[22]; } Fragment80MatchupRecord;
typedef struct Fragment80MatchupTeam {
    u8 unk00[0x18];
    Fragment80MatchupRecord members[6];
    u8 unk228[0x2B8];
} Fragment80MatchupTeam;
typedef char Fragment80MatchupTeamSize[sizeof(Fragment80MatchupTeam)==0x4E0 ? 1 : -1];
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_8420199C.s")

s32 TeamMember_ComputeMatchupValue_fragment80(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    u8 *attacker = (u8 *)&((Fragment80MatchupTeam *)D_84203B54)[arg0].members[arg2];
    u8 move;
    u8 retaliation;
    s32 i;
    u8 ratio;
    u8 threat;
    s32 special;
    s32 total = 0;
    s32 damage;
    s32 value;
    {
        u8 *defender = (u8 *)&((Fragment80MatchupTeam *)D_84203B54)[arg1].members[arg3];
        Fragment80DamageContext context;
        retaliation = Ratio_ScaleToByte_fragment80(func_8420199C(defender, attacker), *(u16 *)(attacker + 0x26));
        context.attacker = attacker;
        context.parameters = (F80BattleParameters *)&D_84203A40;
        context.defender = defender;
        for (i = 0; i != 4; i++) {
            move = attacker[i + 2];
            func_842016BC(move, &context.move);
            if (context.move.power) {
                func_8420168C(&context);
                damage = context.move.damage;
            } else {
                damage = 0;
            }
            ratio = Ratio_ScaleToByte_fragment80(damage, *(u16 *)(defender + 0x26));
            func_84200970(&context);
            special = context.move.score;
            value = func_84203440() * context.move.accuracy * ratio * ((F80BattleParameters *)&D_84203A40)->damage_weight / 255;
            value += context.move.accuracy * special * ((F80BattleParameters *)&D_84203A40)->special_weight / 255;
            if (func_80062D20(move) == 7) {
                threat = 255;
            } else {
                threat = retaliation;
            }
            value -= threat * 255 * ((F80BattleParameters *)&D_84203A40)->threat_weight * func_8420344C() / 255;
            func_842034B0((u8 *)func_80062CE0(context.move.move_id), 0);
            total += value;
        }
    }
    return total;
}

s32 TeamMember_SumMatchupValues_fragment80(u8 arg0, u8 arg1, u8 arg2) {
    s32 i;
    s32 total = 0;
    for (i = 0; i < D_84203B54[arg1].roster_count; i++) {
        func_842034B0(D_84203B54[arg0].mons[arg2], 0);
        func_842034B0(D_84203B54[arg1].mons[i], 0);
        total += TeamMember_ComputeMatchupValue_fragment80(arg0, arg1, arg2, i);
    }
    return total;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84201F2C.s")

void TeamScores_Rank_fragment80(u8 arg0) {
    u8 count = D_84203B54[arg0].roster_count;
    s32 rank;
    s32 i;
    s32 best;
    s32 maximum;
    for (rank = 1; rank <= count; rank++) {
        best = -1;
        maximum = -2147483647 - 1;
        for (i = 0; i < count; i++) {
            if (D_84203A88[i].rank == 0 && maximum < D_84203A88[i].score) {
                best = i;
                maximum = D_84203A88[i].score;
            }
        }
        D_84203A88[best].rank = rank;
    }
}

typedef char F80SelectionRecordSizes[(sizeof(F84202744Entry)==12 && sizeof(F842029A8Record)==0x4E0 && sizeof(F842029A8State)==132) ? 1 : -1];
void TeamCandidates_VisitMembers_fragment80(u8 arg0) {
    s32 i;
    s32 j;
    u8 member;
    for (i = 0; i < ((Fragment80CandidateList *)&D_84203AD0)->count; i++) {
        for (j = 0; j < ((Fragment80CandidateList *)&D_84203AD0)->entries[i].count; j++) {
            member = ((Fragment80CandidateList *)&D_84203AD0)->entries[i].indices[j];
            func_842034B0(D_84203B54[arg0].mons[member], 0);
        }
    }
}

void func_84202294(void *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    _bzero(arg0, 0x10);
    ((u8 *)arg0)[1] = arg1;
    ((u8 *)arg0)[2] = 3;
    ((u8 *)arg0)[3] = arg2;
    ((u8 *)arg0)[4] = arg3;
    ((u8 *)arg0)[5] = arg4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_842022F0.s")

extern u8 func_8006397C(u8);
extern u8 func_800639C0(u8);
extern u8 func_80063454(u8, u8, u8, s32);
typedef struct Fragment80WeaknessMember { u32 words[22]; } Fragment80WeaknessMember;
typedef struct Fragment80WeaknessTeam {
    u8 unk00[0x18];
    Fragment80WeaknessMember members[6];
    u8 unk228[0x2B8];
} Fragment80WeaknessTeam;
typedef char Fragment80WeaknessTeamSize[sizeof(Fragment80WeaknessTeam)==0x4E0 ? 1 : -1];
void TeamCandidate_ApplySharedWeakness_fragment80(F84202744State *state) {
    u8 *first;
    u16 weak[3];
    u8 *second;
    u8 *third;
    s32 i;
    u16 pairs;
    u8 primary;
    first = (u8 *)&((Fragment80WeaknessTeam *)D_84203B54)[state->unk01].members[state->indices[0]];
    second = (u8 *)&((Fragment80WeaknessTeam *)D_84203B54)[state->unk01].members[state->indices[1]];
    third = (u8 *)&((Fragment80WeaknessTeam *)D_84203B54)[state->unk01].members[state->indices[2]];
    if (!(D_84203A40 & 0x800)) {
        for (i = 0; i < 18; i++) {
            pairs = 0;
            primary = func_8006397C(first[0]);
            weak[0] = func_80063454(i, primary, func_800639C0(first[0]), 0);
            primary = func_8006397C(second[0]);
            weak[1] = func_80063454(i, primary, func_800639C0(second[0]), 0);
            primary = func_8006397C(third[0]);
            weak[2] = func_80063454(i, primary, func_800639C0(third[0]), 0);
            if (weak[0] < 10 && weak[1] < 10) pairs = 1;
            if (weak[0] < 10 && weak[2] < 10) pairs++;
            if (weak[1] < 10 && weak[2] < 10) pairs++;
            if (state->total > 0) {
                state->total *= 10 - pairs;
                state->total /= 10;
            } else {
                state->total *= 10 + pairs;
                state->total /= 10;
            }
        }
    }
}

void func_84202744(F84202744State *arg0) {
    s32 i;

    arg0->total = 0;
    for (i = 0; i < arg0->count; i++) {
        arg0->total += D_84203A88[arg0->indices[i]].score;
    }
}

void TeamCandidates_InsertRanked_fragment80(void *arg0) {
    s32 i;
    s32 j;
    for (i = 0; i < 8; i++) {
        if (((Fragment80CandidateList *)&D_84203AD0)->entries[i].total < ((F84202744State *)arg0)->total) break;
        if (((Fragment80CandidateList *)&D_84203AD0)->entries[i].total == ((F84202744State *)arg0)->total && (func_8003570C() & 1)) break;
    }
    if (i < 8) {
        for (j = 7; j > i; j--) {
            ((Fragment80CandidateList *)&D_84203AD0)->entries[j] = ((Fragment80CandidateList *)&D_84203AD0)->entries[j - 1];
        }
        ((Fragment80CandidateList *)&D_84203AD0)->entries[i] = *(F84202744State *)arg0;
        ((Fragment80CandidateList *)&D_84203AD0)->count++;
        if (((Fragment80CandidateList *)&D_84203AD0)->count > 8) {
            ((Fragment80CandidateList *)&D_84203AD0)->count = 8;
        }
    }
}

void func_842029A8(u8 arg0) {
    s32 i;

    D_84203AD0.selected = arg0;
    D_84203AD0.count = D_84203B54[arg0].count;
    for (i = 0; i < D_84203AD0.count; i++) {
        D_84203AD0.indices[i] = i;
    }
    D_84203AD0.active = 1;
}

extern u8 D_84203B5C;
s32 func_842022F0(void *);
void TeamCandidate_ApplySharedWeakness_fragment80(F84202744State *);
void TeamCandidates_InsertRanked_fragment80(void *);
extern u32 func_8003570C(void);
extern void func_84202294(void *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
extern u32 D_84203A40;
void func_84202A20(u8 arg0) {
    s32 i;
    s32 j;
    s32 k;
    u8 limit;
    u8 first, second;
    F84202744State state;

    D_84203B5C = (func_8003570C() & 1) + 1;
    if (D_84203A40 & 0x80) {
        limit = 1;
    } else {
        limit = 4;
    }
    for (i = 0; i < limit; i++) {
        for (j = i + 1; j < 5; j++) {
            first = i;
            second = j;
            for (k = j + 1; k < 6; k++) {
                func_84202294(&state, arg0, first, second, k);
                if (func_842022F0(&state)) {
                    func_84202744(&state);
                    TeamCandidate_ApplySharedWeakness_fragment80(&state);
                    TeamCandidates_InsertRanked_fragment80(&state);
                }
            }
        }
    }
}

extern void func_842029A8(u8 arg0);
extern void func_84202A20(u8 arg0);
void func_84202B58(u8 arg0) {
    u8 *record = (u8 *)D_84203B54 + arg0 * 0x4E0;

    if (record[7] == 6) {
        if (record[8] == 3) {
            goto special;
        }
    }
    func_842029A8(arg0);
    goto done;
special:
    func_84202A20(arg0);
done:
    ;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84202BD0.s")

u8 TeamCandidate_SelectLead_fragment80(F84202744State *state) {
    s32 i;
    u8 member;
    s32 best = -1;
    s32 maximum = -2147483647 - 1;
    F84202744Entry *entry;
    for (i = 0; i < state->count; i++) {
        member = state->indices[i];
        entry = &D_84203A88[member];
        if (maximum < entry->unk04) {
            best = i;
            maximum = entry->unk04;
        } else if (maximum == entry->unk04) {
            if (best == -1 || (func_8003570C() & 1)) {
                best = i;
                maximum = entry->unk04;
            }
        }
    }
    return best;
}

u8 func_84202FE4(void *arg0) { func_84202BD0(arg0); return TeamCandidate_SelectLead_fragment80(arg0); }

extern u8 func_84202FE4(void *arg0);
extern u32 D_84203A40;
void TeamCandidate_PromoteChoice_fragment80(void *arg0) {
    s32 chosen;
    u8 temp;
    if (!(D_84203A40 & 0x100)) {
        if (D_84203A40 & 0x10) chosen = func_8003570C() % ((u8 *)arg0)[2];
        else chosen = func_84202FE4(arg0);
        temp = ((u8 *)arg0)[3];
        ((u8 *)arg0)[3] = ((u8 *)arg0)[chosen + 3];
        ((u8 *)arg0)[chosen + 3] = temp;
    }
}

void TeamRoster_ApplyCandidateOrder_fragment80(void *arg0) {
    s32 i;
    s32 next;
    u8 team_index = ((F84202744State *)arg0)->unk01;
    Fragment80WeaknessTeam *team = &((Fragment80WeaknessTeam *)D_84203B54)[team_index];
    Fragment80WeaknessMember saved[6];
    s32 used[6];
    for (i = 0; i < ((u8 *)team)[7]; i++) {
        saved[i] = team->members[i];
        used[i] = 0;
    }
    for (i = 0; i < ((F84202744State *)arg0)->count; i++) {
        team->members[i] = saved[((F84202744State *)arg0)->indices[i]];
        used[((F84202744State *)arg0)->indices[i]] = 1;
    }
    next = 3;
    for (i = 0; i < ((u8 *)team)[7]; i++) {
        if (!used[i]) {
            team->members[next] = saved[i];
            next++;
        }
    }
    for (i = 0; i < ((F84202744State *)arg0)->count; i++) {
        func_842034B0((u8 *)team + i * 0x58 + 0x4C, 0);
    }
}

extern u32 D_84203A40;
extern u32 func_8003570C(void);
void TeamCandidate_PromoteChoice_fragment80(void *arg0);
void TeamRoster_ApplyCandidateOrder_fragment80(void *arg0);
void func_842032AC(void) {
    s32 index;
    s32 limit;
    s32 last;

    if (*(u8 *)&D_84203AD0 != 0) {
        limit = (D_84203A40 & 0x40) ? 7 : 3;
        last = *(u8 *)&D_84203AD0 - 1;
        if (limit >= last) {
            limit = last;
        }
        index = func_8003570C() % (limit + 1);
        TeamCandidate_PromoteChoice_fragment80((u8 *)&D_84203AD0 + (index * 0x10 + 4));
        TeamRoster_ApplyCandidateOrder_fragment80((u8 *)&D_84203AD0 + (index * 0x10 + 4));
    }
}

void TeamParameters_Load_fragment80(u8);
void TeamCandidates_Reset_fragment80(void);
void func_84201F2C(u8);
void TeamScores_Rank_fragment80(u8);
void func_84202B58(u8);
void TeamCandidates_VisitMembers_fragment80(u8);
void func_842032AC(void);
void func_84203360(u8 arg0) {
    if (((u8 *)D_84203B54)[arg0 * 0x4E0 + 0x49A] != 0) {
        TeamParameters_Load_fragment80(arg0);
        TeamCandidates_Reset_fragment80();
        func_84201F2C(arg0);
        TeamScores_Rank_fragment80(arg0);
        func_84202B58(arg0);
        TeamCandidates_VisitMembers_fragment80(arg0);
        func_842032AC();
    }
}

extern void *D_84203B58;
extern void func_80035700(u32);
void func_842033EC(F842029A8Record *arg0, void *arg1) {
    struct {
        u32 count;
        u32 reserved;
    } state;
    u32 value;

    D_84203B54 = arg0;
    D_84203B58 = arg1;
    state.count = osGetCount();
    value = guRandom() & state.count;
    func_80035700(((value & 0xFFFF0000) >> 16) | ((value & 0xFFFF) << 16));
}

extern u8 D_842034D0;
u8 func_84203440(void) {
    return D_842034D0;
}

extern u8 D_842034D4;
u8 func_8420344C(void) {
    return D_842034D4;
}

extern u8 D_842034D8;
u8 func_84203458(void) {
    return D_842034D8;
}

extern u8 D_842034DC;
u8 func_84203464(void) {
    return D_842034DC;
}

extern u8 D_842034E0;
u8 func_84203470(void) {
    return D_842034E0;
}

extern u8 D_842034E4;
u8 func_8420347C(void) {
    return D_842034E4;
}

extern u8 D_842034EC;
u8 func_84203488(void) {
    return D_842034EC;
}

extern u8 D_842034F0;
u8 func_84203494(void) {
    return D_842034F0;
}

extern u8 D_842034E8;
u8 func_842034A0(void) {
    return D_842034E8;
}
#endif
