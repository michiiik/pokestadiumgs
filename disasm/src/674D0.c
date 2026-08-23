#include "global.h"

extern s32 D_8009DEDC[];
extern u16 D_8009DEF0[];
extern u16 D_8009DEF8[];

#define D_81600000 ((u8 *)0x81600000)
#define D_81700000 ((u8 *)0x81700000)
#define D_82300000 ((u8 *)0x82300000)
#define D_81300000 ((u8 *)0x81300000)
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment14_ROM_START[];
extern u8 fragment15_ROM_START[];
extern u8 fragment18_ROM_START[];
extern u8 fragment19_ROM_START[];
extern u8 fragment20_ROM_START[];

extern void Gfx_InitDisplayListBuffers(u32 size, s32 type);
extern void Gfx_FreeDisplayListBuffers(void);
extern void *StageContext_Allocate(s32 widthMode, s32 heightMode, s32 flags,
                                   s32 depth, s32 arg4, s32 arg5);
extern void func_80008514(void *stageContext);
extern void *Fragment_Load(u32 pool, u32 source, u32 end);
extern s32 Fragment_LoadAndCall(u32 pool, u32 source, u32 end, s32 arg3,
                                void *arg4);
extern void func_8006A328(void);
extern void func_8006A180(void);
extern void func_800354B4(s32 event, s32 arg1, s32 arg2);
extern void Audio_RequestEvent(s32 event);
extern void *func_8006CA54(s32 value);
extern s32 func_8006A3B8(u16 value);
extern s32 func_8006A400(u16 value);
extern u16 func_8006A3E0(void);
extern s32 func_8006A424(void);
extern s32 func_8006A388(s32 value);
extern s32 func_8006A600(u16 arg0, s32 arg1, s32 arg2);
extern s32 func_8006A444(s32 value);
extern s32 func_8006AB8C(u16 arg0, s32 arg1, s32 arg2);
extern s32 func_8006AC4C(u16 value);
extern s32 func_8006B7D8(u16 value);
extern void *func_8006B928(void);
extern void func_8006CAC0(void *value);
extern void func_80008574(void);

/* Maps the four state-8 mode values to the compact callback result used by
 * Game_State08_Run.  The default is the original unsigned -1 sentinel. */
s32 func_800668D0(s32 mode) {
    switch (mode) {
        case 1:
            return 0;
        case 2:
            return 1;
        case 4:
            return 2;
        case 3:
            return 3;
        default:
            return -1;
    }
}

/* Looks up the state-8 callback value in the five-entry table. */
s32 func_80066924(s32 index) {
    if (index > 0 && index < 5) {
        return D_8009DEDC[index];
    }
    return 0;
}

#ifdef VERSION_US
/*
 * Translate a state-8 mode value through the compact mode table.  The
 * original routine compares only the low halfword of its first argument
 * against D_8009DEF0's entries, then returns the matching table entry from
 * the same slot.  A zero result is retained when no entry matches.
 */
s32 func_8006694C(s32 mode, void *unused) {
    u16 key = (u16)mode;
    u16 *entry = D_8009DEF0;

    (void)unused;
    while (entry != (u16 *)D_8009DEF8) {
        if ((u16)func_800668D0(*entry) == key) {
            return *entry;
        }
        entry++;
    }
    return 0;
}

/*
 * Set up and run the state-8 battle/minigame fragment.  The two callers pass
 * the state selector in `mode` and a pointer to the callback argument/result.
 * The fragment protocol and bookkeeping calls are kept in the same order as
 * the original routine; the surrounding state dispatcher remains assembly.
 */
s32 func_800669C4(s32 mode, s32 *callbackArg) {
    void *stageContext;
    void *fragmentState;
    s32 result;
    s32 nextState = mode;
    s32 currentMode = mode;
    s32 repeat = 1;
    u32 pool816;
    u32 pool817;
    u32 pool823;

    Gfx_InitDisplayListBuffers(0x18800, 0);
    stageContext = StageContext_Allocate(1, 0, 2, 0, 2, 1);
    func_80008514(stageContext);

    pool817 = (((u32)D_81700000 & 0x0FF00000) >> 20) - 0x10;
    pool816 = (((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10;
    pool823 = (((u32)D_82300000 & 0x0FF00000) >> 20) - 0x10;

    do {
        main_pool_push_state(0x63736C70);

        if (currentMode == 1) {
            s32 descriptor;

            func_8006A328();
            func_8006A180();
            func_800354B4(7, 0, 0);
            Audio_RequestEvent(0x33);
            fragmentState = func_8006CA54(0);
            Fragment_Load(pool817, (u32)fragment18_ROM_START,
                          (u32)fragment19_ROM_START);
            Fragment_Load(pool816, (u32)fragment11_ROM_START,
                          (u32)fragment12_ROM_START);
            descriptor = *callbackArg;
            result = Fragment_LoadAndCall(
                pool823, (u32)fragment19_ROM_START,
                (u32)fragment20_ROM_START, descriptor, fragmentState);
            *callbackArg = result & 0xFFFF;

            if (result != 0) {
                s32 mappedMode = func_800668D0(result & 0xF);
                func_8006A3B8(mappedMode & 0xFFFF);
                {
                    s32 tableValue = func_80066924((u32)result >> 16);
                    func_8006A400(tableValue);
                }
                func_8006A3E0();
                {
                    s32 first = func_8006A424();
                    s32 second = func_8006A388(first);
                    s32 combined = func_8006A600((u16)first, second, second);
                    func_8006A444(combined);
                }
                func_8006A3E0();
                {
                    s32 first = func_8006A424();
                    s32 second = func_8006A388(first);
                    func_8006AB8C((u16)first, second, second);
                }
                nextState = (func_8006A3E0() == 2) ? 4 : 3;
                func_8006AC4C(0);
                func_8006B7D8(0);
            } else {
                nextState = 0;
            }
            func_8006CAC0(fragmentState);
        } else if (currentMode == 3) {
            void *descriptor;

            func_800354B4(4, 0, 0);
            descriptor = func_8006B928();
            if (descriptor != NULL) {
                u32 pool813 = (((u32)D_81300000 & 0x0FF00000) >> 20) - 0x10;
                Fragment_Load(pool817, (u32)fragment18_ROM_START,
                              (u32)fragment19_ROM_START);
                Fragment_Load(pool816, (u32)fragment11_ROM_START,
                              (u32)fragment12_ROM_START);
                result = Fragment_LoadAndCall(
                    pool813, (u32)fragment14_ROM_START,
                    (u32)fragment15_ROM_START, 0, descriptor);
                if (result == 1) {
                    nextState = 4;
                } else {
                    nextState = 1;
                }
            }
        } else {
            repeat = 0;
        }

        main_pool_pop_state(0x63736C70);
        currentMode = nextState;
    } while (repeat);

    func_80008574();
    Gfx_FreeDisplayListBuffers();
    return nextState;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/674D0/Game_State08_Run.s")
#endif
