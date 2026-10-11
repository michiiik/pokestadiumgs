#include "global.h"


#ifdef VERSION_US
extern void func_8004C8C0(s32);
void func_87F061D0(void) {
    func_8004C8C0(429);
}

extern Gfx *D_800D0510;
extern Gfx D_80094E78[];
void func_87F061F0(void) {
    gSPDisplayList(D_800D0510++, D_80094E78);
    gDPSetCombineLERP(D_800D0510++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0,
                     PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, 0, TEXEL0, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_328E40/func_87F06240.s")
#endif
