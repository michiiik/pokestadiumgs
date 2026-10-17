#include "global.h"


#ifdef VERSION_US
void func_80073080(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    u8 *temp_v0;

    temp_v0 = (u8 *)((u32)arg0 + (arg1 * 0x1DC));
    temp_v0[0x1D4] = arg2;
    temp_v0[0x1D5] = arg3;
    temp_v0[0x1D6] = arg4;
}

extern u8 *func_80060EC8(void *, void *);
extern void func_80051864(s32, s32);
typedef struct RosterCopy730BC { s32 words[17]; } RosterCopy730BC;
typedef struct { u32 words[22]; } WholeCopySource88;
typedef struct { u32 words[15]; } WholeCopyDestination60;
typedef struct {
    u8 unk_00[11];
    u8 unk_0B;
    u8 unk_0C;
    u8 unk_0D[23];
    u16 unk_24;
    u8 unk_26[2];
    WholeCopyDestination60 entries[6];
    u8 unk_190[76];
} WholeCopyDestination476;
typedef struct {
    WholeCopyDestination476 sides[2];
    u8 unk_3B8[108];
    RosterCopy730BC config;
} WholeCopyDestination1128;
typedef struct {
    WholeCopySource88 entries[2][6];
    u8 unk_420[1060];
    RosterCopy730BC *config;
    u8 unk_848[8];
    u8 names[2][12];
    u8 unk_868[24];
    s16 signed_fields[2][2];
    u8 unk_888[12];
    u16 side_fields[2];
} WholeCopySource2200;
typedef char WholeCopySourceSizeCheck[sizeof(WholeCopySource2200)==2200?1:-1];
typedef char WholeCopyDestinationSizeCheck[sizeof(WholeCopyDestination1128)==1128?1:-1];
void func_800730BC(WholeCopyDestination1128 *arg0, WholeCopySource2200 *arg1) {
    s32 side;
    s32 slot;
    for (side = 0; side != 2; side++) {
        func_80060EC8(&arg0->sides[side], arg1->names[side]);
        for (slot = 0; slot != 6; slot++) {
            func_80051864((s32)&arg1->entries[side][slot], (s32)&arg0->sides[side].entries[slot]);
        }
        arg0->sides[side].unk_0B = arg1->signed_fields[side][0];
        arg0->sides[side].unk_0C = arg1->signed_fields[side][1];
        arg0->sides[side].unk_24 = arg1->side_fields[side];
    }
    arg0->config = *arg1->config;
}

extern void func_80051830(void *, void *);
extern void func_80060E48(void *, void *);
void func_80073208(u8 *arg0, u8 *arg1) {
    s32 side;
    s32 filled;
    u32 selected;
    // Selected pass: destination address. Fill pass: source slot index.
    s32 address_or_index;
    u8 mask;
    for (side = 0; side != 2; side++) {
        mask = 0;
        (arg0 + side * 1248)[2] = 1;
        (arg0 + side * 1248)[3] = 3;
        (arg0 + side * 1248)[7] = 6;
        (arg0 + side * 1248)[8] = 3;
        (arg0 + side * 1248)[10] = 0;
        (arg0 + side * 1248)[4] = side;
        (arg0 + side * 1248)[5] = side;
        filled = 0;
        for (; filled != 3; filled++) {
            address_or_index = (s32)((arg0 + side * 1248) + 24 + filled * 88);
            selected = (arg1 + side * 476)[0x1D4 + filled];
            func_80051830((void *)address_or_index, (u32 *)(arg1 + side * 476) + selected * 15 + 10);
            mask |= 1 << selected;
        }
        while (filled < 6) {
            for (address_or_index = 0; address_or_index != 6; address_or_index++) {
                if (!(mask & (1U << address_or_index))) {
                    func_80051830((arg0 + side * 1248) + 24 + filled * 88, (u32 *)(arg1 + side * 476) + address_or_index * 15 + 10);
                    mask |= (1U << address_or_index);
                    break;
                }
            }
            filled++;
        }
        func_80060E48(arg0 + side * 1248 + 0x48C, (arg1 + side * 476));
    }
}

typedef struct Copy73394 {
    s32 words[17];
} Copy73394;

void func_80073394(u8 *arg0, u8 *arg1, u8 arg2, u8 arg3) {
    u8 *src;
    u8 *dst;

    src = (u8 *)((u32)arg1 + (arg3 * 0x1DC));
    dst = (u8 *)((u32)arg0 + (arg2 * 0x4E0));
    *(Copy73394 *)(dst + 0x49C) = *(Copy73394 *)(src + 0x190);
    dst[0x49A] = 0xFF;
}
#endif
