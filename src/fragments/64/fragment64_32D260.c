#include "global.h"


#ifdef VERSION_US
extern void _bcopy(void *, void *, s32);
void func_87F0A5F0(s32 arg0) { s32 sp18[2]; _bcopy(&arg0, &sp18[0], 4); }

extern s32 main_pool_get_available(void);
extern s32 MainPool_AllocState(s32, s32);
extern s32 MainPool_AllocAligned(s32, s32, s32);
extern void MainPool_FinalizeAllocation(s32);
s32 func_87F0A61C(void) { s32 ptr = MainPool_AllocState(main_pool_get_available(), 0); s32 result = MainPool_AllocAligned(ptr, 0xC, 4); MainPool_FinalizeAllocation(ptr); return result; }

void func_87F0A66C(u8 *arg0, u32 *arg1, u32 *arg2) {
    arg0[0x28] = 2;
    *(u32 *)(arg0 + 0x2C) = *arg1;
    *(u32 *)(arg0 + 0x30) = *arg2;
}

typedef struct TreeNode_80050428 TreeNode_80050428;
extern void *func_8005049C(TreeNode_80050428 *, s32);
void func_87F0A688(TreeNode_80050428 *arg0, s32 arg1, s32 arg2) {
    u8 *entry = func_8005049C(arg0, arg1);
    if (entry == NULL) {
        func_87F0A5F0(arg1);
    } else {
        *(s16 *)(entry + 0x26) = arg2;
    }
}

void func_87F0A6C8(TreeNode_80050428 *arg0, s32 arg1, u32 *arg2, u32 *arg3) {
    u8 *entry = func_8005049C(arg0, arg1);
    if (entry == NULL) {
        func_87F0A5F0(arg1);
    } else {
        func_87F0A66C(entry, arg2, arg3);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D260/func_87F0A714.s")

extern void func_800504BC(s16 *);

void func_87F0A91C(s32 arg0, u8 *arg1) {
    struct { s16 position[2]; u32 unused; } scratch;
    u8 *entry;

    switch (arg0) {
        case 0:
            entry = *(u8 **)(arg1 + 0x20);
            func_800504BC(scratch.position);
            *(s16 *)(entry + 4) = *(s16 *)(arg1 + 8) + scratch.position[0];
            *(s16 *)(entry + 6) = *(s16 *)(arg1 + 0xA) + scratch.position[1];
            break;
        case 1:
            break;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/64/fragment64_32D260/func_87F0A988.s")

#ifndef M2C_FIELD /* sweep: m2c --valid-syntax helpers (mirrors mkdraft.py) */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif

M2C_UNK func_8005053C(u8 *, s32);                 /* extern */
M2C_UNK func_80050578(u8 *, s32);                 /* extern */

void func_87F0AA80(TreeNode_80050428 *arg0, s32 arg1, s32 arg2) {
    u8 *sp24;
    s32 sp20;
    s32 sp1C;
    s32 temp_v0;

    sp24 = func_8005049C(arg0, arg1);
    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    sp1C = temp_v0;
    sp20 = MainPool_AllocAligned(temp_v0, 0xC, 4);
    MainPool_FinalizeAllocation(sp1C);
    if (sp24 == NULL) {
        func_87F0A5F0(arg1);
        return;
    }
    func_8005053C(sp24, sp20);
    func_80050578(sp24, arg2);
}
/* Warning: struct TreeNode_80050428 is not defined (only forward-declared) */
typedef struct TargetGraphNode TargetGraphNode;
typedef s32 (*TargetGraphCallback)(s32, TargetGraphNode *);
extern void func_8004E308(TargetGraphNode *, TargetGraphCallback, void *);
void *func_87F0AB08(TreeNode_80050428 *arg0, s32 arg1, void (*arg2)(s32, u8 *), void *arg3) {
    void *entry = func_8005049C(arg0, arg1);

    if (entry == NULL) {
        func_87F0A5F0(arg1);
    } else {
        func_8004E308(entry, (TargetGraphCallback)arg2, arg3);
    }
    return entry;
}
#endif
