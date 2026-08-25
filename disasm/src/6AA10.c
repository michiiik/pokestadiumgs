#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6AA10/func_80069E10.s")

extern void _bzero(void *, s32);
extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void func_80064DFC(s32);
void func_80069E38(void) {
    u8 sp1C[0x7C];
    _bzero(sp1C, 0x1F);
    main_pool_push_state(0x62747063);
    main_pool_pop_state(0x62747063);
    func_80064DFC(2);
}
#endif
