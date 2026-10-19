#include "global.h"


#ifdef VERSION_US
u16 fragment88_main(u8 arg0) {
    u16 result;
    if (arg0 < 0x29) {
        result = arg0 + 0x2A4;
    } else {
        result = arg0 + 0x2A7;
    }
    return result;
}

extern u32 func_8003570C(void);
// D_81C0089C maps these weighted indices to Mystery Gift item IDs.
u8 MysteryGift_RollItemIndex_fragment88(u8 first_bits, u8 second_bits) {
    u8 index;
    u8 result;
    s32 bit_set;

    if ((u8)func_8003570C() < 25U) {
        if ((u8)func_8003570C() < 50U) {
            if ((u8)func_8003570C() < 50U) {
                if (first_bits & 0x80) {
                    result = 33;
                } else {
                    result = 32;
                }
            } else {
                result = ((first_bits >> 4) & 7) + 24;
            }
        } else {
            index = func_8003570C();
            index &= 3;
            bit_set = (first_bits & (1 << index)) ? 1 : 0;
            result = index * 2 + bit_set + 16;
        }
    } else {
        index = func_8003570C();
        index &= 7;
        bit_set = (second_bits & (1 << index)) ? 1 : 0;
        result = index * 2 + bit_set;
    }
    return result;
}

// D_81C008C4 maps these weighted indices to decoration rewards.
u8 MysteryGift_RollDecorationIndex_fragment88(u8 first_bits, u8 second_bits, u8 rare_choice) {
    u8 index;
    u8 result;
    s32 bit_set;

    if ((u8)func_8003570C() < 36U) {
        if ((u8)func_8003570C() < 72U) {
            if ((u8)func_8003570C() < 72U) {
                result = func_8003570C() % 256;
                if (result < 77) {
                    if (rare_choice) {
                        result = 34;
                    } else {
                        result = 36;
                    }
                } else if (result < 154) {
                    result = 36;
                } else if (first_bits & 0x80) {
                    result = 33;
                } else {
                    result = 32;
                }
            } else {
                result = ((first_bits >> 4) & 7) + 24;
            }
        } else {
            index = func_8003570C();
            index &= 3;
            bit_set = (first_bits & (1 << index)) ? 1 : 0;
            result = index * 2 + bit_set + 16;
        }
    } else {
        index = func_8003570C();
        index &= 7;
        bit_set = (second_bits & (1 << index)) ? 1 : 0;
        result = index * 2 + bit_set;
    }
    return result;
}

void func_81C002E4(void *arg0, void *arg1, u8 arg2) {
    (*(s8 *)((u8 *)(arg1) + (0))) = (s8) (func_8003570C() & 1);
    (*(s8 *)((u8 *)(arg1) + (1))) = MysteryGift_RollItemIndex_fragment88((*(u8 *)((u8 *)(arg0) + (0))), (*(u8 *)((u8 *)(arg0) + (1))));
    (*(s8 *)((u8 *)(arg1) + (2))) = MysteryGift_RollDecorationIndex_fragment88((*(u8 *)((u8 *)(arg0) + (1))), (*(u8 *)((u8 *)(arg0) + (0))), arg2);
}

extern void func_80035700(u32);
extern void func_8005D9E0(s32, void *);
extern void func_80060A84(u8 *, s32);
extern u8 func_8005E03C(s32);
extern void func_8005E0BC(s32, u8, u16);
extern void func_8005E07C(s32, u8);
extern u8 D_81C00972[];
extern u8 D_81C00976[];
// Record this save's ID while under the five-entry limit, then roll both selections.
s32 MysteryGift_TryPrepareSelections_fragment88(u8 slot, u8 allow_special) {
    u8 count;
    s32 save_index;
    s32 metadata[4];
    u8 id_bytes[2];
    s32 result;

    result = 0;
    func_80035700(osGetCount());
    save_index = slot;
    func_8005D9E0(save_index, metadata);
    func_80060A84(id_bytes, *(u16 *)metadata);
    count = func_8005E03C(save_index);
    if (count < 5) {
        func_8005E0BC(save_index, count, *(u16 *)metadata);
        count++;
        func_8005E07C(save_index, count);
        func_81C002E4(id_bytes, D_81C00972, allow_special);
        func_81C002E4(id_bytes, D_81C00976, allow_special);
        result = 1;
    }
    return result;
}

