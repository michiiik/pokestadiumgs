#include "global.h"


#ifdef VERSION_US
void func_8410AE50(u8 *arg0, s16 a1, s16 a2, s16 a3, s16 a4) {
    *(s16 *)(arg0 + 0x9A) = a1;
    *(s16 *)(arg0 + 0x9C) = a2;
    *(s16 *)(arg0 + 0x9E) = a3;
    *(s16 *)(arg0 + 0xA0) = a4;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410AE8C.s")
#endif

#ifdef VERSION_US
extern void func_8410AE8C(u8 *, s16, s16, s16, s32);
void func_8410AF1C(void) {
    extern void func_8410AE8C(u8 *, s16, s16, s16, s32);
    extern u8 *D_841911E0;
    extern u8 *D_841911E4;
    extern u8 D_84190428[];
    extern u8 D_841910E0[];

    func_8410AE50(D_841911E0, 0, 0, 0x140, 0x78);
    func_8410AE8C(D_84190428,
        *(s16 *)(D_841911E0 + 0x9A),
        *(s16 *)(D_841911E0 + 0x9C),
        *(s16 *)(D_841911E0 + 0x9E),
        (s32)*(s16 *)(D_841911E0 + 0xA0));
    func_8410AE50(D_841911E4, 0, 0x78, 0x140, 0x78);
    func_8410AE8C(D_841910E0,
        *(s16 *)(D_841911E4 + 0x9A),
        *(s16 *)(D_841911E4 + 0x9C),
        *(s16 *)(D_841911E4 + 0x9E),
        (s32)*(s16 *)(D_841911E4 + 0xA0));
    D_841910E0[1] = (u8)(D_841910E0[1] | 0x10);
}
#endif

#ifdef VERSION_US
extern void func_8410AE8C(u8 *, s16, s16, s16, s32);
extern u8 *D_841911E0;
extern u8 *D_841911E4;
extern u8 D_84190428[];
extern u8 D_841910E0[];
void func_8410AFD4(void) {
    func_8410AE50(D_841911E0, 0, 0, 0xA0, 0xF0);
    func_8410AE8C(D_84190428,
        *(s16 *)(D_841911E0 + 0x9A),
        *(s16 *)(D_841911E0 + 0x9C),
        *(s16 *)(D_841911E0 + 0x9E),
        (s32)*(s16 *)(D_841911E0 + 0xA0));
    func_8410AE50(D_841911E4, 0xA0, 0, 0xA0, 0xF0);
    func_8410AE8C(D_841910E0,
        *(s16 *)(D_841911E4 + 0x9A),
        *(s16 *)(D_841911E4 + 0x9C),
        *(s16 *)(D_841911E4 + 0x9E),
        (s32)*(s16 *)(D_841911E4 + 0xA0));
    D_841910E0[1] = (u8)(D_841910E0[1] | 0x10);
}
#endif

#ifdef VERSION_US
void func_8410B08C(void) {
    extern void func_8410AE8C(u8 *, s16, s16, s16, s32);
    extern u8 D_84190428[];
    extern u8 D_841910E0[];
    extern u8 *D_841911E0;
    extern u8 *D_841911E4;
    func_8410AE8C(D_84190428,
        *(s16 *)(D_841911E0 + 0x9A),
        *(s16 *)(D_841911E0 + 0x9C),
        *(s16 *)(D_841911E0 + 0x9E),
        (s32)*(s16 *)(D_841911E0 + 0xA0));
    func_8410AE8C(D_841910E0,
        *(s16 *)(D_841911E4 + 0x9A),
        *(s16 *)(D_841911E4 + 0x9C),
        *(s16 *)(D_841911E4 + 0x9E),
        (s32)*(s16 *)(D_841911E4 + 0xA0));
    D_841910E0[1] = (u8)(D_841910E0[1] | 0x10);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B104.s")
#endif

#ifdef VERSION_US
extern void func_8410AE8C(u8 *, s16, s16, s16, s32);
extern void func_84111248();
extern u8 D_841910E0[];
extern u8 *D_841911E4;
extern u8 D_84190428[];
void func_8410B1CC(void) {
    func_8410AE8C(D_841910E0, (*(s16 *)((u8 *)(D_841911E4) + (0x9A))), (*(s16 *)((u8 *)(D_841911E4) + (0x9C))), (*(s16 *)((u8 *)(D_841911E4) + (0x9E))), (s32) (*(s16 *)((u8 *)(D_841911E4) + (0xA0))));
    (*(u8 *)((u8 *)(D_84190428) + (1))) = (u8) ((*(u8 *)((u8 *)(D_84190428) + (1))) & 0xFFEF);
    func_84111248();
}
#endif

#ifdef VERSION_US
extern void func_841112C8();
extern u8 *D_841911E0;
void func_8410B224(void) {
    func_8410AE8C(D_84190428, (*(s16 *)((u8 *)(D_841911E0) + (0x9A))), (*(s16 *)((u8 *)(D_841911E0) + (0x9C))), (*(s16 *)((u8 *)(D_841911E0) + (0x9E))), (s32) (*(s16 *)((u8 *)(D_841911E0) + (0xA0))));
    (*(u8 *)((u8 *)(D_841910E0) + (1))) = (u8) ((*(u8 *)((u8 *)(D_841910E0) + (1))) & 0xFFEF);
    func_841112C8();
}
#endif

#ifdef VERSION_US
void func_8410B27C(u8 *arg0, u8 *arg1) {
    extern void *main_pool_alloc(s32, s32);
    D_841911E0 = main_pool_alloc(0xA4, 0);
    *(u8 **)D_841911E0 = arg0;
    D_841911E4 = main_pool_alloc(0xA4, 0);
    *(u8 **)D_841911E4 = arg1;
}
#endif

#ifdef VERSION_US
extern void func_84111248();
void func_8410B2DC(u8 *arg0, u8 *arg1) {
    *(f32 *)(arg0 + 0x34) = 20.0f;
    *(f32 *)(arg0 + 0x38) = 6400.0f;
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    *(f32 *)(arg1 + 0x34) = 20.0f;
    *(f32 *)(arg1 + 0x38) = 6400.0f;
    *(f32 *)(arg1 + 0x2C) = 45.0f;
    func_84111248();
    func_841112C8();
}
#endif

#ifdef VERSION_US
u8 *func_8410B330(u8 *arg0) {
    if (arg0 == *(u8 **)D_841911E0) return D_841911E0;
    return D_841911E4;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B35C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B420.s")
#endif

#ifdef VERSION_US
void func_8410B578(f32 arg0) {
    *(f32 *)(D_841911E0 + 0x8C) = arg0;
    *(u16 *)(D_841911E0 + 0x96) = 0;
}
#endif

#ifdef VERSION_US
void func_8410B594(u8 *arg0) {
    extern u8 *D_841911E0;
    extern void func_8411E084(u8 *, f32 *);
    extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
    f32 values[3];

    func_8411E084(arg0, values);
    Vec3f_SetComponentsDuplicate((f32 *)(D_841911E0 + 0x5C),
        values[0], values[1] + *(f32 *)(D_841911E0 + 0x7C), values[2]);
    Vec3f_SetComponentsDuplicate((f32 *)(D_841911E0 + 0x50),
        values[0], values[1] + *(f32 *)(D_841911E0 + 0x7C), values[2]);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B60C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B704.s")
#endif

#ifdef VERSION_US
extern u8 D_8418455C;
void func_8410B884(u8 *arg0, void *arg1, u8 *arg2, s16 arg3) {
    s32 var_v0;
    void *temp_v1;

    var_v0 = 1;
    if (arg3 < 0) {
        var_v0 = -1;
    }
    temp_v1 = ((*(s16 *)(arg2 + 0x98) * 0x1C) + &D_8418455C);
    *(s16 *)(arg2 + 0x3C) = *(s16 *)((u8 *)temp_v1 + 8);
    *(s16 *)(arg2 + 0x3E) = (*(s16 *)((u8 *)temp_v1 + 0xA) * var_v0) + arg3;
    *(f32 *)(arg2 + 0x40) = *(f32 *)((u8 *)arg1 + 0x64C) * *(f32 *)((u8 *)temp_v1 + 0xC);
    *(f32 *)(arg2 + 0x4C) = *(f32 *)((u8 *)temp_v1 + 0x14);
    *(f32 *)(arg2 + 0x48) = *(f32 *)((u8 *)temp_v1 + 0x18);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B8FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410B974.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410BDA0.s")
#endif

#ifdef VERSION_US
extern u8 *D_841911E8;
extern u8 *func_8410B330(u8 *);
extern void func_8410BDA0(u8 *, s32);
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_84120BB4(u8 *, s32);
void func_8410C304(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *temp_v0;
    temp_v0 = func_8410B330(arg0);
    D_841911E8 = temp_v0;
    func_84120BB4(arg0, arg1);
    *(f32 *)(D_841911E8 + 0x50) = func_8411E1D4(arg1) * -150.0f;
    *(f32 *)(D_841911E8 + 0x54) = 20.0f;
    *(f32 *)(D_841911E8 + 0x58) = 0.0f;
    *(f32 *)(D_841911E8 + 0x74) = 180.0f;
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    *(f32 *)(D_841911E8 + 0x88) = 45.0f;
    Vec3f_SetComponentsDuplicate((f32 *)(D_841911E8 + 0x68), -1.0f, -1.0f, -1.0f);
    Vec3f_SetComponentsDuplicate((f32 *)(D_841911E8 + 0x5C), -1.0f, -1.0f, -1.0f);
    func_8410BDA0(arg0, arg1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410C400.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410C544.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410C720.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410C840.s")
#endif

#ifdef VERSION_US
extern u8 *D_841911E8;
extern u8 D_8418393C;
extern u8 D_8418455C;
extern u8 D_84184968;
extern u8 D_84184984;
extern u8 *func_8410B330(u8 *);
extern s32 func_8411DC80(u16, s32 *, s32);
extern s32 func_8411E140(s32);
extern void func_8410B974(u8 *, void *, s16, s32, s32);
extern void func_800371B4(u8 *, u8 *, s32, s16, s32);
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
void func_8410C934(u8 *arg0, s32 arg1, s16 arg2) {
    s16 var_a2;
    s16 var_t6 = 1;
    u8 *temp_v1;
    u8 *arg1_ptr = (u8 *)(u32)arg1;

    D_841911E8 = func_8410B330(arg0);
    if (func_8411DC80(arg1_ptr[0x61F], (s32 *)&D_8418393C, 8) != 0) {
        var_a2 = (s16)func_8411E140(arg1);
    } else {
        var_a2 = *(s16 *)(arg1_ptr + 0x20);
    }
    if (var_a2 < 0) {
        var_t6 = -1;
    }
    *(f32 *)(D_841911E8 + 0x44) = 0.0f;
    func_8410B974(arg0, arg1_ptr, var_a2, *(s32 *)((u8 *)&arg2 - 2), 1);
    temp_v1 = (u8 *)&D_8418455C + (*(s32 *)((u8 *)&arg2 - 2) * 0x1C);
    *(s16 *)(D_841911E8 + 0x90) = *(s16 *)temp_v1;
    *(s16 *)(D_841911E8 + 0x92) = (*(s16 *)(temp_v1 + 2) * var_t6) + var_a2;
    *(f32 *)(D_841911E8 + 0x74) *= *(f32 *)(temp_v1 + 4);
    *(f32 *)(D_841911E8 + 0x88) = *(f32 *)(temp_v1 + 0x10);
    if ((*(s32 *)((u8 *)&arg2 - 2) == 0x24) || (temp_v1 == (u8 *)&D_84184968) || (temp_v1 == (u8 *)&D_84184984)) {
        *(f32 *)(arg0 + 0x2C) = 80.0f;
        *(f32 *)(D_841911E8 + 0x88) = 80.0f;
    } else {
        *(f32 *)(arg0 + 0x2C) = 45.0f;
        *(f32 *)(D_841911E8 + 0x88) = 45.0f;
    }
    func_800371B4(D_841911E8 + 0x50, arg0 + 0xA8, *(s32 *)(D_841911E8 + 0x74), *(s16 *)(D_841911E8 + 0x90), (s32)*(s16 *)(D_841911E8 + 0x92));
    Vec3f_SetComponentsDuplicate((f32 *)(D_841911E8 + 0x68), *(f32 *)(arg0 + 0xA8), *(f32 *)(arg0 + 0xAC), *(f32 *)(arg0 + 0xB0));
}
#endif

#ifdef VERSION_US
extern void func_800371B4(u8 *, u8 *, s32, s16, s32);
extern u8 * func_8410B330(u8 *);
extern void func_8410B974(u8 *, void *, s16, s32, s32);
extern s32 func_8411DC80(u16, s32 *, s32);
extern s32 func_8411E140(s32);
void func_8410CAE4(u8 *arg0, s32 arg1, s16 arg2) {
    s16 var_a2;
    s16 var_t6 = 1;
    u8 *temp_v1;
    u8 *arg1_ptr = (u8 *)(u32)arg1;

    D_841911E8 = func_8410B330(arg0);
    if (func_8411DC80(arg1_ptr[0x61F], (s32 *)&D_8418393C, 8) != 0) {
        var_a2 = (s16)func_8411E140(arg1);
    } else {
        var_a2 = *(s16 *)(arg1_ptr + 0x20);
    }
    if (var_a2 < 0) {
        var_t6 = -1;
    }
    *(f32 *)(D_841911E8 + 0x44) = 0.0f;
    func_8410B974(arg0, arg1_ptr, var_a2, *(s32 *)((u8 *)&arg2 - 2), 0);
    temp_v1 = (u8 *)&D_8418455C + (*(s32 *)((u8 *)&arg2 - 2) * 0x1C);
    *(s16 *)(D_841911E8 + 0x90) = *(s16 *)temp_v1;
    *(s16 *)(D_841911E8 + 0x92) = (*(s16 *)(temp_v1 + 2) * var_t6) + var_a2;
    *(f32 *)(D_841911E8 + 0x74) *= *(f32 *)(temp_v1 + 4);
    *(f32 *)(D_841911E8 + 0x88) = *(f32 *)(temp_v1 + 0x10);
    if ((*(s32 *)((u8 *)&arg2 - 2) == 0x24) || (temp_v1 == (u8 *)&D_84184968) || (temp_v1 == (u8 *)&D_84184984)) {
        *(f32 *)(arg0 + 0x2C) = 80.0f;
        *(f32 *)(D_841911E8 + 0x88) = 80.0f;
    } else {
        *(f32 *)(arg0 + 0x2C) = 45.0f;
        *(f32 *)(D_841911E8 + 0x88) = 45.0f;
    }
    func_800371B4(D_841911E8 + 0x50, arg0 + 0xA8, *(s32 *)(D_841911E8 + 0x74), *(s16 *)(D_841911E8 + 0x90), (s32)*(s16 *)(D_841911E8 + 0x92));
    Vec3f_SetComponentsDuplicate((f32 *)(D_841911E8 + 0x68), *(f32 *)(arg0 + 0xA8), *(f32 *)(arg0 + 0xAC), *(f32 *)(arg0 + 0xB0));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410CC90.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410CD3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410CF80.s")
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_024(u8 *arg0, s32 arg1) {
    extern void func_841203B4(u8 *, f32, f32);
    if (*(f32 *)(arg0 + 0xB8) <= *(f32 *)(arg0 + 0xAC)) {
        return;
    }
    func_841203B4(arg0 + 0xAC, *(f32 *)(arg0 + 0xB8), 0.02f);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410D088.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410D174.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410D5CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410D9B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410DAC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410DEB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410DFC4.s")
#endif

#ifdef VERSION_US
extern void func_8410B704(u8 *, void *, u8 *, u8 *);
extern void func_8410B884(u8 *, void *, u8 *, s16);
extern void func_8410DFC4(u8 *, void *);
s32 func_8411DC80(u16, s32 *, s32);
extern u8 D_8418393C;
extern u8 *D_841911E8;
extern u8 *func_8410B330(u8 *);
s32 func_8411E140(s32 arg0);
void func_8410E688(u8 *arg0, void *arg1) {
    s16 var_a3;

    D_841911E8 = func_8410B330(arg0);
    if (func_8411DC80((*(u8 *)((u8 *)(arg1) + (0x61F))), &D_8418393C, 8) != 0) {
        if ((*(u8 *)((u8 *)(arg1) + (0x61F))) == 4) {
            func_8410DFC4(arg0, arg1);
        }
        var_a3 = func_8411E140((s32) arg1);
    } else {
        var_a3 = (*(s16 *)((u8 *)(arg1) + (0x20)));
    }
    func_8410B884(arg0, arg1, D_841911E8, var_a3);
    func_8410B704(arg0, arg1, D_841911E8, arg0 + 0xB4);
}
#endif

#ifdef VERSION_US
extern u8 * func_8410B330(u8 *);
extern void func_8410B884(u8 *arg0, void *arg1, u8 *arg2, s16 arg3);
extern s32 func_8411DC80(u16, s32 *, s32);
extern s32 func_8411E140(s32 arg0);
void func_8410E73C(u8 *arg0, void *arg1) {
    s16 var_a3;

    D_841911E8 = func_8410B330(arg0);
    if (func_8411DC80((*(u8 *)((u8 *)(arg1) + (0x61F))), &D_8418393C, 8) != 0) {
        var_a3 = func_8411E140((s32) arg1);
    } else {
        var_a3 = (*(s16 *)((u8 *)(arg1) + (0x20)));
    }
    func_8410B884(arg0, arg1, D_841911E8, var_a3);
    func_8410B704(arg0, arg1, D_841911E8, D_841911E8 + 0x50);
}
#endif

#ifdef VERSION_US
s32 func_8411DC80(u16, s32 *, s32);
extern u8 *D_84193DD0;
s32 func_8411E140(s32 arg0);
void func_8410E7D0(u8 *arg0, void *arg1) {
    s16 var_a3;

    D_841911E8 = func_8410B330(arg0);
    if ((*(u16 *)((u8 *)(D_84193DD0) + (4))) != 0x11) {
        if (func_8411DC80((*(u8 *)((u8 *)(arg1) + (0x61F))), &D_8418393C, 8) != 0) {
            var_a3 = func_8411E140((s32) arg1);
        } else {
            var_a3 = (*(s16 *)((u8 *)(arg1) + (0x20)));
        }
        func_8410B884(arg0, arg1, D_841911E8, var_a3);
        func_8410B704(arg0, arg1, D_841911E8, D_841911E8 + 0x50);
    }
}
#endif

#ifdef VERSION_US
void func_8410E878(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_8410B884(arg0, arg1, D_841911E8, (s16) (func_8411E1D4(arg1) << 0xE));
    func_8410B704(arg0, arg1, D_841911E8, D_841911E8 + 0x50);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410E8E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410EA58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410EB50.s")
#endif

#ifdef VERSION_US
f32 func_8410EB50();
extern void func_8411FEE8(s32);
extern s32 D_841911EC;
extern s32 D_84184148;
void BattleAnim_ModelDispatch_072(void) {
    if (func_8410EB50() <= 1.75f) {
        func_8411FEE8(0);
        (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410ED98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410F0D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410F1A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410F3E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410F6AC.s")
#endif

#ifdef VERSION_US
extern void func_800371B4(u8 *, u8 *, s32, s16, s32);
extern u8 * func_8410B330(u8 *);
void BattleAnim_ModelDispatch_149(u8 *arg0, s32 arg1) {
    extern s32 BattleAnim_StepToS16(s16 *, s16, s16);
    extern void func_800371B4(u8 *, u8 *, s32, s16, s32);
    D_841911E8 = func_8410B330(arg0);
    BattleAnim_StepToS16((s16 *)(D_841911E8 + 0x92), -0x8000, 0x71C);
    func_800371B4(arg0 + 0xA8, arg0 + 0xB4,
        *(s32 *)(D_841911E8 + 0x74),
        *(s16 *)(D_841911E8 + 0x90),
        (s32)*(s16 *)(D_841911E8 + 0x92));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410F78C.s")
#endif

#ifdef VERSION_US
extern void func_800371B4(u8 *, u8 *, s32, s16, s32);
extern u8 * func_8410B330(u8 *);
void BattleAnim_ModelDispatch_156(u8 *arg0, s32 arg1) {
    extern s32 BattleAnim_StepToS16(s16 *, s16, s16);
    extern void func_800371B4(u8 *, u8 *, s32, s16, s32);
    D_841911E8 = func_8410B330(arg0);
    BattleAnim_StepToS16((s16 *)(D_841911E8 + 0x92), 0x4000, 0x71C);
    func_800371B4(arg0 + 0xA8, arg0 + 0xB4,
        *(s32 *)(D_841911E8 + 0x74),
        *(s16 *)(D_841911E8 + 0x90),
        (s32)*(s16 *)(D_841911E8 + 0x92));
}
#endif

#ifdef VERSION_US
extern void func_8410AF1C(void);
extern u8 * func_8410B330(u8 *);
void BattleAnim_ModelDispatch_134(u8 *arg0, s32 arg1) {
    extern u8 *D_841911E8;
    extern u8 *D_841911E0;
    extern s32 D_841911EC;
    extern s32 D_84184148;
    extern u8 *func_8410B330(u8 *);
    extern void func_8410AF1C(void);

    D_841911E8 = func_8410B330(arg0);
    *(f32 *)(arg0 + 0x2C) = 30.0f;
    if (D_841911E8 == D_841911E0) {
        func_8410AF1C();
    }
    *(s32 *)((u8 *)D_841911E8 + (D_841911EC * 8) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410F92C.s")
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_162(u8 *arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_163(u8 *arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410F9FC.s")
#endif

#ifdef VERSION_US
extern void func_841203B4(u8 *, f32, f32);
extern void func_8410E73C();
void BattleAnim_ModelDispatch_170(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_841203B4(arg0 + 0x2C, 45.0f, 0.02f);
    func_8410E73C(arg0, arg1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410FB0C.s")
#endif

#ifdef VERSION_US
extern u8 *D_841911E8;
extern u8 *D_84193DD0;
extern s32 D_841911EC;
extern s32 D_84184148;
extern u8 *func_8410B330(u8 *);
extern void func_84120960(u8 *, s32);
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_800371B4(u8 *, u8 *, s32, s16, s32);
extern f32 D_84188F90;
extern f32 D_84188F94;
void BattleAnim_ModelDispatch_029(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    func_84120960(arg0, arg1);
    *(s16 *)((u8 *)D_841911E8 + 0x90) = 0x222;
    *(s16 *)((u8 *)D_841911E8 + 0x92) = 0;
    *(f32 *)((u8 *)D_841911E8 + 0x74) = 500.0f;
    if ((*(u16 *)((u8 *)D_84193DD0 + 0x12) & 2) || (*(u16 *)((u8 *)D_84193DD0 + 0x22) & 2)) {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 180.0f, 0.0f);
        *(s16 *)((u8 *)D_841911E8 + 0x90) = (s16)-0x888;
    } else {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 40.0f, 0.0f);
    }
    func_800371B4(arg0 + 0xB4, arg0 + 0xA8,
        *(s32 *)((u8 *)D_841911E8 + 0x74),
        *(s16 *)((u8 *)D_841911E8 + 0x90),
        (s32)*(s16 *)((u8 *)D_841911E8 + 0x92));
    *(s32 *)((u8 *)(D_841911E8 + (D_841911EC * 8)) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
extern void func_800371B4(u8 *, u8 *, s32, s16, s32);
void BattleAnim_ModelDispatch_030(u8 *arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = func_8410B330(arg0);
    D_841911E8 = temp_v0;
    (*(s16 *)((u8 *)(temp_v0) + (0x92))) = (s16) ((*(s16 *)((u8 *)(temp_v0) + (0x92))) + 0xE8);
    func_800371B4(arg0 + 0xB4, arg0 + 0xA8, (*(s32 *)((u8 *)(D_841911E8) + (0x74))), (*(s16 *)((u8 *)(D_841911E8) + (0x90))), (s32) (*(s16 *)((u8 *)(D_841911E8) + (0x92))));
    if ((f64) (*(f32 *)((u8 *)(arg0) + (0xAC))) <= 10.0) {
        (*(f32 *)((u8 *)(arg0) + (0xAC))) = 10.0f;
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_057(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    func_84120960(arg0, arg1);
    *(s16 *)((u8 *)D_841911E8 + 0x90) = 0x1C70;
    *(s16 *)((u8 *)D_841911E8 + 0x92) = 0;
    *(f32 *)((u8 *)D_841911E8 + 0x74) = D_84188F90;
    if ((*(u16 *)((u8 *)D_84193DD0 + 0x12) & 2) || (*(u16 *)((u8 *)D_84193DD0 + 0x22) & 2)) {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 180.0f, 0.0f);
    } else {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 40.0f, 0.0f);
    }
    func_800371B4(arg0 + 0xB4, arg0 + 0xA8,
        *(s32 *)((u8 *)D_841911E8 + 0x74),
        *(s16 *)((u8 *)D_841911E8 + 0x90),
        (s32)*(s16 *)((u8 *)D_841911E8 + 0x92));
    *(s32 *)((u8 *)(D_841911E8 + (D_841911EC * 8)) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_058(u8 *arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = func_8410B330(arg0);
    D_841911E8 = temp_v0;
    (*(s16 *)((u8 *)(temp_v0) + (0x92))) = (s16) ((*(s16 *)((u8 *)(temp_v0) + (0x92))) + 0xE8);
    func_800371B4(arg0 + 0xB4, arg0 + 0xA8, (*(s32 *)((u8 *)(D_841911E8) + (0x74))), (*(s16 *)((u8 *)(D_841911E8) + (0x90))), (s32) (*(s16 *)((u8 *)(D_841911E8) + (0x92))));
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_064(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    func_84120960(arg0, arg1);
    *(s16 *)((u8 *)D_841911E8 + 0x90) = 0x9F4;
    *(s16 *)((u8 *)D_841911E8 + 0x92) = 0;
    *(f32 *)((u8 *)D_841911E8 + 0x74) = D_84188F94;
    if ((*(u16 *)((u8 *)D_84193DD0 + 0x12) & 2) || (*(u16 *)((u8 *)D_84193DD0 + 0x22) & 2)) {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 180.0f, 0.0f);
        *(s16 *)((u8 *)D_841911E8 + 0x90) = (s16)-0x9F4;
    } else {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 40.0f, 0.0f);
    }
    func_800371B4(arg0 + 0xB4, arg0 + 0xA8,
        *(s32 *)((u8 *)D_841911E8 + 0x74),
        *(s16 *)((u8 *)D_841911E8 + 0x90),
        (s32)*(s16 *)((u8 *)D_841911E8 + 0x92));
    *(s32 *)((u8 *)(D_841911E8 + (D_841911EC * 8)) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
extern f64 D_84188F98;
void BattleAnim_ModelDispatch_065(u8 *arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = func_8410B330(arg0);
    D_841911E8 = temp_v0;
    (*(s16 *)((u8 *)(temp_v0) + (0x92))) = (s16) ((*(s16 *)((u8 *)(temp_v0) + (0x92))) + 0xE8);
    func_800371B4(arg0 + 0xB4, arg0 + 0xA8, (*(s32 *)((u8 *)(D_841911E8) + (0x74))), (*(s16 *)((u8 *)(D_841911E8) + (0x90))), (s32) (*(s16 *)((u8 *)(D_841911E8) + (0x92))));
    (*(f32 *)((u8 *)(arg0) + (0xB0))) = (f32) ((f64) (*(f32 *)((u8 *)(arg0) + (0xB0))) * D_84188F98);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84110118.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84110264.s")
#endif

#ifdef VERSION_US
extern void func_8410CC90(u8 *, s32, s16);
extern void func_84120BB4(u8 *, s32);
void BattleAnim_ModelDispatch_190(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120BB4(arg0, arg1);
    func_8410CC90(arg0, arg1, (*(s16 *)((u8 *)(D_841911E8) + (0x98))));
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif

#ifdef VERSION_US
extern void func_8410C934(u8 *, s32, s16);
void BattleAnim_ModelDispatch_001(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120BB4(arg0, arg1);
    func_8410C934(arg0, arg1, (*(s16 *)((u8 *)(D_841911E8) + (0x98))));
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif

#ifdef VERSION_US
extern void func_8410CAE4(u8 *, s32, s16);
extern void func_84120C20(u8 *, s32);
void BattleAnim_ModelDispatch_078(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120C20(arg0, arg1);
    func_8410CAE4(arg0, arg1, (*(s16 *)((u8 *)(D_841911E8) + (0x98))));
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif

#ifdef VERSION_US
extern void func_8410ED98(u8 *, s32, s32);
extern void func_84120E14(s32);
void BattleAnim_ModelDispatch_099(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120E14(arg1);
    func_8410ED98(arg0, arg1, 0);
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif

#ifdef VERSION_US
extern void func_84120960(u8 *, s32);
void BattleAnim_ModelDispatch_085(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120960(arg0, arg1);
    func_8410C934(arg0, arg1, (*(s16 *)((u8 *)(D_841911E8) + (0x98))));
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif

#ifdef VERSION_US
extern void func_8410CD3C(u8 *, s32, s16);
extern void func_84120A50(u8 *, s32);
void BattleAnim_ModelDispatch_106(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120A50(arg0, arg1);
    func_8410CD3C(arg0, arg1, (*(s16 *)((u8 *)(D_841911E8) + (0x98))));
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif

#ifdef VERSION_US
extern void func_84120CA4(u8 *, s32);
void BattleAnim_ModelDispatch_036(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120CA4(arg0, arg1);
    func_8410CC90(arg0, arg1, (*(s16 *)((u8 *)(D_841911E8) + (0x98))));
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif

#ifdef VERSION_US
extern void func_84120D34(u8 *, s32);
void BattleAnim_ModelDispatch_043(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120D34(arg0, arg1);
    func_8410CC90(arg0, arg1, (*(s16 *)((u8 *)(D_841911E8) + (0x98))));
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif

#ifdef VERSION_US
extern u8 *func_8410B330(u8 *);
extern void func_8410B420(u8 *, void *, s16);
extern void func_8410EA58(u8 *, void *, s16);
extern u8 *D_841911E8;
extern s32 D_841911EC;
extern s32 D_84184148;
void BattleAnim_ModelDispatch_218(u8 *arg0, void *arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_8410B420(arg0, arg1, *(s16 *)(D_841911E8 + 0x98));
    *(s32 *)(D_841911E8 + (D_841911EC * 8) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84110718.s")
#endif

#ifdef VERSION_US
extern void func_8410B60C(u8 *, void *, u8 *, u8 *);
extern void func_8410B884(u8 *, void *, u8 *, s16);
extern void func_8410D174(u8 *, void *);
extern u8 *func_8410B330(u8 *);
extern u8 *D_841911E8;

void BattleAnim_ModelDispatch_079(u8 *arg0, void *arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_841203B4(arg0 + 0x2C, *(f32 *)(D_841911E8 + 0x88), 0.05f);
    func_8410D174(arg0, arg1);
    func_8410B884(arg0, arg1, D_841911E8, *(s16 *)((u8 *)arg1 + 0x20));
    func_8410B60C(arg0, arg1, D_841911E8, arg0 + 0xB4);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84110860.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84110910.s")
#endif

#ifdef VERSION_US
extern u8 * func_8410B330(u8 *);
extern void func_8410DFC4(u8 *, void *);
extern void func_8410E688(u8 *arg0, void *arg1);
extern s32 func_8411DC80(u16, s32 *, s32);
void BattleAnim_ModelDispatch_093(u8 *arg0, void *arg1) {
    extern u8 *D_841911E8;
    extern s32 func_8411DC80(u16, s32 *, s32);
    extern void func_8410DFC4(u8 *, void *);
    extern void func_8410E688(u8 *, void *);
    extern u8 D_8418393C;

    D_841911E8 = func_8410B330(arg0);
    func_841203B4(arg0 + 0x2C, *(f32 *)(D_841911E8 + 0x88), 0.05f);
    if (func_8411DC80(*(u8 *)((u8 *)arg1 + 0x61F),
            (s32 *)&D_8418393C, 8) == 0) {
        func_8410DFC4(arg0, arg1);
        func_8410E688(arg0, arg1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841109FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84110A98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84110B2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84110C6C.s")
#endif

#ifdef VERSION_US
extern u8 D_84183960[];
extern void func_84110B2C(u8 *, s32);
extern void func_8410DFC4(u8 *, void *);
extern void func_8410E688(u8 *arg0, void *arg1);
extern void func_8410E7D0(u8 *arg0, void *arg1);
extern s32 func_8411DC80(u16, s32 *, s32);
void BattleAnim_ModelDispatch_009(u8 *arg0, s32 arg1) {
    s32 index;

    index = func_8411E1F8(arg1);
    if (((*(u16 *)((u8 *)(D_84193DD0) + (index << 4) + 0x12)) & 2) == 0) {
        func_8410DFC4(arg0, (void *)arg1);
    }
    if (func_8411DC80(*(u16 *)((u8 *)(D_841911E8) + 0x98),
            (s32 *)&D_84183960, 0x10) != 0) {
        func_8410E688(arg0, (void *)arg1);
    } else {
        func_8410E7D0(arg0, (void *)arg1);
    }
    func_84110B2C(arg0, arg1);
}
#endif

#ifdef VERSION_US
extern void func_84108940(u8 *, s32);
void BattleAnim_ModelDispatch_176(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84108940(arg0 + 0xB4, 0);
}
#endif

#ifdef VERSION_US
extern void func_8411EFE4(s32);
void BattleAnim_ModelDispatch_022(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120BB4(arg0, arg1);
    func_8411EFE4(arg1);
    func_8410C934(arg0, arg1, (*(s16 *)((u8 *)(D_841911E8) + (0x98))));
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif

#ifdef VERSION_US
extern void func_8410CF80(void);
void BattleAnim_ModelDispatch_023(u8 *arg0) {
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    func_8410CF80();
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_015(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_84120BB4(arg0, arg1);
    func_8410C934(arg0, arg1, (*(s16 *)((u8 *)(D_841911E8) + (0x98))));
    func_8411EFE4(arg1);
    func_8411EF08((u8 *) arg1);
    (*(s32 *)((u8 *)((D_841911E8 + (D_841911EC * 8))) + (8))) = (s32) D_84184148;
}
#endif

#ifdef VERSION_US
extern void func_8410D088(u8 *, s32);
extern void func_8410E878(u8 *, s32);
void BattleAnim_ModelDispatch_016(u8 *arg0, s32 arg1) {
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    func_8410D088(arg0, arg1);
    func_8410E878(arg0, arg1);
}
#endif

#ifdef VERSION_US
extern void func_8410E73C(u8 *, void *);
void BattleAnim_ModelDispatch_044(u8 *arg0, void *arg1) {
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    func_8410E73C(arg0, arg1);
}
#endif

#ifdef VERSION_US
extern u8 *func_8410B330(u8 *);
extern void func_8410B420(u8 *, void *, s16);
extern void func_8410EA58(u8 *, void *, s16);
extern u8 *D_841911E8;
extern s32 D_841911EC;
extern s32 D_84184148;
void BattleAnim_ModelDispatch_071(u8 *arg0, void *arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_8410EA58(arg0, arg1, *(s16 *)(D_841911E8 + 0x98));
    *(s32 *)(D_841911E8 + (D_841911EC * 8) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
void func_8411123C(u8 *arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111248.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841112C8.s")
#endif

#ifdef VERSION_US
extern u8 D_8418414C;
void func_84111348(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = (arg1 * 0x1C) + &D_8418414C;
    (*(s32 *)((u8 *)(D_841911E0) + (8))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x10))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (4)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x18))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (8)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x20))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0xC)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x28))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x10)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x30))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x14)));
    (*(s32 *)((u8 *)(D_841911E0) + (0x38))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x18)));
    (*(s32 *)((u8 *)(D_841911E0) + (4))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0xC))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0x14))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0x1C))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0x24))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0x2C))) = arg0;
    (*(s32 *)((u8 *)(D_841911E0) + (0x34))) = arg0;
}
#endif

#ifdef VERSION_US
void func_841113F8(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = (arg1 * 0x1C) + &D_8418414C;
    (*(s32 *)((u8 *)(D_841911E4) + (8))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x10))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (4)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x18))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (8)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x20))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0xC)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x28))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x10)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x30))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x14)));
    (*(s32 *)((u8 *)(D_841911E4) + (0x38))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x18)));
    (*(s32 *)((u8 *)(D_841911E4) + (4))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0xC))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0x14))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0x1C))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0x24))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0x2C))) = arg0;
    (*(s32 *)((u8 *)(D_841911E4) + (0x34))) = arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841114A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111774.s")
