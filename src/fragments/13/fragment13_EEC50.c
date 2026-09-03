#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82400BD0.s")

extern void func_8004C8C0(s32);
s32 func_8004C990(s32, s32);
extern s32 D_82407830;
extern s32 D_82407834;
extern s32 D_82407838;
extern s32 D_8240783C;
extern s32 D_82407840;
extern s32 D_82407844;
extern s32 D_82407848;
extern s32 D_8240784C;
extern s32 D_82407850;
extern s32 D_82407854;
extern s32 D_82407858;
extern s32 D_8240785C;
extern s32 D_82407860;
extern s32 D_82407864;
extern s32 D_82407868;
void func_82401000(void) {
    func_8004C4B0(0x3C);
    func_8004C8C0(0x94);
    func_8004C8C0(0x1E);
    func_8004C8C0(0x21);
    func_8004C8C0(0x1F);
    func_8004C8C0(0xE7);
    func_8004C8C0(0xE9);
    func_8004C8C0(0xEA);
    func_8004C8C0(0xE8);
    func_8004C8C0(0xEB);
    func_8004C8C0(0x12);
    D_82407840 = func_8004C990(0xEA, 6);
    D_82407848 = func_8004C990(0xE8, 0);
    D_82407838 = func_8004C990(0x1E, 0);
    D_8240783C = func_8004C990(0x1E, 1);
    D_82407830 = func_8004C990(0x94, 0);
    D_82407844 = func_8004C990(0xEA, 5);
    D_82407834 = func_8004C990(0xEA, 4);
    D_8240784C = func_8004C990(0xEA, 1);
    D_82407850 = func_8004C990(0xEA, 2);
    D_82407854 = func_8004C990(0xEA, 3);
    D_82407858 = func_8004C990(0xEA, 0);
    D_82407868 = func_8004C990(0xEB, 0);
    D_82407864 = func_8004C990(0xEB, 1);
    D_8240785C = func_8004C990(0xEB, 2);
    D_82407860 = func_8004C990(0xEB, 3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82401198.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82401570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_8240182C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82401A28.s")

extern void func_800496A4(s32, s32);
extern void func_8004C54C(s32, s32);
extern s32 func_8004C8A0(void *, s32, s32, s32);
extern void func_800495F8(s32, s32, s32, s32);
void func_82401DD4(s32 arg0) {
    s32 temp[32];
    s32 value;
    func_800496A4(4, 1);
    func_8004C54C(0x14, arg0);
    value = func_8004C8A0(temp, 0x40, 0x3C, 0);
    func_800495F8(0xA0, 0x12, 1, value);
}

extern Gfx *D_800D0510;
extern void func_8004D1FC(u8 *);
extern void func_82400BD0(f32, f32, f32, f32, s32, s32, f32, f32);
void func_82401E30(s32 arg0, s32 arg1) {
    gDPSetEnvColor(D_800D0510++, 0xAA, 0xAA, 0xFF, 0xFF);
    func_8004D1FC((u8 *)(u32)D_82407838);
    func_82400BD0((f32)arg0, (f32)arg1, (f32)*(u16 *)(u8 *)(u32)D_82407838, (f32)*(u16 *)((u8 *)(u32)D_82407838 + 2), 0, 0, 1.0f, 1.0f);
}

void func_82401F08(s32 arg0, s32 arg1) {
    gDPSetEnvColor(D_800D0510++, 0xAA, 0xFF, 0xAA, 0xFF);
    func_8004D1FC((u8 *)(u32)D_8240783C);
    func_82400BD0((f32)arg0, (f32)arg1, (f32)*(u16 *)(u8 *)(u32)D_8240783C, (f32)*(u16 *)((u8 *)(u32)D_8240783C + 2), 0, 0, 1.0f, 1.0f);
}

extern Gfx *D_800D0510;
extern void func_8004D1FC(u8 *);
extern void func_82400BD0(f32, f32, f32, f32, s32, s32, f32, f32);
void func_82401FE0(s32 arg0, s32 arg1) {
    gDPSetEnvColor(D_800D0510++, 0xFF, 0xFF, 0xFF, 0xFF);
    func_8004D1FC((u8 *)(u32)D_82407830);
    func_82400BD0((f32)arg0, (f32)arg1, (f32)*(u16 *)(u8 *)(u32)D_82407830, (f32)*(u16 *)((u8 *)(u32)D_82407830 + 2), 0, 0, 1.0f, 1.0f);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824020B4.s")

extern void func_800498C4(void);
extern void func_82401DD4(s32);
extern void func_82401F08(s32, s32);
extern void func_800499EC(void);
extern void func_800496A4(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800495BC(s32, s32, s32);
extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_824021AC(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        func_800498C4();
        func_82401DD4(arg1);
        func_800499EC();
        return;
    }
    gSPDisplayList(D_800D0510++, D_80094E38);
    func_82401F08(0xF0, 0xCF);
    gSPDisplayList(D_800D0510++, D_80094F50);
    func_800498C4();
    func_800496A4(2, 1);
    func_800495BC(0x100, 0xD1, func_8004C874(0x3C, 5));
    func_800499EC();
}

extern void func_800498C4(void);
extern void func_82401DD4(s32);
extern void func_82401FE0(s32, s32);
extern void func_82401E30(s32, s32);
extern void func_82401F08(s32, s32);
extern void func_800499EC(void);
extern void func_800496A4(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800495BC(s32, s32, s32);
extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_80094F50[];
void func_8240227C(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        func_800498C4();
        func_82401DD4(arg1);
        func_800499EC();
        return;
    }
    gSPDisplayList(D_800D0510++, D_80094E38);
    func_82401FE0(0x1F, 0xCD);
    func_82401E30(0x92, 0xCF);
    func_82401F08(0xF2, 0xCF);
    gSPDisplayList(D_800D0510++, D_80094F50);
    func_800498C4();
    func_800496A4(2, 1);
    func_800495BC(0x35, 0xD1, func_8004C874(0x3C, 1));
    func_800495BC(0xA2, 0xD1, func_8004C874(0x3C, 2));
    func_800495BC(0x102, 0xD1, func_8004C874(0x3C, 0x41));
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_8240239C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824027F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82402904.s")

s32 func_824029E4(s32 arg0, s16 arg1) {
    if (arg1 < 0) {
        return 8;
    }
    return *(s16 *)((u8 *)(u32)arg0 + ((s32)arg1 << 1) + 0x100) + 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82402A14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82402B1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82402E28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_8240330C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82403624.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82403C84.s")

s32 func_80001FF0();
s32 func_80008970();

f32 func_82403F10(void) {
    s32 sp1C;

    sp1C = func_80008970();
    return ((f32) sp1C * 60.0f) / (f32) func_80001FF0();
}

extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_80094F50[];
extern void func_8004D19C(s32, s32, s32, s32, s32);
void func_82403F58(void) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    func_8004D19C(0, 0, D_8240785C, 0, 0);
    gSPDisplayList(D_800D0510++, D_80094F50);
}

extern Gfx *D_800D0510;
extern u8 D_80094E38[];
extern u8 D_80094F50[];
extern void func_8004D19C(s32, s32, s32, s32, s32);
void func_82404000(void) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    func_8004D19C(0, 0xCA, D_82407860, 0, 0);
    gSPDisplayList(D_800D0510++, D_80094F50);
}

void func_824040A8(void) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    func_8004D19C(0, 0x26, D_82407868, 0, 0);
    gSPDisplayList(D_800D0510++, D_80094F50);
}

void func_82404150(void) {
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
    func_8004D19C(0x134, 0x26, D_82407864, 0, 0);
    gSPDisplayList(D_800D0510++, D_80094F50);
}

extern void func_82403F58(void);
extern void func_82404000(void);
extern void func_824040A8(void);
extern void func_82404150(void);
void func_824041F8(void) {
    func_82403F58();
    func_82404000();
    func_824040A8();
    func_82404150();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82404230.s")

extern s32 func_8004C874(s32, s32);
extern s32 func_800472E0(s32);
extern s16 func_80049148(s32, s32, s32);
extern s32 func_8004C990(s32, s32);
void func_8240429C(u8 *arg0) {
    *(s32 *)(arg0 + 8) = func_8004C874(0x3C, 0x3E);
    *(s32 *)(arg0 + 0xC) = func_8004C874(0x3C, 0x3F);
    *(s32 *)(arg0 + 0x10) = func_8004C874(0x3C, 0x40);
    func_800472E0(*(s32 *)(arg0 + 8));
    *(s16 *)(arg0 + 4) = func_80049148(2, 1, *(s32 *)(arg0 + 8));
    *(s32 *)(arg0 + 0x14) = func_8004C990(0x12, 3);
    *(s32 *)(arg0 + 0x18) = func_8004C990(0x12, 2);
    *(s16 *)(arg0 + 4) = 0xAF;
    *(s16 *)(arg0 + 6) = 0x4C;
    *(s16 *)(arg0 + 0) = 0x48;
    *(s16 *)(arg0 + 2) = 0x40;
    *(u8 *)(arg0 + 0x21) = 0;
    *(s8 *)(arg0 + 0x20) = -1;
    *(f32 *)(arg0 + 0x1C) = 0.0f;
}

s32 func_82404360(u8 *arg0) {
    *(s8 *)(arg0 + 0x20) = -1;
    *(f32 *)(arg0 + 0x1C) = 0.0f;
    return 0;
}

s32 func_82404378(void *arg0)
{
  f32 new_var2;
  u8 *new_var;
  new_var2 = func_82403F10();
  *((f32 *) (((u8 *) arg0) + 0x1C)) = (f32) ((*((f32 *) (((u8 *) arg0) + 0x1C))) + new_var2);
  if ((*((f32 *) (((u8 *) arg0) + 0x1C))) >= 8.0f)
  {
    new_var = (u8 *) arg0;
    *((f32 *) (new_var + 0x1C)) = 8.0f;
    *((s8 *) (new_var + 0x21)) = 2;
    *((s8 *) (((u8 *) arg0) + 0x20)) = 0;
  }
  return 0;
}

s32 func_824043D8(void *arg0) {
    (*(f32 *)((u8 *)(arg0) + (0x1C))) = (f32) ((*(f32 *)((u8 *)(arg0) + (0x1C))) - func_82403F10());
    if ((*(f32 *)((u8 *)(arg0) + (0x1C))) <= 0.0f) {
        (*(f32 *)((u8 *)(arg0) + (0x1C))) = 0.0f;
        (*(s8 *)((u8 *)(arg0) + (0x21))) = 4;
    }
    return 0;
}

s32 func_82404430(u8 *arg0) {
    *(f32 *)(arg0 + 0x1C) = 0.0f;
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82404440.s")

extern void func_800226C0(s32, void *);
s8 func_82404564(void *arg0) {
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)(arg0) + (0x21)));
    if (temp_v0 != 0) {
        if (temp_v0 == 4) {
            (*(u8 *)((u8 *)(arg0) + (0x21))) = 0U;
            return (*(s8 *)((u8 *)(arg0) + (0x20)));
        }
        goto block_4;
    }
    (*(u8 *)((u8 *)(arg0) + (0x21))) = 1U;
    func_800226C0(0xA9, arg0);
block_4:
    return -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824045B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824046A4.s")

s32 func_824048A0(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = (*(s32 *)((u8 *)(arg0) + (0x1DC)));
    if ((temp_v0 == 4) && (arg1 == (*(s32 *)((u8 *)(arg0) + (0x1A8))))) {
        return 1;
    }
    if ((temp_v0 == 5) && (arg1 == (*(s32 *)((u8 *)(arg0) + (0x1A4))))) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824048F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82404990.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824049D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82404AE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82404B6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82404C78.s")

extern void func_81A00074(s32, s32);
void func_82404DD8(s32 arg0) {
    func_81A00074(arg0 + 0x24C, *(s32 *)(arg0 + 0x190));
}

void func_82404E00(void *arg0, void *arg1, void *arg2, f32 arg3)
{
  f32 temp_fa1;
  f32 temp_fv0;
  f32 temp_fv1;
  f32 new_var;
 do { temp_fv0 = *((f32 *) (((u8 *) arg1) + 0)); *((f32 *) (((u8 *) arg0) + 0)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 0))) - temp_fv0) * arg3) + temp_fv0); temp_fv1 = *((f32 *) (((u8 *) arg1) + 4)); new_var = arg3; *((f32 *) (((u8 *) arg0) + 4)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 4))) - temp_fv1) * new_var) + temp_fv1); temp_fa1 = *((f32 *) (((u8 *) arg1) + 8)); *((f32 *) (((u8 *) arg0) + 8)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 8))) - temp_fa1) * new_var) + temp_fa1); } while (0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82404E50.s")

extern u8 D_82407DE8;
extern u8 D_82407DF0;
extern u8 D_82408160;
extern u8 D_82408168;
void func_82404F64(void *arg0) {
    (*(u8 *)((u8 *)(&D_82408160) + (0))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x47)));
    (*(u8 *)((u8 *)(&D_82408160) + (1))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x48)));
    (*(u8 *)((u8 *)(&D_82408160) + (2))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x49)));
    (*(u8 *)((u8 *)(&D_82408168) + (0))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4A)));
    (*(u8 *)((u8 *)(&D_82408168) + (1))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4B)));
    (*(u8 *)((u8 *)(&D_82408168) + (2))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4C)));
    (*(u8 *)((u8 *)(&D_82407DE8) + (0))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4D)));
    (*(u8 *)((u8 *)(&D_82407DE8) + (1))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4E)));
    (*(u8 *)((u8 *)(&D_82407DE8) + (2))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x4F)));
    (*(u8 *)((u8 *)(&D_82407DF0) + (0))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x50)));
    (*(u8 *)((u8 *)(&D_82407DF0) + (1))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x51)));
    (*(u8 *)((u8 *)(&D_82407DF0) + (2))) = (u8) (*(u8 *)((u8 *)(arg0) + (0x52)));
}

