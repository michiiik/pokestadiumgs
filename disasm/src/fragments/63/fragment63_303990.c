#include "global.h"


#ifdef VERSION_US
extern u8 *D_87E1BA20;
void func_87E00020(void) {
    *(s32 *)(D_87E1BA20 + 0x2E04) = 0;
}

void func_87E00030(void) {
    *(s32 *)(D_87E1BA20 + 0x2E04) = 1;
}

extern void func_8004C8C0();
void func_87E00044(void) { func_8004C8C0(260); func_8004C8C0(424); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E0006C.s")

extern void func_87E01628();
extern void main_pool_pop_state(s32);

void func_87E000D4(void) {
    func_87E01628();
    main_pool_pop_state(0x4D464D53);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E00100.s")

extern void func_87E015C0(s32);
extern void func_87E01EB0(u8 *);

void func_87E00148(void) {
    (*(s32 *)((u8 *)(D_87E1BA20) + (0x24))) = 0;
    func_87E01EB0(D_87E1BA20 + 0x28);
    func_87E015C0(0);
}

extern void func_87E03CEC(u8 *);
extern void func_87F0F3E4(s32);
void func_87E00184(void) {
    func_87F0F3E4((*(s32 *)((u8 *)(D_87E1BA20) + (0))));
    func_87E03CEC(D_87E1BA20 + 0x2B0);
    (*(s32 *)((u8 *)(D_87E1BA20) + (0x24))) = 1;
}

extern void func_87E03D28(s32);
extern void func_87F0F390(s32);
void func_87E001CC(void) {
    func_87E03D28((s32)(D_87E1BA20 + 0x2B0));
    func_87F0F390(*(s32 *)D_87E1BA20);
}

extern void func_87E04A14(u8 *);

void func_87E00204(void) {
    (*(s32 *)((u8 *)(D_87E1BA20) + (0x24))) = 3;
    func_87E04A14(D_87E1BA20 + 0x4B8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E0023C.s")

s32 func_87E0023C(s32);
extern void func_87E06D8C(u8 *, s32);
extern void func_87E07AC4(u8 *, s32);
void func_87E015C0(s32 arg0);
void func_87E0027C(void) {
    (*(s32 *)((u8 *)(D_87E1BA20) + (0x24))) = 4;
    func_87E06D8C(D_87E1BA20 + 0x734, (*(s32 *)((u8 *)(D_87E1BA20) + (0))));
    func_87E07AC4(D_87E1BA20 + 0x734, func_87E0023C((*(s32 *)((u8 *)(D_87E1BA20) + (0)))));
    func_87E015C0(1);
}

extern void func_87E08BEC(u8 *, s32);

void func_87E002E4(void) {
    (*(s32 *)((u8 *)(D_87E1BA20) + (0x24))) = 5;
    func_87E08BEC(D_87E1BA20 + 0x8C4, (*(s32 *)((u8 *)(D_87E1BA20) + (0))));
}

extern void StageFade_StartFromTransparent(s32);
extern void func_800225C4(s32);

void func_87E00320(s32 *arg0) {
    (*(s32 *)((u8 *)(D_87E1BA20) + (0x1C))) = 0xFF;
    *arg0 = 2;
    StageFade_StartFromTransparent(0xF);
    func_800225C4(0xF);
}

extern void func_80021ED8(s32);
s32 func_8002806C();

void func_87E00360(void) {
    if (func_8002806C() != 0x48) {
        func_80021ED8(0x48);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E00394.s")

extern void func_8003C6B8(s32);
extern void GeoRender_AdvanceFrameCounter();

void func_87E00590(void) {
    GeoRender_AdvanceFrameCounter();
    func_8003C6B8((*(s32 *)((u8 *)(D_87E1BA20) + (0x20))));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E005C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E00648.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E0072C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E00A84.s")

extern s32 func_87E182A8(u8 *);
extern void func_87E17F48(void);
extern void func_87E0006C(void);
extern void func_87E00148(void);
extern void StageFade_StartFromTransparent(s32);
void func_87E00BDC(s32 *arg0) {
    s32 result;
    s32 state;
    result = func_87E182A8(D_87E1BA20 + 0x2260);
    if (result != 0) {
        state = result;
        func_87E17F48();
        switch (state) {
        case 1:
            func_87E0006C();
            func_87E00148();
            break;
        case 2:
            *(s32 *)(D_87E1BA20 + 0x1C) = 0xFE;
            *arg0 = 2;
            StageFade_StartFromTransparent(5);
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E00C70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E00D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E00E04.s")

extern s32 func_87E04114(u8 *);
extern void func_87E001CC(void);
extern void func_87E00D54(void);
extern void func_87E00148(void);
void func_87E00ED4(s32 arg0) {
    s32 temp_v0;
    temp_v0 = func_87E04114(D_87E1BA20 + 0x2B0);
    if (temp_v0 != 2) {
        func_87E001CC();
        switch (temp_v0) {
        case 0:
            func_87E00D54();
            return;
        case 1:
            func_87E00148();
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E00F4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E0101C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E01128.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E0123C.s")

extern void func_87E0123C(s32 *);
u8 StageContext_GetFadeMode(void);
s32 func_87E0132C(s32 arg0) {
    s32 sp1C;

    sp1C = arg0;
    switch (arg0) {                                 /* irregular */
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            sp1C = 1;
        }
        break;
    case 1:
        func_87E0123C(&sp1C);
        break;
    case 2:
        if (StageContext_GetFadeMode() == 1) {
            sp1C = 3;
        }
        break;
    }
    return sp1C;
}

extern void func_87E00A84();
s32 func_87E0132C(s32);
extern void func_800086A4(s32);
extern void StageFade_StartFromOpaque(s32);
u32 func_87F0F468(void);
void func_80064D28(void);
void func_87E013AC(void) {
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        if (func_87F0F468() == -1U) {
            func_80064D28();
        }
        var_s0 = func_87E0132C(var_s0);
        func_87E00A84();
    } while (var_s0 != 3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_303990/func_87E01424.s")

void func_87E015C0(s32 arg0)
{
  s32 temp_v1;
  if (((!D_87E1BA20) && (!D_87E1BA20)) && (!D_87E1BA20))
  {
  }
  temp_v1 = *((s32 *) (((u8 *) D_87E1BA20) + 0x10));
  if (arg0 != temp_v1)
  {
    *((s32 *) (((u8 *) D_87E1BA20) + 0x14)) = temp_v1;
    *((s32 *) (((u8 *) D_87E1BA20) + 0x10)) = arg0;
    *((s32 *) (((u8 *) D_87E1BA20) + 0x18)) = 0;
  }
}

extern void func_87C03B60(u8 *, s32, s32);

void func_87E015F4(s32 arg0, s32 arg1) {
    func_87C03B60(D_87E1BA20 + 0x3074, arg0, arg1);
}

extern void func_87F02340(s32 *);
extern u8 D_80126420;
extern u8 D_87E1B9C0;
extern u8 D_87E1B9D8;
extern u8 D_87E1B9F0;
extern u8 D_87E1BA08;
void func_87E01628(void) {
    func_87F02340(&D_80126420);
    func_87F02340(&D_87E1B9C0);
    func_87F02340(&D_87E1B9D8);
    func_87F02340(&D_87E1B9F0);
    func_87F02340(&D_87E1BA08);
}

u8 *func_87E0167C(void) {
    return D_87E1BA20 + 0x2234;
}

extern void func_87F0DBFC(u8 *, s32, u8, s32);

void func_87E0168C(s32 arg0, u8 arg1, s32 arg2) {
    func_87F0DBFC(D_87E1BA20 + 0x30F4, arg0, arg1, arg2);
}

u8 *func_87E016C8(void) {
    return D_87E1BA20 + 0x3108;
}

s32 func_87E016D8(void *arg0)
{
  s32 var_v1;
  u8 temp_v0;
  ;
  var_v1 = 0;
  if ((*((u8 *) (((u8 *) arg0) + 0x2182))) & 1)
  {
    var_v1 = 1;
  }
  if ((*((u8 *) (((u8 *) arg0) + 0x2182))) & 2)
  {
    var_v1 += 1;
  }
  if ((*((u8 *) (((u8 *) arg0) + 0x2182))) & 4)
  {
    var_v1 += 1;
  }
  if ((*((u8 *) (((u8 *) arg0) + 0x2182))) & 8)
  {
    var_v1 += 1;
  }
  return var_v1;
}
#endif
