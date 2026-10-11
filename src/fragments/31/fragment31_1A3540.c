#include "global.h"


#ifdef VERSION_US
extern void func_88004990(u8, s32);
extern s32 D_880068B8;
extern u8 **D_88234990;

void func_882302C0(void) {
    func_88004990(**D_88234990, 0);
    D_880068B8 = 1;
}

extern void func_8000612C();

void func_882302F8(void) {
    func_8000612C();
    D_880068B8 = 0;
}

extern void func_88001900(void);
extern void func_88211168(s32, s8 *);
extern void func_887009A0(void);
extern void Util_Free(s32);
extern s32 D_880068B4;
extern s32 D_882346F4;

void func_8823031C(void) {
    func_88001900();
    D_880068B4 = 1;
    D_882346F4 = 0;
    if (*(s8 *)((u8 *)D_88234990 + 4) != 0) {
        func_88211168(1, (s8 *)D_88234990 + 4);
    }
    func_887009A0();
    Util_Free((s32)D_88234990);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1A3540/func_88230384.s")
#endif
