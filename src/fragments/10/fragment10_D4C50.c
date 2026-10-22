#include "global.h"


#ifdef VERSION_US
extern void _bzero(void *, s32);
extern s32 func_8004C8C0(u16);
extern s32 func_8004D690(s32);
extern s32 main_pool_get_available(void);
extern u8 *MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(void *);
extern void *func_81600E28(void *, s32, s32);
extern void func_82801510(void *, s32, s32, s32, s32);

void func_82800020(u8 *arg0, s16 *arg1, s32 arg2) {
    u8 *var_v0;

    _bzero(arg0, 192);
    func_8004C8C0(341);
    func_8004C8C0(54);
    *(s32 *)(arg0 + 180) = func_8004D690(arg1[0]);
    var_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    *(void **)(arg0 + 8) = func_81600E28(var_v0, 1, 25);
    *(s16 **)(arg0 + 184) = arg1;
    MainPool_FinalizeAllocation(var_v0);
    func_82801510(arg0 + 12, arg1[1], arg2, *(s32 *)(arg1 + 2), *(s32 *)(arg0 + 180));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D4C50/func_828000CC.s")

extern void func_81600954(void *);
extern void func_81600A34(void *, s32, s32, s32, s32, s32, s32);
extern void func_82801BE8(void *, void *);
extern void func_81600B30(void *);
void func_8280018C(u8 *arg0, s32 arg1) {
    func_81600954(*(void **)(arg0 + 8));
    func_81600A34(*(void **)(arg0 + 8), *(s32 *)(arg0 + 0xB4), arg1 == 0, 0, 0, 640, 480);
    func_82801BE8(arg0 + 0xC, *(void **)(arg0 + 8));
    func_81600B30(*(void **)(arg0 + 8));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/10/fragment10_D4C50/func_828001FC.s")

/* mkdraft:fragment10_main begin */
extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern s32 func_8004C09C(s32);
extern u8 *func_80047588(s32, s32);
extern u8 *Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern u8 D_1000000[], D_446E30[], D_447D00[];
extern void func_80008514(s32);
extern void func_80008624(void);
extern void func_800086A4(s32);
extern void StageLoader_WaitForRetrace(void);
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void func_816031AC(void);
extern s32 func_828001FC(u8 *);
extern void func_828027C0(u8 *);
extern u8 D_828029A0[];
extern u8 D_828029AC[];
extern s32 D_82802A5C;

s32 fragment10_main(s32 arg0, s16 *arg1) {
    s32 configuration;
    s32 result;

    main_pool_push_state(0x43535050);
    if ((*(s32 *)(arg1 + 2) << 5) >= 0) {
        Gfx_InitDisplayListBuffers(0x10000, 0);
        configuration = func_800082E0(1, 0, 2, 0, 2, 1);
    }
    func_8004C09C(0x107);
    func_816031AC();
    func_8004C8C0(0x154);
    func_80047588(0x1C, 0);
    Asset_LoadToSegment(((u32)D_1000000 & 0x0F000000) >> 24, D_446E30, D_447D00, 0);
    func_82800020(D_828029A0, arg1, arg0);
    if ((*(s32 *)(arg1 + 2) << 5) < 0) {
        func_80008624();
    } else {
        func_80008514(configuration);
    }
    result = func_828001FC(D_828029A0);
    if (D_82802A5C != 0) {
        func_800086A4(2);
    }
    func_828027C0(D_828029AC);
    func_80047610();
    func_8004C398();
    if ((*(s32 *)(arg1 + 2) << 5) < 0) {
        StageLoader_WaitForRetrace();
    } else {
        func_80008574();
        Gfx_FreeDisplayListBuffers();
    }
    main_pool_pop_state(0x43535050);
    return result;
}
/* mkdraft:fragment10_main end */
#endif
