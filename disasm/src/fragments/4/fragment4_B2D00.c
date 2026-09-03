#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804720.s")

extern void func_81804720(s32 arg0);
extern void func_8004C8C0(s32 arg0);
void func_818047E0(s32 arg0) {
    s32 var_s0;
    s32 var_a1;

    var_s0 = *(s32 *)((u8 *)(u32)arg0 + 0x30);
    var_a1 = arg0;
    func_81804720(arg0 + 4);
    if (*(s32 *)((u8 *)(u32)var_a1 + 0x30) != 0) {
        if (*(s16 *)(u8 *)(u32)var_s0 >= 0) {
            do {
                func_81804720(*(s32 *)((u8 *)(u32)var_s0 + 4));
                var_s0 += 8;
            } while (*(s16 *)((u8 *)(u32)var_s0) >= 0);
        }
        func_8004C8C0(0x1B);
        func_8004C8C0(0x79);
    }
}

extern void func_818047E0(s32 arg0);
void func_81804858(s32 arg0) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = *(s32 *)(u32)arg0;
    var_s1 = arg0;
    if (var_s0 != 0) {
        do {
            func_818047E0(var_s0);
            var_s0 = *(s32 *)((u8 *)(u32)var_s1 + 4);
            var_s1 += 4;
        } while (var_s0 != 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_818048A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804954.s")

extern void func_81804858(s32);
void WidgetTree_OpenMessagePanel_fragment4(u8 *arg0) {
    func_81804858(*(s32 *)arg0);
}

s32 func_81804A20(u8 *arg0) {
    return *(u16 *)(arg0 + 0x1A) == 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804A2C.s")

f32 __sinf(f32 arg0, f32 arg1);
extern f32 D_81805F98;
extern f32 D_81805F9C;
f32 func_81804AE8(f32 arg0) {
    if (arg0 <= 0.0f) {
        return 0.0f;
    }
    if (arg0 >= 1.0f) {
        return 1.0f;
    }
    return (__sinf((arg0 * D_81805F98) - D_81805F9C, arg0) * 0.5f) + 0.5f;
}
void func_81804AE8_padding(void) {}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804B74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804BC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81804FD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81805308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81805428.s")

extern void *func_818054D0(void *arg0, s32 arg1);
extern void func_81801CB8(void *arg0, void *arg1, void *arg2, s32 arg3);
void func_81805474(void *arg0, u8 *arg1, void *arg2) {
    void *first_offset;
    void *first;
    void *second;

    first = func_818054D0(arg0, arg1[0x1C]);
    first_offset = (u8 *)first + 0x10;
    second = func_818054D0(arg0, arg1[0x1D]);
    func_81801CB8(arg2, first_offset, (u8 *)second + 0x10, *(s32 *)(arg1 + 0x2C));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_818054D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_81805524.s")

s32 func_81805594(u8 *arg0, u8 *arg1) { return 1; }

s32 StageContext_GetFadeMode(s32);
s32 func_81805524();

s32 func_818055A4(void) {
    s32 var_a0;

    var_a0 = func_81805524() != 0;
    if (var_a0 == 0) {
        var_a0 = StageContext_GetFadeMode(var_a0) != 0;
    }
    return var_a0;
}

extern void *func_818054D0(void *arg0, s32 arg1);
extern s32 func_81804B74(void *arg0, void *arg1);
f32 func_818055E0(void *arg0, u8 *arg1) {
    void *first;
    void *second;
    f32 result;

    first = func_818054D0(arg0, arg1[0x1C]);
    second = func_818054D0(arg0, arg1[0x1D]);
    if (func_81804B74(first, second) != 0) {
        result = *(f32 *)(arg1 + 0x28);
    } else {
        result = 1.0f;
    }
    return result;
}

extern void func_8180567C(s32, s32, s32);
extern void func_818057D0();

void func_81805644(s32 arg0, s32 arg1, s32 arg2) {
    func_818057D0();
    func_8180567C(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_8180567C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/4/fragment4_B2D00/func_818057D0.s")
#endif
