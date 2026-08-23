#include "global.h"

extern u8 D_81600000[];
extern u8 D_81800000[];
extern u8 D_82100000[];
extern u8 fragment4_ROM_START[];
extern u8 fragment5_ROM_START[];
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment25_ROM_START[];
extern u8 fragment26_ROM_START[];
extern s32 D_8009DEC0;

extern void *Fragment_Load(u32 pool, u32 source, u32 end);
extern s32 Fragment_LoadAndCall(u32 pool, u32 source, u32 end, s32 arg3,
                                void *arg4);

void Game_State03_Run(void) {
    s32 result;
    s32 i;

    for (i = 0; i < 4; i++) {
        func_80057944(i);
    }

    main_pool_push_state(0x70736C64);
    Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10,
                 (u32)fragment11_ROM_START, (u32)fragment12_ROM_START);
    Fragment_Load((((u32)D_81800000 & 0x0FF00000) >> 20) - 0x10,
                 (u32)fragment4_ROM_START, (u32)fragment5_ROM_START);
    result = Fragment_LoadAndCall(
        (((u32)D_82100000 & 0x0FF00000) >> 20) - 0x10,
        (u32)fragment25_ROM_START, (u32)fragment26_ROM_START,
        D_8009DEC0, NULL);
    D_8009DEC0 = result;

    switch (result) {
        case 0:
            Game_SetState(2);
            break;
        case 1:
            Game_SetState(9);
            break;
        case 2:
            Game_SetState(8);
            break;
        case 3:
            Game_SetState(16);
            break;
        case 4:
            Game_SetState(15);
            break;
        case 5:
            Game_SetState(5);
            break;
        case 6:
            Game_SetState(10);
            break;
        case 7:
            Game_SetState(6);
            break;
        case 8:
            Game_SetState(7);
            break;
        case 9:
            Game_SetState(4);
            break;
        default:
            Game_SetState(1);
            break;
    }
    main_pool_pop_state(0x70736C64);
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/66990/func_80065D90.s")

#endif
