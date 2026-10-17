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

u8 GbText_DecodeCharForMode(u8 value, s32 mode) {
    u8 *table;
    table = D_80097680;
    switch (mode) {
    case 1:
        table = D_80097380;
        break;
    case 2:
    case 3:
        table = D_80097480;
        break;
    case 4:
    case 5:
        table = D_80097580;
        break;
    }
    return table[value];
}

s32 func_80060B28(u8 arg0) {
    u8 i;
    for (i = 0; i < 0x100; i++) {
        if (arg0 == D_80097680[i]) {
            return i;
        }
    }
    return 0;
}

s32 GbText_EncodeCharForMode(u8 value, s32 mode) {
    u8 *table;
    //!bug: the byte index wraps forever if value is absent from the table.
    u8 i;
    table = D_80097680;
    switch (mode) {
    case 1:
        table = D_80097380;
        break;
    case 2:
    case 3:
        table = D_80097480;
        break;
    case 4:
    case 5:
        table = D_80097580;
        break;
    }
    for (i = 0; i < 0x100; i++) {
        if (value == table[i]) {
            return i;
        }
    }
    return 0;
}

extern u8 * D_80097680;
s8 *func_80060C08(s8 *arg0, u8 *arg1) {
    s8 *result;
    result = arg0;
    while (*arg1 != 0x50) {
        *arg0++ = D_80097680[*arg1++];
    }
    *arg0 = 0;
    return result;
}

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

s8 *func_80060C98(s8 *arg0, u8 *arg1, s32 arg2) {
    s8 *result;
    result = arg0;
    while (*arg1 != 0x50) {
        *arg0++ = GbText_DecodeCharForMode(*arg1++, arg2);
    }
    *arg0 = 0;
    return result;
}

extern void *func_8004C874(s32, s32);
extern s8 *HAL_Strcpy(s8 *, s8 *);
s8 *func_80060D1C(s8 *arg0, u8 *arg1) {
    if (arg1[0] == 0x5D) {
        HAL_Strcpy(arg0, (s8 *)func_8004C874(0x41, 2));
        return arg0;
    } else {
        return func_80060C08(arg0, arg1);
    }
}

u8 *func_80060D70(u8 *arg0, s8 *arg1) {
    u8 *result;
    result = arg0;
    while (*arg1 != 0) {
        *arg0++ = func_80060B28(*arg1++);
    }
    *arg0 = 0x50;
    return result;
}

extern s32 HAL_Strcmp(const s8 *, const s8 *);
extern u8 *func_80060EC8(void *, void *);
u8 *func_80060DDC(u8 *arg0, s8 *arg1) {
    u8 *result;

    if (HAL_Strcmp(arg1, (s8 *)func_8004C874(0x41, 2)) == 0) {
        result = arg0;
        *arg0++ = 0x5D;
        *arg0 = 0x50;
        return result;
    } else {
        return func_80060EC8(arg0, arg1);
    }
}

