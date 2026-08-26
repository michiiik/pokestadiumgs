#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00020.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00380.s")
#endif

#ifdef VERSION_US
extern void func_80037120(s32, s32, s32 *, s16 *, s16 *);
extern s32 D_80094908;
s32 func_8FA004CC(s32 arg0, void *arg1) {
    s16 pad;
    s32 sp28;
    s16 sp26;
    s16 sp24;
    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &sp28, &sp26, &sp24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(sp26 + 0x2000);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(sp24 - 0x2000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
s32 func_8FA00534(s32 arg0, void *arg1) {
    s16 pad;
    s32 sp28;
    s16 sp26;
    s16 sp24;
    if (arg0 == 2) {
        func_80037120(D_80094908 + 0xB4, D_80094908 + 0xA8, &sp28, &sp26, &sp24);
        *(s16 *)((u8 *)arg1 + 0x1C) = (s16)(-0x2000 - sp26);
        *(s16 *)((u8 *)arg1 + 0x1E) = (s16)(sp24 + 0x6000);
    }
    return 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA005A0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA0069C.s")
#endif

void func_8FA0071C(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00724.s")
#endif

void func_8FA00AC0(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00AC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00E2C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA00F4C.s")
#endif

#ifdef VERSION_US
s32 func_800542B0(s16);
extern void func_800542E4(s16, s32);
void func_8FA010B0(s16 arg0, s16 arg1, u8 arg2) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;

    temp_v1 = (1 << arg0) & 0xFF;
    temp_a0 = func_800542B0(arg1) & ~temp_v1;
    var_a1 = temp_a0 & 0xFF;
    if (arg2 != 0) {
        var_a1 = (temp_a0 | temp_v1) & 0xFF;
    }
    func_800542E4(arg1, var_a1);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA01110.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA0125C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA01718.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA017B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/75/fragment75_code/func_8FA01830.s")
#endif
