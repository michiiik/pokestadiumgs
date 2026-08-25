#include "global.h"


#ifdef VERSION_US
extern s8 D_8800ED30; extern s8 D_8800ED31;
void func_88001900(void) { D_8800ED30 = 10; D_8800ED31 = 1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_167940/func_8800191C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_167940/func_88001C24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_167940/func_88001C6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_167940/func_88001D0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_167940/func_88001EBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_167940/func_880020CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_167940/func_8800225C.s")

void func_880022B4(void *arg0, s16 arg1, s32 arg2) {
    if (arg2 == 0) {
        (*(s16 *)((u8 *)(arg0) + (0x24))) = (s16) ((*(s16 *)((u8 *)(arg0) + (0x24))) & ~arg1);
        return;
    }
    (*(s16 *)((u8 *)(arg0) + (0x24))) = (s16) ((*(s16 *)((u8 *)(arg0) + (0x24))) | arg1);
}
#endif
