#include "global.h"

extern void* func_80069F20(s32 preserveState, s32 unused1, s32 unused2);

/* Battle scene bookkeeping record.  The assembly helpers below access only
 * these fields; keeping the intervening bytes opaque preserves the original
 * ABI without guessing at the rest of the structure. */
typedef struct BattleSceneRecord {
    u16 field00;
    u16 field02;
    u8 padding04[2];
    s16 field06;
    u8 padding08[8];
    s16 field10;
    s16 field12;
    s16 field14;
    s16 field16;
    u16 field18;
    u8 field1A;
    u8 field1B;
    u32 field1C;
} BattleSceneRecord;

#define D_8009DF70 (*(BattleSceneRecord **)0x8009DF70)
#define D_8009DF74 (*(u16 *)0x8009DF74)

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_80069E80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_80069F20.s")

void* BattleScene_ResetParticipantModelFlags(s32 preserveState) {
    return func_80069F20(preserveState, 0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A160.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A180.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A1FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A278.s")

void func_8006A2EC(void) {
    D_8009DF70 = NULL;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A2F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A328.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A35C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A388.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A3B8.s")

u16 func_8006A3E0(void) {
    if (D_8009DF70 == NULL) {
        return 0xFFFF;
    }
    return D_8009DF70->field00;
}

s32 func_8006A400(u16 value) {
    if (D_8009DF70 == NULL) {
        return 0;
    }
    D_8009DF70->field02 = value;
    return 1;
}

s32 func_8006A424(void) {
    if (D_8009DF70 == NULL) {
        return 0;
    }
    return D_8009DF70->field02;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A444.s")

s32 func_8006A48C(void) {
    if (D_8009DF70 == NULL) {
        return -1;
    }
    return D_8009DF70->field06;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A4AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A51C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A5AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A73C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AB68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AB8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006ABD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AC28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AC4C.s")

s32 func_8006AC70(void) {
    if (D_8009DF70 == NULL) {
        return -1;
    }
    return D_8009DF70->field12;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AC90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006ACCC.s")

s32 func_8006ACF0(void) {
    if (D_8009DF70 == NULL) {
        return 0;
    }
    return D_8009DF70->field16;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AD10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AE90.s")

s32 func_8006AEB4(void) {
    if (D_8009DF70 == NULL) {
        return -1;
    }
    return D_8009DF70->field14;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AED4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AF28.s")

u32 func_8006AF84(void) {
    return D_8009DF70->field1C;
}

s32 func_8006AF94(void) {
    if (D_8009DF70 == NULL) {
        return -1;
    }
    return D_8009DF70->field10;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AFB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AFE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B07C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B0B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B428.s")

s32 func_8006B790(u8 value) {
    if (D_8009DF70 == NULL) {
        return 0;
    }
    D_8009DF70->field1A = value;
    return 1;
}

s32 func_8006B7B4(u8 value) {
    if (D_8009DF70 == NULL) {
        return 0;
    }
    D_8009DF70->field1B = value;
    return 1;
}

s32 func_8006B7D8(u16 value) {
    if (D_8009DF70 == NULL) {
        return 0;
    }
    D_8009DF70->field18 = value;
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B7FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B854.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B928.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006BA74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006BAC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006BF78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006C58C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006C5AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006C644.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006C664.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006C714.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006C9C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006C9F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CA34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CA54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CAC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CAE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CB80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CBA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CBB8.s")

void func_8006CBFC(void) {
    D_8009DF74 = 1;
}

void func_8006CC0C(void) {
    D_8009DF74 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CC18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CDA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CEE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CF70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006D068.s")
#endif
