#include "global.h"


#ifdef VERSION_US
typedef struct Fragment17Slot {
    s16 state;
    s16 counter;
    s16 unk_04;
    s16 unk_06;
    s32 resource;
    s16 unk_0C;
    s16 unk_0E;
    f32 unk_10;
    f32 unk_14;
} Fragment17Slot;

typedef struct Fragment17SlotPool {
    u32 unk_00;
    Fragment17Slot slots[8];
} Fragment17SlotPool;

typedef struct Fragment17SlotFrame {
    s16 resource_id;
    s16 unk_02;
    f32 unk_04;
    f32 unk_08;
} Fragment17SlotFrame;

extern Fragment17SlotFrame D_8220E1D0[];
extern s32 func_8004C990(s32, s32);

void func_8220B850(Fragment17Slot *slot) {
    Fragment17SlotFrame *entry;

    slot->counter++;
    if (slot->counter < 21) {
        entry = &D_8220E1D0[slot->counter];
        slot->unk_04 = 155 - (slot->counter * 155) / 20;
        slot->resource = func_8004C990(159, entry->resource_id);
        slot->unk_10 = entry->unk_04;
        slot->unk_14 = entry->unk_08;
    } else {
        slot->state = 0;
    }
}

extern void _bzero(s32 *, s32);
extern void func_8004C8C0(s32);
extern u8 D_82210B60;

void func_8220B900(void) {
    func_8004C8C0(0x9F);
    _bzero(&D_82210B60, 0xC4);
}

extern u8 D_82210C20;

