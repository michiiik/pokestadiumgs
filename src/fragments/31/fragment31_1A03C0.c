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
// LabPC_ApplyBytePairSortOrder selects the rank callback at state offset 0xE4.
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

// Alternate order selected by LabPC_ApplyBytePairSortOrder; the same index/absence convention.
u8 LabPC_FindAlternateByteOrderIndex(u8 value) {
    s32 i;

    for (i = 0; i < 250; i++) {
        if (D_88233A1C[i] == value) {
            return i;
        }
    }
    return 0;
}

extern u8 *D_88A01C64;
extern u8 *func_88A00710(s32, s16);
extern u8 func_88A007BC(s32);
extern s32 func_88A008CC(u8 *);
extern s32 func_8800005C(void);
extern u8 func_800735A0(u8);
extern u8 func_80073600(u8);
extern void func_88001D0C(void *);
typedef struct LabPCSortControl {
    s32 collection;
    u8 *selection;
    u8 (*rank)(u8);
} LabPCSortControl;
// Sort the selected collections and restore the selected pair's list position.
void LabPC_ApplyBytePairSortOrder(u8 mode) {
    u32 j;
    s32 group;
    s32 groups = 1;
    s32 count;
    s32 wrote;
    LabPCBytePair *work[256];
    LabPCBytePair **cursor;
    s32 alternate;
    s32 changed;
    LabPCBytePair selected;
    u8 *first;

    changed = 0;
    selected = *(LabPCBytePair *)func_88A00710(*(s32 *)((u8 *)D_88234940 + 0xDC), *(s16 *)(((LabPCSortControl *)(D_88234940 + 0xDC))->selection + 8));
    wrote = 0;
    if (func_8800005C() == 0 && *(s32 *)(D_88234940 + 0xDC) == 0) {
        groups = 4;
    }
    for (group = 0; group != groups; group++) {
        if (groups == 4) {
            if (group == 2) continue;
            count = (D_88A01C64 + group)[1];
            first = D_88A01C64;
            first += 2 * (D_88A01C64 + group)[5];
            first += 9;
        } else {
            first = func_88A00710(*(s32 *)(D_88234940 + 0xDC), 0);
            count = func_88A007BC(*(s32 *)(D_88234940 + 0xDC));
        }
        if (count >= 2) {
            if (!wrote) {
                *(s32 *)(D_88A01C64 + 4 * *(s32 *)((u8 *)D_88234940 + 0xDC) + 0x104) = 1;
                alternate = func_88A008CC(first);
                wrote = 1;
            }
            if (mode == 0) {
                *(u8 (**)(u8))((u8 *)D_88234940 + 0xE4) = alternate ? LabPC_FindAlternateByteOrderIndex : LabPC_FindPrimaryByteOrderIndex;
            } else {
                *(u8 (**)(u8))((u8 *)D_88234940 + 0xE4) = alternate ? func_80073600 : func_800735A0;
            }
            for (j = 0, cursor = work; j < count; j++, cursor++) {
                *cursor = (LabPCBytePair *)first;
                first += 2;
            }
            LabPC_SortBytePairContents(work, count, LabPC_CompareRankedBytePairs);
            changed = 1;
        }
    }
    if (changed) {
        first = func_88A00710(*(s32 *)(D_88234940 + 0xDC), 0);
        count = func_88A007BC(*(s32 *)(D_88234940 + 0xDC));
        for (j = 0; j < count; j++, first += 2) {
            if (first[0] == selected.first && first[1] == selected.second) break;
        }
        *(s16 *)(((LabPCSortControl *)(D_88234940 + 0xDC))->selection + 10) = j - (*(s16 *)(((LabPCSortControl *)(D_88234940 + 0xDC))->selection + 8) - *(s16 *)(((LabPCSortControl *)(D_88234940 + 0xDC))->selection + 10));
        func_88001D0C(((LabPCSortControl *)(D_88234940 + 0xDC))->selection);
    }
}

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
        LabPC_ApplyBytePairSortOrder(view[0x29]);
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

