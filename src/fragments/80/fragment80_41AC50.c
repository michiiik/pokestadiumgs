#include "global.h"


#ifdef VERSION_US
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
extern u8 func_84202EE4(void *);
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_842017D0.s")

typedef struct Fragment80CandidateList {
    u8 count, unk01[3];
    F84202744State entries[8];
} Fragment80CandidateList;
typedef char Fragment80CandidateListSizeCheck[sizeof(Fragment80CandidateList)==132 ? 1 : -1];
extern void _bzero(void *, s32);
extern s32 func_84201DDC(u8, u8, u8);
extern u8 *func_842034B0(u8 *, u8 *);
extern u32 func_8003570C(void);
void TeamCandidates_Reset_fragment80(void) {
    s32 i;
    _bzero(((Fragment80CandidateList *)&D_84203AD0), sizeof(Fragment80CandidateList));
    for (i = 0; i < 8; i++) {
        ((Fragment80CandidateList *)&D_84203AD0)->entries[i].total = -2147483647 - 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_842018FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_8420199C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84201AEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84201DDC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_842024CC.s")

void func_84202744(F84202744State *arg0) {
    s32 i;

    arg0->total = 0;
    for (i = 0; i < arg0->count; i++) {
        arg0->total += D_84203A88[arg0->indices[i]].score;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84202798.s")

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
void func_842024CC(void *);
void func_84202798(void *);
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
                    func_842024CC(&state);
                    func_84202798(&state);
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84202EE4.s")

u8 func_84202FE4(void *arg0) { func_84202BD0(arg0); return func_84202EE4(arg0); }

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41AC50/func_84203090.s")

extern u32 D_84203A40;
extern u32 func_8003570C(void);
void TeamCandidate_PromoteChoice_fragment80(void *arg0);
void func_84203090(void *arg0);
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
        func_84203090((u8 *)&D_84203AD0 + (index * 0x10 + 4));
    }
}

void func_842017D0(u8);
void TeamCandidates_Reset_fragment80(void);
void func_84201F2C(u8);
void TeamScores_Rank_fragment80(u8);
void func_84202B58(u8);
void TeamCandidates_VisitMembers_fragment80(u8);
void func_842032AC(void);
void func_84203360(u8 arg0) {
    if (((u8 *)D_84203B54)[arg0 * 0x4E0 + 0x49A] != 0) {
        func_842017D0(arg0);
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
