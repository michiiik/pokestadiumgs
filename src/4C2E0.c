#include "global.h"


#ifdef VERSION_US
extern void _bcopy(u8 *, u8 *, s32);
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
s32 func_800356CC(s32 arg0);
s32 func_8004C4A4(void);
extern u8 *func_800042C0(u8 *, u8 *, s32, s32);
extern u8 D_801270B0;
s32 func_8004B6E0(void) {
    s32 pad_frame[2];
    s32 sp1C;
    u8 *sp18;
    s32 temp_v0;

    temp_v0 = func_800356CC(0xA);
    sp1C = temp_v0;
    sp18 = temp_v0 + 0xFD0;
    func_8004C4A4();
    main_pool_push_state(0x504D4442);
    _bcopy(func_800042C0((u8 *) sp1C, sp18, 0, 0), &D_801270B0, 0xFD0);
    main_pool_pop_state(0x504D4442);
    return 0;
}

s32 func_8004B754(s32 a) {
    s32 r = -1;
    if (a > 0 && a <= 0xfd)
        r = a - 1;
    else if (a >= 0xfe && a <= 0x116)
        r = 0xc8;
    else if (a == 0x117)
        r = 0x18;
    return r;
}

extern s32 func_8004C874(s32, s32);
s32 func_8004B7A4(s32 arg0) {
    s32 result = 0;
    s32 value = func_8004B754(arg0);
    if (value >= 0) {
        result = func_8004C874(0, value);
    }
    return result;
}

typedef struct { f32 x, y, z; } FleetVec3f4C2E0;
typedef struct { s16 x, y, z; } FleetVec3s4C2E0;
extern FleetVec3f4C2E0 D_800948D0;
extern u8 D_801270BC[];
extern FleetVec3f4C2E0 *Vec3f_FromVec3s(FleetVec3f4C2E0 *, FleetVec3s4C2E0 *);
extern FleetVec3s4C2E0 *Vec3s_FromVec3f(FleetVec3s4C2E0 *, FleetVec3f4C2E0 *);
extern s32 func_8004B754(s32 a);
s32 func_8004B7E0(s32 arg0, FleetVec3f4C2E0 *arg1) {
    s32 result = 0;
    s32 value;
    u32 packed;
    FleetVec3s4C2E0 vec;
    value = func_8004B754(arg0);
    *arg1 = D_800948D0;
    if (value >= 0) {
        packed = *(u32 *)((u8 *)D_801270BC + (value * 16));
        vec.x = (s16)(packed >> 16) >> 6;
        vec.y = (s16)(packed >> 6) >> 4;
        vec.z = (s16)(packed << 6) >> 6;
        Vec3f_FromVec3s(arg1, &vec);
        result = 1;
    }
    return result;
}

f32 func_8004B888(s32 arg0) {
    f32 result = 1.0f;
    s32 value = func_8004B754(arg0);
    if (value >= 0) {
        result = (f32)*(s16 *)((u8 *)&D_801270B0 + (value << 4)) / 100;
    }
    return result;
}

extern u8 D_801270B2[];
s32 func_8004B8E4(s32 arg0) {
    s32 result = 0;
    s32 value = func_8004B754(arg0);
    if (value >= 0) {
        result = D_801270B2[value << 4];
    }
    return result;
}

extern u8 D_801270B8[];
extern u8 D_801270BA[];
s16 func_8004B920(s32 arg0, s32 arg1) {
    s16 result = 0;
    s32 value = func_8004B754(arg0);
    if (value >= 0) {
        switch (arg1) {
        case 0:
            result = *(s16 *)((u8 *)(u32)D_801270B8 + (value * 16));
            break;
        case 1:
            result = *(s16 *)((u8 *)(u32)D_801270BA + (value * 16));
            break;
        }
        }
    return result;
}

