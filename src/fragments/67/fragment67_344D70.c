#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908270.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908370.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908470.s")
#endif

void func_829084DC(void) {
}

#ifdef VERSION_US
extern u8 D_82912F84;
extern u8 D_8291B838;

void func_829084E4(s32 arg0) {
    void *temp_v0;

    temp_v0 = (arg0 * 0x10) + &D_82912F84;
    (*(s32 *)((u8 *)(&D_8291B838) + (0))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0)));
    (*(s32 *)((u8 *)(&D_8291B838) + (4))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (4)));
    (*(s32 *)((u8 *)(&D_8291B838) + (8))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (8)));
    (*(s32 *)((u8 *)(&D_8291B838) + (0xC))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0xC)));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908520.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908594.s")
#endif

#ifdef VERSION_US
extern void func_82908520();
extern s16 D_8291B862;

void func_82908608(void) {
    func_82908520();
    D_8291B862 += 1;
}
#endif

void func_82908638(void) {
}

#ifdef VERSION_US
extern u8 D_829130A8;
extern u8 D_8291B848;

void func_82908640(s32 arg0) {
    void *temp_v0;

    temp_v0 = (arg0 * 0x10) + &D_829130A8;
    (*(s32 *)((u8 *)(&D_8291B848) + (0))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0)));
    (*(s32 *)((u8 *)(&D_8291B848) + (4))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (4)));
    (*(s32 *)((u8 *)(&D_8291B848) + (8))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (8)));
    (*(s32 *)((u8 *)(&D_8291B848) + (0xC))) = (s32) (*(s32 *)((u8 *)(temp_v0) + (0xC)));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290867C.s")
#endif

void func_829086F0(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_829086F8.s")
#endif

#ifdef VERSION_US
extern void func_8290867C(void);
void func_829087C0(void) {
    func_8290867C();
}
#endif

#ifdef VERSION_US
extern void func_8290E014(void);
void func_829087E0(void) {
    func_8290E014();
}
#endif

#ifdef VERSION_US
extern void GfxImage_FillCurrent(s32 *, s32);
extern void func_80008648();
extern void func_800088DC();
extern void func_8003C6B8(s32);
extern void GeoRender_AdvanceFrameCounter();
extern u8 D_800D0510;
extern s32 D_8291B868;
void func_82908800(void) {
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 1);
    GeoRender_AdvanceFrameCounter();
    func_8003C6B8(D_8291B868);
    func_829087E0();
    func_80008648();
}
#endif

#ifdef VERSION_US
extern void func_800086A4(s32);
extern void func_800355E4(s32);
extern void func_80007AEC(s32);
extern s32 D_8291B864;
void func_82908854(void) {
    func_800086A4(0x14);
    func_800355E4(0x51);
    func_80007AEC(0x10);
    D_8291B864 = 1;
}
#endif

#ifdef VERSION_US
extern void func_80064D28();
void func_8290888C(void) {
    if (D_8291B864 != 0) {
        do {
            func_80064D28();
            func_82908608();
            func_829087C0();
            func_82908800();
        } while (D_8291B864 != 0);
    }
}
#endif

