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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861007D8.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100E20.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861034A8.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86105AD8.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86106E7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86107098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86107150.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86107208.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86108A50.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109404.s")

extern void StageFade_StartFromTransparent(s32);
extern void StageContext_SetClearColor(s32);
void func_861094BC(s32 arg0) {
    (*(s32 *)((u8 *)(D_8610AD20) + (0x97E8))) = arg0;
    (*(s32 *)((u8 *)(D_8610AD20) + (0x3C))) = 7;
    (*(s32 *)((u8 *)(D_8610AD20) + (0x40))) = 8;
    StageContext_SetClearColor(0xFFFF);
    StageFade_StartFromTransparent(0xA);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109510.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861098CC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109EAC.s")

extern void func_87F02684(void);
void func_86109F58(void) {
    func_87F02684();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109F78.s")
#endif
