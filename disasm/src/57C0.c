#include "global.h"


#ifdef VERSION_US
extern void osWritebackDCacheAll(void);

void func_80004BC0(u8 *arg0) {
    osWritebackDCacheAll();
    *(u16 *)(arg0 + 0x1C) = 0;
    *(u16 *)(arg0 + 0x1E) = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004BEC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004C14.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004CF4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004D4C.s")
#endif

#ifdef VERSION_US
extern s32 func_8000A1E8(s32);

void func_80004EA8(u8 *arg0) {
    func_8000A1E8(2);
    if (*(u16 *)(arg0 + 0x1C) == 3) {
        osSendMesg((OSMesgQueue *)(arg0 + 4), (OSMesg)0x444F4E45, 0);
    }
    *(u16 *)(arg0 + 0x1E) = 2;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004F00.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004F34.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004F60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004FA4.s")
#endif

void func_80004FF4(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004FFC.s")
#endif

#ifdef VERSION_US
void *func_800050A0(void *arg0) {
    if (arg0 && !func_80004C14(arg0)) {
        arg0 = 0;
    }
    return arg0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_800050D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80005110.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80005148.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_800051B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_800052C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80005388.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_800053D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/Thread3_CreateThread.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80005568.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_800055B0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_800055F4.s")
#endif
