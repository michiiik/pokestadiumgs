#include "global.h"


#ifdef VERSION_US
typedef struct SceneNode661F0 {
    u8 unk_00;
    u8 unk_01;
    s8 unk_02;
    u8 unk_03;
    void *unk_04;
    void *unk_08;
} SceneNode661F0;
typedef struct SceneConfig661F0 { s32 words[4]; } SceneConfig661F0;
typedef struct SceneContext661F0 {
    u8 unk_00[0x2C];
    void *unk_2C;
    SceneNode661F0 *unk_30;
} SceneContext661F0;
extern SceneConfig661F0 D_8009DED0;
extern void _bzero(void *, s32);
extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern SceneContext661F0 *BattleScene_ResetParticipantModelFlags(s32);
extern void *func_8006A1FC(s32);
extern s32 func_8006A3B8(u16);
extern s32 func_8006ACCC(s32);
extern s32 Audio_SetModeBlocking(s32, s32, s32);
extern void func_800355E4(s32);
extern void *Fragment_Load(s32, void *, void *);
extern s32 Fragment_LoadAndCall(s32, void *, void *, u32, u32);
extern s32 func_8006A444(s32);
extern s32 func_8006A400(s32);
extern s32 func_8006A3E0(void);
extern s32 func_8006A424(void);
extern s32 func_8006A388(void);
extern s32 func_8006AB8C(u16, s32, s32);
extern s32 func_8006AC4C(s32);
extern s32 func_8006ABD8(void *);
extern s32 func_8006AC28(s32);
extern s32 func_8006AE90(s32);
extern void *func_8006C58C(void);
extern s32 func_8006B0B8(void);
extern void *func_8006BAC4(void);
extern s32 func_8006AEB4(void);
extern void func_80026938(u16);
extern void *func_8006C664(void);
extern void *func_8006C644(void);
extern s32 Game_SetState(s32);
extern u8 D_8AC00000[];
extern u8 D_8AF00000[];
extern u8 D_82600000[];
extern u8 D_84200000[];
extern u8 D_81600000[];
extern u8 D_81400000[];
extern u8 D_81100000[];
extern u8 D_84100000[];
extern u8 D_87F00000[];
extern u8 D_8AB00000[];
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment20_ROM_START[];
extern u8 fragment27_ROM_START[];
extern u8 fragment43_ROM_START[];
extern u8 fragment44_ROM_START[];
extern u8 fragment45_ROM_START[];
extern u8 fragment64_ROM_START[];
extern u8 fragment79_ROM_START[];
extern u8 fragment80_ROM_START[];
extern u8 fragment43_ROM_END[];
extern u8 fragment44_ROM_END[];
extern u8 fragment20_ROM_END[];
extern u8 fragment80_ROM_END[];
extern u8 fragment11_ROM_END[];
extern u8 fragment12_ROM_END[];
extern u8 fragment27_ROM_END[];
extern u8 fragment79_ROM_END[];
extern u8 fragment64_ROM_END[];
extern u8 fragment45_ROM_END[];
void func_800661F0(void) {
    u32 state;
    u32 mode;
    SceneContext661F0 *context;
    s32 fragment_a;
    s32 fragment_b;
    s32 fragment_c;
    s32 value;
    u8 work[36];
    SceneConfig661F0 config;
    config = D_8009DED0;
    state = 1;
    mode = 0;
    _bzero(work, sizeof(work));
    main_pool_push_state(0x706D7063);
    context = BattleScene_ResetParticipantModelFlags(0);
    func_8006A1FC((s32)work);
    func_8006A3B8(1024);
    func_8006ACCC(1);
    do {
        main_pool_push_state(0x706D6C70);
        switch (state) {
        case 1:
            fragment_a = (((u32)D_8AC00000 & 0x0FF00000) >> 20) - 16;
            fragment_b = (((u32)D_8AF00000 & 0x0FF00000) >> 20) - 16;
            Audio_SetModeBlocking(4, 0, 0);
            func_800355E4(7);
            Fragment_Load(fragment_a, fragment43_ROM_START, fragment43_ROM_END);
            value = Fragment_LoadAndCall(fragment_b, fragment44_ROM_START, fragment44_ROM_END, mode, (u32)context->unk_30);
            switch (value) {
            case 1:
                state = 2;
                mode = 1;
                func_8006A444(12);
                func_8006A400(context->unk_30->unk_00 + 25);
                fragment_b = func_8006A3E0() & 0xFFFF;
                fragment_a = func_8006A424();
                func_8006AB8C((u16)fragment_b, fragment_a, func_8006A388());
                func_8006AC4C(context->unk_30->unk_01);
                func_8006ABD8(&config);
                func_8006AC28(0);
                func_8006AE90(27);
                break;
            case 2:
                state = 6;
                mode = 2;
                break;
            default:
                state = 0;
                mode = 0;
                break;
            }
            break;
        case 2:
            Audio_SetModeBlocking(9, 0, 0);
            if (func_8006C58C() != NULL) {
                Fragment_LoadAndCall((((u32)D_82600000 & 0x0FF00000) >> 20) - 16,
                                     fragment20_ROM_START, fragment20_ROM_END, 1, (u32)context->unk_2C);
                state = 3;
                func_8006B0B8();
            }
            break;
        case 3: {
            void *selected = func_8006BAC4();
            if (selected != NULL) {
                fragment_a = (((u32)D_84200000 & 0x0FF00000) >> 20) - 16;
                fragment_b = (((u32)D_81600000 & 0x0FF00000) >> 20) - 16;
                fragment_c = (((u32)D_81400000 & 0x0FF00000) >> 20) - 16;
                Fragment_Load(fragment_a, fragment80_ROM_START, fragment80_ROM_END);
                Fragment_Load(fragment_b, fragment11_ROM_START, fragment11_ROM_END);
                if (Fragment_LoadAndCall(fragment_c, fragment12_ROM_START, fragment12_ROM_END, 0, (u32)selected) != 1) {
                    state = 1;
                    context->unk_30->unk_02 = 1;
                } else {
                    state = 4;
                    context->unk_30->unk_02 = 0;
                }
            }
            break;
        }
        case 4:
            fragment_a = (((u32)D_81100000 & 0x0FF00000) >> 20) - 16;
            fragment_b = (((u32)D_84100000 & 0x0FF00000) >> 20) - 16;
            func_80026938((u16)func_8006AEB4());
            state = 5;
            Audio_SetModeBlocking(8, 18, 0);
            func_800355E4(90);
            Fragment_Load(fragment_a, fragment27_ROM_START, fragment27_ROM_END);
            value = func_8006AEB4();
            Fragment_LoadAndCall(fragment_b, fragment79_ROM_START, fragment79_ROM_END, value, (u32)func_8006C664());
            break;
        case 5:
            Audio_SetModeBlocking(10, 0, 0);
            if (func_8006C644() != NULL) {
                Fragment_LoadAndCall((((u32)D_82600000 & 0x0FF00000) >> 20) - 16,
                                     fragment20_ROM_START, fragment20_ROM_END, 2, (u32)context->unk_2C);
                state = 1;
            }
            break;
        case 6:
            fragment_a = (((u32)D_87F00000 & 0x0FF00000) >> 20) - 16;
            fragment_b = (((u32)D_8AC00000 & 0x0FF00000) >> 20) - 16;
            fragment_c = (((u32)D_8AB00000 & 0x0FF00000) >> 20) - 16;
            Fragment_Load(fragment_a, fragment64_ROM_START, fragment64_ROM_END);
            state = 1;
            Fragment_Load(fragment_b, fragment43_ROM_START, fragment43_ROM_END);
            Fragment_LoadAndCall(fragment_c, fragment45_ROM_START, fragment45_ROM_END, 0, (u32)work);
            break;
        }
        main_pool_pop_state(0x706D6C70);
    } while (state != 0);
    main_pool_pop_state(0x706D7063);
    Game_SetState(3);
}
#endif
