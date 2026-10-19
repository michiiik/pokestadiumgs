#include "global.h"


#ifdef VERSION_US
s32 func_88902B70(u8 *arg0) {
    s32 var_v1;

    var_v1 = 0;
loop_1:
    if ((*(u8 *)((u8 *)(&arg0[var_v1]) + (2))) != 0) {
        var_v1 = (var_v1 + 1) & 0xFF;
        if (var_v1 < 4) {
            goto loop_1;
        }
    }
    return var_v1;
}

s32 func_88902BA0(void *arg0, u8 arg1) {
    s32 index = 0;
loop:
    if (arg1 == ((u8 *)arg0)[index + 2]) {
        return 1;
    }
    index = (index + 1) & 0xFF;
    if (index < 4) {
        goto loop;
    }
    return 0;
}

extern s32 func_88902B70(u8 *); extern u8 D_889041A0; extern u8 func_80062E10(u8); void func_88902BE0(u8 *arg0, u8 arg1) { s32 i = func_88902B70(arg0); if (i < 4) i &= 0xff; else i = D_889041A0; *(u8 *)(arg0 + i + 2) = arg1; *(u8 *)(arg0 + i + 0x18) = func_80062E10(arg1); }

// The type-color helper writes three RGB bytes and returns their destination.
//@src/fragments/29/fragment29_166060.c
typedef struct LabPCMoveNameColor {
    u8 red;
    u8 green;
    u8 blue;
} LabPCMoveNameColor;
extern LabPCMoveNameColor *func_88000510(LabPCMoveNameColor *, s8);
extern u8 func_80062D98(u8);
extern s32 *func_80062CE0(u8);
extern void *func_8004C874(s32, s32);
const char D_88903FE0[] = "<COL1,PUSH,%d,%d,%d,255>%s<COL1,POP>";
char *LabPC_FormatColoredMoveName(char *output, u8 move) {
    LabPCMoveNameColor color;

    func_88000510(&color, move == 252 ? 0 : func_80062D98(move));
    sprintf(output, D_88903FE0, color.red, color.green, color.blue,
        move == 252 ? func_8004C874(69, 19) : (const char *)func_80062CE0(move));
    return output;
}

extern s32 func_88902BA0(void *, u8);
extern u8 func_8005D92C(s32 index);
s32 func_88902CF0(void *arg0, u8 *arg1, s8 arg2) {
    s32 dispatch;
    u8 *p;
    u8 ret;

    dispatch = func_8005D92C(arg2) & 0xFF;
    p = *(u8 **)arg0;
    while (p[0] != 0 && p[0] <= arg1[0x1D]) {
        if (arg1[0x1D] == p[0] && func_88902BA0(arg1, p[1]) == 0) {
            switch (dispatch) {
                case 1:
                case 2:
                case 3:
                    p = *(u8 **)arg0;
                    if (p[2] & 1) {
                        ret = p[1];
                        *(u8 **)arg0 = p + 3;
                        return ret;
                    }
                    break;
                case 4:
                    p = *(u8 **)arg0;
                    if (p[2] & 2) {
                        ret = p[1];
                        *(u8 **)arg0 = p + 3;
                        return ret;
                    }
                    break;
                case 5:
                case 6:
                    p = *(u8 **)arg0;
                    if (p[2] & 4) {
                        ret = p[1];
                        *(u8 **)arg0 = p + 3;
                        return ret;
                    }
                    break;
                default:
                    p = *(u8 **)arg0;
                    if (p[2] & 8) {
                        ret = p[1];
                        *(u8 **)arg0 = p + 3;
                        return ret;
                    }
                    break;
            }
        }
        *(u8 **)arg0 = *(u8 **)arg0 + 3;
        p = *(u8 **)arg0;
    }
    return 0;
}

extern s32 func_80064800(u8);
s32 func_88902E4C(u32 *cursor, u8 *pokemon, s8 slot) {
    *cursor = func_80064800(pokemon[0]);
    return func_88902CF0(cursor, pokemon, slot);
}

