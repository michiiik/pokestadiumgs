#include "global.h"


#ifdef VERSION_US
extern s32 MathUtil_Random16(void);
s32 func_83100020(void) {
    u16 second;
    u16 first;

    first = MathUtil_Random16();
    second = MathUtil_Random16();
    return (((MathUtil_Random16() % 0xC) * (second % 0xC) * (first % 0xC)) + 8) & 0xFFFF;
}

extern s32 func_80054AA0(s32);
extern u8 D_831038E0[];
void func_831000FC(void *arg0) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 0; i != 0x1E; i++) {
        if ((i < 3) || (func_80054AA0(D_831038E0[i]) != 0)) {
            ((u8 *)arg0 + count)[0xAC] = i;
            count++;
        }
    }
    ((u8 *)arg0)[0xCB] = count;
    while (count < 0x1E) {
        count++;
        *(s8 *)((u8 *)arg0 + count + 0xAB) = -1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_831001A8.s")

extern u8 *func_8006218C(s32, s32, s32, s32);
extern s8 func_80062390(void *, s32, u8 *);
extern void func_80062304(u8 *);
extern void func_800226C0(s32);
void func_83100584(void *arg0) {
    u8 *sp18;
    u8 *temp_v0;

    temp_v0 = func_8006218C(0x18, 0, 0, 0);
    if (temp_v0 != NULL) {
        sp18 = temp_v0;
        ((u8 *)arg0)[0x2EC] = func_80062390((u8 *)arg0 + 0xCC, 8, temp_v0);
        func_80062304(sp18);
        return;
    }
    ((u8 *)arg0)[0x2EC] = 0;
}

extern void func_800226C0(s32);
typedef struct Copy831005F0 { s32 words[17]; } Copy831005F0;
void func_831005F0(void *arg0, void *arg1) {
    *(Copy831005F0 *)((u8 *)arg0 + 0x68) = *(Copy831005F0 *)arg1;
    ((u8 *)arg0)[0x64] = 1;
    func_800226C0(0xD2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/6/fragment6_code/func_8310065C.s")

extern void func_81600F0C(void *, s32, s32, s32, s32);
extern void func_818057D0(void *, void *, void *);
void func_83100A98(void *arg0, u8 *arg1, void *arg2) {
    func_81600F0C(*(void **)(arg1 + 0x5C), 0, 0, 0x280, 0x1E0);
    func_818057D0(arg0, arg1, arg2);
}

extern void func_81700D44(s32);
extern void func_8170024C(void);
s32 func_83100AE8(void *arg0, u8 *arg1) {
    if (arg1[0x1D] == 0) {
        func_81700D44(0);
        func_81700D44(1);
    }
    func_8170024C();
    return 1;
}

extern s32 func_81600DA8(void *, void *);
extern void func_81700908(void);
extern u8 D_83102290[];
void func_83100B2C(void *arg0, u8 *arg1, void *arg2) {
    if (func_81600DA8(*(void **)(arg1 + 4), D_83102290) == 0) {
        func_81600F0C(*(void **)(arg1 + 0x5C), 0, 0, 0x280, 0x46);
    }
    func_81700908();
}

extern u8 *func_818054D0(void *, u8);
s32 func_83100B8C(void *arg0, u8 *arg1) {
    struct { s32 unused; s32 value; f64 tail; } result;
    s32 value;

    func_818054D0(arg0, arg1[0x1F]);
    result.value = 0;
    *(u16 *)(arg1 + 0x60) -= 1;
    value = *(u16 *)(arg1 + 0x60);
    if (value == 0) {
        *(u16 *)(arg1 + 0x60) = func_83100020();
        value = *(u16 *)(arg1 + 0x60);
    }
    if (value < 8) {
        result.value = 1;
    }
    return result.value;
}

extern f32 func_818055E0(void *, u8 *);
extern void func_818057D0(void *, void *, void *);
extern void func_81803964(void *, void *, f32, s32);
extern u8 D_831022F8[];
extern u8 D_83102318[];
void func_83100BF8(void *arg0, u8 *arg1, void *arg2) {
    s32 temp_v0;
    f32 sp18;

    sp18 = func_818055E0(arg0, arg1);
    func_818057D0(arg0, arg1, arg2);
    temp_v0 = (*(u16 *)(arg1 + 0x60) - 1) / 2;
    switch (temp_v0) {
    case 1:
    case 3:
        func_81803964(D_831022F8, arg2, sp18, 0);
        break;
    case 2:
        func_81803964(D_83102318, arg2, sp18, 0);
        break;
    }
}

s32 func_83100CA4(void *arg0, u8 *arg1) {
    struct { s32 unused; s32 value; f64 tail; } result;
    s32 value;

    func_818054D0(arg0, arg1[0x1F]);
    result.value = 0;
    *(u16 *)(arg1 + 0x62) -= 1;
    value = *(u16 *)(arg1 + 0x62);
    if (value == 0) {
        *(u16 *)(arg1 + 0x62) = func_83100020();
        value = *(u16 *)(arg1 + 0x62);
    }
    if (value < 8) {
        result.value = 1;
    }
    return result.value;
}

extern f32 func_818055E0(void *, u8 *);
extern void func_818057D0(void *, void *, void *);
extern void func_81803964(void *, void *, f32, s32);
extern u8 D_831023E8[];
extern u8 D_83102408[];
void func_83100D10(void *arg0, u8 *arg1, void *arg2) {
    s32 temp_v0;
    f32 sp18;

    sp18 = func_818055E0(arg0, arg1);
    func_818057D0(arg0, arg1, arg2);
    temp_v0 = (*(u16 *)(arg1 + 0x62) - 1) / 2;
    switch (temp_v0) {
    case 1:
    case 3:
        func_81803964(D_831023E8, arg2, sp18, 0);
        break;
    case 2:
        func_81803964(D_83102408, arg2, sp18, 0);
        break;
    }
}

extern s32 func_81804A20(void *);
extern s32 func_81805524(void *, u8 *);
s32 Fragment6_HandleAvailableListScroll(void *definition, u8 *state) {
    s32 selection;
    s32 scroll;
    s32 handled;

    func_818054D0(definition, state[0x1F]);
    handled = 0;
    if (func_81804A20(state)) {
        selection = state[0x40];
        if (selection < 2 && (*(u16 *)(state + 0x16) & 0x800) && (scroll = state[0x43]) > 0) {
            state[0x43] = scroll - 1;
            func_800226C0(1);
            handled = 1;
        } else if (selection >= 10 && (*(u16 *)(state + 0x16) & 0x400)) {
            scroll = state[0x43];
            if (scroll + 10 <= state[0xCB]) {
                state[0x43] = scroll + 1;
                func_800226C0(1);
                handled = 1;
            }
        }
    }
    if (!handled) {
        handled = func_81805524(definition, state);
    }
    return handled;
}

void func_83100E98(u8 *arg0, s32 arg1)
{
  s32 result = arg1 - 4;
  s32 limit = arg0[0xCB] - 9;
  if (limit < result)
  {
    result = limit;
  }
  if (limit = result < 0)
  {
    result = 0;
  }
  arg0[0x43] = result;
  arg0[0x40] = ((arg1 - result) & 0xFFu) + 1;
}

extern u8 *func_818054D0(void *, u8);
extern s32 func_81804A20(void *);
extern s32 MathUtil_Random16(void);
extern void func_83100E98(u8 *, s32);
extern void func_8310065C(void *, s32);
extern void func_800226C0(s32);
s32 func_83100ED4(void *arg0, u8 *arg1) {
    s16 temp_v0;

    func_818054D0(arg0, arg1[0x1F]);
    if (func_81804A20(arg1) != 0) {
        *(s16 *)(arg1 + 0x66) = *(s16 *)(arg1 + 0x66) - 1;
        temp_v0 = *(s16 *)(arg1 + 0x66);
        if ((temp_v0 >= 0xB) && ((temp_v0 & 1) == 0)) {
            func_83100E98(arg1, (MathUtil_Random16() % (s32)arg1[0xCB]) + 1);
            func_800226C0(1);
        } else if (temp_v0 <= 0) {
            func_8310065C(arg1, 0);
            func_800226C0(0x8D);
        }
    }
    return 1;
}

extern u8 *func_818054D0(void *, u8);
extern s32 func_81804A20(void *);
extern s32 func_81805524(void *, u8 *);
extern s32 func_800718B8(s32);
extern u8 D_831038FF[];
s32 func_83100FA4(void *arg0, u8 *arg1) {
    u8 temp_v0;
    s32 result[2];

    func_818054D0(arg0, arg1[0x1F]);
    if ((func_81804A20(arg1) != 0) && ((*(u16 *)(arg1 + 0x14) & 0x10) != 0) &&
        (temp_v0 = arg1[0x3E], temp_v0 < 6)) {
        result[0] = 1;
        func_831005F0(arg1, func_800718B8(D_831038FF[temp_v0]));
    } else {
        result[0] = func_81805524(arg0, arg1);
    }
    return result[0];
}

extern void func_8310065C(void *, s32);
extern void func_800226C0(s32);
void func_8310103C(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 0;
        func_8310065C(arg0, 1);
        func_800226C0(3);
        return;
    }
    if (arg1 > 0) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 2;
        func_800226C0(2);
    }
}

void func_83101090(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 1;
        func_800226C0(3);
        return;
    }
    if (arg1 == 1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 3;
        func_800226C0(2);
        return;
    }
    if (arg1 >= 2) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 4;
        func_800226C0(2);
    }
}

