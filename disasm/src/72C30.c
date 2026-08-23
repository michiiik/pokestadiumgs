#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_ProcessPlayerEvents.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_UpdateControllerState.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_ResetPlayerRecord.s")

extern u8 D_8012B3F6;

void Minigame_SetPlayerMask(s8 player) {
    D_8012B3F6 = (u8)(1 << player);
}

void Minigame_ResetPlayerSubstate(s32 *substate) {
    substate[0] = 0;
    substate[1] = 0;
    substate[2] = 1;
    substate[3] = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_StateInit.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_SetModeDefaults.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_MapControllerButtons.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_80072264.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_UpdatePlayerCounters.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_800723FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_UpdateResultState.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_ProcessInput.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_ResetControllerPoll.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_ResetRoundPlayers.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Game_State10_Minigame.s")
#endif
