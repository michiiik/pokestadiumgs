#include "global.h"

extern u8 *D_8291A380;
extern s16 D_8291B828;
extern s16 D_8291B85C;
extern s16 D_8291B85E;
extern s16 D_8291B860;

extern void Vec3f_SetComponentsDuplicate(f32 *vector, f32 x, f32 y, f32 z);
extern void Camera_ComputeEyeFromAngles(f32 *eye, f32 *target, f32 distance,
                                        s16 pitch, s16 yaw);

static void Fragment67_SetCamera(f32 distance, s16 angle, s16 pitch, s16 yaw) {
    Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, distance, 0.0f);
    D_8291B860 = angle;
    D_8291B85C = pitch;
    D_8291B85E = yaw;
    Camera_ComputeEyeFromAngles((f32 *)(D_8291A380 + 0xB4),
                                (f32 *)(D_8291A380 + 0xA8),
                                (f32)D_8291B860, D_8291B85C, D_8291B85E);
}


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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_829084E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908520.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908594.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908608.s")
#endif

void func_82908638(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908640.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_829087C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_829087E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908800.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908854.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290888C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_829088EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290894C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908A54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908B60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908BD8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908CF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908E50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_82908E6C.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290A0B0.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290AB10.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290ADD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290AE3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290AEA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290AEEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290AF50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B004.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B098.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B184.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B220.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B264.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B3BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290B3E4.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290BC84.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290D72C.s")
#endif

void BattleAnim_Fragment67Dispatch_045(void) {
    Fragment67_SetCamera(30.0f, 0x00BE, 0, 0);
}

void BattleAnim_Fragment67Dispatch_001(void) {
    Fragment67_SetCamera(15.0f, 0x0096, 0, 0);
}

void BattleAnim_Fragment67Dispatch_005(void) {
    Fragment67_SetCamera(15.0f, 0x005A, 0, 0x1A00);
}

void BattleAnim_Fragment67Dispatch_009(void) {
    Fragment67_SetCamera(15.0f, 0x005A, 0, -0x1A00);
}

void BattleAnim_Fragment67Dispatch_013(void) {
    Fragment67_SetCamera(15.0f, 0x008C, 0, 0);
}

void BattleAnim_Fragment67Dispatch_017(void) {
    Fragment67_SetCamera(15.0f, 0x0082, 0x1900, 0x1900);
}

void BattleAnim_Fragment67Dispatch_021(void) {
    Fragment67_SetCamera(15.0f, 0x0096, -0x1700, -0x1400);
}

void BattleAnim_Fragment67Dispatch_025(void) {
    Fragment67_SetCamera(15.0f, 0x008C, 0x1900, 0);
}

void BattleAnim_Fragment67Dispatch_029(void) {
    Fragment67_SetCamera(15.0f, 0x0096, 0, 0);
}

void BattleAnim_Fragment67Dispatch_033(void) {
    Fragment67_SetCamera(15.0f, 0x00B4, 0, 0);
}

void BattleAnim_Fragment67Dispatch_037(void) {
    Fragment67_SetCamera(15.0f, 0x0078, 0, 0);
}

void BattleAnim_Fragment67Dispatch_041(void) {
    switch (D_8291B828) {
        case 0x24:
            Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 30.0f, 0.0f);
            D_8291B85C = -0x0400;
            D_8291B85E = 0x3A00;
            D_8291B860 = 0x0078;
            break;
        case 0x25:
            Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 30.0f, 0.0f);
            D_8291B85C = -0x0800;
            D_8291B85E = 0x4500;
            D_8291B860 = 0x0096;
            break;
        case 0x26:
            Vec3f_SetComponentsDuplicate((f32 *)(D_8291A380 + 0xB4), 0.0f, 30.0f, 0.0f);
            D_8291B85C = -0x0400;
            D_8291B85E = 0x3700;
            D_8291B860 = 0x0096;
            break;
        default:
            break;
    }
    Camera_ComputeEyeFromAngles((f32 *)(D_8291A380 + 0xB4),
                                (f32 *)(D_8291A380 + 0xA8),
                                (f32)D_8291B860, D_8291B85C, D_8291B85E);
}

void BattleAnim_Fragment67Dispatch_049(void) {
    Fragment67_SetCamera(0.0f, 0x010E, 0, 0);
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290DF6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290E014.s")
#endif
