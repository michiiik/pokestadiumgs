#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84154820.s")

extern u8 *D_841951F8[];
extern u8 D_8419E780[];
void func_841548CC(u8 arg0) {
    D_8419E780[arg0 * 0xCC] = D_841951F8[arg0][8];
    D_8419E780[arg0 * 0xCC + 1] = D_841951F8[arg0][0xA];
    D_8419E780[arg0 * 0xCC + 2] = D_841951F8[arg0][9];
    D_8419E780[arg0 * 0xCC + 3] = D_841951F8[arg0][0xB];
    D_8419E780[arg0 * 0xCC + 4] = D_841951F8[arg0][0xC];
    D_8419E780[arg0 * 0xCC + 5] = D_841951F8[arg0][0xD];
    D_8419E780[arg0 * 0xCC + 6] = D_841951F8[arg0][0xE];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84154948.s")

extern u8 D_8419E920[];
void func_84154AD4(void) {
    _bzero(D_8419E780, 0x19C);
    _bzero(D_8419E920, 0x4D8);
}

u8 *func_84154B0C(void) {
    return D_8419E780;
}

extern u8 D_8419E918;
u8 func_84154B18(void) {
    return D_8419E918;
}

extern u8 D_8419E91A;
u8 func_84154B24(void) {
    return D_8419E91A;
}

u8 *func_84154B30(u8 arg0) {
    return D_8419E780 + arg0 * 0xCC;
}

u8 *func_84154B64(u8 arg0) {
    return D_8419E780 + arg0 * 0xCC + 8;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84154B9C.s")


extern u8 *D_84195208[];
extern u8 *D_84195200[];
void func_84154C10(u8 *arg0, u8 arg1) {
    u8 *value = D_84195208[arg1];
    u8 *aux = D_84195200[arg1];
    arg0[0] = value[0];
    arg0[1] = aux[1];
    *(u16 *)(arg0 + 0x26) = aux[0x24];
    arg0[2] = value[1];
    arg0[3] = value[2];
    arg0[4] = value[5];
    arg0[5] = value[6];
    arg0[6] = value[7];
    arg0[7] = value[8];
    arg0[8] = value[9];
    arg0[9] = value[0xA];
    arg0[0xA] = value[0xB];
    arg0[0xB] = value[0xC];
    arg0[0xC] = aux[0x1D];
    *(u16 *)(arg0 + 0x28) = *(u16 *)(aux + 0x26);
    *(u16 *)(arg0 + 0x2A) = *(u16 *)(aux + 0x28);
    *(u16 *)(arg0 + 0x2C) = *(u16 *)(value + 0x32);
    *(u16 *)(arg0 + 0x2E) = *(u16 *)(value + 0x34);
    *(u16 *)(arg0 + 0x30) = *(u16 *)(value + 0x36);
    *(u16 *)(arg0 + 0x32) = *(u16 *)(value + 0x38);
    *(u16 *)(arg0 + 0x34) = *(u16 *)(value + 0x3A);
    *(u16 *)(arg0 + 0x36) = *(u16 *)(value + 0x3C);
    *(u16 *)(arg0 + 0x38) = *(u16 *)(value + 0x3E);
    *(u16 *)(arg0 + 0x3A) = *(u16 *)(value + 0x40);
    *(u16 *)(arg0 + 0x3C) = *(u16 *)(value + 0x42);
    *(u16 *)(arg0 + 0x3E) = *(u16 *)(value + 0x44);
    arg0[0xD] = value[0x1E];
    arg0[0xE] = value[0x1F];
    arg0[0xF] = value[0x20];
    arg0[0x10] = value[0x21];
    arg0[0x11] = value[0x22];
    arg0[0x12] = value[0x23];
    arg0[0x13] = value[0x24];
    arg0[0x14] = aux[0x1C];
    *(u16 *)(arg0 + 0x40) = *(u16 *)(value + 0x2E);
    *(u16 *)(arg0 + 0x42) = *(u16 *)(value + 0x46);
    arg0[0x15] = value[0xD];
    arg0[0x16] = value[0xE];
    arg0[0x17] = value[0xF];
    arg0[0x18] = value[0x10];
    arg0[0x19] = value[0x11];
    arg0[0x1A] = value[0x12];
    arg0[0x1B] = value[0x13];
    arg0[0x1C] = value[0x14];
    arg0[0x1D] = value[0x15];
    arg0[0x1E] = value[0x16];
    arg0[0x1F] = value[0x17];
    arg0[0x20] = value[0x18];
    arg0[0x21] = value[0x19];
    arg0[0x23] = value[0x1B];
    arg0[0x24] = value[0x26];
    arg0[0x25] = value[0x27];
    *(u16 *)(arg0 + 0x44) = *(u32 *)(value + 0x4C);

    arg0[0x22] = value[0x1A];
    *(u16 *)(arg0 + 0x46) = *(u16 *)(value + 0x30);
    *(u32 *)(arg0 + 0x48) = value[0x2A];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84154DF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84154FC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_841551D4.s")

void func_8415541C(u8 *arg0, u8 arg1, u8 arg2) {
    u8 *value;
    value = D_841951F8[arg1] + arg2 * 0x58;
    arg0[0] = value[0x1A];
    value += 0x18;
    arg0[1] = value[3];
    arg0[2] = value[4];
    arg0[3] = value[5];
    arg0[8] = value[1];
    arg0[9] = value[0x1C];
    *(u16 *)(arg0 + 0xA) = *(u16 *)(value + 0x2A);
    *(u16 *)(arg0 + 0xC) = *(u16 *)(value + 0x2C);
    *(u16 *)(arg0 + 0xE) = *(u16 *)(value + 0x2E);
    *(u16 *)(arg0 + 0x10) = *(u16 *)(value + 0x30);
    *(u16 *)(arg0 + 0x12) = *(u16 *)(value + 0x32);
}

extern u8 *func_84156590(u8, u8);
void func_841554B4(u8 *arg0, u8 arg1, u8 arg2) {
    u8 *value;
    value = func_84156590(arg1, arg2);
    arg0[0] = value[1];
    arg0[1] = value[2];
    arg0[2] = value[3];
    arg0[3] = value[4];
    arg0[8] = value[0xB];
    arg0[9] = value[0xC];
    *(u16 *)(arg0 + 0xA) = *(u16 *)(value + 0xE);
    *(u16 *)(arg0 + 0xC) = *(u16 *)(value + 0x10);
    *(u16 *)(arg0 + 0xE) = *(u16 *)(value + 0x12);
    *(u16 *)(arg0 + 0x10) = *(u16 *)(value + 0x14);
    *(u16 *)(arg0 + 0x12) = *(u16 *)(value + 0x16);
}

s32 func_84155544(u8 *arg0, u8 arg1) {
    s32 result;
    result = (arg1 == arg0[2]);
    if (result == 0) {
        result = (arg1 == arg0[3]);
    }
    return result;
}

extern void func_80063454(u8, u8, u8, s32);
void func_84155574(u8 *arg0, u8 arg1) {
    func_80063454(arg1, arg0[2], arg0[3], (arg0[0x15] & 8) != 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_841555B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_8415565C.s")

extern u8 func_80062D20(u8);
s32 func_841556C4(u8 *arg0, u8 arg1)
{
    s32 var_s0;
    u8 *var_s1;
    u8 var_s3;
    s32 var_s4;
    s32 var_s5;
    u8 temp_a0;

    var_s3 = arg1;
    var_s0 = 0;
    var_s1 = arg0;
    var_s4 = 0xFF;
    var_s5 = 4;
loop_1:
    temp_a0 = var_s1[4];
    if (temp_a0 != var_s4) {
        if (var_s3 == func_80062D20(temp_a0)) {
            return 1;
        }
        var_s0 += 1;
        var_s1 += 1;
        if (var_s0 == var_s5) {
            goto block_5;
        }
        goto loop_1;
    }
block_5:
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84155750.s")

extern u8 D_8419E920[];
extern u8 D_8419E780[];
extern void _bcopy(void *, u8 *, s32);
void func_841557B0(void)
{
  u8 temp_v0;
  temp_v0 = ((*D_8419E920) - 1) & 0xFF;
 *D_8419E920 = temp_v0; _bcopy((D_8419E920 + (temp_v0 * 0x19C)) + 4, D_8419E780, 0x19C);
}
#endif