extern void func_800226C0(s32);
void func_83101104(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        ((u8 *)arg0)[0x1E] = 2;
        func_800226C0(3);
        return;
    }
    if (arg1 == 6) {
        ((u8 *)arg0)[0x1E] = 6;
        func_800226C0(0x8C);
        return;
    }
    if (arg1 == 5) {
        ((u8 *)arg0)[0x1E] = 5;
        func_800226C0(0x8C);
        return;
    }
    if ((arg1 < 5) && (arg1 > 0)) {
        ((u8 *)arg0)[0x1E] = 7;
        func_800226C0(0x8C);
    }
}

extern void func_800226C0(s32);
extern void func_8310065C(void *, s32);
extern s8 D_8009F864;
void func_831011A0(void *arg0, s32 arg1) {
    s32 temp_v0;

    if (arg1 == -1) {
        ((u8 *)arg0)[0x1E] = 4;
        func_800226C0(3);
        return;
    }
    if (arg1 > 0) {
        temp_v0 = ((u8 *)arg0)[0x43] + ((u8 *)arg0)[0x40];
        if (temp_v0 < 2) {
            ((u8 *)arg0)[0x1E] = 8;
            *(u16 *)((u8 *)arg0 + 0x66) = 0x1E;
            D_8009F864 = temp_v0 - 1;
            func_800226C0(2);
            return;
        }
        D_8009F864 = temp_v0 - 1;
        func_8310065C(arg0, 0);
        func_800226C0(0x8D);
    }
}

