#include "global.h"


#ifdef VERSION_US
typedef struct PoolBlock3280 PoolBlock3280;
typedef void (*PoolFunc3280)(u8 *, s32);
struct PoolBlock3280 { PoolBlock3280 *prev; PoolBlock3280 *next; PoolFunc3280 func; s32 arg; };
typedef struct PoolState3280 { s32 freeSpace; PoolBlock3280 *listHeadL; PoolBlock3280 *listHeadR; struct PoolState3280 *prev; } PoolState3280;
typedef struct Pool3280 { OSMesg msgs[1]; OSMesgQueue queue; s32 available; PoolBlock3280 *start; PoolBlock3280 *end; PoolBlock3280 *listHeadL; PoolBlock3280 *listHeadR; PoolState3280 *mainState; } Pool3280;
extern u8 D_800CCDB0[];
extern OSMesgQueue D_800CCDB4;
#define POOL3280 (*(Pool3280 *)D_800CCDB0)
#define POOL_ALIGN16(v) (((v) + 0xF) & ~0xF)
void main_pool_init(void *arg0, void *arg1) {
    POOL3280.start = (PoolBlock3280 *)(u32)(POOL_ALIGN16((u32)arg0) + 0x10);
    POOL3280.end = (PoolBlock3280 *)(u32)(POOL_ALIGN16((u32)arg1 - 0xF) - 0x10);
    POOL3280.available = (s32)POOL3280.end - (s32)POOL3280.start;
    POOL3280.mainState = NULL;
    POOL3280.listHeadL = (PoolBlock3280 *)((u8 *)POOL3280.start - 0x10);
    POOL3280.listHeadL->prev = NULL;
    POOL3280.listHeadL->next = NULL;
    POOL3280.listHeadL->func = NULL;
    POOL3280.listHeadL->arg = 0;
    POOL3280.listHeadR = POOL3280.end;
    POOL3280.listHeadR->prev = NULL;
    POOL3280.listHeadR->next = NULL;
    POOL3280.listHeadL->func = NULL;
    POOL3280.listHeadL->arg = 0;
    osCreateMesgQueue(&D_800CCDB4, (OSMesg *)D_800CCDB0, 1);
    osSendMesg(&D_800CCDB4, NULL, 0);
}

s32 main_pool_alloc_from_pool(s32 arg0, s32 arg1) {
    PoolBlock3280 *newListHead;
    s32 result;
    arg0 = POOL_ALIGN16(arg0) + 0x10;
    result = 0;
    if ((arg0 != 0) && ((u32)arg0 <= (u32)POOL3280.available)) {
        if (arg1 == 0) {
            POOL3280.available -= arg0;
            newListHead = (PoolBlock3280 *)((u8 *)POOL3280.listHeadL + arg0);
            POOL3280.listHeadL->next = newListHead;
            newListHead->prev = POOL3280.listHeadL;
            newListHead->next = NULL;
            newListHead->func = NULL;
            newListHead->arg = 0;
            result = (s32)((u8 *)POOL3280.listHeadL + 0x10);
            POOL3280.listHeadL = newListHead;
        } else if (arg1 == 1) {
            POOL3280.available -= arg0;
            newListHead = (PoolBlock3280 *)((u8 *)POOL3280.listHeadR - arg0);
            POOL3280.listHeadR->prev = newListHead;
            newListHead->next = POOL3280.listHeadR;
            newListHead->prev = NULL;
            newListHead->func = NULL;
            newListHead->arg = 0;
            POOL3280.listHeadR = newListHead;
            result = (s32)((u8 *)newListHead + 0x10);
        }
    }
    return result;
}

extern s32 main_pool_get_available(void);

