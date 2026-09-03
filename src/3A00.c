#include "global.h"


#ifdef VERSION_US
s32 main_pool_alloc(s32, s32);
s32 mem_pool_init(s32, s32);
s32 mem_pool_try_init(s32 arg0, s32 arg1) {
    s32 block;
    s32 result;

    arg0 = (arg0 + 3) & ~3;
    block = main_pool_alloc(arg0, arg1);
    if (block != 0) {
        result = mem_pool_init(block, arg0);
    }
    return result;
}

s32 mem_pool_init(s32 arg0, s32 arg1) {
    u8 *base;
    s32 size;
    OSMesgQueue *queue;

    base = (u8 *)arg0;
    size = (arg1 & ~3) - 0x28;
    *(s32 *)(base + 0x1C) = size;
    *(u8 **)(base + 0x20) = base + 0x28;
    *(u8 **)(base + 0x24) = base + 0x28;
    *(s32 *)(base + 0x28) = 0;
    *(s32 *)(base + 0x2C) = size;
    queue = (OSMesgQueue *)(base + 4);
    osCreateMesgQueue(queue, (OSMesg *)base, 1);
    osSendMesg(queue, NULL, 0);
    return (s32)base;
}

typedef struct MemPoolBlock3A00 {
    struct MemPoolBlock3A00 *next;
    u32 size;
} MemPoolBlock3A00;
typedef struct MemPool3A00 {
    OSMesg msgs[1];
    OSMesgQueue queue;
    u32 available;
    MemPoolBlock3A00 *firstBlock;
    MemPoolBlock3A00 freeList;
} MemPool3A00;
void *mem_pool_alloc(MemPool3A00 *node, s32 size) {
    MemPoolBlock3A00 *freeBlock;
    void *addr;

    osRecvMesg(&node->queue, 0, 1);

    addr = NULL;
    size = ((size + 3) & ~3) + sizeof(MemPoolBlock3A00);
    freeBlock = &node->freeList;

    while (freeBlock->next != NULL) {
        if (freeBlock->next->size >= size) {
            addr = (u8 *)freeBlock->next + sizeof(MemPoolBlock3A00);
            if (freeBlock->next->size - size <= sizeof(MemPoolBlock3A00)) {
                freeBlock->next = freeBlock->next->next;
            } else {
                MemPoolBlock3A00 *newBlock = (MemPoolBlock3A00 *)((u8 *)freeBlock->next + size);
                newBlock->size = freeBlock->next->size - size;
                newBlock->next = freeBlock->next->next;
                freeBlock->next->size = size;
                freeBlock->next = newBlock;
            }
            break;
        }
        freeBlock = freeBlock->next;
    }
    osSendMesg(&node->queue, 0, 0);
    return addr;
}

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
void mem_pool_free(S1_MemoryPool* pool, void* addr) {
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

u8 *MainPool_InitState(u8 *, s32);
u8 *MainPool_AllocState(s32 arg0, s32 arg1) {
    s32 block;
    u8 *result = NULL;

    arg0 = (arg0 + 3) & ~3;
    block = main_pool_alloc(arg0, arg1);
    if (block != 0) {
        result = MainPool_InitState((u8 *)block, arg0);
    }
    return result;
}

#define ALIGN16(val) (((val) + 0xFu) & ~0xFu)
void MainPool_FinalizeAllocation(struct S1_MemoryBlock* block) {
    s32 size = ALIGN16(block->size + 0x10);

    func_80002A40(block, size);
    block->next = (void*)(size - 0x10);
}

u8 *MainPool_InitState(u8 *arg0, s32 arg1) {
    s32 value = (arg1 & ~3) - 0x10;
    u8 *ptr = arg0 + 0x10;
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 0) = value;
    *(u8 **)(arg0 + 8) = ptr;
    *(u8 **)(arg0 + 0xC) = ptr;
    return arg0;
}

typedef struct { s32 freeSpace; s32 listHeadL; s32 listHeadR; s32 prev; } MainPoolState;
s32 MainPool_AllocAligned(MainPoolState *state, s32 arg1, s32 arg2) {
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

void MainPool_ResetStateToOffset(u8 *arg0, s32 arg1) { if (*(s32 *)(arg0 + 0) >= arg1) { *(s32 *)(arg0 + 4) = arg1; *(s32 *)(arg0 + 0xC) = *(s32 *)(arg0 + 8) + arg1; } }

void MainPool_ResetState(u8 *arg0) {
    u8 *ptr = arg0 + 0x10;
    *(s32 *)(arg0 + 4) = 0;
    *(u8 **)(arg0 + 8) = ptr;
    *(u8 **)(arg0 + 0xC) = ptr;
}
#endif
