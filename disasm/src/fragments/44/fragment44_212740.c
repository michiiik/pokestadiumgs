#include "global.h"


#ifdef VERSION_US
extern u8 func_80054794(void);
s32 func_8AF244D0(void) {
    s32 var_v1;
    s32 sp1C;

    sp1C = 0;
    var_v1 = sp1C;
    if ((func_80054794() & 7) == 7) {
        var_v1 = 1;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_212740/func_8AF24508.s")

extern u8 func_80054794(void);
extern s32 func_8AC004E0(s16);
extern void func_800547F4(s32);
extern void func_80051D64(s32, s32);
extern void func_80054E48(s32);
extern s32 D_8AF279E4;
void func_8AF2458C(void) {
    s16 i;
    s32 bit;
    u8 flags;

    flags = func_80054794();
    D_8AF279E4 = 0;
    i = 0;
    do {
        bit = (1 << i) & 0xFF;
        if (!(flags & bit) && (func_8AC004E0(i) != 0)) {
            func_800547F4((flags | bit) & 0xFF);
            func_80051D64(0x13, 0);
            func_80054E48(3);
        }
        i++;
    } while (i < 3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_212740/func_8AF24628.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_212740/func_8AF24A7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_212740/func_8AF24AE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_212740/func_8AF25028.s")

extern void func_8AF24508(s16);
extern s16 D_8AF279E0;
extern s16 D_8AF3A3CC;
extern s16 D_8AF3A3CE;
void func_8AF25870(s16 arg0) {
    D_8AF279E0 = 1;
    D_8AF3A3CE = arg0;
    D_8AF3A3CC = 0;
    func_8AF24508(arg0);
}

void func_8AF258B4(s16 arg0, s16 arg1) {
    D_8AF279E0 = 1;
    D_8AF3A3CE = arg1;
    D_8AF3A3CC = arg0;
    func_8AF24508(arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_212740/func_8AF25908.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_212740/func_8AF25974.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_212740/func_8AF25A84.s")

extern void *D_8AF3A3C0;
extern void *D_8AF3A664;
extern void *D_8AF263C0;
extern s16 D_8AF3A662;
extern s16 D_8AF3A6E4;
extern s16 D_8AF3A6E6;
extern void func_8AF00130(s32);

void func_8AF25DF0(void) {
    (*(s16 *)((u8 *)(D_8AF3A3C0) + (0x30))) = 0x36;
    (*(s16 *)((u8 *)(D_8AF3A3C0) + (0x32))) = 0x4A;
    if (D_8AF3A6E4 < 0x1E) {
        D_8AF3A6E4 += 1;
        return;
    }
    (*(u16 *)((u8 *)(D_8AF3A664) + (2))) =
        (u16)((*(u16 *)((u8 *)(D_8AF3A664) + (2))) | 1);
    if ((*(u16 *)((u8 *)(D_8AF263C0) + (8))) & 0x8000) {
        D_8AF3A662 = 2;
        func_8AF00130(0xC2);
        D_8AF3A6E6 = 0;
        (*(u16 *)((u8 *)(D_8AF3A664) + (2))) =
            (u16)((*(u16 *)((u8 *)(D_8AF3A664) + (2))) & 0xFFFE);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_212740/func_8AF25EA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_212740/func_8AF25F40.s")

s32 func_8AF25F40(s32);
extern s16 D_8AF3A662;
extern void *D_8AF3A664;

void func_8AF2610C(void) {
    (*(u16 *)((u8 *)(D_8AF3A664) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3A664) + (2))) & 0xFFFE);
    if (func_8AF25F40(1) == -1) {
        D_8AF3A662 = 4;
    }
}

extern void func_80021ED8(s32);
s32 func_80025D44();
extern u8 D_8AF3A661;

void func_8AF26154(void) {
    if (func_80025D44() == 0) {
        (*(u16 *)((u8 *)(D_8AF3A664) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3A664) + (2))) | 1);
        func_80021ED8(7);
        D_8AF3A662 = 5;
        if (D_8AF3A661 == 2) {
            D_8AF3A662 = 6;
        }
    }
}

extern void func_8AF00130(s32);
extern void *D_8AF263C0;
extern void *D_8AF3A3C0;
void func_8AF261C0(void) {
    (*(s16 *)((u8 *)(D_8AF3A3C0) + (0x30))) = 0x36;
    (*(s16 *)((u8 *)(D_8AF3A3C0) + (0x32))) = 0x4C;
    if ((*(u16 *)((u8 *)(D_8AF263C0) + (8))) & 0x8000) {
        (*(u16 *)((u8 *)(D_8AF3A664) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3A664) + (2))) & 0xFFFE);
        D_8AF3A662 = 0;
        func_8AF00130(0xC2);
    }
}

void func_8AF26234(void) {
    (*(s16 *)((u8 *)(D_8AF3A3C0) + (0x30))) = 0x36;
    (*(s16 *)((u8 *)(D_8AF3A3C0) + (0x32))) = 0x4D;
    (*(u16 *)((u8 *)(D_8AF3A664) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3A664) + (2))) | 1);
    if ((*(u16 *)((u8 *)(D_8AF263C0) + (8))) & 0x8000) {
        D_8AF3A662 = 7;
        func_8AF00130(0xC2);
    }
}

void func_8AF262AC(void) {
    (*(s16 *)((u8 *)(D_8AF3A3C0) + (0x30))) = 0x36;
    (*(s16 *)((u8 *)(D_8AF3A3C0) + (0x32))) = 0x4E;
    (*(u16 *)((u8 *)(D_8AF3A664) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3A664) + (2))) | 1);
    if ((*(u16 *)((u8 *)(D_8AF263C0) + (8))) & 0x8000) {
        D_8AF3A662 = 8;
        func_8AF00130(0xC2);
    }
}

void func_8AF26324(void) {
    (*(s16 *)((u8 *)(D_8AF3A3C0) + (0x30))) = 0x36;
    (*(s16 *)((u8 *)(D_8AF3A3C0) + (0x32))) = 0x4F;
    (*(u16 *)((u8 *)(D_8AF3A664) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3A664) + (2))) | 1);
    if ((*(u16 *)((u8 *)(D_8AF263C0) + (8))) & 0x8000) {
        (*(u16 *)((u8 *)(D_8AF3A664) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AF3A664) + (2))) & 0xFFFE);
        D_8AF3A662 = 0;
        func_8AF00130(0xC2);
    }
}

void func_8AF263AC(void) {
}
#endif
