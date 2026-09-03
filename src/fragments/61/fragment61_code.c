#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B00020.s")
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_86B000F0(s32 arg0, void *arg1) {
    s16 pad;
    s32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &sp28, &sp26, &sp24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(sp26 + 0x2000);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(sp24 - 0x2000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_86B00158(s32 arg0, void *arg1) {
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
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B001C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B007D0.s")
#endif

#ifdef VERSION_US
extern s32 D_86B0D160; extern s32 D_86B0D164; extern void *D_86B0E0A8; extern u8 *D_86B181C0; extern s32 func_87F08208(void *); extern void StageContext_SetClearColor(s32); extern void StageFade_StartFromTransparent(s32); extern void func_800225C4(s32); extern void func_800279C4(s32); extern void func_800226C0(s32); extern void func_86B01720(s32);
void func_86B00994(void) {
    s32 temp_v0;
    D_86B0D164 = 0;
    temp_v0 = func_87F08208(&D_86B0E0A8);
    switch (temp_v0) {
    case 1:
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(0x14);
        *(s32 *)D_86B181C0 = 2;
        func_800225C4(0x28);
        func_800279C4(0xCF0B);
        D_86B0D160 = 0;
        return;
    case 2:
        func_86B01720(0);
        func_800226C0(3);
        D_86B0D160 = 1;
        return;
    }
}
void func_86B00994_padding(void) {}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B00A3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B014E8.s")
#endif

#ifdef VERSION_US
extern u8 *D_86B181C0;
extern void StageContext_SetClearColor(s32);
extern void StageFade_StartFromTransparent(s32);
void func_86B01720(s32 arg0) {
    *(s32 *)(D_86B181C0 + 0x18) = arg0;
    *(s32 *)D_86B181C0 = 0xC;
    *(s32 *)(D_86B181C0 + 4) = 0xD;
    StageContext_SetClearColor((u16)0xFFFF);
    StageFade_StartFromTransparent(0xA);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B01770.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B01A94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B02180.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B021E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B023FC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B03228.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0355C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B03628.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B04500.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B04870.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B04970.s")
#endif

#ifdef VERSION_US
extern void *D_87F119DC;
extern s32 D_87F119D8;
extern void func_87F026E8(s32, void *);
extern void func_86B052BC(s32);
void func_86B05194(void) {
    s32 result;
    s32 value;
    s32 state_value;

    result = 0;
    value = *(s32 *)((u8 *)D_87F119DC + 0x20);
    switch (value) {
    case 0:
        state_value = *(s32 *)((u8 *)D_87F119DC + 0x1C);
        if (state_value == 0) {
            func_86B052BC(1);
            state_value = *(s32 *)((u8 *)D_87F119DC + 0x1C);
        }
        if (state_value == 2) {
            func_86B052BC(1);
            state_value = *(s32 *)((u8 *)D_87F119DC + 0x1C);
        }
        if (state_value == 4) {
            func_86B052BC(1);
            state_value = *(s32 *)((u8 *)D_87F119DC + 0x1C);
        }
        if (state_value == 6) {
            func_86B052BC(1);
            state_value = *(s32 *)((u8 *)D_87F119DC + 0x1C);
        }
        if (state_value == 8) {
            func_86B052BC(1);
            state_value = *(s32 *)((u8 *)D_87F119DC + 0x1C);
        }
        if (state_value >= 9) {
            result = 1;
        }
        break;
    case 1:
        if (*(s32 *)((u8 *)D_87F119DC + 0x1C) >= 8) {
            result = 1;
        }
        break;
    }
    if (result != 0) {
        func_87F026E8(D_87F119D8, D_87F119DC);
    }
}
#endif

#ifdef VERSION_US
extern void func_86B05194(void);
extern u8 *func_87F025B8(u8 *, void (*)(void));
extern void func_8003F1DC(u8 *);
extern void func_8003F114(u8 *, s32, s32, s32);
extern void func_8003F210(u8 *, s32);
extern u8 D_86B12AD0;
extern f32 D_80087E50[];
extern f32 D_80088E50[];
extern f32 D_86B0D17C;
extern f32 D_86B0D178;
extern f64 D_86B0DDE0;
extern s32 D_86B0E19C;
extern s32 D_86B0E1A0;
void func_86B052BC(s32 arg0) {
    u8 *object;
    u8 *base;
    f32 scale;
    f32 factor;
    s32 index;

    object = func_87F025B8(&D_86B12AD0, func_86B05194);
    if (object != NULL) {
        *(s32 *)(object + 0x1C) = 0;
        *(f32 *)(object + 0x48) = 0.0f;
        *(f32 *)(object + 0x4C) = 0.0f;
        *(f32 *)(object + 0x50) = 0.0f;
        base = object + 0x24;
        *(s32 *)(object + 0x20) = arg0;
        scale = (f32)((f64)D_86B0D178 * D_86B0DDE0);
        *(f32 *)(object + 0x5C) = scale;
        *(f32 *)(object + 0x58) = scale;
        *(f32 *)(object + 0x54) = scale;
        func_8003F1DC(base);
        switch (arg0) {
        case 0:
            func_8003F114(base, 0, -1, D_86B0E19C);
            func_8003F210(base, 0);
            break;
        case 1:
            index = ((guRandom() % 65535) & 0xFFFF) >> 4;
            factor = 45.0f * D_86B0D17C;
            *(f32 *)(object + 0x48) = D_80088E50[index] * factor;
            *(f32 *)(object + 0x4C) = D_80087E50[index] * factor;
            *(f32 *)(object + 0x50) = 0.0f;
            func_8003F114(base, 0, -1, D_86B0E1A0);
            func_8003F210(base, 0);
            break;
        }
    }
}
#endif

#ifdef VERSION_US
extern void func_87F026E8(s32, void *);
extern s32 D_87F119D8;
extern void *D_87F119DC;
void func_86B05428(void) {
    s32 var_v0;

    var_v0 = 0;
    (*(s8 *)((u8 *)(D_87F119DC) + (0x41))) = (s8) (*(s32 *)((u8 *)(D_87F119DC) + (0x20)));
    if ((*(s32 *)((u8 *)(D_87F119DC) + (0x1C))) >= 0x18) {
        var_v0 = 1;
    }
    if (var_v0 != 0) {
        func_87F026E8(D_87F119D8, D_87F119DC);
    }
}
#endif

#ifdef VERSION_US
extern u8 *func_87F025B8(u8 *, void (*)(void));
extern void func_8003F1DC(u8 *);
extern void func_8003F114(u8 *, s32, s32, s32);
extern void func_8003F210(u8 *, s32);
extern f32 D_86B0D178;
extern f64 D_86B0DDE8;
extern s32 D_86B0E1A4;
extern u8 D_86B13A68;
extern void func_86B05428(void);
void func_86B05484(f32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    u8 *object;
    u8 *base;
    f32 scale;

    object = func_87F025B8(&D_86B13A68, func_86B05428);
    if (object != NULL) {
        *(s32 *)(object + 0x1C) = 0;
        scale = (f32)((f64)D_86B0D178 * D_86B0DDE8);
        *(f32 *)(object + 0x5C) = scale;
        *(f32 *)(object + 0x58) = scale;
        *(f32 *)(object + 0x54) = scale;
        base = object + 0x24;
        func_8003F1DC(base);
        *(f32 *)(object + 0x48) = arg0;
        *(f32 *)(object + 0x4C) = arg1;
        *(f32 *)(object + 0x50) = arg2;
        *(s32 *)(object + 0x20) = arg3;
        func_8003F114(base, 0, -1, D_86B0E1A4);
        func_8003F210(base, 0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B05548.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B05610.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B05738.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B057B0.s")
#endif

#ifdef VERSION_US
s16 MathUtil_Atan2s(f32 y, f32 x);
s16 func_86B07D58(f32 arg0, f32 arg1) {
    return (s16) ((s32) (MathUtil_Atan2s(arg0, -arg1) + 0x3FFF) % 65535);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B07D94.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B07FB0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08088.s")
#endif

#ifdef VERSION_US
extern f32 D_86B0DFA8;
extern f64 D_86B0DFB0;
f32 func_86B080D4(f32 arg0, f32 arg1) {
    f32 var_fv1;

    if (arg1 <= arg0) {
        var_fv1 = arg0 - arg1;
    } else {
        var_fv1 = arg1 - arg0;
    }
    if (D_86B0DFA8 < var_fv1) {
        var_fv1 = (f32) (D_86B0DFB0 - (f64) var_fv1);
    }
    return var_fv1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08120.s")
#endif

#ifdef VERSION_US
extern void func_87F0277C(s32 *);
extern u8 D_86B0E1A8;
extern u8 D_86B0E7F8;
extern u8 D_86B0E9A0;
extern u8 D_86B0EE60;
extern u8 D_86B12AD0;
extern u8 D_86B13A68;
void func_86B081B4(void) {
    func_87F0277C(&D_86B0E9A0);
    func_87F0277C(&D_86B0EE60);
    func_87F0277C(&D_86B12AD0);
    func_87F0277C(&D_86B13A68);
    func_87F0277C(&D_86B0E1A8);
    func_87F0277C(&D_86B0E7F8);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08214.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08978.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08B74.s")
#endif

void func_86B08CEC(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08CF4.s")
#endif

void func_86B08E08(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08E10.s")
#endif

void func_86B08F18(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B08F20.s")
#endif

void func_86B09378(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B09380.s")
#endif

void func_86B09478(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B09480.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0952C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B095B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B09834.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0990C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0B04C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0B500.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0B608.s")
#endif

#ifdef VERSION_US
extern Gfx *D_800D0510;
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void func_8003CD84(void);
extern s32 D_86B0E7F4;
void func_86B0B6CC(s32 arg0, s32 arg1) {
    s32 pad[2];
    s32 temp_v0;
    if (arg0 == 5) {
        temp_v0 = func_8004C990(0x133, 0);
        gDPPipeSync(D_800D0510++);
        gDPSetEnvColor(D_800D0510++, 0, 0, 0, 0x80);
        gDPSetCombine(D_800D0510++, 0xFCFFD3FF, 0xFFFEFE38);
        gSPSegment(D_800D0510++, 0xF, func_8004CA60((u8 *)temp_v0));
        gSPDisplayList(D_800D0510++, D_86B0E7F4);
        func_8003CD84();
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0B7B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0B9A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0BA28.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0BB24.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0BF2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/61/fragment61_code/func_86B0CB1C.s")
#endif
