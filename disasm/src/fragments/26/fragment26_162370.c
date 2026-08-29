#include "global.h"


#ifdef VERSION_US
Gfx *DisplayList_BuildSelectedTextureSegment(Gfx *gfx, u32 *textures, s32 index) {
    gDPLoadTextureBlock(gfx++, textures[index + 1], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
        G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD, G_TX_NOLOD);
    gSPEndDisplayList(gfx++);
    return gfx;
}

typedef struct {
    unsigned char pad[0x14];
    u32 *textures;
    Gfx *gfx;
} TextureState81003B78h2;
typedef struct {
    unsigned char pad_00[0x1A];
    s16 modelId;
    unsigned char pad_1C[0x24];
    s16 unk_40;
    unsigned char pad_42[6];
    s32 unk_48;
} GlobalState81003B78h2;
extern GlobalState81003B78h2 *D_8009491C;
extern u16 D_80094904;
extern void *Gfx_AllocDisplayList();
void DisplayList_InitSelectedTextureSegment(s32 arg0, TextureState81003B78h2 *state) {
    s32 index;
    u32 *textures;
    if (arg0 == 2) {
        textures = state->textures;
        state->gfx = (Gfx *)Gfx_AllocDisplayList(0x50);
        if (D_8009491C->modelId == 0x58) {
            index = D_8009491C->unk_48 >> 16;
            if (index >= 0x42) index -= 0x42; else index = 0;
            if (index >= 8) index = 0;
            if (D_8009491C->unk_40 >= 2) index = 0;
        } else {
            index = D_80094904 & 7;
        }
        DisplayList_BuildSelectedTextureSegment(state->gfx, textures, index);
    }
}
#endif
