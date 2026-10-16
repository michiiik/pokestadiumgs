#include "global.h"


#ifdef VERSION_US
typedef struct {
    u8 pad0[0xA];
    s16 unk_0A;
    u16 unk_0C;
    u8 unk_0E;
} Struct_88307FB0;

extern s16 D_88308F10;
extern u8 D_88308E0F;

void func_88307FB0(Struct_88307FB0 *arg0) {
    s32 diff = arg0->unk_0C - arg0->unk_0E;
    s16 old = D_88308F10;

    if (diff == 0) {
        D_88308F10 = 0x3F;
    } else {
        f32 f = (f32)(arg0->unk_0A * 204) / (f32)diff;
        D_88308F10 = (s32)((f > 0.0f ? 0.5f : -0.5f) + f) + 0x3F;
    }

    if (old != D_88308F10) {
        D_88308E0F = 2;
    }
}
#endif
