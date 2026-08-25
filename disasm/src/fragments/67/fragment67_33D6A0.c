#include "global.h"


#ifdef VERSION_US
extern s16 D_829188A8;
extern s16 D_829188AA;

s32 func_82900BA0(s32 arg0, void *arg1) {
    if (arg0 == 2) {
        (*(s16 *)((u8 *)(arg1) + (0x1C))) = (s16) (D_829188A8 + 0x2000);
        (*(s16 *)((u8 *)(arg1) + (0x1E))) = (s16) (D_829188AA - 0x2000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s16 D_829188A8;
extern s16 D_829188AA;

s32 func_82900BD0(s32 arg0, void *arg1) {
    if (arg0 == 2) {
        (*(s16 *)((u8 *)(arg1) + (0x1C))) = (s16) (-0x2000 - D_829188A8);
        (*(s16 *)((u8 *)(arg1) + (0x1E))) = (s16) (D_829188AA + 0x6000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82900C04.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82900C40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82900D78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82900E54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82900E98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82900EFC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82900F80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82900FDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_8290102C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_829011D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_829012E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_829013F8.s")
#endif

#ifdef VERSION_US
extern u8 D_82918868[];
void func_829014F4(void) {
    D_82918868[0x32] = 0;
    D_82918868[0x30] = 0;
    D_82918868[0x31] = 3;
}
#endif

#ifdef VERSION_US
extern s32 D_8291889C;
extern s32 D_829188EC;
extern void func_829014F4(void);
extern void func_82900C04(s32);
extern void func_82900C40(s32);
void func_82901510(s32 arg0) {
    D_829188EC = 1;
    func_829014F4();
    func_82900C04(D_8291889C);
    func_82900C40(D_8291889C);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82901554.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82901628.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_829016B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82901A6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82901AE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82901BA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82901C98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82901DD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82902024.s")
#endif

void func_82902260(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82902268.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_829022E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82902554.s")
#endif

#ifdef VERSION_US
extern void func_82902554(void);
extern void func_82902268(void);
void func_8290260C(void) {
    func_82902554();
    func_82902268();
}
#endif

void func_82902634(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_8290263C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82902694.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82902714.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_8290277C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_33D6A0/func_82902808.s")
#endif
