#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3749B0/func_84105120.s")

extern s32 D_841901AC;
extern s32 func_84108654(u16, u16);
extern s32 func_8410922C(s32, u16);
s32 func_841051D8(u16 arg0, u16 arg1) {
    if (arg0 < 0x2000) {
        return func_84108654(arg0, arg1);
    }
    if (arg0 & 0x1000) {
        D_841901AC = 1;
        return func_8410922C(arg0 - 0x3000, arg1);
    }
    D_841901AC = 0;
    return func_8410922C(arg0 - 0x2000, arg1);
}

extern s32 func_841051D8(u16, u16);
void func_84105250(u16 *arg0, u16 arg1) {
    u16 value;
    value = *arg0;
    while (value != 0) {
        func_841051D8(value, arg1);
        arg0++;
        value = *arg0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3749B0/func_841052AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3749B0/func_8410545C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3749B0/func_841054D4.s")

extern void func_841054D4(void);
extern void func_84105B90(u8 *);
extern void func_841052AC(void);
extern void func_8410545C(void);
extern void func_84107B68(void);
extern void func_841029DC(void);
extern void func_841092B8(u8 *);
extern void func_84105CE8(void);
void func_841055D8(u8 *arg0) {
    func_841054D4();
    func_84105B90(arg0);
    func_841052AC();
    func_8410545C();
    func_84107B68();
    func_841029DC();
    func_841092B8(arg0);
    func_84105CE8();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3749B0/func_84105630.s")

extern void func_84105120(void);
extern void func_841055D8(u8 *);
extern void func_84105630(u8 *, s32);
s32 func_8410580C(s32 arg0, u8 *arg1, s32 arg2) {
    switch (arg0) {
    case 0:
        func_84105120();
        break;
    case 2:
        func_841055D8(arg1);
        break;
    case 5:
        func_84105630(arg1, arg2);
        break;
    }
    return 0;
}
#pragma C_FUNCTION_PADDING(12)
#endif
