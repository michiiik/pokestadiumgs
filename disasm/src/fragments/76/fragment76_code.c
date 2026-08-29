#include "global.h"


void func_8F700020(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700028.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700420.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700538.s")
#endif

#ifdef VERSION_US
extern u8 D_15833A0[];
extern u8 D_8F702368;
extern void Dma_CopyChunks(u8 *, u8 *, u8 *);
void func_8F70058C(u8 arg0) {
    u8 *temp_a2;
    u8 temp_a3 = arg0;
    if (temp_a3 != 0) {
        temp_a2 = (u8 *)((u32)&D_15833A0 + (temp_a3 * 0x44));
        Dma_CopyChunks(&D_8F702368, temp_a2 - 0x44, temp_a2);
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F7005D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700624.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F7006F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F7007B8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700858.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700A54.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700B78.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700CA4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700DC8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700EF4.s")
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
extern void func_8F700EF4(void);
extern s32 D_8F7023B0;
void func_8F700F48(void) {
    func_800226C0(1);
    D_8F7023B0 = D_8F7023B0 + 1;
    if (D_8F7023B0 >= 3) {
        D_8F7023B0 = 0;
    }
    func_8F700EF4();
}
#endif

#ifdef VERSION_US
void func_8F700F90(void) {
    func_800226C0(1);
    D_8F7023B0 = D_8F7023B0 - 1;
    if (D_8F7023B0 < 0) {
        D_8F7023B0 = 2;
    }
    func_8F700EF4();
}
#endif

#ifdef VERSION_US
extern u8 D_8F701358[];
extern u8 D_8F702361;
extern s32 D_8F7023B4;
extern s32 D_8F7023B8;
extern void func_800226C0(s32);
extern void func_8F70058C(u8);
void func_8F700FD8(void) {
    s32 temp_v0;
    temp_v0 = D_8F701358[D_8F7023B4 * 0x30];
    switch (temp_v0) {
    case 0:
        D_8F7023B8 = 0;
        break;
    case 2:
        func_800226C0(2);
        func_8F70058C(D_8F702361);
        break;
    }
}
#endif

#ifdef VERSION_US
extern s32 D_8F7023B4;

void func_8F70104C(void) {
    func_800226C0(3);
    D_8F7023B0 = 0;
    D_8F7023B4 = 2;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F70107C.s")
#endif

#ifdef VERSION_US
extern void func_80008648();
extern void func_800088DC();
extern void func_80064D28();
extern void func_8F700420();
extern void func_8F70107C();
extern s32 D_8F7023B8;
void func_8F7011C8(void) {
    do {
        func_80064D28();
        func_800088DC();
        func_8F70107C();
        func_8F700420();
        func_80008648();
    } while (D_8F7023B8 != 0);
}
#endif

#ifdef VERSION_US
extern void func_8F700538(u8);
extern u8 D_8F702360;
extern u8 D_8F702361;
extern u8 D_8F7023AC;
extern s32 D_8F7023B0;
extern s32 D_8F7023B4;
extern s32 D_8F7023B8;
void func_8F701224(void) {
    u8 value;
    D_8F7023B0 = 0;
    D_8F7023B4 = 0;
    value = 1;
    D_8F702360 = value;
    D_8F7023AC = value;
    D_8F702361 = value;
    D_8F7023B8 = 1;
    func_8F700538(D_8F702360);
}
#endif

#ifdef VERSION_US
extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void func_80006CD0(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_80047588(s32, s32);
extern void func_8004C09C(s32);
extern void func_8F701224(void);
extern void func_80008514(s32);
extern void func_800086A4(s32);
extern void func_80007AEC(s32);
extern void func_8F7011C8(void);
extern void func_80008574(void);
extern void func_80047610(void);
extern void Gfx_FreeDisplayListBuffers(void);
s32 fragment76_main(s32 arg0, s32 arg1) {
    s32 sp24;
    main_pool_push_state(0x41494544);
    func_80006CD0(0x10000, 0);
    sp24 = func_800082E0(1, 1, 2, 0, 2, 1);
    func_80047588(0x1C, 0);
    func_8004C09C(3);
    func_8F701224();
    func_80008514(sp24);
    func_800086A4(2);
    func_80007AEC(0x10);
    func_8F7011C8();
    func_80008574();
    func_80047610();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x41494544);
    return 0;
}
#endif
