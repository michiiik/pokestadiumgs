#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38D510/func_8411DC80.s")

extern u8 *D_84193DD0;
extern s32 func_8411E1F8(s32);
void func_8411DCCC(u8 *arg0, f32 *arg1) {
    s32 index;
    arg1[0] = *(f32 *)(arg0 + 0x24);
    arg1[2] = *(f32 *)(arg0 + 0x2C);
    index = func_8411E1F8((s32)arg0);
    if ((*(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x12) & 2) != 0) {
        arg1[1] = *(f32 *)(arg0 + 0x638) + 200.0f;
    } else {
        index = func_8411E1F8((s32)arg0);
        if ((*(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x12) & 4) != 0) {
            arg1[1] = 0.0f;
        } else {
            arg1[1] = *(f32 *)(arg0 + 0x638);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38D510/func_8411DD8C.s")

extern void func_8411DD8C(void);
void func_8411E084(void) {
    func_8411DD8C();
}

extern f32 D_80087E50[];
extern f32 D_80088E50[];
void func_8411E0A4(void *arg0, void *arg1, void *arg2) {
    extern void func_8411DD8C();
    func_8411DD8C(arg0, arg1);
    *(f32 *)((u8 *)arg1 + 4) += *(f32 *)((u8 *)arg2 + 0x7C);
    *(f32 *)((u8 *)arg1 + 0) += *(f32 *)((u8 *)arg2 + 0x78) * D_80087E50[*(u16 *)((u8 *)arg0 + 0x20) >> 4];
    *(f32 *)((u8 *)arg1 + 8) += *(f32 *)((u8 *)arg2 + 0x78) * D_80088E50[*(u16 *)((u8 *)arg0 + 0x20) >> 4];
}

extern s32 D_84191208;
s32 func_8411E140(s32 arg0) {
    if (arg0 == D_84191208) return 0x4000;
    return -0x4000;
}

extern s32 D_84191208, D_8419120C;
s32 func_8411E164(s32 arg0) {
    if (arg0 == D_84191208) return D_8419120C;
    return D_84191208;
}

s32 func_8411E188(s8 arg0) {
    if (arg0 == 0) return D_84191208;
    return D_8419120C;
}

f32 func_8411E1B4(u8 *arg0) {
    return *(f32 *)(arg0 + 0x648);
}

f32 func_8411E1BC(u8 *arg0) {
    return *(f32 *)(arg0 + 0x648) - *(f32 *)(arg0 + 0x650);
}

f32 func_8411E1CC(u8 *arg0) {
    return *(f32 *)(arg0 + 0x64C);
}

s32 func_8411E1D4(s32 arg0) {
    if (arg0 == D_84191208) return 1;
    return -1;
}

s32 func_8411E1F8(s32 arg0) {
    if (arg0 == D_84191208) return 0;
    return 1;
}

s32 func_8411E21C(u8 *arg0) {
    return *(u8 *)(arg0 + 0x61C);
}

s32 func_8411E224(u8 *arg0) {
    return *(u8 *)(arg0 + 0x61D);
}

s32 func_8411E22C(u8 *arg0) {
    return *(u8 *)(*(u8 **)(arg0 + 0x2D4) + 0x13DA);
}

s32 func_8411E238(u8 *arg0) {
    return *(u8 *)(*(u8 **)(arg0 + 0x2D4) + 0x13DB);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38D510/func_8411E244.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38D510/func_8411E358.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38D510/func_8411E46C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38D510/func_8411E580.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38D510/func_8411ED40.s")

s32 func_8411EE54(u8 *arg0) {
    return *(u8 *)(arg0 + 0x661);
}

s32 func_8411EE5C(u8 *arg0) {
    return *(u8 *)(arg0 + 0x629);
}

s32 func_8411EE64(u8 *arg0) {
    return *(u8 *)(arg0 + 0x62B);
}

s32 func_8411EE6C(u8 *arg0) {
    return *(u8 *)(arg0 + 0x62D);
}

extern void func_84108E00(u8 *, s32);
void func_8411EE74(u8 *arg0) {
    s32 index;
    arg0[1] &= 0xFFFE;
    index = func_8411E1F8(arg0);
    if ((*(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x10) & 7) != 0) {
        func_84108E00(arg0, 2);
    }
    index = func_8411E1F8(arg0);
    if (*(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x10) == 0x20) {
        func_84108E00(arg0, 1);
    }
}

void func_8411EF08(u8 *arg0) {
    arg0[1] |= 1;
}

void func_8411EF18(u8 *arg0) {
    *(s16 *)(arg0 + 0x18) = 0;
}

void func_8411EF20(u8 *arg0) {
    *(s16 *)(arg0 + 0x18) = 3;
}

extern void func_8411EF08(u8 *);
extern s32 func_8411E164(s32);
extern void func_8411EE74(u8 *);
void func_8411EF2C(s32 arg0) {
    func_8411EF08((u8 *)arg0);
    func_8411EE74((u8 *)func_8411E164(arg0));
}

s32 func_8411EF5C(u8 *arg0) {
    return *(u16 *)(arg0 + 0x1A);
}

extern s32 D_84191208, D_84190414, D_84190418;
s32 func_8411EF64(s32 arg0) {
    if (arg0 == D_84191208) return D_84190414;
    return D_84190418;
}

extern void func_8411E084(void);
extern f32 func_8411E1CC(u8 *arg0);
f32 func_8411EF90(u8 *arg0) {
    extern void func_8411E084();
    f32 values[2];
    f32 temp_fv1;
    f32 var_fa0;
    func_8411E084(arg0, values - 1);
    temp_fv1 = func_8411E1CC(arg0) * 0.5f;
    var_fa0 = values[0] - temp_fv1;
    if (values[0] < temp_fv1) {
        var_fa0 = 0.0f;
    }
    return var_fa0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38D510/func_8411EFE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38D510/func_8411F1AC.s")
#endif
