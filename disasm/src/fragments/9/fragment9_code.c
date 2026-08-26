#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB000D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB001C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB002BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB005E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB009C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00C1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00E40.s")

s32 func_8FB00C1C();
s32 func_8FB00F78(void *arg0, void *arg1) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg1) + (0x44)));
    (*(u16 *)((u8 *)(arg0) + (0))) = (u16) (*(u16 *)((u8 *)(temp_v0) + (4)));
    (*(u16 *)((u8 *)(arg0) + (2))) = (u16) (*(u16 *)((u8 *)(temp_v0) + (6)));
    (*(s16 *)((u8 *)(arg0) + (4))) = (s16) ((*(u16 *)((u8 *)(temp_v0) + (0xC))) * 0x14);
    if (func_8FB00C1C() != 0) {
        (*(s16 *)((u8 *)(arg0) + (6))) = (s16) ((*(u16 *)((u8 *)(arg0) + (0xC))) * 0x14);
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB00FE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB011DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01634.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01A74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01C14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01CF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01EC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB01FCC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02108.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB021F8.s")

struct MsgState *func_8FB02418(void)
{
  s32 temp_v0;
  temp_v0 = func_8006B7FC();
  return func_800718B8(func_8006A600(temp_v0 & 0xFFFF, (temp_v0 & 0xFF) & 0xFFu, 0));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02454.s")

struct MsgState { u8 pad[0x40]; u32 flags; };
extern struct MsgState *func_8FB02418(void);
s32 func_8FB02494(void) {
    return (func_8FB02418()->flags >> 31) == 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB024BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02560.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02608.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02698.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02878.s")

extern void func_8FB024BC(void *);
extern void func_8FB02698(void *);
extern void func_8FB02878(void *);
void func_8FB029B4(void *arg0) {
    s32 temp_v0;

    temp_v0 = (*(s32 *)((u8 *)(arg0) + (0x40)));
    switch (temp_v0) {                              /* irregular */
    case 0:
        func_8FB02698(arg0);
        break;
    case 1:
        func_8FB02878(arg0);
        break;
    }
    func_8FB024BC(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB02A10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB03164.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB031E0.s")

extern u8 D_8FB03DF8;
void func_80064D28(void);

void func_8FB032C4(s32 arg0, s32 arg1) {
    if ((*(s32 *)((u8 *)(&D_8FB03DF8) + (0x40))) != 2) {
        do {
            func_80064D28();
            func_8FB029B4(&D_8FB03DF8);
            func_8FB031E0(&D_8FB03DF8);
        } while ((*(s32 *)((u8 *)(&D_8FB03DF8) + (0x40))) != 2);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/9/fragment9_code/func_8FB03328.s")

extern void Gfx_FreeDisplayListBuffers();
extern void func_80008574();
extern void func_80047610();
extern void func_8004C398();

void func_8FB033F0(s32 arg0, s32 arg1) {
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
}

extern void func_8FB032C4(s32, s32);
extern void func_8FB03328(s32, s32);
extern void main_pool_pop_state(s32);
extern void main_pool_push_state(s32);
s32 fragment9_main(s32 arg0, s32 arg1) {
    main_pool_push_state(0x52504D45);
    func_8FB03328(arg0, arg1);
    func_8FB032C4(arg0, arg1);
    func_8FB033F0(arg0, arg1);
    main_pool_pop_state(0x52504D45);
    return 0;
}
#endif
