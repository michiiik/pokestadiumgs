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
extern s32 D_8012B364;
extern u8 D_8012B368[];
extern u8 D_8012B386;
extern u8 D_8012B39E;
extern u8 D_8012B3B6;
extern u8 D_8012B3CE;
extern u8 D_8012B3E8[];
extern u32 D_8012B3F8;

extern void *Fragment_Load(u32 pool, u32 source, u32 end);
extern s32 Fragment_LoadAndCall(u32 pool, u32 source, u32 end, s32 arg3,
                                void *arg4);
extern u8 D_8AC00000[];
extern u8 D_8AB00000[];
extern u8 fragment43_ROM_START[];
extern u8 fragment44_ROM_START[];
extern u8 fragment45_ROM_START[];
extern u8 fragment46_ROM_START[];
extern u8 fragment2_ROM_START[];
extern u8 fragment3_ROM_START[];
extern u8 fragment4_ROM_START[];
extern u8 fragment26_ROM_START[];
extern u8 fragment27_ROM_START[];
extern u8 fragment47_ROM_START[];
extern u8 fragment48_ROM_START[];
extern u8 fragment49_ROM_START[];
extern u8 fragment50_ROM_START[];
extern u8 fragment51_ROM_START[];
extern u8 fragment52_ROM_START[];
extern u8 fragment53_ROM_START[];
extern u8 fragment54_ROM_START[];
extern u8 fragment55_ROM_START[];
extern u8 fragment56_ROM_START[];
extern u8 fragment57_ROM_START[];
extern u8 fragment59_ROM_START[];
extern u8 fragment60_ROM_START[];
extern u8 fragment61_ROM_START[];
extern u8 fragment62_ROM_START[];
extern u8 fragment63_ROM_START[];
extern u8 fragment64_ROM_START[];
extern u8 fragment65_ROM_START[];
extern u8 fragment66_ROM_START[];

#define MINIGAME_POOL(addr) ((((u32)(addr) & 0x0FF00000) >> 20) - 0x10)
#define D_81A00000 ((u8 *)0x81A00000)
#define D_8009F870 ((u8 *)0x8009F870)
#define D_800A5B00 ((s16 *)0x800A5B00)
#define D_87C00000 ((u8 *)0x87C00000)
#define D_87D00000 ((u8 *)0x87D00000)
#define D_87E00000 ((u8 *)0x87E00000)
#define D_86000000 ((u8 *)0x86000000)
#define D_86100000 ((u8 *)0x86100000)
#define D_86200000 ((u8 *)0x86200000)
#define D_86300000 ((u8 *)0x86300000)
#define D_86400000 ((u8 *)0x86400000)
#define D_86500000 ((u8 *)0x86500000)
#define D_86600000 ((u8 *)0x86600000)
#define D_86700000 ((u8 *)0x86700000)
#define D_86800000 ((u8 *)0x86800000)
#define D_86900000 ((u8 *)0x86900000)
#define D_86A00000 ((u8 *)0x86A00000)
#define D_86B00000 ((u8 *)0x86B00000)
#define D_8AC00000 ((u8 *)0x8AC00000)
#define D_8AB00000 ((u8 *)0x8AB00000)

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

/*
 * Build the controller/result flags consumed by the loaded minigame code.
 * The four halfwords at 0x21A6 in the player records are signed status
 * values.  A negative status (or a zero third argument) selects the live
 * controller mask; otherwise the corresponding player is left untouched.
 */
void Minigame_BuildControllerResult(u8 *state, u8 *result, s32 useAllPlayers) {
    s32 i;

    *(s16 *)result = 8;

    if ((s16)*(u16 *)(state + 0x21A6) < 0 &&
        (s16)*(u16 *)(state + 0x21BE) < 0 &&
        (s16)*(u16 *)(state + 0x21D6) < 0 &&
        (s16)*(u16 *)(state + 0x21EE) < 0) {
        result[2] = 2;
    } else {
        switch ((s8)state[0x2181]) {
        case 0:
            result[2] = 1;
            break;
        case 1:
            result[2] = 2;
            break;
        case 2:
        case 3:
            result[2] = 3;
            break;
        default:
            result[0xE] = 0;
            break;
        }
    }

    result[0xE] = 0;
    for (i = 0; i != 4; i += 2) {
        u8 controllerMask = state[0x2182];
        u8 sourceBit = (u8)(1 << i);
        s16 firstStatus = *(s16 *)(state + 0x21A6 + (i * 0x18));

        if (firstStatus < 0 || useAllPlayers == 0) {
            if (controllerMask & sourceBit) {
                result[0xE] |= sourceBit;
            } else {
                result[0xE] |= (u8)(1 << (i + 4));
            }
        }

        {
            u8 secondBit = (u8)(1 << (i + 1));
            s16 secondStatus = *(s16 *)(state + 0x21A6 + (i * 0x18) + 0x18);

            if (secondStatus < 0 || useAllPlayers == 0) {
                if (controllerMask & secondBit) {
                    result[0xE] |= secondBit;
                } else {
                    result[0xE] |= (u8)(1 << (i + 5));
                }
            }
        }
    }

    result[0x14] = state[0x2183];
}

