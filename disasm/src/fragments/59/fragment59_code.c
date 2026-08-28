#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86900020.s")
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_869000D0(s32 arg0, void *arg1) {
    s16 pad;
    s32 x;
    s16 y;
    s16 z;
    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &x, &y, &z);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(y + 0x2000);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(z - 0x2000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_86900138(s32 arg0, void *arg1) {
    s16 pad;
    s32 x;
    s16 y;
    s16 z;
    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &x, &y, &z);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(-0x2000 - y);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(z + 0x6000);
    }
    return 0;
}
void func_86900138_padding(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_869001AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_869003C8.s")
#endif

void func_869004A4(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_869004AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86900698.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690073C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86901414.s")
#endif

#ifdef VERSION_US
extern u8 *D_8691AD58;
extern void func_800088A4(s32);
extern void StageFade_StartFromTransparent(s32);
void func_869015F0(s32 arg0) {
    *(s32 *)(D_8691AD58 + 0x10) = arg0;
    *(s32 *)D_8691AD58 = 0xB;
    *(s32 *)(D_8691AD58 + 4) = 0xC;
    func_800088A4((u16)0xFFFF);
    StageFade_StartFromTransparent(0xA);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86901640.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86901AA8.s")
#endif

#ifdef VERSION_US
extern void func_800086A4(s32);
extern void func_80007AEC(s32);
extern void func_80064D28(void);
extern void func_86901AA8(void);
extern void func_86901414(void);
void func_869020CC(void) {
    func_800086A4(2);
    func_80007AEC(0xA);
    do {
        func_80064D28();
        func_86901AA8();
        func_86901414();
    } while (*(s32 *)D_8691AD58 != 0xC);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86902134.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690241C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86902640.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86904D48.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_869053B4.s")
#endif

void func_869054CC(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_869054D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86905630.s")
#endif

void func_86905804(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690580C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86907614.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690941C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86909EAC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_86909FAC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690AA64.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690ABCC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690AD3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690B2A8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690B700.s")
#endif

#ifdef VERSION_US
extern void func_8690AD3C(s32);
extern u8 D_8691A448;
void func_8690B848(void) {
    s32 var_s0;

    var_s0 = 0;
    if ((*(s32 *)((u8 *)(&D_8691A448) + (0x320))) > 0) {
        do {
            func_8690AD3C(var_s0);
            var_s0 += 1;
        } while (var_s0 < (*(s32 *)((u8 *)(&D_8691A448) + (0x320))));
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690B89C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690B984.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690C20C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690C46C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690C6C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690C7F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690CA50.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690CCB8.s")
#endif

#ifdef VERSION_US
extern void *func_87F025B8(void *, void *);
extern void func_8003F1DC(u8 *);
extern void func_8003F114(u8 *, s32, s32, s32);
extern u8 D_8690FFE8;
extern s32 D_86911290;
extern void func_8690CCB8(void);
void func_8690CF8C(s32 arg0) {
    u8 *v1 = func_87F025B8(&D_8690FFE8, func_8690CCB8);
    if (v1 != NULL) {
        *(s32 *)(v1 + 0x38) = arg0;
        *(s32 *)(v1 + 0x20) = arg0;
        *(f32 *)(v1 + 0x48) = 0.0f;
        *(f32 *)(v1 + 0x4C) = 0.0f;
        *(f32 *)(v1 + 0x50) = 0.0f;
        func_8003F1DC(v1 + 0x24);
        func_8003F114(v1 + 0x24, 0, -1, D_86911290);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690D000.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690DC88.s")
#endif

#ifdef VERSION_US
extern void *func_87F025B8(void *, void *);
extern void func_8003F1DC(u8 *);
extern void func_8003F114(u8 *, s32, s32, s32);
extern u8 D_86911298;
extern s32 D_8691143C;
extern void func_8690DC88(void);
void func_8690DF18(void) {
    u8 *v1 = func_87F025B8(&D_86911298, func_8690DC88);
    if (v1 != NULL) {
        *(f32 *)(v1 + 0x48) = 0.0f;
        *(f32 *)(v1 + 0x4C) = 0.0f;
        *(f32 *)(v1 + 0x54) = 0.0f;
        *(f32 *)(v1 + 0x58) = 0.0f;
        *(f32 *)(v1 + 0x5C) = 0.0f;
        *(f32 *)(v1 + 0x50) = 50.0f;
        func_8003F1DC(v1 + 0x24);
        func_8003F114(v1 + 0x24, 0, -1, D_8691143C);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/59/fragment59_code/func_8690DF90.s")
#endif
