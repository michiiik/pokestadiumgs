#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050BE0.s")

extern u8 D_801281C0;
struct Func80050CACEntry {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};
s32 func_80050CAC(s32 arg0, s32 arg1) {
    struct Func80050CACEntry *temp_v0;
    s32 var_v1 = 0;
    temp_v0 = (struct Func80050CACEntry *)((u8 *)&D_801281C0 + (arg0 * 0xC));
    if ((temp_v0->unk0 & 1) != 0) {
        if (arg1 == 0) {
            var_v1 = temp_v0->unk4;
        } else {
            var_v1 = temp_v0->unk8;
        }
    }
    return var_v1;
}

extern s32 D_800972B0[]; s32 func_80050CF8(s32 arg0){s32 result=0;if(arg0>=0&&arg0<4)result=D_800972B0[arg0];return result;}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050D20.s")

s32 func_80050DE4(s32 arg0) {
    s32 result = 0;
    switch (arg0) {
    case 0x10: result = 0x180; break;
    case 0x11: result = 0x4D8; break;
    case 0x12: result = 0x20C; break;
    case 0x13: result = 0x54; break;
    case 0x14: result = 0x60; break;
    case 0x15: result = 0x1A0; break;
    case 0x16: result = 0x936; break;
    case 0x17: result = 0x58A; break;
    case 0x18: result = 0x250; break;
    case 0x19: result = 0x1B10; break;
    case 0x1A: result = 0x490; break;
    case 0x1B: result = 0xBD0; break;
    case 0x1C: result = 0x3F0; break;
    case 0x1D: result = 0x648; break;
    case 0x1E: result = 0x50; break;
    }
    return result;
}

extern s32 func_80050D20(s32, s32);
extern u8 D_801281C4[];
extern u8 D_801281C8[];
s32 func_80050E88(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 var_v1;
    temp_v0 = func_80050D20(0x10, arg1);
    if (arg0 != 0) {
        goto block_2;
    }
    var_v1 = *(s32 *)(D_801281C4 + (temp_v0 * 0xC)) + ((arg1 % 4) * 0xF00) + (arg2 * 0x180);
    goto block_3;
block_2:
    var_v1 = *(s32 *)(D_801281C8 + (temp_v0 * 0xC)) + ((arg1 % 4) * 0xF00) + (arg2 * 0x180);
block_3:
    return var_v1;
}

extern s32 func_80050D20(s32, s32);
extern u8 D_801281C4[];
extern u8 D_801281C8[];
s32 func_80050F60(arg0, arg1)
s32 arg0;
s32 arg1;
{
    s32 temp_v0;
    s32 var_a0;
    s32 var_a2;
    s32 var_v1;
    temp_v0 = func_80050D20(0x11, arg1);
    if (arg0 == 0) var_a2 = *(s32 *)(D_801281C4 + temp_v0 * 0xC);
    else var_a2 = *(s32 *)(D_801281C8 + temp_v0 * 0xC);
    if (arg1 > 0) {
        var_v1 = arg1 - 1;
    } else {
        var_v1 = arg1;
    }
    var_a0 = var_a2;
    if (temp_v0 == 2) var_a0 += var_v1 * 0x4D8;
    else var_a0 += var_v1 * 0x4D8 + 0x1E00;
    return var_a0;
}

extern s32 func_80050D20(s32, s32);
extern u8 D_801281C4[];
extern u8 D_801281C8[];
void *func_80051028(s32 arg0, s32 arg1) {
    s32 idx = func_80050D20(0x12, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx * 0xC) + (arg1 * 0x20C) + 0x200);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx * 0xC) + (arg1 * 0x20C) + 0x200);
    }
    return result;
}

extern s32 func_80050D20(s32, s32);
extern u8 D_801281C4[];
extern u8 D_801281C8[];

void *func_800510CC(s32 arg0) {
    s32 idx = func_80050D20(0x13, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx*0xC) + 0x618);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx*0xC) + 0x618);
    }
    return result;
}


void *func_80051138(s32 arg0) {
    s32 idx = func_80050D20(0x14, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx*0xC) + 0x1a0);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx*0xC) + 0x1a0);
    }
    return result;
}

s32 func_800511A4(s32 arg0) {
    s32 idx = func_80050D20(0x15, -1);
    s32 result;
    if (arg0 == 0) {
        result = *(s32 *)(D_801281C4 + idx * 0xC);
    } else {
        result = *(s32 *)(D_801281C8 + idx * 0xC);
    }
    return result;
}


