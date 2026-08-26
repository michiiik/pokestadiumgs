#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF14E40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF15080.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF15120.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF152A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF15384.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF154EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF15584.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF15670.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF15954.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF15AD8.s")

extern void func_8AF15670(s32);
extern void func_8AF15AD8(s32);
extern s16 D_8AF33C78;
s32 func_8AF15E80(s32 arg0, s32 arg1) {
    if ((arg0 != 0) && (arg0 == 1)) {
        switch (D_8AF33C78) {                       /* irregular */
        case 0:
        case 1:
            func_8AF15670(arg1);
            break;
        case 2:
        case 3:
            func_8AF15AD8(arg1);
            break;
        }
    }
    return 0;
}

extern s16 D_8AF33C72;
extern s16 D_8AF33C74;
extern s16 D_8AF33C76;
extern s16 D_8AF33C7C;

void func_8AF15EF0(void) {
    D_8AF33C72 = 0;
    D_8AF33C74 = 8;
    D_8AF33C76 = 8;
    D_8AF33C78 = 0;
    D_8AF33C7C = D_8AF33C74;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF15F28.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF16064.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_2030B0/func_8AF1666C.s")
#endif
