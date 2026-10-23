#include "global.h"


#ifdef VERSION_US
typedef struct { f32 x, y, z; } AuxPosition3;
typedef u8 AuxTextureIds[4];
struct S1_GraphNode;
struct S1_MemoryBlock;
typedef s32 (*AuxGraphCallback)(s32, struct S1_GraphNode *);

extern u8 *D_8620E198;
extern Gfx *D_800D0510;
extern u8 *D_8009491C;
extern u32 D_862091F0[];
extern s32 func_8004C990(s32, s32);
extern u8 *func_8004CA60(u8 *);
extern void GeoRender_ApplyMaterialState(void);
extern u8 *func_87F025B8(void *, void (*)(void));
extern void func_80037E3C(struct S1_GraphNode *, AuxGraphCallback, void *);
extern void func_8003F1DC(void *);
extern void func_8003F114(u8 *, s16, s16, void *);
extern s32 main_pool_get_available(void);
extern u8 *MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(struct S1_MemoryBlock *);
extern void *process_geo_layout(struct S1_MemoryBlock *, void *);
extern s32 func_87F08DF8(void *, f32, f32, s32);
extern void func_87F024F4(void *, u8 *, s32);

void SceneAux_UpdatePosition(s32 event, u8 *node) {
    u32 index;
    if (event == 2) {
        index = *(u32 *)(node + 20);
        switch (index) {
            case 0:
                *(AuxPosition3 *)(node + 36) = *(AuxPosition3 *)(D_8620E198 + 466576);
                break;
            case 1:
                *(AuxPosition3 *)(node + 36) = *(AuxPosition3 *)(D_8620E198 + 466560);
                break;
            case 2:
                *(AuxPosition3 *)(node + 36) = *(AuxPosition3 *)(D_8620E198 + 466608);
                break;
            case 3:
                *(AuxPosition3 *)(node + 36) = *(AuxPosition3 *)(D_8620E198 + 466592);
                break;
        }
        *(f32 *)(node + 40) += 1.0f;
    }
}

void SceneAux_RenderModel(s32 event, void *node) {
    u8 *current;
    if (event == 5) {
        current = D_8009491C;
        gDPPipeSync(D_800D0510++);
        gDPSetCombineLERP(D_800D0510++, 0, 0, 0, TEXEL0, ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
        gDPSetEnvColor(D_800D0510++, 0, 0, 0, 150);
        gSPSegment(D_800D0510++, 15, func_8004CA60((u8 *)func_8004C990(434, (*(AuxTextureIds *)(D_8620E198 + 474296))[*(u32 *)(current + 20)])));
        gSPDisplayList(D_800D0510++, *(Gfx **)(D_8620E198 + 473984));
        GeoRender_ApplyMaterialState();
    }
}

void SceneAux_CreateModels(void) {
    s32 index;
    u8 *item;
    for (index = 0; index < 4; index++) {
        item = func_87F025B8(D_8620E198 + 472380, 0);
        if (item != 0) {
            func_80037E3C((struct S1_GraphNode *)(item + 36), (AuxGraphCallback)SceneAux_UpdatePosition, item);
            func_8003F1DC(item + 36);
            func_8003F114(item + 36, 0, -1, *(void **)(D_8620E198 + 368));
            *(s32 *)(item + 56) = index;
            *(f32 *)(item + 92) = 9.0f;
            *(f32 *)(item + 88) = 9.0f;
            *(f32 *)(item + 84) = 9.0f;
            *(s16 *)(item + 66) = -14199;
            switch (index) {
                case 0: *(s16 *)(item + 68) = 8192; break;
                case 1: *(s16 *)(item + 68) = 24576; break;
                case 2: *(s16 *)(item + 68) = -8192; break;
                case 3: *(s16 *)(item + 68) = -24576; break;
            }
        }
    }
}

void SceneAux_LoadResources(void) {
    u8 *state;
    state = MainPool_AllocState(main_pool_get_available(), 0);
    *(void **)(D_8620E198 + 368) = process_geo_layout((struct S1_MemoryBlock *)state, D_862091F0);
    MainPool_FinalizeAllocation((struct S1_MemoryBlock *)state);
    *(s32 *)(D_8620E198 + 473984) = func_87F08DF8((void *)func_8004C990(434, 6), 0.0f, -12.0f, 0x0F000000);
    func_87F024F4(D_8620E198 + 472380, D_8620E198 + 472400, 4);
    SceneAux_CreateModels();
}
#endif
