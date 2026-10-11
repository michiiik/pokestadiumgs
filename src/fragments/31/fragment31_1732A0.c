#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1732A0/func_88200020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1732A0/func_882000AC.s")

extern u8 *D_88234564;
void func_88200134(u8 arg0, u8 arg1) {
    u8 *entry = D_88234564 + arg0 * 0x44;
    if (*(s32 *)(entry + 0x1C) != 0) {
        entry[0x20] = *(s8 *)(entry + 0x20) + arg1 + 1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1732A0/func_88200180.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1732A0/func_882001E8.s")

u8 func_882002F8(u8 *arg0, u8 *arg1) {
    u8 value = *arg0;

    *arg0 = *arg1;
    *arg1 = value;
    return value;
}

u32 func_8820030C(u32 *arg0, u32 *arg1) {
    u32 value = *arg0;

    *arg0 = *arg1;
    *arg1 = value;
    return value;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_1732A0/func_88200320.s")

u32 func_88200458(u32 *arg0, u32 *arg1) {
    u32 value = *arg0;

    *arg0 = *arg1;
    *arg1 = value;
    return value;
}
#endif