extern u8 D_801270B4[];
s32 func_8004B98C(s32 arg0) {
    s32 result = 0;
    s32 value = func_8004B754(arg0);
    if (value >= 0) {
        result = *(s32 *)(D_801270B4 + (value << 4));
        if (result != -1) {
            result = 2;
        } else {
            result = 1;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004B9E0.s")

extern u8 D_801270B3[];
s32 func_8004BA34(s32 arg0) {
    s16 result = 0;
    s32 value = func_8004B754(arg0);
    if (value >= 0) {
        result = D_801270B3[value << 4];
    }
    return result;
}

extern u8 *Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern u8 D_447D00[];
extern u8 D_4488E0[];
extern u8 D_4494C0[];
u8 *func_8004BA70(s32 arg0) {
    u8 *result;

    result = 0;
    switch (arg0) {
    case 0:
        result = Asset_LoadToSegment(0, D_447D00, D_4488E0, 0);
        break;
    case 1:
        result = Asset_LoadToSegment(0, D_4488E0, D_4494C0, 0);
        break;
    }
    return result;
}

f32 func_8004BAE8(s32 arg0, s32 arg1) {
    f32 result = 1.0f;
    s32 value = func_8004B754(arg1);
    if ((arg0 != 0) && (value >= 0)) {
        result = (f32)*(s16 *)((u8 *)((value * 0xC) + arg0)) / 100;
    }
    return result;
}

s16 func_8004BB58(s32 arg0, s32 arg1) {
    s16 result = 0;
    s32 value = func_8004B754(arg1);
    if ((arg0 != 0) && (value >= 0)) {
        result = *(s16 *)((u8 *)((value * 0xC) + arg0) + 2);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BBA8.s")

s32 func_8004BC6C(s32 arg0, s32 arg1) {
    s16 result = 0;
    s32 value = func_8004B754(arg1);
    if ((arg0 != 0) && (value >= 0)) {
        result = *(u8 *)((u8 *)((value * 0xC) + arg0) + 8);
    }
    return result;
}

extern s32 func_8004B754(s32 a);
void func_8004BCBC(s32 arg0, s32 arg1) {
    s32 value = func_8004B754(arg0);
    struct { FleetVec3s4C2E0 vec; s16 pad[3]; } storage;
    if (value >= 0) {
        Vec3s_FromVec3f(&storage.vec, (FleetVec3f4C2E0 *)(u32)arg1);
        *((s32 *)(D_801270BC + (value << 4))) =
            ((((unsigned short)(storage.vec.x ^ 0)) << 22) |
             ((storage.vec.y & 0xFFF) << 10)) | (storage.vec.z & 0x3FF);
    }
}

void func_8004BD28(s32 arg0, f32 arg1) {
    s32 value = func_8004B754(arg0);
    if (value >= 0) {
        *(s16 *)((u8 *)&D_801270B0 + (value << 4)) = (s16)(arg1 * 100.0f);
    }
}

extern s32 func_8004B754(s32);
void func_8004BD78(s32 a, s16 b) {
    s32 i = func_8004B754(a);
    if (i >= 0)
        D_801270B3[i << 4] = (u8)b;
}

void func_8004BDB0(s32 arg0, s32 arg1, s16 arg2) {
    s32 value = func_8004B754(arg0);
    if (value >= 0) {
        switch (arg1) {
        case 0:
            *(s16 *)((u8 *)(u32)D_801270B8 + (value << 4)) = arg2;
            break;
        case 1:
            *(s16 *)((u8 *)(u32)D_801270BA + (value << 4)) = arg2;
            break;
        }
    }
}

void func_8004BE18(s32 a, s32 b) {
    s32 i = func_8004B754(a);
    if (i >= 0)
        *(s32 *)(D_801270B4 + (i << 4)) = b;
}

extern void Dma_CopyChunks(s32 *, s32, s32);
s32 func_800356CC(s32);

void func_8004BE50(void) {
    s32 temp_v0;

    temp_v0 = func_800356CC(0xA);
    Dma_CopyChunks(&D_801270B0, temp_v0, temp_v0 + 0xFD0);
}

void func_8004BE84(s32 arg0, s32 arg1, f32 arg2) {
    s32 value = func_8004B754(arg1);
    if ((arg0 != 0) && (value >= 0)) {
        *(s16 *)((u8 *)((value * 0xC) + arg0)) = (s16)(arg2 * 100.0f);
    }
}

s32 func_8004B754(s32);
void func_8004BEEC(s32 arg0, s32 arg1, s16 arg2) {
    s32 temp_v0;

    temp_v0 = func_8004B754(arg1);
    if ((arg0 != 0) && (temp_v0 >= 0)) {
        (*(s16 *)((u8 *)(((temp_v0 * 0xC) + arg0)) + (2))) = arg2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4C2E0/func_8004BF3C.s")

void func_8004BFC4(s32 arg0, s32 arg1, s16 arg2) {
    s32 temp_v0;

    temp_v0 = func_8004B754(arg1);
    if ((arg0 != 0) && (temp_v0 >= 0)) {
        (*(s8 *)((u8 *)(((temp_v0 * 0xC) + arg0)) + (8))) = (s8) arg2;
    }
}
#endif