typedef struct {
    s16 archive, entry, x, y;
    u8 settings[8];
    s32 blend;
    void *styles[3];
} Fragment6TextRecord;
typedef struct { Fragment6TextRecord records[3]; } Fragment6TextList;
extern Fragment6TextList D_83103168;
extern u8 D_83102B4C[], D_83102B64[], D_83102F64[], D_831031C8[], D_831031E8[];
extern void WidgetResources_DrawRecords(s32, s32, s32);
extern void WidgetResources_DrawSelection(s32, s32, s32);
extern void func_818042E4(void *, void *, void *, f32, s32);
extern void WidgetText_DrawRecordListWithSetup(u8 *, void *, f32, s32);
extern void WidgetText_DrawRecordWithSetup(void *, void *, f32, s32);
extern void WidgetTexture_DrawRecord(u8 *, u8 *, f32, s32);
extern u8 * func_818054D0(void *, u8);
extern f32 func_818055E0(void *, u8 *);
void Fragment6_DrawSelectionControls(void *definition, u8 *state, u8 *origin) {
    Fragment6TextList text;
    u8 *resource;
    f32 weight;
    Fragment6TextRecord *records;
    s32 variant;

    text = D_83103168;
    records = text.records;
    resource = func_818054D0(definition, state[0x1F]);
    weight = func_818055E0(definition, state);
    WidgetResources_DrawRecords((s32)definition, (s32)state, (s32)origin);
    if (*(void **)(resource + 32) != D_83102B4C) {
        func_818042E4(D_83102B4C, origin, state, weight, 0);
    } else {
        records[0].blend = 1;
    }
    if (*(void **)(resource + 32) != D_83102B64) {
        func_818042E4(D_83102B64, origin, state, weight, 0);
    } else {
        records[0].blend = 1;
    }
    if (*(void **)(resource + 32) != D_83102F64) {
        func_818042E4(D_83102F64, origin, state, weight, 0);
    } else {
        records[1].blend = 1;
    }
    WidgetText_DrawRecordListWithSetup((u8 *)records, origin, weight, 0);
    variant = 2;
    if (state[0x1F] == 4 && state[0x3E] < 6) {
        variant = 0;
    }
    WidgetText_DrawRecordWithSetup(D_831031C8, origin, weight, variant);
    WidgetTexture_DrawRecord(D_831031E8, origin, weight, variant);
    WidgetResources_DrawSelection((s32)definition, (s32)state, (s32)origin);
}

