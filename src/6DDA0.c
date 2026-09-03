#include "global.h"


#ifdef VERSION_US
extern u8 D_80128BF0[];
extern u8 D_80128BF4[];
extern u8 D_80128BF8[];
extern u8 D_80128BFC[];
u8 *func_8006D1A0(u16 arg0) {
    u8 *result = NULL;
    switch (arg0) {
    case 0x100: result = D_80128BF0; break;
    case 0x200: result = D_80128BF0 + 2; break;
    case 0x300: result = D_80128BF4; break;
    case 0x400: result = D_80128BF4 + 2; break;
    case 0x500: result = D_80128BF8; break;
    case 0x600: result = D_80128BF8 + 2; break;
    case 0x700: result = D_80128BFC; break;
    }
    return result;
}

extern u8 D_80128BF0[]; extern void _bzero(void *, s32); void func_8006D240(void) { _bzero(D_80128BF0, 0xE); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6DDA0/func_8006D268.s")
#endif
