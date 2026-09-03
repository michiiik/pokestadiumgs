#include "global.h"


#ifdef VERSION_US
extern s32 func_8003514C(void);
extern u8 D_80097380[];
extern u8 D_80097480[];
extern u8 D_80097580[];
extern u8 *D_80097680;
void func_800609D0(void) {
    s32 mode;
    mode = func_8003514C();
    switch (mode) {
    case 1:
        D_80097680 = D_80097380;
        break;
    case 2:
    case 3:
        D_80097680 = D_80097480;
        break;
    case 4:
    case 5:
        D_80097680 = D_80097580;
        break;
    }
}

u16 func_80060A4C(const u8* arg0) {
    return (u16)((arg0[0] << 8) | arg0[1]);
}

u32 GbData_ReadU24BE(const u8 *arg0) { return ((u32)arg0[0] << 16) | ((u32)arg0[1] << 8) | arg0[2]; }

void func_80060A84(u8* arg0, s32 arg1) { arg0[0] = (arg1 >> 8) & 0xFF; arg0[1] = arg1 & 0xFF; }

void GbData_WriteU24BE(u8 *arg0, s32 arg1) {
    arg0[0] = (arg1 >> 16) & 0xFF;
    arg0[1] = (arg1 >> 8) & 0xFF;
    arg0[2] = arg1 & 0xFF;
}

