#include "global.h"


#ifdef VERSION_US
extern void func_800476A0(void *, s32);
extern void func_800476FC(void *, s32);
extern s32 func_8004C990(s32, s32);
extern void func_80047738(s32, s32, s32, s32);
extern void func_80054210(void *);
extern void func_8005487C(void *);
extern void func_8005493C(void *);
extern void func_80055EF0(void *, s32);
extern u8 D_8F300E10[];
extern u8 D_8F300E14[];
extern u8 D_8F300F20[];
extern u8 D_8F300F28[];
extern u8 D_8F300F30[];
extern u8 D_8F300F40[];
extern u8 D_8F300F48[];
extern u8 D_8F300F60[];
extern u8 D_8F300F78[];
void func_8F300020(void) {
    *(s16 *)D_8F300F20 = 0;
    *(s16 *)(D_8F300F20 + 2) = 0;
    *(s32 *)(D_8F300F20 + 4) = 0;
    func_800476A0(D_8F300F78, 0x10);
    func_800476FC(D_8F300F78, 0x10);
    func_80047738(0, func_8004C990(0x33, 5), 0, 0);
    *(s32 *)D_8F300E10 = 0;
    *(s32 *)D_8F300E14 = 0;
    func_80054210(D_8F300F28);
    func_8005487C(D_8F300F30);
    func_8005493C(D_8F300F40);
    func_80055EF0(D_8F300F48, 0);
    func_80055EF0(D_8F300F60, 1);
}
void func_8F300020_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F3000E8.s")

extern void GfxImage_FillCurrent(s32 *, s32);
extern void func_80008648();
extern void func_800088DC();
extern void func_8F3000E8();
extern u8 D_800D0510;

void func_8F300770(void) {
    func_800088DC();
    GfxImage_FillCurrent(&D_800D0510, 1);
    func_8F3000E8();
    func_80008648();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F3007B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/71/fragment71_code/func_8F300AD0.s")

extern void StageFade_StartFromOpaque(s32);
extern void func_800086A4(s32);
extern void func_80064D28();
s32 func_8F300AD0(s32);
void func_8F300CAC(void) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = 0;
    func_800086A4(2);
    StageFade_StartFromOpaque(5);
    do {
        func_80064D28();
        func_8F300770();
        temp_v0 = func_8F300AD0(var_s0);
        var_s0 = temp_v0;
    } while (temp_v0 != 4);
}

extern void main_pool_push_state(s32);
extern void main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern s32 func_800082E0(s32, s32, s32, s32, s32, s32);
extern void func_8004C09C(s32);
extern void func_8004C4B0(s32);
extern void func_8004C8C0(s32);
extern void func_80047588(s32, s32);
extern void Asset_LoadToSegment(s32, u8 *, u8 *, s32);
extern void func_80055A34(void);
extern void func_8F300020(void);
extern void func_80008514(s32);
extern void func_8F300CAC(void);
extern void func_80008574(void);
extern void func_80055028(void);
extern void func_80047610(void);
extern void func_8004C398(void);
extern void Gfx_FreeDisplayListBuffers(void);
extern u8 D_1000000[];
extern u8 D_446E30[];
extern u8 D_447D00[];
s32 fragment71_main(s32 arg0, s32 arg1) {
    s32 sp24;
    main_pool_push_state(0x424B4544);
    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(3);
    func_8004C4B0(0x42);
    func_8004C8C0(0x33);
    func_80047588(0xD, 0);
    Asset_LoadToSegment(((u32)&D_1000000 & 0x0F000000) >> 24, &D_446E30, D_447D00, 0);
    func_80055A34();
    func_8F300020();
    func_80008514(sp24);
    func_8F300CAC();
    func_80008574();
    func_80055028();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(0x424B4544);
    return 0;
}
#endif
