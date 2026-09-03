#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32EC70/func_87F0C000.s")

extern void func_87F0C000(f32, f32);
void func_87F0C094(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5, s16 arg6) {
    (*(f32 *)((u8 *)(arg0) + (0xC))) = arg1;
    (*(f32 *)((u8 *)(arg0) + (0x10))) = arg2;
    (*(f32 *)((u8 *)(arg0) + (0x14))) = arg3;
    (*(f32 *)((u8 *)(arg0) + (0x18))) = arg4;
    (*(s16 *)((u8 *)(arg0) + (0x1C))) = arg5;
    (*(s16 *)((u8 *)(arg0) + (0x1E))) = arg6;
    func_87F0C000(arg1, arg2);
    (*(s32 *)((u8 *)(arg0) + (0x20))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x24))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x28))) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32EC70/func_87F0C0FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32EC70/func_87F0C358.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32EC70/func_87F0C3EC.s")
#endif
