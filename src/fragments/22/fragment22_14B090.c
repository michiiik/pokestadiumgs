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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82701CB8.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_8270216C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702220.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702364.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702528.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702954.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702A2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702BC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/22/fragment22_14B090/func_82702CD8.s")

extern void func_82702954();
extern void func_82702A2C();
extern void func_82702BC8();
extern void func_82702CD8();
void func_82702DF8(s16 *arg0) {
    s16 temp_v0;

    temp_v0 = *arg0;
    switch (temp_v0) {                              /* irregular */
    case 1:
        func_82702954();
        return;
    case 2:
        func_82702A2C();
        return;
    case 3:
        func_82702BC8();
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
