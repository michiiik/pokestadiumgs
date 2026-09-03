#include "global.h"


#ifdef VERSION_US
s32 func_8004D690(s32);
extern s32 *D_825087F0;

void func_82504810(void) {
    *D_825087F0 = func_8004D690(0xD);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_8250483C.s")

extern void func_80008648();
extern void func_800088DC();
extern void func_800468A0(s32);
extern void func_800503A4(s32);
extern void func_8250483C();
void func_8250498C(void) {
    s32 *sp1C;

    sp1C = D_825087F0;
    func_800088DC();
    func_800468A0((*(s32 *)((u8 *)(sp1C) + (0))));
    func_800503A4((*(s32 *)((u8 *)(sp1C) + (4))));
    func_8250483C();
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825049DC.s")

extern void StageFade_StartFromTransparent(s32);
s32 func_825049DC();
s32 func_82504B04(s32 arg0) {
    s32 var_s0;

    var_s0 = arg0;
    switch (arg0) {                                 /* irregular */
    case 0:
        if (StageContext_GetFadeMode() == 0) {
            var_s0 = 1;
        }
        break;
    case 1:
        if (func_825049DC() != 0) {
            var_s0 = 3;
            StageFade_StartFromTransparent(5);
            func_80035424(0xF);
        }
        break;
    case 3:
        if (StageContext_GetFadeMode() == 1) {
            var_s0 = 4;
        }
        break;
    }
    return var_s0;
}

s32 func_82504B04(s32);
s32 func_82504BA0(s32 *arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s1;

    D_825087F0 = arg0;
    var_s1 = 0;
    func_8004C09C(0x107);
    func_8004C4B0(0x31);
    func_82504810();
    func_80008624();
    if (StageContext_GetFadeMode() != 0) {
        func_800086A4(2);
        func_80007AEC(5);
    }
    do {
        func_80064D28();
        func_8250498C();
        temp_v0 = func_82504B04(var_s1);
        var_s1 = temp_v0;
    } while (temp_v0 != 4);
    StageLoader_WaitForRetrace();
    func_8004C398();
    return 5;
}

extern u16 D_82508FF6;
#pragma pack(1)
struct Fragment21PackedWord { s32 value; };
#pragma pack(0)
void func_82504C50(void *arg0, s32 arg1) {
    if ((arg0 != NULL) && (*(s16 *)((u8 *)arg0 + 8) == 0)) {
        *(s16 *)((u8 *)arg0 + 8) = 1;
        *(s16 *)((u8 *)arg0 + 0xC) = 0;
        if (arg1 == 1) {
            *(s16 *)((u8 *)arg0 + 0x10) = 0;
            *(s16 *)((u8 *)arg0 + 0x12) = 0x1E0;
        } else {
            if (D_82508FF6 & 2) {
                *(s16 *)((u8 *)arg0 + 0x10) = -0x280;
            } else {
                *(s16 *)((u8 *)arg0 + 0x10) = 0x280;
            }
            *(s16 *)((u8 *)arg0 + 0x12) = 0;
        }
        *(struct Fragment21PackedWord *)((u8 *)arg0 + 0x14) = *(struct Fragment21PackedWord *)((u8 *)arg0 + 0x10);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82504CC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82504D40.s")

extern u16 D_82508FF6;
void func_82504D94(void *arg0, s32 arg1) {
    if ((arg0 != NULL) && ((*(s16 *)((u8 *)(arg0) + (8))) == 2)) {
        (*(s16 *)((u8 *)(arg0) + (8))) = 5;
        (*(s16 *)((u8 *)(arg0) + (0xC))) = 0;
        switch (arg1) {                             /* irregular */
        case 1:
            (*(s16 *)((u8 *)(arg0) + (0x14))) = 0;
            (*(s16 *)((u8 *)(arg0) + (0x16))) = 0x1E0;
            return;
        case 2:
            if (D_82508FF6 & 2) {
                (*(s16 *)((u8 *)(arg0) + (0x14))) = -0x280;
            } else {
                (*(s16 *)((u8 *)(arg0) + (0x14))) = 0x280;
            }
            (*(s16 *)((u8 *)(arg0) + (0x16))) = 0;
            return;
        default:
            if (D_82508FF6 & 2) {
                (*(s16 *)((u8 *)(arg0) + (0x14))) = 0x280;
            } else {
                (*(s16 *)((u8 *)(arg0) + (0x14))) = -0x280;
            }
            (*(s16 *)((u8 *)(arg0) + (0x16))) = 0;
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82504E38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82504FB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825050EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825052A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82505420.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82505758.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82505A64.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_8250610C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825064A4.s")

extern void _bzero(s16 *, s32);
extern void func_8004C8C0(s32);
extern s16 D_82508FF0;
void func_8250684C(void) {
    func_8004C8C0(0x4B);
    func_8004C8C0(0x85);
    _bzero(&D_82508FF0, 0x68C);
    D_82508FF0 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506888.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825068C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506910.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825069F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506AA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506AD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506BEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506E98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82506FB8.s")

extern void func_82504C50(void *, s32);
void *func_825068C4(s32, s32);

void func_82507000(s16 *arg0) {
    s16 temp_v1;
    void *temp_v0;

    temp_v0 = func_825068C4(1, 0);
    temp_v1 = (*(s16 *)((u8 *)(temp_v0) + (8)));
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_82504C50(temp_v0, 0);
        func_82504C50(func_825068C4(1, 1), 0);
        return;
    case 2:
        *arg0 = 2;
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507078.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507250.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825073B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_825075B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_8250771C.s")

void func_82507AF4(void)
{
  int new_var;
  new_var = 1;
  if (D_82508FF0 == 0)
  {
    D_82508FF0 = new_var;
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507B18.s")


s32 func_82507B58(void) {
    return D_82508FF0 == 2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507B6C.s")


s32 func_82507BBC(void) {
    return D_82508FF0 == 4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507BD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507BFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507C48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507C98.s")


s32 func_82507CF4(void) {
    return D_82508FF0 == 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/21/fragment21_144790/func_82507D04.s")
#endif
