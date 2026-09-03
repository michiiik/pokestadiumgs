#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/67F00/func_80067300.s")

struct Func800675A0Source;
typedef struct { s32 words[24]; } Func80067454Copy;
void func_80067454(struct Func800675A0Source *arg0, void *arg1) {
    Func80067454Copy *dst;
    Func80067454Copy *src;
    s32 i;
    dst = (Func80067454Copy *)arg0;
    src = *(Func80067454Copy **)((u8 *)arg1 + 0x24);
    for (i = 0; i < 6; i++) {
        ((Func80067454Copy *)arg0)[i] = ((Func80067454Copy *)src)[i];
    }
    ((u8 *)arg0)[0x240] = 0;
}

typedef struct Func800675A0Record {
    s32 words[24];
} Func800675A0Record;

typedef struct Func800675A0Source {
    Func800675A0Record records[6];
    u8 pad240[4];
    s8 index;
    s8 value245;
    u8 value246;
} Func800675A0Source;

typedef struct Func800675A0Dest {
    u16 value0;
    s16 value2;
    Func800675A0Record record;
} Func800675A0Dest;

void func_800675A0(Func800675A0Dest *arg0, Func800675A0Source *arg1) {
    arg0->value0 = arg1->value246;
    arg0->value2 = arg1->value245;
    arg0->record = arg1->records[arg1->index];
}

extern u8 D_81600000[];
extern u8 D_81800000[];
extern u8 D_81A00000[];
extern u8 D_82F00000[];
extern u8 D_83300000[];
extern u8 D_87F00000[];
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment3_ROM_START[];
extern u8 fragment4_ROM_START[];
extern u8 fragment5_ROM_START[];
extern u8 fragment8_ROM_START[];
extern u8 fragment9_ROM_START[];
extern u8 fragment57_ROM_START[];
extern u8 fragment58_ROM_START[];
extern u8 fragment64_ROM_START[];
extern u8 fragment65_ROM_START[];
void *main_pool_alloc(s32, s32);
void main_pool_push_state(s32);
void main_pool_pop_state(s32);
void func_800354B4(s32, s32, s32);
void func_80067454(Func800675A0Source *, void *);
void Fragment_Load(s32, void *, void *);
s32 Fragment_LoadAndCall(s32, void *, void *, s32, void *);
void func_800675F8(void *arg0) {
    Func800675A0Source *sp2C;
    Func800675A0Dest *sp28;
    s32 sp24;
    s8 temp_v1;

    sp24 = 0;
    main_pool_push_state(0x777A7063);
    sp2C = main_pool_alloc(0x248, 0);
    sp28 = main_pool_alloc(0x64, 0);
    func_800354B4(0xA, 0, 0);
    main_pool_push_state(0x77617A61);
    func_80067454(sp2C, arg0);
    Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10,
        fragment11_ROM_START, fragment12_ROM_START);
    Fragment_Load((((u32)D_81800000 & 0x0FF00000) >> 20) - 0x10,
        fragment4_ROM_START, fragment5_ROM_START);
    Fragment_LoadAndCall((((u32)D_82F00000 & 0x0FF00000) >> 20) - 0x10,
        fragment8_ROM_START, fragment9_ROM_START, 0, sp2C);
    temp_v1 = sp2C->index;
    if ((temp_v1 >= 0) && (temp_v1 < 6)) {
        sp24 = 1;
        func_800675A0(sp28, sp2C);
    }
    main_pool_pop_state(0x77617A61);
    if (sp24 != 0) {
        func_800354B4(0xC, 0, 0);
        main_pool_push_state(0x77617A61);
        Fragment_Load((((u32)D_81A00000 & 0x0FF00000) >> 20) - 0x10,
            fragment3_ROM_START, fragment4_ROM_START);
        Fragment_Load((((u32)D_87F00000 & 0x0FF00000) >> 20) - 0x10,
            fragment64_ROM_START, fragment65_ROM_START);
        Fragment_LoadAndCall((((u32)D_83300000 & 0x0FF00000) >> 20) - 0x10,
            fragment57_ROM_START, fragment58_ROM_START, 0, sp28);
        main_pool_pop_state(0x77617A61);
    }
    main_pool_pop_state(0x777A7063);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/67F00/func_80067800.s")

s32 func_80067800(s32);
s32 func_800678CC(s32 arg0) {
    s32 result;
    s32 i;

    result = 0;
    i = 1;
loop:
    if (func_80067800(i) == arg0) {
        result = i;
    } else {
        i += 1;
        if (i != 0x15) {
            goto loop;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/67F00/func_80067930.s")

void func_80067930(s32, s32 *, s32 *);
void func_8006AB8C(s32, s32, s32);
void func_80067AE0(s32 arg0, s32 *arg1, s32 *arg2) {
    volatile u8 pad[8];
    s32 sp1C;
    u16 sp1A;

    func_8006A400(func_80067800(arg0));
    sp1A = func_8006A3E0();
    sp1C = func_8006A424();
    func_8006AB8C(sp1A, sp1C, func_8006A388());
    func_80067930(arg0, arg1, arg2);
}

s32 func_80067800();
void func_80067930();
void func_8006AB8C();
s32 func_80067B48(s32 arg0) {
    s32 result;

    switch (func_8006CBB8(arg0)) {
    case 1:
        result = 2;
        break;
    case 2:
        result = 3;
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/67F00/func_80067B8C.s")
#endif
