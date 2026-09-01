#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82902FE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82903058.s")
#endif

#ifdef VERSION_US
extern u8 D_22E0;
extern u8 D_49B780;
extern u8 D_82919CE0;
void func_80003F74(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
extern void func_8290325C(void *);
extern void func_82903298(void *);
extern void func_829034D8();
extern void func_829035C4();
extern void func_8290367C();
extern u8 D_82919D48;
void func_80003F74(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_829031F4(void *arg0) {
    u8 *temp_a1;

    temp_a1 = ((s32) (((*(s16 *)((u8 *)(arg0) + (0x106C))) * 0x30) - 0x30 + &D_22E0) & 0xFFFFFF) + &D_49B780;
    func_80003F74(&D_82919CE0, temp_a1, temp_a1 + 0x30, 0);
}
#endif

#ifdef VERSION_US
extern void func_80041E2C(void);
extern void func_8003F018(s32);
extern s32 func_80041C98(s32);
void func_8290325C(void *arg0) {
    func_80041E2C();
    func_8003F018((s32)((u8 *)arg0 + 4));
    *(s32 *)arg0 = func_80041C98(5);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82903298.s")
#endif

#ifdef VERSION_US
extern f64 D_82917438;
extern f64 D_82917440;
void func_829033DC(f32 *arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    f64 temp_fv1;
    temp_fv0 = *arg0;
    *arg0 = ((arg1 - temp_fv0) * arg2) + temp_fv0;
    temp_fv1 = (f64)*(volatile f32 *)arg0;
    if ((temp_fv1 < D_82917438) && (D_82917440 < temp_fv1)) {
        *arg0 = 0.0f;
    }
}
#endif

#ifdef VERSION_US
s32 main_pool_get_available();
s32 MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(s32);
s32 func_80004B4C(s32, s32);
extern void func_829061CC(s32, s32, s32);
extern void main_pool_push_state(s32);
extern s32 D_82919D14;
extern s32 D_82919D24;
void func_82903444(void) {
    s32 sp1C;
    s32 sp18;
    s32 temp_v0;

    main_pool_push_state(0x53544144);
    sp18 = func_80004B4C(D_82919D14, D_82919D24);
    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    sp1C = temp_v0;
    func_829061CC(D_82919D24, temp_v0, sp18);
    MainPool_FinalizeAllocation(sp1C);
}
#endif

#ifdef VERSION_US
void func_829034B0(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (0x34))) = 20.0f;
    (*(f32 *)((u8 *)(arg0) + (0x38))) = 6400.0f;
    (*(f32 *)((u8 *)(arg0) + (0x2C))) = 45.0f;
}
#endif

#ifdef VERSION_US
extern u8 D_82918990[];
extern void *D_82919C38;
extern void *D_82919DC4;
extern void func_829034B0(void *);
extern void func_82903058(void *, s32);
void func_829034D8(void) {
    D_82919C38 = *(void **)((u8 *)D_82919DC4 + 0xC);
    func_829034B0(D_82919C38);
    func_82903058(D_82918990, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_8290351C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_829035C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_8290367C.s")
#endif

#ifdef VERSION_US
void func_8290379C(void *arg0) {
    func_829035C4();
    (*(s16 *)((u8 *)(arg0) + (0x1068))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x1072))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x1070))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x106C))) = -1;
    (*(s8 *)((u8 *)(&D_82919D48) + (0))) = 0;
    (*(f32 *)((u8 *)(&D_82919D48) + (4))) = 0.0f;
    (*(f32 *)((u8 *)(&D_82919D48) + (8))) = 0.0f;
    func_8290325C(arg0);
    func_82903298(arg0);
    func_8290367C();
    func_829034D8();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82903808.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_80094DB8[];
