#include "global.h"


#ifdef VERSION_US
extern void func_8004A858(s32, s32, u16, u16, s32 *, s32 *);
extern u8 D_8AF26450;
extern u8 D_8AF26454;
s32 func_8AF0EFF0(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0x18)));
    func_8004A858(0, 0, (*(u16 *)((u8 *)(temp_v0) + (4))), (*(u16 *)((u8 *)(temp_v0) + (6))), &D_8AF26450, &D_8AF26454);
    return 0;
}

extern s32 func_8004C594(s32, s32);
extern u8 func_8006397C(u8);
extern u8 func_800639C0(u8);
extern void *func_8004C874(s32, s32);
extern s32 func_8004C54C(s32, s32);
extern s16 func_8AF01530(s16);
extern s16 D_8AF263C4[];
extern char *D_8AF26A30;
extern char D_8AF294E0[];

s32 func_8AF0F040(s32 mode, void *record) {
    s16 index;
    u8 first;
    u8 second;
    char *first_name;
    s32 lookup;

    index = *(s16 *)((u8 *)record + 0x22);
    if (mode != 0 && mode == 1) {
        func_8004C594(3, index);
        lookup = index - 1;
        func_8004C54C(0x2C, (s32)func_8004C874(2, lookup));
        func_8004C54C(0x2D, (s32)func_8004C874(3, lookup));
        func_8004C54C(0x2E, (s32)func_8004C874(1, lookup));
        first = func_8AF01530(func_8006397C(index));
        second = func_8AF01530(func_800639C0(index));
        if (first == second) {
            func_8004C54C(0x2F, (s32)func_8004C874(0xC, D_8AF263C4[first]));
        } else {
            first_name = func_8004C874(0xC, D_8AF263C4[first]);
            sprintf(D_8AF26A30, D_8AF294E0, first_name, func_8004C874(0xC, D_8AF263C4[second]));
            func_8004C54C(0x2F, (s32)D_8AF26A30);
        }
    }
    return 0;
}

extern void func_800504BC(s16 *);
extern s16 D_8AF2F9E0[][3];

void func_8AF0F1A0(s32 mode, void *record) {
    s16 index;
    s16 values[2];
    s16 *entry;

    index = *(s16 *)((u8 *)record + 0x22);
    if (mode != 0 && mode == 1) {
        func_800504BC(values);
        entry = D_8AF2F9E0[index];
        entry[0] = index + 1;
        entry[1] = *(s16 *)((u8 *)record + 8) + values[0];
        entry[2] = *(s16 *)((u8 *)record + 0xA) + values[1];
    }
}

extern s32 func_80063BB8(u8);
extern s16 D_8AF2F9DE;
extern s16 D_8AF2F9D0[];
extern u8 D_8AF2FA70[][3];
extern u8 D_8AF31D42;
extern u8 func_80062D98(u8);
extern u8 *func_8AF12410(u8 *, s16);

void func_8AF0F220(u8 code) {
    struct EvolutionEntry {
        u8 method;
        u8 requirement;
        u8 species;
    };
    u8 *entry;
    u8 *copy;
    s16 index;

    entry = (u8 *)func_80063BB8(code);
    if (entry != NULL) {
        for (;;) {
            if (entry[0] == 0) {
                break;
            }
            D_8AF2F9DE++;
            index = D_8AF2F9DE;
            D_8AF2F9D0[index] = entry[2];
            copy = D_8AF2FA70[index];
            *(struct EvolutionEntry *)copy = *(struct EvolutionEntry *)entry;
            func_8AF0F220(entry[2]);
            entry += 3;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF0F2EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1000C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1025C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF102AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1043C.s")

extern void func_80043E70(s32, s32);
extern s32 D_8AF26A44;

void func_8AF10540(void) {
    if (D_8AF26A44 != 0) {
        func_80043E70(D_8AF26A44, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF1060C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF106A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10784.s")

extern void *D_8AF3011C;
extern void *D_8AF30120;
extern void *D_8AF30124;
extern void *D_8AF30128;
extern void *D_8AF3012C;
extern void *D_8AF30130;

void func_8AF10840(void) {
    *(u16 *)((u8 *)D_8AF3011C + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF30128 + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF30120 + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF3012C + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF30124 + 2) &= ~2;
    *(u16 *)((u8 *)D_8AF30130 + 2) &= ~2;
}

void func_8AF108BC(void) {
    (*(u16 *)((u8 *)(D_8AF3011C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3011C) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30128) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30128) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30120) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30120) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF3012C) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3012C) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30124) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30124) + (2))) | 2);
    (*(u16 *)((u8 *)(D_8AF30130) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF30130) + (2))) | 2);
}

