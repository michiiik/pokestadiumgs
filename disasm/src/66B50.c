#include "global.h"

extern u8 D_81600000[];
extern u8 D_81800000[];
extern u8 D_82800000[];
extern u8 fragment4_ROM_START[];
extern u8 fragment5_ROM_START[];
extern u8 fragment10_ROM_START[];
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];

extern void *Fragment_Load(u32 pool, u32 source, u32 end);
extern s32 Fragment_LoadAndCall(u32 pool, u32 source, u32 end, s32 arg3,
                                void *arg4);

#ifdef VERSION_US
typedef struct State04Query {
    u8 byte0;
    u8 byte1;
    u8 flag;
    u8 padding;
    s32 value;
} State04Query;

typedef struct State04Exit {
    s16 value;
    u8 byte0;
    u8 byte1;
    u8 flag;
    u8 padding[3];
} State04Exit;

void Game_State04_Run(void) {
    s32 result;
    s32 i;
    State04Query query;
    State04Exit exit;
    struct {
        u16 type;
        u16 padding;
        u32 value;
    } descriptor = {0, 0, 0x826E0400};

    main_pool_push_state(0x656D736C);
    Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10,
                  (u32)fragment11_ROM_START, (u32)fragment12_ROM_START);
    Fragment_Load((((u32)D_81800000 & 0x0FF00000) >> 20) - 0x10,
                  (u32)fragment4_ROM_START, (u32)fragment5_ROM_START);
    result = Fragment_LoadAndCall(
        (((u32)D_82800000 & 0x0FF00000) >> 20) - 0x10,
        (u32)fragment10_ROM_START, (u32)fragment11_ROM_START, 0, &descriptor);
    main_pool_pop_state(0x656D736C);

    if (result >= 0 && result < 4) {
        func_80064C94(result);
        Audio_EnableModeFlag();
        Audio_ResetRequestId();

        main_pool_push_state(0x656D626B);
        func_80055948(3);
        func_80054210(&query);
        exit.value = (s16)query.value;
        exit.byte0 = query.byte0;
        exit.byte1 = query.byte1;
        exit.flag = (query.flag & 1) != 0;
        main_pool_pop_state(0x656D626B);

        main_pool_push_state(0x656D756C);
        Audio_WaitForPendingTasks();
        Display_ClearFramebufferLine(1);
        Display_WaitForFrames(3);
        Audio_SetProcessingEnabled(1);
        func_80050994(&exit);
        result = GbTower_RecvExitMesg();
        func_80050B40(&exit);
        Display_ClearFramebufferLine(1);
        Display_WaitForFrames(3);
        Audio_SetProcessingEnabled(0);
        if (result != 0) {
            Game_ShutdownAndLoadFragment(func_80064C88(), result);
        }
        main_pool_pop_state(0x656D756C);

        main_pool_push_state(0x656D626B);
        for (i = 0; i < 16; i++) {
            func_8005777C();
        }
        for (i = 0; i < 4; i++) {
            if (func_80064C88() == i) {
                GbTower_StartPortSession(func_80064C88());
            } else {
                GbTower_UpdatePortState(i);
            }
        }
        func_80055948(3);
        func_80054210(&query);
        query.byte0 = exit.byte0;
        query.byte1 = exit.byte1;
        query.value = exit.value;
        func_80054248(&query);
        func_80051D64(0x14, 0);
        func_80054E48(3);
        main_pool_pop_state(0x656D626B);
    }

    Game_SetState(3);
}
#endif
