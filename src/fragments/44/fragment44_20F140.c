#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF20ED0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF20F64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF20FF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF210FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF2123C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF21610.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF21864.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF21960.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF219B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF21C04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF21C58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF21D14.s")

extern u8 *D_8AF2BDD8;
extern s16 D_8AF3A082;
extern u8 *D_8AF3A090;
extern s16 D_8AF3A176;
extern s16 func_8AF21C04(void);
void func_8AF21EE0(void) {
    s16 temp_v0;
    *(u8 *)(D_8AF2BDD8 + 1) = (u8)D_8AF3A082;
    temp_v0 = func_8AF21C04();
    switch (D_8AF3A176) {
    case 4:
        *(s16 *)(D_8AF3A090 + 0x32) = (s16)(((temp_v0 * 5) * 2) + 4);
        return;
    case 5:
        *(s16 *)(D_8AF3A090 + 0x32) = (s16)(((temp_v0 * 5) * 2) + 5);
        return;
    case 6:
        *(s16 *)(D_8AF3A090 + 0x32) = (s16)(((temp_v0 * 5) * 2) + 7);
        return;
    case 7:
    default:
        *(s16 *)(D_8AF3A090 + 0x32) = (s16)(((temp_v0 * 5) * 2) + 9);
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF21FBC.s")

extern u8 *D_8AF2BDD8;
extern u8 D_8AF279F0[];
extern u8 D_8AF27BCC[];
extern u8 D_8AF27D20[];
extern u8 *D_8AF3A198;
extern s16 D_8AF3A19C;
extern void func_8AF00504(s32);
extern s32 func_8AF003A8(s32);
s32 func_8AF220E8(void) {
    s32 sp1C;
    u8 temp_v0 = *D_8AF2BDD8;
    switch (temp_v0) {
    case 0:
        D_8AF3A19C = 7;
        D_8AF3A198 = D_8AF279F0;
        func_8AF00504(0x51);
        sp1C = func_8AF003A8(0x51);
        break;
    case 1:
        D_8AF3A19C = 5;
        D_8AF3A198 = D_8AF27BCC;
        func_8AF00504(0x47);
        sp1C = func_8AF003A8(0x47);
        break;
    case 2:
        D_8AF3A19C = 4;
        D_8AF3A198 = D_8AF27D20;
        func_8AF00504(0x3C);
        sp1C = func_8AF003A8(0x3C);
        break;
    }
    return sp1C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF221C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF2228C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF22384.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF223C8.s")

extern void func_80051D64(s32, s32);
s8 func_8005453C(u8);
extern void func_800545B4(u8, s32);
extern void func_80054E48(s32);
s32 func_8AF223C8();
extern u8 *D_8AF2BDD8;
extern s8 D_8AF3A144;
extern s16 D_8AF3A19C;

void func_8AF22594(void) {
    if (func_8AF223C8() >= D_8AF3A19C) {
        D_8AF3A144 = func_8005453C(*D_8AF2BDD8);
        func_800545B4(*D_8AF2BDD8, 1);
        func_80051D64(0x13, 0);
        func_80054E48(3);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF22608.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF233B4.s")

extern void func_8AC006B8(s32, s32, s32, s32);
void func_8AF23B38(void) {
    func_8AC006B8(56, 26, 584, 454);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_20F140/func_8AF23B64.s")

extern void func_800498C4();
extern void func_800499EC();
extern void func_8AC005D8();
extern void func_8AC075A8();
extern s16 D_8AF2BA6E;
void func_8AF2447C(void) {
    if (D_8AF2BA6E == 1) {
        func_8AF23B38();
        func_8AC005D8();
        func_8AC075A8();
    }
    func_800498C4();
    func_800499EC();
}
#endif
