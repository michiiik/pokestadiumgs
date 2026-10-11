#include "global.h"


#ifdef VERSION_US
void func_82603A90(s16 *arg0) {
    *arg0 = -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/20/fragment20_12BB60/func_82603A9C.s")

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
