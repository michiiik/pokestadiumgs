#include "global.h"

#define D_801270A8 (*(s32 *)0x801270A8)
#define D_801270AC (*(void **)0x801270AC)

void func_80049ED0(void) {
}

#ifdef VERSION_US
void Input_SetRepeatController(void *controller) {
    D_801270A8 = 10;
    D_801270AC = controller;
}
#endif

#ifdef VERSION_US
u16 Input_GetRepeatedDPad(void) {
    u16 buttons = *(u16 *)((u8 *)D_801270AC + 8);

    if (buttons & 0x0800) {
        D_801270A8 = 10;
        return 0x0800;
    }
    if (buttons & 0x0400) {
        D_801270A8 = 10;
        return 0x0400;
    }
    if (buttons & 0x0200) {
        D_801270A8 = 10;
        return 0x0200;
    }
    if (buttons & 0x0100) {
        D_801270A8 = 10;
        return 0x0100;
    }

    if (--D_801270A8 > 0) {
        return 0;
    }
    D_801270A8 = 0;
    buttons = *(u16 *)((u8 *)D_801270AC + 6);
    if (buttons & 0x0800) {
        D_801270A8 = 2;
        return 0x0800;
    }
    if (buttons & 0x0400) {
        D_801270A8 = 2;
        return 0x0400;
    }
    if (buttons & 0x0200) {
        D_801270A8 = 2;
        return 0x0200;
    }
    if (buttons & 0x0100) {
        D_801270A8 = 2;
        return 0x0100;
    }
    return 0;
}
#endif
