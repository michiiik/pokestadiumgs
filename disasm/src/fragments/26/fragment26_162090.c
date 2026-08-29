#include "global.h"


#ifdef VERSION_US
typedef struct {
    u32 segments[2];
    u32 textures[1];
} DisplayListAddresses26;

Gfx* DisplayList_BuildIndexedTextureSegment(Gfx* gfx, DisplayListAddresses26* addresses, s32 index) {
    gSPDisplayList(gfx++, addresses->segments[0]);
    gDPSetTextureImage(gfx++, G_IM_FMT_I, G_IM_SIZ_16b, 1, addresses->textures[index]);
    gDPSetTile(gfx++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(gfx++);
    gDPLoadBlock(gfx++, 7, 0, 0, 0x3FF, 0x200);
    gDPPipeSync(gfx++);
    gDPSetTile(gfx++, G_IM_FMT_I, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_CLAMP, 0, 0, G_TX_CLAMP, 0, 0);
    gDPSetTileSize(gfx++, 0, 0, 0, 0x7C, 0xFC);
    gSPDisplayList(gfx++, addresses->segments[1]);
    gSPEndDisplayList(gfx++);
    return gfx;
}

typedef struct {
    unsigned char pad[0x14];
    u32* addresses;
    Gfx* gfx;
} Func810038BCState;
extern void* Gfx_AllocDisplayList();
extern Gfx* DisplayList_BuildIndexedTextureSegment();
extern u16 D_80094904;

void DisplayList_InitIndexedTextureSegment(s32 arg0, Func810038BCState* state) {
    Gfx* gfx;
    u32* addresses;
    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = Gfx_AllocDisplayList(0x50);
        state->gfx = gfx;
        DisplayList_BuildIndexedTextureSegment(gfx, addresses, D_80094904 & 7);
    }
}

void DisplayList_BuildTwoSegmentChain(Gfx* gfx, u32* addresses) {
    gSPDisplayList(gfx++, *addresses);
    gSPDisplayList(gfx++, addresses[1]);
    gSPEndDisplayList(gfx++);
}

extern void DisplayList_BuildTwoSegmentChain();

void DisplayList_InitTwoSegmentChain(s32 arg0, Func810038BCState* state) {
    Gfx* gfx;
    u32* addresses;
    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = Gfx_AllocDisplayList(0x18);
        state->gfx = gfx;
        DisplayList_BuildTwoSegmentChain(gfx, addresses);
    }
}

extern u8* D_8009491C;

void DisplayList_BuildConditionalSegment(Gfx* gfx, u32* addresses) {
    if (((u8*)D_8009491C)[0x1C] == 0) {
        gSPDisplayList(gfx++, addresses[0]);
    }
    gSPEndDisplayList(gfx++);
}

extern void DisplayList_BuildConditionalSegment();

void func_810039CC(s32 arg0, Func810038BCState* state) {
    Gfx* gfx;
    u32* addresses;
    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = Gfx_AllocDisplayList(0x50);
        state->gfx = gfx;
        DisplayList_BuildConditionalSegment(gfx, addresses);
    }
}
#endif
