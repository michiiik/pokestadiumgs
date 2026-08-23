#include "global.h"


#ifdef VERSION_US
typedef struct SaveRecordEntry {
    u32 flags;
    u8 *backup;
    u8 *active;
} SaveRecordEntry;

extern SaveRecordEntry D_801281C0[];
extern u8 *D_801281C4[];
extern u8 *D_801281C8[];
extern s32 D_800972C0;

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050BE0.s")

void *func_80050CAC(s32 index, s32 active) {
    SaveRecordEntry *entry = &D_801281C0[index];

    if ((entry->flags & 1) != 0) {
        return active != 0 ? entry->active : entry->backup;
    }
    return NULL;
}

void *func_80050CF8(s32 index) {
    if (index >= 0 && index < 4) {
        extern void *D_800972B0[];
        return D_800972B0[index];
    }
    return NULL;
}

s32 func_80050D20(s32 type, s32 value) {
    switch (type) {
        case 0x10:
            if (value >= 0) {
                return value >> 2;
            }
            return (value + 3) >> 2;
        case 0x11:
            return value > 0 ? 2 : 1;
        case 0x16:
        case 0x17:
            return 1;
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
            return 3;
        default:
            return -1;
    }
}

s32 func_80050DE4(s32 type) {
    static const s32 sizes[] = {
        0x180, 0x4D8, 0x20C, 0x54, 0x60, 0x1A0, 0x936, 0x58A,
        0x250, 0x1B10, 0x490, 0xBD0, 0x3F0, 0x648, 0x50,
    };

    if (type >= 0x10 && type <= 0x1E) {
        return sizes[type - 0x10];
    }
    return 0;
}

static u8 *Save_GetTypedBase(s32 active, s32 type, s32 value) {
    s32 bank = func_80050D20(type, value);

    return active != 0 ? D_801281C8[bank] : D_801281C4[bank];
}

u8 *func_80050E88(s32 active, s32 record, s32 field) {
    s32 group = record % 4;
    u8 *base = Save_GetTypedBase(active, 0x10, record);

    return base + group * 0xF00 + field * 0x180;
}

u8 *func_80050F60(s32 active, s32 record) {
    s32 bank = func_80050D20(0x11, record);
    s32 entry = record > 0 ? record - 1 : record;
    u8 *base = active != 0 ? D_801281C8[bank] : D_801281C4[bank];

    return base + entry * 0x4D8 + (bank == 2 ? 0 : 0x1E00);
}

u8 *func_80051028(s32 active, s32 record) {
    u8 *base = Save_GetTypedBase(active, 0x12, -1);

    return base + record * 0x20C + 0x200;
}

u8 *func_800510CC(s32 active) {
    return Save_GetTypedBase(active, 0x13, -1) + 0x618;
}

u8 *func_80051138(s32 active) {
    return Save_GetTypedBase(active, 0x14, -1) + 0x1A0;
}

u8 *func_800511A4(s32 active) {
    return Save_GetTypedBase(active, 0x15, -1);
}

u8 *func_80051208(s32 active) {
    return Save_GetTypedBase(active, 0x16, -1) + 0x22D8;
}

u8 *func_80051274(s32 active) {
    return Save_GetTypedBase(active, 0x17, -1) + 0x2C0E;
}

u8 *func_800512E0(s32 active) {
    return Save_GetTypedBase(active, 0x18, -1) + 0x66C;
}

u8 *func_8005134C(s32 active) {
    return Save_GetTypedBase(active, 0x19, -1) + 0x8BC;
}

u8 *func_800513B8(s32 active) {
    return Save_GetTypedBase(active, 0x1A, -1) + 0x23CC;
}

u8 *func_80051424(s32 active) {
    return Save_GetTypedBase(active, 0x1B, -1) + 0x285C;
}

u8 *func_80051490(s32 active) {
    return Save_GetTypedBase(active, 0x1C, -1) + 0x342C;
}

u8 *func_800514FC(s32 active) {
    return Save_GetTypedBase(active, 0x1D, -1) + 0x381C;
}

u8 *func_80051568(s32 active) {
    return Save_GetTypedBase(active, 0x1E, -1) + 0x3E64;
}

u16 Save_Checksum(u8 *data, s32 length) {
    u32 sum = 0;
    s32 count = length - 3;

    while (count-- > 0) {
        sum = (sum + *data++) & 0xFFFF;
    }

    return (u16)sum;
}

