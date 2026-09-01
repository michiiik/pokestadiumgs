#include "global.h"


#ifdef VERSION_US
extern s32 D_84191208;
extern s32 D_8419120C;
s32 func_8411F750(s32 arg0) {
    if (arg0 == 0) {
        return D_84191208;
    }
    return D_8419120C;
}

s32 func_8411F770(s32 arg0) { if (arg0 == D_84191208) return 0; return 1; }

extern u8 *D_84193DD0; extern void func_8411FEE8(u16);
s32 func_8411F794(s32 arg0) { if (((*(u16 *)((u8 *)(u32)D_84193DD0 + (arg0 << 4) + 0x12)) & 0x2) != 0) { func_8411FEE8(0); return 1; } return 0; }

extern u8 *D_84193DD0; extern void func_8411FEE8(u16);
s32 func_8411F7E0(s32 arg0) { if (((*(u16 *)((u8 *)(u32)D_84193DD0 + (arg0 << 4) + 0x12)) & 0x4) != 0) { func_8411FEE8(0); return 1; } return 0; }

s32 func_8411F82C(s32 arg0) {
    if (*(u16 *)((u8 *)(u32)D_84193DD0 + (arg0 << 4) + 0x10) == 0x20) {
        func_8411FEE8(0);
        return 1;
    }
    return 0;
}

s32 func_8411F878(s32 arg0) {
    if (*(u16 *)((u8 *)(u32)D_84193DD0 + (arg0 << 4) + 0x10) == 7) {
        func_8411FEE8(0);
        return 1;
    }
    return 0;
}

extern u8 *D_84193DD0; extern void func_8411FEE8(u16);
s32 func_8411F8C4(s32 arg0) { if ((*(u16 *)((u8 *)(u32)D_84193DD0 + (arg0 << 4) + 0xE)) == 0) { func_8411FEE8(0); return 1; } return 0; }

extern void func_8410B104();
extern void func_800238C4(void);
extern s32 func_8411F750(s32);
extern void func_841125F4(s32, s32);
void func_8411F90C(s32 arg0, s32 arg1) {
    func_8410B104();
    func_800238C4();
    func_841125F4(func_8411F750(arg0), 0x1F);
}

extern s32 D_84191208;
extern s32 D_8419120C;
extern s32 func_8003570C(void);
extern u16 D_84183C60[];
extern u8 *D_841911E0;
extern void func_84111348(s32, s32);
extern void func_841125F4(s32, s32);
extern s32 func_8411F750(s32 arg0);
extern void func_8411FEE8(u16 arg0);
void func_8411F94C(void *arg0, void *arg1) {
    u32 v0;

    func_8411FEE8(0x64);
    func_841125F4(D_84191208, 0);
    func_841125F4(D_8419120C, 0);
    v0 = func_8003570C();
    (*(u16 *)((u8 *)(D_841911E0) + (0x98))) = D_84183C60[v0 % 5];
    func_84111348(func_8411F750((s32) arg0), 0xA);
}

extern void func_84112564(s32);
extern void func_84111348(s32, s32);
extern u8 *D_841911E0;
void func_8411F9D8(s32 arg0, s32 arg1) {
    func_8411FEE8(0x12C);
    func_841125F4(D_84191208, 0x1B);
    func_841125F4(D_8419120C, 0x1B);
    func_84112564(func_8411F750(arg0));
    *(u16 *)(D_841911E0 + 0x98) = 0;
    func_84111348(func_8411F750(arg0), 0x12);
}

extern void func_841125F4(s32, s32); void func_8411FA50(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0x16); }

extern void func_841125F4(s32, s32); void func_8411FA7C(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 2); }

extern void func_841125F4(s32, s32); void func_8411FAA8(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 8); }

extern void func_841125F4(s32, s32); void func_8411FAD4(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 6); }

extern void func_841125F4(s32, s32); void func_8411FB00(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 7); }

void func_8411FB2C(s32 arg0, s32 arg1) {
    func_841125F4(func_8411F750(arg0), 0xF);
}
void func_8411FB2C_padding(void) {}

void func_8411FB60(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0x10); }

void func_8411FB8C(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0x11); }

void func_8411FBB8(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 4); }

void func_8411FBE4(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 5); }

void func_8411FC10(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0x13); }