#endif

#ifdef VERSION_US
extern void func_8410B2DC(u8 *arg0, u8 *arg1);
s32 func_84111868(s32 arg0, u8 *arg1, u8 *arg2) {
    extern void func_8410B27C(u8 *, u8 *);
    extern void func_84111774(u8 *, u8 *);

    switch (arg0) {
    case 0:
        func_8410B27C(arg1, arg2);
        break;
    case 1:
    case 2:
        func_84111774(arg1, arg2);
        break;
    case 3:
        func_8410B2DC(arg1, arg2);
        break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841118E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841119CC.s")
#endif

#ifdef VERSION_US
extern void func_841206D0(u8 *);
void func_84111BEC(u8 *arg0) {
    *(u16 *)(arg0 + 0x7E8) = 0;
    func_8411FEE8(0);
    func_841206D0(arg0);
}
#endif

#ifdef VERSION_US
extern void func_841089D8(s32);
void func_84111C1C(void) {
    func_841089D8(1);
}
void func_84111C1C_padding(void) {}
#endif

#ifdef VERSION_US
extern s32 func_800238C4(void);
void func_84111C44(void) {
    (void)func_841089D8(1);
    (void)func_800238C4();
}
#endif

#ifdef VERSION_US
void func_84111C6C(void) { func_841089D8(0); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111C8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111CF8.s")
#endif

#ifdef VERSION_US
void func_84111D64(u8 *arg0, s32 arg1) {
    extern void func_8003F2C4(s32, s32, s32);
    extern s32 D_84190518;
    if (*(s16 *)(arg0 + 0x658) == 0xFC) {
        func_8003F2C4(D_84190518, (s32)arg0, arg1);
    } else {
        func_8003F2C4(*(s32 *)(arg0 + 0x5C0), (s32)arg0, arg1);
    }
}
#endif

#ifdef VERSION_US
extern void func_80024974(s32, s16, s16, s32, s32);
void func_84111DB4(u8 *arg0, s32 arg1) {
    if ((*(f32 *)((u8 *)(arg0) + (0x28))) == 0.0f) {
        func_80024974(func_8411E1F8((s32) arg0) & 0xFF, (*(s16 *)((u8 *)(arg0) + (0x1A))), (*(s16 *)((u8 *)(arg0) + (0x40))), 0, arg1);
    } else {
        func_80024974(func_8411E1F8((s32) arg0) & 0xFF, (*(s16 *)((u8 *)(arg0) + (0x1A))), (*(s16 *)((u8 *)(arg0) + (0x40))), 1, arg1);
    }
    ModelAnim_SetFrame(arg0, (s16) arg1);
}
#endif

#ifdef VERSION_US
extern void func_8003F3BC();
void func_84111E50(arg0)
u8 *arg0;
{
    if ((*(u16 *)(arg0 + 0x56) & 1) == 0) {
        func_8003F3BC();
    }
}
#endif

#ifdef VERSION_US
extern void ModelAnim_SetEventFrame(void *, s16);
s32 func_84111CF8();

void func_84111E80(void *arg0, s16 arg1) {
    if (!((*(u16 *)((u8 *)(arg0) + (0x56))) & 1) && (func_84111CF8() == 0)) {
        ModelAnim_SetEventFrame(arg0, arg1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84111EC4.s")
#endif

#ifdef VERSION_US
s32 ModelAnim_IsEventTrackDone();
s32 func_84111FA4(void *arg0) {
    if ((*(s32 *)((u8 *)(arg0) + (0x58))) == 0) {
        return 1;
    }
    if (ModelAnim_IsEventTrackDone() != 0) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 func_8003EF60(void);
void func_84111FEC(void) {
    (void)func_8003EF60();
}
#endif

#ifdef VERSION_US
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
void func_8411200C(u8 *arg0) {
    s16 temp = *(s16 *)(arg0 + 0x1A);
    if (temp == 0x64) {
        func_84111D64(arg0, 7);
    } else if (temp == 0x6E) {
        func_84111D64(arg0, 7);
    } else if (temp == 0xA9) {
        func_84111D64(arg0, 7);
    } else {
        func_84111D64(arg0, *(u8 *)((u8 *)(u32)*(u32 *)(arg0 + 0x2D4) + 0x13D8));
    }
    func_84111DB4(arg0, 0);
}
#endif

#ifdef VERSION_US
void func_841120A4(u8 *arg0) {}
#endif

#ifdef VERSION_US
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
void func_841120AC(u8 *arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    temp_v0 = arg1 * 0x14;
    func_84111D64(arg0, *(u8 *)(*(u8 **)(arg0 + 0x2D4) + temp_v0));
    func_84111E50(arg0, *(s8 *)(*(u8 **)(arg0 + 0x2D4) + temp_v0 + 1));
    func_84111DB4(arg0, (*(u16 *)(*(u8 **)(arg0 + 0x44) + 0xA) *
        ((arg2 / *(u16 *)(*(u8 **)(arg0 + 0x44) + 0xA)) + 1)) - arg2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112158.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841121CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112218.s")
#endif

#ifdef VERSION_US
void func_84112290(u8 *arg0) {
    func_8003EF70(arg0);
    *(u8 *)(arg0 + 2) = *(u8 *)(arg0 + 2) | 0x20;
    func_8003F3BC(arg0, -1);
    ModelAnim_SetEventFrame(arg0, 0);
}
#endif

#ifdef VERSION_US
extern s32 func_84111C8C(void);
extern void func_84112158(s32, s32);
void func_841122D4(u8 *arg0) { if (func_84111C8C() != 0) { func_84112158(arg0, 0x105); } else { *(u16 *)(arg0 + 0x7F4) |= 1; func_84111E50(arg0, *(u8 *)(*(u8 **)(arg0 + 0x2D4) + 0x1465)); } }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112324.s")
#endif

#ifdef VERSION_US
extern void func_84111DB4(u8 *arg0, s32 arg1);
s32 func_84112418(u8 *arg0) { if (func_84111C8C()) { if (ModelAnim_IsFinished(arg0) != 0) { func_84111DB4(arg0, 0); } return 0; } return 0; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112464.s")
#endif

#ifdef VERSION_US
void func_84112564(s32 arg0) {
    D_84193DD0[1] |= 1;
}
#endif

#ifdef VERSION_US
void func_84112580(s32 arg0) {
    D_84193DD0[1] |= 4;
}
#endif

void func_8411259C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841125A4.s")
#endif

#ifdef VERSION_US
extern u8 D_84183D54;
void func_841125F4(void *arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = (arg1 * 0x1C) + &D_84183D54;
    (*(s32 *)((u8 *)(arg0) + (0x5C8))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0)));
    (*(s32 *)((u8 *)(arg0) + (0x5CC))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (4)));
    (*(s32 *)((u8 *)(arg0) + (0x5D0))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (8)));
    (*(s32 *)((u8 *)(arg0) + (0x5D4))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0xC)));
    (*(s32 *)((u8 *)(arg0) + (0x5D8))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x10)));
    (*(s32 *)((u8 *)(arg0) + (0x5DC))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x14)));
    (*(s32 *)((u8 *)(arg0) + (0x5E0))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0x18)));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112648.s")