extern u8 D_80094D90[];
extern void Gfx_FillRectRgb(s16, s16, s16, s16, u8, u8, u8);
extern void Gfx_FillRectRgba(s16, s16, s16, s16, u8, u8, u8, u8);
void func_82903BA4(void) {
    gSPDisplayList(D_800D0510++, D_80094DB8);
    gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFE793C);
    gDPSetRenderMode(D_800D0510++, 0x00504240, 0);
    Gfx_FillRectRgba(0, 0x1C, 0x140, 4, 0, 0, 0, 0);
    Gfx_FillRectRgba(0, 0xD0, 0x140, 4, 0, 0, 0, 0);
    gSPDisplayList(D_800D0510++, D_80094D90);
    Gfx_FillRectRgb(0, 0, 0x140, 0x1E, 0, 0, 0);
    Gfx_FillRectRgb(0, 0xD2, 0x140, 0x1E, 0, 0, 0);
}
#endif

#ifdef VERSION_US
extern s32 D_82919C10;
extern void *D_82919D18;
extern u8 D_82911FDD[];
extern s32 D_82911FA0[];
extern s32 func_8004C990(s32, s32);
extern void func_829000CC(void);
extern void func_829000F8(s32, s32, s32, s32);
extern void func_829001E4(s32, s32, s32, s32);
extern void func_8004D19C(s32, s32, void *, s32, s32);
void func_82903CDC(void *arg0) {
    if (((u8 *)arg0)[0x18] & 1) {
        D_82919D18 = (void *)func_8004C990(0x43, ((s32 *)D_82911FA0)[((u8 *)D_82911FDD)[D_82919C10 * 0x14]]);
        func_829000CC();
        func_829000F8((s32)((u8 *)arg0)[1], (s32)((u8 *)arg0)[3], (s32)((u8 *)arg0)[5], (s32)((u8 *)arg0)[0x19]);
        func_829001E4((s32)((u8 *)arg0)[7], (s32)((u8 *)arg0)[9], (s32)((u8 *)arg0)[0xB], (s32)((u8 *)arg0)[0x19]);
        func_8004D19C((s16)(s32)*(f32 *)((u8 *)arg0 + 0xC) - ((s32)*(u16 *)D_82919D18 / 2), 0x10, D_82919D18, 0, 0);
    }
}
#endif

#ifdef VERSION_US
extern s32 D_82919C10;
extern void *D_82919D18;
extern u8 D_82911FDF[];
extern s32 D_82911FC0[];
extern s32 func_8004C990(s32, s32);
extern void func_829000CC(void);
extern void func_829000F8(s32, s32, s32, s32);
extern void func_829001E4(s32, s32, s32, s32);
extern void func_8004D19C(s32, s32, void *, s32, s32);
void func_82903DC0(void *arg0) {
    u8 *base;
    if (((u8 *)arg0)[0x18] & 1) {
        base = (u8 *)D_82911FDF;
        D_82919D18 = (void *)func_8004C990(0x43, ((s32 *)D_82911FC0)[base[D_82919C10 * 0x14]]);
        func_829000CC();
        func_829000F8(0xFF, 0xFF, 0xFF, 0xFF);
        func_829001E4(0xFF, 0, 0, 0xFF);
        func_8004D19C(0x1A, 9, D_82919D18, 0, 0);
    }
}
#endif

#ifdef VERSION_US
extern u8 D_82911FDE[];
extern s32 D_82911FB0[];
extern void *D_82919C14;
extern s32 func_8004C990(s32, s32);
extern void func_8004D19C(s32, s32, void *, s32, s32);
extern void func_829000CC(void);
extern void func_829000F8(s32, s32, s32, s32);
extern void func_829001E4(s32, s32, s32, s32);
void func_82903E70(void *arg0) {
    if (((u8 *)arg0)[0x18] & 1) {
        D_82919D18 = (void *)func_8004C990(0x43, ((s32 *)D_82911FB0)[((u8 *)D_82911FDE)[D_82919C10 * 0x14]]);
        func_829000CC();
        func_829000F8((s32)((u8 *)arg0)[1], (s32)((u8 *)arg0)[3], (s32)((u8 *)arg0)[5], (s32)((u8 *)arg0)[0x19]);
        func_829001E4((s32)((u8 *)arg0)[7], (s32)((u8 *)arg0)[9], (s32)((u8 *)arg0)[0xB], (s32)((u8 *)arg0)[0x19]);
        func_8004D19C((s16)(s32)*(f32 *)((u8 *)arg0 + 0xC) - ((s32)*(u16 *)D_82919D18 / 2), 0x2C, D_82919D18, 0, 0);
    }
}
#endif

