#include "global.h"


#ifdef VERSION_US
void func_80069E10(void) {}
void func_80069E10_padding(void) {}
void func_80069E10_padding2(void) {}
void func_80069E10_padding3(void) {}
void func_80069E10_padding4(void) {}

extern void _bzero(void *, s32);
extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void Game_SetState(s32);
void Game_State18_Run(void) {
    u8 sp1C[0x7C];
    _bzero(sp1C, 0x1F);
    main_pool_push_state(0x62747063);
    main_pool_pop_state(0x62747063);
    Game_SetState(2);
}
#endif