void *func_80051208(s32 arg0) {
    s32 idx = func_80050D20(0x16, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx*0xC) + 0x22d8);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx*0xC) + 0x22d8);
    }
    return result;
}


void *func_80051274(s32 arg0) {
    s32 idx = func_80050D20(0x17, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx*0xC) + 0x2c0e);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx*0xC) + 0x2c0e);
    }
    return result;
}


void *func_800512E0(s32 arg0) {
    s32 idx = func_80050D20(0x18, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx*0xC) + 0x66c);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx*0xC) + 0x66c);
    }
    return result;
}


void *func_8005134C(s32 arg0) {
    s32 idx = func_80050D20(0x19, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx*0xC) + 0x8bc);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx*0xC) + 0x8bc);
    }
    return result;
}


void *func_800513B8(s32 arg0) {
    s32 idx = func_80050D20(0x1a, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx*0xC) + 0x23cc);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx*0xC) + 0x23cc);
    }
    return result;
}


void *func_80051424(s32 arg0) {
    s32 idx = func_80050D20(0x1b, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx*0xC) + 0x285c);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx*0xC) + 0x285c);
    }
    return result;
}


void *func_80051490(s32 arg0) {
    s32 idx = func_80050D20(0x1c, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx*0xC) + 0x342c);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx*0xC) + 0x342c);
    }
    return result;
}


void *func_800514FC(s32 arg0) {
    s32 idx = func_80050D20(0x1d, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx*0xC) + 0x381c);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx*0xC) + 0x381c);
    }
    return result;
}


void *func_80051568(s32 arg0) {
    s32 idx = func_80050D20(0x1e, -1);
    void *result;
    if (arg0 == 0) {
        result = (void *)(*(s32 *)(D_801281C4 + idx*0xC) + 0x3e64);
    } else {
        result = (void *)(*(s32 *)(D_801281C8 + idx*0xC) + 0x3e64);
    }
    return result;
}

