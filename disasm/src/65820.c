#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/func_80064C20.s")
#endif

#ifdef VERSION_US
extern s32 D_80128BE0;

s32 func_80064C88(void) {
    return D_80128BE0;
}
#endif

#ifdef VERSION_US
s32 func_80064C94(s32 value) { s32 result = 0; if (value >= 0 && value < 4) { D_80128BE0 = value; result = 1; } return result; }
#endif

#ifdef VERSION_US
extern s16 D_80128BE8;

void func_80064CB8(s32 arg0) {
    D_80128BE8 = arg0;
}
#endif

#ifdef VERSION_US

s16 func_80064CC4(void) {
    return D_80128BE8;
}
#endif

#ifdef VERSION_US
extern s16 D_80128BEA;

void func_80064CD0(s32 arg0) {
    D_80128BEA = arg0;
}
#endif

#ifdef VERSION_US

s16 func_80064CDC(void) {
    return D_80128BEA;
}
#endif

#ifdef VERSION_US
typedef s32 (*S1_FragmentEntry)(s32, s32);
extern u8 fragment24_ROM_START[];
extern u8 fragment23_ROM_START[];
s32 Fragment_LoadAndCall(s32 arg0, u8* romStart, u8* romEnd, u32 arg3, u32 arg4) {
    s32 result;
    S1_FragmentEntry func;

    func = Fragment_Load(arg0, romStart, romEnd);

    result = func(arg3, arg4);

    main_pool_try_free(func);

    return result;
}
#endif

#ifdef VERSION_US
extern void Cont_StartReadInputs();
extern void func_80005F0C();
extern void func_80049ED0();
void func_80064D28(void) { Cont_StartReadInputs(); func_80005F0C(); func_80049ED0(); }
#endif

#ifdef VERSION_US
extern u8 D_82A00000;
extern u8 fragment23_ROM_START[];
extern u8 fragment24_ROM_START[];
extern void GbTower_PowerOffAllPaks(void);
extern void Audio_StopProcessing(void);
extern void Display_ClearFramebufferLine(s32);
extern void Display_ApplyPendingVideoMode(void);
extern void Display_WaitForFrames(s32);
extern void main_pool_pop_state(s32);
extern s32 Fragment_LoadAndCall(s32, u8 *, u8 *, u32, u32);
extern void func_80064DF4(void);
void Game_ShutdownAndLoadFragment(s32 arg0, s32 arg1) {
    osViBlack(1U);
    GbTower_PowerOffAllPaks();
    Audio_StopProcessing();
    func_80064DF4();
    Display_ClearFramebufferLine(1);
    Display_ApplyPendingVideoMode();
    Display_WaitForFrames(0xA);
    main_pool_pop_state(0x47414D45);
    Fragment_LoadAndCall((((u32) &D_82A00000 & 0x0FF00000) >> 20) - 0x10,
        fragment23_ROM_START, fragment24_ROM_START, (u32) arg0, (u32) arg1);
}
#endif

void func_80064DF4(void) {
}

#ifdef VERSION_US
extern s32 D_8009DE94;
extern s32 D_80128BE4;
s32 Game_SetState(s32 value) { s32 result = 0; if (value != D_8009DE94) { D_80128BE4 = D_8009DE94; D_8009DE94 = value; result = 1; } return result; }
#endif

#ifdef VERSION_US

s32 Game_GetState(void) {
    return D_8009DE94;
}
#endif

#ifdef VERSION_US

s32 func_80064E38(void) {
    return D_80128BE4;
}
#endif

#ifdef VERSION_US
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
extern u8 D_82700000;
extern u8 fragment22_ROM_START;
void Game_State11_Options(void) {
    s32 sp24;

    main_pool_push_state(0x6F70746E);
    sp24 = Fragment_LoadAndCall(((u32) ((s32) &D_82700000 & 0x0FF00000) >> 0x14) - 0x10, &fragment22_ROM_START, fragment23_ROM_START, 0U, 0U);
    main_pool_pop_state(0x6F70746E);
    if (sp24 == 0) {
        Game_SetState(2);
        return;
    }
    Game_SetState(1);
}
#endif

