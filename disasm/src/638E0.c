#include "global.h"


#ifdef VERSION_US
extern s32 func_8004C874(s32, s32);
extern void *D_800A5080;
s32 *func_80062CE0(u8 arg0) {
    s32 *temp_v0;
    s32 *var_v1;

    temp_v0 = (s32 *)func_8004C874(6, arg0 - 1);
    if (temp_v0 != NULL) {
        var_v1 = temp_v0;
    } else {
        var_v1 = (s32 *)&D_800A5080;
    }
    return var_v1;
}

u8 func_80062D20(u8 arg0) { extern u8 D_8009782A[]; if (arg0 > 0 && arg0 < 0xFC) return D_8009782A[arg0 * 6]; return 0; }

u8 func_80062D5C(u8 arg0) { extern u8 D_8009782B[]; if (arg0 > 0 && arg0 < 0xFC) return D_8009782B[arg0 * 6]; return 0; }

u8 func_80062D98(u8 arg0) { extern u8 D_8009782C[]; if (arg0 > 0 && arg0 < 0xFC) return D_8009782C[arg0 * 6]; return 0xFF; }

u8 func_80062DD4(u8 arg0) { extern u8 D_8009782D[]; if (arg0 > 0 && arg0 < 0xFC) return D_8009782D[arg0 * 6]; return 0; }

u8 func_80062E10(u8 arg0) { extern u8 D_8009782E[]; if (arg0 > 0 && arg0 < 0xFC) return D_8009782E[arg0 * 6]; return 0; }

extern u8 D_8009782E[];
u8 func_80062E4C(u8 arg0) {
    s32 temp_a0;
    u8 temp_a1;
    s32 temp_lo;
    s32 var_v1;

    temp_a0 = arg0;
    if ((temp_a0 > 0) && (temp_a0 < 0xFC)) {
        temp_lo = (temp_a1 = D_8009782E[temp_a0 * 6]) / 5;
        if (temp_lo >= 8) {
            var_v1 = 7;
        } else {
            var_v1 = temp_lo;
        }
        return var_v1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/638E0/func_80062EB0.s")

u8 func_80062F2C(u8 arg0) { extern u8 D_8009782F[]; if (arg0 > 0 && arg0 < 0xFC) return D_8009782F[arg0 * 6]; return 0; }

u8 func_80062F68(u8 arg0) { extern u8 D_80097E13[]; if (arg0 > 0 && arg0 < 0x3A) return D_80097E13[arg0]; return 0; }

s32 func_80062F98(u8 arg0) {
    s32 temp_a0;
    s32 temp_s1;
    s32 var_s0;

    temp_a0 = arg0;
    if (temp_a0 > 0) {
        var_s0 = 1;
        if (temp_a0 < 0xFC) {
            do {
                temp_s1 = var_s0 & 0xFF;
                if (temp_a0 == (s32) func_80062F68((u8) temp_s1)) {
                    return temp_s1;
                }
                var_s0 += 1;
            } while (var_s0 != 0x3A);
        }
    }
    return 0;
}

u8 func_80063014(u8 arg0) { extern u8 D_80097E4F[]; if (arg0 > 0 && arg0 < 0x38) return D_80097E4F[arg0]; return 0; }

s32 func_80063044(u8 arg0) {
    s32 temp_a0;
    s32 temp_s1;
    s32 var_s0;

    temp_a0 = arg0;
    if (temp_a0 > 0) {
        var_s0 = 1;
        if (temp_a0 < 0xA6) {
            do {
                temp_s1 = var_s0 & 0xFF;
                if (temp_a0 == (s32) func_80063014((u8) temp_s1)) {
                    return temp_s1;
                }
                var_s0 += 1;
            } while (var_s0 != 0x38);
        }
    }
    return 0;
}

extern u8 func_80062D98(u8);s32 func_800630C0(u8 arg0){return func_80062D98(arg0)<0x14;}
#endif