#ifdef VERSION_US
extern void StageFade_StartFromTransparent(s32);
extern void func_800225C4(s32);
void func_829088EC(void) {
    s32 var_s0;

    StageFade_StartFromTransparent(0x10);
    func_800225C4(0x10);
    var_s0 = 0;
    do {
        func_82908608();
        func_829087C0();
        func_82908800();
        var_s0 += 1;
    } while (var_s0 != 0x10);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290894C.s")
#endif

#ifdef VERSION_US
extern void func_80006CD0(s32, s32);
s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_80008514(s32);
extern void func_80008574();
extern void func_8004C8C0(s32);
extern void func_8290894C();
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
extern u8 D_446E30;
extern s32 func_80047588(s32 arg0, s32 arg1);
extern void func_8004C09C(s32 arg0);
s32 func_8004DDF4(s32 arg0);
u8 *Asset_LoadToSegment(s32 id, u8 *rom_start, u8 *rom_end, s32 arg3);
extern u8 D_1000000[];
extern u8 D_447D00[];
void func_80047610(void);
void Gfx_FreeDisplayListBuffers(void);
void func_8004C398(void);
s32 func_800082E0(s32, s32, s32, s32, s32, s32);
s32 func_8004DDF4(s32 arg0);
u8 *Asset_LoadToSegment(s32 id, u8 *rom_start, u8 *rom_end, s32 arg3);
void func_80047610(void);
void Gfx_FreeDisplayListBuffers(void);
void func_8004C398(void);
s32 func_82908A54(s32 arg0, s32 arg1) {
    s32 sp24;

    main_pool_push_state(0x454E44);
    func_80006CD0(0x18000, 0);
    sp24 = func_800082E0(0, 1, 3, 1, 2, 1);
    func_80047588(6, 0);
    func_8004C09C(0x21);
    func_8004C8C0(0xC1);
    func_8004DDF4(0xA6);
    Asset_LoadToSegment((s32) ((u32) ((s32) D_1000000 & 0x0F000000) >> 0x18), &D_446E30, D_447D00, 0);
    func_8290894C();
    func_80008514(sp24);
    func_82908854();
    func_8290888C();
    func_829088EC();
    func_80008574();
    func_80047610();
    Gfx_FreeDisplayListBuffers();
    func_8004C398();
    main_pool_pop_state(0x454E44);
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908B60.s")
#endif

#ifdef VERSION_US
extern f32 Math_StepToF(f32, f32, f32, f32);
void func_82908BD8(f32 *arg0, f32 *arg1, f32 *arg2, s16 arg3) {
    f32 stepX;
    f32 stepY;
    f32 stepZ;

    stepX = (arg1[0] - arg2[0]) / (f32)arg3;
    stepY = (arg1[1] - arg2[1]) / (f32)arg3;
    stepZ = (arg1[2] - arg2[2]) / (f32)arg3;
    if (stepX < 0.0f) stepX *= -1.0f;
    if (stepY < 0.0f) stepY *= -1.0f;
    if (stepZ < 0.0f) stepZ *= -1.0f;
    arg0[0] = Math_StepToF(arg0[0], arg1[0], stepX, stepX);
    arg0[1] = Math_StepToF(arg0[1], arg1[1], stepY, stepY);
    arg0[2] = Math_StepToF(arg0[2], arg1[2], stepZ, stepZ);
}
#endif

#ifdef VERSION_US
extern f32 Math_StepToF(f32, f32, f32, f32);
void func_82908CF4(f32 *arg0, f32 *arg1, f32 *arg2, s16 arg3) {
    f32 stepX;
    f32 stepY;
    f32 stepZ;
    f32 stepW;

    stepX = (arg1[0] - arg2[0]) / (f32)arg3;
    stepY = (arg1[1] - arg2[1]) / (f32)arg3;
    stepZ = (arg1[2] - arg2[2]) / (f32)arg3;
    stepW = (arg1[3] - arg2[3]) / (f32)arg3;
    if (stepX < 0.0f) stepX *= -1.0f;
    if (stepY < 0.0f) stepY *= -1.0f;
    if (stepZ < 0.0f) stepZ *= -1.0f;
    if (stepW < 0.0f) stepW *= -1.0f;
    arg0[0] = Math_StepToF(arg0[0], arg1[0], stepX, stepX);
    arg0[1] = Math_StepToF(arg0[1], arg1[1], stepY, stepY);
    arg0[2] = Math_StepToF(arg0[2], arg1[2], stepZ, stepZ);
    arg0[3] = Math_StepToF(arg0[3], arg1[3], stepW, stepW);
}
#endif

#ifdef VERSION_US
void func_82908E50(f32 *arg0, f32 *arg1) { arg0[0] = arg1[0]; arg0[1] = arg1[1]; arg0[2] = arg1[2]; }
#endif

#ifdef VERSION_US
void func_82908E6C(f32 *arg0, const f32 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
    arg0[3] = arg1[3];
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908E90.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908F60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_829090A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82909170.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_829092AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290954C.s")
#endif

#ifdef VERSION_US
extern void func_8004B7E0(void);
void func_8290A0B0(void) {
    func_8004B7E0();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290A0D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290A208.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290A2FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290A358.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290A3C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290A5B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290A6F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290A81C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290A920.s")
#endif

#ifdef VERSION_US
extern u8 D_8291B831;
extern u8 D_8291A964;
extern void func_8290A920(s32, s32);
extern void func_8290A208(s32);
void func_8290AB10(s32 arg0) {
    s32 i;

    D_8291B831 = 0;
    i = 1;
    if (arg0 >= 2) {
        u8 *record;
        record = &D_8291A964;
        do {
            func_8290A920(i, i);
            func_8290A208(i);
            record += 0x1A4;
            record[-0x19E] = record[-0x19E] | 0x10;
            record[-0x19F] = record[-0x19F] & -2;
            record[-2] = 1;
            i++;
        } while (i != arg0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290ABB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290AC2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290ACA8.s")
#endif

#ifdef VERSION_US
extern void func_80007AEC(s32);
extern void func_8290E2A8(void);
extern void func_8290A5B0(s32);
extern u8 D_8291A960;
extern u8 D_8291AB04;
extern u8 D_8291ACA8;
extern u8 D_8291AE4C;
extern s32 D_8291B858;
extern s32 D_82912F80;
void func_8290ADD0(void) {
    func_80007AEC(8);
    func_8290E2A8();
    func_8290A5B0(4);
    *(s16 *)&D_8291A960 = 0;
    *(s16 *)&D_8291AB04 = 0;
    *(s16 *)&D_8291ACA8 = 0;
    *(s16 *)&D_8291AE4C = 0;
    *(s32 *)((u8 *)&D_8291B838 + (D_8291B858 * 4)) = D_82912F80;
}
#endif

#ifdef VERSION_US
void func_8290AE3C(void) {
    func_80007AEC(8);
    func_8290E2A8();
    func_8290A5B0(3);
    *(s16 *)&D_8291A960 = 0;
    *(s16 *)&D_8291AB04 = 0;
    *(s16 *)&D_8291ACA8 = 0;
    *(s16 *)&D_8291AE4C = 0;
    *(s32 *)((u8 *)&D_8291B838 + (D_8291B858 * 4)) = D_82912F80;
}
#endif

#ifdef VERSION_US
extern void func_8290A5B0(s32);
extern s32 D_8291B858;
extern s32 D_82912F80;
void func_8290AEA8(void) {
    func_80007AEC(8);
    func_8290A5B0(2);
    *(s32 *)((u8 *)&D_8291B838 + (D_8291B858 * 4)) = D_82912F80;
}
#endif

#ifdef VERSION_US
extern void func_80007AEC(s32);
extern void func_8290A5B0(s32);
extern u8 D_8291A7E1;
extern u8 D_8291A985;
extern u8 D_8291AB29;
extern u8 D_8291ACCD;
extern s32 D_8291B858;
extern s32 D_82912F80;
void func_8290AEEC(void) {
    func_80007AEC(8);
    func_8290A5B0(4);
    D_8291A7E1 = 0;
    D_8291A985 = 0;
    D_8291AB29 = 0;
    D_8291ACCD = 0;
    *(s32 *)((u8 *)&D_8291B838 + (D_8291B858 * 4)) = D_82912F80;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290AF50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B004.s")
#endif

#ifdef VERSION_US
extern s16 D_8291B828;
extern u8 D_829131EC;
extern u8 D_829131F8;
extern u8 D_82913204;
extern u8 D_8291A7C0;
extern u8 D_8291A7C4;
extern u8 D_8291A960;
extern s16 D_8291B874;
extern s16 D_8291B876;
extern s16 D_8291B878;
extern u8 D_8291B838;
extern s32 D_8291B858;
extern s32 D_82912F80;
extern void func_80007AEC(s32);
extern void func_8290A5B0(s32);
extern void func_8003F2C4(s32, s32, s32);
extern void ModelAnim_SetFrame(u8 *, s16);
extern void func_8290AB10(s32);
void func_8290B098(void) {
    s16 mode;
    u8 *config;

    mode = D_8291B828;
    if (mode == 0x24) {
        config = &D_829131EC;
    }
    if (mode == 0x25) {
        config = &D_829131F8;
    }
    if (mode == 0x26) {
        config = &D_82913204;
    }
    func_80007AEC(8);
    func_8290A5B0(1);
    func_8003F2C4(*(s32 *)&D_8291A7C0, (s32)&D_8291A7C4, config[0]);
    ModelAnim_SetFrame(&D_8291A7C4, config[1]);
    *(s16 *)&D_8291A960 = 0;
    func_8290AB10(6);
    *(s16 *)&D_8291B874 = *(s16 *)(config + 4);
    *(s16 *)&D_8291B876 = *(s16 *)(config + 6);
    *(s16 *)&D_8291B878 = *(s16 *)(config + 8);
    *(s32 *)((u8 *)&D_8291B838 + D_8291B858 * 4) = D_82912F80;
}
#endif

#ifdef VERSION_US
extern void func_80007AEC(s32);
extern void func_8290A2FC(void);
extern void func_8290ACA8(void);
extern void func_8290A5B0(s32);
extern u8 D_8291A7C0;
extern s32 D_8291B858;
extern s32 D_82912F80;
void func_8290B184(void) {
    u8 *base;

    func_80007AEC(8);
    func_8290A2FC();
    func_8290ACA8();
    func_8290A5B0(3);
    base = (u8 *)&D_8291A7C0;
    *(s16 *)(base + 0x1A0) = 0;
    *(u8 *)(base + 5) &= 0xFFFE;
    *(u8 *)(base + 0x1A9) &= 0xFFFE;
    *(u8 *)(base + 0x34D) &= 0xFFFE;
    *(u8 *)(base + 0x4F1) &= 0xFFFE;
    *(u8 *)(base + 0x21) = 0;
    *(u8 *)(base + 0x1C5) = 0;
    *(u8 *)(base + 0x369) = 0;
    *(s32 *)((u8 *)&D_8291B838 + (D_8291B858 * 4)) = D_82912F80;
}
#endif

#ifdef VERSION_US
extern void func_8290A81C(s32);
void func_8290B220(void) {
    func_80007AEC(8);
    func_8290A81C(3);
    *(s32 *)((u8 *)&D_8291B838 + (D_8291B858 * 4)) = D_82912F80;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B264.s")
#endif

#ifdef VERSION_US
extern u8 D_8291B831;

s32 func_8290B3BC(void) {
    if (D_8291B831 == 0xE) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US

s32 func_8290B3E4(void) {
    if (D_8291B831 == 0x1A) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B40C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B478.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B5A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B76C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B934.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290BADC.s")
#endif

#ifdef VERSION_US
extern void ModelAnim_SetFrame(u8 *, s16);
void func_8290BC84(u8 *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = *(u16 *)(*(u8 **)(arg0 + 0x44) + 0xA);
    ModelAnim_SetFrame(arg0, (s16)((((arg1 / temp_v0) + 1) * temp_v0) - arg1));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290BCF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290BEEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290C0F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290C2A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290C45C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290C6D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290C908.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290CB2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290CD54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290CFD8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290D124.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290D42C.s")
#endif

#ifdef VERSION_US

void func_8290D72C(void) {
    D_8291B864 = 0;
}
#endif

#ifdef VERSION_US
extern s32 D_8291A380;
extern s16 D_8291B85C;
extern s16 D_8291B85E;
extern s16 D_8291B860;
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290D738(void) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 30.0f, 0.0f);
    D_8291B85C = 0;
    D_8291B85E = 0;
    D_8291B860 = 0xBE;
    func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E);
}
#endif

#ifdef VERSION_US
extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290D7C8(void) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 15.0f, 0.0f);
    D_8291B85C = 0;
    D_8291B85E = 0;
    D_8291B860 = 0x96;
    func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E);
}
#endif

#ifdef VERSION_US
extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290D858(void) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 15.0f, 0.0f);
    D_8291B85C = 0;
    D_8291B85E = 0x1A00;
    D_8291B860 = 0x5A;
    func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E);
}
#endif

#ifdef VERSION_US
extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290D8EC(void) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 15.0f, 0.0f);
    D_8291B85C = 0;
    D_8291B85E = -0x1A00;
    D_8291B860 = 0x5A;
    func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E);
}
#endif

