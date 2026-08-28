#include "global.h"


#ifdef VERSION_US
s32 func_81302BB0(const u8 *arg0) {
    return *(const s8 *)(arg0 + 0x4DBC) >= 0;
}

extern s32 func_8160A920(void);
s32 func_81302BC0(u8 *arg0) {
    s32 var_v1;
    s32 offset;
    u8 *entry;

    offset = func_8160A920() * 0xCE8;
    entry = arg0 + offset;
    var_v1 = entry[0x20] == 0;
    if (var_v1 != 0) {
        var_v1 = arg0[0x4DBD] == 0xD;
        if (var_v1 != 0) {
            var_v1 = func_81302BB0(arg0) == 0;
        }
    }
    return var_v1;
}

s32 func_81302C40(const u8 *arg0) {
    return arg0[0x4DBD] == 0 && arg0[0x4DC4] >= 3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81302C64.s")

s32 func_81302CA4(u8 *arg0) {
    return arg0[0x4DBD] == 0x11;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81302CB4.s")

extern void func_81302CB4(u8 *, s16 *);
extern void func_81609A90(u8 *, u8 *);
extern void func_8160A928(u8 *, s32);
void func_81302E58(void *arg0, s32 arg1) {
    u8 sp30[8];
    u8 sp28[8];
    f32 sp24;

    sp24 = *(f32 *)((u8 *)arg0 + 0x4DA4);
    *(f32 *)((u8 *)arg0 + 0x4DA4) = 0.0f;
    func_81302CB4((u8 *)arg0, (s16 *)sp30);
    *(f32 *)((u8 *)arg0 + 0x4DA4) = 16.0f;
    func_81302CB4((u8 *)arg0, (s16 *)sp28);
    if (arg1 != 0) {
        func_81609A90(sp30, sp28);
    } else {
        func_81609A90(sp28, sp30);
    }
    *(f32 *)((u8 *)arg0 + 0x4DA4) = sp24;
}

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

extern f32 func_816092FC(void);
extern s32 func_8160A9CC(void);
void func_813032D0(void *arg0) {
    f32 delta;
    f32 temp_fv1;

    delta = func_816092FC();
    *(f32 *)((u8 *)arg0 + 0x4DA4) =
        *(f32 *)((u8 *)arg0 + 0x4DA4) + delta;
    temp_fv1 = *(f32 *)((u8 *)arg0 + 0x4DA4);
    if (temp_fv1 <= 0.0f) {
        *(f32 *)((u8 *)arg0 + 0x4DA4) = 0.0f;
        return;
    }
    if (temp_fv1 >= 16.0f) {
        *(f32 *)((u8 *)arg0 + 0x4DA4) = 16.0f;
        if (func_8160A9CC() != 0) {
            *(u8 *)((u8 *)arg0 + 0x4DBD) = 4;
            return;
        }
        *(u8 *)((u8 *)arg0 + 0x4DBD) = 0xC;
    }
}

f32 func_816092FC(void);
f32 func_816092FC(void);
void func_81303364(void *arg0) {
    f32 temp_fv1;

    (*(f32 *)((u8 *)(arg0) + (0x4DA4))) = (f32) ((*(f32 *)((u8 *)(arg0) + (0x4DA4))) - func_816092FC());
    temp_fv1 = (*(f32 *)((u8 *)(arg0) + (0x4DA4)));
    if (temp_fv1 <= 0.0f) {
        (*(f32 *)((u8 *)(arg0) + (0x4DA4))) = 0.0f;
        (*(s8 *)((u8 *)(arg0) + (0x4DBD))) = 0;
        (*(s8 *)((u8 *)(arg0) + (0x4DC4))) = 0;
        return;
    }
    if (temp_fv1 >= 16.0f) {
        (*(f32 *)((u8 *)(arg0) + (0x4DA4))) = 16.0f;
    }
}

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

extern void func_8160A94C(u8 *);
extern void func_8160A928(u8 *, s32);
extern f32 func_816092FC(void);
void func_813034E8(u8 *arg0) {
    f32 delta;
    f32 temp_fv1;

    delta = func_816092FC();
    delta = delta / 16;
    *(f32 *)(arg0 + 0x4DA8) = *(f32 *)(arg0 + 0x4DA8) + delta;
    temp_fv1 = *(f32 *)(arg0 + 0x4DA8);
    if (temp_fv1 >= 1.0f) {
        *(u8 *)(arg0 + 0x4DBD) = 0xC;
        return;
    }
    if ((temp_fv1 >= 0.5f) && (*(u32 *)(arg0 + 0x4DB8) == 0)) {
        *(s8 *)(arg0 + 0x4DBC) = *(s8 *)(arg0 + 0x4DBC) + 1;
        func_8160A94C(arg0);
        func_8160A928(arg0, 0);
        *(u32 *)(arg0 + 0x4DB8) = 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813035A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303648.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813037F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_813038D0.s")

extern s32 func_8160A9F0(void);
s32 func_81303A38(void *arg0) {
    void *entry;

    entry = *(void **)(*(u8 **)((u8 *)(u32)(*(s32 *)((u8 *)arg0 + 0x4DA0) + 0x20000) - 0x5EB8) + 0x940);
    if (entry == NULL) {
        return 0;
    }
    return *(u16 *)((u8 *)entry + 0x38) < func_8160A9F0();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303A88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303BF4.s")

extern s32 func_813022F4(void *arg0, void *arg1);
extern void func_81311C18(s32 arg0);
void func_81303CA0(void *arg0) {
    void *temp_a0;

    func_81311C18(*(s32 *)((u8 *)arg0 + 0x4DA0) + 0x74);
    temp_a0 = *(void **)((u8 *)arg0 + 0x4DA0);
    if ((*(u8 *)((u8 *)temp_a0 + 0x8C) == 0) && (func_813022F4(temp_a0, arg0) != 0)) {
        *(u8 *)((u8 *)arg0 + 0x4DBD) = 5;
        return;
    }
    *(u8 *)((u8 *)arg0 + 0x4DBD) = 6;
}

extern s32 D_81311DF0;
extern void func_81311C18(s32);
void func_81303D04(void *arg0) {
    if (func_81311C70((*(s32 *)((u8 *)(arg0) + (0x4DA0))) + 0x74, &D_81311DF0, (*(u8 *)((u8 *)(arg0) + (0xA))), -1) != 0) {
        func_81311C18((*(s32 *)((u8 *)(arg0) + (0x4DA0))) + 0x74);
        (*(s8 *)((u8 *)(arg0) + (0x4DBD))) = 4;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81303D60.s")

extern s32 D_81311E14;
extern s32 func_81311C70(s32, s32 *, u8, s32);
void func_81303E20(u8 *arg0) {
    s32 temp_v0_2;
    void *temp_v0;

    temp_v0 = *(void **)(arg0 + 0x4DA0);
    temp_v0_2 = func_81311C70(
        (s32)temp_v0 + 0x74,
        &D_81311E14,
        arg0[0xA],
        *(u16 *)((u8 *)*(void **)(*(u8 **)((u8 *)(u32)((s32)temp_v0 + 0x20000) - 0x5EB8) + 0x940) + 0x38)
    );
    if (temp_v0_2 != 0) {
        if (temp_v0_2 == 0) {
            func_8160A928(arg0, 5);
            arg0[0x4DBD] = 0xC;
            return;
        }
        func_8160A928(arg0, 0);
        arg0[0x4DBD] = 0x11;
    }
}

s32 func_81303A38(void *);
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

s32 func_81304208(u8 *arg0) {
    if (arg0[0x4DBD] != 0xD) {
        return 0;
    }
    arg0[0x4DBD] = 3;
    func_81302E58(arg0, 0);
    return 1;
}

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

extern void func_81302CB4(u8 *arg0, s16 *arg1);
extern void func_8160B5BC(void *arg0, s16 *arg1);
void func_813049AC(u8 *arg0, s16 *arg1) {
    s16 *output = arg1;
    s16 temp[2];

    func_81302CB4(arg0, temp);
    func_8160B5BC(arg0, output);
    output[0] += temp[0];
    output[1] += temp[1];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81304A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_FAD40/func_81304AD0.s")
#endif
