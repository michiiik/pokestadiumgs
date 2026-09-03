#include "global.h"


void func_8414F260(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BEAF0/func_8414F268.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BEAF0/func_8414F2F4.s")
#endif

#ifdef VERSION_US
extern u8 func_84154B24(void);
void func_8414F3FC(void *arg0) {
    u8 value = func_84154B24();
    if (*(u16 *)((u8 *)arg0 + value * 2 + 2) < 0xB2) {
        *(u8 *)arg0 |= 0x10;
    }
}
#endif

#ifdef VERSION_US
extern u8 *func_84154B64(u8);
extern s32 func_841556C4(u8 *, u8);
void func_8414F444(u8 *arg0, u8 arg1) {
    u8 value = func_84154B24();
    if (func_841556C4(func_84154B64(1 - value), arg1) != 0) {
        *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0x18) - *(s32 *)(arg0 + 0x14);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BEAF0/func_8414F4A0.s")
#endif

#ifdef VERSION_US
extern void func_8414F268(void *);
extern void func_8414F2F4(void *);
void func_8414F5F0(void *arg0) {
    func_8414F268(arg0);
    func_8414F2F4(arg0);
}
#endif

#ifdef VERSION_US
extern void func_8414F5F0(void *);
extern void func_8414F3FC(void *);
void func_8414F618(void *arg0) {
    u8 value;
    u8 *ptr;
    func_8414F5F0(arg0);
    value = func_84154B24();
    ptr = func_84154B64(1 - value);
    if (*(u16 *)(ptr + 0x26) & 0x20) {
        func_8414F3FC(arg0);
    }
}
#endif

#ifdef VERSION_US
extern u8 *func_8414A3A0(u8);
extern void func_8414F444(u8 *, u8);
void func_8414F668(u8 *arg0) {
    u8 value = func_84154B24();
    u8 *ptr = func_8414A3A0(value);
    if ((*(s32 *)ptr << 15) >= 0) {
        func_8414F444(arg0, 0x11);
        func_8414F444(arg0, 0x5E);
        func_8414F444(arg0, 0x19);
        func_8414F444(arg0, 0x71);
    }
}
#endif

#ifdef VERSION_US
void func_8414F6D0(void *arg0) {
    u8 value;
    u8 *ptr;
    func_8414F2F4(arg0);
    value = func_84154B24();
    ptr = func_8414A3A0(value);
    if ((*(s32 *)ptr << 15) >= 0) {
        func_8414F444(arg0, 0x11);
        func_8414F444(arg0, 0x5E);
        func_8414F444(arg0, 0x19);
        func_8414F444(arg0, 0x71);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BEAF0/func_8414F748.s")
#endif

#ifdef VERSION_US
extern void func_8414F4A0(s32, s32);
void func_8414F894(s32 arg0) { func_8414F4A0(arg0, 83); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BEAF0/func_8414F8B4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BEAF0/func_8414F93C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BEAF0/func_8414FA3C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BEAF0/func_8414FB24.s")
#endif
