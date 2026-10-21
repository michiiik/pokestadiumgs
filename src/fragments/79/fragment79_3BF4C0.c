#include "global.h"


#ifdef VERSION_US
typedef struct {
    u8 flags;
    u8 unk_01[7];
    u8 selected[2];
    u8 unk_0A[42];
    u32 score[2];
} BattlePlanScoreHeader;

typedef struct {
    u8 unk_00[13];
    u8 stages[7];
} BattlePlanStageRecord;

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_8414FC30.s")

extern void func_8414A180(u8 *, u8, u8);
extern void func_8414A144(u8 *);
extern u8 * func_84154B64(u8);
void BattlePlan_UpdateMoveAccuracy(u8 *plan, u8 side) {
    u8 move;
    u8 *entry;
    u8 context[12];
    entry = (u8 *)((u32)plan + (u32)side);
    move = entry[6];
    func_84154B64(side);
    if (move != 0) {
        func_8414A180(context, side, move);
        func_8414A144(context);
        entry[10] = context[2];
    }
}

extern void func_8414D198(void *, u8);
void BattlePlan_ApplyPursuitMultiplier(u8 *state, u8 side) {
    u8 *entry;
    if (*(u8 *)((u32)state + (u32)side + 6) == 228) {
        func_8414D198(state, side);
        entry = (u8 *)((u32)state + ((u32)side << 1));
        entry += 4;
        *(u16 *)(entry + 10) *= 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84150330.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841503B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84150538.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841506D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84150878.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841509E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84150B14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84150EA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151128.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84151270.s")

extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 * func_84154B30(u8);
void func_8415132C(void *arg0, u8 arg1) {
    s32 base;
    u8 *sub;
    u8 *state;
    s32 mult;
    u8 var;
    void *table;

    base = (s32)(u32)arg0 + 4;
    state = func_84154B30((1 - (u32)arg1) & 0xFF);
    sub = state + 8;
    if (state[2] >= 2) {
        var = 0;
        table = func_8414A3A0(arg1);
        mult = *(u8 *)((u8 *)table + 0x3F) * func_8414A2AC();
        if (sub[0xD] >= 9) {
            var = (sub[0xD] - 7) >> 1;
        }
        if (sub[0x10] >= 9) {
            var += (sub[0x10] - 7) >> 1;
        }
        *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF;
        *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += var * mult;
        *(u8 *)(u32)base |= 2;
    }
}

extern u8 func_80062D98(u8);
extern s32 func_84155544(u8 *, u8);
s32 func_84151420(u8 *arg0, u8 arg1) {
    u8 value;
    u8 result;
    value = *(u8 *)((s32)(u32)arg0 + arg1 + 4);
    if (value == 0) return 0;
    result = func_80062D98(value);
    if (result == 0x13) return 0;
    if (func_84155544(arg0, result) != 0) return 0;
    return 1;
}

extern s32 func_84151420(u8 *, u8);

s32 func_84151498(u8 *arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (func_84151420(arg0, i) != 0) {
            return 1;
        }
    }
    return 0;
}

extern u8 func_80063454(u8, u8, u8, s32);
u8 BattlePlan_CountResistingMoveSlots(u8 side, u8 target_type) {
    u8 count;
    u8 *record;
    s32 i;
    u8 move_type;
    count = 0;
    record = func_84154B64(side);
    for (i = 0; i < 4; i++) {
        if (func_84151420(record, i) != 0) {
            move_type = func_80062D98(*(u8 *)((u32)record + (u32)i + 4));
            if (func_80063454(target_type, move_type, move_type, 0) < 10) {
                count++;
            }
        }
    }
    return count;
}

extern u8 func_84148C74(u8);
void BattlePlan_AddConversionBonus(u8 *plan, u8 side) {
    u8 other_side;
    u8 move;
    s32 base;
    u8 *table;
    u8 incoming_type;
    u8 count;
    u8 amount;
    base = (s32)(u32)plan + 4;
    other_side = 1 - side;
    move = *(u8 *)((u32)plan + (u32)other_side + 6);
    if (move == 0) {
        move = func_84148C74(other_side);
    }
    if (func_84151498(func_84154B64(side)) != 0) {
        *(u8 *)((u32)base + (u32)side + 8) = 0xFF;
        amount = func_8414A2AC();
        table = func_8414A3A0(side);
        incoming_type = func_80062D98(move);
        count = BattlePlan_CountResistingMoveSlots(side, incoming_type);
        ((u32 *)(u32)base)[(u32)side + 13] += count * table[48] * amount;
        *(u8 *)(u32)base |= 2;
    }
}

extern s32 func_8414C858(u8 *);
extern u8 func_8414A288(void);
void BattlePlan_AddFlinchBonus(u8 *plan, u8 side, u8 chance) {
    u8 *other;
    BattlePlanScoreHeader *base;
    u8 *table;
    u8 amount;
    base = (void *)(plan + 4);
    other = func_84154B64((1 - (u32)side) & 0xFF);
    if (((other[24] & 0x10) == 0) && ((*(u16 *)(other + 38) & 0x27) == 0)) {
        if (func_8414C858(plan) != 0) {
            base->selected[side] = chance;
            amount = func_8414A288();
            table = func_8414A3A0(side);
            base->score[side] += table[17] * amount * chance / 255;
            base->flags |= 2;
        }
    }
}

extern s32 func_8414A2DC(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_8415178C(void *arg0, u8 arg1, u8 arg2) {
    void *state;
    s32 base;
    u8 pad;
    void *table;
    s32 amount;
    state=func_84154B64((s32)arg1);
    if (*(u16 *)((u8 *)state+0x2A)!=*(u16 *)((u8 *)state+0x28)) {
        base=(s32)(u32)arg0+4;
        table=func_8414A3A0(arg1);
        amount=*(u8 *)((u8 *)table+0x3D) * func_8414A2DC();
        *(u8 *)((u8 *)(u32)base+(u32)arg1+8)=0xFF;
        if (*(u8 *)((u8 *)arg0+1)&2) amount>>=2;
        *(s32 *)((u8 *)(u32)base+((u32)arg1<<2)+0x34)+=amount;
        *(u8 *)(u32)base|=2;
    }
}

extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 * func_84154B30(u8);
void func_84151838(void *arg0, u8 arg1) { s32 base; void *table; u32 *entry; u8 amount; base = (s32)(u32)arg0 + 4; if ((func_84154B30(arg1)[3] & 8) == 0) { *(u8 *)((u8 *)(u32)base + arg1 + 8) = 0xFF; amount = func_8414A2AC(); table = func_8414A3A0(arg1); entry = (u32 *)((u8 *)(u32)base + (arg1 << 2) + 0x34); *entry += *(u8 *)((u8 *)table + 0x25) * amount; *(u8 *)(u32)base |= 2; } }

extern void func_841506D0(void *, u8, u8, u8);
extern void func_84150878(void *, u8, u8, u8);
extern void func_841509E0(void *, u8, u8, u8);

void func_841518D0(void *arg0, u8 arg1, u8 arg2) {
    u8 local = arg2 / 3;

    func_841506D0(arg0, arg1, 0xA1, local);
    func_84150878(arg0, arg1, 0xA1, local);
    func_841509E0(arg0, arg1, 0xA1, local);
}

extern s32 func_841493F4(void);
extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_84151940(void *arg0, u8 arg1) {
    u8 *state;
    s32 base;
    s32 amount;
    void *table;
    state = func_84154B64((1 - (u32)arg1) & 0xFF);
    if (state[0x23] > 0) return;
    if (state[0x18] & 0x10) return;
    table = func_8414A3A0(arg1);
    base = (s32)(u32)arg0 + 4;
    amount = *(u8 *)((u8 *)table + 0x2D) * func_8414A2AC();
    *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += amount;
    *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += (amount * func_841493F4()) / 128;
    if ((state[0x15] & 0x10) && state[0x1F] >= 2) *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += amount;
    *(u8 *)((u8 *)(u32)base + arg1 + 8) = 0xFF;
    *(u8 *)(u32)base |= 2;
}

extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_84151A5C(void *arg0, u8 arg1) {
    s32 base;
    void *state;
    void *table;
    u8 amount;
    base = (s32)(u32)arg0 + 4;
    state = func_84154B64(arg1);
    if (0 == (*(u8 *)((u8 *)state + 0x18) & 2)) {
        *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF;
        amount = func_8414A2AC();
        table = func_8414A3A0(arg1);
        *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += *(u8 *)((u8 *)table + 0x26) * amount;
        *(u8 *)(u32)base |= 2;
    }
}

extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_84151AF4(void *arg0, u8 arg1) {
    s32 base;
    void *state;
    void *table;
    u8 amount;
    base = (s32)(u32)arg0 + 4;
    state = func_84154B64(arg1);
    if (0 == (*(u8 *)((u8 *)state + 0x18) & 4)) {
        *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF;
        amount = func_8414A2AC();
        table = func_8414A3A0(arg1);
        *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += *(u8 *)((u8 *)table + 0x27) * amount;
        *(u8 *)(u32)base |= 2;
    }
}

extern s32 func_80063660(u8);
extern u8 func_8414A2A0(void);
extern void * func_8414A3A0(u8);
extern u8 * func_84154B30(u8);
extern u8 *func_84154B64(u8);
extern s32 func_841556C4(u8 *, u8);
void func_84151B8C(s32 arg0, u8 arg1, u8 arg2) {
    u8 *state;
    u8 *sub;
    u8 *other;
    s32 base;
    s32 amount;
    void *table;
    s32 unused;

    state = func_84154B30((1 - (u32)arg1) & 0xFF);
    sub = state + 8;
    other = func_84154B64(arg1);
    if (func_80063660(sub[1]) == 0x19) return;
    if (sub[0x17] & 0x80) return;
    if (sub[0x18] & 0x10) return;
    base = arg0 + 4;
    if (state[3] & 4) return;
    *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = arg2;
    table = func_8414A3A0(arg1);
    amount = (*(u8 *)((u8 *)table + 0x12) * func_8414A2A0() * arg2) / 255;
    *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += amount;
    if (func_841556C4(other, 0x6F)) {
        *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += amount;
    }
    *(u8 *)(u32)base |= 2;
}

extern u8 *func_84154B64(u8);
void func_84151CD8(void *arg0, u8 arg1) { s32 base; base = (s32)(u32)arg0 + 4; if ((*(u8 *)((u8 *)func_84154B64((1 - arg1) & 0xFF) + 0x19) & 8) == 0) { *(u8 *)((u8 *)(u32)base + arg1 + 8) = 0xFF; *(u8 *)((u8 *)(u32)base) |= 2; } }

extern u8 func_8414A2AC(void);
extern void *func_8414A3A0(u8);
extern u8 * func_84154B30(u8);
void func_84151D3C(void *arg0, u8 arg1) { void *state; void *table; s32 base; u8 value; state = func_84154B30(arg1); base = (s32)(u32)arg0 + 4; if ((*(u8 *)((u8 *)state + 3) & 0x10) == 0) { *(u8 *)((u8 *)(u32)base + arg1 + 8) = 0xFF; value = func_8414A2AC(); table = func_8414A3A0(arg1); *(u32 *)((u8 *)(u32)base + (arg1 << 2) + 0x34) += (*(u8 *)((u8 *)table + 0x28)) * value; *(u8 *)((u8 *)(u32)base) |= 2; } }

extern u8 *func_84154B64(u8);
void func_84151DD4(void *arg0, u8 arg1) { void *state; s32 base; state = func_84154B64(arg1); base = (s32)(u32)arg0 + 4; if (((*(u8 *)((u8 *)state + 0x18) & 0x10) == 0) && (((s32)*(u16 *)((u8 *)state + 0x2A) >> 2) < (s32)*(u16 *)((u8 *)state + 0x28))) { *(u8 *)((u8 *)(u32)base + arg1 + 8) = 0xFF; *(u8 *)((u8 *)(u32)base) |= 2; } }

void BattlePlan_AddMimicBonus(u8 *plan, u8 side) {
    u8 *own;
    u8 *other;
    u8 move;
    s32 i;
    u8 *table;
    s32 base;
    u8 amount;
    base = (s32)(u32)plan + 4;
    own = func_84154B64(side);
    other = func_84154B64((1 - (u32)side) & 0xFF);
    move = other[36];
    if ((move != 0) && (move != 165)) {
        for (i = 0; i < 4; i++) {
            if (own[i + 4] == move) {
                return;
            }
        }
        *(u8 *)((u32)base + (u32)side + 8) = 0xFF;
        amount = func_8414A2AC();
        table = func_8414A3A0(side);
        ((u32 *)(u32)base)[(u32)side + 13] += table[62] * amount;
        *(u8 *)(u32)base |= 2;
    }
}

extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
void func_84151F20(void *arg0, u8 arg1) {
    void *table;
    u32 *entry;
    u8 amount;
    s32 base;
    base = (s32)(u32)arg0 + 4;
    *(u8 *)((u8 *)(u32)base + arg1 + 8) = 0xFF;
    amount = func_8414A2AC();
    table = func_8414A3A0(arg1);
    entry = (u32 *)((u8 *)(u32)base + (arg1 << 2) + 0x34);
    *entry += *(u8 *)((u8 *)table + 0x2F) * amount;
    *(u8 *)(u32)base |= 2;
}

void BattlePlan_AddLeechSeedBonus(u8 *plan, u8 side) {
    u8 *own;
    u8 *other;
    s32 base;
    u32 amount;
    u8 *table;
    own = func_84154B64(side);
    other = func_84154B64((1 - (u32)side) & 0xFF);
    base = (s32)(u32)plan + 4;
    if ((other[24] & 0x90) == 0 && func_84155544(other, 22) == 0) {
        *(u8 *)((u32)base + (u32)side + 8) = 0xFF;
        table = func_8414A3A0(side);
        amount = table[19] * func_8414A2A0();
        ((u32 *)(u32)base)[(u32)side + 13] += amount;
        if (func_841556C4(own, 111) != 0) {
            ((u32 *)(u32)base)[(u32)side + 13] += amount;
        }
        *(u8 *)(u32)base |= 2;
    }
}

extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_84152088(void *arg0, u8 arg1) {
    s32 base;
    u8 *state;
    u8 flag;

    base = (s32)(u32)arg0 + 4;
    state = func_84154B64((1 - (u32)arg1) & 0xFF);
    flag = state[0x24];
    if (flag == 0) {
        return;
    }
    if (flag == 0xA5) {
        return;
    }
    if (state[0x1D] > 0) {
        return;
    }
    *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF;
    *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += *(u8 *)((u8 *)func_8414A3A0(arg1) + 0x29) * func_8414A2AC();
    *(u8 *)(u32)base |= 2;
}

extern u8 func_8414A2A0(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_84152140(void *arg0, u8 arg1) {
    s32 sp18;
    s32 base;
    u8 value;
    void *table;
    u8 sp1F;

    table = func_84154B64((1 - (u32)arg1) & 0xFF);
    value = *(u8 *)((u8 *)table + 0x25);
    if ((value != 0) && (value != 0xA5) && (value != 0xE3) && (value != 0x77)) {
        base = (s32)(u32)arg0 + 4;
        if (!(*(u8 *)((u8 *)table + 0x19) & 0x10)) {
            *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF;
            sp18 = base;
            sp1F = func_8414A2A0();
            table = func_8414A3A0(arg1);
            *(u32 *)((u8 *)(u32)sp18 + ((u32)arg1 << 2) + 0x34) += *(u8 *)((u8 *)table + 0x14) * sp1F;
            *(u8 *)(u32)sp18 |= 2;
        }
    }
}

extern u8 func_80063454(u8, u8, u8, s32);
extern u8 func_80062D98(u8);
extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
extern s32 func_84155544(u8 *, u8);
void func_8415220C(void *arg0, u8 arg1) {
    void *ptr1;
    s32 index;
    s32 base;
    u8 val1;
    u8 val2;
    s32 mult;
    void *ptr2;

    base = (s32)(u32)arg0 + 4;
    index = arg1;
    ptr1 = func_84154B64(index);
    ptr2 = func_84154B64((1 - index) & 0xFF);
    val1 = *(u8 *)((u8 *)ptr2 + 0x24);
    if (val1 != 0) {
        val2 = func_80062D98(val1);
        if ((val2 != 0x13) && (func_84155544(ptr1, val2) == 0)) {
            *(u8 *)((u8 *)(u32)base + index + 8) = 0xFF;
            ptr2 = func_8414A3A0(index);
            mult = *(u8 *)((u8 *)ptr2 + 0x31) * func_8414A2AC();
            if (func_80063454(val2, *(u8 *)((u8 *)ptr1 + 2), *(u8 *)((u8 *)ptr1 + 3), 0) >= 0xB) {
                *(u32 *)((u8 *)(u32)base + (index << 2) + 0x34) += mult;
            }
            *(u8 *)(u32)base |= 2;
        }
    }
}

extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_84152308(void *arg0, u8 arg1) {
    void *state;
    s32 base;
    s32 amount;
    void *table;
    
    state = func_84154B64((1 - (u32)arg1) & 0xFF);
    if (*(u8 *)((u8 *)state + 0x18) & 0x10) return;
    base = (s32)(u32)arg0 + 4;
    if (*(u8 *)((u8 *)state + 0x19) & 0x20) return;
    
    *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF;
    table = func_8414A3A0(arg1);
    amount = func_8414A2AC();
    amount *= *(u8 *)((u8 *)table + 0x32);
    *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += amount;
    *(u8 *)(u32)base |= 2;
    
}

extern void *D_841951F8[];
void func_841523BC(void *arg0, u8 arg1) {
    s32 base;
    base = (s32)(u32)arg0 + 4;
    if (((u8 *)D_841951F8[arg1])[9] >= 2) {
        *(u8 *)((u8 *)(u32)base + arg1 + 8) = 0xFF;
        *(u8 *)((u8 *)(u32)base) |= 2;
    }
}

extern u8 func_8414A2D0(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_84152408(void *arg0, u8 arg1) {
    u8 scratch[8];
    void *table;
    s32 base;
    u8 mult;
    u8 value;

    value = *((u8 *)func_84154B64((1 - (u32)arg1) & 0xFF) + 0x24);
    if ((value != 0) && (value != 0xA5)) {
        base = ((s32)(u32)arg0 + 4) ^ 0;
        *((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF;
        mult = func_8414A2D0();
        table = func_8414A3A0(arg1);
        *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += *((u8 *)table + 0x33) * mult;
        *(u8 *)(u32)base |= 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841524B4.s")

extern s32 func_84154B9C(u8, u16);
extern u8 func_841524B4(u8);
void BattlePlan_AddHealBellBonus(u8 *plan, u8 side) {
    u8 *own;
    s32 base;
    u32 amount;
    u8 *table;
    own = func_84154B64(side);
    base = (s32)(u32)plan + 4;
    if (func_84154B9C(side, 0xFF) != 0 || (own[23] & 0x80) != 0) {
        *(u8 *)(u32)base |= 2;
        *(u8 *)((u32)base + (u32)side + 8) = 0xFF;
        table = func_8414A3A0(side);
        amount = table[52] * func_8414A2AC();
        ((u32 *)(u32)base)[(u32)side + 13] += amount * func_841524B4(side);
    }
}

extern s32 func_80063754(s32);
void BattlePlan_AddStealableItemBonus(u8 *plan, u8 side) {
    u8 *own;
    u8 *other;
    s32 base;
    u8 *table;
    u8 amount;
    own = func_84154B64(side);
    other = func_84154B64((1 - (u32)side) & 0xFF);
    base = (s32)(u32)plan + 4;
    if (own[1] == 0 && other[1] != 0 && func_80063754(other[1]) == 0) {
        *(u8 *)((u32)base + (u32)side + 8) = 0xFF;
        amount = func_8414A2AC();
        table = func_8414A3A0(side);
        ((u32 *)(u32)base)[(u32)side + 13] += table[53] * amount;
        *(u8 *)(u32)base |= 2;
    }
}

extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_841526CC(void *arg0, u8 arg1) {
    s32 base;
    void *state;
    void *table;
    u8 amount;
    base = (s32)(u32)arg0 + 4;
    state = func_84154B64(arg1);
    if (((*(u16 *)((u8 *)state + 0x26) & 7) != 0)) {
        *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF;
        amount = func_8414A2AC();
        table = func_8414A3A0(arg1);
        *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += *(u8 *)((u8 *)table + 0x36) * amount;
        *(u8 *)(u32)base |= 2;
    }
}

extern void *D_841951FC[];
extern s32 func_841493F4(void);
extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
extern s32 func_841556C4(u8 *, u8);
void func_84152764(void *arg0, u8 arg1)
{
    u8 *state;
    u8 *other;
    s32 base;
    s32 amount;
    void *table;

    base = (s32)(u32)arg0 + 4;
    state = func_84154B64(arg1);
    table = (void *)(u32)arg1;
    other = func_84154B64((u8)(1 - (u32)table));
    if (!(state[0x19] & 0x80) && (*(u8 *)((u8 *)(*(void **)((u8 *)D_841951FC + -(s32)((u32)table << 2))) + 9) >= 2) && (func_841556C4(other, 0x7F) == 0)) {
        table = func_8414A3A0(arg1);
        amount = func_8414A2AC();
        amount *= *(u8 *)((u8 *)table + 0x2D);
        *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += amount;
        *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += (amount * func_841493F4()) / 128;
        if ((other[0x15] & 0x10) && (other[0x1F] >= 2)) {
            *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += amount;
        }
        *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF;
        *(u8 *)(u32)base |= 2;
    }
}

extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_841528C4(void *arg0, u8 arg1) {
    s32 base;
    u8 *state;
    void *table;

    state = func_84154B64((1 - (u32)arg1) & 0xFF);
    if (!(state[0x18] & 0x10)) {
        if (*(u16 *)(state + 0x26) & 7) {
            base = (s32)(u32)arg0 + 4;
            if (!(state[0x15] & 1)) {
                *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF;
                table = func_8414A3A0(arg1);
                *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) = *(u8 *)((u8 *)table + 0x16) * func_8414A2AC();
                *(u8 *)(u32)base |= 2;
            }
        }
    }
}

extern void func_84150B14(void *, u8, s32, s32, s32, s32);
extern void func_84150EA4(u8 *, u8, u8, u8, u8, u8);
void BattlePlan_ScoreCurse(u8 *plan, u8 side) {
    u8 *own;
    u8 *other;
    u8 other_side;
    s32 base;
    u8 *table;
    base = (s32)(u32)plan + 4;
    own = func_84154B64(side);
    other_side = 1 - side;
    other = func_84154B64(other_side);
    if (func_84155544(own, 8) != 0) {
        if (((other[21] & 2) == 0) && ((other[24] & 0x10) == 0)) {
            *(u8 *)((u32)base + (u32)side + 8) = 0xFF;
            table = func_8414A3A0(side);
            ((u32 *)(u32)base)[(u32)side + 13] = table[22] * func_8414A2AC();
            *(u8 *)(u32)base |= 2;
        }
    } else {
        func_84150B14(plan, side, 174, 0xFF, 0, 1);
        func_84150B14(plan, side, 174, 0xFF, 1, 1);
        func_84150EA4(plan, other_side, 174, 0xFF, 2, 1);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84152AC0.s")

extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 * func_84154B30(u8);
void func_84152C34(void *arg0, u8 arg1) { s32 base; void *table; u32 *entry; u8 amount; base = (s32)(u32)arg0 + 4; if ((func_84154B30((0x1 - (u32)arg1) & 0xFF)[3] & 1) == 0) { *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF; amount = func_8414A2AC(); table = func_8414A3A0(arg1); entry = (u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34); *entry += *(u8 *)((u8 *)table + 0x38) * amount; *(u8 *)(u32)base |= 2; } }

extern u8 func_80062D5C(u8);
extern u8 func_80062D98(u8);
s32 BattlePlan_HasOnlyNormalOrFightingMoves(u8 *state) {
    s32 i;
    u16 type;
    for (i = 0; i < 4; i++) {
        if (state[i + 4] == 0) {
            break;
        }
        type = func_80062D98(state[i + 4]);
        //!bug The retail code tests the power getter address instead of calling it.
        if (type != 0 && type != 1 && func_80062D5C != NULL) {
            return 0;
        }
    }
    return 1;
}

u8 BattlePlan_CountHitObstacles(u8 side) {
    u8 result;
    u8 *own;
    u8 *other;
    result = 0;
    own = func_84154B64(side);
    other = func_84154B64((1 - side) & 0xFF);
    if (own[18] < 7) {
        result = 1;
    }
    if (other[19] >= 8) {
        result++;
    }
    if (func_84155544(other, 8) != 0 && BattlePlan_HasOnlyNormalOrFightingMoves(own) != 0) {
        result += 2;
    }
    return result;
}

void BattlePlan_AddHitObstacleBonus(u8 *plan, u8 side) {
    u8 count;
    u8 *other;
    s32 base;
    u8 *table;
    u32 *score;
    u8 amount;
    func_84154B64(side);
    other = func_84154B64((1 - (u32)side) & 0xFF);
    base = (s32)(u32)plan + 4;
    if ((other[21] & 8) == 0) {
        *(u8 *)((u32)base + (u32)side + 8) = 0xFF;
        count = BattlePlan_CountHitObstacles(side);
        if (count > 0) {
            amount = func_8414A2AC();
            table = func_8414A3A0(side);
            score = (u32 *)((u32)base + ((u32)side << 2));
            score[13] += count * table[57] * amount;
            *(u8 *)(u32)base |= 2;
        }
    }
}

void BattlePlan_AddPerishSongBonus(u8 *plan, u8 side) {
    u8 *own;
    s32 base;
    s32 index;
    u32 amount;
    u8 *table;
    own = func_84154B64(side);
    index = side;
    base = (s32)(u32)plan + 4;
    if ((func_84154B64((1 - index) & 0xFF)[21] & 0x10) == 0 && ((u8 *)D_841951F8[side])[9] >= 2) {
        *(u8 *)((u32)base + (u32)side + 8) = 0xFF;
        table = func_8414A3A0(side);
        amount = table[58] * func_8414A2AC();
        ((u32 *)(u32)base)[(u32)side + 13] += amount;
        if ((*(u8 **)((u32)D_841951FC + -(s32)(index << 2)))[9] == 1) {
            ((u32 *)(u32)base)[(u32)side + 13] += amount * 3;
        }
        if (func_841556C4(own, 111) != 0) {
            ((u32 *)(u32)base)[(u32)side + 13] += amount;
        }
        *(u8 *)(u32)base |= 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153028.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_841531D4.s")

extern void func_84151B8C(s32, u8, u8);
extern u8 *func_84154B64(u8);
void func_84153304(s32 arg0, u8 arg1, u8 arg2) {
    if ((s32) (*(u8 *)((u8 *)(func_84154B64((1 - arg1) & 0xFF)) + (0xD))) < 0xD) {
        func_84151B8C(arg0, arg1, arg2);
    }
}

extern s32 func_80064474(u8, u16);
extern u8 func_8414A2A0(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_8415335C(void *arg0, u8 arg1) {
    u8 val1;
    void *ptr1, *ptr2;
    s32 index;
    s32 base;
    u8 amount;
    u8 val2;

    base = (s32)(u32)arg0 + 4;
    index = arg1;
    ptr1 = func_84154B64(index);
    ptr2 = func_84154B64((1 - index) & 0xFF);
    if (!(*(u8 *)((u8 *)ptr2 + 0x15) & 0x80)) {
        val1 = func_80064474(*(u8 *)ptr1, *(u16 *)((u8 *)ptr1 + 0x40));
        val2 = func_80064474(*(u8 *)ptr2, *(u16 *)((u8 *)ptr2 + 0x40));
        if ((val1 != 0) && (val2 != 0) && (val1 != val2)) {
            *(u8 *)((u8 *)(u32)base + index + 8) = 0xFF;
            amount = func_8414A2A0();
            ptr1 = func_8414A3A0(index);
            *(u32 *)((u8 *)(u32)base + (index << 2) + 0x34) += *(u8 *)((u8 *)ptr1 + 0x15) * amount;
            *(u8 *)(u32)base |= 2;
        }
    }
}

extern s32 func_841556C4(u8 *, u8);
extern u8 func_8414A2C4(void);
extern u8 func_8414A2AC(void);
extern void * func_8414A3A0(u8);
extern u8 * func_84154B30(u8);
void func_84153454(void *arg0, u8 arg1) {
    u8 *state;
    u8 *sub;
    s32 base;
    void *table;
    s32 unused;
    base = (s32)(u32)arg0 + 4;
    state = func_84154B30(arg1);
    sub = state + 8;
    table = func_8414A3A0(arg1);
    if (!(state[3] & 4)) {
        if (func_841556C4(sub, 0x1B) != 0) {
            *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += *(u8 *)((u8 *)table + 0xB) * func_8414A2C4();
        }
        *(u8 *)((u8 *)(u32)base + (u32)arg1 + 8) = 0xFF;
        *(u32 *)((u8 *)(u32)base + ((u32)arg1 << 2) + 0x34) += *(u8 *)((u8 *)table + 0x3B) * func_8414A2AC();
        *(u8 *)(u32)base |= 2;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153554.s")

u8 *func_84154B30(u8);
u8 func_84153718(u8 arg0) { u8 *state; u8 result; state = func_84154B30(arg0); result = 0; if ((state[0x20] & 0x80) != 0) result = 1; if ((state[3] & 1) != 0) { result++; result &= 0xFF; } if (state[0x2B] > 0) result++; return result; }

void BattlePlan_AddConditionCountBonus(u8 *state, u8 side) {
    s32 base;
    u32 *entry;
    u8 count;
    u8 amount;
    base = (s32)(u32)state + 4;
    state[(u32)side + 12] = 0xFF;
    amount = func_8414A2AC();
    count = func_84153718(side);
    entry = (u32 *)(base + ((u32)side << 2));
    entry[13] += ((u32)count << 7) * amount;
    *(u8 *)(u32)base |= 2;
}

extern u8 *func_84154B0C(void);
extern u8 func_8414A2B8(void);
extern u8 func_84148C74(u8);
extern u8 func_80062D98(u8);
extern s32 BattleRecord_HasPoweredMoveOfType(u8 *, u8);
extern s32 BattleRecord_HasMove(u8 *, u8);
void BattlePlan_AddRainDanceBonus(u8 *plan, u8 side) {
    u8 *own;
    BattlePlanScoreHeader *base;
    s32 amount;
    u8 *table;
    own = func_84154B64(side);
    base = (void *)(plan + 4);
    if (func_84154B0C()[408] != 1) {
        base->selected[side] = 0xFF;
        table = func_8414A3A0(side);
        amount = table[43] * func_8414A2B8();
        if (BattleRecord_HasPoweredMoveOfType(own, 21) != 0) {
            base->score[side] += amount;
        }
        if (func_80062D98(func_84148C74((1 - (u32)side) & 0xFF)) == 20) {
            base->score[side] += amount;
        }
        if (BattleRecord_HasMove(own, 87) != 0) {
            base->score[side] += amount;
        }
        base->score[side] += amount / 2;
        base->flags |= 2;
    }
}

void BattlePlan_AddSunnyDayBonus(u8 *plan, u8 side) {
    u8 *own;
    BattlePlanScoreHeader *base;
    s32 amount;
    u8 *table;
    own = func_84154B64(side);
    base = (void *)(plan + 4);
    if (func_84154B0C()[408] != 2) {
        base->selected[side] = 0xFF;
        table = func_8414A3A0(side);
        amount = table[42] * func_8414A2B8();
        if (BattleRecord_HasPoweredMoveOfType(own, 20) != 0) {
            base->score[side] += amount;
        }
        if (func_80062D98(func_84148C74((1 - (u32)side) & 0xFF)) == 21) {
            base->score[side] += amount;
        }
        if (BattleRecord_HasMove(own, 76) != 0) {
            base->score[side] += amount;
        }
        base->score[side] += amount / 2;
        base->flags |= 2;
    }
}

extern void func_84150B14(void *, u8, s32, s32, s32, s32);
extern u8 *func_84154B64(u8);
void func_84153A64(void *arg0, u8 arg1)
{
  u8 *state;
  int new_var;
  state = func_84154B64(arg1);
  new_var = 4;
  func_84154B64((1 - ((u32) arg1)) & 0xFF);
  if ((((*((u16 *) (state + 0x28))) >= ((*((u16 *) (state + 0x2A))) >> 1)) && (state[0xD] < 0xD)) && ((*((u16 *) (state + 0x36))) < 0x3E7))
  {
    func_84150B14(arg0, arg1, 0xBB, 0xFF, 0, 0xD);
    *(((u8 *) arg0) + new_var) |= 2;
  }
}

s32 BattlePlan_HasUnfavorableStages(u8 *plan, u8 side) {
    s32 i;
    BattlePlanStageRecord *own;
    BattlePlanStageRecord *other;
    own = (void *)func_84154B64(side);
    other = (void *)func_84154B64((1 - (u32)side) & 0xFF);
    for (i = 0; i < 7; i++) {
        if (own->stages[i] < 7) {
            return 1;
        }
        if (other->stages[i] > 7) {
            return 1;
        }
    }
    return 0;
}

void BattlePlan_AddPsychUpBonus(u8 *plan, u8 side) {
    BattlePlanStageRecord *own;
    s32 i;
    s32 difference;
    BattlePlanStageRecord *other;
    s32 base;
    base = (s32)(u32)plan + 4;
    own = (void *)func_84154B64(side);
    other = (void *)func_84154B64((1 - (u32)side) & 0xFF);
    if (BattlePlan_HasUnfavorableStages(plan, side) != 0) {
        for (i = 0; i < 7; i++) {
            difference = other->stages[i] - own->stages[i];
            if (difference > 0) {
                func_84150B14(plan, side, 244, 0xFF, i, difference);
            }
        }
        *(u8 *)(u32)base |= 2;
    }
}

extern u8 func_8414A2D0(void);
extern void * func_8414A3A0(u8);
extern u8 *func_84154B64(u8);
void func_84153D94(void *arg0, u8 arg1)
{
  s32 base;
  void *table;
  u8 *new_var;
  volatile unsigned char amount;
  base = ((s32) ((u32) arg0)) + 4;
  if ((*((u8 *) (((u8 *) func_84154B64(arg1)) + 0x22))) == 0)
  {
    *((u8 *) ((((u8 *) ((u32) base)) + ((u32) arg1)) + 8)) = 0xFF;
    amount = func_8414A2D0();
    table = func_8414A3A0(arg1);
    new_var = (u8 *) table;
    *((u32 *) ((((u8 *) ((u32) base)) + (((u32) arg1) << 2)) + 0x34)) += (*((u8 *) (new_var + 0x3C))) * amount;
    *((u8 *) ((u32) base)) |= 2;
  }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3BF4C0/func_84153E28.s")
#endif
