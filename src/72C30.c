#include "global.h"


#ifdef VERSION_US
extern s32 func_87F0EFA0;
extern s32 (*func_80003240(s32 *))(s32 *);
void Minigame_ProcessPlayerEvents(s32 arg0, u8 arg1, s32 arg2) {
    ((void (*)(s32, u8, s32))(void *)func_80003240(&func_87F0EFA0))(arg0, arg1, arg2);
}

extern s32 func_87F0EDDC;
void Minigame_UpdateControllerState(s32 arg0, u8 arg1) {
    ((void (*)(s32, u8))(void *)func_80003240(&func_87F0EDDC))(arg0, arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_800720A8.s")

extern u8 D_8012B3F6;
void Minigame_SetPlayerMask(s8 arg0) {
    D_8012B3F6 = 1 << arg0;
}

void Minigame_ResetPlayerSubstate(s32 *arg0) {
    arg0[0] = 0;
    arg0[1] = 0;
    arg0[2] = 1;
    arg0[3] = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_80072184.s")

void Minigame_SetModeDefaults(u8 *arg0) {
    *(s16 *)(arg0 + 0) = 4;
    arg0[0xE] = 1;
}

void func_800721EC(u8 *arg0, u8 *arg1) {
    arg1[0xE] = 0;
    if (arg0[0x2182] & 1) arg1[0xE] |= 1;
    if (arg0[0x2182] & 2) arg1[0xE] |= 2;
    if (arg0[0x2182] & 4) arg1[0xE] |= 4;
    if (arg0[0x2182] & 8) arg1[0xE] |= 8;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_80072264.s")

extern u8 func_87F097B0;
extern u8 D_801291E0;
extern s8 D_8012B363;
void Minigame_UpdatePlayerCounters(void) {
    ((void (*)(void *, s8))(void *)func_80003240(&func_87F097B0))(&D_801291E0, D_8012B363);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_800723FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_80072650.s")

s32 (*func_80003240(s32 *))(s32 *);
extern u8 func_87F0EE0C;
void Minigame_ProcessInput(s32 arg0) {
    func_80003240(&func_87F0EE0C)(&D_801291E0);
}

extern u8 func_87F0F390;
void Minigame_ResetControllerPoll(s32 arg0) {
    func_80003240(&func_87F0F390)(arg0);
}

extern u8 func_87F0F3E4;
void Minigame_ResetRoundPlayers(s32 arg0) {
    func_80003240(&func_87F0F3E4)(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_800727D4.s")
#endif
