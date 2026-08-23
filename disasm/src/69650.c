#include "global.h"

extern void _bzero(void *dst, s32 size);
extern s32 func_8006A3B8(u16 value);
extern s32 func_8006A400(u16 value);

#ifdef VERSION_US
/* Initialize the compact scene descriptor and copy its 9-byte source key. */
void func_80068A50(void *descriptor, const void *source) {
    u8 *dst = (u8 *)descriptor;
    const u8 *src = (const u8 *)source;
    s32 i;

    if (descriptor == NULL) {
        return;
    }
    _bzero(descriptor, 0x5C);
    dst[0] = 0;
    for (i = 0; i < 9; i++) {
        dst[4 + i] = src[i];
    }
}

/* Select the scene command and participant slot associated with a state. */
s32 func_80068AB0(u32 state) {
    u16 command = 0xFFFF;
    u16 slot = 4;

    switch (state) {
        case 0:
            command = 0x200;
            break;
        case 1:
            command = 0x202;
            slot = 1;
            break;
        case 2:
            command = 0x202;
            slot = 2;
            break;
        case 3:
            command = 0x202;
            slot = 3;
            break;
        case 4:
            command = 0x202;
            break;
        case 5:
            command = 0x220;
            break;
        case 6:
            command = 0x201;
            slot = 1;
            break;
        case 7:
            command = 0x201;
            slot = 2;
            break;
        case 8:
            command = 0x201;
            slot = 3;
            break;
        case 9:
            command = 0x201;
            break;
        case 10:
            command = 0x203;
            break;
        case 11:
            command = 0x210;
            break;
        default:
            break;
    }

    func_8006A3B8(command);
    return func_8006A400(slot);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/69650/func_80068B78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/69650/func_80068CBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/69650/Game_State16_Run.s")
#endif
