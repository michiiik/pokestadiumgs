#include "global.h"


#ifdef VERSION_US
extern void func_80015AB8(void);
extern void func_80018704(s32, s32);
void func_80021AC0(s32 arg0, s32 arg1) {
    if (arg0 || arg1) {
        /* intentionally empty */
    }
    func_80015AB8();
    func_80018704(0x41010000, 0x3F2147AE);
    func_80018704(0x41000000, 0x3F4F5C29);
}

extern void func_80021AC0(s32, s32);
extern void func_80028140(void);
extern void func_80035020(s32);
extern void func_800248A0(void);
extern void func_80018728(s32, s32);
extern void Audio_RenderNextBuffer(s32, s32, s32, s32);

void Audio_InitializeTaskState(void) {
    func_80021AC0(0, 0);
    func_80028140();
    func_80035020(2);
    func_800248A0();
    func_80018728(0xE40000FF, Audio_RenderNextBuffer);
}

void func_80021B50(void) {
    func_80018728(0x82010000, 0);
}

extern s32 D_80090090;
extern s32 func_80017AC0(void);
extern void func_80034FE0(void);
s32 Audio_BuildSchedulerTask(void) {
    s32 *address;
    address = &D_80090090;
    *address = func_80017AC0();
    func_80034FE0();
    if (*address == 0) {
        return 0;
    }
    return *address;
}

extern s32 func_800187AC(void);
extern void func_800239C8(void);
extern void func_80027490(void);
extern void Audio_UpdateDeferredSounds(void);
extern void Audio_UpdateCommandQueue(void);
extern u8 D_80090094;
extern s32 D_80090098;
extern u8 D_8009009C;
extern u8 D_800900A0;
extern u8 D_80090220;
extern u8 D_80090A54;
extern s8 D_80090B80;
extern s32 D_80094570;
void func_80021BBC(void) {
    s32 desired;
    s32 first;
    s32 second_value;
    if (D_80090094 != 0) {
        func_80018728(0x82010000, 0);
        D_80090B80 = 1;
        func_80018728(0x82020600, 0);
        func_80018704(0x41020000, 0x3F25E354);
        D_80090094 = 0;
    }
    switch ((u32)D_80094570) {
    default:
        goto default_value;
    case 1:
    case 2:
        goto one_or_two_steps;
    case 3:
        goto three_steps;
    }
one_or_two_steps:
    desired = 225;
    goto value_selected;
three_steps:
    desired = 150;
    goto value_selected;
default_value:
    desired = 113;
value_selected:
    if (desired != D_80090098) {
        first = D_80090220;
        if (first >= 3 || first == 0) {
            func_80018728(0x47010000, desired);
        } else {
            D_8009009C = 1;
        }
        if (D_80090A54 >= 3 || D_80090A54 == 0) {
            func_80018728(0x47030000, desired);
        } else {
            D_800900A0 = 1;
        }
    }
    D_80090098 = desired;
    D_80094570 = 0;
    if (D_8009009C != 0) {
        first = D_80090220;
        if (first >= 3 || first == 0) {
            func_80018728(0x47010000, D_80090098);
            D_8009009C = 0;
        }
    }
    second_value = D_80090A54;
    if (D_800900A0 != 0) {
        if (second_value >= 3 || D_80090A54 == 0) {
            func_80018728(0x47030000, D_80090098);
            second_value = D_80090A54;
            D_800900A0 = 0;
        }
    }
    first = D_80090220;
    if (first > 0 && first < 3) {
        D_80090220 = first + 1;
    }
    if (second_value > 0 && second_value < 3) {
        D_80090A54 = D_80090A54 + 1;
    }
    func_80027490();
    Audio_UpdateDeferredSounds();
    Audio_UpdateCommandQueue();
    func_800239C8();
    func_800187AC();
}
#endif