void func_8AF10938(u8 *arg0, s32 arg1, s32 arg2) {
    *(s32 *)(arg0 + 0x28) = arg1;
    *(s32 *)(arg0 + 0x2C) = arg2;
}

extern void *D_8AF300C8;
extern void *D_8AF300CC;
extern void *D_8AF300D0;
extern s16 D_8AF300C4;
extern s16 D_8AF31000;

void func_8AF10944(void) {
    *(u16 *)((u8 *)D_8AF300C8 + 2) &= ~1;
    *(u16 *)((u8 *)D_8AF300CC + 2) &= ~1;
    *(u16 *)((u8 *)D_8AF300D0 + 2) &= ~1;
    func_8AF10938(D_8AF30128, (s32)0xC3A05AFF, (s32)0xE1C38CFF);
    func_8AF10938(D_8AF3012C, (s32)0xC3A05AFF, (s32)0xE1C38CFF);
    func_8AF10938(D_8AF30130, (s32)0xC3A05AFF, (s32)0xE1C38CFF);
    if (D_8AF31000 == 0) {
        switch (D_8AF300C4) {
        case 0:
            *(u16 *)((u8 *)D_8AF300C8 + 2) |= 1;
            func_8AF10938(D_8AF30128, (s32)0xFFFF00FF, (s32)0xFFFF00FF);
            break;
        case 2:
            *(u16 *)((u8 *)D_8AF300CC + 2) |= 1;
            func_8AF10938(D_8AF3012C, (s32)0xFFFF00FF, (s32)0xFFFF00FF);
            break;
        case 1:
            *(u16 *)((u8 *)D_8AF300D0 + 2) |= 1;
            func_8AF10938(D_8AF30130, (s32)0xFFFF00FF, (s32)0xFFFF00FF);
            break;
        }
    }
}

extern void _bzero(s32 *, s32);
extern u8 D_8AF30158[];
extern s16 D_8AF26EF8[][2];
struct MenuRGBA {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};
extern struct MenuRGBA D_8AF26A50;
extern struct MenuRGBA D_8AF26A54;
extern s16 D_8AF30FF8;

void func_8AF10AB8(void) {
    u8 *bank;
    u8 *record;
    s32 count;
    s32 first;
    s32 i;
    s16 *descriptor;
    s32 group;

    _bzero((s32 *)D_8AF30158, 0xEA0);
    descriptor = &D_8AF26EF8[0][0];
    for (group = 0; group < 9; group++) {
        count = descriptor[1];
        first = descriptor[0];
        bank = D_8AF30158 + group * 0x1A0;
        record = bank;
        for (i = 0; i < count; i++) {
            *(s16 *)(record + 0) = 1;
            *(s16 *)(record + 2) = 0;
            *(s16 *)(record + 4) = i * 0x18;
            *(s32 *)(record + 8) = 0x3B;
            *(s32 *)(record + 0xC) = first + i;
            *(struct MenuRGBA *)(record + 0x16) = D_8AF26A50;
            *(struct MenuRGBA *)(record + 0x1A) = D_8AF26A54;
            record += 0x20;
        }
        descriptor += 2;
    }
}

extern s16 D_8AF30FFA;
extern s16 D_8AF30FFC;
extern s16 D_8AF30FFE;