#pragma REWRITE_FUNCTION_HEX(func_800027F0, 935f01243dc8d7153c477b72c88922bb322f4431ff112c70862792b4a29718cd, 27bdffd8afb100183c11800d2631cdb08e2200282483fff0afb30020afb2001c0062082b00a09825afbf0024afb0001410200016006090258c4e000012600007ae2e00288dc3000825c40010506000048e2200280060f8098dc5000c8e2200288e2f001c8c58000401f8c82103224023ae28001cac4000048e2200285642ffef8c4e00001000001c000000008e30002c0070082b142000180070082b1420001600000000526000098e0900048e02000826040010504000058e0900040040f8098e05000c8e30002c8e0900048e2a001cae29002c8d2c000001495821016c6823ae2d001cad2000008e30002c0250082b1020ffec000000000c000000000000008fbf00248fb000148fb100188fb2001c8fb3002003e0000827bd0028)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_800027F0, 0xF8, 4, main_pool_get_available)
s32 func_800027F0(s32 arg0, s32 arg1) {
    PoolBlock3280 *target = (PoolBlock3280 *)((u8 *)arg0 - 0x10);
    PoolBlock3280 *block;

    if ((u32)target < (u32)POOL3280.listHeadL) {
        block = POOL3280.listHeadL->prev;
        do {
            if (arg1 != 0) {
                POOL3280.listHeadL = block;
                if (block->func != NULL) {
                    block->func((u8 *)block + 0x10, block->arg);
                }
            }
            POOL3280.available += (s32)POOL3280.listHeadL->next - (s32)POOL3280.listHeadL;
            POOL3280.listHeadL->next = NULL;
            block = POOL3280.listHeadL->prev;
        } while (target != POOL3280.listHeadL);
    } else {
        block = POOL3280.listHeadR;
        if ((u32)target >= (u32)block) {
            while (1) {
                if (arg1 != 0) {
                    if (block->func != NULL) {
                        block->func((u8 *)block + 0x10, block->arg);
                    }
                }
                POOL3280.listHeadR = block->next;
                POOL3280.available += (s32)POOL3280.listHeadR - (s32)POOL3280.listHeadR->prev;
                POOL3280.listHeadR->prev = NULL;
                block = POOL3280.listHeadR;
                if ((u32)target < (u32)block) {
                    break;
                }
            }
        }
    }
    return main_pool_get_available();
}

extern s32 main_pool_alloc_from_pool(s32, s32);
extern u8 *main_pool_set_func(u8 *, s32, s32);
s32 main_pool_alloc_with_func(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 result;
    osRecvMesg(&D_800CCDB4, NULL, 1);
    result = main_pool_alloc_from_pool(arg0, arg1);
    if (result != 0) {
        main_pool_set_func((u8 *)(u32)result, arg2, arg3);
    }
    osSendMesg(&D_800CCDB4, NULL, 0);
    return result;
}

s32 main_pool_alloc(s32 arg0, s32 arg1) {
    s32 result;

    osRecvMesg(&D_800CCDB4, NULL, 1);
    result = main_pool_alloc_from_pool(arg0, arg1);
    osSendMesg(&D_800CCDB4, NULL, 0);
    return result;
}

extern s32 func_800027F0(s32, s32);
extern s32 main_pool_get_available(void);
s32 main_pool_try_free(s32 arg0) {
    if (arg0 != 0) {
        osRecvMesg(&D_800CCDB4, NULL, 1);
        func_800027F0(arg0, 1);
        osSendMesg(&D_800CCDB4, NULL, 0);
    }
    return main_pool_get_available();
}

extern s32 main_pool_alloc_from_pool(s32, s32);
extern u8 *main_pool_set_func(u8 *, s32, s32);
extern s32 func_800027F0(s32, s32);
u8 *main_pool_realloc(u8 *arg0, u32 arg1)
{
  PoolBlock3280 *prior = (PoolBlock3280 *) (((u8 *) arg0) - 0x10);
  u8 *newaddr = 0;
  osRecvMesg(&D_800CCDB4, 0, 1);
  if (prior->next == ((Pool3280 *) D_800CCDB0)->listHeadL)
  {
    u32 diff = ((u32) prior->next) - ((u32) arg0);
    arg1 = (arg1 + 0xF) & (~0xF);
    if ((diff >= arg1) || (((u32) (*((Pool3280 *) D_800CCDB0)).available) >= (arg1 - diff)))
    {
      s32 savedArg = prior->arg;
      PoolFunc3280 savedFunc = prior->func;
      func_800027F0((s32) arg0, 0);
      newaddr = (u8 *) ((u32) main_pool_alloc_from_pool(arg1, 0));
      main_pool_set_func(newaddr, savedArg, (s32) savedFunc);
    }
  }
  osSendMesg(&D_800CCDB4, 0, 0);
  return newaddr;
}

