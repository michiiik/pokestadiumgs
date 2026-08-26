#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_841614E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84161670.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84161CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84161DAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162078.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_841621A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162660.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162798.s")

extern f64 D_8418C7A8;
extern f64 D_8418C7B0;

void TexturedRibbonSheet_Update(f32 arg0, f32 *arg1, f32 arg2) {
    f32 sp30[4][4];
    f32 angle = (arg0 * D_8418C7A8) / D_8418C7B0;
    guRotateRPYF(sp30, 90.0f, angle, angle);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg2, &arg1[0], &arg1[1], &arg1[2]);
}

typedef struct {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
} S1_Color_RGB8;
typedef struct S1_Vec3f {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} S1_Vec3f;
typedef struct S1_TexturedRibbonSheetNode {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ S1_Vec3f unk_0C;
    /* 0x18 */ S1_Vec3f unk_18;
    /* 0x24 */ S1_Vec3f unk_24;
    /* 0x30 */ Vtx unk_30[2];
} S1_TexturedRibbonSheetNode;
typedef struct S1_TexturedRibbonSheet {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ S1_Color_RGB8 unk_00A;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ char unk01C[0x1C];
    /* 0x038 */ S1_TexturedRibbonSheetNode unk_038[10];
} S1_TexturedRibbonSheet;
void TexturedRibbonSheet_UpdateRecord(S1_TexturedRibbonSheet* arg0) {
    s32 i;
    s32 j;
    Vtx* var_a1;
    Vtx* var_a2;
    S1_TexturedRibbonSheetNode* var_v0;
    S1_TexturedRibbonSheetNode* var_v1;

    var_v0 = &arg0->unk_038[9];
    for (i = 0; i < 9; i++, var_v0--) {
        var_a1 = &var_v0[0].unk_30[0];
        var_a2 = &var_v0[-1].unk_30[0];
        for (j = 0; j < 2; j++) {
            *var_a1++ = *var_a2++;
        }
    }

    var_v1 = &arg0->unk_038[0];
    switch (arg0->unk_002) {
        case 0:
            var_v1->unk_0C.y += var_v1->unk_24.y;
            if (arg0->unk_004 >= 0xB) {
                arg0->unk_002 = 1;
            }
            var_v1->unk_08 += 2.0 * arg0->unk_014;
            break;

        case 1:
            var_v1->unk_0C.x += var_v1->unk_18.x;
            var_v1->unk_0C.y += var_v1->unk_18.y;
            var_v1->unk_0C.z += var_v1->unk_18.z;

            if (arg0->unk_008 > 0) {
                var_v1->unk_18.x += 2.0;
                if (var_v1->unk_18.x > 20.0) {
                    var_v1->unk_18.x = 20.0f;
                }
            } else {
                var_v1->unk_18.x -= 2.0;
                if (var_v1->unk_18.x < -20.0) {
                    var_v1->unk_18.x = -20.0f;
                }
            }
            var_v1->unk_08 += arg0->unk_014;
            break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162C88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D0D70/func_84162DE8.s")
#endif