extern void _bcopy(const void *, void *, s32);
extern s8 *func_80060C08(s8 *, u8 *);
extern s8 *func_80060D1C(s8 *, u8 *);
extern u8 *func_80060EC8(void *, void *);
extern s32 func_8004B7A4(s32);
extern void Pokemon_ValidateSpeciesForGbPort(void *, u8);
extern void Pokemon_ValidateMovesForGbPort(void *, u8);
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
u8 *func_80060EC8(void *arg0, void *arg1) {
    char sp1C[11];
    return func_80060D70(arg0, (s8 *)func_80060F68(sp1C, arg1));
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

extern s8 *HAL_Strcpy(s8 *, s8 *); char *func_80060F68(char *arg0, char *arg1) { return (char *)HAL_Strcpy((s8 *)arg0, (s8 *)arg1); }

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

extern u32 Pokemon_CalculateStat(s32, s32, u16, u16, u16);
void func_800612B8(u8 *arg0, u8 *arg1) {
    func_80060FF8(arg0, arg1);
    arg0[0x1D] = arg1[0x21];
    *(u16 *)(arg0 + 0x28) = func_80060A4C(arg1 + 0x22);
    *(u16 *)(arg0 + 0x26) = func_80060A4C(arg1 + 1);
    *(u16 *)(arg0 + 0x2A) = func_80060A4C(arg1 + 0x24);
    *(u16 *)(arg0 + 0x2C) = func_80060A4C(arg1 + 0x26);
    *(u16 *)(arg0 + 0x2E) = func_80060A4C(arg1 + 0x28);
    *(u16 *)(arg0 + 0x30) = Pokemon_CalculateStat(4, arg0[0], *(u16 *)(arg0 + 0x14), arg0[0x1D], *(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x32) = Pokemon_CalculateStat(5, arg0[0], *(u16 *)(arg0 + 0x14), arg0[0x1D], *(u16 *)(arg0 + 0x16));
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
    func_80060A84(arg0 + 0x2A, Pokemon_CalculateStat(6, arg1[0], *(u16 *)(arg1 + 0x14), arg1[0x1D], *(u16 *)(arg1 + 0x16)));
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

u16 Pokemon_GetDVForStat(s32 stat, u16 dvs) {
    //!bug: stat values outside 0..6 leave result uninitialized.
    u16 result;
    switch (stat) {
    case 0:
        result = ((dvs & 0x1000) >> 9) | ((dvs & 0x100) >> 6) | ((dvs & 0x10) >> 3) | (dvs & 1);
        break;
    case 1:
        result = (dvs >> 12) & 0xF;
        break;
    case 2:
        result = (dvs >> 8) & 0xF;
        break;
    case 3:
        result = (dvs >> 4) & 0xF;
        break;
    case 4:
    case 5:
    case 6:
        result = dvs & 0xF;
        break;
    }
    return result;
}

extern u8 func_80063838(u8, u8);
u32 Pokemon_CalculateStat(s32 stat, s32 species, u16 stat_exp, u16 level, u16 dvs) {
    u16 result;
    u16 base;
    u16 dv;
    s32 effort;
    base = func_80063838((u8)species, (u8)stat);
    dv = Pokemon_GetDVForStat(stat, dvs);
    effort = StatExpSqrt(stat_exp);
    if (stat == 0) {
        result = (((effort / 4) + (base + dv) * 2) * level) / 100;
        result += level + 10;
    } else {
        result = ((((effort / 4) + (base + dv) * 2) * level) / 100) + 5;
    }
    if (result >= 1000) {
        result = 999;
    }
    return result;
}

u16 Pokemon_ClampCurrentStat(s32 stat, s32 species, u16 stat_exp, u16 level, u16 dvs, u16 current) {
    struct {
        u16 minimum;
        s32 maximum;
    } limits;

    func_80063838((u8)species, (u8)stat);
    Pokemon_GetDVForStat(stat, dvs);
    limits.minimum = Pokemon_CalculateStat(stat, species, 0, level, dvs);
    limits.maximum = Pokemon_CalculateStat(stat, species, stat_exp, level, dvs);
    if (limits.maximum < current) {
        current = limits.maximum;
    }
    if (current < limits.minimum) {
        current = limits.minimum;
    }
    return current;
}

extern u16 Pokemon_LevelFromExp(s32, s32);
void func_800619E8(u8 *arg0) {
    arg0[0x1D] = Pokemon_LevelFromExp(arg0[0], *(s32 *)(arg0 + 8));
    *(u16 *)(arg0 + 0x28) = Pokemon_CalculateStat(0, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0xC), arg0[0x1D], (s32)*(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x2A) = Pokemon_CalculateStat(1, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0xE), (s32)arg0[0x1D], (s32)*(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x2C) = Pokemon_CalculateStat(2, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0x10), (s32)arg0[0x1D], (s32)*(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x2E) = Pokemon_CalculateStat(3, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0x12), (s32)arg0[0x1D], (s32)*(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x30) = Pokemon_CalculateStat(4, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0x14), (s32)arg0[0x1D], (s32)*(u16 *)(arg0 + 0x16));
    *(u16 *)(arg0 + 0x32) = Pokemon_CalculateStat(5, (s32)arg0[0], (s32)*(u16 *)(arg0 + 0x14), (s32)arg0[0x1D], (s32)*(u16 *)(arg0 + 0x16));
}

u16 Pokemon_StatExpForTarget(s32 stat, s32 species, u16 target, u16 level, u16 dvs) {
    s32 i;
    s32 value;
    for (i = 1; i < 0xFFFF; i += 2) {
        value = Pokemon_CalculateStat(stat, species, (u16)(i + 2), level, dvs);
        if (target < value) {
            break;
        }
    }
    return i;
}

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

u8 Pokemon_LevelFromExpWithHint(s32 species, u32 experience, u8 level) {
    u8 lower = 2;
    u8 upper = 101;
    u32 current_exp;
    u32 next_exp;
    if (level < 2) {
        level = 2;
    }
    if (level > 100) {
        level = 100;
    }
    while (1) {
        current_exp = func_80061B88(species, level);
        next_exp = func_80061B88(species, level + 1);
        if (experience < current_exp) {
            upper = level;
            level = (level + lower) / 2;
            if (level < 3) {
                level = 2;
                break;
            }
        } else if (next_exp < experience) {
            lower = level;
            level = (upper + level) / 2;
            if (level >= 100) {
                level = 100;
                break;
            }
        } else {
            if (experience == next_exp) {
                level++;
                if (level > 100) {
                    level = 100;
                }
            }
            break;
        }
    }
    return level;
}

u16 Pokemon_LevelFromExp(s32 species, s32 experience) {
    s32 i;
    for (i = 2; i < 100; i++) {
        if ((u32)experience < (u32)func_80061B88(species, (u16)(i + 1))) {
            break;
        }
    }
    return i;
}

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

extern s32 func_80053B38(s32, s32, s32, u8 *);
extern s32 func_8005D698(s32, s32, s32, s32, u8 *);
s32 Deck_ReadEntries(u8 *buffer, s32 remaining, u8 *handle) {
    s32 cursor;
    s32 success;
    s32 transferred = 0;
    while (remaining-- > 0 && ((cursor = *(s16 *)(handle + 10)) < handle[5])) {
        success = 0;
        switch (handle[1] & 0xF0) {
        case 0x10:
            success = func_80053B38(handle[1], handle[3], cursor, buffer);
            break;
        case 0x20:
            success = func_8005D698(handle[1], handle[2], handle[3], cursor, buffer);
            break;
        }
        if (success == 0) {
            break;
        }
        (*(s16 *)(handle + 10))++;
        transferred++;
        buffer += *(s16 *)(handle + 8);
    }
    return transferred;
}

extern s32 func_80053F04(s32, s32, s32, u8 *);
extern s32 func_8005D778(s32, s32, s32, s32, u8 *);
extern s32 func_8005370C(s32, s32);
extern s32 func_8005CF20(s32, s32, s32);
s32 Deck_WriteEntries(u8 *buffer, s32 remaining, u8 *handle) {
    s32 cursor;
    s32 success;
    s32 transferred = 0;
    while (remaining-- > 0 && ((cursor = *(s16 *)(handle + 10)) < *(s16 *)(handle + 6))) {
        success = 0;
        switch (handle[1] & 0xF0) {
        case 0x10:
            success = func_80053F04(handle[1], handle[3], cursor, buffer);
            handle[5] = func_8005370C(handle[1], handle[3]);
            break;
        case 0x20:
            success = func_8005D778(handle[1], handle[2], handle[3], cursor, buffer);
            handle[5] = func_8005CF20(handle[1], handle[2], handle[3]);
            break;
        }
        if (success == 0) {
            break;
        }
        (*(s16 *)(handle + 10))++;
        transferred++;
        buffer += *(s16 *)(handle + 8);
        handle[4] |= 1;
    }
    return transferred;
}

s32 func_800625E0(s32 arg0, s32 arg1) {
    extern char *func_80060F68(char *, char *);
    func_80060F68(arg0, func_8004B7A4(arg1));
    return arg0;
}

extern s32 func_80062C24(s32);
extern s32 func_80063754(s32);
extern s8 * HAL_Strcpy(s8 *, s8 *);
extern void _bcopy(const void *, void *, s32);
extern void * func_8004C874(s32, s32);
extern u16 func_80060A4C(const u8* arg0);
extern s8 * func_80060C98(s8 *arg0, u8 *arg1, s32 arg2);
extern void func_80060E48(void *arg0, void *arg1);
void GbMail_ImportRecord(u8 *dest, u8 *src) {
    s32 language = 1;
    _bcopy(src, dest + 0x44, 33);
    dest[0x65] = 0x50;
    _bcopy(src + 0x29, dest + 0x42, 2);
    if (src[0x29] == 0x84) {
        switch (src[0x2A]) {
        case 0x85:
            language = 2;
            break;
        case 0x86:
            language = 3;
            break;
        case 0x88:
            language = 4;
            break;
        case 0x92:
            language = 5;
            break;
        }
    }
    if (func_80062C24((s32)(dest + 0x44))) {
        func_80060C98((s8 *)dest, dest + 0x44, language);
    } else {
        HAL_Strcpy((s8 *)dest, (s8 *)func_8004C874(0x41, 5));
    }
    func_80060E48(dest + 0x66, src + 0x21);
    *(u16 *)(dest + 0x72) = func_80060A4C(src + 0x2B);
    dest[0x74] = src[0x2D];
    if (dest[0x74] == 0 || dest[0x74] >= 252) {
        dest[0x74] = 132;
    }
    dest[0x75] = src[0x2E];
    if (!func_80063754(dest[0x75])) {
        dest[0x75] = 186;
    }
}

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

extern s32 func_80057A80(s32);
void Pokemon_ValidateSpeciesForGbPort(void *record, u8 port) {
    u8 *mon = record;
    s32 limit;
    s32 species;
    s32 i;
    if (func_80057A80(port)) {
        limit = 151;
    } else {
        limit = 251;
    }
    species = mon[0];
    if (species <= 0 || limit < species) {
        mon[0] = 132;
        for (i = 0; i < 4; i++) {
            mon[2 + i] = 0;
            mon[0x18 + i] = 0;
        }
    }
}

extern s32 func_80064800(u8);
extern u8 func_80062E10(u8);
void Pokemon_ValidateMovesForGbPort(void *record, u8 port) {
    u8 *mon = record;
    u8 *p;
    s32 i;
    s32 limit;
    u8 old_pp;
    u8 max_pp;
    if (func_80057A80(port)) {
        limit = 165;
    } else {
        limit = 251;
    }
    i = 0;
    p = mon;
    for (; i < 4; i++, p++) {
        if (p[2] == 0 || limit < p[2]) {
            break;
        }
        old_pp = p[0x18];
        max_pp = func_80062EB0(p[2], old_pp);
        if ((max_pp & 0x3F) < (old_pp & 0x3F)) {
            p[0x18] = max_pp;
        }
    }
    for (; i < 4; i++, p++) {
        p[2] = 0;
    }
    if (mon[2] == 0) {
        mon[2] = ((u8 *)func_80064800(mon[0]))[1];
        mon[0x18] = func_80062E10(mon[2]);
    }
}

#pragma REWRITE_FUNCTION_HEX(func_80062978, e23b14689c69f570e64a2ba86e85d910c687a0a57cdb1163ebac2ee44fd7a9d5, 27bdffd0afbf002cafb30028afb20024afb10020afb0001cafa500349093001d008080258e050008908400000c00000002603025305100ff12330006a202001d920400000c0000003225ffffae0200089213001d920e0001240100ff0000202515c100023267ffffa20000018faf0034240100019202000011e10036961200169606000cafb200100000202500408825004028250c0000003267ffffa60200289606000eafb2001024040001022028250c0000003267ffffa602002a96060010afb2001024040002022028250c0000003267ffffa602002c96060012afb2001024040003022028250c0000003267ffffa602002e96060014afb2001024040004022028250c0000003267ffffa602003096060014afb2001024040005022028250c0000003267ffff9218001ea60200328fa80034331900011720004124010002510100408fbf002c960900281000003ca60900269606000cafb20010960a002800408825004028250c000000afaa0014a60200289606000eafb20010960b002a24040001022028253267ffff0c000000afab0014a602002a96060010afb20010960c002c24040002022028253267ffff0c000000afac0014a602002c96060012afb20010960d002e24040003022028253267ffff0c000000afad0014a602002e96060014afb20010960e003024040004022028253267ffff0c000000afae0014a602003096060014afb20010960f003224040005022028253267ffff0c000000afaf00149603002896180026a60200320078082a502000038fbf002ca60300268fbf002c8fb0001c8fb100208fb200248fb3002803e0000827bd0030)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0x2c, 4, Pokemon_LevelFromExpWithHint)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0x44, 4, func_80061B88)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0x94, 4, Pokemon_CalculateStat)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0xb0, 4, Pokemon_CalculateStat)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0xcc, 4, Pokemon_CalculateStat)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0xe8, 4, Pokemon_CalculateStat)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0x104, 4, Pokemon_CalculateStat)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0x120, 4, Pokemon_CalculateStat)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0x168, 4, Pokemon_ClampCurrentStat)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0x18c, 4, Pokemon_ClampCurrentStat)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0x1b0, 4, Pokemon_ClampCurrentStat)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0x1d4, 4, Pokemon_ClampCurrentStat)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0x1f8, 4, Pokemon_ClampCurrentStat)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_80062978, 0x21c, 4, Pokemon_ClampCurrentStat)
void func_80062978(void *arg0, s32 arg1) {
    u8 *mon = (u8 *)arg0;
    u8 level = mon[0x1D];
    u32 exp = *(u32 *)(mon + 0x8);
    u8 new_level = Pokemon_LevelFromExpWithHint(mon[0], exp, level);
    u16 dvs;

    if (new_level != level) {
        mon[0x1D] = new_level;
        *(u32 *)(mon + 0x8) = func_80061B88(mon[0], new_level);
        level = mon[0x1D];
    }

    if (mon[1] == 0xFF) {
        mon[1] = 0;
    }

    if (arg1 != 1) {
        dvs = *(u16 *)(mon + 0x16);
        *(u16 *)(mon + 0x28) = Pokemon_CalculateStat(0, mon[0], *(u16 *)(mon + 0xC), level, dvs);
        *(u16 *)(mon + 0x2A) = Pokemon_CalculateStat(1, mon[0], *(u16 *)(mon + 0xE), level, dvs);
        *(u16 *)(mon + 0x2C) = Pokemon_CalculateStat(2, mon[0], *(u16 *)(mon + 0x10), level, dvs);
        *(u16 *)(mon + 0x2E) = Pokemon_CalculateStat(3, mon[0], *(u16 *)(mon + 0x12), level, dvs);
        *(u16 *)(mon + 0x30) = Pokemon_CalculateStat(4, mon[0], *(u16 *)(mon + 0x14), level, dvs);
        *(u16 *)(mon + 0x32) = Pokemon_CalculateStat(5, mon[0], *(u16 *)(mon + 0x14), level, dvs);
        if (!(mon[0x1E] & 1)) {
            if (arg1 != 2) {
                *(u16 *)(mon + 0x26) = *(u16 *)(mon + 0x28);
            }
        }
    } else {
        dvs = *(u16 *)(mon + 0x16);
        *(u16 *)(mon + 0x28) = Pokemon_ClampCurrentStat(0, mon[0], *(u16 *)(mon + 0xC), level, dvs, *(u16 *)(mon + 0x28));
        *(u16 *)(mon + 0x2A) = Pokemon_ClampCurrentStat(1, mon[0], *(u16 *)(mon + 0xE), level, dvs, *(u16 *)(mon + 0x2A));
        *(u16 *)(mon + 0x2C) = Pokemon_ClampCurrentStat(2, mon[0], *(u16 *)(mon + 0x10), level, dvs, *(u16 *)(mon + 0x2C));
        *(u16 *)(mon + 0x2E) = Pokemon_ClampCurrentStat(3, mon[0], *(u16 *)(mon + 0x12), level, dvs, *(u16 *)(mon + 0x2E));
        *(u16 *)(mon + 0x30) = Pokemon_ClampCurrentStat(4, mon[0], *(u16 *)(mon + 0x14), level, dvs, *(u16 *)(mon + 0x30));
        *(u16 *)(mon + 0x32) = Pokemon_ClampCurrentStat(5, mon[0], *(u16 *)(mon + 0x14), level, dvs, *(u16 *)(mon + 0x32));
        if (*(u16 *)(mon + 0x28) < *(u16 *)(mon + 0x26)) {
            *(u16 *)(mon + 0x26) = *(u16 *)(mon + 0x28);
        }
    }
}

extern void func_80062978(void *, s32);
void func_80062BD4(void *arg0, s32 arg1, void *arg2) {
    Pokemon_ValidateSpeciesForGbPort(arg0, arg1);
    Pokemon_ValidateMovesForGbPort(arg0, arg1);
    func_80062978(arg0, arg2);
}

s32 func_80062C18(s32 arg0) { return 1; }

s32 func_80062C24(s32 arg0) { return 1; }

void func_80062C30(u8 *arg0) {
    s32 temp_v0 = func_8003514C();

    switch (temp_v0) {
    case 1:
        arg0[0x42] = 0x84;
        arg0[0x43] = 0x84;
        break;
    case 2:
        arg0[0x42] = 0x84;
        arg0[0x43] = 0x85;
        break;
    case 3:
        arg0[0x42] = 0x84;
        arg0[0x43] = 0x86;
        break;
    case 4:
        arg0[0x42] = 0x84;
        arg0[0x43] = 0x88;
        break;
    case 5:
        arg0[0x42] = 0x84;
        arg0[0x43] = 0x92;
        break;
    }
}
#endif
