#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82600A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82600BA0.s")

extern void func_800619E8(void *);
s32 func_80061B88(u8, u8, void *);

void func_82600CF4(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + (8))) = func_80061B88((*(u8 *)((u8 *)(arg0) + (0))), (*(u8 *)((u8 *)(arg0) + (0x1D))), arg0);
    func_800619E8(arg0);
    (*(u16 *)((u8 *)(arg0) + (0x26))) = (u16) (*(u16 *)((u8 *)(arg0) + (0x28)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82600D38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82601070.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82601298.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_8260166C.s")

void func_82601824(void *arg0) {
    u8 *values[4];
    s32 i;

    values[0] = *(u8 **)((u8 *)arg0 + 0xAC) + 0x134;
    values[1] = *(u8 **)((u8 *)arg0 + 0xAC) + 0x1CC;
    values[2] = *(u8 **)((u8 *)arg0 + 0xAC) + 0x264;
    i = 0;
    do {
        if (i != 0) {
            func_8006AF28(i, values[(*(s16 *)(*(u8 **)arg0 + 0xC))]);
        }
        i += 1;
    } while (i != 2);
}

void func_826018BC(void *arg0) {
    u8 *values[4];
    s32 i;
    u8 *temp_v0;

    values[0] = *(u8 **)((u8 *)arg0 + 0xC) + 0x134;
    values[1] = *(u8 **)((u8 *)arg0 + 0xC) + 0x1CC;
    values[2] = *(u8 **)((u8 *)arg0 + 0xC) + 0x264;
    i = 0;
    do {
        temp_v0 = *(u8 **)arg0;
        if (*(s8 *)(temp_v0 + i) == -1) {
            func_8006AED4(i, values[(*(s16 *)(temp_v0 + 0xC))]);
        }
        i += 1;
    } while (i != 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82601968.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82601A84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82601BB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82601D2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82601E70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82601F90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_826020C0.s")


void func_826026E8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    *(u16 *)(arg0 + 0xA0) = (u16)1;
    *(u16 *)(arg0 + 0xA4) = (u16)arg1;
    *(u16 *)(arg0 + 0xA6) = (u16)arg2;
    *(u16 *)(arg0 + 0xA8) = (u16)arg3;
    *(u16 *)(arg0 + 0xAA) = (u16)arg4;
}

void func_82602708(u8 *arg0) {
    *(u16 *)(arg0 + 0xA0) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602710.s")


typedef struct { u8 pad_00[4]; void *unk_04; } Func82615340StateX;
extern Func82615340StateX *D_82615340;
extern void func_82602710(u8 *);
extern void func_800088DC(void);
extern void func_826042A0(void);
extern void func_82614BD0(void);
extern void func_80008648(void);

void func_82602888(void) {
    func_80043E70(D_82615340->unk_04, 0);
    func_800088DC();
    func_82602710(D_82615340);
    func_826042A0();
    func_82614BD0();
    func_80008648();
}


typedef struct {
    u8 pad_00[8];
    u16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x7C];
    s16 unk_88;
} Func826028E0StateX;
extern s32 func_8006AD10(u16, s16, s16);
extern s32 func_80054AA0(s32);
extern void func_80054AF4(s32);

void func_826028E0(Func826028E0StateX *arg0) {
    s32 value;
    value = func_8006AD10(arg0->unk_08, arg0->unk_0A, arg0->unk_88);
    if (value != -1) {
        if (func_80054AA0(value) == 0) {
            func_80054AF4(value);
        }
    }
}


s32 func_82602930(s32 arg0) {
    s32 result = arg0;
    switch (arg0) {
    case 0:
        if (StageContext_GetFadeMode() == 0) result = 1;
        break;
    case 1:
        if (func_80044144(D_82615340->unk_04) != 0) {
            result = 2;
            func_82614CE0();
            func_800355E4(0x28);
        }
        break;
    case 2:
        if (func_82614F0C() != 0) {
            result = 3;
            func_800088A4(1);
            StageFade_StartFromTransparent(5);
            func_800226C0(0x65);
        }
        break;
    case 3:
        if (StageContext_GetFadeMode() == 1) result = 4;
        break;
    }
    return result;
}

extern void func_800086A4(s32);
extern void func_80007AEC(s32);
extern void func_80064D28(void);
extern void func_82604170(void);
extern void func_82613814(void);
extern void func_82602888(void);
extern void func_826028E0(Func826028E0StateX *arg0);
extern s32 func_82602930(s32 arg0);
void func_82602A0C(void) {
    Func826028E0StateX *sp24;
    u16 sp22;
    s32 temp_v0_2;
    s32 var_s0;

    sp24 = (Func826028E0StateX *)*(void **)D_82615340;
    var_s0 = 0;
    sp22 = sp24->unk_08 & 0xFF00;
    if (StageContext_GetFadeMode() != 0) {
        func_800086A4(2);
        func_80007AEC(5);
    }
    do {
        func_80064D28();
        func_82604170();
        func_82613814();
        func_82602888();
        temp_v0_2 = func_82602930(var_s0);
        var_s0 = temp_v0_2;
    } while (temp_v0_2 != 4);
    if ((sp22 == 0x300) || (sp22 == 0x600)) {
        func_826028E0(sp24);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602AC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602B9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602E14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602FE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_826030E4.s")

extern Func82615340StateX *D_82615370;
extern void func_80008648(void);
extern void func_800088DC(void);
extern void func_82602710(u8 *);
extern void func_826042A0(void);
extern void func_82614BD0(void);
void func_82603684(void) {
    func_80043E70(D_82615370->unk_04, 0);
    func_800088DC();
    func_82602710(D_82615370);
    func_826042A0();
    func_82614BD0();
    func_80008648();
}

extern void func_80055F6C(s32 *, s32);
extern s32 D_82615374;
extern u8 D_826163C0;
extern s32 func_8006CBB8(s32);
extern s32 func_8006CBA0(s32, s32);
extern u16 func_80056024(s32);
void func_826036DC(void *arg0) {
    s32 temp_a0;
    s32 sp24;
    u16 sp1E;
    s32 temp_v0;

    temp_a0 = *(s16 *)((u8 *)arg0 + 0xA);
    sp24 = temp_a0;
    func_8006CBB8(temp_a0);
    if (func_8006CBA0(*(s16 *)((u8 *)arg0 + 0x88), *(s16 *)((u8 *)arg0 + 0x8A)) != 0) {
        sp1E = func_80056024(sp24);
        temp_v0 = func_8006CBB8(sp24);
        switch (temp_v0) {
        case 0:
            (*(u16 *)((u8 *)&D_826163C0 + 0x0)) |= sp1E;
            break;
        case 1:
            (*(u16 *)((u8 *)&D_826163C0 + 0x4)) |= sp1E;
            break;
        case 2:
            (*(u16 *)((u8 *)&D_826163C0 + 0x2)) |= sp1E;
            break;
        }
        if (sp1E != 0) {
            func_80055F6C((s32 *)&D_826163C0, D_82615374);
        }
    }
}

void func_826037BC(void *arg0) {
    func_8006CBB8(*(s16 *)((u8 *)(arg0) + (0xA)));
    if (func_8006CBA0(*(s16 *)((u8 *)(arg0) + (0x88)), *(s16 *)((u8 *)(arg0) + (0x8A))) != 0) {
        (*(s8 *)((u8 *)(&D_826163C0) + (0xA))) = 1;
        func_80055F6C(&D_826163C0, D_82615374);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82603814.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82603870.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_826039A0.s")
#endif
