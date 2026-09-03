#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/42/fragment42_code/func_88D00020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/42/fragment42_code/func_88D00178.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/42/fragment42_code/func_88D0038C.s")

extern void func_80064D28(void);
extern s32 func_88D00020(void);
extern void func_88D00178(void);
void func_88D00488(void) {
    s32 result;
    do {
        func_80064D28();
        result = func_88D00020();
        func_88D00178();
    } while (result == 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/42/fragment42_code/func_88D004C8.s")

extern s32 mem_pool_try_init(s32, s32);
extern void func_80057908(s32);
extern s32 func_8005DA1C(s32);
extern u8 func_8005D92C(s32);
extern void func_8005DC48(s32, u8 *);
extern void func_8005A014(s32);
extern void func_8005A034(s32);
extern s32 func_80055948(s32);
extern void func_88A00D0C(s32);
extern s8 D_88006868[];
extern u8 D_8800686D[];
void func_88D005CC(void) {
    s32 pool = mem_pool_try_init(0x14000, 0);
    func_80057908(0);
    D_88006868[0] = 0;
    *(s16 *)(D_88006868 + 2) = func_8005DA1C(D_88006868[0]);
    D_88006868[4] = func_8005D92C(D_88006868[0]);
    func_8005DC48(D_88006868[0], D_8800686D);
    func_8005A014(0);
    func_8005A034(0);
    func_80055948(3);
    func_88A00D0C(pool);
}

extern void main_pool_push_state(s32 arg0);
extern void main_pool_pop_state(s32 arg0);
extern void Gfx_InitDisplayListBuffers(s32 arg0, s32 arg1);
extern s32 func_800082E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern void func_8004C09C(s32 arg0);
extern s32 func_80047588(s32 arg0, s32 arg1);
extern s32 D_8800687C;
extern void func_88D005CC(void);
extern void func_80008514(s32 arg0);
extern void func_88D0038C(void);
extern void func_88D00488(void);
extern void func_88D004C8(void);
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void Gfx_FreeDisplayListBuffers(void);
extern void func_80057944(s32 arg0);
s32 fragment42_main(s32 arg0, s32 arg1) {
    s32 stage;
    main_pool_push_state(0x4946554C);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    stage = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(3);
    D_8800687C = func_80047588(0x18, 0);
    func_88D005CC();
    func_80008514(stage);
    func_88D0038C();
    func_88D00488();
    func_88D004C8();
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    func_80057944(0);
    main_pool_pop_state(0x4946554C);
    return 0;
}
#endif
