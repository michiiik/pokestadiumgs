#include "global.h"


#ifdef VERSION_US
extern u8 *D_88234564;
extern void func_800033DC(void *);
extern void main_pool_pop_state(s32);
extern void func_8821CE40(s32);
extern s32 D_88234560;
void func_88213410(void) {
    func_800033DC(D_88234564);
    main_pool_pop_state(0x4D41494C);
    func_8821CE40(4);
    D_88234560 = 5;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88213450.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88213530.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88213A3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88213A94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88213BE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88213E9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882142DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88214330.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88214394.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882143EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882152F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88215420.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882157DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882158E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882159A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88215BCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88215C4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88215CE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88215D4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88215E54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882160F8.s")

extern u8 *D_88234564;
extern void func_800033DC(void *);
extern void main_pool_pop_state(s32);
extern void func_8821CE40(s32);
extern s32 D_88234560;
void func_882164E0(void) {
    func_800033DC(D_88234564);
    main_pool_pop_state(0x4C495354);
    func_8821CE40(0);
    D_88234560 = 5;
}

extern void func_88200134(s32, s32);
void func_88216520(void) { func_88200134(0, 2); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88216544.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88216D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88216D98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88216E28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88216E80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88216EFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88216F74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88217040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88217C90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88217DA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88217F70.s")

extern s32 D_889041B4;
s32 func_88218064(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 result = 1;
    *arg2 = arg0;
    *arg3 = arg0 + arg1 - 1;
    if (D_889041B4 == 3) {
        if (*arg2 >= 0xFD) {
            result = 0;
        } else if (*arg3 >= 0xFD) {
            *arg3 = 0xFC;
        }
    }
    return result;
}

void func_882180C4(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    *arg2 = arg1;
    *arg3 = arg1 + 0x13;
    if (arg0 == 0) {
        if (*arg2 < 0x93) {
            *arg2 = 0x93;
        }
    } else if (arg0 == 0xE) {
        if (*arg3 >= 0x1AB) {
            *arg3 = 0x1AA;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821811C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821B3E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821B438.s")

extern u16 D_88234758; extern s32 D_88234778; s32 func_8821B468(void) { s32 result = 0; if (D_88234758 == 0) { if (D_88234778 == 0) result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821B498.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821B5EC.s")

extern s32 D_88234778; extern s32 D_8823477C; void func_8821B700(s32 arg0, s32 arg1) { D_88234778 = arg0; D_8823477C = arg1; }

extern u16 D_88234744; extern void func_8821B700(s32, s32); extern void func_8821CCE8(s32, s32); void func_8821B714(s32 arg0, s32 arg1) { func_8821B700(arg0, arg1); if (D_88234744 >= 2) func_8821CCE8(arg0, arg1); }

extern u8 D_88234765; extern u8 D_882347B8[]; void func_8821B758(u8 arg0) { D_88234765 = D_882347B8[arg0]; }

extern u16 D_88234758; s32 func_8821B778(void) { s32 result = 0; if (D_88234758 & 1) { result = 1; } return result; }

extern u16 D_88234758; s32 func_8821B79C(void) { s32 result = 0; if (D_88234758 & 2) { result = 1; } return result; }

extern u16 D_88234758; s32 func_8821B7C0(void) { s32 result = 0; if (D_88234758 & 4) { result = 1; } return result; }

extern u16 D_88234758; s32 func_8821B7E4(u8 arg0) { s32 result = 0; if (D_88234758 & 0x10) { if (((u8 *)&D_88234758)[4] == arg0) result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821B81C.s")

extern u16 D_88234758; extern u8 D_882347B8[]; s32 func_8821B884(u8 arg0) { s32 result = 0; if (D_88234758 & 0x40) { if (((u8 *)&D_88234758)[0xD] == D_882347B8[arg0]) result = 1; } return result; }

extern u16 D_88234758; s32 func_8821B8C8(void) { s32 result = 0; if (D_88234758 & 0x80) { result = 1; } return result; }

extern u16 D_88234758; typedef struct { u16 flags; u8 pad[14]; u32 value; } State_8821B8EC_rev; s32 func_8821B8EC(u8 arg0) { s32 result = 0; if (D_88234758 & 0x100) { if (arg0 == ((State_8821B8EC_rev *)&D_88234758)->value) result = 1; } return result; }

extern u16 D_88234758; typedef struct { u16 flags; u8 pad[18]; u32 value; } State_8821B924_rev; s32 func_8821B924(u8 arg0) { s32 result = 0; if (D_88234758 & 0x200) { if (arg0 == ((State_8821B924_rev *)&D_88234758)->value) result = 1; } return result; }

extern u16 D_88234758; s32 func_8821B95C(void) { s32 result = 0; if (D_88234758 & 0x400) { result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821B980.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821B9EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821BA34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821C004.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821C0B0.s")

extern s32 D_88234778; extern void func_8821C0B0(void); void func_8821C298(void) { if (D_88234778 == 0x10) func_8821C0B0(); }

extern u32 D_882347B4; extern u8 D_8823474D; void func_8821C2C8(s32 arg0) { if (D_882347B4 != arg0) { D_882347B4 = arg0; D_8823474D = 2; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821C2F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821C39C.s")
#endif
