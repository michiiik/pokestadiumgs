#include "global.h"

extern s32 D_80128C00;
extern s32 D_8009DFB0;
extern void *Fragment_Load(u32 pool, u32 source, u32 end);
extern s32 Fragment_LoadAndCall(u32 pool, u32 source, u32 end, s32 arg3,
                                void *arg4);
extern s32 func_80064C88(void);
extern s32 func_80064C94(s32 value);
extern void func_80041E2C(void);
extern s32 func_80041C98(s32 value);
extern void func_80057908(s32 value);
extern void func_80057944(s32 value);
extern void func_8005A0F4(s32 value);
extern s32 func_8005D92C(s32 value);
extern u8 fragment4_ROM_START[];
extern u8 fragment5_ROM_START[];
extern u8 fragment10_ROM_START[];
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment31_ROM_START[], fragment32_ROM_START[], fragment33_ROM_START[];
extern u8 fragment34_ROM_START[], fragment35_ROM_START[], fragment36_ROM_START[];
extern u8 fragment37_ROM_START[], fragment38_ROM_START[], fragment39_ROM_START[];
extern u8 fragment43_ROM_START[], fragment44_ROM_START[], fragment45_ROM_START[];
extern u8 fragment46_ROM_START[], fragment47_ROM_START[];
extern u8 fragment64_ROM_START[], fragment65_ROM_START[];
extern u8 fragment79_ROM_START[], fragment80_ROM_START[], fragment81_ROM_START[];
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
#define D_88100000 ((u8 *)0x88100000)
#define D_88200000 ((u8 *)0x88200000)
#define D_88300000 ((u8 *)0x88300000)
#define D_88400000 ((u8 *)0x88400000)
#define D_88500000 ((u8 *)0x88500000)
#define D_88600000 ((u8 *)0x88600000)
#define D_88700000 ((u8 *)0x88700000)
#define D_88800000 ((u8 *)0x88800000)
#define D_88900000 ((u8 *)0x88900000)
#define D_88A00000 ((u8 *)0x88A00000)
#define D_8AC00000 ((u8 *)0x8AC00000)
#define D_8AE00000 ((u8 *)0x8AE00000)

#define STATE05_POOL(address) ((((u32)(address) & 0x0FF00000) >> 20) - 0x10)
#define D_80128C60 (*(volatile s32 *)0x80128C60)
#define D_80128C64 (*(volatile s32 *)0x80128C64)
#define D_8009DFA0 ((void *)0x8009DFA0)
#define D_8009DFA8 ((void *)0x8009DFA8)

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

