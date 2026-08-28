#include "global.h"


#ifdef VERSION_US
void func_84100020(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x14) |= arg1;
}

void func_84100030(u8 *arg0, u32 arg1) {
    *(u32 *)(arg0 + 0x14) &= ~arg1;
}

void func_84100044(u8 *arg0, s32 arg1) {
    *(s32 *)(arg0 + 0x14) ^= arg1;
}

s32 func_84100054(u8 *arg0, s32 arg1) {
    s32 result = 0;
    if (*(s32 *)(arg0 + 0x14) & arg1) {
        result = 1;
    }
    return result;
}

s32 func_84100074(u8 *arg0, s32 arg1) {
    s32 result = 0;
    if ((*(s32 *)(arg0 + 0x14) & arg1) == 0) {
        result = 1;
    }
    return result;
}

void func_84100094(u8 *arg0) {
    arg0[0x92] = 0;
}

extern s32 func_84100054(u8 *arg0, s32 arg1);
extern s32 func_84100074(u8 *arg0, s32 arg1);
s32 func_8410009C(u8 *arg0) {
    s32 result;

    result = 0;
    if (arg0[0x92] == 0) {
        result = 1;
    }
    if (arg0[0x7F] == 0xFF) {
        if (func_84100074(arg0, 1) != 0) {
            result = 1;
        }
    }
    if ((func_84100054(arg0, 0x20000) != 0) && (*(f32 *)(arg0 + 0x24) <= 0.0f)) {
        result = 1;
    }
    return result;
}

extern u8 *D_8418C950;
extern u32 D_8418C954;
extern u8 *main_pool_alloc(s32 arg0, s32 arg1);
void func_84100134(void) {
    D_8418C950 = main_pool_alloc(0xB6D0, 0);
    _bzero(D_8418C950, 0xB6D0);
    D_8418C954 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100174.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100260.s")

extern void func_84100260(void);
void func_84100328(void) {
    func_84100260();
}

void func_84100348(u8 *arg0) {
    arg0[0x92] = 0;
}

void func_84100350(u8 *arg0) {
    u8 *next;
    u8 *prev;
    *(u32 *)(arg0 + 0x14) = 0;
    func_84100348(arg0);
    next = *(u8 **)(arg0 + 0x4);
    if (next != NULL) {
        *(u8 **)(next + 0x0) = *(u8 **)(arg0 + 0x0);
    }
    prev = *(u8 **)(arg0 + 0x0);
    if (prev != NULL) {
        *(u8 **)(prev + 0x4) = *(u8 **)(arg0 + 0x4);
    }
    *(u32 *)(arg0 + 0x4) = 0;
    *(u32 *)(arg0 + 0x0) = 0;
    arg0[0x98] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841003AC.s")

typedef struct Func8410056CParticleS8 {
    u8 pad[0x98];
    s8 active;
    u8 tail[3];
} Func8410056CParticleS8;
s32 Particle_CountActive(void) {
    s32 i;
    s32 var_v1 = 0;
    Func8410056CParticleS8 *ptr = (Func8410056CParticleS8 *)D_8418C950;
    for (i = 0; i < 0x12C; i++, ptr++) {
        if (ptr->active != 0) {
            var_v1++;
        }
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841005E0.s")

typedef struct {
    u8 pad_00[1];
    u8 mode;
    u8 divisor;
    u8 count;
    s16 *values;
} Func84100688Table;

s16 func_84100688(Func84100688Table *arg0, u32 arg1) {
    s32 i;

    if (arg0->mode == 0) {
        arg1 %= arg0->divisor;
    }
    for (i = 0; i < arg0->count - 1; i++) {
        if (arg1 >= (u32)arg0->values[i] && arg1 < (u32)arg0->values[i + 1]) {
            return (s16)i;
        }
    }
    return arg0->count - 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100710.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100874.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841009D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100B3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100C68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84100DE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101084.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_8410119C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841013F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101888.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101AF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101C00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84101D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84102750.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841027B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_8410291C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841029DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84102B3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84102D38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84102E84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841031F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_841032F0.s")

extern u8 *D_80094910;
extern void func_841031F4(u8 *, void *, s32);
extern s32 func_84100054(u8 *arg0, s32 arg1);
extern s32 func_84100074(u8 *arg0, s32 arg1);
void func_84103394(s32 arg0) {
    s32 i;
    s32 result;
    u8 *record;
    void *child;

    record = D_8418C950;
    for (i = 0; i < 0x12C; i++, record += 0x9C) {
        if (*(s8 *)(record + 0x98) != 0) {
            if (func_84100074(record, 0x102800) != 0) {
                if (func_84100054(record, 0x1000) != 0) {
                    child = *(void **)(record + 0x10);
                    result = 0;
                    if ((child != NULL) && ((*(u32 *)((u8 *)child + 8) & 2) != 0)) {
                        result = 3;
                    }
                    if (result == *(s16 *)(D_80094910 + 0x18)) {
                        func_841031F4(record, child, arg0);
                    }
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_36F8B0/func_84103478.s")
#endif
