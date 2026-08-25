#include "global.h"


#ifdef VERSION_US
extern void func_80049ED8(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_88229AE0(void) {
    func_80049ED8(D_80087200);
    D_880068B8 = 0;
}

extern void func_800033DC(s32);
extern s32 D_880068B4;
extern u32 D_882348C0;
void func_88229B08(void) {
    func_80049ED8(D_80087200);
    D_880068B4 = 1;
    func_800033DC(D_882348C0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19CD60/func_88229B44.s")

extern u32 D_882348C0;
extern void func_8821D930(s32);
void func_88229C88(void) { func_8821D930((D_882348C0 + 4)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19CD60/func_88229CB0.s")
#endif