#endif

#ifdef VERSION_US
extern s32 func_8411E164();
extern void func_841125A4(s32);
extern void func_84112158(s32, s32);
void func_841126C8(s32 arg0) {
    func_841125A4(func_8411E164());
    func_84112158(func_8411E164(arg0), 0xFB);
}
#endif

#ifdef VERSION_US
void func_84112704(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0x664)));
    (*(f32 *)((u8 *)(arg0) + (0x644))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x20)));
    (*(f32 *)((u8 *)(arg0) + (0x640))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x1C)));
    (*(f32 *)((u8 *)(arg0) + (0x654))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0xC)));
    (*(f32 *)((u8 *)(arg0) + (0x64C))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (4)));
    (*(f32 *)((u8 *)(arg0) + (0x650))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (8)));
    (*(f32 *)((u8 *)(arg0) + (0x654))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0xC)));
    (*(f32 *)((u8 *)(arg0) + (0x634))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x10)));
    (*(f32 *)((u8 *)(arg0) + (0x638))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x14)));
    (*(f32 *)((u8 *)(arg0) + (0x63C))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x18)));
    (*(f32 *)((u8 *)(arg0) + (0x648))) = (f32) (*(f32 *)((u8 *)(temp_v0) + (0x14)));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411275C.s")
#endif