u8 func_80060AAC(u8 arg0) { extern u8 *D_80097680; return D_80097680[arg0]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060AC8.s")

s32 func_80060B28(u8 arg0) {
    u8 i;
    for (i = 0; i < 0x100; i++) {
        if (arg0 == D_80097680[i]) {
            return i;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060C08.s")

s8 *func_80060C50(s8 *arg0, u8 *arg1) {
    s8 *result;
    result = arg0;
    while (*arg1 != 0x50) {
        *arg0 = D_80097680[*arg1];
        arg0++;
        arg1++;
    }
    *arg0 = 0;
    return result;
}

extern u8 func_80060AC8(u8, s32);
s8 *func_80060C98(s8 *arg0, u8 *arg1, s32 arg2) {
    s8 *result;
    result = arg0;
    while (*arg1 != 0x50) {
        *arg0++ = func_80060AC8(*arg1++, arg2);
    }
    *arg0 = 0;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060D1C.s")

u8 *func_80060D70(u8 *arg0, s8 *arg1) {
    u8 *result;
    result = arg0;
    while (*arg1 != 0) {
        *arg0++ = func_80060B28(*arg1++);
    }
    *arg0 = 0x50;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80060DDC.s")

extern void _bcopy(const void *, void *, s32);
extern void func_80060C08(void *, void *);
extern void func_80060D1C(void *, void *);
extern void func_80060EC8(void *, void *);
extern s32 func_8004B7A4(s32);
extern void func_80062808(void *, s32);
extern void func_80062884(void *, s32);
extern void func_80062978(void *, s32);
void func_80060E48(void *arg0, void *arg1) {
    u8 sp1C[11];
    _bcopy(arg1, sp1C, 0xA);
    sp1C[0xA] = 0x50;
    func_80060C08(arg0, sp1C);
}

void func_80060E88(void *arg0, void *arg1) {
    u8 sp1C[11];
    _bcopy(arg1, sp1C, 0xA);
    sp1C[0xA] = 0x50;
    func_80060D1C(arg0, sp1C);
}

extern char * func_80060F68(char *arg0, char *arg1);
void func_80060EC8(void *arg0, void *arg1) {
    char sp1C[11];
    func_80060D70(arg0, func_80060F68(sp1C, arg1));
}

void func_80060EF8(void *arg0, void *arg1) {
    u8 sp1C[9];
    _bcopy(arg1, sp1C, 8);
    sp1C[8] = 0x50;
    func_80060C08(arg0, sp1C);
}

extern char * func_80060F68(char *arg0, char *arg1);
void func_80060F38(void *arg0, void *arg1) {
    char sp1C[19];
    func_80060D70(arg0, func_80060F68(sp1C, arg1));
}

extern char *HAL_Strcpy(char *, char *); char *func_80060F68(char *arg0, char *arg1) { return HAL_Strcpy(arg0, arg1); }

s32 func_80060F88(void) { return 0x46; }

s32 func_80060F90(void) { return 0; }

extern u8 D_80097684[];
u8 func_80060F98(u8 arg0) {
    u8 *entry;
    entry = D_80097684;
    if (arg0 == 0) {
        return 0;
    }
    while (entry[0] != 0) {
        if (arg0 == entry[0]) {
            return entry[1];
        }
        entry += 2;
    }
    return arg0;
}

extern s32 func_80062008(s32);
void func_80060FF8(u8 *arg0, u8 *arg1) {
    s32 i;
    u8 *src;
    u8 *dst;
    u8 value;
    arg0[0] = func_80062008(arg1[0]);
    arg0[1] = func_80060F98(arg1[7]);
    *(u16 *)(arg0 + 0x26) = func_80060A4C(arg1 + 1);
    arg0[0x24] = arg1[4];
    *(u16 *)(arg0 + 6) = func_80060A4C(arg1 + 0xC);
    *(u32 *)(arg0 + 8) = GbData_ReadU24BE(arg1 + 0xE);
    *(u16 *)(arg0 + 0xC) = func_80060A4C(arg1 + 0x11);
    *(u16 *)(arg0 + 0xE) = func_80060A4C(arg1 + 0x13);
    *(u16 *)(arg0 + 0x10) = func_80060A4C(arg1 + 0x15);
    *(u16 *)(arg0 + 0x12) = func_80060A4C(arg1 + 0x17);
    *(u16 *)(arg0 + 0x14) = func_80060A4C(arg1 + 0x19);
    *(u16 *)(arg0 + 0x16) = func_80060A4C(arg1 + 0x1B);
    for (i = 0; i < 4; i++) {
        if (arg1[i + 8] == 0) {
            break;
        }
        arg0[i + 2] = arg1[i + 8];
        arg0[i + 0x18] = arg1[i + 0x1D];
    }
    for (; i < 4; i++) {
        arg0[i + 2] = 0;
        arg0[i + 0x18] = 0;
    }
    arg0[0x1C] = func_80060F88();
    arg0[0x20] = func_80060F90();
    arg0[0x21] = 0;
    arg0[0x22] = 0;
}

extern s32 func_80062030(s32);
void func_80061124(u8 *arg0, u8 *arg1) {
    s32 i;
    u8 *src;
    u8 *dst;
    u8 value;
    arg0[0] = func_80062030(arg1[0]);
    arg0[1] = arg1[1];
    arg0[0x24] = 0;
    *(u16 *)(arg0 + 6) = func_80060A4C(arg1 + 6);
    *(u32 *)(arg0 + 8) = GbData_ReadU24BE(arg1 + 8);
    *(u16 *)(arg0 + 0xC) = func_80060A4C(arg1 + 0xB);
    *(u16 *)(arg0 + 0xE) = func_80060A4C(arg1 + 0xD);
    *(u16 *)(arg0 + 0x10) = func_80060A4C(arg1 + 0xF);
    *(u16 *)(arg0 + 0x12) = func_80060A4C(arg1 + 0x11);
    *(u16 *)(arg0 + 0x14) = func_80060A4C(arg1 + 0x13);
    *(u16 *)(arg0 + 0x16) = func_80060A4C(arg1 + 0x15);
    for (i = 0; i < 4; i++) {
        if (arg1[i + 2] == 0) {
            break;
        }
        arg0[i + 2] = arg1[i + 2];
        arg0[i + 0x18] = arg1[i + 0x17];
    }
    for (; i < 4; i++) {
        arg0[i + 2] = 0;
        arg0[i + 0x18] = 0;
    }
    arg0[0x1C] = arg1[0x1B];
    arg0[0x1D] = arg1[0x1F];
    arg0[0x20] = arg1[0x1C];
    arg0[0x21] = arg1[0x1D];
    arg0[0x22] = arg1[0x1E];
}

void func_80061248(u8 *arg0, u8 *arg1) {
    _bcopy(arg1, arg0, 0x24);
    _bcopy(arg1 + 0x30, arg0 + 0x4C, 0xB);
    func_80060E88(arg0 + 0x34, arg1 + 0x24);
    func_80060E88(arg0 + 0x40, arg1 + 0x30);
    arg0[0x24] = 0;
}

extern s16 func_8006183C(s32, s32, s32, s32, s32);
void func_800612B8(u8 *arg0, u8 *arg1) {
    func_80060FF8(arg0, arg1);
    arg0[0x1D] = arg1[0x21];
    *(u16 *)(arg0 + 0x28) = func_80060A4C(arg1 + 0x22);
    *(u16 *)(arg0 + 0x26) = func_80060A4C(arg1 + 1);
    *(u16 *)(arg0 + 0x2A) = func_80060A4C(arg1 + 0x24);
    *(u16 *)(arg0 + 0x2C) = func_80060A4C(arg1 + 0x26);
    *(u16 *)(arg0 + 0x2E) = func_80060A4C(arg1 + 0x28);
    *(u16 *)(arg0 + 0x30) = func_8006183C(4, arg0[0], *(u16 *)(arg0 + 0x14), arg0[0x1D], *(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x32) = func_8006183C(5, arg0[0], *(u16 *)(arg0 + 0x14), arg0[0x1D], *(u16 *)(arg0 + 0x16));
}

void func_8006136C(u8 *arg0, u8 *arg1) {
    func_80061124(arg0, arg1);
    arg0[0x24] = arg1[0x20];
    *(u16 *)(arg0 + 0x28) = func_80060A4C(arg1 + 0x24);
    *(u16 *)(arg0 + 0x26) = func_80060A4C(arg1 + 0x22);
    *(u16 *)(arg0 + 0x2A) = func_80060A4C(arg1 + 0x26);
    *(u16 *)(arg0 + 0x2C) = func_80060A4C(arg1 + 0x28);
    *(u16 *)(arg0 + 0x2E) = func_80060A4C(arg1 + 0x2A);
    *(u16 *)(arg0 + 0x30) = func_80060A4C(arg1 + 0x2C);
    *(u16 *)(arg0 + 0x32) = func_80060A4C(arg1 + 0x2E);
}

extern s32 Species_ToInternalIndex(s32);
extern s32 func_8006397C(s32);
extern s32 func_800639C0(s32);
void func_800613F8(u8 *arg0, u8 *arg1) {
    arg0[0] = Species_ToInternalIndex(arg1[0]);
    func_80060A84(arg0 + 1, *(u16 *)(arg1 + 0x26));
    arg0[3] = arg1[0x1D];
    arg0[4] = arg1[0x24];
    arg0[5] = func_8006397C(arg1[0]);
    arg0[6] = func_800639C0(arg1[0]);
    arg0[7] = arg1[1];
    func_80060A84(arg0 + 0xC, *(u16 *)(arg1 + 6));
    GbData_WriteU24BE(arg0 + 0xE, *(u32 *)(arg1 + 8));
    func_80060A84(arg0 + 0x11, *(u16 *)(arg1 + 0xC));
    func_80060A84(arg0 + 0x13, *(u16 *)(arg1 + 0xE));
    func_80060A84(arg0 + 0x15, *(u16 *)(arg1 + 0x10));
    func_80060A84(arg0 + 0x17, *(u16 *)(arg1 + 0x12));
    func_80060A84(arg0 + 0x19, *(u16 *)(arg1 + 0x14));
    func_80060A84(arg0 + 0x1B, *(u16 *)(arg1 + 0x16));
    memcpy(arg0 + 8, arg1 + 2, 4);
    memcpy(arg0 + 0x1D, arg1 + 0x18, 4);
}

void func_800614EC(u8 *arg0, u8 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    func_80060A84(arg0 + 6, *(u16 *)(arg1 + 6));
    GbData_WriteU24BE(arg0 + 8, *(u32 *)(arg1 + 8));
    func_80060A84(arg0 + 0xB, *(u16 *)(arg1 + 0xC));
    func_80060A84(arg0 + 0xD, *(u16 *)(arg1 + 0xE));
    func_80060A84(arg0 + 0xF, *(u16 *)(arg1 + 0x10));
    func_80060A84(arg0 + 0x11, *(u16 *)(arg1 + 0x12));
    func_80060A84(arg0 + 0x13, *(u16 *)(arg1 + 0x14));
    func_80060A84(arg0 + 0x15, *(u16 *)(arg1 + 0x16));
    arg0[0x1B] = arg1[0x1C];
    arg0[0x1C] = arg1[0x20];
    arg0[0x1D] = arg1[0x21];
    arg0[0x1E] = arg1[0x22];
    arg0[0x1F] = arg1[0x1D];
    memcpy(arg0 + 2, arg1 + 2, 4);
    memcpy(arg0 + 0x17, arg1 + 0x18, 4);
}

void func_800615D0(void *arg0, void *arg1) {
    _bcopy(arg1, arg0, 0x24);
    _bcopy((u8 *)arg1 + 0x4C, (u8 *)arg0 + 0x30, 0xB);
    func_80060EC8((u8 *)arg0 + 0x24, (u8 *)arg1 + 0x34);
}

void func_8006162C(u8 *arg0, u8 *arg1) {
    func_800613F8(arg0, arg1);
    arg0[0x21] = arg1[0x1D];
    func_80060A84(arg0 + 0x22, *(u16 *)(arg1 + 0x28));
    func_80060A84(arg0 + 0x24, *(u16 *)(arg1 + 0x2A));
    func_80060A84(arg0 + 0x26, *(u16 *)(arg1 + 0x2C));
    func_80060A84(arg0 + 0x28, *(u16 *)(arg1 + 0x2E));
    func_80060A84(arg0 + 0x2A, func_8006183C(6, arg1[0], *(u16 *)(arg1 + 0x14), arg1[0x1D], *(u16 *)(arg1 + 0x16)));
}

void func_800616BC(u8 *arg0, u8 *arg1) {
    func_800614EC(arg0, arg1);
    arg0[0x20] = arg1[0x24];
    if (arg1[0x1E] & 1) {
        *(u16 *)(arg1 + 0x26) = 0;
    }
    func_80060A84(arg0 + 0x22, *(u16 *)(arg1 + 0x26));
    func_80060A84(arg0 + 0x24, *(u16 *)(arg1 + 0x28));
    func_80060A84(arg0 + 0x26, *(u16 *)(arg1 + 0x2A));
    func_80060A84(arg0 + 0x28, *(u16 *)(arg1 + 0x2C));
    func_80060A84(arg0 + 0x2A, *(u16 *)(arg1 + 0x2E));
    func_80060A84(arg0 + 0x2C, *(u16 *)(arg1 + 0x30));
    func_80060A84(arg0 + 0x2E, *(u16 *)(arg1 + 0x32));
}

u16 StatExpSqrt(u16 arg0) { u16 i; for (i = 1; i < 255; i++) { if ((i * i) >= arg0) break; } return i; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006179C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006183C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061940.s")

extern u8 func_80061ED0(u8, s32);
void func_800619E8(u8 *arg0) {
    u8 value;
    value = func_80061ED0(arg0[0], *(s32 *)(arg0 + 8));
    arg0[0x1D] = value;
    *(u16 *)(arg0 + 0x28) = func_8006183C(0, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0xC), value & 0xFF, (s32)*(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x2A) = func_8006183C(1, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0xE), (s32)arg0[0x1D], (s32)*(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x2C) = func_8006183C(2, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0x10), (s32)arg0[0x1D], (s32)*(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x2E) = func_8006183C(3, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0x12), (s32)arg0[0x1D], (s32)*(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x30) = func_8006183C(4, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0x14), (s32)arg0[0x1D], (s32)*(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x32) = func_8006183C(5, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0x14), (s32)arg0[0x1D], (s32)*(u16 *)(arg0 + 0x16));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061ADC.s")

extern u8 func_80063A04(u8);
s32 func_80061B88(s32 arg0, u16 arg1) {
    s32 sp1C;
    u8 temp_v0;
    temp_v0 = func_80063A04(arg0 & 0xFF);
    switch (temp_v0) {
    case 0: sp1C = arg1 * arg1 * arg1; break;
    case 1: sp1C = (((s32)(arg1 * arg1 * arg1 * 3) / 4) + (arg1 * 0xA * arg1)) - 0x1E; break;
    case 2: sp1C = (((s32)(arg1 * arg1 * arg1 * 3) / 4) + (arg1 * 0x14 * arg1)) - 0x46; break;
    case 3: sp1C = ((((s32)(arg1 * arg1 * arg1 * 6) / 5) - (arg1 * 0xF * arg1)) + (arg1 * 0x64)) - 0x8C; break;
    case 4: sp1C = (s32)(arg1 * arg1 * arg1 * 4) / 5; break;
    case 5: sp1C = (s32)(arg1 * arg1 * arg1 * 5) / 4; break;
    }
    return sp1C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061D8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80061ED0.s")

extern u8 func_80062EB0(u8, u8);
void func_80061F44(u8 *arg0) {
    s32 i;
    u8 *p;

    *(u16 *)(arg0 + 0x26) = *(u16 *)(arg0 + 0x28);
    arg0[0x24] = 0;
    p = arg0;
    i = 0;
    do {
        if (p[2] != 0) {
            p[0x18] = func_80062EB0(p[2], p[0x18]);
        }
        i++;
        p++;
    } while (i != 4);
}

extern s32 _bcmp(const void *, const void *, s32); s32 GbSave_PlayerIdentityMatches(const void *a, const void *b) { return _bcmp(a, b, 0xD) == 0; }

extern u8 D_800976A0[]; u8 func_80061FD0(s32 index) { return D_800976A0[index]; }

extern u8 D_800976D7[];
s32 Species_ToInternalIndex(s32 index) { if (index <= 0 || index >= 0x98) return 0; return D_800976D7[index]; }

extern u8 D_8009776F[];
s32 func_80062008(s32 index) { if (index <= 0 || index >= 0xBF) return 0xFC; return D_8009776F[index]; }

s32 func_80062030(s32 value) { if (value > 0 && value < 0xFC) return value; return 0xFC; }

extern void func_80053808(s32, s32, s32);
extern s32 func_800532F0(s32);
extern s32 func_80053230(s32);
extern s32 func_8005370C(s32, s32);
void func_80062054(u8 *arg0) {
    u8 *s0;
    s0 = arg0;
    if (arg0[0] == 1) {
        arg0[4] = arg0[4] | 1;
        func_80053808(arg0[1], arg0[3], 0);
    }
    *(u16 *)(s0 + 8) = func_800532F0(s0[1]);
    *(u16 *)(s0 + 6) = func_80053230(s0[1]);
    s0[5] = func_8005370C(s0[1], s0[3]);
    if (s0[0] == 2) {
        *(u16 *)(s0 + 0xA) = s0[5];
    } else {
        *(u16 *)(s0 + 0xA) = 0;
    }
}

extern void func_8005D2BC(s32, s32, s32, s32);
extern s32 func_8005CBA0(s32);
extern s32 func_8005CAA4(s32);
extern s32 func_8005CF20(s32, s32, s32);
void func_800620E8(u8 *arg0) {
    u8 *s0;
    s0 = arg0;
    if (s0[0] == 1) {
        func_8005D2BC(s0[1], s0[2], s0[3], 0);
    }
    if (s0[0] != 0) {
        s0[4] = s0[4] | 1;
    }
    *(u16 *)(s0 + 8) = func_8005CBA0(s0[1]);
    *(u16 *)(s0 + 6) = func_8005CAA4(s0[1]);
    s0[5] = func_8005CF20(s0[1], s0[2], s0[3]);
    if (s0[0] == 2) {
        *(u16 *)(s0 + 0xA) = s0[5];
    } else {
        *(u16 *)(s0 + 0xA) = 0;
    }
}

extern void *Util_Malloc(s32);
extern void func_80062054(u8 *);
extern void func_800620E8(u8 *);
u8 *func_8006218C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v1;
    u8 *temp_v0;
    u8 *var_s0;
    var_s0 = NULL;
    if ((arg1 >= 0) && (arg1 < 4)) {
        temp_v0 = Util_Malloc(0xC);
        var_s0 = temp_v0;
        if (temp_v0 != NULL) {
            temp_v0[0] = arg3;
            temp_v0[1] = arg0;
            temp_v0[2] = arg1;
            temp_v0[3] = arg2;
            temp_v1 = arg0 & 0xF0;
            temp_v0[4] = 0;
            switch (temp_v1) {
            case 16:
                func_80062054(var_s0);
                break;
            case 32:
                func_800620E8(var_s0);
                break;
            }
        }
    }
    return var_s0;
}

typedef struct S1_DeckHandle {
    /* 0x00 */ u8 mode; // func_8006218C's arg3; ==1 selected by Deck_Initialize*Backend to reset the entry count
    /* 0x01 */ u8 deckType; // func_8006218C's arg0; high nibble dispatches Deck_InitializeSaveBackend(0x10)/InitializeBoxBackend(0x20)
    /* 0x02 */ u8 port; // func_8006218C's arg1
    /* 0x03 */ u8 slot; // func_8006218C's arg2 (box/save-record index)
    /* 0x04 */ u8 dirty; // bit 0 set when the deck was modified; checked by Deck_CloseAndFlush/CloseAndFlushBox to decide whether to commit
    /* 0x05 */ u8 recordSize; // Deck_GetSaveRecordSize/Deck_GetEntrySize
    /* 0x06 */ s16 capacity; // Deck_GetSaveRecordCapacity/Deck_GetCapacity
    /* 0x08 */ s16 count; // Deck_GetSaveEntryCount/Deck_GetCount
    /* 0x0A */ s16 cursor; // Deck_SetCursor
} S1_DeckHandle;
S1_DeckHandle* Deck_OpenAndSetName(s32 arg0, s32 arg1, s32 arg2, s32 arg3, char* arg4, u16 arg5) {
    S1_DeckHandle* sp24;
    S1_DeckHandle* temp_v0;
    S1_DeckHandle* var_v1;

    sp24 = func_8006218C(arg0, arg1, arg2, 1);
    if ((sp24 != NULL) && (arg0 & 0xF0)) {
        func_800535D4(arg0, arg2, arg3, arg4, arg5);
    }
    return sp24;
}

extern void func_80052150(s32, s32); extern void Util_Free(void *);
s32 func_8006229C(u8 *arg0) { s32 result = 0; if ((arg0[1] & 0x10) && (arg0[4] & 1)) { func_80052150(arg0[1], arg0[3]); result = 1; } Util_Free(arg0); return result; }

extern s32 func_80051D64(s32, s32);
extern void Util_Free(void *);
s32 func_80062304(u8 *arg0) { s32 result = 0; if ((arg0[1] & 0x10) && (arg0[4] & 1)) { func_80051D64(arg0[1], arg0[3]); result = 1; } Util_Free(arg0); return result; }

s32 func_8006236C(u8 *arg0, s32 arg1) { s32 result = 0; if (arg0[5] >= arg1) { *(u16 *)(arg0 + 10) = arg1; result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_8006249C.s")

s32 func_800625E0(s32 arg0, s32 arg1) {
    extern char *func_80060F68(char *, char *);
    func_80060F68(arg0, func_8004B7A4(arg1));
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062614.s")

void func_8006276C(s32 arg0, s32 arg1) {
    s32 pad_frame[2];
    s32 sp24;

    func_80060EC8(&sp24, arg1 + 0x66);
    _bcopy(arg1 + 0x44, (void *) arg0, 0x21);
    _bcopy(&sp24, arg0 + 0x21, 8);
    _bcopy(arg1 + 0x42, arg0 + 0x29, 2);
    func_80060A84(arg0 + 0x2B, (s32) (*(u16 *)((u8 *)(arg1) + (0x72))));
    (*(u8 *)((u8 *)(arg0) + (0x2D))) = (u8) (*(u8 *)((u8 *)(arg1) + (0x74)));
    (*(u8 *)((u8 *)(arg0) + (0x2E))) = (u8) (*(u8 *)((u8 *)(arg1) + (0x75)));
}

void func_800627F0(s32 arg0, s32 arg1) {}

void func_800627FC(s32 arg0, s32 arg1) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062808.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062884.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062978.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062BD4.s")

s32 func_80062C18(s32 arg0) { return 1; }

s32 func_80062C24(s32 arg0) { return 1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/615D0/func_80062C30.s")
#endif
