#include "global.h"


#ifdef VERSION_US
extern Gfx* D_800D0510;
void ParticleGfx_SetPrimColor_fragment83(u8 r, u8 g, u8 b, u8 a) {
    gDPSetPrimColor(D_800D0510++, 0, 0, r, g, b, a);
}
#endif

#ifdef VERSION_US
void func_82C00078(u8 *arg0, u8 arg1) {
    ParticleGfx_SetPrimColor_fragment83(arg0[0], arg0[1], arg0[2], arg1);
}
#endif

#ifdef VERSION_US
void func_82C000B0(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    gDPPipeSync(D_800D0510++);
    gDPSetFillColor(D_800D0510++, (((((arg0 << 8) & 0xF800) | ((arg1 << 3) & 0x7C0) | ((arg2 >> 2) & 0x3E) | (arg3 & 1)) << 16) |
        (((arg0 << 8) & 0xF800) | ((arg1 << 3) & 0x7C0) | ((arg2 >> 2) & 0x3E) | (arg3 & 1))));
}
#endif

#ifdef VERSION_US
extern void func_82C000B0(u16, u16, u16, u16);
void func_82C0012C(s32 arg0) {
    if (arg0 != 0) {
        u8 *value = (u8 *)(u32)arg0;
        func_82C000B0(value[0], value[1], value[2], 1);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00164.s")
#endif

#ifdef VERSION_US
extern void func_82C00164(s32, s32, s32, s32);
void func_82C002B8(u8 *arg0) {
    func_82C00164(*(s16 *)(arg0 + 0), *(s16 *)(arg0 + 2), *(u16 *)(arg0 + 4), *(u16 *)(arg0 + 6));
}
#endif

#ifdef VERSION_US
void func_82C002EC(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    s32 right = (arg0 + arg2) - 1;
    s32 bottom = (arg1 + arg3) - 1;

    gDPScisFillRectangle(D_800D0510++, arg0, arg1, right, bottom);
}
#endif

void func_82C003B4(void) {
}

#ifdef VERSION_US
extern void *func_8004C990(s32, s32);
extern void func_8004D1FC(void *);
void func_82C003BC(u16 arg0, u16 arg1) {
    void *value = func_8004C990(arg0, arg1);
    func_8004D1FC(value);
}
#endif

#ifdef VERSION_US
extern void func_8004D19C(s32, s32, void *, s32, s32);
void func_82C003F8(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    void *value = func_8004C990(arg2, arg3);
    func_8004D19C(arg0, arg1, value, 0, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00444.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00624.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00804.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C008BC.s")
#endif

#ifdef VERSION_US
extern void func_82C00624(s16, s16, u16, u16);
extern void func_82C00804(s16, s16, s32, s32);
void func_82C009F8(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    func_82C00804((s16) (arg0 + 3), (s16) (arg1 + 3), (arg2 - 6) & 0xFFFF, (arg3 - 6) & 0xFFFF);
    func_82C00624(arg0, arg1, arg2, arg3);
}
#endif

#ifdef VERSION_US
extern void func_82C008BC(s16, s16, s32, s32);
void func_82C00A70(s16 arg0, s16 arg1, u16 arg2, u16 arg3) {
    func_82C008BC((s16) (arg0 + 3), (s16) (arg1 + 3), (arg2 - 5) & 0xFFFF, (arg3 - 6) & 0xFFFF);
    func_82C00624(arg0, arg1, arg2, arg3);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00AE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00C78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C00F20.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C019B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C01C38.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C01E24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C01E98.s")
#endif

#ifdef VERSION_US
extern u8 D_82C04C39;
extern s16 D_82C04C44;
extern s16 D_82C04C46;
extern u8 D_80094E38[];
extern void func_82C003F8(s16 arg0, s16 arg1, u16 arg2, u16 arg3);
void func_82C01FE4(void) {
    if ((D_82C04C39 == 1) || (D_82C04C39 == 2) || (D_82C04C39 == 4)) {
        gSPDisplayList(D_800D0510++, D_80094E38);
        func_82C003F8((s16)(D_82C04C44 + 0x14), (s16)(D_82C04C46 + 0x13D), 0x33, 0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02078.s")
#endif

#ifdef VERSION_US
extern void func_80008648();
extern void func_800088DC();
extern void func_82C00C78();
extern void func_82C00F20();
extern void func_82C019B4();
extern void func_82C01C38();
extern void func_82C01E24();
extern void func_82C01E98();
extern void func_82C01FE4();
extern void func_82C02078();
void func_82C02328(void) {
    func_800088DC();
    func_82C00C78();
    func_82C00F20();
    func_82C019B4();
    func_82C01E24();
    func_82C01E98();
    func_82C01FE4();
    func_82C02078();
    func_82C01C38();
    func_80008648();
}
#endif

#ifdef VERSION_US
extern u8 D_82C04A14;
extern s8 D_82C04C42;
void func_82C02390(void *arg0, void *arg1, s8 arg2) {
    u8 factor;

    if (arg2 > 0) {
        factor = ((D_82C04A14 - D_82C04C42) + 1) & 0xFF;
    } else {
        factor = (u8)D_82C04C42;
    }
    *(s16 *)((u8 *)arg0 + 6) = (s16)((*(s16 *)((u8 *)arg1 + 6) * factor) / (s32)D_82C04A14);
    *(s16 *)((u8 *)arg0 + 2) = (s16)(((*(s16 *)((u8 *)arg1 + 6) - *(s16 *)((u8 *)arg0 + 6)) / 2) +
        *(s16 *)((u8 *)arg1 + 2));
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02440.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02664.s")
#endif

#ifdef VERSION_US
extern s32 func_82C02664(u8 *, u8);
s32 func_82C026D4(s32 arg0) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 1; i != 0xFC; i++) {
        if (func_82C02664((u8 *) arg0, i) != 0) {
            count++;
        }
    }
    return count & 0xFFFF;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0273C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02834.s")
#endif

#ifdef VERSION_US
extern void func_82C02834(s32);
extern u8 D_82C04C38;

void func_82C02950(void) {
    (*(s8 *)((u8 *)(&D_82C04C38) + (0x124A))) = 0;
    (*(s8 *)((u8 *)(&D_82C04C38) + (0x124B))) = 0;
    (*(s16 *)((u8 *)(&D_82C04C38) + (0x1250))) = 0;
    (*(s8 *)((u8 *)(&D_82C04C38) + (0x1249))) = 1;
    func_82C02834(1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0298C.s")
#endif

#ifdef VERSION_US
extern u16 D_82C04C34;
extern u16 D_82C04C32;
extern u8 D_82C04C38;
extern void func_82C0298C(void);
extern void func_800226C0(s32);
void func_82C02A44(void) {
    if (D_82C04C34 & 0x800) {
        *(s8 *)((u8 *)&D_82C04C38 + 2) = *(s8 *)((u8 *)&D_82C04C38 + 2) - 1;
        if (*(s8 *)((u8 *)&D_82C04C38 + 2) < 0) {
            *(s8 *)((u8 *)&D_82C04C38 + 2) = *(u8 *)((u8 *)&D_82C04C38 + 3) - 1;
        }
        func_800226C0(1);
    } else if (D_82C04C34 & 0x400) {
        *(s8 *)((u8 *)&D_82C04C38 + 2) = *(s8 *)((u8 *)&D_82C04C38 + 2) + 1;
        if (*(s8 *)((u8 *)&D_82C04C38 + 2) > *(u8 *)((u8 *)&D_82C04C38 + 3) - 1) {
            *(s8 *)((u8 *)&D_82C04C38 + 2) = 0;
        }
        func_800226C0(1);
    }
    if (D_82C04C32 & 0x8000) {
        func_82C0298C();
        return;
    }
    if (D_82C04C32 & 0x4000) {
        *(u8 *)((u8 *)&D_82C04C38 + 1) = 9;
        func_800226C0(3);
    }
}
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
extern u8 D_82C04A14;
extern u16 D_82C04C32;
void func_82C02B30(void) {
    if (!(D_82C04C32 & 0x8000) && (D_82C04C32 & 0x4000)) {
        (*(s8 *)((u8 *)(&D_82C04C38) + (1))) = 4;
        (*(u8 *)((u8 *)(&D_82C04C38) + (0xA))) = (u8) D_82C04A14;
        func_800226C0(3);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C02B84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03134.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0329C.s")
#endif

#ifdef VERSION_US
extern void func_82C02A44();
extern void func_82C0329C();
extern u8 D_82C04C39;
void func_82C033E4(void) {
    switch (D_82C04C39) {                           /* irregular */
    case 1:
        func_82C02A44();
        return;
    case 3:
        func_82C02B30();
        return;
    case 6:
        func_82C0329C();
        return;
    }
}
#endif

#ifdef VERSION_US
extern void *D_80087200;
extern u8 D_82C04A10;
extern u16 D_82C04C30;
extern u16 D_82C04C34;
void func_82C03450(void) {
    func_80064D28();
    if (D_82C04A10 != 0) {
        D_82C04C30 = (*(u16 *)((u8 *)(D_80087200) + (6)));
        D_82C04C32 = (*(u16 *)((u8 *)(D_80087200) + (8)));
        D_82C04C34 = (*(u16 *)((u8 *)(D_80087200) + (0xC)));
        return;
    }
    D_82C04C30 = 0;
    D_82C04C32 = 0;
    D_82C04C34 = 0;
}
#endif

#ifdef VERSION_US
extern void func_82C02440();
extern void func_82C033E4();
extern void func_82C03450();
void func_82C034C8(void) {
    do {
        func_82C03450();
        func_82C033E4();
        func_82C02440();
        func_82C02328();
    } while ((*(u8 *)((u8 *)(&D_82C04C38) + (1))) != 9);
}
#endif

#ifdef VERSION_US
extern void func_8004C8C0(s32);
void func_82C03524(void) { func_8004C8C0(0x101); func_8004C8C0(0x102); func_8004C8C0(0x33); func_8004C8C0(0x79); func_8004C8C0(0x1B); func_8004C8C0(0x1C); func_8004C8C0(0x123); }
#endif

#ifdef VERSION_US
extern void func_8004C4B0();
void func_82C03574(void) { func_8004C4B0(21); func_8004C4B0(19); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0359C.s")
#endif

#ifdef VERSION_US
extern s8 *HAL_Strcpy(s8 *, s8 *);
extern s8 *func_8004C874(s32, s32);
s32 func_82C03674(s32 arg0, s32 arg1, void *arg2) {
    s32 var_v1;

    var_v1 = 0;
    if ((*(s16 *)((u8 *)(arg2) + (0x34))) == 0) {
        HAL_Strcpy(arg0 + 4, func_8004C874(0x15, 6));
        HAL_Strcpy(arg0 + 0x54, func_8004C874(0x15, 0x1E));
        var_v1 = 1;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C036E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0383C.s")
#endif

#ifdef VERSION_US
s32 func_82C03904(s32 arg0, s32 arg1, void *arg2) {
    s32 var_v1;

    var_v1 = 0;
    if ((*(s16 *)((u8 *)(arg2) + (0x34))) == 5) {
        HAL_Strcpy(arg0 + 4, func_8004C874(0x15, 0x19));
        HAL_Strcpy(arg0 + 0x54, func_8004C874(0x15, 0x36));
        var_v1 = 1;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03974.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03CA8.s")
#endif

#ifdef VERSION_US
s32 func_82C03D50(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1;

    var_v1 = 0;
    if ((arg1 & 0xFF00) == 0x300) {
        HAL_Strcpy(arg0 + 4, func_8004C874(0x15, 0xC));
        HAL_Strcpy(arg0 + 0x54, func_8004C874(0x15, 0x27));
        var_v1 = 1;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03DC0.s")
#endif

#ifdef VERSION_US
s32 func_82C03EE0(s8 *arg0, s32 arg1, s32 arg2) {
    HAL_Strcpy(arg0 + 4, func_8004C874(0x15, 7));
    HAL_Strcpy(arg0 + 0x54, func_8004C874(0x15, 0x20));
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C03F40.s")
#endif

#ifdef VERSION_US
extern s8 * func_8004C874(s32, s32);
s32 func_82C03FB4(s32 arg0, s32 arg1, void *arg2) {
    HAL_Strcpy(arg0 + 4, func_8004C874(0x15, 0x10));
    if ((arg1 & 0xFF00) != 0x200 || (*(s16 *)((u8 *)arg2 + 0x34)) == 5) {
        HAL_Strcpy(arg0 + 0x54, func_8004C874(0x15, 0x2B));
    } else {
        HAL_Strcpy(arg0 + 0x54, func_8004C874(0x15, 0x3C));
    }
    return 1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0405C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0412C.s")
#endif

#ifdef VERSION_US
s32 func_82C041CC(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1;

    var_v1 = 0;
    if ((arg1 & 0xFF00) == 0x100) {
        HAL_Strcpy(arg0 + 4, func_8004C874(0x15, 0x1B));
        HAL_Strcpy(arg0 + 0x54, func_8004C874(0x15, 0x39));
        var_v1 = 1;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0423C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C04350.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C0458C.s")
#endif

#ifdef VERSION_US
extern void func_8004C594(s32, s32);
extern void func_8004C8A0(s32 *, s32, s32, s32);
s32 func_82C026D4(s32);
extern s32 D_82C04C50;
extern u8 D_82C05E90;
void func_82C04778(void) {
    func_8004C594(3, func_82C026D4(D_82C04C50 + 0x14));
    func_8004C8A0(&D_82C05E90, 0x3C, 0x15, 4);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C047C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/83/fragment83_code/func_82C04880.s")
#endif
