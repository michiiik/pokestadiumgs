#include "global.h"


#ifdef VERSION_US
void func_82906A10(f32 *arg0, f32 *arg1) { arg0[0] = arg1[0]; arg0[1] = arg1[1]; arg0[2] = arg1[2]; }

void func_82906A2C(f32 *arg0, const f32 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
    arg0[3] = arg1[3];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82906A50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82906B6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82906CC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82906D64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82906DFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82906EC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82906F8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82907054.s")

extern void func_82906B6C(f32 *, s32 *, f32 *, s32);
extern f32 D_8291247C;
extern u8 D_8291248C;
extern f32 D_82919DA8;
extern void func_82906B6C(f32 *, s32 *, f32 *, s32);
extern f32 D_8291247C;
extern u8 D_8291248C;
extern f32 D_82919DA8;
void func_8290711C(s32 arg0) {
    if (arg0 == 0) {
        func_82906A2C(&D_82919DA8, &D_8291247C);
    }
    if ((arg0 >= 0xC) && (arg0 < 0x27)) {
        func_82906B6C(&D_82919DA8, &D_8291248C, &D_8291247C, 0x1A);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82907188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_343510/func_82907274.s")
#endif
