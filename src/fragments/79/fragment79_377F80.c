#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_841086F0.s")

extern void func_841086F0();
extern u32 D_84190188;
void func_84108728(void) {
    func_841086F0();
    D_84190188 = 0;
}

extern void func_841086F0();
extern s32 D_84190194;
extern u32 D_84190188;
extern u32 D_841901B8;

void func_8410874C(s32 arg0, s32 arg1, s32 arg2) {
    func_841086F0(arg0, arg1, arg2);
    D_84190194 = arg2;
    D_84190188 = 2;
    D_841901B8 = 1;
}
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
            func_8410874C(arg0, arg1, arg2);
            return;
        case 0x2F:
            func_8410874C(arg0, arg1, arg2);
            return;
        case 0x30:
            func_8410874C(arg0, arg1, arg2);
            return;
        case 0x5F:
            func_8410874C(arg0, arg1, arg2);
            return;
        case 0x67:
            func_8410874C(arg0, arg1, arg2);
            return;
        case 0xAD:
            func_8410874C(arg0, arg1, arg2);
            return;
        case 0x39:
            func_8410878C(arg0, arg1, arg2);
            return;
        case 0xC3:
            func_8410874C(arg0, arg1, arg2);
            return;
        default:
            func_841089D8(1);
            return;
        }
    } else {
        func_8410874C(arg0, arg1, arg2);
    }
}

extern u32 D_84190188; extern u32 D_841901A8; extern void func_841086F0(); void func_841088CC(s32 arg0){ func_841086F0(); D_84190188=1; if(arg0==0x5B) D_841901A8=1; }

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

extern s32 D_84190180;
void func_84108974(s32 arg0) {
    s32 one = 1;
    if ((D_841901A8 != 0) && (arg0 == one) && (one == D_84190188) && (D_84190180 == 0x5B)) {
        func_8410890C(0x12D, D_84190194);
        D_841901A8 = 0;
    }
}

extern void func_84105E3C(); extern void func_841003AC(); extern void func_84109460(); extern void func_84108974(); void func_841089D8(s32 arg0){ func_84105E3C(arg0); func_841003AC(arg0); func_84109460(arg0); func_84108974(arg0); }

/* mkdraft:func_84108A10 begin */
extern float sqrtf(float value);
extern u8 *D_8418C950;

void func_84108A10(s32 arg0)
{
  s32 var_s1;
  u8 *var_s0;
  void *temp_v0;
  var_s0 = D_8418C950;
 var_s1 = 0; do { if ((((*((s8 *) (((u8 *) var_s0) + 0x98))) != 0) && (func_84100054(var_s0, 0x10000) != 0)) && (arg0 == (*((s32 *) (((u8 *) var_s0) + 8))))) { func_84100030(var_s0, 0x10080U); if (func_84100054(var_s0, 0x8000) != 0) { func_84100348(var_s0); if (1) { } if (1) { } if (1) { } if (1) { } if (1) { } if (1) { } temp_v0 = *((void **) (((u8 *) var_s0) + 0xC));
        if (temp_v0 != NULL)
        {
          *((u8 *) (((u8 *) temp_v0) + 1)) = (u8) ((*((u8 *) (((u8 *) temp_v0) + 1))) & (~1));
        }
      }
    }
    var_s1 += 1;
    var_s0 += 0x9C;
  }
  while (var_s1 != 0x12C);
}
/* mkdraft:func_84108A10 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84108AF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84108CE8.s")

#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

M2C_UNK func_84100020(u8 *, M2C_UNK);             /* extern */
extern u8 *D_8418C950;