void Minigame_UpdatePlayerCounters(void) {
    void (*handler)(void *, s8);

    handler = (void (*)(void *, s8))func_80003240((void *)func_87F097B0);
    handler((void *)D_801291E0, D_8012B363);
}

/* Advance the minigame result handshake after a loaded game callback.
 *
 * D_8012B364 is the pending result state: values 1 and 2 are acknowledged
 * only by the corresponding callback result.  Any other result clears the
 * handshake and resets the shared player record.  When all four player
 * statuses are not simultaneously resolved, the common result fragment is
 * loaded and its per-player completion bit is reflected in the four status
 * bytes at D_8012B386..D_8012B3CE.
 */
void Minigame_AdvanceResultHandshake(s32 callbackResult, s32 *outResult,
                                     s32 useAllPlayers) {
    u8 *state = D_801291E0;
    u8 *result = D_8012B3E8;
    s32 negativeStatusCount;
    s32 i;

    if (state[0x2180] == 4) {
        *outResult = 0xFF;
        return;
    }

    if (D_8012B364 == 1) {
        if (callbackResult == 1) {
            D_8012B364 = 0;
        }
    } else if (D_8012B364 == 2) {
        if (callbackResult == 2) {
            negativeStatusCount = 0;
            for (i = 0; i < 4; i++) {
                if (*(s16 *)(state + 0x21A6 + i * 0x18) < 0) {
                    negativeStatusCount++;
                }
            }
            if (negativeStatusCount != 1) {
                Minigame_BuildControllerResult(state, result, useAllPlayers);
                Fragment_Load(
                    (((u32)D_8AC00000 & 0x0FF00000) >> 20) - 0x10,
                    (u32)fragment43_ROM_START, (u32)fragment44_ROM_START);
                Fragment_LoadAndCall(
                    (((u32)D_8AB00000 & 0x0FF00000) >> 20) - 0x10,
                    (u32)fragment45_ROM_START, (u32)fragment46_ROM_START,
                    0, result);

                if (result[0x0F] == 0) {
                    D_8012B386 |= 0x80;
                } else {
                    D_8012B386 &= 0x7F;
                }
                if (result[0x0F] == 1) {
                    D_8012B39E |= 0x80;
                } else {
                    D_8012B39E &= 0x7F;
                }
                if (result[0x0F] == 2) {
                    D_8012B3B6 |= 0x80;
                } else {
                    D_8012B3B6 &= 0x7F;
                }
                if (result[0x0F] == 3) {
                    D_8012B3CE |= 0x80;
                } else {
                    D_8012B3CE &= 0x7F;
                }
                Minigame_UpdatePlayerCounters();
            }
        } else {
            D_8012B364 = 0;
        }
    } else {
        D_8012B364 = 0;
    }

    if (D_8012B364 == 0) {
        Minigame_ResetPlayerRecord(D_8012B368);
    }
    *outResult = -1;
}

void Minigame_UpdateResultState(u8 *state) {
    u8 *result = D_8012B3E8;
    s32 resultState;

    switch (*(s32 *)(state + 0x2184)) {
    case 3:
    case 5:
        *(s16 *)result = 6;
        resultState = *(s32 *)(state + 0x2200);
        break;
    case 4:
        *(s16 *)result = 4;
        resultState = *(s32 *)(state + 0x2204);
        Minigame_MapControllerButtons(state, result);
        break;
    default:
        *(s16 *)result = 6;
        resultState = *(s32 *)(state + 0x2200);
        break;
    }

    switch (resultState) {
    case 0:
        result[2] = 1;
        break;
    case 1:
        result[2] = 2;
        break;
    case 2:
    case 3:
        result[2] = 3;
        break;
    }
}

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

