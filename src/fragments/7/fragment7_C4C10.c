#include "global.h"


#ifdef VERSION_US
extern void _bzero(void *, s32);
extern void func_8300A9E0(void *);
void func_8300A9E0(void *arg0) {
    s32 index;
    u8 *dst;

    index = *(u8 *)((u8 *)arg0 + 1);
    if (index < *(u8 *)((u8 *)arg0 + 0)) {
        dst = (u8 *)((u32)arg0 + (index * 0x44) + 4);
        do {
            _bzero(dst, 0x44);
            index += 1;
            dst += 0x44;
        } while (index < *(u8 *)((u8 *)arg0 + 0));
    }
}

typedef struct {
    u32 capacity : 8;
    u32 count : 8;
    u32 expanded : 1;
    u32 source : 2;
    u32 unk_13 : 13;
} Fragment7BankHeader;
typedef struct { u32 words[17]; } Fragment7RuleRecord;
typedef struct { u32 words[292]; } Fragment7TeamRecord;
typedef struct { u32 words[136]; } Fragment7ProfileRecord;
typedef struct { Fragment7BankHeader header; Fragment7RuleRecord records[8]; } Fragment7RuleBank;
typedef struct { Fragment7BankHeader header; Fragment7TeamRecord records[6]; } Fragment7TeamBank;
typedef struct { Fragment7BankHeader header; Fragment7ProfileRecord records[8]; } Fragment7ProfileBank;
extern u8 *func_8006218C(s32, s32, s32, s32);
extern s32 Deck_ReadEntries(u8 *, s32, u8 *);
extern s32 func_80062304(u8 *);
extern void func_8300A9E0(void *arg0);
void Fragment7_InitializeRuleBank(void *bank, s32 expanded, s32 source) {
    _bzero(bank, sizeof(Fragment7RuleBank));
    ((Fragment7RuleBank *)bank)->header.capacity = expanded ? 8 : 5;
    ((Fragment7RuleBank *)bank)->header.expanded = expanded;
    ((Fragment7RuleBank *)bank)->header.source = source;
    func_8300A9E0(bank);
}

void func_8300AAD4(void *arg0, void *arg1) {
    u8 index;
    u8 *dst;

    index = *(u8 *)((u8 *)arg0 + 1);
    if (index < *(u8 *)((u8 *)arg0 + 0)) {
        dst = (u8 *)((u32)arg0 + (index * 0x44));
        *(Fragment7RuleRecord *)(dst + 4) = *(Fragment7RuleRecord *)arg1;
        *(u8 *)((u8 *)arg0 + 1) = *(u8 *)((u8 *)arg0 + 1) + 1;
        func_8300A9E0(arg0);
    }
}

void func_8300AB58(void *arg0, void *arg1, s32 arg2) {
    u8 *dst;

    if (arg2 < *(u8 *)((u8 *)arg0 + 1)) {
        dst = (u8 *)((u32)arg0 + (arg2 * 0x44));
        *(Fragment7RuleRecord *)(dst + 4) = *(Fragment7RuleRecord *)arg1;
        func_8300A9E0(arg0);
    }
}

void Fragment7_RemoveRuleRecord(void *bank, s32 selected) {
    s32 index;

    if (selected < (s32)((Fragment7RuleBank *)bank)->header.count) {
        for (index = selected; index < (s32)((Fragment7RuleBank *)bank)->header.count - 1; index++) {
            ((Fragment7RuleBank *)bank)->records[index] =
                ((Fragment7RuleBank *)bank)->records[index + 1];
        }
        ((Fragment7RuleBank *)bank)->header.count--;
        func_8300A9E0(bank);
    }
}

extern void func_8300B54C(void *);
void Fragment7_SwapRuleRecords(void *bank, s32 first, s32 second) {
    Fragment7RuleRecord temporary;
    if (first < (s32)((Fragment7RuleBank *)bank)->header.count &&
        second < (s32)((Fragment7RuleBank *)bank)->header.count) {
        temporary = ((Fragment7RuleBank *)bank)->records[first];
        ((Fragment7RuleBank *)bank)->records[first] = ((Fragment7RuleBank *)bank)->records[second];
        ((Fragment7RuleBank *)bank)->records[second] = temporary;
        func_8300A9E0(bank);
    }
}

extern s32 Deck_WriteEntries(u8 *, s32, u8 *);
typedef struct {
    u8 species;
    u8 unk_01[28];
    u8 level, flags, unk_1F;
    u32 payload[14];
} Fragment7ProfilePokemon;
extern u8 * func_8006218C(s32, s32, s32, s32);
void Fragment7_SaveRuleBank(void *bank) {
    u8 *handle = NULL;

    func_8300A9E0(bank);
    if (((Fragment7RuleBank *)bank)->header.expanded) {
        handle = func_8006218C(24, 0, 0, 1);
    } else {
        if (((Fragment7RuleBank *)bank)->header.source < 4) {
            handle = func_8006218C(38, ((Fragment7RuleBank *)bank)->header.source, 0, 1);
        }
    }
    if (handle != NULL) {
        Deck_WriteEntries((u8 *)((Fragment7RuleBank *)bank)->records,
            ((Fragment7RuleBank *)bank)->header.count, handle);
        func_80062304(handle);
    }
}