u16 Save_Checksum(u8* arg0, s32 arg1) {
    u16 var_v1 = 0;

    while (arg1-- > 2) {
        var_v1 += *arg0++;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051610.s")

extern void _bcopy(void *, void *, s32);
void Save_WriteRecord(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 *temp_v0;

    _bcopy(arg0, arg1, arg2);
    temp_v0 = (s32 *)((u8 *)&D_801281C0 + (arg3 * 0xC));
    *temp_v0 |= 2;
}

extern void func_80051610(void *, s32, s32);
void Save_CommitRecord(u8 *arg0, s32 arg1, s32 arg2) {
    s32 *temp_v0;

    if ((*arg0 & 2) != 0) {
        *arg0 &= 0xFFFD;
        func_80051610(arg0, arg1, 1);
        temp_v0 = (s32 *)((u8 *)&D_801281C0 + (arg2 * 0xC));
        *temp_v0 |= 2;
    }
}

void Save_InvalidateRecord(u8 *arg0, s32 arg1, s32 arg2) {
    s32 *temp_v0;

    if ((*arg0 & 2) != 0) {
        func_80051610(arg0, arg1, 0);
        temp_v0 = (s32 *)((u8 *)&D_801281C0 + (arg2 * 0xC));
        *temp_v0 |= 2;
    }
}

typedef struct Func80051780Entry {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Func80051780Entry;
void Save_RestoreRecord(s32 arg0, s32 arg1, s32 arg2) {
    Func80051780Entry *temp_v0 = (Func80051780Entry *)((u8 *)&D_801281C0 + arg2 * 0xC);
    s32 v1 = arg0 - temp_v0->unk4;
    _bcopy(temp_v0->unk8 + v1, arg0, arg1);
}

extern void _bzero(void *, s32);
void Save_ClearRecord(u8 *arg0, s32 arg1, s32 arg2) {
    s32 *temp_v0;

    _bzero(arg0, arg1);
    *arg0 |= 2;
    temp_v0 = (s32 *)((u8 *)&D_801281C0 + (arg2 * 0xC));
    *temp_v0 |= 2;
}

extern void func_80061248();
extern void func_800619E8(void *);

void func_80051830(void *arg0) {
    func_80061248();
    func_800619E8(arg0);
    (*(u16 *)((u8 *)(arg0) + (0x26))) = (u16) (*(u16 *)((u8 *)(arg0) + (0x28)));
}

extern void func_800615D0(s32,s32); void func_80051864(s32 a0,s32 a1){func_800615D0(a1,a0);}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051890.s")

void func_800519AC(u8 *arg0, u8 *arg1) {
    u8 *temp_a3 = arg1;
    _bzero(arg1, 0x48);
    temp_a3[0] = arg0[0x36];
    temp_a3[1] = arg0[0x37];
    *(u16 *)(temp_a3 + 2) = *(u16 *)(arg0 + 0x38);
    temp_a3[4] = *(u32 *)(arg0 + 0x40) >> 31;
    temp_a3[5] = (*(u32 *)(arg0 + 0x40) << 1) >> 31;
    temp_a3[6] = (*(u32 *)(arg0 + 0x40) << 2) >> 31;
    temp_a3[7] = (*(u32 *)(arg0 + 0x40) << 3) >> 31;
    temp_a3[8] = (*(u32 *)(arg0 + 0x40) << 4) >> 31;
    temp_a3[9] = (*(u32 *)(arg0 + 0x40) << 5) >> 31;
    temp_a3[0xB] = *(s16 *)(arg0 + 0x34);
    _bcopy(arg0 + 0x14, temp_a3 + 0x14, 0x20);
    _bcopy(arg0, temp_a3 + 0x34, 0x14);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051A8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051BF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051D64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80052150.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005253C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80052928.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80052ECC.s")

extern void func_80052ECC(s32);

void func_800530DC(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_80052ECC(var_s0);
        var_s0 += 1;
    } while (var_s0 != 4);
}

extern void func_80052928(s32,s32); extern void func_80051D64(s32,s32); void Save_ResetAndCommitTypedRecord(s32 a0,s32 a1){func_80052928(a0,a1);func_80051D64(a0,a1);}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005314C.s")

s32 func_80053230(s32 arg0) {
    s32 result = 0;
    switch (arg0) {
    case 0x10: result = 0x6; break;
    case 0x11: result = 0x14; break;
    case 0x13: result = 0x2D; break;
    case 0x12: result = 0xFA; break;
    case 0x16: result = 0x32; break;
    case 0x17: result = 0x1E; break;
    case 0x18: result = 0x8; break;
    case 0x19: result = 0x6; break;
    case 0x1A: result = 0x1; break;
    case 0x1B: result = 0x8; break;
    case 0x1C: result = 0x32; break;
    case 0x1D: result = 0x64; break;
    case 0x1E: result = 0x46; break;
    }
    return result;
}

s32 func_800532C4(s32 arg0){s32 result=0;switch(arg0){case 0x10:result=1;break;case 0x11:result=0xE;break;}return result;}

s32 func_800532F0(s32 arg0) {
    s32 result = 0;
    switch (arg0) {
    case 0x10: result = 0x58; break;
    case 0x11: result = 0x58; break;
    case 0x12: result = 0x2; break;
    case 0x13: result = 0x1; break;
    case 0x16: result = 0x76; break;
    case 0x17: result = 0x76; break;
    case 0x18: result = 0x44; break;
    case 0x19: result = 0x490; break;
    case 0x1A: result = 0x490; break;
    case 0x1B: result = 0x220; break;
    case 0x1C: result = 0x14; break;
    case 0x1D: result = 0x10; break;
    case 0x1E: result = 0x1; break;
    }
    return result;
}

s32 Deck_IsSaveEntryPresent(void *arg0, void *arg1) { return func_80051A8C(arg0, arg1, 1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800533A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053440.s")

extern u8 D_801281F0[]; u8 *func_800534FC(s32 arg0){u8 *result=NULL;if(arg0>=0&&arg0<0xE)result=D_801281F0+arg0*0x20;return result;}

s32 func_80053524(s32 arg0, u8 *arg1) {
    s32 result = 0;
    s32 next;
    *arg1 = 0;
    if (Deck_IsSaveEntryPresent((void *)0x11, (void *)arg0) != 0) {
        next = func_80050F60(0, arg0);
        if (next != -0x10) {
            next += 0x10;
            result = func_80060C08((u16 *)arg1, (u16 *)next);
        }
    }
    return result;
}

extern void func_80060D70(u8 *, u8 *);
extern void func_80051BF0(s32, void *, s32);

void func_80053584(void *arg0, s32 arg1) {
    u8 *v0;
    if (arg1 == 0) {
        return;
    }
    v0 = (u8 *)func_80050F60(0, arg0, arg1);
    func_80060D70(v0 + 0x10, arg1);
    func_80051BF0(0x11, arg0, 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800535D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005370C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053808.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053908.s")

extern void func_80062614(void);
void func_80053A30(void) {
    func_80062614();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053A50.s")

void func_80053AC8(u16 *a0,u16 *a1){a0[0]=a1[0];a0[1]=a1[1];a0[2]=a1[2];func_80060C08(a0+4,a1+4);}

void func_80053B04(u16 *a0,u16 *a1){a0[0]=a1[0];a0[1]=a1[1];func_80060C08(a0+2,a1+2);}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053B38.s")

extern void func_8006276C(s32,s32); void func_80053DDC(s32 a0,s32 a1){func_8006276C(a1,a0);}

void func_80053E08(u8 *arg0, u8 *arg1) {
    u8 *var_s2;
    s32 var_s1;
    u8 *var_s0;
    func_80060D70(arg1, arg0);
    var_s0 = arg0 + 0x10;
    var_s1 = 0;
    var_s2 = arg1 + 0x10;
    *(u16 *)(arg1 + 0xC) = *(u16 *)(arg0 + 0xC);
    do {
        func_80051864((s32)var_s0, (s32)var_s2);
        var_s1 += 0x3C;
        var_s0 += 0x58;
        var_s2 += 0x3C;
    } while (var_s1 != 0x168);
}

void func_80053E8C(u8 *arg0, u8 *arg1) {
    *(u16 *)(arg1 + 0) = *(u16 *)(arg0 + 0);
    *(u16 *)(arg1 + 2) = *(u16 *)(arg0 + 2);
    *(u16 *)(arg1 + 4) = *(u16 *)(arg0 + 4);
    func_80060D70(arg1 + 8, arg0 + 8);
}

void func_80053ECC(u8 *arg0, u8 *arg1) {
    *(u16 *)(arg1 + 0) = *(u16 *)(arg0 + 0);
    *(u16 *)(arg1 + 2) = *(u16 *)(arg0 + 2);
    func_80060D70(arg1 + 4, arg0 + 4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053F04.s")

extern void *func_80051138(s32);

typedef struct { s32 a, b; } Pair80054210;
void func_80054210(Pair80054210 *arg0) {
    Pair80054210 *v0 = (Pair80054210 *)((u8 *)func_80051138(0) + 0x14);
    *arg0 = *v0;
}

extern s32 _bcmp(const void *, const void *, s32);
typedef struct Func80054248Pair {
    s32 a;
    s32 b;
} Func80054248Pair;
void func_80054248(Func80054248Pair *arg0) {
    Func80054248Pair *temp_v0;
    if (_bcmp(arg0, (u8 *)func_80051138(0) + 0x14, sizeof(Func80054248Pair)) != 0) {
        temp_v0 = (Func80054248Pair *)((u8 *)func_80051138(0) + 0x14);
        *temp_v0 = *arg0;
        func_80051BF0(0x14, 0, 2);
    }
}

extern void func_80053B38(s32, s32, s32, u8 *);

u8 func_800542B0(s32 arg0) {
    u8 sp1F;

    sp1F = 0;
    func_80053B38(0x13, 0, arg0, &sp1F);
    return sp1F;
}

extern void func_80053F04(s32, s32, s32, u8 *);

void func_800542E4(s32 arg0, u8 arg1) {
    u8 sp1F;

    sp1F = arg1;
    func_80053F04(0x13, 0, arg0, &sp1F);
}

u8 func_8005431C(void) {
    u8 result = 0;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC)) & 1) != 0) {
        result = *((u8 *)func_800510CC(0) + 1);
    }
    return result;
}

extern void * func_800510CC(s32 arg0);
extern void func_80051BF0(s32, void *, s32);

s32 func_8005437C(u8 arg0) {
    s32 result = 0;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC)) & 1) != 0) {
        if (arg0 != *((u8 *)func_800510CC(0) + 1)) {
            *((u8 *)func_800510CC(0) + 1) = arg0;
            func_80051BF0(0x13, 0, 2);
            result = 1;
        }
    }
    return result;
}

u8 func_80054410(s32 arg0) {
    u8 result = 0;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC)) & 1) != 0 && arg0 < 0x10) {
        result = *((u8 *)func_800510CC(0) + arg0 + 0x2F);
    }
    return result;
}

