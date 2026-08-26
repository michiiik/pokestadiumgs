#include "global.h"


#ifdef VERSION_US
extern u32 D_80128C00;
extern u32 D_80128C30;
extern u32 D_80128C34;
extern u32 D_80128C38;
u32 ParticleGfx_GetFrameDivisor(s32 arg0) {
    u32 ret = D_80128C00;
    switch (arg0) {
        case 2: ret = D_80128C38; break;
        case 3: ret = D_80128C34; break;
        case 4: ret = D_80128C30; break;
    }
    return ret;
}

void func_810001D4(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u32 arg7) {
    u32 temp_v0 = arg7;
    s32 temp_v1 = arg1 + (arg3 * temp_v0);
    s32 temp_a0 = arg2 - (arg4 * temp_v0);
    gDPSetTileSize(gfx, G_TX_RENDERTILE, temp_v1, temp_a0, ((temp_v1 + arg5) - 1) << 2, ((temp_a0 + arg6) - 1) << 2);
}

void func_81000248(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u32 arg7) {
    u32 temp_v0 = arg7;
    s32 temp_v1 = arg1 + (arg3 * temp_v0);
    s32 temp_a0 = arg2 - (arg4 * temp_v0);
    gDPSetTileSize(gfx, 1, temp_v1, temp_a0, ((temp_v1 + arg5) - 1) << 2, ((temp_a0 + arg6) - 1) << 2);
}

Gfx *ParticleGfx_LoadTextureBlock4ToList(Gfx *gfx, u8 *texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt) {
    gDPLoadTextureBlock_4b(gfx++, texture, fmt, width, height, 0, cms, cmt, masks, maskt, shifts, shiftt);
    return gfx;
}

void ParticleGfx_LoadTextureI4ToList(Gfx *gfx, u8 *texture, s32 width, s32 height) {
    ParticleGfx_LoadTextureBlock4ToList(gfx, texture, G_IM_FMT_I, width, height,
        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_81000550.s")


typedef struct { u8 pad_00[4]; s16 count; u8 pad_06[2]; s16 *values; } Func810006C4Table;
s16 func_810006C4(Func810006C4Table *arg0, u32 arg1) {
    s32 i;
    for (i = 0; i < arg0->count - 1; i++) {
        if (arg1 >= arg0->values[i] && arg1 < arg0->values[i + 1]) {
            return (s16)i;
        }
    }
    return arg0->count - 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_8100072C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_81000894.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_810009C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_81000E54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_8100107C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_8100124C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_81001F14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_810020E0.s")

typedef struct { s16 first; s16 second; } Func810023ACRangeA;
typedef struct { u8 pad[0x44]; void *flag; s32 value; } Func810023ACContextA;
typedef struct { u8 pad[0x7F]; u8 value; } Func810023ACInputA;
extern s32 func_84100054(u8 *, s32);
s32 func_810023AC(Func810023ACRangeA *arg0, u8 *arg1, Func810023ACContextA *arg2) {
    s32 result = 0;
    Func810023ACRangeA *range = *(Func810023ACRangeA **)((u8 *)arg0 + 4);
    if (range != NULL) {
        s16 denominator = range->second;
        s16 selector = range->first;
        if (denominator == 0) {
            if (arg1 != NULL && func_84100054(arg1, 0x100) != 0) {
                result = ((Func810023ACInputA *)arg1)->value / selector;
            } else {
                result = ParticleGfx_GetFrameDivisor(selector);
            }
        } else if (arg2 != NULL && arg2->flag != NULL) {
            result = (arg2->value >> 16) / selector;
        } else if (arg1 != NULL) {
            result = ((Func810023ACInputA *)arg1)->value / selector;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_810024E0.s")

typedef struct {
    unsigned char pad_00[3];
    u8 unk_03;
    unsigned char pad_04[0x10];
    void *unk_14;
} Func8100338CStateK;
extern s32 D_800D0510;
extern s32 func_810024E0();
void func_8100338C(s32 arg0, Func8100338CStateK *state) {
    if (arg0 == 5) {
        D_800D0510 = func_810024E0(D_800D0510, state->unk_14, 0, 0, state->unk_03);
    }
}

typedef struct { unsigned char pad_00[3]; u8 unk_03; unsigned char pad_04[0x10]; void *unk_14; } Func810033DCStateG2;
typedef struct { unsigned char pad_00[0x1C]; u8 unk_1C; } Func810033DCGlobalG2;
extern Func810033DCGlobalG2 *D_8009491C;
void func_810033DC(s32 arg0, Func810033DCStateG2 *state) {
    if (arg0 == 5) {
        Func810033DCGlobalG2 *global = D_8009491C;
        Func810033DCStateG2 *temp = state;
        void *value = temp->unk_14;
        if (global->unk_1C == 0) {
            D_800D0510 = func_810024E0(D_800D0510, value, 1, 0, temp->unk_03);
        }
    }
}

typedef struct {
    unsigned char pad_00[3];
    u8 unk_03;
    unsigned char pad_04[0x10];
    void *unk_14;
} Func8100343CState;
void func_8100343C(s32 arg0, Func8100343CState *state) {
    if (arg0 == 5) {
        D_800D0510 = func_810024E0(D_800D0510, state->unk_14, 2, 0, state->unk_03);
    }
}

void func_8100348C(s32 arg0, s32 arg1) {
    s32 value = 0;
    D_800D0510 = func_810024E0(D_800D0510, arg1, 0, arg0, value);
}

typedef struct {
    unsigned char pad_00[3];
    u8 unk_03;
    unsigned char pad_04[0x10];
    void *unk_14;
} Func810034C0StateD;
void func_810034C0(s32 arg0, Func810034C0StateD *state) {
    if (arg0 == 5) {
        D_800D0510 = func_810024E0(D_800D0510, state->unk_14, 4, 0, state->unk_03);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_81003510.s")

void func_81003524(s32 arg0, s32 arg1) { if (arg0 == 5) { arg1 = arg1; } }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_8100352C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_81003680.s")

void func_81003750(u8 *arg0, s32 arg1) {}

void func_8100375C(u8 *arg0, s32 arg1) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_15EA30/func_81003768.s")
#endif
