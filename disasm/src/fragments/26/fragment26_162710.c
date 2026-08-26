#include "global.h"


#ifdef VERSION_US
typedef struct { f32 x; f32 y; f32 z; } Vec3Local;
typedef struct {
    s16 active; u8 pad_02[2];
    Vec3Local position; Vec3Local velocity; Vec3Local scale;
    s16 misc; u8 pad_2A[2];
} Func81003E60State;
extern Vec3Local D_8100614C;
extern Vec3Local D_81006158;
extern Vec3Local D_81006164;
void func_81003E60(Func81003E60State *arg0) {
    arg0->active = 0;
    arg0->position = D_8100614C;
    arg0->velocity = D_81006158;
    arg0->scale = D_81006164;
    arg0->misc = 0;
}

typedef struct {
    u8 pad[8];
    u8 *pool;
} Func81003ECCHeaderRetry;
typedef struct {
    s16 active;
    u8 pad_02[2];
    u8 data[0x28];
} Func81003E60StateRetry;
extern Func81003ECCHeaderRetry *D_8100678C;
extern Func81003E60StateRetry *D_81006780;
extern Func81003ECCHeaderRetry *func_8003F54C();
extern void func_81003E60();
void func_81003ECC(void) {
    s32 i;
    D_8100678C = func_8003F54C();
    if (D_8100678C != NULL) {
        D_81006780 = (Func81003E60StateRetry *)D_8100678C->pool;
        if (D_81006780 != NULL) {
            for (i = 0; i < 10; i++) {
                func_81003E60(D_81006780);
                D_81006780++;
            }
        }
    }
}

extern s32 D_81006784, D_81006788;

void func_81003F44(void) {
    D_81006784 = 0;
    D_81006788 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81003F58.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_810045C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81004818.s")

typedef struct { s16 active; u8 data[0x2A]; } Func81005480Slot;
extern Gfx *func_81004818(Gfx *, Func81005480Slot *, void *, s16);
Gfx *Particle31_BuildDisplayList(Gfx *gfx, Func81005480Slot *slots, void *arg2, s16 arg3) {
    s32 i;
    for (i = 0; i < 10; i++, slots++) {
        if (slots->active == 1) {
            gfx = func_81004818(gfx, slots, arg2, arg3);
        }
    }
    return gfx;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81005524.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81005628.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/26/fragment26_162710/func_81005758.s")
#endif
