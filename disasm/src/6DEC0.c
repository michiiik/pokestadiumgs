#include "global.h"

extern s32 D_80128C00;
extern s32 D_8009DFB0;
extern void *Fragment_Load(u32 pool, u32 source, u32 end);
extern s32 Fragment_LoadAndCall(u32 pool, u32 source, u32 end, s32 arg3,
                                void *arg4);
extern s32 func_80064C88(void);
extern s32 func_80064C94(s32 value);
extern u8 fragment4_ROM_START[];
extern u8 fragment5_ROM_START[];
extern u8 fragment10_ROM_START[];
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment29_ROM_START[];
extern u8 fragment30_ROM_START[];
extern u8 fragment40_ROM_START[];
extern u8 fragment41_ROM_START[];
extern u8 fragment88_ROM_START[];
extern u8 D_437610[];

#define D_81600000 ((u8 *)0x81600000)
#define D_81800000 ((u8 *)0x81800000)
#define D_82800000 ((u8 *)0x82800000)
#define D_81C00000 ((u8 *)0x81C00000)
#define D_88000000 ((u8 *)0x88000000)
#define D_88B00000 ((u8 *)0x88B00000)

/* Returns the current decoded frame counter used by the state-5 helpers. */
s32 func_8006D424(void) {
    return D_80128C00;
}

/* These hooks are intentionally empty; their argument is only present in the
 * original ABI and is saved into the caller's outgoing argument area. */
void func_8006D430(s32 arg0) {
    (void)arg0;
}

void func_8006D438(s32 arg0) {
    (void)arg0;
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6DEC0/func_8006D2C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6DEC0/Game_State05_Run.s")

void Game_State19_Run(void) {
    s32 result;
    u32 pool816 = (((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10;
    u32 pool818 = (((u32)D_81800000 & 0x0FF00000) >> 20) - 0x10;
    u32 pool828 = (((u32)D_82800000 & 0x0FF00000) >> 20) - 0x10;

    main_pool_push_state(0x4353454C);
    Fragment_Load(pool816, (u32)fragment11_ROM_START,
                  (u32)fragment12_ROM_START);
    Fragment_Load(pool818, (u32)fragment4_ROM_START,
                  (u32)fragment5_ROM_START);
    result = Fragment_LoadAndCall(
        pool828, (u32)fragment10_ROM_START, (u32)fragment11_ROM_START,
        -1, &D_8009DFB0);
    main_pool_pop_state(0x4353454C);

    if (result == -1) {
        return;
    }

    func_80064C94(result);
    main_pool_push_state(0x4C414243);
    Fragment_Load(
        (((u32)D_81C00000 & 0x0FF00000) >> 20) - 0x10,
        (u32)fragment88_ROM_START, (u32)D_437610);
    Fragment_Load(
        (((u32)D_88000000 & 0x0FF00000) >> 20) - 0x10,
        (u32)fragment29_ROM_START, (u32)fragment30_ROM_START);
    result = func_80064C88();
    Fragment_LoadAndCall(
        (((u32)D_88B00000 & 0x0FF00000) >> 20) - 0x10,
        (u32)fragment40_ROM_START, (u32)fragment41_ROM_START, result, NULL);
    main_pool_pop_state(0x4C414243);
}
#endif