s16 MathUtil_Atan2s(f32 y, f32 x);
void func_82404FE8(s16 *arg0, s16 *arg1, void *arg2) {
    f32 temp_ft4;
    f32 temp_fv1;

    temp_fv1 = (*(f32 *)((u8 *)(arg2) + (0)));
    temp_ft4 = (*(f32 *)((u8 *)(arg2) + (8)));
    *arg0 = MathUtil_Atan2s(sqrtf((temp_fv1 * temp_fv1) + (temp_ft4 * temp_ft4)), (*(f32 *)((u8 *)(arg2) + (4))));
    *arg1 = MathUtil_Atan2s((*(f32 *)((u8 *)(arg2) + (8))), (*(f32 *)((u8 *)(arg2) + (0))));
}

extern void func_8005F37C(u8, void *, void *, void *, void *);
void func_8240504C(void *arg0, s32 arg1) {
    *(f32 *)((u8 *)arg0 + 0) = 0.0f;
    if ((arg1 >= 0) && (arg1 < 4)) {
        func_8005F37C((u8)arg1, (u8 *)arg0 + 4, (u8 *)arg0 + 6, (u8 *)arg0 + 7, (u8 *)arg0 + 8);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824050A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82405244.s")

void func_82405494(void *arg0, void *arg1, void *arg2, f32 arg3)
{
  f32 temp_fa1;
  f32 temp_fv0;
  f32 temp_fv1;
  f32 new_var;
 do { temp_fv0 = *((f32 *) (((u8 *) arg1) + 0)); *((f32 *) (((u8 *) arg0) + 0)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 0))) - temp_fv0) * arg3) + temp_fv0); temp_fv1 = *((f32 *) (((u8 *) arg1) + 4)); new_var = arg3; *((f32 *) (((u8 *) arg0) + 4)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 4))) - temp_fv1) * new_var) + temp_fv1); temp_fa1 = *((f32 *) (((u8 *) arg1) + 8)); *((f32 *) (((u8 *) arg0) + 8)) = (f32) ((((*((f32 *) (((u8 *) arg2) + 8))) - temp_fa1) * new_var) + temp_fa1); } while (0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824054E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82405718.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82405934.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824059E4.s")

void func_82405A58(s32 arg0, void *arg1) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg1) + (0x14)));
    if (arg0 == 2) {
        (*(u8 *)((u8 *)(arg1) + (0x18))) = (u8) (*(u8 *)((u8 *)(temp_v0) + (0x44)));
        (*(u8 *)((u8 *)(arg1) + (0x19))) = (u8) (*(u8 *)((u8 *)(temp_v0) + (0x45)));
        (*(u8 *)((u8 *)(arg1) + (0x1A))) = (u8) (*(u8 *)((u8 *)(temp_v0) + (0x46)));
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82405A84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82405B24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82405BAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82405C0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82405D38.s")

extern Gfx *D_800D0510;
extern void func_80038E14(void *, s32, s32, s32, f32, f32, f32, s32);
extern void GeoCamera_SetPerspective(void *, f32, f32, f32);
extern void func_80006F70(Gfx **, s32, s32, s32, s32);
s32 func_82405EE0(s32 arg0, void *arg1) {
    void *record;

    record = *(void **)((u8 *)arg1 + 0x14);
    if (arg0 == 0) {
        return 1;
    }
    func_80038E14(arg1, *(s32 *)((u8 *)record + 0x174), *(s32 *)((u8 *)record + 0x178), *(s32 *)((u8 *)record + 0x17C), *(f32 *)((u8 *)record + 0x180), *(f32 *)((u8 *)record + 0x184), *(f32 *)((u8 *)record + 0x188), 0);
    GeoCamera_SetPerspective(arg1, 23.1f, 64.0f, 10000.0f);
    if (arg0 == 5) {
        func_80006F70(&D_800D0510, 0xD, 0x27, 0x126, 0xA1);
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82405F8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82406060.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_8240641C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82406560.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82406880.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82406A78.s")

s32 func_82406CCC(u8 *arg0) {
    return *(s32 *)(arg0 + 0x1E4) == 4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82406CDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82406E14.s")

extern f32 (*D_8160BD1C)(f32);
f32 func_82407088(void *arg0) {
    f32 factor;
    f32 start;
    factor = D_8160BD1C(*(f32 *)((u8 *)arg0 + 0x200) / 20.0f);
    start = (f32)*(s32 *)((u8 *)arg0 + 0x1E0);
    return ((f32)*(s32 *)((u8 *)arg0 + 0x1DC) - start) * factor + start;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_824070E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82407170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/13/fragment13_EEC50/func_82407228.s")
#endif
