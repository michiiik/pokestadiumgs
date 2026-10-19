#include "global.h"


#ifdef VERSION_US
extern void func_8005FC7C(s32, u8, u8);
extern u8 * func_8005FA1C(s32);
extern u8 func_800648A0(u8);
// Selected-decoration fields 0..3 are bed, carpet, plant, and poster.
// func_8005FA1C selects these save bytes; func_8005FC7C writes saved room-map blocks.
//@src/585D0.c
void RoomDecor_SetBed_fragment87(u8 slot, u8 decoration, s32 update_map) {
    u8 *decorations;
    u8 block_id;
    s32 save_index;

    save_index = slot;
    decorations = func_8005FA1C(save_index);
    if (decoration < 2 || decoration >= 6) {
        decoration = 0;
    }
    decorations[0] = decoration;
    if (update_map != 0) {
        if (decoration != 0) {
            block_id = func_800648A0(decoration);
        } else {
            block_id = func_800648A0(1);
        }
        func_8005FC7C(save_index, 19, block_id);
    }
}

void RoomDecor_SetCarpet_fragment87(u8 slot, u8 decoration, s32 update_map) {
    u8 *decorations;
    u8 block_id;
    s32 save_index;

    save_index = slot;
    decorations = func_8005FA1C(save_index);
    if (decoration < 7 || decoration >= 11) {
        decoration = 0;
    }
    decorations[1] = decoration;
    if (update_map != 0) {
        if (decoration != 0) {
            block_id = func_800648A0(decoration);
        } else {
            block_id = func_800648A0(6);
        }
        func_8005FC7C(save_index, 7, block_id);
        func_8005FC7C(save_index, 13, block_id + 1);
        func_8005FC7C(save_index, 14, block_id + 2);
        func_8005FC7C(save_index, 15, block_id + 1);
    }
}

void RoomDecor_SetPlant_fragment87(u8 slot, u8 decoration, s32 update_map) {
    u8 *decorations;
    u8 block_id;
    s32 save_index;

    save_index = slot;
    decorations = func_8005FA1C(save_index);
    if (decoration < 12 || decoration >= 15) {
        decoration = 0;
    }
    decorations[2] = decoration;
    if (update_map != 0) {
        if (decoration != 0) {
            block_id = func_800648A0(decoration);
        } else {
            block_id = func_800648A0(11);
        }
        func_8005FC7C(save_index, 22, block_id);
    }
}

extern void func_8005F9CC(s32, u16);
extern void func_8005F9F4(s32, u16);
void RoomDecor_SetPoster_fragment87(u8 slot, u8 decoration, s32 update_map) {
    u8 *decorations;
    u8 block_id;
    s32 save_index;

    save_index = slot;
    decorations = func_8005FA1C(save_index);
    if (decoration >= 16 && decoration < 20) {
        func_8005F9CC(save_index, 716);
    } else {
        decoration = 0;
        func_8005F9F4(save_index, 716);
    }
    decorations[3] = decoration;
    if (update_map != 0) {
        if (decoration != 0) {
            block_id = func_800648A0(decoration);
        } else {
            block_id = func_800648A0(15);
        }
        func_8005FC7C(save_index, 10, block_id);
    }
}

extern u8 *func_8005FD24(s32);
extern u8 func_8005D92C(s32);
extern void func_8005FDB0(s32, s32, s32);
void func_81B002EC(u8 arg0, u8 arg1, s32 arg2) {
    u8 *sp2C;
    u8 *sp28;
    u8 sp27;
    s32 temp_s0;

    temp_s0 = arg0;
    sp2C = func_8005FA1C(temp_s0);
    sp28 = func_8005FD24(temp_s0);
    if (func_8005D92C(temp_s0) == 7) {
        sp27 = 1;
    } else {
        sp27 = 2;
    }
    if (((s32) arg1 >= 21) && ((s32) arg1 < 25)) {
        sp2C[4] = arg1;
        func_8005F9F4(temp_s0, 1857);
        if (arg2 != 0) {
            sp28[0] = func_800648A0(arg1);
            func_8005FDB0(temp_s0, sp27, 0);
        }
    } else {
        sp2C[4] = 0;
        if ((!arg1) && (!arg1)) { } // FAKE: redundant empty condition.
        func_8005F9CC(temp_s0, 1857);
        if (arg2 != 0) {
            func_8005FDB0(temp_s0, sp27 & 0xFF, 0xFF);
        }
    }
}

