#include "global.h"


#ifdef VERSION_US
typedef u8 *(*Func87C01730Callback)(s32, s32);
u8 *func_87C01730(void **arg0) {
    u8 *entry = *(u8 **)((u8 *)*arg0 + 0xC);
    if (entry != NULL) {
        Func87C01730Callback callback = *(Func87C01730Callback *)(entry + 0x2C);
        if (callback != NULL) {
            return callback(0, 0);
        }
    }
    return NULL;
}

s32 func_87C0177C(s16 *arg0) {
    s32 count;
    s16 *entry;
    s32 valid;

    if (arg0 == NULL) {
        return 0;
    }
    count = 1;
    valid = *arg0 >= 0;
    entry = arg0 + 1;
    while (valid) {
        valid = *entry >= 0;
        count++;
        entry++;
    }
    return count - 1;
}

u8 *func_87C017D0(void **arg0, s32 arg1) {
    u8 *state = func_87C01730(arg0);

    if (arg1 < 0 || state == NULL || arg1 >= state[4]) {
        return NULL;
    }
    return (*(u8 ***)(state + 0xC))[arg1];
}

u8 *func_87C0182C(void **arg0, s32 arg1) {
    u8 *state = func_87C01730(arg0);

    if (arg1 < 0 || state == NULL || arg1 >= state[5]) {
        return NULL;
    }
    return (*(u8 ***)(state + 0x10))[arg1];
}

void func_87C01888(void *arg0, s32 arg1, s32 arg2) {
    (*(s32 *)((u8 *)(arg0) + (0))) = arg1;
    (*(s32 *)((u8 *)(arg0) + (4))) = 0;
    (*(s16 *)((u8 *)(arg0) + (0x14))) = -1;
    (*(s16 *)((u8 *)(arg0) + (0x16))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x18))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x1C))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x20))) = 0;
    (*(s32 *)((u8 *)(arg0) + (0x24))) = arg2;
    (*(f32 *)((u8 *)(arg0) + (8))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (0x10))) = 0.0f;
    (*(f32 *)((u8 *)(arg0) + (0xC))) = 1.0f;
}

s32 func_80001FF0();
s32 func_80008970();

f32 func_87C018C8(void) {
    s32 sp1C;

    sp1C = func_80008970();
    return ((f32) sp1C * 60.0f) / (f32) func_80001FF0();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C01910.s")

extern void func_87C01910(void *);
void func_87C019B0(u8 *arg0, s16 arg1) {
    *(s16 *)(arg0 + 0x14) = arg1;
    func_87C01910(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C019DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C01A90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/48/fragment48_257730/func_87C01CBC.s")

extern void func_87C019B0(u8 *arg0, s16 arg1);
void func_87C01DB8(u8 *arg0, s32 arg1, s32 arg2) {
    s32 original;

    original = arg1;
    if ((arg2 != 0) || (arg1 != *(s16 *)(arg0 + 0x14))) {
        *(f32 *)(arg0 + 8) = 0.0f;
    }
    func_87C019B0(arg0, (s16)arg1);
    *(s32 *)(arg0 + 4) = 0;
    if (original < 0) {
        *(s32 *)(arg0 + 0x1C) = 1;
    } else {
        *(s32 *)(arg0 + 0x1C) = 0;
    }
    *(s32 *)(arg0 + 0x18) = 0;
}

s16 func_87C01E28(u8 *arg0) {
    return *(s16 *)(arg0 + 0x14);
}

void func_87C01E30(void *arg0, void *arg1, s32 arg2) {
    s16 *entry = arg1;

    if ((arg2 == 0) && (arg1 == *(void **)((u8 *)arg0 + 4))) {
        return;
    }
    *(void **)((u8 *)arg0 + 4) = entry;
    if (entry != NULL) {
        *(s16 *)((u8 *)arg0 + 0x16) = 0;
        func_87C019B0(arg0, entry[*(s16 *)((u8 *)arg0 + 0x16)]);
        *(f32 *)((u8 *)arg0 + 8) = 0.0f;
    } else {
        func_87C019B0(arg0, -1);
    }
}

s32 func_87C01FE0(void **arg0, s32 arg1);
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

void func_87C01E98(u8 *arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    f32 temp_fv1;
    s16 *temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_a1 = M2C_FIELD(arg0, s16 **, 4);
    if (temp_a1 != NULL) {
        temp_v0 = func_87C0177C(temp_a1);
        M2C_FIELD(arg0, s16 *, 0x16) = (s16) (s32) ((f32) temp_v0 * arg1);
        if (M2C_FIELD(arg0, s16 *, 0x16) >= temp_v0) {
            M2C_FIELD(arg0, s16 *, 0x16) = (s16) (temp_v0 - 1);
        }
        func_87C019B0(arg0, M2C_FIELD(arg0, s16 **, 4)[M2C_FIELD(arg0, s16 *, 0x16)]);
        temp_v0_2 = func_87C01FE0((u8 **) arg0, (s32) M2C_FIELD(arg0, s16 *, 0x14));
        temp_fv0 = (f32) temp_v0_2;
        temp_fv1 = temp_fv0 * arg2;
        M2C_FIELD(arg0, f32 *, 8) = temp_fv1;
        if (temp_fv0 <= temp_fv1) {
            M2C_FIELD(arg0, f32 *, 8) = (f32) (temp_v0_2 - 1);
        }
    }
}
void func_87C01F6C(u8 *arg0, f32 arg1) {
    *(f32 *)(arg0 + 0xC) = arg1;
}

f32 func_87C01F78(u8 *arg0) {
    return *(f32 *)(arg0 + 0xC);
}

extern u8 *func_87C01730(void **);
s32 func_87C01F80(void **arg0) {
    u8 *state = func_87C01730(arg0);
    s32 result;
    if (state != NULL) {
        result = state[4];
    } else {
        result = 0;
    }
    return result;
}

s32 func_87C01FB0(void **arg0) {
    u8 *state = func_87C01730(arg0);
    s32 result;
    if (state != NULL) {
        result = state[5];
    } else {
        result = 0;
    }
    return result;
}

extern u8 *func_87C017D0(void **, s32);
s32 func_87C01FE0(void **arg0, s32 arg1) {
    u8 *state = func_87C017D0(arg0, arg1);
    s32 result;
    if (state != NULL) {
        result = *(u16 *)(state + 0xA);
    } else {
        result = 0;
    }
    return result;
}

extern u8 *func_87C0182C(void **, s32);
s32 func_87C02010(void **arg0, s32 arg1) {
    u8 *state = func_87C0182C(arg0, arg1);
    s32 result;
    if (state != NULL) {
        result = *(u16 *)(state + 0xA);
    } else {
        result = 0;
    }
    return result;
}

s32 func_87C02040(void **arg0, s32 arg1) {
    u8 *state = func_87C017D0(arg0, arg1);
    return state ? ((*(s16 *)state) & 1) : 0;
}
#endif
