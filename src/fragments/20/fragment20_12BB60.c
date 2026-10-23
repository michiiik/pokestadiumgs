#include "global.h"


#ifdef VERSION_US
typedef struct {
    f32 x;
    f32 y;
} RecordTrailPoint;

// The free-slot scan advances by 2068 bytes; update wraps the point index at 256.
typedef struct {
    s16 index;
    s16 unk_02;
    s16 count;
    s16 unk_06;
    f32 step;
    RecordTrailPoint velocity;
    RecordTrailPoint points[256];
} RecordTrail;
typedef char RecordTrailSize[sizeof(RecordTrail) == 2068 ? 1 : -1];
extern void func_82603D70(RecordTrail *, s32, s32);
extern s32 func_8004C990(s32, s32);
extern s32 func_8004D1FC(u8 *);
extern Gfx *D_800D0510;
extern Gfx D_80094E78[];
extern Gfx D_80094F50[];

void func_82603A90(s16 *arg0) {
    *arg0 = -1;
}

s16 *func_82603A9C(s16 *arg0, s32 arg1) {
    s16 *new_var;
    s16 *current;
    s16 *result;
    s32 index;

    result = 0;
    index = 0;
    if (arg1 > 0) {
        current = (new_var = arg0);
        do {
            index += 1;
            if ((*current) == -1) {
                result = current;
                break;
            }
            current += 0x40A;
        } while (index != arg1);
    }
    return result;
}
void func_82603AD8(RecordTrail *arg0, f32 arg1,
                  RecordTrailPoint *arg2, RecordTrailPoint *arg3) {
    arg0->index = 0;
    arg0->unk_02 = 0;
    arg0->count = 1;
    arg0->step = arg1;
    arg0->velocity = *arg2;
    arg0->points[arg0->index] = *arg3;
}

void TrailEffect_Advance(RecordTrail *arg0, s32 arg1) {
    s32 index;
    RecordTrailPoint origin;
    s32 next_index;

    if (arg0->index != -1) {
        origin = arg0->points[arg0->index];
        for (index = 0; index < arg1; index++) {
            next_index = (arg0->index + index + 1) % 256;
            arg0->points[next_index].x = origin.x + arg0->velocity.x * arg0->step * (index + 1);
            arg0->points[next_index].y = origin.y + arg0->velocity.y * arg0->step * (index + 1);
            if (arg0->count < 256) {
                arg0->count++;
            }
        }
        arg0->index = (arg0->index + arg1) % 256;
        if (arg0->points[arg0->index].x < -640.0f) {
            arg0->index = -1;
        } else if (arg0->points[arg0->index].x > 1280.0f) {
            arg0->index = -1;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12BB60/func_82603D70.s")

extern u8 D_826163E0[];
extern RecordTrail D_826163E8[8];
extern void func_800226C0(s32);
extern s32 func_8004C8C0(u16);

s32 TrailEffect_Initialize(void) {
    s32 index;

    func_800226C0(100);
    _bzero(D_826163E0, 16552);
    if (func_8004C8C0(307) != 0) {
        ((u16 *)D_826163E0)[0] |= 1;
        ((u16 *)D_826163E0)[1] = 32;
        for (index = 0; index < 8; index++) {
            func_82603A90(&D_826163E8[index].index);
        }
    }
    return (((u16 *)D_826163E0)[0] & 1) != 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12BB60/func_82604170.s")

s32 TrailEffect_DrawAll(void) {
    u16 *texture;
    s32 index;

    if ((((u16 *)D_826163E0)[0] & 1) != 0) {
        texture = (u16 *)func_8004C990(307, 2);
        if (func_8004D1FC((u8 *)texture) != 0) {
            gSPDisplayList(D_800D0510++, D_80094E78);
            for (index = 0; index < 8; index++) {
                func_82603D70(&D_826163E8[index], texture[0], texture[1]);
            }
            gSPDisplayList(D_800D0510++, D_80094F50);
        }
    }
    return (((u16 *)D_826163E0)[0] & 1) != 0;
}
#endif
