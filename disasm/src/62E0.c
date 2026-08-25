#include "global.h"


#ifdef VERSION_US
extern u32 D_800CE040;
void func_800056E0(u16* buf) {
    int i, j;

    if (D_800CE040 <= 15) {
        // where is the framebuffer starting, based on the line number of the effect?
        u16* ptr = buf + D_800CE040 * 320;

        // iterate over and clear the 15 lines of the next frame during the effect.
        for (j = 0; j < 15; j++) {
            for (i = 0; i < 320; i++) {
                *ptr++ = 1;
            }
            ptr += (320 * 15); // move the framebuffer pointer to the next line to clear
                               // (down 15 lines).
        }
        osWritebackDCacheAll();
    }
}

void func_8000575C(u16* buf) {
    int i, j;

    if (D_800CE040 <= 15) {
        // where is the framebuffer starting, based on the line number of the effect?
        u16* ptr = buf + D_800CE040 * (640 * 2);

        // iterate over and clear the 15 lines of the next frame during the effect.
        for (j = 0; j < 15; j++) {
            for (i = 0; i < (640 * 2); i++) {
                *ptr++ = 1;
            }
            ptr += ((640 * 2) * 15); // move the framebuffer pointer to the next line to clear
                                     // (down 15 lines).
        }
        osWritebackDCacheAll();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/62E0/func_800057DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/62E0/func_800058B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/62E0/SoftReset_CreateThread.s")
#endif
