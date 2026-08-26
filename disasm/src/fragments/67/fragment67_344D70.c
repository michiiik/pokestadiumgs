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
extern void func_80007820(s32 *, s32);
extern void func_80008648();
extern void func_800088DC();
extern void func_8003C6B8(s32);
extern void func_8003C970();
extern u8 D_800D0510;
extern s32 D_8291B868;
void func_82908800(void) {
    func_800088DC();
    func_80007820(&D_800D0510, 1);
    func_8003C970();
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
extern void func_80007B34(s32);
extern void func_800225C4(s32);
void func_829088EC(void) {
    s32 var_s0;

    func_80007B34(0x10);
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
extern void func_8290A81C(s32);
extern s32 D_8291B858;
extern s32 D_82912F80;
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
extern u8 D_8291B831;

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
extern s32 D_8291B864;

void func_8290D72C(void) {
    D_8291B864 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290D738.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290D7C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290D858.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290D8EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290D980.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290DA10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290DAA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290DB3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290DBD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290DC60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290DCF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_344D70/func_8290DD80.s")
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
