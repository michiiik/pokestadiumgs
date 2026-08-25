#include "global.h"


#ifdef VERSION_US
extern u32 D_800D0510;
extern void func_80006F70(void *, s32, s32, s32, s32);
s32 func_82400530(s32 arg0, s32 arg1) {
    if (arg0 == 2) {
        func_80006F70(&D_800D0510, 0xD, 0x27, 0x126, 0xA1);
    }
    return 1;
}

void func_82400578(u8 *arg0, s32 arg1) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE5B0/func_82400584.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE5B0/func_824005D8.s")

extern u8 D_824090F3;
extern u8 D_82408A60[];
extern u8 D_82408A6C[];
void func_824006C8(s32 arg0, s32 arg1) {
    if (arg0 == 2) {
        u8 value = D_824090F3;
        D_82408A60[3] = value;
        D_82408A60[8] = value;
        D_82408A6C[3] = value;
        D_82408A6C[7] = value;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE5B0/func_82400704.s")

extern u8 D_824090A0[];
extern void *D_8240AA68;
extern void func_800088DC(void);
extern void func_8003C970(void);
extern void func_82406E14(void *, void *);
extern void func_80008648(void);
void func_82400880(void) {
    func_800088DC();
    func_8003C970();
    func_82406E14(D_824090A0, D_8240AA68);
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE5B0/func_824008C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE5B0/func_824009AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EE5B0/func_82400A9C.s")
#endif
