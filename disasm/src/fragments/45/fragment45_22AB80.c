#include "global.h"


#ifdef VERSION_US
extern u8 *D_8AB11D0C;
void func_8AB05A00(void) { s32 i; s32 value; value = -1; i = 2; *(u8 *)(D_8AB11D0C + 0x16) = value; *(u8 *)(D_8AB11D0C + 4) = value; *(u8 *)(D_8AB11D0C + 5) = value; do { *(u8 *)(D_8AB11D0C + i + 4) = value; *(u8 *)(D_8AB11D0C + i + 5) = value; *(u8 *)(D_8AB11D0C + i + 6) = value; *(u8 *)(D_8AB11D0C + i + 7) = value; i += 4; } while (i != 0xA); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB05A6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB05B88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB06270.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB062C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB064C4.s")

extern s32 func_8AB06650(s32);
void func_8AB06630(void) { func_8AB06650(0); }

extern s32 StageContext_GetFadeMode(void);
extern void func_8AB04AE4(void);
extern s32 func_8AB06718(s32);
s32 func_8AB06650(s32 arg0) { s32 result = 2; switch (arg0) { case 0: func_8AB04AE4(); break; case 1: if (StageContext_GetFadeMode() == 0) result = func_8AB06718(0); break; } return result; }

extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromTransparent(s32);
s32 func_8AB066B4(s32 arg0) { s32 result = 3; switch (arg0) { case 0: StageFade_StartFromTransparent(5); break; case 1: if (StageContext_GetFadeMode() == 1) result = 0; break; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB06718.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB0683C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB0699C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB06AE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB06D78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07128.s")

s32 func_8AB072E4(void) {
    return 0xA;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB072EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB073F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07538.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07A34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07C34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07DC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07E6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07F80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB080A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB0896C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB08B14.s")

extern s32 func_8AB08C6C(s32);
void func_8AB08C4C(void) { func_8AB08C6C(0); }

extern s32 StageContext_GetFadeMode(void);
extern void func_8AB04AE4(void);
extern s32 func_8AB08DBC(s32);
s32 func_8AB08C6C(s32 arg0) { s32 result = 0x13; switch (arg0) { case 0: func_8AB04AE4(); break; case 1: if (StageContext_GetFadeMode() == 0) result = func_8AB08DBC(0); break; } return result; }

extern s16 D_8AB16CC8;
extern s32 func_8AB08D3C(s32);
s32 func_8AB08CD0(s32 arg0) { s32 result = 0x15; s16 *p; p = &D_8AB16CC8; switch (arg0) { case 0: *p = 0; break; case 1: if (*p >= 0xA) func_8AB08D3C(0); *p += 1; break; } return result; }

extern void StageFade_StartFromTransparent(s32);
s32 StageContext_GetFadeMode();
extern void func_800225C4(s32);
s32 func_8002806C();

s32 func_8AB08D3C(s32 arg0) {
    s32 sp1C;

    sp1C = 0x14;
    switch (arg0) {                                 /* irregular */
    case 0:
        StageFade_StartFromTransparent(5);
        if (func_8002806C() != 0x48) {
            func_800225C4(5);
        }
        break;
    case 1:
        if (StageContext_GetFadeMode() == 1) {
            sp1C = 0;
        }
        break;
    }
    return sp1C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB08DBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB08F58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB090B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB092F4.s")

void func_8AB09418(u8 *arg0) {
    *(s32 *)(arg0 + 0xC) = 1;
    *(s16 *)(arg0 + 0x10) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB09428.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB099BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB09A28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB09BD8.s")

extern f32 D_8AB11970;
extern f32 D_8AB11974;
extern u8 D_80088E50[];
extern u16 *D_8AB16C20[];
extern s32 StageContext_GetFadeMode(void);
extern void func_8AB04AE4(void);
extern s32 func_8AB06718(s32);
extern s32 func_8AB08DBC(s32);
void func_8AB09DCC(void *arg0, s32 arg1) {
    u16 *p;
    if (*(s32 *)((u8 *)arg0 + 0xC) == 1) {
        *(s16 *)((u8 *)arg0 + 0x10) -= 1;
        if (*(s16 *)((u8 *)arg0 + 0x10) <= 0) {
            *(s16 *)((u8 *)arg0 + 0x10) = 0;
            *(s32 *)((u8 *)arg0 + 0xC) = 0;
            if (*(s32 *)((u8 *)arg0 + 8) == 0) {
                p = D_8AB16C20[arg1];
                p[1] &= 0xFFFD;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB09E28.s")

s32 func_8AB09FBC(void) {
    return 0x1C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB09FC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB0A074.s")

extern u8 *D_8AB16B80;
extern u8 *D_8AB16B84;
extern u8 *D_8AB16B88;
extern u8 *D_8AB16B90;
extern u8 *D_8AB16B94;
extern u8 *D_8AB16B98;
extern s16 D_8AB16CDE;
extern void func_8AB00B98(u8 *, u32);
void func_8AB0A1A4(void) {
    (*(u16 *)((u8 *)(D_8AB16B80) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16B80) + (2))) & 0xFFFE);
    (*(u16 *)((u8 *)(D_8AB16B84) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16B84) + (2))) & 0xFFFE);
    (*(u16 *)((u8 *)(D_8AB16B88) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16B88) + (2))) & 0xFFFE);
    func_8AB00B98(D_8AB16B90, -1U);
    func_8AB00B98(D_8AB16B94, -1U);
    func_8AB00B98(D_8AB16B98, -1U);
    switch (D_8AB16CDE) {
    case 0:
        (*(u16 *)((u8 *)(D_8AB16B80) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16B80) + (2))) | 1);
        func_8AB00B98(D_8AB16B90, 0xFFFF00FFU);
        return;
    case 1:
        (*(u16 *)((u8 *)(D_8AB16B84) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16B84) + (2))) | 1);
        func_8AB00B98(D_8AB16B94, 0xFFFF00FFU);
        return;
    case 2:
        (*(u16 *)((u8 *)(D_8AB16B88) + (2))) = (u16) ((*(u16 *)((u8 *)(D_8AB16B88) + (2))) | 1);
        func_8AB00B98(D_8AB16B98, 0xFFFF00FFU);
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB0A2D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB0A720.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB0A8D4.s")
#endif
