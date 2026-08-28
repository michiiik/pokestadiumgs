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

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050DE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050E88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80050F60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80051028.s")

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
void func_80051680(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 *temp_v0;

    _bcopy(arg0, arg1, arg2);
    temp_v0 = (s32 *)((u8 *)&D_801281C0 + (arg3 * 0xC));
    *temp_v0 |= 2;
}

extern void func_80051610(void *, s32, s32);
void func_800516C4(u8 *arg0, s32 arg1, s32 arg2) {
    s32 *temp_v0;

    if ((*arg0 & 2) != 0) {
        *arg0 &= 0xFFFD;
        func_80051610(arg0, arg1, 1);
        temp_v0 = (s32 *)((u8 *)&D_801281C0 + (arg2 * 0xC));
        *temp_v0 |= 2;
    }
}

void func_80051724(u8 *arg0, s32 arg1, s32 arg2) {
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
void func_80051780(s32 arg0, s32 arg1, s32 arg2) {
    Func80051780Entry *temp_v0 = (Func80051780Entry *)((u8 *)&D_801281C0 + arg2 * 0xC);
    s32 v1 = arg0 - temp_v0->unk4;
    _bcopy(temp_v0->unk8 + v1, arg0, arg1);
}

extern void _bzero(void *, s32);
void func_800517D8(u8 *arg0, s32 arg1, s32 arg2) {
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800519AC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053230.s")

s32 func_800532C4(s32 arg0){s32 result=0;switch(arg0){case 0x10:result=1;break;case 0x11:result=0xE;break;}return result;}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800532F0.s")

void Deck_IsSaveEntryPresent(void *arg0, void *arg1) { func_80051A8C(arg0, arg1, 1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800533A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053440.s")

extern u8 D_801281F0[]; u8 *func_800534FC(s32 arg0){u8 *result=NULL;if(arg0>=0&&arg0<0xE)result=D_801281F0+arg0*0x20;return result;}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80053524.s")

extern void *func_80050F60(s32, void *, s32);
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

extern void func_80060C08(u16 *,u16 *); void func_80053AC8(u16 *a0,u16 *a1){a0[0]=a1[0];a0[1]=a1[1];a0[2]=a1[2];func_80060C08(a0+4,a1+4);}

extern void func_80060C08(u16 *,u16 *); void func_80053B04(u16 *a0,u16 *a1){a0[0]=a1[0];a0[1]=a1[1];func_80060C08(a0+2,a1+2);}

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_8005437C.s")

u8 func_80054410(s32 arg0) {
    u8 result = 0;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC)) & 1) != 0 && arg0 < 0x10) {
        result = *((u8 *)func_800510CC(0) + arg0 + 0x2F);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80054488.s")

u8 func_8005453C(s32 arg0) {
    u8 result = 0;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC)) & 1) != 0 && arg0 < 9) {
        result = *((u8 *)func_800510CC(0) + arg0 + 0x3F);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800545B4.s")

u8 func_80054668(s32 arg0) {
    u8 result = 0;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC)) & 1) != 0 && arg0 < 3) {
        result = *((u8 *)func_800510CC(0) + arg0 + 0x48);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800546E0.s")

u8 func_80054794(void) {
    u8 result = 0;
    if ((*(s32 *)((u8 *)&D_801281C0 + (func_80050D20(0x13, -1) * 0xC)) & 1) != 0) {
        result = *((u8 *)func_800510CC(0) + 0x4B);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800547F4.s")


typedef struct { s32 a, b, c, d; } Quad8005487C;
void func_8005487C(Quad8005487C *arg0) {
    Quad8005487C *v0 = (Quad8005487C *)((u8 *)func_80051138(0) + 0x4);
    *arg0 = *v0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800548C4.s")


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

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055BA8.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055DC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055E54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80055F6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_80056024.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/517E0/func_800560F0.s")

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
