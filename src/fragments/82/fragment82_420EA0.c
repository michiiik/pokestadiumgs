#include "global.h"


#ifdef VERSION_US
extern u8 D_82D06F80;
void func_82D00020(u8 arg0) {
    D_82D06F80 = arg0;
}

s32 func_82D00030(u8 *arg0, u8 arg1) {
    s32 byteIndex;
    s32 bitIndex;
    if (arg1-- == 0) return 0;
    byteIndex = arg1 / 8;
    bitIndex = arg1 % 8;
    return (arg0[byteIndex] & (1 << (7 - bitIndex))) != 0;
}

void func_82D000A0(u8 *arg0, u8 arg1) {
    s32 byteIndex;
    s32 bitIndex;
    if (arg1-- == 0) return;
    byteIndex = arg1 / 8;
    bitIndex = arg1 % 8;
    arg0[byteIndex] ^= 1 << (7 - bitIndex);
}

typedef struct Fragment82DeckEntryFlags {
    u8 bit7 : 1;
    u8 bit6 : 1;
    u8 bit5 : 1;
    u8 bit4 : 1;
    u8 bit3 : 1;
    u8 bit2 : 1;
    u8 bits1_0 : 2;
} Fragment82DeckEntryFlags;
typedef struct Fragment82DeckEntry {
    u8 unk_00[20];
    u8 species_mask[32];
    u16 unk_34;
    u8 unk_36, unk_37;
    u16 unk_38;
    u8 unk_3A[6];
    Fragment82DeckEntryFlags flags;
    u8 unk_41[3];
} Fragment82DeckEntry;
typedef char Fragment82DeckEntrySizeCheck[
    (sizeof(Fragment82DeckEntry) == 68 && sizeof(Fragment82DeckEntryFlags) == 1) ? 1 : -1];

// The species mask stores 256 bits, including the unused tail bits.
void SpeciesMask_Invert_fragment82(u8 *mask) {
    s32 i;
    for (i = 0; i < 32; i++) {
        mask[i] = ~mask[i];
    }
}

extern s32 func_82D00030(u8 *, u8);
s32 func_82D00158(u8 *arg0) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 1; i != 0xFC; i++) {
        if (func_82D00030(arg0, i) != 0) {
            count++;
        }
    }
    return count & 0xFFFF;
}

extern void func_800226C0(s32);
extern u16 D_82D23D8A;
void MenuSelection_StepSkipping_fragment82(s8 *selection, u8 first, u8 last, u8 skip) {
    s8 original = *selection;
    if (D_82D23D8A & 0x800) {
        (*selection)--;
        if (*selection < first) {
            *selection = last;
        }
        if (*selection == skip) {
            (*selection)--;
            if (*selection < first) {
                *selection = last;
            }
        }
        if (original != *selection) {
            func_800226C0(1);
        }
    } else if (D_82D23D8A & 0x400) {
        (*selection)++;
        if (*selection > last) {
            *selection = first;
        }
        if (*selection == skip) {
            (*selection)++;
            if (*selection > last) {
                *selection = first;
            }
        }
        if (original != *selection) {
            func_800226C0(1);
        }
    }
}

extern u16 D_82D23D8A;
extern void func_800226C0(s32);
s32 func_82D002CC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 flags = D_82D23D8A;
    s32 original = arg0;

    if ((flags & 0x800) != 0) {
        arg0 += arg1;
        if (arg0 > arg3) {
            arg0 = arg3;
        }
    } else if ((flags & 0x400) != 0) {
        arg0 -= arg1;
        if (arg0 < arg2) {
            arg0 = arg2;
        }
    }
    if (original != arg0) {
        func_800226C0(0x13);
    }
    return arg0;
}

