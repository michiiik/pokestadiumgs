#include "global.h"


#ifdef VERSION_US
s32 func_80071210(u8 *arg0) { return arg0 ? ((*(u32 *)(arg0 + 0x40) << 1) >> 31) : 0; }

s32 func_80071230(u8 *arg0) { return arg0 ? ((*(u32 *)(arg0 + 0x40) << 2) >> 31) : 0; }

s32 func_80071250(u8 *arg0) {
    s16 value = *(s16 *)(arg0 + 0x34);

    return value > 0 && value < 5;
}

extern s32 func_80071CD0(s32, s32);

s32 func_8007126C(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 >= 0xFB) {
        return 0;
    }
    if (arg0 != 0) {
        return arg2 >= *(u8 *)((u8 *)arg0 + 0x36) &&
               arg2 <= *(u8 *)((u8 *)arg0 + 0x37) &&
               func_80071CD0(arg0 + 0x14, arg1) != 0;
    } else {
        return 1;
    }
}

s32 func_800712DC(s32 arg0, void *arg1) {
    u8 value = *(u8 *)arg1;
    s32 result = 0;
    if (value <= 0) goto empty;
    result = func_8007126C(arg0, value - 1, *(u8 *)((u8 *)arg1 + 0x1D));
    goto finish;
empty:
    result = 0;
finish:
    return result;
}

typedef struct {u8 pad[0x1D];u8 value;u8 rest[0x3A];} R;
s32 func_8007131C(R *arg0){s32 result=0; s32 count=0; s32 i,j,k; R *p=arg0; while(count<6){if(p->pad[0]==0||p->pad[0]>=0xFC)break;result+=p->value;count++;p++;} for(i=0;i<count;i++)for(j=i+1;j<count;j++)for(k=j+1;k<count;k++){s32 v=arg0[i].value+arg0[j].value+arg0[k].value;if(result>=v)result=v;}return result;}

s32 func_800714E8(void *rules, R *roster) {
    s32 index_or_limit;
    s32 other_index;
    s32 team_count;
    s32 level_sum;

    // Between roster passes, the index temporary carries the chosen level limit.
    level_sum = 0;
    team_count = 0;
    while (team_count < 6) {
        if (roster[team_count].pad[0] == 0) {
            break;
        }
        team_count++;
    }
    if (team_count == 0) {
        return 0;
    }
    if ((*(u32 *)((u8 *)rules + 0x40) >> 31) != 0 && team_count < 6) {
        return 0;
    }
    for (index_or_limit = 0; index_or_limit < team_count; index_or_limit++) {
        level_sum += roster[index_or_limit].value;
        if (func_800712DC((s32)rules, &roster[index_or_limit]) == 0) {
            return 0;
        }
    }
    if ((*(u32 *)((u8 *)rules + 0x40) >> 31) != 0) {
        index_or_limit = level_sum;
    } else {
        index_or_limit = func_8007131C(roster);
    }
    if (*(u16 *)((u8 *)rules + 0x38) < index_or_limit) {
        return 0;
    }
    if (((*(u32 *)((u8 *)rules + 0x40) << 1) >> 31) == 0) {
        for (index_or_limit = 0; index_or_limit < team_count; index_or_limit++) {
            for (other_index = index_or_limit + 1; other_index < team_count; other_index++) {
                if (roster[index_or_limit].pad[0] == roster[other_index].pad[0]) {
                    return 0;
                }
            }
        }
    }
    if (((*(u32 *)((u8 *)rules + 0x40) << 2) >> 31) == 0) {
        for (index_or_limit = 0; index_or_limit < team_count; index_or_limit++) {
            u8 item = roster[index_or_limit].pad[1];
            if (item == 0) {
                continue;
            }
            for (other_index = index_or_limit + 1; other_index < team_count; other_index++) {
                if (roster[other_index].pad[1] == 0) {
                    continue;
                }
                if (item == roster[other_index].pad[1]) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

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
