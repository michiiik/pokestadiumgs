#include "global.h"

#ifdef VERSION_US
/* Stadium 1 transfer helper: allocates a typed block from the supplied pool. */
extern void *MainPool_AllocAligned(void *, size_t, s32);
extern Vtx *func_800398F8();
#endif


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80021DE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80021ED8.s")
#endif

#ifdef VERSION_US
extern void func_800187AC();
extern s8 D_8009019C;
extern s8 D_800901A0;
extern s8 D_800901A4;
extern void func_80018728(u32, ...);

void func_800225C4(s32 arg0) {
    func_80018728(0x83000000U, arg0 * 3, arg0);
    func_800187AC();
    D_8009019C = 0;
    D_800901A0 = 0;
    D_800901A4 = 0;
}
#endif

#ifdef VERSION_US
void func_8002260C(s32 arg0, s32 arg1) {
    func_80018728(0x82000100, 0);
  }
#endif

#ifdef VERSION_US
s32 func_8002263C(void) {
    return 0x61;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80022644.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800226C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80023110.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800231A0.s")
#endif

#ifdef VERSION_US
extern s8 D_80090220;
extern s32 D_8009022C;
extern s8 D_80090B80;
void func_800238C4(void) {
    if (D_80090B80 == 2) {
        D_80090220 = 0;
        func_80018728(0x83010000U, 0xB4);
        D_8009022C = -1;
    }
}
#endif

#ifdef VERSION_US
void func_8002390C(s32 arg0) {
    if (D_80090B80 == 2) {
        D_80090220 = 0;
        func_80018728(0x83010000U, arg0);
        D_8009022C = -1;
    }
}
#endif

#ifdef VERSION_US
void func_80023954(void) {
    func_8001874C(0x06010005, 1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002397C.s")
#endif

#ifdef VERSION_US
extern s32 D_80090224, D_80090228;

void func_800239B4(s32 arg0, s32 arg1) {
    D_80090224 = arg0;
    D_80090228 = arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800239C8.s")
#endif

#ifdef VERSION_US
extern s32 D_8009061C[][4];
s32 func_80023A10(u8 arg0, u8 arg1) {
    return D_8009061C[arg0][arg1];
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80023A3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024180.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002421C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024480.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024864.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800248A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800248EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024974.s")
#endif

#ifdef VERSION_US
extern s8 D_80090A54;

void func_80024D10(s32 arg0) {
    D_80090A54 = 0;
    func_80018728(0x83030000U, arg0 * 3, arg0);
}
#endif

#ifdef VERSION_US
extern s32 D_80090A50;
extern u8 D_80090A74;
extern s8 D_80090A78;

void func_80024D44(void) {
    D_80090A50 = 0;
    (*(s8 *)((u8 *)(&D_80090A74) + (0))) = 0;
    (*(s8 *)((u8 *)(&D_80090A74) + (1))) = 0;
    D_80090A78 = -1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024D6C.s")
#endif

#ifdef VERSION_US
s32 func_80024E30(u32 arg0) {
    s32 var_v1;
    u8 *var_v0;

    if (((arg0 == 0) || (arg0 >= 0xFCU)) && (arg0 != 0x12C)) {
        return -1;
    }
    var_v0 = &D_80090A74;
    var_v1 = 0;
loop_5:
    if (arg0 == *var_v0) {
        return var_v1;
    }
    var_v1 += 1;
    var_v0 += 1;
    if (var_v1 == 2) {
        return -2;
    }
    goto loop_5;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024E8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80024F20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800251F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025294.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025848.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800258F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002596C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025ACC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025B54.s")
#endif

#ifdef VERSION_US
extern s8 D_80090B90;
void func_80025C50(u32 arg0) {
    if (arg0 < 5U) {
        if (arg0 == 4) {
            D_80090B90 = 1;
        } else {
            D_80090B90 = 0;
        }
        func_80018728(0xF0000000U, arg0);
    }
}
#endif

#ifdef VERSION_US
extern s32 func_80018C14(void);
s32 func_80025C9C(void) {
    return func_80018C14();
}
#endif

#ifdef VERSION_US
extern void func_800315E8();
extern s8 D_80090B9C;
void func_8002B1A0(void);
extern void func_80028140(void);

void func_80025CBC(s32 arg0) {
    s32 temp_s0;

    func_8002B1A0();
    func_800315E8();
    func_80028140();
    temp_s0 = arg0 * 3;
    func_80018728(0x83000000U, temp_s0);
    func_80018728(0x83010000U, temp_s0);
    func_80018728(0x83020000U, temp_s0);
    func_80018728(0x83030000U, temp_s0);
    func_80018728(0x83040000U, temp_s0);
    D_80090B9C = 0;
}
#endif

#ifdef VERSION_US
extern s32 func_80019378(void);

s32 func_80025D44(void) {
    return func_80019378();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025D64.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025DB0.s")
#endif

#ifdef VERSION_US
extern void func_80025DB0();
extern u8 D_800D1910;

void func_80025E7C(void) {
    func_80025DB0();
    func_80018728(0xE2000700U, &D_800D1910);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025EB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80025F84.s")
#endif

#ifdef VERSION_US
extern void func_80018728(u32, ...); extern u8 D_80090B8C; void func_8002602C(void) { s32 mask; func_80018728(0x83030000, 0); mask = osSetIntMask(1); D_80090B8C = 0; osSetIntMask(mask); }
#endif

#ifdef VERSION_US
extern void func_80034E5C(s32, s32);

void func_80026068(u32 arg0) {
    s32 temp_a1;

    if (arg0 != 0) {
        temp_a1 = arg0 - 1;
        if (arg0 < 0xFCU) {
            func_80034E5C(temp_a1 & 0xFFFF, temp_a1);
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_80034F30(void); void func_80026098(void) { func_80034F30(); }
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800260C0.s")
#endif

#ifdef VERSION_US
s32 func_80018ACC();
extern u8 D_80090B64;
s32 func_80026298(void) {
    func_80018810();
    if (D_80090B64 != 0) {
        if (func_80018ACC() == 0) {
            return 0;
        }
        D_80090B64 = 0;
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 1;
    }
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800262F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800265B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800266F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026938.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026990.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026BB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026C80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026E08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026ED8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80026F44.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002702C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800271DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002730C.s")
#endif

#ifdef VERSION_US
s32 func_8002738C(s32 arg0) {
    s32 *ptr = &arg0;
    arg0 = *ptr & 0xFF;
    if (arg0 < 0xF) {
        arg0 = (arg0 + 1) & 0xFF;
    } else {
        arg0 = 0;
    }
    return arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800273B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027490.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800275E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027634.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027774.s")
#endif

#ifdef VERSION_US

extern void func_8002781C(u16 resource_id, u8 mode, ...);
void func_800277C4(u16 resource_id, u8 mode) {
    func_8002781C(resource_id, mode);
}
#endif

#ifdef VERSION_US
void func_800277F0(u16 resource_id, void *context) {
    func_8002781C(resource_id, 0, context);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002781C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800278C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800279C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027A28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027BD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027E30.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027EE0.s")
#endif

#ifdef VERSION_US
extern void func_80027F7C();
extern s8 D_80090BB0;

void func_80027F4C(void) {
    func_80018728(0x83020000U, 0x14);
    func_80027F7C();
    D_80090BB0 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80027F7C.s")
#endif

#ifdef VERSION_US
extern u8 D_8011F300;
extern void func_80027EE0(s32);
extern void func_800279C4(s32);

void func_80028014(void) {
    func_80027EE0(0xFFD);
    func_800279C4(0xCF07);
    if (D_8011F300 == 0x5C) {
        func_80018728(0x83000000U, 0x1E);
        return;
    }
    func_80018728(0xF1000000U, 0);
}
#endif

#ifdef VERSION_US
extern u8 D_8011BE90;
extern u16 D_800D2B44;
extern s16 D_800D2BA8;
extern u8 D_800D2B78;
s32 func_8002806C(void) {
    u8 *base;
    s32 result;

    base = &D_8011BE90;
    result = *(u8 *)(base + 0x3470) - 0x27;
    if (((u32)*(s32 *)(base + 0x346C) >> 31) == 0) {
        return 0;
    }
    return result;
}
#endif

#ifdef VERSION_US
void func_8002809C(void) {
    func_80018728(0xF2000000, 0);
}
#endif

#ifdef VERSION_US

void func_800280C0(void) {
    func_80027EE0(0xFFE);
    func_80018728(0x4B000000U, 1);
}
#endif

#ifdef VERSION_US

void func_800280EC(void) {
    func_80027EE0(0xFFF);
    func_80018728(0x4C000000U, 1);
}
#endif

#ifdef VERSION_US
extern u8 D_80090BB4;
void func_80028118(u8 arg0) {
    D_80090BB4 = arg0 + 1;
}
#pragma C_FUNCTION_PADDING(20)
#endif

#ifdef VERSION_US
extern u8 D_800D1A70;
extern u8 D_800D1A78;
extern u8 D_800D1A80;
extern u8 D_800D1A82;
void func_80028140(void) {
    (*(s32 *)((u8 *)(&D_800D1A70) + (0))) = -1;
    (*(s32 *)((u8 *)(&D_800D1A70) + (4))) = -1;
    (*(s32 *)((u8 *)(&D_800D1A78) + (0))) = -1;
    (*(s32 *)((u8 *)(&D_800D1A78) + (4))) = -1;
    (*(s8 *)((u8 *)(&D_800D1A80) + (0))) = 0x7F;
    (*(s8 *)((u8 *)(&D_800D1A80) + (1))) = 0x7F;
    (*(s8 *)((u8 *)(&D_800D1A82) + (0))) = 0;
    (*(s8 *)((u8 *)(&D_800D1A82) + (1))) = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002818C.s")
#endif

#ifdef VERSION_US
void func_80028300(void) {
    func_8001874C(0x06040003, 1);
    func_8001874C(0x06040103, 1);
    func_80028140();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028340.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800284C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028540.s")
#endif

#ifdef VERSION_US
void Audio_SwapSoundCandidates(u8 *arg0, u8 *arg1) { if (*arg0 != *arg1) { u8 temp = *arg0; *arg0 = *arg1; *arg1 = temp; } }
#endif

#ifdef VERSION_US
extern u32 D_800D1AD8[24];
u16 Audio_FilterRecentSoundId(u16 arg0) {
    s32 i;
    for (i = 0; i < 24; i++) {
        if (arg0 == D_800D1AD8[i]) return 0;
    }
    return arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800289B0.s")
#endif

#ifdef VERSION_US
void Audio_RemoveRecentSoundAt(u16 arg0) {
    u32 i;
    for (i = arg0; i > 0; i--) D_800D1AD8[i] = D_800D1AD8[i - 1];
    D_800D1AD8[0] = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028ADC.s")
#endif

#ifdef VERSION_US
extern void func_800314D4(s32);
extern s32 func_80028ADC(void);
void func_80028CA8(void) {
    s32 v0;
    s32 masked;

    v0 = func_80028ADC();
    masked = v0 & 0xFFFF;
    if (v0 != 0) {
        func_800314D4(masked);
    }
}
void func_80028CA8_padding(void) {}
void func_80028CA8_padding2(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028CE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028D9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028E60.s")
#endif

#ifdef VERSION_US
void func_80028EA8(void) { extern u8 D_80091B90[]; func_80028D9C(D_80091B90); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80028ECC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A1FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A25C.s")
#endif

#ifdef VERSION_US
extern u16 D_80090BA0;
extern u8 D_800D2650[];
void func_8002A7A8(s32 arg0, s32 arg1) { D_800D2650[0] = arg0; D_800D2650[1] = arg1; D_800D2650[3] = D_80090BA0; if (D_80090BA0 == 1) D_800D2650[2] = 1; else D_800D2650[2] = 0; D_800D2650[4] = 0; *(u32 *)(D_800D2650 + 8) = 0; }
#endif

#ifdef VERSION_US
extern s8 D_80091A0C;

void func_8002A7E8(s32 arg0) {
    if (arg0 != 0) {
        D_80091A0C = 1;
        return;
    }
    D_80091A0C = 0;
}
#endif

#ifdef VERSION_US
extern s8 D_80091A10;

void func_8002A80C(s32 arg0) {
    if (arg0 != 0) {
        D_80091A10 = 1;
        return;
    }
    D_80091A10 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A830.s")
#endif

#ifdef VERSION_US
extern s32 D_800D2630;

void func_8002A9C0(s32 arg0) {
    D_800D2630 = arg0;
}
#endif

#ifdef VERSION_US
extern s32 D_800D2634;

void func_8002A9CC(s32 arg0) {
    D_800D2634 = arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002A9D8.s")
#endif

#ifdef VERSION_US
extern s8 D_80091A18;
void func_8002AAD0(u8 arg0) {
    if (arg0) {
        D_80091A18 = 1;
        return;
    }
    D_80091A18 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002AAFC.s")
#endif

#ifdef VERSION_US
extern void func_8002A25C();
extern void func_80024180();
void func_8002B1A0(void) { func_8002A25C(); func_80024180(0, 0); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B1CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B2FC.s")
#endif

#ifdef VERSION_US
extern void func_80023A3C(s32, s32, s32);
extern void func_8002AAFC(s32);
extern void func_800314D4(s32);

void func_8002B43C(void) {
    D_80091A18 = 0;
    func_8002AAFC(0);
    func_80023A3C(3, 0, 0);
    func_800314D4(0x2226);
}
#endif

#ifdef VERSION_US
extern s32 D_80091B08, D_80091B0C;
void func_8002B47C(s32 arg0, s32 arg1) {
    D_80091B08 = arg0;
    D_80091B0C = arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B490.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002B5B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002BE44.s")
#endif

#ifdef VERSION_US
extern u32 D_80091A2C;
extern s16 D_800D1AB8[];
void func_8002C2A0(unsigned short arg0)
{
  D_800D1AB8[D_80091A2C] = arg0;
  D_80091A2C = D_80091A2C + 1;
  if (((u32) D_80091A2C) >= 10U)
  {
    D_80091A2C = D_80091A2C - 1;
  }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8002C2E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80030420.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80030AD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003121C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800314D4.s")
#endif

#ifdef VERSION_US
void func_80031530(u16 a) {
    func_800314D4(a | 0x10000000);
}

void func_80031530_padding(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031564.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800315E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031638.s")
#endif

#ifdef VERSION_US
extern u8 D_800D1B90[];
void func_80031844(s32 arg0, s32 arg1) { s32 *p0 = &arg0; *p0 = arg0; arg0 &= 0xFF; if (arg0 < 2) { if (arg1 <= 0) D_800D1B90[arg0] = 0; else D_800D1B90[arg0] = arg1; } }
#endif

#ifdef VERSION_US
void func_80031880(s32 arg0, s32 arg1) {
    switch (arg1) {
        case 1:
            arg0 |= 0x3000;
            break;
        case 2:
            arg0 |= 0x2000;
            break;
        case 0:
            break;
        default:
            return;
    }
    func_800314D4(arg0);
}
#endif

#ifdef VERSION_US
s32 func_80019230(s32, s32, s32);

s32 func_800318C8(void) {
    if (func_80019230(4, 1, 0) != 0) {
        return 1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800318FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800319D0.s")
#endif

#ifdef VERSION_US
extern u8 D_800D2AD8[];
u8 GbAudio_GetRegisterValue(char arg0)
{
  return D_800D2AD8[arg0 & 0xFF];
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031A6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031C84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031E6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80031F00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80032600.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80032A28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80032E40.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80032F0C.s")
#endif

#ifdef VERSION_US
extern u16 D_800D2B5C;
extern void func_80032F0C(void);
void func_80033188(void) {
    u16 sp1E;

    sp1E = D_800D2B5C;
    func_80032F0C();
    D_800D2B5C = sp1E;
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B41; void func_800331B8(void) { D_800D2B41 = 1; }
#endif

#ifdef VERSION_US
extern u8 D_800D2B41; void func_800331C8(void) { D_800D2B41 = 0; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800331D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800333CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033488.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800334C0.s")
#endif

#ifdef VERSION_US
extern void func_80033670(s32);
extern void func_80033864(s32);
extern void func_80033890(s32);
void func_8003364C(s32 arg0) { s32 *p = &arg0; func_80033670(arg0 & 0xFF); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033670.s")
#endif

#ifdef VERSION_US
void func_800337D8(s32 arg0) { s32 *p = &arg0; func_80033864(arg0 & 0xFF); }
#endif

#ifdef VERSION_US
extern void func_800319D0(s32, s32, s32);
extern u8 D_800D2B43;
void func_800337FC(void) {
    s32 var_s0;

    var_s0 = 0x20;
    do {
        func_800319D0(var_s0 & 0xFFFF, 0, 0);
        var_s0 += 1;
    } while (var_s0 != 0x30);
    func_800319D0(0xFF1C, ((D_800D2B43 & 0xF0) * 2) & 0xFF, 0);
}
#endif

#ifdef VERSION_US
void func_80033864(s32 arg0) {}
#endif

#ifdef VERSION_US
void func_8003386C(s32 arg0) { s32 *p = &arg0; func_80033890(arg0 & 0xFF); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033890.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033950.s")
#endif

#ifdef VERSION_US
void func_800339DC(s32 arg0) {}
#endif

void func_800339E4(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800339EC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033A78.s")
#endif

#ifdef VERSION_US
void func_80033ACC(u8 arg0) {
    D_800D2B44 += *(s16 *)((u8 *)&D_800D2BA8 + (arg0 * 0x3C));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033B04.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033BF4.s")
#endif

#ifdef VERSION_US
void func_80033C40(s32 arg0) {}
#endif

#ifdef VERSION_US
void func_80033C48(s32 arg0) {}
#endif

#ifdef VERSION_US
void func_80033C50(s32 arg0) {}
#endif

#ifdef VERSION_US
extern u8 D_800D2B49;
extern u8 D_800D2B68;
extern u8 D_800D2B6A;
void func_80033C58(u8 arg0) {
    if (arg0 != 4) return;
    *(s16 *)((u8 *)&D_800D2B78 + 0x15C) = 0;
    *(s16 *)((u8 *)&D_800D2B78 + 0x1D4) = 0;
    D_800D2B49 = D_800D2B68;
    D_800D2B68 = 0;
    D_800D2B6A = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033CA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033E34.s")
#endif

void func_80033ED0(void) {
}

#ifdef VERSION_US
extern void (*D_800921E4[])(u8, u8);
void func_80033ED8(u8 a, u8 b) {
    D_800921E4[b](a, b);
}
#endif

#ifdef VERSION_US
void func_80033F14(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
void func_80033F20(u8 arg0, u8 arg1) {
    u8 *entry;

    entry = &D_800D2B78 + (arg0 * 0x3C);
    entry[3] &= 0xFFFD;
    *(s32 *)(entry + 8) = *(s32 *)(entry + 0xC);
}
#endif

#ifdef VERSION_US
void func_80033F5C(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
void func_80033F68(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80033F74.s")
#endif

#ifdef VERSION_US
s8 func_800347E8(u8);
extern u8 D_800D2B8D;

void func_80034058(u8 arg0, s32 arg1) {
    *(&D_800D2B8D + (arg0 * 0x3C)) = func_800347E8(arg0);
}
#endif

#ifdef VERSION_US
void func_80034098(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
void func_800340A4(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
extern u8 D_800D2B69;
void func_800340B0(s32 arg0, s32 arg1) {
    D_800D2B69 = 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800340C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034118.s")
#endif

#ifdef VERSION_US
void func_800341BC(s32 arg0, s32 arg1) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800341C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034238.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003428C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800342F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034348.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034394.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800343FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034464.s")
#endif

#ifdef VERSION_US
extern s8 D_800D2B4B;

void func_800344C4(u8 arg0, s32 arg1) {
    void *temp_v1;

    D_800D2B4B = func_800347E8(arg0);
    temp_v1 = (arg0 * 0x3C) + &D_800D2B78;
    (*(u8 *)((u8 *)(temp_v1) + (0x14))) = (u8) ((*(u8 *)((u8 *)(temp_v1) + (0x14))) | 8);
}
#endif

#ifdef VERSION_US
extern u8 D_800D2B8E;
void func_80034518(u8 arg0, s32 arg1)
{
  unsigned char new_var;
  new_var = func_800347E8(arg0);
  (&D_800D2B8E)[0x3C * arg0] = (new_var << 1) << 5;
}
#endif

#ifdef VERSION_US
s8 func_800347E8(u8);
extern u8 D_800D2B8F;

void func_8003455C(u8 arg0, s32 arg1) {
    *(&D_800D2B8F + (arg0 * 0x3C)) = func_800347E8(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003459C.s")
#endif

#ifdef VERSION_US
extern u8 D_800D2B93[];
void func_800345E8(s32 arg0, s32 arg1) {
    s32 *p0 = &arg0;
    s32 *p1 = &arg1;
    arg0 = *p0 & 0xFF;
    *(u8 *)(D_800D2B93 + (arg0 * 0x3C)) = *p1 & 7;
}
#endif

#ifdef VERSION_US
s8 func_800347E8(u8);
extern u8 D_800D2B94;

void func_80034614(u8 arg0, s32 arg1) {
    *(&D_800D2B94 + (arg0 * 0x3C)) = func_800347E8(arg0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034654.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800346A4.s")
#endif

#ifdef VERSION_US
extern u8 D_800D2B59;
extern u8 D_800D2B49;
void func_800346F8(u8 arg0, s32 arg1) {
    s8 result = func_800347E8(arg0);
    if (D_800D2B59 == 0) D_800D2B49 = result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034738.s")
#endif

#ifdef VERSION_US
extern u8 D_800D2B6A;
void func_800347A4(s32 arg0, s32 arg1) {
    D_800D2B6A = 1;
}
#endif

#ifdef VERSION_US
void func_800347BC(s32 arg0, s32 arg1) {
    D_800D2B6A = 0;
}
#endif

#ifdef VERSION_US
void func_800347D0(s32 arg0, s32 arg1) { }
#endif

#ifdef VERSION_US
void func_800347DC(s32 arg0, s32 arg1) { }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800347E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034838.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800348C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003492C.s")
#endif

#ifdef VERSION_US
extern void func_80034A50(u8);
void func_80034A08(u8 arg0) {
    void *temp_v0;

    func_80034A50(arg0);
    temp_v0 = (arg0 * 0x3C) + &D_800D2B78;
    (*(u8 *)((u8 *)(temp_v0) + (3))) = (u8) ((*(u8 *)((u8 *)(temp_v0) + (3))) | 1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034A50.s")
#endif

#ifdef VERSION_US
extern u16 D_800D2B4C;

void func_80034A94(u16 arg0) {
    func_800331C8();
    D_800D2B4C = arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034ABC.s")
#endif

#ifdef VERSION_US
void func_80034C48(s32 arg0) { }
#endif

#ifdef VERSION_US
void func_80034C50(s32 arg0) { }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034C58.s")
#endif

#ifdef VERSION_US
u8 func_80034CF8(const u8 *arg0) { return arg0[0]; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034D00.s")
#endif

#ifdef VERSION_US
u8 func_80034D98(const u8 *arg0) { return arg0[0]; }
#endif

#ifdef VERSION_US
extern u8 D_80092520; extern u8 D_800925E4[]; extern u8 D_800925E8[]; u8 *func_80034DA0(void) { if (D_80092520 & 0x20) return D_800925E8; return D_800925E4; }
#endif

#ifdef VERSION_US
extern void func_80032F0C(void); void func_80034DD0(void) { func_80032F0C(); }
#endif

#ifdef VERSION_US
extern void func_800331D4(void); void func_80034DF0(void) { func_800331D4(); }
#endif

#ifdef VERSION_US
u8 func_80034E10(const u8 *arg0, s32 unused) { return arg0[0]; }
#endif

#ifdef VERSION_US
extern void func_80032F0C(void);
extern void func_80034A94(u16 arg0);
void func_80034E1C(u16 arg0) {
    if (arg0 & 0xFF) {
        func_80034A94(arg0);
    } else {
        func_80032F0C();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034E5C.s")
#endif

#ifdef VERSION_US
void func_80034EA4(void) { D_800D2B49 = 0x77; }
#endif

#ifdef VERSION_US
void func_80034EB4(void) { D_800D2B49 = 0x33; }
#endif

#ifdef VERSION_US
extern u8 D_800D2B49; void func_80034EC4(void) { D_800D2B49 = 0; }
#endif

#ifdef VERSION_US
void func_80034ED0(void) { D_800D2B59 = 4; }
#endif

#ifdef VERSION_US
void func_80034EE0(void) { D_800D2B59 = 0x84; }
#endif

#ifdef VERSION_US
void func_80034EF0(s32 arg0)
{
  s32 var_s0;
  var_s0 = arg0 & 0xFF;
  if (var_s0 != 0)
  {
    do
    {
      var_s0 = ((unsigned long) (var_s0 - 1)) & 0xFF;
      func_80034DF0();
    }
    while (var_s0 != 0);
    if (arg0)
    {
    }
  }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80034F30.s")
#endif

#ifdef VERSION_US
extern s32 D_80094570;

void func_80034FE0(void) {
    if ((s8) D_80090B8C != 0) {
        func_80034DF0();
    }
    D_80094570 += 1;
}
#endif

#ifdef VERSION_US
extern OSMesgQueue D_800D2D60;
extern OSPiHandle *D_800D2D78;
extern void *D_800D2D7C;
void func_80035020(s32 arg0) {
    if (arg0 != 1) {
        D_800D2D78 = osCartRomInit();
    }
    osCreateMesgQueue(&D_800D2D60, &D_800D2D7C, 1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035068.s")
#endif

#ifdef VERSION_US
extern s32 D_80094850; void func_80035140(s32 value) { D_80094850 = value; }
#endif

#ifdef VERSION_US
s32 func_8003514C(void) { return (s32)D_80094850; }
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
extern s32 D_80094870[];
s32 func_80035160(s32 index) { return D_80094870[index]; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035174.s")
#endif

#ifdef VERSION_US
extern void func_80035174(void *);
extern OSThread D_80122B20;
extern u8 D_80124D00[];
void Thread4_CreateThread(void) {
    osCreateThread(&D_80122B20, 4, func_80035174, NULL, D_80124D00, 0x50);
    osStartThread(&D_80122B20);
}
#endif

#ifdef VERSION_US
extern void func_80021BBC(void);
void func_8003539C(void) {
    func_80021BBC();
}
#endif

#ifdef VERSION_US
extern s32 func_80025C9C(void);
extern s32 D_80122A40;
s32 Audio_StopProcessing(void) {
    func_80025C9C();
    D_80122A40 = 0;
    return 0;
}
#endif

#ifdef VERSION_US
extern s32 func_80025D44(void);
s32 Audio_WaitForPendingTasks(void) {
    s32 completed = 0;

    while (func_80025D44() != 0) {
        completed++;
    }
    return completed;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035424.s")
#endif

#ifdef VERSION_US
void Audio_SetProcessingEnabled(s32 enabled) { D_80122A40 = enabled ? 0 : 1; }
#endif

#ifdef VERSION_US
extern s32 D_80094860;
void Audio_ResetModeSelector(void) {
    D_80094860 = -1;
}
#endif

#ifdef VERSION_US
extern s32 D_80094868;
void Audio_EnableModeFlag(void) {
    D_80094868 = 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800354B4.s")
#endif

#ifdef VERSION_US
extern s32 D_80094864;
void Audio_ResetRequestId(void) {
    D_80094864 = -1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800355E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035620.s")
#endif

#ifdef VERSION_US
s32 func_800356CC(s32 arg0) { s32 result = 0; if (arg0 >= 0 && arg0 < 19) result = *((s32 *)((u8 *)D_80124D00 + arg0 * 4)); return result; }
#pragma C_FUNCTION_PADDING(12)
#endif

#ifdef VERSION_US
extern u32 D_80124D50;
void func_80035700(u32 seed) {
    D_80124D50 = seed;
}
#endif

#ifdef VERSION_US
u32 func_8003570C(void) {
    D_80124D50 = D_80124D50 * 0x0019660D + 0x3C6EF35F;
    return D_80124D50;
}
#endif

#ifdef VERSION_US
typedef struct { u8 r, g, b, a; } Color3573C;
Color3573C *Color_SetRGB(Color3573C *arg0, u8 r, u8 g, u8 b) {
    arg0->r = r;
    arg0->g = g;
    arg0->b = b;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { u8 r, g, b, a; } Color3575C;
Color3575C *Color_SetRGBA(Color3575C *arg0, u8 r, u8 g, u8 b, u8 a) {
    arg0->r = r;
    arg0->g = g;
    arg0->b = b;
    arg0->a = a;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f35784;
Vec3f35784 *Vec3f_SetComponents(Vec3f35784 *arg0, f32 x, f32 y, f32 z) {
    arg0->x = x;
    arg0->y = y;
    arg0->z = z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f357A8;
Vec3f357A8 *Vec3f_SetComponentsDuplicate(Vec3f357A8 *arg0, f32 x, f32 y, f32 z) {
    arg0->x = x;
    arg0->y = y;
    arg0->z = z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f357CC;
Vec3f357CC *Vec3f_AddInPlace(Vec3f357CC *arg0, Vec3f357CC *arg1) {
    arg0->x += arg1->x;
    arg0->y += arg1->y;
    arg0->z += arg1->z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f35804;
Vec3f35804 *Vec3f_Add(Vec3f35804 *arg0, Vec3f35804 *arg1, Vec3f35804 *arg2) {
    arg0->x = arg1->x + arg2->x;
    arg0->y = arg1->y + arg2->y;
    arg0->z = arg1->z + arg2->z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f3583C;
Vec3f3583C *Vec3f_SubtractInPlace(Vec3f3583C *arg0, Vec3f3583C *arg1) {
    arg0->x -= arg1->x;
    arg0->y -= arg1->y;
    arg0->z -= arg1->z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f35874;
Vec3f35874 *Vec3f_Subtract(Vec3f35874 *arg0, Vec3f35874 *arg1, Vec3f35874 *arg2) {
    arg0->x = arg1->x - arg2->x;
    arg0->y = arg1->y - arg2->y;
    arg0->z = arg1->z - arg2->z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f358AC;
typedef struct { s16 x, y, z; } Vec3s358AC;
Vec3f358AC *Vec3f_FromVec3s(Vec3f358AC *arg0, Vec3s358AC *arg1) {
    arg0->x = arg1->x;
    arg0->y = arg1->y;
    arg0->z = arg1->z;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f358F0;
Vec3f358F0 *Vec3f_CrossProductFromPoints(Vec3f358F0 *arg0, Vec3f358F0 *arg1, Vec3f358F0 *arg2, Vec3f358F0 *arg3) {
    arg0->x = ((arg2->y - arg1->y) * (arg3->z - arg2->z)) - ((arg3->y - arg2->y) * (arg2->z - arg1->z));
    arg0->y = ((arg2->z - arg1->z) * (arg3->x - arg2->x)) - ((arg3->z - arg2->z) * (arg2->x - arg1->x));
    arg0->z = ((arg2->x - arg1->x) * (arg3->y - arg2->y)) - ((arg3->x - arg2->x) * (arg2->y - arg1->y));
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct {
    f32 x, y, z;
} Vec3f359A0;

Vec3f359A0 *Vec3f_CrossProduct(Vec3f359A0 *out, Vec3f359A0 *a, Vec3f359A0 *b) {
    out->x = (a->y * b->z) - (b->y * a->z);
    out->y = (a->z * b->x) - (b->z * a->x);
    out->z = (a->x * b->y) - (b->x * a->y);
    return out;
}
#endif

#ifdef VERSION_US
typedef struct { f32 x, y, z; } Vec3f35A10;
Vec3f35A10 *func_80035A10(Vec3f35A10 *arg0) {
    f32 scale = 1.0f / sqrtf((arg0->x * arg0->x) + (arg0->y * arg0->y) + (arg0->z * arg0->z));
    arg0->x *= scale; arg0->y *= scale; arg0->z *= scale; return arg0;
}
#endif

#ifdef VERSION_US
void *Vec3s_SetComponents(void *arg0, s16 arg1, s16 arg2, s16 arg3) {
    (*(s16 *)((u8 *)(arg0) + (0))) = arg1;
    (*(s16 *)((u8 *)(arg0) + (2))) = arg2;
    (*(s16 *)((u8 *)(arg0) + (4))) = arg3;
    return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { s16 x, y, z; } Vec3s35AA0;
Vec3s35AA0 *Vec3s_AddInPlace(Vec3s35AA0 *arg0, Vec3s35AA0 *arg1) {
    arg0->x += arg1->x; arg0->y += arg1->y; arg0->z += arg1->z; return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { s16 x, y, z; } Vec3s35AD8;
Vec3s35AD8 *Vec3s_Add(Vec3s35AD8 *arg0, Vec3s35AD8 *arg1, Vec3s35AD8 *arg2) {
    arg0->x = arg1->x + arg2->x; arg0->y = arg1->y + arg2->y; arg0->z = arg1->z + arg2->z; return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { s16 x, y, z; } Vec3s35B10;
Vec3s35B10 *Vec3s_SubtractInPlace(Vec3s35B10 *arg0, Vec3s35B10 *arg1) {
    arg0->x -= arg1->x; arg0->y -= arg1->y; arg0->z -= arg1->z; return arg0;
}
#endif

#ifdef VERSION_US
typedef struct { s16 x, y, z; } Vec3s35B48;
Vec3s35B48 *Vec3s_Subtract(Vec3s35B48 *arg0, Vec3s35B48 *arg1, Vec3s35B48 *arg2) {
    arg0->x = arg1->x - arg2->x; arg0->y = arg1->y - arg2->y; arg0->z = arg1->z - arg2->z; return arg0;
}
#endif

#ifdef VERSION_US
#define ROUND_MAX(x) ((x) + ((x) > 0.0f ? 0.5f : -0.5f))
typedef struct { s16 x, y, z; } Vec3s35B80;
typedef struct { f32 x, y, z; } Vec3f35B80;
Vec3s35B80 *Vec3s_FromVec3f(Vec3s35B80 *arg0, Vec3f35B80 *arg1) {
    arg0->x = ROUND_MAX(arg1->x); arg0->y = ROUND_MAX(arg1->y); arg0->z = ROUND_MAX(arg1->z); return arg0;
}
#endif

#ifdef VERSION_US
void MtxF_Copy(u32 *dest, u32 *src) {
    if (dest != src) {
        s32 i; u32 *d = dest; u32 *s = src;
        for (i = 0; i < 16; i++) { *d++ = *s++; }
    }
}
#endif

#ifdef VERSION_US
void MtxF_Identity(f32 *arg0) {
    s32 i;
    f32 *dest;
    for (dest = arg0 + 1, i = 0; i < 14; dest++, i++) { *dest = 0.0f; }
    for (dest = arg0, i = 0; i < 4; dest += 5, i++) { *dest = 1.0f; }
}
#endif

#ifdef VERSION_US
extern void MtxF_Identity(f32 *arg0);
void MtxF_SetTranslation(f32 *dest, f32 *source) {
    MtxF_Identity(dest);
    dest[12] = source[0];
    dest[13] = source[1];
    dest[14] = source[2];
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035D14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80035FFC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003614C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80036284.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80036430.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800365B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80036714.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003691C.s")
#endif

#ifdef VERSION_US
typedef struct S1_Vec3s S1_Vec3s;
struct S1_Vec3s {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
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
extern f32 D_80087E50[];
extern f32 D_80088E50[0x1000];
typedef struct S1_Vec3f S1_Vec3f;
struct S1_Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
};
extern S1_Vec3f D_800948D0;
typedef union S1_Vec2s_s32 S1_Vec2s_s32;
union S1_Vec2s_s32 {
    struct {
        /* 0x0 */ s16 x;
        /* 0x2 */ s16 y;
    };
    s32 xy;
};
typedef union S1_Color_RGBA8_u32 S1_Color_RGBA8_u32;
union S1_Color_RGBA8_u32 {
    struct {
        u8 r, g, b, a;
    };
    u32 rgba;
};
typedef struct S1_GraphNode S1_GraphNode;
typedef struct S1_unk_D_86002F34_00C S1_unk_D_86002F34_00C;
typedef struct S1_unk_D_86002F34_00C_040 S1_unk_D_86002F34_00C_040;
typedef struct S1_unk_D_86002F34_00C_0CC S1_unk_D_86002F34_00C_0CC;
typedef struct S1_unk_D_86002F34_00C_060 S1_unk_D_86002F34_00C_060;
typedef struct S1_unk_D_86002F34_00C_024 S1_unk_D_86002F34_00C_024;
typedef struct S1_unk_D_86002F34_00C_018 S1_unk_D_86002F34_00C_018;
typedef s32 (*S1_func_D_86002F34_000_010)(s32, struct S1_GraphNode*);
extern void *func_80003240();
struct S1_GraphNode {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ struct S1_GraphNode* unk_04;
    /* 0x08 */ struct S1_GraphNode* unk_08;
    /* 0x0C */ struct S1_unk_D_86002F34_00C* unk_0C;
    /* 0x10 */ S1_func_D_86002F34_000_010 unk_10;
    /* 0x14 */ void* unk_14;
};
struct S1_unk_D_86002F34_00C_040 {
    /* 0x00 */ Mtx* mtx;
    /* 0x04 */ f32 l;
    /* 0x08 */ f32 r;
    /* 0x0C */ f32 b;
    /* 0x10 */ f32 t;
    /* 0x14 */ f32 n;
    /* 0x18 */ f32 f;
    /* 0x1C */ f32 scale;
};
struct S1_unk_D_86002F34_00C_0CC {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ S1_Color_RGBA8_u32 color;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ u8* texture;
};
struct S1_unk_D_86002F34_00C_024 {
    /* 0x00 */ Mtx* mtx;
    /* 0x04 */ u16 perspNorm;
    /* 0x08 */ f32 fovy;
    /* 0x0C */ f32 aspect;
    /* 0x10 */ f32 near;
    /* 0x14 */ f32 far;
    /* 0x18 */ f32 scale;
};
struct S1_unk_D_86002F34_00C_060 {
    /* 0x00 */ S1_MtxF* p_mtxf;
    /* 0x04 */ S1_MtxF mtxf;
    /* 0x44 */ LookAt* lookat;
    /* 0x48 */ S1_Vec3f eye;
    /* 0x54 */ S1_Vec3f at;
    /* 0x60 */ S1_Vec3f up;
};
struct S1_unk_D_86002F34_00C_018 {
    /* 0x00 */ Vp* vp;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 width;
    /* 0x0A */ s16 height;
};
struct S1_unk_D_86002F34_00C {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ S1_unk_D_86002F34_00C_018 unk_18;	//	viewPort
    /* 0x24 */ S1_unk_D_86002F34_00C_024 unk_24;	//	projection
    /* 0x40 */ S1_unk_D_86002F34_00C_040 unk_40;
    /* 0x60 */ S1_unk_D_86002F34_00C_060 unk_60;	//	camera
    /* 0xCC */ S1_unk_D_86002F34_00C_0CC unk_CC;
    /* 0xEC */ char unkEC[0x4];
};
extern Vtx *func_8003946C(S1_unk_D_86002F34_00C_0CC *, S1_unk_D_86002F34_00C_040 *);
typedef struct S1_MainPoolState S1_MainPoolState;
typedef struct S1_MainPoolBlock S1_MainPoolBlock;
struct S1_MainPoolState {
    /* 0x00 */ s32 freeSpace;
    /* 0x04 */ S1_MainPoolBlock *listHeadL;
    /* 0x08 */ S1_MainPoolBlock *listHeadR;
    /* 0x0C */ struct S1_MainPoolState *prev;
};
typedef void (*S1_AllocateFunc)(struct S1_MainPoolBlock*, u32);
struct S1_MainPoolBlock {
    /* 0x00 */ struct S1_MainPoolBlock *prev;
    /* 0x04 */ struct S1_MainPoolBlock *next;
    /* 0x08 */ S1_AllocateFunc func;
    /* 0x0C */ s32 arg; // passed into func as the 2nd argument.
};
typedef struct S1_unk_D_86002F34_alt2 S1_unk_D_86002F34_alt2;
struct S1_unk_D_86002F34_alt2 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ S1_GraphNode* unk_18;
};
typedef struct S1_MemoryBlock S1_MemoryBlock;
struct S1_MemoryBlock {
    /* 0x00 */ struct S1_MemoryBlock *next;
    /* 0x04 */ u32 size;
};
typedef struct S1_unk_D_86002F34_alt13 S1_unk_D_86002F34_alt13;
struct S1_unk_D_86002F34_alt13 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
};
typedef struct S1_unk_D_86002F34_alt1 S1_unk_D_86002F34_alt1;
struct S1_unk_D_86002F34_alt1 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ s8 unk_1C;
    /* 0x1D */ s8 unk_1D;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ Lights7* lights;
};
typedef struct S1_unk_D_86002F34_alt14 S1_unk_D_86002F34_alt14;
struct S1_unk_D_86002F34_alt14 {
    /* 0x00 */ S1_GraphNode unk_00;
};
typedef struct S1_unk_D_86002F34_alt15 S1_unk_D_86002F34_alt15;
struct S1_unk_D_86002F34_alt15 {
    /* 0x00 */ S1_GraphNode unk_00;
};
typedef struct S1_unk_D_86002F34_alt16 S1_unk_D_86002F34_alt16;
struct S1_unk_D_86002F34_alt16 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ u32 unk_18;
};
typedef struct S1_unk_D_8690A610 S1_unk_D_8690A610;
typedef struct S1_unk_D_8690A610_018 S1_unk_D_8690A610_018;
typedef struct S1_unk_D_86002F58_004_000_000 S1_unk_D_86002F58_004_000_000;
typedef struct S1_unk_D_86002F58_004_000_00C S1_unk_D_86002F58_004_000_00C;
typedef struct S1_unk_D_86002F58_004_000_010 S1_unk_D_86002F58_004_000_010;
typedef struct S1_unk_D_86002F58_004_000_010_024 S1_unk_D_86002F58_004_000_010_024;
typedef union S1_arg1_func_80010CA8 S1_arg1_func_80010CA8;
typedef struct S1_unk_D_86002F58_004_000_004 S1_unk_D_86002F58_004_000_004;
typedef struct S1_unk_D_86002F58_004_000_00C_028 S1_unk_D_86002F58_004_000_00C_028;
struct S1_unk_D_8690A610_018 {
    /* 0x00 */ s16 fogNear; // GeoNode_CreateFog's arg2
    /* 0x02 */ s16 fogFar; // GeoNode_CreateFog's arg3
    /* 0x04 */ S1_Color_RGBA8_u32 fogColor;
};
struct S1_unk_D_86002F58_004_000_000 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ struct S1_unk_D_86002F58_004_000_000* unk_04;
    /* 0x08 */ struct S1_unk_D_86002F58_004_000_000* unk_08;
    /* 0x0C */ S1_unk_D_86002F58_004_000_00C* unk_0C;
    /* 0x10 */ S1_unk_D_86002F58_004_000_010* unk_10;
    /* 0x14 */ s32 unk_14;
};
struct S1_unk_D_8690A610 {
    /* 0x00 */ S1_unk_D_86002F58_004_000_000 unk_00;
    /* 0x18 */ S1_unk_D_8690A610_018 unk_18;
};
struct S1_unk_D_86002F58_004_000_004 {
    /* 0x00 */ struct S1_unk_D_86002F58_004_000_004* unk_00[4];
    /* 0x10 */ struct S1_unk_D_86002F58_004_000_00C* unk_10;
    /* 0x14 */ S1_unk_D_86002F58_004_000_010* unk_14;
};
typedef S1_unk_D_86002F58_004_000_00C_028* (*S1_unk_D_86002F58_004_000_00C_028_func)(s32, s32);
struct S1_unk_D_86002F58_004_000_00C {
    /* 0x00 */ S1_unk_D_86002F58_004_000_004 unk_00;
    /* 0x18 */ char unk_18[0x10];
    /* 0x28 */ S1_unk_D_86002F58_004_000_00C_028_func unk_28;
};
union S1_arg1_func_80010CA8 {
    struct {
        /* 0x00 */ s16 unk_00;
        /* 0x02 */ s8 unk_02;
        /* 0x03 */ s8 unk_03;
    };
    u32 raw;
};
struct S1_unk_D_86002F58_004_000_010 {
    /* 0x00 */ u8 configFlags; // PokeIcon_AllocFramebuffers's arg0: bit0=frame-load enabled, bit1=background-load enabled, bit2=double-buffered, bit3=quad-buffered
    /* 0x01 */ u8 pendingFlags; // bit0=frame load pending, bit1=background load pending (PokeIcon_RequestFrameLoad/RequestBackgroundLoad/ApplyLoadResult)
    /* 0x02 */ u8 activeVariant; // index into framebuffers[], flipped by configFlags bit2 in PokeIcon_RequestFrameLoad
    /* 0x04 */ s32 framebuffers[1]; // declared size undersells - up to 5 entries when configFlags bit3 is set (PokeIcon_AllocFramebuffers)
    /* 0x08 */ char pad8[0x10];
    /* 0x18 */ s32 backgroundBuffer; // PokeIcon_RequestBackgroundLoad's poolPtr
    /* 0x1C */ s32 frameResultSize; // PokeIcon_ApplyLoadResult's case 1: poolSize
    /* 0x20 */ s32 backgroundResultSize; // case 2: poolSize
    /* 0x24 */ S1_unk_D_86002F58_004_000_010_024* lastLoadedFragment; // case 1: result; PokeIcon_RequestFrameLoad reuses the load if this matches the requested species
    /* 0x28 */ s32 backgroundResult; // case 2: result
    /* 0x2C */ S1_arg1_func_80010CA8 colorAdjust; // cached alongside lastLoadedFragment for the reuse check
    /* 0x30 */ OSMesgQueue frameQueue;
    /* 0x48 */ OSMesg frameMsgBuf;
    /* 0x4C */ char pad4C[0x4];
    /* 0x50 */ OSMesgQueue backgroundQueue;
    /* 0x68 */ OSMesg backgroundMsgBuf;
    /* 0x6C */ char pad6C[0x4];
};
struct S1_unk_D_86002F58_004_000_010_024 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ char unk02[0x6];
    /* 0x08 */ struct S1_unk_D_86002F58_004_000_004* unk_08;
};
struct S1_unk_D_86002F58_004_000_00C_028 {
    /* 0x00 */ char pad0[4];
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char pad6[6];
    /* 0x0C */ s32* unk_0C;
    /* 0x10 */ s32* unk_10;
};
typedef struct S1_unk_D_86002F34_alt19 S1_unk_D_86002F34_alt19;
struct S1_unk_D_86002F34_alt19 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ u8 r;
    /* 0x19 */ u8 g;
    /* 0x1A */ u8 b;
};
typedef struct S1_unk_D_86002F34_alt12 S1_unk_D_86002F34_alt12;
struct S1_unk_D_86002F34_alt12 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
};
typedef struct S1_unk_D_86002F34_alt20 S1_unk_D_86002F34_alt20;
struct S1_unk_D_86002F34_alt20 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
};
typedef struct S1_unk_D_86002F34_alt21 S1_unk_D_86002F34_alt21;
struct S1_unk_D_86002F34_alt21 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
};
typedef struct S1_unk_D_86002F34_alt5 S1_unk_D_86002F34_alt5;
struct S1_unk_D_86002F34_alt5 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ S1_Vec3f unk_18;
    /* 0x24 */ S1_Vec3s unk_24;
};
typedef struct S1_unk_D_86002F34_alt22 S1_unk_D_86002F34_alt22;
struct S1_unk_D_86002F34_alt22 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ S1_Vec3f unk_18;
};
typedef struct S1_unk_D_86002F34_alt6 S1_unk_D_86002F34_alt6;
struct S1_unk_D_86002F34_alt6 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ S1_Vec3s unk_18;
    /* 0x1E */ S1_Vec3s unk_1E;
    /* 0x24 */ S1_Vec3f unk_24;
    /* 0x30 */ u8 unk_30;
    /* 0x31 */ u8 unk_31;
    /* 0x32 */ s16 unk_32;
};
typedef struct S1_unk_D_86002F34_alt7 S1_unk_D_86002F34_alt7;
struct S1_unk_D_86002F34_alt7 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ s16 unk_1C;
};
typedef struct S1_unk_D_86002F34_alt8 S1_unk_D_86002F34_alt8;
struct S1_unk_D_86002F34_alt8 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ S1_MtxF unk_1C;
};
typedef struct S1_unk_D_86002F34_alt9 S1_unk_D_86002F34_alt9;
struct S1_unk_D_86002F34_alt9 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ S1_Vec3f unk_1C;
    /* 0x28 */ f32 unk_28;
};
typedef struct S1_unk_func_80011B94 S1_unk_func_80011B94;
struct S1_unk_func_80011B94 {
    /* 0x00 */ S1_unk_D_86002F58_004_000_000 unk_00;
    /* 0x18 */ Gfx* displayList; // GeoNode_CreateDisplayList's arg3
};
typedef struct S1_unk_D_86002F34_alt10 S1_unk_D_86002F34_alt10;
struct S1_unk_D_86002F34_alt10 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ u8 unk_22;
    /* 0x24 */ S1_Color_RGBA8_u32 unk_24;
};
typedef struct S1_unk_D_86002F34_alt23 S1_unk_D_86002F34_alt23;
struct S1_unk_D_86002F34_alt23 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
};
typedef struct S1_unk_D_86002F34_alt24 S1_unk_D_86002F34_alt24;
struct S1_unk_D_86002F34_alt24 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ S1_Color_RGBA8_u32 unk_28;
};
extern Gfx* D_800D0510;
extern Mtx D_80094890;
typedef struct S1_unk_D_86002F34_alt3 S1_unk_D_86002F34_alt3;
struct S1_unk_D_86002F34_alt3 {
    /* 0x00 */ S1_GraphNode unk_00;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s32 unk_1C;
};
typedef struct S1_unk_D_800ABCC0_008 S1_unk_D_800ABCC0_008;
typedef struct S1_unk_D_800ABCC0 S1_unk_D_800ABCC0;
typedef struct S1_unk_D_86002F58_004_000_040_004 S1_unk_D_86002F58_004_000_040_004;
struct S1_unk_D_800ABCC0_008 {
    /* 0x00 */ u8 translationKeyCount; // ModelAnim_EvaluateTranslationChannel: ==1 means a static (non-animated) value
    /* 0x01 */ u8 rotationKeyCount;
    /* 0x02 */ u8 scaleKeyCount;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u16 translationBaseIndex; // index into the context's translation value array
    /* 0x06 */ u16 rotationBaseIndex; // packed-bits index into the context's rotation value array
    /* 0x08 */ u16 scaleBaseIndex; // packed-bits index into the context's scale value array
};
struct S1_unk_D_800ABCC0 {
    /* 0x00 */ u8 isActive; // ModelAnim_BeginCurveContext: 1 when curveData != NULL, else 0
    /* 0x01 */ u8 flags; // mirrors curveData->unk_00; bit2 selects 16-bit vs 12-bit packed scale format
    /* 0x02 */ s16 currentFrame;
    /* 0x04 */ S1_unk_D_86002F58_004_000_040_004* curveData;
    /* 0x08 */ S1_unk_D_800ABCC0_008* channels; // per-joint-axis channel descriptors, indexed by ModelAnim_EvaluateJointTransform's arg3
    /* 0x0C */ s16* translationValues; // raw keyframe values, scaled by /1000.0f
    /* 0x10 */ s16* rotationValues; // PackedBits_ReadSigned source
    /* 0x14 */ s16* scaleValues; // PackedBits_ReadSigned source
};
struct S1_unk_D_86002F58_004_000_040_004 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ u32 unk_14;
    /* 0x18 */ u32 unk_18;
};
typedef struct S1_unk_func_80016B30_arg0 S1_unk_func_80016B30_arg0;
struct S1_unk_func_80016B30_arg0 {
    /* 0x00 */ S1_Vec3s vec;
    /* 0x06 */ s16 unk_06;
};
typedef struct S1_unk_D_86002F58_004_000_040_raw S1_unk_D_86002F58_004_000_040_raw;
typedef union S1_unk_D_86002F58_004_000_040_raw_08 S1_unk_D_86002F58_004_000_040_raw_08;
union S1_unk_D_86002F58_004_000_040_raw_08 {
    struct {
        s16 unk_00;
        s16 unk_02;
    };
    s32 raw;
};
struct S1_unk_D_86002F58_004_000_040_raw {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ S1_unk_D_86002F58_004_000_040_004* unk_04;
    /* 0x08 */ S1_unk_D_86002F58_004_000_040_raw_08 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk10[0x2];
    /* 0x12 */ u16 unk_12;
};
typedef struct S1_unk_D_86002F58_004_000_040 S1_unk_D_86002F58_004_000_040;
typedef struct S1_unk_D_86002F58_004_000 S1_unk_D_86002F58_004_000;
typedef struct S1_unk_D_86002F58_004_000_054 S1_unk_D_86002F58_004_000_054;
typedef struct S1_unk_D_86002F58_004_000_0A8 S1_unk_D_86002F58_004_000_0A8;
typedef struct S1_unk_D_86002F58_004_000_054_004 S1_unk_D_86002F58_004_000_054_004;
struct S1_unk_D_86002F58_004_000_040 {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ S1_unk_D_86002F58_004_000_040_004* unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ char unk10[0x2];
    /* 0x12 */ u16 unk_12;
};
struct S1_unk_D_86002F58_004_000_054 {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ S1_unk_D_86002F58_004_000_054_004* unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ u16 unk_0A;
};
struct S1_unk_D_86002F58_004_000_0A8 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ S1_Vec3f unk_04;
};
struct S1_unk_D_86002F58_004_000 {
    /* 0x000 */ S1_unk_D_86002F58_004_000_000 unk_000;
    /* 0x018 */ s16 animType; // Model_InitDisplayObject's arg1
    /* 0x01A */ s16 modelId; // Model_InitDisplayObject's arg2; a species id in most battle-scene consumers
    /* 0x01C */ u8 textureMode; // Model_SetMaterialTextureMode
    /* 0x01D */ u8 materialAlpha; // Model_SetMaterialAlpha
    /* 0x01E */ S1_Vec3s unk_01E;			//	total Rotation
    /* 0x024 */ S1_Vec3f unk_024;			//	global Position
    /* 0x030 */ S1_Vec3f unk_030;			//	scale
    /* 0x03C */ S1_Color_RGBA8_u32 unk_03C;
    /* 0x040 */ S1_unk_D_86002F58_004_000_040 unk_040;
    /* 0x054 */ S1_unk_D_86002F58_004_000_054 unk_054;
    /* 0x060 */ S1_MtxF unk_060;
    /* 0x0A0 */ S1_Color_RGBA8_u32 unk_0A0;    //  vertex color ?
    /* 0x0A4 */ char unk0A4[2];
    /* 0x0A6 */ u8 poolIndex; // stable index into the shared displayObjectPool; GeoRender_RecordAnchorPosition/etc.
    /* 0x0A7 */ u8 anchorCount; // GeoRender_RecordAnchorPosition/FindAnchorPosition; caps at 0xC (12)
    /* 0x0A8 */ S1_unk_D_86002F58_004_000_0A8 anchors[1]; // declared size undersells - indexed up to anchorCount (max 12)
    /* 0x0B8 */ char unk0B8[0x24];
    /* 0x0DC */ S1_Vec3f unk_0DC;
    /* 0x0E0 */ char unk0E0[0x4];
    /* 0x0EC */ S1_Vec3f unk_0EC;
    /* 0x0F8 */ char unk0F8[0x4];
    /* 0x0FC */ S1_Vec3f unk_0FC;
    /* 0x108 */ char unk108[0x60];
};
struct S1_unk_D_86002F58_004_000_054_004 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk_02[0x2];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ void* unk_0C;
    /* 0x10 */ void* unk_10;
};
typedef unsigned int S1_uintptr_t;
typedef struct S1_unk_D_800ABE00_cmd8 S1_unk_D_800ABE00_cmd8;
typedef struct S1_unk_D_86002F34_000_014 S1_unk_D_86002F34_000_014;
struct S1_unk_D_800ABE00_cmd8 {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ S1_func_D_86002F34_000_010 callback; // func_80037E3C's arg1
    /* 0x08 */ S1_unk_D_86002F34_000_014* callbackData; // func_80037E3C's arg2
};
struct S1_unk_D_86002F34_000_014 {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ u8* unk_04;
};
typedef struct S1_unk_D_800ABE00_cmd9 S1_unk_D_800ABE00_cmd9;
struct S1_unk_D_800ABE00_cmd9 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
};
typedef struct S1_unk_D_800ABE00_cmdA S1_unk_D_800ABE00_cmdA;
struct S1_unk_D_800ABE00_cmdA {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ S1_GraphNode* refNode; // GeoNode_CreateWithReference's arg1
};
typedef struct S1_unk_D_800ABE00_cmdB S1_unk_D_800ABE00_cmdB;
struct S1_unk_D_800ABE00_cmdB {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ u16 fovy;
    /* 0x04 */ u16 viewportX;
    /* 0x06 */ u16 viewportY;
    /* 0x08 */ s16 viewportWidth;
    /* 0x0A */ s16 viewportHeight;
    /* 0x0C */ S1_Vec3s lookAt;
    /* 0x12 */ s16 yaw;
    /* 0x14 */ s16 pitch;
    /* 0x16 */ s16 eyeDistance;
};
typedef struct S1_unk_D_800ABE00_cmdC S1_unk_D_800ABE00_cmdC;
struct S1_unk_D_800ABE00_cmdC {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 unk_02;
};
typedef struct S1_unk_D_800ABE00_cmdD S1_unk_D_800ABE00_cmdD;
struct S1_unk_D_800ABE00_cmdD {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 unk_02;
};
typedef struct S1_unk_D_800ABE00_cmdE S1_unk_D_800ABE00_cmdE;
struct S1_unk_D_800ABE00_cmdE {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 unk_02;
};
typedef struct S1_unk_D_800ABE00_cmdF S1_unk_D_800ABE00_cmdF;
struct S1_unk_D_800ABE00_cmdF {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 unk_02;
};
typedef struct S1_unk_D_800ABE00_cmd10 S1_unk_D_800ABE00_cmd10;
struct S1_unk_D_800ABE00_cmd10 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 r;
    /* 0x02 */ u8 g;
    /* 0x03 */ u8 b;
};
typedef struct S1_unk_D_800ABE00_cmd13 S1_unk_D_800ABE00_cmd13;
struct S1_unk_D_800ABE00_cmd13 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 r;
    /* 0x02 */ u8 g;
    /* 0x03 */ u8 b;
    /* 0x04 */ s16 fogNear;
    /* 0x06 */ s16 fogFar;
};
typedef struct S1_unk_D_800ABE00_cmd14 S1_unk_D_800ABE00_cmd14;
struct S1_unk_D_800ABE00_cmd14 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ s16 pitch; // func_800382E4's arg2, scaled (val<<0xF)/180
    /* 0x06 */ s16 yaw; // func_800382E4's arg3, scaled (val<<0xF)/180
    /* 0x08 */ u8 r;
    /* 0x09 */ u8 g;
    /* 0x0A */ u8 b;
    /* 0x0B */ u8 a;
};
typedef struct S1_unk_D_800ABE00_cmd18 S1_unk_D_800ABE00_cmd18;
struct S1_unk_D_800ABE00_cmd18 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
};
typedef struct S1_unk_D_800ABE00_cmd19 S1_unk_D_800ABE00_cmd19;
struct S1_unk_D_800ABE00_cmd19 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ s16 nearDistance; // Geo_NodeCullDistance: children render only when nearDistance <= depth < farDistance
    /* 0x06 */ s16 farDistance;
};
typedef struct S1_unk_D_800ABE00_cmd1A S1_unk_D_800ABE00_cmd1A;
struct S1_unk_D_800ABE00_cmd1A {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 caseIndex; // Geo_NodeSwitchCase: walks this many siblings from the first child before dispatching
};
typedef struct S1_unk_D_800ABE00_cmd1B S1_unk_D_800ABE00_cmd1B;
struct S1_unk_D_800ABE00_cmd1B {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ s16 rotX; // degrees, scaled (val<<0xF)/180
    /* 0x06 */ s16 rotY;
    /* 0x08 */ s16 rotZ;
    /* 0x0A */ S1_Vec3s translation;
};
typedef struct S1_unk_D_800ABE00_cmd1C S1_unk_D_800ABE00_cmd1C;
struct S1_unk_D_800ABE00_cmd1C {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ u32 translateX; // Q16 fixed point, /65536.0f
    /* 0x08 */ u32 translateY;
    /* 0x0C */ u32 translateZ;
};
typedef struct S1_unk_D_800ABE00_cmd1D S1_unk_D_800ABE00_cmd1D;
struct S1_unk_D_800ABE00_cmd1D {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 partIndex; // GeoNode_CreateAnimatedPart's arg2
    /* 0x02 */ u8 flags; // bit0/bit1 remapped into GeoNode_CreateAnimatedPart's arg3
    /* 0x03 */ u8 animIndex; // GeoNode_CreateAnimatedPart's arg4
    /* 0x04 */ S1_Vec3s rotationA; // GeoNode_CreateAnimatedPart's arg5
    /* 0x0A */ S1_Vec3s rotationB; // GeoNode_CreateAnimatedPart's arg6
    /* 0x10 */ u32 translateX; // Q16 fixed point, /65536.0f
    /* 0x14 */ u32 translateY;
    /* 0x18 */ u32 translateZ;
};
typedef struct S1_unk_D_800ABE00_cmd1E S1_unk_D_800ABE00_cmd1E;
struct S1_unk_D_800ABE00_cmd1E {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 partIndex; // GeoNode_CreateDisplayListPart's arg2
    /* 0x02 */ s16 unk_02; // GeoNode_CreateDisplayListPart's arg4
    /* 0x04 */ Gfx* displayList;
};
typedef struct S1_unk_D_800ABE00_cmd1F S1_unk_D_800ABE00_cmd1F;
struct S1_unk_D_800ABE00_cmd1F {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 modelIndex; // func_80038894's arg2
    /* 0x04 */ s16 rotX; // degrees, scaled (val<<0xF)/180
    /* 0x06 */ s16 rotY;
    /* 0x08 */ s16 rotZ;
    /* 0x0A */ S1_Vec3s position;
    /* 0x10 */ s16 scaleX; // /100.0f
    /* 0x12 */ s16 scaleY;
    /* 0x14 */ s16 scaleZ;
    /* 0x16 */ char pad[0x2];
};
typedef struct S1_unk_D_800ABE00_cmd20 S1_unk_D_800ABE00_cmd20;
struct S1_unk_D_800ABE00_cmd20 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 partIndex; // GeoNode_CreateDisplayListMatrixFromTransform's arg2
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 rotX; // degrees, scaled (val<<0xF)/180
    /* 0x06 */ s16 rotY;
    /* 0x08 */ s16 rotZ;
    /* 0x0A */ S1_Vec3s position;
    /* 0x10 */ Gfx* displayList;
};
typedef struct S1_unk_D_800ABE00_cmd21 S1_unk_D_800ABE00_cmd21;
struct S1_unk_D_800ABE00_cmd21 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 partIndex; // GeoNode_CreateScale's arg2
    /* 0x02 */ S1_Vec3s position;
    /* 0x08 */ u32 scale; // Q16 fixed point, /65536.0f
    /* 0x0C */ Gfx* displayList;
};
typedef struct S1_unk_D_800ABE00_cmd22 S1_unk_D_800ABE00_cmd22;
struct S1_unk_D_800ABE00_cmd22 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 partIndex; // GeoNode_CreateDisplayList's arg2
    /* 0x04 */ Gfx* displayList;
};
typedef struct S1_unk_D_800ABE00_cmd23 S1_unk_D_800ABE00_cmd23;
struct S1_unk_D_800ABE00_cmd23 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 colorOverrideFlag; // Geo_NodeShadowTexture: ==1 forces the shadow color to opaque white
    /* 0x02 */ s16 eventFrame; // ModelAnim_GetEventAtFrame's frame arg
    /* 0x04 */ Gfx* displayList;
    /* 0x07 */ s16 textureIndex1; // indexes D_8006F0A0's first texture array when >= 0
    /* 0x0A */ s16 textureIndex2; // indexes D_8006F0A0's second texture array when >= 0
    /* 0x0C */ u8 r;
    /* 0x0D */ u8 g;
    /* 0x0E */ u8 b;
    /* 0x0F */ u8 a;
};
typedef struct S1_unk_D_800ABE00_cmd24 S1_unk_D_800ABE00_cmd24;
struct S1_unk_D_800ABE00_cmd24 {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 anchorId; // GeoNode_CreateAnchor's arg2
};
typedef struct S1_unk_D_800ABE00_cmd26 S1_unk_D_800ABE00_cmd26;
struct S1_unk_D_800ABE00_cmd26 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 r;
    /* 0x11 */ u8 g;
    /* 0x12 */ u8 b;
    /* 0x13 */ u8 a;
};
typedef struct S1_arg1_func_80019420 S1_arg1_func_80019420;
struct S1_arg1_func_80019420 {
    /* 0x00 */ s8 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ void* unk_04;
};
void MtxF_Multiply(S1_MtxF* arg0, S1_MtxF* arg1, S1_MtxF* arg2) {
    f32 entry0;
    f32 entry1;
    f32 entry2;

    entry0 = arg1->mf[0][0];
    entry1 = arg1->mf[0][1];
    entry2 = arg1->mf[0][2];

    arg0->mf[0][0] = (entry0 * arg2->mf[0][0]) + (entry1 * arg2->mf[1][0]) + (entry2 * arg2->mf[2][0]);
    arg0->mf[0][1] = (entry0 * arg2->mf[0][1]) + (entry1 * arg2->mf[1][1]) + (entry2 * arg2->mf[2][1]);
    arg0->mf[0][2] = (entry0 * arg2->mf[0][2]) + (entry1 * arg2->mf[1][2]) + (entry2 * arg2->mf[2][2]);

    entry0 = arg1->mf[1][0];
    entry1 = arg1->mf[1][1];
    entry2 = arg1->mf[1][2];

    arg0->mf[1][0] = (entry0 * arg2->mf[0][0]) + (entry1 * arg2->mf[1][0]) + (entry2 * arg2->mf[2][0]);
    arg0->mf[1][1] = (entry0 * arg2->mf[0][1]) + (entry1 * arg2->mf[1][1]) + (entry2 * arg2->mf[2][1]);
    arg0->mf[1][2] = (entry0 * arg2->mf[0][2]) + (entry1 * arg2->mf[1][2]) + (entry2 * arg2->mf[2][2]);

    entry0 = arg1->mf[2][0];
    entry1 = arg1->mf[2][1];
    entry2 = arg1->mf[2][2];

    arg0->mf[2][0] = (entry0 * arg2->mf[0][0]) + (entry1 * arg2->mf[1][0]) + (entry2 * arg2->mf[2][0]);
    arg0->mf[2][1] = (entry0 * arg2->mf[0][1]) + (entry1 * arg2->mf[1][1]) + (entry2 * arg2->mf[2][1]);
    arg0->mf[2][2] = (entry0 * arg2->mf[0][2]) + (entry1 * arg2->mf[1][2]) + (entry2 * arg2->mf[2][2]);

    entry0 = arg1->mf[3][0];
    entry1 = arg1->mf[3][1];
    entry2 = arg1->mf[3][2];

    arg0->mf[3][0] = (entry0 * arg2->mf[0][0]) + (entry1 * arg2->mf[1][0]) + (entry2 * arg2->mf[2][0]) + arg2->mf[3][0];
    arg0->mf[3][1] = (entry0 * arg2->mf[0][1]) + (entry1 * arg2->mf[1][1]) + (entry2 * arg2->mf[2][1]) + arg2->mf[3][1];
    arg0->mf[3][2] = (entry0 * arg2->mf[0][2]) + (entry1 * arg2->mf[1][2]) + (entry2 * arg2->mf[2][2]) + arg2->mf[3][2];

    arg0->mf[0][3] = arg0->mf[1][3] = arg0->mf[2][3] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}
#endif

#ifdef VERSION_US
void MtxF_ScaleRows(S1_MtxF* dest, S1_MtxF* mtx, S1_Vec3f* s) {
    s32 i;

    for (i = 0; i < 4; i++) {
        dest->mf[0][i] = mtx->mf[0][i] * s->x;
        dest->mf[1][i] = mtx->mf[1][i] * s->y;
        dest->mf[2][i] = mtx->mf[2][i] * s->z;
        dest->mf[3][i] = mtx->mf[3][i];
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80036D8C.s")
#endif

#ifdef VERSION_US
void MtxF_TransformVec3s(S1_MtxF* arg0, S1_Vec3s* arg1) {
    f32 entry0 = arg1->x;
    f32 entry1 = arg1->y;
    f32 entry2 = arg1->z;

    arg1->x = ((entry0 * arg0->mf[0][0]) + (entry1 * arg0->mf[1][0]) + (entry2 * arg0->mf[2][0])) + arg0->mf[3][0];
    arg1->y = ((entry0 * arg0->mf[0][1]) + (entry1 * arg0->mf[1][1]) + (entry2 * arg0->mf[2][1])) + arg0->mf[3][1];
    arg1->z = ((entry0 * arg0->mf[0][2]) + (entry1 * arg0->mf[1][2]) + (entry2 * arg0->mf[2][2])) + arg0->mf[3][2];
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80036F0C.s")
#endif

#ifdef VERSION_US
extern void func_80036714(S1_MtxF *, s32, s32, s32, f32);
extern void func_8003614C(void *, s32, s32);
void MtxF_BuildTransform(S1_MtxF *arg0, s32 arg1, s32 arg2, S1_Vec3f *arg3, s32 arg4, s32 arg5) {
    S1_MtxF sp60;
    S1_MtxF sp20;

    func_80036714(&sp60, arg4, arg5, arg1, 1.0f);
    func_8003614C(&sp20, (s32) &D_800948D0, arg2);
    MtxF_Multiply(&sp20, &sp20, &sp60);
    MtxF_ScaleRows(arg0, &sp20, arg3);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80037120.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800371B4.s")
#endif

#ifdef VERSION_US
s16 Math_StepToS(s16 current, s16 target, s16 inc) {
    s16 temp_v0 = target - current;

    if (temp_v0 < 0) {
        temp_v0 += inc;
        if (temp_v0 > 0) {
            temp_v0 = 0;
        }
    } else {
        temp_v0 -= inc;
        if (temp_v0 < 0) {
            temp_v0 = 0;
        }
    }

    return target - temp_v0;
}
#endif

#ifdef VERSION_US
s32 Math_StepToS32(s32 current, s32 target, s32 inc, s32 dec) {
    if (current < target) {
        current += inc;
        if (current > target) {
            current = target;
        }
    } else {
        current -= dec;
        if (current < target) {
            current = target;
        }
    }
    return current;
}
#endif

#ifdef VERSION_US
f32 Math_StepToF(f32 current, f32 target, f32 inc, f32 dec) {
    if (current < target) {
        current += inc;
        if (current > target) {
            current = target;
        }
    } else {
        current -= dec;
        if (current < target) {
            current = target;
        }
    }
    return current;
}
#endif

#ifdef VERSION_US
s16 func_80037360(s16* arg0, s32 arg1, s32 arg2) {
    S1_Vec2s_s32 spC;
    s16* temp_a3 = &arg0[(arg1 * arg2) / 16];
    s16* p_spC = &spC.x;

    p_spC[0] = temp_a3[0];
    p_spC[1] = temp_a3[1];

    spC.xy <<= ((arg1 * arg2) % 16);
    spC.xy >>= -arg2;
    return spC.y;
}
#endif

#ifdef VERSION_US
void Color_RGBToHSV(f32 arg0, f32 arg1, f32 arg2, S1_Vec3f* arg3) {
    f32 temp_ft4;
    f32 var_ft5;
    f32 var_fv0;
    f32 var_fv1;
    s32 var_v0;

    var_v0 = 0x47;
    if (arg1 <= arg0) {
        var_fv0 = arg0;
        var_v0 = 0x52;
    } else {
        var_fv0 = arg1;
    }

    if (var_fv0 < arg2) {
        var_fv0 = arg2;
        var_v0 = 0x42;
    }

    if (arg0 <= arg1) {
        var_fv1 = arg0;
    } else {
        var_fv1 = arg1;
    }

    if (arg2 < var_fv1) {
        var_fv1 = arg2;
    }

    temp_ft4 = var_fv0 + var_fv1;
    arg3->z = temp_ft4 - 1.0f;
    if (var_fv0 == var_fv1) {
        arg3->y = 0.0f;
        arg3->x = 0.0f;
        return;
    }

    if (arg3->z <= 0.0f) {
        var_ft5 = var_fv0 - var_fv1;
        arg3->y = var_ft5 / temp_ft4;
    } else {
        var_ft5 = var_fv0 - var_fv1;
        arg3->y = var_ft5 / (2.0 - temp_ft4);
    }

    if (var_v0 == 0x52) {
        arg3->x = (arg1 - arg2) / var_ft5;
    } else if (var_v0 == 0x47) {
        arg3->x = ((arg2 - arg0) / var_ft5) + 2.0;
    } else {
        arg3->x = ((arg0 - arg1) / var_ft5) + 4.0;
    }

    arg3->x *= 60.0f;
    if (arg3->x < 0.0f) {
        arg3->x += 360.0f;
    }
}
#endif

#ifdef VERSION_US
void Color_RGBA8ToHSV(S1_Color_RGBA8_u32 arg0, S1_Vec3f* arg1) {
    Color_RGBToHSV((s32)arg0.r / 255.0f, (s32)arg0.g / 255.0f, (s32)arg0.b / 255.0f, arg1);
}
#endif

#ifdef VERSION_US
void Color_RGB5551ToHSV(u16 arg0, S1_Vec3f* arg1) {
    Color_RGBToHSV(((arg0 & 0xF800) >> 0xB) / 31.0f, ((arg0 & 0x7C0) >> 6) / 31.0f, ((arg0 & 0x3E) >> 1) / 31.0f, arg1);
}
#endif

#ifdef VERSION_US
f32 Color_HSVInterpolate(f32 arg0, f32 arg1, f32 arg2) {
    f32 ret;

    if (arg0 < 0.0f) {
        arg0 += 360.0f;
    } else {
        while (arg0 >= 360.0f) {
            arg0 -= 360.0f;
        }
    }

    if (arg0 < 60.0f) {
        ret = (((arg2 - arg1) * arg0) / 60.0f) + arg1;
    } else if ((arg0 >= 60.0f) && (arg0 < 180.0f)) {
        ret = arg2;
    } else if ((arg0 >= 180.0f) && (arg0 < 240.0f)) {
        ret = arg1 + (((arg2 - arg1) * (240.0 - arg0)) / 60.0);
    } else {
        ret = arg1;
    }

    return ret;
}
#endif

#ifdef VERSION_US
void Color_HSVToRGB(f32* arg0, f32* arg1, f32* arg2, S1_Vec3f* arg3) {
    f32 sp24;
    f32 sp20;
    f32 temp_ft4;

    if (arg3->z < -1.0f) {
        arg3->z = -1.0f;
    } else if (arg3->z > 1.0f) {
        arg3->z = 1.0f;
    }

    if (arg3->y < 0.0f) {
        arg3->y = 0.0f;
    } else {
        sp24 = 1.0f;
        if (arg3->y > 1.0f) {
            arg3->y = 1.0f;
        }
    }

    if (arg3->x < 0.0f) {
        arg3->x += 360.0f;
    } else {
        while (arg3->x >= 360.0f) {
            arg3->x -= 360.0f;
        }
    }

    if (arg3->z <= 0.0f) {
        temp_ft4 = arg3->z + 1.0f;
        sp24 = temp_ft4 * 0.5f * (1.0f - arg3->y);
        sp20 = temp_ft4 - sp24;
    } else {
        temp_ft4 = arg3->z + 1.0f;
        sp20 = (temp_ft4 * 0.5 * (1.0f - arg3->y)) + arg3->y;
        sp24 = temp_ft4 - sp20;
    }

    *arg0 = Color_HSVInterpolate(arg3->x + 120.0f, sp24, sp20);
    *arg1 = Color_HSVInterpolate(arg3->x, sp24, sp20);
    *arg2 = Color_HSVInterpolate(arg3->x - 120.0f, sp24, sp20);
}
#endif

#ifdef VERSION_US
u16 Color_HSVToRGB5551(S1_Vec3f* arg0) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;

    Color_HSVToRGB(&sp2C, &sp28, &sp24, arg0);

    var_a1 = (sp2C * 31.0f) + 0.5f;
    if (var_a1 >= 0x20) {
        var_a1 = 0x1F;
    }

    var_v1 = (sp28 * 31.0f) + 0.5f;
    if (var_v1 >= 0x20) {
        var_v1 = 0x1F;
    }

    var_a0 = (sp24 * 31.0f) + 0.5f;
    if (var_a0 >= 0x20) {
        var_a0 = 0x1F;
    }

    return (var_a1 << 0xB) | (var_v1 << 6) | (var_a0 * 2) | 1;
}
#endif

#ifdef VERSION_US
S1_Color_RGBA8_u32* Color_HSVToRGBA8(S1_Color_RGBA8_u32* arg0, S1_Vec3f* arg1, s32 arg2) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;
    S1_Color_RGBA8_u32 sp1C;

    Color_HSVToRGB(&sp34, &sp30, &sp2C, arg1);

    var_a1 = (sp34 * 255.0f) + 0.5f;
    if (var_a1 >= 0x100) {
        var_a1 = 0xFF;
    }

    var_v1 = (sp30 * 255.0f) + 0.5f;
    if (var_v1 >= 0x100) {
        var_v1 = 0xFF;
    }

    var_a0 = (sp2C * 255.0f) + 0.5f;
    if (var_a0 >= 0x100) {
        var_a0 = 0xFF;
    }

    sp1C.r = var_a1;
    sp1C.g = var_v1;
    sp1C.b = var_a0;
    sp1C.a = arg2;

    *arg0 = sp1C;

    return arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80037B08.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80037C80.s")
#endif

#ifdef VERSION_US
void GeoNode_Init(S1_GraphNode* arg0, u8 arg1) {
    if (arg0 != NULL) {
        arg0->unk_00 = arg1;
        arg0->unk_01 = 0x11;
        arg0->unk_02 = 0;
        arg0->unk_03 = 0;
        arg0->unk_04 = arg0;
        arg0->unk_08 = arg0;
        arg0->unk_0C = NULL;
        arg0->unk_10 = NULL;
        arg0->unk_14 = NULL;
    }
}
#endif

#ifdef VERSION_US
void func_80037E3C(S1_GraphNode* arg0, S1_func_D_86002F34_000_010 arg1, void* arg2) {
    if (arg1 != NULL) {
        arg1 = func_80003240(arg1);
    }

    if (arg0 != NULL) {
        arg0->unk_14 = arg2;
        arg0->unk_10 = arg1;
        if (arg1 != NULL) {
            arg1(0, arg0);
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80037E9C.s")
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt2* GeoNode_CreateWithReference(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt2* arg1, S1_GraphNode* arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt2), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        GeoNode_Init(arg1, 1);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80037F40.s")
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt13* GeoNode_CreateType3(S1_MemoryBlock* arg0, S1_unk_D_86002F34_alt13* arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt13), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        GeoNode_Init(arg1, 3);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt1* GeoNode_CreateType4(S1_MemoryBlock* arg0, S1_unk_D_86002F34_alt1* arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt1), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        arg1->unk_1A = 0;
        GeoNode_Init(arg1, 4);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800380B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003811C.s")
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt16* GeoNode_CreateBackground(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt16* arg1, u8 arg2, u8 arg3, u8 arg4) {
    u32 temp_v0;

    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt16), 4);
    }

    if (arg1 != NULL) {
        temp_v0 = ((arg2 >> 3) << 0xB) | ((arg3 >> 3) << 6) | ((arg4 >> 3) << 1) | 1;
        arg1->unk_18 = (temp_v0 << 0x10) | temp_v0;
        GeoNode_Init(arg1, 7);
    }
    return arg1;
}
#endif

#ifdef VERSION_US
s32 func_8003820C(s32 arg0, s32 arg1) {
    s32 var_a2;

    var_a2 = arg1;
    if (arg0 != 0) {
        var_a2 = (s32)(u32)MainPool_AllocAligned((void *)(u32)arg0, 0x18, 4);
    }
    if (var_a2 != 0) {
        arg1 = var_a2;
        GeoNode_Init((S1_GraphNode *) var_a2, 8U);
        var_a2 = arg1;
    }
    return var_a2;
}
#endif

#ifdef VERSION_US
S1_unk_D_8690A610* GeoNode_CreateFog(s32 arg0, S1_unk_D_8690A610* arg1, s16 arg2, s16 arg3, u8 r, u8 g, u8 b, u8 a) {
    if (arg0 != 0) {
        arg1 = MainPool_AllocAligned((void *)(u32)arg0, sizeof(S1_unk_D_8690A610), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18.fogNear = arg2;
        arg1->unk_18.fogFar = arg3;
        arg1->unk_18.fogColor.rgba = (r << 0x18) | (g << 0x10) | (b << 8) | a;
        GeoNode_Init(arg1, 0xA);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800382E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80038390.s")
#endif

#ifdef VERSION_US
void func_800383DC(void *arg0, s16 arg1, s16 arg2) {
    if (arg0 != NULL) {
        (*(s16 *)((u8 *)(arg0) + (0x1C))) = arg1;
        (*(s16 *)((u8 *)(arg0) + (0x1E))) = arg2;
        (*(s8 *)((u8 *)(arg0) + (0x2B))) = 0;
    }
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt19* GeoNode_CreateAmbientLight(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt19* arg1, u8 r, u8 g, u8 b) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt19), 4);
    }

    if (arg1 != NULL) {
        arg1->r = r;
        arg1->g = g;
        arg1->b = b;
        GeoNode_Init(arg1, 0xD);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
s32 func_80038474(s32 arg0, s32 arg1) {
    s32 var_a2;

    var_a2 = arg1;
    if (arg0 != 0) {
        var_a2 = (s32)(u32)MainPool_AllocAligned((void *)(u32)arg0, 0x18, 4);
    }
    if (var_a2 != 0) {
        arg1 = var_a2;
        GeoNode_Init((S1_GraphNode *) var_a2, 0x1DU);
        var_a2 = arg1;
    }
    return var_a2;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800384C0.s")
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt12* GeoNode_CreateShadow(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt12* arg1, s16 arg2, s16 arg3, s16 arg4,
                                    s16 arg5) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt12), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        arg1->unk_1A = arg3;
        arg1->unk_1C = arg4;
        arg1->unk_1E = arg5;
        GeoNode_Init(arg1, 0xF);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt20* GeoNode_CreateCullDistance(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt20* arg1, s16 arg2, s16 arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt20), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        arg1->unk_1A = arg3;
        GeoNode_Init(arg1, 0x10);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt21* GeoNode_CreateSwitchCase(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt21* arg1, s16 arg2, s16 arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt21), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        arg1->unk_1A = arg3;
        GeoNode_Init(arg1, 0x11);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt5* GeoNode_CreateTranslateRotate(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt5* arg1, S1_Vec3f* arg2, S1_Vec3s* arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt5), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = *arg2;
        arg1->unk_24 = *arg3;
        GeoNode_Init(arg1, 0x12);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt22* GeoNode_CreateTranslate(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt22* arg1, S1_Vec3f* arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt22), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = *arg2;
        GeoNode_Init(arg1, 0x13);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt6* GeoNode_CreateAnimatedPart(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt6* arg1, s16 arg2, s16 arg3, s16 arg4,
                                   S1_Vec3s* arg5, S1_Vec3s* arg6, S1_Vec3f* arg7) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt6), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = *arg5;
        arg1->unk_1E = *arg6;
        arg1->unk_24 = *arg7;
        arg1->unk_30 = arg2;
        arg1->unk_31 = arg3;
        arg1->unk_32 = arg4;
        GeoNode_Init(arg1, 0x14);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt7* GeoNode_CreateDisplayListPart(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt7* arg1, s32 arg2, Gfx* arg3, s16 arg4) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt7), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg3;
        arg1->unk_1C = arg4;
        GeoNode_Init(arg1, 0x15);
        arg1->unk_00.unk_03 = arg2;
    }

    return arg1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80038894.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003899C.s")
#endif

#ifdef VERSION_US
extern void func_8003899C(s32, s32, s32, s32, void *);
void GeoNode_CreateDisplayListMatrixFromTransform(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp[16];
    func_8003614C(temp, arg4, arg5);
    func_8003899C(arg0, arg1, arg2, arg3, temp);
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt9* GeoNode_CreateScale(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt9* arg1, s32 arg2, Gfx* arg3, S1_Vec3f* arg4,
                                   f32 arg5) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt9), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_1C = *arg4;
        arg1->unk_28 = arg5;
        arg1->unk_18 = arg3;
        GeoNode_Init(arg1, 0x18);
        arg1->unk_00.unk_03 = arg2;
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_func_80011B94* GeoNode_CreateDisplayList(S1_MainPoolState* arg0, S1_unk_func_80011B94* arg1, s32 arg2, Gfx* arg3) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_func_80011B94), 4);
    }

    if (arg1 != NULL) {
        arg1->displayList = arg3;
        GeoNode_Init(arg1, 0x19);
        arg1->unk_00.unk_03 = arg2;
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt10* GeoNode_CreateShadowTexture(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt10* arg1, s16 arg2, s16 arg3, Gfx* arg4,
                                    s16 arg5, s16 arg6, u8 r, u8 g, u8 b, u8 a) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt10), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_22 = arg2;
        arg1->unk_20 = arg3;
        arg1->unk_18 = arg4;
        arg1->unk_1C = arg5;
        arg1->unk_1E = arg6;
        arg1->unk_24.rgba = (r << 0x18) | (g << 0x10) | (b << 8) | a;
        GeoNode_Init(arg1, 0x1A);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt23* GeoNode_CreateAnchor(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt23* arg1, s16 arg2) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt23), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_18 = arg2;
        GeoNode_Init(arg1, 0x1B);
    }

    return arg1;
}
#endif

#ifdef VERSION_US
S1_unk_D_86002F34_alt24* GeoNode_CreateGroup(S1_MainPoolState* arg0, S1_unk_D_86002F34_alt24* arg1, s32 arg2, s16 arg3, s16 arg4,
                                    s16 arg5, s16 arg6, s16 arg7, s16 arg8, s32 arg9, u8 r, u8 g, u8 b, u8 a) {
    if (arg0 != NULL) {
        arg1 = MainPool_AllocAligned(arg0, sizeof(S1_unk_D_86002F34_alt24), 4);
    }

    if (arg1 != NULL) {
        arg1->unk_1C = arg3;
        arg1->unk_1E = arg4;
        arg1->unk_20 = arg5;
        arg1->unk_22 = arg6;
        arg1->unk_18 = arg7;
        arg1->unk_1A = arg8;
        arg1->unk_24 = arg9;
        arg1->unk_28.rgba = (r << 0x18) | (g << 0x10) | (b << 8) | a;
        GeoNode_Init(arg1, 0x1C);
        arg1->unk_00.unk_03 = arg2;
    }

    return arg1;
}
#endif

#ifdef VERSION_US
void GeoCamera_SetViewport(S1_unk_D_86002F34_00C* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    arg0->unk_18.x = arg1;
    arg0->unk_18.y = arg2;
    arg0->unk_18.width = arg3;
    arg0->unk_18.height = arg4;

    arg0->unk_40.l = -arg3 * 0.5f;
    arg0->unk_40.r = arg3 * 0.5f;
    arg0->unk_40.t = arg4 * 0.5f;
    arg0->unk_40.b = -arg4 * 0.5f;
    arg0->unk_40.n = -2.0f;
    arg0->unk_40.f = 2.0f;
    arg0->unk_40.scale = 1.0f;
}
#endif

#ifdef VERSION_US
void GeoCamera_SetPerspective(S1_unk_D_86002F34_00C* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_24.aspect = (f32)arg0->unk_18.width / arg0->unk_18.height;
    arg0->unk_24.fovy = arg1;
    arg0->unk_24.near = arg2;
    arg0->unk_24.far = arg3;
    arg0->unk_24.scale = 1.0f;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80038E14.s")
#endif

#ifdef VERSION_US
void GeoCamera_SetBackground(S1_unk_D_86002F34_00C* arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    S1_unk_D_86002F34_00C_0CC* ptr = &arg0->unk_CC;

    if (arg2 < 2) {
        if ((arg1 == 2) || (arg1 == 4)) {
            ptr->unk_00 = 0;
        } else {
            ptr->unk_00 = 1;
        }
    } else {
        ptr->unk_00 = arg1;
        ptr->unk_08 = arg2;
        ptr->unk_0A = 1;
        ptr->color.r = arg3;
        ptr->color.g = arg4;
        ptr->color.b = arg5;
    }
}
#endif

#ifdef VERSION_US
void func_80038F8C(void *arg0, void *arg1) {
    void *temp_v0;
    void *temp_v1;

    if ((arg0 != NULL) && (arg1 != NULL)) {
        temp_v0 = (*(void **)((u8 *)(arg0) + (0xC)));
        if (temp_v0 == NULL) {
            (*(void **)((u8 *)(arg0) + (0xC))) = arg1;
            (*(void **)((u8 *)(arg1) + (4))) = arg1;
            (*(void **)((u8 *)(arg1) + (8))) = arg1;
            return;
        }
        temp_v1 = (*(void **)((u8 *)(temp_v0) + (4)));
        (*(void **)((u8 *)(arg1) + (8))) = temp_v0;
        (*(void **)((u8 *)(arg1) + (4))) = temp_v1;
        (*(void **)((u8 *)(temp_v0) + (4))) = arg1;
        (*(void **)((u8 *)(temp_v1) + (8))) = arg1;
    }
}
#endif

#ifdef VERSION_US
typedef struct GraphNodeLink {
    char pad0[4];
    struct GraphNodeLink *prev;
    struct GraphNodeLink *next;
} GraphNodeLink;
typedef struct {
    char pad[0xC];
    GraphNodeLink *child;
} GraphNode38FD4;

void GraphNode_RemoveChild(GraphNode38FD4 *root, GraphNodeLink *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    if (node == root->child) {
        if (node == node->next) {
            root->child = NULL;
        } else {
            root->child = node->next;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80039018.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80039070.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800390D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80039158.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80039204.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800392B8.s")
#endif

#ifdef VERSION_US
extern u8 D_80124F68;
void *func_8003936C(s32 arg0) {
    void *var_v1;
    struct PoolBase {
        u8 pad[0x10A0];
        s32 count;
    };

    var_v1 = NULL;
    if (arg0 <= 0) {
        var_v1 = (void *)((u8 *)&D_80124F68 + (((struct PoolBase *)&D_80124F68)->count << 6) + (arg0 << 6));
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
extern u8 D_80124F68;

void *GeoRender_GetMatrix(s32 arg0) {
    void *var_v1;

    var_v1 = NULL;
    if ((arg0 >= 0) && (arg0 < 0x20)) {
        var_v1 = (arg0 << 6) + &D_80124F68;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
extern u8 D_80126010;
extern u8 D_800948E4[];
void GeoRender_ResetTransformStack(void) {
    struct Vec3Words {
        s32 x;
        s32 y;
        s32 z;
    };
    struct State {
        struct Vec3Words value;
        u8 pad[0x174];
        s32 flag;
    };

    ((struct State *)&D_80126010)->flag = 0;
    ((struct State *)&D_80126010)->value = *(struct Vec3Words *)D_800948E4;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800393F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003946C.s")
#endif

#ifdef VERSION_US
void GeoOverlay_DrawFadeQuad(S1_unk_D_86002F34_00C_0CC* arg0, S1_unk_D_86002F34_00C_040* arg1) {
    Vtx* temp_v0 = func_8003946C(arg0, arg1);

    if (temp_v0 != NULL) {
        gDPSetCombineMode(D_800D0510++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(D_800D0510++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

        gSPVertex(D_800D0510++, (u32)temp_v0 & 0x1FFFFFFF, 4, 0);
        gSP2Triangles(D_800D0510++, 0, 1, 2, 0, 0, 2, 3, 0);
    }

    if (arg0->unk_00 != 1) {
        arg0->unk_0A++;
        if (arg0->unk_0A == arg0->unk_08) {
            if (arg0->unk_00 == 2) {
                arg0->unk_00 = 0;
            } else {
                arg0->unk_00 = 1;
            }
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80039808.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800398F8.s")
#endif

#ifdef VERSION_US
void GeoOverlay_DrawRotatingQuad(S1_unk_D_86002F34_00C_0CC* arg0, UNUSED S1_unk_D_86002F34_00C_040* arg1) {
    Vtx* temp_v0 = func_800398F8(arg0);

    if (temp_v0 != 0) {
        gDPSetCombineMode(D_800D0510++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(D_800D0510++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);

        gSPVertex(D_800D0510++, (u32)temp_v0 & 0x1FFFFFFF, 8, 0);
        gSP2Triangles(D_800D0510++, 0, 4, 1, 0, 1, 4, 5, 0);
        gSP2Triangles(D_800D0510++, 1, 5, 2, 0, 2, 5, 6, 0);
        gSP2Triangles(D_800D0510++, 2, 6, 7, 0, 2, 7, 3, 0);
        gSP2Triangles(D_800D0510++, 3, 4, 0, 0, 3, 7, 4, 0);

        gDPPipeSync(D_800D0510++);

        gDPSetCombineMode(D_800D0510++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
        gDPSetRenderMode(D_800D0510++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        gDPSetTextureFilter(D_800D0510++, G_TF_BILERP);

        if (arg0->unk_02 == 0) {
            gDPLoadTextureBlock(D_800D0510++, arg0->texture, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureBlock(D_800D0510++, arg0->texture, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, 0,
                                G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
        }

        gSPTexture(D_800D0510++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

        gSPVertex(D_800D0510++, (u32)temp_v0 & 0x1FFFFFFF, 4, 0);
        gSP2Triangles(D_800D0510++, 0, 1, 2, 0, 0, 2, 3, 0);

        gSPTexture(D_800D0510++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetTextureFilter(D_800D0510++, G_TF_BILERP);
    }

    arg0->unk_0A++;
    if (arg0->unk_0A == arg0->unk_08) {
        if (arg0->unk_00 == 4) {
            arg0->unk_00 = 0;
        } else {
            arg0->unk_00 = 1;
        }
    }
}
#endif

#ifdef VERSION_US
void GeoOverlay_Draw(S1_unk_D_86002F34_00C_0CC* arg0, S1_unk_D_86002F34_00C_040* arg1) {
    if (arg0->unk_00 != 0) {
        gDPPipeSync(D_800D0510++);

        gDPSetCycleType(D_800D0510++, G_CYC_1CYCLE);
        gSPClearGeometryMode(D_800D0510++, G_ZBUFFER | G_LIGHTING);
        gSPPerspNormalize(D_800D0510++, 0xFFFF);
        gSPMatrix(D_800D0510++, (u32)arg1->mtx & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(D_800D0510++, (u32)&D_80094890 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if ((arg0->unk_00 == 1) || (arg0->unk_00 == 2) || (arg0->unk_00 == 3)) {
            GeoOverlay_DrawFadeQuad(arg0, arg1);
        } else {
            GeoOverlay_DrawRotatingQuad(arg0, arg1);
        }

        gDPPipeSync(D_800D0510++);
        gDPSetCycleType(D_800D0510++, G_CYC_2CYCLE);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003A2C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003A370.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003A440.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003A4CC.s")
#endif

#ifdef VERSION_US
extern s32 D_8009490C;
extern void func_8003A2C8(void *, ...);
void Geo_NodeType3Pass(s32 arg0) {
    D_8009490C = arg0;
    func_8003A2C8((void *)arg0);
    D_8009490C = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003A7F4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003A960.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003A9CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003AA58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003AB68.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003ABFC.s")
#endif

#ifdef VERSION_US
void func_8003AC84(s32 arg0) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003AC8C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003ADA4.s")
#endif

#ifdef VERSION_US
void func_8003B03C(s32 arg0) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B044.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B218.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B350.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B48C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B534.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B5AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B600.s")
#endif

#ifdef VERSION_US
s32 func_800392B8(s32, s32);
extern void func_8003A370(s32);
extern s32 D_8009499C;

void func_8003B690(s32 arg0) {
    D_8009499C = func_800392B8(arg0 + 0x18, 0);
    func_8003A370(arg0);
    (*(s32 *)((u8 *)(&D_80124F68) + (0x10A0))) = (s32) ((*(s32 *)((u8 *)(&D_80124F68) + (0x10A0))) - 1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B6D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003B9F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003BC48.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003BCB4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003BEF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003BF9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003C080.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003C10C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003C2D8.s")
#endif

#ifdef VERSION_US
extern void func_8003C2D8(s16);
extern void func_8003A2C8(void *, ...);
void Geo_NodeAnchor(void *arg0) {
    func_8003C2D8(*(s16 *)((u8 *)arg0 + 0x18));
    func_8003A2C8(arg0);
}
#endif

#ifdef VERSION_US
extern void func_8003A2C8(void *, ...); void Geo_NodeGroup(void *arg0) { func_8003A2C8(arg0); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003C390.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003C6B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003C848.s")
#endif

#ifdef VERSION_US
extern s32 D_80094900;
void func_8003C964(s32 value) { D_80094900 = value; }
#endif

#ifdef VERSION_US
extern u16 D_80094904;
void GeoRender_AdvanceFrameCounter(void) { D_80094904++; }
#endif

#ifdef VERSION_US
typedef struct { char pad[0x1A]; u16 unk_1A; } ModelFrame;
extern ModelFrame *D_80094910; extern u16 D_80094904;
s32 GeoRender_IsModelFrameCurrent(void) { s32 var_v1 = 1; if (D_80094910 != NULL) { var_v1 = D_80094910->unk_1A == D_80094904; } return var_v1; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003C9B8.s")
#endif

#ifdef VERSION_US
typedef struct S1_arg1_func_81407874_014_000_010 S1_arg1_func_81407874_014_000_010;
struct S1_arg1_func_81407874_014_000_010 {
      u8 unk_00;
      u8 unk_01;
      u8 unk_02;
      u8 unk_03;
      u8 unk_04;
      u8 unk_05;
      u8 unk_06;
      u8 unk_07;
      u8 unk_08;
      u8 unk_09;
      u8 unk_0A;
      u8 unk_0B;
      u8 unk_0C;
      u8 unk_0D;
      u8 unk_0E;
      u8 unk_0F;
};
void func_8003CA30(Gfx* arg0, S1_arg1_func_81407874_014_000_010* arg1) {
    gDPSetCombine(arg0++,
                  GCCc0w0(arg1->unk_00, arg1->unk_02, arg1->unk_04, arg1->unk_06) | GCCc1w0(arg1->unk_08, arg1->unk_0A),

                  GCCc0w1(arg1->unk_01, arg1->unk_03, arg1->unk_05, arg1->unk_07) |
                      GCCc1w1(arg1->unk_09, arg1->unk_0C, arg1->unk_0E, arg1->unk_0B, arg1->unk_0D, arg1->unk_0F));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003CB3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003CBD4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003CC14.s")
#endif

#ifdef VERSION_US
s32 func_8003CD58(s32 arg0) { s32 var_v1; if ((arg0 != 0) && (arg0 != 5) && (arg0 != 0xA)) { var_v1 = 0; } else { var_v1 = 1; } return var_v1; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003CD84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003CFB8.s")
#endif

#ifdef VERSION_US
extern void func_8003CC14();
extern void *D_801263A8;

void GeoRender_RestoreRenderMode(s32 arg0) {
    if ((*(s32 *)((u8 *)(D_801263A8) + (0x14))) & 0xFF) {
        func_8003CC14();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D0C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D188.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D1F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D270.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D55C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D70C.s")
#endif

#ifdef VERSION_US
extern u8 D_801261B0[];
void func_8003D7B8(s16 arg0) {
    if (((arg0 > 0) && (arg0 < 4)) || (arg0 == 0x84) || (arg0 == 7)) {
        D_801261B0[3] = D_801261B0[2];
        return;
    }
    D_801261B0[3] = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D808.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003D888.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003DA20.s")
#endif

#ifdef VERSION_US
void GeoRender_SetMaterialParams(s32 arg0, s32 arg1, s32 arg2) {
    s32 *p0 = &arg0;
    s32 *p1 = &arg1;
    *(s32 *)(D_801261B0 + 8) = *p0;
    D_801261B0[1] = (u8)*p1;
    D_801261B0[2] = (u8)arg2;
}
#endif

#ifdef VERSION_US
typedef union CandidateColor {
    struct { u8 r, g, b, a; };
    u32 rgba;
} CandidateColor;
void GeoRender_SetMaterialTexture(s32 arg0, CandidateColor arg1, void *arg2, void *arg3, s32 arg4) {
    D_801261B0[0] = arg0;
    *(s32 *)(D_801261B0 + 4) = arg1.rgba;
    *(void **)(D_801261B0 + 0xC) = arg2;
    *(void **)(D_801261B0 + 0x10) = arg3;
    *(s32 *)(D_801261B0 + 0x14) = arg4;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003DB38.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003DD2C.s")
#endif

#ifdef VERSION_US
f32 ModelAnim_EvaluateTranslationChannel(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    f32 ret;
    s32 var_a2;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];

    if (temp_v0->translationKeyCount == 1) {
        ret = temp_v0->translationBaseIndex / 1000.0f;
    } else {
        if (arg0->currentFrame < temp_v0->translationKeyCount) {
            var_a2 = temp_v0->translationBaseIndex + arg0->currentFrame;
        } else {
            var_a2 = (temp_v0->translationBaseIndex + temp_v0->translationKeyCount) - 1;
        }

        ret = arg0->translationValues[var_a2] / 1000.0f;
    }

    return ret;
}
#endif

#ifdef VERSION_US
s16 ModelAnim_EvaluateRotationChannel(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    s32 var_a1;
    s16 var_v1;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];

    if (temp_v0->rotationKeyCount == 1) {
        var_v1 = temp_v0->rotationBaseIndex * 0x10;
    } else {
        if (arg0->currentFrame < temp_v0->rotationKeyCount) {
            var_a1 = temp_v0->rotationBaseIndex + arg0->currentFrame;
        } else {
            var_a1 = (temp_v0->rotationBaseIndex + temp_v0->rotationKeyCount) - 1;
        }
        var_v1 = func_80037360(arg0->rotationValues, var_a1, 0xC) * 0x10;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
f32 ModelAnim_EvaluateScaleChannel(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    f32 var_fv1;
    s16 var_a2;
    s32 var_a1;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];

    if (temp_v0->scaleKeyCount == 1) {
        if (arg0->flags & 4) {
            var_fv1 = (s16)temp_v0->scaleBaseIndex;
        } else {
            var_a2 = temp_v0->scaleBaseIndex * 0x10;
            var_fv1 = var_a2 >> 4;
        }
    } else {
        if (arg0->currentFrame < temp_v0->scaleKeyCount) {
            var_a1 = temp_v0->scaleBaseIndex + arg0->currentFrame;
        } else {
            var_a1 = (temp_v0->scaleBaseIndex + temp_v0->scaleKeyCount) - 1;
        }

        if (arg0->flags & 4) {
            var_fv1 = func_80037360(arg0->scaleValues, var_a1, 0x10);
        } else {
            var_fv1 = func_80037360(arg0->scaleValues, var_a1, 0xC);
        }
    }

    return var_fv1;
}
#endif

#ifdef VERSION_US
f32 ModelAnim_InterpolateKeyframe(S1_Vec3s* arg0, s16 arg1, s16 arg2) {
    f32 y;
    s32 i;
    f32 x;
    f32 var_fv1;

    if (arg0->x >= arg2) {
        var_fv1 = arg0->y;
    } else {
        if (arg2 >= arg0[arg1 - 1].x) {
            var_fv1 = arg0[arg1 - 1].y;
        } else {
            for (i = 0; i < arg1 - 2; i++) {
                if (arg2 < arg0[i + 1].x) {
                    break;
                }
            }

            x = (arg2 - arg0[i].x) / 30.0f;
            y = 30.0f / (arg0[i + 1].x - arg0[i].x);

            var_fv1 = (arg0[i].y * (((2.0f * x * x * x * y * y * y) - 3.0f * x * x * y * y) + 1.0f))
                    + (arg0[i + 1].y * ((-2.0f * x * x * x * y * y * y) + 3.0f * x * x * y * y))
                    + (arg0[i].z * ((x * x * x * y * y - (2.0f * x * x * y)) + x))
                    + (arg0[i + 1].z * (x * x * x * y * y - (x * x * y)));
        }
    }
    return var_fv1;
}
#endif

#ifdef VERSION_US
f32 ModelAnim_InterpolateKeyframeTangent(S1_unk_func_80016B30_arg0* arg0, s16 arg1, s16 arg2) {
    f32 y;
    s32 i;
    f32 x;
    f32 var_fv1;

    if (arg0->vec.x >= arg2) {
        var_fv1 = arg0->vec.y;
    } else {
        if (arg2 >= arg0[arg1 - 1].vec.x) {
            var_fv1 = arg0[arg1 - 1].vec.y;
        } else {
            for (i = 0; i < arg1 - 2; i++) {
                if (arg2 < arg0[i + 1].vec.x) {
                    break;
                }
            }

            x = (arg2 - arg0[i].vec.x) / 30.0f;
            y = 30.0f / (arg0[i + 1].vec.x - arg0[i].vec.x);

            var_fv1 = (arg0[i].vec.y * (((2.0f * x * x * x * y * y * y) - 3.0f * x * x * y * y) + 1.0f))
                    + (arg0[i + 1].vec.y * ((-2.0f * x * x * x * y * y * y) + 3.0f * x * x * y * y))
                    + (arg0[i].unk_06 * ((x * x * x * y * y - (2.0f * x * x * y)) + x))
                    + (arg0[i + 1].vec.z * (x * x * x * y * y - (x * x * y)));
        }
    }
    return var_fv1;
}
#endif

#ifdef VERSION_US
f32 ModelAnim_EvaluateTranslationCurve(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    f32 var_fv1;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];
    s16* tmp;

    if (temp_v0->translationKeyCount < 2) {
        var_fv1 = (s16)temp_v0->translationBaseIndex / 100.0f;
    } else {
        tmp = &arg0->translationValues[temp_v0->translationBaseIndex];
        if (temp_v0->unk_03 & 4) {
            var_fv1 = ModelAnim_InterpolateKeyframeTangent(tmp, temp_v0->translationKeyCount, arg0->currentFrame) / 100.0f;
        } else {
            var_fv1 = ModelAnim_InterpolateKeyframe(tmp, temp_v0->translationKeyCount, arg0->currentFrame) / 100.0f;
        }
    }
    return var_fv1;
}
#endif

#ifdef VERSION_US
s16 ModelAnim_EvaluateRotationCurve(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    f32 var_fv1;
    s16* temp_a0;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];

    if (temp_v0->rotationKeyCount < 2) {
        var_fv1 = (s16)temp_v0->rotationBaseIndex / 10.0f;
    } else {
        temp_a0 = &arg0->rotationValues[temp_v0->rotationBaseIndex];
        if (temp_v0->unk_03 & 2) {
            var_fv1 = ModelAnim_InterpolateKeyframeTangent(temp_a0, temp_v0->rotationKeyCount, arg0->currentFrame) / 10.0f;
        } else {
            var_fv1 = ModelAnim_InterpolateKeyframe(temp_a0, temp_v0->rotationKeyCount, arg0->currentFrame) / 10.0f;
        }
    }

    while (var_fv1 < 0.0f) {
        var_fv1 += 360.0f;
    }

    while (var_fv1 >= 360.0f) {
        var_fv1 -= 360.0f;
    }

    return (var_fv1 / 360.0f) * 65536.0f;
}
#endif

#ifdef VERSION_US
f32 ModelAnim_EvaluateScaleCurve(S1_unk_D_800ABCC0* arg0, s32 arg1) {
    s16* temp_a0;
    f32 var_fv0;
    f32 var_fv1;
    S1_unk_D_800ABCC0_008* temp_v0 = &arg0->channels[arg1];

    if (temp_v0->scaleKeyCount < 2) {
        var_fv1 = (s16)temp_v0->scaleBaseIndex;
    } else {
        temp_a0 = &arg0->scaleValues[temp_v0->scaleBaseIndex];
        if (temp_v0->unk_03 & 1) {
            var_fv0 = ModelAnim_InterpolateKeyframeTangent(temp_a0, temp_v0->scaleKeyCount, arg0->currentFrame);
        } else {
            var_fv0 = ModelAnim_InterpolateKeyframe(temp_a0, temp_v0->scaleKeyCount, arg0->currentFrame);
        }
        var_fv1 = var_fv0;
    }
    return var_fv1;
}
#endif

#ifdef VERSION_US
s32 ModelAnim_AdvanceCurveFrame(S1_unk_D_86002F58_004_000_040_raw* arg0, u16 arg1) {
    S1_unk_D_86002F58_004_000_040_raw_08 spC;
    S1_unk_D_86002F58_004_000_040_raw_08* ptr;
    S1_unk_D_86002F58_004_000_040_004* temp_v0;

    ptr = &spC;
    temp_v0 = arg0->unk_04;
    spC.raw = arg0->unk_08.raw;
    if (arg0->unk_12 != arg1) {
        spC.raw += arg0->unk_0C;
        if (arg0->unk_0C >= 0) {
            if (ptr->unk_00 >= temp_v0->unk_0A) {
                if (temp_v0->unk_00 & 2) {
                    ptr->unk_00 = temp_v0->unk_0A - 1;
                } else {
                    ptr->unk_00 = temp_v0->unk_06;
                }
            }
        } else {
            if (ptr->unk_00 < temp_v0->unk_06) {
                if (temp_v0->unk_00 & 2) {
                    ptr->unk_00 = temp_v0->unk_06;
                } else {
                    ptr->unk_00 = temp_v0->unk_0A - 1;
                }
            }
        }
    }

    return spC.raw;
}
#endif

#ifdef VERSION_US
extern s32 D_801263E0; void ModelAnim_ResetCurveContext(void) { D_801263E0 = -1; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003E7B0.s")
#endif

#ifdef VERSION_US
extern s32 D_801263E0; void ModelAnim_EndCurveContext(void) { if (D_801263E0 >= 0) { D_801263E0--; } }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003E8C8.s")
#endif

#ifdef VERSION_US
void ModelAnim_ClearTransformChannel(u8 *arg0) { *(s16 *)(arg0 + 0x40) = -1; *(s32 *)(arg0 + 0x44) = 0; }
#endif

#ifdef VERSION_US
s32 ModelAnim_BindTransformCurve(S1_unk_D_86002F58_004_000* arg0, s16 arg1, void* arg2, s32 arg3) {
    S1_unk_D_86002F58_004_000_040_004* temp_v0 = func_80003240(arg2);
    S1_unk_D_86002F58_004_000_040* ptr = &arg0->unk_040;

    if ((temp_v0 != ptr->unk_04) || (arg1 != ptr->unk_00)) {
        ptr->unk_00 = arg1;
        ptr->unk_04 = temp_v0;
        ptr->unk_08 = (temp_v0->unk_04 << 0x10) - arg3;
    }

    ptr->unk_0C = arg3;
    return ptr->unk_08 >> 0x10;
}
#endif

#ifdef VERSION_US
s32 ModelAnim_SetSpeed(u8 *arg0, s32 arg1) { *(s32 *)(arg0 + 0x4C) = arg1; return *(s32 *)(arg0 + 0x48) >> 16; }
#endif

#ifdef VERSION_US
void ModelAnim_SetFrame(u8 *arg0, s16 value) { *(s32 *)(arg0 + 0x48) = ((s32)value << 16) - *(s32 *)(arg0 + 0x4C); }
#endif

#ifdef VERSION_US
typedef struct { char pad[0x40]; struct { s16 pad0; void *data; s32 frame; s32 speed; } curve; } ModelAnim;
s32 ModelAnim_HasCrossedFrame(ModelAnim *arg0, s16 arg1) { struct { s16 pad0; void *data; s32 frame; s32 speed; } *ptr = &arg0->curve; s32 temp_v0 = ptr->frame + ptr->speed; s32 arg = arg1 << 16; s32 var_a2; s32 v = ptr->speed; if (v >= 0) { var_a2 = ptr->frame < arg; if (var_a2 != 0) var_a2 = temp_v0 >= arg; } else { var_a2 = arg < ptr->frame; if (var_a2 != 0) var_a2 = arg >= temp_v0; } return var_a2; }
#endif

#ifdef VERSION_US
typedef struct { s16 flags; char pad2[4]; s16 fallback; char pad8[2]; u16 frameCount; } EventData;
s32 ModelAnim_IsAnimationDone(ModelAnim *arg0) { return ModelAnim_HasCrossedFrame(arg0, ((EventData *)arg0->curve.data)->frameCount - 1); }
#endif

#ifdef VERSION_US
typedef struct { u8 pad[0x44]; u8 *value44; s32 value48; } Func3EC34;
s32 ModelAnim_IsFinished(Func3EC34 *arg0) { return arg0->value48 >= ((*(u16 *)(arg0->value44 + 0xA) - 1) << 16); }
#endif

#ifdef VERSION_US
typedef struct { u8 pad[0x48]; s32 value48; s32 value4C; } Func3EC54;
s32 func_8003EC54(Func3EC54 *arg0) { s32 value = arg0->value48 + arg0->value4C; return (s16)(value >> 16); }
#endif

#ifdef VERSION_US
typedef struct { u16 keyCount; u16 baseIndex; } EventIndex;
s32 ModelAnim_ResolveEventIndex(s32 arg0, EventIndex* arg1, s32 arg2) { EventIndex* temp_v0 = &arg1[arg2]; s32 ret; if (arg0 < temp_v0->keyCount) { ret = arg0 + temp_v0->baseIndex; } else { ret = (temp_v0->baseIndex + temp_v0->keyCount) - 1; } return ret; }
#endif

#ifdef VERSION_US
s16 ModelAnim_AdvanceEventFrame(S1_unk_D_86002F58_004_000_054* arg0, u16 arg1) {
    s16 var_v1;
    S1_unk_D_86002F58_004_000_054_004* temp_v0;

    var_v1 = arg0->unk_08;
    temp_v0 = arg0->unk_04;

    if (arg0->unk_0A != arg1) {
        var_v1 += 1;
        if (var_v1 >= temp_v0->unk_0A) {
            if (temp_v0->unk_00 & 2) {
                var_v1 = temp_v0->unk_0A - 1;
            } else {
                var_v1 = temp_v0->unk_06;
            }
        }
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
extern s32 D_80126410; void ModelAnim_ResetEventContext(void) { D_80126410 = -1; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003ED18.s")
#endif

#ifdef VERSION_US
extern s32 D_80126410; void ModelAnim_EndEventContext(void) { if (D_80126410 >= 0) { D_80126410--; } }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003EE20.s")
#endif

#ifdef VERSION_US
void ModelAnim_ClearEventTrack(u8 *arg0) { *(s16 *)(arg0 + 0x54) = -1; *(s32 *)(arg0 + 0x58) = 0; }
#endif

#ifdef VERSION_US
s16 ModelAnim_BindEventTrack(S1_unk_D_86002F58_004_000* arg0, s16 arg1, s32 arg2) {
    S1_unk_D_86002F58_004_000_054_004* temp_v0 = func_80003240(arg2);
    S1_unk_D_86002F58_004_000_054* ptr = &arg0->unk_054;

    if ((temp_v0 != ptr->unk_04) || (arg1 != ptr->unk_00)) {
        ptr->unk_00 = arg1;
        ptr->unk_04 = temp_v0;
        ptr->unk_08 = temp_v0->unk_04 - 1;
    }

    return ptr->unk_08;
}
#endif

#ifdef VERSION_US
void ModelAnim_SetEventFrame(u8 *arg0, s16 value) { *(s16 *)(arg0 + 0x5C) = value - 1; }
#endif

#ifdef VERSION_US
void func_8003EF60(u8 *arg0) { *(u16 *)(arg0 + 0x56) |= 1; }
#endif

#ifdef VERSION_US
void func_8003EF70(u8 *arg0) { *(u16 *)(arg0 + 0x56) &= (u16)~1; }
#endif

#ifdef VERSION_US
s32 ModelAnim_IsEventFrame(u8 *arg0, s16 value) { return value == *(s16 *)(arg0 + 0x5C) + 1; }
#endif

#ifdef VERSION_US
s32 ModelAnim_IsEventTrackNearEnd(u8 *arg0) { return *(u16 *)(*(s32 *)(arg0 + 0x58) + 0xA) == *(s16 *)(arg0 + 0x5C) + 2; }
#endif

#ifdef VERSION_US
s32 ModelAnim_IsEventTrackDone(u8 *arg0) { return *(u16 *)(*(s32 *)(arg0 + 0x58) + 0xA) == *(s16 *)(arg0 + 0x5C) + 1; }
#pragma C_FUNCTION_PADDING(8)
#endif

#ifdef VERSION_US
extern void func_80037E9C(s32, void *);
extern u8 D_80126420[];
extern u8 D_80126438[];
void ModelRenderer_InitDisplayRoots(void) {
    func_80037E9C(0, D_80126420);
    func_80037E9C(0, D_80126438);
}
#endif

#ifdef VERSION_US
extern void func_8003F03C(s32, void *);
void func_8003F018(s32 arg0) {
    func_8003F03C(arg0, D_80126420);
}
#endif

#ifdef VERSION_US
extern S1_unk_D_86002F58_004_000 *func_80038894(S1_MainPoolState *, void *, s16, S1_Vec3f *, S1_Vec3s *, S1_Vec3f *);
extern u8 D_800948DC[];
void func_8003F03C(s32 arg0, void *arg1) {
    func_80038894(NULL, (void *) arg0, -1, &D_800948D0, (S1_Vec3s *) D_800948DC, (S1_Vec3f *) D_800948E4);
    func_80038F8C(arg1, (void *) arg0);
    (*(u8 *)((u8 *)(arg0) + (1))) = (u8) ((*(u8 *)((u8 *)(arg0) + (1))) & 0xFFFE);
}
#endif

#ifdef VERSION_US
void ModelRenderer_AttachSecondaryDisplayObject(void *arg0) {
    func_80038894(NULL, arg0, 0, &D_800948D0, (S1_Vec3s *) D_800948DC, (S1_Vec3f *) D_800948E4);
    func_80038F8C(D_80126438, arg0);
    (*(u8 *)((u8 *)(arg0) + (1))) = (u8) ((*(u8 *)((u8 *)(arg0) + (1))) & 0xFFFE);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F114.s")
#endif

#ifdef VERSION_US
extern void func_8006D438();

void func_8003F1DC(void *arg0) {
    func_8006D438();
    (*(s32 *)((u8 *)(arg0) + (0xC))) = 0;
    (*(u8 *)((u8 *)(arg0) + (1))) = (u8) ((*(u8 *)((u8 *)(arg0) + (1))) & 0xFFFE);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F210.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F2C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F3BC.s")
#endif

#ifdef VERSION_US
void func_8003F454(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    Color_SetRGBA((Color3575C *)(u32)(arg0 + 0xA0), arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF, (u8) (s32) arg4);
}
#endif

#ifdef VERSION_US
void func_8003F498(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    Color_SetRGBA((Color3575C *)(u32)(arg0 + 0xA0), arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF, (u8) (s32) arg4);
}
#endif

#ifdef VERSION_US
void func_8003F4DC(u8 *arg0, u8 value) { arg0[0x1D] = value; }
#endif

#ifdef VERSION_US
void func_8003F4E8(u8 *arg0, u8 value) { arg0[0x1C] = value; }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F4F4.s")
#endif

#ifdef VERSION_US
extern void *func_80003240();
void *func_8003F54C(void *arg0) {
    void *result = NULL;
    void *entry;
    void *value;

    entry = *(void **)((u8 *)arg0 + 0xC);
    if (entry != NULL) {
        value = (*(void *(**)(s32, s32))((u8 *)entry + 0x2C))(0, 0);
        if (*(void **)((u8 *)value + 0x18) != NULL) {
            result = func_80003240(*(void **)((u8 *)value + 0x18));
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F5AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F6E0.s")
#endif

#ifdef VERSION_US
extern void _bzero(void *arg0, s32 arg1);
void func_8003F818(s32 *arg0, s32 arg1) {
    _bzero(arg0, 0x10);
    *arg0 = arg1;
}
#endif

#ifdef VERSION_US
void func_8003F84C(u8 *arg0, u32 value1, u32 value2) { arg0[4] |= 0x80; *(u32 *)(arg0 + 8) = value1; *(u32 *)(arg0 + 0xC) = value2; }
#endif

#ifdef VERSION_US
void func_8003F864(u8 *arg0) { arg0[4] = (u8)(arg0[4] & ~0x10); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F874.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F904.s")
#endif

#ifdef VERSION_US
s32 func_8003F954(u16 value) { return value % 9; }
#endif

#ifdef VERSION_US
s32 func_8003F970(s32 arg0, u16 arg1) {
    s32 result = 0;
    if (arg0 == 0xEB) {
        result = func_8003F954(arg1);
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003F9AC.s")
#endif

#ifdef VERSION_US
extern void func_80027E30(s32);
extern void func_80027F4C(void);
extern s16 D_8012651A;
extern s32 D_80126458[];
extern s16 D_8012651E;
extern s16 D_80126518;
extern s32 D_80126520;
extern void *func_80003240();
void geo_layout_cmd_branch_and_link(void)
{
  s32 p = D_80126520;
  s32 i = D_8012651A;
  if (D_8012651A)
  {
  }
  D_80126458[i] = p + 8;
  D_8012651A = i + 1;
  D_80126458[D_8012651A] = (D_80126518 << 16) + D_8012651E;
  D_8012651A = D_8012651A + 1;
  D_8012651E = D_8012651A;
  D_80126520 = (s32) func_80003240(*((s32 *) (((u8 *) p) + 4)));
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_2A(void) {
    s32 new_var;
    s32 p = D_80126520;
    s32 i = D_8012651A;
    if (D_8012651A)
    {
    }
    new_var = p;
    D_80126458[i] = p + 8;
    D_8012651A = i + 1;
    D_80126458[D_8012651A] = (D_80126518 << 16) + D_8012651E;
    D_8012651A = D_8012651A + 1;
    D_8012651E = D_8012651A;
    D_80126520 = (s32)func_80003240(*((s32 *) (*((s32 **) (new_var + 4)))));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003FB2C.s")
#endif

#ifdef VERSION_US
extern s32 D_80126520;
void geo_layout_cmd_jump(void) {
    void *p = (void *)(u32)D_80126520;
    D_80126520 = (s32)func_80003240(*(s32 *)((u8 *)p + 4));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003FBE0.s")
#endif

#ifdef VERSION_US
extern s16 D_8012651A;
extern s32 D_80126458[];
extern void * func_80003240();
void geo_layout_cmd_27(void)
{
    s32 new_var;
    s32 i = D_8012651A;
    s32 p = D_80126520;
    new_var = p;
    D_80126458[i] = p + 8;
    if (D_80126520)
    {
    }
    D_8012651A = i + 1;
    D_80126520 = (s32)func_80003240(*((s32 *) (*((s32 **) (new_var + 4)))));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003FC8C.s")
#endif

#ifdef VERSION_US
extern s16 D_80126518;
extern s32 D_80126498[];
void geo_layout_cmd_open_node(void) {
    s32 i = D_80126518;
    s32 *table = D_80126498;
    table[i + 1] = table[i];
    D_80126518 = i + 1;
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_close_node(void) {
    D_80126518--;
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003FD34.s")
#endif

#ifdef VERSION_US
extern S1_MainPoolState *D_80126450;
extern void func_8003FD34(void *);
extern void *func_800380B8(S1_MainPoolState *, s32, s16);
extern void *func_8003811C(S1_MainPoolState *, s32, s16);
void geo_layout_cmd_attach_node(void) {
    struct Cmd {
        u8 pad[4];
        void *child;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(cmd->child);
    D_80126520 += 8;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003FDD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003FE2C.s")
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_reference(void) {
    struct Cmd {
        u8 pad[4];
        S1_GraphNode *reference;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(GeoNode_CreateWithReference(D_80126450, NULL, cmd->reference));
    D_80126520 += 8;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8003FEB8.s")
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_type3(void) {
    struct Cmd {
        u8 command;
        u8 pad;
        s16 value;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(GeoNode_CreateType3((S1_MemoryBlock *)D_80126450, NULL, cmd->value));
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_type4(void) {
    struct Cmd {
        u8 command;
        u8 pad;
        s16 value;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(GeoNode_CreateType4((S1_MemoryBlock *)D_80126450, NULL, cmd->value));
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_ortho(void) {
    struct Cmd {
        u8 command;
        u8 pad;
        s16 value;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(func_800380B8(D_80126450, 0, cmd->value));
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_perspective(void) {
    struct Cmd {
        u8 command;
        u8 pad;
        s16 value;
    } *cmd;

    cmd = (struct Cmd *)(u32)D_80126520;
    func_8003FD34(func_8003811C(D_80126450, 0, cmd->value));
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_background(void) {
    struct TargetCmd16 { u8 cmd; u8 r; u8 g; u8 b; } *cmd;
    cmd = (struct TargetCmd16 *)(u32)D_80126520;
    func_8003FD34(GeoNode_CreateBackground(D_80126450, NULL, cmd->r, cmd->g, cmd->b));
    D_80126520 += sizeof(struct TargetCmd16);
}
#endif

#ifdef VERSION_US
extern s32 func_8003820C(s32, s32);
void geo_layout_cmd_create_clear_depth(void) {
    func_8003FD34((void *)(S1_uintptr_t)func_8003820C((s32)(S1_uintptr_t)D_80126450, 0));
    D_80126520 += 4;
}
#endif

void geo_layout_cmd_noop(void) {
}

#ifdef VERSION_US
void geo_layout_cmd_create_fog(void) {
    S1_unk_D_800ABE00_cmd13* cmd = (S1_unk_D_800ABE00_cmd13*)D_80126520;

    func_8003FD34(GeoNode_CreateFog((s32)(S1_uintptr_t)D_80126450, NULL, cmd->fogNear, cmd->fogFar, cmd->r, cmd->g, cmd->b, 0xFF));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd13);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80040244.s")
#endif

#ifdef VERSION_US
void geo_layout_cmd_28(void) {
    s32 *node = (s32 *)D_80126498[D_80126518];
    if (node != NULL) {
        *((u8 *)node + 2) |= 1;
    }
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
s32 func_80038474(s32, s32);

void geo_layout_cmd_29(void) {
    func_8003FD34((void *)(S1_uintptr_t)func_80038474((s32)(S1_uintptr_t)D_80126450, 0));
    D_80126520 += 4;
}
#endif

#ifdef VERSION_US
extern s32 D_80126520; void geo_layout_cmd_skip(void) { D_80126520 += 0xC; }
#endif

#ifdef VERSION_US
typedef struct S1_unk_D_800ABE00_cmd16 S1_unk_D_800ABE00_cmd16;
struct S1_unk_D_800ABE00_cmd16 {
      u8 cmd;
      u8 r;
      u8 g;
      u8 b;
};
void geo_layout_cmd_create_ambient_light(void) {
    S1_unk_D_800ABE00_cmd16* cmd = (S1_unk_D_800ABE00_cmd16*)D_80126520;

    func_8003FD34(GeoNode_CreateAmbientLight(D_80126450, NULL, cmd->r, cmd->g, cmd->b));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd16);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_17(void) {
    s32 var_v1;

    var_v1 = 0;
    if ((*(u8 *)((u8 *)(D_80126520) + (1))) & 1) {
        var_v1 = 1;
    }
    func_8003FD34(func_800384C0(D_80126450, 0, (*(s16 *)((u8 *)(D_80126520) + (2))), (*(s32 *)((u8 *)(D_80126520) + (8))), (s32) (*(s16 *)((u8 *)(D_80126520) + (4))), (*(s32 *)((u8 *)(D_80126520) + (0xC))), (s32) (*(s16 *)((u8 *)(D_80126520) + (6))), (*(s32 *)((u8 *)(D_80126520) + (0x10))), var_v1));
    D_80126520 += 0x14;
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_shadow(void) {
    S1_unk_D_800ABE00_cmd18* cmd = (S1_unk_D_800ABE00_cmd18*)D_80126520;

    func_8003FD34(GeoNode_CreateShadow(D_80126450, NULL, cmd->unk_01, cmd->unk_04, cmd->unk_06, cmd->unk_02));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd18);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_cull_distance(void) {
    S1_unk_D_800ABE00_cmd19* cmd = (S1_unk_D_800ABE00_cmd19*)D_80126520;

    func_8003FD34(GeoNode_CreateCullDistance(D_80126450, NULL, cmd->nearDistance, cmd->farDistance));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd19);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_switch_case(void) {
    S1_unk_D_800ABE00_cmd1A* cmd = (S1_unk_D_800ABE00_cmd1A*)D_80126520;

    func_8003FD34(GeoNode_CreateSwitchCase(D_80126450, NULL, cmd->unk_01, cmd->caseIndex));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1A);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_translate_rotate(void) {
    S1_Vec3s sp30;
    S1_Vec3f sp24;
    UNUSED s32 pad;
    S1_unk_D_800ABE00_cmd1B* cmd = (S1_unk_D_800ABE00_cmd1B*)D_80126520;

    Vec3f_FromVec3s(&sp24, &cmd->translation);
    Vec3s_SetComponents(&sp30, (cmd->rotX << 0xF) / 180, (cmd->rotY << 0xF) / 180, (cmd->rotZ << 0xF) / 180);
    func_8003FD34(GeoNode_CreateTranslateRotate(D_80126450, NULL, &sp24, &sp30));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1B);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_translate(void) {
    S1_Vec3f sp24;
    S1_unk_D_800ABE00_cmd1C* cmd = (S1_unk_D_800ABE00_cmd1C*)D_80126520;

    sp24.x = cmd->translateX / 65536.0f;
    sp24.y = cmd->translateY / 65536.0f;
    sp24.z = cmd->translateZ / 65536.0f;
    func_8003FD34(GeoNode_CreateTranslate(D_80126450, NULL, &sp24));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1C);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_animated_part(void) {
    S1_Vec3f sp3C;
    s16 var_a3 = 1;
    S1_unk_D_800ABE00_cmd1D* cmd = (S1_unk_D_800ABE00_cmd1D*)D_80126520;

    sp3C.x = cmd->translateX / 65536.0f;
    sp3C.y = cmd->translateY / 65536.0f;
    sp3C.z = cmd->translateZ / 65536.0f;

    if (cmd->flags & 1) {
        var_a3 = 0;
    }

    if (cmd->flags & 2) {
        var_a3 |= 2;
    }

    func_8003FD34(
        GeoNode_CreateAnimatedPart(D_80126450, NULL, cmd->partIndex, var_a3, cmd->animIndex, &cmd->rotationA, &cmd->rotationB, &sp3C));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1D);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_display_list_part(void) {
    S1_unk_D_800ABE00_cmd1E* cmd = (S1_unk_D_800ABE00_cmd1E*)D_80126520;

    func_8003FD34(GeoNode_CreateDisplayListPart(D_80126450, NULL, cmd->partIndex, cmd->displayList, cmd->unk_02));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1E);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_model_part(void) {
    S1_Vec3s sp40;
    S1_Vec3f sp34;
    S1_Vec3f sp28;
    S1_unk_D_86002F58_004_000* tmp;
    S1_unk_D_800ABE00_cmd1F* cmd = (S1_unk_D_800ABE00_cmd1F*)D_80126520;

    Vec3f_FromVec3s(&sp34, &cmd->position);

    sp28.x = cmd->scaleX / 100.0f;
    sp28.y = cmd->scaleY / 100.0f;
    sp28.z = cmd->scaleZ / 100.0f;

    Vec3s_SetComponents(&sp40, (cmd->rotX << 0xF) / 180, (cmd->rotY << 0xF) / 180, (cmd->rotZ << 0xF) / 180);
    tmp = func_80038894(D_80126450, NULL, cmd->modelIndex, &sp34, &sp40, &sp28);
    func_8003FD34(tmp);

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd1F);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80040A9C.s")
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_scale(void) {
    S1_Vec3f sp2C;
    S1_unk_D_86002F34_alt9* tmp;
    S1_unk_D_800ABE00_cmd21* cmd = (S1_unk_D_800ABE00_cmd21*)D_80126520;

    Vec3f_FromVec3s(&sp2C, &cmd->position);
    tmp = GeoNode_CreateScale(D_80126450, NULL, cmd->partIndex, cmd->displayList, &sp2C, cmd->scale / 65536.0f);
    func_8003FD34(tmp);

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd21);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_display_list(void) {
    S1_unk_D_800ABE00_cmd22* cmd = (S1_unk_D_800ABE00_cmd22*)D_80126520;

    func_8003FD34(GeoNode_CreateDisplayList(D_80126450, NULL, cmd->partIndex, cmd->displayList));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd22);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_shadow_texture(void) {
    S1_unk_D_800ABE00_cmd23* cmd = (S1_unk_D_800ABE00_cmd23*)D_80126520;

    func_8003FD34(GeoNode_CreateShadowTexture(D_80126450, NULL, cmd->colorOverrideFlag, cmd->eventFrame, cmd->displayList, cmd->textureIndex1, cmd->textureIndex2,
                                cmd->r, cmd->g, cmd->b, cmd->a));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd23);
}
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_anchor(void) {
    S1_unk_D_800ABE00_cmd24* cmd = (S1_unk_D_800ABE00_cmd24*)D_80126520;

    func_8003FD34(GeoNode_CreateAnchor(D_80126450, NULL, cmd->anchorId));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd24);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80040D9C.s")
#endif

#ifdef VERSION_US
void geo_layout_cmd_create_group(void) {
    S1_unk_D_800ABE00_cmd26* cmd = (S1_unk_D_800ABE00_cmd26*)D_80126520;

    func_8003FD34(GeoNode_CreateGroup(D_80126450, NULL, cmd->unk_01, cmd->unk_04, cmd->unk_06, cmd->unk_08, cmd->unk_0A,
                                cmd->unk_02, cmd->unk_03, cmd->unk_0C, cmd->r, cmd->g, cmd->b, cmd->a));

    D_80126520 += sizeof(S1_unk_D_800ABE00_cmd26);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80040E80.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80040F60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041130.s")
#endif

#ifdef VERSION_US
extern void Yay0_DecompressAndRelocate(u8 *, u8 *);
u8 *func_800411F0(void *arg0, u8 *arg1, s32 arg2, u8 *arg3) {
    u8 *var_a1;
    u8 *sp1C;

    if (arg1 == NULL) {
        var_a1 = MainPool_AllocAligned(arg0, *(u32 *)((u8 *)arg3 + 0x10), 0x10);
    } else {
        var_a1 = arg1;
    }
    if (var_a1 != NULL) {
        sp1C = var_a1;
        Yay0_DecompressAndRelocate(arg3, var_a1);
    }
    return var_a1;
}
#endif

#ifdef VERSION_US
extern void Util_Memcpy(u32 *, const u32 *, s32);
extern void *MainPool_AllocAligned(void *, size_t, s32);
void *func_8004124C(void *arg0, void *arg1, s32 arg2, s32 arg3, u32 arg4) {
    void *var_a0;
    void *sp1C;

    if (arg1 == NULL) {
        var_a0 = MainPool_AllocAligned(arg0, arg4, 0x10);
    } else {
        var_a0 = arg1;
    }
    if (var_a0 != NULL) {
        sp1C = var_a0;
        Util_Memcpy(var_a0, arg2 + arg3, arg4 >> 2);
    }
    return var_a0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800412B0.s")
#endif

#ifdef VERSION_US
#define RELOCATIONS_SIZE 1
typedef struct S1_Fragment S1_Fragment;
struct S1_Fragment {
      u32 inst[2];
      char magic[8];
      u32 headerSize;
      u32 relocOffset;
      u32 sizeInRom;
      u32 sizeInRam;
      char data[RELOCATIONS_SIZE];
};
void func_800413A0(S1_MainPoolState* arg0, u32 arg1, S1_Fragment* arg2) {
    Memmap_RelocateFragment(arg1, arg2);
    MainPool_ResetStateToOffset(arg0, ((u32)arg2 + arg2->sizeInRam) - (u32)arg0->listHeadR);
}
#endif

#ifdef VERSION_US
extern void func_800412B0(s32, s32, s32, s32, s32, s32);
void func_800413E8(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 arg4, s32 arg5) {
    s32 sum1 = arg3[0] + arg2[1];
    s32 sum2 = sum1 + arg3[1];
    func_800412B0(arg0, arg1, sum1, sum2, arg4, arg5);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041430.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041548.s")
#endif

#ifdef VERSION_US
extern void *func_80040E80(S1_MemoryBlock *, void *);
void Fragment_ProcessGeoLayoutList(S1_MemoryBlock* arg0, S1_arg1_func_80019420* arg1) {
    while (arg1->unk_00) {
        if (arg1->unk_00 == 3) {
            arg1->unk_04 = func_80040E80(arg0, arg1->unk_04);
        }

        arg1++;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800416C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041780.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8004186C.s")
#endif

#ifdef VERSION_US
s32 func_80041430(s32, s32, s32, s16, s32, s32);
extern OSThread D_80126530;
void func_8002B1A0(void);
s32 func_80041430(s32, s32, s32, s16, s32, s32);
void func_80041A18(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_80041430(0, (*(s32 *)((u8 *)(arg0) + (0x14))), (*(s32 *)((u8 *)(&D_80126530) + (0x9F8))), (*(s16 *)((u8 *)(arg0) + (2))), (*(s32 *)((u8 *)(&D_80126530) + (0x9FC))), 0xF000);
    if (temp_v0 != 0) {
        (*(s32 *)((u8 *)(arg0) + (0xC))) = temp_v0;
        return;
    }
    (*(s32 *)((u8 *)(arg0) + (0xC))) = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041A78.s")
#endif

#ifdef VERSION_US
void func_80041A78(void *);
extern void *D_80126EE0;
extern OSMesgQueue D_80126F00;
void func_80041B84(void) {
    osCreateMesgQueue(&D_80126F00, &D_80126EE0, 8);
    osCreateThread(&D_80126530, 7, func_80041A78, NULL, &D_80126EE0, 0xA);
    osStartThread(&D_80126530);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041BF0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041C98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041D84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041E2C.s")
#endif

#ifdef VERSION_US
s32 main_pool_alloc(s32, s32);
s32 BinArchive_Open(s32, s32, s32, s32);
extern s32 D_80126F28;
extern s32 D_80126F2C;
void func_80041F14(void) {
    D_80126F28 = BinArchive_Open(func_800356CC(8), 0, 1, 1);
    D_80126F2C = main_pool_alloc(0xF000, 1);
}
#endif

#ifdef VERSION_US
extern s16 D_8009F428[];
s32 func_80041F60(s16 *arg0) {
    s16 *ptr = D_8009F428;
    s32 result = 0;
    while (*ptr != -1) {
        if (ptr == arg0) {
            result = 1;
        }
        ptr++;
    }
    return result;
}
#endif

#ifdef VERSION_US
typedef union { s32 word; s8 bytes[4]; } Func80041FA0State;
typedef Func80041FA0State Func80041FA0Packed;
extern s32 func_80041FD0(s32, u16, Func80041FA0State, s32);
void func_80041FA0(s32 arg0, u16 arg1, Func80041FA0State arg2) {
    func_80041FD0(arg0, arg1, arg2, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80041FD0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800421E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800422B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_8004239C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80042484.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800425C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800427B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80042808.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_80042858.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800428A8.s")
#endif

#ifdef VERSION_US
extern void func_800425C0(s32, void *);

void func_800428F8(s32 arg0) {
    void *sp1C;

    osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0x50), &sp1C, 1);
    func_800425C0(arg0, sp1C);
}
#endif

#ifdef VERSION_US

void PokeIcon_WaitBackgroundLoad(s32 arg0) {
    void *sp1C;

    osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0x70), &sp1C, 1);
    func_800425C0(arg0, sp1C);
}
#endif

#ifdef VERSION_US

void func_80042968(s32 arg0) {
    void *sp1C;

    osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0x90), &sp1C, 1);
    func_800425C0(arg0, sp1C);
}
#endif

#ifdef VERSION_US

void func_800429A0(s32 arg0) {
    void *sp1C;

    osRecvMesg((OSMesgQueue *)(u32)(arg0 + 0xB0), &sp1C, 1);
    func_800425C0(arg0, sp1C);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/229E0/func_800429D8.s")
#endif

#ifdef VERSION_US
s32 func_80042A64(s32 arg0) { return 0; }
#endif

#ifdef VERSION_US
extern void *func_80004B4C(void *arg0, s32 arg1);
extern S1_MemoryBlock *MainPool_AllocState(s32 arg0, s32 arg1);
extern s32 main_pool_get_available(void);
extern void MainPool_FinalizeAllocation(S1_MemoryBlock *arg0);
extern s32 D_80126F24;
S1_arg1_func_80019420 *BattleAnim_LoadResourceTable(s32 arg0) {
    s32 sp24;
    S1_arg1_func_80019420 *sp20;
    S1_MemoryBlock *sp1C;
    sp20 = NULL;
    sp24 = (s32)func_80004B4C((void *)D_80126F24, arg0);
    if (sp24 != 0) {
        sp1C = MainPool_AllocState(main_pool_get_available(), 0);
        sp20 = (S1_arg1_func_80019420 *)(sp24 + 0x20);
        Fragment_ProcessGeoLayoutList(sp1C, sp20);
        MainPool_FinalizeAllocation(sp1C);
    }
    return sp20;
}
#endif

#ifdef VERSION_US
s32 func_80042ADC(u8 *arg0) { s32 result = -1; if (arg0 != NULL) result = arg0[2] & 0xF; return result; }
#endif
