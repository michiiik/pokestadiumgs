#include "global.h"


#ifdef VERSION_US
void func_8004E250(void *arg0, void *arg1) {
    void *temp_v0;
    void *temp_v1;

    if ((arg0 != NULL) && (arg1 != NULL)) {
        temp_v0 = (*(void **)((u8 *)(arg0) + (0x18)));
        if (temp_v0 == NULL) {
            (*(void **)((u8 *)(arg0) + (0x18))) = arg1;
            (*(void **)((u8 *)(arg1) + (0x10))) = arg1;
            (*(void **)((u8 *)(arg1) + (0x14))) = arg1;
            return;
        }
        temp_v1 = (*(void **)((u8 *)(temp_v0) + (0x10)));
        (*(void **)((u8 *)(arg1) + (0x14))) = temp_v0;
        (*(void **)((u8 *)(arg1) + (0x10))) = temp_v1;
        (*(void **)((u8 *)(temp_v0) + (0x10))) = arg1;
        (*(void **)((u8 *)(temp_v1) + (0x14))) = arg1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E298.s")

typedef struct TargetGraphNode TargetGraphNode;
typedef s32 (*TargetGraphCallback)(s32, struct TargetGraphNode*);
struct TargetGraphNode {
    u8 pad_00[0x1C];
    TargetGraphCallback unk_1C;
    void* unk_20;
};
void func_8004E308(TargetGraphNode* arg0, TargetGraphCallback arg1, void* arg2) {
    if (arg1 != NULL) {
        arg1 = func_80003240(arg1);
    }

    if (arg0 != NULL) {
        arg0->unk_20 = arg2;
        arg0->unk_1C = arg1;
        if (arg1 != NULL) {
            arg1(0, arg0);
        }
    }
}

extern s32 MainPool_AllocAligned(s32, s32, s32);
void func_8004E298(s32, s32, s32, s16, s16, s16, s16);
s32 func_8004E368(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        arg1 = MainPool_AllocAligned(arg0, 0x24, 4);
    }
    if (arg1 != 0) {
        func_8004E298(arg1, 1, 0x524F4F54, 0, 0, 0, 0);
    }
    return arg1;
}

s32 func_8004E3C8(arg0, arg1, arg2, arg3, arg4, arg5, arg6)
s32 arg0;
s32 arg1;
s32 arg2;
s16 arg3;
s16 arg4;
s16 arg5;
s16 arg6;
{
    if (arg0 != 0) {
        arg1 = MainPool_AllocAligned(arg0, 0x24, 4);
    }
    if (arg1 != 0) {
        func_8004E298(arg1, 0, arg2, arg3, arg4, arg5, arg6);
    }
    return arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E438.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E52C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E610.s")

extern s32 D_80128094;
extern s32 D_8012809C;
extern s32 D_801280A0[];
void func_8004E748(s32 arg0) {
    s32 index;
    s32 *entry;
    if (arg0 != 0) {
        index = D_8012809C;
        entry = &D_801280A0[index];
        entry[0] = arg0;
        if (index == 0) {
            if (D_80128094 == 0) {
                D_80128094 = arg0;
            }
        } else {
            func_8004E250((void *)(u32)entry[-1], (void *)(u32)arg0);
        }
    }
}

extern s32 D_80128098; void func_8004E7AC(void) { D_80128098 = 0; }

extern s32 D_8012809C;
extern s32 D_801280A0[];
void func_8004E7B8(void) {
    s32 i = D_8012809C;
    s32 *table = D_801280A0;
    table[i + 1] = table[i];
    D_8012809C = i + 1;
    D_80128098 += 4;
}

extern s32 D_80128098;
extern s32 D_8012809C;
void func_8004E7FC(void) {
    D_8012809C -= 1;
    D_80128098 += 4;
}

s32 func_8004E368(s32, s32);
extern void func_8004E748(s32);
extern s32 D_80128090;

void func_8004E828(void) {
    func_8004E748(func_8004E368(D_80128090, 0));
    D_80128098 += 0x10;
}

s32 func_8004E3C8();
void func_8004E868(void) {
    struct Command {
        u8 pad_00[4];
        s32 value;
        s16 arg3;
        s16 arg4;
        u16 arg5;
        u16 arg6;
    } *cmd;
    cmd = (struct Command *)(u32)D_80128098;
    func_8004E748(func_8004E3C8(D_80128090, 0, cmd->value, cmd->arg3, cmd->arg4, cmd->arg5, cmd->arg6));
    D_80128098 += 0x10;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E8D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E9C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004EA60.s")

s32 func_8004EB1C(s32 value) { s32 result = value; if (value > 0) result = 1 << (value + 31); return result; }

u16 func_8004EB38(u16 *arg0) { return *arg0; }

extern u8 D_80097154[];
s32 func_8004EB40(u16 *arg0) { u16 index = *arg0; return *(s32 *)(D_80097154 + (index * 8)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004EB58.s")
#endif
