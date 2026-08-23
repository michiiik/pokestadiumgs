#include "global.h"

extern u32 D_8009DEA0;

extern u32 func_800657B0(void);
extern void func_80065220(s32 x, s32 y);
extern void func_80065974(s32 count);
extern void Audio_ResetRequestId(void);

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65E20/func_80065220.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/65E20/func_800657B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/65E20/func_80065814.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/65E20/func_80065974.s")

void Game_State01_Loop(void) {
    u32 packed;
    u16 cycle;
    u8 result;
    u8 x;
    u8 y;

    if (Game_GetState() != 1) {
        return;
    }

    cycle = 0;
    while (Game_GetState() == 1) {
        packed = func_800657B0();
        y = (packed >> 16) & 0xFF;
        x = (packed >> 8) & 0xFF;
        result = packed & 0xFF;
        D_8009DEA0 = y;

        main_pool_push_state(0x6C6F6F70);
        if (result == 1) {
            func_80065974(cycle);
            cycle = (cycle + 1) & 0xFFFF;
        } else if (result == 2) {
            func_80065220(x, y);
            Audio_ResetRequestId();
        } else {
            Game_SetState(2);
        }
        main_pool_pop_state(0x6C6F6F70);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/65E20/Game_State17_Boot.s")
#endif