extern s32 func_8005F790(s32, u8);
extern void func_8005F7B8(s32, u8);
extern void func_8005F9CC(s32, u16);
extern void func_8005DFD4(s32, u8);
extern u8 D_81C0089C[];
extern u8 D_81C008C4[];
extern u16 D_81C008EA[];
// Updates the saved gift and decoration flags for D_81C00972's selection.
//@src/585D0.c
u16 MysteryGift_ReceiveReward_fragment88(u8 slot) {
    u8 decoration;
    u16 result;

    result = 0;
    if (D_81C00972[0]) {
        if (D_81C00972[2] < 37) {
            decoration = D_81C008C4[D_81C00972[2]];
            if (func_8005F790(slot, decoration) == 0) {
                result = D_81C008EA[decoration];
                func_8005F7B8(slot, decoration);
                func_8005F9CC(slot, fragment88_main(decoration));
            }
        }
    }
    if (result == 0) {
        if (D_81C00972[1] < 37) {
            result = D_81C0089C[D_81C00972[1]];
            func_8005DFD4(slot, result);
        }
    }
    if (result == 0) {
        result = 173;
    }
    return result;
}

// Prefer an unowned decoration (256 + decoration ID), then an item, then Berry.
u16 MysteryGift_SelectReward_fragment88(s32 decoration_flags_addr) {
    u16 result;
    u8 index;

    result = 0;
    if (D_81C00976[0]) {
        if (D_81C00976[2] < 37) {
            index = D_81C008EA[D_81C008C4[D_81C00976[2]]] - 256;
            if (*(index + (u8 *)decoration_flags_addr) == 0) {
                result = index + 256;
            }
        }
    }
    if (result == 0) {
        if (D_81C00976[1] < 37) {
            result = D_81C0089C[D_81C00976[1]];
        }
    }
    if (result == 0) {
        result = 173;
    }
    return result;
}

extern void _bzero(void *, s32);
extern void *func_8004C874(s32, s32);
extern u8 *func_80060EC8(void *, void *);
extern u8 func_8005D92C(s32);
extern void func_8005E1F0(u8, void *);
typedef struct Fragment88GiftPokemon {
    u8 level;
    u8 species;
    u8 moves[4];
} Fragment88GiftPokemon;
typedef struct Fragment88GiftTeam {
    u8 name[11];
    u8 version;
    Fragment88GiftPokemon pokemon[6];
    u8 marker;
    u8 unk_31;
} Fragment88GiftTeam;
extern Fragment88GiftPokemon D_81C00830[3][6];
extern Fragment88GiftTeam D_81C00940;
// Fill and save a six-Pokemon Mystery Gift team from one of three ROM templates.
void MysteryGift_BuildTeam_fragment88(u8 slot) {
    u8 template_index;
    s32 i;

    _bzero(&D_81C00940, sizeof(D_81C00940));
    func_80060EC8(&D_81C00940, func_8004C874(61, 62));
    switch (func_8005D92C(slot)) {
    case 5:
    case 7:
        D_81C00940.version = 1;
        break;
    case 6:
        D_81C00940.version = 2;
        break;
    }
    template_index = func_8003570C() % 3;
    for (i = 0; i < 6; i++) {
        D_81C00940.pokemon[i] = D_81C00830[template_index][i];
    }
    D_81C00940.marker = 0xFF;
    func_8005E1F0(slot, &D_81C00940);
}

void func_81C00740(u8 arg0, s16 *arg1, s16 *arg2, s32 arg3, u8 arg4) {
    if (MysteryGift_TryPrepareSelections_fragment88(arg0, arg4) != 0) {
        MysteryGift_BuildTeam_fragment88(arg0);
        *arg1 = MysteryGift_ReceiveReward_fragment88(arg0);
        *arg2 = MysteryGift_SelectReward_fragment88(arg3);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C007A4.s")
#endif
