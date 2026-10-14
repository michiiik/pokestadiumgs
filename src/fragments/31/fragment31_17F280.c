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
typedef struct {
    u8 reserved;
    u8 count[4];
    u8 lower[4];
} F31Limits;
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

extern u8 func_88A007BC(s32);
extern s32 func_80001FF0(void);
extern void func_88001C6C(void*, u16, u8, s16, u8, s16, s16, s16, s16, s16, s32);
void func_8820C114(u8 slot, s32 list) {
    s16 flags;

    if (*(s32*)((u8*)D_88234710 + 4)) {
        flags = 12;
    } else {
        flags = 0xF0C;
    }
    ((F31SelectionState*)D_88234710)->list[slot] = list;
    /* Keep the count query and two-call rounding expression inline. */
    func_88001C6C(&((F31SelectionState*)D_88234710)->records[slot],
                 func_88A007BC(((F31SelectionState*)D_88234710)->list[slot]), 8, 125, 27, 14,
                 (s32)(600.0f / func_80001FF0() + (0.0f < (600.0f / func_80001FF0()) ? 0.5f : -0.5f)),
                 43, 43, flags, 70);
}

extern s32 main_pool_push_state(s32);
extern s32 mem_pool_try_init(s32, s32);
extern void* mem_pool_alloc(void*, s32);
extern s32 func_8004C4B0(s32);
extern s32 func_8004C8C0(u16);
extern s32 func_8004C990(s32, s32);
extern s32 D_882345D0;
extern s8 D_88006868;
extern s32 func_800606F4(s32);
extern void func_88A00D0C(void*);
extern s32 D_80087200;
extern void Input_SetRepeatController(s32);
extern s32 D_880068B8;
extern s32 D_880068B4;
extern s32 D_88234714;
extern void func_88205EB0(
    s16, s16, s16, s16, s16, s16, s16, s16, s16, s16,
    s16, s16, s16, s16, s16, s16, s16, s16, s16, s16,
    s16, s16, s16, s16, s16, s16, s16, s16, s16, s16,
    s16, s16, s16, s16, s16, s16, s16, s16, s16, s16,
    s16, s16, s16, s16, s16, s16, s16, s16, s16, s16,
    s16, s16, s16, s16, s16, s16, s16, s16, s16, s16,
    s16, s16, s16, s16, s16, s16, s16, s16, s16, s16,
    s16, s16, s16, s16, s16, s16, u8, u8, void (*)(void));
extern s32 func_8004C54C(s32, s32);
extern u8 D_8800686D;
extern void* func_8004C8A0(void*, s32, s32, s32);
extern void func_88005B60(s32, void (*)(void), void (*)(void), void (*)(void));
extern void D_88000E4C(void);
extern s32 D_882346F0;
extern s32 D_88234718;
void func_8820C258(void) {
    u32 index;
    void* pool;

    main_pool_push_state(0x41525249);
    pool = (void*)(u32)mem_pool_try_init(0x14000, 0);
    D_88234710 = mem_pool_alloc(pool, 0xC8);
    func_8004C4B0(0x21);
    func_8004C4B0(9);
    func_8004C4B0(11);
    func_8004C8C0(28);
    D_882345D0 = func_8004C990(28, 0);
    if (func_800606F4(D_88006868)) {
        *(u16*)((u8*)D_88234710 + 0xC4) = 20;
    } else {
        *(u16*)((u8*)D_88234710 + 0xC4) = 19;
    }
    func_8004C8C0(*(u16*)((u8*)D_88234710 + 0xC4));
    func_88A00D0C(pool);
    *(u8*)D_88234710 = 0;
    *(s32*)((u8*)D_88234710 + 4) = 1;
    *(s16*)((u8*)D_88234710 + 8) = 0;
    *(u8*)((u8*)D_88234710 + 0xAC) = 0;
    func_8820C114(0, 0);
    func_8820C114(1, 1);
    for (index = 0; index != 2; index++) {
        *(s32*)((u8*)D_88234710 + index * 4 + 0xB0) = 0;
    }
    Input_SetRepeatController(D_80087200);
    D_882346F0 = 0;
    D_880068B4 = D_880068B8 = 1;
    D_88234714 = 0;
    D_88234718 = 0;
    func_88205EB0(44, 373, 553, 76, 44, 72, 242, 296, 49, 105,
        229, 255, 355, 72, 242, 296, 360, 105, 229, 255,
        52, 108, 223, 17, 52, 340, 223, 17, 363, 108,
        223, 17, 363, 340, 223, 17, 289, 72, 63, 38,
        52, 125, 223, 26, 363, 125, 223, 26, 251, 79,
        363, 79, 61, 112, 256, 112, 372, 112, 567, 112,
        136, 112, 154, 112, 154, 344, 174, 344, 447, 112,
        465, 112, 465, 344, 485, 344, 5, 34, func_8820C000);
    func_8004C54C(21, (s32)&D_8800686D);
    func_8004C8A0((u8*)D_88234710 + 0x6C, 64, 33, 19);
    func_88005B60(0, D_88000E4C, D_88000E4C, D_88000E4C);
}

