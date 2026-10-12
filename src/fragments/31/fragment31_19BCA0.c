#include "global.h"


#ifdef VERSION_US
extern void Input_SetRepeatController(s32);
extern s32 D_80087200;
extern s32 D_880068B8;

void func_88228A20(void) {
    Input_SetRepeatController(D_80087200);
    D_880068B8 = 0;
}

typedef struct {
    u8 unused[0x5C];
    u8 selected;
    u8 padding[3];
    void (*callback)(void);
} Cleanup_88228A48;
extern u32 D_88234890;
extern s32 D_880068B4;
extern void func_88001900(void);
extern void Util_Free(s32);
void func_88228A48(void) {
    Cleanup_88228A48 *state = (Cleanup_88228A48 *)D_88234890;

    if (state->selected != 0) {
        state->callback();
    } else {
        Input_SetRepeatController(D_80087200);
        func_88001900();
        D_880068B4 = 1;
    }
    Util_Free((s32)D_88234890);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19BCA0/func_88228AB4.s")

extern u32 D_88234890;
extern void func_8821D930(s32);
void func_88228BA4(void) {
    func_8821D930((D_88234890 + 4));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/31/fragment31_19BCA0/func_88228BCC.s")
#endif
