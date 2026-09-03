#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_164400/func_81005B50.s")

typedef struct {
    unsigned char pad[0x14];
    u32 *addresses;
    Gfx *gfx;
} Func81005DB4State;
extern void *func_80006DEC();

void func_81005DB4(s32 arg0, Func81005DB4State *state) {
    Gfx *gfx;
    u32 *addresses;
    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = func_80006DEC(0xF0);
        state->gfx = gfx;
        func_81005B50(gfx, addresses);
    }
}
#endif
