#include "global.h"

extern s32 D_8009DEDC[];
extern u16 D_8009DEF0[];
extern u16 D_8009DEF8[];

/* Maps the four state-8 mode values to the compact callback result used by
 * Game_State08_Run.  The default is the original unsigned -1 sentinel. */
s32 func_800668D0(s32 mode) {
    switch (mode) {
        case 1:
            return 0;
        case 2:
            return 1;
        case 4:
            return 2;
        case 3:
            return 3;
        default:
            return -1;
    }
}

/* Looks up the state-8 callback value in the five-entry table. */
s32 func_80066924(s32 index) {
    if (index > 0 && index < 5) {
        return D_8009DEDC[index];
    }
    return 0;
}

#ifdef VERSION_US
/*
 * Translate a state-8 mode value through the compact mode table.  The
 * original routine compares only the low halfword of its first argument
 * against D_8009DEF0's entries, then returns the matching table entry from
 * the same slot.  A zero result is retained when no entry matches.
 */
s32 func_8006694C(s32 mode, void *unused) {
    u16 key = (u16)mode;
    u16 *entry = D_8009DEF0;

    (void)unused;
    while (entry != (u16 *)D_8009DEF8) {
        if ((u16)func_800668D0(*entry) == key) {
            return *entry;
        }
        entry++;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/674D0/func_800669C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/674D0/Game_State08_Run.s")
#endif
