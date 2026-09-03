#include "global.h"


#ifdef VERSION_US
extern s32 D_80128120;
extern u8 D_80128128[];
typedef struct Pair4EC00G { u8 bytes[4]; } Pair4EC00G;
void func_8004EC00(s32 arg0, s32 arg1) {
    s32 index;
    Pair4EC00G *entry;
    Pair4EC00G *entry2;
    index = D_80128120;
    if (index < 0x1F) {
        entry = (Pair4EC00G *)(D_80128128 + index * 4);
        entry[1] = entry[0];
        D_80128120 = index + 1;
        index = D_80128120;
    }
    entry2 = (Pair4EC00G *)(D_80128128 + index * 4);
    *(s16 *)entry2 = arg0;
    *(s16 *)((u8 *)entry2 + 2) = arg1;
}
#endif

#ifdef VERSION_US
extern s32 D_80128120; void func_8004EC5C(void) { if (D_80128120 > 0) { D_80128120--; } }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004EC7C.s")
#endif

#ifdef VERSION_US
extern s32 D_80128120;
extern u8 D_80128128[];
extern void func_8004EC00();
extern void func_8004EC5C(void);
typedef void (*CallbackNode_8004ECD4)();
typedef void (*RenderNode_8004ECD4)();
extern RenderNode_8004ECD4 D_80097200[];
typedef struct Node_8004ECD4 {
    u8 type; u8 pad1; u16 flags; u8 pad4[4]; s16 x; s16 y; u8 padC[8];
    struct Node_8004ECD4 *next; u8 pad18[4]; CallbackNode_8004ECD4 callback;
} Node_8004ECD4;
typedef struct Copy4_8004ECD4 { u8 bytes[4]; } Copy4_8004ECD4;
void func_8004ECD4(void *arg0, s32 arg1, s32 arg2) {
    Node_8004ECD4 *head;
    Node_8004ECD4 *node;
    CallbackNode_8004ECD4 callback;
    Copy4_8004ECD4 pair;
    s16 *coords;
    head = *(Node_8004ECD4 **)((u8 *)arg0 + 0x18);
    node = head;
    coords = (s16 *)pair.bytes;
    if (head != NULL) {
        do {
            func_8004EC00(arg1, arg2);
            if (node->flags & 1) {
                callback = node->callback;
                if (callback != NULL) {
                    callback(1, node);
                }
                pair = *(Copy4_8004ECD4 *)(D_80128128 + D_80128120 * 4);
                coords[0] += node->x;
                coords[1] += node->y;
                D_80097200[node->type](node, coords[0], coords[1]);
            }
            func_8004EC5C();
            node = node->next;
        } while (node != head);
    }
}
#endif

#ifdef VERSION_US
extern void func_8004ECD4(void *, s32, s32);
void func_8004EE04(u8 *arg0, s32 arg1, s32 arg2) {
    arg1 += *(s16 *)(arg0 + 8);
    arg2 += *(s16 *)(arg0 + 10);
    func_8004ECD4(arg0, arg1, arg2);
}
#endif

#ifdef VERSION_US
void func_8004EE30(u8 *arg0, const u8 *arg1) {
    arg0[0] = arg1[0];
    arg0[1] = arg1[1];
    arg0[2] = arg1[2];
}
#endif

#ifdef VERSION_US
void func_8004EE4C(u16 *arg0, u8 *arg1)
{
  u8 r = arg1[0];
  u8 g = arg1[1];
  u8 b = arg1[2];
  g = (g >> 3) & 0x1F;
  b = (b >> 3) & 0x1F;
  r = r >> 3;
  *arg0 = (((r << 11) | (g << 6)) | (b << 1)) | 1;
}
#endif

