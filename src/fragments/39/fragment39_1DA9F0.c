#include "global.h"


#ifdef VERSION_US
extern u8 *D_88A01C64;
u8 *func_88A00710(s32 arg0, s16 arg1) {
    u8 *result;
    switch (arg0) {
    case 0:
        result = (u8 *)((u8 *)D_88A01C64 + (arg1 << 1) + 9);
        break;
    case 1:
        result = *(u8 **)((u8 *)D_88A01C64 + 0xF0) + (arg1 << 1);
        break;
    case 2:
        result = *(u8 **)((u8 *)D_88A01C64 + 0xF8) + (arg1 << 1);
        break;
    case 3:
        result = *(u8 **)((u8 *)D_88A01C64 + 0x100) + (arg1 << 1);
        break;
    }
    return result;
}

u8 func_88A007BC(s32 arg0) {
    u8 result;
    switch (arg0) {
    case 0: result = D_88A01C64[0]; break;
    case 1: result = D_88A01C64[0xEF]; break;
    case 2: result = D_88A01C64[0xF4]; break;
    case 3: result = D_88A01C64[0xFC]; break;
    }
    return result;
}

s32 func_88A0083C(u8 *arg0) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (arg0 < func_88A00710(i, 0)) continue;
        if (func_88A00710(i, func_88A007BC(i) - 1) < arg0) continue;
        return i;
    }
    return 0;
}

extern s32 func_8800005C(void);
extern s32 func_88A0083C(u8 *arg0);
s32 func_88A008CC(arg0)
u8 *arg0;
{
    s32 result;

    if (func_8800005C() != 0) {
        if (func_88A0083C(arg0) == 2) {
            result = 0;
        } else {
            result = 1;
        }
        return result;
    }
    if (func_88A0083C(arg0) == 3) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

extern void func_800635E0(u8, u8 *);
extern void func_80063620(u8, u8 *);
s32 func_88A008CC();

void func_88A00938(u8 *arg0) {
    if (func_88A008CC() != 0) {
        func_80063620(*arg0, arg0);
        return;
    }
    func_800635E0(*arg0, arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/39/fragment39_1DA9F0/func_88A00978.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/39/fragment39_1DA9F0/func_88A00B44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/39/fragment39_1DA9F0/func_88A00D0C.s")

s32 func_88A00FD4(u8 arg0) {
    s32 result = 0;
    switch (arg0) {
    case 2:
        result = 3;
        break;
    case 3:
        result = 1;
        break;
    case 4:
        result = 2;
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/39/fragment39_1DA9F0/func_88A01018.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/39/fragment39_1DA9F0/func_88A01074.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/39/fragment39_1DA9F0/func_88A013E8.s")

extern s32 func_8800005C(void);
extern u8 func_8006378C(u8);
extern s32 func_88A00FD4(u8);
extern void func_88A013E8(s32, s8);
void func_88A014C8(s32 arg0, u8 arg1, s8 arg2) {
    s32 index;

    switch (arg0) {
    case 0:
        if (func_8800005C() != 0) {
            index = 0;
        } else {
            index = func_88A00FD4(func_8006378C(arg1));
        }
        func_88A013E8(index, arg2);
        break;
    case 1:
        D_88A01C64[0xEF] += arg2;
        break;
    case 2:
        D_88A01C64[0xF4] += arg2;
        break;
    case 3:
        D_88A01C64[0xFC] += arg2;
        break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/39/fragment39_1DA9F0/func_88A015A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/39/fragment39_1DA9F0/func_88A016F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/39/fragment39_1DA9F0/func_88A017B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/39/fragment39_1DA9F0/func_88A01990.s")
#endif
