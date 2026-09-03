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
void func_80064D58(s32 arg0, s32 arg1) {
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/65820/Game_Thread.s")
#endif

#ifdef VERSION_US
void func_80065210(s32 arg0) { }
#endif
