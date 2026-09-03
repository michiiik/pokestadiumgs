#include "global.h"


#ifdef VERSION_US
extern u8 D_8800ED40; extern u8 D_8800ED41;
void func_880022F0(void) { D_8800ED40 = 10; D_8800ED41 = 1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_8800230C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880024FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_8800254C.s")

typedef struct { u8 pad0[4]; s16 mode; u8 pad6[2]; s32 status; u8 padC[4]; u16 x; u16 alt; s16 out; } Fragment29Node;
typedef struct { u8 pad0[8]; u16 flags; } Fragment29Input;
extern s16 func_8800230C(void);
extern void func_8800254C(Fragment29Node *);
extern Fragment29Input *D_80087200;
void func_88002640(Fragment29Node *arg0) {
    s16 mode;
    s16 current;

    if (arg0->status != 0) goto done;
    mode = func_8800230C();
    current = arg0->mode;
    if (mode == current) goto done;
    if (current != 0) goto set_status;
    arg0->mode = mode;
    if (mode == 0x10) goto positive;
    if (mode == 0x20) goto negative;
    if (mode == 0x100) goto positive;
    if (mode != 0x200) goto done;
negative:
    if (D_80087200->flags & 0x220) arg0->out = -arg0->x;
    else arg0->out = -arg0->alt;
    goto done;
positive:
    if (D_80087200->flags & 0x110) arg0->out = arg0->x;
    else arg0->out = arg0->alt;
    goto done;
set_status:
    arg0->status = 1;
done:
    func_8800254C(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002720.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002820.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002958.s")

extern s32 func_800472E0(u8 *); extern s32 func_800472B8(s32);
s32 func_88002A08(u8 **arg0, u16 arg1, s32 arg2, s16 arg3) {
    s32 temp_s2;
    s32 temp_s3;
    s32 var_s0;
    s32 var_s2;
    u8 **var_s1;
    s32 result;

    temp_s3 = arg1;
    var_s2 = 0;
    var_s0 = 0;
    if (temp_s3 != 0) {
        var_s1 = arg0;
        do {
            temp_s2 = func_800472E0(*var_s1);
            var_s0 += 1;
            var_s2 += temp_s2;
            var_s1 += 1;
            var_s2 &= 0xFFFF;
        } while (var_s0 != temp_s3);
    }
    result = func_800472B8(arg2);
    return (result * var_s2 + (arg3 * (var_s2 - 1))) & 0xFFFF;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002AA8.s")

extern Gfx *D_800D0510;
void func_88002BA0(u8 arg0, u8 arg1, u8 arg2) {
    gDPPipeSync(D_800D0510++);
    gDPSetEnvColor(D_800D0510++, arg0, arg1, arg2, 0xFF);
    gDPSetRenderMode(D_800D0510++, 0x0F0A7008, 0);
}

void func_88002C2C(u8 arg0, u8 arg1, u8 arg2) {
    gDPPipeSync(D_800D0510++);
    gDPSetEnvColor(D_800D0510++, arg0, arg1, arg2, 0xFF);
    gDPSetRenderMode(D_800D0510++, 0x0F0A4000, 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002CB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88002EC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880032C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_8800335C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003430.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003480.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003534.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880036CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003858.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88003A00.s")

extern void func_88003A00();
extern s8 D_8800EF18;
void func_88003FBC(void *arg0) {
    s8 var_v0;

    if ((*(s32 *)((u8 *)(arg0) + (0x1C))) == 3) {
        if ((*(s32 *)((u8 *)(arg0) + (0x14))) == 3) {
            var_v0 = 4;
        } else {
            var_v0 = D_8800EF18;
        }
        if (var_v0 == (*(s8 *)((u8 *)(arg0) + (0x20)))) {
            func_88003A00();
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004014.s")

extern u8 D_8800ED50[]; extern void func_88003A00(u8 *);
void func_880040D4(void) {
    u8 *entry;
    u32 i;
    s32 state;
    u8 *child;
    void (*callback)(void);

    entry = D_8800ED50;
    i = 0;
    state = 2;
    do {
        child = entry + 4;
        if ((*(s32 *)(entry + 0x20) == state) && (*(s32 *)(child + 0x28) != 0)) {
            callback = (void (*)(void))(u32)*(u32 *)(child + 0x34);
            if (callback != 0) {
                callback();
            }
        }
        i += 1;
        entry += 0x4C;
    } while (i < 6);

    entry = D_8800ED50;
    i = 0;
    do {
        if (*(s32 *)(entry + 0x20) != 0) {
            func_88003A00(entry + 4);
        }
        i += 1;
        entry += 0x4C;
    } while (i != 6);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004180.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_880046EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004804.s")

extern u8 D_8800ED50[];
extern void func_880046EC(s32, s32, s16, s16, s32, s32, u8, u8, u8,
                          s32 *, s32 *, s32 *, s32 *, u8, u8, void *);

void func_880048D4(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5,
                   u8 arg6, u8 arg7, u8 arg8, s32 *arg9, s32 *arg10,
                   s32 *arg11, s32 *arg12, u8 arg13, u8 arg14, s32 arg15) {
    u8 *entry;

    entry = D_8800ED50 + ((u8)arg15 * 0x4C);
    if (*(s32 *)(entry + 0x20) == 0) {
        func_880046EC(arg0, arg1, arg2, arg3, arg4, arg5,
                       arg6, arg7, arg8, arg9, arg10, arg11, arg12,
                       arg13, arg14, entry);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/29/fragment29_168330/func_88004990.s")
#endif
