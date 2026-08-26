#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_800635E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063620.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063660.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063690.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_800636C0.s")

s32 func_80063754(s32 arg0) { s32 *value = &arg0; arg0 &= 0xFF; if (arg0 == 0x9E || (arg0 >= 0xB5 && arg0 < 0xBE)) return 1; return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_8006378C.s")

extern u8 D_8009830A[];
u8 func_800637C0(u8 arg0) { s32 index = arg0; if ((arg0 > 0) && (arg0 < 0xFC)) return D_8009830A[index * 22]; return 0; }

extern u8 D_80099E03[];
u8 func_80063804(u8 arg0) { s32 index = arg0; if ((arg0 > 0) || (arg0 < 0xFC)) return D_80099E03[index]; return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063838.s")

extern u8 D_80098311[];
u8 func_8006397C(u8 arg0) { s32 index = arg0; if ((arg0 > 0) && (arg0 < 0xFC)) return D_80098311[index * 22]; return 0; }

extern u8 D_80098312[];
u8 func_800639C0(u8 arg0) { s32 index = arg0; if ((arg0 > 0) && (arg0 < 0xFC)) return D_80098312[index * 22]; return 0; }

extern u8 D_80098316[];
u8 func_80063A04(u8 arg0) { s32 index = arg0; if ((arg0 > 0) && (arg0 < 0xFC)) return D_80098316[index * 22]; return 0; }

extern u8 D_80098317[];
u8 func_80063A48(u8 arg0) { s32 index = arg0; if ((arg0 > 0) && (arg0 < 0xFC)) return D_80098317[index * 22]; return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063A8C.s")

extern u8 D_8009D278[];
u8 func_80063B7C(u8 arg0) { s32 index = arg0; if ((arg0 > 0) && (arg0 < 0xFC)) return D_8009D278[index * 12]; return 0; }

extern u8 D_8009D27C[];
s32 func_80063BB8(u8 arg0) { s32 index = arg0; if ((arg0 > 0) && (arg0 < 0xFC)) return *(s32 *)(D_8009D27C + index * 12); return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063BF4.s")

void func_80063C90(u8 arg0, unsigned short arg1)
{
  u8 *new_var2;
  int new_var4;
  u8 *new_var3;
  int new_var;
  new_var = func_80062F98(arg1 & 0xFF) & 0xFF;
  new_var3 = &arg0;
  new_var2 = new_var3;
  new_var4 = new_var;
  func_80063BF4(*new_var2, new_var4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063CC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063D54.s")

void func_80063EE4(u8 arg0, s32 arg1)
{
  s32 *new_var2;
  s32 new_var;
  new_var2 = &arg1;
  new_var = *new_var2;
  func_80063CC4(arg0, func_80063044(new_var & 0xFF) & 0xFF);
}

void func_80063F18(u8 arg0, s32 arg1)
{
  s32 *new_var;
  new_var = &arg1;
  func_80063D54(arg0, func_80063044((*new_var) & 0xFF) & (0xFF & 0xFFFFu));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063F4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80064070.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_800640B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_800640F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_800641CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80064248.s")

extern void func_80064248(s32, s32, s32, s32);

void func_800643CC(s32 arg0, s32 arg1, s32 arg2) {
    func_80064248(arg0 & 0xFF, arg1 & 0xFF, arg2 & 0xFF, 0xFF);
}

extern void func_80064248(s32, s32, s32, s32);

void func_80064404(s32 arg0, s32 arg1, s32 arg2) {
    func_80064248(arg0 & 0xFF, arg1 & 0xFF, arg2 & 0xFF, 4);
}

extern void func_80064248(s32, s32, s32, s32);

void func_8006443C(s32 arg0, s32 arg1, s32 arg2) {
    func_80064248(arg0 & 0xFF, arg1 & 0xFF, arg2 & 0xFF, 0x7F);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80064474.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80064520.s")

s32 func_8006456C(s32 arg0) { s32 *value = &arg0; if (((*value) & 0x2FFF) == 0x2AAA) return 1; return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80064590.s")

s32 func_8006461C(s32 arg0) { s32 temp_v0 = arg0 & 0xFF; s32 *value = &arg0; if (temp_v0 & 0xF) return 1; if (temp_v0 & 0xF0) return 2; return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80064650.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_800646C8.s")

s32 func_80064700(s32 arg0) {
    s32 *ptr = &arg0;
    s32 value = *ptr & 0xFF;
    if (value == 1) {
        value = 0xC9;
    } else {
        value = value + 0xFC;
    }
    return value & 0xFFFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80064728.s")

extern void *D_800A5160;
extern void *func_8004B7A4(s32);
s32 func_800647C8(u8 arg0) {
    void *v;
    v = func_8004B7A4(arg0);
    if (v) {
        return (s32)v;
    }
    return (s32)&D_800A5160;
}

extern u8 D_8009D280[];
s32 func_80064800(u8 arg0) { s32 index = arg0; if ((arg0 > 0) && (arg0 < 0xFC)) return *(s32 *)(D_8009D280 + index * 12); return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_8006483C.s")
#endif
