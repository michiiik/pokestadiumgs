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

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063C90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063CC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063EE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80063F18.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80064700.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_80064728.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_800647C8.s")

extern u8 D_8009D280[];
s32 func_80064800(u8 arg0) { s32 index = arg0; if ((arg0 > 0) && (arg0 < 0xFC)) return *(s32 *)(D_8009D280 + index * 12); return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/641E0/func_8006483C.s")
#endif
