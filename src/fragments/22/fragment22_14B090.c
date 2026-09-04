#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700DD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700E38.s")

void *func_82700E70(s32 arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 i;
    u8 *ptr;
    void *result;

    result = NULL;
    i = 0;
    if (arg3 > 0) {
        ptr = arg2;
        do {
            i += 1;
            if ((arg0 == *(s16 *)ptr) && (arg1 == *(s16 *)(ptr + 2))) {
                result = ptr;
                break;
            }
            ptr += 0x28;
        } while (i != arg3);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700EC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700EFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700FA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82700FF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_8270103C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827010F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701278.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701300.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827013F0.s")

extern u16 D_827034EC;
extern u8 D_82703514[];
s32 func_827015A4(s32 arg0, s32 arg1) {
    s32 result;
    void *entry;

    result = 0;
    if (D_827034EC & 1) {
        entry = func_82700E70(arg0, arg1, D_82703514, 0x10);
        if ((entry != NULL) && (*(s16 *)((u8 *)entry + 6) == 0)) {
            *(s16 *)((u8 *)entry + 6) = 1;
            *(s16 *)((u8 *)entry + 8) = 0;
            result = 1;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_8270160C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_8270174C.s")

extern u16 D_827034EC;
extern u8 D_82703514[];
s32 func_82701820(s32 arg0, s32 arg1) {
    s32 result;
    void *entry;

    result = 0;
    if (D_827034EC & 1) {
        entry = func_82700E70(arg0, arg1, D_82703514, 0x10);
        if ((entry != NULL) && (*(s16 *)((u8 *)entry + 6) == 2)) {
            *(s16 *)((u8 *)entry + 6) = 4;
            *(s16 *)((u8 *)entry + 8) = 0;
            result = 1;
        }
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_8270188C.s")

s32 func_82701920(void *arg0) {
    u8 *state;
    s32 result;
    u8 *record;
    s16 flag;

    state = *(u8 **)((u8 *)arg0 + 0x20);
    result = 0;
    record = *(u8 **)((u8 *)arg0 + 0x1C);
    flag = (s16)((state[1] & 1) != 0);
    if (*(s16 *)record != 0) result = 1;
    if (*(u16 *)(record + 2) != state[0]) result = 1;
    if (flag != *(s16 *)(record + 4)) result = 1;
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701978.s")

extern void *func_82700E70(s32, s32, void *, s32);
extern s32 func_827015A4(s32, s32);
void func_82701CB8(void *arg0) {
    s32 pad_frame[3];
    s32 sp28;
    s32 temp_a1;
    s32 var_s0;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_2;

    temp_s2 = (u8 *)arg0 + 0x34;
    temp_v0 = func_82700E70(2, 4, temp_s2, 0x10);
    sp28 = 1;
    if (*(s16 *)((u8 *)temp_v0 + 6) != 0) {
        *(s16 *)((u8 *)arg0 + 0x12) = (s16)(0xFF - *(s16 *)((u8 *)temp_v0 + 0xC));
    } else {
        *(s16 *)((u8 *)arg0 + 0x12) = 0xFF;
    }
    if (*(s16 *)((u8 *)arg0 + 0xE) >= 0) {
        if ((*(s16 *)((u8 *)arg0 + 0xE) & 3) == 0) {
            temp_a1 = *(s16 *)((u8 *)arg0 + 0xE) / 4;
            if (temp_a1 < 2) {
                func_827015A4(3, temp_a1);
            } else {
                *(s16 *)((u8 *)arg0 + 0xE) = -1;
            }
        }
        if (*(s16 *)((u8 *)arg0 + 0xE) >= 0) {
            *(s16 *)((u8 *)arg0 + 0xE) = *(s16 *)((u8 *)arg0 + 0xE) + 1;
        }
    }
    var_s0 = 0;
    do {
        temp_v0_2 = func_82700E70(3, var_s0, temp_s2, 0x10);
        var_s0 += 1;
        if ((temp_v0_2 != NULL) && (*(s16 *)((u8 *)temp_v0_2 + 6) != 2)) {
            sp28 = 0;
            break;
        }
    } while (var_s0 != 2);
    if (sp28 != 0) {
        *(s16 *)((u8 *)arg0 + 2) = 4;
        *(s16 *)((u8 *)arg0 + 6) = 1;
        *(u16 *)((u8 *)arg0 + 0xC) |= 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701DF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701F7C.s")

void func_827020F4(void *arg0)
{
  s16 temp_v0;
  temp_v0 = *((s16 *) (((u8 *) arg0) + 0xE));
  if (temp_v0 < 0xA)
  {
    *((s16 *) (((u8 *) arg0) + 0xE)) = (s16) (temp_v0 + 1);
  }
  temp_v0 = *((s16 *) (((u8 *) arg0) + 0xE));
  if (temp_v0 == 2)
  {
    func_8005314C();
    func_80055028();
    func_8005487C(*((s32 *) (((u8 *) arg0) + 0x20)));
    func_82701300(arg0, *((s32 *) (((u8 *) arg0) + 0x20)), 1);
    *((s16 *) (((u8 *) arg0) + 0xA)) = 3;
  }
}

void func_8270216C(void *arg0) {
    void *sp34;
    void *sp20;
    volatile s32 reserve[2];
    void *temp_v0;

    sp20 = (u8 *)arg0 + 0x34;
    sp34 = func_82700E70(3, 0, sp20, 0x10);
    temp_v0 = func_82700E70(2, 4, sp20, 0x10);
    if (*(s16 *)((u8 *)sp34 + 6) != 0) {
        *(s16 *)((u8 *)arg0 + 0x12) = *(s16 *)((u8 *)sp34 + 0xC);
    } else {
        *(s16 *)((u8 *)arg0 + 0x12) = 0;
    }
    if ((temp_v0 != NULL) && (*(s16 *)((u8 *)temp_v0 + 6) == 2) &&
        (*(s16 *)((u8 *)arg0 + 0x12) == 0)) {
        *(s16 *)((u8 *)arg0 + 2) = 2;
        *(s16 *)((u8 *)arg0 + 0x16) = 2;
        *(void **)((u8 *)arg0 + 0x18) = (u8 *)arg0 + 4;
        *(u16 *)((u8 *)arg0 + 0xC) |= 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702220.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702364.s")

void func_82702528(void *arg0) {
    void *sp3C;
    void *sp24;
    void *temp_a2;
    void *temp_v0;
    volatile s32 reserve[2];

    temp_a2 = (u8 *)arg0 + 0x34;
    sp24 = temp_a2;
    sp3C = func_82700E70(4, 0, temp_a2, 0x10);
    func_82700E70(2, 3, temp_a2, 0x10);
    temp_v0 = func_82700E70(2, 4, temp_a2, 0x10);
    if (*(s16 *)((u8 *)sp3C + 6) != 0) {
        *(s16 *)((u8 *)arg0 + 0x14) = *(s16 *)((u8 *)sp3C + 0xC);
    } else {
        *(s16 *)((u8 *)arg0 + 0x14) = 0;
    }
    if ((temp_v0 != NULL) && (*(s16 *)((u8 *)temp_v0 + 6) == 2) &&
        (*(s16 *)((u8 *)arg0 + 0x14) == 0)) {
        *(s16 *)((u8 *)arg0 + 2) = 2;
        *(s16 *)((u8 *)arg0 + 0x16) = 2;
        *(void **)((u8 *)arg0 + 0x18) = (u8 *)arg0 + 4;
        *(u16 *)((u8 *)arg0 + 0xC) |= 2;
    }
}

void func_827025F0(void *arg0) {
    void *entry;

    entry = func_82700E70(2, 2, (u8 *)arg0 + 0x34, 0x10);
    if (*(s16 *)((u8 *)entry + 6) == 2) {
        *(s16 *)((u8 *)arg0 + 0xE) = *(s16 *)((u8 *)arg0 + 0xE) + 1;
        if (*(s16 *)((u8 *)arg0 + 0xE) >= 2) {
            *(s16 *)((u8 *)arg0 + 0xA) = 2;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702658.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702810.s")

extern void func_800498C4(void);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800496A4(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800495F8(s32, s32, s32, s32);
extern void func_800499EC(void);
void func_82702954(arg0, arg1) void *arg0; s32 arg1; { s32 result; s32 value; result = func_8004C874(0x1A, 4); value = (*(s16 *)((u8 *)arg0 + 0xC) * 0xFF) / 255; func_800498C4(); func_8004972C(0xFF, 0xFF, 0xFF, value); if (result != 0) { func_800496A4(8, 0); func_800495F8(*(s16 *)((u8 *)arg0 + 0x12) + 0x1E, *(s16 *)((u8 *)arg0 + 0x14) + 6, 0, result); } func_800499EC(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702A2C.s")

extern s32 D_827032E4;
extern u8 D_827032D0[];
extern u8 D_827032D4[];
extern void func_800498C4(void);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800496A4(s32, s32);
extern s32 func_8004C874(s32, s32);
extern void func_800495F8(s32, s32, s32, s32);
extern void func_800499EC(void);

void func_82702BC8(arg0, arg1)
void *arg0;
s32 arg1;
{
    volatile s32 reserve[2];
    s32 sp2C;
    s32 sp28;
    u8 *sp24;

    sp2C = D_827032E4;
    sp28 = (*(s16 *)((u8 *)arg0 + 0xC) * 0xFF) / 255;
    if (arg1 == 0) {
        sp24 = D_827032D0;
    } else {
        sp24 = D_827032D4;
    }
    func_800498C4();
    func_8004972C(sp24[0], sp24[1], sp24[2], sp28);
    if (((s16 *)&sp2C)[*(s16 *)((u8 *)arg0 + 2)] >= 0) {
        func_800496A4(0x10, 0);
        func_800495F8(
            *(s16 *)((u8 *)arg0 + 0x12) + 0x40,
            *(s16 *)((u8 *)arg0 + 0x14) + 4,
            0,
            func_8004C874(0x1A, ((s16 *)&sp2C)[*(s16 *)((u8 *)arg0 + 2)]));
    }
    func_800499EC();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702CD8.s")

#ifdef CC_CHECK
extern void func_82702954(void *, s32);
#else
extern void func_82702954();
#endif
extern void func_82702A2C();
#ifdef CC_CHECK
extern void func_82702BC8(void *, s32);
#else
extern void func_82702BC8();
#endif
extern void func_82702CD8();
void func_82702DF8(s16 *arg0) {
    s16 temp_v0;

    temp_v0 = *arg0;
    switch (temp_v0) {                              /* irregular */
    case 1:
#ifdef CC_CHECK
        func_82702954((void *)0, 0);
#else
        func_82702954();
#endif
        return;
    case 2:
        func_82702A2C();
        return;
    case 3:
#ifdef CC_CHECK
        func_82702BC8((void *)0, 0);
#else
        func_82702BC8();
#endif
        return;
    case 4:
        func_82702CD8();
        return;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702E78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702F70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_827030D0.s")

extern u16 D_827034EC;
extern s16 D_827034EA;
s32 func_82703188(void) {
    s32 result = -2;
    if (D_827034EC & 1) {
        result = D_827034EA;
    }
    return result;
}
#endif
