#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Game_PollState.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064C88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064C94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064CB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064CC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064CD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064CDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Fragment_LoadAndCall.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064D28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Game_ShutdownAndLoadFragment.s")
#endif

void func_80064DF4(void) {
}

extern s32 D_8009DE94;
extern s32 D_80128BE4;

s32 Game_SetState(s32 state) {
    s32 previous = D_8009DE94;

    if (state != previous) {
        D_80128BE4 = previous;
        D_8009DE94 = state;
        return 1;
    }

    return 0;
}

s32 Game_GetState(void) {
    return D_8009DE94;
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064E38.s")
#endif

extern u8 D_82700000[];
extern u8 fragment22_ROM_START[];
extern u8 fragment23_ROM_START[];

void Game_State11_Options(void) {
    s32 result;

    main_pool_push_state(0x6F70746E);
    result = Fragment_LoadAndCall(
        ((((u32)D_82700000 & 0x0FF00000) >> 20) - 0x10),
        fragment22_ROM_START, fragment23_ROM_START, 0, 0);
    main_pool_pop_state(0x6F70746E);

    if (result == 0) {
        Game_SetState(2);
    } else {
        Game_SetState(1);
    }
}

extern s32 D_80128BE0;
extern s32 D_8009DE90;

void Game_ThreadInit(void) {
    __osSetFpcCsr(0x1000C01);
    func_8000644C();
    func_80035140(1);
    func_80035620();
    func_8004C020();
    func_80046980();
    func_80041B84();
    func_8006D240();
    Game_SetState(17);
    D_80128BE0 = -1;
    D_8009DE90 = 0;
    main_pool_push_state(0x47414D45);
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064F54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Game_Thread.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80065210.s")
#endif
