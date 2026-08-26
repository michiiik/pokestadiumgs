#include "global.h"


#ifdef VERSION_US
s32 func_83400020(s32 arg0, s32 arg1) {
    return arg0 + arg1 / 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83400038.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_8340010C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_834006A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83400A64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83400AFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83400B98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83400EA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_8340135C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83401454.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_8340156C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83401904.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83401AAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83401E64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_834022F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_8340295C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83402A24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83402B10.s")

s32 func_8003C9B8(s32 *, s32, f32 *);
extern f32 D_834041D4;
extern u8 D_83404250;
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
void func_83402C80(void) {
    Vec3f_SetComponentsDuplicate(&D_834041D4, (*(f32 *)((u8 *)(&D_83404250) + (0x24))), (*(f32 *)((u8 *)(&D_83404250) + (0x28))), (*(f32 *)((u8 *)(&D_83404250) + (0x2C))));
    if (func_8003C9B8(&D_83404250, 0x64, &D_834041D4) == 0) {
        func_8003C9B8(&D_83404250, 9, &D_834041D4);
        return;
    }
    func_8003C9B8(&D_83404250, 0x64, &D_834041D4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83402D00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83402DA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83402F08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83402FE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_834034CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/58/fragment58_code/func_83403560.s")
#endif
