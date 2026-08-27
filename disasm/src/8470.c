#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80007870.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80007A84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80007AEC.s")

s32 func_80007A84();
extern s32 D_800D0554;
s32 StageFade_StartFromTransparent(void) {
    s32 var_v1;

    var_v1 = 0;
    if ((D_800D0554 != 0) && ((*(u8 *)((u8 *)(D_800D0554) + (0x11))) == 0)) {
        var_v1 = func_80007A84();
    }
    return var_v1;
}

extern s32 D_800D0554;
void StageFade_SetMode(s32 arg0) {
    if (D_800D0554 != 0) {
        ((u8 *)(u32)D_800D0554)[0x11] = arg0;
        ((u8 *)(u32)D_800D0554)[0x13] = 0;
        ((u8 *)(u32)D_800D0554)[0x12] = 0;
    }
}

void Profiler_SetDisplayModes(s32 arg0, s32 arg1) { extern s32 D_80087230; extern s32 D_80087234; if ((u32)arg0 < 3) D_80087230 = arg0; if ((u32)arg1 < 2) D_80087234 = arg1; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80007BD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80007DB4.s")

extern void GfxImage_ResetCurrent(void);
extern s32 func_8000339C(void);
extern void Memmap_SetSegmentMap(s32, s32, s32);
extern void func_80002178(void *);
extern void func_80007BD0(void);
extern void func_80007DB4(void);
extern u8 D_800D0510[];
void func_80007E18(void) {
    GfxImage_ResetCurrent();
    Memmap_SetSegmentMap(0, 0x80000000, func_8000339C());
    func_80002178(D_800D0510);
    func_80007BD0();
    func_80007DB4();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80007E6C.s")

void StageLoader_SwapDisplayListAndReset(void) { func_80006D6C(); func_80007E18(); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_800080E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80008188.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_800082E0.s")


s32 func_80008494(void) {
    return D_800D0554;
}


u8 StageContext_GetFadeMode(void) {
    return ((u8 *)(u32)D_800D0554)[0x11];
}

void StageContext_SaveAndSwitch(void *arg0) {
    s8 temp_v0;

    (*(u8 *)((u8 *)(arg0) + (0x11))) = (u8) (*(u8 *)((u8 *)(D_800D0554) + (0x11)));
    (*(u8 *)((u8 *)(arg0) + (0x12))) = (u8) (*(u8 *)((u8 *)(D_800D0554) + (0x12)));
    (*(u8 *)((u8 *)(arg0) + (0x13))) = (u8) (*(u8 *)((u8 *)(D_800D0554) + (0x13)));
    (*(u16 *)((u8 *)(arg0) + (0x14))) = (u16) (*(u16 *)((u8 *)(D_800D0554) + (0x14)));
    temp_v0 = (*(s8 *)((u8 *)(D_800D0554) + (0x16)));
    if (temp_v0 < (*(s8 *)((u8 *)(arg0) + (0xE)))) {
        (*(s8 *)((u8 *)(arg0) + (0x16))) = temp_v0;
    } else {
        (*(s8 *)((u8 *)(arg0) + (0x16))) = 0;
    }
    D_800D0554 = (s32) arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80008514.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80008574.s")

s32 func_8000204C();

void StageLoader_WaitForRetrace(void) {
    if (func_8000204C() == 0) {
        do {

        } while (func_8000204C() == 0);
    }
}

extern u8 D_800D0510[]; void func_80008624(void) { func_80002178(D_800D0510); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80008648.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_800086A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_80008734.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_800087E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_800088A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/8470/func_800088DC.s")

typedef struct {
    u8 pad16[0x16];
    s8 index16;
} Func80008944State;
s32 StageContext_GetCurrentImage(void) {
    s32 result = 0;
    if (D_800D0554 != 0) {
        Func80008944State *p = (Func80008944State *)(u32)D_800D0554;
        result = *(s32 *)((u8 *)p + (p->index16 << 2) + 0x18);
    }
    return result;
}

s32 func_80008970(void) { s32 value = 0; if (D_800D0554 != 0) { value = *(s8 *)((u8 *)(u32)D_800D0554 + 0x17); } return value; }

s32 StageContext_IsHighResolution(void) { extern s32 D_800D0554; s32 value = 0; if (D_800D0554 != 0) { value = ((s8 *)((u8 *)(u32)D_800D0554))[0xC] == 1; } return value; }
#endif
