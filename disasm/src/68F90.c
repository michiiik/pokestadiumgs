#include "global.h"

extern s32 func_8006A3B8(u16 value);
extern s32 func_8006A400(u16 value);

#ifdef VERSION_US
/* Convert a packed scene selector into its command and participant slot. */
s32 func_80068390(u32 selector) {
    u16 command = 0xFFFF;
    u16 slot = 4;
    u32 group = selector & 0xFFFF0000;

    switch (group) {
        case 0x00010000:
            command = 0x103;
            break;
        case 0x00020000:
            command = 0x101;
            break;
        case 0x00030000:
            command = 0x100;
            break;
        case 0x00040000:
            command = 0x102;
            if ((u16)selector < 3) {
                slot = (u16)selector + 1;
            }
            break;
        case 0x00050000:
            command = 0x110;
            break;
        default:
            break;
    }

    func_8006A3B8(command);
    return func_8006A400(slot);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/68F90/func_80068464.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/68F90/Game_State13_Run.s")
#endif
