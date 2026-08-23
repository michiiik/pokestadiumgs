#include "global.h"

extern u8 D_81600000[];
extern u8 D_81800000[];
extern u8 D_82800000[];
extern u8 D_81A00000[];
extern u8 D_81B00000[];
extern u8 D_81000000[];
extern u8 D_82400000[];
extern u8 fragment3_ROM_START[];
extern u8 fragment4_ROM_START[];
extern u8 fragment10_ROM_START[];
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment13_ROM_START[];
extern u8 fragment14_ROM_START[];
extern u8 fragment26_ROM_START[];
extern u8 fragment27_ROM_START[];
extern u8 fragment87_ROM_START[];
extern u8 fragment88_ROM_START[];

extern void *Fragment_Load(u32 pool, u32 source, u32 end);
extern s32 Fragment_LoadAndCall(u32 pool, u32 source, u32 end, s32 arg3,
                                void *arg4);

void Game_State07_Run(void) {
    s32 result;
    u32 pool816 = (((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10;

    main_pool_push_state(0x6D79726D);
    Fragment_Load(pool816, (u32)fragment11_ROM_START, (u32)fragment12_ROM_START);
    Fragment_Load((((u32)D_81800000 & 0x0FF00000) >> 20) - 0x10,
                 (u32)fragment4_ROM_START, (u32)fragment5_ROM_START);

    /* State 7 enters the shared menu fragment with a 0x11/0x42A10585
     * descriptor in its outgoing argument area. */
    {
        struct {
            u16 type;
            u16 padding;
            u32 value;
        } descriptor = {0x11, 0, 0x42A10585};
        result = Fragment_LoadAndCall(
            (((u32)D_82800000 & 0x0FF00000) >> 20) - 0x10,
            (u32)fragment10_ROM_START, (u32)fragment11_ROM_START,
            0, &descriptor);
    }
    (void)result;

    main_pool_pop_state(0x6D79726D);
    main_pool_push_state(0x6D79726D);
    Fragment_Load((((u32)D_81A00000 & 0x0FF00000) >> 20) - 0x10,
                 (u32)fragment3_ROM_START, (u32)fragment4_ROM_START);
    Fragment_Load((((u32)D_81B00000 & 0x0FF00000) >> 20) - 0x10,
                 (u32)fragment87_ROM_START, (u32)fragment88_ROM_START);
    Fragment_Load((((u32)D_81000000 & 0x0FF00000) >> 20) - 0x10,
                 (u32)fragment26_ROM_START, (u32)fragment27_ROM_START);

    if (result >= 0 && result < 4) {
        Fragment_LoadAndCall(
            (((u32)D_82400000 & 0x0FF00000) >> 20) - 0x10,
            (u32)fragment13_ROM_START,
                             (u32)fragment14_ROM_START, 0, NULL);
    }
    main_pool_pop_state(0x6D79726D);
    Game_SetState(3);
}


#ifdef VERSION_US
#endif
