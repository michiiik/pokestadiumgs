#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/69F70/func_80069370.s")

s32 func_80069750(s32 arg0) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    if ((*(volatile u32 *)0xA4600010 & 3) == 0) {
        if ((*(volatile u32 *)0xB0000504 & 0xFFFF) != 0xA460) {
            arg0 = -32;
        }
    }
    osSetIntMask(mask);
    return arg0;
}

/* mkdraft:func_800697B8 begin */
extern s32 Audio_SetModeBlocking(s32, s32, s32);
extern s32 func_8006A388(void);
extern s32 Fragment_LoadAndCall(s32, u8 *, u8 *, u32, u32);
extern u8 D_82900000;
extern u8 D_82E00000;
extern u8 fragment66_ROM_START[];
extern u8 fragment67_ROM_START[];
extern u8 fragment68_ROM_START[];

s32 func_800697B8(void) {
    // FAKE: a one-element array preserves the retail halfword packet stack slot.
    s32 seg1;
    s32 seg2;
    s16 var_v0[1];
    s32 var_v1;

    Audio_SetModeBlocking(0xD, 0, 0);
    seg1 = (((u32)&D_82900000 & 0x0FF00000) >> 20) - 16;
    Fragment_LoadAndCall(seg1, fragment67_ROM_START, fragment68_ROM_START, 2, 0);
    var_v0[0] = func_8006A388();
    seg2 = (((u32)&D_82E00000 & 0x0FF00000) >> 20) - 16;
    if (Fragment_LoadAndCall(seg2, fragment66_ROM_START, fragment67_ROM_START, 0, (u32)var_v0) != 0) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1;
}
/* mkdraft:func_800697B8 end */

extern s32 func_800354B4(s32, s32, s32);
extern s32 func_8006A388(void);
extern void (*Fragment_Load(s32, u8 *, u8 *))(void);
extern s32 Fragment_LoadAndCall(s32, u8 *, u8 *, u32, u32);
extern u8 D_87F00000;
extern u8 D_83400000;
extern u8 fragment64_ROM_START[];
extern u8 fragment65_ROM_START[];
extern u8 fragment58_ROM_START[];
extern u8 fragment59_ROM_START[];

void func_80069868(void) {
    // FAKE: a one-element array preserves the retail halfword packet stack slot.
    s16 var_v0[1];

    func_800354B4(12, 0, 0);
    var_v0[0] = func_8006A388();
    Fragment_Load((((u32)&D_87F00000 & 0x0FF00000) >> 20) - 16,
                  fragment64_ROM_START, fragment65_ROM_START);
    Fragment_LoadAndCall((((u32)&D_83400000 & 0x0FF00000) >> 20) - 16,
                         fragment58_ROM_START, fragment59_ROM_START, 0, (u32)var_v0);
}

typedef struct SceneConfig69900 { s32 words[4]; } SceneConfig69900;
typedef struct SceneContext69900 {
    u8 unk_00[0x2C];
    void *unk_2C;
} SceneContext69900;
extern SceneConfig69900 D_8009DF50;
extern SceneContext69900 *BattleScene_ResetParticipantModelFlags(s32);
extern s32 func_8006A3B8(u16);
extern s32 func_8006A444(s32);
extern s32 func_8006A3E0(void);
extern s32 func_8006A424(void);
extern s32 func_8006A388(void);
extern s32 func_8006AB8C(u16, s32, s32);
extern s32 func_8006ABD8(void *);
extern s32 func_8006AC28(s32);
extern s32 func_8006AE90(s32);
extern s32 func_8006A2EC(void);
extern void func_80026938(u16);
extern s32 func_8006A48C(void);
extern s32 func_8006A51C(s32);
extern s32 func_8006AC70(void);
extern s32 func_8006AEB4(void);
extern void *func_8006C58C(void);
extern void *func_8006BAC4(void);
extern void *func_8006C644(void);
extern void *func_8006C664(void);
extern void *func_8006B928(void);
extern s32 func_80069750(s32);
extern s32 func_800697B8(void);
extern void func_80069868(void);
extern s32 Audio_SetModeBlocking(s32, s32, s32);
extern void func_800355E4(s32);
extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern s32 Game_SetState(s32);
extern u8 D_81700000[];
extern u8 D_81600000[];
extern u8 D_81300000[];
extern u8 D_82600000[];
extern u8 D_84200000[];
extern u8 D_81400000[];
extern u8 D_84100000[];
extern u8 D_81100000[];
extern u8 fragment67_ROM_START[];
extern u8 fragment68_ROM_START[];
extern u8 fragment18_ROM_START[];
extern u8 fragment19_ROM_START[];
extern u8 fragment11_ROM_START[];
extern u8 fragment11_ROM_END[];
extern u8 fragment12_ROM_START[];
extern u8 fragment13_ROM_START[];
extern u8 fragment14_ROM_START[];
extern u8 fragment15_ROM_START[];
extern u8 fragment20_ROM_START[];
extern u8 fragment21_ROM_START[];
extern u8 fragment80_ROM_START[];
extern u8 fragment81_ROM_START[];
extern u8 fragment27_ROM_START[];
extern u8 fragment28_ROM_START[];
extern u8 fragment79_ROM_START[];