void Save_WriteFooter(u8 *data, s32 length, s32 valid) {
    u8 *footer = data + length - 6;
    u16 checksum;

    if (valid != 0) {
        *(u16 *)(footer + 0) = 0x5033;
        *(u16 *)(footer + 2) = 0x7630;
        checksum = Save_Checksum(footer, length);
    } else {
        *(u16 *)(footer + 0) = 0x5858;
        *(u16 *)(footer + 2) = 0x5858;
        checksum = Save_Checksum(footer, length) ^ 0xFF;
    }

    *(u16 *)(footer + 4) = checksum;
}

void Save_WriteRecord(void *src, void *dst, s32 length, s32 index) {
    bcopy(src, dst, length);
    D_801281C0[index].flags |= 2;
}

void Save_CommitRecord(u8 *data, s32 length, s32 unused, s32 index) {
    if ((data[0] & 2) != 0) {
        data[0] &= 0xFD;
        Save_WriteFooter(data, length, 1);
        D_801281C0[index].flags |= 2;
    }
}

void Save_InvalidateRecord(u8 *data, s32 length, s32 unused, s32 index) {
    if ((data[0] & 2) != 0) {
        Save_WriteFooter(data, length, 0);
        D_801281C0[index].flags |= 2;
    }
}

void Save_RestoreRecord(u8 *data, s32 length, s32 index) {
    SaveRecordEntry *entry = &D_801281C0[index];
    bcopy(entry->active + (data - entry->backup), data, length);
}

void Save_ClearRecord(u8 *data, s32 length, s32 index) {
    bzero(data, length);
    data[0] |= 2;
    D_801281C0[index].flags |= 2;
}

void func_80051830(void *arg) {
    func_80061248(arg);
    func_800619E8(arg);
    *(u16 *)((u8 *)arg + 0x26) = *(u16 *)((u8 *)arg + 0x28);
}

void func_80051864(void *arg, void *data) {
    func_800615D0(data);
}

void func_80051890(void *arg, u8 *src) {
    u8 *dst = arg;

    bzero(dst, 0x44);
    dst[0x36] = src[0];
    dst[0x37] = src[1];
    *(u16 *)(dst + 0x38) = *(u16 *)(src + 2);
    *(s16 *)(dst + 0x3A) = 0x17;
    *(s16 *)(dst + 0x3C) = -1;
    *(s16 *)(dst + 0x3E) = -1;
    dst[0x40] = (dst[0x40] & 0x7F) | (((s8)src[4] << 7) & 0x80);
    dst[0x40] = (dst[0x40] & 0xBF) | (((s8)src[5] << 6) & 0x40);
    dst[0x40] = (dst[0x40] & 0xDF) | (((s8)src[6] << 5) & 0x20);
    dst[0x40] = (dst[0x40] & 0xEF) | (((s8)src[7] << 4) & 0x10);
    dst[0x40] = (dst[0x40] & 0xF7) | (((s8)src[8] << 3) & 8);
    dst[0x40] = (dst[0x40] & 0xFB) | (((s8)src[9] << 2) & 4);
    *(s16 *)(dst + 0x34) = (s8)src[0xB];
    bcopy(src + 0x14, dst + 0x14, 0x20);
    bcopy(src + 0x34, dst, 0x14);
}

void func_800519AC(u8 *src, void *arg) {
    u8 *dst = arg;

    bzero(dst, 0x48);
    dst[0] = src[0x36];
    dst[1] = src[0x37];
    *(u16 *)(dst + 2) = *(u16 *)(src + 0x38);
    dst[4] = (src[0x40] >> 7) & 1;
    dst[5] = (src[0x40] >> 6) & 1;
    dst[6] = (src[0x40] >> 5) & 1;
    dst[7] = (src[0x40] >> 4) & 1;
    dst[8] = (src[0x40] >> 3) & 1;
    dst[9] = (src[0x40] >> 2) & 1;
    dst[0xB] = src[0x34];
    bcopy(src + 0x14, dst + 0x14, 0x20);
    bcopy(src, dst + 0x34, 0x14);
}

