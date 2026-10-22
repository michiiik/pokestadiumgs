#include "global.h"


#ifdef VERSION_US
extern u8 D_8850D6D8;
u8 *func_88500CF0(u8 arg0) {
    typedef struct {
        u8 data[0x58];
    } Item;
    typedef struct {
        Item items[30];
        u8 padA50[0x24];
    } Row;
    typedef struct {
        u8 pad0000[0xC88];
        s8 itemIndex;
        s8 rowIndex;
        u8 pad0C8A[6];
        Row rows[1];
    } State;
    State *state;

    state = (State *)((arg0 * 0xA960) + &D_8850D6D8);
    return (u8 *)&state->rows[state->rowIndex].items[state->itemIndex];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_88500D60.s")

extern u8 *D_8850D6D0;
s8 func_88500E4C(void) {
    typedef struct {
        u8 pad2F[0x2F];
        u8 count;
        s8 index;
        u8 pad31;
    } State;
    State *state;
    s8 index;
    s8 result;

    state = (State *)D_8850D6D0;
    index = state->index;
    if (index >= state->count) {
        result = 0;
    } else {
        result = *((s8 *)state + index + 0x32);
    }
    return result;
}

extern void func_88004990(u8, s32);
extern s32 D_880068B8;
void func_88500E80(void) {
    *(s32 *)(*(u8 **)((u8 *)D_8850D6D0 + 0) + 0x34) = 1;
    *(s32 *)(*(u8 **)((u8 *)D_8850D6D0 + 4) + 0x34) = 1;
    func_88004990(**(u8 **)((u8 *)D_8850D6D0 + 0), 0);
    func_88004990(**(u8 **)((u8 *)D_8850D6D0 + 4), 0);
    D_880068B8 = 1;
}

extern u8 *D_8850D6D0;
void func_88500EF4(void) {
    *(s32 *)(*(u8 **)((u8 *)D_8850D6D0 + 4) + 0x30) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_88500F08.s")

extern void func_8000612C(void);
extern s32 D_88804058;
extern void func_88500E80(void);
void func_885010EC(void) {
    typedef struct {
        s32 words[0x320];
    } CopyRecord;
    typedef struct {
        u8 pad00[0x10];
        u8 index;
        u8 pad11[3];
        u8 *records[1];
    } MainState;
    u8 *state;

    state = (D_8850D6D0[0xA] * 0xA960) + &D_8850D6D8;
    func_8000612C();
    *(s32 *)(*(u8 **)(D_8850D6D0 + 4) + 0x2C) = 1;
    *(s32 *)(D_8850D6D0 + 0x64) = 1;
    if (D_88804058 != 0) {
        state[1] = 1;
        *(CopyRecord *)(state + 8) = *(CopyRecord *)((*(s8 *)(state + 0xC88) * 0xC80) + ((MainState *)D_8850D6D0)->records[((MainState *)D_8850D6D0)->index]);
        func_88500E80();
    } else {
        state[1] = 0;
    }
}

typedef struct unk_func_885011EC {
    u8 unk_00[44];
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
} unk_func_885011EC;

typedef struct unk_D_8850D6D0 {
    void* unk_00;
    unk_func_885011EC* unk_04;
    u8 unk_08;
    u8 unk_09[91];
    s32 unk_64;
} unk_D_8850D6D0;

extern void func_88500F08(void);
extern s32 func_88802DCC(s32 arg0, u8* arg1, void (*arg2)(void), void (*arg3)(void),
                        void (*arg4)(void), void* arg5, u8 arg6, u8 arg7);

void func_885011EC(u8* arg0) {
    func_88802DCC(3, arg0, func_88500EF4, func_885010EC, func_88500F08, NULL, 0, 2);
    ((unk_D_8850D6D0*)D_8850D6D0)->unk_04->unk_2C = 0;
    ((unk_D_8850D6D0*)D_8850D6D0)->unk_04->unk_34 = 1;
    ((unk_D_8850D6D0*)D_8850D6D0)->unk_08 = 2;
    ((unk_D_8850D6D0*)D_8850D6D0)->unk_64 = 0;
}

#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

s32 func_8004C874(M2C_UNK, s16);                    /* extern */
M2C_UNK func_88903C50(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32, s32, u8 *, M2C_UNK *, void (*)()); /* extern */
extern M2C_UNK D_88000E4C;

void func_88501274(s16 arg0) {
    func_88903C50(func_8004C874(0x34, arg0), 0x141, 0x108, 4, 0xFF, 0xAA, 0x8C, 0, 2, M2C_FIELD(D_8850D6D0, s32 *, 4) + 0x2C, D_8850D6D0 + 0x88, &D_88000E4C, func_8000612C);
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_8850130C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_88501380.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_88501570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_88501AE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_88503644.s")

extern s32 D_880068B4;
extern void Util_Free(u8 *);
extern void func_888002DC(void);
extern void main_pool_pop_state(s32);
void func_885037EC(void) {
    D_880068B4 = 1;
    Util_Free(D_8850D6D0);
    func_888002DC();
    main_pool_pop_state(0x50495550);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_88503830.s")
#endif