void Game_State05_Run(void) {
    s32 result;
    s32 callbackResult;
    s32 state;
    s32 loopState;
    s32 callbackArg = 8;
    s32 mode;
    u8 gameMode;

    main_pool_push_state(0x4353454C);
    Fragment_Load(STATE05_POOL(D_81600000), (u32)fragment11_ROM_START,
                  (u32)fragment12_ROM_START);
    Fragment_Load(STATE05_POOL(D_81800000), (u32)fragment4_ROM_START,
                  (u32)fragment5_ROM_START);
    result = Fragment_LoadAndCall(STATE05_POOL(D_82800000),
                                  (u32)fragment10_ROM_START,
                                  (u32)fragment11_ROM_START, -1,
                                  D_8009DFA0);
    main_pool_pop_state(0x4353454C);
    if (result == -1) {
        return;
    }

    func_80064C94(result);
    D_80128C60 = 7;
    main_pool_push_state(0x4C414243);
    Fragment_Load(STATE05_POOL(D_88000000), (u32)fragment29_ROM_START,
                  (u32)fragment30_ROM_START);
    func_80041E2C();
    gameMode = (u8)func_80064C88();
    main_pool_push_state(0x47424D4F);
    func_80057908(gameMode);
    func_8005A0F4(gameMode);

    mode = 0;
    if (D_80128C60 != 8) {
        loopState = 1;
        do {
            main_pool_push_state(0x4C414250);
            state = D_80128C60;
            switch (state) {
                /* jtbl_800A58E0 maps state 1 to the controller loop. */
                case 1:
                    callbackArg = state;
                    mode = 0;
                    main_pool_push_state(0x424F434F);
                    Fragment_Load(STATE05_POOL(D_88600000),
                                  (u32)fragment35_ROM_START,
                                  (u32)fragment36_ROM_START);
                    D_80128C64 = func_80041C98(5);
                    do {
                        result = Fragment_LoadAndCall(
                            STATE05_POOL(D_88300000),
                            (u32)fragment32_ROM_START,
                            (u32)fragment33_ROM_START, mode,
                            (void *)0x98);
                        mode = (u16)result;
                        state = D_80128C60;
                        if (state == 2) {
                            Fragment_LoadAndCall(
                                STATE05_POOL(D_88400000),
                                (u32)fragment33_ROM_START,
                                (u32)fragment34_ROM_START, 0,
                                (void *)mode);
                            mode = 1;
                            D_80128C60 = loopState;
                            state = loopState;
                        } else if (state == 3) {
                            Fragment_Load(STATE05_POOL(D_8AC00000),
                                          (u32)fragment43_ROM_START,
                                          (u32)fragment44_ROM_START);
                            result = func_8005D92C(gameMode);
                            Fragment_LoadAndCall(
                                STATE05_POOL(D_8AE00000),
                                (u32)fragment46_ROM_START,
                                (u32)fragment47_ROM_START, result,
                                (void *)mode);
                            mode = 2;
                            D_80128C60 = loopState;
                            state = loopState;
                        }
                    } while (state == loopState);
                    main_pool_pop_state(0x4F474157);
                    main_pool_pop_state(0x424F434F);
                    break;

                /* state 0 and state 7 share .L8006D670. */
                case 0:
                case 7:
                    callbackArg = state;
                    Fragment_Load(STATE05_POOL(D_88A00000),
                                  (u32)fragment39_ROM_START,
                                  (u32)fragment40_ROM_START);
                    Fragment_Load(STATE05_POOL(D_88700000),
                                  (u32)fragment36_ROM_START,
                                  (u32)fragment37_ROM_START);
                    Fragment_Load(STATE05_POOL(D_88800000),
                                  (u32)fragment37_ROM_START,
                                  (u32)fragment38_ROM_START);
                    Fragment_Load(STATE05_POOL(D_88900000),
                                  (u32)fragment38_ROM_START,
                                  (u32)fragment39_ROM_START);
                    result = Fragment_LoadAndCall(
                        STATE05_POOL(D_88200000), (u32)fragment31_ROM_START,
                        (u32)fragment32_ROM_START, 0, NULL);
                    D_80128C60 = result;
                    break;

                /* state 6 selects the single loaded callback. */
                case 6:
                    Fragment_Load(STATE05_POOL(D_88A00000),
                                  (u32)fragment39_ROM_START,
                                  (u32)fragment40_ROM_START);
                    result = Fragment_LoadAndCall(
                        STATE05_POOL(D_88100000), (u32)fragment30_ROM_START,
                        (u32)fragment31_ROM_START, callbackArg, NULL);
                    D_80128C60 = result;
                    break;

                case 4:
                    callbackArg = state;
                    Fragment_Load(STATE05_POOL(D_88800000),
                                  (u32)fragment37_ROM_START,
                                  (u32)fragment38_ROM_START);
                    Fragment_Load(STATE05_POOL(D_88900000),
                                  (u32)fragment38_ROM_START,
                                  (u32)fragment39_ROM_START);
                    result = Fragment_LoadAndCall(
                        STATE05_POOL(D_88500000), (u32)fragment34_ROM_START,
                        (u32)fragment35_ROM_START, 0, NULL);
                    D_80128C60 = result;
                    break;

                /* state 5 selects the GB-mode callback. */
                case 5:
                    callbackArg = state;
                    Fragment_Load(STATE05_POOL(D_81600000),
                                  (u32)fragment11_ROM_START,
                                  (u32)fragment12_ROM_START);
                    Fragment_Load(STATE05_POOL(D_81800000),
                                  (u32)fragment4_ROM_START,
                                  (u32)fragment5_ROM_START);
                    result = Fragment_LoadAndCall(
                        STATE05_POOL(D_82800000), (u32)fragment10_ROM_START,
                        (u32)fragment11_ROM_START, gameMode, D_8009DFA8);
                    if (result != -1) {
                        func_80064C94(result);
                    }
                    D_80128C60 = 7;
                    break;

                default:
                    break;
            }

            main_pool_pop_state(0x4C414250);
            callbackResult = func_80064C88();
            if (callbackResult != gameMode) {
                func_80057944(gameMode);
                main_pool_pop_state(0x47424D4F);
                gameMode = (u8)func_80064C88();
                main_pool_push_state(0x47424D4F);
                func_80057908(gameMode);
                func_8005A0F4(gameMode);
            }
        } while (D_80128C60 != 8);
    }

    func_80057944(gameMode);
    main_pool_pop_state(0x47424D4F);
    main_pool_pop_state(0x4C414243);
}

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
