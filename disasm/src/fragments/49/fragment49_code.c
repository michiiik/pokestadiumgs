#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861000B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100120.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861001A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861003A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100418.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_8610068C.s")

extern s32 D_8610AD20;
extern s32 StageContext_GetFadeMode(void);
extern void func_86105008(void);
extern void func_86104CAC(void);
extern void func_80007AEC(s32);
extern void func_87F00688(void);
extern void func_87F0277C(s32);

void func_86100728(void) {
    if (StageContext_GetFadeMode() == 1) {
        func_86105008();
        func_86104CAC();
        func_80007AEC(0x14);
        *(s32 *)((u8 *)(u32)D_8610AD20 + 0x3C) = 3;
        func_87F00688();
    }
    func_87F0277C(D_8610AD20 + 0x7C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100790.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861007D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100874.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861008E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100A58.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100BA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100BE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86100CFC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861018D8.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86103194.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_8610320C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86103384.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861034A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_8610362C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86103B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86103C48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861044EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861047CC.s")

void func_861048FC(void **p) {
    void *x = *p;
    func_86104B2C();
    *(f32 *)((u8 *)x + 0x18) = 0;
    *(f32 *)((u8 *)x + 0x14) = 0;
    *(u32 *)((u8 *)x + 0x0C) |= 0x02000000;
    *(f32 *)((u8 *)x + 0x10) = 0;
    *(f32 *)((u8 *)x + 0x50) = 0;
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86104B2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86104BEC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86105070.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86105F68.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861086AC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109318.s")

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
extern void func_800088A4(s32);
void func_861094BC(s32 arg0) {
    (*(s32 *)((u8 *)(D_8610AD20) + (0x97E8))) = arg0;
    (*(s32 *)((u8 *)(D_8610AD20) + (0x3C))) = 7;
    (*(s32 *)((u8 *)(D_8610AD20) + (0x40))) = 8;
    func_800088A4(0xFFFF);
    StageFade_StartFromTransparent(0xA);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109510.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861095EC.s")

extern void func_861086AC();
extern void func_861095EC();
void func_86109864(void) {
    func_800086A4(2);
    func_80007AEC(0xA);
    do {
        func_80064D28();
        func_861095EC();
        func_861086AC();
    } while ((*(s32 *)((u8 *)(D_8610AD20) + (0x3C))) != 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_861098CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109AE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109D64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109EAC.s")

extern void func_87F02684(void);
void func_86109F58(void) {
    func_87F02684();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/49/fragment49_code/func_86109F78.s")
#endif