extern void * func_800510CC(s32 arg0);
extern void func_80051BF0(s32, void *, s32);

s32 func_80054488(s32 arg0, u8 arg1) {
    s32 result = 0;
    u8 *record;
    record = (u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC);
    if (arg0 < 0x10 && (*(s32 *)record & 1) != 0 &&
        arg1 != *(u8 *)((u8 *)func_800510CC(0) + arg0 + 0x2F)) {
        *(u8 *)((u8 *)func_800510CC(0) + arg0 + 0x2F) = arg1;
        func_80051BF0(0x13, 0, 2);
        result = 1;
    }
    return result;
}

u8 func_8005453C(s32 arg0) {
    u8 result = 0;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC)) & 1) != 0 && arg0 < 9) {
        result = *((u8 *)func_800510CC(0) + arg0 + 0x3F);
    }
    return result;
}

extern void * func_800510CC(s32 arg0);
extern void func_80051BF0(s32, void *, s32);

s32 func_800545B4(s32 arg0, u8 arg1) {
    s32 result = 0;
    u8 *record;
    record = (u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC);
    if (arg0 < 9 && (*(s32 *)record & 1) != 0 &&
        arg1 != *(u8 *)((u8 *)func_800510CC(0) + arg0 + 0x3F)) {
        *(u8 *)((u8 *)func_800510CC(0) + arg0 + 0x3F) = arg1;
        func_80051BF0(0x13, 0, 2);
        result = 1;
    }
    return result;
}

