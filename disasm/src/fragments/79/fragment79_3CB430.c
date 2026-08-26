#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CB430/func_8415BBA0.s")

typedef struct Strip400Node_79 {
    f32 unk_00;
    f32 unk_04;
    f32 unk_08;
    f32 unk_0C;
} Strip400Node_79;
typedef struct Strip400State_79 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    f32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    s16 unk_28;
    s16 unk_2A;
    u8 unk_2C[0xC];
    Strip400Node_79 nodes[400];
} Strip400State_79;
extern Strip400State_79 *D_84187498;
f32 func_8415BCD8(void) {
    Strip400State_79 *ptr;
    f32 tmp;
    s32 tmp2;
    ptr = D_84187498;
    tmp2 = ptr->unk_00;
    if (tmp2 < (ptr->unk_06 - 0x34)) {
        return 1.0f;
    }
    if (ptr->unk_18 == 0.0f) {
        return 1.0f;
    }
    tmp = (ptr->nodes[0].unk_0C * 2.0f) / (ptr->unk_14 + ptr->unk_18);
    return tmp;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CB430/func_8415BD48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CB430/func_8415C2E0.s")

typedef struct Radial20Node_79 { f32 unk_00; u8 unk_04; u8 pad_05[3]; f32 unk_08; f32 unk_0C; f32 unk_10; f32 unk_14; f32 unk_18; f32 unk_1C; f32 unk_20; f32 unk_24; u8 pad_28[0x20]; } Radial20Node_79;
typedef struct Radial20_79 { s16 unk_000; s16 unk_002; s16 unk_004; s16 unk_006; u8 pad_008[0x40]; Radial20Node_79 unk_048[20]; } Radial20_79;
extern u8 *D_84187530; extern s16 func_84169BA8(void);
void func_8415C530(void) {
    s16 temp_v0; s32 i; s32 j; Radial20_79 *var_a2; Radial20Node_79 *var_v1;
    temp_v0=func_84169BA8(); var_a2=(Radial20_79 *)(D_84187530+0x3C8);
    for(i=0;i<10;i++) {
        var_a2->unk_000=0; var_a2->unk_004=0; var_a2->unk_006=0; var_v1=&var_a2->unk_048[0];
        for(j=0;j<20;j++,var_v1++) {
            var_v1->unk_00=0.0f; var_v1->unk_04=0; var_v1->unk_08=1.0f; var_v1->unk_0C=0.0f;
            var_v1->unk_10=0.0f; var_v1->unk_14=0.0f; var_v1->unk_18=0.0f; var_v1->unk_1C=0.0f;
            var_v1->unk_20=0.0f; var_v1->unk_24=0.0f;
        }
        var_a2->unk_002=temp_v0;
        var_a2++;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CB430/func_8415C644.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CB430/func_8415C884.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CB430/func_8415CC74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CB430/func_8415D074.s")

extern f64 D_8418C688;
extern f64 D_8418C690;
void Radial20_RotateVertexOffset(f32 arg0, f32 *arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    UNUSED f32 pad[16];
    f32 sp30[4][4];
    UNUSED s32 pad2[2];
    guRotateF(sp30, (arg0 * D_8418C688) / D_8418C690, 1.0f, 0.0f, 0.0f);
    guMtxXFMF(sp30, 0.0f, 0.0f, arg3, &arg2[0], &arg2[1], &arg2[2]);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CB430/func_8415D4C4.s")

typedef struct Radial20Complete_79 { s16 unk_000; s16 unk_002; s16 unk_004; s16 unk_006; s16 unk_008; u8 pad_00A[0x3E]; Radial20Node_79 unk_048[20]; } Radial20Complete_79;
extern void func_8415D4C4(Radial20Complete_79 *); extern void func_84169DBC(s16);
s32 func_8415DAE4(void) {
    s32 i;
    s32 var_s2 = 0;
    Radial20Complete_79 *var_s0 = (Radial20Complete_79 *)(D_84187530 + 0x3C8);
    for (i = 0; i < 10; i++, var_s0++) {
        if (var_s0->unk_000 == 1) {
            var_s0->unk_004++;
            if (var_s0->unk_006 < var_s0->unk_004) {
                var_s0->unk_000 = 0;
                if (var_s0->unk_008 == 5) {
                }
            } else {
                func_8415D4C4(var_s0);
                var_s2++;
            }
            func_84169DBC(var_s0->unk_002);
        }
    }
    if (var_s2 > 0) return 0;
    return -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3CB430/func_8415DBBC.s")
#endif
