#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14A2E0/func_82700020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14A2E0/func_827000B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14A2E0/func_8270030C.s")

extern s32 D_827031C8;
s32 func_82700598(s32 arg0, s32 arg1) {
    if ((arg0 != 0) && (arg0 == 5) && (D_827031C8 != 0)) {
        func_8270030C(D_827031C8);
        func_8003CD84();
    }
    return 0;
}

void func_827005E4(u16 *arg0, u8 *arg1) {
    arg0[0] = 0;
    arg0[1] = arg1[0];
    arg0[2] = (arg1[1] & 1) != 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14A2E0/func_82700604.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14A2E0/func_82700788.s")

extern void *D_827031C4;
extern void *D_82703358;
extern s32 func_80043678(void *);
extern void func_800088DC(void);
extern void func_82700788(void);
extern void func_8003C6B8(void *);
extern void func_82702F70(void);
extern void func_80008648(void);
void func_82700924(void) {
    D_827031C8 = func_80043678(D_827031C4);
    func_800088DC();
    func_82700788();
    func_8003C6B8(D_82703358);
    func_82702F70();
    func_80008648();
}

extern void func_82703188(void);
void func_82700978(void) {
    func_82703188();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14A2E0/func_82700998.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14A2E0/func_82700AF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14A2E0/func_82700B84.s")
#endif
