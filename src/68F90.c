#include "global.h"


#ifdef VERSION_US
extern s32 func_8006A3B8(u16);
extern s32 func_8006A400(s32);
void func_80068390(s32 arg0) {
    u16 var_a1;
    s16 var_a2;

    var_a1 = 0xFFFF;
    var_a2 = 4;
    switch (arg0 & 0xFFFF0000) {
        case 0x30000:
            var_a1 = 0x100;
            break;
        case 0x20000:
            var_a1 = 0x101;
            break;
        case 0x40000:
            var_a1 = 0x102;
            switch (arg0 & 0xFFFF) {
                case 0:
                    var_a2 = 1;
                    break;
                case 1:
                    var_a2 = 2;
                    break;
                case 2:
                    var_a2 = 3;
                    break;
                case 3:
                    break;
            }
            break;
        case 0x10000:
            var_a1 = 0x103;
            break;
        case 0x50000:
            var_a1 = 0x110;
            break;
    }
    func_8006A3B8(var_a1);
    func_8006A400(var_a2);
}
extern s32 func_8006A3E0(void);
extern s32 func_8006A424(void);
extern void func_80055948(s32);
extern u8 *func_8006218C(s32, s32, s32, s32);
extern void func_8006249C(void *, s32, u8 *);
extern void func_80062304(u8 *);
extern void func_80055028(void);
s32 func_80068464(u8 *arg0) {
    u8 *temp_s0;
    u8 *temp_v0;
    void *sp24;
    s32 result;

    temp_s0 = *(u8 **)(arg0 + 0x20);
    result = 0;
    if (temp_s0[0x423] != 0) {
        *(s16 *)(temp_s0 + 0x488) = func_8006A3E0();
        *(s16 *)(temp_s0 + 0x48A) = func_8006A424();
        func_80055948(3);
        temp_v0 = func_8006218C(0x1A, 0, 0, 1);
        sp24 = temp_v0;
        func_8006249C(temp_s0, 1, temp_v0);
        func_80062304(sp24);
        func_80055028();
        result = 1;
    }
    return result;
}

typedef struct SceneConfig68F90 { s32 words[4]; } SceneConfig68F90;
typedef struct SceneContext68F90 {
    u8 unk_00[0x1C];
    void *unk_1C;
    u8 unk_20[0x0C];
    void *unk_2C;
    u8 unk_30[4];
    void *unk_34;
} SceneContext68F90;
typedef struct SceneSub68F90 {
    s32 unk_00;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    u8 unk_0C[0x8C];
    s16 unk_88;
    s16 unk_8A;
} SceneSub68F90;
extern SceneConfig68F90 D_8009DF20;
extern SceneContext68F90 *BattleScene_ResetParticipantModelFlags(s32);
extern SceneSub68F90 *func_8006A278(void);
extern void func_8006B790(s32);
extern void func_8006B428(s32, s32);
extern void func_80068390(s32);
extern s32 func_8006A3E0(void);
extern s32 func_8006A424(void);
extern s32 func_8006A388(void);
extern s32 func_8006A600(s32, s32, s32);
extern s32 func_8006A444(s32);
extern s32 func_8006A4AC(void *);
extern s32 func_8006ABD8(void *);
extern s32 func_8006AC28(s32);
extern s32 func_8006A2EC(void);
extern void func_80026938(u16);
extern s32 func_8006A48C(void);
extern s32 func_8006A51C(s32);
extern s32 func_8006AEB4(void);
extern s32 func_8006AC4C(s16);
extern s32 func_8006ACCC(s16);
extern s32 func_8006AC70(void);
extern s32 func_8006AD10(s32, s32, s32);
extern s32 func_8006AE90(s32);
extern void *func_8006C9F4(void);
extern s32 func_8006C58C(void);
extern void *func_8006BAC4(void);
extern s32 func_8006C644(void);
extern void *func_8006C664(void);
extern s32 func_80068464(u8 *);
extern s32 Audio_SetModeBlocking(s32, s32, s32);
extern void func_800355E4(s32);
extern void *Fragment_Load(s32, void *, void *);
extern s32 Fragment_LoadAndCall(s32, void *, void *, u32, u32);
extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern s32 Game_SetState(s32);
extern u8 D_81700000[];
extern u8 D_81600000[];
extern u8 D_82B00000[];
extern u8 D_84300000[];
extern u8 D_82600000[];
extern u8 D_84200000[];
extern u8 D_81400000[];
extern u8 D_81100000[];
extern u8 D_84100000[];
extern u8 fragment18_ROM_START[];
extern u8 fragment19_ROM_START[];
extern u8 fragment11_ROM_START[];
extern u8 fragment11_ROM_END[];
extern u8 fragment12_ROM_START[];
extern u8 fragment13_ROM_START[];
extern u8 fragment24_ROM_START[];
extern u8 fragment25_ROM_START[];
extern u8 fragment13_ROM_START[];
extern u8 fragment80_ROM_START[];
extern u8 fragment81_ROM_START[];
extern u8 fragment82_ROM_START[];
extern u8 fragment81_ROM_START[];
extern u8 fragment82_ROM_START[];
extern u8 fragment81_ROM_END[];
extern u8 fragment20_ROM_START[];
extern u8 fragment21_ROM_START[];
extern u8 fragment27_ROM_START[];
extern u8 fragment28_ROM_START[];
extern u8 fragment79_ROM_START[];
extern u8 fragment80_ROM_START[];

