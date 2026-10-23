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
extern void GeoCamera_SetViewport(u8 *, s16, s16, s16, s16);
extern void GeoCamera_SetPerspective(u8 *, s32, f32, f32);
extern void func_80038E14(u8 *, s32, s32, s32, f32, f32, f32, s32);
void func_8410AE8C(u8 *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) { GeoCamera_SetViewport(arg0, arg1, arg2, arg3, *(s16 *)((u8 *)&arg4 + 2)); GeoCamera_SetPerspective(arg0, *(s32 *)(arg0 + 0x2C), 20.0f, 6400.0f); func_80038E14(arg0, *(s32 *)(arg0 + 0xA8), *(s32 *)(arg0 + 0xAC), *(s32 *)(arg0 + 0xB0), *(f32 *)(arg0 + 0xB4), *(f32 *)(arg0 + 0xB8), *(f32 *)(arg0 + 0xBC), 0); }
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
extern void func_8411EF18(u8 *);
extern void func_8410AE8C(u8 *, s16, s16, s16, s32);
extern void func_841112C8(void);
extern u8 D_84190428[];
extern u8 D_841910E0[];
extern u8 * D_841911E0;
extern s32 D_84191208;
extern s32 D_8419120C;
void func_8410B104(void) {
    if (D_841910E0[1] & 0x10) {
        *(s16 *)(D_841911E0 + 0x9A) = 0;
        *(s16 *)(D_841911E0 + 0x9C) = 0;
        *(s16 *)(D_841911E0 + 0x9E) = 0x140;
        *(s16 *)(D_841911E0 + 0xA0) = 0xF0;
        func_8410AE8C(D_84190428, *(s16 *)(D_841911E0 + 0x9A), *(s16 *)(D_841911E0 + 0x9C), *(s16 *)(D_841911E0 + 0x9E), (s32)*(s16 *)(D_841911E0 + 0xA0));
        D_841910E0[1] &= 0xFFEF;
        D_84190428[1] |= 0x10;
    }
    func_841112C8();
    func_8411EF18((u8 *)D_84191208);
    func_8411EF18((u8 *)D_8419120C);
}
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
/* mkdraft:func_8410B420 begin */
extern u8 *D_841911E8;
extern u8 D_8418393C;
extern u8 D_8418455C;
extern u8 *func_8410B330(u8 *);
extern s32 func_8411DC80(u16, s32 *, s32);
extern s32 func_8411E140(s32);
extern void func_8410B35C(u8 *, void *, s16);
extern void func_800371B4(u8 *, u8 *, f32, s16, s16);
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);

