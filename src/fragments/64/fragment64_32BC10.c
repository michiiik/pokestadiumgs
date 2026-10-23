#include "global.h"


#ifdef VERSION_US
extern Gfx *D_800D0510;
extern Gfx D_87F11190[];

// D_87F11190 is the mode-setting Gfx display list in this fragment's data
// (asm/us/data/fragments/64/fragment64_data.data.s:2071, ends with G_ENDDL);
// D_800D0510 is the shared display-list cursor (the file-idiom Gfx * extern).
// The u8 parameter is load-bearing for the register schedule: ugen homes a
// narrow register parameter framelessly into the caller's outgoing-arg area
// (sw a0, 0(sp), raw value, no sp adjustment), and the macro's _SHIFTL(a, 0, 8)
// mask on the alpha subsumes the in-place entry narrowing, so the single
// andi t3, a0, 0xff sits at the use reading raw a0. A wider parameter type
// drops the home store entirely (verified score 315) and also loses the
// as1 interleave that splits the first command's lui/addiu pair around the
// pointer advance.
void func_87F08FA0(u8 arg0) {
    gSPDisplayList(D_800D0510++, D_87F11190);
    gDPSetEnvColor(D_800D0510++, 0, 0, 0, arg0);
    gSPTextureRectangle(D_800D0510++, 0, 0, 320 << 2, 240 << 2, G_TX_RENDERTILE, 0, 0, 1024, 1024);
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32BC10/func_87F09040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32BC10/func_87F09120.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32BC10/func_87F09504.s")
#endif