#ifdef VERSION_US
extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290D980(void) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 15.0f, 0.0f);
    D_8291B85C = 0;
    D_8291B85E = 0;
    D_8291B860 = 0x8C;
    func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E);
}
#endif

#ifdef VERSION_US
extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290DA10(void) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 15.0f, 0.0f);
    D_8291B85C = 0x1900;
    D_8291B85E = 0x1900;
    D_8291B860 = 0x82;
    func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E);
}
#endif

#ifdef VERSION_US
extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290DAA4(void) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 15.0f, 0.0f);
    D_8291B85C = -0x1700;
    D_8291B85E = -0x1400;
    D_8291B860 = 0x96;
    func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E);
}
#endif

#ifdef VERSION_US
extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290DB3C(void) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 15.0f, 0.0f);
    D_8291B85C = 0x1900;
    D_8291B85E = 0;
    D_8291B860 = 0x8C;
    func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E);
}
#endif

#ifdef VERSION_US
extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290DBD0(void) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 15.0f, 0.0f);
    D_8291B85C = 0;
    D_8291B85E = 0;
    D_8291B860 = 0x96;
    func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E);
}
#endif

#ifdef VERSION_US
extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290DC60(void) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 15.0f, 0.0f);
    D_8291B85C = 0;
    D_8291B85E = 0;
    D_8291B860 = 0xB4;
    func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E);
}
#endif

