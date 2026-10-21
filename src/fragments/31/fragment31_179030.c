#include "global.h"


#ifdef VERSION_US
extern void Util_Free(void *);
extern void *D_882346F8;

void func_88205DB0(void) {
    (*(s32 (**)())((u8 *)(D_882346F8) + (0x9C)))();
    Util_Free(D_882346F8);
}

extern void func_88200134();
void func_88205DE8(void) { func_88200134(0, 1); func_88200134(1, 1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88205E18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88205EB0.s")

void func_88206430(void) { func_88200134(2, 2); func_88200134(3, 2); }

extern void func_88003A00(s32);
extern s32 D_88234564;
void func_88206460(void) {
    func_88003A00(D_88234564 + 0x88);
    func_88003A00(D_88234564 + 0xCC);
    func_88003A00(D_88234564 + 0x44);
    func_88003A00(D_88234564);
}

extern void func_880022B4(void *, s16, s32);
void func_882064B4(s32 arg0, s32 *arg1, void *arg2, void *arg3) {
    s32 mode;

    *arg1 = arg0;
    if (arg0 != 0) {
        mode = 0;
    } else {
        mode = 1;
    }
    func_880022B4(arg2, 0xF00, mode);
    func_880022B4(arg3, 0xF00, mode);
}

extern void func_800226C0(s32);
extern void func_88903C50(void *, s16, s16, s32, u8, u8, u8, u8, u8,
                         s32 *, s32 *, void (*)(void), void (*)(void));
extern void func_88903B00(void);
extern void D_88000E4C(void);
extern s32 D_880068B4;
extern s32 D_880068B8;

void func_88206508(void *arg0, u8 *arg1) {
    *arg1 = 2;
    func_800226C0(73);
    func_88903C50(arg0, 320, 240, 4, 255, 170, 140, 2, 0,
                 &D_880068B4, &D_880068B8, func_88903B00, D_88000E4C);
}

s32 func_8004C990(s32, s32);
s32 func_8004D150(s32, s32, s32, s32, s32, s32);
extern s32 D_8823459C;
extern s32 D_882345A0;
extern s32 D_882345A4;
extern s32 D_882345B0;
extern s32 D_882345BC;
extern s32 D_882345C0;
extern s32 D_882345C4;

void func_8820659C(s16 arg0, s16 arg1, s32 arg2, s32 arg3) {
    u16 flag = 0;

    if (arg3 != 0) {
        if (arg2 == D_8823459C) {
            arg2 = func_8004C990(0xF, 2);
        } else if ((arg2 == D_882345A0) || (arg2 == D_882345A4) || (arg2 == D_882345B0) ||
                   (arg2 == D_882345BC) || (arg2 == D_882345C0) || (arg2 == D_882345C4)) {
            flag = 1;
        }
    }
    func_8004D150(arg0, arg1, arg2, 0, flag, 0);
}
extern Gfx *D_800D0510;
extern Gfx D_80094E38[];
extern Gfx D_80094F50[];
extern u8 *D_8800ECC0;
extern void func_882001E8(void);
extern void func_882052F8(void);
extern s32 func_8004D27C(u8 *, s32, s32);
extern void func_88002BA0(u8, u8, u8);
extern void func_88200180(u8);

void func_88206668(void) {
    func_882001E8();
    func_882052F8();
    gSPDisplayList(D_800D0510++, D_80094E38);
    func_8004D27C(D_8800ECC0, 128, 1);
    func_88002BA0(220, 220, 180);
    func_88200180(0);
    func_88200180(1);
    gSPDisplayList(D_800D0510++, D_80094F50);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206714.s")

extern s32 D_882346F0;

void func_88206C2C(u16 arg0) {
    gDPPipeSync(D_800D0510++);
    if (D_882346F0 == 1 || D_882346F0 == 3 || arg0 != 0) {
        gDPSetEnvColor(D_800D0510++, 220, 220, 180, 255);
    } else {
        gDPSetEnvColor(D_800D0510++, 150, 150, 130, 255);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88206CC0.s")

extern void Gfx_SetScissorRect(Gfx **, s16, s16, s16, s16);
s32 func_880032C4();
extern void func_882001E8();
extern Gfx *D_800D0510;

void func_88207D14(u8 *arg0) {
    if (*arg0 != 0) {
        Gfx_SetScissorRect(&D_800D0510, 0x2C, 0x48, 0x229, 0x17F);
        func_882001E8();
        if (func_880032C4() == 0) {
            *arg0 -= 1;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_179030/func_88207D80.s")
#endif