extern void func_88001C24(void*, u16, u8);
extern void func_88001D0C(void*);
void func_8820C65C(u8 slot, s32 enabled) {
    F31SelectionScroll* record;

    if (enabled != ((F31SelectionState*)D_88234710)->enabled[slot]) {
        record = &((F31SelectionState*)D_88234710)->records[slot];
        ((F31SelectionState*)D_88234710)->enabled[slot] = enabled;
        if (enabled) {
            if (func_88A007BC(((F31SelectionState*)D_88234710)->list[slot])) {
                func_88001C24(record, (u16)(record->count + 1), 8);
                if (record->position - record->start == 7) {
                    record->start++;
                } else {
                    record->scroll += record->stride;
                }
            }
        } else {
            if (func_88A007BC(((F31SelectionState*)D_88234710)->list[slot])) {
                func_88001C24(record, (u16)(record->count - 1), 8);
                if (record->position - record->start == 7) {
                    record->start--;
                } else {
                    record->scroll -= record->stride;
                }
            }
        }
        func_88001D0C(record);
    }
}

extern u8* D_88A01C64;
extern s32 func_88202158(u8*, s32);
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

extern void func_8800225C(void*, s16, s16);
extern s32 func_88A00FD4(u8);
void func_8820CA50(u8 slot, u8 type) {
    s32 category;
    s16 bound;

    if (func_8800005C() == 0 && ((F31SelectionState*)D_88234710)->list[slot] == 0) {
        category = func_88A00FD4(type);
        bound = ((F31Limits*)D_88A01C64)->lower[category];
        func_8800225C(&((F31SelectionState*)D_88234710)->records[slot], bound, (s16)bound);
    }
}

extern s32 func_88A01018(u8);
void func_8820CAE4(u8 slot, u8 type) {
    s32 value;

    if (func_8800005C() == 0 && ((F31SelectionState*)D_88234710)->list[slot] == 0) {
        value = func_88A01018(type);
        func_8800225C(&((F31SelectionState*)D_88234710)->records[slot], (s16)(value - 4), (s16)value);
    }
}

extern void* Util_Malloc(s32);
extern void* D_8800EF54;
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

