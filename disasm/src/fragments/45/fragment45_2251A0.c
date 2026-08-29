#include "global.h"


#ifdef VERSION_US
extern u8 *D_8AB11D0C;
void func_8AB00020(void) {
    s32 i;
    ((s8 *)D_8AB11D0C)[4] = -1;
    ((s8 *)D_8AB11D0C)[5] = -1;
    i = 2;
    do {
        ((s8 *)D_8AB11D0C)[i + 4] = -1;
        ((s8 *)D_8AB11D0C)[i + 5] = -1;
        ((s8 *)D_8AB11D0C)[i + 6] = -1;
        ((s8 *)D_8AB11D0C)[i + 7] = -1;
        i += 4;
    } while (i != 10);
}
#endif

#ifdef VERSION_US
extern u8 D_8AB11D10[];
extern u8 D_8AB12668[];
extern u8 D_8AB12678[];
extern u8 D_8AB126A8[];
extern u8 D_8AB127A8[];
extern u8 D_8AB12BA8[];
extern u8 D_8AB12CB0[];
extern u32 D_8AB11D00;
extern u32 D_8AB11D04;
extern u32 D_8AB11D08;
extern u8 *D_8AB11D0C;
extern u32 D_8AB12688;
extern u32 D_8AB1268C;
extern s16 D_8AB12690;
extern s16 D_8AB12692;
extern s16 D_8AB12694;
extern s16 D_8AB12696;
extern s16 D_8AB12698;
extern s16 D_8AB1269A;
extern s16 D_8AB1269C;
extern u16 D_8AB1269E;
extern s16 D_8AB126A0;
extern u8 D_8AB13F00[];
extern u8 *D_8AB13F28;
extern s16 D_8AB13F2C;
extern void _bzero(void *, s32);
void func_8AB00084(void) {
    _bzero(D_8AB11D10, 0x958);
    _bzero(D_8AB12668, 0x10);
    _bzero(D_8AB12678, 0x10);
    _bzero(D_8AB126A8, 0x100);
    _bzero(D_8AB127A8, 0x400);
    _bzero(D_8AB12BA8, 0x100);
    _bzero(D_8AB12CB0, 0x250);
    D_8AB11D00 = 0;
    D_8AB11D04 = 0;
    D_8AB11D08 = 0;
    D_8AB11D0C = 0;
    D_8AB12688 = 0;
    D_8AB1268C = 0;
    D_8AB12690 = 1;
    D_8AB12692 = 0;
    D_8AB12694 = 0;
    D_8AB12696 = 0;
    D_8AB12698 = 0;
    D_8AB1269A = 0;
    D_8AB1269C = 0;
    D_8AB1269E = 0;
    D_8AB126A0 = 0;
    D_8AB13F28 = D_8AB13F00;
    D_8AB13F2C = 0;
}
#endif

#ifdef VERSION_US
extern u16 D_8AB1269E;