void func_8411FC3C(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0x17); }

void func_8411FC68(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 3); }

extern u8 D_841911F9;
void func_8411FC94(s32 arg0, s32 arg1) {
    if (D_841911F9 == 5) {
        func_841125F4(func_8411F750(0), 0x22);
    } else {
        func_841125F4(func_8411F750(0), 0x18);
    }
}

void func_8411FCF4(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0xC); }

void func_8411FD20(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0x19); }

void func_8411FD4C(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0x12); }

void func_8411FD78(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0x14); }

void func_8411FDA4(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 9); }

void func_8411FDD0(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0xB); }

void func_8411FDFC(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0xD); }

void func_8411FE28(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0x15); }

void func_8411FE54(s32 arg0, s32 arg1) { func_841125F4(func_8411F750(arg0), 0x1C); }

s32 func_8411FE80(void) {
    if ((*(u8 *)((u8 *)(D_84193DD0) + (2))) == 0) {
        return 1;
    }
    (*(u8 *)((u8 *)(D_84193DD0) + (2))) = 0U;
    return 0;
}

void func_8411FEAC(u8 arg0, u16 arg1, u8 arg2) {
    D_84193DD0[0] = arg0;
    *(u16 *)(D_84193DD0 + 4) = arg1;
    D_84193DD0[2] = 1;
    D_84193DD0[8] = arg2;
}

extern u8 *D_84193DD0;
void func_8411FEE8(u16 arg0) {
    *(u16 *)(D_84193DD0 + 6) = arg0;
}

void func_8411FEFC(void) {
    if (*(u16 *)(D_84193DD0 + 6) != 0) {
        *(u16 *)(D_84193DD0 + 6) -= 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_8411FF1C.s")

f32 *func_841202D0(f32 *arg0, f32 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
    return arg0;
}

s16 *func_841202F0(s16 *arg0, s16 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
    return arg0;
}

s32 BattleAnim_StepToS16(s16* arg0, s16 arg1, s16 arg2) {
    s16 temp_v0 = arg1 - *arg0;

    if (arg2 < 0) {
        arg2 *= -1;
    }

    if (temp_v0 > 0) {
        temp_v0 -= arg2;
        if (temp_v0 >= 0) {
            *arg0 = arg1 - temp_v0;
        } else {
            *arg0 = arg1;
        }
    } else {
        temp_v0 += arg2;
        if (temp_v0 <= 0) {
            *arg0 = arg1 - temp_v0;
        } else {
            *arg0 = arg1;
        }
    }

    if (arg1 == *arg0) {
        return 0;
    }

    return 1;
}

extern f64 D_84189C30;
extern f64 D_84189C38;
void func_841203B4(f32 *arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    f64 temp_fv1;

    temp_fv0 = *arg0;
    *arg0 = ((arg1 - temp_fv0) * arg2) + temp_fv0;
    temp_fv1 = (f64)*(volatile f32 *)arg0;
    if ((temp_fv1 < D_84189C30) && (D_84189C38 < temp_fv1)) {
        *arg0 = 0.0f;
    }
}

extern f32 D_80087E50[];
extern f32 D_80088E50[0x1000];
void BattleAnim_Vec3fSetPolarXZ(void *arg0, f32 arg1, s16 arg2) {
    s32 index;

    index = ((u16) arg2) >> 4;
    (*(f32 *)((u8 *)(arg0) + (0))) = D_80088E50[index] * arg1;
    (*(f32 *)((u8 *)(arg0) + (8))) = D_80087E50[index] * arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84120464.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_841204BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_8412060C.s")

extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_8411EFE4(s32);
extern u8 *D_841911E0;
void func_8412063C(void *arg0) {
    func_8411EFE4((s32) arg0);
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(*(void **)D_841911E0) + 0xC0), 0.0f, 1.0f, 0.0f);
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(arg0) + 0x30), 1.0f, 1.0f, 1.0f);
    (*(u8 *)((u8 *)(arg0) + (0x2))) &= 0xFFFD;
    func_8412060C(arg0);
    (*(u8 *)((u8 *)(arg0) + (0x1C))) = 0;
    (*(u8 *)((u8 *)(arg0) + (0x61F))) = 0xFF;
}

