#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0D330.s")

extern s16 D_8AB17238; void func_8AB0D4A4(void) { D_8AB17238 += 1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0D4BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0D5F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0DFC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E0F4.s")

extern void func_8AB0E21C(s32);
void func_8AB0E1FC(void) {
    func_8AB0E21C(0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E21C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E280.s")

extern void StageFade_StartFromTransparent(s32 arg0);
extern s32 StageContext_GetFadeMode(void);
s32 func_8AB0E2EC(s32 arg0) {
    s32 result = 0x23;
    switch (arg0) {
    case 0:
        StageFade_StartFromTransparent(5);
        break;
    case 1:
        if (StageContext_GetFadeMode() == 1) {
            result = 0;
        }
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E350.s")

extern void *func_8004C8A0(void *, s32, s32, s32);
extern void func_80021ED8(s32);
extern void func_8003C6B8(s32);
extern s32 func_8004C54C(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800225C4(s32);
extern void func_87F005F0(f32, f32);
extern void func_87F006BC(void);
extern u32 func_87F006AC(void);
extern void func_8AB00BA4();
extern s32 func_8AB0E684(s32);
extern void *D_8AB11D00;
extern u8 *D_8AB11D0C;
extern u8 D_8AB126A8[];
extern s16 D_8AB17188;
extern void *D_8AB17220;
extern s32 D_8AB17234;

s32 func_8AB0E4BC(s32 arg0) {
    s32 sp1C;

    sp1C = 0x26;
    switch (arg0) {
    case 0:
        func_87F005F0((f32) (*(s16 *)((u8 *)D_8AB17220 + 8) - 0x140), (f32) (0xF0 - *(s16 *)((u8 *)D_8AB17220 + 0xA)));
        func_8004C8A0(D_8AB126A8, 0x100, 0x3A, 0x183);
        D_8AB17188 = 3;
        func_800225C4(0x5A);
        func_8004C54C(0xF, func_8004C874(0x39, *(s8 *)(D_8AB11D0C + 0x14) + 0x269));
        func_8004C8A0(D_8AB126A8, 0x100, 0x39, 0x172);
        *(u16 *)((u8 *)D_8AB11D00 + 2) = (u16)(*(u16 *)((u8 *)D_8AB11D00 + 2) | 1);
        break;
    case 1:
        func_87F006BC();
        switch ((s16) func_87F006AC()) {
        case 1:
            func_8AB00BA4(0x64, D_8AB17188, 0);
            D_8AB17188 -= 1;
            break;
        case 2:
            func_80021ED8(0x4C);
            func_8AB00BA4(0x64, D_8AB17188, 0);
            D_8AB17188 -= 1;
            break;
        case 3:
            *(u16 *)((u8 *)D_8AB11D00 + 2) = (u16)(*(u16 *)((u8 *)D_8AB11D00 + 2) & 0xFFFE);
            sp1C = func_8AB0E684(0);
            break;
        }
        break;
    case 2:
        func_8003C6B8(D_8AB17234);
        break;
    }
    return sp1C;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E684.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E8B4.s")

void func_8AB0E9D8(u8 *arg0) {
    *(s32 *)(arg0 + 0xC) = 1;
    *(s16 *)(arg0 + 0x10) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0E9E8.s")

extern u8 D_8AB12CB0[];
extern u8 *D_8AB11D0C;
extern s16 D_8AB1721C;
extern s32 func_8AB0F518(s32 arg0);
s32 func_8AB0EED8(s32 arg0) {
    s32 result = arg0;
    s32 i = 0;
    u8 *ptr = D_8AB12CB0;
    for (i = 0; i < 4; i++, ptr += 0x94) {
        if (*(s16 *)(ptr + 2) == 1) {
            D_8AB1721C = i;
            D_8AB11D0C[0xF] = i;
            result = func_8AB0F518(0);
            break;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0EF44.s")

/* mkdraft:func_8AB0F0A8 begin */
extern s16 D_8AB1269C;
extern s16 D_8AB17230;
extern s16 D_8AB17232;
extern s32 D_8AB17240;
extern void func_8AB01728(void);
extern void func_8AB0E9E8(void);
extern s32 func_80001FF0(void);
extern void func_8AB00BA4();
extern s32 func_8AB0F2F0(s32);

s32 func_8AB0F0A8(s32 arg0) {
    s16 n;
    s32 result;
    result = 0x29;
    switch (arg0) {
    case 0:
        D_8AB1269C = 0x14;
        D_8AB17240 = 0;
        break;
    case 1:
        func_8AB01728();
        func_8AB0E9E8();
        if (D_8AB17240 % (func_80001FF0() / 4) == 0) {
            D_8AB1269C--;
            if (D_8AB1269C < 0) {
                D_8AB1269C = 0;
                if (D_8AB17230 == 0) {
                    func_8AB00BA4(0x65, 0, 0);
                }
                D_8AB17230 = 1;
            }
        }
        if (D_8AB17240 % ((func_80001FF0() / 4) * 2) == 0) {
            n = D_8AB1269C / 2 + 1;
            if (D_8AB17230 == 0) {
                func_8AB00BA4(0x65, n, 0);
            }
        }
        if (D_8AB17232 == 0 || D_8AB17230 == 1) {
            result = func_8AB0F2F0(0);
        }
        result = func_8AB0EED8(result);
        D_8AB17240++;
        break;
    case 2:
        break;
    }
    return result;
}
/* mkdraft:func_8AB0F0A8 end */

extern u8 *D_8AB17190[];
void func_8AB0F29C(u8 *arg0, s32 arg1) {
    if (*(s32 *)(arg0 + 0xC) == 1) {
        *(s16 *)(arg0 + 0x10) -= 1;
        if (*(s16 *)(arg0 + 0x10) > 0) {
            return;
        }
        *(s16 *)(arg0 + 0x10) = 0;
        *(s32 *)(arg0 + 0xC) = 0;
        *(u16 *)(D_8AB17190[arg1] + 2) &= 0xFFFD;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0F2F0.s")

extern void func_8AB01FBC(void);
extern void func_8AB03ED4(void);
extern void func_8AB012A4(void);
extern s32 func_8AB0E684(s32);
extern s16 D_8AB17246;
s32 func_8AB0F484(s32 arg0) {
    s32 result = 0x2B;
    s16 *counter = &D_8AB17246;
    switch (arg0) {
    case 0:
        *counter = 0;
        func_8AB01FBC();
        break;
    case 1:
        *counter += 1;
        func_8AB03ED4();
        if (*counter >= 0xB) {
            func_8AB012A4();
            result = func_8AB0E684(0);
        }
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2324B0/func_8AB0F518.s")

extern s16 D_8AB126A0;
extern void *D_8AB16FC8;
extern s16 D_8AB1724A;
extern void func_800226C0(s32);
extern void func_80027774(u16, u8);
extern void func_8AB00618(void);
extern void func_8AB007E0(void);

s32 func_8AB0F5F8(s32 arg0) {
    s32 sp1C;
    s16 *counter = &D_8AB1724A;

    sp1C = 0x2D;
    switch (arg0) {
    case 0:
        *counter = 0;
        *(u16 *)((u8 *)D_8AB16FC8 + 2) = (u16) (*(u16 *)((u8 *)D_8AB16FC8 + 2) & 0xFFFE);
        func_8004C54C(0xF, func_8004C874(0x39, *(s8 *)(D_8AB11D0C + 0x14) + 0x269));
        if (*(s16 *)(D_8AB12CB0 + D_8AB1721C * 0x94) == 2) {
            func_8004C8A0(D_8AB126A8, 0x100, 0x39, D_8AB1721C + 0x228);
        } else {
            func_8004C8A0(D_8AB126A8, 0x100, 0x39, D_8AB1721C + 0x224);
        }
        *(u16 *)((u8 *)D_8AB11D00 + 2) = (u16) (*(u16 *)((u8 *)D_8AB11D00 + 2) | 1);
        func_80021ED8(0x37);
        func_80027774(0xCA0F, 0x24);
        func_8AB007E0();
        D_8AB126A0 = 0;
        break;
    case 1:
        *counter += 1;
        func_8AB03ED4();
        func_8AB00618();
        if (*counter >= 0x79) {
            func_800226C0(3);
            sp1C = func_8AB0E2EC(0);
        }
        break;
    }
    return sp1C;
}
#endif
