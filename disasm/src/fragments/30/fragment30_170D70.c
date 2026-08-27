#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_881038A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_88103A64.s")

extern void *D_80087200;
extern void Input_SetRepeatController(void *);
extern s32 D_880068B8;
void func_88103B90(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

extern void *D_88104EA0;
extern void Util_Free(void *);
void func_88103BB8(void) {
    u32 var_s0;
    s32 offset;
    void *state;
    state = D_88104EA0;
    var_s0 = 0;
    offset = 0;
    if (*(u16 *)((u8 *)state + 0x10) != 0) {
        do {
            Util_Free(*(void **)((u8 *)*(void **)((u8 *)state + 0x38) + offset));
            state = D_88104EA0;
            var_s0 += 1;
            offset += 4;
        } while (var_s0 < *(u16 *)((u8 *)state + 0x10));
        var_s0 = 0;
    }
    if (*(u16 *)((u8 *)state + 0x20) != 0) {
        offset = 0;
        do {
            Util_Free(*(void **)((u8 *)*(void **)((u8 *)state + 0x3C) + offset));
            state = D_88104EA0;
            var_s0 += 1;
            offset += 4;
        } while (var_s0 < *(u16 *)((u8 *)state + 0x20));
    }
    Util_Free(*(void **)((u8 *)state + 0x18));
    Util_Free(*(void **)((u8 *)D_88104EA0 + 0x28));
    Util_Free(*(void **)((u8 *)D_88104EA0 + 0x38));
    Util_Free(*(void **)((u8 *)D_88104EA0 + 0x3C));
    Util_Free(D_88104EA0);
}

extern void func_88103BB8(void);
extern s32 D_880068B4;
void func_88103CAC(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B4 = 1;
    func_88103BB8();
}

extern void *D_88104EA0;
extern void func_88004990(s32, s32);
void func_88103CE0(void) {
    func_88004990(**(u8 **)((u8 *)D_88104EA0 + 0), 0);
    func_88004990(**(u8 **)((u8 *)D_88104EA0 + 4), 0);
    D_880068B8 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_88103D30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_88103DC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_88104214.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/30/fragment30_170D70/func_88104730.s")
#endif
