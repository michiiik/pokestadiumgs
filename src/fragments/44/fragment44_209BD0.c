#include "global.h"


#ifdef VERSION_US
extern void func_800504BC(s16 *);
extern s16 D_8AF37560;
extern s16 D_8AF37562;

s32 func_8AF1B960(s32 arg0, u8 *arg1) {
    s16 position[2];

    switch (arg0) {
        case 0:
            break;
        case 1:
            func_800504BC(position);
            D_8AF37560 = *(s16 *)(arg1 + 8) + position[0];
            D_8AF37562 = *(s16 *)(arg1 + 0xA) + position[1];
            break;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_209BD0/func_8AF1B9C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_209BD0/func_8AF1BA18.s")

#ifndef M2C_FIELD /* mkdraft: m2c --valid-syntax helpers */
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
extern s32 D_8AF27480;
extern s32 D_8AF27484;
extern s32 D_8AF27488;
extern s32 D_8AF2748C;
extern void Ui_DrawGradientQuad(s32, s32, s32, s32, u8 *, u8 *);
extern s16 D_8AF27490;

s32 func_8AF1BAE8(s32 arg0, void *arg1) {
    s16 temp_a0;
    s16 sp24;
    s16 temp_a2;
    s16 temp_a3;

    if ((arg0 != 0) && (arg0 == 1)) {
        temp_a0 = M2C_FIELD(arg1, s16 *, 8);
        sp24 = M2C_FIELD(arg1, s16 *, 0xA);
        temp_a2 = M2C_FIELD(arg1, s16 *, 0xC);
        temp_a3 = M2C_FIELD(arg1, s16 *, 0xE);
        if (D_8AF27490 != 0x27) {
            if (D_8AF27490 == 0x46) {
                Ui_DrawGradientQuad((s32) temp_a0, (s32) sp24, (s32) temp_a2, (s32) temp_a3, &D_8AF27480, &D_8AF27484);
            }
        } else {
            Ui_DrawGradientQuad((s32) temp_a0, (s32) sp24, (s32) temp_a2, (s32) temp_a3, &D_8AF27488, &D_8AF2748C);
        }
    }
    return 0;
}

extern s16 D_8AF27490;
void func_8AF1BB84(s16 arg0) {
    D_8AF27490 = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_209BD0/func_8AF1BB9C.s")

extern void *D_8AF37244;

s32 func_8AF1BED8(void) {
    if ((*(s16 *)((u8 *)(D_8AF37244) + (0xA))) < 0) {
        return 1;
    }
    return 0;
}

extern s32 D_8AF27494;

s32 func_8AF1BF00(void) {
    if (-D_8AF27494 < (*(s16 *)((u8 *)(D_8AF37244) + (0xA)))) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/44/fragment44_209BD0/func_8AF1BF38.s")

extern void func_800498C4(void);
extern void func_800496A4(s32, s32);
extern void func_8004972C(s32, s32, s32, s32);
extern void func_800499EC(void);
extern void func_8AC05F00(void *);
extern u8 D_8AF37278[];
extern u8 D_8AF372F0[];

void func_8AF1C31C(void) {
    func_800498C4();
    func_800496A4(16, 0);
    func_8004972C(255, 255, 255, 255);
    func_800499EC();
    if (func_8AF1BED8() != 0) {
        func_8AC05F00(D_8AF37278);
    }
    if (func_8AF1BF00() != 0) {
        func_8AC05F00(D_8AF372F0);
    }
}
/* Preserve the original three alignment NOPs after this owner. */
#pragma C_FUNCTION_PADDING(12)
#endif
