#include "global.h"


#ifdef VERSION_US
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
    D_886018B8 = ((((((((((s8)((u32)(((f32)func_80001FF0() * 4.0f) / 2))) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF;
    D_886018B9 = (s8)((u32)(((f32)func_80001FF0() * 0.5f) / 2));
}

extern u8 D_88601510[];
s32 func_8860043C(s32 arg0) { u8 *table = D_88601510; s32 i = 0; do { if (table[i] == arg0) return i; i++; i &= 0xFF; } while (i < 0x12); }

void func_8860047C(void) { extern u8 D_88601914[]; extern f32 D_886018D0[]; extern f32 D_886018E0[]; extern u8 D_88601918[]; D_886018D0[0] = D_88601914[0]; D_886018D0[1] = D_88601914[1]; D_886018D0[2] = D_88601914[2]; D_886018E0[0] = D_88601918[0]; D_886018E0[1] = D_88601918[1]; D_886018E0[2] = D_88601918[2]; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_88600578.s")

extern f32 D_886018D0[];
extern f32 D_886018E0[];
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_88600860.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_88600C38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_88600CC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/35/fragment35_1CCE70/func_88600D64.s")

extern void func_88600D64(s32);
extern f32 D_88601924;
extern f32 D_88601928;
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
void func_886014D8(s32 arg0) { func_886013BC(arg0, 0); }
#endif
