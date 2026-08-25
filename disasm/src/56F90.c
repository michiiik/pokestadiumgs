#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056390.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_800564BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_8005655C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056708.s")

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
s32 func_800567B0(s32 arg0, u8* arg1) {
    s32 var_s0 = 0;
    u8 sp34[0x20];

    if (arg1 == NULL) {
        arg1 = sp34;
    }
    func_8000B650((char*)arg1, 0x55, 0x20);
    if (func_80056708(arg0, arg1) != 0) {
        func_8000B650((char*)arg1, 0xAA, 0x20);
        if (func_80056708(arg0, arg1) != 0) {
            s32 i;
            for (i = 0; i < ARRAY_COUNT(sp34); i++) {
                arg1[i] = osGetCount();
            }
            var_s0 = func_80056708(arg0, arg1);
        }
    }
    return var_s0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056870.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056960.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056A5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056AF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056BA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056C98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056E90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056F08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80056F7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80057038.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_800570CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_8005712C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_8005718C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80057210.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80057294.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_800572D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80057318.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_800573C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80057450.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_800574E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80057640.s")

extern u8 D_80128557;
u8 func_80057764(u8 arg0) {
    u8 old = D_80128557;
    D_80128557 = arg0;
    return old;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_8005777C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80057908.s")

extern u8 D_80128558;
void func_80057944(u8 arg0) { D_80128558 &= ~(1 << arg0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/56F90/func_80057970.s")
#endif
