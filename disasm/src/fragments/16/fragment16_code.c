#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000098.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000100.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_820001F0.s")
#endif

#ifdef VERSION_US
extern s16 D_82001D58;
extern void func_800468A0(s32);
extern void func_820001F0(s16 *);
void func_820006B8(void) {
    s16 *base = &D_82001D58;
    s32 *table = (s32 *)((u8 *)base + 8);
    func_800468A0(table[*(s16 *)((u8 *)base + 4)]);
    if (*base == 1) {
        func_820001F0(base);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_8200070C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000794.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000C00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000CB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000CE0.s")
#endif

#ifdef VERSION_US
s32 func_82000D10(s32 arg0, u8 *arg1) {
    if (arg0 == 0) {
        arg1[0x28] = 0x21;
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern u8 D_82001EB8;
extern s16 D_82001EBC;
extern s16 D_82001EBE;

s32 func_82000D24(s32 arg0, void *arg1) {
    if (arg0 == 0) {
        (*(s16 *)((u8 *)(&D_82001EB8) + (0))) = (s16) (*(s16 *)((u8 *)(arg1) + (8)));
        (*(s16 *)((u8 *)(&D_82001EB8) + (2))) = (s16) (*(s16 *)((u8 *)(arg1) + (0xA)));
        D_82001EBC = (*(s16 *)((u8 *)(arg1) + (0xC)));
        D_82001EBE = (*(s16 *)((u8 *)(arg1) + (0xE)));
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern s16 D_82001EC0;

s32 func_82000D64(s32 arg0, void *arg1) {
    if (arg0 == 0) {
        D_82001EC0 = (*(s16 *)((u8 *)(arg1) + (0xA)));
    }
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_82000D80(s32 arg0, void *arg1) {
    switch (arg0) {                                 /* irregular */
    case 1:
        break;
    case 0:
        if (func_800033A8() != 0) {
            (*(u16 *)((u8 *)(arg1) + (2))) = (u16) ((*(u16 *)((u8 *)(arg1) + (2))) | 2);
        } else {
            (*(u16 *)((u8 *)(arg1) + (2))) = (u16) ((*(u16 *)((u8 *)(arg1) + (2))) & 0xFFFD);
        }
        break;
    }
    return 0;
}
#endif

void func_82000DE0(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000DE8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82000FB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_820010BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_820011D8.s")
#endif

#ifdef VERSION_US
extern void func_800498C4();
extern void func_800499EC();
extern void func_82000FB0();
extern s32 D_82001CD4;

void func_82001304(void) {
    func_800498C4();
    if (D_82001CD4 != 0) {
        func_82000FB0();
    }
    func_800499EC();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82001344.s")
#endif

#ifdef VERSION_US
extern void *D_82001CD0;
extern s32 D_82001EC4;
extern s32 D_82001EC8;
extern void *D_80087200;
extern s32 func_8006D268(s32);
extern void func_800088DC(void);
extern void func_800503A4(void *);
extern void func_82000C00(void);
extern void func_82001344(void);
extern void func_820010BC(void);
extern void func_820011D8(void);
extern void func_82001304(void);
extern void func_80008648(void);
extern void func_820006B8(void);
void func_820014C4(void) {
    func_800088DC();
    if (func_8006D268(0x202) != 0 && ((*(u16 *)((u8 *)(u32)D_80087200 + 8)) & 4) != 0) {
        (*(s16 *)((u8 *)&D_82001D58 + 4)) =
            (s16)((*(s16 *)((u8 *)&D_82001D58 + 4) + 1) % 3);
    }
    func_820006B8();
    func_800503A4(D_82001CD0);
    func_82000C00();
    func_82001344();
    if (D_82001EC4 != 0) {
        func_820010BC();
    }
    if (D_82001EC8 != 0) {
        func_820011D8();
    }
    func_82001304();
    func_80008648();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82001590.s")
#endif

#ifdef VERSION_US
extern void *D_80087200;
extern s32 func_80025D44(void);
extern s32 func_8006D268(s32);
s32 func_82001688(void) {
    s32 result = 0;
    if (func_80025D44() == 0) {
        result = 1;
    } else if (func_8006D268(0x201) != 0 && ((*(u16 *)((u8 *)(u32)D_80087200 + 8)) & 2) != 0) {
        result = 1;
    }
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_820016EC.s")
#endif

#ifdef VERSION_US
extern s16 D_82001D58;
s32 func_8200180C(void) {
    s32 result = 0;
    if (D_82001D58 == 0) result = 1;
    return result;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_8200182C.s")
#endif

#ifdef VERSION_US
extern void func_82000100();
extern void func_82000794();
extern void func_820014C4();
s32 func_8200182C(s32);
extern s32 D_82001D50;
void func_820019EC(void) {
    s32 temp_v0;
    s32 var_s1;

    var_s1 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(0xA);
    do {
        func_80064D28();
        func_82000100();
        func_82000794();
        func_820014C4();
        if (D_82001D50 != 0) {
            D_82001D50 -= 1;
        }
        temp_v0 = func_8200182C(var_s1);
        var_s1 = temp_v0;
    } while (temp_v0 != 6);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82001A78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/16/fragment16_code/func_82001ADC.s")
#endif