static void Minigame_RunRoundCase(s32 round, u8 *state, s32 *result) {
    u32 pool;
    s32 loadedResult;

    switch (round) {
    case -1:
    case 0xFE:
        pool = MINIGAME_POOL(D_8AC00000);
        Minigame_UpdateResultState(state);
        Fragment_Load(pool, (u32)fragment43_ROM_START,
                      (u32)fragment44_ROM_START);
        loadedResult = Fragment_LoadAndCall(
            MINIGAME_POOL(D_8AB00000), (u32)fragment45_ROM_START,
            (u32)fragment46_ROM_START, 0, D_8012B3E8);
        (void)loadedResult;
        if (D_8012B3F8 != 0) {
            *(s32 *)(state + 0x2184) = 6;
        }
        *result = -1;
        return;
    case 1:
        Fragment_Load(MINIGAME_POOL(D_87C00000),
                      (u32)fragment48_ROM_START,
                      (u32)fragment49_ROM_START);
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86000000), (u32)fragment47_ROM_START,
            (u32)fragment48_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    case 2:
        Minigame_UpdateControllerState(state, state[0x2182]);
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86500000), (u32)fragment53_ROM_START,
            (u32)fragment54_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    case 5:
        Minigame_UpdateControllerState(state, state[0x2182]);
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86600000), (u32)fragment54_ROM_START,
            (u32)fragment55_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    case 0:
        Fragment_Load(MINIGAME_POOL(D_87D00000),
                      (u32)fragment65_ROM_START,
                      (u32)fragment66_ROM_START);
        Fragment_Load(MINIGAME_POOL(D_86100000),
                      (u32)fragment49_ROM_START,
                      (u32)fragment50_ROM_START);
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86100000), (u32)fragment49_ROM_START,
            (u32)fragment50_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    case 3:
        Fragment_Load(MINIGAME_POOL(D_87D00000),
                      (u32)fragment65_ROM_START,
                      (u32)fragment66_ROM_START);
        Fragment_Load(MINIGAME_POOL(D_87C00000),
                      (u32)fragment49_ROM_START,
                      (u32)fragment50_ROM_START);
        Minigame_UpdateControllerState(state, state[0x2182]);
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86200000), (u32)fragment50_ROM_START,
            (u32)fragment51_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    case 4:
        Fragment_Load(MINIGAME_POOL(D_87D00000),
                      (u32)fragment65_ROM_START,
                      (u32)fragment66_ROM_START);
        Fragment_Load(MINIGAME_POOL(D_87C00000),
                      (u32)fragment49_ROM_START,
                      (u32)fragment50_ROM_START);
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86300000), (u32)fragment51_ROM_START,
            (u32)fragment52_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    case 6:
        Fragment_Load(MINIGAME_POOL(D_87D00000),
                      (u32)fragment65_ROM_START,
                      (u32)fragment66_ROM_START);
        Fragment_Load(MINIGAME_POOL(D_87C00000),
                      (u32)fragment49_ROM_START,
                      (u32)fragment50_ROM_START);
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86400000), (u32)fragment52_ROM_START,
            (u32)fragment53_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    case 7:
        Fragment_Load(MINIGAME_POOL(D_87C00000),
                      (u32)fragment48_ROM_START,
                      (u32)fragment49_ROM_START);
        Minigame_UpdateControllerState(state, state[0x2182]);
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86900000), (u32)fragment59_ROM_START,
            (u32)fragment60_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    case 8:
        Minigame_UpdateControllerState(state, state[0x2182]);
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86700000), (u32)fragment55_ROM_START,
            (u32)fragment56_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    case 9:
        Fragment_Load(MINIGAME_POOL(D_87C00000),
                      (u32)fragment48_ROM_START,
                      (u32)fragment49_ROM_START);
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86A00000), (u32)fragment60_ROM_START,
            (u32)fragment61_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    case 10:
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86800000), (u32)fragment56_ROM_START,
            (u32)fragment57_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    case 11:
        Fragment_Load(MINIGAME_POOL(D_87C00000),
                      (u32)fragment48_ROM_START,
                      (u32)fragment49_ROM_START);
        *result = Fragment_LoadAndCall(
            MINIGAME_POOL(D_86B00000), (u32)fragment61_ROM_START,
            (u32)fragment62_ROM_START, 0, state);
        Minigame_AdvanceResultHandshake(*result, result, 0);
        return;
    default:
        return;
    }
}

void Game_State10_Minigame(s32 initialize) {
    u8 *state = D_801291E0;
    s32 round;

    main_pool_push_state(0x6D696E69);
    Fragment_Load(MINIGAME_POOL(D_81A00000),
                  (u32)fragment3_ROM_START, (u32)fragment4_ROM_START);
    Fragment_Load(MINIGAME_POOL((u8 *)0x87F00000),
                  (u32)fragment64_ROM_START, (u32)fragment65_ROM_START);
    Fragment_Load(MINIGAME_POOL((u8 *)0x81000000),
                  (u32)fragment26_ROM_START, (u32)fragment27_ROM_START);
    Fragment_Load(MINIGAME_POOL((u8 *)0x81900000),
                  (u32)fragment2_ROM_START, (u32)fragment3_ROM_START);

    Minigame_StateInit(state);
    Minigame_ProcessInput();
    Minigame_SetModeDefaults(D_8012B3E8);

    if (initialize == 0) {
        round = -1;
    } else if (initialize == 1) {
        u8 old = D_8009F870[0];
        u8 next = (u8)(old + 1);
        if (next >= 12) {
            next = 0;
        }
        D_8009F870[0] = next;
        state[0x2181] = 1;
        state[0x2180] = 4;
        state[0x2182] = 0xF;
        Minigame_ProcessPlayerEvents(state, 0xF, NULL);
        round = D_800A5B00[next];
    } else {
        round = -1;
    }

    for (;;) {
        main_pool_push_state(0x7A6D676D);
        Minigame_UpdateControllerState(state, state[0x2182]);
        Minigame_ResetControllerPoll(state);
        Minigame_RunRoundCase(round, state, &round);
        main_pool_pop_state(0x7A6D676D);
        if (round == -1) {
            break;
        }
    }

    Minigame_ResetRoundPlayers(state);
    func_80035424(2);
    main_pool_pop_state(0x6D696E69);
}
#endif
