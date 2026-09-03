#include "global.h"


#ifdef VERSION_US
typedef struct F2340Node {
    u8 pad_00[4];
    struct F2340Node *prev;
    struct F2340Node *next;
} F2340Node;
typedef struct {
    u8 pad_00[0xC];
    F2340Node *child;
} F2340State;
extern void GraphNode_RemoveChild(F2340State *, F2340Node *);
void func_87F02340(F2340State *arg0) {
    F2340Node *node;
    node = arg0->child;
    while (node) {
        GraphNode_RemoveChild(arg0, node);
        node = arg0->child;
    }
}

extern u8 D_80126420[];
extern void func_87F023B0(void *, void *);

void func_87F02388(void *arg0) {
    func_87F023B0(D_80126420, arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F023B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F0242C.s")

extern u32 D_87F119C0;
extern void func_80037E9C(s32, void *);
void func_87F024CC(void) { func_80037E9C(0, &D_87F119C0); }

extern void func_87F0252C(void *, void *, s32, s32);

void func_87F024F4(void *arg0, s32 arg1, s32 arg2) {
    func_87F0252C(D_80126420, arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F0252C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F025B8.s")

typedef struct {
    s32 count;
    u8 pad_04[4];
    u8 *items;
} F2684State;
extern void func_87F026E8(F2684State *, u8 *);

void func_87F02684(F2684State *arg0) {
    u8 *item;
    s32 i;
    item = arg0->items;
    i = 0;
    while (i < arg0->count) {
        func_87F026E8(arg0, item);
        i += 1;
        item += 0x18C;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F026E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F0277C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F02800.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F02878.s")

extern u32 D_87F119C0;
extern void func_87F029EC(u32 *, s32, s32);
void func_87F029B8(s32 arg0, u8 arg1) {
    func_87F029EC(&D_87F119C0, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F029EC.s")
#endif