extern s32 Deck_ReadEntries(u8 *, s32, u8 *);
extern s8 * HAL_Strcpy(s8 *, s8 *);
extern u8 * func_8006218C(s32, s32, s32, s32);
extern void func_80062304(u8 *);
extern s8 D_82D23838[];
extern u8 D_82D23938;
extern u8 D_82D2393C[];
extern u8 D_82D23B60[];
void DeckMenu_LoadEntries_fragment82(void) {
    typedef struct Fragment82WordDeckArchive {
        u32 header;
        Fragment82DeckEntry entries[8];
    } Fragment82WordDeckArchive;
    typedef char ArchiveSizeCheck[(sizeof(Fragment82WordDeckArchive) == 548) ? 1 : -1];
    s32 i;
    u8 *handle;
    handle = func_8006218C(24, 0, 0, 0);
    D_82D23938 = Deck_ReadEntries(D_82D2393C, 8, handle);
    for (i = 0; i < D_82D23938; i++) {
        HAL_Strcpy(D_82D23838 + i * 20, (s8 *)&((Fragment82DeckEntry *)D_82D2393C)[i]);
    }
    func_80062304(handle);
    *(Fragment82WordDeckArchive *)D_82D23B60 = *(Fragment82WordDeckArchive *)&D_82D23938;
}

extern u8 D_82D23938;
extern u8 D_82D2393C[];
extern u8 *func_8006218C(s32, s32, s32, s32);
extern void func_8006249C(void *, s32, u8 *);
extern void func_80062304(u8 *);
void func_82D00444(void) {
    u8 *sp1C;

    sp1C = func_8006218C(0x18, 0, 0, 1);
    func_8006249C(D_82D2393C, D_82D23938, sp1C);
    func_80062304(sp1C);
}
void func_82D00444_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D0049C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D00590.s")

extern u8 D_82D07428[];
void func_82D00590(u8);
void func_82D06B34(s32, s32, s32);
void func_82D006B8(void) {
    D_82D07428[0x10E] = 0;
    D_82D07428[0xE] = 0;
    *(u16 *)(D_82D07428 + 4) = 0;
    func_82D00590(D_82D07428[0x10] = 1);
    func_82D06B34(9, 1, 0);
}

void DeckEntry_InitDefaults_fragment82(Fragment82DeckEntry *entry) {
    s32 i;
    entry->unk_36 = 1;
    entry->unk_37 = 100;
    entry->unk_38 = 300;
    entry->flags.bit7 = 0;
    entry->flags.bit6 = 0;
    entry->flags.bit5 = 0;
    entry->flags.bit2 = 1;
    entry->flags.bit3 = 1;
    entry->unk_34 = 14;
    for (i = 0; i < 32; i++) {
        entry->species_mask[i] = 0xFF;
    }
}

s32 MenuName_HasNonspace_fragment82(char *text) {
    char *cursor = text;
    while (*cursor != 0) {
        if (*cursor++ != ' ') {
            return 1;
        }
    }
    return 0;
}

