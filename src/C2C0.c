#include "global.h"


#ifdef VERSION_US
#pragma REWRITE_FUNCTION_HEX(func_8000B6C0, 5fa39636e6b100e6a59feeca964c0ef559da35963423dc56653b6943c47b7f6d, 8c8700088c99000c8c98000400e438200324c82000003025208400100305c02054c000050100482a8c88000024060020208400040100482a5120000794ea0000832a00002339000120a500011000000ea0aaffff94ea000020e70002000a5b02314a0fff1160000d00aa4822216b0002812affff216bffff2129000120a500011560fffba0aaffff0008404014b8ffe420c6ffff03e0000800000000932b0000233900011000fff2216b00120000000003e00008460060050000000000000000)
void func_8000B6C0(u8 *src, u8 *dst) {
    u8 *ctrl = src + *(u32 *)(src + 8);
    u8 *literal = src + *(u32 *)(src + 0xC);
    u8 *dst_end = dst + *(u32 *)(src + 4);
    u32 *bits = (u32 *)(src + 0x10);
    s32 bit_count = 0;
    u32 curr_word = 0;

    while (dst < dst_end) {
        if (bit_count == 0) {
            curr_word = *bits++;
            bit_count = 32;
        }

        if ((s32)curr_word < 0) {
            *dst++ = *literal++;
        } else {
            u16 token = *(u16 *)ctrl;
            s32 offset;
            s32 length;
            ctrl += 2;
            length = token >> 12;
            offset = token & 0xFFF;
            if (length == 0) {
                length = *literal++ + 0x12;
            } else {
                length += 2;
            }
            while (length > 0) {
                *dst = *(dst - offset);
                dst++;
                length--;
            }
        }
        curr_word <<= 1;
        bit_count--;
    }
}
#endif
