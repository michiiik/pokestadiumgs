#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_841086F0.s")

extern void func_841086F0(void);
extern u32 D_84190188;
void func_84108728(void) {
    func_841086F0();
    D_84190188 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_8410874C.s")

extern s32 D_84190194;
extern u32 D_841901B8;
void func_8410878C(s32 arg0, s32 arg1, s32 arg2) {
    D_84190194 = arg2;
    D_84190188 = 2;
    D_841901B8 = 1;
}

extern void func_8410874C();
extern u8 *D_84193DD0;
void func_841089D8(s32 arg0);
void func_841087B8(s32 arg0, s32 arg1, s32 arg2) {
    if (((*(u8 *)((u8 *)(D_84193DD0) + (9))) & 7) == 1) {
        switch (arg0) {                             /* irregular */
        case 0x2D:
            func_8410874C();
            return;
        case 0x2F:
            func_8410874C();
            return;
        case 0x30:
            func_8410874C();
            return;
        case 0x5F:
            func_8410874C();
            return;
        case 0x67:
            func_8410874C();
            return;
        case 0xAD:
            func_8410874C();
            return;
        case 0x39:
            func_8410878C(arg0, arg1, arg2);
            return;
        case 0xC3:
            func_8410874C();
            return;
        default:
            func_841089D8(1);
            return;
        }
    } else {
        func_8410874C();
    }
}

extern u32 D_84190188; extern u32 D_841901A8; extern void func_841086F0(void); void func_841088CC(s32 arg0){ func_841086F0(); D_84190188=1; if(arg0==0x5B) D_841901A8=1; }

extern s32 D_8419018C;
extern s32 D_84190190;
extern s32 D_841901A4;
void func_8410890C(s32 arg0, s32 arg1) {
    D_8419018C = arg0;
    D_84190190 = 1;
    D_84190194 = arg1;
    if (arg0 == 0x12C) {
        D_841901A4 = 1;
    }
}

extern u8 D_8418C958;
void func_84108940(void *arg0, s32 arg1) {
    u8 *p = (u8 *)&D_8418C958 + arg1 * 0xC;
    *(f32 *)((u8 *)arg0 + 0x0) = *(f32 *)(p + 0x0);
    *(f32 *)((u8 *)arg0 + 0x4) = *(f32 *)(p + 0x4);
    *(f32 *)((u8 *)arg0 + 0x8) = *(f32 *)(p + 0x8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84108974.s")

extern void func_84105E3C(); extern void func_841003AC(); extern void func_84109460(); extern void func_84108974(); void func_841089D8(s32 arg0){ func_84105E3C(arg0); func_841003AC(arg0); func_84109460(arg0); func_84108974(arg0); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84108A10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84108AF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84108CE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84108E00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84108F88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84109118.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_841091CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_8410922C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_841092B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_8410933C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84109394.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_841093E8.s")

extern void func_84109394();
extern void func_841093E8();
extern s32 D_841901AC;
void func_84109460(s32 arg0) {
    if (arg0 == 0) {
        if (D_841901AC == 0) {
            func_84109394();
        }
    } else {
        func_841093E8();
    }
}

extern u32 D_84190090;
u32 func_841094A4(void) {
    return D_84190090;
}

extern u8 *D_84190198;
extern s32 func_8411EF5C(u8 *arg0);
s32 BattleAnim_GetSecondaryOwnerSpecies(void) {
    return func_8411EF5C(D_84190198);
}

extern u32 D_841901B0;
void func_841094D4(u32 arg0) {
    D_841901B0 = arg0;
}

u32 func_841094E0(void) {
    return D_841901B0;
}

u32 func_841094EC(void) {
    return D_841901B8;
}

extern u32 func_8411EE54(u8 *arg0);
extern f32 D_84188E20;
f32 func_841094F8(void) {
    f32 var_ft1;
    u32 temp_v0;

    temp_v0 = func_8411EE54((u8 *) D_84190194);
    var_ft1 = (f32) temp_v0;
    return var_ft1 * D_84188E20;
}

extern f32 D_84188E24;
f32 func_84109544(void) {
    f32 var_ft1;
    u32 temp_v0;

    temp_v0 = func_8411EE54(D_84190198);
    var_ft1 = (f32) temp_v0;
    return var_ft1 * D_84188E24;
}

extern u8 *D_8419019C;
extern f32 D_84188E28;
f32 func_84109590(void) {
    f32 var_ft1;
    u32 temp_v0;

    temp_v0 = func_8411EE54(D_8419019C);
    var_ft1 = (f32) temp_v0;
    return var_ft1 * D_84188E28;
}

extern u32 func_8411E358(s32 arg0, s32 arg1);
extern f32 D_84188E2C;
f32 func_841095DC(void) {
    f32 var_ft1;
    u32 temp_v0;

    temp_v0 = func_8411E358(D_84190194, D_8419018C);
    var_ft1 = (f32) temp_v0;
    return var_ft1 * D_84188E2C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84109630.s")

s32 func_8003C9B8(s32, s16, s32);
s32 func_8411E21C(u8 *arg0);
extern void func_8411DCCC(s32, s32);
extern void func_84109630(s32, s32);
void func_8410971C(s32 arg0) {
    if (func_8003C9B8(D_84190194, func_8411E21C((u8 *) D_84190194), arg0) == 0) {
        func_8411DCCC(D_84190194, arg0);
    }
    func_84109630(D_84190194, arg0);
}

void func_84109780(s32 arg0) {
    if (func_8003C9B8(D_84190198, func_8411E21C(D_84190198), arg0) == 0) {
        func_8411DCCC((s32) D_84190198, arg0);
    }
    func_84109630((s32) D_84190198, arg0);
}

extern s32 func_8411E22C(u8 *);
s32 func_841097E4(s32 arg0) {
    if (func_8003C9B8((s32) D_8419019C, func_8411E22C(D_8419019C), arg0) == 0) {
        func_8411DCCC((s32) D_8419019C, arg0);
    }
    func_84109630((s32) D_8419019C, arg0);
}

void func_84109848(s32 arg0) {
    func_8411DCCC(D_84190194, arg0);
    func_84109630(D_84190194, arg0);
}

void func_84109884(s32 arg0) {
    func_8411DCCC(D_84190198, arg0);
    func_84109630(D_84190198, arg0);
}

void func_841098C0(s32 arg0) {
    func_8411DCCC(D_8419019C, arg0);
    func_84109630(D_8419019C, arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_841098FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84109A18.s")

void func_84109B1C(s32 arg0) {
    if (func_8003C9B8(D_84190194, func_8411E244(D_84190194, D_8419018C), arg0) == 0) {
        func_8411DCCC(D_84190194, arg0);
    }
    func_84109A18(D_84190194, arg0);
}

void func_84109B88(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}

void func_84109B9C(u8 *arg0) {}

void func_84109BA4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}
#endif