void func_8410B420(u8 *arg0, void *arg1, s16 arg2) {
    s16 var_s2;
    s16 var_t6 = 1;
    u8 *temp_v1;

    D_841911E8 = func_8410B330(arg0);
    if (func_8411DC80(*(u8 *)((u8 *)arg1 + 0x61F), (s32 *)&D_8418393C, 8) != 0) {
        var_s2 = (s16)func_8411E140((s32)arg1);
    } else {
        var_s2 = *(s16 *)((u8 *)arg1 + 0x20);
    }
    if (var_s2 < 0) {
        var_t6 = -1;
    }
    func_8410B35C(arg0, arg1, var_s2);
    temp_v1 = (u8 *)&D_8418455C + (*(s32 *)((u8 *)&arg2 - 2) * 0x1C);
    *(s16 *)(D_841911E8 + 0x90) = *(s16 *)temp_v1;
    *(s16 *)(D_841911E8 + 0x92) = (*(s16 *)(temp_v1 + 2) * var_t6) + var_s2;
    *(f32 *)(D_841911E8 + 0x74) *= *(f32 *)(temp_v1 + 4);
    *(f32 *)(D_841911E8 + 0x88) = *(f32 *)(temp_v1 + 0x10);
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    *(f32 *)(D_841911E8 + 0x88) = 45.0f;
    func_800371B4(D_841911E8 + 0x50, arg0 + 0xA8, *(f32 *)(D_841911E8 + 0x74), *(s16 *)(D_841911E8 + 0x90), (s32)*(s16 *)(D_841911E8 + 0x92));
    Vec3f_SetComponentsDuplicate((f32 *)(D_841911E8 + 0x68), *(f32 *)(arg0 + 0xA8), *(f32 *)(arg0 + 0xAC), *(f32 *)(arg0 + 0xB0));
}
/* mkdraft:func_8410B420 end */
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
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_80037120(void *, void *, f32 *, s16 *, s16 *);
extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
extern s32 func_8411DC80(u16, s32 *, s32);
extern void func_841203B4(u8 *, f32, f32);
void func_8410B704(u8 *arg0, void *arg1, u8 *arg2, u8 *arg3) {
    extern s32 D_84183930[];
    f32 target[3];
    f32 pos[3];
    f32 distance;
    s16 angle1;
    s16 angle0;
    f32 padding[2];
    f32 scaled;
    if (func_8411DC80(*(u16 *)(arg2 + 0x98), D_84183930, 12) != 0) {
        Camera_ComputeEyeFromAngles(arg3, (u8 *)target, *(f32 *)(arg2 + 0x40), *(s16 *)(arg2 + 0x3C), *(s16 *)(arg2 + 0x3E));
        Vec3f_SetComponentsDuplicate(pos, *(f32 *)(arg0 + 0xA8), *(f32 *)(arg0 + 0xAC), *(f32 *)(arg0 + 0xB0));
        func_80037120((s32)pos, (s32)target, (s32 *)&distance, &angle0, &angle1);
        Camera_ComputeEyeFromAngles((u8 *)pos, arg0 + 0xA8, distance, angle0, angle1);
        if (*(f32 *)(arg0 + 0xAC) <= 10.0f) {
            *(f32 *)(arg0 + 0xAC) = 10.0f;
        }
    } else {
        func_841203B4(arg2 + 0x44, *(f32 *)(arg2 + 0x4C), *(f32 *)(arg2 + 0x48));
        Camera_ComputeEyeFromAngles(arg3, (u8 *)target, *(f32 *)(arg2 + 0x40), *(s16 *)(arg2 + 0x3C), *(s16 *)(arg2 + 0x3E));
        Vec3f_SetComponentsDuplicate(pos, *(f32 *)(arg0 + 0xA8), *(f32 *)(arg0 + 0xAC), *(f32 *)(arg0 + 0xB0));
        func_80037120((s32)pos, (s32)target, (s32 *)&distance, &angle0, &angle1);
        Camera_ComputeEyeFromAngles((u8 *)pos, arg0 + 0xA8, *(f32 *)(arg2 + 0x44) * distance, angle0, angle1);
        if (*(f32 *)(arg0 + 0xAC) <= 10.0f) {
            *(f32 *)(arg0 + 0xAC) = 10.0f;
        }
    }
}
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
extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
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
    Camera_ComputeEyeFromAngles(D_841911E8 + 0x50, arg0 + 0xA8, *(f32 *)(D_841911E8 + 0x74), *(s16 *)(D_841911E8 + 0x90), (s32)*(s16 *)(D_841911E8 + 0x92));
    Vec3f_SetComponentsDuplicate((f32 *)(D_841911E8 + 0x68), *(f32 *)(arg0 + 0xA8), *(f32 *)(arg0 + 0xAC), *(f32 *)(arg0 + 0xB0));
}
#endif

