#include "global.h"


#ifdef VERSION_US
s32 func_86800020(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    f32 temp_fv0;
    temp_fv0 = (f32)((s32)(arg1 - arg3) / (s32)(arg0 - arg2));
    return (s32)(((f32)arg4 * temp_fv0) + (f32)(arg1 - (s32)((f32)arg0 * temp_fv0)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868000AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86800298.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868003E4.s")

extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_86800434(s32 arg0, void *arg1) {
    s16 pad;
    s32 sp28;
    s16 sp26;
    s16 sp24;
    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &sp28, &sp26, &sp24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(sp26 + 0x2000);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(sp24 - 0x2000);
    }
    return 0;
}

s32 func_8680049C(s32 arg0, void *arg1) {
    s16 pad;
    s32 sp28;
    s16 sp26;
    s16 sp24;
    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &sp28, &sp26, &sp24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(-0x2000 - sp26);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(sp24 + 0x6000);
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86800508.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86800594.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86800A7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86800B98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86800D5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680105C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86801160.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868014C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86801E8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86802740.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86802EE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680349C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86803618.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868039F8.s")

s32 func_87F00930();
extern void func_87F01D44();

void func_86803EA4(void) {
    if (func_87F00930() == 1) {
        func_87F01D44();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86803ED8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868040EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680422C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868044D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868048C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86804C5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86804EE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680537C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868058C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86805AA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86805C88.s")

extern void *D_86808590;
extern s32 D_8682F2A8;
void func_86805D50(void) {
    if (StageContext_GetFadeMode() == 0) {
        if ((*(u8 *)((u8 *)(D_86808590) + (0x2180))) == 4) {
            func_80007AEC(0x14);
            func_87F00688();
            D_8682F2A8 = 5;
            return;
        }
        D_8682F2A8 = 3;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86805DB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86806044.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86806180.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868063CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680649C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680660C.s")

extern s32 D_8682F2B4;
void func_868066B8(void) {
    if (D_8682F2B4 != 1) {
        if (func_87F006AC() == 1) {
            func_800279C4(0x7F03);
        }
        if (func_87F006AC() == 2) {
            D_8682F2A8 = 2;
            func_800279C4(0x7F04);
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680671C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680686C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86806CD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86806E94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86807120.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680729C.s")
#endif
