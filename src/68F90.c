#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/68F90/func_80068390.s")

extern s32 func_8006A3E0(void);
extern s32 func_8006A424(void);
extern void func_80055948(s32);
extern u8 *func_8006218C(s32, s32, s32, s32);
extern void func_8006249C(void *, s32, u8 *);
extern void func_80062304(u8 *);
extern void func_80055028(void);
s32 func_80068464(u8 *arg0) {
    u8 *temp_s0;
    u8 *temp_v0;
    void *sp24;
    s32 result;

    temp_s0 = *(u8 **)(arg0 + 0x20);
    result = 0;
    if (temp_s0[0x423] != 0) {
        *(s16 *)(temp_s0 + 0x488) = func_8006A3E0();
        *(s16 *)(temp_s0 + 0x48A) = func_8006A424();
        func_80055948(3);
        temp_v0 = func_8006218C(0x1A, 0, 0, 1);
        sp24 = temp_v0;
        func_8006249C(temp_s0, 1, temp_v0);
        func_80062304(sp24);
        func_80055028();
        result = 1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/68F90/func_800684F0.s")
#endif
