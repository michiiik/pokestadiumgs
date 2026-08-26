#include "global.h"


#ifdef VERSION_US
extern u8 D_84400B3F[];
s32 fragment86_main(u8 arg0) { s32 result = 0xA0; if (arg0 > 0 && arg0 < 0xFC) { result = (D_84400B3F[arg0] & 0xE0) & 0xFF; } return result; }
#endif

#ifdef VERSION_US
s32 func_84400058(u8 arg0) { s32 result = 0; if (arg0 > 0 && arg0 < 0xFC) { result = (D_84400B3F[arg0] & 0x1F) & 0xFF; } return result; }
#endif

#ifdef VERSION_US
void func_84400090(u8 *arg0) {
    *arg0 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_84400098.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_844000C4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_844001E0.s")
#endif

#ifdef VERSION_US
u8 func_84400338(u8 *arg0) {
    return *arg0;
}
#endif

void func_84400340(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_84400348.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_84400394.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_844003E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_84400528.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_844006F8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_844007D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_844008E4.s")
#endif