s32 func_80051A8C(s32 type, s32 record, s32 mask) {
    u8 *data = NULL;

    switch (type) {
        case 0x10:
            data = func_80050E88(0, D_800972C0, record);
            break;
        case 0x11:
            data = func_80050F60(0, record);
            break;
        case 0x12:
            data = func_80051028(0, record);
            break;
        case 0x13:
            data = func_800510CC(0);
            break;
        case 0x14:
            data = func_80051138(0);
            break;
        case 0x15:
            data = func_800511A4(0);
            break;
        case 0x16:
            data = func_80051208(0);
            break;
        case 0x17:
            data = func_80051274(0);
            break;
        case 0x18:
            data = func_800512E0(0);
            break;
        case 0x19:
            data = func_8005134C(0);
            break;
        case 0x1A:
            data = func_800513B8(0);
            break;
        case 0x1B:
            data = func_80051424(0);
            break;
        case 0x1C:
            data = func_80051490(0);
            break;
        case 0x1D:
            data = func_800514FC(0);
            break;
        case 0x1E:
            data = func_80051568(0);
            break;
    }

    return data != NULL ? ((*(u8 *)data & mask) != 0) : 0;
}

/**
 * Set bits in the header byte of a typed save record.
 *
 * The record type is the same 0x10..0x1E selector used by the typed address
 * accessors above.  Type 0x10 additionally uses the current save slot and
 * the caller-provided record index; all other types use the record argument
 * only where their accessor requires it.
 */
s32 func_80051BF0(s32 type, s32 record, s32 mask) {
    u8 *data = NULL;

    switch (type) {
        case 0x10:
            data = func_80050E88(0, D_800972C0, record);
            break;
        case 0x11:
            data = func_80050F60(0, record);
            break;
        case 0x12:
            data = func_80051028(0, record);
            break;
        case 0x13:
            data = func_800510CC(0);
            break;
        case 0x14:
            data = func_80051138(0);
            break;
        case 0x15:
            data = func_800511A4(0);
            break;
        case 0x16:
            data = func_80051208(0);
            break;
        case 0x17:
            data = func_80051274(0);
            break;
        case 0x18:
            data = func_800512E0(0);
            break;
        case 0x19:
            data = func_8005134C(0);
            break;
        case 0x1A:
            data = func_800513B8(0);
            break;
        case 0x1B:
            data = func_80051424(0);
            break;
        case 0x1C:
            data = func_80051490(0);
            break;
        case 0x1D:
            data = func_800514FC(0);
            break;
        case 0x1E:
            data = func_80051568(0);
            break;
    }

    if (data == NULL) {
        return 0;
    }

    *data |= (u8)mask;
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051D64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80052150.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005253C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80052928.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80052ECC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800530DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/Save_ResetAndCommitTypedRecord.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005314C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053230.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800532C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800532F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/Deck_IsSaveEntryPresent.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800533A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053440.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800534FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053524.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053584.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800535D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005370C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053808.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053908.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053A30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053A50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053AC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053B04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053B38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053DDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053E08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053E8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053ECC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053F04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054210.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054248.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800542B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800542E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005431C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005437C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054488.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005453C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800545B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054668.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800546E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054794.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800547F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005487C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800548C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005493C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054974.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800549DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054A24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054AA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054AF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054B7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054CC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054E10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054E48.s")

u32 func_80055028(void) {
    u32 mask = 0;
    s32 bank;

    for (bank = 0; bank < 4; bank++) {
        if (func_80054E48(bank) != 0) {
            mask |= 1u << bank;
        }
    }

    return mask;
}

void Save_ResetBank(void *unused, u32 bankId) {
    SaveRecordEntry *entry;
    u32 index;

    if (bankId < 0x424E4B30 || bankId >= 0x424E4B34) {
        return;
    }

    index = (bankId - 0x424E4B30) * 5;
    entry = &D_801281C0[index];
    entry->flags &= ~3u;
    entry->backup = NULL;
    entry->active = NULL;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800550E8.s")

s32 func_800551EC(u8 *data, s32 length) {
    u8 *footer = data + length - 6;

    if (*(u16 *)(footer + 0) != 0x5033 || *(u16 *)(footer + 2) != 0x7630) {
        return 0;
    }

    return *(u16 *)(footer + 4) == Save_Checksum(data, length);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055260.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800555B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005565C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005577C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800557E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055948.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055A34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055A74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055A9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055B14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/Deck_FindFirstFreeTeamSlot.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/Deck_CompactRegisteredTeams.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055CCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055D44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055DC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055E54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055F6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80056024.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800560F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80056184.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800561E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800562B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005633C.s")
#endif
