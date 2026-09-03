#include "global.h"


#ifdef VERSION_US
extern u8 **D_87F11768;
void fragment64_main(u8 *arg0) {
    *D_87F11768 = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F00030.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F00138.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F003F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F00534.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F005F0.s")

extern void func_87F005F0(f32, f32);
void func_87F00688(void) {
    func_87F005F0(0.0f, 0.0f);
}

u32 func_87F006AC(void) {
    return *(u32 *)((u8 *)D_87F11768 + 0xC);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F006BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_322C90/func_87F0085C.s")
#endif
