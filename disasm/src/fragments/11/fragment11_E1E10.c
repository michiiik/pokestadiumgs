#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160A270.s")

s32 func_8160A2E8(s32 arg0) {
    return ((arg0 % 3) * 0x9A) + 0xC;
}

s32 func_8160A31C(s32 arg0) {
    s32 quotient = arg0 / 3;
    return quotient * 65 + 9;
}

void *func_8160A33C(void *arg0, s32 arg1) {
    while (arg1-- > 0) {
        arg0 = *(void **)((u8 *)arg0 + 0x4D98);
    }
    return arg0;
}

void *func_8160A360(void *arg0, s32 arg1) {
    while (arg1-- > 0) {
        arg0 = *(void **)((u8 *)arg0 + 0x4D94);
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160A384.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160A438.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160A50C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160A6AC.s")

extern void func_8004D878(s32, s32, s32);
void func_8160A6D0(s32 arg0, s32 arg1) {
    s32 offset = arg1 * 0xCE8;
    u8 *temp_v0 = (u8 *)((u32)arg0 + offset);
    if (temp_v0[0x20] != 0) {
        func_8004D878((s32)(temp_v0 + 0x80), 0x84, 0);
    }
}

extern void func_8004D878(s32, s32, s32);
void func_8160A72C(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = arg0 + 0x80;
    do {
        func_8004D878(var_s1, 0x84, 0);
        var_s0 += 0xCE8;
        var_s1 += 0xCE8;
    } while (var_s0 != 0x4D70);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160A780.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160A844.s")

s32 func_8160A8DC(arg0)
u8 *arg0;
{
    s32 i = 0;
    s32 stride = 0xCE8;
    if (arg0[0x20] != 0) {
        do {
            i++;
            if (i >= 6) {
                break;
            }
        } while (*(u8 *)((u32)arg0 + i * stride + 0x20) != 0);
    }
    return i;
}

s32 func_8160A920(u8 *arg0) {
    return *(s8 *)(arg0 + 8);
}

void func_8160A928(u8 *arg0, s32 arg1) {
    arg1 += 6;
    arg1 %= 6;
    arg0[9] = arg1;
    arg0[8] = arg1;
    *(f32 *)(arg0 + 4) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160A94C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160A994.s")

s32 func_8160A8DC();

s32 func_8160A9CC(void) {
    return func_8160A8DC() >= 6;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160A9F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160ABF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160B128.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160B3E0.s")

extern void func_81604944(s32, s32, s32, s32, s32 *, s32 *);
extern void func_81607360(s32);
extern void func_81607408();
extern void func_81608A38(s32, s32, s32, s32);
extern u8 D_8160BF10;
extern u8 D_8160BF18;
void func_8160B54C(s32 arg0, s32 arg1, s32 arg2) {
    func_81607360(arg2);
    func_81604944(arg0, arg1, 0x1D9, 0x8F, &D_8160BF18, &D_8160BF10);
    func_81608A38(arg0, arg1, 7, 0x3F800000);
    func_81607408();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160B5BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160B6E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160B828.s")

extern void func_8160A6AC(void *);
void func_8160B8A8(u8 *arg0, s32 arg1, s32 arg2) {
    arg0[9] = 0;
    arg0[10] = arg1;
    *(s32 *)arg0 = arg2;
    ((s8 *)arg0)[8] = ((s8 *)arg0)[9];
    *(f32 *)(arg0 + 4) = 0.0f;
    func_8160A6AC(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160B8E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/11/fragment11_E1E10/func_8160B9A0.s")
#endif