#ifdef VERSION_US
extern void __osSetFpcCsr(s32);
extern void func_8000644C();
extern void func_80035620();
extern void func_80046980();
extern s32 D_8009DE90;
void func_80035140(s32 value);
void func_8004C020(void);
void func_80041B84(void);
void func_8006D240(void);
void Game_ThreadInit(void) {
    __osSetFpcCsr(0x01000C01);
    func_8000644C();
    func_80035140(1);
    func_80035620();
    func_8004C020();
    func_80046980();
    func_80041B84();
    func_8006D240();
    Game_SetState(0x11);
    D_80128BE0 = -1;
    D_8009DE90 = 0;
    main_pool_push_state(0x47414D45);
}
#endif

#ifdef VERSION_US
extern s32 D_8009DE90;
extern void func_8004B6E0(void);
extern void func_80050BE0(void);
extern void main_pool_push_state(s32);
extern void func_8005AEA0(void);
extern void main_pool_pop_state(s32);
void func_80064F54(void) {
    if (D_8009DE90 == 0) {
        D_8009DE90 = 1;
        func_8004B6E0();
        func_80050BE0();
        main_pool_push_state(0x4750414B);
        func_8005AEA0();
        main_pool_pop_state(0x4750414B);
    }
}
#endif

#ifdef VERSION_US
extern s32 func_80064C20(s32);
extern void func_800354B4(s32, s32, s32);
extern void func_800355E4(s32);
extern void func_80065A18(void);
extern void Game_State02_Run(void);
extern void func_80065D9C(void);
extern void func_80065F50(void);
extern void func_800661F0(void);
extern void func_8006D440(void);
extern void func_800666F0(void);
extern void func_80066D24(void);
extern void func_80067B8C(void);
extern void func_800727D4(s32);
extern void Audio_ResetRequestId(void);
extern void Game_State12_Nop(void);
extern void func_800684F0(void);
extern void func_80069370(void);
extern void func_80069900(void);
extern void func_80068E14(void);
extern void Game_State17_Boot(void);
extern void Game_State18_Run(void);
extern void Game_State19_Run(void);
extern void Game_State18_Run(void);
void Game_Thread(s32 arg0) {
    s32 state;

    Game_ThreadInit();
loop:
    state = func_80064C20(D_8009DE94);
    switch (state) {
    case 17: func_800354B4(0, 0, 0); Game_State17_Boot(); break;
    case 1: func_80065A18(); break;
    case 2: func_800354B4(2, 0, 0); func_800355E4(0x25); Game_State02_Run(); break;
    case 3: func_800354B4(2, 0, 0); func_800355E4(0x25); func_80065D9C(); break;
    case 4: func_80065F50(); break;
    case 5: func_800354B4(3, 0, 0); func_800355E4(8); func_8006D440(); Game_SetState(3); break;
    case 6: func_800661F0(); break;
    case 7: func_800354B4(5, 0, 0); func_800355E4(0x29); func_800666F0(); break;
    case 8: func_80066D24(); break;
    case 9: func_80067B8C(); break;
    case 10: func_800354B4(6, 0, 0); func_800727D4(0); Game_SetState(3); Audio_ResetRequestId(); break;
    case 11: func_800354B4(2, 0, 0); func_800355E4(0x2A); Game_State11_Options(); break;
    case 12: func_800354B4(0x1E, 0, 0); Game_State12_Nop(); break;
    case 13: func_800684F0(); break;
    case 14: func_80069370(); break;
    case 15: func_80069900(); break;
    case 16: func_80068E14(); break;
    case 18: Game_State18_Run(); break;
    case 19: func_800355E4(0x44); Game_State19_Run(); Game_SetState(2); break;
    default: break;
    }
    goto loop;
}
#endif

#ifdef VERSION_US
void func_80065210(s32 arg0) { }
#endif