extern Gfx *D_800D0510;
extern Gfx D_80094DB8[];
extern u8 D_83103208[], D_83103228[];
extern void func_800498C4(void);
extern void func_800499EC(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800495BC(s32, s32, const char *, ...);
extern void Gfx_FillRectRgba(s16, s16, s16, s16, u8, u8, u8, u8);
extern void *func_8004C874(s32, s32);
void Fragment6_DrawAvailableEntryList(void *definition, u8 *state, s16 *origin) {
    s32 selected;
    s32 i;
    s32 label;
    f32 weight;
    s32 slot;
    s32 row_y;
    s32 scroll;

    func_818054D0(definition, state[31]);
    weight = func_818055E0(definition, state);
    selected = -1;
    if (func_81804A20(state)) {
        selected = state[64] - 1;
    }
    WidgetResources_DrawRecords((s32)definition, (s32)state, (s32)origin);
    gSPDisplayList(D_800D0510++, D_80094DB8);
    Gfx_FillRectRgba((s16)(origin[0] + 54), (s16)(origin[1] + 54), 253, 286, 0, 0, 0, (u8)(100.0f * weight));
    func_800498C4();
    func_800496A4(8, 1);
    func_8004972C(255, 255, 255, (s32)(255.0f * weight));
    for (i = 0; i < 10; i++) {
        scroll = state[67];
        label = 31;
        if (scroll + i > 0) {
            slot = *((s8 *)state + i + scroll + 171);
            if (slot < 0) {
                continue;
            }
            if (slot >= 0) {
                label = slot + 32;
            } else {
                label = 62;
            }
        }
        row_y = i * 26;
        if (i == selected) {
            func_8004972C(255, 255, 0, (s32)(255.0f * weight));
        } else if (label == 62) {
            func_8004972C(128, 128, 128, (s32)(255.0f * weight));
        } else {
            func_8004972C(255, 255, 255, (s32)(255.0f * weight));
        }
        func_800495BC(origin[0] + 111, origin[1] + row_y + 70, func_8004C874(44, label));
    }
    func_800499EC();
    scroll = state[67];
    if (scroll > 0) {
        func_81803964(D_83103208, origin, weight, 0);
    }
    scroll = state[67];
    if (scroll + 10 <= state[203]) {
        func_81803964(D_83103228, origin, weight, 0);
    }
    WidgetResources_DrawSelection((s32)definition, (s32)state, (s32)origin);
}

extern void func_800226C0(s32);
void func_83101714(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 2;
        func_800226C0(3);
        return;
    }
    if (arg1 > 0) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 4;
        func_800226C0(0x90);
    }
}

extern u8 *func_818054D0(void *, u8);
extern s32 func_81804A20(void *);
extern s32 func_81805524(void *, u8 *);
extern void func_831005F0(void *, void *);
extern void func_800226C0(s32);
s32 func_83101764(void *arg0, u8 *arg1) {
    u8 temp_v0;

    func_818054D0(arg0, arg1[0x1F]);
    if ((func_81804A20(arg1) != 0) && ((*(u16 *)(arg1 + 0x14) & 0x10) != 0)) {
        temp_v0 = arg1[0x3F];
        if (arg1[0x2EC] >= temp_v0) {
            func_831005F0(arg1, (u8 *)arg1 + (temp_v0 * 0x44) + 0x88);
        } else {
            func_800226C0(5);
        }
    } else {
        func_81805524(arg0, arg1);
    }
    return 1;
}