void func_81B003EC(u8 arg0, u8 arg1, s32 arg2) {
    u8 *sp2C;
    u8 *sp28;
    u8 sp27;
    s32 temp_s0;

    temp_s0 = arg0;
    sp2C = func_8005FA1C(temp_s0);
    sp28 = func_8005FD24(temp_s0);
    if (func_8005D92C(temp_s0) == 7) {
        sp27 = 2;
    } else {
        sp27 = 3;
    }
    if (((s32) arg1 >= 30) && ((s32) arg1 < 53)) {
        sp2C[5] = arg1;
        func_8005F9F4(temp_s0, 1858);
        if (arg2 != 0) {
            sp28[1] = func_800648A0(arg1);
            func_8005FDB0(temp_s0, sp27, 0);
        }
    } else {
        sp2C[5] = 0;
        if ((!arg1) && (!arg1)) { } // FAKE: redundant empty condition.
        func_8005F9CC(temp_s0, 1858);
        if (arg2 != 0) {
            func_8005FDB0(temp_s0, sp27 & 0xFF, 0xFF);
        }
    }
}

void func_81B004EC(u8 arg0, u8 arg1, s32 arg2) {
    u8 *sp2C;
    u8 *sp28;
    u8 sp27;
    s32 temp_s0;

    temp_s0 = arg0;
    sp2C = func_8005FA1C(temp_s0);
    sp28 = func_8005FD24(temp_s0);
    if (func_8005D92C(temp_s0) == 7) {
        sp27 = 3;
    } else {
        sp27 = 4;
    }
    if (((s32) arg1 >= 30) && ((s32) arg1 < 53)) {
        sp2C[6] = arg1;
        func_8005F9F4(temp_s0, 1859);
        if (arg2 != 0) {
            sp28[2] = func_800648A0(arg1);
            func_8005FDB0(temp_s0, sp27, 0);
        }
    } else {
        sp2C[6] = 0;
        if ((!arg1) && (!arg1)) { } // FAKE: redundant empty condition.
        func_8005F9CC(temp_s0, 1859);
        if (arg2 != 0) {
            func_8005FDB0(temp_s0, sp27 & 0xFF, 0xFF);
        }
    }
}

void func_81B005EC(u8 arg0, u8 arg1, s32 arg2) {
    u8 *sp2C;
    u8 *sp28;
    u8 sp27;
    s32 temp_s0;

    temp_s0 = arg0;
    sp2C = func_8005FA1C(temp_s0);
    sp28 = func_8005FD24(temp_s0);
    if (func_8005D92C(temp_s0) == 7) {
        sp27 = 4;
    } else {
        sp27 = 5;
    }
    if (((s32) arg1 >= 26) && ((s32) arg1 < 29)) {
        sp2C[7] = arg1;
        func_8005F9F4(temp_s0, 1860);
        if (arg2 != 0) {
            sp28[3] = func_800648A0(arg1);
            func_8005FDB0(temp_s0, sp27, 0);
        }
    } else {
        sp2C[7] = 0;
        if ((!arg1) && (!arg1)) { } // FAKE: redundant empty condition.
        func_8005F9CC(temp_s0, 1860);
        if (arg2 != 0) {
            func_8005FDB0(temp_s0, sp27 & 0xFF, 0xFF);
        }
    }
}

s32 func_81B006EC(u8 arg0) {
    switch (arg0) {
        case 0x16: return 1;
        case 0x17: return 3;
        default: return 0;
    }
}

s32 func_81B00728(u8 arg0) {
    switch (arg0) {
        case 0x33: return 3;
        case 0x34: return 5;
        default: return 0;
    }
}

s32 func_81B00764(u8 arg0) {
    switch (arg0) {
    case 0x1B:
        return 3;
    default:
        return 1;
    }
}

