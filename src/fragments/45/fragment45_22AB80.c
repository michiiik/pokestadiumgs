#include "global.h"


#ifdef VERSION_US
extern u8 *D_8AB11D0C;
void func_8AB05A00(void) { s32 i; s32 value; value = -1; i = 2; *(u8 *)(D_8AB11D0C + 0x16) = value; *(u8 *)(D_8AB11D0C + 4) = value; *(u8 *)(D_8AB11D0C + 5) = value; do { *(u8 *)(D_8AB11D0C + i + 4) = value; *(u8 *)(D_8AB11D0C + i + 5) = value; *(u8 *)(D_8AB11D0C + i + 6) = value; *(u8 *)(D_8AB11D0C + i + 7) = value; i += 4; } while (i != 0xA); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB05A6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB05B88.s")

extern u8 D_80088E50[];
extern f32 D_8AB11970;
extern f32 D_8AB11974;
void func_8AB06270(void *arg0, u16 arg1) {
    f32 *temp;
    f32 scale;
    f32 offset;
    arg1 <<= 12;
    temp = (f32 *)D_80088E50 + (arg1 >> 4);
    scale = D_8AB11970;
    offset = D_8AB11974;
    *(f32 *)((u8 *)arg0 + 0x40) = *temp * scale + offset;
    *(f32 *)((u8 *)arg0 + 0x44) = *temp * scale + offset;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB062C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB064C4.s")

extern s32 func_8AB06650(s32);
void func_8AB06630(void) {
    func_8AB06650(0);
}

extern s32 StageContext_GetFadeMode(void);
extern void func_8AB04AE4(void);
extern s32 func_8AB06718(s32);
s32 func_8AB06650(s32 arg0) { s32 result = 2; switch (arg0) { case 0: func_8AB04AE4(); break; case 1: if (StageContext_GetFadeMode() == 0) result = func_8AB06718(0); break; } return result; }

extern s32 StageContext_GetFadeMode(void);
extern void StageFade_StartFromTransparent(s32);
s32 func_8AB066B4(s32 arg0) { s32 result = 3; switch (arg0) { case 0: StageFade_StartFromTransparent(5); break; case 1: if (StageContext_GetFadeMode() == 1) result = 0; break; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB06718.s")

extern void *D_8AB16964;
extern u8 D_8AB126A8[];
extern s16 D_8AB16950;
extern s32 D_8AB16A14;
extern void func_87F005F0(f32, f32);
extern void func_8004C8A0(void *, s32, s32, s32);
extern void func_87F006BC(void);
extern u32 func_87F006AC(void);
extern void func_8AB00BA4();
extern void func_80021ED8(s32);
extern s32 func_8AB0699C(s32);
extern void func_8003C6B8(s32);
extern void func_800225C4(s32);
s32 func_8AB0683C(s32 arg0) {
    s32 result = 5;
    s16 temp_v0;
    switch (arg0) {
    case 0:
        func_87F005F0((f32)(*(s16 *)((u8 *)D_8AB16964 + 8) - 0x140), (f32)(0xF0 - *(s16 *)((u8 *)D_8AB16964 + 0xA)));
        func_8004C8A0(D_8AB126A8, 0x100, 0x39, 0x166);
        D_8AB16950 = 3;
        func_800225C4(0x5A);
        break;
    case 1:
        func_87F006BC();
        temp_v0 = func_87F006AC();
        switch (temp_v0) {
        case 1:
            func_8AB00BA4(0x64, D_8AB16950, 0);
            D_8AB16950 -= 1;
            break;
        case 2:
            func_8AB00BA4(0x64, D_8AB16950, 0);
            func_80021ED8(0x14);
            D_8AB16950 -= 1;
            break;
        case 3:
            result = func_8AB0699C(0);
            break;
        }
        break;
    case 2:
        func_8003C6B8(D_8AB16A14);
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB0699C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB06AE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB06D78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07128.s")

s32 func_8AB072E4(void) {
    return 0xA;
}

extern s16 D_8AB16A2A;
extern u8 *D_8AB12668[];
extern u8 *D_8AB12678[];
extern u16 D_8AB1269E;
extern s16 D_8AB12694;
extern s32 func_8AB073F4(s32);
extern void func_8AB00B98(u8 *, u32);
extern void func_8AB01FBC(void);
extern void func_8AB03ED4(void);
extern s32 func_8AB0699C(s32);
s32 func_8AB072EC(s32 arg0)
{
    s32 result;
    u8 **ptr;
    u8 **end;
    s16 step;

    step = 1;
    result = 0xB;
    switch (arg0) {
        case 0:
            D_8AB16A2A = 0;
            func_8AB01FBC();
            break;
        case 1:
            D_8AB16A2A += step;
            func_8AB03ED4();
            end = D_8AB12678;
            if (D_8AB16A2A >= 0xB) {
                ptr = D_8AB12668;
                do {
                    func_8AB00B98(*ptr, -1U);
                    ptr++;
                } while (ptr != end);
                if (D_8AB1269E == 0) {
                    result = func_8AB0699C(0);
                } else {
                    D_8AB12694 += 1;
                    if (D_8AB12694 >= 0xA) {
                        result = func_8AB073F4(0);
                    } else {
                        result = func_8AB0699C(0);
                    }
                }
            }
            break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB073F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07538.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07A34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07C34.s")

extern s16 D_8AB16A36;
extern s32 func_80025D44(void);
extern s32 func_8AB07E6C(s32);
extern void func_80021ED8(s32);
extern void func_8004C8A0(void *, s32, s32, s32);
extern u8 D_8AB126A8[];
s32 func_8AB07DC4(s32 arg0)
{
    s32 result;
    int new_var;
    new_var = 1;
    result = 0x10;
    switch (arg0)
    {
        case 0:
            D_8AB16A36 = 0;
            func_8004C8A0(D_8AB126A8, 0x100, 0x39, 0x183);
            func_80021ED8(0x4B);
            break;
        case 1:
            D_8AB16A36 += new_var;
            if ((((u32) func_80025D44()) < 2U) && (D_8AB16A36 >= 0x3D))
            {
                result = func_8AB07E6C(0);
            }
            break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07E6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB07F80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB080A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB0896C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_22AB80/func_8AB08B14.s")

extern s32 func_8AB08C6C(s32);
void func_8AB08C4C(void) {
    func_8AB08C6C(0);
}

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

extern u8 *D_8AB16CB0;
extern s16 D_8AB16C18;
extern s32 D_8AB16CC4;
extern s32 func_8AB090B8(s32);
extern void func_80021ED8(s32);
extern void func_800225C4(s32);
extern void func_8003C6B8(s32);
extern void func_8004C8A0(void *, s32, s32, s32);
extern void func_87F005F0(f32, f32);
extern u32 func_87F006AC(void);
extern void func_87F006BC(void);
extern void func_8AB00BA4();
extern u8 D_8AB126A8[];
s32 func_8AB08F58(s32 arg0) {
    s32 result = 0x17;
    s16 temp_v0;
    switch (arg0) {
    case 0:
        func_87F005F0((f32)(*(s16 *)(D_8AB16CB0 + 8) - 0x140), (f32)(0xF0 - *(s16 *)(D_8AB16CB0 + 0xA)));
        func_8004C8A0(D_8AB126A8, 0x100, 0x3A, 0x183);
        D_8AB16C18 = 3;
        func_800225C4(0x5A);
        break;
    case 1:
        func_87F006BC();
        temp_v0 = func_87F006AC();
        switch (temp_v0) {
        case 1:
            func_8AB00BA4(0x64, D_8AB16C18, 0);
            D_8AB16C18 -= 1;
            break;
        case 2:
            func_8AB00BA4(0x64, D_8AB16C18, 0);
            func_80021ED8(0x4C);
            D_8AB16C18 -= 1;
            break;
        case 3:
            result = func_8AB090B8(0);
            break;
        }
        break;
    case 2:
        func_8003C6B8(D_8AB16CC4);
        break;
    }
    return result;
}

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

extern s16 D_8AB16CE6;
extern s32 func_8AB0A2D8(s32);
s32 func_8AB0A8D4(s32 arg0) { s32 result = 0x21; s16 *count = &D_8AB16CE6; switch (arg0) { case 0: *count = 0; break; case 1: if (*count >= 0x1F) result = func_8AB0A2D8(0); *count = *count + 1; break; } return result; }
#endif
