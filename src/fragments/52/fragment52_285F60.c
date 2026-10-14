#include "global.h"


#ifdef VERSION_US
typedef struct F52Group {
    /* 0x00 */ s32 count;
    /* 0x04 */ u8 rest[0x10];
} F52Group;
typedef struct F52RelatedState {
    u8 pad00[0x20];
    /* 0x20 */ s32 state20;
} F52RelatedState;
typedef struct F52Item {
    u8 pad00[0x20];
    /* 0x20 */ F52RelatedState* related;
    u8 pad24[0x1C];
    /* 0x40 */ s16 angles[3];
    u8 pad46[2];
    /* 0x48 */ f32 position[3];
    /* 0x54 */ f32 scale[3];
    u8 pad60[0x12C];
} F52Item;
typedef struct F52State {
    u8 pad00[0x7B0];
    /* 0x07B0 */ void* graph;
    u8 pad7B4[0xA754];
    /* 0xAF08 */ F52Group group;
    /* 0xAF1C */ F52Item items[4];
    /* 0xB54C */ Gfx* displayList;
} F52State;
typedef struct F52Node {
    u8 pad00[0x14];
    /* 0x14 */ F52Item* source;
    u8 pad18[8];
    /* 0x20 */ s16 angle;
    u8 pad22[2];
    /* 0x24 */ f32 position[3];
    /* 0x30 */ f32 scale[3];
} F52Node;
extern F52State* D_86416C00;
extern u8 D_86409800[], D_86409C70[];
extern f32 D_86409C40, D_86409C44, D_86409C48;
extern Gfx* D_800D0510;
extern s32 main_pool_get_available(void);
extern void* MainPool_AllocState(s32, s32);
extern void MainPool_FinalizeAllocation(void*);
extern void* func_80040E80(void*, void*);
extern void func_8004C8C0(s32);
extern void* func_8004C990(s32, s32);
extern void* func_8004CA60(void*);
extern Gfx* func_87F08E3C(void*, s32);
extern void func_87F0252C(void*, F52Group*, F52Item*, s32);
extern void func_87F026E8(F52Group*, F52Item*);
extern void func_8003CD84(void);
void func_86407AA0(void) {
    void* pool;
    pool = MainPool_AllocState(main_pool_get_available(), 0);
    D_86416C00->graph = func_80040E80(pool, D_86409800);
    MainPool_FinalizeAllocation(pool);
    func_8004C8C0(0x157);
    func_8004C8C0(0x133);
    D_86416C00->displayList = func_87F08E3C(func_8004C990(0x133, 0), 0x0F000000);
    func_87F0252C(D_86409C70, &D_86416C00->group, D_86416C00->items, 4);
}

void func_86407B54(void) {
    s32 i;
    F52Item* item;
    item = D_86416C00->items;
    i = 0;
    while (i < D_86416C00->group.count) {
        func_87F026E8(&D_86416C00->group, item);
        item++;
        i++;
    }
}

void func_86407BF0(s32 kind, s32 unused) {
    if (kind == 5) {
        gDPPipeSync(D_800D0510++);
        gDPSetEnvColor(D_800D0510++, 0, 0, 0, 0x80);
        gDPSetCombineLERP(D_800D0510++, 0, 0, 0, ENVIRONMENT, ENVIRONMENT, 0, TEXEL0, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
        { Gfx* segment = D_800D0510++;
        segment->words.w0 = 0xDB06003C;
        segment->words.w1 = (u32)func_8004CA60(func_8004C990(0x133, 0)); }
        gSPDisplayList(D_800D0510++, D_86416C00->displayList);
        func_8003CD84();
    }
}

void func_86407CE0(s32 kind, F52Node* node) {
    F52Item* item;
    F52RelatedState* relation;
    f32 first;
    f32 second;
    item = node->source;
    relation = item->related;
    if (kind == 2) {
        node->position[0] = item->position[0];
        node->position[1] = 0.0f;
        node->position[2] = item->position[2];
        node->angle = item->angles[2];
        if (relation->state20 > 0) {
            first = D_86409C40;
            node->scale[2] = first;
            node->scale[1] = first;
            node->scale[0] = first;
        } else {
            first = D_86409C44;
            second = D_86409C48;
            node->scale[0] = first;
            node->scale[2] = second;
            node->scale[1] = second;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/52/fragment52_285F60/func_86407D58.s")
#endif
