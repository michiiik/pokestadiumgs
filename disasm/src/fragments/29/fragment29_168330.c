#include "global.h"


#ifdef VERSION_US
extern u8 D_8800ED40; extern u8 D_8800ED41;
void func_880022F0(void) { D_8800ED40 = 10; D_8800ED41 = 1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_8800230C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880024FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_8800254C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002640.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002720.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002820.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002958.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002AA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002BA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002C2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002CB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002EC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880032C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_8800335C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003430.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003480.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003534.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880036CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003858.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003A00.s")

extern void func_88003A00();
extern s8 D_8800EF18;
void func_88003FBC(void *arg0) {
    s8 var_v0;

    if ((*(s32 *)((u8 *)(arg0) + (0x1C))) == 3) {
        if ((*(s32 *)((u8 *)(arg0) + (0x14))) == 3) {
            var_v0 = 4;
        } else {
            var_v0 = D_8800EF18;
        }
        if (var_v0 == (*(s8 *)((u8 *)(arg0) + (0x20)))) {
            func_88003A00();
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004014.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880040D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004180.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880046EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004804.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880048D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004990.s")
#endif
