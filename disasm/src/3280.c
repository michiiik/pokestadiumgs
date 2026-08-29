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

#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/func_800027F0.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/3280/main_pool_pop_state.s")

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
