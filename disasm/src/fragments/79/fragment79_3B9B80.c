#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414A2F0.s")

extern u8 *D_841951F8[];
u8 *func_8414A3A0(u8 arg0) {
    return D_841951F8[arg0] + 0x49C;
}

s32 func_8414A3C0(u8 arg0, u32 arg1) {
    return (*(u32 *)(D_841951F8[arg0] + 0x49C) & arg1) != 0;
}

extern void func_8414A2F0(s32, u8);
void func_8414A3E8(void) {
    s32 i;
    u8 **p;
    p = D_841951F8;
    i = 0;
    do {
        func_8414A2F0(i & 0xFF, (*p)[0x49A]);
        i++;
        p++;
    } while (i != 2);
}

extern void _bzero(void *, s32);
void func_8414A440(u8 *arg0, u8 arg1, u8 arg2) {
    s32 i;
    u8 *var_s0;
    u8 *temp_s2;

    *(s32 *)(arg0 + 0x10) = 0;
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x18) = 0;
    *(s32 *)(arg0 + 0x0C) = 0;
    *(s32 *)(arg0 + 0x1C) = 0;
    *(s32 *)(arg0 + 0x20) = 0;
    *(s32 *)(arg0 + 0x24) = 0x80000000;
    var_s0 = arg0 + 0x28;
    i = 0;
    do {
        temp_s2 = var_s0;
        _bzero(var_s0, 0x40);
        i += 0x40;
        var_s0 += 0x40;
        temp_s2[arg1 + 6] = arg2;
    } while (i != 0x80);
}

extern void _bzero(void *, s32);
void func_8414A4E4(u8 *arg0, u8 arg1, u8 arg2, u8 arg3) {
    s32 i;
    u8 *var_s0;
    u8 *temp_s2;

    *(s32 *)(arg0 + 0x10) = 0;
    *(s32 *)(arg0 + 0x14) = 0;
    *(s32 *)(arg0 + 0x18) = 0;
    *(s32 *)(arg0 + 0x0C) = 0;
    *(s32 *)(arg0 + 0x1C) = 0;
    *(s32 *)(arg0 + 0x20) = 0;
    *(s32 *)(arg0 + 0x24) = 0x80000000;
    var_s0 = arg0 + 0x28;
    i = 0;
    do {
        temp_s2 = var_s0;
        _bzero(var_s0, 0x40);
        i += 0x40;
        var_s0 += 0x40;
        temp_s2[arg1 + 2] = arg2;
        temp_s2[arg1 + 6] = arg3;
    } while (i != 0x80);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414A59C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414B574.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414B73C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414B7BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414B878.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414B958.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414B9D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414BDA0.s")

extern void func_8414B574(void);
extern void func_8414B73C(void);
extern void func_8414B9D0(void);
extern void func_8414BDA0(void);
void func_8414BEB0(void) {
    func_8414B574();
    func_8414B73C();
    func_8414B9D0();
    func_8414BDA0();
}

extern u8 D_8419D7C0[];
void func_8414BEE8(void) {
    _bzero(D_8419D7C0, 0xFC0);
}

extern u8 func_80062D20(u8);
s32 func_8414BF10(u8 arg0, u8 arg1) {
    u8 temp_v0;

    temp_v0 = func_80062D20(arg1);
    if (D_841951F8[arg0][9] < 2) {
        if (temp_v0 == 7) return 0;
        if (temp_v0 == 0x62) return 0;
        if (temp_v0 == 0x72) return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414BF94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414C048.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414C18C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414C3BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414C4AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414C7D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414C858.s")

s32 func_8414C924(u8 arg0, u8 arg1) {
    return (D_8419D7C0[arg0 * 0xA8] & arg1) != 0;
}

u8 *func_8414C960(u8 arg0) {
    return D_8419D7C0 + arg0 * 0xA8;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3B9B80/func_8414C98C.s")

extern u8 *func_84154B30(u8);
void func_8414C9AC(u8 *arg0, u8 arg1) {
    arg0[0] = arg1;
    arg0[2] = func_84154B30(0)[1];
    arg0[3] = func_84154B30(1)[1];
}
#endif
