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
// RGBA16 preview image address returned by func_80043678.
//@src/43700.c
extern s32 D_8AB16794;
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
extern s32 func_8004C8C0(s32);
void func_8AB003A4(s32 archive) {
    func_8004C8C0(archive);
}
#endif

#ifdef VERSION_US
extern s32 func_8004C4B0(s32);
void func_8AB003C4(s32 entry) {
    func_8004C4B0(entry);
}
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
extern void func_80024F20(s32, s32, s32);
void func_8AB00BA4(s32 event, s32 parameter, s32 variant) {
    func_80024F20(event, parameter, variant);
}
#endif

#ifdef VERSION_US
extern Gfx D_8AB11168[];
extern s32 func_8004C990(s32, s32);
extern Gfx * D_800D0510;
void func_8AB00BC4(s16 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    gSPDisplayList(D_800D0510++, D_8AB11168);
    gDPSetEnvColor(D_800D0510++, arg3, arg4, arg5, 255);
    if (arg2 < 0) arg2 = 0;
    if (arg2 >= 1000) arg2 = 999;
    if (arg2 >= 100) arg0 += 20;
    else if (arg2 >= 10) arg0 += 10;
    arg0 -= 12;
    func_8004D1FC(func_8004C990(0x118, arg2 % 10));
    gSPTextureRectangle(D_800D0510++, arg0 << 2, arg1 << 2, (arg0 + 24) << 2, (arg1 + 32) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    if (arg2 >= 100) {
        arg0 -= 20;
        func_8004D1FC(func_8004C990(0x118, (arg2 / 10) % 10));
        gSPTextureRectangle(D_800D0510++, arg0 << 2, arg1 << 2, (arg0 + 24) << 2, (arg1 + 32) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
        arg0 -= 20;
        func_8004D1FC(func_8004C990(0x118, (arg2 / 100) % 10));
        gSPTextureRectangle(D_800D0510++, arg0 << 2, arg1 << 2, (arg0 + 24) << 2, (arg1 + 32) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    } else if (arg2 >= 10) {
        arg0 -= 20;
        func_8004D1FC(func_8004C990(0x118, (arg2 / 10) % 10));
        gSPTextureRectangle(D_800D0510++, arg0 << 2, arg1 << 2, (arg0 + 24) << 2, (arg1 + 32) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    }
}
#endif

#ifdef VERSION_US
extern s32 func_8004C990(s32, s32);
extern Gfx * D_800D0510;
extern Gfx D_8AB11168[];
void func_8AB00FF8(s16 arg0, s16 arg1) {
    u8 color[8];
    *(u32 *)color = 0xFF500080;
    gSPDisplayList(D_800D0510++, D_8AB11168);
    gDPSetEnvColor(D_800D0510++, ((struct {u8 r,g,b,a;} *)color)->r, ((struct {u8 r,g,b,a;} *)color)->g, ((struct {u8 r,g,b,a;} *)color)->b, ((struct {u8 r,g,b,a;} *)color)->a);
    func_8004D1FC(func_8004C990(0x115, 0));
    gSPTextureRectangle(D_800D0510++, arg0 << 2, arg1 << 2, (arg0 + 0x30) << 2, (arg1 + 0x30) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
}
#endif

#ifdef VERSION_US
extern s32 func_8004C990(s32, s32);
extern Gfx * D_800D0510;
extern Gfx D_8AB11168[];
void func_8AB01140(s16 arg0, s16 arg1) {
    u8 color[8];
    *(u32 *)color = 0x1E82FF80;
    gSPDisplayList(D_800D0510++, D_8AB11168);
    gDPSetEnvColor(D_800D0510++, ((struct {u8 r,g,b,a;} *)color)->r, ((struct {u8 r,g,b,a;} *)color)->g, ((struct {u8 r,g,b,a;} *)color)->b, ((struct {u8 r,g,b,a;} *)color)->a);
    func_8004D1FC(func_8004C990(0x115, 1));
    gSPTextureRectangle(D_800D0510++, arg0 << 2, arg1 << 2, (arg0 + 0x30) << 2, (arg1 + 0x30) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
}
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
extern void func_8AC05E40(s32, void *, s32);
extern void func_8AC06400(void *, void *);
extern u8 D_8AB16548;
void func_8AB01378(s32 arg0, void *arg1, s16 arg2) {
    void *temp_v0;
    void *temp_v1;
    temp_v0 = (arg2 * 0x90) + &D_8AB16548;
    *(void **)temp_v0 = arg1;
    *(s16 *)((u8 *)temp_v0 + 8) = 0;
    temp_v1 = (u8 *)temp_v0 + 0x18;
    *(s16 *)((u8 *)temp_v0 + 0xA) = *(s16 *)((u8 *)arg1 + 8);
    *(s16 *)((u8 *)temp_v0 + 0xC) = *(s16 *)((u8 *)arg1 + 0xA);
    *(s16 *)((u8 *)temp_v0 + 0x12) = 0;
    *(s16 *)((u8 *)temp_v0 + 0x14) = 0;
    *(s16 *)((u8 *)temp_v0 + 0xE) = *(s16 *)((u8 *)temp_v0 + 0xA);
    *(s16 *)((u8 *)temp_v0 + 0x10) = *(s16 *)((u8 *)temp_v0 + 0xC);
    func_8AC05E40(arg0, *(void **)((u8 *)arg1 + 4), (s32)temp_v1);
    func_8AC06400(temp_v1, arg1);
    *(s32 *)((u8 *)temp_v0 + 0x8C) = 1;
}
#endif

#ifdef VERSION_US
extern u8 D_8AB16548;
void func_8AB01414(s16 arg0) {
    void *temp_v0;

    temp_v0 = (arg0 * 0x90) + &D_8AB16548;
    *(s16 *)((u8 *)temp_v0 + 8) = 1;
    *(s16 *)((u8 *)temp_v0 + 0x10) = *(s16 *)((u8 *)temp_v0 + 0xC);
    *(s16 *)((u8 *)temp_v0 + 0x14) = -0xF;
}
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
extern void *func_8004C874(s32, s32);
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
typedef struct TextCallbackColorBytes { u8 bytes[4]; } TextCallbackColorBytes;
extern void func_800504BC(s16 *);
void TextNumber_DrawCallback(s32 phase, void *record) {
    u8 *node;
    TextCallbackColorBytes color;
    s16 *value_pointer;
    s16 coordinates[2];
    s16 x;
    s16 y;
    s16 value;
    node = record;
    value_pointer = *(s16 **)(node + 32);
    value = *value_pointer;
    if (value < 0) { value = 0; }
    switch (phase) {
    case 0:
        *(u16 *)(node + 2) &= 0xFFFD;
        break;
    case 1:
        func_800504BC(coordinates);
        x = *(s16 *)(node + 8) + coordinates[0];
        y = *(s16 *)(node + 10) + coordinates[1];
        color = *(TextCallbackColorBytes *)(node + 40);
        func_8AB00BC4(x, y, value, color.bytes[0], color.bytes[1], color.bytes[2]);
        break;
    }
}
#endif

#ifdef VERSION_US
extern u8 D_8AB11400[];
extern void func_800498C4(void);
extern void Font_EnableTwoCycleTexturing(void);
extern void Font_DisableTwoCycleTexturing(void);
extern void func_800496A4(s32, s32);
extern s32 func_80049668(s32);
extern void func_8004989C(s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800497E4(s32, s32, s32, s32);
extern void func_800495F8(s32, s32, s32, const char *, ...);
extern void func_800499EC(void);
s32 TextLabel_DrawCallback(s32 phase, void *record) {
    s16 x;
    s16 y;
    s16 coordinates[2];
    char *text;
    u16 alignment;
    TextCallbackColorBytes foreground;
    TextCallbackColorBytes shadow;
    u8 *node;
    node = record;
    text = *(char **)(node + 32);
    switch (phase) {
    case 0:
        *(u16 *)(node + 2) &= 0xFFFD;
        break;
    case 1:
        if (((u32)node == D_8AB11D00) && (text == NULL)) { text = (char *)D_8AB11400; }
        func_800504BC(coordinates);
        x = *(s16 *)(node + 8) + coordinates[0];
        y = *(s16 *)(node + 10) + coordinates[1];
        foreground = *(TextCallbackColorBytes *)(node + 40);
        shadow = *(TextCallbackColorBytes *)(node + 44);
        func_800498C4();
        Font_EnableTwoCycleTexturing();
        func_800496A4(*(u16 *)(node + 36), 0);
        func_80049668(1);
        func_8004989C(32);
        func_8004972C(foreground.bytes[0], foreground.bytes[1], foreground.bytes[2], foreground.bytes[3]);
        func_800497E4(shadow.bytes[0], shadow.bytes[1], shadow.bytes[2], shadow.bytes[3]);
        switch (node[39] & 0xF) {
        case 2: alignment = 0; break;
        case 1: alignment = 2; break;
        case 0: alignment = 1; break;
        default: alignment = 0; break;
        }
        func_800495F8(x, y, alignment, text);
        Font_DisableTwoCycleTexturing();
        func_800499EC();
        break;
    }
    return 0;
}
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
extern void *D_8AB16790;
extern void *D_8AB1678C;
extern void *PokeIcon_AllocLoadContext(u32);
extern void *ModelPreview_Create(void *, s32, s32);
extern s32 func_80042D54(u8 *, u16);
extern s32 func_80042FBC(void *, s32);
void TextPreview_InitializeModel(s16 species) {
    D_8AB16790 = PokeIcon_AllocLoadContext(1);
    D_8AB1678C = ModelPreview_Create(D_8AB16790, 80, 80);
    func_80042D54((u8 *)D_8AB1678C, 0);
    func_80042FBC(D_8AB1678C, species);
    *(u16 *)D_8AB1678C |= 0x100;
    *(u16 *)D_8AB1678C &= ~2;
    *(u16 *)D_8AB1678C &= ~4;
    D_8AB126A0 = 0;
}
#endif

#ifdef VERSION_US
extern void *D_8AB1678C;
s32 func_80042FBC(void *, s32);
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
void TextPreview_DrawRgba16Rect(s16 x, s16 y, s16 width, s16 height, void *image, s16 stride) {
    gDPLoadTextureBlock(D_800D0510++, image, G_IM_FMT_RGBA, G_IM_SIZ_16b, stride, height, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(D_800D0510++, x << 2, y << 2, (x + width) << 2, (y + height) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
}
#endif

#ifdef VERSION_US
extern Gfx D_8AB111B0[];
extern Gfx D_80094F50[];
void TextPreview_DrawImage80(s32 x, s32 y, u8 *image, s16 lod_fraction) {
    s32 row;
    gSPDisplayList(D_800D0510++, D_8AB111B0);
    gDPSetPrimColor(D_800D0510++, 0, lod_fraction, 0, 0, 0, 255);
    for (row = 0; row < 20; row += 1) {
        TextPreview_DrawRgba16Rect((s16)x, (s16)(y + row * 4), 80, 4, image, 80);
        image += 640;
    }
    gSPDisplayList(D_800D0510++, D_80094F50);
}
#endif

#ifdef VERSION_US
void func_8AB0234C(void)
{
  int new_var;
  if (((D_8AB14678 == 4) || (D_8AB14678 == 2)) && (D_8AB126A0 == 2))
  {
    if (D_8AB14678) // FAKE: empty state check in the existing matching dispatcher.
    {
    }
    new_var = D_8AB14678;
    if (new_var != 2)
    {
      new_var = D_8AB14678;
      if (new_var == 4)
      {
        TextPreview_DrawImage80(*((s16 *) (((u8 *) D_8AB11D04) + 8)), *((s16 *) (((u8 *) D_8AB11D04) + 0xA)), (u8 *)(u32)D_8AB16794, 0);
      }
    }
    else
    {
      TextPreview_DrawImage80(*((s16 *) (((u8 *) D_8AB11D04) + 8)), *((s16 *) (((u8 *) D_8AB11D04) + 0xA)), (u8 *)(u32)D_8AB16794, 0xFF);
    }
    D_8AB126A0 = 1;
  }
}
#endif

#ifdef VERSION_US
u32 func_8003570C();

u16 func_8AB023EC(u32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return ((u32) (func_8003570C() >> 0xC) % arg0) & 0xFFFF;
}
#endif

#ifdef VERSION_US
typedef struct TextChoiceNodeCopy { s32 unk_words[12]; u16 archive; u16 entry; } TextChoiceNodeCopy;
extern u8 D_8AB14268[];
extern u8 D_8AB14458[];
extern void *func_8004C8A0(void *, s32, s32, s32);
void TextChoice_ShuffleAndRefresh(void) {
    s32 i;
    s16 first;
    s16 second;
    TextChoiceNodeCopy saved;
    D_8AB1269A = 0;
    for (i = 0; i < 100; i++) {
        first = func_8AB023EC(4);
        second = func_8AB023EC(4);
        while (first == second) {
            second = func_8AB023EC(4);
        }
        saved = *(((TextChoiceNodeCopy **)D_8AB12668)[first]);
        ((TextChoiceNodeCopy **)D_8AB12668)[first]->archive = ((TextChoiceNodeCopy **)D_8AB12668)[second]->archive;
        ((TextChoiceNodeCopy **)D_8AB12668)[first]->entry = ((TextChoiceNodeCopy **)D_8AB12668)[second]->entry;
        ((TextChoiceNodeCopy **)D_8AB12668)[second]->archive = saved.archive;
        ((TextChoiceNodeCopy **)D_8AB12668)[second]->entry = saved.entry;
        if (first == D_8AB1269A) {
            D_8AB1269A = second;
        } else if (second == D_8AB1269A) {
            D_8AB1269A = first;
        }
    }
    for (i = 0; i < 4; i++) {
        if (((TextChoiceNodeCopy **)D_8AB12668)[i] != NULL) {
            func_8004C8A0(D_8AB127A8 + i * 256, 256,
                         ((TextChoiceNodeCopy **)D_8AB12668)[i]->archive,
                         ((TextChoiceNodeCopy **)D_8AB12668)[i]->entry);
        }
        if (((u8 **)D_8AB14268)[i] != NULL) {
            *(u16 *)(((u8 **)D_8AB14268)[i] + 2) &= ~1;
        }
        if (((u8 **)D_8AB14458)[i] != NULL) {
            *(u16 *)(((u8 **)D_8AB14458)[i] + 2) |= 1;
        }
        *(s16 *)(D_8AB12CB0 + i * 148 + 4) = 0;
    }
    D_8AB1269C = 20;
}
#endif

#ifdef VERSION_US
void TextReference_BuildShuffledPairs(u16 count, u16 start) {
    s32 i;
    s16 first;
    s16 second;
    s32 saved;
    for (i = 0; i < count; i++) {
        ((u16 *)D_8AB14680)[i] = start + i;
    }
    count = count / 2;
    if (count >= 2) {
        for (i = 0; i < 500; i++) {
            first = func_8AB023EC(count);
            second = func_8AB023EC(count);
            while (first == second) {
                second = func_8AB023EC(count);
            }
            first *= 2;
            second *= 2;
            saved = ((u16 *)D_8AB14680)[first];
            ((u16 *)D_8AB14680)[first] = ((u16 *)D_8AB14680)[second];
            ((u16 *)D_8AB14680)[second] = saved;
            first++;
            second++;
            saved = ((u16 *)D_8AB14680)[first];
            ((u16 *)D_8AB14680)[first] = ((u16 *)D_8AB14680)[second];
            ((u16 *)D_8AB14680)[second] = saved;
        }
        for (i = 0; i < 10; i++) {
            if (func_8AB023EC(100) >= 50) {
                first = i * 2;
                second = i * 2 + 1;
                saved = ((u16 *)D_8AB14680)[first];
                ((u16 *)D_8AB14680)[first] = ((u16 *)D_8AB14680)[second];
                ((u16 *)D_8AB14680)[second] = saved;
            }
        }
        for (i = 0; i < 10; i++) {
            ((u16 *)D_8AB14680)[i] = ((u16 *)D_8AB14680)[i * 2];
            ((u32 *)D_8AB148B0)[i] = ((u32 *)D_8AB148B0)[i * 2];
            {
                s16 mode_offset;
                switch (D_8AB1269E) {
                case 1: mode_offset = ((u16 *)D_8AB14680)[i] - 330; break;
                case 2: mode_offset = ((u16 *)D_8AB14680)[i] - 370; break;
                case 3: mode_offset = ((u16 *)D_8AB14680)[i] - 392; break;
                default: mode_offset = -2; break;
                }
                mode_offset = mode_offset / 2 + 1;
                ((s8 *)D_8AB11D0C)[i + 4] = mode_offset;
            }
        }
    }
}
#endif

#ifdef VERSION_US
extern u8 D_8AB14680[];
void func_8AB029BC(u16 count, u16 start) {
    s32 i;
    for (i = 0; i < count; i++) {
        ((u16 *)D_8AB14680)[i] = start + i;
    }
}
#endif

#ifdef VERSION_US
void TextReference_BuildShuffledRange(u16 count, u16 start) {
    s32 i;
    s16 first;
    s16 second;
    s32 value;
    for (i = 0; i < count; i++) {
        ((u16 *)D_8AB14680)[i] = start + i;
    }
    if (count >= 2) {
        for (i = 0; i < 500; i++) {
            first = func_8AB023EC(count);
            second = func_8AB023EC(count);
            while (first == second) {
                second = func_8AB023EC(count);
            }
            value = ((u16 *)D_8AB14680)[first];
            ((u16 *)D_8AB14680)[first] = ((u16 *)D_8AB14680)[second];
            ((u16 *)D_8AB14680)[second] = value;
        }
    }
}
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
extern u8 *D_8AB11D0C;
extern s16 D_8AB12696;

s32 func_8AB02C20(void) {
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
        D_8AB12696 = 0x48;
        result = 0x20E;
        break;
    case 4:
        result = 0x20E;
        D_8AB12696 = 0x48;
        break;
    }
    return result;
}
#endif

#ifdef VERSION_US
extern u8 * D_8AB11D0C;
extern s16 D_8AB12696;
s32 func_8AB02CB4(void) {
    s32 result;
    s32 new_var;
    u8 state;
    s16 flag;

    flag = 1;
    state = D_8AB11D0C[3];
    switch (state) {
    case 0:
        result = 0x19E;
        break;
    case 1:
        result = 0x1B2;
        break;
    case 2:
        result = 0x1BD;
        break;
    default:
        result = 0;
        break;
    }
    result += ((s8 *)D_8AB11D0C)[0x15];
    D_8AB12696 = flag;
    result--;
    return result & 0xFFFF;
}
#endif

#ifdef VERSION_US
extern void TextReference_BuildShuffledPairs(u16, u16);
void TextReference_BuildModeSelection(void) {
    s32 mode;
    u16 start;
    func_8AB003E4();
    mode = D_8AB1269E;
    switch (mode) {
    case 4:
        start = func_8AB02BA8();
        break;
    case 5:
        start = func_8AB02BA8();
        break;
    case 8:
        start = func_8AB02C20();
        break;
    case 6:
        start = func_8AB02C20();
        break;
    case 11:
        start = func_8AB02CB4();
        break;
    case 1:
        D_8AB12696 = 40;
        start = 330;
        break;
    case 2:
        D_8AB12696 = 22;
        start = 370;
        break;
    case 3:
        D_8AB12696 = 22;
        start = 392;
        break;
    case 0:
        D_8AB12696 = 268;
        start = 330;
        break;
    default:
        D_8AB12696 = 84;
        start = 330;
        break;
    }
    mode = D_8AB1269E;
    switch (mode) {
    case 1:
        TextReference_BuildShuffledPairs((u16)(D_8AB12696), start);
        break;
    case 2:
        TextReference_BuildShuffledPairs((u16)(D_8AB12696), start);
        break;
    case 3:
        TextReference_BuildShuffledPairs((u16)(D_8AB12696), start);
        break;
    case 0:
        func_8AB029BC((u16)(D_8AB12696), start);
        break;
    case 11:
        ((u16 *)D_8AB14680)[0] = start;
        break;
    default:
        func_8AB00020();
        TextReference_BuildShuffledRange((u16)(D_8AB12696), start);
        break;
    }
}
#endif

#ifdef VERSION_US
void *func_8AB02EF8(void) {
    s16 idx;
    void *result;

    if (func_8AB01340(D_8AB12694) != 0) {
        do {
            func_8AB012A4();
        } while (func_8AB01340(D_8AB12694) != 0);
    }
    D_8AB12692 += 1;
    if (D_8AB12692 >= 0x3E8) {
        D_8AB12692 = 0x3E7;
    }
    idx = ((s16 *)D_8AB14680)[D_8AB12694];
    result = *(void **)(D_8AB11D10 + idx * 4);
    return result;
}
#endif

#ifdef VERSION_US
extern u8 D_8AB1143C[];
u8 *TextReference_GetText(u8 *references, u16 entry_index) {
    u16 archive;
    u16 entry;
    u8 *text;

    archive = *(u16 *)(references + entry_index * 4);
    entry = *(u16 *)(references + entry_index * 4 + 2);
    text = func_8004C874(archive, entry);
    if (text == NULL) {
        text = D_8AB1143C;
    }
    return text;
}
#endif

#ifdef VERSION_US
/* mkdraft:func_8AB02FE0 begin */
extern void *func_8004C8A0(void *, s32, s32, s32);

void func_8AB02FE0(u16 arg0, u8 *arg1, u16 arg2) {
    *(u16 *)((u8 *)((void **)D_8AB12668)[arg0] + 0x30) = *(u16 *)(arg1 + (arg2 << 2));
    *(u16 *)((u8 *)((void **)D_8AB12668)[arg0] + 0x32) = *(u16 *)(arg1 + (arg2 << 2) + 2);
    func_8004C8A0(&D_8AB127A8[arg0 * 0x100], 0x100,
                  *(u16 *)((u8 *)((void **)D_8AB12668)[arg0] + 0x30),
                  *(u16 *)((u8 *)((void **)D_8AB12668)[arg0] + 0x32));
}
/* mkdraft:func_8AB02FE0 end */
#endif

#ifdef VERSION_US
extern s16 D_8AB1466A;
void func_8AB03064(u8 *arg0, u16 arg1, u16 arg2) {
    arg2 &= 0xFFFF;
    arg1 &= 0xFFFF;
    do {
        if (*(u16 *)arg0 == 0xFFFF) break;
        arg0 += 4;
    } while (1);
    *(u16 *)(arg0 + 0) = arg1;
    *(u16 *)(arg0 + 2) = arg2;
    arg0 += 4;
    *(u16 *)arg0 = 0xFFFF;
    arg0 += 2;
    *(u16 *)arg0 = 0xFFFF;
    D_8AB1466A++;
}
#endif

#ifdef VERSION_US
void func_8AB030BC(u8 *arg0, u16 arg1, u16 arg2, u16 arg3) {
    s32 i;
    u8 *dst;
    dst = arg0 + (arg1 * 4);
    i = 0;
    do {
        if (*(u16 *)arg0 == 0xFFFF) {
            break;
        }
        arg0 += 4;
        i = (i + 1) & 0xFFFF;
    } while (1);
    if (arg1 < i) {
        *(u16 *)dst = arg2;
        dst += 2;
        *(u16 *)dst = arg3;
    }
}
#endif

#ifdef VERSION_US
s32 func_8AB03124(u16 *arg0)
{
    s32 count;
    u16 value;
    count = 0;
    do {
        if (*arg0 == 0xFFFF) {
            break;
        }
        if (*arg0 == 0xFFFE) {
            u16 *p = arg0;
            do {
                if (*p == 0xFFFF) {
                    break;
                }
                p[0] = p[2];
                p[1] = p[3];
                p += 2;
            } while (1);
            value = *arg0;
        } else {
            value = arg0[2];
            arg0 += 2;
            count = count;
            count = (count + 1) & 0xFFFF;
        }
    } while (1);
    return count;
}
#endif

void func_8AB0318C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB03194.s")
#endif

#ifdef VERSION_US
extern u16 func_8AB023EC(u32 arg0);
extern s16 D_8AB13F30[];
extern s16 D_8AB1466A;
void func_8AB0322C(void) {
    s32 i;
    s16 x;
    s16 y;
    s16 t;
    s16 *table;
    table = D_8AB13F30;
    for (i = 0; i < D_8AB1466A * 5; i++) {
        y = (s16)func_8AB023EC(D_8AB1466A);
        x = (s16)func_8AB023EC(D_8AB1466A);
        t = table[y];
        table[y] = table[x];
        table[x] = t;
    }
}
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
extern void func_8AB01288(void); extern void TextReference_BuildModeSelection(void); void func_8AB03CE8(void) { func_8AB01288(); TextReference_BuildModeSelection(); }
#endif

#ifdef VERSION_US
extern u8 D_8AB14268[];
extern u8 D_8AB14278[];
void TextRow_SetOrangeState(s16 row_index) {
    u8 *row;
    u8 *panel;
    u8 *highlight;
    u8 *secondary;
    panel = ((u8 **)D_8AB14268)[D_8AB1269A];
    highlight = D_8AB14278 + D_8AB1269A * 120;
    func_8AB00BA4(1, row_index, D_8AB12690);
    row = D_8AB12CB0;
    row += row_index * 148;
    if (*(s16 *)(row + 4) == 0) {
        (*(s16 *)(row + 2))++;
    }
    *(u16 *)(panel + 2) |= 1;
    *(u32 *)(highlight + 108) = 0xFF500080;
    *(s16 *)(highlight + 38) = 0;
    secondary = *(u8 **)(row + 20);
    if (secondary != NULL) {
        *(u16 *)(secondary + 2) |= 1;
        *(u32 *)(row + 132) = 0xFF500080;
        *(s16 *)(row + 62) = 0;
    }
    *(s16 *)(row + 4) = 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB03DFC.s")
#endif

#ifdef VERSION_US
extern u8 D_8AB14278[];
extern u8 D_8AB12CC8[];
extern u16 D_8AB14660[];
extern f32 D_80088E50[];
void TextHighlight_AnimateScales(void) {
    s32 i;
    u8 *highlight;
    f32 amplitude;
    amplitude = 0.1f;
    for (i = 0; i < 4; i++) {
        highlight = D_8AB14278 + i * 120;
        if (highlight != NULL) {
            *(f32 *)(highlight + 64) = 1.0f + D_80088E50[D_8AB14660[i] >> 4] * amplitude;
            *(f32 *)(highlight + 68) = 1.0f + D_80088E50[D_8AB14660[i] >> 4] * amplitude;
            D_8AB14660[i] += 2048;
        }
    }
    amplitude = 0.2f;
    for (i = 0; i < 4; i++) {
        highlight = D_8AB12CC8 + i * 148;
        if (highlight != NULL) {
            *(f32 *)(highlight + 64) = 1.0f + D_80088E50[D_8AB14660[i] >> 4] * amplitude;
            *(f32 *)(highlight + 68) = 1.0f + D_80088E50[D_8AB14660[i] >> 4] * amplitude;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB04038.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB04210.s")
#endif

#ifdef VERSION_US
extern u8 D_8AB141C8[];
extern u8 D_8AB14458[];
extern u8 D_8AB14268[];
extern u8 D_8AB12668[];
extern u8 D_8AB12678[];
extern u8 D_8AB12CB0[];
extern u8 D_8AB12F00[];
void func_8AB04AE4(void) {
    s32 i = 0;
    s32 mask = -2;
    do {
        if (((void **)D_8AB12668)[i]) { ((u16 *)((void **)D_8AB12668)[i])[1] &= mask; }
        if (((void **)D_8AB141C8)[i]) { ((u16 *)((void **)D_8AB141C8)[i])[1] &= mask; }
        if (((void **)D_8AB12678)[i]) { ((u16 *)((void **)D_8AB12678)[i])[1] &= mask; }
        if (((void **)D_8AB14458)[i]) { ((u16 *)((void **)D_8AB14458)[i])[1] &= mask; }
        if (((void **)D_8AB14268)[i]) { ((u16 *)((void **)D_8AB14268)[i])[1] &= mask; }
        if (*(void **)(D_8AB12CB0 + i * 0x94 + 0x14)) { ((u16 *)*(void **)(D_8AB12CB0 + i * 0x94 + 0x14))[1] &= mask; }
        i++;
    } while (D_8AB12F00 != D_8AB12CB0 + i * 0x94);
}
#endif

#ifdef VERSION_US
extern u8 D_8AB14218[];
void TextPanels_UpdateVisibility(void) {
    s32 index;
    for (index = 0; index < 4; index++) {
        if (*(s32 *)D_8AB14218 != 0) {
            ((u16 **)D_8AB12668)[index][1] &= ~1;
            ((u16 **)D_8AB141C8)[index][1] |= 1;
        } else {
            ((u16 **)D_8AB141C8)[index][1] &= ~1;
            ((u16 **)D_8AB12668)[index][1] |= 1;
        }
        ((u16 **)D_8AB12678)[index][1] |= 1;
        ((u16 **)D_8AB14458)[index][1] |= 1;
    }
}
#endif

#ifdef VERSION_US
extern u8 *D_8AB14190;
void TextInterface_DrawMarkers(void) {
    s32 i;
    s16 x;
    s16 y;
    gDPPipeSync(D_800D0510++);
    gDPSetCycleType(D_800D0510++, G_CYC_1CYCLE);
    gSPTexture(D_800D0510++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(D_800D0510++, G_CULL_BACK | G_LIGHTING);
    gDPSetTexturePersp(D_800D0510++, G_TP_NONE);
    gDPSetRenderMode(D_800D0510++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineLERP(D_800D0510++, 0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT,
                     0, 0, 0, ENVIRONMENT, 0, 0, 0, ENVIRONMENT);
    if (D_8AB1269C < 4) {
        gDPSetEnvColor(D_800D0510++, 0xFF, 0x5A, 0x96, 0xFF);
    } else {
        gDPSetEnvColor(D_800D0510++, 0xFF, 0xFF, 0, 0xFF);
    }
    for (i = 0; i < D_8AB1269C; i++) {
        x = (*(s16 *)(D_8AB14190 + 8) + i * 5 + 6);
        y = (*(s16 *)(D_8AB14190 + 10) + 6);
        gSPTextureRectangle(D_800D0510++, x << 2, y << 2, (x + 3) << 2,
                            (y + 7) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);
    }
}
#endif

#ifdef VERSION_US
void func_8AB04ED8(void) {}
void func_8AB04ED8_padding(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/45/fragment45_2251A0/func_8AB04EE8.s")
#endif

#ifdef VERSION_US
extern s32 func_8AB062C4(s32);
extern s32 func_8AB0896C(s32);
extern s32 func_8AB0B24C(s32);
extern s32 TextMode8_UpdateState(s32);
extern s32 func_8AB0FE10(s32);

s32 func_8AB051AC(s32 arg0) {
    switch (D_8AB1269E) {
    case 0:
    case 1:
    case 2:
    case 3:
        arg0 = func_8AB062C4(arg0);
        break;
    case 4:
    case 5:
        arg0 = func_8AB0896C(arg0);
        break;
    case 6:
        arg0 = func_8AB0B24C(arg0);
        break;
    case 8:
        arg0 = TextMode8_UpdateState(arg0);
        break;
    case 11:
        arg0 = func_8AB0FE10(arg0);
        break;
    default:
        arg0 = func_8AB062C4(arg0);
    }
    return arg0;
}
#endif

#ifdef VERSION_US
/* mkdraft:func_8AB05254 begin */
extern u8 D_8AB11210[];
extern u16 D_8AB11208;

void func_8AB05254(void) {
    s16 temp_a0;
    s16 temp_a0_2;
    u16 mask;
    u16 var_v0;

    var_v0 = *(u16 *)(D_8AB13F28 + 6);
    if ((D_8AB1269E == 4) || (D_8AB1269E == 6)) {
        temp_a0 = *(s16 *)(D_8AB13F28 + 2);
        if (temp_a0 >= 6) {
            var_v0 |= 0x200;
        }
        if (temp_a0 < -5) {
            var_v0 |= 0x100;
        }
        temp_a0_2 = *(s16 *)(D_8AB13F28 + 4);
        if (temp_a0_2 >= 6) {
            var_v0 |= 0x800;
        }
        if (temp_a0_2 < -5) {
            var_v0 |= 0x400;
        }
        mask = (*(u16 *)(D_8AB11210 - 8) ^ var_v0) & var_v0;
        D_8AB11208 = var_v0;
        *(u16 *)(D_8AB13F28 + 8) = *(u16 *)(D_8AB13F28 + 8) | mask;
    }
}
/* mkdraft:func_8AB05254 end */
#endif

#ifdef VERSION_US
// The input loop copies the selected port's complete 40-byte controller state.
typedef struct TextControllerSnapshot {
    u32 words[10];
} TextControllerSnapshot;
extern void *D_80087200;
extern void *D_80087204;
extern void *D_80087208;
extern void *D_8008720C;
extern s32 D_8AB14188;
extern void func_800086A4(s32);
extern s32 StageFade_StartFromOpaque(s32);
extern void func_80064D28(void);
extern s32 func_80043678(u8 *);
extern void func_8AB04EE8(s32);
void TextInterface_RunMainLoop(void) {
    s32 previous_state;
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        func_80064D28();
        if (D_8AB11D0C[14] & 1) {
            *(TextControllerSnapshot *)D_8AB13F00 = *(TextControllerSnapshot *)D_80087200;
            D_8AB13F2C = 0;
        } else if (D_8AB11D0C[14] & 2) {
            *(TextControllerSnapshot *)D_8AB13F00 = *(TextControllerSnapshot *)D_80087204;
            D_8AB13F2C = 1;
        } else if (D_8AB11D0C[14] & 4) {
            *(TextControllerSnapshot *)D_8AB13F00 = *(TextControllerSnapshot *)D_80087208;
            D_8AB13F2C = 2;
        } else if (D_8AB11D0C[14] & 8) {
            *(TextControllerSnapshot *)D_8AB13F00 = *(TextControllerSnapshot *)D_8008720C;
            D_8AB13F2C = 3;
        }
        func_8AB05254();
        previous_state = D_8AB14188;
        D_8AB14188 = func_8AB051AC(D_8AB14188);
        if (D_8AB126A0 == 1) {
            D_8AB16794 = func_80043678(D_8AB1678C);
            D_8AB126A0 = 2;
        }
        func_8AB04EE8(previous_state);
    } while (D_8AB14188 != 0);
    func_8AB01FBC();
}
#endif

#ifdef VERSION_US
extern u8 D_1000000[];
extern u8 D_446E30[];
extern u8 D_447D00[];
extern u8 D_47D310[];
extern u8 D_48B920[];
extern u8 D_8AB16478[];
extern s32 D_8AB12CA8;
extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern s32 main_pool_alloc(s32, s32);
extern s32 func_80055948(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 StageContext_Allocate(s32, s32, s32, s32, s32, s32);
extern void func_80008514(s32);
extern void func_80008574(void);
extern s32 func_8004C09C(s32);
extern s32 func_8004D690(s32);
extern void func_8004C398(void);
extern void func_80027EE0(u16);
extern void func_87F00030(void);
extern void fragment64_main(s32);
extern u8 *Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern s32 BinArchive_Open(u8 *, u8 *, s32, s32);
extern void *func_80004B4C(s32, s32);
extern u8 *func_80047588(s32, s32);
extern void func_800476A0(u8 *, s32);
extern s32 func_800476FC(s32, s32);
extern s32 func_80047738(s32, s32, s32, s32);
extern void func_80047610(void);
extern void Audio_InitializeBufferMemory(void *);
extern void func_800251F8(s32);
extern void func_8002602C(void);
extern void func_80051D64(s32, s32);
extern s32 func_80054E48(s32);
extern void func_8AB04210(void);
s32 TextInterface_Run(s32 arg0, u8 *configuration) {
    s32 index;
    s32 stage;
    s32 archive;
    void *resource;

    func_8AB00084();
    D_8AB11D0C = configuration;
    D_8AB1269E = *(u16 *)D_8AB11D0C;
    if (D_8AB1269E == 8) {
        func_80027EE0(4095);
    }
    D_8AB12CA8 = 0;
    if ((D_8AB11D0C[14] & 0xF) == 0) {
        D_8AB12CA8 = 1;
    }
    main_pool_push_state(0x504D515A);
    func_80055948(3);
    Gfx_InitDisplayListBuffers(65536, 0);
    stage = StageContext_Allocate(1, 0, 2, 0, 2, 1);
    func_8004C09C(271);
    if ((D_8AB1269E == 1) || (D_8AB1269E == 2) || (D_8AB1269E == 3) || (D_8AB1269E == 11)) {
        D_8AB11D08 = func_8004D690(14);
    } else {
        func_8AB003A4(276);
        D_8AB11D08 = 0;
    }
    func_87F00030();
    fragment64_main(20);
    if (D_8AB1269E != 11) {
        func_8AB00020();
    }
    Asset_LoadToSegment(((u32)D_1000000 & 0x0F000000) >> 24, D_446E30, D_447D00, 0);
    archive = BinArchive_Open(D_47D310, D_48B920, 1, 1);
    for (index = 0; index < 598; index++) {
        resource = func_80004B4C(archive, index);
        ((void **)D_8AB11D10)[index] = resource;
    }
    func_8AB003A4(239);
    func_8AB003A4(280);
    func_8AB003A4(51);
    func_8AB003A4(147);
    func_80047588(24, 0);
    func_8AB003C4(58);
    func_8AB003C4(12);
    func_8AB003C4(0);
    func_8AB003C4(8);
    func_8AB003C4(9);
    func_8AB003C4(57);
    func_8AB003C4(6);
    func_8AB003C4(1);
    func_8AB003C4(2);
    func_8AB003C4(3);
    func_8AB003C4(14);
    func_8AB003C4(49);
    func_8AB003C4(42);
    switch (D_8AB1269E) {
    case 0:
    case 1:
    case 2:
    case 3:
        func_800476A0(D_8AB16478, 1);
        func_800476FC((s32)D_8AB16478, 1);
        func_80047738(0, func_8004C990(187, 1), 0, 0);
        break;
    default:
        func_8AB003A4(435);
        func_800476A0(D_8AB16478, 9);
        func_800476FC((s32)D_8AB16478, 9);
        func_80047738(0, func_8004C990(51, 0), 0, 0);
        func_80047738(1, func_8004C990(435, 5), 0, 0);
        func_80047738(2, func_8004C990(435, 6), 0, 0);
        func_80047738(3, func_8004C990(435, 7), 0, 0);
        func_80047738(4, func_8004C990(435, 8), 0, 0);
        func_80047738(5, func_8004C990(435, 1), 0, 0);
        func_80047738(6, func_8004C990(435, 2), 0, 0);
        func_80047738(7, func_8004C990(435, 3), 0, 0);
        func_80047738(8, func_8004C990(435, 4), 0, 0);
        break;
    case 11:
        break;
    }
    Audio_InitializeBufferMemory((void *)main_pool_alloc(33792, 0));
    func_800251F8(0);
    func_8AB04210();
    func_80008514(stage);
    TextInterface_RunMainLoop();
    func_80008574();
    func_8002602C();
    func_800251F8(1);
    if (D_8AB1269E == 8) {
        func_80027EE0(4094);
    }
    func_80051D64(19, 0);
    func_80054E48(3);
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x504D515A);
    return 0;
}
#endif