void func_841206D0(void *arg0)
{
  *((u8 *) (((u8 *) arg0) + 2)) = (u8) ((*((u8 *) (((u8 *) arg0) + 2))) & 0xFFFD);
  *(((u8 *) arg0) + 0x61F) = 0xFF;
  func_8412060C();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84120700.s")

extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern s32 D_84191208;
extern s32 D_8419120C;
extern void func_8411EF08(u8 *arg0);
extern void func_84120700(s32);
extern void func_8410B578(f32 arg0);
extern u8 *D_84193DD0;
extern f32 D_84189C4C;
extern f32 D_84189C54;
void func_84120960(void *arg0, void *arg1) {
    f32 f1;
    (*(s16 *)((u8 *)(arg1) + (0x7EA))) = 0;
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(arg0) + (0xC0)), 0.0f, 1.0f, 0.0f);
    func_8411EF08((u8 *) D_84191208);
    func_8411EF08((u8 *) D_8419120C);
    func_84120700(D_84191208);
    func_84120700(D_8419120C);
    if (*(u16 *)((u8 *) D_84193DD0 + 0x12) & 8) {
        Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(D_84191208) + 0x30), D_84189C4C, D_84189C4C, D_84189C4C);
    }
    f1 = D_84189C54;
    if (*(u16 *)((u8 *) D_84193DD0 + 0x22) & 8) {
        Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(D_8419120C) + 0x30), f1, f1, f1);
    }
    func_8410B578(0.0f);
}

extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern s32 D_84191208;
extern s32 D_8419120C;
extern void func_8411EF08(u8 *arg0);
extern s32 func_8411E164(s32 arg0);
extern void func_84120700(s32);
extern void func_8410B578(f32 arg0);
void func_84120A50(void *arg0, void *arg1) {
    (*(s16 *)((u8 *)(arg1) + (0x7EA))) = 0;
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(arg0) + (0xC0)), 0.0f, 1.0f, 0.0f);
    func_8411EF08((u8 *) D_84191208);
    func_8411EF08((u8 *) D_8419120C);
    func_84120700(func_8411E164((s32) arg1));
    func_8410B578(0.0f);
}

extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern s32 D_84191208;
extern s32 D_8419120C;
extern void func_8411EF08(u8 *arg0);
extern void func_84120700(s32);
extern void func_8410B578(f32 arg0);
extern u8 *D_84193DD0;
extern f32 D_84189C58;
extern f32 D_84189C60;
void func_84120AC4(void *arg0, void *arg1) {
    f32 f1;
    (*(s16 *)((u8 *)(arg1) + (0x7EA))) = 0;
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(arg0) + (0xC0)), 0.0f, 1.0f, 0.0f);
    func_8411EF08((u8 *) D_84191208);
    func_8411EF08((u8 *) D_8419120C);
    func_84120700(D_84191208);
    func_84120700(D_8419120C);
    if (*(u16 *)((u8 *) D_84193DD0 + 0x12) & 8) {
        Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(D_84191208) + 0x30), D_84189C58, D_84189C58, D_84189C58);
    }
    f1 = D_84189C60;
    if (*(u16 *)((u8 *) D_84193DD0 + 0x22) & 8) {
        Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(D_8419120C) + 0x30), f1, f1, f1);
    }
    func_8410B578(0.0f);
}

extern void func_84120700(s32);
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
void func_8411EF2C(s32 arg0);
void func_8410B578(f32 arg0);
void func_84120BB4(u8 *arg0, s32 arg1) {
    (*(s16 *)((u8 *)(arg1) + (0x7EA))) = 0;
    Vec3f_SetComponentsDuplicate((f32 *) (arg0 + 0xC0), 0.0f, 1.0f, 0.0f);
    func_8411EF2C(arg1);
    func_84120700(D_84191208);
    func_84120700(D_8419120C);
    func_8410B578(0.0f);
}

extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_8411EFE4(s32);
extern void func_8411EF2C(s32);
extern void func_8410B578(f32 arg0);
void func_84120C20(void *arg0, void *arg1) {
    (*(s16 *)((u8 *)(arg1) + (0x7EA))) = 0;
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(arg0) + (0xC0)), 0.0f, 1.0f, 0.0f);
    func_8411EFE4((s32) arg1);
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(arg1) + (0x30)), 1.0f, 1.0f, 1.0f);
    func_8411EF2C((s32) arg1);
    (*(u8 *)((u8 *)(arg1) + (0x1C))) = 0;
    func_8410B578(0.0f);
}

extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern s32 D_84191208;
extern s32 D_8419120C;
extern void func_8411EF08(u8 *arg0);
extern void func_84120700(s32);
extern s32 func_8411E164(s32 arg0);
extern void func_841125F4(s32, s32);
extern void func_8410B578(f32 arg0);
extern f32 D_84189C70;
extern void func_84120464(s32, s32, s32);
void func_84120CA4(void *arg0, void *arg1) {
    (*(s16 *)((u8 *)(arg1) + (0x7EA))) = 0;
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(arg0) + (0xC0)), 0.0f, 1.0f, 0.0f);
    func_8411EF08((u8 *) D_84191208);
    func_8411EF08((u8 *) D_8419120C);
    func_84120700(D_84191208);
    func_84120700(D_8419120C);
    func_841125F4(func_8411E164((s32) arg1), 0);
    func_8410B578(0.0f);
}

extern s32 D_84191208;
extern s32 D_8419120C;
extern void func_8411EFE4(s32);
extern void func_8411EF08(u8 *);
extern void func_84120700(s32);
extern s32 func_8411E164(s32);
extern void func_841125F4(s32, s32);
extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_8410B578(f32);
void func_84120D34(void *arg0, void *arg1)
{
  s32 temp_v1;
  *((s16 *) (((u8 *) arg1) + 0x7EA)) = 0;
  func_8411EFE4(D_84191208);
  func_8411EFE4(D_8419120C);
  func_8411EF08((u8 *) D_84191208);
  func_8411EF08((u8 *) D_8419120C);
  temp_v1 = (s32) arg1;
  func_84120700(D_84191208);
  func_84120700(D_8419120C);
  func_841125F4(func_8411E164(temp_v1), 0);
  Vec3f_SetComponentsDuplicate((f32 *) (((u8 *) arg0) + 0xC0), 0.0f, 1.0f, 0.0f);
  temp_v1 = *((s16 *) (((u8 *) arg1) + 0x1A));
  if ((temp_v1 != 0x32) && ((*((s16 *) (((u8 *) arg1) + 0x1A))) != 0x33))
  {
    *((u8 *) (((u8 *) arg1) + 1)) &= 0xFFFE;
    *((f32 *) (((u8 *) arg1) + 0x28)) = 30.0f;
    if (arg1)
    {
    }
  }
  func_8410B578(0.0f);
}

extern void func_8411EFE4(s32);
s32 func_8411E164(s32 arg0);
void func_8411EE74(u8 *arg0);
void func_8411EF08(u8 *arg0);
void func_8410B578(f32 arg0);
void func_8411EF2C(s32 arg0);
s32 func_8411E164(s32 arg0);
void func_8411EE74(u8 *arg0);
void func_8411EF08(u8 *arg0);
void func_8410B578(f32 arg0);
void func_84120E14(s32 arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x7EA))) = 0;
    func_8411EFE4(func_8411E164(arg0));
    func_8411EE74((u8 *) arg0);
    func_8411EF08(func_8411E164(arg0));
    func_84120700(func_8411E164(arg0));
    func_8410B578(0.0f);
}