void func_8220B930(void) {
    u8 *cursor = &D_82210B60, *end = &D_82210C20;

    do {
        if (*(s16 *)(cursor + 4) != 0) {
            func_8220B850((Fragment17Slot *)(cursor + 4));
        }
        cursor += 24;
    } while (cursor != end);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220B984.s")

s32 func_8220BC40(void) {
    Fragment17SlotPool *pool = (Fragment17SlotPool *)&D_82210B60;
    s32 result = -1;
    s32 index;

    for (index = 0; index < 8; index++) {
        if (pool->slots[index].state == 0) {
            result = index;
            break;
        }
    }
    return result;
}

s32 func_8220BC7C(s32 arg0, s32 arg1) {
    s32 result;
    s32 temp_v0;
    u8 *temp_v1;
    result = 0;
    temp_v0 = func_8220BC40();
    if (temp_v0 != -1) {
        temp_v1 = (u8 *)(&D_82210B60) + (temp_v0 * 0x18);
        *(s16 *)(temp_v1 + 4) = 1;
        *(s16 *)(temp_v1 + 6) = 0;
        *(s16 *)(temp_v1 + 8) = 0;
        *(s32 *)(temp_v1 + 0xC) = 0;
        result = 1;
        *(s16 *)(temp_v1 + 0x10) = arg0;
        *(f32 *)(temp_v1 + 0x14) = 0.0f;
        *(f32 *)(temp_v1 + 0x18) = 0.0f;
        *(s16 *)(temp_v1 + 0x12) = arg1;
    }
    return result;
}

typedef struct Fragment17HalfPair {
    s16 x;
    s16 y;
} Fragment17HalfPair;

typedef struct Fragment17Panel {
    s16 mode;
    s16 state;
    s16 counter;
    Fragment17HalfPair pair_06;
    Fragment17HalfPair pair_0A;
    Fragment17HalfPair pair_0E;
    Fragment17HalfPair pair_12;
} Fragment17Panel;

void func_8220BD00(void *arg0, s32 mode) {
    Fragment17Panel *panel = (Fragment17Panel *)arg0;

    panel->mode = mode;
    panel->state = 0;
    panel->counter = 0;
    switch (mode) {
    case 0:
        panel->pair_06.x = 407;
        panel->pair_06.y = 321;
        panel->pair_0A.x = 0;
        panel->pair_0A.y = -480;
        panel->pair_12.x = 116;
        panel->pair_12.y = 75;
        break;
    case 1:
        panel->pair_06.x = 407;
        panel->pair_06.y = 134;
        panel->pair_0A.x = 640;
        panel->pair_0A.y = 0;
        panel->pair_12.x = 116;
        panel->pair_12.y = 173;
        break;
    }
    panel->pair_0E = panel->pair_0A;
}

extern s16 D_82210C36;
void func_8220BD90(s16 *arg0) {
    arg0[1] = 1;
    arg0[2] = 0;
    D_82210C36 = arg0[0];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220BDAC.s")

void func_8220BE84(s16 *arg0) {
    arg0[1] = 3;
    arg0[2] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220BE94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220BF68.s")

extern void func_8220BD90(s16 *);
extern void func_800226C0(s32);
void func_8220C030(void *arg0) {
    s16 temp_v0;
    temp_v0 = *(s16 *)((u8 *)arg0 + 0x16);
    switch (temp_v0) {
    case 0:
        func_8220BD90((s16 *)((u8 *)arg0 + 0x14));
        func_800226C0(0xA9);
        break;
    case 2:
        *(s16 *)((u8 *)arg0 + 2) = 2;
        *(s16 *)((u8 *)arg0 + 4) = 0;
        break;
    }
}

typedef struct Fragment17MenuPrefix {
    s16 enabled;
    s16 state;
    s16 counter;
    s16 selected_panel;
    s16 result;
    s16 selection;
    s16 secondary_selection;
} Fragment17MenuPrefix;

extern void *D_80087200;

void func_8220C08C(void *arg0) {
    Fragment17MenuPrefix *menu = (Fragment17MenuPrefix *)arg0;
    s32 previous_selection = menu->selection;

    if ((*(u16 *)((u8 *)D_80087200 + 8) & 0x800) != 0) {
        menu->selection--;
        if (menu->selection < 0) {
            menu->selection = 0;
        }
    }
    if ((*(u16 *)((u8 *)D_80087200 + 8) & 0x400) != 0) {
        menu->selection++;
        if (menu->selection >= 3) {
            menu->selection = 2;
        }
    }
    if (previous_selection != menu->selection) {
        func_800226C0(1);
    }
    if ((*(u16 *)((u8 *)D_80087200 + 8) & 0x8000) != 0) {
        switch (menu->selection) {
        case 0:
            menu->state = 4;
            menu->result = 1;
            func_800226C0(147);
            break;
        case 1:
            menu->state = 4;
            menu->result = 0;
            func_800226C0(163);
            break;
        case 2:
            menu->state = 3;
            menu->counter = 0;
            menu->secondary_selection = 1;
            func_800226C0(16);
            break;
        }
    }
}

extern void Save_ResetAndCommitTypedRecord(s32, s32);

void func_8220C1C4(void *arg0) {
    Fragment17MenuPrefix *menu = (Fragment17MenuPrefix *)arg0;
    s32 previous_selection = menu->secondary_selection;
    s32 return_to_menu = 0;

    switch (*(s16 *)((u8 *)arg0 + 44)) {
    case 0:
        func_8220BD90((s16 *)((u8 *)arg0 + 42));
        func_800226C0(166);
        break;
    case 2:
        if ((*(u16 *)((u8 *)D_80087200 + 8) & 0x800) != 0) {
            menu->secondary_selection--;
            if (menu->secondary_selection < 0) {
                menu->secondary_selection = 0;
            }
        }
        if ((*(u16 *)((u8 *)D_80087200 + 8) & 0x400) != 0) {
            menu->secondary_selection++;
            if (menu->secondary_selection >= 2) {
                menu->secondary_selection = 1;
            }
        }
        if (previous_selection != menu->secondary_selection) {
            func_800226C0(1);
        }
        if ((*(u16 *)((u8 *)D_80087200 + 8) & 0x8000) != 0) {
            if (menu->secondary_selection == 0) {
                menu->state = 4;
                menu->result = 0;
                Save_ResetAndCommitTypedRecord(21, 0);
                func_800226C0(67);
            } else {
                return_to_menu = 1;
            }
        } else if ((*(u16 *)((u8 *)D_80087200 + 8) & 0x4000) != 0) {
            return_to_menu = 1;
        }
        break;
    }
    if (return_to_menu) {
        menu->state = 2;
        menu->counter = 0;
        func_8220BE84((s16 *)((u8 *)arg0 + 42));
        func_800226C0(3);
        func_800226C0(168);
        menu->selected_panel = 0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220C340.s")

void func_8220C42C(u8 *arg0, u8 *arg1, s16 *arg2) {
    if (*arg2 == 1) {
        arg0[0] = 0xDC;
        arg0[1] = 0x96;
        arg0[2] = 0x96;
    } else {
        arg0[0] = 0xFF;
        arg0[1] = 0xFF;
        arg0[2] = 0xFF;
    }
    arg1[0] = 0;
    arg1[1] = 0;
    arg1[2] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220C470.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220C6C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220CB34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220CE10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220CF9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220D3C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220D560.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_11B210/func_8220D630.s")

extern s16 D_82210C38;
s32 func_8220D670(void) { s32 result = D_82210C38; return result; }

extern s16 D_82210C30;
extern s16 D_82210C32;
s32 func_8220D67C(void) {
    s32 result = 0;
    if (D_82210C30 != 0) {
        if (D_82210C32 != 0) result = 1;
    }
    return result;
}

s32 func_8220D6AC(void) {
    s32 result = 0;
    if ((D_82210C30 != 0) && ((D_82210C32 == 2) || (D_82210C32 == 3))) {
        result = 1;
    }
    return result;
}
#endif
