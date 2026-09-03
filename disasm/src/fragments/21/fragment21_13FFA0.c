#include "global.h"


#ifdef VERSION_US
extern s16 D_82508F6E;
s32 func_82500020(s32 arg0, void *arg1) {
    if (arg0 != 0 && arg0 == 1) {
        if (D_82508F6E != 0) {
            *(u16 *)((u8 *)arg1 + 2) |= 2;
        } else {
            *(u16 *)((u8 *)arg1 + 2) &= 0xFFFD;
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 D_82508F80;
s32 func_82500064(s32 arg0, s32 arg1) { switch (arg0) { case 0: D_82508F80 = arg1; break; case 1: break; default: break; } return 0; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_8250008C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82500120.s")
#endif

#ifdef VERSION_US
extern s16 D_82508F6C;
s32 func_825001B4(s32 arg0, void *arg1) {
    if (arg0 != 0 && arg0 == 1) {
        if (D_82508F6C != 0) {
            *(u16 *)((u8 *)arg1 + 2) |= 2;
        } else {
            *(u16 *)((u8 *)arg1 + 2) &= 0xFFFD;
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825001F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825003DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825004A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82500780.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82500BC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82500CF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82500D24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82500D68.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82500EF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82501034.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825010F8.s")
#endif

#ifdef VERSION_US
extern u16 D_82508F88;
extern s16 D_82508F96;
extern s16 D_82508F98;
s32 func_82501244(s32 arg0, void *arg1) { s32 index; u8 *entry; index = *(s32 *)((u8 *)arg1 + 0x20); if ((arg0 != 0) && (arg0 == 1)) { entry = (u8 *)&D_82508F88 + index * 2; if ((*(s16 *)(entry + 0x34) == D_82508F96) && (*(s16 *)(entry + 0x38) == D_82508F98)) { *(u16 *)((u8 *)arg1 + 2) |= 2; } else { *(u16 *)((u8 *)arg1 + 2) &= 0xFFFD; } } return 0; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825012B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82501490.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825015D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82501754.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82501814.s")
#endif

#ifdef VERSION_US
extern void *D_80087200;

void func_82501CDC(void *arg0) {
    if ((*(u16 *)((u8 *)(D_80087200) + (8))) & 0x8000) {
        (*(s16 *)((u8 *)(arg0) + (4))) = 3;
        (*(s16 *)((u8 *)(arg0) + (6))) = 0;
        (*(s16 *)((u8 *)(arg0) + (8))) = 0;
        (*(s16 *)((u8 *)(arg0) + (0xC))) = 0xFF;
        (*(s16 *)((u8 *)(arg0) + (0xA))) = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82501D18.s")
#endif

#ifdef VERSION_US
extern void func_82501814(u16 *);
extern void func_82501D18(u16 *);
void func_82508268(void);
extern s16 D_82508F8C;
extern u16 D_82508F88;
void func_8250202C(void) {
    func_82508268();
    switch (D_82508F8C) {                           /* irregular */
    case 1:
        func_82501814(&D_82508F88);
        return;
    case 2:
        func_82501CDC(&D_82508F88);
        return;
    case 3:
        func_82501D18(&D_82508F88);
        return;
    }
}
#endif

#ifdef VERSION_US
extern s16 D_82508F8C;
extern u16 D_82508F88;
extern s32 D_82508F9C[];
extern void func_8250850C(void);
extern s32 func_8250865C(void);
extern void func_800503A4(s32);
void func_825020A8(void) { u32 index; if (D_82508F8C != 0) { func_8250850C(); if (func_8250865C() != 0) { index = D_82508F88 & 0xFF; func_800503A4(D_82508F9C[index]); } } }
#endif

#ifdef VERSION_US

s32 func_82502104(void) {
    return D_82508F8C == 0;
}
#endif

#ifdef VERSION_US
s32 func_82502114(void) {
    return D_82508F88;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502120.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502404.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502528.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502634.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502854.s")
#endif

#ifdef VERSION_US
s16 func_825028E8(u8 *arg0)
{
  s16 var_v1;
  u8 new_var;
  int new_var2;
  var_v1 = -1;
  if (arg0 != (0 & 0xFFFFFFFFFFFFFFFF))
  {
    new_var = *arg0;
    new_var2 = new_var * 0x98;
    var_v1 = (*((u8 *) (((u8 *) (arg0 + new_var2)) + (-0x94)))) - 1;
  }
  return var_v1;
}
#endif

#ifdef VERSION_US
s16 func_82502924(u8 *arg0) {
    s16 result = -1;
    u8 index;
    u32 offset;

    if (arg0) {
        index = *arg0;
        offset = index * 0x98;
        result = *(u8 *)(arg0 + offset - 0x93) - 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502960.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502DDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502E20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502E60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82502EBC.s")
#endif

void func_82503748(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82503750.s")
#endif

#ifdef VERSION_US
extern void func_80008648();
extern void func_800088DC();
extern void func_800503A4(s32);
extern void func_81700908();
extern void func_825020A8();
extern void func_82503750();
extern void func_8250771C();
s32 func_8250865C();
extern s32 D_82508D04;

void func_82503840(void) {
    func_800088DC();
    if (func_8250865C() == 0) {
        func_82503750();
        func_800503A4(D_82508D04);
        func_8250771C();
        func_81700908();
    }
    func_825020A8();
    func_80008648();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825038A4.s")
#endif

#ifdef VERSION_US
extern u8 D_82508D10[];
s32 func_82503954(s32 arg0) {
    s32 result = arg0;
    if ((arg0 >= 0) && (*(s16 *)(D_82508D10 + arg0 * 0x3C) == 0)) {
        result = -1;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82503988.s")
#endif

#ifdef VERSION_US
s32 func_82503DDC(void)
{
  s32 sp1C;
  u16 temp_v0;
  sp1C = 0;
  if (func_82507BBC() == 0)
  {
    return 0;
  }
  ;
  if ((*((u16 *) (((u8 *) D_80087200) + 8))) & 0x8000)
  {
    sp1C = 1;
  }
  else
    if ((*((u16 *) (((u8 *) D_80087200) + 8))) & 0x4000)
  {
    func_82507BD0();
    sp1C = -1;
    func_800226C0(3);
  }
  return sp1C;
}
#endif

#ifdef VERSION_US
extern s32 func_82502104(void);
extern s32 func_82502114(void);
s32 func_82503E50(void) { s32 result; result = 0; if (func_82502104() != 0) { if (func_82502114() == 0x201) { result = 2; } else { result = 1; } } return result; }
#endif

#ifdef VERSION_US
extern s32 func_82507CF4();
s32 func_82503E98(void) {
    s32 result = 0;
    if (func_82507CF4() != 0) {
        result = 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
s32 func_82503EC8(void) {
    s32 result = 0;
    if (func_82507CF4() != 0) {
        result = 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
s32 func_82503EF8(void) {
    s32 result = 0;
    if (func_82507CF4() != 0) {
        result = 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82503F28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825043AC.s")
#endif

#ifdef VERSION_US
extern void Fragment_LoadAndCall(s32, s32 *, s32 *, s32, s32);
s32 func_800718B8(s32);
extern u8 D_82C00000;
extern u8 fragment83_ROM_START;
extern u8 fragment84_ROM_START;

void func_825044D0(void) {
    Fragment_LoadAndCall(((u32) ((s32) &D_82C00000 & 0x0FF00000) >> 0x14) - 0x10, &fragment83_ROM_START, &fragment84_ROM_START, 0x300, func_800718B8(6));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82504524.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_825045EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_13FFA0/func_82504628.s")
#endif