#ifdef VERSION_US
extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
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
    Camera_ComputeEyeFromAngles(D_841911E8 + 0x50, arg0 + 0xA8, *(f32 *)(D_841911E8 + 0x74), *(s16 *)(D_841911E8 + 0x90), (s32)*(s16 *)(D_841911E8 + 0x92));
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
extern void func_80037120(void *, void *, f32 *, s16 *, s16 *);
extern u8 * func_8410B330(u8 *arg0);
extern void func_8411E0A4(void *, void *, void *);
extern void func_841203B4(u8 *, f32, f32);
extern u8 * D_841911E8;
void BattleAnim_UpdateCameraHeightTarget(u8 *arg0, u8 *arg1) {
    f32 position[3];
    f64 separation;
    f32 distance;
    s16 angle_x;
    s16 angle_y;
    D_841911E8 = func_8410B330(arg0);
    func_8411E0A4(arg1, position, D_841911E8);
    func_80037120(position, D_841911E8 + 80, &distance, &angle_x, &angle_y);
    separation = distance;
    if (*(f32 *)(D_841911E8 + 128) * 0.6 < separation) {
        func_841203B4(D_841911E8 + 96, position[1], 0.3f);
    }
    *(f32 *)(arg0 + 184) = *(f32 *)(D_841911E8 + 96);
}
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
void BattleAnim_AdjustCameraDistance(u8 *arg0, f32 distance, s16 pitch, s16 angle, u8 *from, u8 *to) {
    if (distance > *(f32 *)(arg0 + 128) * 1.7f) {
        func_800371B4(from, to, distance * 0.6f, pitch, angle);
    } else if (distance > *(f32 *)(arg0 + 128) * 1.6f) {
        func_800371B4(from, to, distance * 0.75f, pitch, angle);
    } else if (distance > *(f32 *)(arg0 + 128) * 1.5f) {
        func_800371B4(from, to, distance * 0.85f, pitch, angle);
    }
}
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
extern void func_8410B8FC(f32 *, u8 *, s16);
extern void func_8411E0A4(void *, void *, void *);
extern u8 * func_8410B330(u8 *);
extern s32 D_84184148;
extern u8 * D_841911E8;
extern s32 D_841911EC;
extern u8 * D_84193DD0;
void BattleAnim_ModelDispatch_127(u8 *arg0, u8 *arg1) {
    f32 sp3C[3];
    f32 sp30[3];
    f32 sp24[3];
    s32 index;

    D_841911E8 = func_8410B330(arg0);
    *(s16 *)(D_841911E8 + 0x94) = 0;
    *(s16 *)(D_841911E8 + 0xA2) = 0;
    index = func_8411E1F8(arg1);
    if (*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x10) == 0x20) {
        *(s16 *)(D_841911E8 + 0x98) = 0x26;
    } else {
        *(s16 *)(D_841911E8 + 0x98) = 0x24;
    }
    *(f32 *)(D_841911E8 + 0x44) = 0.0f;
    *(f32 *)(D_841911E8 + 0x48) = 0.0f;
    *(f32 *)(D_841911E8 + 0x84) = *(f32 *)(arg1 + 0x644);
    *(f32 *)(D_841911E8 + 0x80) = *(f32 *)(arg1 + 0x640);
    *(f32 *)(D_841911E8 + 0x7C) = *(f32 *)(arg1 + 0x654);
    *(f32 *)(D_841911E8 + 0x74) = *(f32 *)(arg1 + 0x64C);
    *(f32 *)(D_841911E8 + 0x78) = 0.0f;
    func_8410B8FC(sp3C, arg1 + 0x634, *(s16 *)(arg1 + 0x20));
    sp3C[0] += *(f32 *)(arg1 + 0x24);
    sp3C[2] += *(f32 *)(arg1 + 0x2C);
    Vec3f_SetComponentsDuplicate((f32 *)(D_841911E8 + 0x5C), sp3C[0], *(f32 *)(arg1 + 0x638), sp3C[2]);
    Vec3f_SetComponentsDuplicate((f32 *)(D_841911E8 + 0x50), sp3C[0], *(f32 *)(arg1 + 0x638), sp3C[2]);
    index = func_8411E1F8(arg1);
    if ((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12) & 2) != 0) {
        func_8411E0A4(arg1, sp30, D_841911E8);
        Vec3f_SetComponentsDuplicate((f32 *)(D_841911E8 + 0x5C), sp3C[0], sp30[1], sp3C[2]);
        Vec3f_SetComponentsDuplicate((f32 *)(D_841911E8 + 0x50), sp3C[0], sp30[1], sp3C[2]);
    }
    index = func_8411E1F8(arg1);
    if (((*(u16 *)((u8 *)D_84193DD0 + (index << 4) + 0x12) & 4) != 0) ||
        ((*(u16 *)(arg1 + 0x7F4) & 0x10) != 0)) {
        *(f32 *)(D_841911E8 + 0x60) = 30.0f;
        *(f32 *)(D_841911E8 + 0x54) = 30.0f;
    }
    Vec3f_SetComponentsDuplicate((f32 *)(D_841911E8 + 0x68), *(f32 *)(arg0 + 0xA8), *(f32 *)(arg0 + 0xAC), *(f32 *)(arg0 + 0xB0));
    *(s32 *)(D_841911E8 + (D_841911EC * 8) + 8) = D_84184148;
    *(f32 *)(D_841911E8 + 0x88) = 80.0f;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_37A6E0/func_8410F3E8.s")
