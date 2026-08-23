#include "global.h"

#define D_80128BF0 ((u8 *)0x80128BF0)

extern void _bzero(void *dst, s32 size);

#ifdef VERSION_US
/* Return the two-byte flag slot associated with a command group. */
u8 *func_8006D1A0(s32 command) {
    switch ((u16)command) {
        case 0x100:
            return D_80128BF0;
        case 0x200:
            return D_80128BF0 + 2;
        case 0x300:
            return D_80128BF0 + 4;
        case 0x400:
            return D_80128BF0 + 6;
        case 0x500:
            return D_80128BF0 + 8;
        case 0x600:
            return D_80128BF0 + 10;
        case 0x700:
            return D_80128BF0 + 12;
        default:
            return NULL;
    }
}

void func_8006D240(void) {
    _bzero(D_80128BF0, 0x0E);
}

/* Test whether the command's low-byte flag is set in its group slot. */
s32 func_8006D268(s32 command) {
    u16 key = (u16)command;
    u16 *slot = (u16 *)func_8006D1A0(key & 0xFF00);

    if (slot == NULL) {
        return 0;
    }
    return ((*slot & key) & 0xFF) != 0;
}
#endif
