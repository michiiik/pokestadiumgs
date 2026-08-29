#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6DEC0/func_8006D2C0.s")

extern s32 D_80128C00; s32 func_8006D424(void) { return D_80128C00; }

void func_8006D430(s32 arg0) {}

void func_8006D438(s32 arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6DEC0/func_8006D440.s")

extern u8 D_81600000[]; extern u8 D_81800000[]; extern u8 D_82800000[]; extern u8 D_81C00000[]; extern u8 D_88000000[]; extern u8 D_88B00000[]; extern u8 D_8009DFB0[]; extern u8 D_437610[];
extern u8 fragment4_ROM_START[]; extern u8 fragment5_ROM_START[]; extern u8 fragment10_ROM_START[]; extern u8 fragment11_ROM_START[]; extern u8 fragment12_ROM_START[];
extern u8 fragment29_ROM_START[]; extern u8 fragment30_ROM_START[]; extern u8 fragment40_ROM_START[]; extern u8 fragment41_ROM_START[]; extern u8 fragment88_ROM_START[];
void main_pool_push_state(s32); void main_pool_pop_state(s32); void Fragment_Load(s32, void *, void *);
s32 Fragment_LoadAndCall(s32, void *, void *, s32, void *); void func_80064C94(s32); s32 func_80064C88(void);
void Game_State19_Run(void) {
    s32 result;
    main_pool_push_state(0x4353454C);
    Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10, fragment11_ROM_START, fragment12_ROM_START);
    Fragment_Load((((u32)D_81800000 & 0x0FF00000) >> 20) - 0x10, fragment4_ROM_START, fragment5_ROM_START);
    result = Fragment_LoadAndCall((((u32)D_82800000 & 0x0FF00000) >> 20) - 0x10, fragment10_ROM_START, fragment11_ROM_START, -1, D_8009DFB0);
    main_pool_pop_state(0x4353454C);
    if (result != -1) {
        func_80064C94(result);
        main_pool_push_state(0x4C414243);
        Fragment_Load((((u32)D_81C00000 & 0x0FF00000) >> 20) - 0x10, fragment88_ROM_START, D_437610);
        Fragment_Load((((u32)D_88000000 & 0x0FF00000) >> 20) - 0x10, fragment29_ROM_START, fragment30_ROM_START);
        Fragment_LoadAndCall((((u32)D_88B00000 & 0x0FF00000) >> 20) - 0x10, fragment40_ROM_START, fragment41_ROM_START, func_80064C88(), 0);
        main_pool_pop_state(0x4C414243);
    }
}
#endif
