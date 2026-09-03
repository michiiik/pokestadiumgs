#include "global.h"


#ifdef VERSION_US
extern s32 D_80126F40;

s32 func_80042B00(s32 arg0, s32 arg1) {
    if (!arg0) {
        D_80126F40 = arg1;
    }
    return 0;
}

void func_80042B14(u8 *arg0) {
    *(u16 *)(arg0 + 0) = 0;
    *(u32 *)(arg0 + 4) = 0;
}

extern s32 func_80064728();
extern void func_8003F5AC();
void func_80042B20(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4) {
    if (arg1 != 0) {
        *arg3 = func_80064728(arg2);
        *(u16 *)(arg0 + 0) |= 1;
        func_8003F5AC(arg4, arg2);
    } else {
        *arg3 = arg2;
        *(u16 *)(arg0 + 0) &= 0xFFFE;
        *arg4 = 0;
    }
    *(u16 *)(arg0 + 0) |= 2;
    *(s32 *)(arg0 + 4) = arg2;
}

void func_80042BB0(u16 *arg0) {
    *arg0 &= (u16)~2;
}

extern u8 D_80094C64;
extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState();
extern s32 func_80040E80();
extern void MainPool_FinalizeAllocation();
extern void GeoCamera_SetViewport(void *, s16, s16, s16, s32);
extern void GeoCamera_SetPerspective(void *, f32, f32, f32);
void func_80042BC0(u8 *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    s32 temp;
    temp = MainPool_AllocState(main_pool_get_available(), 0);
    *(s32 *)(arg0 + 0x18) = func_80040E80(temp, &D_80094C64);
    *(s32 *)(arg0 + 0x1C) = D_80126F40;
    MainPool_FinalizeAllocation(temp);
    GeoCamera_SetViewport((void *)(u32)*(u32 *)((u8 *)(u32)*(u32 *)(arg0 + 0x18) + 0xC), arg1, arg2, arg3, arg4);
    GeoCamera_SetPerspective((void *)(u32)*(u32 *)((u8 *)(u32)*(u32 *)(arg0 + 0x18) + 0xC), 30.0f, 100.0f, 12800.0f);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042C68.s")

s32 func_80042D54(u8 *arg0, u16 arg1) { s32 result = 0; if (arg0 != NULL) { *(u16 *)(arg0 + 2) = arg1; result = 1; } return result; }

s32 func_80042D74(u8 *arg0, s32 arg1) { s32 result = 0; if (arg0 != NULL) { *(s32 *)(arg0 + 8) = arg1; result = 1; } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042D8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80042EB8.s")

void func_80042F94(void* arg0, void* arg1) {
    func_80042EB8(arg0, 1, arg1, 1);
}

void func_80042FBC(void* arg0, void* arg1) {
    func_80042EB8(arg0, 0, arg1, 1);
}

void func_80042FE4(void* arg0, void* arg1) {
    func_80042EB8(arg0, 0, arg1, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_8004300C.s")

extern s32 func_800427B8();
extern void func_80042D8C();
s32 func_80043064(u8 *arg0) {
    s32 result = 0;
    if (func_800427B8(*(s32 *)(arg0 + 0x14), arg0) != 0) {
        result = *(u16 *)(u32)*(u32 *)((u8 *)(u32)*(u32 *)(arg0 + 0x14) + 0x38);
        func_80042D8C(arg0);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_800430B4.s")

extern void *D_80087200;
s32 func_8004335C(s32 arg0, u8 *arg1) {
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0;
    s32 result;

    result = 0;
    if (arg0 == 0) {
        var_v0 = 0x800;
        var_a0 = 0x400;
        var_a1 = 0x200;
        var_a2 = 0x100;
    } else {
        var_v0 = 8;
        var_a0 = 4;
        var_a1 = 2;
        var_a2 = 1;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_v0) != 0) {
        result = 1;
        *(s16 *)(arg1 + 0) = *(s16 *)(arg1 + 0) + 0x400;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_a0) != 0) {
        result = 1;
        *(s16 *)(arg1 + 0) = *(s16 *)(arg1 + 0) - 0x400;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_a1) != 0) {
        result = 1;
        *(s16 *)(arg1 + 2) = *(s16 *)(arg1 + 2) + 0x400;
    }
    if ((*(u16 *)((u8 *)D_80087200 + 6) & var_a2) != 0) {
        result = 1;
        *(s16 *)(arg1 + 2) = *(s16 *)(arg1 + 2) - 0x400;
    }
    return result;
}

s32 func_80043444(u8 *arg0) { return 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/43700/func_80043450.s")

extern s32 D_80094C60;
extern void func_800430B4();
extern s32 func_8004335C();
extern void func_80043450();
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
void func_80043500(u8 *arg0) {
    s32 result;
    u16 flags;
    s16 countdown;
    f32 scale;

    result = 0;
    if (D_80094C60 != 0) {
        func_800430B4();
    }
    flags = *(u16 *)(arg0 + 0);
    if (*(u16 *)(arg0 + 0) & 2) {
        result = func_8004335C((*(u16 *)(arg0 + 0) & 1) != 0, *(s32 *)(arg0 + 0x1C) + 0x1E);
        if (result == 0) {
            result = func_80043444((u8 *)((u32)*(u32 *)(arg0 + 0x1C) + 0x1E));
        }
    }
    if (result != 0) {
        *(s16 *)(arg0 + 0xE) = 0;
        *(s16 *)(arg0 + 0xC) = 0x78;
    } else if (*(u16 *)(arg0 + 0) & 4) {
        countdown = *(s16 *)(arg0 + 0xC);
        if (countdown > 0) {
            *(s16 *)(arg0 + 0xC) = countdown - 1;
        } else {
            func_80043450(arg0);
        }
    }
    scale = *(f32 *)(arg0 + 0x10);
    Vec3f_SetComponentsDuplicate((f32 *)((u32)*(u32 *)(arg0 + 0x1C) + 0x30), scale, scale, scale);
}

extern Gfx *D_800D0510;
extern void GfxImage_FillCurrent();
extern void func_8000766C();
void func_800435D4(u8 *arg0) {
    void (*callback)();
    callback = *(void (**)())(arg0 + 8);
    if (callback == NULL) {
        GfxImage_FillCurrent(&D_800D0510, *(u16 *)(arg0 + 2));
    } else {
        callback(arg0);
        gDPPipeSync(D_800D0510++);
        gDPSetTexturePersp(D_800D0510++, G_TP_PERSP);
        func_8000766C(&D_800D0510, 0, 0, *(s16 *)(arg0 + 4), *(s16 *)(arg0 + 6));
    }
}

extern void func_80043500();
extern void func_80007328();
extern void func_800435D4();
extern void GeoRender_AdvanceFrameCounter();
extern void func_8003C6B8();
s32 func_80043678(u8 *arg0) {
    func_80043500(arg0);
    func_80007328(&D_800D0510, *(s32 *)(arg0 + 0x20));
    func_800435D4(arg0);
    GeoRender_AdvanceFrameCounter();
    func_8003C6B8(*(s32 *)(arg0 + 0x18));
    return *(s32 *)((u8 *)(u32)*(u32 *)(arg0 + 0x20) + 8);
}

void func_800436CC(s32 value) { if (value >= 0 && value < 7) D_80094C60 = value; }


s32 func_800436E8(void) {
    return D_80094C60;
}
#endif
