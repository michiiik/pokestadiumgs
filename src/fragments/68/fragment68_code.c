#include "global.h"


#ifdef VERSION_US
extern void* func_80041C98(s32 arg0);
extern void func_80041E2C(void);
extern u16* func_80042C68(void* arg0, s32 arg1, s32 arg2);
extern u16* D_8F000924;
extern s32 D_8F00092C;
extern s32 D_8F000920;

void func_8F000020(s32 arg0) {
    void* var_v0;

    var_v0 = func_80041C98(5);
    func_80041E2C();
    D_8F000924 = func_80042C68(var_v0, 128, 128);
    *D_8F000924 &= 0xFEFF;
    D_8F00092C = 0;
    D_8F000920 = 0;
    if (arg0 != 0) {
        D_8F000920 = arg0 - 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/68/fragment68_code/func_8F000098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/68/fragment68_code/func_8F000284.s")

extern void func_80008648();
extern void func_800088DC();
extern void func_8F000098();
extern void func_8F000284();

void func_8F0004EC(void) {
    func_800088DC();
    func_8F000284();
    func_8F000098();
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/68/fragment68_code/func_8F000524.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/68/fragment68_code/func_8F00068C.s")

extern s32 D_8F000920;
s32 func_8F0007C8(void) {
    s32 result = 0;
    if (D_8F000920 >= 0) result = D_8F000920 + 1;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/68/fragment68_code/func_8F0007E8.s")
#endif