// Complete byte views of the 16-byte GB map-object and 40-byte actor records.
typedef struct Fragment87MapObjectTemplate {
    u8 bytes[16];
} Fragment87MapObjectTemplate;

typedef struct Fragment87ActorTemplate {
    u8 bytes[40];
} Fragment87ActorTemplate;
extern Fragment87MapObjectTemplate D_81B00FB0, D_81B00FC0, D_81B00FD0, D_81B00FE0;
extern Fragment87ActorTemplate D_81B00FF0, D_81B01018, D_81B01040, D_81B01068;
extern u8 *func_8005FF0C(s32, u8);
extern void _bzero(void *, s32);
extern void func_800649E0(void);
extern void func_80064A10(u8, u8);
extern void func_80064AC8(void);
extern void func_80064B84(u8);
extern u8 func_80064A7C(u8);
extern u8 * func_8005FE58(s32, u8);
extern s32 func_81B006EC(u8 arg0);
extern s32 func_81B00728(u8 arg0);
extern s32 func_81B00764(u8 arg0);
void RoomDecor_RebuildObjects_fragment87(u8 slot) {
    u8 *decorations;
    u8 *sprites;
    u8 is_crystal; // Byte truth tests below preserve IDO's byte-valued flag handling.
    u8 next_object;
    u8 map_slot;
    s32 save_index;
    u8 *actors;
    u8 *map_objects;

    save_index = slot;
    decorations = func_8005FA1C(save_index);
    sprites = func_8005FD24(save_index);
    is_crystal = func_8005D92C(save_index) == 7;
    next_object = 1;
    if (is_crystal) {
        map_slot = 1;
    } else {
        map_slot = 2;
    }
    actors = func_8005FE58(save_index, 1);
    map_objects = func_8005FF0C(save_index, map_slot);
    _bzero(actors, 160);
    func_800649E0();
    func_80064A10(1, 1);
    func_80064A10(240, sprites[0]);
    func_80064A10(241, sprites[1]);
    func_80064A10(242, sprites[2]);
    func_80064A10(243, sprites[3]);
    if (is_crystal) {
        func_80064AC8();
    }
    func_80064B84(is_crystal);
    *(Fragment87MapObjectTemplate *)map_objects = D_81B00FB0;
    if (is_crystal) {
        map_objects[10] += 120;
        map_objects[11] += 15;
    }
    if (decorations[4] != 0) {
        *(Fragment87ActorTemplate *)actors = D_81B00FF0;
        actors[1] = map_slot;
        actors[2] = func_80064A7C(240);
        actors[6] = (actors[6] & 0xF8) + func_81B006EC(decorations[4]);
        map_objects[0] = next_object++;
        actors += 40;
    }
    map_slot++;
    map_objects += 16;
    *(Fragment87MapObjectTemplate *)map_objects = D_81B00FC0;
    if (is_crystal) {
        map_objects[10] += 120;
        map_objects[11] += 15;
    }
    if (decorations[5] != 0) {
        *(Fragment87ActorTemplate *)actors = D_81B01018;
        actors[1] = map_slot;
        actors[2] = func_80064A7C(241);
        actors[6] = (actors[6] & 0xF8) + func_81B00728(decorations[5]);
        map_objects[0] = next_object++;
        actors += 40;
    }
    map_slot++;
    map_objects += 16;
    *(Fragment87MapObjectTemplate *)map_objects = D_81B00FD0;
    if (is_crystal) {
        map_objects[10] += 120;
        map_objects[11] += 15;
    }
    if (decorations[6] != 0) {
        *(Fragment87ActorTemplate *)actors = D_81B01040;
        actors[1] = map_slot;
        actors[2] = func_80064A7C(242);
        actors[6] = (actors[6] & 0xF8) + func_81B00728(decorations[6]);
        map_objects[0] = next_object++;
        actors += 40;
    }
    map_slot++;
    map_objects += 16;
    *(Fragment87MapObjectTemplate *)map_objects = D_81B00FE0;
    if (is_crystal) {
        map_objects[10] += 120;
        map_objects[11] += 15;
    }
    if (decorations[7] != 0) {
        *(Fragment87ActorTemplate *)actors = D_81B01068;
        actors[1] = map_slot;
        actors[2] = func_80064A7C(243);
        actors[6] = (actors[6] & 0xF8) + func_81B00764(decorations[7]);
        map_objects[0] = next_object++;
        actors += 40;
    }
}

