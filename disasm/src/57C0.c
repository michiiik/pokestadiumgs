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
s32 func_80004BEC(u8 *arg0) {
    OSMesg msg;
    return osRecvMesg((OSMesgQueue *)(arg0 + 4), &msg, 1);
}
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
OSMesg func_80004F34(u8 *arg0) {
    OSMesg msg;
    osRecvMesg((OSMesgQueue *)(arg0 + 0x1C0), &msg, 1);
    return msg;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/57C0/func_80004F60.s")
#endif

#ifdef VERSION_US
extern u32 D_800CD020[];

void func_80004FA4(void) {
    if (D_800CD020[0xA18 / 4] == 0 && D_800CD020[0xA20 / 4] != 0) {
        D_800CD020[0xA18 / 4] = D_800CD020[0xA20 / 4];
        D_800CD020[0xA20 / 4] = 0;
    }
    if (D_800CD020[0xA1C / 4] == 0 && D_800CD020[0xA24 / 4] != 0) {
        D_800CD020[0xA1C / 4] = D_800CD020[0xA24 / 4];
        D_800CD020[0xA24 / 4] = 0;
    }
}
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
extern u32 D_800CDA34;

void func_800050D4(void) {
    if (D_800CD020[0xA14 / 4] == 0) {
        D_800CDA34 = (u32)func_800050A0((void *)D_800CD020[0xA1C / 4]);
    }
}
#endif

#ifdef VERSION_US
s32 func_80004CF4(u32);

s32 func_80005110(void) {
    s32 var_v1;

    var_v1 = 0;
    if (D_800CDA34 != 0) {
        var_v1 = func_80004CF4(D_800CDA34);
    }
    return var_v1;
}
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