extern s32 D_800CCDCC;
s32 main_pool_get_available(void) {
    s32 value = D_800CCDCC - 0x10;

    if (value < 0) {
        value = 0;
    }
    return value;
}

extern PoolState3280 *D_800CCDE0;
s32 main_pool_push_state(s32 arg0) {
    PoolState3280 *state;
    PoolBlock3280 *listHeadL;
    PoolBlock3280 *listHeadR;
    s32 available;
    osRecvMesg(&D_800CCDB4, NULL, 1);
    available = POOL3280.available;
    listHeadL = POOL3280.listHeadL;
    listHeadR = POOL3280.listHeadR;
    state = (PoolState3280 *)(u32)main_pool_alloc_from_pool(0x10, 0);
    if (state != NULL) {
        ((PoolBlock3280 *)((u8 *)state - 0x10))->arg = arg0;
        state->prev = POOL3280.mainState;
        state->freeSpace = available;
        state->listHeadL = listHeadL;
        state->listHeadR = listHeadR;
        D_800CCDE0 = state;
    }
    osSendMesg(&D_800CCDB4, NULL, 0);
    return main_pool_get_available();
}

/* Restore through the requested checkpoint tag; zero pops one checkpoint. */
s32 main_pool_pop_state(s32 arg0) {
    PoolState3280 *state;
    PoolBlock3280 *list_head_l;
    PoolBlock3280 *list_head_r;
    PoolBlock3280 *block;
    osRecvMesg(&D_800CCDB4, NULL, 1);
    do {
        state = POOL3280.mainState;
        list_head_l = state->listHeadL;
        list_head_r = state->listHeadR;
        POOL3280.available = state->freeSpace;
        POOL3280.mainState = state->prev;
        if (arg0 == 0) {
            break;
        }
        state = (PoolState3280 *)((u8 *)state - 16); /* Inspect the allocation header's tag. */
        if (arg0 == ((PoolBlock3280 *)state)->arg) {
            break;
        }
    } while (POOL3280.mainState != NULL);
    block = POOL3280.listHeadR;
    while ((u32)block < (u32)list_head_r) {
        if (block->func != NULL) {
            block->func((u8 *)block + 16, block->arg);
        }
        block = block->next;
    }
    block = POOL3280.listHeadL->prev;
    while ((u32)block >= (u32)list_head_l) {
        if (block->func != NULL) {
            block->func((u8 *)block + 16, block->arg);
        }
        block = block->prev;
    }
    POOL3280.listHeadL = list_head_l;
    POOL3280.listHeadR = list_head_r;
    osSendMesg(&D_800CCDB4, NULL, 0);
    return main_pool_get_available();
}

u8 *main_pool_search(u32 arg0, s32 *arg1) {
    PoolBlock3280 *node;
    PoolBlock3280 *otherNode;
    node = POOL3280.listHeadL->prev;
    while (node != NULL) {
        s32 isAddrLater = (arg0 >= (u32)((u8 *)node + 0x10));
        otherNode = node->next;
        if (isAddrLater && (arg0 < ((u32)otherNode & 0xFFFFFFFF))) {
            if (arg1 != NULL) {
                *arg1 = node->arg;
            }
            return (u8 *)node + 0x10;
        }
        node = node->prev;
    }
    node = POOL3280.listHeadR;
    otherNode = node->next;
    while (otherNode != NULL) {
        s32 isAddrLater = (arg0 >= (u32)((u8 *)node + 0x10));
        PoolBlock3280 *new_var = otherNode;
        if (isAddrLater && (arg0 < ((u32)new_var & 0xFFFFFFFF))) {
            if (arg1 != NULL) {
                *arg1 = node->arg;
            }
            return (u8 *)node + 0x10;
        }
        otherNode = (node = otherNode)->next;
    }
    return NULL;
}

u8 *main_pool_set_func(u8 *arg0, s32 arg1, s32 arg2) {
    arg0 -= 0x10;
    *(s32 *)(arg0 + 8) = arg2;
    *(s32 *)(arg0 + 0xC) = arg1;
    return arg0;
}

s32 MainPool_GetAllocationSize(u8 *arg0) { return *(s32 *)(arg0 - 0xC) - (s32)arg0; }

extern u8 D_800CCDB0[]; u8 *func_80002DF0(void) { return D_800CCDB0; }
#endif
