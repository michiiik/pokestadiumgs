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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_885011EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_88501274.s")

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
