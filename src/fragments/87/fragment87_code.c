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

extern void func_8005F9CC(s32, s32);
extern void func_8005F9F4(s32, s32);
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
        if ((!arg1) && (!arg1)) { }
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
        if ((!arg1) && (!arg1)) { }
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
        if ((!arg1) && (!arg1)) { }
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
        if ((!arg1) && (!arg1)) { }
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B00788.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B00CA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/87/fragment87_code/func_81B00E58.s")

s32 func_80059AE0(u8);
extern void func_81B00788(u8);

void func_81B00F78(u8 arg0) {
    if (func_80059AE0(arg0) != 0) {
        func_81B00788(arg0);
    }
}
#endif
