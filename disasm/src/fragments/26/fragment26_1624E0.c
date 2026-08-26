#include "global.h"


#ifdef VERSION_US
typedef struct {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} Func81003CC0Range;
typedef struct {
    u8 unk_00;
    u8 unk_01;
} Func81003CC0Flag;
typedef struct {
    u8 pad[4];
    Func81003CC0Flag *flag;
    u8 pad_08[12];
    Func81003CC0Range *range;
} Func81003CC0State;
typedef struct {
    u8 pad_00[0x40];
    s16 unk_40;
    u8 pad_42[6];
    u32 unk_48;
} Func81003CC0Global;
extern Func81003CC0Global *D_8009491C;

void DisplayList_SetFlagInRange(s32 arg0, Func81003CC0State *arg1) {
    s32 temp_a2;
    s32 var_v1;
    Func81003CC0Range *temp_v0;
    Func81003CC0Flag *temp_v0_2;

    if (arg0 == 2) {
        temp_v0 = arg1->range;
        var_v1 = 0;
        if (D_8009491C->unk_40 == temp_v0->unk_00) {
            temp_a2 = ((s32) D_8009491C->unk_48 >> 16) & 0xFFFF;
            if ((temp_a2 >= (s32) temp_v0->unk_02) && ((s32) temp_v0->unk_04 >= temp_a2)) {
                var_v1 = 1;
            }
        }
        if (var_v1 == 1) {
            temp_v0_2 = arg1->flag;
            temp_v0_2->unk_01 |= 1;
            return;
        }
        temp_v0_2 = arg1->flag;
        temp_v0_2->unk_01 &= 0xFFFE;
    }
}

void DisplayList_SetFlagOutOfRange(s32 arg0, Func81003CC0State *arg1) {
    s32 temp_a2;
    s32 var_v1;
    Func81003CC0Range *temp_v0;
    Func81003CC0Flag *temp_v0_2;

    if (arg0 == 2) {
        temp_v0 = arg1->range;
        var_v1 = 1;
        if (D_8009491C->unk_40 == temp_v0->unk_00) {
            temp_a2 = ((s32) D_8009491C->unk_48 >> 16) & 0xFFFF;
            if ((temp_a2 >= (s32) temp_v0->unk_02) && ((s32) temp_v0->unk_04 >= temp_a2)) {
                var_v1 = 0;
            }
        }
        if (var_v1 == 1) {
            temp_v0_2 = arg1->flag;
            temp_v0_2->unk_01 |= 1;
            return;
        }
        temp_v0_2 = arg1->flag;
        temp_v0_2->unk_01 &= 0xFFFE;
    }
}

typedef struct {
    u8 pad_00[0x14];
    void *unk_14;
    u8 pad_18[4];
    u16 unk_1C;
    u8 pad_1E[2];
    s16 unk_20;
} Func81003D50StateAlt;
typedef struct {
    u8 pad_00[0x0C];
    void *unk_0C;
    s32 unk_10;
} Func81003D50TableAlt;
extern s32 ModelAnim_ResolveEventIndex();
void func_81003D50(Func81003D50StateAlt *arg0, s32 arg1, Func81003D50TableAlt *arg2) {
    arg0->unk_20 = -1;
    arg0->unk_1C = *(u8 *)(ModelAnim_ResolveEventIndex(arg1, arg2->unk_0C, arg0->unk_14) + arg2->unk_10);
}

typedef struct {
    u8 pad_00[0x14];
    void *unk_14;
    u8 pad_18[4];
    u16 unk_1C;
    u8 pad_1E[2];
    s16 unk_20;
} Func81003DACStateAlt;
typedef struct {
    u8 pad_00[0x10];
    void *unk_10;
} Func81003DACResultAlt;
typedef struct {
    u8 pad_00[0x0A];
    u16 unk_0A;
} Func81003DACEntryAlt;
typedef struct {
    u8 pad_00[0x2C];
    s32 (*callback)(s32, s32);
} Func81003DACGlobalAlt;
extern Func81003DACGlobalAlt *D_80094920;
void func_81003DAC(s32 arg0, Func81003DACStateAlt *arg1) {
    Func81003DACStateAlt *state = arg1;
    s32 frame;
    Func81003DACEntryAlt *entry;

    switch (arg0) {
        case 0:
            state->unk_14 = (void *)(s32)state->unk_20;
            break;
        case 2:
            if ((D_8009491C != NULL) && (D_80094920 != NULL)) {
                frame = *(s8 *)((u8 *)D_8009491C + 0xA6);
                entry = *(Func81003DACEntryAlt **)((Func81003DACResultAlt *)D_80094920->callback(0, 0))->unk_10;
                if (frame < 0 || frame >= entry->unk_0A) {
                    frame = 0;
                }
                func_81003D50(state, frame, entry);
            }
            break;
        default:
            break;
    }
}
#pragma C_FUNCTION_PADDING(8)
#endif
