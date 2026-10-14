#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41A5F0/func_84201170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41A5F0/func_84201234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41A5F0/func_8420138C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41A5F0/func_84201408.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41A5F0/func_8420151C.s")

typedef struct unk_func_84201620 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02[18];
    u32* unk_14;
} unk_func_84201620;

extern void func_8420138C(void* arg0);

void func_84201620(unk_func_84201620* arg0) {
    if ((*arg0->unk_14 & 1) == 0) {
        if ((arg0->unk_01 != 38) && (arg0->unk_01 != 40) && (arg0->unk_01 != 41) &&
            (arg0->unk_01 != 87) && (arg0->unk_01 != 88) && (arg0->unk_01 != 148)) {
            func_8420138C(arg0);
        }
    }
}

void func_8420168C(void *arg0) { func_84201408(arg0); func_8420151C(arg0); func_84201620(arg0); }

typedef struct unk_func_842016BC {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05[7];
    s32 unk_0C;
    s32 unk_10;
} unk_func_842016BC;

extern u8 func_80062D20(u8 arg0);
extern u8 func_80062D5C(u8 arg0);
extern u8 func_80062D98(u8 arg0);
extern u8 func_80062DD4(u8 arg0);

void func_842016BC(u8 arg0, unk_func_842016BC* arg1) {
    arg1->unk_00 = arg0;
    arg1->unk_01 = func_80062D20(arg0);
    arg1->unk_02 = func_80062D5C(arg0);
    arg1->unk_03 = func_80062D98(arg0);
    arg1->unk_04 = func_80062DD4(arg0);
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/80/fragment80_41A5F0/func_84201728.s")

void func_84201794(u8 *arg0) { if (arg0[1] == 0x26) { func_84201728(); } }
#endif
