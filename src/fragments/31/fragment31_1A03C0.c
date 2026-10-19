#include "global.h"


#ifdef VERSION_US
typedef struct { u8 first, second; } LabPCBytePair;
extern u32 D_88234940;

void LabPC_SwapBytePairContents(LabPCBytePair *arg0, LabPCBytePair *arg1) {
    LabPCBytePair temp = *arg0;
    *arg0 = *arg1;
    *arg1 = temp;
}

// Sort the pointed-to pair contents; the pointer-array positions do not move.
void LabPC_SortBytePairContents(LabPCBytePair **entries, s32 count, s32 (*compare)(LabPCBytePair *, LabPCBytePair *)) {
    LabPCBytePair **limit;
    LabPCBytePair **current;
    LabPCBytePair **cursor;

    limit = entries + count;
    for (current = entries; current < limit; current++) {
        cursor = current;
        while ((cursor > entries) && (compare(cursor[-1], cursor[0]) > 0)) {
            LabPC_SwapBytePairContents(cursor[0], cursor[-1]);
            cursor--;
        }
    }
}

// Compare active first-byte ranks, then second bytes descending, then addresses.
// func_8822D45C selects the rank callback at state offset 0xE4.
s32 LabPC_CompareRankedBytePairs(LabPCBytePair *left, LabPCBytePair *right) {
    s32 result;
    u8 first_rank;

    first_rank = (*(u8 (**)(u8))(D_88234940 + 0xE4))(left->first);
    result = first_rank - (*(u8 (**)(u8))(D_88234940 + 0xE4))(right->first);
    if (result != 0) {
        return result;
    }
    result = right->second - left->second;
    return (result != 0) ? result : ((left == right) ? 0 : ((left < right) ? -1 : 1));
}

extern u8 D_88233920[];
extern u8 D_88233A1C[];
// Search the primary 250-byte order; absence returns 0, as does a match at index 0.
u8 LabPC_FindPrimaryByteOrderIndex(u8 value) {
    s32 i;

    for (i = 0; i < 250; i++) {
        if (D_88233920[i] == value) {
            return i;
        }
    }
    return 0;
}

// Alternate order selected by func_8822D45C; the same index/absence convention.
u8 LabPC_FindAlternateByteOrderIndex(u8 value) {
    s32 i;

    for (i = 0; i < 250; i++) {
        if (D_88233A1C[i] == value) {
            return i;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A03C0/func_8822D45C.s")

extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_8822D750(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern s32 D_880068B4;
extern void Util_Free(s32);
void func_8822D778(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B4 = 1;
    Util_Free(D_88234940);
}

extern void func_800226C0(s32);
extern void func_88004990(u8, u8);
extern void func_88002720(void *, u16, void *);
extern void func_8822D45C(u8);
// B closes the dialog; A applies the selected sort order before closing it.
void LabPC_UpdateSortDialogInput(void) {
    u8 *view;
    u32 pressed;

    pressed = *(u16 *)((u8 *)D_80087200 + 8);
    view = (u8 *)D_88234940 + 0x20;
    if (pressed & B_BUTTON) {
        func_800226C0(72);
        func_88004990((*(u8 **)D_88234940)[0], 0);
        D_880068B8 = 1;
    } else if (pressed & A_BUTTON) {
        func_800226C0(68);
        func_8822D45C(view[0x29]);
        func_88004990((*(u8 **)D_88234940)[0], 0);
        D_880068B8 = 1;
    } else {
        func_88002720(view + 0x28, *(u16 *)(view + 0xC), view + 0x2C);
    }
}

extern void func_8821D930(s32);
void func_8822D874(void) {
    func_8821D930(D_88234940 + 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A03C0/func_8822D89C.s")


void func_8822DB00(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void *D_88234950;
// Free both child-allocation lists, their backing buffers and the shared owner.
void LabPC_DestroyOwnedLists(void) {
    u32 i;

    Input_SetRepeatController(D_80087200);
    D_880068B4 = 1;
    for (i = 0; i < *(u16 *)((u8 *)D_88234950 + 0x38); i++) {
        Util_Free((*(s32 **)((u8 *)D_88234950 + 0x60))[i]);
    }
    for (i = 0; i < *(u16 *)((u8 *)D_88234950 + 0x48); i++) {
        Util_Free((*(s32 **)((u8 *)D_88234950 + 0x64))[i]);
    }
    Util_Free(*(s32 *)((u8 *)D_88234950 + 0x40));
    Util_Free(*(s32 *)((u8 *)D_88234950 + 0x50));
    Util_Free(*(s32 *)((u8 *)D_88234950 + 0x60));
    Util_Free(*(s32 *)((u8 *)D_88234950 + 0x64));
    Util_Free((s32)D_88234950);
}

void func_8822DC34(void) {
    func_88004990(*(*(u8 **)((u8 *)(D_88234950) + (4))), 0);
    func_88004990(*(*(u8 **)((u8 *)(D_88234950) + (8))), 0);
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A03C0/func_8822DC84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A03C0/func_8822DEBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A03C0/func_8822E290.s")
#endif
