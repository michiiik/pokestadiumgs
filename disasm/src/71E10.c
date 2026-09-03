#include "global.h"


#ifdef VERSION_US
s32 func_80071210(u8 *arg0) { return arg0 ? ((*(u32 *)(arg0 + 0x40) << 1) >> 31) : 0; }

s32 func_80071230(u8 *arg0) { return arg0 ? ((*(u32 *)(arg0 + 0x40) << 2) >> 31) : 0; }

s32 func_80071250(u8 *arg0) {
    s16 value = *(s16 *)(arg0 + 0x34);

    return value > 0 && value < 5;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/71E10/func_8007126C.s")

extern s32 func_8007126C(s32, s32, u8, void *);
s32 func_800712DC(s32 arg0, void *arg1) {
    u8 value = *(u8 *)arg1;
    s32 result = 0;
    if (value <= 0) goto empty;
    result = func_8007126C(arg0, value - 1, *(u8 *)((u8 *)arg1 + 0x1D), arg1);
    goto finish;
empty:
    result = 0;
finish:
    return result;
}

typedef struct {u8 pad[0x1D];u8 value;u8 rest[0x3A];} R;
s32 func_8007131C(R *arg0){s32 result=0; s32 count=0; s32 i,j,k; R *p=arg0; while(count<6){if(p->pad[0]==0||p->pad[0]>=0xFC)break;result+=p->value;count++;p++;} for(i=0;i<count;i++)for(j=i+1;j<count;j++)for(k=j+1;k<count;k++){s32 v=arg0[i].value+arg0[j].value+arg0[k].value;if(result>=v)result=v;}return result;}

#pragma GLOBAL_ASM("asm/us/nonmatchings/71E10/func_800714E8.s")

s32 func_80071890(void *arg0, s32 arg1) {
    u16 temp_v1;

    if ((arg0 == NULL) || (temp_v1 = (*(u16 *)((u8 *)(arg0) + (0x38))), (temp_v1 == 0))) {
        return 1;
    }
    return (s32) temp_v1 >= arg1;
}

s32 func_800718B8(s32 arg0) { extern s32 D_8009F828[]; if (arg0 < 0 || arg0 >= 0xF) return 0; return D_8009F828[arg0]; }

s32 func_800718E4(u8 *arg0) { return func_8004D690(arg0 != NULL ? *(u16 *)(arg0 + 0x3A) : 8); }

s16 func_80071914(void *arg0) {
    return arg0 ? *(s16 *)((u8 *)arg0 + 0x3C) : -1;
}
#endif
