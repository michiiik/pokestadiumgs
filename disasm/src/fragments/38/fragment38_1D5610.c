#include "global.h"


#ifdef VERSION_US
extern u8 *D_88904190;
u8 *func_88900020(void) {
    return D_88904190 + 0x6C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900030.s")

extern u8 *D_88904190;
extern void func_800033DC(void *arg0);
extern void main_pool_pop_state(s32 arg0);
void func_88900494(void) {
    func_800033DC(D_88904190);
    main_pool_pop_state(0x45564F56);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_889004C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900528.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_8890055C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900638.s")

extern u8 *D_88904190;
void func_88900754(void) {
    u8 *ptr = D_88904190;
    if (*(u32 *)(ptr + 0x44) != 0) {
        *(s32 *)(*(u8 **)(ptr + 0x48) + 0x2C) = 1;
    }
}

extern void func_80049ED8(void *arg0);
extern void *D_80087200;
void func_8890077C(void) {
    func_80049ED8(D_80087200);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_889007A0.s")

extern u8 *D_88904190;
extern void func_889033FC(void *arg0, void *arg1);
void func_88900ADC(void) {
    func_889033FC(*(void **)(D_88904190 + 4), D_88904190 + 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900B08.s")

void func_88900C54(void) {
    func_80049ED8(D_80087200);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900C78.s")

extern u8 *D_88904190;
extern void func_889035FC(void *arg0);
void func_88900D8C(void) {
    func_889035FC(D_88904190 + 0x48);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900DB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900EE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88900F54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88901A24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_88902624.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/38/fragment38_1D5610/func_889027A4.s")
#endif
