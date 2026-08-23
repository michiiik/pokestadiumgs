#include "global.h"


#ifdef VERSION_US
extern void *func_80003240(void *table);
extern void func_87F0EFA0(void);
extern void func_87F0EDDC(void);
extern void func_87F097B0(void);
extern void func_87F0EE0C(void);
extern void func_87F0F390(void);
extern void func_87F0F3E4(void);
extern u8 D_801291E0[];
extern s8 D_8012B363;

void Minigame_ProcessPlayerEvents(void *player, s32 event, void *context) {
    void (*handler)(void *, u8, void *);

    handler = (void (*)(void *, u8, void *))func_80003240((void *)func_87F0EFA0);
    handler(player, (u8)event, context);
}

void Minigame_UpdateControllerState(void *player, s32 event) {
    void (*handler)(void *, u8);

    handler = (void (*)(void *, u8))func_80003240((void *)func_87F0EDDC);
    handler(player, (u8)event);
}

void Minigame_ResetPlayerRecord(u8 *record) {
    record[0x1E] &= 0x1F;
    record[0x36] = 7;
    record[0x36] &= 0x1F;
    record[0x4E] &= 0x1F;
    record[0x66] &= 0x1F;
    *(u32 *)(record + 0x00) = 7;
    *(u32 *)(record + 0x68) = 0;
    record[0x05] = 0;
    record[0x06] = 0;
    record[0x07] = 1;
    record[0x6E] = 0;
    *(u32 *)(record + 0x20) = 0;
    *(u32 *)(record + 0x38) = 0;
    *(u32 *)(record + 0x50) = 0;
    *(u32 *)(record + 0x08) = 0;
}

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

void Minigame_StateInit(u8 *state) {
    state[0x2183] = 5;
    state[0x2180] = 0;
    state[0x2181] = 1;
    state[0x2182] = 1;
    *(u32 *)(state + 0x2184) = 0;
    Minigame_ResetPlayerRecord(state + 0x2188);
    Minigame_ResetPlayerSubstate((s32 *)(state + 0x21F8));
}

void Minigame_SetModeDefaults(u8 *mode) {
    *(s16 *)mode = 4;
    mode[0x0E] = 1;
}

void Minigame_MapControllerButtons(u8 *state, u8 *input) {
    u8 buttons = state[0x2182];

    input[0x0E] = 0;
    if (buttons & 0x01) {
        input[0x0E] |= 0x01;
    }
    if (buttons & 0x02) {
        input[0x0E] |= 0x02;
    }
    if (buttons & 0x04) {
        input[0x0E] |= 0x04;
    }
    if (buttons & 0x08) {
        input[0x0E] |= 0x08;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_80072264.s")

void Minigame_UpdatePlayerCounters(void) {
    void (*handler)(void *, s8);

    handler = (void (*)(void *, s8))func_80003240((void *)func_87F097B0);
    handler((void *)D_801291E0, D_8012B363);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/func_800723FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Minigame_UpdateResultState.s")

void Minigame_ProcessInput(void) {
    void (*handler)(void *);

    handler = (void (*)(void *))func_80003240((void *)func_87F0EE0C);
    handler((void *)D_801291E0);
}

void Minigame_ResetControllerPoll(void *input) {
    void (*handler)(void *);

    handler = (void (*)(void *))func_80003240((void *)func_87F0F390);
    handler(input);
}

void Minigame_ResetRoundPlayers(void *state) {
    void (*handler)(void *);

    handler = (void (*)(void *))func_80003240((void *)func_87F0F3E4);
    handler(state);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/72C30/Game_State10_Minigame.s")
#endif