#endif

#ifdef VERSION_US
extern void func_80037120(void *, void *, f32 *, s16 *, s16 *);
extern u8 * func_8410B330(u8 *);
extern s32 D_84184148;
extern u8 * D_841911E8;
extern s32 D_841911EC;
void BattleAnim_ModelDispatch_148(u8 *arg0, s32 arg1) {
    u8 *temp_v0;
    temp_v0 = func_8410B330(arg0);
    D_841911E8 = temp_v0;
    func_80037120((s32)(arg0 + 0xA8), (s32)(arg0 + 0xB4), (s32 *)(D_841911E8 + 0x74), (s16 *)(D_841911E8 + 0x90), (s16 *)(D_841911E8 + 0x92));
    *(s32 *)(D_841911E8 + (D_841911EC * 8) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
extern u8 * func_8410B330(u8 *);
void BattleAnim_ModelDispatch_149(u8 *arg0, s32 arg1) {
    extern s32 BattleAnim_StepToS16(s16 *, s16, s16);
    extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
    D_841911E8 = func_8410B330(arg0);
    BattleAnim_StepToS16((s16 *)(D_841911E8 + 0x92), -0x8000, 0x71C);
    Camera_ComputeEyeFromAngles(arg0 + 0xA8, arg0 + 0xB4,
        *(f32 *)(D_841911E8 + 0x74),
        *(s16 *)(D_841911E8 + 0x90),
        (s32)*(s16 *)(D_841911E8 + 0x92));
}
#endif

#ifdef VERSION_US
extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
extern u8 * func_8410B330(u8 *);
extern s32 D_84184148;
extern u8 * D_841911E8;
extern s32 D_841911EC;
void func_8410F78C(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_80037120((s32)(arg0 + 0xA8), (s32)(arg0 + 0xB4), (s32 *)(D_841911E8 + 0x74), (s16 *)(D_841911E8 + 0x90), (s16 *)(D_841911E8 + 0x92));
    *(s16 *)(D_841911E8 + 0x92) += 0x5555;
    Camera_ComputeEyeFromAngles(arg0 + 0xA8, arg0 + 0xB4, *(f32 *)(D_841911E8 + 0x74), *(s16 *)(D_841911E8 + 0x90), (s32)*(s16 *)(D_841911E8 + 0x92));
    *(s32 *)(D_841911E8 + (D_841911EC * 8) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
extern u8 * func_8410B330(u8 *);
void BattleAnim_ModelDispatch_156(u8 *arg0, s32 arg1) {
    extern s32 BattleAnim_StepToS16(s16 *, s16, s16);
    extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
    D_841911E8 = func_8410B330(arg0);
    BattleAnim_StepToS16((s16 *)(D_841911E8 + 0x92), 0x4000, 0x71C);
    Camera_ComputeEyeFromAngles(arg0 + 0xA8, arg0 + 0xB4,
        *(f32 *)(D_841911E8 + 0x74),
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
extern u8 * func_8410B330(u8 *arg0);
extern void func_8410C934(u8 *arg0, s32 arg1, s16 arg2);
extern s32 D_84184148;
extern u8 * D_841911E8;
extern s32 D_841911EC;
void func_8410F9FC(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    if (*(s16 *)(arg1 + 0x1A) == 0x5F) {
        *(s16 *)(D_841911E8 + 0x98) = 0x23;
    } else if (*(s16 *)(arg1 + 0x1A) == 0xF9) {
        *(s16 *)(D_841911E8 + 0x98) = 0x23;
    } else {
        *(s16 *)(D_841911E8 + 0x98) = 0x22;
    }
    func_8410C934(arg0, arg1, *(s16 *)(D_841911E8 + 0x98));
    *(f32 *)(arg0 + 0x2C) = 70.0f;
    *(s32 *)(D_841911E8 + (D_841911EC * 8) + 8) = D_84184148;
}
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
extern u8 * func_8410B330(u8 *);
extern void func_84120960(u8 *, s32);
extern s32 D_84184148;
extern u8 * D_841911E8;
extern s32 D_841911EC;
extern u8 * D_84193DD0;
void BattleAnim_ModelDispatch_204(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    func_84120960(arg0, arg1);
    *(s16 *)(D_841911E8 + 0x90) = 0x222;
    *(s16 *)(D_841911E8 + 0x92) = 0;
    *(f32 *)(D_841911E8 + 0x74) = 500.0f;
    if ((*(u16 *)(D_84193DD0 + 0x12) & 2) != 0 || (*(u16 *)(D_84193DD0 + 0x22) & 2) != 0) {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 180.0f, 0.0f);
    } else {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 40.0f, 0.0f);
    }
    Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xA8), -323.0f, 394.0f, 268.0f);
    *(s32 *)(D_841911E8 + (D_841911EC * 8) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
extern u8 *D_841911E8;
extern u8 *D_84193DD0;
extern s32 D_841911EC;
extern s32 D_84184148;
extern u8 *func_8410B330(u8 *);
extern void func_84120960(u8 *, s32);
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
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
    Camera_ComputeEyeFromAngles(arg0 + 0xB4, arg0 + 0xA8,
        *(f32 *)((u8 *)D_841911E8 + 0x74),
        *(s16 *)((u8 *)D_841911E8 + 0x90),
        (s32)*(s16 *)((u8 *)D_841911E8 + 0x92));
    *(s32 *)((u8 *)(D_841911E8 + (D_841911EC * 8)) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
void BattleAnim_ModelDispatch_030(u8 *arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = func_8410B330(arg0);
    D_841911E8 = temp_v0;
    (*(s16 *)((u8 *)(temp_v0) + (0x92))) = (s16) ((*(s16 *)((u8 *)(temp_v0) + (0x92))) + 0xE8);
    Camera_ComputeEyeFromAngles(arg0 + 0xB4, arg0 + 0xA8, (*(f32 *)((u8 *)(D_841911E8) + (0x74))), (*(s16 *)((u8 *)(D_841911E8) + (0x90))), (s32) (*(s16 *)((u8 *)(D_841911E8) + (0x92))));
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
    *(f32 *)((u8 *)D_841911E8 + 0x74) = 550.0f;
    if ((*(u16 *)((u8 *)D_84193DD0 + 0x12) & 2) || (*(u16 *)((u8 *)D_84193DD0 + 0x22) & 2)) {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 180.0f, 0.0f);
    } else {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 40.0f, 0.0f);
    }
    Camera_ComputeEyeFromAngles(arg0 + 0xB4, arg0 + 0xA8,
        *(f32 *)((u8 *)D_841911E8 + 0x74),
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
    Camera_ComputeEyeFromAngles(arg0 + 0xB4, arg0 + 0xA8, (*(f32 *)((u8 *)(D_841911E8) + (0x74))), (*(s16 *)((u8 *)(D_841911E8) + (0x90))), (s32) (*(s16 *)((u8 *)(D_841911E8) + (0x92))));
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_064(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    *(f32 *)(arg0 + 0x2C) = 45.0f;
    func_84120960(arg0, arg1);
    *(s16 *)((u8 *)D_841911E8 + 0x90) = 0x9F4;
    *(s16 *)((u8 *)D_841911E8 + 0x92) = 0;
    *(f32 *)((u8 *)D_841911E8 + 0x74) = 550.0f;
    if ((*(u16 *)((u8 *)D_84193DD0 + 0x12) & 2) || (*(u16 *)((u8 *)D_84193DD0 + 0x22) & 2)) {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 180.0f, 0.0f);
        *(s16 *)((u8 *)D_841911E8 + 0x90) = (s16)-0x9F4;
    } else {
        Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), 0.0f, 40.0f, 0.0f);
    }
    Camera_ComputeEyeFromAngles(arg0 + 0xB4, arg0 + 0xA8,
        *(f32 *)((u8 *)D_841911E8 + 0x74),
        *(s16 *)((u8 *)D_841911E8 + 0x90),
        (s32)*(s16 *)((u8 *)D_841911E8 + 0x92));
    *(s32 *)((u8 *)(D_841911E8 + (D_841911EC * 8)) + 8) = D_84184148;
}
#endif

#ifdef VERSION_US
void BattleAnim_ModelDispatch_065(u8 *arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = func_8410B330(arg0);
    D_841911E8 = temp_v0;
    (*(s16 *)((u8 *)(temp_v0) + (0x92))) = (s16) ((*(s16 *)((u8 *)(temp_v0) + (0x92))) + 0xE8);
    Camera_ComputeEyeFromAngles(arg0 + 0xB4, arg0 + 0xA8, (*(f32 *)((u8 *)(D_841911E8) + (0x74))), (*(s16 *)((u8 *)(D_841911E8) + (0x90))), (s32) (*(s16 *)((u8 *)(D_841911E8) + (0x92))));
    (*(f32 *)((u8 *)(arg0) + (0xB0))) = (f32) ((f64) (*(f32 *)((u8 *)(arg0) + (0xB0))) * 0.599999999999999978);
}
#endif

#ifdef VERSION_US
extern u8 D_84185258;
extern u8 D_84185264;
extern s32 D_841910D8;
extern s32 D_841911EC;
extern s32 D_84184148;

/* IDO colors the CSE'd D_84185258 row base v0 here; retail keeps it v1 for
   both Vec3f_SetComponentsDuplicate blocks. The 8 register words are the
   objdump-verified rotation (offsets 0x78-0x84, 0xD4-0xE0). */
#pragma REWRITE_FUNCTION_WORD(func_84110118, 0x78, 0x01091021, 0x01091821)
#pragma REWRITE_FUNCTION_WORD(func_84110118, 0x7C, 0x844A0000, 0x846A0000)
#pragma REWRITE_FUNCTION_WORD(func_84110118, 0x80, 0x844B0002, 0x846B0002)
#pragma REWRITE_FUNCTION_WORD(func_84110118, 0x84, 0x844C0004, 0x846C0004)
#pragma REWRITE_FUNCTION_WORD(func_84110118, 0xD4, 0x01CF1021, 0x01CF1821)
#pragma REWRITE_FUNCTION_WORD(func_84110118, 0xD8, 0x84580006, 0x84780006)
#pragma REWRITE_FUNCTION_WORD(func_84110118, 0xDC, 0x84590008, 0x84790008)
#pragma REWRITE_FUNCTION_WORD(func_84110118, 0xE0, 0x8448000A, 0x8468000A)

/* mkdraft:func_84110118 begin */
void func_84110118(u8 *arg0, s32 arg1) {
    D_841911E8 = func_8410B330(arg0);
    *(f32 *)(arg0 + 0x2C) = (f32)*(s16 *)((u8 *)&D_84185264 + D_841910D8 * 0xE);
    func_84120960(arg0, arg1);
    Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4),
        (f32)*(s16 *)((u8 *)&D_84185258 + D_841910D8 * 0xE),
        (f32)*(s16 *)((u8 *)&D_84185258 + D_841910D8 * 0xE + 2),
        (f32)*(s16 *)((u8 *)&D_84185258 + D_841910D8 * 0xE + 4));
    Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xA8),
        (f32)*(s16 *)((u8 *)&D_84185258 + D_841910D8 * 0xE + 6),
        (f32)*(s16 *)((u8 *)&D_84185258 + D_841910D8 * 0xE + 8),
        (f32)*(s16 *)((u8 *)&D_84185258 + D_841910D8 * 0xE + 0xA));
    *(s32 *)((u8 *)(D_841911E8 + (D_841911EC * 8)) + 8) = D_84184148;
}
/* mkdraft:func_84110118 end */
#endif

