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

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E368.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E3C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E438.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E52C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E610.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E748.s")

extern s32 D_80128098; void func_8004E7AC(void) { D_80128098 = 0; }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E7B8.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E868.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E8D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004E9C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004EA60.s")

s32 func_8004EB1C(s32 value) { s32 result = value; if (value > 0) result = 1 << (value + 31); return result; }

u16 func_8004EB38(u16 *arg0) { return *arg0; }

extern u8 D_80097154[];
s32 func_8004EB40(u16 *arg0) { u16 index = *arg0; return *(s32 *)(D_80097154 + (index * 8)); }

#pragma GLOBAL_ASM("asm/us/nonmatchings/4EE50/func_8004EB58.s")
#endif