void func_84120E7C(u8 *arg0) {
    s32 var_s1;
    u8 *var_s0;
    u8 *var_s2;
    u8 *var_s3;
    u8 *var_s4;
    var_s0 = arg0;
    var_s1 = 0;
    var_s2 = arg0 + 0x2FC;
    var_s3 = arg0 + 0x2F6;
    var_s4 = arg0 + 0x308;
    do {
        *(s16 *)(var_s0 + 0x444) = 0;
        var_s0[0x2F5] = 0x80;
        var_s0[0x2D9] |= 1;
        func_841202D0((f32 *)var_s2, (f32 *)(arg0 + 0x24));
        func_841202F0((s16 *)var_s3, (s16 *)(arg0 + 0x1E));
        func_841202D0((f32 *)var_s4, (f32 *)(arg0 + 0x30));
        var_s1 += 1;
        var_s0 += 0x170;
        var_s2 += 0x170;
        var_s3 += 0x170;
        var_s4 += 0x170;
        *(s16 *)(var_s0 + 0x188) = *(s16 *)(arg0 + 0x20);
    } while (var_s1 != 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84120F5C.s")

extern void func_84120464(s32, s32, s32);
extern s32 D_84183C90;
void func_841210CC(s32 arg0) {
    Vec3f_SetComponentsDuplicate(arg0 + 0x5E4, 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(arg0 + 0x5F0, 0.0f, 0.0f, 0.0f);
    func_84120464(arg0, D_84183C90, 0x4000);
}

extern void func_841204BC(void *, s32, s32, s32, f32);
void func_84121130(void *arg0) { f32 d = *(f32 *)((u8 *)arg0 + 0x28) - *(f32 *)((u8 *)arg0 + 0x650); if (((*(f32 *)((u8 *)arg0 + 0x28) - *(f32 *)((u8 *)arg0 + 0x650))) >= 200.0f) { *(f32 *)((u8 *)arg0 + 0x28) = *(f32 *)((u8 *)arg0 + 0x650) + 200.0f; return; } func_841204BC(arg0, 0x3FB9999A, 0x3C75C28F, 0x4000, 18.0f); ; if (((*(f32 *)((u8 *)arg0 + 0x28) - *(f32 *)((u8 *)arg0 + 0x650))) >= 200.0f) { *(f32 *)((u8 *)arg0 + 0x28) = *(f32 *)((u8 *)arg0 + 0x650) + 200.0f; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_841211CC.s")

void func_84121260(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x5FE))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x5FC))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x623))) = 0;
    (*(s8 *)((u8 *)(arg0) + (0x624))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x604))) = (s16) (*(s16 *)((u8 *)(arg0) + (0x20)));
    func_84120464((s32) arg0, D_84183C90, 0x4000);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_841212A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_8412142C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_841214C0.s")

void func_84121708(u8 *arg0) {
    *(s16 *)(arg0 + 0x5FE) = 0;
    *(s16 *)(arg0 + 0x5FC) = 0;
    *(u8 *)(arg0 + 0x623) = 0;
    *(u8 *)(arg0 + 0x624) = 0;
    *(s16 *)(arg0 + 0x604) = *(s16 *)(arg0 + 0x20);
}

s32 func_841211CC(void *, s16, s16);
void func_84121724(void *arg0) {
    if ((*(s8 *)((u8 *)(arg0) + (0x623))) == 0) {
        (*(s16 *)((u8 *)(arg0) + (0x5FE))) = Math_StepToS32((s32) (*(s16 *)((u8 *)(arg0) + (0x5FE))), 0x2C14, 0xB6, 0xB6);
        if (func_841211CC(arg0, (*(s16 *)((u8 *)(arg0) + (0x5FE))), (s16) (func_8411E1D4((s32) arg0) * -0x4000)) != 0) {
            (*(s8 *)((u8 *)(arg0) + (0x623))) = (s8) ((*(s8 *)((u8 *)(arg0) + (0x623))) + 1);
        }
    }
    if ((*(s8 *)((u8 *)(arg0) + (0x623))) == 1) {
        (*(s16 *)((u8 *)(arg0) + (0x604))) = (s16) (func_8411E1D4((s32) arg0) * -0x4000);
    }
    (*(s16 *)((u8 *)(arg0) + (0x20))) = (s16) (*(s16 *)((u8 *)(arg0) + (0x604)));
}

void func_841217C8(u8 *arg0) {
    *(s16 *)(arg0 + 0x5FE) = 0;
    *(s16 *)(arg0 + 0x5FC) = 0;
    *(u8 *)(arg0 + 0x623) = 0;
    *(u8 *)(arg0 + 0x624) = 0;
    *(s16 *)(arg0 + 0x604) = *(s16 *)(arg0 + 0x20);
}

