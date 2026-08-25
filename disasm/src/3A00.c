#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80002E00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80002E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_80002EB8.s")

typedef struct S1_MemoryBlock {
    /* 0x00 */ struct S1_MemoryBlock *next;
    /* 0x04 */ u32 size;
} S1_MemoryBlock;
typedef unsigned int	S1_size_t;
typedef struct S1_MemoryPool {
    /* 0x00 */ OSMesg msgs[1];
    /* 0x04 */ OSMesgQueue queue;
    /* 0x1C */ S1_size_t available;
    /* 0x20 */ struct S1_MemoryBlock *firstBlock;
    /* 0x24 */ struct S1_MemoryBlock freeList;
} S1_MemoryPool;
void func_80002F90(S1_MemoryPool* pool, void* addr) {
    struct S1_MemoryBlock* block;
    struct S1_MemoryBlock* freeList;

    if (addr != NULL) {
        osRecvMesg(&pool->queue, NULL, 1);
        block = (struct S1_MemoryBlock*)((u8*)addr - sizeof(struct S1_MemoryBlock));
        freeList = pool->freeList.next;
        if (pool->freeList.next == NULL) {
            pool->freeList.next = block;
            block->next = NULL;
        } else if (block < pool->freeList.next) {
            if ((u32)pool->freeList.next == ((u32)block + (u32)block->size)) {
                block->size += ((u32)freeList->size);
                block->next = freeList->next;
                pool->freeList.next = block;
            } else {
                block->next = pool->freeList.next;
                pool->freeList.next = block;
            }
        } else {
            while (freeList->next != NULL) {
                if (freeList < block && block < freeList->next) {
                    break;
                }
                freeList = freeList->next;
            }
            if (((u32)freeList + (u32)freeList->size) == (u32)block) {
                freeList->size += block->size;
                block = freeList;
            } else {
                block->next = freeList->next;
                freeList->next = block;
            }
            if (block->next != NULL && (u32)block->next == ((u32)block + (u32)block->size)) {
                block->size = (u32)block->size + (u32)block->next->size;
                block->next = block->next->next;
            }
        }
        osSendMesg(&pool->queue, NULL, 0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/3A00/func_800030D0.s")

#define ALIGN16(val) (((val) + 0xFu) & ~0xFu)
void func_80003120(struct S1_MemoryBlock* block) {
    s32 size = ALIGN16(block->size + 0x10);

    func_80002A40(block, size);
    block->next = (void*)(size - 0x10);
}

u8 *func_80003164(u8 *arg0, s32 arg1) {
    s32 value = (arg1 & ~3) - 0x10;
    u8 *ptr = arg0 + 0x10;
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 0) = value;
    *(u8 **)(arg0 + 8) = ptr;
    *(u8 **)(arg0 + 0xC) = ptr;
    return arg0;
}

typedef struct { s32 freeSpace; s32 listHeadL; s32 listHeadR; s32 prev; } MainPoolState;
s32 func_8000318C(MainPoolState *state, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_a3;
    s32 var_v0;
    s32 ret = 0;
    if (arg2 > 0) var_v0 = ((state->prev + arg2) - 1) & ~(arg2 - 1);
    else var_v0 = state->prev;
    temp_a2 = (var_v0 - state->prev) + arg1;
    if (temp_a2 > 0) {
        temp_a3 = state->listHeadL + temp_a2;
        if (state->freeSpace >= temp_a3) {
            ret = var_v0;
            state->prev += temp_a2;
            state->listHeadL = temp_a3;
        }
    }
    return ret;
}

void func_800031FC(u8 *arg0, s32 arg1) { if (*(s32 *)(arg0 + 0) >= arg1) { *(s32 *)(arg0 + 4) = arg1; *(s32 *)(arg0 + 0xC) = *(s32 *)(arg0 + 8) + arg1; } }

void func_80003224(u8 *arg0) {
    u8 *ptr = arg0 + 0x10;
    *(s32 *)(arg0 + 4) = 0;
    *(u8 **)(arg0 + 8) = ptr;
    *(u8 **)(arg0 + 0xC) = ptr;
}
#endif
