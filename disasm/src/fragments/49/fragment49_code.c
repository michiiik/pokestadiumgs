#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861000B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100120.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861001A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861003A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100418.s")

extern s32 D_8610AD20;
extern s32 func_87F08208(void *);
extern void StageContext_SetClearColor(s32);
extern void StageFade_StartFromTransparent(s32);
extern void func_800225C4(s32);
extern void func_800226C0(s32);
extern void func_800279C4(s32);
extern void func_861094BC(s32 arg0);
extern void func_87F0277C(s32);
void func_8610068C(void) {
    s32 temp_v0;

    func_87F0277C(D_8610AD20 + 0x7C);
    temp_v0 = func_87F08208((void *)(u32)(D_8610AD20 + 0x44));
    switch (temp_v0) {
    case 1:
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0x14);
        *(s32 *)((u8 *)(u32)D_8610AD20 + 0x3C) = 2;
        func_800225C4(0x28);
        func_800279C4(0xCF0B);
        return;
    case 2:
        func_861094BC(0);
        func_800226C0(3);
        return;
    }
}

extern s32 D_8610AD20;
extern s32 StageContext_GetFadeMode(void);
extern void func_86105008(void);
extern void func_86104CAC(void);
extern void StageFade_StartFromOpaque(s32);
extern void func_87F00688(void);
extern void func_87F0277C(s32);