#ifdef VERSION_US
extern s32 func_8004C990(s32, s32);
extern void func_8004D19C(s32, s32, void *, s32, s32);
extern void func_829000CC(void);
extern void func_829000F8(s32, s32, s32, s32);
extern void func_829001E4(s32, s32, s32, s32);
void func_82903F54(void *arg0) {
    if (((u8 *)arg0)[0x18] & 1) {
        D_82919D18 = (void *)func_8004C990(0x43, 4);
        func_829000CC();
        func_829000F8((s32)((u8 *)arg0)[1], (s32)((u8 *)arg0)[3], (s32)((u8 *)arg0)[5], (s32)((u8 *)arg0)[0x19]);
        func_829001E4((s32)((u8 *)arg0)[7], (s32)((u8 *)arg0)[9], (s32)((u8 *)arg0)[0xB], (s32)((u8 *)arg0)[0x19]);
        if (*(u16 *)D_82919C14 == 2) {
            func_8004D19C((s16)(s32)*(f32 *)((u8 *)arg0 + 0xC) - ((s32)*(u16 *)D_82919D18 / 2), 0x9E, D_82919D18, 0, 0);
            return;
        }
        func_8004D19C((s16)(s32)*(f32 *)((u8 *)arg0 + 0xC) - ((s32)*(u16 *)D_82919D18 / 2), 0xAC, D_82919D18, 0, 0);
    }
}
#endif