extern s32 func_841211CC(void *, s16, s16);
void func_841217E4(u8 *arg0) {
    extern f32 func_8411E1B4(u8 *);
    if (*(s8 *)(arg0 + 0x623) < 3) {
        *(s16 *)(arg0 + 0x5FE) = Math_StepToS32(*(s16 *)(arg0 + 0x5FE), 0x3FFC, 0x16C, 0x16C);
        if (func_841211CC(arg0, *(s16 *)(arg0 + 0x5FE), (s16)(func_8411E1D4((s32)arg0) << 14)) != 0) {
            *(s8 *)(arg0 + 0x623) = *(s8 *)(arg0 + 0x623) + 1;
        }
    }
    if (*(s8 *)(arg0 + 0x623) >= 3) {
        func_841211CC(arg0, *(s16 *)(arg0 + 0x5FE), (s16)(func_8411E1D4((s32)arg0) << 14));
        *(f32 *)(arg0 + 0x28) = (f32)Math_StepToS32((s32)*(f32 *)(arg0 + 0x28), (s32)((f64)(-func_8411E1B4(arg0)) * 3.5), 5, 5);
    }
    *(s16 *)(arg0 + 0x20) = *(s16 *)(arg0 + 0x604);
}

extern void func_84120E7C(u8 *);
void func_841218EC(u8 *arg0) {
    *(s16 *)(arg0 + 0x5FE) = 0;
    *(s16 *)(arg0 + 0x5FC) = 0;
    arg0[0x623] = 0;
    arg0[0x624] = 0;
    *(f32 *)(arg0 + 0x60C) = 0.0f;
    func_84120E7C(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84121920.s")

extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern u8 *D_841911E0;
extern f32 D_80087E50[];
extern f32 D_80088E50[0x1000];
void func_84121AB8(void *arg0) {
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(*(void **)D_841911E0) + 0xC0), 0.0f, 1.0f, 0.0f);
    (*(s16 *)((u8 *)(arg0) + (0x5FE))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x600))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x5FC))) = 0;
    (*(u8 *)((u8 *)(arg0) + (0x623))) = 0;
    (*(f32 *)((u8 *)(arg0) + (0x60C))) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84121B18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84121CAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84121DE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_8412230C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84122448.s")

