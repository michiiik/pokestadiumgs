#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B00E10.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B00E34.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B00EA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B00F14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B00F68.s")
#endif

#ifdef VERSION_US
void *func_82B00F14(s32);

void func_82B01054(s32 arg0) {
    void *temp_v0;

    temp_v0 = func_82B00F14(0x46554C4C);
    if (temp_v0 != NULL) {
        (*(s16 *)((u8 *)(temp_v0) + (4))) = (s16) arg0;
    }
}
#endif

#ifdef VERSION_US
void *func_82B00F14(s32);

s16 func_82B01088(void) {
    s16 var_v1;
    void *temp_v0;

    temp_v0 = func_82B00F14(0x46554C4C);
    var_v1 = 0;
    if (temp_v0 != NULL) {
        var_v1 = (*(s16 *)((u8 *)(temp_v0) + (4)));
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B010BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B01130.s")
#endif

#ifdef VERSION_US
extern s32 D_82B12674;
s32 func_82B011C0(s32 arg0, s32 arg1) {
    s32 var_a2;
    s32 var_v1;
    var_a2 = -1;
    var_v1 = 0;
    switch (arg0) {
    case 0: var_a2 = 0xC; break;
    case 1: var_a2 = 0xA; break;
    case 2: var_a2 = 0; break;
    case 4: var_a2 = -2; break;
    }
    if (var_a2 >= 0) var_v1 = func_800718B8(var_a2);
    else if (var_a2 == -2) var_v1 = ((s32 *)&D_82B12674)[arg1];
    return var_v1;
}
#endif

#ifdef VERSION_US
s32 func_82B01254(void *arg0, s32 arg1) {
    s32 var_v1;

    if (arg0 != NULL) {
        var_v1 = arg1 >= (s32) (*(u8 *)((u8 *)(arg0) + (0x36)));
        if (var_v1 != 0) {
            var_v1 = (s32) (*(u8 *)((u8 *)(arg0) + (0x37))) >= arg1;
        }
        return var_v1;
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B0128C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B0173C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B01850.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B018CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B01904.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B01BB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B01CE0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B01E0C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B01F14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B0201C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02198.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02334.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B024B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B025E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B026E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02800.s")
#endif

#ifdef VERSION_US
void func_82B0284C(u8 *arg0, u8 *arg1) {
    *(s16 *)(arg1 + 0) = *(s16 *)(arg0 + 0x10) + *(s16 *)(arg0 + 0xC);
    *(s16 *)(arg1 + 2) = *(s16 *)(arg0 + 0x12) + *(s16 *)(arg0 + 0xE);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02870.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B028CC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02924.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B029B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02A34.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02ABC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02BA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02CA0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02D84.s")
#endif

#ifdef VERSION_US
extern void func_82B02ABC(void *);
extern void func_82B02BA4(void *);
extern void func_82B02CA0(void *);
extern void func_82B02D84(void *);
void func_82B02E50(void *arg0) {
    u16 temp_v0;

    temp_v0 = (*(u16 *)((u8 *)(arg0) + (6)));
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82B02ABC(arg0);
        break;
    case 3:
        func_82B02BA4(arg0);
        break;
    case 4:
        func_82B02CA0(arg0);
        break;
    }
    if ((*(s16 *)((u8 *)(arg0) + (0))) == 3) {
        func_82B02D84(arg0);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02EDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B02F78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B0341C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B03538.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B03688.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B0373C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B038BC.s")
#endif

#ifdef VERSION_US
extern s32 func_8004C990(s32, s32);
extern void func_8004B35C(s32, s32, s32, s32, s32);
void func_82B03934(s32 arg0, s32 arg1) { s32 temp = func_8004C990(0x156, 0); func_8004B35C(arg0, arg1, 0x78, 0x20, temp); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B03978.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B03F38.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B04008.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B041C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B042D8.s")
#endif

#ifdef VERSION_US
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800495F8(s32, s32, s32, s32);
extern u8 D_82B085CC[];
extern u8 D_82B085D0[];
void func_82B04430(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_a3;
    u8 *var_v0;
    if (arg3 & 5) {
        var_a3 = arg4;
        var_v0 = &D_82B085D0;
    } else {
        var_a3 = 0xFF;
        var_v0 = &D_82B085CC;
    }
    func_800496A4(4, 0);
    func_8004972C(var_v0[0], var_v0[1], var_v0[2], var_a3);
    func_800495F8(arg0, arg1, 0, arg2);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B044B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B04558.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B04624.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B04718.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B0504C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B050E8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B05494.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B0556C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B055A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B0560C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B05654.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B05920.s")
#endif

#ifdef VERSION_US
extern void func_82B06360(s32);
extern void func_82B060A0(s32);
void func_82B05E3C(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 2:
        func_82B060A0(1);
        return;
    case 6:
        func_82B06360(0);
        /* fallthrough */
    case 3:
    case 4:
        return;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B05E98.s")
#endif

#ifdef VERSION_US
void *func_82B02800(s32, s32);

void func_82B05EF0(s32 arg0, s32 arg1, u16 arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *temp_v0;

    if ((arg0 >= 0) && (arg0 < 2)) {
        temp_v0 = func_82B02800(8, arg0);
        if (temp_v0 != NULL) {
            (*(s32 *)((u8 *)(temp_v0) + (0x50))) = arg1;
            (*(u16 *)((u8 *)(temp_v0) + (0x54))) = arg2;
            (*(s16 *)((u8 *)(temp_v0) + (0x56))) = (s16) arg3;
            (*(s32 *)((u8 *)(temp_v0) + (0x58))) = arg4;
            (*(s32 *)((u8 *)(temp_v0) + (0x5C))) = arg5;
        }
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B05F60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B060A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B062BC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B062F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B06360.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B0671C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B06C98.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B070B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B072DC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B07454.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B0760C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B07960.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B07A5C.s")
#endif

void func_82B07AB4(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B07ABC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B07BEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B07C88.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B07E18.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B07F84.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/24/fragment24_150C10/func_82B080D0.s")
#endif

#ifdef VERSION_US
void func_82B084AC(void) { func_82B060A0(0); }
#endif

#ifdef VERSION_US
s32 func_82B084CC(void) {
    return 0;
}
#endif

#ifdef VERSION_US
extern s16 D_82B12450;
extern s16 D_82B1245A;

s16 func_82B084D4(void) {
    s16 var_v1;

    var_v1 = -2;
    if (D_82B12450 == 9) {
        var_v1 = D_82B1245A;
    }
    return var_v1;
}
#endif

#ifdef VERSION_US
extern s16 D_82B12452;
s32 func_82B084FC(void) {
    return D_82B12452;
}
#endif

#ifdef VERSION_US
extern s16 D_82B1246C;
s32 func_82B08508(void) {
    return D_82B1246C;
}
#endif

#ifdef VERSION_US
extern s16 D_82B1246E;
s32 func_82B08514(void) {
    return D_82B1246E;
}
#endif
