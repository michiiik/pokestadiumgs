#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_800015C0.s")
#endif

#ifdef VERSION_US

extern void func_800055F4(void *, s32);
void func_80001684(void *arg0, void *arg1, s32 arg2) {
    *(u32 *)((u8 *)arg0 + 0x50) = *(u32 *)((u8 *)arg1 + 4);
    *(u32 *)((u8 *)arg0 + 0x54) = *(u32 *)((u8 *)arg1 + 8);
    func_800055F4(arg0, arg2);
}
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

extern u8 leoDiskID[];
extern void func_80004F34(void *);
extern void func_80004F60(void *);

void func_80001AC8(void) {
    func_80004F34(leoDiskID);
    if (*(s32 *)(leoDiskID + 0x1C8) > 0) {
        do {
            func_80004F60(leoDiskID);
        } while (*(s32 *)(leoDiskID + 0x1C8) > 0);
    }
    func_80004F34(leoDiskID);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/dp_intro/func_80001B20.s")
#endif

void func_80001CA8(void) {
}

#ifdef VERSION_US

s32 func_80001CB0(arg0)
s32 arg0;
{
    s32 result = 0;
    if (arg0 == 1) {
        goto set_result;
    }
    if (arg0 != 2) {
        goto done;
    }
set_result:
    result = 1;
done:
    return result;
}
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

extern u8 *D_800AB3C0;
s32 func_80001E70(void) {
    s32 result = 1;
    u16 *ptr = *(u16 **)(D_800AB3C0 + 8);
    u16 expected = *ptr;
    s32 count = 0x27F;

    do {
        if (expected != *ptr++) {
            result = 0;
        }
    } while (count-- > 0);
    return result;
}
#endif

#ifdef VERSION_US
extern u8 *D_800AB3C0;
s32 func_80001EB8(void) { u8 *ptr = *(u8 **)(D_800AB3C0 + 8); return *(u16 *)ptr; }
#endif

#ifdef VERSION_US
extern u8 *D_800AB3C0; extern void *osViGetCurrentFramebuffer(void);
s32 func_80001ECC(void) { s32 result = 0; if (osViGetCurrentFramebuffer() == *(void **)(D_800AB3C0 + 8)) result = 1; return result; }
#endif

#ifdef VERSION_US
void func_80001F08(void) { extern OSMesgQueue D_800AB3E4; osRecvMesg(&D_800AB3E4, NULL, OS_MESG_BLOCK); }
#endif

#ifdef VERSION_US

extern OSMesgQueue D_800AB3CC;
void func_80001F34(s32 arg0) {
    osSendMesg(&D_800AB3CC, (OSMesg)arg0, NULL);
}
#endif

#ifdef VERSION_US
void func_80001F60(s32 arg0) {
    while (arg0-- > 0) {
        func_80001F34(0);
        func_80001F08();
    }
}
#endif

#ifdef VERSION_US
void func_80001FA8(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7) {
    arg0[1] = arg1;
    arg0[2] = arg2;
    arg0[0] = arg3;
    arg0[3] = arg4;
    *(s32 *)(arg0 + 4) = arg5;
    *(s32 *)(arg0 + 8) = arg6;
    *(s32 *)(arg0 + 0xC) = arg7;
}
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
