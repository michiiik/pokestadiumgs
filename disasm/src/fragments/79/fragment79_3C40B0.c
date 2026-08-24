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

extern u8 D_8419E780[];
extern u8 D_8419E920[];
void func_84154AD4(void) {
    _bzero(D_8419E780, 0x19C);
    _bzero(D_8419E920, 0x4D8);
}

extern u8 D_8419E780[];
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

extern u8 D_8419E780[];
u8 *func_84154B30(u8 arg0) {
    return D_8419E780 + arg0 * 0xCC;
}

extern u8 D_8419E780[];
u8 *func_84154B64(u8 arg0) {
    return D_8419E780 + arg0 * 0xCC + 8;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84154B9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84154C10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84154DF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84154FC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_841551D4.s")

extern u8 *D_841951F8[];
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84155544.s")

extern void func_80063454(u8, u8, u8, s32);
void func_84155574(u8 *arg0, u8 arg1) {
    func_80063454(arg1, arg0[2], arg0[3], (arg0[0x15] & 8) != 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_841555B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_8415565C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_841556C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_84155750.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C40B0/func_841557B0.s")
#endif
