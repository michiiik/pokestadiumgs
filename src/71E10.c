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

#pragma REWRITE_FUNCTION_HEX(func_800714E8, b1011ff6da5c7087c98b149e46a5ffa6731dfc191d54ee89fcca4f2e9098708a, 27bdffb8afb0001800a08025afbf001c00803825000030250000402500a0102524030006904e000011c0000400000000250800011503fffb24420058550000048ce20040100000d3000010258ce2004029010006000217c210400005000000001020000300000000100000ca000010251900001c000018250200502502002825afa70048914f001d8fa40048afaa002400cf3021afa60038afa8003cafa500280c000000afa300448fa300448fa500288fa600388fa8003c144000038faa0024100000b40000102524630001254a00581468ffec24a500588fa700488ce20040000217c210400003020020251000000700c01825afa700480c000000afa8003c8fa8003c004018258fa7004894f900380323082a502000048ce600401000009d000010258ce600400006604005820042000678801900003f00001825246900010128082a10200039012020250003688001a36823000d688001a368230109382330e70003000d68c010e00012020d50210004708001c47023000e708001c47023000e70c0020e182100e9282191420000906f000024840001144f0003000000001000007c0000102514a4fff9246300581088001e0004c0800304c0230018c0800304c0230018c0c00218182191420000907900002484000454590004906b00581000006c00001025906b0058544b0004906c00b01000006700001025906c00b0544c0004906d01081000006200001025906d0108144d0003000000001000005d000010251488ffea246301601528ffc3012018250006788005e200562402000119000053000018250200502591450001246900010128082a14a0000300000000100000482469000110200046012020250109382330e7000310e0001200e930210004c0800304c0230018c0800304c0230018c0c0021818219062000124840001104000050000000014a2000300000000100000380000102514c4fff724630058108800300004c8800324c8230019c8800324c8230019c8c00219182190620001504000069062005954a200049062005910000028000010259062005950400006906200b154a20004906200b11000002100001025906200b1504000069062010954a20004906201091000001a000010259062010900085880016858231440000624630160000b588001685823000b58c01000000a0170102114a20003000860801000000c0000102501886023000c608001886023000c60c0019010215462ffd890620001012018251528ffb0254a0058240200018fbf001c8fb0001827bd004803e0000800000000)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_800714E8, 0xa0, 4, func_800712DC)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_800714E8, 0xf8, 4, func_8007131C)
s32 func_800714E8(void *arg0, R *arg1) {
    s32 count = 0;
    s32 sum = 0;
    s32 i, j;
    s32 limit;
    u32 rule_flags;

    while (count < 6) {
        if (arg1[count].pad[0] == 0) {
            break;
        }
        count++;
    }

    if (count == 0) {
        return 0;
    }

    rule_flags = *(u32 *)((u8 *)arg0 + 0x40);
    if ((rule_flags >> 31) && (count < 6)) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        sum += arg1[i].value;
        if (!func_800712DC((s32)arg0, &arg1[i])) {
            return 0;
        }
    }

    if (rule_flags >> 31) {
        limit = sum;
    } else {
        limit = func_8007131C(arg1);
    }

    if (*(u16 *)((u8 *)arg0 + 0x38) < limit) {
        return 0;
    }

    if (!((s32)(rule_flags << 1) < 0)) {
        for (i = 0; i < count; i++) {
            for (j = i + 1; j < count; j++) {
                if (arg1[i].pad[0] == arg1[j].pad[0]) {
                    return 0;
                }
            }
        }
    }

    if (!((s32)(rule_flags << 2) < 0)) {
        for (i = 0; i < count; i++) {
            u8 item = arg1[i].pad[1];
            if (item != 0) {
                for (j = i + 1; j < count; j++) {
                    if (arg1[j].pad[1] != 0 && item == arg1[j].pad[1]) {
                        return 0;
                    }
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
