#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C088.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C09C.s")

extern s32 D_80097120; void func_8004C398(void) { D_80097120 = 0; }

void func_8004C3A4(s32 unused, u8 *arg1) { *(s32 *)arg1 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C3B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C3EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C468.s")

extern s32 D_80097120; s32 func_8004C4A4(void) { return D_80097120; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C4B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C504.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C54C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C594.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C5E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C7A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C874.s")

void func_8004C8A0(void) { func_8004C7A0(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C8C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C948.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004C990.s")

u16 func_8004CA10(u16 *arg0) { u16 value = 0; if (arg0 != NULL) { value = *arg0; } return value; }

u16 func_8004CA24(u16 *arg0) { u16 value = 0; if (arg0 != NULL) { value = arg0[1]; } return value; }

s32 func_8004CA38(u8 *arg0) { s32 value = -1; if (arg0 != NULL) { value = arg0[4]; } return value; }

s32 func_8004CA4C(u8 *arg0) { s32 value = -1; if (arg0 != NULL) { value = arg0[5]; } return value; }

u8 *func_8004CA60(u8 *arg0) { u8 *value = NULL; if (arg0 != NULL) { value = arg0 + 8; } return value; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CA74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CB28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004CB7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D150.s")

extern void func_8004D150(s32, s32, s32, s32, s32, s32);
void func_8004D19C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) { func_8004D150(a0, a1, a2, a3, 0, a4); }

extern void func_8004CB7C(s32, s32, s32, s32, s32, s32, s32, s32);
void func_8004D1C4(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) { func_8004CB7C(a0, a1, a2, a3, a4, a5, 0, a6); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D1FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D27C.s")

s32 func_8004D314(s32 arg0, s32 arg1) { s32 result = -1; if (arg0 == 0xEF && arg1 == 0) result = 0; return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D334.s")

extern s16 D_80128082;

void func_8004D40C(s32 arg0) {
    D_80128082 = (s16)arg0;
}

extern void *memcpy(void *, const void *, s32); void *func_8004D418(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D43C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D488.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D5B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D690.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D6D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D720.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D7F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D878.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004D998.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DA18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DA8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DAF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DB5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DC6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DCB4.s")

void func_8004DCFC(void) { func_8004DB5C(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DD1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DD64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DDAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DDF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DE3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DE84.s")

void func_8004DEF8(s32 arg0) { func_8004DE84(arg0, 0); }

void func_8004DF18(s32 arg0, s32 arg1) { func_8004DF38(arg0, arg1, 0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DF38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004DFEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004E018.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4CC20/func_8004E0F0.s")
#endif
