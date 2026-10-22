#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32C420/func_87F097B0.s")

extern void _bzero(void *, s32);
void func_87F09870(s32 *arg0) { _bzero(arg0, 0x1C); *arg0 = 0; }

extern void Audio_PlayDefaultSound(s32);
void func_87F0989C(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + (0))) = 1;
    (*(s32 *)((u8 *)(arg0) + (0x18))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x14))) = -0x100;
    (*(f32 *)((u8 *)(arg0) + (4))) = 160.0f;
    (*(f32 *)((u8 *)(arg0) + (0xC))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (0x10))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (8))) = 240.0f;
    Audio_PlayDefaultSound(0xCF11);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32C420/func_87F098F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32C420/func_87F09B7C.s")

extern void func_87F0E390(u8 *, s32);
extern s32 func_8004DC6C(s32);
extern s32 main_pool_get_available(void);
extern u8 *MainPool_AllocState(s32, s32);
extern s32 func_8004EB58(s32, s32);
extern void MainPool_FinalizeAllocation(void *);
extern void func_8004DCFC(u8 *, s32 *);
extern s32 func_8004C8C0(u16);

void func_87F09EBC(u8 *arg0, s32 arg1) {
    u8 *sp2C;
    s32 sp28;
    void *var_v1;

    func_87F0E390(arg0 + 0x58, arg1);
    *(s32 *)(arg0 + 0) = func_8004DC6C(0x5D);
    if (*(s32 *)(arg0 + 0) != 0) {
        sp2C = MainPool_AllocState(main_pool_get_available(), 0);
        *(s32 *)(arg0 + 0x10) = func_8004EB58((s32)sp2C, *(s32 *)(arg0 + 0));
        MainPool_FinalizeAllocation(sp2C);
    }
    *(s32 *)(arg0 + 4) = func_8004DC6C(0x5E);
    if (*(s32 *)(arg0 + 4) != 0) {
        sp2C = MainPool_AllocState(main_pool_get_available(), 0);
        *(s32 *)(arg0 + 0x14) = func_8004EB58((s32)sp2C, *(s32 *)(arg0 + 4));
        MainPool_FinalizeAllocation(sp2C);
    }
    *(s32 *)(arg0 + 8) = func_8004DC6C(0x5F);
    if (*(s32 *)(arg0 + 8) != 0) {
        sp2C = MainPool_AllocState(main_pool_get_available(), 0);
        *(s32 *)(arg0 + 0x18) = func_8004EB58((s32)sp2C, *(s32 *)(arg0 + 8));
        MainPool_FinalizeAllocation(sp2C);
    }
    *(s32 *)(arg0 + 0xC) = func_8004DC6C(0x60);
    if (*(s32 *)(arg0 + 0xC) != 0) {
        sp2C = MainPool_AllocState(main_pool_get_available(), 0);
        *(s32 *)(arg0 + 0x1C) = func_8004EB58((s32)sp2C, *(s32 *)(arg0 + 0xC));
        MainPool_FinalizeAllocation(sp2C);
    }
    func_8004DCFC((u8 *)*(s32 *)(arg0 + 0), &sp28);
    *(s32 *)(arg0 + 0x20) |= sp28;
    func_8004DCFC((u8 *)*(s32 *)(arg0 + 4), &sp28);
    *(s32 *)(arg0 + 0x20) |= sp28;
    func_8004DCFC((u8 *)*(s32 *)(arg0 + 8), &sp28);
    *(s32 *)(arg0 + 0x20) |= sp28;
    func_8004DCFC((u8 *)*(s32 *)(arg0 + 0xC), &sp28);
    *(s32 *)(arg0 + 0x20) |= sp28;
    func_8004C8C0(444);
    func_8004C8C0(445);
    var_v1 = *(void **)(arg0 + 0x10);
    *(s32 *)(arg0 + 0x38) = 0;
    *(void **)(arg0 + 0x24) = var_v1;
    *(s16 *)((u8 *)var_v1 + 0xA) = -0xF0;
    *(s32 *)(arg0 + 0x30) = 0;
    *(s32 *)(arg0 + 0x34) = 0;
    *(f32 *)(arg0 + 0x28) = -240.0f;
    *(f32 *)(arg0 + 0x2C) = 0.0f;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32C420/func_87F0A098.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32C420/func_87F0A3E8.s")

extern void func_800503A4(s32);
extern void func_87F09B7C(void *);
void func_87F0A5BC(void *arg0) {
    func_800503A4(*(s32 *)((u8 *)arg0 + 0x24));
    func_87F09B7C((u8 *)arg0 + 0x3C);
}
#endif
