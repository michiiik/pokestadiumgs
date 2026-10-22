#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82600A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82600BA0.s")

extern void func_800619E8(void *);
s32 func_80061B88(u8, u8, void *);

void func_82600CF4(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + (8))) = func_80061B88((*(u8 *)((u8 *)(arg0) + (0))), (*(u8 *)((u8 *)(arg0) + (0x1D))), arg0);
    func_800619E8(arg0);
    (*(u16 *)((u8 *)(arg0) + (0x26))) = (u16) (*(u16 *)((u8 *)(arg0) + (0x28)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82600D38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82601070.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82601298.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_8260166C.s")

void func_82601824(void *arg0) {
    u8 *values[4];
    s32 i;

    values[0] = *(u8 **)((u8 *)arg0 + 0xAC) + 0x134;
    values[1] = *(u8 **)((u8 *)arg0 + 0xAC) + 0x1CC;
    values[2] = *(u8 **)((u8 *)arg0 + 0xAC) + 0x264;
    i = 0;
    do {
        if (i != 0) {
            func_8006AF28(i, values[(*(s16 *)(*(u8 **)arg0 + 0xC))]);
        }
        i += 1;
    } while (i != 2);
}

void func_826018BC(void *arg0) {
    u8 *values[4];
    s32 i;
    u8 *temp_v0;

    values[0] = *(u8 **)((u8 *)arg0 + 0xC) + 0x134;
    values[1] = *(u8 **)((u8 *)arg0 + 0xC) + 0x1CC;
    values[2] = *(u8 **)((u8 *)arg0 + 0xC) + 0x264;
    i = 0;
    do {
        temp_v0 = *(u8 **)arg0;
        if (*(s8 *)(temp_v0 + i) == -1) {
            func_8006AED4(i, values[(*(s16 *)(temp_v0 + 0xC))]);
        }
        i += 1;
    } while (i != 2);
}

typedef struct {
    s8 *owners;
    u8 unk_04[8];
    u8 *table;
} RecordTextCopyContext;
typedef struct {
    u8 unk_00[136];
    s16 selection;
} RecordTextSelectionView;
extern void *func_8004C874(s32, s32);
extern void _bcopy(void *, void *, s32);
typedef struct {
    u8 unk_00[52];
    s8 text[12];
    u8 unk_40[24];
} RecordTextEntry88;
typedef struct {
    u8 unk_00[144];
    RecordTextEntry88 groups[4][6];
} RecordTextGridState;
typedef char RecordTextEntrySizeCheck[sizeof(RecordTextEntry88) == 88 ? 1 : -1];
typedef char RecordTextGridSizeCheck[sizeof(RecordTextGridState) == 2256 ? 1 : -1];

void RecordText_CopyUnassignedEntries(void *arg0) {
    RecordTextCopyContext *context = (RecordTextCopyContext *)arg0;
    RecordTextSelectionView *selection;
    s8 *records;
    s8 *record;
    u8 *base;
    u8 *table;
    s8 *result;
    s32 inner;
    s32 outer;
    records = context->owners;
    base = context->table;
    selection = (RecordTextSelectionView *)records;
    outer = 0;
    table = base;
    table += *(s16 *)((u8 *)context + selection->selection * 2 + 24) * 152;
    table += 4;
    record = records;
    do {
        inner = 0;
        if (*record == -1) {
            do {
                result = (s8 *)func_8004C874(table[3] + 76, inner + 33);
                if (result != 0 && *result != 0) {
                    _bcopy(result, ((RecordTextGridState *)records)->groups[outer][inner].text, 12);
                }
                inner++;
            } while (inner != 6);
        }
        outer++;
        record++;
    } while (outer != 4);
}

extern void *func_8004C874(s32, s32);
extern void _bcopy(void *, void *, s32);
void RecordNames_LoadFourSlots(u8 *context, s32 override_names) {
    s32 index;
    s32 selection;
    u8 *table;
    s8 *state;
    s8 *owner;
    u8 *entry;
    void *name;
    table = *(u8 **)(context + 12);
    state = *(s8 **)context;
    selection = *(s16 *)((u8 *)state + 136);
    if (table != 0) {
        entry = ((u8 (*)[152])table)[((s16 *)context)[selection + 12]] + 4;
        index = 0;
        owner = state;
        do {
            if (*owner >= 0 && override_names) {
                name = func_8004C874(42, 87);
                if (name != 0) {
                    _bcopy(name, (u8 *)state + index * 12 + 2256, 12);
                }
            } else if (*owner == -1) {
                name = func_8004C874(42, entry[1] - 1);
                if (name != 0) {
                    _bcopy(name, (u8 *)state + index * 12 + 2256, 12);
                }
            }
            index++;
            owner++;
        } while (index != 4);
    }
}

extern s32 func_8004C594(s32, s32);
extern void *func_8004C8A0(void *, s32, s32, s32);
void RecordNames_FormatTwoSlots(u8 *context) {
    s32 index;
    s32 selection;
    s8 *state;
    u8 *table;
    u8 *record;
    s8 *descriptor;
    u8 *slot_context;
    void *name;
    state = *(s8 **)context;
    selection = *(s16 *)((u8 *)state + 136);
    table = *(u8 **)(context + 12);
    index = 0;
    descriptor = (s8 *)(context + 176);
    slot_context = context;
    record = ((u8 (*)[152])table)[((s16 *)context)[selection + 12]] + 4;
    do {
        if (*(s16 *)(slot_context + 176) < 2) {
            if (descriptor[2] >= 0) {
                func_8004C594(1, descriptor[2] + 1);
                func_8004C8A0((u8 *)state + index * 12 + 2256, 12, 18, 29);
            } else {
                name = func_8004C874(42, record[1] - 1);
                if (name != 0) {
                    _bcopy(name, (u8 *)state + index * 12 + 2256, 12);
                }
            }
        } else {
            func_8004C594(1, descriptor[2] + 1);
            func_8004C594(2, descriptor[3] + 1);
            func_8004C8A0((u8 *)state + index * 12 + 2256, 12, 18, 28);
        }
        index++;
        slot_context += 1064;
        descriptor += 1064;
    } while (index != 2);
}

void RecordNames_LoadTwoSlots(u8 *context) {
    s8 slot;
    u8 *row;
    void *name;
    u8 *teams[2];
    u8 *profiles[3];
    s32 index;
    s8 *state;
    s8 *cursor;
    state = *(s8 **)context;
    teams[0] = *(u8 **)(context + 12) + 4;
    index = 0;
    teams[1] = *(u8 **)(context + 12) + 156;
    profiles[0] = *(u8 **)(context + 12) + 308;
    profiles[1] = *(u8 **)(context + 12) + 460;
    cursor = state;
    profiles[2] = *(u8 **)(context + 12) + 612;
    do {
        slot = *cursor;
        name = 0;
        switch (slot) {
        case -1:
            row = profiles[*(s16 *)(*(u8 **)context + 12)];
            break;
        case -2:
            row = 0;
            break;
        default:
            row = teams[index];
            break;
        }
        if (row != 0) {
            name = func_8004C874(42, row[1] - 1);
        }
        if (name != 0) {
            _bcopy(name, (u8 *)state + index * 12 + 2256, 12);
        }
        index++;
        cursor++;
    } while (index != 2);
}

void RecordNames_LoadSelectedOrDefaultSlots(u8 *context) {
    s32 index;
    s32 selection;
    s8 *state;
    u8 *selected_row;
    u8 *default_row;
    s8 *cursor;
    s8 slot;
    u8 *row;
    void *name;
    default_row = *(u8 **)(context + 12) + 4;
    state = *(s8 **)context;
    index = 0;
    selection = *(s16 *)((u8 *)state + 136);
    selected_row = ((u8 (*)[152])(*(u8 **)(context + 12)))[((s16 *)context)[selection + 12]] + 4;
    cursor = state;
    do {
        slot = *cursor;
        name = 0;
        switch (slot) {
        case -1:
            row = selected_row;
            break;
        case -2:
            row = 0;
            break;
        default:
            row = default_row;
            break;
        }
        if (row != 0) {
            name = func_8004C874(42, row[1] - 1);
        }
        if (name != 0) {
            _bcopy(name, (u8 *)state + index * 12 + 2256, 12);
        }
        index++;
        cursor++;
    } while (index != 2);
}

extern s32 D_82615348[];
extern void func_80049C70(s32 *, s32 *, void *);
void RecordText_SelectAndMeasure(void *context, u8 records[][152]) {
    s32 index;
    s32 width;
    s32 height;
    s32 text_id;
    u8 *cursor;
    u8 *record;
    u8 *dimensions;
    void *resource;
    index = 0;
    cursor = (u8 *)context;
    while (index < *(s16 *)((u8 *)context + 20)) {
        record = records[*(s16 *)(cursor + 24)] + 4;
        if (index < *(s16 *)(*(u8 **)context + 136)) {
            text_id = 39;
        } else {
            text_id = D_82615348[(u32)guRandom() % 3];
        }
        resource = func_8004C874(record[3] + 76, text_id);
        if (resource != 0) {
            *(s16 *)(cursor + 56) = text_id;
            dimensions = (u8 *)context + index * 4;
            func_80049C70(&width, &height, resource);
            *(s16 *)(dimensions + 88) = width;
            *(s16 *)(dimensions + 90) = height;
        }
        index++;
        cursor += 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_826020C0.s")


void func_826026E8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    *(u16 *)(arg0 + 0xA0) = (u16)1;
    *(u16 *)(arg0 + 0xA4) = (u16)arg1;
    *(u16 *)(arg0 + 0xA6) = (u16)arg2;
    *(u16 *)(arg0 + 0xA8) = (u16)arg3;
    *(u16 *)(arg0 + 0xAA) = (u16)arg4;
}

void func_82602708(u8 *arg0) {
    *(u16 *)(arg0 + 0xA0) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602710.s")


typedef struct { u8 pad_00[4]; void *unk_04; } Func82615340StateX;
extern Func82615340StateX *D_82615340;
extern void func_82602710(u8 *);
extern void BgStage_DrawFrame(void);
extern void func_826042A0(void);
extern void func_82614BD0(void);
extern void func_80008648(void);

void func_82602888(void) {
    func_80043E70(D_82615340->unk_04, 0);
    BgStage_DrawFrame();
    func_82602710(D_82615340);
    func_826042A0();
    func_82614BD0();
    func_80008648();
}


typedef struct {
    u8 pad_00[8];
    u16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x7C];
    s16 unk_88;
} Func826028E0StateX;
extern s32 func_8006AD10(u16, s16, s16);
extern s32 func_80054AA0(s32);
extern void func_80054AF4(s32);

void func_826028E0(Func826028E0StateX *arg0) {
    s32 value;
    value = func_8006AD10(arg0->unk_08, arg0->unk_0A, arg0->unk_88);
    if (value != -1) {
        if (func_80054AA0(value) == 0) {
            func_80054AF4(value);
        }
    }
}


s32 func_82602930(s32 arg0) {
    s32 result = arg0;
    switch (arg0) {
    case 0:
        if (StageContext_GetFadeMode() == 0) result = 1;
        break;
    case 1:
        if (func_80044144(D_82615340->unk_04) != 0) {
            result = 2;
            func_82614CE0();
            func_800355E4(0x28);
        }
        break;
    case 2:
        if (func_82614F0C() != 0) {
            result = 3;
            StageContext_SetClearColor(1);
            StageFade_StartFromTransparent(5);
            func_800226C0(0x65);
        }
        break;
    case 3:
        if (StageContext_GetFadeMode() == 1) result = 4;
        break;
    }
    return result;
}

extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern void func_82604170(void);
extern void func_82613814(void);
extern void func_82602888(void);
extern void func_826028E0(Func826028E0StateX *arg0);
extern s32 func_82602930(s32 arg0);
void func_82602A0C(void) {
    Func826028E0StateX *sp24;
    u16 sp22;
    s32 temp_v0_2;
    s32 var_s0;

    sp24 = (Func826028E0StateX *)*(void **)D_82615340;
    var_s0 = 0;
    sp22 = sp24->unk_08 & 0xFF00;
    if (StageContext_GetFadeMode() != 0) {
        func_800086A4(2);
        StageFade_StartFromOpaque(5);
    }
    do {
        func_80064D28();
        func_82604170();
        func_82613814();
        func_82602888();
        temp_v0_2 = func_82602930(var_s0);
        var_s0 = temp_v0_2;
    } while (temp_v0_2 != 4);
    if ((sp22 == 0x300) || (sp22 == 0x600)) {
        func_826028E0(sp24);
    }
}

void RecordNames_LoadUnassignedFourSlots(u8 *context) {
    s32 index;
    s32 selection;
    s8 *state;
    s8 *cursor;
    u8 *base;
    u8 *record;
    void *name;
    state = *(s8 **)context;
    selection = *(s16 *)((u8 *)state + 136);
    base = *(u8 **)(context + 12);
    index = 0;
    cursor = state;
    record = ((u8 (*)[152])base)[((s16 *)context)[selection + 12]] + 4;
    do {
        if (*cursor == -1) {
            name = func_8004C874(42, record[1] - 1);
            if (name != 0) {
                _bcopy(name, (u8 *)state + index * 12 + 2256, 12);
            }
        }
        index++;
        cursor++;
    } while (index != 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602B9C.s")

void RecordNames_LoadSelectedOrDefaultPair(u8 *context) {
    s32 index;
    s32 selection;
    s8 *state;
    u8 *selected_row;
    u8 *default_row;
    s8 *cursor;
    s8 slot;
    u8 *row;
    void *name;
    default_row = *(u8 **)(context + 12) + 4;
    state = *(s8 **)context;
    index = 0;
    selection = *(s16 *)((u8 *)state + 136);
    selected_row = ((u8 (*)[152])(*(u8 **)(context + 12)))[((s16 *)context)[selection + 12]] + 4;
    cursor = state;
    do {
        slot = *cursor;
        name = 0;
        switch (slot) {
        case -1:
            row = selected_row;
            break;
        case -2:
            row = 0;
            break;
        default:
            row = default_row;
            break;
        }
        if (row != 0) {
            name = func_8004C874(42, row[1] - 1);
        }
        if (name != 0) {
            _bcopy(name, (u8 *)state + index * 12 + 2256, 12);
        }
        index++;
        cursor++;
    } while (index != 2);
}

extern s32 D_82615390[];
extern s32 D_82615384[];
extern s32 D_82615378[];
extern void *func_8004C874(s32, s32);
extern void func_80049C70(s32 *, s32 *, void *);
void func_82602E14(void *arg0) {
    s32 selection;
    u8 *record;
    s32 i;
    s32 mode;
    s32 width;
    s32 height;
    u8 *base;
    void *resource;
    u8 *root;

    root = *(u8 **)arg0;
    base = *(u8 **)((u8 *)arg0 + 0xC);
    mode = root[7];
    for (i = 0; i < *(s16 *)((u8 *)arg0 + 0x14); i++) {
        record = base;
        record += *(s16 *)((u8 *)arg0 + 0x18 + i * 2) * 0x98;
        record += 4;
        if (i == *(s16 *)(*(u8 **)arg0 + 0x88)) {
            switch (mode) {
                case 0:
                case 4:
                    selection = D_82615390[guRandom() % 3U];
                    break;
                case 3:
                    selection = 0x20;
                    break;
                case 1:
                    selection = D_82615384[guRandom() % 3U];
                    break;
                default:
                    selection = 0x1F;
                    break;
            }
        } else if (i < *(s16 *)(*(u8 **)arg0 + 0x88)) {
            selection = 0x27;
        } else {
            selection = D_82615378[guRandom() % 3U];
        }
        resource = func_8004C874(record[3] + 0x4C, selection);
        if (resource != 0) {
            *(s16 *)((u8 *)arg0 + 0x38 + i * 2) = selection;
            func_80049C70(&width, &height, resource);
            *(s16 *)((u8 *)arg0 + 0x58 + i * 4) = width;
            *(s16 *)((u8 *)arg0 + 0x5A + i * 4) = height;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602FE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_826030E4.s")

extern Func82615340StateX *D_82615370;
extern void func_80008648(void);
extern void BgStage_DrawFrame(void);
extern void func_82602710(u8 *);
extern void func_826042A0(void);
extern void func_82614BD0(void);
void func_82603684(void) {
    func_80043E70(D_82615370->unk_04, 0);
    BgStage_DrawFrame();
    func_82602710(D_82615370);
    func_826042A0();
    func_82614BD0();
    func_80008648();
}

extern void func_80055F6C(s32 *, s32);
extern s32 D_82615374;
extern u8 D_826163C0;
extern s32 func_8006CBB8(s32);
extern s32 func_8006CBA0(s32, s32);
extern u16 func_80056024(s32);
void func_826036DC(void *arg0) {
    s32 temp_a0;
    s32 sp24;
    u16 sp1E;
    s32 temp_v0;

    temp_a0 = *(s16 *)((u8 *)arg0 + 0xA);
    sp24 = temp_a0;
    func_8006CBB8(temp_a0);
    if (func_8006CBA0(*(s16 *)((u8 *)arg0 + 0x88), *(s16 *)((u8 *)arg0 + 0x8A)) != 0) {
        sp1E = func_80056024(sp24);
        temp_v0 = func_8006CBB8(sp24);
        switch (temp_v0) {
        case 0:
            (*(u16 *)((u8 *)&D_826163C0 + 0x0)) |= sp1E;
            break;
        case 1:
            (*(u16 *)((u8 *)&D_826163C0 + 0x4)) |= sp1E;
            break;
        case 2:
            (*(u16 *)((u8 *)&D_826163C0 + 0x2)) |= sp1E;
            break;
        }
        if (sp1E != 0) {
            func_80055F6C((s32 *)&D_826163C0, D_82615374);
        }
    }
}

void func_826037BC(void *arg0) {
    func_8006CBB8(*(s16 *)((u8 *)(arg0) + (0xA)));
    if (func_8006CBA0(*(s16 *)((u8 *)(arg0) + (0x88)), *(s16 *)((u8 *)(arg0) + (0x8A))) != 0) {
        (*(s8 *)((u8 *)(&D_826163C0) + (0xA))) = 1;
        func_80055F6C(&D_826163C0, D_82615374);
    }
}

s32 RecordOwners_AnyUnassigned(void) {
    s32 result;
    s32 index;
    s8 *owners;
    owners = *(s8 **)D_82615370;
    result = 0;
    for (index = 0; index < 4; index++) {
        if (owners[index] == -1) {
            result = 1;
        }
    }
    return result;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82603870.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_826039A0.s")
#endif
