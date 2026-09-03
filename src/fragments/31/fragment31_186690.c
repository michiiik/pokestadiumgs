#include "global.h"


#ifdef VERSION_US
extern u8 *D_88234564;
extern void Util_Free(void *);
extern void main_pool_pop_state(s32);
extern void func_8821CE40(s32);
extern s32 D_88234560;
void func_88213410(void) {
    Util_Free(D_88234564);
    main_pool_pop_state(0x4D41494C);
    func_8821CE40(4);
    D_88234560 = 5;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88213450.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88213530.s")

extern u8 *D_88234730;
u8 *func_88213A3C(s32 arg0) { switch (arg0) { case 3: return D_88234730 + 0xC4; case 4: return D_88234730 + 0xF8; case 5: return D_88234730 + 0x12C; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88213A94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88213BE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88213E9C.s")

extern void func_882064B4(s32, u8 *, u8 *, u8 *);
extern void func_88213A94(u8, s32);
extern s32 D_882346F0;
extern u8 *D_88234730;
void func_882142DC(void) {
    D_882346F0 = 4;
    func_882064B4(0, D_88234730 + 4, D_88234730 + 0xC, D_88234730 + 0x38);
    func_88213A94(*D_88234730, 1);
}

extern void func_88213BE4(s32, s32);
extern void func_88220E08(s32);
extern s32 D_880068B4;
void func_88214330(void) {
    s16 temp_v0;

    temp_v0 = (*(s16 *)((u8 *)(D_88234730) + (8)));
    switch (temp_v0) {                              /* irregular */
    case 3:
        func_88220E08(1);
        return;
    case 5:
        D_880068B4 = 1;
        func_88213BE4(0x12, 0);
        return;
    }
}

extern void func_800226C0(s32);
void func_88214394(void) {
    s16 temp_v0;

    temp_v0 = (*(s16 *)((u8 *)(D_88234730) + (8)));
    switch (temp_v0) {                              /* irregular */
    case 3:
        func_800226C0(0x5C);
        return;
    case 5:
        func_800226C0(0x5D);
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882143EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882152F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88215420.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882157DC.s")

extern void func_800496A4(s32, s32); extern void func_80049064(s32, s32, s32, s32); extern s32 func_8003514C(void); extern void func_882157DC(s8 *, s8 *, s32); extern void func_80047634(s32); extern s32 D_8800687C; extern void func_80048E30(s32, s16, s16, s32, s32); extern void func_80047650(s32);
void func_882158E4(s16 arg0, s16 arg1, s8 *arg2) { s8 temp[0x44]; s32 count; if (arg2[0x66] != 0) { func_800496A4(4, 1); func_80049064(arg0 + 0xD3, arg1 + 4, 2, arg2 + 0x66); if (func_8003514C() == 0) count = 6; else count = 0xC; func_882157DC(temp + 4, arg2, count); func_800496A4(8, 2); func_80047634(1); func_80048E30(D_8800687C, arg0, arg1, temp + 4, 1); func_80047650(1); } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882159A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88215BCC.s")

extern void func_800496A4(s32, s32); extern s32 func_8004C874(s32, s16); extern void func_80049064(s32, s32, s32, s32); extern s16 D_8800EF58; extern s32 D_882346F0; extern u8 *D_88234730;
void func_88215C4C(void) { if (D_8800EF58 == 0) { if (D_882346F0 == 0) { func_800496A4(4, 2); func_80049064(0x140, 0x198, 1, func_8004C874(0x23, 7)); } } func_800496A4(0x10, 2); func_80049064(0x140, 0x15F, 1, func_8004C874(0x23, *(s16 *)(D_88234730 + 8))); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88215CE0.s")

extern u8 *func_88213450(s32, u8); extern void func_8004989C(s32); extern void func_80049668(s32); extern void func_800495F8(s32, s32, s32, void *, s32); extern u8 D_88233F88[];
extern void func_80047634(s32);
extern void func_80047650(s32);
extern void func_80048E30(s32, s16, s16, s32, s32);
extern void func_80049064(s32, s32, s32, s32);
extern s32 func_8004C874(s32, s16);
void func_88215D4C(void) { u8 *p; p = func_88213450(1, *D_88234730); if (((s8 *)p)[0x66] != 0) { func_8004989C(0x20); func_800496A4(0x10, 2); func_80047634(1); func_80049064(0x13F, 0x154, 1, (s32)p); func_80047650(1); func_800496A4(8, 1); func_80048E30(D_8800687C, 0xD5, 0x196, (s32)(p + 0x66), 1); func_800496A4(4, 1); func_80048E30(D_8800687C, 0x13E, 0x19A, func_8004C874(0xD, 9), 1); func_80049668(0); func_800495F8(0x161, 0x19A, 0, D_88233F88, *(u16 *)(p + 0x72)); } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88215E54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_882160F8.s")

void func_882164E0(void) {
    Util_Free(D_88234564);
    main_pool_pop_state(0x4C495354);
    func_8821CE40(0);
    D_88234560 = 5;
}

extern void func_88200134(s32, s32);
void func_88216520(void) { func_88200134(0, 2); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88216544.s")

extern u8 *D_88234740;
u8 *func_88216D54(s32 arg0) { switch (arg0) { case 0: case 1: return D_88234740 + 0xC4; case 2: return D_88234740 + 0xF8; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88216D98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_88216E28.s")

s32 func_88200D04(s32);
s32 func_88201F0C();
s32 func_88228BCC(s32, s32, void (*)());
s32 func_88228F30(s32, s32, void (*)());
s32 func_882295E4(s32, s32, void (*)());

void func_88216E80(void) {
    if (func_88201F0C() != 0) {
        func_88228F30(0x17C, 0x11F, func_88216520);
        return;
    }
    if (func_88200D04(7) != 0) {
        func_882295E4(0x17C, 0x11F, func_88216520);
        return;
    }
    func_88228BCC(0x17C, 0x11F, func_88216520);
}

extern u8 *D_88234740;
extern u8 D_88006880[];
extern void *D_80087200;
extern void func_880022B4(void *, s32, s32);
extern void func_88001900(void);
extern void Input_SetRepeatController(void *);
void func_88216EFC(void *arg0) {
    if (*(void **)D_88234740 != arg0) {
        *(void **)D_88234740 = arg0;
        if (arg0 != 0) {
            func_880022B4(D_88006880, 0xF00, 1);
            func_88001900();
        } else {
            func_880022B4(D_88006880, 0xF00, 0);
            Input_SetRepeatController(D_80087200);
        }
    }
}

extern void func_800226C0(s32); extern void *D_80087200; extern u8 *D_88234740; extern s8 D_88234746; extern u8 D_882338A4[];
void func_88216F74(void) { func_800226C0(0x4B); if ((*(u16 *)((u8 *)D_80087200 + 8) & 2) != 0) { D_88234746--; if (D_88234746 < 0) D_88234746 = 3; } else if ((*(u16 *)((u8 *)D_80087200 + 8) & 1) != 0) { D_88234746++; if (D_88234746 >= 4) D_88234746 = 0; } if (D_882338A4[D_88234746] + 1 < ((s8 *)D_88234740)[4]) D_88234740[4] = D_882338A4[D_88234746] + 1; }

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

extern void func_8821B3E0(void);
extern s32 D_88234778;
extern s32 D_8823477C;
void func_8821B438(void) {
    func_8821B3E0();
    D_88234778 = 0;
    D_8823477C = 1;
}

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

extern u16 D_88234758;
s32 func_8821B81C(s8 arg0, s8 arg1) {
    s32 result = 0;
    if ((D_88234758 & 8) &&
        (((arg0 == ((s8 *)&D_88234758)[5]) && (arg1 == ((s8 *)&D_88234758)[6])) ||
         ((arg1 == ((s8 *)&D_88234758)[5]) && (arg0 == ((s8 *)&D_88234758)[6])))) result = 1;
    return result;
}

extern u16 D_88234758; extern u8 D_882347B8[]; s32 func_8821B884(u8 arg0) { s32 result = 0; if (D_88234758 & 0x40) { if (((u8 *)&D_88234758)[0xD] == D_882347B8[arg0]) result = 1; } return result; }

extern u16 D_88234758; s32 func_8821B8C8(void) { s32 result = 0; if (D_88234758 & 0x80) { result = 1; } return result; }

extern u16 D_88234758; typedef struct { u16 flags; u8 pad[14]; u32 value; } State_8821B8EC_rev; s32 func_8821B8EC(u8 arg0) { s32 result = 0; if (D_88234758 & 0x100) { if (arg0 == ((State_8821B8EC_rev *)&D_88234758)->value) result = 1; } return result; }

extern u16 D_88234758; typedef struct { u16 flags; u8 pad[18]; u32 value; } State_8821B924_rev; s32 func_8821B924(u8 arg0) { s32 result = 0; if (D_88234758 & 0x200) { if (arg0 == ((State_8821B924_rev *)&D_88234758)->value) result = 1; } return result; }

extern u16 D_88234758; s32 func_8821B95C(void) { s32 result = 0; if (D_88234758 & 0x400) { result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821B980.s")

extern u8 *D_88234750;
u32 func_8821B9EC(s32 arg0) {
    u8 *p = (u8 *)D_88234750;
    u32 i = 0;

    if (D_88234744) {
        do {
            if (arg0 == *(s32 *)p)
                return i;
            p += 4;
            i++;
        } while (i < (u16)D_88234744);
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821BA34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821C004.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821C0B0.s")

extern s32 D_88234778; extern void func_8821C0B0(void); void func_8821C298(void) { if (D_88234778 == 0x10) func_8821C0B0(); }

extern u32 D_882347B4; extern u8 D_8823474D; void func_8821C2C8(s32 arg0) { if (D_882347B4 != arg0) { D_882347B4 = arg0; D_8823474D = 2; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821C2F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_186690/func_8821C39C.s")
#endif