typedef struct {
    u8 unk_00[63];
    u8 selected;
    u8 unk_40[140];
    char entries[8][68];
    u8 count;
} Fragment6SavedEntryListPrefix;
extern u8 D_831034C4[], D_83103504[];
void Fragment6_DrawSavedEntryList(void *definition, u8 *state, s16 *origin) {
    Fragment6SavedEntryListPrefix *list = (Fragment6SavedEntryListPrefix *)state;
    s32 has_entries;
    s32 i;
    f32 weight;

    has_entries = list->count > 0;
    weight = func_818055E0(definition, state);
    WidgetResources_DrawRecords((s32)definition, (s32)state, (s32)origin);
    WidgetTexture_DrawRecord(D_831034C4, (u8 *)origin, weight, has_entries ? 0 : 2);
    WidgetText_DrawRecordWithSetup(D_83103504, origin, weight, has_entries ? 0 : 2);
    func_800498C4();
    func_800496A4(8, 1);
    func_8004972C(255, 255, 255, (s32)(255.0f * weight));
    for (i = 0; i < list->count; i++) {
        if (i + 1 == list->selected) {
            func_8004972C(255, 255, 0, (s32)(255.0f * weight));
        }
        func_800495BC(origin[0] + 59, origin[1] + i * 26 + 39, list->entries[i]);
        if (i + 1 == list->selected) {
            func_8004972C(255, 255, 255, (s32)(255.0f * weight));
        }
    }
    func_800499EC();
    gSPDisplayList(D_800D0510++, D_80094DB8);
    for (i = 1; i != 8; i++) {
        Gfx_FillRectRgba((s16)(origin[0] + 49), (s16)(origin[1] + i * 26 + 35), 172, 1, 70, 120, 70, (u8)(255.0f * weight));
    }
    Gfx_FillRectRgba((s16)(origin[0] + 15), (s16)(origin[1] + 35), 206, 1, 70, 120, 70, (u8)(255.0f * weight));
    WidgetResources_DrawSelection((s32)definition, (s32)state, (s32)origin);
}

extern u8 *func_818054D0(void *arg0, u8 arg1);
extern void func_81801CB8(void *arg0, void *arg1, void *arg2, s32 arg3);
void func_83101B04(void *arg0, u8 *arg1, void *arg2) {
    void *first_offset;
    void *first;
    void *second;

    first = func_818054D0(arg0, arg1[0x1C]);
    first_offset = (u8 *)first + 0x10;
    second = func_818054D0(arg0, arg1[0x1D]);
    func_81801CB8(arg2, first_offset, (u8 *)second + 0x10, *(s32 *)(arg1 + 0x2C));
}

void func_83101B60(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 4;
        func_800226C0(3);
        return;
    }
    if (arg1 > 0) {
        if (*(u8 *)((u8 *)arg0 + 0x2EC) >= arg1) {
            *(u8 *)((u8 *)arg0 + 0x1E) = 7;
            func_800226C0(0x90);
            return;
        }
        func_800226C0(5);
    }
}

extern void func_800226C0(s32);
void func_83101BD4(void *arg0, s32 arg1) {
    if (arg1 == -1) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 4;
        func_800226C0(3);
        return;
    }
    if (arg1 > 0) {
        *(u8 *)((u8 *)arg0 + 0x1E) = 7;
        func_800226C0(0x8D);
    }
}

extern u8 *func_818054D0(void *arg0, u8 arg1);
extern void func_81801CB8(void *arg0, void *arg1, void *arg2, s32 arg3);
void func_83101C24(void *arg0, u8 *arg1, void *arg2) {
    void *first_offset;
    void *first;
    void *second;

    first = func_818054D0(arg0, arg1[0x1C]);
    first_offset = (u8 *)first + 0x10;
    second = func_818054D0(arg0, arg1[0x1D]);
    func_81801CB8(arg2, first_offset, (u8 *)second + 0x10, *(s32 *)(arg1 + 0x2C));
}

