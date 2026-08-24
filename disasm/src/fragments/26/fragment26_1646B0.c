#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_1646B0/func_81005E00.s")

typedef struct Func81005F38State {
    unsigned char pad[0x14];
    u32 *addresses;
    Gfx *gfx;
} Func81005F38State;

extern Gfx *func_80006DEC(s32);
extern void func_81005E00(Gfx *, u32 *);

void func_81005F38(s32 arg0, Func81005F38State *state) {
    Gfx *gfx;
    u32 *addresses;

    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = func_80006DEC(0x50);
        state->gfx = gfx;
        func_81005E00(gfx, addresses);
    }
}

extern void *D_80094BB0;

s32 func_81005F80(s32 arg0, void *arg1) {
    if (arg0 == 0) {
        if (D_80094BB0 == NULL) {
            D_80094BB0 = arg1;
        }
    }
    return 0;
}
#endif
