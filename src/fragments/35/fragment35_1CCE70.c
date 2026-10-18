#include "global.h"


#ifdef VERSION_US
typedef struct Fragment35Rgba {
    u8 r, g, b, a;
} Fragment35Rgba;
extern void func_8004C8C0(s32);
extern s32 func_8004C990(s32, s32);
extern s32 func_80001FF0(void);
extern s32 D_886018A8;
extern s32 D_886018AC;
extern s32 D_886018B0;
extern s32 D_886018B4;
extern s8 D_886018B8;
extern s8 D_886018B9;
void func_88600270(void) {
    func_8004C8C0(2);
    D_886018A8 = func_8004C990(2, 0);
    D_886018AC = func_8004C990(2, 1);
    D_886018B0 = func_8004C990(2, 5);
    D_886018B4 = func_8004C990(2, 6);
    D_886018B8 = ((((((((((s8)((u32)(((f32)func_80001FF0() * 4.0f) / 2))) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF; // FAKE: redundant masks affect the later conversion's temporary-register order.
    D_886018B9 = (s8)((u32)(((f32)func_80001FF0() * 0.5f) / 2));
}

extern u8 D_88601510[];
s32 func_8860043C(s32 arg0) { u8 *table = D_88601510; s32 i = 0; do { if (table[i] == arg0) return i; i++; i &= 0xFF; } while (i < 0x12); }

void func_8860047C(void) { extern Fragment35Rgba D_88601914; extern f32 D_886018D0[]; extern f32 D_886018E0[]; extern Fragment35Rgba D_88601918; D_886018D0[0] = D_88601914.r; D_886018D0[1] = D_88601914.g; D_886018D0[2] = D_88601914.b; D_886018E0[0] = D_88601918.r; D_886018E0[1] = D_88601918.g; D_886018E0[2] = D_88601918.b; }

extern f32 D_886018D0[];
extern f32 D_886018E0[];
extern Fragment35Rgba D_88601914, D_88601918;
/* Signed rounding precedes byte narrowing; both alpha channels are preserved. */
void func_88600578(void) {
    D_88601914.r = (s32)(D_886018D0[0] + (D_886018D0[0] > 0.0f ? 0.5f : -0.5f));
    D_88601914.g = (s32)(D_886018D0[1] + (D_886018D0[1] > 0.0f ? 0.5f : -0.5f));
    D_88601914.b = (s32)(D_886018D0[2] + (D_886018D0[2] > 0.0f ? 0.5f : -0.5f));
    D_88601918.r = (s32)(D_886018E0[0] + (D_886018E0[0] > 0.0f ? 0.5f : -0.5f));
    D_88601918.g = (s32)(D_886018E0[1] + (D_886018E0[1] > 0.0f ? 0.5f : -0.5f));
    D_88601918.b = (s32)(D_886018E0[2] + (D_886018E0[2] > 0.0f ? 0.5f : -0.5f));
}

extern f32 D_886018F0[];
extern f32 D_88601900[];
void func_886006B8(s32 arg0, u8 arg1) {
    f32 temp;
    f32 temp2;
    switch (arg0) {
    case 3:
    case 6:
        temp = (f32)arg1;
        D_886018D0[0] -= temp * D_886018F0[0];
        D_886018D0[1] -= temp * D_886018F0[1];
        D_886018D0[2] -= temp * D_886018F0[2];
        D_886018E0[0] -= temp * D_88601900[0];
        D_886018E0[1] -= temp * D_88601900[1];
        D_886018E0[2] -= temp * D_88601900[2];
        return;
    case 4:
    case 7:
        temp2 = (f32)arg1;
        D_886018D0[0] += temp2 * D_886018F0[0];
        D_886018D0[1] += temp2 * D_886018F0[1];
        D_886018D0[2] += temp2 * D_886018F0[2];
        D_886018E0[0] += temp2 * D_88601900[0];
        D_886018E0[1] += temp2 * D_88601900[1];
        D_886018E0[2] += temp2 * D_88601900[2];
        return;
    }
}

extern s32 D_886018BC;
extern u8 D_886018C0;
extern f32 D_88601924;
extern f32 D_88601928;
typedef struct Fragment35TexturePair {
    s32 first;
    s32 second;
} Fragment35TexturePair;
typedef struct Fragment35TypePreview {
    s32 unk_00;
    /* Low command-byte parameter of gDPSetPrimColor in func_88600D64. */
    u8 lod_fraction;
    Fragment35Rgba primary;
    Fragment35Rgba secondary;
    s8 unk_0D, unk_0E, unk_0F, unk_10, unk_11, unk_12, unk_13, unk_14;
    f32 scale_x, scale_y;
    Fragment35TexturePair *textures;
} Fragment35TypePreview;
extern Fragment35TypePreview D_88601524[];
extern Fragment35TexturePair D_88601930;
extern s8 D_886018A0, D_886018A1, D_886018A2, D_886018A3;
extern s32 D_8860190C;
extern u8 D_88601910;
extern s8 D_8860191C, D_8860191D, D_8860191E, D_8860191F;
extern s8 D_88601920, D_88601921, D_88601922, D_88601923;
extern s32 D_886018C4, D_886018C8;

void func_88600860(s32 first_type, s32 second_type, s32 mode, u8 step) {
    Fragment35TypePreview *entry;
    f32 duration;

    D_886018C0 = step;
    if (mode == 0 || mode == 1 || mode == 4 || mode == 7) {
        D_886018A0 = D_886018A1 = D_886018A2 = D_886018A3 = 0;
        if (mode == 0) {
            mode = 2;
        }
    }
    switch (mode) {
    case 1:
    case 2:
    case 3:
    case 7:
        entry = &D_88601524[func_8860043C(first_type)];
        D_8860190C = first_type;
        break;
    case 4:
    case 5:
    case 6:
        entry = &D_88601524[func_8860043C(second_type)];
        D_8860190C = second_type;
        break;
    }
    D_88601930.first = entry->textures->first;
    D_88601930.second = entry->textures->second;
    D_88601910 = entry->lod_fraction;
    switch (mode) {
    default:
        D_88601914 = entry->primary;
        D_88601918 = entry->secondary;
        break;
    case 4:
    case 7:
        D_88601914.r = 0;
        D_88601914.g = 0;
        D_88601914.b = 0;
        D_88601914.a = entry->primary.a;
        D_88601918.r = 0;
        D_88601918.g = 0;
        D_88601918.b = 0;
        D_88601918.a = entry->secondary.a;
        break;
    }
    D_8860191C = entry->unk_0D;
    D_8860191D = entry->unk_0E;
    D_8860191E = entry->unk_0F;
    D_8860191F = entry->unk_10;
    D_88601920 = entry->unk_11;
    D_88601921 = entry->unk_12;
    D_88601922 = entry->unk_13;
    D_88601923 = entry->unk_14;
    D_88601924 = entry->scale_x;
    D_88601928 = entry->scale_y;
    D_886018BC = mode;
    if (D_886018BC != 1) {
        D_886018C4 = first_type;
        D_886018C8 = second_type;
        if (first_type == second_type) {
            D_886018BC = 1;
        } else {
            duration = (u8)D_886018B9;
            D_886018F0[0] = (u32)entry->primary.r / duration;
            D_886018F0[1] = (u32)entry->primary.g / duration;
            D_886018F0[2] = (u32)entry->primary.b / duration;
            D_88601900[0] = (u32)entry->secondary.r / duration;
            D_88601900[1] = (u32)entry->secondary.g / duration;
            D_88601900[2] = (u32)entry->secondary.b / duration;
            if (step == 0) {
                func_8860047C();
            } else {
                func_8860047C();
                func_886006B8(mode, step);
                func_88600578();
            }
        }
    }
}

extern s32 func_886000F0(u16);
extern u8 func_8006397C(u8);
extern u8 func_800639C0(u8);
void func_88600C38(u16 species, s32 mode) {
    u8 type2;
    u8 type1;

    if (species >= 254) {
        species = 201;
    }
    if (func_886000F0(species) == 1) {
        func_88600860(19, 19, mode, 0);
    } else {
        type1 = func_8006397C(species);
        type2 = func_800639C0(species);
        func_88600860(type1, type2, mode, 0);
    }
}

void func_88600CC8(u16 species) {
    u8 type2;
    u8 type1;

    if (species >= 254) {
        species = 201;
    }
    if (func_886000F0(species) == 1) {
        func_88600860(19, 19, D_886018BC, D_886018C0);
    } else {
        type1 = func_8006397C(species);
        type2 = func_800639C0(species);
        func_88600860(type1, type2, D_886018BC, D_886018C0);
    }
}

typedef struct Fragment35TextureHeader {
    u16 width, height;
    u8 format, size;
    u16 unk_06;
} Fragment35TextureHeader;
extern Gfx *D_800D0510;
extern Gfx D_886017B0[];
extern s32 D_886017AC;
extern s32 D_88601934;
extern s8 *D_88601500[4];
extern u8 *func_8004CA60(u8 *);
extern void func_800459AC(s32, s32, s32, u32, u32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80045DB4(s32, s32, s32, s32, s32, u32, u32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_88600D64(s32 translucent) {
    s32 combine_mode;
    s32 i;

    gSPDisplayList(D_800D0510++, D_886017B0);
    if (translucent != 0) {
        gDPSetRenderMode(D_800D0510++, G_RM_PASS, G_RM_CLD_SURF2);
    } else {
        gDPSetRenderMode(D_800D0510++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    }
    combine_mode = D_88601524[func_8860043C(D_8860190C)].unk_00;
    switch (combine_mode) {
    case 0:
        gDPSetCombineLERP(D_800D0510++, TEXEL0, TEXEL1, PRIM_LOD_FRAC, TEXEL1, 1, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, 0, 0, 0, COMBINED);
        break;
    case 1:
        gDPSetCombineLERP(D_800D0510++, NOISE, SHADE, PRIM_LOD_FRAC, TEXEL1, 1, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, 0, 0, 0, COMBINED);
        break;
    }
    gDPSetPrimColor(D_800D0510++, 0, D_88601910,
                   D_88601914.r, D_88601914.g, D_88601914.b, D_88601914.a);
    gDPSetEnvColor(D_800D0510++, D_88601918.r, D_88601918.g, D_88601918.b, D_88601918.a);
    if (D_886017AC != 0) {
        D_886018A0 += D_8860191C;
        D_886018A1 += D_8860191D;
        D_886018A2 += D_8860191E;
        D_886018A3 += D_8860191F;
        //!bug: The upper wrap test cannot succeed for signed scroll bytes.
        for (i = 0; i < 4; i++) {
            if (*D_88601500[i] < 0) {
                *D_88601500[i] = *D_88601500[i] + 128;
            } else if (*D_88601500[i] >= 128) {
                *D_88601500[i] = *D_88601500[i] - 128;
            }
        }
    }
    func_800459AC((s32)func_8004CA60((u8 *)D_88601930.first),
                  ((Fragment35TextureHeader *)D_88601930.first)->format,
                  ((Fragment35TextureHeader *)D_88601930.first)->size,
                  ((Fragment35TextureHeader *)D_88601930.first)->width,
                  ((Fragment35TextureHeader *)D_88601930.first)->height,
                  1, 0, 0, 0, 5, 5, D_88601920, D_88601921);
    func_80045DB4((s32)func_8004CA60((u8 *)D_88601934), 256, 1,
                  ((Fragment35TextureHeader *)D_88601934)->format,
                  ((Fragment35TextureHeader *)D_88601934)->size,
                  ((Fragment35TextureHeader *)D_88601934)->width,
                  ((Fragment35TextureHeader *)D_88601934)->height,
                  1, 0, 0, 0, 5, 5, D_88601922, D_88601923);
    gDPSetTileSize(D_800D0510++, 0, D_886018A0, D_886018A1, D_886018A0 + 124, D_886018A1 + 124);
    gDPSetTileSize(D_800D0510++, 1, D_886018A2, D_886018A3, D_886018A2 + 124, D_886018A3 + 124);
    if (D_886018BC != 1) {
        if (D_886017AC != 0) {
            D_886018C0++;
            switch (D_886018BC) {
            case 2:
            case 5:
                if (D_886018C0 >= (u8)D_886018B8) {
                    if (D_886018BC == 2) {
                        func_88600860(D_886018C4, D_886018C8, 3, 0);
                    } else {
                        func_88600860(D_886018C4, D_886018C8, 6, 0);
                    }
                }
                break;
            case 3:
            case 6:
                if (D_886018C0 >= (u8)D_886018B9) {
                    if (D_886018BC == 3) {
                        func_88600860(D_886018C4, D_886018C8, 4, 0);
                    } else if (D_886018BC == 6) {
                        func_88600860(D_886018C4, D_886018C8, 7, 0);
                    }
                } else {
                    func_886006B8(D_886018BC, 1);
                }
                break;
            case 4:
            case 7:
                if (D_886018C0 >= (u8)D_886018B9) {
                    if (D_886018BC == 7) {
                        func_88600860(D_886018C4, D_886018C8, 2, 0);
                    } else if (D_886018BC == 4) {
                        func_88600860(D_886018C4, D_886018C8, 5, 0);
                    }
                } else {
                    func_886006B8(D_886018BC, 1);
                }
                break;
            }
        }
        if (D_886018BC != 2 && D_886018BC != 5) {
            func_88600578();
        }
    }
}

extern void func_80044270(s32, s32, s32, s32, s32, s32, s32, s32, s32);
typedef struct {
    u8 pad[4];
    s16 unk4;
    s16 unk6;
} Func886013BCRecord;
void func_886013BC(s32 arg0, s32 arg1) {
    Func886013BCRecord *ptr = (Func886013BCRecord *)((u32)arg0);
    f32 temp_fa0;
    f32 temp_fv0;
    f32 var_fa1;
    f32 var_fv1;
    s16 temp_a2;
    s16 temp_a3;
    func_88600D64(arg1);
    temp_a2 = ptr->unk4;
    temp_fa0 = ((D_88601924 * 1024.0f) * 32.0f) / ((f32)temp_a2);
    do {
        if (temp_fa0 > 0.0f) {
            var_fa1 = 0.5f;
        } else {
            var_fa1 = -0.5f;
        }
    } while (0);
    temp_a3 = ptr->unk6;
    temp_fv0 = ((D_88601928 * 1024.0f) * 32.0f) / ((f32)temp_a3);
    if (temp_fv0 > 0.0f) {
        var_fv1 = 0.5f;
    } else {
        var_fv1 = -0.5f;
    }
    func_80044270(0, 0, temp_a2, temp_a3, -0x10, -0x10,
        (s32)(var_fa1 + temp_fa0), (s32)(var_fv1 + temp_fv0), 0x100000);
}

extern void func_886013BC(s32, s32);
void func_886014D8(s32 arg0) {
    func_886013BC(arg0, 0);
}
#endif
