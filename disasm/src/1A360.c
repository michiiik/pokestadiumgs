#include "global.h"


#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_80019760.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_80019C08.s")

typedef struct Copy32_1A360 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
} Copy32_1A360;
extern Copy32_1A360 D_8008F1E4;
extern void func_8001BE1C(void *, s32, s32);
void func_80019CC0(void *arg0) {
    void *obj = *(void **)((u8 *)arg0 + 0x44);
    if (*(u8 *)((u8 *)obj + 0x28) == 0) {
        func_8001BE1C((u8 *)arg0 + 0x60,
            *(s32 *)((u8 *)(*(void **)((u8 *)obj + 0x60)) + 0x8C),
            (s32)((u8 *)arg0 + 0x36));
    } else {
        func_8001BE1C((u8 *)arg0 + 0x60,
            *(s32 *)((u8 *)obj + 0x2C),
            (s32)((u8 *)arg0 + 0x36));
    }
    *(u8 *)((u8 *)arg0 + 0x34) = 0;
    *(u8 *)((u8 *)arg0 + 0x60) =
        (*(u8 *)((u8 *)arg0 + 0x60) & 0xFFF0) | 1;
    *(Copy32_1A360 *)((u8 *)arg0 + 0xD0) = D_8008F1E4;
}

void func_80019D80(u8 *arg0) {
    if (((u32)(*(s32 *)(arg0 + 0xD0) << 1) >> 31) == 1) {
        *(volatile u8 *)(arg0 + 0xD0) &= 0xFFBF;
    }
    arg0[0x30] = 0;
    *(volatile u8 *)(arg0 + 0xD0) &= 0xFF7F;
    arg0[0x34] = 0;
    *(volatile u8 *)(arg0 + 0xD0) &= 0xFFDF;
    *(s32 *)(arg0 + 0x44) = -1;
    *(s32 *)(arg0 + 0x40) = -1;
    arg0[0x60] &= 0xFFF0;
    *(f32 *)(arg0 + 0x70) = 0.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_80019DE4.s")

void *func_8001A2CC(void *arg0, s32 arg1) {
    u8 *p = (u8 *)arg0;
    void *result;

    if (arg1 < p[1]) {
        result = p + 8;
    } else if (p[2] >= arg1) {
        result = p + 0x10;
    } else {
        result = p + 0x18;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A3DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A4C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A5B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001A6F8.s")

extern void func_8001A6F8(void *arg0, s32 arg1);
void func_8001A994(void *arg0) {
    func_8001A6F8(arg0, 6);
}

void func_8001A9B4(void *arg0) {
    func_8001A6F8(arg0, 7);
}

void func_8001A9D4(u32 *arg0) {
    arg0[0] = (u32)arg0;
    arg0[1] = (u32)arg0;
    arg0[2] = 0;
}

void func_8001A9E4(void *arg0) {
    func_8001A9D4(arg0);
    func_8001A9D4((u8 *)arg0 + 0x10);
    func_8001A9D4((u8 *)arg0 + 0x20);
    func_8001A9D4((u8 *)arg0 + 0x30);
    *(u32 *)((u8 *)arg0 + 0x0C) = (u32)arg0;
    *(u32 *)((u8 *)arg0 + 0x1C) = (u32)arg0;
    *(u32 *)((u8 *)arg0 + 0x2C) = (u32)arg0;
    *(u32 *)((u8 *)arg0 + 0x3C) = (u32)arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001AA34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001AAD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001AC38.s")

void func_8001AD74(s32 *arg0, s32 *arg1) {
    if ((*(s32 **)((u8 *)(arg1) + (0))) == NULL) {
        (*(s32 **)((u8 *)(arg1) + (0))) = arg0;
        (*(s32 **)((u8 *)(arg1) + (4))) = (s32 *) (*(s32 **)((u8 *)(arg0) + (4)));
        *(*(s32 ***)((u8 *)(arg0) + (4))) = arg1;
        (*(s32 **)((u8 *)(arg0) + (4))) = arg1;
        (*(s32 *)((u8 *)(arg0) + (8))) = (s32) ((*(s32 *)((u8 *)(arg0) + (8))) + 1);
        (*(s32 *)((u8 *)(arg1) + (0xC))) = (s32) (*(s32 *)((u8 *)(arg0) + (0xC)));
    }
}

void func_8001ADB4(void *arg0) {
    void *temp_v0;

    temp_v0 = (*(void **)((u8 *)(arg0) + (0)));
    if (temp_v0 != NULL) {
        (*(void ***)((u8 *)(temp_v0) + (4))) = (void **) (*(void ***)((u8 *)(arg0) + (4)));
        *(*(void ***)((u8 *)(arg0) + (4))) = (*(void **)((u8 *)(arg0) + (0)));
        (*(void **)((u8 *)(arg0) + (0))) = NULL;
    }
}

typedef struct ListNode1A360 {
    void *unk0;
    struct ListNode1A360 *next;
    u8 *data;
} ListNode1A360;
void *func_8001ADE0(ListNode1A360 *arg0, s32 arg1) {
    ListNode1A360 *cur;
    ListNode1A360 *best;
    u8 *result;
    cur = arg0->next;
    if (cur == arg0) {
        return NULL;
    }
    best = cur;
    while (cur != arg0) {
        if (best->data[0x30] >= cur->data[0x30]) {
            best = cur;
        }
        cur = cur->next;
    }
    if (best == NULL) {
        return NULL;
    }
    result = best->data;
    if (result[0x30] >= arg1) {
        return NULL;
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001AE60.s")

void func_8001AFAC(void *arg0, s32 arg1) {
    func_8001A9B4((*(void **)((u8 *)(arg0) + (0x44))));
    (*(s32 *)((u8 *)(arg0) + (0x48))) = arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001AFE0.s")

s32 func_8001B00C(s32 *arg0, s32 arg1) {
    s32 v = func_8001CB5C(arg0);
    if (v) {
        func_8001AE60(v, arg1);
        func_8001AD74((u8 *)arg0 + 0x30, v);
    }
    return v;
}

extern void func_8001AFE0(void *, void *);
extern void func_8001CB1C(void *, void *);
void *func_8001B058(void *arg0, void *arg1) {
    void *result = func_8001ADE0((ListNode1A360 *)((u8 *)arg0 + 0x10),
        *(u8 *)((u8 *)(*(void **)((u8 *)arg1 + 0x60)) + 5));
    if (result != NULL) {
        func_8001AFE0(result, arg1);
        func_8001CB1C((u8 *)arg0 + 0x20, result);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001B0B0.s")

void *func_8001B1A8(void *arg0, void *arg1) {
    void *result = func_8001ADE0((ListNode1A360 *)((u8 *)arg0 + 0x30),
        *(u8 *)((u8 *)(*(void **)((u8 *)arg1 + 0x60)) + 5));
    if (result != NULL) {
        func_8001AFAC(result, (s32)arg1);
        func_8001CB1C((u8 *)arg0 + 0x20, result);
        *(u8 *)((u8 *)result + 0x30) =
            *(u8 *)((u8 *)(*(void **)((u8 *)arg1 + 0x60)) + 5);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001B218.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/1A360/func_8001B59C.s")
#endif
