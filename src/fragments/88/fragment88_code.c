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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C00174.s")

u8 func_81C00174(u8, u8, u8);
void func_81C002E4(void *arg0, void *arg1, u8 arg2) {
    (*(s8 *)((u8 *)(arg1) + (0))) = (s8) (func_8003570C() & 1);
    (*(s8 *)((u8 *)(arg1) + (1))) = MysteryGift_RollItemIndex_fragment88((*(u8 *)((u8 *)(arg0) + (0))), (*(u8 *)((u8 *)(arg0) + (1))));
    (*(s8 *)((u8 *)(arg1) + (2))) = func_81C00174((*(u8 *)((u8 *)(arg0) + (1))), (*(u8 *)((u8 *)(arg0) + (0))), arg2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C0034C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C00408.s")

extern u8 D_81C00976[];
extern u8 D_81C008C4[];
extern u16 D_81C008EA[];
extern u8 D_81C0089C[];
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C00584.s")

s32 func_81C0034C(u8, u8);
s16 func_81C00408(u8);
extern void func_81C00584(u8);
void func_81C00740(u8 arg0, s16 *arg1, s16 *arg2, s32 arg3, u8 arg4) {
    if (func_81C0034C(arg0, arg4) != 0) {
        func_81C00584(arg0);
        *arg1 = func_81C00408(arg0);
        *arg2 = MysteryGift_SelectReward_fragment88(arg3);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/88/fragment88_code/func_81C007A4.s")
#endif