#ifdef VERSION_US
extern void Camera_ComputeEyeFromAngles(u8 *, u8 *, f32, s16, s32);
extern u8 * func_8410B330(u8 *arg0);
extern void func_8410B884(u8 *arg0, void *arg1, u8 *arg2, s16 arg3);
extern void func_8410C934(u8 *arg0, s32 arg1, s16 arg2);
extern s32 D_84184148;
extern u8 * D_841911E8;
extern s32 D_841911EC;
void func_84110264(u8 *arg0, s32 arg1)
{
    func_8410C934(arg0, arg1, *(s16 *)((D_841911E8 = func_8410B330(arg0)) + 0x98));
    func_8410B884(arg0, (void *)(u32)arg1, D_841911E8, *(s16 *)((u8 *)(u32)arg1 + 0x20));
    Camera_ComputeEyeFromAngles(D_841911E8 + 0x50, arg0 + 0xA8, *(f32 *)(D_841911E8 + 0x74) / (f32)2, 0, *(s16 *)(D_841911E8 + 0x92));
    *(s16 *)(D_841911E8 + 0x3C) = 0;
    *(s32 *)(D_841911E8 + D_841911EC * 8 + 8) = D_84184148;
}
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
extern u8 D_84183944[];
extern u8 * func_8410B330(u8 *arg0);
extern void func_8410DFC4(u8 *, void *);
extern void func_8410E688(u8 *arg0, void *arg1);
extern void func_8410E73C(u8 *arg0, void *arg1);
extern void func_84110B2C(u8 *, s32);
extern s32 func_8411DC80(u16, s32 *, s32);
extern void func_841203B4(u8 *, f32, f32);
extern u8 D_8418393C;
extern u8 * D_841911E8;
void func_84110718(u8 *arg0, u8 *arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_841203B4(arg0 + 0x2C, *(f32 *)(D_841911E8 + 0x88), 0.05f);
    if (func_8411DC80(arg1[0x61F], (s32 *)&D_8418393C, 8) == 0) {
        func_8410DFC4(arg0, arg1);
    }
    if (func_8411DC80(*(u16 *)(D_841911E8 + 0x98), (s32 *)D_84183944, 0x1C) != 0) {
        func_8410E688(arg0, arg1);
    } else {
        func_8410E73C(arg0, arg1);
    }
    func_84110B2C(arg0, (s32)arg1);
}
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
extern u8 * func_8410B330(u8 *);
extern void func_8410B884(u8 *arg0, void *arg1, u8 *arg2, s16 arg3);
extern void func_8410DFC4(u8 *, void *);
extern void func_841203B4(u8 *, f32, f32);
extern u8 * D_841911E8;
void BattleAnim_ModelDispatch_191(u8 *arg0, void *arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_841203B4(arg0 + 0x2C, *(f32 *)(D_841911E8 + 0x88), 0.05f);
    if (10.0f < *(f32 *)(arg0 + 0xB8)) {
        func_8410DFC4(arg0, arg1);
    } else {
        *(f32 *)(arg0 + 0xB8) = 10.0f;
    }
    func_8410B884(arg0, arg1, D_841911E8, *(s16 *)((u8 *)arg1 + 0x20));
    func_8410B60C(arg0, arg1, D_841911E8, arg0 + 0xB4);
}
#endif

#ifdef VERSION_US
extern void func_8410C840(u8 *, void *, u8 *, u8 *);
extern u8 * func_8410B330(u8 *);
extern void func_8410DFC4(u8 *, void *);
extern void func_841203B4(u8 *, f32, f32);
extern u8 * D_841911E8;
void BattleAnim_ModelDispatch_184(u8 *arg0, void *arg1) {
    D_841911E8 = func_8410B330(arg0);
    func_841203B4(arg0 + 0x2C, *(f32 *)(D_841911E8 + 0x88), 0.05f);
    func_8410DFC4(arg0, arg1);
    func_8410C840(arg0, arg1, D_841911E8, arg0 + 0xB4);
}
#endif