#ifdef VERSION_US
extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290DCF0(void) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 15.0f, 0.0f);
    D_8291B85C = 0;
    D_8291B85E = 0;
    D_8291B860 = 0x78;
    func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E);
}
#endif

#ifdef VERSION_US
extern s16 D_8291B828; extern s32 D_8291A380; extern s16 D_8291B85C; extern s16 D_8291B85E; extern s16 D_8291B860; extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32); extern void func_800371B4(s32, s32, f32, s16, s32);
void func_8290DD80(void) { s16 mode; mode = D_8291B828; switch (mode) { case 0x24: Vec3f_SetComponentsDuplicate(D_8291A380 + 0xB4, 0.0f, 30.0f, 0.0f); D_8291B85C = -0x400; D_8291B85E = 0x3A00; D_8291B860 = 0x78; break; case 0x25: Vec3f_SetComponentsDuplicate(D_8291A380 + 0xB4, 0.0f, 30.0f, 0.0f); D_8291B85C = -0x800; D_8291B85E = 0x4500; D_8291B860 = 0x96; break; case 0x26: Vec3f_SetComponentsDuplicate(D_8291A380 + 0xB4, 0.0f, 30.0f, 0.0f); D_8291B85C = -0x400; D_8291B85E = 0x3700; D_8291B860 = 0x96; break; } func_800371B4(D_8291A380 + 0xB4, D_8291A380 + 0xA8, (f32)D_8291B860, D_8291B85C, (s32)D_8291B85E); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290DED4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290DF6C.s")
#endif

#ifdef VERSION_US
extern void func_8290DF6C(void);
extern void func_8290954C(void);
void func_8290E014(void) {
    func_8290DF6C();
    func_8290954C();
}
#endif
