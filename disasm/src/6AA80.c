#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_80069E80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_80069F20.s")

extern void func_80069F20();
void func_8006A13C(s32 arg0) { func_80069F20(arg0, 0, 0); }

extern void func_80069F20(void); void func_8006A160(void) { func_80069F20(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A180.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A1FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A278.s")

extern s32 D_8009DF70; void func_8006A2EC(void) { D_8009DF70 = 0; }

extern s32 D_8009DF70; s32 func_8006A2F8(u16 value){s32 result=0; s32 ptr=D_8009DF70; if(ptr!=0){*(u16 *)((u8 *)(u32)ptr+4)|=value; result=1;} return result;}

extern s32 D_8009DF70; s32 func_8006A328(u16 value){s32 result=0; s32 ptr=D_8009DF70; if(ptr!=0){*(u16 *)((u8 *)(u32)ptr+4)&=~value; result=1;} return result;}

extern s32 D_8009DF70;
s32 func_8006A35C(u16 value) { s32 result = 0; if (D_8009DF70 != 0) result = ((*(u16 *)((u8 *)(u32)D_8009DF70 + 4) & value) != 0); return result; }

s32 func_8006A388(void) { s32 result = 0; if (D_8009DF70 != 0 && (*(u16 *)((u8 *)(u32)D_8009DF70 + 4) & 1) != 0) result = 1; return result; }

s32 func_8006A3B8(u16 arg0) { s32 result = 0; if (D_8009DF70 != 0) { *(u16 *)((u8 *)(u32)D_8009DF70) = arg0; result = 1; } return result; }

s32 func_8006A3E0(void) { s32 result = 0xFFFF; if (D_8009DF70 != 0) result = *(u16 *)((u8 *)(u32)D_8009DF70); return result; }

s32 func_8006A400(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 2) = value; result = 1; } return result; }

s32 func_8006A424(void) { s32 result = 0; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 2); return result; }

extern void _bzero(void *, s32);
s32 func_8006A444(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 6) = value; _bzero((u8 *)(u32)D_8009DF70 + 0x3C, 0x44); result = 1; } return result; }

s32 func_8006A48C(void) { s32 result = -1; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 6); return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A4AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A51C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A5AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006A73C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AB68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AB8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006ABD8.s")

s32 func_8006AC28(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s32 *)((u8 *)(u32)D_8009DF70 + 0xC) = value; result = 1; } return result; }

s32 func_8006AC4C(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 0x12) = value; result = 1; } return result; }

s32 func_8006AC70(void) { s32 result = -1; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 0x12); return result; }

extern s32 func_8006CBA0(s32, s32);
s32 func_8006AC90(void) { s32 result = 0; s32 ptr = D_8009DF70; if (ptr != 0) result = func_8006CBA0(*(s16 *)((u8 *)(u32)ptr + 0x12), *(s16 *)((u8 *)(u32)ptr + 0x16)); return result; }

s32 func_8006ACCC(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 0x16) = value; result = 1; } return result; }

s32 func_8006ACF0(void) { s32 result = 0; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 0x16); return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AD10.s")

s32 func_8006AE90(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 0x14) = value; result = 1; } return result; }

s32 func_8006AEB4(void) { s32 result = -1; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 0x14); return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AED4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AF28.s")


s32 func_8006AF84(void) {
    return *(s32 *)((u8 *)(u32)D_8009DF70 + 0x1C);
}

s32 func_8006AF94(void) { s32 result = -1; s32 ptr = D_8009DF70; if (ptr != 0) result = *(s16 *)((u8 *)(u32)ptr + 0x10); return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AFB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006AFE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B07C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B0B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B428.s")

s32 func_8006B790(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(u8 *)((u8 *)(u32)D_8009DF70 + 0x1A) = value; result = 1; } return result; }

s32 func_8006B7B4(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(u8 *)((u8 *)(u32)D_8009DF70 + 0x1B) = value; result = 1; } return result; }

s32 func_8006B7D8(s32 value) { s32 result = 0; if (D_8009DF70 != 0) { *(s16 *)((u8 *)(u32)D_8009DF70 + 0x18) = value; result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B7FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B854.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006B928.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006BA74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006BAC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006BF78.s")

extern void func_8006BF78(s32); void func_8006C58C(void) { func_8006BF78(0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006C5AC.s")

extern void func_8006BF78(s32); void func_8006C644(void) { func_8006BF78(1); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006C664.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006C714.s")

extern void func_800029E0(void);
void func_8006C9C0(void) { func_800029E0(); if (D_8009DF70 != 0) *(s32 *)((u8 *)(u32)D_8009DF70 + 0x38) = 0; }

extern void *func_80002984(s32, s32);
void *func_8006C9F4(void) { void *result = func_80002984(0x440, 0); if (result != NULL) _bzero(result, 0x440); return result; }

extern void func_800029E0(void); void func_8006CA34(void) { func_800029E0(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CA54.s")

extern void func_800029E0(void); void func_8006CAC0(void) { func_800029E0(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CAE0.s")

extern void func_800029E0(void); void func_8006CB80(void) { func_800029E0(); }

s32 func_8006CBA0(s32 a,s32 b){s32 result=0; s32 next=a+1; if(b==next)result=1; return result;}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CBB8.s")

extern s16 D_8009DF74; void func_8006CBFC(void) { D_8009DF74 = 1; }

extern s16 D_8009DF74; void func_8006CC0C(void) { D_8009DF74 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CC18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CDA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CEE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006CF70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA80/func_8006D068.s")
#endif
