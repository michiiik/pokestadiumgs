#include "global.h"


#ifdef VERSION_US
extern s32 D_82615330;
void func_826005F0(s32 arg0) {
    D_82615330 = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_1286C0/func_826005FC.s")

extern void func_80008648();
extern void BgStage_DrawFrame();
extern void func_826005FC();
extern void func_82602710(s32);
extern void func_826042A0();
extern s32 D_8261533C;
void func_826007E4(void) {
    BgStage_DrawFrame();
    func_82602710(D_82615330);
    func_826042A0();
    if (D_8261533C != 0) {
        func_826005FC();
    }
    func_80008648();
}

/* D_82615330 is declared s32 earlier in this file; the (u8 *)D_82615330 casts
 * load that value and dereference it as the stage-state pointer. */

extern s32 StageContext_GetFadeMode(void);
extern void *D_80087200;

s32 func_82600838(s32 arg0) {
    s32 var_a2;
    void *var_v1;
    /* FAKE: exists only so the three `*base` reads constant-propagate to ugen's
     * `lw $r, D_80087200` macro form (as1: lui %hi + lw %lo with base=dest in
     * v1) instead of routing through the live la of the bare reads; removing it
     * re-joins those loads to the a3 la web and loses the reload pairs. */
    void **base;

    base = &D_80087200;
    var_a2 = arg0;
    switch (arg0) {
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            var_a2 = 1;
        }
        break;
    case 1:
        if (*(u16 *)((u8 *)*(void **)D_82615330 + 8) != 0x500) {
            if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x800) {
                *(s16 *)((u8 *)D_82615330 + 0x16) = *(s16 *)((u8 *)D_82615330 + 0x16) - 1;
                if (*(s16 *)((u8 *)D_82615330 + 0x16) < 0) {
                    *(s16 *)((u8 *)D_82615330 + 0x16) = *(s16 *)((u8 *)D_82615330 + 0x14) - 1;
                }
            }
            if (*(u16 *)((u8 *)D_80087200 + 0xC) & 0x400) {
                *(s16 *)((u8 *)D_82615330 + 0x16) = *(s16 *)((u8 *)D_82615330 + 0x16) + 1;
                if (*(s16 *)((u8 *)D_82615330 + 0x16) >= *(s16 *)((u8 *)D_82615330 + 0x14)) {
                    *(s16 *)((u8 *)D_82615330 + 0x16) = 0;
                }
            }
            var_v1 = *base;
        } else {
            var_v1 = D_80087200;
            if (*(u16 *)((u8 *)var_v1 + 0xC) & 0x800) {
                *(s32 *)((u8 *)D_82615330 + 0x98) = *(s32 *)((u8 *)D_82615330 + 0x98) + 1;
                var_v1 = *base;
            }
            if (*(u16 *)((u8 *)var_v1 + 0xC) & 0x400) {
                *(s32 *)((u8 *)D_82615330 + 0x98) = *(s32 *)((u8 *)D_82615330 + 0x98) - 1;
                var_v1 = *base;
            }
        }
        if (*(u16 *)((u8 *)var_v1 + 8) & 0x8000) {
            var_a2 = 3;
        }
        break;
    }
    return var_a2;
}
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_1286C0/func_826009A0.s")
#endif
