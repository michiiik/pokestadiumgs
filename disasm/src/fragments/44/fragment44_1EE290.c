#include "global.h"


#ifdef VERSION_US
s32 func_8003514C();
s32 func_8AF244D0();
extern u16 D_8AF2BE8A;

s32 func_8AF00020(void) {
    if (func_8003514C() == 0) {
        return 1;
    }
    if ((D_8AF2BE8A & 0x100) && (func_8AF244D0() != 0)) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF0007C.s")

extern void func_800226C0(void);
void func_8AF00130(void) {
    func_800226C0();
  }

extern u8 D_8AF2BE98[]; extern s32 D_8AF2BF10; void func_8AF00150(void) { _bzero(D_8AF2BE98, 0x78); D_8AF2BF10 = 0; }

extern s16 D_8AF2BE9A;
u8 *func_8AF0017C(s16 arg0) {
    s32 i;
    u8 *entry;
    entry = D_8AF2BE98;
    if (arg0 == D_8AF2BE9A) {
        return entry;
    }
    entry += 0xC;
    if (arg0 == *(s16 *)(entry + 2)) {
        return entry;
    }
    entry += 0xC;
    i = 2;
    do {
        if (arg0 == *(s16 *)(entry + 2)) {
            return entry;
        }
        i++;
        entry += 0xC;
    } while (i != 0xA);
    return NULL;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00240.s")

void func_8AF00304(s16 arg0, s32 arg1)
{
  void *temp_v0;
  if ((arg0 == 0x89) || (arg0 == 0x92))
  {
    temp_v0 = func_8AC06D8C(arg1 ^ 0, 0x70696330, arg1);
    if (temp_v0 != 0)
    {
      *((u16 *) (((u8 *) temp_v0) + 2)) = (u16) ((*((u16 *) (((u8 *) temp_v0) + 2))) & 0xFFFE);
    }
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00360.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF003A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00504.s")

extern void func_800503A4(s32);
extern void func_8AC00738();
void func_8AF00620(void) {
    s32 var_s1;
    u8 *var_s0;

    var_s0 = D_8AF2BE98;
    var_s1 = 0;
    do {
        if (((*(s16 *)((u8 *)(var_s0) + (2))) != 0) && ((*(s16 *)((u8 *)(var_s0) + (4))) == 0)) {
            func_8AC00738();
            func_800503A4((*(s32 *)((u8 *)(var_s0) + (8))));
        }
        var_s1 += 1;
        var_s0 += 0xC;
    } while (var_s1 != 0xA);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00690.s")

void func_8AF00760(void) {}
void func_8AF00760_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00770.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00B74.s")

s16 func_8AF00B74();
extern s16 D_8AF2BA6C;
extern s32 D_8AF2BDD0;
extern s16 D_8AF2BDD4;
extern s32 D_8AF2BE78;
extern s16 D_8AF2BE7C;
void func_8AF00D90(void) {
    s16 temp_v0;

    temp_v0 = func_8AF00B74();
    if (temp_v0 != D_8AF2BA6C) {
        D_8AF2BDD0 = 1;
        D_8AF2BDD4 = 4;
        D_8AF2BE78 = 1;
        D_8AF2BE7C = temp_v0;
        return;
    }
    if (D_8AF2BDD0 != 0) {
        D_8AF2BDD4 -= 1;
        if (D_8AF2BDD4 < 0) {
            D_8AF2BDD0 = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF00E24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF0118C.s")

extern void func_800504BC(s16 *);
extern void func_8AF0118C(s16, s16, void *);
s32 func_8AF013D8(s32 mode, void *record) {
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
        func_8AF0118C(first, second, preserved);
        break;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF0145C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01530.s")

extern s16 D_8AF263F0[];
s16 Trade_GetSelectedBox(s16 arg0) { return D_8AF263F0[arg0]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01618.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01654.s")

extern u8 D_8AF28760[];
extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern void Ui_DrawGradientPanel(s32, s32, s32, s32, s32, s32);
void func_8AF016BC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    Ui_DrawGradientPanel(arg0, arg1, arg2, arg3, arg4, arg5);
}
void func_8AF016BC_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01718.s")

extern void func_8AC00824(void);
extern void func_8AF00D90(void);
void func_8AF01750(void) {
    func_8AC00824();
    func_8AF00D90();
}

extern Gfx *D_800D0510;
extern u8 D_8AF26418[];
void Font_EndTexturedTextRendering_fragment44(void) { Gfx *temp_v1 = D_800D0510++; temp_v1->words.w0 = 0xDE000000; temp_v1->words.w1 = (u32)D_8AF26418; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF017A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01910.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01A0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01C84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01D7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01EAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF01FFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_1EE290/func_8AF02208.s")
#endif
