#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D3260/func_841639D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D3260/func_84163B4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D3260/func_84163DA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D3260/func_84163E60.s")

extern u8 *D_84187A70;
extern void func_84163E60(u8 *);
s32 func_841641EC(void) {
    u8 *ptr = D_84187A70;
    s32 i = 0;
    while (i != 4) {
        if (*(s16 *)ptr == 1) {
            *(s16 *)(ptr + 2) += 1;
            if (*(s16 *)(ptr + 2) > *(s16 *)(ptr + 4)) {
                *(s16 *)ptr = 0;
            } else {
                func_84163E60(ptr);
            }
        }
        i++;
        ptr += 0x430;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3D3260/func_84164280.s")
#endif