extern void *Util_Malloc(s32);
extern void *func_8004C874(s32, s32);
extern s32 func_8004C54C(s32, s32);
extern void *func_8004C8A0(void *, s32, s32, s32);
extern s32 func_8800005C(void);
extern u8 *func_88002AA8(u8 *, s32, u8 **, u16, s32, s16, s16, s16, s16, s16, s16, s32, s16, void *);
extern u8 func_88004804(s32, s32, s16, s16, s32, s32, u8, u8, u8, s32 *, s32 *, s32 *, s32 *, u8, u8);
extern u8 D_88006020[];
extern u8 D_8800ED50[];
// Create the two-choice sort dialog and attach its input and lifecycle callbacks.
void LabPC_CreateSortDialog(s32 collection, void *selection, void *label_override) {
    s32 message;
    u32 slot;
    void *label;
    u32 i;

    D_88234940 = (u32)Util_Malloc(232);
    *(s32 *)(D_88234940 + 0xDC) = collection;
    *(void **)(D_88234940 + 0xE0) = selection;
    for (i = 0; i < 2; i++) {
        *(void **)(D_88234940 + 0x54 + i * 4) = func_8004C874(33, i + 28);
    }
    func_88002AA8((u8 *)D_88234940 + 0x20, 0, (u8 **)(D_88234940 + 0x54), 2, 8, 1, 6, 0, 0, 0, 0, 0, 0, D_88006020);
    switch (collection) {
    case 0:
        message = func_8800005C() ? 17 : 18;
        label = func_8004C874(33, message);
        break;
    case 1:
        label = label_override;
        break;
    case 2:
        label = func_8004C874(33, 20);
        break;
    case 3:
        label = func_8004C874(33, 21);
        break;
    }
    func_8004C54C(74, (s32)label);
    *(void **)(D_88234940 + 12) = func_8004C8A0((u8 *)D_88234940 + 0x5C, 128, 33, 27);
    *(s32 *)(D_88234940 + 8) = 0;
    *(s32 *)(D_88234940 + 16) = 4;
    *(s16 *)(D_88234940 + 20) = 1;
    *(s16 *)(D_88234940 + 22) = 4;
    slot = func_88004804(D_88234940 + 4, 2, 320, 240, 4, 1, 220, 220, 180,
        (s32 *)LabPC_UpdateSortDialogInput, (s32 *)func_8822D874, (s32 *)func_8822D750, (s32 *)func_8822D778, 0, 0);
    *(u8 **)D_88234940 = D_8800ED50 + 76 * slot;
    D_880068B4 = 0;
}


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

extern void func_88208010(u8, u8, u8);
// Handle menu/list selection and tint the choice window for the active list.
void LabPC_UpdateListChoiceDialogInput(void) {
    u8 *list;
    s32 mode;

    mode = *(s16 *)((u8 *)D_88234950 + 16);
    switch (mode) {
    case 1:
        list = (u8 *)D_88234950 + 0x34;
        break;
    case 2:
        list = (u8 *)D_88234950 + 0x44;
        break;
    }
    if (*(s32 *)((u8 *)D_88234950 + 12)) {
        if (*(u16 *)((u8 *)D_80087200 + 8) & B_BUTTON) {
            func_800226C0(72);
            func_8822DC34();
        } else if (*(u16 *)((u8 *)D_80087200 + 8) & A_BUTTON) {
            func_800226C0(71);
            if (*(s16 *)((u8 *)D_88234950 + 16) == 0) {
                func_88208010(*(u8 *)D_88234950, 0, 0);
                func_8822DC34();
            } else {
                *(s32 *)((u8 *)D_88234950 + 12) = 0;
            }
        } else {
            func_88002720((u8 *)D_88234950 + 16, 3, (u8 *)D_88234950 + 20);
        }
    } else {
        if (*(u16 *)((u8 *)D_80087200 + 8) & B_BUTTON) {
            func_800226C0(72);
            *(s32 *)((u8 *)D_88234950 + 12) = 1;
        } else if (*(u16 *)((u8 *)D_80087200 + 8) & A_BUTTON) {
            func_800226C0(71);
            func_88208010(*(u8 *)D_88234950, *((u8 *)D_88234950 + 17), list[7]);
            func_8822DC34();
        } else if (mode == 1 || mode == 2) {
            func_88002720(list + 6, *(u16 *)(list + 4), list + 8);
        }
    }
    mode = *(s16 *)((u8 *)D_88234950 + 16);
    if (mode != 1 && mode != 2) {
        (*(u8 **)((u8 *)D_88234950 + 8))[28] = 150;
        (*(u8 **)((u8 *)D_88234950 + 8))[29] = 150;
        (*(u8 **)((u8 *)D_88234950 + 8))[30] = 130;
    } else {
        (*(u8 **)((u8 *)D_88234950 + 8))[28] = 220;
        (*(u8 **)((u8 *)D_88234950 + 8))[29] = 220;
        (*(u8 **)((u8 *)D_88234950 + 8))[30] = 180;
    }
}

