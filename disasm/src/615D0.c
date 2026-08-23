#include "global.h"


#ifdef VERSION_US
extern s32 func_8003514C(void);
#define D_80097380 ((u8 *)0x80097380)
#define D_80097480 ((u8 *)0x80097480)
#define D_80097580 ((u8 *)0x80097580)
#define D_80097680 (*(u8 **)0x80097680)

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800609D0.s")
#if 0
void func_800609D0(void) {
    switch (func_8003514C()) {
    case 1:
        D_80097680 = D_80097380;
        break;
    case 2:
        D_80097680 = D_80097480;
        break;
    case 3:
    case 4:
    case 5:
        D_80097680 = D_80097580;
        break;
    }
}

#endif

u16 func_80060A4C(const u8 *data) {
    return ((u16)data[0] << 8) | data[1];
}

u32 GbData_ReadU24BE(const u8 *data) {
    return ((u32)data[0] << 16) | ((u32)data[1] << 8) | data[2];
}

void func_80060A84(u8 *data, s32 value) {
    data[0] = (u8)(value >> 8);
    data[1] = (u8)value;
}

void GbData_WriteU24BE(u8 *data, s32 value) {
    data[0] = (u8)(value >> 16);
    data[1] = (u8)(value >> 8);
    data[2] = (u8)value;
}

u8 func_80060AAC(s32 value) {
    return D_80097680[(u8)value];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060AC8.s")
#if 0
u8 func_80060AC8(s32 value, s32 table) {
    u8 *data = D_80097680;

    switch (table) {
    case 1:
        data = D_80097380;
        break;
    case 2:
        data = D_80097480;
        break;
    case 3:
    case 4:
    case 5:
        data = D_80097580;
        break;
    }
    return data[(u8)value];
}

#endif

s32 func_80060B28(s32 value) {
    u8 target = (u8)value;
    s32 index;

    for (index = 0; index < 0x100; index++) {
        if (D_80097680[index] == target) {
            return index;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060B74.s")
#if 0
s32 func_80060B74(s32 value, s32 table) {
    u8 *data = D_80097680;
    s32 index;

    switch (table) {
    case 1:
        data = D_80097380;
        break;
    case 2:
        data = D_80097480;
        break;
    case 3:
    case 4:
    case 5:
        data = D_80097580;
        break;
    }

    for (index = 0; index < 0x100; index++) {
        if (data[index] == (u8)value) {
            return index;
        }
    }
    return 0;
}

#endif

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060C08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060C50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060C98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060D1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060D70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060DDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060E88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060EC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060EF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060F38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060F68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060F88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060F90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060F98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060FF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061124.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061248.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800612B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006136C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800613F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800614EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800615D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006162C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800616BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/StatExpSqrt.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006179C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006183C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061940.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800619E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/Pokemon_StatExpForTarget.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061B88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061D8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061ED0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061F44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/GbSave_PlayerIdentityMatches.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061FD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/Species_ToInternalIndex.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062008.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062030.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800620E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006218C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/Deck_OpenAndSetName.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006229C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062304.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006236C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006249C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800625E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062614.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006276C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800627F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_800627FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062808.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062884.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062978.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062C18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062C24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062C30.s")
#endif
