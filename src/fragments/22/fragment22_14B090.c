#include "global.h"


#ifdef VERSION_US
typedef struct Fragment22RowPoint {
    s16 x;
    s16 y;
} Fragment22RowPoint;

typedef struct Fragment22RowEntry {
    s16 kind;
    s16 row_index;
    s16 unk_04;
    s16 state;
    s16 counter;
    s16 width;
    s16 alpha;
    Fragment22RowPoint layout_position;
    Fragment22RowPoint position;
    Fragment22RowPoint animation_start;
    Fragment22RowPoint animation_target;
    s16 unk_1e;
    s16 selection;
    s16 option_count;
    u32 payload;
} Fragment22RowEntry;

typedef struct Fragment22RowOptionCounts {
    s16 values[5];
} Fragment22RowOptionCounts;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Quad800548C4;

typedef struct Fragment22Menu {
    s16 unk_00;
    s16 state;
    s16 unk_04;
    s16 selection;
    s16 unk_08;
    s16 unk_0a;
    u16 flags;
    s16 row_counter;
    s16 unk_10;
    s16 unk_12;
    s16 alpha;
    s16 unk_16;
    void *unk_18;
    void *unk_1c;
    Quad800548C4 *settings;
    Quad800548C4 settings_backup;
    Fragment22RowEntry rows[16];
} Fragment22Menu;
extern void *D_80087200;
extern void func_800226C0(s32);
extern void func_800548C4(Quad800548C4 *);
extern void func_80051D64(s32, s32);
extern void func_82701300(void *, u8 *, s32);

typedef char Fragment22RowEntrySizeCheck[sizeof(Fragment22RowEntry) == 40 ? 1 : -1];
typedef char Fragment22RowOptionCountsSizeCheck[sizeof(Fragment22RowOptionCounts) == 10 ? 1 : -1];
extern Fragment22RowOptionCounts D_82703280;
extern u32 D_8270329C[];

s32 func_82700DD0(s32 value) {
    OSIntMask old_mask;

    old_mask = osSetIntMask(OS_IM_NONE);
    if (!(IO_READ(PI_STATUS_REG) & 3) && (IO_READ(PI_DOM1_ADDR2 + 0xD10) & 0xFFFF) != 1024) {
        value = -64;
    }
    osSetIntMask(old_mask);
    return value;
}

void *func_82700E38(void *arg0, s32 arg1) {
    s32 i;
    u8 *ptr;
    void *result;
    void *base;

    result = NULL;
    i = 0;
    base = arg0;
    if (arg1 > 0) {
        ptr = base;
        do {
            i += 1;
            if (*(s16 *)ptr == 0) {
                result = ptr;
                break;
            }
            ptr += 0x28;
        } while (i != arg1);
    }
    return result;
}

void *func_82700E70(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 i;
    u8 *ptr;
    void *result;

    result = NULL;
    i = 0;
    if (arg3 > 0) {
        ptr = arg2;
        do {
            i += 1;
            if ((arg0 == *(s16 *)ptr) && (arg1 == *(s16 *)(ptr + 2))) {
                result = ptr;
                break;
            }
            ptr += 0x28;
        } while (i != arg3);
    }
    return result;
}

void func_82700EC8(void *arg0) {
    struct Pair { s16 x, y; };
    struct State {
        u8 pad[0xA];
        s16 width;
        s16 unused;
        struct Pair current;
        struct Pair previous;
    };
    struct State *state = arg0;
    state->width = 0xC0;
    state->current.x = 0x280 - state->width;
    state->current.y = 0x52;
    state->previous = state->current;
}

void func_82700EFC(Fragment22RowEntry *entry, s32 unused) {
    Fragment22RowOptionCounts option_counts = D_82703280;

    entry->width = 369;
    entry->layout_position.x = 640 - entry->width;
    entry->layout_position.y = entry->row_index * 44 + 126;
    entry->position = entry->layout_position;
    entry->selection = 0;
    entry->option_count = option_counts.values[entry->row_index];
    entry->payload = D_8270329C[entry->row_index];
}

