#include "global.h"


#ifdef VERSION_US
typedef struct {
    u32 segments[2];
    u32 textures[1];
} Func810059D0Addresses;
extern void func_8007087C(void);
extern Gfx *func_80070974(Gfx *);
#define Func810059D0_LoadTextureBlock(pkt, timg) { \
    gDPSetTextureImage((pkt), G_IM_FMT_IA, G_IM_SIZ_16b, 1, (timg)); \
    gDPSetTile((pkt), G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD); \
    gDPLoadSync((pkt)); \
    gDPLoadBlock((pkt), G_TX_LOADTILE, 0, 0, 0x3FF, 0x200); \
    gDPPipeSync((pkt)); \
    gDPSetTile((pkt), G_IM_FMT_IA, G_IM_SIZ_8b, 4, 0, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD); \
    gDPSetTileSize((pkt), G_TX_RENDERTILE, 0, 0, 0x7C, 0xFC); \
}
Gfx *DisplayList_BuildAnimatedModelTexture(Gfx *gfx, Func810059D0Addresses *addresses, s32 index) {
    Func810059D0_LoadTextureBlock(gfx++, addresses->textures[index]);
    func_8007087C();
    gfx = func_80070974(gfx);
    gSPSetGeometryMode(gfx++, 0x00020000);
    gSPEndDisplayList(gfx++);
    return gfx;
}

typedef struct { u8 pad[0x14]; u32 *addresses; Gfx *gfx; } Func81005AC0UlocA;
typedef struct { u16 unused; u16 index; u32 *addresses; } Func81005AC0UlocalsA;
extern u8 *D_8009491C; extern u16 D_80094904; extern void *func_8003F54C(void *); extern Gfx *func_80006DEC(s32);
void func_81005AC0(s32 arg0, Func81005AC0UlocA *state) {
 volatile u8 stack_pad[2]; Func81005AC0UlocalsA locals; Gfx *gfx;
 if(arg0==2) { if(func_8003F54C(D_8009491C)!=NULL) {
 locals.index=D_80094904; locals.addresses=state->addresses; gfx=func_80006DEC(0x140);
 state->gfx=gfx; DisplayList_BuildAnimatedModelTexture(gfx,locals.addresses,locals.index%8); } }
}
#endif