extern s32 func_80063BB8(u8);
extern s32 func_8800005C(void);
extern void func_8005F37C(s32, s32, s32, s32, s32);
extern u8 D_88006868;
s32 LabPC_FindLevelUpEvolution(u8 *pokemon, s32 use_clock) {
    u8 *rule;
    u16 days;
    u8 hour;
    u8 minute;
    u8 second;

    rule = (u8 *)func_80063BB8(pokemon[0]);
    if (rule != NULL && pokemon[1] != 112) {
        while (rule[0] != 0) {
            switch (rule[0]) {
            case 1:
                if (pokemon[29] >= rule[1]) {
                    return rule[2];
                }
                break;
            case 3:
                if (func_8800005C() != 0) {
                    break;
                }
                if (pokemon[28] >= 221) {
                    if (rule[1] == 1) {
                        return rule[2];
                    }
                    if (use_clock != 0) {
                        func_8005F37C(D_88006868, (s32)&days, (s32)&hour, (s32)&minute, (s32)&second);
                        if (hour >= 4 && hour < 18) {
                            return 196;
                        }
                        return 197;
                    }
                    return rule[2];
                }
                break;
            case 5:
                if (func_8800005C() != 0 || pokemon[29] < rule[1]) {
                    break;
                }
                if (*(u16 *)(pokemon + 44) < *(u16 *)(pokemon + 42)) {
                    return rule[2];
                }
                break;
            case 6:
                if (func_8800005C() != 0 || pokemon[29] < rule[1]) {
                    break;
                }
                if (*(u16 *)(pokemon + 42) < *(u16 *)(pokemon + 44)) {
                    return rule[2];
                }
                break;
            case 7:
                if (func_8800005C() != 0 || pokemon[29] < rule[1]) {
                    break;
                }
                if (*(u16 *)(pokemon + 44) == *(u16 *)(pokemon + 42)) {
                    return rule[2];
                }
                break;
            }
            rule += 3;
        }
    }
    return 0;
}

u8 func_88903084(u8 arg0) { u8 result = 0; switch (arg0) { case 0x1e: result=0x1f; break; case 0x21: result=0x22; break; case 0x23: result=0x24; break; case 0x27: result=0x28; break; default: break; } return result; }

u8 LabPC_FindFireStoneEvolution(u8 species) {
    u8 result = 0;

    switch (species) {
    case 133:
        result = 136;
        break;
    case 37:
        result = 38;
        break;
    case 58:
        result = 59;
        break;
    }
    return result;
}

u8 func_8890311C(u8 arg0) {
    u8 result = 0;
    if (arg0 != 0x19) {
        if (arg0 == 0x85) {
            result = 0x87;
        }
    } else {
        result = 0x1A;
    }
    return result;
}

u8 LabPC_FindWaterStoneEvolution(u8 species) {
    u8 result = 0;

    switch (species) {
    case 133:
        result = 134;
        break;
    case 61:
        result = 62;
        break;
    case 90:
        result = 91;
        break;
    case 120:
        result = 121;
        break;
    }
    return result;
}

u8 LabPC_FindLeafStoneEvolution(u8 species) {
    u8 result = 0;

    switch (species) {
    case 70:
        result = 71;
        break;
    case 102:
        result = 103;
        break;
    case 44:
        result = 45;
        break;
    }
    return result;
}

u8 func_889031EC(u8 arg0) { u8 result = 0; switch (arg0) { case 0x2c: result=0xb6; break; case 0xbf: result=0xc0; break; default: break; } return result; }

extern u8 func_8005D92C(s32 index);
extern s32 fragment29_main(u8);
s32 func_88903220(u8 *arg0, s8 arg1) {
    u8 result = 0;

    if ((arg0[0x1E] & 1) == 0) {
        if (arg0[1] != 0x70) {
            switch (arg0[0]) {
                case 0x40: result = 0x41; break;
                case 0x43: result = 0x44; break;
                case 0x4B: result = 0x4C; break;
                case 0x5D: result = 0x5E; break;
            }
            if (result == 0) {
                if (fragment29_main(func_8005D92C(arg1)) == 0) {
                    switch (arg0[0]) {
                        case 0x3D:
                            if (arg0[1] == 0x52) result = 0xBA;
                            break;
                        case 0x4F:
                            if (arg0[1] == 0x52) result = 0xC7;
                            break;
                        case 0x5F:
                            if (arg0[1] == 0x8F) result = 0xD0;
                            break;
                        case 0x7B:
                            if (arg0[1] == 0x8F) result = 0xD4;
                            break;
                        case 0x75:
                            if (arg0[1] == 0x97) result = 0xE6;
                            break;
                        case 0x89:
                            if (arg0[1] == 0xAC) result = 0xE9;
                            break;
                    }
                }
            }
        }
    }
    return result;
}
#endif
