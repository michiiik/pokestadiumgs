#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290E5F0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290E6D4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290E76C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290E81C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290E8D8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290EAC0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290EFA0.s")
#endif

void func_8290F36C(void) {
}

#ifdef VERSION_US
#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

M2C_UNK GfxRect_DrawTextured(s16, s16, s16, s16, s32, s32, s32, s32, s32); /* extern */
M2C_UNK func_800459AC(s32, u8, u8, u16, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
s32 func_8004CA60(u8 *);                          /* extern */

void func_8290F374(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 *arg4) {
    if (arg4 != NULL) {
        func_800459AC(func_8004CA60(arg4), M2C_FIELD(arg4, u8 *, 4), M2C_FIELD(arg4, u8 *, 5), M2C_FIELD(arg4, u16 *, 0), (s32) M2C_FIELD(arg4, u16 *, 2), 1, 0, 2, 2, 0, 0, 0, 0);
    }
    GfxRect_DrawTextured(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, 0);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290F42C.s")
#endif

#ifdef VERSION_US
extern void BgStage_DrawFrame(void);
extern void func_8290F42C(void);
extern void func_80008648(void);
void func_8290FA00(void) {
    BgStage_DrawFrame();
    func_8290F42C();
    func_80008648();
}
#endif

#ifdef VERSION_US
extern s32 D_8291BC40;
extern s32 D_8291BC44;
extern void StageFade_StartFromOpaque(s32);
extern void func_8290FA00(void);
extern void func_80021ED8(s32);
void func_8290FA30(void) {
    s32 var_s0;

    D_8291BC40 = 1;
    D_8291BC44 = 1;
    StageFade_StartFromOpaque(0xC);
    var_s0 = 0;
    do {
        func_8290FA00();
        var_s0 += 1;
    } while (var_s0 != 0xE);
    func_80021ED8(0x3F);
    D_8291BC44 = 0;
}
#endif

#ifdef VERSION_US
extern void func_80064D28(void);
extern void func_8290E8D8(void);
void func_8290FA9C(void) {
    func_80064D28();
    func_8290E8D8();
    func_8290FA00();
}
#endif

#ifdef VERSION_US
extern void StageFade_StartFromTransparent(s32);
extern void func_800225C4(s32);
void func_8290FACC(void) {
    s32 var_s0;

    func_800225C4(0x10);
    StageFade_StartFromTransparent(0x10);
    var_s0 = 0;
    do {
        func_8290FA00();
        var_s0 += 1;
    } while (var_s0 != 0x10);
}
#endif

#ifdef VERSION_US
extern void func_8290E5F0(void);
void func_8290FB1C(void) {
    func_8290E5F0();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/67/fragment67_34B0F0/func_8290FB3C.s")
#endif
