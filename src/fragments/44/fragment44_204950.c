#include "global.h"


#ifdef VERSION_US
typedef struct {
    u32 unk_00[321];
} unk_func_8AF166E0;

void func_8AF166E0(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u8 arg7,
                   u8 arg8, u8 arg9, u8 arg10, s32 arg11, s32 arg12, const unk_func_8AF166E0* arg13) {
    *(s32*)(arg0 + 24) = arg1;
    *(s32*)(arg0 + 8) = arg2;
    *(s32*)(arg0 + 12) = arg3;
    *(s32*)(arg0 + 16) = arg4;
    arg0[34] = arg5;
    arg0[35] = arg6;
    arg0[36] = arg7;
    arg0[37] = arg8;
    arg0[38] = arg9;
    arg0[39] = arg10;
    *(s32*)arg0 = arg11;
    *(s32*)(arg0 + 20) = -1;
    *(s32*)(arg0 + 28) = arg12;
    *(unk_func_8AF166E0*)(arg0 + 40) = *arg13;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF16774.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF16878.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF169A4.s")

extern void *D_8AF27150;
extern void *D_8AF263C0;
extern u16 D_8AF2BDC6;
extern s32 D_8AF340C0;
extern s32 D_8AF34138;
extern s32 D_8AF341B0;
extern s32 func_8AF0326C(void *);
extern void func_8AF00130(s32);
extern void func_8AC0686C(void *, s16);
extern void func_8AC0619C(s32 *, u16);
extern void func_8AC06220(s32 *, u16);
s16 func_8AF16D2C(void) {
    s16 result = 0x11;
    void *state = D_8AF27150;
    if (func_8AF0326C(state) == 0) {
        if ((*(u16 *)((u8 *)D_8AF263C0 + 8)) & 0x4000) {
            func_8AF00130(3);
            result = 0x10;
        }
    }
    func_8AC0686C(&D_8AF341B0, *(s16 *)((u8 *)state + 0x38));
    func_8AC0619C(&D_8AF340C0, D_8AF2BDC6);
    func_8AC06220(&D_8AF34138, D_8AF2BDC6);
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF16DC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF16E60.s")

extern u16 *D_8AF2BAA4;
s32 func_8AF16EB0(u8 arg0) {
    u16 *entry;
    u16 value;
    s32 result;
    entry = D_8AF2BAA4;
    entry += arg0;
    value = *--entry;
    result = 0;
    if (value & 1) {
        return 1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF16EF0.s")

extern void func_8004C594(s32, s16);
extern void *D_8AF342E0;
extern s16 D_8AF34800;
extern s16 D_8AF34D64;
void func_8AF171D8(s32 arg0) {
    (*(s16 *)((u8 *)(D_8AF342E0) + (0x30))) = 0x3B;
    (*(s16 *)((u8 *)(D_8AF342E0) + (0x32))) = (s16) (D_8AF34D64 + 0xDB);
    func_8004C594(2, D_8AF34800);
}

extern void _bzero(s32 *, s32);
extern s16 D_8AF347F4;
extern s16 D_8AF347F6;
extern u8 D_8AF34808;

void func_8AF1722C(void) {
    D_8AF347F4 = 0;
    D_8AF347F6 = 0;
    _bzero(&D_8AF34808, 0xE);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF17264.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF174DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_204950/func_8AF176C4.s")
#endif