u8 func_80054668(s32 arg0) {
    u8 result = 0;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC)) & 1) != 0 && arg0 < 3) {
        result = *((u8 *)func_800510CC(0) + arg0 + 0x48);
    }
    return result;
}

extern void * func_800510CC(s32 arg0);
extern void func_80051BF0(s32, void *, s32);

s32 func_800546E0(s32 arg0, u8 arg1) {
    s32 result = 0;
    u8 *record;
    record = (u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC);
    if (arg0 < 3 && (*(s32 *)record & 1) != 0 &&
        arg1 != *(u8 *)((u8 *)func_800510CC(0) + arg0 + 0x48)) {
        *(u8 *)((u8 *)func_800510CC(0) + arg0 + 0x48) = arg1;
        func_80051BF0(0x13, 0, 2);
        result = 1;
    }
    return result;
}

u8 func_80054794(void) {
    u8 result = 0;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC)) & 1) != 0) {
        result = *((u8 *)func_800510CC(0) + 0x4B);
    }
    return result;
}

extern void * func_800510CC(s32 arg0);
extern void func_80051BF0(s32, void *, s32);

u8 func_800547F4(u8 arg0) {
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC)) & 1) != 0 &&
        arg0 != *((u8 *)func_800510CC(0) + 0x4B)) {
        *((u8 *)func_800510CC(0) + 0x4B) = arg0;
        func_80051BF0(0x13, 0, 2);
    }
    return arg0;
}


typedef struct { s32 a, b, c, d; } Quad8005487C;
void func_8005487C(Quad8005487C *arg0) {
    Quad8005487C *v0 = (Quad8005487C *)((u8 *)func_80051138(0) + 0x4);
    *arg0 = *v0;
}

extern s32 _bcmp(const void *, const void *, s32);
extern void * func_80051138(s32 arg0);
extern void func_80051BF0(s32, void *, s32);

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Quad800548C4;

void func_800548C4(Quad800548C4 *arg0) {
    Quad800548C4 *dst;
    if (_bcmp(arg0, (u8 *)func_80051138(0) + 4, 0x10) != 0) {
        dst = (Quad800548C4 *)((u8 *)func_80051138(0) + 4);
        *dst = *arg0;
        func_80051BF0(0x14, 0, 2);
    }
}


typedef struct { s32 a, b; } Pair8005493C;
void func_8005493C(Pair8005493C *arg0) {
    Pair8005493C *v0 = (Pair8005493C *)((u8 *)func_80051138(0) + 0x4C);
    *arg0 = *v0;
}