typedef struct {
    u8 bytes[9];
} Fragment6SelectionConfiguration;
extern void _bzero(void *, s32);
extern void WidgetState_Initialize(void *, s32, s32, void *, s32);
extern u8 D_831038A0[];
extern void func_831001A8(u8 *);
void Fragment6_InitializeSelectionState(void *arg0, void *memory, s32 setup_address) {
    u8 *state = arg0;

    _bzero(state, 756);
    *(void **)(state + 0x38) = (void *)setup_address;
    WidgetState_Initialize(state, *(s8 *)*(void **)(state + 0x38), 9, D_831038A0, (s32)memory);
    if ((*(u8 **)(state + 0x38))[12] > 0) {
        *(Fragment6SelectionConfiguration *)(state + 0x3C) = *(Fragment6SelectionConfiguration *)(*(u8 **)(state + 0x38) + 4);
        state[0x1E] = state[0x1C] = state[0x1D] = state[0x1F] = (*(u8 **)(state + 0x38))[12];
    } else {
        state[0x1E] = 1;
    }
    *(s16 *)(state + 0x60) = func_83100020();
    *(s16 *)(state + 0x62) = func_83100020();
    func_83100584(state);
    func_831000FC(state);
    func_831001A8(state);
    func_83100E98(state, (u8)D_8009F864);
}

extern void main_pool_push_state(s32);
extern void func_8004C09C(s32);
extern void *func_8004D690(s32);
extern void func_8004C8C0(s32);
extern void WidgetTree_OpenMessagePanel_fragment4(void *);
extern void func_8004C594(s32, s32);
extern void func_817000A4(void);
extern void func_81700974(s32, s32, s32, s32, s32, void *, void *, s32);
extern void func_81700C70(s32);
extern void func_81700C0C(s32);
extern u8 D_831038C7[];
extern u8 D_831038D0[];
void func_83101D74(void *arg0) {
    void *temp_v0;
    s32 temp_v1;

    main_pool_push_state(0x46425352);
    func_8004C09C(7);
    temp_v0 = func_8004D690(0x16);
    *(void **)((u8 *)arg0 + 0x5C) = temp_v0;
    func_8004C8C0(0x32);
    func_8004C8C0(0x76);
    WidgetTree_OpenMessagePanel_fragment4(arg0);
    func_8004C594(1, ((u8 *)arg0)[0x40] + ((u8 *)arg0)[0x43] - 1);
    func_8004C594(2, ((u8 *)arg0)[0xCB]);
    func_817000A4();
    temp_v1 = (s32)func_8004C874(0x2C, 0x3F);
    func_81700974(0, 0, 0x30, 0x10, temp_v1, D_831038C7, D_831038D0, 0);
    temp_v1 = (s32)func_8004C874(0x2C, 0x40);
    func_81700974(1, 0x280, 0x30, 8, temp_v1, D_831038C7, D_831038D0, 0);
    if (((u8 *)arg0)[0x1F] != 0) {
        func_81700C70(0);
        func_81700C70(1);
    } else {
        func_81700C0C(0);
        func_81700C0C(1);
    }
}

extern void BgStage_DrawFrame(void);
extern void func_818017A8(void);
extern void func_81805308(void *);
extern void func_80008648(void);
extern void StageLoader_WaitForRetrace(void);
extern void func_8004C398();
extern void main_pool_pop_state(s32);
extern s32 Fragment_LoadAndCall(s32, void *, void *, s32, void *);
extern void func_83101D74(void *);
extern void func_80008624(void);
extern u8 D_831039B0[];
extern u8 D_83103A14;
extern u8 D_83103A18[];
extern u8 fragment83_ROM_START[];
extern u8 fragment84_ROM_START[];
extern u8 D_82C00000[];
void func_83101EB0(void) {
    BgStage_DrawFrame();
    func_818017A8();
    func_81805308(D_831039B0);
    func_80008648();
    StageLoader_WaitForRetrace();
    func_8004C398();
    main_pool_pop_state(0x46425352);
    Fragment_LoadAndCall((((u32)&D_82C00000 & 0x0FF00000) >> 20) - 0x10, fragment83_ROM_START, fragment84_ROM_START, 0x200, D_83103A18);
    func_83101D74(D_831039B0);
    func_80008624();
    D_83103A14 = 0;
}

