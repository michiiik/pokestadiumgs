#include "global.h"

extern u8 D_81600000[];
extern u8 D_82200000[];
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment17_ROM_START[];
extern u8 fragment18_ROM_START[];
extern s32 D_8009DEB0;

extern void *Fragment_Load(u32 pool, u32 source, u32 end);
extern s32 Fragment_LoadAndCall(u32 pool, u32 source, u32 end, s32 arg3,
                                void *arg4);

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/667B0/Game_State02_Run.s")
#if 0
void Game_State02_Run(void) {
    s32 result;
    s32 i;
    struct {
        u8 padding[0x32];
        s16 x;
        s16 y;
        u8 padding2[2];
        u16 flags;
    } descriptor;

    for (i = 0; i < 4; i++) {
        func_80057944(i & 0xFF);
    }

    main_pool_push_state(0x67626368);
    func_8006CC0C();
    Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10,
                  (u32)fragment11_ROM_START, (u32)fragment12_ROM_START);

    if (func_80064E38() == 1) {
        D_8009DEB0 = 0;
    }

    result = Fragment_LoadAndCall(
        (((u32)D_82200000 & 0x0FF00000) >> 20) - 0x10,
        (u32)fragment17_ROM_START, (u32)fragment18_ROM_START,
        D_8009DEB0, &descriptor);
    D_8009DEB0 = result;
    main_pool_pop_state(0x67626368);

    switch (result) {
        case 1:
            func_80064CB8(descriptor.x);
            func_80064CD0(descriptor.y);
            Game_SetState(14);
            break;
        case 2:
            Game_SetState(3);
            func_80065D90(1);
            break;
        case 3:
            Game_SetState(13);
            break;
        case 4:
            Game_SetState(11);
            break;
        case 5:
            if ((descriptor.flags & 0xFF00) == 0) {
                func_8006CBFC();
                Game_SetState(8);
            } else if ((descriptor.flags & 0xFF00) == 0x300) {
                func_8006CBFC();
                Game_SetState(9);
            } else {
                Game_SetState(3);
            }
            break;
        default:
            Game_SetState(1);
            break;
    }
}
#endif
#endif