#ifdef VERSION_US
extern void func_8411275C(void);
void func_8411281C(void) {
    func_8411275C();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411283C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411293C.s")
#endif

#ifdef VERSION_US
void func_841129E8(u8 *arg0, s16 arg1, s32 arg2) {
    extern void func_8003F114(u8 *, s32, s16, s32);
    extern void func_8003F9AC(u8 *, s16, u16);
    s32 index;

    func_8003F114(arg0, 0, arg1, arg2);
    index = func_8411E1F8((s32)arg0);
    func_8003F9AC(arg0, arg1,
        *(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x14));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112A40.s")
#endif

#ifdef VERSION_US
void func_84112B44(void) {
    func_8411275C();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112B64.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112C98.s")
#endif

#ifdef VERSION_US
extern void func_84112B64(s32);
extern s32 D_84191208;
extern s32 D_8419120C;
extern void func_84112C98();
void func_84112DB8(void) {
    if ((*(u16 *)((u8 *)(D_84193DD0) + (0x12))) & 1) {
        func_84112B64(D_84191208);
    } else {
        func_84112C98(D_84191208);
    }
    if ((*(u16 *)((u8 *)(D_84193DD0) + (0x22))) & 1) {
        func_84112B64(D_8419120C);
        return;
    }
    func_84112C98(D_8419120C);
}
#endif

#ifdef VERSION_US
extern void func_84112C98();
void func_84112E40(s32 arg0) {
    extern s32 func_8411F750(u8);
    s32 index;

    index = func_8411F750(*(u8 *)(u32)D_84193DD0);
    index = func_8411E1F8(index);
    if ((*(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x12) & 1) != 0) {
        func_84112B64(arg0);
        return;
    }
    func_84112C98(arg0);
}
#endif

#ifdef VERSION_US

void func_84112EAC(void *arg0) {
    if ((*(s16 *)((u8 *)(arg0) + (0x1A))) == 0xFC) {
        func_84112C98();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84112EDC.s")
#endif

#ifdef VERSION_US
typedef union {
    s32 word;
    s8 bytes[4];
} F12State;
extern s32 func_80041FD0(u8 *, u16, F12State, s32);
void func_84112FD0(u8 *arg0, u16 arg1, F12State arg2, s32 arg3) {
    func_80041FD0(arg0, arg1, arg2, arg3);
}
#endif

#ifdef VERSION_US
void func_84112FFC(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x678) = arg1;
}
#endif

#ifdef VERSION_US
void func_84113004(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x664) = arg1;
}
#endif

#ifdef VERSION_US
void func_8411300C(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x668) = arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113014.s")
#endif

#ifdef VERSION_US
s32 func_841133EC(s32 arg0) {
    extern u8 D_84193DDC;
    return D_84193DDC & 0xD0;
}
#endif

#ifdef VERSION_US
extern u8 D_84193DD8[];
extern u8 D_84193DDC;
extern s32 func_8003F904(u8 *);
s32 func_84113400(s32 arg0) {
    func_8003F904(D_84193DD8);
    return D_84193DDC & 0xC0;
}
#endif

#ifdef VERSION_US
extern void func_8410373C(u8 *);

s32 func_84113430(s32 arg0) {
    if (func_84113400(arg0) == 0) {
        func_8410373C(D_84193DD8);
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern void func_84103640(u8 *, s32);
void func_8411346C(s32 arg0) {
    func_8411FEE8(0xFFFF);
    func_84103640(D_84193DD8, 0);
}
#endif

#ifdef VERSION_US
extern void func_84103694(u8 *, u8);
void func_841134A0(u8 *arg0) {
    func_8411FEE8(0xFFFF);
    func_84103694(D_84193DD8, arg0[0x618]);
}
#endif

#ifdef VERSION_US
extern s32 func_80062D20(u8);
void func_841134D8(u8 *arg0) {
    func_8411FEE8(0xFFFF);
    if (arg0[0x618] != 0xF8) {
        if (func_80062D20(D_84193DD0[8]) != 0x4D &&
            func_80062D20(D_84193DD0[8]) != 0x1D) {
            return;
        }
    }
    func_84111C44();
    func_84103694(D_84193DD8, arg0[0x618]);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113560.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113590.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113658.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841136E8.s")
#endif

#ifdef VERSION_US
void func_841137F0(u8 *arg0) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841137F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411388C.s")
#endif

#ifdef VERSION_US
extern void func_84112218(u8 *, s32, s32);
void func_84113920(u8 *arg0) {
    s32 index;

    index = func_8411E1F8((s32)arg0);
    if (((*(u16 *)((u8 *)(D_84193DD0) + (index << 4) + 0x12)) & 4) != 0) {
        if (*(s16 *)(arg0 + 0x1A) == 0x32) {
            func_84112218(arg0, 0x102, 0x28);
            return;
        }
    }
    index = func_8411E1F8((s32)arg0);
    if (((*(u16 *)((u8 *)(D_84193DD0) + (index << 4) + 0x12)) & 4) != 0) {
        if (*(s16 *)(arg0 + 0x1A) == 0x33) {
            func_84112218(arg0, 0x102, 0x30);
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841139D0.s")
#endif

#ifdef VERSION_US
extern s32 func_841139D0(u8 *);
extern void func_841136E8(u8 *);
extern s32 D_841911F4;
extern s32 D_84183D50;
void BattleAnim_Dispatch_001(u8 *arg0) {
    if ((func_841139D0(arg0) == 0) && ((*(s16 *)((u8 *)(arg0) + (0x40))) != 0)) {
        func_84112158((s32) arg0, 0xFB);
    }
    func_841136E8(arg0);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern f32 D_84188FEC;
extern void func_84112158(s32, s32);
extern void func_841136E8(u8 *);
void BattleAnim_Dispatch_190(u8 *arg0) {
    s32 index;

    if ((func_841139D0(arg0) == 0) && (*(s16 *)(arg0 + 0x40) != 0)) {
        func_84112158((s32)arg0, 0xFB);
    }
    func_841136E8(arg0);
    index = func_8411E1F8((s32)arg0);
    if ((*(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x12) & 8) != 0) {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0x30),
            D_84188FEC, D_84188FEC, D_84188FEC);
    }
    *(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + 0x5C8) = (s32)D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_841137F8(u8 *);
void BattleAnim_Dispatch_002(u8 *arg0) {
    if (func_841139D0(arg0) == 0) {
        func_841137F8(arg0);
    }
}
#endif

#ifdef VERSION_US
void func_84113D38(u8 *arg0) {
    if ((func_841139D0(arg0) == 0) && ((*(s16 *)((u8 *)(arg0) + (0x40))) != 0)) {
        func_84112158((s32) arg0, 0xFB);
    }
    func_841136E8(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113D7C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84113E7C.s")
#endif

#ifdef VERSION_US
void func_84114600(void *arg0) {
    extern void func_84108728(u8, void *, s32);
    extern void func_800231A0(u8, s16, s32, ...);
    s32 result;

    result = func_8411E164(arg0);
    func_84108728(*(u8 *)((u8 *)arg0 + 0x618), arg0, result);
    if ((D_84193DD0[9] & 7) == 1) {
        func_800231A0(*(u8 *)((u8 *)arg0 + 0x618),
            *(s16 *)((u8 *)arg0 + 0x658), 2, arg0);
        return;
    }
    func_800231A0(*(u8 *)((u8 *)arg0 + 0x618),
        *(s16 *)((u8 *)arg0 + 0x658), 0, arg0);
}
#endif

#ifdef VERSION_US
extern void func_800231A0(u8, s16, s32, ...);
void func_84114678(void *arg0) {
    if (((*(u8 *)((u8 *)(D_84193DD0) + (9))) & 7) == 1) {
        func_800231A0((*(u8 *)((u8 *)(arg0) + (0x618))), (*(s16 *)((u8 *)(arg0) + (0x658))), 2, arg0);
        return;
    }
    func_800231A0((*(u8 *)((u8 *)(arg0) + (0x618))), (*(s16 *)((u8 *)(arg0) + (0x658))), 0, arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841146D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84114804.s")
#endif

#ifdef VERSION_US
f32 func_8410EB50();
void BattleAnim_Dispatch_015(u8 *arg0) {
    (*(u8 *)((u8 *)(arg0) + (0x618))) = (u8) (*(u8 *)((u8 *)(D_84193DD0) + (8)));
    func_84111C44();
    func_841134A0(arg0);
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 5;
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84114A04.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84114BF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841153DC.s")
#endif

#ifdef VERSION_US
extern void func_84114BF4(s32);
extern void func_841153DC(s32);
void BattleAnim_Dispatch_017(s32 arg0) {
    if ((func_841133EC(arg0) == 0) && ((*(s8 *)((u8 *)(arg0) + (0x7F6))) == 0)) {
        if ((*(u8 *)((u8 *)(arg0) + (0x618))) == 0x9C) {
            func_841153DC(arg0);
            return;
        }
        func_84114BF4(arg0);
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_043(u8 *arg0) {
    (*(s8 *)((u8 *)(arg0) + (0x618))) = 0x13;
    func_84111C44();
    func_841134A0(arg0);
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 5;
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_841146D4(u8 *, s32);
void func_841155B0(u8 *arg0) {
    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        arg0[0x61F] = 3;
        func_841146D4(arg0, 0x100);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841155E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841156D0.s")
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84112158(s32, s32);
extern void func_8411FEE8(s32);
void func_841157D8(s32 arg0) {
    s16 var_v0;

    var_v0 = *(s16 *)((u8 *)(u32)arg0 + 0x7E8);
    if (var_v0 == 1) {
        *(s16 *)(D_841911E0 + 0x98) = 8;
        func_84111348(arg0, 0xF);
        var_v0 = *(s16 *)((u8 *)(u32)arg0 + 0x7E8);
    }
    if (var_v0 == 0x1E) {
        func_8411FEE8(0);
    }
    if (ModelAnim_IsFinished(arg0) != 0) {
        func_84112158(arg0, 0x106);
    }
}
#endif

#ifdef VERSION_US
extern void func_841156D0(s32);
extern void func_841157D8(s32);
void BattleAnim_Dispatch_045(s32 arg0) {
    s8 temp_v0;

    if (func_841133EC(arg0) == 0) {
        if ((*(u8 *)((u8 *)(arg0) + (0x618))) == 0x13) {
            func_841139D0(func_8411E164(arg0));
        }
        temp_v0 = (*(s8 *)((u8 *)(arg0) + (0x7F6)));
        switch (temp_v0) {                          /* irregular */
        case 0:
            func_841156D0(arg0);
            return;
        case 1:
            func_841157D8(arg0);
            break;
        }
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_050(u8 *arg0) {
    (*(s8 *)((u8 *)(arg0) + (0x618))) = 0x5B;
    func_84111C44();
    func_841134A0(arg0);
    func_8411FEE8(0x258);
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 5;
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
void func_84115940(u8 *arg0) {
    if (!((*(u16 *)((u8 *)(arg0) + (0x7EC))) & 1)) {
        (*(s16 *)((u8 *)(D_841911E0) + (0x98))) = 0x10;
        (*(s8 *)((u8 *)(arg0) + (0x61F))) = 5;
        func_841146D4(arg0, 0x102);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84115988.s")
#endif

#ifdef VERSION_US
void func_84115A24(void *arg0)
{
  if (ModelAnim_IsFinished() != 0)
  {
    *((u8 *) (((u8 *) arg0) + 2)) = (u8) ((*((u8 *) (((u8 *) arg0) + 2))) & 0xFFFD);
    *((s8 *) (((u8 *) arg0) + 0x7F6)) = 3;
    *((s16 *) (((u8 *) arg0) + 0x7E8)) = 0;
  }
  if (arg0)
  {
  }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84115A64.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84115B34.s")
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_106(u8 *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 5;
    (*(s8 *)((u8 *)(arg0) + (0x618))) = 0x5B;
    func_84111C44();
    func_841134A0(arg0);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84115D4C.s")
#endif

#ifdef VERSION_US
extern void func_84108A10(u8 *);
void func_84115D98(u8 *arg0) {
    s16 temp_v0;

    temp_v0 = (*(s16 *)((u8 *)(arg0) + (0x1A)));
    if ((temp_v0 == 0x32) || (temp_v0 == 0x33)) {
        if (ModelAnim_IsFinished(arg0) != 0) {
            func_84108A10(arg0);
            func_84111BEC(arg0);
            (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        }
    } else if ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 0x19) {
        func_84108A10(arg0);
        func_84111BEC(arg0);
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84115E28.s")
#endif

#ifdef VERSION_US
extern void func_800231A0(u8, s16, s32, ...);
extern void func_84108728(u8, void *, s32);
extern void func_84115D98(u8 *arg0);
void BattleAnim_Dispatch_108(u8 *arg0) {
    s32 result;
    if (func_841133EC((s32)arg0) != 0) return;
    if (*(s8 *)(arg0 + 0x7F6) != 0) return;
    if (*(s16 *)(arg0 + 0x7E8) == 2) {
        if ((*(s16 *)(arg0 + 0x1A) != 0x32) && (*(s16 *)(arg0 + 0x1A) != 0x33)) {
            result = func_8411E164((s32)arg0);
            func_84108728(*(u8 *)(arg0 + 0x618), arg0, result);
        }
        func_800231A0(*(u8 *)(arg0 + 0x618), *(s16 *)(arg0 + 0x658), 0);
        func_84112564((s32)arg0);
        *(u16 *)(arg0 + 0x7F4) &= 0xFFEF;
    }
    func_84115D98(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84115FAC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116010.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116138.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116248.s")
#endif

#ifdef VERSION_US
extern void func_84112158(s32, s32);
void BattleAnim_Dispatch_059(s32 arg0) {
    extern void func_84116248(s32);

    if (func_841133EC(arg0) == 0) {
        s8 temp_v0 = *(s8 *)((u8 *)arg0 + 0x7F6);
        switch (temp_v0) {
        case 0:
            func_84116248(arg0);
            return;
        case 1:
            if (ModelAnim_IsFinished(arg0) != 0) {
                func_84112158(arg0, 0xFB);
            }
            break;
        }
    }
}
#endif

#ifdef VERSION_US
void func_84116410(u8 *arg0) {
    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        s32 index = arg0[0x618] - 1;
        arg0[0x616] = *(u8 *)(*(u8 **)(arg0 + 0x2D4) + (index * 0x14));
        func_841146D4(arg0, index);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116460.s")
#endif

#ifdef VERSION_US
extern u8 D_841849B6[];
extern void func_841119CC(u8 *, u16);
extern s32 func_800427B8(s32);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84111C44(void);
extern void func_841126C8(s32 arg0);
extern void func_84112EDC(u8 *);
void BattleAnim_Dispatch_156(u8 *arg0) {
    func_841139D0(func_8411E164((s32)arg0));
    if (func_800427B8(*(s32 *)(arg0 + 0x5C0)) != 0) {
        func_841126C8((s32)arg0);
        func_84111C44();
        func_84112EAC(arg0);
        func_84112EDC(arg0);
        func_84116410(arg0);
        *(u8 *)(arg0 + 0x7F6) = 1;
        *(s16 *)(arg0 + 0x7E8) = 0;
        func_841119CC(D_841911E0,
            *(u16 *)((u8 *)D_841849B6 + (*(u8 *)(arg0 + 0x618) << 3)));
        func_84111348((s32)arg0, 0);
        *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116604.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841166C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116808.s")
#endif

#ifdef VERSION_US
extern u32 func_8003570C(void);
void func_841168A0(u8 *arg0) {
    extern u8 D_84183BDC;
    extern u32 func_8003570C(void);
    s32 sp1C;

    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        sp1C = *(u8 *)(arg0 + 0x618) - 1;
        *(u16 *)(D_841911E0 + 0x98) =
            *(u16 *)((u8 *)&D_84183BDC +
                ((func_8003570C() % 6) * 2));
        *(u8 *)(arg0 + 0x61F) = 0xFF;
        func_841146D4(arg0, sp1C);
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_113(u8 *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 5;
    (*(s8 *)((u8 *)(arg0) + (0x618))) = 1;
    func_841136E8(arg0);
    func_84111C44();
    func_841134A0(arg0);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84111D64(u8 *, s32);
extern void func_84111DB4(u8 *arg0, s32 arg1);
extern void func_84111E80(void *arg0, s16 arg1);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
extern void func_841168A0(u8 *arg0);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_114(u8 *arg0) {
    if (func_84113430((s32)arg0) != 0) {
        func_84112EAC(arg0);
        *(u8 *)(arg0 + 0x7F6) = 0;
        func_841168A0(arg0);
        func_841126C8((s32)arg0);
        func_84111348((s32)arg0, 0);
        func_84111E50(arg0, *(s8 *)(arg0 + 0x617));
        func_84111D64(arg0, *(s8 *)(arg0 + 0x616));
        func_84111E80(arg0, 0);
        func_84111DB4(arg0, *(u8 *)(arg0 + 0x61B));
        *(s16 *)(arg0 + 0x7E8) = *(u8 *)(arg0 + 0x61B);
        func_8411FEE8(0x258);
        func_84112564((s32)arg0);
        *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116A3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116AC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116B40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116BC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116EB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84116F7C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841170A0.s")
#endif

#ifdef VERSION_US
void func_841175D4(s32 arg0) {
    extern f32 func_8413D358(s32);
    extern u8 D_841911F8;
    s32 temp_v0;

    if ((func_8413D358(func_8411E1F8(arg0) & 0xFF) == 0.0f) &&
        (D_841911F8 == 0)) {
        temp_v0 = *(s16 *)((u8 *)(u32)arg0 + 0x7E8) + 0x32;
        if (temp_v0 < (s32)*(u8 *)((u8 *)(u32)arg0 + 0x61A)) {
            *(u8 *)((u8 *)(u32)arg0 + 0x61A) = (u8)temp_v0;
        }
        D_841911F8 = 1;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117648.s")
#endif

#ifdef VERSION_US
extern void func_80023A3C(s32, s32, s32);
extern void func_8410890C(s32, s32);
void func_841176E0(void *arg0) {
    if (((*(s16 *)((u8 *)(arg0) + (0x7E8))) == (*(u8 *)((u8 *)(arg0) + (0x619)))) && ((*(u8 *)((u8 *)(D_84193DD0) + (9))) & 0x10)) {
        func_80023A3C(0x10, 0, 0);
        func_8410890C(0xFD, (s32) arg0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117744.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117880.s")
#endif

#ifdef VERSION_US
void func_84117948(s32 arg0) {
    s32 temp_v0;

    if ((*(u16 *)((u8 *)(D_84193DD0) + (4))) == 0xE) {
        func_84112158(arg0, 0xFE);
        return;
    }
    temp_v0 = (*(u8 *)((u8 *)(D_84193DD0) + (9))) & 7;
    if ((temp_v0 != 6) && ((*(u8 *)((u8 *)(arg0) + (0x618))) != 0xD4) && (temp_v0 != 2) && (temp_v0 != 5)) {
        func_84112158(arg0, 0xFE);
    }
}
#endif

#ifdef VERSION_US
extern void func_84111DB4(u8 *arg0, s32 arg1);
void func_841179C4(u8 *arg0) {
    extern void func_84111D64(u8 *, s32);
    s32 temp_v0;

    temp_v0 = D_84193DD0[9] & 7;
    if ((temp_v0 != 6) && (temp_v0 != 2) && (temp_v0 != 5)) {
        func_84111D64(arg0,
            *(u8 *)((u8 *)(u32)*(u32 *)(arg0 + 0x2D4) + 0x13D8));
        func_84111DB4(arg0, 0);
    }
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84120BB4(u8 *, s32);
void func_84117A24(u8 *arg0) {
    extern u8 *D_841911E0;

    if (((*(s8 *)(arg0 + 0x619) + 2) == *(s16 *)(arg0 + 0x7E8)) &&
        (*(u8 *)(arg0 + 0x618) == 0xC7)) {
        func_84120BB4(*(u8 **)D_841911E0, (s32)arg0);
        func_8410C934(*(u8 **)D_841911E0, (s32)arg0,
            *(s16 *)(D_841911E0 + 0x98));
        func_84111348((s32)arg0, 0x19);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117AA0.s")
#endif

#ifdef VERSION_US
void func_84117C18(void *arg0)
{
  u8 temp_v0;
  ;
  if ((*((u8 *) (((u8 *) arg0) + 0x618))) == 0xD9)
  {
    if (((*((s8 *) (((u8 *) arg0) + 0x619))) + 0x39) == (*((s16 *) (((u8 *) arg0) + 0x7E8))))
    {
      func_84112564((s32) arg0);
    }
  }
  else
    if ((*((u8 *) (((u8 *) arg0) + 0x618))) == 0xCD)
  {
    if (((*((s8 *) (((u8 *) arg0) + 0x619))) + 0x13) == (*((s16 *) (((u8 *) arg0) + 0x7E8))))
    {
      func_84112564((s32) arg0);
    }
  }
  else
    if ((*((s8 *) (((u8 *) arg0) + 0x619))) == (*((s16 *) (((u8 *) arg0) + 0x7E8))))
  {
    func_84112564((s32) arg0);
  }
}
#endif

#ifdef VERSION_US
s32 func_84117CAC(void *arg0) {
    if (((*(s8 *)((u8 *)(arg0) + (0x619))) == (*(s16 *)((u8 *)(arg0) + (0x7E8)))) && (((*(u8 *)((u8 *)(D_84193DD0) + (9))) & 7) != 6)) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117CEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117DC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84117E94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84118138.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841182E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411845C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411854C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411862C.s")
#endif

#ifdef VERSION_US
void func_84118704(u8 *arg0) {
    extern void func_84117648(u8 *);

    if (*(s16 *)(arg0 + 0x7E8) == 0) {
        func_84112564((s32)arg0);
        func_841139D0(arg0);
    }
    func_841139D0(arg0);
    func_84117648(arg0);
}
#endif

#ifdef VERSION_US
extern void func_84117648(u8 *);

void func_84118754(u8 *arg0) {
    if ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 0) {
        func_84112564((s32) arg0);
        func_841139D0(arg0);
    }
    func_84117648(arg0);
}
#endif

#ifdef VERSION_US
extern s32 func_84112418(u8 *);
void func_84118794(u8 *arg0) {
    if ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 0) {
        func_84112564((s32) arg0);
        func_841139D0(arg0);
    }
    func_84112418(arg0);
    func_84117648(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841187E4.s")
#endif

#ifdef VERSION_US
extern void func_84111C44(void);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_064(s32 arg0) {
    extern void func_8410B104(void);
    func_8410B104();
    func_84111C44();
    func_8411FEE8(0x50);
    *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    *(u8 *)((u8 *)arg0 + 0x7F6) = 1;
    *(s32 *)((u8 *)(arg0 + (D_841911F4 * 4)) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841189EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84118C08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84118DD4.s")
#endif

#ifdef VERSION_US
extern void func_84111C44(void);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_197(s32 arg0) {
    func_84111C44();
    func_8411FEE8(0x50);
    *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    *(u8 *)((u8 *)arg0 + 0x7F6) = 1;
    *(s32 *)((u8 *)(arg0 + (D_841911F4 * 4)) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_841193E0.s")
#endif

#ifdef VERSION_US
extern f32 D_84188FEC;
extern void func_84111348(s32 arg0, s32 arg1);
extern s32 func_84113430(s32 arg0);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_199(u8 *arg0) {
    if (*(s8 *)(arg0 + 0x7F6) != 1) {
        if (func_84113430((s32)arg0) != 0) {
            *(s16 *)(arg0 + 0x7E8) = 0;
            func_8411FEE8(0x64);
            if (*(u16 *)(D_84193DD0 + 4) == 0x36) {
                func_84112EAC(arg0);
                func_84113D38(arg0);
                *(s16 *)(D_841911E0 + 0x98) = 0;
                func_84111348((s32)arg0, 0);
                func_84123F60(arg0, 0x17);
            }
            *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84119630.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84119908.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84119AB4.s")
#endif

#ifdef VERSION_US
extern void func_8410B104();
void BattleAnim_Dispatch_120(s32 arg0) {
    func_8411FEE8(0x3E);
    func_84111C44();
    func_8410B104();
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84119CF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_84119F24.s")
#endif

#ifdef VERSION_US
extern void func_84112E40(s32);
void BattleAnim_Dispatch_141(s32 arg0) {
    func_8411FEE8(0x1F);
    func_84112E40(arg0);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_142(u8 *arg0) {
    s32 index;

    if (func_84113430((s32)arg0) != 0) {
        func_841126C8((s32)arg0);
        *(s16 *)(arg0 + 0x7E8) = 0;
        func_8411FEE8(0x1F);
        index = func_8411E1F8((s32)arg0);
        if (((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12)) & 2) != 0) {
            *(s16 *)(D_841911E0 + 0x98) = 0x24;
        } else {
            *(s16 *)(D_841911E0 + 0x98) = 0;
        }
        func_84111348((s32)arg0, 0);
        func_84113D38(arg0);
        *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_8410890C(s32, s32);
void BattleAnim_Dispatch_143(s32 arg0) {
    if (func_841133EC(arg0) != 0) return;

    BattleAnim_Dispatch_002((u8 *)arg0);
    if (*(s16 *)((u8 *)(u8 *)arg0 + 0x7E8) == 2) {
        func_84112564(arg0);
        func_8410890C(0x104, arg0);
        func_80023A3C(8, 0, 0);
    }
    if (*(s16 *)((u8 *)(u8 *)arg0 + 0x7E8) == 0x1E) {
        *(u16 *)((u8 *)(u8 *)arg0 + 0x7F4) &= 0xFFFE;
        *(u16 *)((u8 *)(u8 *)arg0 + 0x7F4) &= 0xFFFD;
        func_841206D0((u8 *)arg0);
        *(s16 *)((u8 *)(u8 *)arg0 + 0x7E8) = 0;
        *(s32 *)((u8 *)(u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411A310.s")
#endif

#ifdef VERSION_US
void func_8411A3D4(void *arg0) {
    extern u8 D_84183C74;
    extern u32 func_8003570C(void);
    void *temp_v1;

    if ((*(u16 *)((u8 *)arg0 + 0x7EC) & 1) == 0) {
        *(u16 *)(D_841911E0 + 0x98) =
            *(u16 *)((u8 *)&D_84183C74 +
                ((func_8003570C() % 3) * 2));
        temp_v1 = *(void **)((u8 *)arg0 + 0x2D4);
        *(u8 *)((u8 *)arg0 + 0x619) = *(u8 *)((u8 *)temp_v1 + 0x13CF);
        *(u8 *)((u8 *)arg0 + 0x61A) = *(u8 *)((u8 *)temp_v1 + 0x13CE);
        *(u8 *)((u8 *)arg0 + 0x620) = *(u8 *)((u8 *)temp_v1 + 0x13CD);
    }
}
#endif

#ifdef VERSION_US
extern void func_84111C44(void);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_036(u8 *arg0) {
    extern void func_84108A10(u8 *);

    func_8411FEE8(0x258);
    func_84111C44();
    func_84108A10(arg0);
    *(s16 *)(arg0 + 0x7E8) = 0;
    *(u8 *)(arg0 + 0x7F6) = 3;
    *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411A4AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411A544.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411A620.s")
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_225(s32 arg0) {
    func_8411FEE8(0x50);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_8411A310(u8 *arg0);
extern void func_8411EE74(u8 *arg0);
void BattleAnim_Dispatch_226(u8 *arg0) {
    s32 temp_v0;

    temp_v0 = *(u16 *)((u8 *)D_84193DD0 + 6);
    if (temp_v0 == 0x4D) {
        func_84112580((s32) arg0);
        func_84112564((s32) arg0);
        temp_v0 = *(u16 *)((u8 *)D_84193DD0 + 6);
    }
    if (temp_v0 == 0x37) {
        func_8411EE74(arg0);
    }
    func_8411A310(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411A7D8.s")
#endif

#ifdef VERSION_US
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84112EDC(u8 *);
void BattleAnim_Dispatch_023(u8 *arg0) {
    extern s32 func_800427B8(s32);
    extern void func_84112EDC(u8 *);

    if (func_800427B8(*(s32 *)(arg0 + 0x5C0)) != 0) {
        func_84112EDC(arg0);
        *(s16 *)(arg0 + 0x7E8) = 0;
        *(u8 *)(arg0 + 0x7F6) = 1;
        *(s16 *)(D_841911E0 + 0x98) = 0;
        func_84111348((s32)arg0, 0);
        *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_024(u8 *arg0) {
    if (((*(s8 *)((u8 *)(arg0) + (0x7F6))) != 0) && ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 4)) {
        func_841206D0(arg0);
        func_8411FEE8(0);
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411A964.s")
#endif

#ifdef VERSION_US
extern s32 func_800427B8(s32);
extern void func_8410890C(s32, s32);
extern void func_84112EDC(u8 *);
void BattleAnim_Dispatch_163(u8 *arg0) {
    extern s32 func_800427B8(s32);
    extern void func_84112EDC(u8 *);
    extern void func_8410890C(s32, s32);
    s32 index;

    func_841139D0(func_8411E164(arg0));
    if (func_800427B8(*(s32 *)(arg0 + 0x5C0)) != 0) {
        func_84112EDC(arg0);
        *(s16 *)(arg0 + 0x7E8) = 0;
        *(u8 *)(arg0 + 0x7F6) = 1;
        index = func_8411E1F8((s32) arg0);
        if ((*(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0x10) & 7) != 0) {
            func_8410890C(0x100, (s32) arg0);
        }
        *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
    }
}
#endif

#ifdef VERSION_US
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_164(u8 *arg0) {
    if (*(s8 *)(arg0 + 0x7F6) != 0) {
        func_841139D0(func_8411E164((s32)arg0));
        if (*(s16 *)(arg0 + 0x7E8) == 4) {
            func_841206D0(arg0);
            func_8411FEE8(0);
            *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_84111C44(void);
extern void func_84113560(s32);
void BattleAnim_Dispatch_127(s32 arg0) {
    *(u8 *)((u8 *)arg0 + 0x618) = 1;
    func_84111C44();
    func_84113560(0x126);
    *(s32 *)((u8 *)(arg0 + (D_841911F4 * 4)) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411ABAC.s")
#endif

#ifdef VERSION_US
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_129(s32 arg0) {
    if (func_841133EC(arg0) == 0) {
        if (*(s16 *)((u8 *)arg0 + 0x7E8) == 0x46) {
            *(u16 *)((u8 *)arg0 + 0x7F4) = *(u16 *)((u8 *)arg0 + 0x7F4) & 0xFFFE;
            *(u16 *)((u8 *)arg0 + 0x7F4) = *(u16 *)((u8 *)arg0 + 0x7F4) & 0xFFFD;
            func_841206D0((u8 *)arg0);
            *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
            func_8411FEE8(0);
            *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
        }
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_101(u8 *arg0) {
    s8 temp_v0;

    temp_v0 = (*(s8 *)((u8 *)(arg0) + (0x7F6)));
    switch (temp_v0) {                              /* irregular */
    case 1:
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 2;
        return;
    case 2:
        func_84112158((s32) arg0, 0xFC);
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 3;
        return;
    case 3:
        if (ModelAnim_IsFinished(arg0) != 0) {
            func_841206D0(arg0);
            func_84112158((s32) arg0, 0xFB);
            func_8411FEE8(0);
        }
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411AE08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411AEA8.s")
#endif

#ifdef VERSION_US
extern u8 *D_841911E0;
void func_8411AF6C(u8 *arg0) {
    u8 *entry;
    s32 index;
    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        *(s16 *)(D_841911E0 + 0x98) = 0;
        index = arg0[0x618] - 1;
        entry = *(u8 **)(arg0 + 0x2D4) + (index * 0x14);
        arg0[0x616] = entry[0];
        arg0[0x61F] = 0xFF;
        arg0[0x617] = entry[1];
        arg0[0x619] = entry[0xB];
        arg0[0x61A] = entry[0xA];
        arg0[0x61B] = entry[6];
        arg0[0x620] = entry[9];
        arg0[0x61C] = entry[2];
        arg0[0x61D] = entry[3];
        *(s16 *)(arg0 + 0x628) = entry[0xC];
        *(s16 *)(arg0 + 0x62A) = entry[0xD];
        *(s16 *)(arg0 + 0x62C) = entry[0xE];
        arg0[0x661] = entry[0xF];
    }
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_092(u8 *arg0) {
    func_84111C44();
    (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 0;
    (*(u8 *)((u8 *)(arg0) + (0x618))) = (u8) (*(u8 *)((u8 *)(D_84193DD0) + (8)));
    func_841134A0(arg0);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411B070.s")
#endif

#ifdef VERSION_US
extern void func_84111D64(u8 *, s32);
extern void func_84112564(s32);
extern u8 * D_841911E0;
void func_8411B160(u8 *arg0) { if (*(s8 *)(arg0 + 0x619) == *(s16 *)(arg0 + 0x7E8)) { arg0[0x7F6] = 2; if (*(s16 *)(D_841911E0 + 0x98) == 4) *(f32 *)(D_841911E0 + 0x88) = 60.0f; func_84112564(arg0); } if (ModelAnim_IsFinished(arg0) != 0) { func_84111E50(arg0, (*(u8 **)(arg0 + 0x2D4))[0x139D]); func_84111D64(arg0, (*(u8 **)(arg0 + 0x2D4))[0x139C]); } }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411B1F4.s")
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_078(u8 *arg0)
{
  int new_var;
  new_var = 0xA4;
  *((s16 *) (((u8 *) arg0) + 0x7E8)) = 0;
  *((s8 *) (((u8 *) arg0) + 0x7F6)) = 0;
  func_8411FEE8(0x64);
  *((s8 *) (((u8 *) arg0) + 0x618)) = new_var;
  func_84111C44();
  func_841134A0(arg0);
  *((s32 *) (((u8 *) (arg0 + (D_841911F4 * 4))) + 0x5C8)) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
extern u8 D_841849B6[];
extern void func_841119CC(u8 *, u16);
extern void func_80030420(s32, u8, s16, s32);
extern void func_84111348(s32 arg0, s32 arg1);
extern void func_84112158(s32, s32);
extern void func_841126C8(s32 arg0);
extern s32 func_84113430(s32 arg0);
void BattleAnim_Dispatch_079(u8 *arg0) {
    if (func_84113430((s32)arg0) == 0) {
        return;
    }
    func_841126C8((s32)arg0);
    *(s16 *)(arg0 + 0x7E8) = 0;
    func_84112158((s32)arg0, 0xFB);
    func_841119CC(D_841911E0,
        *(u16 *)((u8 *)D_841849B6 + (*(u8 *)(arg0 + 0x618) << 3)));
    func_84111348((s32)arg0, 0);
    *(s8 *)(arg0 + 0x7F6) = 1;
    func_80030420(func_8411E1F8((s32)arg0) & 0xFF,
        *(u8 *)(arg0 + 0x618), *(s16 *)(arg0 + 0x1A), 0);
    *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411B3B8.s")
#endif

#ifdef VERSION_US
extern void func_84111C44(void);
extern void func_841134A0(u8 *arg0);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_148(u8 *arg0) {
    extern void func_84108AF8(u8 *);

    *(s16 *)(arg0 + 0x7E8) = 0;
    *(u8 *)(arg0 + 0x7F6) = 0;
    func_8411FEE8(0x3E8);
    func_84112B64((s32)arg0);
    *(u8 *)(arg0 + 0x618) = 0x90;
    func_84111C44();
    func_84108AF8(arg0);
    func_841134A0(arg0);
    *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
extern void func_84113920(u8 *);
void BattleAnim_Dispatch_149(u8 *arg0) {
    func_841139D0(arg0);
    func_84113920(arg0);
    if (func_84113430((s32) arg0) != 0) {
        func_841126C8((s32) arg0);
        func_84112158((s32) arg0, 0xFB);
        (*(s16 *)((u8 *)(D_841911E0) + (0x98))) = 0;
        func_84111348((s32) arg0, 0);
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411B5A8.s")
#endif

#ifdef VERSION_US
void func_8411B710(u8 *arg0) {
    s32 index;
    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        index = func_8411E1F8((s32)arg0);
        *(u16 *)(arg0 + 0x65C) = *(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0xC);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411B75C.s")
#endif

#ifdef VERSION_US
s32 func_800427B8(s32);
extern void func_84112EDC(u8 *);
void BattleAnim_Dispatch_177(u8 *arg0) {
    if (func_800427B8((*(s32 *)((u8 *)(arg0) + (0x5C0)))) != 0) {
        func_841126C8((s32) arg0);
        func_841136E8(arg0);
        func_84112EDC(arg0);
        func_8411FEE8(0x384);
        (*(s16 *)((u8 *)(arg0) + (0x7EA))) = 0;
        (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        (*(s8 *)((u8 *)(arg0) + (0x1D))) = 0;
        func_8410890C(0x12C, (s32) arg0);
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411B898.s")
#endif

#ifdef VERSION_US
void func_8411BAB8(u8 *arg0) {
    s32 index;
    if ((*(u16 *)(arg0 + 0x7EC) & 1) == 0) {
        index = func_8411E1F8((s32)arg0);
        *(u16 *)(arg0 + 0x65C) = *(u16 *)((u8 *)(u32)D_84193DD0 + (index << 4) + 0xC);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411BB04.s")
#endif

#ifdef VERSION_US
s32 func_800427B8(s32);
extern void func_84113560(s32);
void func_8411EE74(u8 *arg0);
void BattleAnim_Dispatch_086(u8 *arg0) {
    func_8411EE74(arg0);
    if (func_800427B8((*(s32 *)((u8 *)(arg0) + (0x5C0)))) != 0) {
        func_841126C8((s32) arg0);
        func_841136E8(arg0);
        func_84112EDC(arg0);
        func_8411FEE8(0x384);
        (*(s16 *)((u8 *)(arg0) + (0x7EA))) = 0;
        (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        func_841126C8((s32) arg0);
        (*(s8 *)((u8 *)(arg0) + (0x1D))) = 0;
        func_84113560(0x122);
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
        func_8411EE74(arg0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411BCC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411C1D4.s")
#endif

#ifdef VERSION_US
extern void func_841125A4(s32);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_169(s32 arg0) {
    func_841125A4(D_8419120C);
    *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    *(u8 *)((u8 *)arg0 + 0x7F6) = 0;
    func_8411FEE8(0x320);
    *(s32 *)((u8 *)(arg0 + (D_841911F4 * 4)) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411C310.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411C418.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411C7B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411C8A0.s")
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_184(s32 arg0) {
    if (func_84113430(arg0) != 0) {
        func_8410890C(0x112, arg0);
        (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411C9DC.s")
#endif

#ifdef VERSION_US
extern void func_841125A4(s32);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_239(s32 arg0) {
    func_841125A4(D_8419120C);
    *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    *(u8 *)((u8 *)arg0 + 0x7F6) = 0;
    func_8411FEE8(0x320);
    *(s32 *)((u8 *)(arg0 + (D_841911F4 * 4)) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411CC2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411CD38.s")
#endif

#ifdef VERSION_US
extern void func_8410C304(u8 *arg0, s32 arg1, s32 arg2);
extern void func_84111248();
extern void func_841125A4(s32);
extern void func_84113560(s32);
extern void func_8411FEE8(s32);
void BattleAnim_Dispatch_232(s32 arg0) {
    func_841125A4(D_8419120C);
    func_841112C8();
    *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    *(u8 *)((u8 *)arg0 + 0x7F6) = 0;
    func_8411FEE8(0x320);
    func_84113560(0x12A);
    func_84111248();
    func_8410C304(*(u8 **)D_841911E0, D_84191208, *(s16 *)(D_841911E0 + 0x98));
    *(u8 *)((u8 *)(u32)D_84191208 + 1) &= 0xFFFE;
    *(u8 *)((u8 *)(u32)1 + D_8419120C) &= 0xFFFE;
    *(s32 *)((u8 *)arg0 + (D_841911F4 * 4) + 0x5C8) = D_84183D50;
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_233(s32 arg0) {
    if (func_84113430(arg0) != 0) {
        (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
        (*(s8 *)((u8 *)(arg0) + (0x7F6))) = 1;
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411D1A8.s")
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_204(u8 *arg0) {}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_205(u8 *arg0) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411D2E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411D388.s")
#endif

#ifdef VERSION_US
extern void func_80024480(s16, s32);
void BattleAnim_Dispatch_008(u8 *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x7E8))) = 0;
    if (func_841139D0(arg0) == 0) {
        func_84112158((s32) arg0, 0xFC);
        func_80024480((*(s16 *)((u8 *)(arg0) + (0x658))), 2);
    }
    func_8411FEE8(0x12C);
    (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
}
#endif

#ifdef VERSION_US
void BattleAnim_Dispatch_009(u8 *arg0) {
    func_841139D0(arg0);
    if ((*(s16 *)((u8 *)(arg0) + (0x1A))) == 0xFC) {
        if ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 0x3C) {
            func_8411FEE8(0);
            (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
        }
    } else if ((ModelAnim_IsFinished(arg0) != 0) || ((*(s16 *)((u8 *)(arg0) + (0x7E8))) == 0x78)) {
        func_8411FEE8(0);
        (*(s32 *)((u8 *)((arg0 + (D_841911F4 * 4))) + (0x5C8))) = (s32) D_84183D50;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411D594.s")
#endif

#ifdef VERSION_US
extern void func_84112158(s32, s32);
extern void func_841125F4(void *arg0, s32 arg1);
void BattleAnim_Dispatch_247(s32 arg0) {
    if (ModelAnim_IsFinished(arg0) != 0) {
        func_84112158(arg0, 0xFB);
        func_841206D0((u8 *)arg0);
        func_841125F4((void *)arg0, 0);
        *(s16 *)((u8 *)arg0 + 0x7E8) = 0;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411D65C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411D7F8.s")
#endif

#ifdef VERSION_US
void func_8411D9B4(void) {
    extern s32 D_84191208;
    extern s32 D_8419120C;
    extern u8 D_84190410;
    extern u8 D_84190411;
    extern u8 D_841911FA;
    extern void func_8411D7F8(u8 *);
    extern void func_8411D65C(void);

    *(u16 *)((u8 *)(*(u8 **)&D_84191208) + 0x7EC) = 0;
    *(u16 *)((u8 *)(*(u8 **)&D_8419120C) + 0x7EC) = 0;
    *(u16 *)((u8 *)(*(u8 **)&D_84191208) + 0x7F4) = 0;
    *(u16 *)((u8 *)(*(u8 **)&D_8419120C) + 0x7F4) = 0;
    func_8411D7F8(*(u8 **)&D_84191208);
    func_8411D7F8(*(u8 **)&D_8419120C);
    D_84190410 = 0;
    D_84190411 = 0;
    D_841911FA = 0;
    func_8411D65C();
}
#endif

#ifdef VERSION_US
extern void func_84112648(void);
void func_8411DA2C(void) {
    func_84112648();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411DA4C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411DAE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8411DBF4.s")
#endif