void func_84122990(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84122998.s")

void func_84122A04(u8 *arg0) {
    arg0[0x623] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84122A0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84122A78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84122AB8.s")

extern f32 D_84189CC4;

void func_84122C94(void *arg0) {
    f32 temp_fv0;

    (*(s16 *)((u8 *)(arg0) + (0x5FE))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x600))) = 0xAAA;
    temp_fv0 = (*(f32 *)((u8 *)(arg0) + (0x30)));
    (*(f32 *)((u8 *)(arg0) + (0x60C))) = (f32) D_84189CC4;
    (*(f32 *)((u8 *)(arg0) + (0x5F0))) = temp_fv0;
    (*(f32 *)((u8 *)(arg0) + (0x5E4))) = temp_fv0;
    (*(f32 *)((u8 *)(arg0) + (0x5F4))) = (f32) (*(f32 *)((u8 *)(arg0) + (0x34)));
    (*(f32 *)((u8 *)(arg0) + (0x5F8))) = (f32) (*(f32 *)((u8 *)(arg0) + (0x38)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84122CCC.s")

void func_84122D74(s32 arg0) {
    Vec3f_SetComponentsDuplicate(arg0 + 0x5E4, 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(arg0 + 0x5F0, 0.0f, 0.0f, 0.0f);
    func_84120464(arg0, D_84183C90, 0x4000);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84122DD8.s")

typedef struct S1_Vec3f S1_Vec3f;
struct S1_Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
};
typedef float S1_MtxF_t[4][4];
typedef union {
    S1_MtxF_t mf;
    struct {
        float xx, yx, zx, wx,
              xy, yy, zy, wy,
              xz, yz, zz, wz,
              xw, yw, zw, ww;
    };
} S1_MtxF;
void GalleryCamera_RotateVecByMatrix(S1_Vec3f* arg0, S1_MtxF* arg1) {
    f32 x = (arg1->mf[0][0] * arg0->x) + (arg1->mf[0][1] * arg0->y) + (arg1->mf[0][2] * arg0->z);
    f32 y = (arg1->mf[1][0] * arg0->x) + (arg1->mf[1][1] * arg0->y) + (arg1->mf[1][2] * arg0->z);
    f32 z = (arg1->mf[2][0] * arg0->x) + (arg1->mf[2][1] * arg0->y) + (arg1->mf[2][2] * arg0->z);

    arg0->x = x;
    arg0->y = y;
    arg0->z = z;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84122EEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84123034.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84123150.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_8412328C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84123468.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84123664.s")

extern f32 D_84189D0C;

void func_84123828(void *arg0) {
    (*(s16 *)((u8 *)(arg0) + (0x600))) = 0x71C;
    (*(f32 *)((u8 *)(arg0) + (0x60C))) = (f32) D_84189D0C;
    (*(f32 *)((u8 *)(arg0) + (0x5F0))) = (f32) (*(f32 *)((u8 *)(arg0) + (0x30)));
    (*(f32 *)((u8 *)(arg0) + (0x5F4))) = (f32) (*(f32 *)((u8 *)(arg0) + (0x34)));
    (*(f32 *)((u8 *)(arg0) + (0x5F8))) = (f32) (*(f32 *)((u8 *)(arg0) + (0x38)));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84123858.s")

void func_84123914(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_8412391C.s")

void func_841239E0(u8 *arg0) {}

extern f32 func_8415BCD8(void);
extern f32 D_84189D2C;
extern void func_841203B4(f32 *arg0, f32 arg1, f32 arg2);
void func_841239E8(void *arg0)
{
  f32 sp1C;
  int new_var;
  sp1C = (1.0f - func_8415BCD8()) * D_84189D2C;
  func_841203B4((f32 *) (((u8 *) arg0) + 0x30), 1.0f - sp1C, 0.5f);
  func_841203B4((f32 *) (((u8 *) arg0) + 0x34), 1.0f + sp1C, 0.5f);
  new_var = 0x38;
  func_841203B4((f32 *) (((u8 *) arg0) + new_var), 1.f - sp1C, 0.5f);
}

extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_84120464(s32, s32, s32);
extern void func_8411EFE4(s32);
extern void func_8411EF2C(s32);
extern void func_8410B578(f32 arg0);
extern s32 D_84191208;
extern s32 D_8419120C;
extern void func_8411FEE8(u16);
extern void func_841125F4(s32, s32);
extern s32 func_8003570C(void);
extern u16 D_84183C60[];
extern u8 *D_841911E0;
extern void func_84111348(s32, s32);
void func_84123A90(void *arg0) {
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(arg0) + (0x5E4)), 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate((f32 *)((u8 *)(arg0) + (0x5F0)), 0.0f, 0.0f, 0.0f);
    func_84120464((s32) arg0, 0x3F666666, 0x4000);
    (*(s16 *)((u8 *)(arg0) + (0x606))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x602))) = 0;
    (*(u8 *)((u8 *)(arg0) + (0x623))) = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84123B08.s")

void func_84123CD8(u8 *arg0) {
    *(s16 *)(arg0 + 0x5FE) = 0;
    *(s16 *)(arg0 + 0x5FC) = 0;
    *(u8 *)(arg0 + 0x623) = 0;
    *(u8 *)(arg0 + 0x624) = 0;
    *(f32 *)(arg0 + 0x60C) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84123CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84123E74.s")

extern f32 Math_StepToF(f32, f32, f32, f32);
extern f32 D_84189D38;
extern f32 D_84189D3C;
void func_84123EB0(u8 *arg0) {
    *(s8 *)(arg0 + 0x623) = *(s8 *)(arg0 + 0x623) + 1;
    if (*(s8 *)(arg0 + 0x623) >= 0xF) {
        f32 limit = D_84189D38;
        f32 step = D_84189D3C;
        f32 current = *(f32 *)(arg0 + 0x60C);
        *(f32 *)(arg0 + 0x60C) = Math_StepToF(current, step, limit, limit);
        *(f32 *)(arg0 + 0x34) = Math_StepToF(
            *(f32 *)(arg0 + 0x34), *(f32 *)(arg0 + 0x5E8),
            *(f32 *)(arg0 + 0x60C), *(f32 *)(arg0 + 0x60C));
        *(f32 *)(arg0 + 0x38) = Math_StepToF(
            *(f32 *)(arg0 + 0x38), *(f32 *)(arg0 + 0x5EC),
            *(f32 *)(arg0 + 0x60C), *(f32 *)(arg0 + 0x60C));
        *(f32 *)(arg0 + 0x30) = Math_StepToF(
            *(f32 *)(arg0 + 0x30), *(f32 *)(arg0 + 0x5E4),
            *(f32 *)(arg0 + 0x60C), *(f32 *)(arg0 + 0x60C));
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84123F60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EFE0/func_84124104.s")
#endif