extern u8 func_8005FAB4(s32);
extern u8 func_8005FB40(s32);
extern void func_8005FBCC(s32, u8, u8);
extern u8 func_8005FFB4(s32, u8);
extern u8 D_81B01090[];
extern void RoomDecor_SetCarpet_fragment87(u8 slot, u8 decoration, s32 update_map);
extern void RoomDecor_SetPlant_fragment87(u8 slot, u8 decoration, s32 update_map);
extern void RoomDecor_SetPoster_fragment87(u8 slot, u8 decoration, s32 update_map);
extern void func_81B002EC(u8 arg0, u8 arg1, s32 arg2);
extern void func_81B003EC(u8 arg0, u8 arg1, s32 arg2);
extern void func_81B004EC(u8 arg0, u8 arg1, s32 arg2);
extern void func_81B005EC(u8 arg0, u8 arg1, s32 arg2);
extern void RoomDecor_RebuildObjects_fragment87(u8);
// Restore the saved 30-block room view and player object, then reapply all decorations.
void RoomDecor_RestoreSavedView_fragment87(u8 slot) {
    s32 i;
    u8 saved_x;
    u8 saved_y;
    u8 *player_object;
    s32 save_index;

    save_index = slot;
    saved_x = func_8005FAB4(save_index);
    saved_y = func_8005FB40(save_index);
    player_object = func_8005FE58(save_index, 0);
    if (saved_x != 2 || saved_y != 2) {
        func_8005FBCC(save_index, 2, 2);
        for (i = 0; i < 30; i++) {
            func_8005FC7C(save_index, i, D_81B01090[i]);
        }
        player_object[16] = 6;
        player_object[17] = 6;
        player_object[18] = 6;
        player_object[19] = 6;
        RoomDecor_SetBed_fragment87(slot, func_8005FFB4(save_index, 0), 1);
        RoomDecor_SetCarpet_fragment87(slot, func_8005FFB4(save_index, 1), 1);
        RoomDecor_SetPlant_fragment87(slot, func_8005FFB4(save_index, 2), 1);
        RoomDecor_SetPoster_fragment87(slot, func_8005FFB4(save_index, 3), 1);
        func_81B002EC(slot, func_8005FFB4(save_index, 4), 1);
        func_81B003EC(slot, func_8005FFB4(save_index, 5), 1);
        func_81B004EC(slot, func_8005FFB4(save_index, 6), 1);
        func_81B005EC(slot, func_8005FFB4(save_index, 7), 1);
        RoomDecor_RebuildObjects_fragment87(slot);
    }
}

extern s32 func_80059AE0(s32);
extern void RoomDecor_RestoreSavedView_fragment87(u8 slot);
// Dispatch categories 0..7 to the saved room-decoration setters.
void RoomDecor_SetByCategory_fragment87(u8 slot, u8 category, u8 decoration) {
    s32 update_map;

    update_map = func_80059AE0(slot);
    if (update_map != 0) {
        RoomDecor_RestoreSavedView_fragment87(slot);
    }
    switch (category) {
    case 0:
        RoomDecor_SetBed_fragment87(slot, decoration, update_map);
        break;
    case 1:
        RoomDecor_SetCarpet_fragment87(slot, decoration, update_map);
        break;
    case 2:
        RoomDecor_SetPlant_fragment87(slot, decoration, update_map);
        break;
    case 3:
        RoomDecor_SetPoster_fragment87(slot, decoration, update_map);
        break;
    case 4:
        func_81B002EC(slot, decoration, update_map);
        break;
    case 5:
        func_81B003EC(slot, decoration, update_map);
        break;
    case 6:
        func_81B004EC(slot, decoration, update_map);
        break;
    case 7:
        func_81B005EC(slot, decoration, update_map);
        break;
    }
}


void func_81B00F78(u8 arg0) {
    if (func_80059AE0(arg0) != 0) {
        RoomDecor_RebuildObjects_fragment87(arg0);
    }
}
#endif
