#include "global.h"


#ifdef VERSION_US
extern s32 func_80063754();
extern s16 func_88A00248(void *, s32 *, u8 **, void *, s32, s8);
extern void _bcopy(void *, void *, s32);
extern void _bzero(void *, s32);
extern s8 D_88006868;
extern s16 D_882345F0;
extern u8 D_882345F8[];
extern u8 D_88234618[];
extern s32 D_88A01C30;
extern u8 *D_88A01C34;
extern u8 (*D_88A01C38)[0x60];
extern u8 D_88A01C40[];

void func_882011E0(void *arg0) {
    u32 i;

    D_882345F0 = func_88A00248(arg0, &D_88A01C30, &D_88A01C34, &D_88A01C38, 3, D_88006868);
    _bcopy(D_88A01C40, D_882345F8, 30);
    _bzero(D_88234618, 6);
    for (i = 0; i < D_88A01C34[0x15]; i++) {
        if (func_80063754(D_88A01C38[i][9]) != 0) {
            D_88234618[i] = 1;
        }
    }
}
s8 func_882012E4(void *arg0) {
    u8 *state = *(u8 **)arg0;
    void **entry = *(void ***)(state + 0x10);
    s32 index = 0;
    u32 count = state[0x15];
    s32 result = -1;
    if (count != 0) {
loop:
        if (*entry == arg0) {
            return index;
        }
        index++;
        entry++;
        if (index < count) {
            goto loop;
        }
    }
    return result;
}

s8 func_88201330(void *arg0) {
    u8 *state = *(u8 **)arg0;
    void **entry = *(void ***)(state + 0xC);
    s32 index = 0;
    u32 count = state[0x11];
    s32 result = -1;
    if (count != 0) {
loop:
        if (*entry == arg0) {
            return index;
        }
        index++;
        entry++;
        if (index < count) {
            goto loop;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_8820137C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201420.s")

extern void func_88201420(s32, s32);
void func_88201608(s32 arg0) {
    func_88201420(arg0, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201628.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_8820172C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_882017F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201A74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201E28.s")

typedef struct {
    u8 pad[0xC];
    void **entries;
    u32 unused;
} EntryRow_88201ED0;
extern s32 D_88A01C30;
void *func_88201ED0(u8 arg0, u8 arg1) {
    void **entries = ((EntryRow_88201ED0 *)D_88A01C30)[arg0].entries;
    return entries[arg1];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201F0C.s")

extern s32 HAL_Strcmp(const s8 *, const s8 *);
extern s8 D_8800686D[];
extern u8 D_882345D4;
extern u16 D_8800686A;
s32 func_88201F7C(void *arg0) {
    s32 result = 1;
    if (D_882345D4 == 0) {
        if (*(u16 *)((u8 *)arg0 + 6) != *(u16 *)&D_8800686A ||
            HAL_Strcmp(D_8800686D, (s8 *)((u8 *)arg0 + 0x40)) != 0) result = 0;
    }
    return result;
}
#endif