void func_800684F0(void) {
    s32 state;
    u32 mode;
    SceneContext68F90 *context;
    s32 fragment_a;
    s32 fragment_b;
    s32 value;
    s32 temp_s1;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    SceneConfig68F90 config;
    s32 temp_v0_4;

    config = D_8009DF20;
    mode = 0x10000;
    state = 7;
    main_pool_push_state(0x62747063);
    context = BattleScene_ResetParticipantModelFlags(0);
    func_8006A278();
    func_8006B790(1);
    do {
        main_pool_push_state(0x62746C70);
        switch (state) {
        case 7:
            Audio_SetModeBlocking(7, 0, 0);
            func_800355E4(0x19);
            if (context->unk_34 != NULL) {
                fragment_a = (((u32)D_81700000 & 0x0FF00000) >> 20) - 16;
                fragment_b = (((u32)D_81600000 & 0x0FF00000) >> 20) - 16;
                ((SceneSub68F90 *)context->unk_34)->unk_00 = (s32)func_8006C9F4();
                Fragment_Load(fragment_a, fragment18_ROM_START, fragment19_ROM_START);
                Fragment_Load(fragment_b, fragment11_ROM_START, fragment12_ROM_START);
                mode = Fragment_LoadAndCall((((u32)D_82B00000 & 0x0FF00000) >> 20) - 16,
                                             fragment24_ROM_START, fragment25_ROM_START, mode, (u32)context->unk_34);
                if (mode == 0) {
                    state = 0;
                } else {
                    state = 4;
                    func_80068390(mode);
                    if ((func_8006A3E0() & 0xFF) != 0x10) {
                        temp_s1 = func_8006A3E0() & 0xFFFF;
                        temp_s0 = func_8006A424();
                        func_8006A444(func_8006A600(temp_s1 & 0xFFFF, temp_s0, func_8006A388()));
                    } else {
                        func_8006A4AC((u8 *)context->unk_34 + 0xC);
                    }
                    func_8006ABD8(&config);
                    func_8006AC28(0);
                }
                func_8006B428(*(s32 *)context->unk_34, (func_8006A3E0() & 0xFF) != 2);
                *(s32 *)context->unk_34 = 0;
            } else {
                state = 0;
            }
            break;
        case 4:
            Audio_SetModeBlocking(9, 0, 0);
            state = 5;
            if (func_8006C58C() != 0) {
                Fragment_Load((((u32)D_84300000 & 0x0FF00000) >> 20) - 16, fragment81_ROM_START, fragment82_ROM_START);
                Fragment_LoadAndCall((((u32)D_82600000 & 0x0FF00000) >> 20) - 16,
                                     fragment20_ROM_START, fragment21_ROM_START, 1, (u32)context->unk_2C);
                func_8006AC4C(*(s16 *)((u8 *)context->unk_2C + 0x88));
                func_8006ACCC(*(s16 *)((u8 *)context->unk_2C + 0x8A));
                temp_s1 = func_8006A3E0() & 0xFFFF;
                temp_s0 = func_8006A424();
                func_8006AE90(func_8006AD10(temp_s1 & 0xFFFF, temp_s0, func_8006AC70()));
            }
            break;
        case 5: {
            void *selected = func_8006BAC4();
            if (selected != NULL) {
                Fragment_Load((((u32)D_84200000 & 0x0FF00000) >> 20) - 16, fragment80_ROM_START, fragment81_ROM_START);
                fragment_b = (((u32)D_81600000 & 0x0FF00000) >> 20) - 16;
                Fragment_Load(fragment_b, fragment11_ROM_START, fragment11_ROM_END);
                if (Fragment_LoadAndCall((((u32)D_81400000 & 0x0FF00000) >> 20) - 16, fragment12_ROM_START, fragment13_ROM_START, 0, (u32)selected) != 1) {
                    state = 3;
                } else {
                    state = 6;
                }
            }
            break;
        }
        case 6:
            if (((SceneSub68F90 *)context->unk_34)->unk_04 != 0) {
                *(s8 *)((u8 *)context->unk_1C + 0x9C0) = ((SceneSub68F90 *)context->unk_34)->unk_06;
                *(s8 *)((u8 *)context->unk_1C + 0x9C1) = ((SceneSub68F90 *)context->unk_34)->unk_08;
            } else {
                *(s8 *)((u8 *)context->unk_1C + 0x9C0) = 0;
                *(s8 *)((u8 *)context->unk_1C + 0x9C1) = 0;
            }
            state = 8;
            func_80026938((u16) func_8006AEB4());
            Audio_SetModeBlocking(8, func_8006A51C(func_8006A48C()), 0xB);
            func_800355E4(0x5A);
            fragment_a = (((u32)D_81100000 & 0x0FF00000) >> 20) - 16;
            Fragment_Load(fragment_a, fragment27_ROM_START, fragment28_ROM_START);
            fragment_b = (((u32)D_84100000 & 0x0FF00000) >> 20) - 16;
            value = func_8006AEB4();
            Fragment_LoadAndCall(fragment_b, fragment79_ROM_START, fragment80_ROM_START, value, (u32)func_8006C664());
            func_80068464((u8 *)context);
            break;
        case 8:
            Audio_SetModeBlocking(0xA, 0, 0);
            if (func_8006C644() != 0) {
                Fragment_LoadAndCall((((u32)D_82600000 & 0x0FF00000) >> 20) - 16,
                                     fragment20_ROM_START, fragment21_ROM_START, 2, (u32)context->unk_2C);
                state = 7;
            }
            break;
        }
        main_pool_pop_state(0x62746C70);
    } while (state != 0);
    func_8006A2EC();
    main_pool_pop_state(0x62747063);
    Game_SetState(2);
}
#endif
