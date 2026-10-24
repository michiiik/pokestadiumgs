#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB0F760.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB0F87C.s")
#endif

void func_8AB0FE08(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB0FE10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB0FF40.s")
#endif

#ifdef VERSION_US
extern s32 func_8AB1007C(s32);
s32 func_8AB1005C(void) {
    return func_8AB1007C(0);
}
#endif

#ifdef VERSION_US
extern void func_8AB04AE4(void);
extern u8 StageContext_GetFadeMode(void);
extern s32 func_8AB10144(s32);

s32 func_8AB1007C(s32 arg0) {
    s32 result = 0x3D;

    switch (arg0) {
    case 0:
        func_8AB04AE4();
        break;
    case 1:
        if (StageContext_GetFadeMode() == 0) {
            result = func_8AB10144(0);
        }
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
extern u8 StageContext_GetFadeMode(void);
extern void StageFade_StartFromTransparent(s32);
s32 func_8AB100E0(s32 arg0) {
    s32 result = 0x3E;

    switch (arg0) {
    case 0:
        StageFade_StartFromTransparent(5);
        break;
    case 1:
        if (StageContext_GetFadeMode() == 1) {
            result = 0;
        }
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB10144.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB10248.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB103B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB104FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB1075C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB10AD0.s")
#endif

#ifdef VERSION_US
s32 func_8AB10D28(void) {
    return 0x45;
}
#endif

#ifdef VERSION_US
extern s16 D_8AB1744E;
extern u8 *D_8AB12668[];
extern u8 *D_8AB12678[];
extern void func_8AB01FBC(void);
extern void TextHighlight_AnimateScales(void);
extern void func_8AB00B98(u8 *, u32);
extern s32 func_8AB10DE4(s32);
s32 func_8AB10D30(s32 arg0) {
    s32 result = 70;
    s16 *counter = &D_8AB1744E;
    u8 **panel;

    switch (arg0) {
    case 0:
        *counter = 0;
        func_8AB01FBC();
        break;
    case 1:
        *counter += 1;
        TextHighlight_AnimateScales();
        if (*counter >= 11) {
            panel = D_8AB12668;
            do {
                func_8AB00B98(*panel, -1U);
                panel++;
            } while (panel != D_8AB12678);
            result = func_8AB10DE4(0);
        }
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
extern s16 D_8AB17450;
extern void *D_8AB11D00;
extern u8 D_8AB126A8[];
extern void *D_8AB1725C;
extern void *func_8004C8A0(void *, s32, s32, s32);
extern void func_8AB00BA4(s32, s32, s32);
extern void func_800225C4(s32);
extern s32 func_8AB10F14(s32);
s32 func_8AB10DE4(s32 arg0) {
    s16 *counter = &D_8AB17450;
    s32 result = 71;
    s32 i;

    switch (arg0) {
    case 0:
        *counter = 0;
        *(u16 *)((u8 *)D_8AB11D00 + 2) |= 1;
        func_8AB04AE4();
        func_8004C8A0(D_8AB126A8, 256, 57, 389);
        *(u16 *)((u8 *)D_8AB1725C + 2) &= ~1;
        for (i = 0; i < 4; i++) {
            *(u16 *)(D_8AB12678[i] + 2) &= ~1;
        }
        func_8AB00BA4(65550, 0, 0);
        func_800225C4(40);
        break;
    case 1:
        *counter += 1;
        TextHighlight_AnimateScales();
        if (*counter >= 61) {
            result = func_8AB10F14(0);
        }
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2348E0/func_8AB10F14.s")
#endif
