#include "global.h"

extern u8 fragment11_ROM_START[], fragment12_ROM_START[], fragment13_ROM_START[];
extern u8 fragment20_ROM_START[], fragment21_ROM_START[];
extern u8 fragment27_ROM_START[], fragment28_ROM_START[];
extern u8 fragment43_ROM_START[], fragment44_ROM_START[], fragment45_ROM_START[];
extern u8 fragment46_ROM_START[], fragment64_ROM_START[], fragment65_ROM_START[];
extern u8 fragment79_ROM_START[], fragment80_ROM_START[], fragment81_ROM_START[];
extern void *Fragment_Load(u32, u32, u32);
extern s32 Fragment_LoadAndCall(u32, u32, u32, s32, void *);
extern void func_800354B4(s32, s32, s32);
extern void Audio_RequestEvent(s32);
extern void *BattleScene_ResetParticipantModelFlags(s32);
extern void func_8006A1FC(void *);
extern void func_8006A3B8(u16);
extern u16 func_8006A3E0(void);
extern u16 func_8006A388(s32);
extern u16 func_8006A400(u16);
extern u16 func_8006A424(void);
extern void func_8006A444(s32);
extern void func_8006AB8C(u16, s32, s32);
extern void func_8006AC4C(u16);
extern void func_8006AC28(s32);
extern void func_8006ACCC(s32);
extern void func_8006ABD8(void *);
extern void func_8006AE90(s32);
extern void func_80026938(u16);
extern s32 func_8006B0B8(void);
extern void *func_8006BAC4(void);
extern s32 func_8006AEB4(void);
extern s32 func_8006C58C(void);
extern s32 func_8006C644(void);
extern s32 func_8006C664(void);
extern void Game_SetState(s32);