void func_80069900(void) {
    s32 state;
    s32 temp;
    s32 selected;
    s32 flag;
    SceneContext69900 *context;
    s32 fragment_b;
    s32 temp_v0;
    SceneConfig69900 config;
    s32 temp_v0_2;

    config = D_8009DF50;
    state = 0xE;
    flag = 0;
    main_pool_push_state(0x62747063);
    context = BattleScene_ResetParticipantModelFlags(1);
    func_8006A3B8(0x600);
    func_8006A444(0xB);
    fragment_b = func_8006A3E0() & 0xFFFF;
    func_8006AB8C((u16)fragment_b, func_8006A424(), func_8006A388());
    func_8006ABD8(&config);
    func_8006AC28(0);
    func_8006AE90(0x1D);
    do {
        main_pool_push_state(0x62746C70);
        switch (state) {
        case 14:
            temp = (((u32)&D_82900000 & 0x0FF00000) >> 20) - 16;
            Audio_SetModeBlocking(7, 0, 0);
            state = 3;
            Fragment_LoadAndCall(temp, fragment67_ROM_START, fragment68_ROM_START, 3, 0);
            break;
        case 3:
            Audio_SetModeBlocking(7, 0, 0);
            temp = func_8006B928();
            if (temp != 0) {
                Fragment_Load((((u32)D_81700000 & 0x0FF00000) >> 20) - 16, fragment18_ROM_START, fragment19_ROM_START);
                Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 16, fragment11_ROM_START, fragment12_ROM_START);
                if (Fragment_LoadAndCall((((u32)D_81300000 & 0x0FF00000) >> 20) - 16,
                                         fragment14_ROM_START, fragment15_ROM_START, 0, (u32)temp) != 1) {
                    state = 0;
                } else {
                    state = 4;
                }
            }
            break;
        case 4:
            Audio_SetModeBlocking(9, 0, 0);
            state = 5;
            if (func_8006C58C() != 0) {
                Fragment_LoadAndCall((((u32)D_82600000 & 0x0FF00000) >> 20) - 16,
                                     fragment20_ROM_START, fragment21_ROM_START, 1, (u32)context->unk_2C);
                func_8006AC4C(*(s16 *)((u8 *)context->unk_2C + 0x88));
                func_8006ACCC(*(s16 *)((u8 *)context->unk_2C + 0x8A));
            }
            break;
        case 5:
            selected = func_8006BAC4();
            if (selected != 0) {
                Fragment_Load((((u32)D_84200000 & 0x0FF00000) >> 20) - 16, fragment80_ROM_START, fragment81_ROM_START);
                Fragment_Load((((u32)D_81600000 & 0x0FF00000) >> 20) - 16, fragment11_ROM_START, fragment11_ROM_END);
                if (Fragment_LoadAndCall((((u32)D_81400000 & 0x0FF00000) >> 20) - 16,
                                         fragment12_ROM_START, fragment13_ROM_START, 0, (u32)selected) != 1) {
                    state = 3;
                } else {
                    state = 6;
                }
            }
            break;
        case 6:
            func_80026938((u16)func_8006AEB4());
            Audio_SetModeBlocking(8, func_8006A51C(func_8006A48C()), func_8006AC70() + 1);
            func_800355E4(0x5A);
            Fragment_Load((((u32)D_81100000 & 0x0FF00000) >> 20) - 16, fragment27_ROM_START, fragment28_ROM_START);
            Fragment_LoadAndCall((((u32)D_84100000 & 0x0FF00000) >> 20) - 16, fragment79_ROM_START, fragment80_ROM_START, (u32)func_8006AEB4(), (u32)func_8006C664());
            state = func_80069750(8);
            break;
        case 8:
            Audio_SetModeBlocking(0xA, 0, 0);
            if (func_8006C644() != 0) {
                temp = Fragment_LoadAndCall((((u32)D_82600000 & 0x0FF00000) >> 20) - 16,
                                             fragment20_ROM_START, fragment21_ROM_START, 2, (u32)context->unk_2C);
                switch (temp) {
                    case 2:
                        state = 0xF;
                        break;
                    case 3:
                    case 4:
                        state = 3;
                        break;
                    default:
                        state = 0;
                        break;
                }
            }
            break;
        case 15:
            if (func_800697B8() != 0) {
                state = 0x10;
            } else {
                state = 0;
                flag = 1;
            }
            break;
        case 16:
            state = 0;
            flag = 1;
            func_80069868();
            break;
        }
        main_pool_pop_state(0x62746C70);
    } while (state != 0);
    func_8006A2EC();
    main_pool_pop_state(0x62747063);
    if (flag != 0) {
        Game_SetState(0x11);
    } else {
        Game_SetState(3);
    }
}
#endif
