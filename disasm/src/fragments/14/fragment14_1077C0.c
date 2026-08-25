#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130F630.s")
#endif

void func_8130F69C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130F6A4.s")
#endif

#ifdef VERSION_US
extern u8 D_81312924[];
extern f32 func_8130F6A4(u8 *arg0, u8 *arg1, u8 *arg2);
f32 func_8130F794(u8 *arg0, u8 *arg1) {
    return func_8130F6A4(arg0, arg1, D_81312924);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130F7B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130F8B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130F970.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130FA0C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130FB58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130FBC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130FC80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130FD10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130FE28.s")
#endif

#ifdef VERSION_US
s32 func_8130FE8C(u8 *arg0) {
    *(f32 *)(arg0 + 0x30) = 0.0f;
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_8130FE9C(u8 *arg0) {
    arg0[0x3A]++;
    *(f32 *)(arg0 + 0x30) = 0.0f;
    return 1;
}
#endif

void func_8130FEB8(void) {
}

#ifdef VERSION_US
extern f32 func_816092FC(void);
extern void func_8130FEC0(u8 *arg0, f32 arg1);
extern f32 func_8130FF70(f32 arg0);
void func_8130FEC0(u8 *arg0, f32 arg1) {
    *(f32 *)(arg0 + 0x30) += arg1;
    if (*(f32 *)(arg0 + 0x30) >= 16.0f) {
        *(f32 *)(arg0 + 0x30) = 16.0f;
        return;
    }
    if (*(f32 *)(arg0 + 0x30) <= 0.0f) {
        *(f32 *)(arg0 + 0x30) = 0.0f;
    }
}
#endif

#ifdef VERSION_US
s32 func_8130FF18(u8 *arg0) {
    func_8130FEC0(arg0, func_816092FC());
    if (*(f32 *)(arg0 + 0x30) >= 16.0f) {
        arg0[0x38] = 3;
    }
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8130FF70.s")
#endif

#ifdef VERSION_US
extern f32 func_8130FF70(f32 arg0);
void func_8130FFE0(f32 arg0, f32 arg1) {
    f32 temp[2];
    temp[0] = func_8130FF70(arg1);
    func_8130FF70(temp[0] - func_8130FF70(arg0));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8131001C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_813102A4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8131058C.s")
#endif

#ifdef VERSION_US
s32 func_813107A0(u8 *arg0) {
    func_8130FEC0(arg0, -func_816092FC());
    if (*(f32 *)(arg0 + 0x30) <= 0.0f) {
        arg0[0x38] = 5;
        arg0[0x3A] = 0;
    }
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_81310800.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_81310894.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_81310A14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_81310BF8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_81311030.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/14/fragment14_1077C0/func_8131109C.s")
#endif
