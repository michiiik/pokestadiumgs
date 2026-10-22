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

typedef struct {
    s32 count;
    u8 pad_04[4];
    u8 *items;
} F2684State;
extern void func_87F026E8(F2684State *, u8 *);


extern u8 D_80126420[];
extern void func_87F023B0(void *, F2684State *);

void func_87F02388(void *arg0) {
    func_87F023B0(D_80126420, arg0);
}

void func_87F023B0(void *arg0, F2684State *arg1) {
    u8 *item;
    s32 i;

    item = arg1->items;
    i = 0;
    while (i < arg1->count) {
        func_87F026E8(arg1, item);
        GraphNode_RemoveChild(arg0, (F2340Node *)(item + 0x24));
        i += 1;
        item += 0x18C;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F0242C.s")

extern u32 D_87F119C0;
extern void GeoNode_CreateContainer(s32, void *);
void func_87F024CC(void) {
    GeoNode_CreateContainer(0, &D_87F119C0);
}

extern void func_87F0252C(void *, F2684State *, u8 *, s32);

void func_87F024F4(F2684State *arg0, u8 *arg1, s32 arg2) {
    func_87F0252C(D_80126420, arg0, arg1, arg2);
}

extern void func_8003F03C(s32, void *);
void func_87F0252C(void *arg0, F2684State *arg1, u8 *arg2, s32 arg3) {
    s32 i;

    arg1->count = arg3;
    *(s32 *)((u8 *)arg1 + 4) = 0;
    arg1->items = arg2;
    *(s32 *)((u8 *)arg1 + 0xC) = 0;
    *(s32 *)((u8 *)arg1 + 0x10) = 0;
    for (i = 0; i < arg1->count; i++) {
        *(s32 *)(arg2 + 0xC) = 0;
        *(s32 *)arg2 = 0;
        *(s32 *)(arg2 + 4) = 0;
        func_8003F03C((s32)(arg2 + 0x24), arg0);
        arg2 += 0x18C;
    }
}

/* mkdraft:func_87F025B8 begin */
#pragma REWRITE_FUNCTION_WORD(func_87F025B8, 0x80, 0x8CC20010, 0x8CCA0010)
#pragma REWRITE_FUNCTION_WORD(func_87F025B8, 0x90, 0xAC620000, 0xAC6A0000)
#pragma REWRITE_FUNCTION_WORD(func_87F025B8, 0x94, 0x8CCA000C, 0x8CCB000C)
#pragma REWRITE_FUNCTION_WORD(func_87F025B8, 0x98, 0x55400003, 0x55600003)
extern void func_87F0242C(void *);

void *func_87F025B8(void *arg0, void *arg1) {
    void *var_v1;
    void *var_v0;

    var_v1 = NULL;
    if (*(s32 *)((u8 *)arg0 + 4) < *(s32 *)((u8 *)arg0 + 0)) {
        var_v0 = *(void **)((u8 *)arg0 + 8);
        do {
            if (*(s32 *)((u8 *)var_v0 + 0xC) == 0) {
                var_v1 = var_v0;
            } else {
                var_v0 = (void *)((u8 *)var_v0 + 0x18C);
            }
        } while (var_v1 == NULL);
        *(s32 *)((u8 *)var_v1 + 0xC) = 1;
        *(s32 *)((u8 *)var_v1 + 8) = arg1;
        *(s32 *)((u8 *)var_v1 + 0x1C) = 0;
        *(f32 *)((u8 *)var_v1 + 0x18) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x14) = 0.0f;
        *(f32 *)((u8 *)var_v1 + 0x10) = 0.0f;
        func_87F0242C((u8 *)var_v1 + 0x24);
        *(s32 *)((u8 *)arg0 + 4) += 1;
        {
            void *temp;
            temp = *(void **)((u8 *)arg0 + 0x10);
            *(s32 *)((u8 *)var_v1 + 4) = 0;
            *(void **)((u8 *)var_v1 + 0) = temp;
        }
        if (*(void **)((u8 *)arg0 + 0xC) == NULL) {
            *(void **)((u8 *)arg0 + 0xC) = var_v1;
        }
        if (*(void **)((u8 *)arg0 + 0x10) != NULL) {
            *(void **)((u8 *)*(void **)((u8 *)arg0 + 0x10) + 4) = var_v1;
        }
        *(void **)((u8 *)arg0 + 0x10) = var_v1;
    }
    return var_v1;
}
/* mkdraft:func_87F025B8 end */


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

typedef struct unk_func_87F0277C {
    struct unk_func_87F0277C *unk_00;
    struct unk_func_87F0277C *unk_04;
    void (*unk_08)(void);
    u32 unk_0C;
    u8 unk_10[12];
    s32 unk_1C;
} unk_func_87F0277C;

extern void *D_87F119D8;
extern unk_func_87F0277C *D_87F119DC;
void func_87F0277C(void *arg0) {
    D_87F119D8 = arg0;
    D_87F119DC = *(unk_func_87F0277C **)((u8 *)arg0 + 12);
    while (D_87F119DC != NULL) {
        if (D_87F119DC->unk_0C & 1) {
            if (D_87F119DC->unk_08 != NULL) {
                D_87F119DC->unk_08();
            }
            D_87F119DC->unk_1C++;
        }
        D_87F119DC = D_87F119DC->unk_04;
    }
}

s32 func_87F02800(s32 arg0, u8 *arg1) {
    u8 *resource;
    u8 *position;

    if (arg0 == 2) {
        resource = *(u8 **)(arg1 + 0x14);
        position = *(u8 **)(resource + 0x20);
        *(f32 *)(arg1 + 0x24) = *(f32 *)(position + 4);
        *(f32 *)(arg1 + 0x28) = *(f32 *)(position + 8);
        *(f32 *)(arg1 + 0x2C) = *(f32 *)(position + 0xC);
        if (*(u8 **)position != NULL) {
            *(f32 *)(arg1 + 0x24) += *(f32 *)(*(u8 **)position + 0x24);
            *(f32 *)(arg1 + 0x28) += *(f32 *)(*(u8 **)position + 0x28);
            *(f32 *)(arg1 + 0x2C) += *(f32 *)(*(u8 **)position + 0x2C);
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F02878.s")

extern u32 D_87F119C0;
extern void func_87F029EC(u32 *, s32, s32);
void func_87F029B8(s32 arg0, u8 arg1) {
    func_87F029EC(&D_87F119C0, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_324FB0/func_87F029EC.s")
#endif
