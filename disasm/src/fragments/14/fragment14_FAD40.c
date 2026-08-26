#include "global.h"


#ifdef VERSION_US
s32 func_81302BB0(const u8 *arg0) {
    return *(const s8 *)(arg0 + 0x4DBC) >= 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81302BC0.s")

s32 func_81302C40(const u8 *arg0) {
    return arg0[0x4DBD] == 0 && arg0[0x4DC4] >= 3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81302C64.s")

s32 func_81302CA4(u8 *arg0) {
    return arg0[0x4DBD] == 0x11;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81302CB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81302E58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81302EE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_8130302C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813031D8.s")

void func_81303228(u8 *arg0) {}

void func_81303230(u8 *arg0) {
    arg0[0x4DC4] += 1;
}

void func_81303240(u8 *arg0) {}

extern s32 func_8160A920(void);
extern s32 func_8130A708(u8 *arg0);
extern void func_8160B9A0(u8 *arg0, s32 arg1, s32 arg2);
void func_81303248(u8 *arg0) {
    s32 value = func_8160A920();
    if (func_8130A708(*(u8 **)(arg0 + 0x4DA0) + 0xDA8)) {
        s32 valid = func_81302BB0(arg0);
        func_8160B9A0(arg0, value, valid);
        arg0[0x4DBD] = 0xD;
        *(s32 *)(arg0 + 0x4DAC) = 1;
    }
}

extern void func_81303248(u8 *arg0);
void func_813032B0(u8 *arg0) {
    func_81303248(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813032D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303364.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813033DC.s")

extern void func_81302E58(void *, s32);
s32 func_81311C70(s32, s32 *, u8, s32);
extern u8 D_81311D60;
void func_8130345C(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_81311C70((*(s32 *)((u8 *)(arg0) + (0x4DA0))) + 0x74, &D_81311D60, (*(u8 *)((u8 *)(arg0) + (0xA))), -1);
    if (temp_v0 != -1) {
        if (temp_v0 == 1) {
            (*(s8 *)((u8 *)(arg0) + (0x4DBD))) = 0xF;
            (*(s32 *)((u8 *)(arg0) + (0x4DB8))) = 0;
            (*(f32 *)((u8 *)(arg0) + (0x4DA8))) = 0.0f;
        }
    } else {
        func_8130A570((*(s32 *)((u8 *)(arg0) + (0x4DA0))) + 0xDA8, (*(s32 *)((u8 *)(arg0) + (0x4DB4))));
        (*(s8 *)((u8 *)(arg0) + (0x4DBD))) = 3;
        func_81302E58(arg0, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813034E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813035A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303648.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813037F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813038D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303A38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303A88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303BF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303CA0.s")

extern s32 D_81311DF0;
extern void func_81311C18(s32);
void func_81303D04(void *arg0) {
    if (func_81311C70((*(s32 *)((u8 *)(arg0) + (0x4DA0))) + 0x74, &D_81311DF0, (*(u8 *)((u8 *)(arg0) + (0xA))), -1) != 0) {
        func_81311C18((*(s32 *)((u8 *)(arg0) + (0x4DA0))) + 0x74);
        (*(s8 *)((u8 *)(arg0) + (0x4DBD))) = 4;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303D60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303E20.s")

s32 func_81303A38(void *);
extern void func_81311C18(s32);
void func_81303EA8(void *arg0) {
    func_81311C18((*(s32 *)((u8 *)(arg0) + (0x4DA0))) + 0x74);
    if (func_81303A38(arg0) != 0) {
        (*(s8 *)((u8 *)(arg0) + (0x4DBD))) = 7;
        return;
    }
    (*(s8 *)((u8 *)(arg0) + (0x4DBD))) = 4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303EF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81304178.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81304208.s")

s32 func_81304248(u8 *arg0) {
    s32 var_s0;

    var_s0 = 0;
    if ((*(u8 *)((u8 *)(arg0) + (0x4DBD))) != 0xD) {
        return 0;
    }
    do {
        func_8160B9A0(arg0, var_s0, func_81302BB0(arg0));
        var_s0 += 1;
    } while (var_s0 != 6);
    func_8130A5D0((*(s32 *)((u8 *)(arg0) + (0x4DA0))) + 0xDA8);
    func_8160A928(arg0, 0);
    (*(u8 *)((u8 *)(arg0) + (0x4DBD))) = 0xCU;
    (*(s32 *)((u8 *)(arg0) + (0x4DAC))) = 1;
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813042E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_8130437C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81304444.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_8130456C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81304678.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81304788.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81304884.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813049AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81304A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81304AD0.s")
#endif
