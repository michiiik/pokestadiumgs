#include "global.h"


#ifdef VERSION_US
extern u8 D_81600000[];
extern u8 D_81800000[];
extern u8 D_82800000[];

extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment4_ROM_START[];
extern u8 fragment5_ROM_START[];
extern u8 fragment10_ROM_START[];

extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void Fragment_Load(s32, void *, void *);
extern s32 Fragment_LoadAndCall(s32, void *, void *, s32, void *);
extern void func_80064C94(s32);
extern void Audio_EnableModeFlag(void);
extern void Audio_ResetRequestId(void);
extern void func_80055948(s32);
extern void func_80054210(void *);
extern void func_80054248(void *);
extern void Audio_WaitForPendingTasks(void);
extern void Display_ClearFramebufferLine(s32);
extern void Display_WaitForFrames(s32);
extern void Audio_SetProcessingEnabled(s32);
extern void func_80050994(void *);
extern s32 GbTower_RecvExitMesg(void);
extern void func_80050B40(void *);
extern s32 func_80064C88(void);
extern void Game_ShutdownAndLoadFragment(s32, s32);
extern void func_8005777C(void);
extern void func_8005ADD8(s32);
extern void func_8005A364(s32);
extern void func_80051D64(s32, s32);
extern void func_80054E48(s32);
extern void Game_SetState(s32);

typedef struct {
    s16 unk0;
    s16 unk2;
    void *unk4;
} Struct_80065F50_sp30;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    s32 unk4;
} Struct_80065F50_sp38;

typedef struct {
    s16 unk0;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    char unk5[11];
} Struct_80065F50_sp40;

void func_80065F50(void) {
    Struct_80065F50_sp40 sp40;
    Struct_80065F50_sp38 sp38;
    Struct_80065F50_sp30 sp30;
    s32 s0;

    main_pool_push_state(0x656D736C);
    Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10, fragment11_ROM_START, fragment12_ROM_START);
    Fragment_Load((((u32)D_81800000 & 0x0FF00000) >> 20) - 0x10, fragment4_ROM_START, fragment5_ROM_START);

    sp30.unk0 = 0;
    sp30.unk4 = (void *)0x826E0400;
    sp30.unk2 = 0;

    s0 = Fragment_LoadAndCall((((u32)D_82800000 & 0x0FF00000) >> 20) - 0x10, fragment10_ROM_START, fragment11_ROM_START, 0, &sp30);
    main_pool_pop_state(0x656D736C);

    if (s0 >= 0 && s0 < 4) {
        func_80064C94(s0);
        Audio_EnableModeFlag();
        Audio_ResetRequestId();
        main_pool_push_state(0x656D626B);
        func_80055948(3);
        func_80054210(&sp38);

        sp40.unk2 = sp38.unk0;
        sp40.unk3 = sp38.unk1;
        sp40.unk0 = sp38.unk4;
        sp40.unk4 = (sp38.unk2 & 1) != 0;

        main_pool_pop_state(0x656D626B);
        main_pool_push_state(0x656D756C);
        Audio_WaitForPendingTasks();
        Display_ClearFramebufferLine(1);
        Display_WaitForFrames(3);
        Audio_SetProcessingEnabled(1);
        func_80050994(&sp40);
        s0 = GbTower_RecvExitMesg();
        func_80050B40(&sp40);
        Display_ClearFramebufferLine(1);
        Display_WaitForFrames(3);
        Audio_SetProcessingEnabled(0);

        if (s0 != 0) {
            Game_ShutdownAndLoadFragment(func_80064C88(), s0);
        }
        main_pool_pop_state(0x656D756C);
        main_pool_push_state(0x656D626B);

        for (s0 = 0; s0 != 16; s0++) {
            func_8005777C();
        }

        for (s0 = 0; s0 < 4; s0++) {
            if (func_80064C88() == s0) {
                func_8005ADD8(func_80064C88());
            } else {
                func_8005A364(s0);
            }
        }

        func_80055948(3);
        func_80054210(&sp38);

        sp38.unk0 = sp40.unk2;
        sp38.unk1 = sp40.unk3;
        sp38.unk4 = sp40.unk0;
        func_80054248(&sp38);

        func_80051D64(0x14, 0);
        func_80054E48(3);
        main_pool_pop_state(0x656D626B);
    }

    Game_SetState(3);
}
#endif
