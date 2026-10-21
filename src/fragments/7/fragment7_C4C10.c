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
typedef struct { Fragment7BankHeader header; u8 records[8][68]; } Fragment7RuleBank;
typedef struct { Fragment7BankHeader header; u8 records[6][1168]; } Fragment7TeamBank;
typedef struct { Fragment7BankHeader header; u8 records[8][544]; } Fragment7ProfileBank;
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

typedef struct Func8300AAD4Copy0 { s32 words[17]; } Func8300AAD4Copy0;
void func_8300AAD4(void *arg0, void *arg1) {
    u8 index;
    u8 *dst;

    index = *(u8 *)((u8 *)arg0 + 1);
    if (index < *(u8 *)((u8 *)arg0 + 0)) {
        dst = (u8 *)((u32)arg0 + (index * 0x44));
        *(Func8300AAD4Copy0 *)(dst + 4) = *(Func8300AAD4Copy0 *)arg1;
        *(u8 *)((u8 *)arg0 + 1) = *(u8 *)((u8 *)arg0 + 1) + 1;
        func_8300A9E0(arg0);
    }
}

typedef struct Func8300AB58Copy0 { s32 words[17]; } Func8300AB58Copy0;
void func_8300AB58(void *arg0, void *arg1, s32 arg2) {
    u8 *dst;

    if (arg2 < *(u8 *)((u8 *)arg0 + 1)) {
        dst = (u8 *)((u32)arg0 + (arg2 * 0x44));
        *(Func8300AB58Copy0 *)(dst + 4) = *(Func8300AB58Copy0 *)arg1;
        func_8300A9E0(arg0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300ABCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300AC8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300ADA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300AE40.s")

s32 func_8300AED8(void *arg0) {
    return (s32) (*(u8 *)((u8 *)(arg0) + (1))) >= (s32) (*(u8 *)((u8 *)(arg0) + (0)));
}

void Fragment7_InitializeTeamBank(void *bank, s32 expanded, s32 source) {
    _bzero(bank, sizeof(Fragment7TeamBank));
    ((Fragment7TeamBank *)bank)->header.expanded = expanded;
    ((Fragment7TeamBank *)bank)->header.capacity = expanded ? 6 : 3;
    ((Fragment7TeamBank *)bank)->header.source = source;
}

typedef struct Func8300AF68Copy { s32 words[292]; } Func8300AF68Copy;
void func_8300AF68(void *arg0, void *arg1) {
    u8 index;
    u8 *dst;

    index = *(u8 *)((u8 *)arg0 + 1);
    if (index < *(u8 *)((u8 *)arg0 + 0)) {
        dst = (u8 *)((u32)arg0 + (index * 0x490));
        *(Func8300AF68Copy *)(dst + 4) = *(Func8300AF68Copy *)arg1;
        *(u8 *)((u8 *)arg0 + 1) = *(u8 *)((u8 *)arg0 + 1) + 1;
    }
}

typedef struct Func8300AFD8Copy { s32 words[292]; } Func8300AFD8Copy;
void func_8300AFD8(void *arg0, void *arg1, s32 arg2) {
    u8 *dst;
    if (arg2 < *(u8 *)((u8 *)arg0 + 1)) {
        dst = (u8 *)((u32)arg0 + (arg2 * 0x490));
        *(Func8300AFD8Copy *)(dst + 4) = *(Func8300AFD8Copy *)arg1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B038.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B0DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B1CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B260.s")

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

typedef struct Func8300B3A8Copy { s32 words[136]; } Func8300B3A8Copy;
void func_8300B3A8(void *arg0, void *arg1) {
    u8 index;
    u8 *dst;
    index = *(u8 *)((u8 *)arg0 + 1);
    if (index < *(u8 *)((u8 *)arg0 + 0)) {
        dst = (u8 *)((u32)arg0 + (index * 0x220));
        *(Func8300B3A8Copy *)(dst + 4) = *(Func8300B3A8Copy *)arg1;
        *(u8 *)((u8 *)arg0 + 1) = *(u8 *)((u8 *)arg0 + 1) + 1;
    }
}

typedef struct Func8300B410Copy { s32 words[136]; } Func8300B410Copy;
void func_8300B410(void *arg0, void *arg1, s32 arg2) {
    u8 *dst;
    if (arg2 < *(u8 *)((u8 *)arg0 + 1)) {
        dst = (u8 *)((u32)arg0 + (arg2 * 0x220));
        *(Func8300B410Copy *)(dst + 4) = *(Func8300B410Copy *)arg1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B468.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B504.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B54C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B728.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B818.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/7/fragment7_C4C10/func_8300B8AC.s")

s32 func_8300B988(void *arg0) {
    return (s32) (*(u8 *)((u8 *)(arg0) + (1))) >= (s32) (*(u8 *)((u8 *)(arg0) + (0)));
}
#endif