extern s16 D_8800EF58;
extern Gfx* D_800D0510;
extern s32 func_8004D1FC(u8*);
extern s32 func_8004D19C(s32, s32, s32, s32, s32);
extern void func_80044270(s16, s16, s16, s16, s16, s16, s16, s16, s32);
void func_8820E6A4(void) {
    s32 category;
    u8* texture;

    if (D_8800EF58 == 0 && func_8800005C() == 0 && ((F31SelectionState*)D_88234710)->list[((F31SelectionState*)D_88234710)->slot] == 0 && func_88A007BC(((F31SelectionState*)D_88234710)->list[((F31SelectionState*)D_88234710)->slot]) != 0) {
        category = func_8820E580();
        texture = (u8*)(u32)func_8004C990(*(u16*)((u8*)D_88234710 + 0xC4), 0);
        func_8004D1FC((u8*)texture);
        gDPPipeSync(D_800D0510++);
        if (category == 0) {
            gDPSetEnvColor(D_800D0510++, 40, 130, 255, 255);
        } else {
            gDPSetEnvColor(D_800D0510++, 255, 255, 255, 255);
        }
        func_80044270(63, 402, *(s16*)texture, *(s16*)(texture + 2), -16, -16, 1024, 1024, 0);
        gDPPipeSync(D_800D0510++);
        if (category == 2) {
            gDPSetEnvColor(D_800D0510++, 240, 130, 10, 255);
        } else {
            gDPSetEnvColor(D_800D0510++, 255, 255, 255, 255);
        }
        func_80044270(89, 402, (s16)(*(u16*)texture), *(s16*)(texture + 2), (*(u16*)texture) * 32 - 16, -16, -1024, 1024, 0);
        gDPPipeSync(D_800D0510++);
        if (category == 3) {
            gDPSetEnvColor(D_800D0510++, 255, 70, 140, 255);
        } else {
            gDPSetEnvColor(D_800D0510++, 255, 255, 255, 255);
        }
        func_8004D19C(70, 392, func_8004C990(*(u16*)((u8*)D_88234710 + 0xC4), 1), 0, 0);
        gDPPipeSync(D_800D0510++);
        if (category == 1) {
            gDPSetEnvColor(D_800D0510++, 100, 255, 100, 255);
        } else {
            gDPSetEnvColor(D_800D0510++, 255, 255, 255, 255);
        }
        func_8004D19C(74, 409, func_8004C990(*(u16*)((u8*)D_88234710 + 0xC4), 2), 0, 0);
    }
}

extern void* Color_SetRGB(void*, u8, u8, u8);
extern void func_880006E0(void*);
extern void func_800496A4(s32, s32);
extern void* func_8004C874(s32, s32);
extern void* D_8800687C;
extern void func_80048E30(void*, s16, s16, void*, s32);
void func_8820E9BC(void) {
    u8 color[4];
    s32 category;

    if (D_8800EF58 == 0 && func_8800005C() == 0 && ((F31SelectionState*)D_88234710)->list[((F31SelectionState*)D_88234710)->slot] == 0 && func_88A007BC(((F31SelectionState*)D_88234710)->list[((F31SelectionState*)D_88234710)->slot]) != 0) {
        category = func_8820E580();
        switch (category) {
        case 0:
            func_880006E0(Color_SetRGB(color, 160, 190, 255));
            break;
        case 1:
            func_880006E0(Color_SetRGB(color, 150, 255, 100));
            break;
        case 2:
            func_880006E0(Color_SetRGB(color, 255, 200, 100));
            break;
        case 3:
            func_880006E0(Color_SetRGB(color, 255, 140, 210));
            break;
        }
        func_800496A4(4, 1);
        func_80048E30(D_8800687C, 111, 402, func_8004C874(0x21, category + 0x20), 1);
    }
}

void func_8820EB14(u8 selected, u8* record) {
    s32 type = func_8006378C(record[0]);

    switch (type) {
    case 1:
        if (selected == 1) {
            gDPSetFillColor(D_800D0510++, 0x09A909A9);
        } else {
            gDPSetFillColor(D_800D0510++, 0x39CF39CF);
        }
        break;
    case 3:
        if (selected == 3) {
            gDPSetFillColor(D_800D0510++, 0x03550355);
        } else {
            gDPSetFillColor(D_800D0510++, 0x02950295);
        }
        break;
    case 4:
        if (selected == 4) {
            gDPSetFillColor(D_800D0510++, 0x8AD18AD1);
        } else {
            gDPSetFillColor(D_800D0510++, 0x5A0D5A0D);
        }
        break;
    case 2:
        if (selected == 2) {
            gDPSetFillColor(D_800D0510++, 0x91579157);
        } else {
            gDPSetFillColor(D_800D0510++, 0x618F618F);
        }
        break;
    }
}

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

extern void func_800495F8(s32, s32, s32, void *, s32);
extern u8 D_88233F50[];
extern void *func_88A00938(u8 *);
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

extern void func_80049064(s32, s32, s32, const char*);

void func_8820FD80(void) {
    func_800496A4(4, 2);
    func_80049064(0x140, 0x1A4, 1, func_8004C874(0x21, 0x1F));
    func_800496A4(0x10, 2);
    func_80049064(0x140, 0x183, 1, func_8004C874(0x21, (*(s16 *)((u8 *)(D_88234710) + (8)))));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_17F280/func_8820FDF8.s")
#endif
