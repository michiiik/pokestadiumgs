#include "global.h"

#ifdef VERSION_US
extern u32 func_8003570C(void);
extern u8 func_844001E0(u8 *);
extern s32 func_80061B88(s32, u16);
extern s32 func_8004B7A4(s32);
extern s8 *HAL_Strcpy(s8 *, s8 *);
extern void func_800619E8(u8 *);
extern void func_80061F44(u8 *);
extern u8 *D_84400B28[];
extern u8 D_84400C40[];
extern u8 func_80062E10(u8);
extern u8 func_84400528(u8 *, u8 *, u8);

// Seven bytes copied from the original trainer-name string "SATORU".
typedef struct Fragment86TrainerPrefix {
    u8 bytes[7];
} Fragment86TrainerPrefix;
#endif

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
void func_84400098(u8 *arg0, u8 arg1) {
    if (arg0 != NULL) {
        arg0[++arg0[0]] = arg1;
    }
}
#endif

#ifdef VERSION_US
u8 ByteList_ChooseRandom_fragment86(u8 *list) {
    u32 count;
    f32 fraction;
    u8 index;

    fraction = (f32)((f64)func_8003570C() / 4294967296.0);
    //!bug The count is read before the null-pointer guard.
    count = list[0];
    index = (u32)((f32)count * fraction) + 1;
    if (count == 0 || list == NULL) {
        return 0;
    }
    return list[index];
}
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
s32 ByteList_FindIndex_fragment86(u8 *list, u8 value) {
    s32 i;

    for (i = 1; i <= list[0]; i++) {
        if (list[i] == value) {
            return (u8)i;
        }
    }
    return 0;
}
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
void MoveSelection_AssignThree_fragment86(u8 *mon, u8 *other) {
    s32 i;
    u8 *p;
    u8 result;

    switch (mon[0]) {
    case 132:
        mon[2] = 144;
        mon[3] = 0;
        mon[4] = 0;
        mon[5] = 0;
        break;
    case 201:
        mon[2] = 237;
        mon[3] = 0;
        mon[4] = 0;
        mon[5] = 0;
        break;
    default:
        mon[2] = func_84400528(mon, other, 0);
        mon[3] = func_84400528(mon, other, 1);
        mon[4] = func_84400528(mon, mon, 2);
        mon[5] = 0;
        break;
    }
    p = mon;
    for (i = 0; i != 3; i++) {
        result = func_80062E10(p[2]);
        p++;
        p[23] = result;
    }
}
#endif

#ifdef VERSION_US
void Pokemon_GenerateLevel100_fragment86(u8 *mon, u8 group) {
    mon[0] = func_844001E0(D_84400B28[group]);
    mon[29] = 100;
    *(u32 *)(mon + 8) = func_80061B88(mon[0], mon[29]);
    *(u16 *)(mon + 12) = 0xFFFF;
    *(u16 *)(mon + 14) = 0;
    *(u16 *)(mon + 16) = 0xFFFF;
    *(u16 *)(mon + 18) = 0;
    *(u16 *)(mon + 20) = 0;
    *(u16 *)(mon + 22) = func_8003570C() & 0x7FFF;
    mon[28] = 0xFF;
    HAL_Strcpy((s8 *)(mon + 52), (s8 *)func_8004B7A4(mon[0]));
    *(Fragment86TrainerPrefix *)(mon + 64) = *(Fragment86TrainerPrefix *)D_84400C40;
    func_800619E8(mon);
    func_80061F44(mon);
    if (mon[0] == 25 && (func_8003570C() & 3) == 0) {
        mon[30] |= 2;
    }
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/86/fragment86_code/func_844008E4.s")
#endif
