#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006540.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_800065DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006664.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_800066EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006778.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006800.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006870.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_800068C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/rsp_init.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006A78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006ACC.s")

struct S1_UnkStruct80000E80 {
    char unk0;
    char filler4[0x18];
    s32 unk1C;
    u8* unk20;
    s32 unk24;
    s32 unk28;
};
typedef unsigned int S1_uintptr_t;
s32 func_80006B40(s32 arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct S1_UnkStruct80000E80* temp_v0;

    temp_v0 = func_800033B4(0x2C);
    if (temp_v0 != NULL) {
        temp_v0->unk0 = 0xF4;
        temp_v0->unk1C = (S1_uintptr_t)arg1;
        temp_v0->unk24 = arg2;
        temp_v0->unk20 = (void*)(S1_uintptr_t)arg0;
        temp_v0->unk28 = arg3;
        func_80006A78(temp_v0, arg4);
    }
    return temp_v0 == NULL;
}

s32 func_80006BB4(s32 arg0, void* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    struct S1_UnkStruct80000E80* temp_v0;

    temp_v0 = func_800033B4(0x2C);
    if (temp_v0 != NULL) {
        if (arg0 == 0) {
            temp_v0->unk0 = 0xF2;
        } else {
            temp_v0->unk0 = 0xF3;
        }
        temp_v0->unk1C = arg2;
        temp_v0->unk24 = arg3;
        temp_v0->unk20 = arg1;
        temp_v0->unk28 = arg4;
        func_80006A78(temp_v0, arg5);
    }
    return temp_v0 == NULL;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/7140/func_80006C40.s")
#endif
