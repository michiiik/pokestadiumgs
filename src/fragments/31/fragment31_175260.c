#include "global.h"


#ifdef VERSION_US
/* mkdraft:func_88201FE0 begin */
u8 func_80062F68(u8);
u8 func_80063014(u8);
s32 func_88A008CC(u8 *);
extern u8 D_88A01B80[];

u8 func_88201FE0(u8 *arg0) {
    s32 i;

    if (func_88A008CC(arg0) != 0) {
        if (arg0[0] >= 0xC9 && arg0[0] < 0xFB) {
            return func_80063014(arg0[0] - 0xC8);
        }
        if (arg0[0] >= 0xC4 && arg0[0] < 0xC9) {
            return func_80063014(arg0[0] - 0x91);
        }
    } else {
        for (i = 0; i != 0x39; i++) {
            if (arg0[0] == D_88A01B80[i]) {
                return func_80062F68(i + 1);
            }
        }
    }
    return 0;
}
/* mkdraft:func_88201FE0 end */

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_88202098.s")

extern u8 func_8006378C(u8);
s32 func_88202104(u8 arg0) {
    s32 result = 0;

    if (func_8006378C(arg0) == 2 || (arg0 >= 0xF3 && arg0 < 0xFA)) {
        result = 1;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_88202158.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_882025B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_882026A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_882027F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_88202AA0.s")

extern s32 func_88202098(u8);
extern s32 func_88A008CC(u8 *);
extern s32 func_88A0083C(u8 *);
extern void func_88A015A0(s32);
extern u8 *D_88A01C64;

void func_88202F0C(u8 *arg0) {
    s32 var_v0;

    if (func_88A008CC(arg0) != 0) {
        var_v0 = func_88202098(arg0[0]) == 0;
    } else {
        var_v0 = func_88202104(arg0[0]) == 0;
    }
    if (var_v0 != 0) {
        var_v0 = func_88A0083C(arg0);
        *(s32 *)(D_88A01C64 + var_v0 * 4 + 260) = 1;
        if (--arg0[1] == 0) {
            func_88A015A0(var_v0);
        }
    }
}

extern void func_88202F0C(u8 *);
void func_88202FA0(void *a0, u8 *a1) {
    *(u8 *)((u8 *)a0 + 9) = *(u8 *)a1;
    *(s32 *)((u8 *)*(void **)a0 + 0xC) = 1;
    func_88202F0C(a1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_88202FD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_175260/func_882033B0.s")
#endif
