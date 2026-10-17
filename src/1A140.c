#include "global.h"


#ifdef VERSION_US
void func_80019540(void *arg0, s32 arg1) {
    u32 sp1C;

    sp1C = osSetIntMask(1U);
    osInvalDCache(arg0, arg1);
    osSetIntMask(sp1C);
}

void func_80019580(void *arg0, s32 arg1) {
    u32 sp1C;

    sp1C = osSetIntMask(1U);
    osWritebackDCache(arg0, arg1);
    osSetIntMask(sp1C);
}


extern u8 D_8008FAA0;
extern u8 Audio_AiHdwrBugFlag;

s32 func_800195C0(void *bufPtr, s32 size) {
    char *bptr = bufPtr;
    register s32 status;

    if (D_8008FAA0 != 0) {
        bptr = (char *)bufPtr - 0x2000;
    }

    if ((((u32)bufPtr + size) & 0x1FFF) == 0) {
        Audio_AiHdwrBugFlag = 1;
    } else {
        Audio_AiHdwrBugFlag = 0;
    }

    status = IO_READ(AI_STATUS_REG);
    if (status & AI_STATUS_FIFO_FULL) {
        return -1;
    }

    IO_WRITE(AI_DRAM_ADDR_REG, OS_K0_TO_PHYSICAL(bptr));
    IO_WRITE(AI_LEN_REG, size);
    return 0;
}


extern u8 D_8008FAB8;
extern u8 D_8008FB28;
extern void *D_8008FC18;
extern void *D_8008FC1C;

void func_80019634(s32 arg0) {
    D_8008FC18 = (arg0 * 0x22) + &D_8008FB28;
    D_8008FC1C = (arg0 * 0x10) + &D_8008FAB8;
}

extern s16 D_8008FAA4[];

s32 func_80019670(s32 arg0) {
    s32 var_v1 = 0;
    s32 var_a1;

    for (var_a1 = 1; var_a1 < 16; var_a1++) {
        if (arg0 < ((s16*)D_8008FC18)[var_a1]) {
            break;
        }
        var_v1++;
    }
    if (var_a1 == 16) {
        return 0;
    }
    var_v1 = ((s8*)D_8008FC1C)[var_v1];
    return D_8008FAA4[var_v1];
}

s32 func_800196E0(s32 *arg0, s32 *arg1) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;

    var_s0 = *arg0;
    var_s1 = *arg1;
loop_1:
    temp_v0 = func_80019670(var_s0);
    if (temp_v0 == 0) {
        return -1;
    }
    if (var_s1 >= temp_v0) {
        var_s1 -= temp_v0;
        var_s0 += 1;
        goto loop_1;
    }
    *arg0 = var_s0;
    *arg1 = var_s1;
    return 0;
}
#endif
