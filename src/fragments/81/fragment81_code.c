#include "global.h"


#ifdef VERSION_US
extern u32 func_8003570C(void);
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84300020.s")

extern u8 D_843023A8[]; u8 func_8430009C(void) { return D_843023A8[(func_8003570C() & 3)]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_843000C8.s")

extern u8 D_843023AC[]; u8 func_843001CC(void) { u32 value = func_8003570C(); u32 remainder = value % 10; return D_843023AC[remainder]; }

void func_84300200(u8 *arg0, u8 arg1) {
    if (arg0 != 0) {
        arg0[(u8)++arg0[0]] = arg1;
    }
}

u8 ByteList_ChooseRandom_fragment81(u8 *list) {
    u32 count;
    f32 fraction;
    u8 index;
    u32 offset;

    fraction = (f32)((f64)func_8003570C() / 4294967296.0);
    //!bug The count is read before the null-pointer guard.
    count = list[0];
    offset = (u32)((f32)count * fraction);
    index = offset + 1;
    if (count == 0 || list == NULL) {
        return 0;
    }
    return list[index];
}

u8 func_84300348(u8 *arg0) {
    return *arg0;
}

void ByteList_RemoveFirst_fragment81(u8 *list, u8 value) {
    s32 i;
    s32 j;

    if (list[0] > 0) {
        for (i = 1; i <= list[0]; i++) {
            if (list[i] == value) {
                list[i] = 0;
                list[0]--;
                break;
            }
        }
        for (j = i; j <= list[0]; j++) {
            list[j] = list[j + 1];
        }
    }
}

s32 func_843003E0(u8 *arg0, u8 arg1) {
    s32 i;

    for (i = 1; i <= arg0[0]; i++) {
        if (arg0[i] == arg1) {
            return (u8)i;
        }
    }
    return 0;
}

extern void func_84300200(u8 *, u8);
extern s32 func_843003E0(u8 *, u8);
void func_8430042C(u8 *arg0, u8 *arg1) {
    s32 i;

    if (func_843003E0(arg0, arg1[1]) != 0) {
        i = 0;
        if (arg1[2] > 0) {
            do {
                func_84300200(arg0, arg1[1]);
                i++;
            } while (i < arg1[2]);
        }
    }
}

typedef struct Fragment81MoveWeight {
    u8 species;
    u8 move;
    u8 copies;
} Fragment81MoveWeight;
extern u8 D_843029DC[];
extern void func_8430042C(u8 *, u8 *);
extern u8 D_84302CA2[];
extern u8 D_84302D06[];
extern u8 D_84302D56[];
extern u8 D_84302DA6[];
extern u8 D_84302DF6[];
extern u8 D_84302E46[];
extern u8 D_84302EA0[];
extern u8 D_84302EFA[];
extern u8 D_84302F54[];
extern u8 D_84302FAE[];
extern u8 D_84302FD2[];
void MoveLists_ApplySpeciesWeights_fragment81(u8 species) {
    Fragment81MoveWeight *record = (Fragment81MoveWeight *)D_843029DC;

    for (; record->species != 0; record++) {
        if (record->species == species) {
            break;
        }
    }
    if (record->move > 0) {
        func_8430042C(D_84302CA2, (u8 *)record);
        func_8430042C(D_84302D06, (u8 *)record);
        func_8430042C(D_84302D56, (u8 *)record);
        func_8430042C(D_84302DA6, (u8 *)record);
        func_8430042C(D_84302DF6, (u8 *)record);
        func_8430042C(D_84302E46, (u8 *)record);
        func_8430042C(D_84302EA0, (u8 *)record);
        func_8430042C(D_84302EFA, (u8 *)record);
        func_8430042C(D_84302F54, (u8 *)record);
        func_8430042C(D_84302FAE, (u8 *)record);
        func_8430042C(D_84302FD2, (u8 *)record);
    }
}

typedef struct Fragment81RulePrefix {
    u8 *types;
    u8 *effects;
} Fragment81RulePrefix;

extern Fragment81RulePrefix *D_84302C9C;
extern u8 func_80062D20(u8);
s32 MoveRules_MatchesEffect_fragment81(u8 move) {
    u8 *effects = D_84302C9C->effects;

    if (effects == NULL) {
        return 0;
    }
    while (*effects != 0xFF) {
        if (*effects == func_80062D20(move)) {
            return 1;
        }
        effects++;
    }
    return 0;
}

extern u8 func_80063838(u8, u8);
s32 func_84300648(u8 arg0) {
    u16 result = 0;
    s32 index;

    for (index = 0; index < 6; index++) {
        result += func_80063838(arg0, index);
    }
    return result;
}

extern u8 func_8006397C(u8);
extern u8 func_800639C0(u8);
u8 HeldItem_IsRedundantForType_fragment81(u8 species, u8 held_item) {
    switch (held_item) {
    case 74: // PSNCUREBERRY: reject for Poison or Steel typing.
        if (func_8006397C(species) == 3 || func_800639C0(species) == 3) {
            return 1;
        }
        if (func_8006397C(species) == 9 || func_800639C0(species) == 9) {
            return 1;
        }
        break;
    case 80: // ICE_BERRY: reject for Fire typing.
        if (func_8006397C(species) == 20 || func_800639C0(species) == 20) {
            return 1;
        }
        break;
    case 79: // BURNT_BERRY: reject for Ice typing.
        if (func_8006397C(species) == 25 || func_800639C0(species) == 25) {
            return 1;
        }
        break;
    }
    return 0;
}

extern u8 HeldItem_IsRedundantForType_fragment81(u8, u8);
extern u8 *D_84302C80;
extern u8 D_84302C88[];
u8 func_843007BC(u8 arg0, u8 arg1) {
    s32 i;
    u8 *p;

    if (arg1 == 0) {
        return 1;
    }
    if (HeldItem_IsRedundantForType_fragment81(arg0, arg1) != 0) {
        return 1;
    }
    p = D_84302C80;
    for (i = 0; i < D_84302C88[0]; i++) {
        if (p[0] != 0 && p[1] == arg1) {
            return 1;
        }
        p += 0x58;
    }
    return 0;
}

extern u8 *D_84302C80;
extern u8 D_84302C88[];
s32 func_84300858(u8 arg0) {
    u8 *p;
    s32 i;

    p = D_84302C80;
    i = 0;
    while (i < D_84302C88[0]) {
        if (*p != 0 && *p == arg0) {
            return 0;
        }
        i++;
        p += 0x58;
    }
    return 1;
}

s32 func_800630F0(s32);
extern s32 D_84302C98;
u8 func_8006397C(u8 arg0);
u8 func_800639C0(u8 arg0);
s32 func_843008B0(u8 arg0) {
    s32 var_v1;

    var_v1 = ((1 << func_800630F0(func_8006397C(arg0) & 0xFF)) & D_84302C98) != 0;
    if (var_v1 == 0) {
        var_v1 = ((1 << func_800630F0(func_800639C0(arg0) & 0xFF)) & D_84302C98) != 0;
    }
    return var_v1;
}

extern u8 * D_84302C80;
extern u8 D_84302C88[];
s32 func_84300928(u8 arg0) {
    u8 *p;
    u8 *q;
    s32 i;
    s32 j;
    p = D_84302C80;
    i = 0;
    while (i < D_84302C88[0]) {
        j = 0;
        q = p;
        while (j < 4) {
            if (q[2] == 0) { break; }
            if (q[2] == arg0) { return 0; }
            j++;
            q++;
        }
        i++;
        p += 0x58;
    }
    return 1;
}

typedef struct {
    u16 value;
    u8 tail[0x92];
} Fragment81Row;
extern u8 D_84302566[];
extern u8 D_84302C88[];
extern u8 D_84303008[];
extern u8 D_84303108[];
extern s32 func_84300648(u8);
extern void func_84300200(u8 *, u8);
void func_843009A4(u8 arg0) {
    s32 result;
    s32 first;
    s32 limit;

    if (arg0 > 0 && arg0 < 0xFC) {
        result = func_84300648(arg0);
        first = ((Fragment81Row *)D_84302566)[D_84302C88[1]].value;
        limit = *(u16 *)(D_84302C88 + 0xE);
        if ((first < limit && result < limit) || (first >= limit && result >= limit)) {
            func_84300200(D_84303008, arg0);
        } else {
            func_84300200(D_84303108, arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84300A54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84300B30.s")

extern u8 ByteList_ChooseRandom_fragment81(u8 *);
extern u16 D_84302CA0;
extern s32 func_800630F0(s32);
extern u8 func_8006397C(u8 arg0);
extern u8 func_800639C0(u8 arg0);
extern u8 func_84300348(u8 *arg0);
extern s32 func_84300648(u8);
extern u8 D_84302C88[];
extern u8 D_84303008[];
extern u8 D_84303108[];
u8 func_84300BE8(void) {
    u8 result;
    result = 0;
    if (func_84300348(D_84303008) > 0) result = ByteList_ChooseRandom_fragment81(D_84303008);
    else if (func_84300348(D_84303108) > 0) result = ByteList_ChooseRandom_fragment81(D_84303108);
    if (result != 0) {
        D_84302CA0 = func_84300648(result);
        *(u32 *)(D_84302C88 + 0x10) |= 1 << func_800630F0(func_8006397C(result) & 0xFF);
        *(u32 *)(D_84302C88 + 0x10) |= 1 << func_800630F0(func_800639C0(result) & 0xFF);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84300CC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84301094.s")

extern void ByteList_RemoveFirst_fragment81(u8 *, u8);
extern void MoveLists_ApplySpeciesWeights_fragment81(u8);
extern u8 D_84302CA2[];
extern u8 D_84302FAE[];
extern u8 D_84302FD2[];
extern u8 ByteList_ChooseRandom_fragment81(u8 *);
extern u8 func_84300348(u8 *arg0);
extern s32 func_84300928(u8 arg0);
u8 func_843013A4(u8 *arg0) {
    u8 result;

    result = 0;
    if (func_84300348(D_84302CA2) > 0) {
        result = ByteList_ChooseRandom_fragment81(D_84302CA2);
        ByteList_RemoveFirst_fragment81(D_84302CA2, result);
    } else if (func_84300348(D_84302FAE) > 0) {
        result = ByteList_ChooseRandom_fragment81(D_84302FAE);
        if (func_84300928(result) == 0) {
            result = ByteList_ChooseRandom_fragment81(D_84302FAE);
        }
        ByteList_RemoveFirst_fragment81(D_84302FAE, result);
    } else if (func_84300348(D_84302FD2) > 0) {
        result = ByteList_ChooseRandom_fragment81(D_84302FD2);
        ByteList_RemoveFirst_fragment81(D_84302FD2, result);
    }
    MoveLists_ApplySpeciesWeights_fragment81(result);
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84301490.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_843016CC.s")

extern s32 D_84302C8C;
extern s32 func_8006443C(u8, u8, u8);
extern s32 func_80064404(u8, u8, u8);
s32 func_84301838(u8 arg0, u8 arg1, u8 arg2) {
    if (D_84302C8C != 0) {
        return func_8006443C(arg0, arg1, arg2);
    } else {
        return func_80064404(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_8430188C.s")

void Pokemon_ShuffleMoves_fragment81(u8 *mon) {
    u8 count = 0;
    s32 i;
    u8 index;
    u8 temp;

    //!bug The move byte is read before the bound, including mon[6] at count 4.
    while ((mon + 2)[count] != 0 && count < 4) {
        count++;
    }
    if (count >= 2) {
        for (i = 0; i < 3; i++) {
            index = func_8003570C() % count;
            temp = (mon + 2)[index];
            (mon + 2)[index] = mon[2];
            mon[2] = temp;
        }
    }
}

extern void func_8430188C(u8);
extern u8 func_84300CC0(void);
extern u8 func_84301094(u8 *);
extern u8 func_843013A4(u8 *);
extern u8 func_84301490(u8 *);
void func_84301BA4(u8 *arg0) {
    u8 value;

    value = arg0[0];
    switch (value) {
    case 0x84:
        arg0[2] = 0x90;
        arg0[3] = 0;
        arg0[4] = 0;
        arg0[5] = 0;
        return;
    case 0xCA:
        arg0[2] = 0x44;
        arg0[3] = 0xF3;
        arg0[4] = 0xDB;
        arg0[5] = 0xC2;
        return;
    default:
        func_8430188C(value);
        arg0[2] = func_84300CC0();
        arg0[3] = func_84301094(arg0);
        arg0[4] = func_843013A4(arg0);
        arg0[5] = func_84301490(arg0);
        return;
    }
}

extern u8 func_80062E10(u8);
void func_84301C58(u8 *arg0) {
    s32 i;
    u8 *p;
    u8 value;
    u8 result;

    p = arg0;
    i = 0;
    do {
        value = p[2];
        if (value == 0) {
            return;
        }
        result = func_80062E10(value);
        i++;
        p++;
        p[0x17] = result;
    } while (i != 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84301CB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84301DEC.s")

extern s32 func_8006A388(void);
extern s32 func_8006A3E0(void);
s32 func_843020F0(void) {
    s32 mode;

    if (func_8006A388() != 0) {
        return 1;
    }
    mode = func_8006A3E0() & 0xFF00;
    if ((mode == 0x100) || (mode == 0x200)) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/81/fragment81_code/func_84302148.s")
#endif