void func_86100728(void) {
    if (StageContext_GetFadeMode() == 1) {
        func_86105008();
        func_86104CAC();
        StageFade_StartFromOpaque(0x14);
        *(s32 *)((u8 *)(u32)D_8610AD20 + 0x3C) = 3;
        func_87F00688();
    }
    func_87F0277C(D_8610AD20 + 0x7C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100790.s")

extern s32 func_87F0C930(s32);
extern s32 func_87F0A098(void *, void *, s32, u32, u32, u32, u32);
extern s32 D_8610AD20;
void func_861007D8(void) {
    s32 v0 = *(s32 *)&D_8610AD20;
    if (*(u8 *)((u8 *)(u32)*(s32 *)((u8 *)(u32)v0) + 0x2180) == 4) {
        func_87F0C930(v0 + 0x2C);
        return;
    }
    *(s32 *)((u8 *)(u32)v0 + 0x97DC) = 1;
    v0 = *(s32 *)&D_8610AD20;
    func_87F0A098((void *)((u8 *)(u32)v0 + 0x9704), (void *)*(s32 *)((u8 *)(u32)v0), 0,
                  *(u32 *)((u8 *)(u32)v0 + 0x708) & 0x100000,
                  *(u32 *)((u8 *)(u32)v0 + 0x894) & 0x100000,
                  *(u32 *)((u8 *)(u32)v0 + 0xA20) & 0x100000,
                  *(u32 *)((u8 *)(u32)v0 + 0xBAC) & 0x100000);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100874.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861008E8.s")

extern void *func_87F0A3E8(void *);
extern void func_86109394(void);
extern void func_861094BC(s32);
void func_86100A58(void) {
    func_86109394();
    if (func_87F0A3E8((void *)((u8 *)(u32)D_8610AD20 + 0x9704)) != NULL) {
        if (*(u8 *)((u8 *)(u32)*(s32 *)((u8 *)(u32)D_8610AD20) + 0x2180) == 1) {
            func_861094BC(2);
        } else {
            *(s32 *)((u8 *)(u32)D_8610AD20 + 0x3C) = 6;
        }
    }
}
void func_86100A58_padding(void) {}

extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_86100ACC(s32 a, void *p) {
    s16 pad;
    s32 x;
    s16 y;
    s16 z;
    if (a == 2) {
        func_80037120(
            D_80094908 + 0xB4,
            D_80094908 + 0xA8,
            &x, &y, &z
        );
        *(s16 *)((u8 *)p + 0x1C) = y + 0x2000;
        *(s16 *)((u8 *)p + 0x1E) = z - 0x2000;
    }
    return 0;
}

extern s32 D_80094908;
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);

s32 func_86100B34(s32 arg0, void *arg1) {
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

extern Gfx *D_800D0510;
s32 func_86100BA0(s32 arg0, void *arg1) {
    if (arg0 == 2) {
        gDPSetScissor(D_800D0510++, 0, 0, 10, 320, 230);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100BE0.s")

extern s32 D_8610AD20;
extern f32 D_8610AAAC;
extern f32 D_8610AAB0;
extern f32 D_8610AAB4;
void func_86100CFC(void *arg0) {
    f32 temp_fv1;
    f32 var_fv0;
    void *temp_v0;

    temp_v0 = (void *)((u8 *)arg0 + 0x24);
    if (*(s32 *)((u8 *)(u32)D_8610AD20 + 0x3C) == 4) {
        var_fv0 = D_8610AAAC;
    } else {
        var_fv0 = D_8610AAB0;
    }
    if (*(f32 *)((u8 *)temp_v0 + 0x28) < var_fv0) {
        *(f32 *)((u8 *)temp_v0 + 0x28) = var_fv0;
        temp_fv1 = *(f32 *)((u8 *)arg0 + 0x14);
        if (temp_fv1 < 0.0f) {
            *(f32 *)((u8 *)arg0 + 0x14) = temp_fv1 * -0.5f;
        }
    }
    if (D_8610AAB4 < *(f32 *)((u8 *)temp_v0 + 0x28)) {
        *(f32 *)((u8 *)temp_v0 + 0x28) = D_8610AAB4;
        *(f32 *)((u8 *)arg0 + 0x14) = *(f32 *)((u8 *)arg0 + 0x14) * (f32)0;
    }
}

void func_86100DA8(void *arg0) {
    if ((*(f32 *)((u8 *)(arg0) + (0x10))) < -15.0f) {
        (*(f32 *)((u8 *)(arg0) + (0x10))) = -15.0f;
    }
    if ((*(f32 *)((u8 *)(arg0) + (0x10))) > 15.0f) {
        (*(f32 *)((u8 *)(arg0) + (0x10))) = 15.0f;
    }
    if ((*(f32 *)((u8 *)(arg0) + (0x14))) < -15.0f) {
        (*(f32 *)((u8 *)(arg0) + (0x14))) = -15.0f;
    }
    if ((*(f32 *)((u8 *)(arg0) + (0x14))) > 15.0f) {
        (*(f32 *)((u8 *)(arg0) + (0x14))) = 15.0f;
    }
}

extern void func_8003F210(void *, s32);
extern void ModelAnim_SetFrame(u8 *, s16);
extern u32 func_8003570C(void);
void func_86100E20(void *arg0, s32 arg1) { if ((arg1 & 0x80000000) != 0) { if ((*(s32 *)((u8 *)arg0+12)<<1)>=0) { *(s32 *)((u8 *)arg0+12)|=arg1; *(s32 *)((u8 *)arg0+28)=0; } } else if ((arg1 & 0x40000000) != 0) { *(s32 *)((u8 *)arg0+12)&=0x7EFFFFFF; *(s32 *)((u8 *)arg0+12)|=arg1; *(s32 *)((u8 *)arg0+28)=0; } else if ((arg1 & 0x00400000) != 0) { *(s32 *)((u8 *)arg0+28)=0; *(s32 *)((u8 *)arg0+12)|=arg1; func_8003F210((u8 *)arg0+36,5); ModelAnim_SetFrame((u8 *)arg0+36,(s16)(func_8003570C()%12)); } else if ((arg1 & 0x01000000) != 0) { *(s32 *)((u8 *)arg0+196)=0xFF0000AF; *(s32 *)((u8 *)arg0+12)|=arg1; *(s32 *)((u8 *)arg0+28)=0; } else { *(s32 *)((u8 *)arg0+28)=0; *(s32 *)((u8 *)arg0+12)|=arg1; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100F1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_8610109C.s")

void func_86101558(f32 *arg0, f32 *arg1) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    temp_fv1 = *arg1;
    temp_fa0 = *arg0;
    temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa0 * temp_fa0));
    if (temp_fv0 != 0.0f) {
        *arg0 = temp_fa0 / temp_fv0;
        *arg1 /= temp_fv0;
    }
}
void func_86101558_padding(void) {}

extern f32 D_8610AADC;
extern s32 D_8610AD20;
f32 func_861015AC(f32 arg0, f32 arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 var_fv1;
    void *var_v0;

    var_v0 = (*(void **)((u8 *)(D_8610AD20) + (0x260C)));
    var_fv1 = 0.0f;
    if (var_v0 != NULL) {
        do {
            temp_fa0 = arg0 - (*(f32 *)((u8 *)(var_v0) + (0x48)));
            temp_fa1 = arg1 - (*(f32 *)((u8 *)(var_v0) + (0x4C)));
            temp_ft4 = (((700.0f * (D_8610AADC * (*(f32 *)((u8 *)(D_8610AD20) + (0x9768))))) + 30.0f) * 3.0f) - sqrtf((temp_fa0 * temp_fa0) + (temp_fa1 * temp_fa1));
            if (temp_ft4 > 0.0f) {
                var_fv1 += temp_ft4;
            }
            var_v0 = (*(void **)((u8 *)(var_v0) + (4)));
        } while (var_v0 != NULL);
    }
    return var_fv1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_8610167C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86101758.s")

extern f32 D_8610AAF0;
extern f32 D_8610AAF4;
extern void * D_87F119DC;
s32 func_861018D8(f32 arg0, f32 arg1) { f32 *coord; f32 y; f32 dx; f32 dy; s32 result = 1; coord = &arg1; if (arg0 < D_8610AAF0) { result = 0; } else { y = *(f32 *)((u8 *)D_87F119DC + 0x48); if (arg0 < y) { dx = y - arg0; dy = *(f32 *)((u8 *)D_87F119DC + 0x4C) - *coord; if ((arg0 - D_8610AAF4) * 2.0f < sqrtf(dx * dx + dy * dy)) result = 0; } } return result; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86101964.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86101AEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86101BD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86101E04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86101F60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861021A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861023D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861024C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86102630.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86102720.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86102908.s")

extern void *D_87F119DC;
void func_86102B30(void *arg0, f32 *arg1, f32 *arg2) {
    *arg1 = *(f32 *)((u8 *)arg0 + 0x18) - *(f32 *)((u8 *)D_87F119DC + 0x48);
    *arg2 = *(f32 *)((u8 *)arg0 + 0x1C) - *(f32 *)((u8 *)D_87F119DC + 0x4C);
}

extern f32 D_8610AB34;
extern f32 D_8610AB38;
extern f32 D_8610AB3C;
void func_86102B64(void *arg0, f32 *arg1, f32 *arg2) {
    f32 temp_fv0;
    f32 temp_fv0_2;

    temp_fv0 = (*(f32 *)((u8 *)(D_87F119DC) + (0x48)));
    if (temp_fv0 < D_8610AB34) {
        *arg1 = D_8610AB34 - temp_fv0;
    } else {
        *arg1 = (*(f32 *)((u8 *)(arg0) + (0x18))) - temp_fv0;
    }
    temp_fv0_2 = (*(f32 *)((u8 *)(D_87F119DC) + (0x4C)));
    if (temp_fv0_2 < D_8610AB38) {
        *arg2 = D_8610AB38 - temp_fv0_2;
        return;
    }
    if (D_8610AB3C < temp_fv0_2) {
        *arg2 = D_8610AB3C - temp_fv0_2;
        return;
    }
    *arg2 = (*(f32 *)((u8 *)(arg0) + (0x1C))) - temp_fv0_2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86102C08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86102D50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86102E8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86102FF0.s")

extern void func_8610109C(void *, void *);
void func_86103194(void) {
    void **var_s0;
    s32 var_s1;

    var_s0 = (void **)(u32)(D_8610AD20 + 0x8DE0);
    for (var_s1 = 0; var_s1 != 4; var_s1 += 1) {
        if (*var_s0 != D_87F119DC) {
            func_8610109C(D_87F119DC, *var_s0);
        }
        var_s0 = (void **)((u8 *)var_s0 + 0x2C);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_8610320C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86103384.s")

extern f32 D_8610AB5C;
extern f32 D_8610AB60;
extern f32 D_8610AB64;
extern f32 D_8610AB68;
extern f32 D_8610AB6C;

typedef struct {
    char pad0[0x10];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    char pad1C[0x28];
    s16 unk44;
    char pad46[2];
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
} Struct861034A8;
extern u32 func_8003570C(void);
extern s32 D_8610AD20;
void func_861034A8(Struct861034A8 *arg0, s32 arg1) {
    f32 scale;

    arg0->unk10 = ((f32)func_8003570C() / 4294967296.0f) * 100.0f;
    arg0->unk14 = ((f32)func_8003570C() / 4294967296.0f) * 100.0f;
    arg0->unk18 = 0.0f;

    switch (arg1) {
    case 0:
        arg0->unk48 = 0.0f;
        arg0->unk4C = D_8610AB5C;
        break;
    case 1:
        arg0->unk48 = D_8610AB60;
        arg0->unk4C = 0.0f;
        break;
    case 2:
        arg0->unk48 = 0.0f;
        arg0->unk4C = D_8610AB64;
        break;
    case 3:
        arg0->unk48 = D_8610AB68;
        arg0->unk4C = 0.0f;
        break;
    }

    scale = D_8610AB6C;
    arg0->unk50 = 1200.0f;
    arg0->unk54 = (*(f32 *)((u8 *)D_8610AD20 + 0x9768)) * scale;
    arg0->unk5C = (*(f32 *)((u8 *)D_8610AD20 + 0x9768)) * scale;
    arg0->unk58 = (*(f32 *)((u8 *)D_8610AD20 + 0x9768)) * scale;
    arg0->unk44 = 0x3FFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_8610362C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86103B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86103C48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861044EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861047CC.s")

extern void func_86104B2C();
void func_861048FC(void **p) {
    void *sp1C;
    sp1C = *p;
    func_86104B2C();
    *(f32 *)((u8 *)sp1C + 0x18) = 0;
    *(f32 *)((u8 *)sp1C + 0x14) = 0;
    *(u32 *)((u8 *)sp1C + 0x0C) |= 0x02000000;
    *(f32 *)((u8 *)sp1C + 0x10) = 0;
    *(f32 *)((u8 *)sp1C + 0x50) = 0;
}

extern s32 D_8610AD20;
extern void func_861048FC(void **);

void func_86104948(void) {
    typedef struct {
        u8 pad[0xC];
        s32 flags;
    } Node;
    s32 var_s1;
    Node **var_s0;
    var_s0 = (Node **)(u32)(D_8610AD20 + 0x8DE0);
    for (var_s1 = 0; var_s1 != 4; var_s1 += 1) {
        if (!((*var_s0)->flags & 0x02000000)) {
            func_861048FC((void **)var_s0);
        }
        var_s0 = (Node **)((u8 *)var_s0 + 0x2C);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861049C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86104A3C.s")

extern u32 func_8003570C(void);
extern f32 D_8610AC08;
extern f32 D_8610AC0C;
extern f32 D_8610AC10;
extern f32 D_8610AC14;
void func_86104B2C(void *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x18)) = ((f32)func_8003570C() / 4294967296.0f) * D_8610AC08 + D_8610AC0C;
    (*(f32 *)((u8 *)arg0 + 0x1C)) = ((f32)func_8003570C() / 4294967296.0f) * D_8610AC10 + D_8610AC14;
    (*(f32 *)((u8 *)arg0 + 0x20)) = 0.0f;
}

extern u32 func_8003570C(void);
extern f32 D_8610AC18;
extern f32 D_8610AC1C;
extern f32 D_8610AC20;
extern f32 D_8610AC24;
void func_86104BEC(void *arg0) {
    (*(f32 *)((u8 *)arg0 + 0x18)) = ((f32)func_8003570C() / 4294967296.0f) * D_8610AC18 + D_8610AC1C;
    (*(f32 *)((u8 *)arg0 + 0x1C)) = ((f32)func_8003570C() / 4294967296.0f) * D_8610AC20 + D_8610AC24;
    (*(f32 *)((u8 *)arg0 + 0x20)) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86104CAC.s")

extern s32 D_8610AD20;
extern void func_87F026E8(s32, s32);

void func_86105008(void) {
    s32 var_s0;
    s32 var_s1;
    var_s0 = D_8610AD20 + 0x90;
    for (var_s1 = 0; var_s1 != 4; var_s1 += 1) {
        func_87F026E8(D_8610AD20 + 0x7C, var_s0);
        var_s0 += 0x18C;
    }
}

extern f32 func_87D005E8(f32 *, f32 *, f32 *);
extern u32 func_8003570C(void);
void func_86105070(void *arg0, f32 *arg1) {
    f32 random;
    random = (f32)func_8003570C() / 4294967296.0f;
    arg1[6] = random + random - 1.0f;
    random = (f32)func_8003570C() / 4294967296.0f;
    arg1[7] = random + random - 1.0f;
    random = (f32)func_8003570C() / 4294967296.0f;
    arg1[8] = random + 2.0f;
    func_87D005E8(&arg1[6], &arg1[7], &arg1[8]);
    arg1[6] *= 500.0f;
    arg1[7] *= 500.0f;
    arg1[8] *= 1000.0f;
}

extern f32 D_80087E50[];
s16 MathUtil_Atan2s(f32 y, f32 x);
void func_8610519C(void) {
    (*(f32 *)((u8 *)(D_87F119DC) + (0x10))) = (f32) D_80087E50[(s32) (((*(s32 *)((u8 *)(D_87F119DC) + (0x1C))) * 0xFF) & 0xFFFF) >> 4];
    (*(s16 *)((u8 *)(D_87F119DC) + (0x44))) = MathUtil_Atan2s((*(f32 *)((u8 *)(D_87F119DC) + (0x18))), (*(f32 *)((u8 *)(D_87F119DC) + (0x10))));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86105204.s")

extern void func_8610519C(void);
extern void func_86105204(void);
void func_861054B0(void) {
    s32 temp_v0;
    temp_v0 = *(s32 *)((u8 *)(D_8610AD20) + (0x3C));
    switch (temp_v0) {
    case 1:
        func_8610519C();
        return;
    case 2:
        func_86105204();
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86105508.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861056C0.s")

extern f32 D_8610AC50;
void func_86105928(f32 *arg0) { f32 zero; f32 value; zero = 0.0f; value = D_8610AC50; arg0[4] = zero; arg0[5] = zero; arg0[6] = zero; arg0[23] = value; arg0[22] = value; arg0[21] = value; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86105950.s")

extern u8 D_8610A0D0[];
extern Gfx D_8610A970[];
extern void func_8003CD84(void);
extern s32 func_8004C990(s32, s32);
extern u8 * func_8004CA60(u8 *);
extern void * D_8009491C;
extern Gfx * D_800D0510;
void func_86105AD8(s32 arg0, s32 arg1) {
    void *context;
    void *temp_v0;
    s32 *countPtr;
    s32 divisor;
    s32 idx;

    if (arg0 == 5) {
        context = D_8009491C;
        temp_v0 = *(void **)((u8 *)context + 0x14);
        countPtr = *(s32 **)((u8 *)temp_v0 + 0x20);
        if (*(s32 *)((u8 *)temp_v0 + 0xC) & 0x10000000) {
            divisor = 1;
        } else {
            divisor = 3;
        }
        idx = (*countPtr % (divisor * 8)) / divisor;
        gDPPipeSync(D_800D0510++);
        gDPSetEnvColor(D_800D0510++, 0xFF, 0xFF, 0xFF, 0xFF);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60((u8 *)func_8004C990(0x45, D_8610A0D0[idx])));
        gSPDisplayList(D_800D0510++, D_8610A970);
        func_8003CD84();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86105C30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86105CD8.s")

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
void func_86105F68(s32 arg0, s32 arg1) {
    void *context;
    void *temp_v0;
    if (arg0 == 5) {
        context = D_8009491C;
        temp_v0 = *(void **)((u8 *)context + 0x14);
        gDPPipeSync(D_800D0510++);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60((u8 *)func_8004C990(0xDD, *(s32 *)temp_v0)));
        gDPSetCombine(D_800D0510++, 0xFFFFFF, 0xFFFCF238);
        gSPDisplayList(D_800D0510++, *(void **)((u8 *)(u32)D_8610AD20 + 0x6E0));
        func_8003CD84();
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86106044.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861060F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861061B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86106504.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86106630.s")

extern f32 D_8610AC74;
extern f32 D_8610AC78;
void func_86106688(void) {
    f32 var_fv0;

    var_fv0 = (*(f32 *)((u8 *)(D_87F119DC) + (0x4C)));
    if (D_8610AC74 < var_fv0) {
        (*(f32 *)((u8 *)(D_87F119DC) + (0x4C))) = (f32) D_8610AC74;
        (*(f32 *)((u8 *)(D_87F119DC) + (0x14))) = (f32) ((*(f32 *)((u8 *)(D_87F119DC) + (0x14))) * -1.0f);
        var_fv0 = (*(f32 *)((u8 *)(D_87F119DC) + (0x4C)));
    }
    if (var_fv0 < D_8610AC78) {
        (*(f32 *)((u8 *)(D_87F119DC) + (0x4C))) = (f32) D_8610AC78;
        (*(f32 *)((u8 *)(D_87F119DC) + (0x14))) = (f32) ((*(f32 *)((u8 *)(D_87F119DC) + (0x14))) * -1.0f);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86106710.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86106784.s")

extern void func_86106688();
extern void func_86106504();
void func_86106C28(void) { func_86106688(); func_86106504(D_87F119DC); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86106C54.s")

extern u8 D_8610A890[];
extern void func_8003CD84(void);
extern s32 func_8004C990(s32, s32);
extern u8 * func_8004CA60(u8 *);
extern void * D_8009491C;
extern Gfx * D_800D0510;
void func_86106E7C(s32 arg0, s32 arg1) {
    u8 *root;
    u8 *temp_a1;
    u8 *temp_a2;
    s32 temp;
    u8 alpha;

    if (arg0 != 5) {
        return;
    }
    root = D_8009491C;
    temp_a1 = *(u8 **)(root + 0x14);
    temp_a2 = *(u8 **)(temp_a1 + 0x20);
    gDPPipeSync(D_800D0510++);
    if ((*(s32 *)(temp_a1 + 0xC) << 1) < 0) {
        alpha = (u8)((1.0f - ((f32)*(s32 *)(temp_a1 + 0x1C) / 6.0f)) * 255.0f);
    } else {
        alpha = 0xFF;
    }
    if (temp_a2 == NULL) {
        temp = 0;
    } else {
        switch (*(s32 *)(temp_a2 + 0x20)) {
        case 0:
            temp = 1;
            break;
        case 1:
            temp = 2;
            break;
        case 2:
            temp = 3;
            break;
        case 3:
            temp = 4;
            break;
        }
    }
    gDPSetEnvColor(D_800D0510++, 255, 255, 255, alpha);
    gSPSegment(D_800D0510++, 0xF, func_8004CA60(func_8004C990(0xDE, temp)));
    gSPDisplayList(D_800D0510++, D_8610A890);
    func_8003CD84();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86107098.s")

extern f32 D_80088E50[];
extern void func_86107098(s32, s32, s32, s32, f32, f32, f32, f32);
extern u32 func_8003570C(void);
extern f32 D_80087E50[];
extern s32 D_8610AD20;
extern void * D_87F119DC;
void func_86107150(s32 arg0) {
    u32 rand = func_8003570C();
    u32 rem = rand % 0xA000;
    s16 angle = (s16)(rem - 0x1FFF);
    u8 *base = (u8 *)D_87F119DC + 0xD0;
    if (*(s32 *)((u8 *)D_8610AD20 + 0x3C) == 5) {
        u32 idx = (u16)angle >> 4;
        func_86107098((s32)0x80000000, arg0, *(s32 *)(base + 0), *(s32 *)(base + 4),
                      *(f32 *)(base + 8), D_80088E50[idx] * 10.0f, D_80087E50[idx] * 10.0f, 0.0f);
    }
}

extern void func_86107150(s32 arg0);
extern s32 D_8610AD20;
extern void * D_87F119DC;
void func_86107208(void) {
    void *obj;
    s32 state;
    s32 cond;

    obj = D_87F119DC;
    *(f32 *)((u8 *)obj + 0x48) += *(f32 *)((u8 *)(u32)D_8610AD20 + 0x9774) * 0.5f;
    state = *(s32 *)((u8 *)obj + 0x6C) >> 16;
    cond = 0;
    if ((state == 8) || (state == 0x2F)) {
        if (*(f32 *)((u8 *)(u32)D_8610AD20 + 0x9774) == 0.0f) {
            cond = 1;
        }
    }
    if (cond != 0) {
        func_86107150(0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861072AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86107360.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861075DC.s")

void func_86107A10(void) {}
void func_86107A10_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86107A20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86107EBC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86108018.s")

extern Gfx *D_800D0510;
extern s32 D_8610AD20;
extern void func_800088DC(void);
extern void GfxImage_FillCurrent(void *, u16);
extern void func_8000766C(void *, s32, s32, s32, s32);
extern s32 func_87F00930(void);
extern void GeoRender_AdvanceFrameCounter(void);
extern void func_8003C6B8(s32);
extern void func_86108018(void);
extern void func_87F0A5BC(u8 *);
extern void func_87F07FE8(u8 *);
extern void func_87F022F0(void);
extern void func_87F01D44(void);
extern void func_87F0C88C(u8 *);
extern void func_80008648(void);
void func_861086AC(void) {
    s32 flags;
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 1);
    func_8000766C(&D_800D0510, 0, 0, 0x140, 0xF0);
    if (func_87F00930() == 0) {
        GeoRender_AdvanceFrameCounter();
    }
    func_8003C6B8(*(s32 *)((u8 *)D_8610AD20 + 0x38));
    if (*(s32 *)((u8 *)D_8610AD20 + 0x3C) == 5) {
        func_86108018();
        if (*(s32 *)((u8 *)D_8610AD20 + 0x97DC) != 0) {
            func_87F0A5BC((u8 *)D_8610AD20 + 0x9704);
        }
        flags = *(s32 *)((u8 *)D_8610AD20 + 0x97E0);
    } else {
        flags = *(s32 *)((u8 *)D_8610AD20 + 0x97E0);
        if (!(flags & 1)) {
            func_86108018();
            flags = *(s32 *)((u8 *)D_8610AD20 + 0x97E0);
        }
    }
    if (flags & 1) {
        func_87F07FE8((u8 *)D_8610AD20 + 0x44);
        flags = *(s32 *)((u8 *)D_8610AD20 + 0x97E0);
    }
    if (flags & 2) {
        func_87F022F0();
    }
    func_87F01D44();
    func_87F0C88C((u8 *)D_8610AD20 + 0x2C);
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_8610880C.s")

extern s32 D_8610AD20;
s32 func_86108A50(s32 *arg0) {
    s32 count;
    s32 *p;
    s32 i;
    void *slot;

    count = 0;
    p = arg0;
    i = 0;
    do {
        i++;
        p++;
        p[-1] = 0;
    } while (i < 4);

    slot = (void *)((u8 *)(u32)D_8610AD20 + 0x8DE0);
    for (i = 0; i < 4; i++) {
        if (*(s32 *)((u8 *)(*(void **)slot) + 0xC) & 0x20000000) {
            *arg0++ = (s32)slot;
            count++;
        }
        slot = (void *)((u8 *)slot + 0x2C);
    }
    return count;
}

void func_86108B14(s32 *arg0, s32 *arg1) {
    s32 temp_v0;

    temp_v0 = *arg0;
    *arg0 = *arg1;
    *arg1 = temp_v0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86108B28.s")

void func_86108BE0(s32 arg0, u32 arg1)
{
  s32 temp_s4;
  s32 var_s0;
  u32 temp_s1;
  temp_s4 = arg1 * 3;
  var_s0 = 0;
  if (temp_s4 > 0)
  {
    do
    {
      temp_s1 = func_8003570C() % arg1;
      func_86108B14((temp_s1 * 4) + arg0, ((func_8003570C() % arg1) * 4) + arg0);
      var_s0 += 1;
    }
    while (var_s0 != (arg1 * 3));
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86108C90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86108EE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_8610916C.s")

extern void func_86108C90(void);
extern void func_86108EE4(void);
extern void func_8610916C(void);
void func_86109318(void) {
    s8 mode;

    mode = *(s8 *)((u8 *)(u32)D_8610AD20 + 0x97E4);
    if (mode == 0) {
        return;
    }
    switch (mode) {
    case 1:
        func_86108C90();
        break;
    case 2:
        func_86108EE4();
        break;
    case 3:
        func_8610916C();
        break;
    }
}

extern void func_87F0277C(s32);
void func_86109394(void) {
    func_87F0277C(D_8610AD20 + 0x6E8);
    func_87F0277C(D_8610AD20 + 0xD2C);
    func_87F0277C(D_8610AD20 + 0x2600);
    func_87F0277C(D_8610AD20 + 0x8914);
    func_87F0277C(D_8610AD20 + 0x8C40);
}

extern void func_800225C4(s32);
extern void func_86109318(void);
extern void func_86109394(void);
extern s32 D_8610AD20;
void func_86109404(void) {
    func_86109318();
    if (((u32)(*(u8 *)(D_8610AD20 + 0x97D9)) >> 7) != 0) {
        func_86100418();
    }
    func_86109394();
    *(s32 *)((u8 *)(u32)D_8610AD20 + 0x97B4) = *(s32 *)(D_8610AD20 + 0x97B4) - 1;
    if (*(f32 *)(D_8610AD20 + 0x9774) == 0.0f) {
        *(s32 *)(D_8610AD20 + 0x3C) = 5;
        *(s32 *)(D_8610AD20 + 0x8F20) = 0;
        func_800225C4(0x28);
        func_861008E8();
    }
}

extern void StageFade_StartFromTransparent(s32);
extern void StageContext_SetClearColor(s32);
void func_861094BC(s32 arg0) {
    (*(s32 *)((u8 *)(D_8610AD20) + (0x97E8))) = arg0;
    (*(s32 *)((u8 *)(D_8610AD20) + (0x3C))) = 7;
    (*(s32 *)((u8 *)(D_8610AD20) + (0x40))) = 8;
    StageContext_SetClearColor(0xFFFF);
    StageFade_StartFromTransparent(0xA);
}

extern s32 func_87F01A40(void);
extern s32 func_87F006AC(void);
extern void func_80021ED8(s32);
extern void func_800279C4(s32);
extern void func_86104948(void);
extern void func_861094BC(s32 arg0);
extern s32 D_8610AD20;
void func_86109510(void) {
    s32 state;
    if (StageContext_GetFadeMode() == 0) { state = func_87F01A40(); } else { state = 2; }
    switch (state) {
    case 0:
    case 2: {
        func_86100790();
        if (func_87F006AC() == 1) { func_800279C4(0xF06); }
        if (func_87F006AC() == 2) {
            *(s32 *)((u8 *)(u32)D_8610AD20 + 0x3C) = 4;
            func_800279C4(0xF07); func_80021ED8(0xD); func_86104948();
        }
        break;
    }
    case 3: { func_861094BC(0); break; }
    case 4: { func_861094BC(1); break; }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861095EC.s")

extern void func_861086AC();
extern void func_861095EC();
void func_86109864(void) {
    func_800086A4(2);
    StageFade_StartFromOpaque(0xA);
    do {
        func_80064D28();
        func_861095EC();
        func_861086AC();
    } while ((*(s32 *)((u8 *)(D_8610AD20) + (0x3C))) != 8);
}

extern s64 main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern u8 D_8610AD28[];
extern void func_80027EE0(s32);
extern u8 D_800CE060[];
extern u8 D_800CE100[];
extern void func_80006148(void *);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_8004C09C(s32);
extern void func_87F09EBC(void *, s32);
extern void func_87F06EAC(s32, void *, s32);
extern void func_8004C8C0(s32);
extern void func_87F061D0(void);
extern void func_80047588(s32, s32);
extern u8 D_1000000[];
extern u8 D_446E30[];
extern u8 D_447D00[];
extern void Asset_LoadToSegment(s32, void *, void *, s32);
extern void func_86107A20(void);
extern void func_80008514(s32);
extern void func_80008574(void);
extern void func_80006158(void);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void Gfx_FreeDisplayListBuffers(void);
extern void func_87F0F480(s32);
extern void func_86109864(void);
extern s32 D_8610AD20;
s32 fragment49_main(s32 arg0, s32 arg1) {
    u8 *ptr;
    u8 *end;
    s32 stage;

    main_pool_push_state(0x4D59524D);
    D_8610AD20 = (s32)D_8610AD28;
    *(s32 *)D_8610AD20 = arg1;

    if (*(u8 *)(*(s32 *)D_8610AD20 + 0x2182) == 15) {
        *(s8 *)((u8 *)D_8610AD20 + 0x97E4) = 1;
    } else {
        *(s8 *)((u8 *)D_8610AD20 + 0x97E4) = *(s8 *)(*(s32 *)D_8610AD20 + 0x2181);
    }

    if (*(u8 *)(*(s32 *)D_8610AD20 + 0x2180) == 4) {
        func_80027EE0(0xFFF);
    }

    ptr = D_800CE060, end = D_800CE100;
    do {
        func_80006148(ptr);
        ptr += 0x28;
    } while (ptr != end);

    Gfx_InitDisplayListBuffers(0x20000, 0);
    stage = func_800082E0(0, 0, 2, 1, 2, 1);
    func_8004C09C(0x123);
    func_87F09EBC((u8 *)D_8610AD20 + 0x9704, *(s32 *)D_8610AD20);
    func_87F06EAC(0x61, (u8 *)D_8610AD20 + 0x44, *(s32 *)D_8610AD20);
    func_8004C8C0(0x45);
    func_8004C8C0(0xDD);
    func_8004C8C0(0xDE);
    func_87F061D0();
    func_80047588(*(s32 *)((u8 *)D_8610AD20 + 0x9724) | (*(s32 *)((u8 *)D_8610AD20 + 0x4C) | 0x28), 0);
    Asset_LoadToSegment(((u32)&D_1000000 & 0x0F000000) >> 24, &D_446E30, D_447D00, 0);
    func_86107A20();
    func_80008514(stage);
    func_86109864();
    func_80008574();
    func_80006158();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x4D59524D);
    func_87F0F480(*(s32 *)D_8610AD20);
    func_80027EE0(0xFFE);
    return *(s32 *)((u8 *)D_8610AD20 + 0x97E8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109AE0.s")

extern Gfx *D_800D0510;
extern void *D_8009491C;
extern u8 D_8610A224[];
extern void func_8003CD84(void);
typedef struct {
    u8 prim_r;
    u8 prim_g;
    u8 prim_b;
    u8 prim_a;
    u8 env_r;
    u8 env_g;
    u8 env_b;
    u8 env_a;
} Func86109D64Color;
void func_86109D64(s32 arg0, s32 arg1) {
    u8 *context;
    void *record;
    Func86109D64Color *color;
    if (arg0 == 5) {
        context = (u8 *)D_8009491C;
        record = *(void **)(context + 0x14);
        color = (Func86109D64Color *)(D_8610A224 + (*(u8 *)((u8 *)record + 0x10) << 3));
        gDPPipeSync(D_800D0510++);
        gDPSetCombine(D_800D0510++, 0x30E7FF, 0x5FFE9E38);
        gDPSetPrimColor(D_800D0510++, 0, 0, color->prim_r, color->prim_g, color->prim_b, color->prim_a);
        gDPSetEnvColor(D_800D0510++, color->env_r, color->env_g, color->env_b, color->env_a);
        gSPSegment(D_800D0510++, 0xF, *(void **)((u8 *)record + 4));
        gSPDisplayList(D_800D0510++, *(void **)record);
        func_8003CD84();
    }
}

extern void *func_87F025B8(void *, void *);
extern void func_80037E3C(void *, void *, void *);
extern void func_8003F1DC(void *);
extern void func_8003F114(void *, s32, s32, s32);
extern void func_86109AE0(void);
void func_86109EAC(void *arg0, s32 arg1, s32 arg2) {
    u8 *result;
    u8 *entry;
    s32 table_value;

    result = func_87F025B8(arg0, NULL);
    if (result == NULL) return;
    table_value = arg1 * 20;
    entry = (u8 *)arg0 + table_value;
    entry[0x654] = arg1;
    *(s32 *)(entry + 0x64C) = arg2;
    func_80037E3C(result + 0x24, func_86109AE0, entry + 0x644);
    func_8003F1DC(result + 0x24);
    func_8003F114(result + 0x24, 0, -1, *(s32 *)((u8 *)arg0 + 0x694));
    *(f32 *)(result + 0x5C) = 2.25f;
    *(f32 *)(result + 0x58) = 2.25f;
    *(f32 *)(result + 0x54) = 2.25f;
}

extern void func_87F02684(void);
void func_86109F58(void) {
    func_87F02684();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109F78.s")
#endif