#define D_81400000 ((u8 *)0x81400000)
#define D_81600000 ((u8 *)0x81600000)
#define D_82600000 ((u8 *)0x82600000)
#define D_84100000 ((u8 *)0x84100000)
#define D_84200000 ((u8 *)0x84200000)
#define D_87F00000 ((u8 *)0x87F00000)
#define D_8AB00000 ((u8 *)0x8AB00000)
#define D_8AC00000 ((u8 *)0x8AC00000)
#define D_8AF00000 ((u8 *)0x8AF00000)
#define D_81100000 ((u8 *)0x81100000)
#define D_8009DED0 ((u32 *)0x8009DED0)

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/66DF0/Game_State06_Run.s")
#if 0
void Game_State06_Run(void) {
    u32 descriptor[4];
    u8 stateData[0x24];
    void *scene;
    u8 *sceneData;
    void *sceneArg;
    s32 state = 1;
    s32 callbackArg = 0;

    descriptor[0] = D_8009DED0[0]; descriptor[1] = D_8009DED0[1];
    descriptor[2] = D_8009DED0[2]; descriptor[3] = D_8009DED0[3];
    bzero(stateData, sizeof(stateData));
    main_pool_push_state(0x706D7063);
    scene = BattleScene_ResetParticipantModelFlags(0);
    func_8006A1FC(stateData);
    func_8006A3B8(0x400); func_8006ACCC(1);
    sceneData = *(u8 **)((u8 *)scene + 0x30);
    sceneArg = *(void **)((u8 *)scene + 0x2C);
    while (state != 0) {
        main_pool_push_state(0x706D6C70);
        switch (state) {
            case 1: {
                s32 result;
                u32 poolA = (((u32)D_8AC00000 & 0x0FF00000) >> 20) - 0x10;
                u32 poolB = (((u32)D_8AF00000 & 0x0FF00000) >> 20) - 0x10;
                func_800354B4(4, 0, 0); Audio_RequestEvent(7);
                Fragment_Load(poolA, (u32)fragment43_ROM_START, (u32)fragment44_ROM_START);
                result = Fragment_LoadAndCall(poolB, (u32)fragment44_ROM_START,
                    (u32)fragment45_ROM_START, callbackArg, sceneData);
                state = 2;
                if (result == 1) {
                    callbackArg = 1; func_8006A444(0xC);
                    func_8006A400((u16)(sceneData[0] + 0x19)); func_8006A3E0();
                    { u16 first = func_8006A424(); u16 second = func_8006A388(first);
                      func_8006AB8C(first, second, second); }
                    func_8006AC4C(sceneData[1]); func_8006ABD8(descriptor);
                    func_8006AC28(0); func_8006AE90(0x1B);
                } else if (result == 2) { callbackArg = 2; state = 6; }
                else { state = 0; callbackArg = 0; }
                break;
            }
            case 2: {
                u32 pool = (((u32)D_82600000 & 0x0FF00000) >> 20) - 0x10;
                func_800354B4(9, 0, 0);
                state = 3;
                if (func_8006C58C() != 0) {
                    Fragment_LoadAndCall(pool, (u32)fragment20_ROM_START,
                        (u32)fragment21_ROM_START, 1, sceneArg); func_8006B0B8(); }
                break;
            }
            case 3: {
                void *arg = func_8006BAC4();
                if (arg != NULL) {
                    u32 poolA = (((u32)D_84200000 & 0x0FF00000) >> 20) - 0x10;
                    u32 poolB = (((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10;
                    s32 result;
                    Fragment_Load(poolA, (u32)fragment80_ROM_START, (u32)fragment81_ROM_START);
                    Fragment_Load(poolB, (u32)fragment11_ROM_START, (u32)fragment12_ROM_START);
                    poolA = (((u32)D_81400000 & 0x0FF00000) >> 20) - 0x10;
                    result = Fragment_LoadAndCall(poolA, (u32)fragment12_ROM_START,
                        (u32)fragment13_ROM_START, 0, arg);
                    state = (result == 1) ? 4 : 1; sceneData[2] = (result == 1) ? 0 : 1;
                }
                break;
            }
            case 4: {
                u32 poolA = (((u32)D_81100000 & 0x0FF00000) >> 20) - 0x10;
                u32 poolB = (((u32)D_84100000 & 0x0FF00000) >> 20) - 0x10;
                s32 descriptorValue; s32 argValue; s32 mode; void *arg;
                mode = func_8006AEB4();
                func_80026938((u16)mode);
                func_800354B4(8, 0x12, 0);
                Audio_RequestEvent(0x5A);
                Fragment_Load(poolA, (u32)fragment27_ROM_START, (u32)fragment28_ROM_START);
                argValue = func_8006AEB4(); descriptorValue = func_8006C664();
                arg = (void *)(u32)argValue;
                Fragment_LoadAndCall(poolB, (u32)fragment79_ROM_START,
                    (u32)fragment80_ROM_START, descriptorValue, arg); state = 5;
                break;
            }
            case 5: {
                u32 pool = (((u32)D_82600000 & 0x0FF00000) >> 20) - 0x10;
                func_800354B4(10, 0, 0);
                if (func_8006C644() != 0) { state = 1;
                    Fragment_LoadAndCall(pool, (u32)fragment20_ROM_START,
                        (u32)fragment21_ROM_START, 2, sceneArg); }
                break;
            }
            case 6: {
                u32 pool = (((u32)D_87F00000 & 0x0FF00000) >> 20) - 0x10;
                Fragment_Load(pool, (u32)fragment64_ROM_START, (u32)fragment65_ROM_START);
                pool = (((u32)D_8AC00000 & 0x0FF00000) >> 20) - 0x10;
                Fragment_Load(pool, (u32)fragment43_ROM_START, (u32)fragment44_ROM_START);
                pool = (((u32)D_8AB00000 & 0x0FF00000) >> 20) - 0x10;
                Fragment_LoadAndCall(pool, (u32)fragment45_ROM_START,
                    (u32)fragment46_ROM_START, 0, descriptor); state = 1;
                break;
            }
            default: state = 0; break;
        }
        main_pool_pop_state(0x706D6C70);
    }
    main_pool_pop_state(0x706D7063); Game_SetState(3);
}
#endif
#endif
