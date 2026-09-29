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

extern f32 D_8682F304;
extern f32 D_86807C60;
extern f32 D_86807C84;
extern s32 D_86808698[];
extern s32 D_868086C0[];
void func_86800508(void) {
    s32 index;
    f32 t;
    s32 height;
    s32 (*endpoint)[];
    f32 threshold;
    
    
    t = 0.0f;
    threshold = D_8682F304;
    do {
        
        do {
            do {
                
                index = 0;
                height = 500; do {
                    t = 0.0f;
                    for (;;) {
                        if (((f32)height - D_86807C60 * t * t) <= threshold) {
                            D_86808698[index++] = t / D_86807C84;
                            break;
                        }
                        t += D_86807C84;
                    }
                    height += 10;
                } while (&D_86808698[index] != *(endpoint = &D_868086C0));
            } while (0);
        } while (0);
    } while (0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86800594.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86800A7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86800B98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86800D5C.s")

extern u32 func_8003570C(void);
extern u8 D_868086C8[];
extern u8 D_868085C0[];
extern f32 D_86808218;
extern void func_87F03884(void *, s32, void *, f32, f32, f32, s32, f32, s32);
void func_8680105C(s32 arg0) {
    volatile s32 pad[8];
    u32 rand1;
    u32 rand0;
    u8 *ptr;
    f32 temp;
    f32 zero;
    rand0 = func_8003570C();
    rand1 = func_8003570C();
    func_8003570C();
    ptr = D_868086C8 + arg0 * 0x168;
    zero = 0.0f;
    func_87F03884(D_868085C0, 0, ptr, 20.0f, *(f32 *)(ptr + 0xB0) - *(f32 *)(ptr + 0x28) + 30.0f, zero, (rand0 % 31) * 0x200, ((f32)rand1 / 4294967296.0f) * D_86808218 * (f32)(4 | (rand0 & 0)), 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86801160.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868014C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86801E8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86802740.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86802EE8.s")

extern s32 D_868074C0;
extern s32 D_868074C4;
extern s32 D_86807EE4;
extern s32 D_86807EE8;
extern s32 D_86807EEC;
extern s32 D_86807EF4;
extern s32 D_86807EF8;
extern s32 D_86807F04;
extern s32 func_8004C990(s32, s32);
extern void func_8004D19C(s32, s32, s32, s32, s32);
void func_8680349C(s32 arg0) {
    s32 sp2C;
    s32 temp_lo;
    s32 temp_v0;
    if (arg0 == 0x64) {
        func_8004D19C(D_86807EE4, 0x1A, func_8004C990(0x194, D_868074C4), 0, 0);
        temp_v0 = func_8004C990(0x194, D_868074C0);
        func_8004D19C(D_86807EE8, 0x1A, temp_v0, 0, 0);
        func_8004D19C(D_86807EEC, 0x1A, temp_v0, 0, 0);
        return;
    }
    if (arg0 >= 0xA) {
        temp_lo = arg0 / 10;
        sp2C = temp_lo;
        func_8004D19C(D_86807EF4, 0x1A, func_8004C990(0x194, (&D_868074C0)[temp_lo]), 0, 0);
        temp_v0 = arg0 - (sp2C * 0xA);
        func_8004D19C(D_86807EF8, 0x1A,
                      func_8004C990(0x194, (&D_868074C0)[temp_v0]), 0, 0);
        return;
    }
    func_8004D19C(D_86807F04, 0x1A, func_8004C990(0x194, (&D_868074C0)[arg0]), 0, 0);
}

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

extern s32 D_86807C7C;
extern u8 D_8682CD20[];
extern u8 D_8682EE18[];
s32 func_868040EC(s32 arg0, s32 arg1) {
    s32 value;
    s32 result = -1;
    if (D_86807C7C == 0) {
        return 1;
    }
    value = *(s32 *)(&D_8682EE18[arg0 * 0x124] + 0x1C);
    switch (value) {
    case 0:
        break;
    case 2:
        if (*(s32 *)&D_8682CD20[(arg0 * 0x640) + (arg1 * 0x28)] == 1) { result = 1; *(s32 *)(&D_8682EE18[arg0 * 0x124] + 0x10) = 1; }
        break;
    case 1:
        if (*(s32 *)&D_8682CD20[(arg0 * 0x640) + (arg1 * 0x28)] == 3) { result = 1; *(s32 *)(&D_8682EE18[arg0 * 0x124] + 0x10) = 3; }
        break;
    case 3:
        if (*(s32 *)&D_8682CD20[(arg0 * 0x640) + (arg1 * 0x28)] == 2) { result = 1; *(s32 *)(&D_8682EE18[arg0 * 0x124] + 0x10) = 2; }
        break;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680422C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868044D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868048C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86804C5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86804EE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680537C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_868058C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86805AA4.s")

extern s32 D_8682F2A8;
extern s32 func_87F02104(void);
extern void StageContext_SetClearColor(s32);
extern void StageFade_StartFromTransparent(s32);
void func_86805C88(void) {
    s32 temp_v0;
    temp_v0 = func_87F02104();
    switch (temp_v0) {
    case 1:
        *(s32 *)((u8 *)&D_8682F2A8 + 0x10) = 2;
        *(s32 *)((u8 *)&D_8682F2A8 + 0x0) = 0xC;
        StageContext_SetClearColor(1);
        StageFade_StartFromTransparent(0xA);
        return;
    case 2:
        *(s32 *)((u8 *)&D_8682F2A8 + 0x8) = 0;
        *(s32 *)((u8 *)&D_8682F2A8 + 0x0) = 9;
        *(s32 *)((u8 *)&D_8682F2A8 + 0x10) = 2;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    case 3:
        *(s32 *)((u8 *)&D_8682F2A8 + 0x8) = 1;
        *(s32 *)((u8 *)&D_8682F2A8 + 0x0) = 9;
        *(s32 *)((u8 *)&D_8682F2A8 + 0x10) = 2;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    }
}

extern void *D_86808590;
extern s32 D_8682F2A8;
void func_86805D50(void) {
    if (StageContext_GetFadeMode() == 0) {
        if ((*(u8 *)((u8 *)(D_86808590) + (0x2180))) == 4) {
            StageFade_StartFromOpaque(0x14);
            func_87F00688();
            D_8682F2A8 = 5;
            return;
        }
        D_8682F2A8 = 3;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86805DB8.s")

extern f32 D_868083E0;
extern u8 D_868085E8[];
extern u8 D_86808C68[];
extern f32 D_8682F30C;
extern s32 D_8682F310;
extern u32 func_8003570C(void);
extern void func_87F03884(void *, s32, void *, f32, f32, f32, s32, f32, s32);
void func_86806044(s32 arg0) {
    volatile s32 pad[3];
    u32 rand1;
    u32 rand0;
    u32 rand2;
    u8 *ptr;
    D_8682F310 = 1;
    D_8682F30C = D_868083E0;
    rand0 = func_8003570C();
    rand1 = func_8003570C();
    rand2 = func_8003570C();
    ptr = D_86808C68 + arg0 * 0x168;
    func_87F03884(D_868085E8, 0, ptr, 0.0f, *(f32 *)(ptr + 0xB0) - 20.0f, -20.0f, (rand0 % 31) * 0x200, ((f32)rand1 / 4294967296.0f) * 1.5f * D_8682F30C, (rand2 % (D_8682F310 + 1)) + 1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_86806180.s")

extern s32 D_86807CB4;
extern s32 D_86808558;
extern s32 func_87F08208(void *);
extern void func_86805DB8(void);
extern void func_800225C4(s32);
extern void func_800226C0(s32);
extern void StageContext_SetClearColor(s32);
extern void StageFade_StartFromTransparent(s32);
extern void func_800279C4(s32);
extern s32 D_8682F2A8;
void func_868063CC(void) {
    s32 temp_v0;
    if (++D_86807CB4 >= 0x97) {
        D_86807CB4 = 0x32;
    }
    temp_v0 = func_87F08208(&D_86808558);
    switch (temp_v0) {
    case 1:
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0x14);
        func_86805DB8();
        D_8682F2A8 = 4;
        func_800225C4(0x28);
        func_800279C4(0xCF0B);
        return;
    case 2:
        D_8682F2A8 = 9;
        *(s32 *)((u8 *)&D_8682F2A8 + 0x10) = 1;
        *(s32 *)((u8 *)&D_8682F2A8 + 0x8) = 0;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        func_800226C0(3);
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/56/fragment56_code/func_8680649C.s")

extern s32 D_8682F2A8;
extern s32 func_87F01A40(void);
extern void StageContext_SetClearColor(s32);
extern void StageFade_StartFromTransparent(s32);
void func_8680660C(void) {
    s32 temp_v0;
    *(s32 *)((u8 *)&D_8682F2A8 + 0xC) = 1;
    temp_v0 = func_87F01A40();
    switch (temp_v0) {
    case 0:
    case 2:
        *(s32 *)((u8 *)&D_8682F2A8 + 0xC) = 0;
        return;
    case 3:
        *(s32 *)((u8 *)&D_8682F2A8 + 0x8) = 0;
        *(s32 *)((u8 *)&D_8682F2A8 + 0x0) = 9;
        *(s32 *)((u8 *)&D_8682F2A8 + 0x10) = 3;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    case 4:
        *(s32 *)((u8 *)&D_8682F2A8 + 0x8) = 1;
        *(s32 *)((u8 *)&D_8682F2A8 + 0x0) = 9;
        *(s32 *)((u8 *)&D_8682F2A8 + 0x10) = 3;
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0xA);
        return;
    }
}

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
