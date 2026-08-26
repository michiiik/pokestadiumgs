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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F70058C.s")
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F700FD8.s")
#endif

#ifdef VERSION_US
extern void func_800226C0(s32);
extern s32 D_8F7023B0;
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F701224.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/76/fragment76_code/func_8F701280.s")
#endif