void Fragment7_LoadRuleBank(void *bank) {
    u8 *handle = NULL;

    if (((Fragment7RuleBank *)bank)->header.expanded) {
        handle = func_8006218C(24, 0, 0, 0);
    } else {
        if (((Fragment7RuleBank *)bank)->header.source < 4) {
            handle = func_8006218C(38, ((Fragment7RuleBank *)bank)->header.source, 0, 0);
        }
    }
    if (handle != NULL) {
        ((Fragment7RuleBank *)bank)->header.count = Deck_ReadEntries((u8 *)((Fragment7RuleBank *)bank)->records,
            ((Fragment7RuleBank *)bank)->header.capacity, handle);
        func_80062304(handle);
    }
}

s32 func_8300AED8(void *arg0) {
    return (s32) (*(u8 *)((u8 *)(arg0) + (1))) >= (s32) (*(u8 *)((u8 *)(arg0) + (0)));
}

void Fragment7_InitializeTeamBank(void *bank, s32 expanded, s32 source) {
    _bzero(bank, sizeof(Fragment7TeamBank));
    ((Fragment7TeamBank *)bank)->header.expanded = expanded;
    ((Fragment7TeamBank *)bank)->header.capacity = expanded ? 6 : 3;
    ((Fragment7TeamBank *)bank)->header.source = source;
}

void func_8300AF68(void *arg0, void *arg1) {
    u8 index;
    u8 *dst;

    index = *(u8 *)((u8 *)arg0 + 1);
    if (index < *(u8 *)((u8 *)arg0 + 0)) {
        dst = (u8 *)((u32)arg0 + (index * 0x490));
        *(Fragment7TeamRecord *)(dst + 4) = *(Fragment7TeamRecord *)arg1;
        *(u8 *)((u8 *)arg0 + 1) = *(u8 *)((u8 *)arg0 + 1) + 1;
    }
}

void func_8300AFD8(void *arg0, void *arg1, s32 arg2) {
    u8 *dst;
    if (arg2 < *(u8 *)((u8 *)arg0 + 1)) {
        dst = (u8 *)((u32)arg0 + (arg2 * 0x490));
        *(Fragment7TeamRecord *)(dst + 4) = *(Fragment7TeamRecord *)arg1;
    }
}

void Fragment7_RemoveTeamRecord(void *bank, s32 selected) {
    s32 index;

    if (selected < (s32)((Fragment7TeamBank *)bank)->header.count) {
        for (index = selected; index < (s32)((Fragment7TeamBank *)bank)->header.count - 1; index++) {
            ((Fragment7TeamBank *)bank)->records[index] =
                ((Fragment7TeamBank *)bank)->records[index + 1];
        }
        ((Fragment7TeamBank *)bank)->header.count--;
    }
}

void Fragment7_SwapTeamRecords(void *bank, s32 first, s32 second) {
    Fragment7TeamRecord temporary;

    if (first < (s32)((Fragment7TeamBank *)bank)->header.count &&
        second < (s32)((Fragment7TeamBank *)bank)->header.count) {
        temporary = ((Fragment7TeamBank *)bank)->records[first];
        ((Fragment7TeamBank *)bank)->records[first] = ((Fragment7TeamBank *)bank)->records[second];
        ((Fragment7TeamBank *)bank)->records[second] = temporary;
    }
}

void Fragment7_SaveTeamBank(void *bank) {
    u8 *handle = NULL;

    if (((Fragment7TeamBank *)bank)->header.expanded) {
        handle = func_8006218C(25, 0, 0, 1);
    } else {
        if (((Fragment7TeamBank *)bank)->header.source < 4) {
            handle = func_8006218C(39, ((Fragment7TeamBank *)bank)->header.source, 0, 1);
        }
    }
    if (handle != NULL) {
        Deck_WriteEntries((u8 *)((Fragment7TeamBank *)bank)->records,
            ((Fragment7TeamBank *)bank)->header.count, handle);
        func_80062304(handle);
    }
}

/* The original owner contains an empty traversal and has no return value. */
void Fragment7_TeamBankNoOp(void *bank) {
    s32 index;
    for (index = 0; index < *(u8 *)((u8 *)bank + 1); index++) {
    }
}

void Fragment7_LoadTeamBank(void *bank) {
    u8 *handle = NULL;

    if (((Fragment7TeamBank *)bank)->header.expanded) {
        handle = func_8006218C(25, 0, 0, 0);
    } else {
        if (((Fragment7TeamBank *)bank)->header.source < 4) {
            handle = func_8006218C(39, ((Fragment7TeamBank *)bank)->header.source, 0, 0);
        }
    }
    if (handle != NULL) {
        ((Fragment7TeamBank *)bank)->header.count = Deck_ReadEntries((u8 *)((Fragment7TeamBank *)bank)->records, ((Fragment7TeamBank *)bank)->header.capacity, handle);
        func_80062304(handle);
    }
}