extern s32 _bcmp(const void *, const void *, s32);
typedef struct Func80054974Pair {
    s32 a;
    s32 b;
} Func80054974Pair;
void func_80054974(Func80054974Pair *arg0) {
    Func80054974Pair *temp_v0;
    if (_bcmp(arg0, (u8 *)func_80051138(0) + 0x4C, sizeof(Func80054974Pair)) != 0) {
        temp_v0 = (Func80054974Pair *)((u8 *)func_80051138(0) + 0x4C);
        *temp_v0 = *arg0;
        func_80051BF0(0x14, 0, 2);
    }
}


u8 func_800549DC(s32 arg0) {
    u8 result = 0;
    u8 *v0;
    if (arg0 >= 0 && arg0 < 2) {
        v0 = (u8 *)func_80051138(0);
        result = *(v0 + arg0 + 0x54);
    }
    return result;
}

void func_80054A24(s32 arg0, u8 arg1) {
    void *temp_v0;
    u8 current;
    if ((arg0 >= 0) && (arg0 < 2)) {
        temp_v0 = func_80051138(0);
        current = *((u8 *)temp_v0 + arg0 + 0x54);
        if (current != arg1) {
            temp_v0 = func_80051138(0);
            *((u8 *)temp_v0 + arg0 + 0x54) = arg1;
            func_80051BF0(0x14, 0, 2);
        }
    }
}