#ifdef VERSION_US
extern u8 D_82919D10;
extern u8 D_82917430[];
extern void func_8004C594(s32, s32);
extern s32 func_8004C8A0(void *, s32, s32, s32);
extern s32 func_80049148(s32, s32, s32);
extern void func_82903808(s32, s32, s32, s32, s32);
extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_800495F8(s32, s32, s32, void *, void *);
extern void func_800499EC(void);
void func_82904070(void) {
    s32 buffer[16];
    s32 value;
    if (*(u16 *)D_82919C14 == 2) {
        func_8004C594(3, D_82919D10);
        value = func_80049148(1, 0, func_8004C8A0(buffer, 0x40, 0x33, 0)) + 0xA;
        func_82903808(0xA0 - (value / 2), 0xD0, value, 0x10, 0x32);
        func_800498C4();
        func_800496A4(1, 0);
        func_80049148(1, 0, func_8004C8A0(buffer, 0x40, 0x33, 0));
        func_800495F8(0xA0, 0xD3, 1, D_82917430, buffer);
        func_800499EC();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82904160.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82904208.s")
#endif

#ifdef VERSION_US
extern f64 D_82917478;
extern f64 D_82917480;
void func_829042A4(f32 *arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    f64 temp_fv1;
    temp_fv0 = *arg0;
    *arg0 = ((arg1 - temp_fv0) * arg2) + temp_fv0;
    temp_fv1 = (f64)*(volatile f32 *)arg0;
    if ((temp_fv1 < D_82917478) && (D_82917480 < temp_fv1)) {
        *arg0 = 0.0f;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_8290430C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_829043B4.s")
#endif

void func_82904554(void) {
}

#ifdef VERSION_US
typedef struct S1_unk_D_86002F58_004_000_010_024 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ char unk02[0x6];
    /* 0x08 */ struct S1_unk_D_86002F58_004_000_004* unk_08;
} S1_unk_D_86002F58_004_000_010_024;
typedef union S1_arg1_func_80010CA8 {
    struct {
        /* 0x00 */ s16 unk_00;
        /* 0x02 */ s8 unk_02;
        /* 0x03 */ s8 unk_03;
    };
    u32 raw;
} S1_arg1_func_80010CA8;
typedef struct S1_unk_D_86002F58_004_000_010 {
    /* 0x00 */ u8 configFlags; // PokeIcon_AllocFramebuffers's arg0: bit0=frame-load enabled, bit1=background-load enabled, bit2=double-buffered, bit3=quad-buffered
    /* 0x01 */ u8 pendingFlags; // bit0=frame load pending, bit1=background load pending (PokeIcon_RequestFrameLoad/RequestBackgroundLoad/ApplyLoadResult)
    /* 0x02 */ u8 activeVariant; // index into framebuffers[], flipped by configFlags bit2 in PokeIcon_RequestFrameLoad
    /* 0x04 */ s32 framebuffers[1]; // declared size undersells - up to 5 entries when configFlags bit3 is set (PokeIcon_AllocFramebuffers)
    /* 0x08 */ char pad8[0x10];
    /* 0x18 */ s32 backgroundBuffer; // PokeIcon_RequestBackgroundLoad's poolPtr
    /* 0x1C */ s32 frameResultSize; // PokeIcon_ApplyLoadResult's case 1: poolSize
    /* 0x20 */ s32 backgroundResultSize; // case 2: poolSize
    /* 0x24 */ S1_unk_D_86002F58_004_000_010_024* lastLoadedFragment; // case 1: result; PokeIcon_RequestFrameLoad reuses the load if this matches the requested species
    /* 0x28 */ s32 backgroundResult; // case 2: result
    /* 0x2C */ S1_arg1_func_80010CA8 colorAdjust; // cached alongside lastLoadedFragment for the reuse check
    /* 0x30 */ OSMesgQueue frameQueue;
    /* 0x48 */ OSMesg frameMsgBuf;
    /* 0x4C */ char pad4C[0x4];
    /* 0x50 */ OSMesgQueue backgroundQueue;
    /* 0x68 */ OSMesg backgroundMsgBuf;
    /* 0x6C */ char pad6C[0x4];
} S1_unk_D_86002F58_004_000_010;
typedef struct S1_unk_D_86002F58_004_000_004 {
    /* 0x00 */ struct S1_unk_D_86002F58_004_000_004* unk_00[4];
    /* 0x10 */ struct S1_unk_D_86002F58_004_000_00C* unk_10;
    /* 0x14 */ S1_unk_D_86002F58_004_000_010* unk_14;
} S1_unk_D_86002F58_004_000_004;
typedef struct S1_unk_D_86002F58_004_000_00C_028 {
    /* 0x00 */ char pad0[4];
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char pad6[6];
    /* 0x0C */ s32* unk_0C;
    /* 0x10 */ s32* unk_10;
} S1_unk_D_86002F58_004_000_00C_028;
typedef S1_unk_D_86002F58_004_000_00C_028* (*S1_unk_D_86002F58_004_000_00C_028_func)(s32, s32);
typedef struct S1_unk_D_86002F58_004_000_00C {
    /* 0x00 */ S1_unk_D_86002F58_004_000_004 unk_00;
    /* 0x18 */ char unk_18[0x10];
    /* 0x28 */ S1_unk_D_86002F58_004_000_00C_028_func unk_28;
} S1_unk_D_86002F58_004_000_00C;
typedef struct S1_unk_D_86002F58_004_000_000 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ struct S1_unk_D_86002F58_004_000_000* unk_04;
    /* 0x08 */ struct S1_unk_D_86002F58_004_000_000* unk_08;
    /* 0x0C */ S1_unk_D_86002F58_004_000_00C* unk_0C;
    /* 0x10 */ S1_unk_D_86002F58_004_000_010* unk_10;
    /* 0x14 */ s32 unk_14;
} S1_unk_D_86002F58_004_000_000;
typedef struct S1_Vec3s {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} S1_Vec3s;
typedef struct S1_Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} S1_Vec3f;
typedef union S1_Color_RGBA8_u32 {
        u8 r, g, b, a;
    u32 rgba;
} S1_Color_RGBA8_u32;
typedef struct S1_unk_D_86002F58_004_000_040_004 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ u32 unk_14;
    /* 0x18 */ u32 unk_18;
} S1_unk_D_86002F58_004_000_040_004;
typedef struct S1_unk_D_86002F58_004_000_040 {
    /* 0x04 */ S1_unk_D_86002F58_004_000_040_004* unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x10 */ char unk10[0x2];
    /* 0x12 */ u16 unk_12;
} S1_unk_D_86002F58_004_000_040;
typedef struct S1_unk_D_86002F58_004_000_054_004 {
    /* 0x02 */ char unk_02[0x2];
    /* 0x0C */ void* unk_0C;
    /* 0x10 */ void* unk_10;
} S1_unk_D_86002F58_004_000_054_004;
typedef struct S1_unk_D_86002F58_004_000_054 {
    /* 0x04 */ S1_unk_D_86002F58_004_000_054_004* unk_04;
    /* 0x08 */ s16 unk_08;
} S1_unk_D_86002F58_004_000_054;
typedef float S1_MtxF_t[4][4];
typedef union {
    S1_MtxF_t mf;
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
} S1_MtxF;
typedef struct S1_unk_D_86002F58_004_000_0A8 {
    /* 0x04 */ S1_Vec3f unk_04;
} S1_unk_D_86002F58_004_000_0A8;
typedef struct S1_unk_D_86002F58_004_000 {
    /* 0x000 */ S1_unk_D_86002F58_004_000_000 unk_000;
    /* 0x018 */ s16 animType; // Model_InitDisplayObject's arg1
    /* 0x01A */ s16 modelId; // Model_InitDisplayObject's arg2; a species id in most battle-scene consumers
    /* 0x01C */ u8 textureMode; // Model_SetMaterialTextureMode
    /* 0x01D */ u8 materialAlpha; // Model_SetMaterialAlpha
    /* 0x01E */ S1_Vec3s unk_01E;			//	total Rotation
    /* 0x024 */ S1_Vec3f unk_024;			//	global Position
    /* 0x030 */ S1_Vec3f unk_030;			//	scale
    /* 0x03C */ S1_Color_RGBA8_u32 unk_03C;
    /* 0x040 */ S1_unk_D_86002F58_004_000_040 unk_040;
    /* 0x054 */ S1_unk_D_86002F58_004_000_054 unk_054;
    /* 0x060 */ S1_MtxF unk_060;
    /* 0x0A0 */ S1_Color_RGBA8_u32 unk_0A0;    //  vertex color ?
    /* 0x0A4 */ char unk0A4[2];
    /* 0x0A6 */ u8 poolIndex; // stable index into the shared displayObjectPool; GeoRender_RecordAnchorPosition/etc.
    /* 0x0A7 */ u8 anchorCount; // GeoRender_RecordAnchorPosition/FindAnchorPosition; caps at 0xC (12)
    /* 0x0A8 */ S1_unk_D_86002F58_004_000_0A8 anchors[1]; // declared size undersells - indexed up to anchorCount (max 12)
    /* 0x0B8 */ char unk0B8[0x24];
    /* 0x0DC */ S1_Vec3f unk_0DC;
    /* 0x0E0 */ char unk0E0[0x4];
    /* 0x0EC */ S1_Vec3f unk_0EC;
    /* 0x0F8 */ char unk0F8[0x4];
    /* 0x0FC */ S1_Vec3f unk_0FC;
    /* 0x108 */ char unk108[0x60];
} S1_unk_D_86002F58_004_000;
s32 Intro_StepRotationOvershoot(S1_unk_D_86002F58_004_000* arg0, s16 arg1, s16 arg2) {
    if (arg1 > 0) {
        arg0->unk_01E.y -= arg1;
        if ((arg0->unk_01E.y < arg2) && ((arg2 - arg1) < arg0->unk_01E.y)) {
            return 1;
        }
    } else {
        arg0->unk_01E.y -= arg1;
        if ((arg2 < arg0->unk_01E.y) && (arg0->unk_01E.y < (arg2 - arg1))) {
            return 1;
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_829045E4(void *arg0, s16 arg1, s16 arg2) {
    s16 current;
    s16 after;
    s32 delta;
    s32 quotient;
    current = *(s16 *)((u8 *)arg0 + 0x20);
    delta = current - arg2;
    quotient = delta / 182;
    if ((quotient >= -0x168) && (quotient < -0x149)) {
        arg1 = (s16)((s16)(delta + 0x10000) / 4);
    }
    *(s16 *)((u8 *)arg0 + 0x20) = current - arg1;
    if (arg1 > 0) {
        after = *(s16 *)((u8 *)arg0 + 0x20);
        if ((arg2 >= after) && (after >= (arg2 - arg1))) {
            *(s16 *)((u8 *)arg0 + 0x20) = arg2;
            return 1;
        }
    } else {
        after = *(s16 *)((u8 *)arg0 + 0x20);
        if ((after >= arg2) && ((arg2 - arg1) >= after)) {
            *(s16 *)((u8 *)arg0 + 0x20) = arg2;
            return 1;
        }
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_829046A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82904794.s")
#endif

#ifdef VERSION_US
extern void *D_82919A08;
extern void func_829046A8(void);
extern void func_82904794(void);
extern void func_800226C0(s32);
void func_82904824(void *arg0) {
    ((u8 *)arg0)[5] &= 0xFFFE;
    ((u8 *)D_82919A08)[1] |= 1;
    func_829046A8();
    func_82904794();
    if (*(f32 *)((u8 *)D_82919A08 + 0x28) == 0.0f) {
        *(s16 *)((u8 *)arg0 + 0x1068) = 8;
        func_800226C0(0x7B);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_829048A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82904AC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82904C28.s")
#endif

#ifdef VERSION_US
extern u8 D_82919A88[];
extern u8 D_82919AF8[];
extern u8 D_82919B68[];
extern u8 D_82919B80;
extern void func_82904AC8(void *, void *, u16, u16, s32, s32, s32, s32, s32);
void func_82904D78(s32 arg0) {
    func_82904AC8(&D_82919A88, &D_82919A88, 0xFF, 0xFF, 0xFF, 0, 0x64, 0xFF, 0x14);
    func_82904AC8(&D_82919AF8, &D_82919AF8, 0xFF, 0xFF, 0xFF, 0, 0x64, 0xFF, 0x14);
    if (!(D_82919B80 & 2)) {
        func_82904AC8(&D_82919B68, &D_82919B68, 0xFF, 0xFF, 0xFF, 0xFF, 0xC8, 0, 0x14);
        return;
    }
    func_82904AC8(&D_82919B68, &D_82919B68, 0xFF, 0xFF, 0xFF, 0, 0x64, 0xFF, 0x14);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82904E9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82904F78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82905078.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_829050C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_829051AC.s")
#endif

#ifdef VERSION_US
extern void *D_80087200;
extern void func_80064D28(void);
extern void func_829050C8(void *);
extern void func_82904208(void);
void func_829053F8(void) {
    s32 var_s0;
    var_s0 = 1;
    do {
        func_80064D28();
        func_829050C8(D_82918990);
        if ((*(u16 *)((u8 *)D_80087200 + 8) & 0xD000) && (*(s16 *)((u8 *)D_82918990 + 0x1068) == 0xA)) {
            var_s0 = 0;
        }
        func_82904208();
    } while (var_s0 != 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_82905488.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_829054F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33FAE0/func_829056A4.s")
#endif
