#include "global.h"


#ifdef VERSION_US
extern void Util_Free(s32);
extern void func_8821CE40(s32);
extern void main_pool_pop_state(s32);
extern s32 D_88234560;
extern s32 D_88234564;

void func_8820C000(void) {
    Util_Free(D_88234564);
    main_pool_pop_state(0x41525249);
    func_8821CE40(3);
    D_88234560 = 5;
}

extern void* D_88234710;
typedef struct {
    s16 flags;
    u16 reserved;
    s32 state;
    s16 position;
    s16 start;
    u16 count;
    u8 visible;
    u8 stride;
    s16 scroll;
    s16 base;
    u8 tail[24];
} F31SelectionScroll;
typedef struct {
    u8 slot;
    u8 reserved[11];
    s32 list[2];
    F31SelectionScroll records[2];
    u8 reservedTail[0x44];
    s32 enabled[2];
    s32 position;
    u8* selectedRecord;
    s16 lower;
    s16 upper;
} F31SelectionState;
extern u8* func_88A00710(s32, s16);
u8* func_8820C040(s32 mode, u8 slot) {
    s16 position;
    u32 index = slot;

    /* Only modes 0 through 3 define a selection position. */
    switch (mode) {
    case 0:
        position = *(s16*)((u8*)D_88234710 + index * 44 + 30);
        break;
    case 1:
        position = *(s16*)((u8*)D_88234710 + index * 44 + 28);
        break;
    case 2:
        position = 0;
        break;
    case 3:
        position = *(s16*)((u8*)D_88234710 + 0xB8);
        break;
    }
    return func_88A00710(*(s32*)((u8*)D_88234710 + index * 4 + 12), position);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C114.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C258.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820C65C.s")

extern u8* D_88A01C64;
extern s32 func_88202158(u8*, s32);
extern u8 func_88A007BC(s32);
extern u8 func_8006378C(u8);
extern s32 func_8800005C(void);
s32 func_8820C798(void) {
    u8* state = D_88234710;
    u8 slot = state[0];
    s32 result = 0;

    if (((s32*)state)[4 - slot] == 2 || ((s32*)state)[4 - slot] == 3) {
        result = func_88202158(func_8820C040(1, slot), 1);
    }
    return result;
}

s32 func_8820C800(u8 slot, u8 type) {
    u8 count = func_88A007BC(*(s32*)((u8*)D_88234710 + slot * 4 + 12));
    u8* record = func_8820C040(2, slot);
    u32 index;

    for (index = 0; index < count; index++, record += 2) {
        if (type == func_8006378C(record[0])) {
            return 1;
        }
    }
    return 0;
}

u8 func_8820C8A0(u8 type, u8 slot) {
    u8 result = 0;
    u8* table;
    u8* record;
    u32 count;
    u32 index;

    if (func_8800005C() == 0 && *(s32*)((u8*)D_88234710 + slot * 4 + 12) == 0 && func_8006378C(type) == 4) {
        table = D_88A01C64;
        count = table[3];
        record = table;
        record += record[7] * 2 + 9;
        for (index = 0; index < count; index++, record += 2) {
            if (type == record[0]) {
                result = record[1];
                break;
            }
        }
    }
    return result;
}

s32 func_8820C94C(void) {
    u32 index;
    s32 result = 0;
    u8* other;

    for (index = 0; index != 2; index++) {
        if (func_8800005C() == 0 && *(s32*)((u8*)D_88234710 + index * 4 + 12) == 0) {
            other = func_8820C040(1, 1 - index);
            if (func_8006378C(other[0]) == 4) {
                if (other[0] != func_8820C040(1, index)[0]) {
                    if (other[1] + func_8820C8A0(other[0], index) >= 100) {
                        result = 1;
                        break;
                    }
                }
            }
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CA50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CAE4.s")

extern void* Util_Malloc(s32);
extern void* D_8800EF54;
extern s32 D_88234718;
extern void func_800226C0(s32);
extern void func_88231AE8(void);
extern void func_88004990(u8, u8);
typedef struct {
    u8* other;
    u8 deltas[2];
    u8 slot;
    u8 counts[2];
    u8 reserved[3];
} F31Transfer;
void func_8820CB74(void) {
    u32 index;
    F31Transfer* transfer = Util_Malloc(12);

    transfer->other = func_8820C040(1, 1 - *(u8*)D_88234710);
    transfer->slot = 1 - *(u8*)D_88234710;
    transfer->counts[transfer->slot] = (transfer->other)[1];
    transfer->counts[1 - transfer->slot] = 0;
    for (index = 0; index != 2; index++) {
        transfer->deltas[index] = *(s16*)((u8*)D_88234710 + index * 44 + 28) - *(s16*)((u8*)D_88234710 + index * 44 + 30);
        *(s32*)(D_88A01C64 + *(s32*)((u8*)D_88234710 + index * 4 + 12) * 4 + 0x104) = 1;
    }
    D_8800EF54 = transfer;
    func_800226C0(0x5D);
    func_800226C0(0x63);
    func_88231AE8();
    if (D_88234718 == 2) {
        D_88234718 = 0;
        func_88004990(**(u8**)((u8*)D_88234710 + 0xBC), 0);
    }
}

extern s32 D_882346F0;
extern s32 func_88A00FD4(u8);
extern void func_8820C65C(u8, s32);
extern void func_8820CAE4(u8, u8);
extern void func_8820CA50(u8, u8);
typedef struct {
    u8 reserved;
    u8 count[4];
    u8 lower[4];
} F31Limits;
void func_8820CCA8(void) {
    s32 playSound = 1;
    s32 guarded;
    u8 currentType;
    u8* other;
    u8 otherType;
    s32 category;

    D_882346F0 = 1;
    *(u8*)D_88234710 ^= 1;
    guarded = func_8800005C() == 0 && ((F31SelectionState*)D_88234710)->list[((F31SelectionState*)D_88234710)->slot] == 0;
    if (guarded) {
        currentType = func_8006378C(func_8820C040(1, *(u8*)D_88234710)[0]);
    }
    func_8820C65C(*(u8*)D_88234710, 1);
    if (guarded) {
        other = func_8820C040(1, 1 - *(u8*)D_88234710);
        otherType = func_8006378C(other[0]);
        category = func_88A00FD4(otherType);
        *(s16*)((u8*)D_88234710 + 0xC0) = ((F31Limits*)D_88A01C64)->lower[category];
        *(s16*)((u8*)D_88234710 + 0xC2) = ((F31Limits*)D_88A01C64)->count[category] + ((F31SelectionState*)D_88234710)->lower;
        if (category == 2) {
            func_8820CAE4(*(u8*)D_88234710, other[0]);
            func_8820CB74();
            playSound = 0;
        } else if (otherType != currentType) {
            func_8820CA50(*(u8*)D_88234710, otherType);
        }
    }
    if (playSound) {
        func_800226C0(0x47);
    }
}

extern u8 D_88234934;
extern void func_88A016F0(s32, u8*, s16);
extern void func_88202AA0(s32, s16);
extern void func_88001C24(void*, u16, u8);
extern void func_88001D0C(void*);
extern void func_88001900(void);
typedef struct {
    u8 type;
    u8 count;
} F31Item;
void func_8820CE2C(void) {
    u32 index;
    u8* other;
    s16 position;
    F31Item pair;

    func_800226C0(0x5E);
    if (D_882346F0 == 1) {
        other = func_8820C040(1, 1 - *(u8*)D_88234710);
        position = ((F31SelectionState*)D_88234710)->records[((F31SelectionState*)D_88234710)->slot].position;
        pair.type = other[0];
        pair.count = D_88234934;
        func_88A016F0(((F31SelectionState*)D_88234710)->list[((F31SelectionState*)D_88234710)->slot], (u8*)&pair,
                     position);
        *(s32*)((u8*)D_88234710 + *(u8*)D_88234710 * 4 + 0xB0) = 0;
    }
    for (index = 0; index != 2; index++) {
        func_88202AA0(*(s32*)((u8*)D_88234710 + index * 4 + 12), *(s16*)((u8*)D_88234710 + index * 44 + 28));
        func_88001C24((u8*)D_88234710 + index * 44 + 20,
                     func_88A007BC(*(s32*)((u8*)D_88234710 + index * 4 + 12)), 8);
        func_88001D0C((u8*)D_88234710 + index * 44 + 20);
    }
    func_88001900();
    D_882346F0 = 0;
    *(u8*)D_88234710 ^= 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820CF8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820E450.s")

s32 func_8820E580(void) {
    u32 otherType;
    u8* current = func_8820C040(1, *(u8*)D_88234710);
    u32 selected;
    s32 result;
    s16 position;
    s32 atEnd;

    selected = *(u8*)D_88234710;
    if (*(s32*)((u8*)D_88234710 + selected * 4 + 0xB0)) {
        otherType = (func_8006378C(func_8820C040(1, 1 - selected)[0]) & 0xFF);
        position = ((F31SelectionState*)D_88234710)->records[((F31SelectionState*)D_88234710)->slot].position;
        atEnd = position + 1 == ((F31SelectionState*)D_88234710)->records[((F31SelectionState*)D_88234710)->slot].count ? 1 : 0;
        if (atEnd) {
            current -= 2;
        }
        if (position >= *(s16*)(((u8*)D_88234710) + 0xC0) && position <= *(s16*)(((u8*)D_88234710) + 0xC2)) {
            result = func_88A00FD4(otherType);
        } else {
            result = func_88A00FD4(func_8006378C(current[0]));
        }
    } else {
        result = func_88A00FD4(func_8006378C(current[0]));
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820E6A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820E9BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820EB14.s")

extern void *Color_SetRGB(void *, u8, u8, u8);
extern void func_880006E0(void *);
extern u8 D_88005FA0[];
void func_8820ECE8(u8 arg0, u8 *arg1) {
    u8 sp1C[4];

    if (arg0 == func_8006378C(*arg1)) {
        func_880006E0(D_88005FA0);
        return;
    }
    func_880006E0(Color_SetRGB(sp1C, 0x96, 0x96, 0x96));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820ED44.s")

extern void func_800496A4(s32, s32);
extern void func_800495F8(s32, s32, s32, void *, s32);
extern u8 D_88233F50[];
extern void *D_8800687C;
extern void *func_88A00938(u8 *);
extern void func_80048E30(void *, s16, s16, void *, s32);
void func_8820F74C(s16 arg0, s16 arg1, u8 *arg2, u8 arg3) {
    if (func_88202158(arg2, 1) == 0) {
        func_800496A4(4, 1);
        func_800495F8((s32)arg0 + 0xD3, (s32)arg1 + 4, 2, D_88233F50, (s32)arg3);
    }
    func_800496A4(8, 2);
    func_80048E30(D_8800687C, arg0, arg1, func_88A00938(arg2), 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820F7EC.s")

extern char D_88233F54[];
extern s32 func_8005CAA4(s32);
extern s32 func_80053230(s32);
extern void func_8004D5B8(s32, s32, s32, const char*, ...);
void func_8820FC78(u8 slot) {
    s32 x;
    u16 limit;

    x = !slot ? 269 : 580;
    switch (*(s32*)((u8*)D_88234710 + slot * 4 + 12)) {
    case 0:
        if (func_8800005C() == 0) {
            return;
        }
        limit = 20;
        break;
    case 1:
        limit = func_8005CAA4(0x22);
        break;
    default:
        limit = func_80053230(0x12);
        break;
    }
    func_8004D5B8(x, 341, 2, D_88233F54,
                 func_88A007BC(*(s32*)((u8*)D_88234710 + slot * 4 + 12)), limit);
}

void func_8820FD58(void) { func_8820FC78(0); func_8820FC78(1); }

extern void func_80049064(s32, s32, s32, s32);
s32 func_8004C874(s32, s16);

void func_8820FD80(void) {
    func_800496A4(4, 2);
    func_80049064(0x140, 0x1A4, 1, func_8004C874(0x21, 0x1F));
    func_800496A4(0x10, 2);
    func_80049064(0x140, 0x183, 1, func_8004C874(0x21, (*(s16 *)((u8 *)(D_88234710) + (8)))));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820FDF8.s")
#endif
