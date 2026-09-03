#include "global.h"


#ifdef VERSION_US
extern void main_pool_push_state(s32 arg0);
extern void main_pool_pop_state(s32 arg0);
extern void Gfx_InitDisplayListBuffers(s32 arg0, s32 arg1);
extern void func_800082E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern s32 func_80047588(s32 arg0, s32 arg1);
extern u32 D_8FE00118;
extern u8 D_1000000[];
extern u8 D_81000000[];
extern u8 D_446E30[];
extern u8 D_447D00[];
extern u8 fragment26_ROM_START[];
extern u8 fragment27_ROM_START[];
extern u8 *Asset_LoadToSegment(s32 id, u8 *rom_start, u8 *rom_end, s32 arg3);
extern u8 *Fragment_Load(s32 id, u8 *rom_start, u8 *rom_end);
extern void func_80047610(void);
extern void Gfx_FreeDisplayListBuffers(void);
s32 fragment28_main(UNUSED s32 arg0, UNUSED s32 arg1) {
    main_pool_push_state(0x4241544C);
    Gfx_InitDisplayListBuffers(0x30000, 0);
    func_800082E0(0, 1, 3, 1, 2, 1);
    D_8FE00118 = func_80047588(7, 0);
    Asset_LoadToSegment((((u32)&D_1000000 & 0x0F000000) >> 24), D_446E30, D_447D00, 0);
    Fragment_Load((((u32)&D_81000000 & 0x0FF00000) >> 20) - 0x10, fragment26_ROM_START, fragment27_ROM_START);
    func_80047610();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4241544C);
    return 0;
}
#pragma C_FUNCTION_PADDING(8)
#endif
