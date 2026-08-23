#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_800015C0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001684.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/Vi_SelectMode.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_8000177C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_800017F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001AC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001B20.s")
#endif

void func_80001CA8(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001CB0.s")
#endif

void func_80001CD4(void) {
}

#ifdef VERSION_US
void func_80001CDC(void) { func_80001CB0(); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/Thread5_CreateThread.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001E18.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001E70.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001EB8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001ECC.s")
#endif

#ifdef VERSION_US
void func_80001F08(void) { extern OSMesgQueue D_800AB3E4; osRecvMesg(&D_800AB3E4, NULL, OS_MESG_BLOCK); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001F34.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001F60.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001FA8.s")
#endif

#ifdef VERSION_US
extern s32 D_800AB49C;
s32 func_80001FE4(void) {
    return D_800AB49C;
}
#endif

#ifdef VERSION_US
s32 func_80001FF0(void) { extern s32 osTvType; return osTvType == 0 ? 0x32 : 0x3C; }
#endif

#ifdef VERSION_US
extern u8 D_800AB46B;
u8 func_80002014(void) {
    return D_800AB46B;
}
#endif

#ifdef VERSION_US
void func_80002020(void) { extern u8 leoDiskID[]; Vi_SelectMode(*(s8 *)(leoDiskID + 0xAB1), *(s8 *)(leoDiskID + 0xAB2)); }
#endif

#ifdef VERSION_US
s32 func_8000204C(void) { extern u8 leoDiskID[]; s32 ready = 1; if (*(s32 *)(leoDiskID + 0xAA4) != 0) ready = *(s32 *)(leoDiskID + 0xA2C) > 0; return ready; }
#endif

#ifdef VERSION_US
extern s32 D_800871D0;
void func_80002074(void) {
    D_800871D0 = 1;
}
#endif

#ifdef VERSION_US
extern s32 D_800871D0;
void func_80002084(void) {
    D_800871D0 = 0;
}
#endif

#ifdef VERSION_US
extern f32 D_800AB46C;
f32 func_80002090(void) {
    return D_800AB46C;
}
#endif
