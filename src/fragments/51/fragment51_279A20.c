#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_279A20/func_86303C00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/51/fragment51_279A20/func_86303E54.s")

extern u8 *D_863075D8;
extern Gfx *D_800D0510;
extern void func_87F05204(Gfx **);
extern void func_87F09040(void);
void func_86303F00(void) {
    if ((u32)D_863075D8[0x8F51] >> 7) {
        func_87F05204(&D_800D0510);
        func_87F09040();
    }
}
#pragma C_FUNCTION_PADDING(8)
#endif
