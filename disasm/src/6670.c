#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_80005A70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_80005B88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_80005CA4.s")

extern void func_800063B0(void); extern OSMesgQueue D_800CE100;
void func_80005EE0(void) { func_800063B0(); osContStartReadData(&D_800CE100); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_80005F0C.s")

extern u8 D_800CE118; u8 func_800060E8(void) { return D_800CE118; }

void func_800060F4(s16 arg0, s16 arg1) { extern s16 D_80087210; extern s16 D_80087214; if (arg0 > 0) D_80087210 = arg0; if (arg1 > 0) D_80087214 = arg1; }

extern s16 D_80087210; extern s16 D_80087214; void func_8000612C(void) { D_80087210 = 10; D_80087214 = 2; }

void func_80006148(u8 *arg0) { *(u16 *)(arg0 + 0x10) |= 1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_80006158.s")

s32 func_800061C4(void *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if ((*(*(u16 **)((u8 *)(arg0) + (0x20))) & 0x1F07) == 5) {
        var_v1 = 1;
    }
    return var_v1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_800061EC.s")

extern u8 D_800CE119; s32 func_80006230(void) { return D_800CE119 != 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_80006240.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_800062F8.s")

void func_800063B0(void) { extern OSMesgQueue D_800CE150; osRecvMesg(&D_800CE150, NULL, OS_MESG_BLOCK); }

void func_800063DC(void) { extern OSMesgQueue D_800CE150; osSendMesg(&D_800CE150, NULL, OS_MESG_NOBLOCK); }

void func_80006408(void) { extern OSMesgQueue D_800CE150; extern OSMesg D_800CE14C; osCreateMesgQueue(&D_800CE150, &D_800CE14C, 1); osSendMesg(&D_800CE150, NULL, OS_MESG_NOBLOCK); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/6670/func_8000644C.s")
#endif
