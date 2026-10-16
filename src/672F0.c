#include "global.h"

#ifdef VERSION_US
extern u8 D_81600000[];
extern u8 D_81800000[];
extern u8 D_82800000[];
extern u8 D_81A00000[];
extern u8 D_81B00000[];
extern u8 D_81000000[];
extern u8 D_82400000[];

extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment4_ROM_START[];
extern u8 fragment5_ROM_START[];
extern u8 fragment10_ROM_START[];
extern u8 fragment3_ROM_START[];
extern u8 fragment87_ROM_START[];
extern u8 fragment88_ROM_START[];
extern u8 fragment26_ROM_START[];
extern u8 fragment27_ROM_START[];
extern u8 fragment13_ROM_START[];
extern u8 fragment14_ROM_START[];

extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void Fragment_Load(s32, void *, void *);
extern s32 Fragment_LoadAndCall(s32, void *, void *, s32, void *);
extern void Game_SetState(s32);

void func_800666F0(void) {
    s32 ret;
    struct {
        s16 unk0;
        s16 unk2;
        s32 unk4;
    } sp2C;

    main_pool_push_state(0x6D79726D);
    Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10, fragment11_ROM_START, fragment12_ROM_START);
    Fragment_Load((((u32)D_81800000 & 0x0FF00000) >> 20) - 0x10, fragment4_ROM_START, fragment5_ROM_START);

    sp2C.unk0 = 0x11;
    sp2C.unk4 = 0x42A10585;
    sp2C.unk2 = 0;

    ret = Fragment_LoadAndCall((((u32)D_82800000 & 0x0FF00000) >> 20) - 0x10, fragment10_ROM_START, fragment11_ROM_START, 0, &sp2C);
    main_pool_pop_state(0x6D79726D);

    main_pool_push_state(0x6D79726D);
    Fragment_Load((((u32)D_81A00000 & 0x0FF00000) >> 20) - 0x10, fragment3_ROM_START, fragment4_ROM_START);
    Fragment_Load((((u32)D_81B00000 & 0x0FF00000) >> 20) - 0x10, fragment87_ROM_START, fragment88_ROM_START);
    Fragment_Load((((u32)D_81000000 & 0x0FF00000) >> 20) - 0x10, fragment26_ROM_START, fragment27_ROM_START);
    Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10, fragment11_ROM_START, fragment12_ROM_START);

    if (ret >= 0 && ret < 4) {
        Fragment_LoadAndCall((((u32)D_82400000 & 0x0FF00000) >> 20) - 0x10, fragment13_ROM_START, fragment14_ROM_START, ret, NULL);
    }

    main_pool_pop_state(0x6D79726D);
    Game_SetState(3);
}
#endif