void func_8AF10CD4(void) {
    D_8AF31000 = 0;
    D_8AF30FF8 = 0;
    D_8AF30FFC = 0;
    D_8AF30FFA = 0;
    D_8AF30FFE = 0;
    D_8AF300C4 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF10D08.s")

void func_8AF11358(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (arg1 < value) {
        value -= arg2;
        if (value < arg1) value = arg1;
        *arg0 = value;
    }
}

void func_8AF11398(f32 *arg0, f32 arg1, f32 arg2) {
    f32 value = *arg0;
    if (value < arg1) {
        value += arg2;
        if (arg1 < value) value = arg1;
        *arg0 = value;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF113D8.s")

extern void func_800498C4(void);
extern void func_800499EC(void);
void func_8AF12398(void) {
    func_800498C4();
    func_800499EC();
}

extern s16 *D_8AF2BA94;
extern u8 D_8AF31C48[250];
void func_8AF123C0(void) {
    s16 *source;
    s16 index;
    s16 value;
    s16 sentinel;

    source = D_8AF2BA94;
    index = 0;
    sentinel = -1;
    for (;;) {
        value = *source;
        if (sentinel != value) {
            *((u8 *)&D_8AF31C48 + index) = value;
            index++;
            index = (s16) index;
            if (index >= 250) {
                break;
            }
        }
        source++;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF12410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF124A8.s")

extern s16 D_8AF31024;
extern char D_8AF315A0[];
extern char D_8AF296C8[];
extern u8 D_8AF316C8[];

u8 *func_8AF125D0(s16 category) {
    u8 *output;
    u8 *destination;
    s32 index;
    s16 count;
    s16 selected;
    s16 mapped;
    s16 id;
    u16 saved;

    count = 0;
    D_8AF31024 = 1;
    *(s16 *)&D_8AF31D42 = -1;
    selected = (s16)category;
    sprintf(D_8AF315A0, D_8AF296C8);
    func_8004C54C(0x2F, (s32)func_8004C874(0xC, D_8AF263C4[selected]));
    func_8AF123C0();
    output = D_8AF316C8;
    _bzero((s32 *)output, 1000);
    destination = output;
    for (index = 0; index != 250; index++) {
        id = D_8AF31C48[index];
        saved = id;
        mapped = func_8AF01530(func_80062D98(id));
        if (id == 0xA5) {
            continue;
        }
        if (mapped != selected) {
            continue;
        }
        destination[0] = saved;
        destination[1] = mapped;
        destination += 4;
        count++;
    }
    return func_8AF12410(destination, count);
}

/* Preserve this logical source line for IDO's instruction scheduling. */
u8 *func_8AF1271C(u8 *output, s16 *table, u16 mask) { \
    u8 *entry; \
    u8 *end; \
    u8 *destination; \
    s32 id; \
    s16 count; \
    destination = output;
    count = 0;
    entry = D_8AF31C48; end = &D_8AF31D42;
    do {
        id = *entry;
        if (table[id - 1] & mask) {
            destination[0] = id;
            destination[1] = func_8AF01530(func_80062D98(id));
            destination += 4;
            count++;
        }
        entry++;
    } while (entry != end);
    return func_8AF12410(destination, count);
}

extern char D_8AF314A0[];
extern char D_8AF296F0[];
extern char D_8AF29730[];
extern char D_8AF29734[];
extern char D_8AF29738[];
extern char D_8AF2973C[];
extern s16 *D_8AF2BA90[];
extern u16 D_8AF26F4C[][13][2];

void func_8AF127E8(s16 group, s16 selected) {
    char *heading;
    char *detail;
    u8 *output;
    u8 *destination;
    u16 *entry;
    s32 i;

    *(s16 *)&D_8AF31D42 = selected;
    D_8AF31024 = 2;
    heading = func_8004C874(0x3B, group + 0x68);
    if (selected >= 0) {
        detail = func_8004C874(0x3B, D_8AF26EF8[group][0] + selected);
    } else {
        detail = D_8AF296F0;
    }
    if (selected >= 0) {
        sprintf(D_8AF314A0, D_8AF29730, heading);
        sprintf(D_8AF315A0, D_8AF29734, detail);
    } else {
        sprintf(D_8AF314A0, D_8AF29738, heading);
        sprintf(D_8AF315A0, D_8AF2973C);
    }
    func_8AF123C0();
    output = D_8AF316C8;
    _bzero((s32 *)output, 1000);
    destination = output;
    switch (group) {
    case 0:
        for (i = 0; i != 9; i++) {
            destination = func_8AF1271C(destination, D_8AF2BA90[2], 0x8000 >> i);
        }
        break;
    case 1:
        for (i = 0; i != 7; i++) {
            destination = func_8AF1271C(destination, D_8AF2BA90[2], 0x40 >> i);
        }
        func_8AF1271C(destination, D_8AF2BA90[3], 0x8000);
        break;
    default:
        entry = D_8AF26F4C[group][selected];
        func_8AF1271C(output, D_8AF2BA90[entry[0] + 1], entry[1]);
        break;
    }
}

extern u8 D_8AF26F34[];
s32 func_8AF129F8(u8 arg0) {
    u8 *ptr;
    s32 index;
    ptr = &D_8AF26F34;
    index = 0;
    for (;;) {
        if (*ptr != 0xFF) {
            if (arg0 == *ptr) return index;
            ptr++;
            index++;
            index = (s16)index;
        } else {
            return -1;
        }
    }
}

extern u8 func_80062D5C(u8);
extern u8 func_80062E10(u8);
extern u8 func_80062DD4(u8);
extern void *D_8AF31178;
extern void *D_8AF3117C;
extern void *D_8AF31180;
extern void *D_8AF31188;
extern void *D_8AF3118C;
extern void *D_8AF31190;
extern u8 D_8AF316B2[2];
extern u8 D_8AF316B4;
extern s16 D_8AF316B0;
extern s16 D_8AF31D78;
extern s32 D_8AF316AC;
extern char D_8AF311A0[];
extern char D_8AF312A0[];
extern char D_8AF313A0[];
extern char D_8AF29740[];
extern char D_8AF29744[];
extern char D_8AF29778[];
extern char D_8AF2977C[];

void func_8AF12A4C(u8 *record) {
    u8 id;
    u8 category;
    s32 texture_index;
    u8 rate;

    id = record[0];
    category = record[1];
    texture_index = id - 1;
    *(s16 *)((u8 *)D_8AF31178 + 0x30) = 6;
    *(s16 *)((u8 *)D_8AF31178 + 0x32) = texture_index;
    *(s16 *)((u8 *)D_8AF3117C + 0x30) = 7;
    *(s16 *)((u8 *)D_8AF3117C + 0x32) = texture_index;
    D_8AF316B2[0] = func_80062D5C(id);
    D_8AF316B2[1] = func_80062E10(id);
    rate = func_80062DD4(id);
    D_8AF316B4 = (s32)((((func_80062DD4(id) * 100.0f / 255.0f) > 0.0f) ? 0.5f : -0.5f) +
                      (rate * 100.0f / 255.0f));
    sprintf(D_8AF312A0, D_8AF29740, D_8AF316B2[1]);
    sprintf(D_8AF313A0, D_8AF29744, D_8AF316B4);
    switch (D_8AF31024) {
    case 0:
        func_8004C54C(0x2F, (s32)func_8004C874(0xC, D_8AF263C4[category]));
        func_8004C54C(0x3D, (s32)D_8AF314A0);
        func_8004C54C(0x3F, (s32)D_8AF315A0);
        *(s16 *)((u8 *)D_8AF31188 + 0x30) = 0x3B;
        *(s16 *)((u8 *)D_8AF31188 + 0x32) = 0x9F;
        break;
    case 1:
        func_8004C54C(0x3F, (s32)D_8AF315A0);
        *(s16 *)((u8 *)D_8AF31188 + 0x30) = 0x3B;
        *(s16 *)((u8 *)D_8AF31188 + 0x32) = 0xA0;
        break;
    case 2:
        func_8004C54C(0x2F, (s32)func_8004C874(0xC, D_8AF263C4[category]));
        func_8004C54C(0x3E, (s32)D_8AF314A0);
        func_8004C54C(0x3F, (s32)D_8AF315A0);
        *(s16 *)((u8 *)D_8AF31188 + 0x30) = 0x3B;
        *(s16 *)((u8 *)D_8AF31188 + 0x32) = 0xA1;
        break;
    }
    func_8004C54C(0x31, (s32)D_8AF312A0);
    func_8004C54C(0x32, (s32)D_8AF313A0);
    func_8004C594(2, D_8AF316B0);
    D_8AF31D78 = func_8AF129F8(id);
    if (D_8AF31D78 >= 0) {
        *(s16 *)((u8 *)D_8AF3118C + 0x32) = D_8AF31D78 + 0xA8;
        *(u16 *)((u8 *)D_8AF3118C + 2) |= 1;
        *(u16 *)((u8 *)D_8AF31190 + 2) |= 1;
    } else {
        *(u16 *)((u8 *)D_8AF3118C + 2) &= ~1;
        *(u16 *)((u8 *)D_8AF31190 + 2) &= ~1;
    }
    if (record[2] != 0) {
        *(s16 *)((u8 *)D_8AF31180 + 0x32) = 0xA2;
    } else {
        *(s16 *)((u8 *)D_8AF31180 + 0x32) = 0x67;
    }
    if (D_8AF316B2[0] >= 2) {
        sprintf(D_8AF311A0, D_8AF29778, D_8AF316B2[0]);
    } else {
        sprintf(D_8AF311A0, D_8AF2977C, D_8AF316AC);
    }
    func_8004C54C(0x30, (s32)D_8AF311A0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF12E30.s")

extern s32 D_8AF26F30;
extern s16 D_8AF316A4;
extern s16 D_8AF316A6;
extern u8 D_8AF316B8;

void func_8AF12E7C(void) {
    D_8AF316A4 = 0;
    D_8AF316A6 = 0;
    _bzero(&D_8AF316B8, 0xE);
    D_8AF26F30 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF12EB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF133C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1FD260/func_8AF13718.s")
#endif
