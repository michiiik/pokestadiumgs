#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100214.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100514.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100658.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_821006AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100764.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_821008BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100AEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100B2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100B6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100C14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100C50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100CD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100D20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100D9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82100F68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82101040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82101094.s")

extern void func_8004C398();
extern void main_pool_pop_state(s32);

void func_82101420(s32 arg0) {
    func_8004C398();
    main_pool_pop_state(0x50535253);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_8210144C.s")

extern void func_80008574(void);
extern void func_80047610(void);
extern void func_80006D3C(void);
extern void func_82100A40(void *);
extern u8 D_82104170[];
void func_82101648(s32 arg0) {
    func_82101420(arg0);
    func_80008574();
    func_80047610();
    func_80006D3C();
    func_82100A40(D_82104170);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_8210168C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_821016F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82101728.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_821019AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82101A30.s")

f32 func_82101AB4(u8 *arg0) {
    return ((f32)*(s16 *)(*(u8 **)(arg0 + 0) + 0x0C) *
            (*(f32 *)(*(u8 **)(arg0 + 8) + 0x2C) + 1.0f) * 0.5f) +
           (f32)*(s16 *)(*(u8 **)(arg0 + 0) + 0x08);
}

typedef struct { u8 padA[0xA]; s16 a; u8 padC[2]; s16 b; } S82101p;
typedef struct { u8 pad30[0x30]; f32 c; } T82101p;
typedef struct { S82101p *p; u8 pad4[4]; T82101p *q; } U82101p;
f32 func_82101AFC(U82101p *arg0) {
    return (f32)arg0->p->a + ((f32)arg0->p->b * (arg0->q->c + 1.0f) * 0.5f);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/25/fragment25_15A060/func_82101B44.s")
#endif