s32 func_8AB0019C(void) {
    s32 var_v1;

    var_v1 = 0;
    if ((D_8AB1269E == 0) || (D_8AB1269E == 1) || (D_8AB1269E == 2) || (D_8AB1269E == 3)) {
        var_v1 = 1;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
s16 func_8AB001D8(s16);
s16 func_8AB001D8(s16 arg0) {
    s16 result = arg0;
    switch (arg0) {
    case 0x1D8:
    case 0x1D9:
        result = 0x1D1;
        break;
    case 0x1D6:
    case 0x1DA:
        result = 0x1C8;
        break;
    case 0x201:
        result = 0x1F0;
        break;
    case 0x1FD:
        result = 0x1F7;
        break;
    case 0x1FF:
        result = 0x1E0;
        break;
    case 0x228:
        result = 0x211;
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
s16 func_8AB001D8(s16);
extern u16 D_8AB13F2E;
extern u8 D_8AB12F00[];
void func_8AB0026C(s16 arg0, s16 arg1) {
    void *sp1C;

    sp1C = ((s16) D_8AB13F2E * 4) + D_8AB12F00;
    if (func_8AB0019C() == 0) {
        (*(s16 *)((u8 *)(sp1C) + (0))) = func_8AB001D8(arg0);
        (*(s16 *)((u8 *)(sp1C) + (2))) = arg1;
        D_8AB13F2E = (s16) D_8AB13F2E + 1;
        if ((s16) D_8AB13F2E >= 0x400) {
            D_8AB13F2E = 0;
        }
    }
}
#endif

#ifdef VERSION_US
extern u8 D_8AB12F00[];
extern s32 func_8AB0019C(void);
extern s16 func_8AB001D8(s16 arg0);
s32 func_8AB002F8(s16 arg0, s16 arg1)
{
  u8 *sp24;
  s16 temp_a0;
  s32 sp1C;
  s32 var_v1;
  sp1C = 0;
  sp24 = D_8AB12F00;
  arg1 = arg1;
  if (func_8AB0019C() != 0)
  {
    return 0;
  }
  temp_a0 = func_8AB001D8(arg0);
 var_v1 = 0; loop_3: var_v1 += 1; if ((temp_a0 == (*((s16 *) (sp24 + 0)))) && (arg1 == (*((s16 *) (sp24 + 2))))) {
    sp1C = 1;
  }
  else
  {
    sp24 += 4;
    if (var_v1 != 0x400)
    {
      goto loop_3;
    }
  }
  return sp1C;
}
#endif

#ifdef VERSION_US
extern void func_8004C8C0(void); void func_8AB003A4(void) { func_8004C8C0(); }
#endif

#ifdef VERSION_US
extern void func_8004C4B0(void); void func_8AB003C4(void) { func_8004C4B0(); }
#endif

#ifdef VERSION_US
extern u8 D_8AB14680[]; extern u8 D_8AB148B0[]; extern u8 D_8AB12F00[]; extern u16 D_8AB13F2E; extern void _bzero(void *, s32); void func_8AB003E4(void) { _bzero(D_8AB14680, 0x22C); _bzero(D_8AB148B0, 0x458); _bzero(D_8AB12F00, 0x1000); D_8AB13F2E = 0; }
#endif

#ifdef VERSION_US
extern u8 D_8AB14D08[]; extern u8 D_8AB154D8[]; extern u8 D_8AB15CA8[]; extern void _bzero(void *, s32); void func_8AB00430(void) { _bzero(D_8AB14D08, 0x7D0); _bzero(D_8AB154D8, 0x7D0); _bzero(D_8AB15CA8, 0x7D0); }
#endif

#ifdef VERSION_US
typedef struct Copy34 { s32 words[13]; } Copy34;
extern Copy34 D_8AB11130;
extern Copy34 D_8AB110FC;
extern Copy34 D_8AB11060;
extern Copy34 D_8AB11094;
extern Copy34 D_8AB16508;
extern s32 func_8004C990(s32, s32);
void func_8AB00478(void) {
    Copy34 *src;
    Copy34 *dst;
    src = &D_8AB11130;
    dst = &D_8AB16508;
    *dst = *src;
    dst->words[0] = func_8004C990(0x99, 1);
}
#endif

#ifdef VERSION_US
extern s32 func_8004C990(s32, s32);
void func_8AB004E0(void) {
    Copy34 *src;
    Copy34 *dst;
    src = &D_8AB110FC;
    dst = &D_8AB16508;
    *dst = *src;
    dst->words[0] = func_8004C990(0x99, 0);
}
#endif

#ifdef VERSION_US
extern s32 func_8004C990(s32, s32);
void func_8AB00548(void) {
    Copy34 *src;
    Copy34 *dst;
    src = &D_8AB11060;
    dst = &D_8AB16508;
    *dst = *src;
    dst->words[0] = func_8004C990(0x99, 2);
}
#endif

#ifdef VERSION_US
extern s32 func_8004C990(s32, s32);
void func_8AB005B0(void) {
    Copy34 *src;
    Copy34 *dst;
    src = &D_8AB11094;
    dst = &D_8AB16508;
    *dst = *src;
    dst->words[0] = func_8004C990(0x99, 1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB00618.s")
#endif

#ifdef VERSION_US
extern Copy34 D_8AB110C8;
extern s16 D_8AB1653C;
extern void func_8AB00618(void);
extern s32 func_8004C990(s32, s32);
void func_8AB007E0(void) {
    Copy34 *src;
    Copy34 *dst;
    src = &D_8AB110C8;
    dst = &D_8AB16508;
    *dst = *src;
    dst->words[0] = func_8004C990(0x99, 2);
    D_8AB1653C = 0;
    func_8AB00618();
}
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_800459AC(u8 *, u8, u8, u16, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80044270(s16, s16, s16, s16, s32, s32, s32, s32, s32);
void func_8AB00858(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s5;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s4;

    temp_v0 = func_8004C990(arg0, arg1);
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    gDPSetEnvColor(D_800D0510++, 0, 0xFF, 0, 0xFF);
    var_s4 = 0;
    var_s5 = 0;
    do {
        func_800459AC(((*(u16 *)((u8 *)temp_v0 + 0)) << 5) * var_s4 +
                          func_8004CA60((u8 *)temp_v0),
                      *(u8 *)((u8 *)temp_v0 + 4), *(u8 *)((u8 *)temp_v0 + 5),
                      *(u16 *)((u8 *)temp_v0 + 0), 0x20, 1, 0, 0, 2, 7, 0, 0, 0);
        var_s1 = 0;
        var_s0 = var_s5;
loop_2:
        if (var_s0 < 0x1E0) {
            func_80044270(0, var_s0, 0x280, 0x20, 0, 0, 0x400, 0x400, 0);
        }
        var_s1 += 0x80;
        var_s0 += 0x80;
        if (var_s1 != 0x200) {
            goto loop_2;
        }
        var_s4 += 1;
        var_s5 += 0x20;
    } while (var_s4 != 4);
}
#endif

#ifdef VERSION_US
void func_8AB009E0(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s5;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s4;
    s32 var_s2;

    temp_v0 = func_8004C990(arg0, arg1);
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    gDPSetEnvColor(D_800D0510++, 0, 0xFF, 0, 0xFF);
    var_s4 = 0;
    var_s5 = 0;
    var_s2 = 0x200;
    do {
        func_800459AC(((*(u16 *)((u8 *)temp_v0 + 0)) << 5) * var_s4 +
                          func_8004CA60((u8 *)temp_v0),
                      *(u8 *)((u8 *)temp_v0 + 4), *(u8 *)((u8 *)temp_v0 + 5),
                      *(u16 *)((u8 *)temp_v0 + 0), 0x20, 1, 0, 0, 2, 7, 0, 0, 0);
        var_s1 = 0;
        var_s0 = var_s5;
loop_2:
        if ((var_s0 >= 0x137) && (var_s0 < 0x1AE)) {
            func_80044270(0x40, var_s0, var_s2, 0x20, 0x800, 0, 0x400, 0x400, 0);
        }
        var_s1 += 0x80;
        var_s0 += 0x80;
        if (var_s1 != var_s2) {
            goto loop_2;
        }
        var_s4 += 1;
        var_s5 += 0x20;
    } while (var_s4 != 4);
}
#endif

#ifdef VERSION_US
extern s32 func_800226C0(void); void func_8AB00B78(void) { func_800226C0(); }
#endif

#ifdef VERSION_US
void func_8AB00B98(u8 *arg0, u32 arg1) {
    *(u32 *)(arg0 + 0x28) = arg1;
    *(u32 *)(arg0 + 0x2C) = arg1;
}
#endif

#ifdef VERSION_US
extern void func_80024F20(void); void func_8AB00BA4(void) { func_80024F20(); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB00BC4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB00FF8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB01140.s")
#endif

#ifdef VERSION_US
extern s16 D_8AB12692;
extern s16 D_8AB12694;
extern s16 D_8AB12698;
void func_8AB01288(void) { D_8AB12692 = 0; D_8AB12694 = 0; D_8AB12698 = 0; }
#endif

#ifdef VERSION_US
extern s16 D_8AB12696;
extern s16 D_8AB14668;
void func_8AB012A4(void) {
    D_8AB12694 += 1;
    if (D_8AB12694 >= D_8AB12696) {
        D_8AB12694 = 0;
        D_8AB12698 += D_8AB12696;
        if (D_8AB12698 >= 0x3E9) {
            D_8AB12698 = 0x3E8;
        }
    }
    D_8AB14668 = 0;
}
#endif

#ifdef VERSION_US
extern u8 D_8AB148B0[];
void func_8AB0130C(s16 arg0) {
    if (D_8AB1269E != 0)
        *(s32 *)((u8 *)D_8AB148B0 + (arg0 * 4)) = 1;
}
#endif

#ifdef VERSION_US
s32 func_8AB01340(s16 arg0) {
    s32 result;

    result = 0;
    if (D_8AB1269E == 0) {
        return result;
    }
    result = *(s32 *)(D_8AB148B0 + (arg0 * 4));
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB01378.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB01414.s")
#endif

#ifdef VERSION_US
extern u8 D_8AB16548;

void func_8AB01454(s16 arg0) {
    void *temp_v0;

    temp_v0 = (arg0 * 0x90) + &D_8AB16548;
    (*(s16 *)((u8 *)(temp_v0) + (8))) = 2;
    (*(s16 *)((u8 *)(temp_v0) + (0x16))) = 0x1E;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB0148C.s")
#endif

#ifdef VERSION_US
extern u8 D_8AB1678A;
extern s32 func_8004C874(s32, s32);
extern void func_80026068(u32);
extern s16 D_8AB16788;
void func_8AB016E4(u8 arg0) {
    D_8AB1678A = arg0;
    func_8004C874(0, arg0);
    func_80026068(D_8AB1678A + 1);
    D_8AB16788 = 0;
}
#endif

#ifdef VERSION_US
s32 func_80026098();
extern void func_8AB016E4(u8);
extern s16 D_8AB14678;
extern s16 D_8AB16788;
extern u8 D_8AB1678A;

void func_8AB01728(void) {
    if (D_8AB14678 == 3) {
        D_8AB16788 += 1;
        if ((D_8AB16788 >= 0x29) && (func_80026098() == 0)) {
            func_8AB016E4(D_8AB1678A);
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB0178C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB01850.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB019B8.s")
#endif

#ifdef VERSION_US
extern void func_800504BC(s16 *);
extern void func_8AB019B8(s16, s16, void *);

s32 func_8AB01C04(s32 mode, void *record) {
    s16 values[2];
    s16 first;
    s16 second;
    void *preserved;

    preserved = record;
    switch (mode) {
    case 0:
        *(u16 *)((u8 *)preserved + 2) = *(u16 *)((u8 *)preserved + 2) & 0xFFFD;
        break;
    case 1:
        func_800504BC(values);
        first = *(s16 *)((u8 *)preserved + 8) + values[0];
        second = *(s16 *)((u8 *)preserved + 0xA) + values[1];
        func_8AB019B8(first, second, preserved);
        break;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB01C88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB01ED4.s")
#endif

#ifdef VERSION_US
extern void *D_8AB1678C;
void func_80042FBC(void *arg0, void *arg1);
extern s16 D_8AB126A0;
void func_8AB01F80(s16 arg0) {
    func_80042FBC(D_8AB1678C, arg0 + 1);
    D_8AB126A0 = 1;
}
#endif

#ifdef VERSION_US

void func_8AB01FBC(void) {
    D_8AB126A0 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB01FC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB02240.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB0234C.s")
#endif

#ifdef VERSION_US
u32 func_8003570C();

s32 func_8AB023EC(u32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return ((u32) (func_8003570C() >> 0xC) % arg0) & 0xFFFF;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB02438.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB02644.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB029BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB02A58.s")
#endif

#ifdef VERSION_US
extern u8 *D_8AB11D0C;
extern s16 D_8AB12696;

s32 func_8AB02BA8(void) {
    u8 state;
    s32 result;

    state = D_8AB11D0C[2];
    switch (state) {
    default:
        D_8AB12696 = 0x17;
        result = 0x1C8;
        break;
    case 1:
        D_8AB12696 = 0x17;
        result = 0x1C8;
        break;
    case 2:
        D_8AB12696 = 0x2F;
        result = 0x1DF;
        break;
    case 3:
        result = 0x20E;
        D_8AB12696 = 0x48;
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB02C20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB02CB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB02D14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB02EF8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB02F94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB02FE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB03064.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB030BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB03124.s")
#endif

void func_8AB0318C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB03194.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB0322C.s")
#endif

#ifdef VERSION_US
extern s16 D_8AB13F30[];
extern s16 D_8AB14668;
extern s16 D_8AB1466A;
extern s32 func_8AB002F8(s16, s16);
void func_8AB032F0(s16 arg0)
{
  s16 *var_s0;
  s32 var_s1;
  int new_var;
  var_s1 = 0;
 do { if (0, D_8AB1466A > 0) { var_s0 = &D_8AB13F30[0]; loop_2: D_8AB14668 = *var_s0; new_var = 0; if (func_8AB002F8(arg0, D_8AB14668)) { var_s1 += 1; var_s0 += 1; if (var_s1 < D_8AB1466A) { goto loop_2; } } } } while (0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB03394.s")
#endif

#ifdef VERSION_US
extern void func_8AB01288(void); extern void func_8AB02D14(void); void func_8AB03CE8(void) { func_8AB01288(); func_8AB02D14(); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB03D10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB03DFC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB03ED4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB04038.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB04210.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB04AE4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB04BD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB04C94.s")
#endif

#ifdef VERSION_US
void func_8AB04ED8(void) {}
void func_8AB04ED8_padding(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB04EE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB051AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB05254.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB05300.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB05538.s")
#endif
