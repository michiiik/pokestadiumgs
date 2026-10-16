#include "global.h"


#ifdef VERSION_US
extern s32 D_8009DEC0;

void func_80065D90(s32 arg0) {
    D_8009DEC0 = arg0;
}

extern u8 D_81600000[];
extern u8 D_81800000[];
extern u8 D_82100000[];

extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment4_ROM_START[];
extern u8 fragment5_ROM_START[];
extern u8 fragment25_ROM_START[];
extern u8 fragment26_ROM_START[];

extern void func_80057944(u8);
extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void Fragment_Load(s32, void *, void *);
extern s32 Fragment_LoadAndCall(s32, void *, void *, s32, void *);
extern void Game_SetState(s32);

void func_80065D9C(void) {
    s32 i;
    s32 ret;

    for (i = 0; i < 4; i++) {
        func_80057944(i);
    }

    main_pool_push_state(0x70736C64);
    Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10, fragment11_ROM_START, fragment12_ROM_START);
    Fragment_Load((((u32)D_81800000 & 0x0FF00000) >> 20) - 0x10, fragment4_ROM_START, fragment5_ROM_START);

    ret = Fragment_LoadAndCall((((u32)D_82100000 & 0x0FF00000) >> 20) - 0x10, fragment25_ROM_START, fragment26_ROM_START, D_8009DEC0, NULL);
    D_8009DEC0 = ret;

    switch (ret) {
        case 0:
            Game_SetState(2);
            break;
        case 4:
            Game_SetState(9);
            break;
        case 1:
            Game_SetState(8);
            break;
        case 2:
            Game_SetState(16);
            break;
        case 6:
            Game_SetState(15);
            break;
        case 3:
            Game_SetState(5);
            break;
        case 5:
            Game_SetState(10);
            break;
        case 9:
            Game_SetState(6);
            break;
        case 7:
            Game_SetState(7);
            break;
        case 8:
            Game_SetState(4);
            break;
        default:
            Game_SetState(1);
            break;
    }

    main_pool_pop_state(0x70736C64);
}
#endif

