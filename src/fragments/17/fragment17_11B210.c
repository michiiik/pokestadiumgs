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

extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern s32 func_8004D1FC(u8 *);
extern void func_80044270(s16, s16, s16, s16, s16, s16, s16, s16, s32);

void func_8220B984(void) {
    f32 bias;
    f32 width;
    f32 height;
    f32 scale_x;
    f32 scale_y;
    s32 draw_width;
    u16 *texture;
    Fragment17Slot *slot;
    u8 *cursor;

    gSPDisplayList(D_800D0510++, D_80094E38);
    for (cursor = &D_82210B60; ; ) {
        slot = (Fragment17Slot *)(cursor + 4);
        if (*(s16 *)(cursor + 4) != 0) {
            texture = (u16 *)slot->resource;
            if (texture != 0 && slot->unk_04 > 0 &&
                slot->unk_10 > 0.0f && slot->unk_14 > 0.0f) {
                scale_x = slot->unk_10 * 2.0f;
                scale_y = slot->unk_14 * 2.0f;
                width = (f32)(u32)texture[0] * scale_x;
                height = (f32)(u32)texture[1] * scale_y;
                bias = width > 0.0f ? 0.5f : -0.5f;
                draw_width = (s32)(bias + width);
                bias = height > 0.0f ? 0.5f : -0.5f;
                func_8004D1FC((u8 *)texture);
                gDPPipeSync(D_800D0510++);
                gDPSetEnvColor(D_800D0510++, 255, 255, 255, slot->unk_04);
                func_80044270((s16)(s32)((f32)slot->unk_0C - width / 2),
                              (s16)(s32)((f32)slot->unk_0E - height / 2),
                              draw_width, (s32)(bias + height), 0, 0,
                              (s32)(1024.0f / scale_x), (s32)(1024.0f / scale_y), 0);
            }
        }
        cursor += 24;
        if (cursor == &D_82210C20) {
            break;
        }
    }
}

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

/* mkdraft:func_8220BE94 begin */
extern s32 D_8220E070;

void func_8220BE94(void *arg0) {
    Fragment17Panel *panel = (Fragment17Panel *)arg0;
    s32 counter;
    s32 divisor;

    panel->counter = panel->counter + (counter = panel->counter, divisor = D_8220E070, 1);
    if (panel->counter < divisor) {
        panel->pair_0A.x = (panel->pair_0E.x * panel->counter) / divisor;
        panel->pair_0A.y = (panel->pair_0E.y * panel->counter) / divisor;
        return;
    }
    panel->state = 0;
    panel->counter = 0;
    panel->pair_0A.x = panel->pair_0E.x;
    panel->pair_0A.y = panel->pair_0E.y;
}
/* mkdraft:func_8220BE94 end */

/* mkdraft:func_8220BF68 begin */
s32 func_80054E10(void);
extern s16 D_82210C30;
extern s16 D_82210C32;
extern s16 D_82210C34;
extern s16 D_82210C36;
extern s16 D_82210C38;
extern s32 D_82210C40;
extern u8 D_82210C44;

#pragma COALESCE_AT_LUI(func_8220BF68, D_82210C32, D_82210C34, D_82210C36)
#pragma REWRITE_FUNCTION_WORD(func_8220BF68, 0x20, 0x340FFFFF, 0x240FFFFF)
#pragma SWAP_FUNCTION_WORDS(func_8220BF68, 0x68, 0x00008025, 0x24120002)


void func_8220BF68(s32 arg0) {
    u8 *var_s1;
    s32 var_s0;

    if (func_80054E10() != 0) {
        D_82210C30 = 1;
    } else {
        D_82210C30 = 0;
    }
    D_82210C32 = 0;
    D_82210C34 = 0;
    *(u16 *)&D_82210C36 = -1;
    D_82210C38 = -1;
    D_82210C40 = arg0;
    var_s1 = &D_82210C44;
    var_s0 = 0;
    do {
        func_8220BD00(var_s1, var_s0);
        var_s0 += 1;
        var_s1 += 0x16;
    } while (var_s0 != 2);
    func_8004C8C0(0x52);
    func_8004C8C0(0x51);
    func_8004C8C0(0x11D);
    func_8004C8C0(0x79);
    func_8004C4B0(0x12);
}
/* mkdraft:func_8220BF68 end */

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

void func_8220CB34(s32 x, s32 y, s32 width, s32 height) {
    s32 resource;
    s32 tile_width;
    s32 tile_height;

    resource = func_8004C990(81, 0);
    tile_width = ((u16 *)resource)[0];
    tile_height = ((u16 *)resource)[1];
    tile_width /= 4;
    func_80044270(x, y, tile_width, tile_height, 0, 0, 1024, 1024, 0);
    func_80044270(x + tile_width, y, width - tile_width * 2, tile_height,
                  tile_width << 5, 0, 0, 1024, 0);
    func_80044270(x + width - tile_width, y, tile_width, tile_height,
                  tile_width << 5, 0, 1024, 1024, 0);
    func_80044270(x, y + tile_height, tile_width, height - tile_height * 2,
                  (tile_width * 2) << 5, 0, 1024, 0, 0);
    func_80044270(x, y + height - tile_height, tile_width, tile_height,
                  (tile_width * 2) << 5, 0, 1024, 1024, 0);
    func_80044270(x + tile_width, y + height - tile_height,
                  width - tile_width * 2, tile_height,
                  (tile_width * 3) << 5, 0, 0, 1024, 0);
    func_80044270(x + width - tile_width, y + height - tile_height,
                  tile_width, tile_height, (tile_width * 3) << 5, 0, 1024, 1024, 0);
    func_80044270(x + width - tile_width, y + tile_height,
                  tile_width, height - tile_height * 2,
                  (tile_width * 3) << 5, 0, 1024, 0, 0);
}

extern u8 D_80094E78[];

void func_8220CE10(Fragment17Panel *panel) {
    s32 resource;
    Fragment17HalfPair position;
    struct {
        u8 r;
        u8 g;
        u8 b;
    } environment, primitive;

    resource = func_8004C990(81, 0);
    if (resource != 0) {
        position.x = panel->pair_0A.x + panel->pair_12.x;
        position.y = panel->pair_0A.y + panel->pair_12.y;
        gSPDisplayList(D_800D0510++, D_80094E78);
        gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
        func_8004D1FC((u8 *)resource);
        func_8220C42C((u8 *)&environment, (u8 *)&primitive, (s16 *)panel);
        gDPPipeSync(D_800D0510++);
        gDPSetEnvColor(D_800D0510++, environment.r, environment.g, environment.b, 255);
        gDPSetPrimColor(D_800D0510++, 0, 0, primitive.r, primitive.g, primitive.b, 255);
        func_8220CB34(position.x + 54, position.y + 36, 300, 97);
        func_8220CB34(position.x + 54, position.y + 172, 300, 82);
    }
}

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
