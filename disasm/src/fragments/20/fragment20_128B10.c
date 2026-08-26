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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82601824.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_826018BC.s")

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
            func_80007B34(5);
            func_800226C0(0x65);
        }
        break;
    case 3:
        if (StageContext_GetFadeMode() == 1) result = 4;
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602A0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602AC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602B9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602E14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82602FE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_826030E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82603684.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_826036DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_826037BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82603814.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_82603870.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_128B10/func_826039A0.s")
#endif