s32 func_80054AA0(s32 arg0) {
    s32 result = 0;
    void *temp_v0;
    u32 flags;

    temp_v0 = func_80051138(0);
    flags = *(u32 *)((u8 *)temp_v0 + 0xC);
    if ((arg0 >= 0) && (arg0 < 0x20)) {
        result = (flags & (1 << arg0)) != 0;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054AF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054B7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054CC4.s")

s32 func_80054E10(u16 *arg0)
{
  int new_var;
  func_80050D20(0x15, -1);
  new_var = (*arg0) != 0xFFFF;
  return new_var;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054E48.s")

extern s32 func_80054E48(s32);

s32 func_80055028(void) {
    s32 result = 0;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (func_80054E48(i)) {
            result |= 1 << i;
        }
    }
    return result;
}

void Save_ResetBank(s32 arg0, u32 arg1) {
    void *temp_v0;

    if ((arg1 >= 0x424E4B30U) && (arg1 < 0x424E4B34U)) {
        temp_v0 = ((arg1 - 0x424E4B30) * 0xC) + &D_801281C0;
        (*(s32 *)((u8 *)(temp_v0) + (4))) = 0;
        (*(s32 *)((u8 *)(temp_v0) + (0))) = (s32) ((*(s32 *)((u8 *)(temp_v0) + (0))) & ~3);
        (*(s32 *)((u8 *)(temp_v0) + (8))) = 0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800550E8.s")

s32 func_800551EC(u8 *arg0, s32 arg1) {
    struct Footer {
        u16 magic;
        u16 version;
        u16 checksum;
    } *footer;

    footer = (struct Footer *)(arg0 + arg1 - 6);
    if (footer->magic != 0x5033) {
        return 0;
    }
    if (footer->version != 0x7630) {
        return 0;
    }
    if (footer->checksum != Save_Checksum(arg0, arg1)) {
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055260.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800555B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005565C.s")

extern void func_80055260(s32, s32);
void func_8005577C(s32 arg0) {
    s32 var_s0;

    var_s0 = 1;
    do {
        if (arg0 == 0) {
            func_80055260(0x11, var_s0);
        } else {
            Save_ResetAndCommitTypedRecord(0x11, var_s0);
        }
        var_s0 += 1;
    } while (var_s0 != 0xE);
}

void func_800557E4(s32 arg0) {
    s32 var_s0;

    if (arg0 == 0) {
        func_80055260(0x14, 0);
        func_80055260(0x15, 0);
        func_80055260(0x13, 0);
        func_80055260(0x18, 0);
        func_80055260(0x19, 0);
        func_80055260(0x1A, 0);
        func_80055260(0x1B, 0);
        func_80055260(0x1C, 0);
        func_80055260(0x1D, 0);
        func_80055260(0x1E, 0);
    } else {
        Save_ResetAndCommitTypedRecord(0x14, 0);
        Save_ResetAndCommitTypedRecord(0x15, 0);
        Save_ResetAndCommitTypedRecord(0x13, 0);
        Save_ResetAndCommitTypedRecord(0x18, 0);
        Save_ResetAndCommitTypedRecord(0x19, 0);
        Save_ResetAndCommitTypedRecord(0x1A, 0);
        Save_ResetAndCommitTypedRecord(0x1B, 0);
        Save_ResetAndCommitTypedRecord(0x1C, 0);
        Save_ResetAndCommitTypedRecord(0x1D, 0);
        Save_ResetAndCommitTypedRecord(0x1E, 0);
    }
    var_s0 = 0;
    do {
        if (arg0 == 0) {
            func_80055260(0x12, var_s0);
        } else {
            Save_ResetAndCommitTypedRecord(0x12, var_s0);
        }
        var_s0 += 1;
    } while (var_s0 != 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055948.s")

extern void func_80055948(s32);

void func_80055A34(void) {
    s32 var_s0;

    var_s0 = 0;
    do {
        func_80055948(var_s0);
        var_s0 += 1;
    } while (var_s0 != 4);
}

s32 func_80055A74(s32 arg0) { extern s32 D_800972C0; s32 old = D_800972C0; if (arg0 >= 0 && arg0 < 6) D_800972C0 = arg0; return old; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055A9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055B14.s")

s32 Deck_FindFirstFreeTeamSlot(void) {
    s32 i;
    for (i = 0; i < 0xA; i++) {
        if (Deck_IsSaveEntryPresent((void *)0x10, (void *)i) == 0) {
            break;
        }
    }
    return i;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055BF8.s")

extern void func_80053B38(s32, s32, s32, u8 *);
u8 func_80055CCC(s32 arg0) {
    u8 result;
    u8 padding[8];

    result = 0;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x1E, -1) * 0xC)) & 1) &&
        (arg0 >= 0) && (arg0 < 0x22)) {
        func_80053B38(0x1E, 0, arg0, &result);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055D44.s")

extern void func_80053B38(s32, s32, s32, u8 *);
extern void func_80053F04(s32, s32, s32, u8 *);

typedef struct {
    u8 leading[3];
    u8 value;
    u8 padding[8];
} Temp80055DC4;

void func_80055DC4(s32 arg0, u8 arg1) {
    Temp80055DC4 temp;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x1E, -1) * 0xC)) & 1) != 0 &&
        arg0 >= 0 && arg0 < 0x22) {
        func_80053B38(0x1E, 0, arg0, &temp.value);
        if (temp.value != arg1) {
            func_80053F04(0x1E, 0, arg0, &arg1);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055E54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055F6C.s")

s32 func_80056024(s32 arg0) { s32 result = 0; switch (arg0) { case 5: result = 1; break; case 6: result = 2; break; case 7: result = 4; break; case 8: result = 8; break; case 9: result = 0x10; break; case 10: result = 0x20; break; case 11: result = 0x40; break; case 12: result = 0x80; break; case 13: result = 0x100; break; case 14: result = 1; break; case 15: result = 2; break; case 16: result = 1; break; case 17: result = 2; break; case 18: result = 4; break; case 19: result = 8; break; case 20: result = 0x10; break; case 21: result = 0x20; break; case 22: result = 0x40; break; case 23: result = 0x80; break; case 24: result = 0x100; break; } return result; }

extern void func_80055EF0(void *, s32);
s32 func_800560F0(s32 arg0) {
    s32 result = 1;
    u8 local[0x18];
    s32 mode;
    if (arg0 != 0) {
        mode = 1;
    } else {
        mode = 0;
    }
    func_80055EF0((u8 *)local - 4, mode);
    if ((((u8 *)local - 4)[6] & 1) != 1) result = 0;
    if ((((u8 *)local - 4)[7] & 0xF) != 0xF) result = 0;
    if ((((u8 *)local - 4)[8] & 0xF) != 0xF) result = 0;
    if ((((u8 *)local - 4)[9] & 1) != 1) result = 0;
    if ((*(u16 *)((u8 *)local - 2) & 0x100) == 0) result = 0;
    return result;
}

s32 func_80056184(void *arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (!((*(u8 *)((u8 *)(arg0) + (6))) & 1)) {
        var_v1 = 0;
    }
    if (!((*(u8 *)((u8 *)(arg0) + (9))) & 1)) {
        var_v1 = 0;
    }
    if (((*(u8 *)((u8 *)(arg0) + (7))) & 0xF) != 0xF) {
        var_v1 = 0;
    }
    if (((*(u8 *)((u8 *)(arg0) + (8))) & 0xF) != 0xF) {
        var_v1 = 0;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800561E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800562B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005633C.s")
#endif
