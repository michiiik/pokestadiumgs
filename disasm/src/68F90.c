#include "global.h"

extern s32 func_8006A3B8(u16 value);
extern s32 func_8006A400(u16 value);
extern s32 func_8006A3E0(void);
extern s32 func_8006A424(void);
extern void func_80055948(s32 mode);
extern s32 func_8006218C(s32 kind, s32 arg1, s32 arg2, s32 arg3);
extern void func_8006249C(void *state, s32 enabled, s32 handle);
extern void func_80062304(s32 handle);
extern void func_80055028(void);

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

s32 func_80068464(void *context) {
    u8 *state = *(u8 **)((u8 *)context + 0x20);
    u16 first;
    u16 second;
    s32 handle;

    if (state[0x423] == 0) {
        return 0;
    }
    first = (u16)func_8006A3E0();
    second = (u16)func_8006A424();
    *(u16 *)(state + 0x488) = first;
    *(u16 *)(state + 0x48A) = second;
    func_80055948(3);
    handle = func_8006218C(0x1A, 0, 0, 1);
    func_8006249C(state, 1, handle);
    func_80062304(handle);
    func_80055028();
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/68F90/Game_State13_Run.s")
#endif
