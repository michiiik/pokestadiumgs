#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E01720.s")

extern u8 D_87E19720[];
extern void func_87E01720(s32, s32, s32, s32, void *);
void func_87E01798(s32 arg0) {
    func_87E01720(arg0, 4, 4, 0x1A6, D_87E19720);
}

extern u8 D_87E19724[];
void func_87E017CC(s32 arg0) {
    func_87E01720(arg0, 3, 8, 0x1A7, D_87E19724);
}

extern u8 D_87E1972C[];
void func_87E01800(s32 arg0) {
    func_87E01720(arg0, 3, 6, 0x1A4, D_87E1972C);
}

extern u8 D_87E19734[];
void func_87E01834(s32 arg0) {
    func_87E01720(arg0, 3, 8, 0x1A5, D_87E19734);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E01868.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E01A5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E01B50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E01DB4.s")

typedef struct { u8 pad_00[0x2180]; u8 mode; } F1E24ObjB;
typedef struct { u8 pad_00[4]; s32 value; u8 pad_08[0x278]; F1E24ObjB *obj; s8 out_284; s8 out_285; } F1E24StateB;
void func_87E01E24(F1E24StateB *arg0) {
    s32 value;
    switch (arg0->obj->mode) {
        case 0: arg0->value = 0; break;
        case 1: arg0->value = 1; break;
        case 2: arg0->value = 2; break;
        case 3: arg0->value = 3; break;
    }
    value = arg0->value;
    arg0->out_284 = value % 2;
    arg0->out_285 = value / 2;
}

extern void func_87E01E24();
extern void func_87E01B50();
extern void func_87E134C0();
extern void func_87E13490();
extern void func_87E13480();
extern void func_87E0168C();
void func_87E01EB0(void *arg0) {
    *(s32 *)arg0 = 0;
    func_87E01E24(arg0);
    func_87E01B50(arg0);
    func_87E134C0();
    func_87E13490();
    func_87E13480(1);
    func_87E0168C(3, 0x8C, 0x2D);
}

void func_87E01F04(u8 *arg0) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E01F0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E01F44.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E02150.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E021CC.s")

extern void func_8004C8C0(s32);
void func_87E02438(void) {
    func_8004C8C0(0x1A4);
    func_8004C8C0(0x1A5);
    func_8004C8C0(0x1A6);
    func_8004C8C0(0x1A7);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E02470.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/63/fragment63_305090/func_87E02538.s")

extern void func_87E02538(void);
extern void func_800088DC(void);
void func_87E0276C(void) {
    func_87E02538();
    func_800088DC();
}

extern void func_87E02438();
extern void func_87E02470();
extern void func_87E01DB4();
void func_87E02794(void *arg0, s32 arg1) {
    *(s32 *)((u8 *)arg0 + 0x280) = arg1;
    *(s32 *)arg0 = 0;
    func_87E01E24(arg0);
    func_87E02438();
    func_87E02470(arg0);
    func_87E01DB4(arg0);
}
#endif
