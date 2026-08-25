#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700DD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700E38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700E70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700EC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700EFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700FA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700FF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_8270103C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827010F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701278.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701300.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827013F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827015A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_8270160C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_8270174C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701820.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_8270188C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701920.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701978.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701CB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701DF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701F7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827020F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_8270216C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702220.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702364.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702528.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827025F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702658.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702810.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702954.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702A2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702BC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702CD8.s")

extern void func_82702954();
extern void func_82702A2C();
extern void func_82702BC8();
extern void func_82702CD8();
void func_82702DF8(s16 *arg0) {
    s16 temp_v0;

    temp_v0 = *arg0;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82702954();
        return;
    case 2:
        func_82702A2C();
        return;
    case 3:
        func_82702BC8();
        return;
    case 4:
        func_82702CD8();
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702E78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702F70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827030D0.s")

extern u16 D_827034EC;
extern s16 D_827034EA;
s32 func_82703188(void) {
    s32 result = -2;
    if (D_827034EC & 1) {
        result = D_827034EA;
    }
    return result;
}
#endif