void func_84108E00(s32 arg0, s32 arg1) {
    s16 *temp_v1;
    s16 *temp_v1_2;
    s16 *temp_v1_3;
    s32 var_s1;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *var_s0;

    var_s0 = D_8418C950;
    var_s1 = 0;
    do {
        if ((M2C_FIELD(var_s0, s8 *, 0x98) != 0) && (arg0 == M2C_FIELD(var_s0, s32 *, 8))) {
            switch (arg1) {                         /* irregular */
            case 0:
                temp_v0 = M2C_FIELD(var_s0, u8 **, 0x10);
                if (temp_v0 != NULL) {
                    temp_v1 = M2C_FIELD(temp_v0, s16 **, 0x14);
                    if ((temp_v1 != NULL) && (*temp_v1 == 0xD3)) {
                        temp_v0_2 = M2C_FIELD(var_s0, u8 **, 0xC);
                        if (temp_v0_2 != NULL) {
                            M2C_FIELD(temp_v0_2, u8 *, 1) = (u8) (M2C_FIELD(temp_v0_2, u8 *, 1) & ~1);
                        }
                    }
                }
                break;
            case 1:
                temp_v0_3 = M2C_FIELD(var_s0, u8 **, 0x10);
                if (temp_v0_3 != NULL) {
                    temp_v1_2 = M2C_FIELD(temp_v0_3, s16 **, 0x14);
                    if ((temp_v1_2 != NULL) && (*temp_v1_2 == 0x13D)) {
                        temp_v0_4 = M2C_FIELD(var_s0, u8 **, 0xC);
                        if (temp_v0_4 != NULL) {
                            M2C_FIELD(temp_v0_4, u8 *, 1) = (u8) (M2C_FIELD(temp_v0_4, u8 *, 1) & ~1);
                        }
                    }
                }
                break;
            case 2:
                temp_v0_5 = M2C_FIELD(var_s0, u8 **, 0x10);
                if (temp_v0_5 != NULL) {
                    temp_v1_3 = M2C_FIELD(temp_v0_5, s16 **, 0x14);
                    if ((temp_v1_3 != NULL) && (*temp_v1_3 == 0x12)) {
                        func_84100020(var_s0, 0x100000);
                    }
                }
                break;
            }
        }
        var_s1 += 1;
        var_s0 += 0x9C;
    } while (var_s1 != 0x12C);
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84108F88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_84109118.s")

extern u8 D_841901B4;
extern s32 D_841901C0[8];
extern s32 D_841901E0[8];
extern s32 D_841901AC;
extern u32 D_841901B0;

void func_841091CC(void) {
    s32 index;

    D_841901B4 = 0;
    for (index = 0; index < 8; index++) {
        D_841901C0[index] = 0;
        D_841901E0[index] = 0;
    }
    D_841901AC = 0;
    D_841901B0 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_377F80/func_8410922C.s")

/* mkdraft:func_841092B8 begin */
void func_841092B8(void* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if ((D_841901C0[i] != 0) && (((s32 (*)(void))D_841901C0[i])() != 0)) {
            D_841901C0[i] = 0;
            D_841901E0[i] = 0;
        }
    }
}
/* mkdraft:func_841092B8 end */

/* mkdraft:func_8410933C begin */
void func_8410933C(void* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_841901E0[i] != 0) {
            ((void (*)(void))D_841901E0[i])();
        }
    }
}
/* mkdraft:func_8410933C end */

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

s32 GeoRender_FindAnchorPosition(s32, s16, s32);
s32 func_8411E21C(u8 *arg0);
extern void func_8411DCCC(s32, s32);
extern void func_84109630(s32, s32);
void func_8410971C(s32 arg0) {
    if (GeoRender_FindAnchorPosition(D_84190194, func_8411E21C((u8 *) D_84190194), arg0) == 0) {
        func_8411DCCC(D_84190194, arg0);
    }
    func_84109630(D_84190194, arg0);
}

void func_84109780(void *position) {
    if (GeoRender_FindAnchorPosition(D_84190198, func_8411E21C(D_84190198), (s32)position) == 0) {
        func_8411DCCC((s32) D_84190198, (s32)position);
    }
    func_84109630((s32) D_84190198, (s32)position);
}

extern s32 func_8411E22C(u8 *);
s32 func_841097E4(s32 arg0) {
    if (GeoRender_FindAnchorPosition((s32) D_8419019C, func_8411E22C(D_8419019C), arg0) == 0) {
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
    if (GeoRender_FindAnchorPosition(D_84190194, func_8411E244(D_84190194, D_8419018C), arg0) == 0) {
        func_8411DCCC(D_84190194, arg0);
    }
    func_84109A18(D_84190194, arg0);
}

typedef struct { f32 x, y, z; } ParticleStubPosition;

// OwnerLinkedFourStream_Start passes position by value and consumes a particle handle.
//@src/fragments/79/fragment79_3D4060.c
//!bug Retail stub falls through without defining its return value.
u8 *func_84109B88(ParticleStubPosition position, u8 kind) {
}

void func_84109B9C(u8 *arg0) {}

void func_84109BA4(u8 *particle, ParticleStubPosition position) {
}
#endif