void func_8004EE94(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004EE9C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004F2D0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004F64C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004FA6C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004FC58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_8004FE00.s")
#endif

#ifdef VERSION_US
extern s32 D_800971F8;
extern void func_8004FC58(u8 *, s32, s32);
extern void func_8004FE00(u8 *, s32, s32);
extern void func_8004ECD4(void *, s32, s32);
void func_800501A0(u8 *arg0, s32 arg1, s32 arg2) {
    if (*(u16 *)(arg0 + 2) & 2) {
        if (*(u8 *)(arg0 + 0x29) == 0) {
            func_8004FC58(arg0, arg1, arg2);
        } else {
            func_8004FE00(arg0, arg1, arg2);
        }
    }
    D_800971F8 = (s32)arg0;
    func_8004ECD4(arg0, arg1, arg2);
    D_800971F8 = 0;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_80050218.s")
#endif

#ifdef VERSION_US
extern s32 D_800971F0;
extern void func_8004EE04(u8 *, s32, s32);
typedef void (*Callback_800503A4)();
void func_800503A4(u8 *arg0) {
    if (arg0 != NULL && (*(u16 *)(arg0 + 2) & 1)) {
        D_80128120 = 0;
        *(s16 *)(D_80128128 + 0) = 0;
        *(s16 *)(D_80128128 + 2) = 0;
        D_800971F0 = (s32)arg0;
        if (*(Callback_800503A4 *)(arg0 + 0x1C) != NULL) {
            (*(Callback_800503A4 *)(arg0 + 0x1C))(1, arg0);
        }
        func_8004EE04(arg0, 0, 0);
        D_800971F0 = 0;
    }
}
#endif

#ifdef VERSION_US
typedef struct TreeNode_80050428 {
    u8 pad0[4];
    s32 id;
    u8 pad8[12];
    struct TreeNode_80050428 *next;
    struct TreeNode_80050428 *children;
} TreeNode_80050428;
void *func_80050428(arg0, arg1)
TreeNode_80050428 *arg0;
s32 arg1;
{
    TreeNode_80050428 *first;
    TreeNode_80050428 *node;
    void *result;
    result = NULL;
    first = arg0->children;
    if (arg1 == arg0->id) {
        result = arg0;
    } else {
        node = first;
        if (first != NULL) {
            do {
                result = func_80050428(node, arg1);
                if (result != NULL) break;
                node = node->next;
            } while (node != first);
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
void func_8005049C(void) {
    func_80050428();
}
#endif

#ifdef VERSION_US
void func_800504BC(s16 *arg0) {
    if (D_800971F0 != 0) {
        arg0[0] = *(s16 *)(D_80128128 + D_80128120 * 4);
        arg0[1] = *(s16 *)(D_80128128 + D_80128120 * 4 + 2);
        return;
    }
    arg0[0] = 0;
    arg0[1] = 0;
}
#endif

#ifdef VERSION_US
u8 func_80050518(u8 arg0) {
    return arg0 & 0xF;
}
#endif

#ifdef VERSION_US
void func_80050528(u8 *arg0) {
    *(s16 *)(arg0 + 0) = 0;
    *(s16 *)(arg0 + 4) = 1;
    *(s32 *)(arg0 + 8) = 0;
}
#endif

#ifdef VERSION_US
void func_8005053C(void *arg0, u8 *arg1) {
    if (arg0 != NULL) {
        func_80050528(arg1);
        (*(u8 **)((u8 *)(arg0) + (0x34))) = arg1;
    }
}
#endif

#ifdef VERSION_US
void func_80050578(u8 *arg0, s32 arg1) { if (arg0 != NULL) { u8 *value = *(u8 **)(arg0 + 0x34); if (value != NULL) { *(s16 *)(value + 0) = -1; *(s16 *)(value + 2) = 0; *(s32 *)(value + 8) = arg1; } } }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_800505A4.s")
#endif

#ifdef VERSION_US
extern s32 func_800505A4(u8 *);
s32 func_80050640(u8 *arg0)
{
  s32 result = -2;
  int new_var;
  if ((*((u16 *) (arg0 + 4))) & 1)
  {
    if ((*((u8 **) (arg0 + 8))) != 0)
    {
      *((s16 *) arg0) = func_800505A4(arg0);
      result = *((s16 *) (((*((u8 **) ((*((u8 **) (arg0 + 8))) + 4))) + ((*((s16 *) (arg0 + 2))) * 4)) + (new_var = 2)));
    }
  }
  return result;
}
#endif

#ifdef VERSION_US
s32 func_800506A4(u8 *arg0) {
    s32 result = 0;
    u8 *value;
    u8 *sub;
    value = *(u8 **)(arg0 + 0x34);
    if (value != NULL) {
        sub = *(u8 **)(value + 8);
        if (sub != NULL) {
            if (*(u16 *)(sub + 2) == *(s16 *)(value + 2) + 1) {
                if (*(s16 *)(*(u8 **)(sub + 4) + (*(s16 *)(value + 2) * 4)) == *(s16 *)value + 1) result = 1;
            }
        }
    }
    return result;
}
#endif

#ifdef VERSION_US
extern s32 D_801281B4;
extern u8 D_815097B0[];
extern u8 D_800CD020[];
extern void *func_80003240();
extern void __osSetFpcCsr();
extern void Sched_InitClientQueue();
extern void func_80005568();
extern void func_80004F34();
typedef void (*CallbackThread_80050700)();
void GbTower_AudioThread(s32 arg0) {
    CallbackThread_80050700 callback = (CallbackThread_80050700)func_80003240(D_815097B0);
    __osSetFpcCsr(0x01000C01);
    Sched_InitClientQueue(D_801281B4, 0, 1);
    func_80005568(D_801281B4);
loop:
    func_80004F34(D_801281B4);
    if (*(s16 *)(D_800CD020 + 0xA38) >= 0x15) {
        goto loop;
    }
    callback(D_801281B4);
    goto loop;
}
#endif

#ifdef VERSION_US
extern s32 D_801281B0;
extern u8 D_81509440[];
extern u8 D_81509674[];
typedef void (*CallbackThread_800507B8)();
void GbTower_EmuThread(s32 arg0) {
    CallbackThread_800507B8 callback1 = (CallbackThread_800507B8)func_80003240(D_81509440);
    CallbackThread_800507B8 callback2 = (CallbackThread_800507B8)func_80003240(D_81509674);
    __osSetFpcCsr(0x01000C01);
    Sched_InitClientQueue(D_801281B0, 0, 1);
    func_80005568(D_801281B0);
    callback1(D_801281B0);
    osStartThread((OSThread *)D_801281B4);
loop:
    func_80004F34(D_801281B0);
    if (*(s16 *)(D_800CD020 + 0xA38) >= 0x15) {
        goto loop;
    }
    callback2(D_801281B0);
    goto loop;
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_80050878.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/4F800/func_80050994.s")
#endif

#ifdef VERSION_US

void *GbTower_RecvExitMesg(void) {
    void *sp1C;

    osRecvMesg(D_801281B0 + 0x21E4, &sp1C, 1);
    return sp1C;
}
#endif

#ifdef VERSION_US
extern u8 D_801281B8;
extern u8 GbTower_SetPollMask(u8);
extern void Display_ApplyPendingVideoMode(void);
extern void func_800055B0();
extern void main_pool_pop_state();
typedef struct Copy8_80050B40 { u8 bytes[8]; } Copy8_80050B40;
void func_80050B40(void *arg0) {
    *(Copy8_80050B40 *)arg0 = *(Copy8_80050B40 *)((u8 *)D_801281B0 + 0x2208);
    GbTower_SetPollMask(D_801281B8);
    osViBlack(1);
    Display_ApplyPendingVideoMode();
    func_800055B0(D_801281B0);
    func_800055B0(D_801281B4);
    osDestroyThread((OSThread *)D_801281B0);
    osDestroyThread((OSThread *)D_801281B4);
    main_pool_pop_state(0x4742454D);
}
#endif