extern void func_80064D28(void);
extern void func_831001A8(u8 *);
extern void func_81804FD0(u8 *);
extern s32 func_81801388(s32, s32);
extern u8 D_831039B0[];
s32 func_83101F5C(s32 arg0) {
    s32 var_s1;
    s32 var_v1;

    var_s1 = 0;
    func_80064D28();
    if ((D_831039B0[0x1C] == D_831039B0[0x1D]) && (D_831039B0[0x1E] == D_831039B0[0x1D])) {
        var_s1 = *(s32 *)(D_831039B0 + 0x2F0);
    }
    func_831001A8(D_831039B0);
    if (var_s1 == 0) {
        func_81804FD0(D_831039B0);
    } else {
        var_s1 = func_81801388(5, 1);
    }
    func_831001A8(D_831039B0);
    if (var_s1 != 0) {
        var_v1 = 1;
    } else {
        var_v1 = arg0;
    }
    return var_v1;
}

extern void BgStage_DrawFrame(void);
extern void func_818017A8(void);
extern void func_8004C594(s32, s32);
extern void func_81805308(void *);
extern void func_80008648(void);
extern void func_83101EB0(void);
extern u8 D_831039B0[];
extern u8 D_83103A14;
extern u8 D_83103A7B;
void func_83101FFC(s32 arg0) {
    BgStage_DrawFrame();
    func_818017A8();
    func_8004C594(1, D_831039B0[0x40] + D_831039B0[0x43] - 1);
    func_8004C594(2, D_83103A7B);
    func_81805308(D_831039B0);
    func_80008648();
    if (D_83103A14 > 0) {
        func_83101EB0();
    }
}

s32 func_83101F5C(s32);
extern void func_83101FFC(s32);
void func_83102080(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    do {
        temp_v0 = func_83101F5C(var_s0);
        var_s0 = temp_v0;
        func_83101FFC(temp_v0);
    } while (var_s0 != 1);
}

extern void Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern void func_80055948(s32);
extern s32 main_pool_get_available(void);
extern u8 *MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(void *);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern s32 StageContext_Allocate(s32, s32, s32, s32, s32, s32);
extern void func_80047588(s32, s32);
extern void Fragment6_InitializeSelectionState(void *, void *, s32);
extern void func_83101D74(void *);
extern void func_80008514(s32);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
extern void func_81801794(void);
extern void func_800355E4(s32);
extern u8 D_1000000;
extern u8 D_446E30;
extern u8 D_447D00[];
extern u8 D_831039B0[];
extern u8 *D_83103CA4;
void func_831020D0(s32 arg0, s32 arg1) {
    s32 sp24;
    u8 *sp20;

    Asset_LoadToSegment((s32)(((u32)(s32)&D_1000000 & 0x0F000000) >> 24), &D_446E30, D_447D00, 0);
    func_80055948(3);
    sp20 = MainPool_AllocState(main_pool_get_available(), 0);
    D_83103CA4 = func_81600E28(sp20, 1, 0xA);
    MainPool_FinalizeAllocation(sp20);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = StageContext_Allocate(1, 0, 2, 0, 2, 1);
    func_80047588(0x1C, 0);
    Fragment6_InitializeSelectionState(D_831039B0, D_83103CA4, arg1);
    func_83101D74(D_831039B0);
    func_80008514(sp24);
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    func_81801794();
    func_800355E4(0x40);
}

extern void Gfx_FreeDisplayListBuffers();
extern void func_80008574();
extern void func_80047610();
extern void func_8004C398();

void func_831021E8(s32 arg0, s32 arg1) {
    func_80008574();
    func_8004C398();
    func_80047610();
    Gfx_FreeDisplayListBuffers();
}

extern void func_83102080(s32, s32);
extern void func_831020D0(s32, s32);
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
s32 fragment6_main(s32 arg0, s32 arg1) {
    main_pool_push_state(0x4642534C);
    func_831020D0(arg0, arg1);
    func_83102080(arg0, arg1);
    func_831021E8(arg0, arg1);
    main_pool_pop_state(0x4642534C);
    return 0;
}
#endif