void func_82700FA4(Fragment22RowEntry *entry) {
    entry->width = 208;
    entry->layout_position.x = 640 - entry->width;
    entry->layout_position.y = entry->row_index * 44 + 354;
    entry->position = entry->layout_position;
}

void func_82700FF0(Fragment22RowEntry *entry) {
    entry->width = 369;
    entry->layout_position.x = 640 - entry->width;
    entry->layout_position.y = entry->row_index * 44 + 310;
    entry->position = entry->layout_position;
}

void func_8270103C(Fragment22RowEntry *entry, s32 kind_value, s32 row_index) {
    _bzero(entry, sizeof(*entry));
    entry->kind = kind_value;
    entry->row_index = row_index;
    entry->state = 0;
    entry->alpha = 255;
    switch (entry->kind) {
    case 1:
        func_82700EC8(entry);
        break;
    case 2:
        func_82700EFC(entry, 1);
        break;
    case 3:
        func_82700FA4(entry);
        break;
    case 4:
        func_82700FF0(entry);
        break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827010F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701278.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701300.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827013F0.s")

extern u16 D_827034EC;
extern u8 D_82703514[];
s32 func_827015A4(s32 arg0, s32 arg1) {
    s32 result;
    void *entry;

    result = 0;
    if (D_827034EC & 1) {
        entry = func_82700E70(arg0, arg1, D_82703514, 0x10);
        if ((entry != NULL) && (*(s16 *)((u8 *)entry + 6) == 0)) {
            *(s16 *)((u8 *)entry + 6) = 1;
            *(s16 *)((u8 *)entry + 8) = 0;
            result = 1;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_8270160C.s")

extern void * func_82700E70(s32 arg0, s32 arg1, void *arg2, s32 arg3);
void func_8270174C(void *arg0) {
    s32 i; u8 *table; s32 one; s32 mask; void *entry;
    i=0; table=(u8 *)arg0+0x34; one=1; mask=-2;
    do { entry=func_82700E70(2,i,table,0x10); switch(i) { case 0: (*(u8 **)((u8 *)arg0+0x20))[0]=*(s16 *)((u8 *)entry+0x20); break; case 1: if(*(s16 *)((u8 *)entry+0x20)==0) (*(u8 **)((u8 *)arg0+0x20))[1]|=1; else (*(u8 **)((u8 *)arg0+0x20))[1]&=mask; break; } i++; } while(i!=5);
}

s32 func_82701820(s32 arg0, s32 arg1) {
    s32 result;
    void *entry;

    result = 0;
    if (D_827034EC & 1) {
        entry = func_82700E70(arg0, arg1, D_82703514, 0x10);
        if ((entry != NULL) && (*(s16 *)((u8 *)entry + 6) == 2)) {
            *(s16 *)((u8 *)entry + 6) = 4;
            *(s16 *)((u8 *)entry + 8) = 0;
            result = 1;
        }
    }
    return result;
}

s32 func_8270188C(s32 kind, s32 row_index, s16 x, s16 y) {
    s32 result;
    Fragment22RowEntry *entry;

    result = 0;
    if (D_827034EC & 1) {
        entry = func_82700E70(kind, row_index, D_82703514, 16);
        if (entry != NULL && entry->state == 2) {
            entry->state = 3;
            entry->counter = 0;
            entry->animation_start = entry->position;
            entry->animation_target.x = x;
            entry->animation_target.y = y;
            result = 1;
        }
    }
    return result;
}

s32 func_82701920(void *arg0) {
    u8 *state;
    s32 result;
    u8 *record;
    s16 flag;

    state = *(u8 **)((u8 *)arg0 + 0x20);
    result = 0;
    record = *(u8 **)((u8 *)arg0 + 0x1C);
    flag = (s16)((state[1] & 1) != 0);
    if (*(s16 *)record != 0) result = 1;
    if (*(u16 *)(record + 2) != state[0]) result = 1;
    if (flag != *(s16 *)(record + 4)) result = 1;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701978.s")

extern void *func_82700E70(s32, s32, void *, s32);
extern s32 func_827015A4(s32, s32);
void func_82701CB8(void *arg0) {
    s32 pad_frame[3];
    s32 sp28;
    s32 temp_a1;
    s32 var_s0;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;

    temp_s2 = (u8 *)arg0 + 0x34;
    temp_v0 = func_82700E70(2, 4, temp_s2, 0x10);
    sp28 = 1;
    if (*(s16 *)((u8 *)temp_v0 + 6) != 0) {
        *(s16 *)((u8 *)arg0 + 0x12) = (s16)(0xFF - *(s16 *)((u8 *)temp_v0 + 0xC));
    } else {
        *(s16 *)((u8 *)arg0 + 0x12) = 0xFF;
    }
    if (*(s16 *)((u8 *)arg0 + 0xE) >= 0) {
        if ((*(s16 *)((u8 *)arg0 + 0xE) & 3) == 0) {
            temp_a1 = *(s16 *)((u8 *)arg0 + 0xE) / 4;
            if (temp_a1 < 2) {
                func_827015A4(3, temp_a1);
            } else {
                *(s16 *)((u8 *)arg0 + 0xE) = -1;
            }
        }
        if (*(s16 *)((u8 *)arg0 + 0xE) >= 0) {
            *(s16 *)((u8 *)arg0 + 0xE) = *(s16 *)((u8 *)arg0 + 0xE) + 1;
        }
    }
    var_s0 = 0;
    do {
        temp_v0_2 = func_82700E70(3, var_s0, temp_s2, 0x10);
        var_s0 += 1;
        if ((temp_v0_2 != NULL) && (*(s16 *)((u8 *)temp_v0_2 + 6) != 2)) {
            sp28 = 0;
            break;
        }
    } while (var_s0 != 2);
    if (sp28 != 0) {
        *(s16 *)((u8 *)arg0 + 2) = 4;
        *(s16 *)((u8 *)arg0 + 6) = 1;
        *(u16 *)((u8 *)arg0 + 0xC) |= 2;
    }
}

void func_82701DF4(Fragment22Menu *menu) {
    s32 previous;
    s32 confirmed;
    s32 i;

    previous = menu->selection;
    confirmed = 0;
    if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x800) {
        menu->selection--;
        if (menu->selection < 0) {
            menu->selection = 0;
        }
    }
    if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x400) {
        menu->selection++;
        if (menu->selection >= 2) {
            menu->selection = 1;
        }
    }
    if (previous != menu->selection) {
        func_800226C0(1);
    }
    if (*(u16 *)((u8 *)D_80087200 + 8) & 0x8000) {
        confirmed = 1;
        if (menu->selection == 0) {
            func_800226C0(16);
        } else {
            func_800226C0(3);
        }
    } else if (*(u16 *)((u8 *)D_80087200 + 8) & 0x4000) {
        menu->selection = 1;
        confirmed = 1;
        func_800226C0(3);
    }
    if (confirmed) {
        if (menu->selection == 0) {
            menu->state = 5;
            menu->row_counter = 0;
            menu->selection = 1;
            menu->unk_10 = 1;
        } else {
            menu->state = 7;
            menu->row_counter = 0;
            menu->flags &= ~2;
            i = 0;
            do {
                func_82701820(3, i);
                i++;
            } while (i != 2);
            func_827015A4(2, 4);
        }
    }
}


void func_82701F7C(Fragment22Menu *menu) {
    s32 previous;
    s32 confirmed;
    s32 i;

    previous = menu->selection;
    confirmed = 0;
    if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x800) {
        menu->selection--;
        if (menu->selection < 0) {
            menu->selection = 0;
        }
    }
    if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x400) {
        menu->selection++;
        if (menu->selection >= 2) {
            menu->selection = 1;
        }
    }
    if (previous != menu->selection) {
        func_800226C0(1);
    }
    if (*(u16 *)((u8 *)D_80087200 + 8) & 0x8000) {
        confirmed = 1;
        if (menu->selection == 0) {
            func_800226C0(67);
        } else {
            func_800226C0(3);
        }
    } else if (*(u16 *)((u8 *)D_80087200 + 8) & 0x4000) {
        menu->selection = 1;
        confirmed = 1;
        func_800226C0(3);
    }
    if (confirmed) {
        if (menu->selection == 0) {
            menu->state = 6;
            menu->row_counter = 0;
        } else {
            menu->state = 7;
            menu->row_counter = 0;
            menu->flags &= ~2;
            i = 0;
            do {
                func_82701820(3, i);
                i++;
            } while (i != 2);
            func_827015A4(2, 4);
        }
    }
}

void func_827020F4(void *arg0)
{
  s16 temp_v0;
  temp_v0 = *((s16 *) (((u8 *) arg0) + 0xE));
  if (temp_v0 < 0xA)
  {
    *((s16 *) (((u8 *) arg0) + 0xE)) = (s16) (temp_v0 + 1);
  }
  temp_v0 = *((s16 *) (((u8 *) arg0) + 0xE));
  if (temp_v0 == 2)
  {
    func_8005314C();
    func_80055028();
    func_8005487C(*((s32 *) (((u8 *) arg0) + 0x20)));
    func_82701300(arg0, *((s32 *) (((u8 *) arg0) + 0x20)), 1);
    *((s16 *) (((u8 *) arg0) + 0xA)) = 3;
  }
}

void func_8270216C(void *arg0) {
    void *sp34;
    void *sp20;
    volatile s32 reserve[2];
    void *temp_v0;

    sp20 = (u8 *)arg0 + 0x34;
    sp34 = func_82700E70(3, 0, sp20, 0x10);
    temp_v0 = func_82700E70(2, 4, sp20, 0x10);
    if (*(s16 *)((u8 *)sp34 + 6) != 0) {
        *(s16 *)((u8 *)arg0 + 0x12) = *(s16 *)((u8 *)sp34 + 0xC);
    } else {
        *(s16 *)((u8 *)arg0 + 0x12) = 0;
    }
    if ((temp_v0 != NULL) && (*(s16 *)((u8 *)temp_v0 + 6) == 2) &&
        (*(s16 *)((u8 *)arg0 + 0x12) == 0)) {
        *(s16 *)((u8 *)arg0 + 2) = 2;
        *(s16 *)((u8 *)arg0 + 0x16) = 2;
        *(void **)((u8 *)arg0 + 0x18) = (u8 *)arg0 + 4;
        *(u16 *)((u8 *)arg0 + 0xC) |= 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702220.s")


void func_82702364(Fragment22Menu *menu) {
    s32 previous;
    s32 confirmed;
    s32 i;

    previous = menu->unk_08;
    confirmed = 0;
    if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x800) {
        menu->unk_08--;
        if (menu->unk_08 < 0) {
            menu->unk_08 = 0;
        }
    }
    if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x400) {
        menu->unk_08++;
        if (menu->unk_08 >= 3) {
            menu->unk_08 = 2;
        }
    }
    if (previous != menu->unk_08) {
        func_800226C0(1);
    }
    if (*(u16 *)((u8 *)D_80087200 + 8) & 0x8000) {
        confirmed = 1;
    } else if (*(u16 *)((u8 *)D_80087200 + 8) & 0x4000) {
        confirmed = 1;
        menu->unk_08 = 2;
    }
    if (confirmed) {
        switch (menu->unk_08) {
        case 0:
            menu->state = 12;
            menu->row_counter = 0;
            menu->unk_0a = 100;
            func_800548C4(menu->settings);
            func_80051D64(20, 0);
            func_800226C0(17);
            break;
        case 1:
            menu->state = 12;
            menu->row_counter = 0;
            menu->unk_0a = 4;
            func_800226C0(20);
            func_82701300(menu, (u8 *)&menu->settings_backup, 1);
            break;
        default:
            menu->state = 11;
            menu->row_counter = 0;
            menu->flags &= ~2;
            for (i = 0; i != 3; i++) {
                func_82701820(4, i);
            }
            func_827015A4(2, 3);
            func_827015A4(2, 4);
            func_800226C0(3);
            break;
        }
    }
}

void func_82702528(void *arg0) {
    void *sp3C;
    void *sp24;
    void *temp_a2;
    void *temp_v0;
    volatile s32 reserve[2];

    temp_a2 = (u8 *)arg0 + 0x34;
    sp24 = temp_a2;
    sp3C = func_82700E70(4, 0, temp_a2, 0x10);
    func_82700E70(2, 3, temp_a2, 0x10);
    temp_v0 = func_82700E70(2, 4, temp_a2, 0x10);
    if (*(s16 *)((u8 *)sp3C + 6) != 0) {
        *(s16 *)((u8 *)arg0 + 0x14) = *(s16 *)((u8 *)sp3C + 0xC);
    } else {
        *(s16 *)((u8 *)arg0 + 0x14) = 0;
    }
    if ((temp_v0 != NULL) && (*(s16 *)((u8 *)temp_v0 + 6) == 2) &&
        (*(s16 *)((u8 *)arg0 + 0x14) == 0)) {
        *(s16 *)((u8 *)arg0 + 2) = 2;
        *(s16 *)((u8 *)arg0 + 0x16) = 2;
        *(void **)((u8 *)arg0 + 0x18) = (u8 *)arg0 + 4;
        *(u16 *)((u8 *)arg0 + 0xC) |= 2;
    }
}

void func_827025F0(void *arg0) {
    void *entry;

    entry = func_82700E70(2, 2, (u8 *)arg0 + 0x34, 0x10);
    if (*(s16 *)((u8 *)entry + 6) == 2) {
        *(s16 *)((u8 *)arg0 + 0xE) = *(s16 *)((u8 *)arg0 + 0xE) + 1;
        if (*(s16 *)((u8 *)arg0 + 0xE) >= 2) {
            *(s16 *)((u8 *)arg0 + 0xA) = 2;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702658.s")

typedef struct Fragment22TextureHeader {
    u16 width;
    u16 height;
    u8 format;
    u8 size;
    u16 unk_06;
} Fragment22TextureHeader;
extern u8 D_827032C0[];
extern u8 D_827032D0[];
extern u8 D_827032D4[];
extern Gfx *D_800D0510;
extern Gfx D_80094E38[];
extern s32 func_8004C990(s32, s32);
extern s32 func_8004D19C(s32, s32, s32, s32, s32);
extern void func_80044270(s16, s16, s16, s16, s16, s16, s16, s16, s32);
extern void *func_8004C874(s32, s32);
extern void func_800495F8(s32, s32, s32, const char *, ...);
extern void func_800498C4(void);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800496A4(s32, s32);
extern void func_800499EC(void);

void func_82702810(Fragment22RowEntry *entry) {
    Fragment22TextureHeader *texture;
    struct RowColor {
        u8 red;
        u8 green;
        u8 blue;
    } *color;
    s32 alpha;

    texture = (Fragment22TextureHeader *)func_8004C990(247, 0);
    alpha = entry->alpha * 160 / 255;
    color = (struct RowColor *)&D_827032C0[entry->kind * 3];
    if (texture != NULL) {
        gSPDisplayList(D_800D0510++, D_80094E38);
        gDPSetEnvColor(D_800D0510++, color->red, color->green, color->blue, alpha);
        func_8004D19C(entry->position.x, entry->position.y, (s32)texture, 0, 0);
        func_80044270(entry->position.x + texture->width, entry->position.y,
                     entry->width - texture->width, (s16)texture->height,
                     (texture->width - 1) << 5, 0, 0, 1024, 0);
    }
}

void func_82702954(void *record, s32 selected) {
    const char *text;
    s32 alpha;

    text = func_8004C874(26, 4);
    alpha = (*(s16 *)((u8 *)record + 12) * 255) / 255;
    func_800498C4();
    func_8004972C(255, 255, 255, alpha);
    if (text != NULL) {
        func_800496A4(8, 0);
        func_800495F8(*(s16 *)((u8 *)record + 18) + 30,
                     *(s16 *)((u8 *)record + 20) + 6, 0, text);
    }
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702A2C.s")

extern s32 D_827032E4;

void func_82702BC8(arg0, arg1)
void *arg0;
s32 arg1;
{
    volatile s32 reserve[2];
    s32 sp2C;
    s32 sp28;
    u8 *sp24;

    sp2C = D_827032E4;
    sp28 = (*(s16 *)((u8 *)arg0 + 0xC) * 0xFF) / 255;
    if (arg1 == 0) {
        sp24 = D_827032D0;
    } else {
        sp24 = D_827032D4;
    }
    func_800498C4();
    func_8004972C(sp24[0], sp24[1], sp24[2], sp28);
    if (((s16 *)&sp2C)[*(s16 *)((u8 *)arg0 + 2)] >= 0) {
        func_800496A4(0x10, 0);
        func_800495F8(
            *(s16 *)((u8 *)arg0 + 0x12) + 0x40,
            *(s16 *)((u8 *)arg0 + 0x14) + 4,
            0,
            func_8004C874(0x1A, ((s16 *)&sp2C)[*(s16 *)((u8 *)arg0 + 2)]));
    }
    func_800499EC();
}

extern struct IDs { s16 a, b, c; } D_827032E8;
void func_82702CD8(arg0, arg1) void *arg0; s32 arg1; {
    volatile s32 reserve[2];
    struct IDs sp30;
    s32 sp2C;
    u8 *sp28;

    sp30 = D_827032E8;
    sp2C = (*(s16 *)((u8 *)arg0 + 0xC) * 0xFF) / 255;
    if (arg1 == 0) {
        sp28 = D_827032D0;
    } else {
        sp28 = D_827032D4;
    }
    func_800498C4();
    func_8004972C(sp28[0], sp28[1], sp28[2], sp2C);
    if (((s16 *)&sp30)[*(s16 *)((u8 *)arg0 + 2)] >= 0) {
        func_800496A4(0x10, 0);
        func_800495F8(
            *(s16 *)((u8 *)arg0 + 0x12) + 0x40,
            *(s16 *)((u8 *)arg0 + 0x14) + 4,
            0,
            func_8004C874(0x1A, ((s16 *)&sp30)[*(s16 *)((u8 *)arg0 + 2)]));
    }
    func_800499EC();
}

extern void func_82702954(void *, s32);
extern void func_82702A2C(void *, s32);
extern void func_82702BC8(void *, s32);
extern void func_82702CD8(void *, s32);

void func_82702DF8(void *record, s32 selected) {
    s16 kind;

    kind = *(s16 *)record;
    switch (kind) {
    case 1:
        func_82702954(record, selected);
        return;
    case 2:
        func_82702A2C(record, selected);
        return;
    case 3:
        func_82702BC8(record, selected);
        return;
    case 4:
        func_82702CD8(record, selected);
        return;
    }
}

extern void func_8004989C(s32);

void func_82702E78(void *record) {
    Fragment22Menu *menu = record;
    s32 alpha;

    func_800498C4();
    func_800496A4(8, 0);
    alpha = menu->unk_12;
    if (alpha > 0) {
        func_8004972C(255, 255, 0, alpha);
        func_8004989C(26);
        if (menu->unk_10 == 1) {
            func_800495F8(581, 300, 2, func_8004C874(26, 18));
        } else {
            func_800495F8(581, 300, 2, func_8004C874(26, 9));
        }
    }
    alpha = menu->alpha;
    if (alpha > 0) {
        func_8004972C(255, 255, 0, alpha);
        func_800495F8(581, 282, 2, func_8004C874(26, 19));
    }
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702F70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827030D0.s")

extern s16 D_827034EA;
s32 func_82703188(void) {
    s32 result = -2;
    if (D_827034EC & 1) {
        result = D_827034EA;
    }
    return result;
}
#endif
