#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/69F70/func_80069370.s")

s32 func_80069750(s32 arg0) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    if ((*(volatile u32 *)0xA4600010 & 3) == 0) {
        if ((*(volatile u32 *)0xB0000504 & 0xFFFF) != 0xA460) {
            arg0 = -32;
        }
    }
    osSetIntMask(mask);
    return arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/69F70/func_800697B8.s")

extern s32 func_800354B4(s32, s32, s32);
extern s32 func_8006A388(void);
extern void (*Fragment_Load(s32, u8 *, u8 *))(void);
extern s32 Fragment_LoadAndCall(s32, u8 *, u8 *, u32, u32);
extern u8 D_87F00000;
extern u8 D_83400000;
extern u8 fragment64_ROM_START[];
extern u8 fragment65_ROM_START[];
extern u8 fragment58_ROM_START[];
extern u8 fragment59_ROM_START[];

void func_80069868(void) {
    // FAKE: a one-element array preserves the retail halfword packet stack slot.
    s16 var_v0[1];

    func_800354B4(12, 0, 0);
    var_v0[0] = func_8006A388();
    Fragment_Load((((u32)&D_87F00000 & 0x0FF00000) >> 20) - 16,
                  fragment64_ROM_START, fragment65_ROM_START);
    Fragment_LoadAndCall((((u32)&D_83400000 & 0x0FF00000) >> 20) - 16,
                         fragment58_ROM_START, fragment59_ROM_START, 0, (u32)var_v0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/69F70/func_80069900.s")
#endif
