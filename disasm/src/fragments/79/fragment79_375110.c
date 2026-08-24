#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375110/func_84105880.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375110/func_84105930.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375110/func_84105988.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375110/func_84105A0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375110/func_84105A54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375110/func_84105AD8.s")

extern u8 *D_84190114;
void func_84105B20(u8 *arg0, u8 *arg1) {
    *(s16 *)arg0 = *(s16 *)(D_84190114 + 0x76);
    *(s16 *)arg1 = *(s16 *)(D_84190114 + 0x78);
}

extern u8 *D_84190114;
void func_84105B44(u8 *arg0) {
    *(s16 *)arg0 = *(s16 *)(D_84190114 + 0x78);
}

void func_84105B58(u8 *arg0, u8 *arg1) {
    *(s16 *)arg0 = *(s16 *)(*(u8 **)&D_84190114 + 0x70);
    *(s16 *)arg1 = *(s16 *)(*(u8 **)&D_84190114 + 0x72);
}

extern u8 *D_84190114;
void func_84105B7C(u8 *arg0) {
    *(s16 *)arg0 = *(s16 *)(D_84190114 + 0x72);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_375110/func_84105B90.s")
#endif