s32 func_8300B31C(void *arg0) {
    return (s32) (*(u8 *)((u8 *)(arg0) + (1))) >= (s32) (*(u8 *)((u8 *)(arg0) + (0)));
}

void Fragment7_InitializeProfileBank(void *bank, s32 expanded, s32 source) {
    _bzero(bank, sizeof(Fragment7ProfileBank));
    ((Fragment7ProfileBank *)bank)->header.capacity = expanded ? 8 : 1;
    ((Fragment7ProfileBank *)bank)->header.expanded = expanded;
    ((Fragment7ProfileBank *)bank)->header.source = source;
}

void func_8300B3A8(void *arg0, void *arg1) {
    u8 index;
    u8 *dst;
    index = *(u8 *)((u8 *)arg0 + 1);
    if (index < *(u8 *)((u8 *)arg0 + 0)) {
        dst = (u8 *)((u32)arg0 + (index * 0x220));
        *(Fragment7ProfileRecord *)(dst + 4) = *(Fragment7ProfileRecord *)arg1;
        *(u8 *)((u8 *)arg0 + 1) = *(u8 *)((u8 *)arg0 + 1) + 1;
    }
}

void func_8300B410(void *arg0, void *arg1, s32 arg2) {
    u8 *dst;
    if (arg2 < *(u8 *)((u8 *)arg0 + 1)) {
        dst = (u8 *)((u32)arg0 + (arg2 * 0x220));
        *(Fragment7ProfileRecord *)(dst + 4) = *(Fragment7ProfileRecord *)arg1;
    }
}

void Fragment7_RemoveProfileRecord(void *bank, s32 selected) {
    s32 index;

    if (selected < (s32)((Fragment7ProfileBank *)bank)->header.count) {
        for (index = selected; index < (s32)((Fragment7ProfileBank *)bank)->header.count - 1; index++) {
            ((Fragment7ProfileBank *)bank)->records[index] =
                ((Fragment7ProfileBank *)bank)->records[index + 1];
        }
        ((Fragment7ProfileBank *)bank)->header.count--;
    }
}

s32 Fragment7_IsValidProfilePokemon(Fragment7ProfilePokemon *pokemon) {
    if (((pokemon->flags & 1) != 0) == 0 && pokemon->species > 0 && pokemon->species < 252 && pokemon->level > 0) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B54C.s")

void Fragment7_SwapProfileRecords(void *bank, s32 first, s32 second) {
    Fragment7ProfileRecord temporary;

    if (first < (s32)((Fragment7ProfileBank *)bank)->header.count &&
        second < (s32)((Fragment7ProfileBank *)bank)->header.count) {
        temporary = ((Fragment7ProfileBank *)bank)->records[first];
        ((Fragment7ProfileBank *)bank)->records[first] = ((Fragment7ProfileBank *)bank)->records[second];
        ((Fragment7ProfileBank *)bank)->records[second] = temporary;
    }
}

void Fragment7_SaveProfileBank(void *bank) {
    u8 *handle = NULL;

    if (((Fragment7ProfileBank *)bank)->header.expanded) {
        handle = func_8006218C(27, 0, 0, 1);
    } else {
        if (((Fragment7ProfileBank *)bank)->header.source < 4) {
            handle = func_8006218C(40, ((Fragment7ProfileBank *)bank)->header.source, 0, 1);
        }
    }
    if (handle != NULL) {
        Deck_WriteEntries((u8 *)((Fragment7ProfileBank *)bank)->records,
            ((Fragment7ProfileBank *)bank)->header.count, handle);
        func_80062304(handle);
    }
}

void Fragment7_LoadProfileBank(void *bank) {
    u8 *handle = NULL;
    s32 index;

    ((Fragment7ProfileBank *)bank)->header.count = 0;
    if (((Fragment7ProfileBank *)bank)->header.expanded) {
        handle = func_8006218C(27, 0, 0, 0);
    } else {
        if (((Fragment7ProfileBank *)bank)->header.source < 4) {
            handle = func_8006218C(40, ((Fragment7ProfileBank *)bank)->header.source, 0, 0);
        }
    }
    if (handle != NULL) {
        ((Fragment7ProfileBank *)bank)->header.count = Deck_ReadEntries((u8 *)((Fragment7ProfileBank *)bank)->records,
            ((Fragment7ProfileBank *)bank)->header.capacity, handle);
        func_80062304(handle);
    }
    for (index = 0; index < (s32)((Fragment7ProfileBank *)bank)->header.count; index++) {
        func_8300B54C(&((Fragment7ProfileBank *)bank)->records[index]);
    }
}

s32 func_8300B988(void *arg0) {
    return (s32) (*(u8 *)((u8 *)(arg0) + (1))) >= (s32) (*(u8 *)((u8 *)(arg0) + (0)));
}
#endif
