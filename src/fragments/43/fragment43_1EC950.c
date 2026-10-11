#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1EC950/func_8AC06F60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1EC950/func_8AC07378.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1EC950/func_8AC075A8.s")

typedef struct {
    s16 state;
    u8 pad[0x12];
    s32 resource;
    u8 tail[0x180];
} Entry_8AC07A8C;
extern Entry_8AC07A8C D_8AC099D0[3];
extern s32 func_8004C990(s32, s32);

void func_8AC07A8C(void) {
    Entry_8AC07A8C *entry = D_8AC099D0;
    s32 index;

    _bzero(entry, 0x4C8);
    index = 0;
    do {
        entry->state = 0;
        entry->resource = func_8004C990(0x93, 0);
        index++;
        entry++;
    } while (index != 3);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/43/fragment43_1EC950/func_8AC07AF4.s")
#endif
