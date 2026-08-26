#include "global.h"


#ifdef VERSION_US
extern u8 fragment11_ROM_START[];
extern u8 fragment12_ROM_START[];
extern u8 fragment17_ROM_START[];
extern u8 fragment18_ROM_START[];
extern u8 D_81600000[];
extern u8 D_82200000[];
extern s32 D_8009DEB0;
typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u8 pad_0A[0x1E];
} Unk667B0; /* size = 0x28 */
extern void func_80057944(u8);
extern void main_pool_push_state(u32);
extern void main_pool_pop_state(u32);
extern void func_8006CC0C(void);
extern void Fragment_Load(s32, void *, void *);
extern s32 func_80064E38(void);
extern s32 Fragment_LoadAndCall(s32, void *, void *, s32, void *);
extern void func_80064CB8(s16);
extern void func_80064CD0(s16);
extern void Game_SetState(s32);
extern void func_80065D90(s32);
extern void func_8006CBFC(void);
void Game_State02_Run(void) {
    s32 ret;
    s32 i;
    Unk667B0 sp30;

    for (i = 0; i < 4; i++) {
        func_80057944(i);
    }

    main_pool_push_state(0x67626368);
    func_8006CC0C();
    Fragment_Load               ((((u32)D_81600000 & 0x0FF00000) >> 20) - 0x10, fragment11_ROM_START, fragment12_ROM_START);
    if (func_80064E38() == 1) {
        D_8009DEB0 = 0;
    }
    ret = Fragment_LoadAndCall((((u32)D_82200000 & 0x0FF00000) >> 20) - 0x10, fragment17_ROM_START, fragment18_ROM_START, D_8009DEB0, &sp30);
    D_8009DEB0 = ret;
    main_pool_pop_state(0x67626368);

    switch (ret) {
        case 1:
            func_80064CB8(sp30.unk_02);
            func_80064CD0(sp30.unk_04);
            Game_SetState(14);
            break;
        case 2:
            Game_SetState(3);
            func_80065D90(1);
            break;
        case 3:
            Game_SetState(13);
            break;
        case 5:
            Game_SetState(11);
            break;
        case 4:
            Game_SetState(19);
            break;
        case 7:
            switch (sp30.unk_08 & 0xFF00) {
                case 0:
                    func_8006CBFC();
                    Game_SetState(8);
                    break;
                case 0x300:
                    func_8006CBFC();
                    Game_SetState(9);
                    break;
                default:
                    Game_SetState(3);
                    break;
            }
            break;
        default:
            Game_SetState(1);
            break;
    }
}
#endif
