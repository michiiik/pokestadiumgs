#include "global.h"


void func_8410A600(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_379E90/func_8410A608.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_379E90/func_8410A6A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_379E90/func_8410A884.s")
#endif

#ifdef VERSION_US
extern void func_8411DBF4(s32 arg0);
void func_8410A9B4(void) {
    func_8411DBF4(5);
}
#endif

#ifdef VERSION_US
extern u8 D_84190428[];
extern s32 func_8410580C(s32, u8 *, s32);
s32 func_8410A9D4(s32 arg0, u8 *arg1) {
    if (arg0 == 2) {
        func_8410580C(5, D_84190428, *(s32 *)(arg1 + 0x14));
    }
    return 0;
}
void func_8410A9D4_tail_void(void) {
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_379E90/func_8410AA18.s")
#endif

#ifdef VERSION_US
s32 func_8410AE34(s32 arg0, s32 arg1) {
    return 0;
}
#endif
