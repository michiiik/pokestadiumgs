#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EBD0/func_8411F340.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_38EBD0/func_8411F400.s")

extern void Vec3f_SetComponentsDuplicate(f32 *, f32, f32, f32);
extern void func_800371B4(void *, void *, s32, s32, s32);
void func_8411F4F4(u8 *arg0, u8 *arg1) {
    Vec3f_SetComponentsDuplicate((f32 *)(arg0 + 0xB4), *(f32 *)(*(u8 **)(arg1 + 0x668) + 8), *(f32 *)(*(u8 **)(arg1 + 0x668) + 0xC), 0.0f);
    func_800371B4(arg0 + 0xB4, arg0 + 0xA8, *(s32 *)(*(u8 **)(arg1 + 0x668) + 4), *(s16 *)(*(u8 **)(arg1 + 0x668) + 0), *(s16 *)(*(u8 **)(arg1 + 0x668) + 2));
}

extern void func_8411F400();
extern void func_8411F4F4();
void func_8411F558(u8 *arg0, s32 arg1) {
    func_8411F400(arg0, arg1);
    func_8411F4F4(arg0, arg1);
    arg0[1] |= 0x10;
}

extern u8 *main_pool_alloc(s32, s32);
extern u8 *D_84193F80[2];
extern u8 *D_84193F88;
extern u8 *D_84193F8C;
void func_8411F598(void) {
    D_84193F80[0] = main_pool_alloc(0x19C, 0);
    D_84193F80[1] = main_pool_alloc(0x19C, 0);
    D_84193F88 = D_84193F80[0];
    D_84193F8C = D_84193F80[1];
}

extern s32 D_84191208;
extern s32 D_8419120C;
extern void func_8003F018(u8 *);
void func_8411F5F4(s32 arg0, s32 arg1) {
    *(s32 *)(D_84193F88 + 0x168) = arg0;
    func_8003F018(D_84193F88);
    func_8411F400(arg0, D_84191208);
    func_8411F4F4(arg0, D_84191208);
    *(s32 *)(D_84193F8C + 0x168) = arg1;
    func_8003F018(D_84193F8C);
    func_8411F400(arg1, D_8419120C);
    func_8411F4F4(arg1, D_8419120C);
}

void func_8411F688(u8 *arg0, s32 arg1) {}

extern void func_8411F598(void);
extern void func_8411F5F4(s32, s32);
s32 func_8411F694(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg0) {
    case 0: func_8411F598(); break;
    case 1:
    case 2: func_8411F688((u8 *)arg1, arg2); break;
    case 3: func_8411F5F4(arg1, arg2); break;
    }
    return 0;
}
#endif