typedef struct {
    s32 enabled;
    u8 *flags;
} F29TextMask;
extern Gfx *D_800D0510;
extern Gfx D_80094E38[];
extern Gfx D_80094F50[];
extern u8 *D_88A01C30;
extern u8 *D_88A01C34;
extern char D_88234540[];
extern void func_88002BA0(u8, u8, u8);
extern s32 func_8004D334(s32, s32);
extern void func_8004D40C(s32);
extern void func_8004D5B8(s32, s32, s32, const char *, ...);
extern void func_88000FC4(s32, s32, s32, s32, s16, s16);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_88002820(s16, s16, s8, u8 **, u16, s16, F29TextMask *);
extern void func_800499EC(void);
extern void func_880009A8(s32, s16, s16, s16, s16, s16, s16);
extern void func_8004B314(s32, s32, s32, s32);
// Draw the menu and selected list, then mark the focused row.
void LabPC_DrawListChoiceDialog(void) {
    u32 i;
    s16 x;
    s16 y;
    s16 cursor_y;
    u8 *list;
    u8 *entry;
    s16 row;

    switch (*(s16 *)((u8 *)D_88234950 + 16)) {
    case 1:
        entry = D_88A01C34 + 24 * D_88A01C30[16];
        list = (u8 *)D_88234950 + 0x34;
        break;
    case 2:
        entry = D_88A01C34 + 24 * D_88A01C30[16] + 24 * D_88A01C30[36];
        list = (u8 *)D_88234950 + 0x44;
        break;
    }
    gSPDisplayList(D_800D0510++, D_80094E38);
    func_88002BA0(255, 255, 255);
    func_8004D334(239, 0);
    func_8004D40C(2);
    func_8004D5B8(*(s16 *)((u8 *)D_88234950 + 0x2E), *(s16 *)(*(u8 **)((u8 *)D_88234950 + 4) + 14) + 19,
        0, D_88234540, D_88A01C34[21], D_88A01C34[20]);
    if (*(s16 *)((u8 *)D_88234950 + 16) == 1 || *(s16 *)((u8 *)D_88234950 + 16) == 2) {
        x = *(u16 *)((u8 *)D_88234950 + 0x5C) + *(s16 *)(*(u8 **)((u8 *)D_88234950 + 8) + 12) + 30;
        y = *(s16 *)(*(u8 **)((u8 *)D_88234950 + 8) + 14) + 12;
        for (i = 0; i < *(u16 *)(list + 4); i++) {
            func_88000FC4(x, y, 1, 2, entry[21], entry[20]);
            y += 20;
            entry += 24;
        }
    }
    gSPDisplayList(D_800D0510++, D_80094F50);
    func_800498C4();
    func_800496A4(4, 1);
    if (*(s16 *)((u8 *)D_88234950 + 16) == 1 || *(s16 *)((u8 *)D_88234950 + 16) == 2) {
        func_88002820(*(s16 *)(*(u8 **)((u8 *)D_88234950 + 8) + 12) + 24,
            *(s16 *)(*(u8 **)((u8 *)D_88234950 + 8) + 14) + 11, 0,
            *(u8 ***)list, *(u16 *)(list + 4), *(s16 *)((u8 *)D_88234950 + 0x5A), (F29TextMask *)(list + 8));
    }
    x = *(s16 *)(*(u8 **)((u8 *)D_88234950 + 4) + 12) + 15;
    y = *(s16 *)(*(u8 **)((u8 *)D_88234950 + 4) + 14) + 13;
    func_800496A4(8, 1);
    func_88002820(x, y, 0, (u8 **)((u8 *)D_88234950 + 0x20), 3, 6, (F29TextMask *)((u8 *)D_88234950 + 20));
    func_800499EC();
    cursor_y = y;
    func_880009A8(*(s32 *)((u8 *)D_88234950 + 12), x, (cursor_y += 26 * *(s16 *)((u8 *)D_88234950 + 16)),
        *(s16 *)((u8 *)D_88234950 + 0x2C), 20, 5, 5);
    if (*(s32 *)((u8 *)D_88234950 + 12) == 0) {
        row = (*(s16 *)((u8 *)D_88234950 + 16) == 1) ? *(s16 *)((u8 *)D_88234950 + 0x3A) : *(s16 *)((u8 *)D_88234950 + 0x4A);
        func_8004B314(*(s16 *)(*(u8 **)((u8 *)D_88234950 + 8) + 12) + 19,
            20 * row + *(s16 *)(*(u8 **)((u8 *)D_88234950 + 8) + 14) + 6,
            *(u16 *)((u8 *)D_88234950 + 0x5E) + 10, 26);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A03C0/func_8822E290.s")
#endif