typedef struct Fragment82NameState {
    u8 kind;
    s8 selection, digit, secondary_selection;
    u8 unk_04[2], name_index, name_count;
    s8 names[9][20];
} Fragment82NameState;
typedef struct Fragment82SettingsFlagWord {
    u32 bits31_27 : 5;
    u32 flag26 : 1;
    u32 bits25_0 : 26;
} Fragment82SettingsFlagWord;
typedef char Fragment82SettingsFlagsSizeCheck[(sizeof(Fragment82SettingsFlagWord) == 4) ? 1 : -1];
extern Fragment82SettingsFlagWord D_82D23930;
extern s8 D_82D238D8[], D_82D238F0[];
extern s8 D_82D23838[];
extern u8 D_82D23B60[];
extern void func_887009A0(void);
extern s8 *HAL_Strcpy(s8 *, s8 *);
extern void func_82D0087C(void), func_82D0049C(void);
extern s32 Deck_ReadEntries(u8 *, s32, u8 *);
extern s32 MenuName_HasNonspace_fragment82(char *text);
extern void func_82D06B34(s32, s32, s32);
extern u8 D_82D23830;
extern u8 D_82D23D84;
void DeckName_CommitEdit_fragment82(void) {
    func_887009A0();
    if (MenuName_HasNonspace_fragment82((char *)D_82D238D8) != 0) {
        HAL_Strcpy(((Fragment82NameState *)&D_82D23830)->names[0] + ((Fragment82NameState *)&D_82D23830)->name_index * 20, D_82D238D8);
        HAL_Strcpy(D_82D238F0, ((Fragment82NameState *)&D_82D23830)->names[0] + ((Fragment82NameState *)&D_82D23830)->name_index * 20);
    }
    D_82D23D84 = 2;
    D_82D23830 = 4;
    func_82D06B34(8, 6, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D0087C.s")

extern void MenuSelection_StepSkipping_fragment82(s8 *selection, u8 first, u8 last, u8 skip);
extern s8 D_82D23831;
extern u16 D_82D23D88;
void DeckMenu_HandleSettingsInput_fragment82(void) {
    u8 skip;
    skip = D_82D23930.flag26 ? 255 : 5;
    MenuSelection_StepSkipping_fragment82(&D_82D23831, 0, 6, skip);
    if (D_82D23D88 & 0x8000) {
        func_82D0087C();
    } else if (D_82D23D88 & 0x4000) {
        D_82D23831 = 6;
        func_82D0087C();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D00C34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D010F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D0125C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D01590.s")

extern u8 D_82D23926, D_82D23927;
extern u16 D_82D23928;
extern void func_800226C0(s32);
extern s32 func_82D002CC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_82D23830;
extern u8 D_82D23D84;
extern u16 D_82D23D88;
extern u16 D_82D23D8A;
void DeckMenu_EditBoundedValue_fragment82(void) {
    u16 lower, upper;
    if (D_82D23D8A & 0x200) {
        ((Fragment82NameState *)&D_82D23830)->digit--;
        if (((Fragment82NameState *)&D_82D23830)->digit < 0) ((Fragment82NameState *)&D_82D23830)->digit = 2;
        func_800226C0(1);
    } else if (D_82D23D8A & 0x100) {
        ((Fragment82NameState *)&D_82D23830)->digit++;
        if (((Fragment82NameState *)&D_82D23830)->digit >= 3) ((Fragment82NameState *)&D_82D23830)->digit = 0;
        func_800226C0(1);
    }
    lower = D_82D23926 * 3;
    upper = D_82D23927 * 3;
    switch (((Fragment82NameState *)&D_82D23830)->digit) {
    case 0:
        D_82D23928 = func_82D002CC(D_82D23928, 100, lower, upper);
        break;
    case 1:
        D_82D23928 = func_82D002CC(D_82D23928, 10, lower, upper);
        break;
    case 2:
        D_82D23928 = func_82D002CC(D_82D23928, 1, lower, upper);
        break;
    }
    if (D_82D23D88 & 0xC000) {
        D_82D23D84 = 2;
        ((Fragment82NameState *)&D_82D23830)->kind = 4;
        func_800226C0(146);
    }
}

extern u8 D_82D07420[];
extern s8 D_82D07421;
extern u8 D_82D2382A;
extern u8 D_82D23830;
extern u8 D_82D23D84;
extern void func_800226C0(s32);
extern void func_82D06B34(s32, s32, s32);
void func_82D019D8(void) {
    s8 var_v0;

    D_82D23830 = 1;
    D_82D07420[0] = 1;
    D_82D23D84 = 7;
    var_v0 = D_82D07420[1];
    if (var_v0 != 0) {
        func_82D06B34(2, 2, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 1) {
        func_82D06B34(3, 2, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 2) {
        func_82D06B34(4, 2, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 3) {
        func_82D06B34(5, 2, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 4) {
        func_82D06B34(6, 2, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D01AAC.s")

extern void func_82D06B34(s32, s32, s32);
void func_82D01D68(void) {
    s8 var_v0;

    D_82D23830 = 0;
    D_82D2382A = 0x17;
    D_82D07420[0] = 0;
    D_82D23D84 = 1;
    var_v0 = D_82D07420[1];
    if (var_v0 != 0) {
        func_82D06B34(2, 1, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 1) {
        func_82D06B34(3, 1, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 2) {
        func_82D06B34(4, 1, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 3) {
        func_82D06B34(5, 1, 0);
        var_v0 = D_82D07421;
    }
    if (var_v0 != 4) {
        func_82D06B34(6, 1, 0);
    }
    func_800226C0(3);
}

extern s8 D_82D23831;
extern u16 D_82D23D88;
extern void MenuSelection_StepSkipping_fragment82(s8 *, u8, u8, u8);
extern void func_82D01AAC(void);
void func_82D01E4C(void) {
    s32 flags;

    MenuSelection_StepSkipping_fragment82(&D_82D23831, ((u8 *)&D_82D23830)[4], ((u8 *)&D_82D23830)[5], 0xFF);
    flags = D_82D23D88;
    if (flags & 0x8000) {
        func_82D01AAC();
    } else if (flags & 0x4000) {
        func_82D01D68();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D01EB8.s")

extern u8 D_82D23828;
extern void func_82D01EB8(void);
extern void func_800226C0(s32);
extern void func_82D01D68(void);
extern u8 D_82D23830;
extern u8 D_82D23938;
extern u8 D_82D23D84;
extern u16 D_82D23D88;
extern u16 D_82D23D8A;
void func_82D0201C(void) {
    if (D_82D23D8A & 0x300) {
        ((u8 *)&D_82D23828)[1] = (((u8 *)&D_82D23828)[1] + 1) & 1;
        func_800226C0(1);
    }
    if (D_82D23D88 & 0xC000) {
        if ((D_82D23D88 & 0x8000) && ((u8 *)&D_82D23828)[1] == 0) {
            func_82D01EB8();
            if (D_82D23938 > 0) {
                ((u8 *)&D_82D23830)[4] = 0;
                ((u8 *)&D_82D23830)[5] = D_82D23938 - 1;
                ((u8 *)&D_82D23830)[1] = 0;
                ((u8 *)&D_82D23830)[0] = 1;
                ((u8 *)&D_82D23828)[2] = 0x1C;
                ((u8 *)&D_82D23828)[0] = 0;
                D_82D23D84 = 7;
            } else {
                func_82D01D68();
                ((u8 *)&D_82D23828)[0] = 0;
            }
            func_800226C0(0x43);
        } else {
            ((u8 *)&D_82D23828)[2] = 0x1C;
            ((u8 *)&D_82D23828)[0] = 0;
            ((u8 *)&D_82D23830)[0] = 1;
            D_82D23D84 = 7;
            func_800226C0(3);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D0213C.s")

extern s8 D_82D23833;
extern u16 D_82D23D88;
extern void MenuSelection_StepSkipping_fragment82(s8 *, u8, u8, u8);
extern void func_82D0213C(void);
extern void func_800226C0(s32);
void func_82D022D0(void) {
    MenuSelection_StepSkipping_fragment82(&D_82D23833, 0, ((((u8 *)&D_82D23830)[7] - 1) & 0xFF), ((u8 *)&D_82D23830)[1]);
    if (D_82D23D88 & 0xC000) {
        if (D_82D23D88 & 0x8000) {
            func_82D0213C();
            *(s8 *)((u8 *)&D_82D23830 + 1) = *(s8 *)((u8 *)&D_82D23830 + 3);
            func_800226C0(0x44);
        } else {
            func_800226C0(3);
        }
        D_82D23D84 = 7;
        ((u8 *)&D_82D23830)[0] = 1;
        D_82D2382A = 0x1D;
    }
}

extern u16 D_82D23D88; extern u8 D_82D2382A; extern u8 D_82D23D84; void func_82D02380(void) { if (D_82D23D88 != 0) { D_82D2382A = 0x17; D_82D23D84 = 1; } }

extern void func_82D06B34(s32, s32, s32);

void func_82D023AC(void) {
    if (D_82D23D88 != 0) {
        D_82D23D84 = 4;
        func_82D06B34(0xA, 7, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/82/fragment82_420EA0/func_82D023EC.s")

extern void MenuSelection_StepSkipping_fragment82(s8 *, u8, u8, u8);
extern void func_82D023EC();
extern s8 D_82D07421;
void func_82D0265C(void) {
    MenuSelection_StepSkipping_fragment82(&D_82D07421, 0, 4, 0xFF);
    if (D_82D23D88 & 0x8000) {
        func_82D023EC();
        return;
    }
    if (D_82D23D88 & 0x4000) {
        D_82D07421 = 4;
        func_82D023EC();
    }
}

extern void func_82D0265C(void), func_88700CE4(void);
extern void func_82D0125C(void), func_82D01590(void), DeckMenu_EditBoundedValue_fragment82(void);
extern void func_82D01E4C(void), func_82D0201C(void), func_82D022D0(void);
extern void func_82D02380(void), func_82D023AC(void);
extern u8 D_82D06F80;
extern void DeckMenu_HandleSettingsInput_fragment82(void);
extern u8 D_82D23D84;
void DeckMenu_DispatchState_fragment82(void) {
    switch (D_82D23D84) {
    case 1:
        func_82D0265C();
        break;
    case 2:
        DeckMenu_HandleSettingsInput_fragment82();
        break;
    case 3:
        func_88700CE4();
        break;
    case 4:
        func_82D0125C();
        break;
    case 5:
        func_82D01590();
        break;
    case 6:
        DeckMenu_EditBoundedValue_fragment82();
        break;
    case 7:
        func_82D01E4C();
        break;
    case 8:
        func_82D0201C();
        break;
    case 9:
        func_82D022D0();
        break;
    case 10:
        func_82D02380();
        break;
    case 11:
        func_82D023AC();
        break;
    case 12:
        if (D_82D06F80 != 0) {
            D_82D23D84 = 13;
        }
        break;
    }
}

extern void *D_80087200;
extern u16 D_82D23D86;
extern u16 D_82D23D8A;
void func_80064D28(void);
void func_82D027D4(void) {
    func_80064D28();
    if (D_82D06F80 != 0) {
        D_82D23D86 = (*(u16 *)((u8 *)(D_80087200) + (6)));
        D_82D23D88 = (*(u16 *)((u8 *)(D_80087200) + (8)));
        D_82D23D8A = (*(u16 *)((u8 *)(D_80087200) + (0xC)));
        return;
    }
    D_82D23D86 = 0;
    D_82D23D88 = 0;
    D_82D23D8A = 0;
}

extern void func_80008648();
extern void BgStage_DrawFrame();
extern void DeckMenu_DispatchState_fragment82(void);
extern void func_82D027D4();
extern void func_82D05C90();
extern void func_82D068A0();
void func_82D0284C(void) {
    do {
        func_82D027D4();
        DeckMenu_DispatchState_fragment82();
        func_82D068A0();
        BgStage_DrawFrame();
        func_82D05C90();
        func_80008648();
    } while (D_82D23D84 != 0xD);
}

extern void func_82D06C9C(s32, u8 *);
extern u8 D_82D23837;
extern void DeckMenu_LoadEntries_fragment82(void);
extern void func_82D06B34(s32, s32, s32);
extern u8 D_82D07420[];
extern u8 D_82D07428[];
extern u8 D_82D23828;
extern u8 D_82D2382A;
extern u8 D_82D23830;
extern u8 D_82D23938;
extern u8 D_82D23D84;
void func_82D028B8(void) {
    s8 anchor;
    D_82D23D84 = 1;
    D_82D2382A = 0x17;
    func_82D06C9C(2, D_82D07420);
    func_82D06C9C(3, D_82D07420);
    func_82D06C9C(4, D_82D07420);
    func_82D06C9C(5, D_82D07420);
    func_82D06C9C(6, D_82D07420);
    func_82D06C9C(9, D_82D07428);
    func_82D06C9C(7, &D_82D23828);
    func_82D06C9C(8, &D_82D23830);
    func_82D06B34(2, 1, 0);
    func_82D06B34(3, 1, 3);
    func_82D06B34(4, 1, 6);
    func_82D06B34(5, 1, 9);
    func_82D06B34(6, 1, 0xC);
    func_82D06B34(7, 1, 0);
    func_82D06B34(8, 1, 0);
    DeckMenu_LoadEntries_fragment82();
    D_82D23837 = D_82D23938;
}

extern u8 D_82D23B60[];
extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void func_82D028B8(void);
extern void func_82D06D50(void);
extern void func_80008624(void);
extern void StageLoader_WaitForRetrace(void);
extern s32 _bcmp(const void *, const void *, s32);
extern void func_82D0284C(void);
s32 fragment82_main(s32 arg0, s32 arg1) {
    main_pool_push_state(0x524C4544);
    func_82D028B8();
    func_82D06D50();
    func_80008624();
    func_82D0284C();
    StageLoader_WaitForRetrace();
    main_pool_pop_state(0x524C4544);
    return _bcmp(&D_82D23938, D_82D23B60, 0x224) != 0;
}
#pragma C_FUNCTION_PADDING(8)
#endif
