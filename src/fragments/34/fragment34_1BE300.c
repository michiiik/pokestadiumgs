#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_88500CF0.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_88500E80.s")

extern u8 *D_8850D6D0;
void func_88500EF4(void) {
    *(s32 *)(*(u8 **)((u8 *)D_8850D6D0 + 4) + 0x30) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_88500F08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/34/fragment34_1BE300/func_885010EC.s")

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
