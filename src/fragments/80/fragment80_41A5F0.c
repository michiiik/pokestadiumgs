#include "global.h"


#ifdef VERSION_US
/* Original debug text preceding this translation unit's jump table. */
const char D_84203790[] = "SetPower...";
const char D_8420379C[] = "end\n";
const char D_842037A4[] = "SetPowerPSP\n";
const char D_842037B4[] = "GetDamagePSP\n";
const char D_842037C4[] = "ChkZokuseiPSP\n";
const char D_842037D4[] = "aiesDamage\n";
const char D_842037E0[] = "aiesSetEntrySimData\n";

typedef struct Fragment80DamageContext {
    u8 move, effect, power, type, accuracy, level;
    u16 attack, defense;
    u8 unk_0A[2];
    s32 damage, score;
    u32 *parameters;
    u8 *attacker, *defender;
} Fragment80DamageContext;
typedef char Fragment80DamageContextSizeCheck[sizeof(Fragment80DamageContext)==32 ? 1 : -1];
extern s32 Species_HasType_fragment80(u8 *, s32);
extern u8 func_8006397C(u8);
extern u8 func_800639C0(u8);
extern s32 func_800632CC(s32 *, u8, u8, u8, s32);
extern s32 func_800636C0(u8, u8);
extern u8 func_80063690(u8);
extern u8 func_84200094(u8 *, u8);

void MoveDamage_LoadStats_fragment80(void *arg0) {
    Fragment80DamageContext *ctx = arg0;
    if (ctx->power != 0) {
        if (ctx->type < 20) {
            ctx->attack = *(u16 *)(ctx->attacker + 0x2A);
            ctx->defense = *(u16 *)(ctx->defender + 0x2C);
            if (ctx->attacker[1] == 118 && (ctx->attacker[0] == 104 || ctx->attacker[0] == 105)) {
                ctx->attack *= 2;
            }
        } else {
            ctx->attack = *(u16 *)(ctx->attacker + 0x30);
            ctx->defense = *(u16 *)(ctx->defender + 0x32);
            if (ctx->attacker[1] == 163 && ctx->attacker[0] == 25) {
                ctx->attack *= 2;
            }
        }
        ctx->level = ctx->attacker[0x1D];
    }
}

void MoveDamage_ComputeBase_fragment80(void *arg0) {
    Fragment80DamageContext *ctx = arg0;
    if (ctx->power != 0) {
        if (ctx->effect == 7) {
            ctx->defense >>= 1;
        }
        if (ctx->defense == 0) {
            ctx->defense++;
        }
        ctx->damage = (((ctx->level * 2 / 5 + 2) * ctx->power * ctx->attack) / ctx->defense) / 50;
        if (func_800636C0(ctx->attacker[1], ctx->type)) {
            ctx->damage *= func_80063690(ctx->attacker[1]) + 100;
            ctx->damage /= 100;
        }
        if (ctx->damage >= 999) {
            ctx->damage = 996;
        }
        ctx->damage += 2;
    }
}

void MoveDamage_ApplyTypeFactors_fragment80(void *arg0) {
    u8 second;
    u8 first;
    if (Species_HasType_fragment80(((Fragment80DamageContext *)arg0)->attacker, ((Fragment80DamageContext *)arg0)->type)) {
        ((Fragment80DamageContext *)arg0)->damage += ((Fragment80DamageContext *)arg0)->damage >> 1;
    }
    first = func_8006397C(((Fragment80DamageContext *)arg0)->defender[0]);
    second = func_800639C0(((Fragment80DamageContext *)arg0)->defender[0]);
    func_800632CC(&((Fragment80DamageContext *)arg0)->damage, ((Fragment80DamageContext *)arg0)->type, first, second, 0);
}

void MoveDamage_ApplyPowerEffect_fragment80(void *arg0) {
    Fragment80DamageContext *ctx = arg0;
    switch (ctx->effect) {
    case 99:
        ctx->power = 60;
        MoveDamage_LoadStats_fragment80(ctx);
        break;
    case 121:
        MoveDamage_LoadStats_fragment80(ctx);
        ctx->power = ctx->attacker[0x1C] * 10 / 25;
        break;
    case 122:
        MoveDamage_LoadStats_fragment80(ctx);
        ctx->power = 52;
        break;
    case 123:
        MoveDamage_LoadStats_fragment80(ctx);
        ctx->power = (255 - ctx->attacker[0x1C]) * 10 / 25;
        break;
    case 126:
        MoveDamage_LoadStats_fragment80(ctx);
        ctx->power = 64;
        break;
    case 135:
        MoveDamage_LoadStats_fragment80(ctx);
        break;
    default:
        MoveDamage_LoadStats_fragment80(ctx);
        break;
    }
}

void MoveDamage_ApplyEffect_fragment80(void *arg0) {
    Fragment80DamageContext *ctx = arg0;
    switch (ctx->effect) {
    case 38:
        if (ctx->attacker[0x1D] >= ctx->defender[0x1D]) {
            ctx->damage = 65535;
        }
        return;
    case 40:
        ctx->damage = *(u16 *)(ctx->defender + 0x26) >> 1;
        if (!ctx->damage) {
            ctx->damage++;
        }
        return;
    case 41:
        ctx->damage = ctx->power;
        return;
    case 87:
        ctx->damage = ctx->attacker[0x1D];
        return;
    case 88:
        ctx->damage = ctx->attacker[0x1D] * 0.75;
        return;
    default:
        MoveDamage_ComputeBase_fragment80(ctx);
        return;
    }
}

typedef struct unk_func_84201620 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02[18];
    u32* unk_14;
} unk_func_84201620;

void func_84201620(unk_func_84201620* arg0) {
    if ((*arg0->unk_14 & 1) == 0) {
        if ((arg0->unk_01 != 38) && (arg0->unk_01 != 40) && (arg0->unk_01 != 41) &&
            (arg0->unk_01 != 87) && (arg0->unk_01 != 88) && (arg0->unk_01 != 148)) {
            MoveDamage_ApplyTypeFactors_fragment80(arg0);
        }
    }
}

void func_8420168C(void *arg0) { MoveDamage_ApplyPowerEffect_fragment80(arg0); MoveDamage_ApplyEffect_fragment80(arg0); func_84201620(arg0); }

typedef struct unk_func_842016BC {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 unk_05[7];
    s32 unk_0C;
    s32 unk_10;
} unk_func_842016BC;

extern u8 func_80062D20(u8 arg0);
extern u8 func_80062D5C(u8 arg0);
extern u8 func_80062D98(u8 arg0);
extern u8 func_80062DD4(u8 arg0);

void func_842016BC(u8 arg0, unk_func_842016BC* arg1) {
    arg1->unk_00 = arg0;
    arg1->unk_01 = func_80062D20(arg0);
    arg1->unk_02 = func_80062D5C(arg0);
    arg1->unk_03 = func_80062D98(arg0);
    arg1->unk_04 = func_80062DD4(arg0);
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
}

void MoveAccuracy_AdjustLevelDifference_fragment80(u8 *arg0) {
    s32 difference;
    difference = (*(u8 **)(arg0 + 0x18))[0x1D] - (*(u8 **)(arg0 + 0x1C))[0x1D];
    if (func_84200094(*(u8 **)(arg0 + 0x1C), arg0[3]) && difference >= 0) {
        arg0[4] += difference * 2;
    } else {
        arg0[4] = 0;
    }
}

void func_84201794(u8 *arg0) { if (arg0[1] == 0x26) { MoveAccuracy_AdjustLevelDifference_fragment80(arg0); } }
#endif
