#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_882011E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_882012E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201330.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_8820137C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201420.s")

extern void func_88201420(s32, s32);
void func_88201608(s32 arg0) {
    func_88201420(arg0, 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201628.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_8820172C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_882017F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201A74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201E28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201ED0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_174460/func_88201F0C.s")

extern s32 HAL_Strcmp(const s8 *, const s8 *);
extern s8 D_8800686D[];
extern u8 D_882345D4;
extern u16 D_8800686A;
s32 func_88201F7C(void *arg0) {
    s32 result = 1;
    if (D_882345D4 == 0) {
        if (*(u16 *)((u8 *)arg0 + 6) != *(u16 *)&D_8800686A ||
            HAL_Strcmp(D_8800686D, (s8 *)((u8 *)arg0 + 0x40)) != 0) result = 0;
    }
    return result;
}
#endif
