#include "global.h"


#ifdef VERSION_US
extern u8 D_8AF2C4F8[];
extern u32 D_8AF2C548;
void func_8AF035E0(void *arg0) {
    u32 count = D_8AF2C548;
    if (count < 0xA) {
        u8 *dest = D_8AF2C4F8 + count * 8;
        *(s32 *)dest = *(s32 *)((u8 *)arg0 + 0x4E4);
        *(s32 *)(dest + 4) = *(s32 *)((u8 *)arg0 + 0x4E8);
        D_8AF2C548 = count + 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03624.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03678.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03730.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03798.s")

extern void func_8AC0619C(s32 *, u16);
extern void func_8AC06220(s32 *, u16);
extern u16 D_8AF2BDC6;
extern s16 D_8AF2C094;
extern u8 D_8AF2C098;
extern u8 D_8AF2C110;
extern u8 D_8AF2C188;
extern u8 D_8AF2C200;
void func_8AF037EC(void) {
    switch (D_8AF2C094) {                           /* irregular */
    case 0:
        func_8AC0619C(&D_8AF2C188, D_8AF2BDC6);
        func_8AC06220(&D_8AF2C200, D_8AF2BDC6);
        return;
    case 1:
        func_8AC0619C(&D_8AF2C098, D_8AF2BDC6);
        func_8AC06220(&D_8AF2C110, D_8AF2BDC6);
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03878.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03B38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03BC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03D34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03DA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03DF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03E38.s")

extern void func_8AC00738();

s32 func_8AF03F14(s32 arg0, s32 arg1) {
    if ((arg0 != 0) && (arg0 == 1)) {
        func_8AC00738();
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03F4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF03FF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04340.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04404.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF044C4.s")

void func_8AF04514(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x24))) = 0xB5;
    (*(s16 *)((u8 *)(arg0) + (0x26))) = 1;
    (*(s32 *)((u8 *)(arg0) + (0x2C))) = -1;
}

void func_8AF04530(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x24))) = 0xB5;
    (*(s16 *)((u8 *)(arg0) + (0x26))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x2C))) = 0xDC0000FF;
}

void func_8AF0454C(u8 *arg0) {
    *(s16 *)(arg0 + 0x24) = 0xB6;
    *(s16 *)(arg0 + 0x26) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF0455C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04894.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04A14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04A54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04C50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04CC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04D68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04DB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04E2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04E8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF04F38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF0501C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF05C10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF05DC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF05E14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF05E94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF05EE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF06404.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF06450.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF065DC.s")

extern void func_800503A4(s32);
s32 *func_8AF04E2C();

void func_8AF06E74(void) {
    s32 *temp_v0;

    temp_v0 = func_8AF04E2C();
    if (temp_v0 != NULL) {
        func_800503A4(*temp_v0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1F1850/func_8AF06EA4.s")

s32 main_pool_alloc(s32, s32);
extern void func_80025F84(s32);
extern void func_8AC00FFC(s32);
extern s32 D_8AF2646C;
extern s32 D_8AF2C020;

void func_8AF070B4(void) {
    if (D_8AF2646C == 0) {
        func_8AC00FFC(0x47425345);
        D_8AF2646C = 1;
        D_8AF2C020 = main_pool_alloc(0x8400, 0);
    }
    func_80025F84(D_8AF2C020);
}

extern void func_8002602C();
extern void func_8AC01064(s32);
void func_8AF07110(void) {
    func_8002602C();
    if (D_8AF2646C != 0) {
        D_8AF2646C = 0;
        func_8AC01064(0x47425345);
    }
}
#endif
