#include "global.h"


#ifdef VERSION_US
void func_82603A90(s16 *arg0) {
    *arg0 = -1;
}

s16 *func_82603A9C(s16 *arg0, s32 arg1) {
    s16 *new_var;
    s16 *current;
    s16 *result;
    s32 index;

    result = 0;
    index = 0;
    if (arg1 > 0) {
        current = (new_var = arg0);
        do {
            index += 1;
            if ((*current) == -1) {
                result = current;
                break;
            }
            current += 0x40A;
        } while (index != arg1);
    }
    return result;
}
typedef struct {
    u32 words[2];
} Pair_82603AD8;
typedef struct {
    s16 index;
    s16 field2;
    s16 field4;
    s16 pad6;
    f32 value;
    Pair_82603AD8 first;
    Pair_82603AD8 entries[1];
} State_82603AD8;

void func_82603AD8(State_82603AD8 *arg0, f32 arg1,
                   Pair_82603AD8 *arg2, Pair_82603AD8 *arg3) {
    arg0->index = 0;
    arg0->field2 = 0;
    arg0->field4 = 1;
    arg0->value = arg1;
    arg0->first = *arg2;
    arg0->entries[arg0->index] = *arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12BB60/func_82603B20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12BB60/func_82603D70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12BB60/func_826040D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12BB60/func_82604170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12BB60/func_826042A0.s")
#endif
