#include "global.h"
#include <stdarg.h>


#ifdef VERSION_US
s32 BinArchive_Open(s32, s32, s32, s32);
extern void func_800049B8(s32);
void *func_80004B4C(s32, s32);
s32 func_800356CC(s32);
extern s32 D_80097124;
extern s32 D_80097128;
void func_8004C020(void) {
    s32 sp1C;
    s32 temp_v0;

    temp_v0 = BinArchive_Open(func_800356CC(2), 0, 2, 1);
    sp1C = temp_v0;
    D_80097124 = (s32)func_80004B4C(temp_v0, 0x41);
    D_80097128 = (s32)func_80004B4C(sp1C, 0);
    func_800049B8(sp1C);
}

void func_8004C088(s32 arg0, s32 arg1) {
    extern s32 D_80097120;
    D_80097120 = 0;
}

extern s32 main_pool_alloc(s32, s32);
extern u8* main_pool_set_func(u8*, s32, s32);
extern s32 D_80097120;
extern void Fragment_Load(s32, void *, void *);
extern u8 D_81000000[];
typedef struct TextureSelectionState {
    /* 0x00 */ s16 index;
    /* 0x02 */ s16 spacing;
    /* 0x04 */ u8* texture;
} TextureSelectionState;
extern TextureSelectionState D_80128080;
extern u8 fragment26_ROM_START[];
extern u8 fragment27_ROM_START[];
typedef union ResourceInitFlags {
    u32 raw;
    struct {
        /* 0x00 */ u16 upper;
        /* 0x02 */ u16 bits;
    } half;
} ResourceInitFlags;
s32 func_8004C09C(ResourceInitFlags flags) {
    s32 cachedState;
    s32 state;
    s32 i;

    cachedState = D_80097120;
    if (cachedState == 0) {
        if ((state = main_pool_alloc(0x22C, 0)) != 0) {
            main_pool_set_func((u8*)(u32)state, 0, (s32)func_8004C088);
            if ((*(u16*)(u32)state = flags.half.bits) & 1) {
                *(s32 *)((u8 *)(u32)state + 4) = BinArchive_Open(func_800356CC(1), 0, 1, 0);
            } else {
                *(s32 *)((u8 *)(u32)state + 4) = 0;
            }
            if (*(u16 *)(u32)state & 2) {
                *(s32 *)((u8 *)(u32)state + 8) = BinArchive_Open(func_800356CC(2), 0, 1, 0);
                *(s32 *)((u8 *)(u32)*(s32 *)((u8 *)(u32)state + 8) + 0x428) = D_80097124;
                *(s32 *)((u8 *)(u32)*(s32 *)((u8 *)(u32)state + 8) + 0x18) = D_80097128;
            } else {
                *(s32 *)((u8 *)(u32)state + 8) = 0;
            }
            for (i = 0; i < 128; i++) {
                *(s32*)((u8*)(u32)state + 0x2C + i * 4) = 0;
            }
            if (*(u16 *)(u32)state & 4) {
                *(s32 *)((u8 *)(u32)state + 0xC) = BinArchive_Open(func_800356CC(8), 0, 1, 0);
            } else {
                *(s32 *)((u8 *)(u32)state + 0xC) = 0;
            }
            if (*(u16 *)(u32)state & 8) {
                *(s32 *)((u8 *)(u32)state + 0x10) = BinArchive_Open(func_800356CC(4), 0, 1, 0);
                *(s32 *)((u8 *)(u32)state + 0x14) = BinArchive_Open(func_800356CC(0x11), 0, 1, 0);
                *(s32 *)((u8 *)(u32)state + 0x18) = BinArchive_Open(func_800356CC(0x12), 0, 1, 0);
            } else {
                *(s32 *)((u8 *)(u32)state + 0x10) = 0;
                *(s32 *)((u8 *)(u32)state + 0x14) = 0;
                *(s32 *)((u8 *)(u32)state + 0x18) = 0;
            }
            if (*(u16 *)(u32)state & 0x100) {
                *(s32 *)((u8 *)(u32)state + 0x1C) = BinArchive_Open(func_800356CC(3), 0, 1, 0);
            } else {
                *(s32 *)((u8 *)(u32)state + 0x1C) = 0;
            }
            if (*(u16 *)(u32)state & 0x10) {
                *(s32 *)((u8 *)(u32)state + 0x20) = BinArchive_Open(func_800356CC(0xD), 0, 1, 0);
            } else {
                *(s32 *)((u8 *)(u32)state + 0x20) = 0;
            }
            if (*(u16 *)(u32)state & 0x20) {
                *(s32 *)((u8 *)(u32)state + 0x24) = BinArchive_Open(func_800356CC(0xC), 0, 1, 1);
                Fragment_Load(((((u32)&D_81000000 & 0x0FF00000) >> 20) - 0x10), &fragment26_ROM_START, &fragment27_ROM_START);
            } else {
                *(s32 *)((u8 *)(u32)state + 0x24) = 0;
            }
            if (*(u16 *)(u32)state & 0x40) {
                *(s32 *)((u8 *)(u32)state + 0x28) = BinArchive_Open(func_800356CC(0xF), 0, 1, 0);
            } else {
                *(s32 *)((u8 *)(u32)state + 0x28) = 0;
            }
            D_80097120 = state;
            D_80128080.index = -1;
            D_80128080.spacing = 0;
            D_80128080.texture = NULL;
        }
    } else {
        state = cachedState;
    }
    return state;
}

extern s32 D_80097120; void func_8004C398(void) { D_80097120 = 0; }

void func_8004C3A4(s32 unused, u8 *arg1) { *(s32 *)arg1 = 0; }

s32 func_8004C3B0(s32 arg0, s32 arg1) {
    s32 result;
    u8 *entry;
    result = 0;
    if (arg0 != 0 && arg1 >= 0) {
        entry = (u8 *)((u8 *)(u32)arg0 + arg1 * 0x10 + 0x10);
        if ((u32)arg1 < (u32)*(s32 *)((u8 *)(u32)arg0 + 0xC) && entry != NULL) {
            result = *(s32 *)(entry + 8);
        }
    }
    return result;
}

s32 func_8004C3EC(s32 arg0, s32 arg1, s32 arg2) {
    s32 result;
    result = func_8004C3B0(arg0, arg1);
    if (result == 0 || arg2 == 0) {
        result = (s32)func_80004B4C(arg0, arg1);
        if (result != 0) {
            main_pool_set_func((u8*)(u32)result, arg0 + 0x18 + arg1 * 0x10, (s32)func_8004C3A4);
        }
    }
    return result;
}

extern s32 func_8004C3B0(s32, s32);
extern s32 main_pool_try_free(s32);
s32 func_8004C468(s32 arg0, s32 arg1) {
    s32 result;
    s32 value;
    result = 0;
    value = func_8004C3B0(arg0, arg1);
    if (value != 0) {
        main_pool_try_free(value);
        result = 1;
    }
    return result;
}

extern s32 D_80097120; s32 func_8004C4A4(void) { return D_80097120; }

extern s32 D_80097120; extern s32 func_8004C3EC(s32,s32,s32); s32 func_8004C4B0(s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0&&func_8004C3EC(*(s32*)((u8*)(u32)ptr+8),value,1)!=0)result=1; return result;}

extern s32 D_80097120; extern s32 func_8004C468(s32,s32); s32 func_8004C504(s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0)result=func_8004C468(*(s32*)((u8*)(u32)ptr+8),value); return result;}

extern s32 D_80097120; s32 func_8004C54C(s32 index,s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0&&index>=0xA&&index<0x80){*(s32*)((u8*)(u32)ptr+index*4+0x2C)=value; result=1;} return result;}

extern s32 D_80097120; s32 func_8004C594(s32 index,s32 value){s32 result=0; s32 ptr=D_80097120; if(ptr!=0&&*(s32*)((u8*)(u32)ptr+8)!=0&&index>0&&index<10&&value>=0){*(s32*)((u8*)(u32)ptr+index*4+0x2C)=value; result=1;} return result;}

extern char D_800A4520[];
extern s32 D_80097120;
void func_8004C5E0(s8* output, s32 capacity, s8* input) {
    s8* number;
    s8* start;
    s8* cursor;
    s32 character;
    s32 code;
    s8 formatted[12];
    character = *input;
    start = output;
    cursor = input + 1;
    if (character != 0) {
        do {
            if (character == '#') {
                code = cursor[0] - '0';
                code = cursor[1] + code * 10 - '0';
                cursor += 2;
                if (code > 0 && (number = formatted, code < 10)) {
                    sprintf((char*)formatted, D_800A4520, *(s32*)((u8*)(u32)D_80097120 + code * 4 + 0x2C));
                    if (*number != 0) {
                        do {
                            if (output - start < capacity - 1) {
                                *output++ = *number;
                            }
                            number++;
                        } while (*number != 0);
                    }
                } else if (code >= 10 && code < 128) {
                    s8* replacement = *(s8**)((u8*)(u32)D_80097120 + code * 4 + 0x2C);
                    if (replacement != NULL) {
                        s8* scan;
                        s32 value = *replacement;
                        do {
                            scan = replacement;
                            if (value == 0) {
                                break;
                            }
                            do {
                                if (output - start < capacity - 1) {
                                    *output++ = value;
                                }
                                value = scan[1];
                                scan++;
                            } while (value != 0);
                        } while (0);
                    }
                }
            } else if (output - start < capacity - 1) {
                *output++ = character;
            }
            character = *cursor++;
        } while (character != 0);
    }
    *output = 0;
}

void* func_8004C7A0(void* destination, s32 capacity, s32 archiveId, s32 entryId) {
    void* result = NULL;
    s32 table;
    u8* text;
    if (archiveId >= 0) {
        table = 0;
        switch (archiveId) {
        case 0x41:
            table = D_80097124;
            break;
        case 0:
            table = D_80097128;
            break;
        default:
            if (D_80097120 != 0) {
                table = func_8004C3B0(*(s32*)((u8*)(u32)D_80097120 + 8), archiveId);
            }
            break;
        }
        if (table != 0 && entryId >= 0 && (u32)entryId < *(u32*)(u32)table) {
            text = (u8*)(*(u32*)((u8*)(u32)table + entryId * 4 + 4) + (u32)table);
            if (destination == NULL) {
                result = text;
            } else {
                result = destination;
                func_8004C5E0(destination, capacity, (s8*)text);
            }
        }
    }
    return result;
}

extern void *func_8004C7A0(void *, s32, s32, s32);
void *func_8004C874(s32 arg0, s32 arg1) {
    return func_8004C7A0(NULL, 0, arg0, arg1);
}

void *func_8004C8A0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_8004C7A0(arg0, arg1, arg2, arg3);
}

extern s32 func_8004C3EC(s32 arg0, s32 arg1, s32 arg2);
#ifdef CC_CHECK
s32 func_8004C8C0(u16 arg0) {
#else
s32 func_8004C8C0(arg0)
s32 arg0;
{
#endif
    s32 sp18;
    s32 result;
    s32 i;
    s32 value;
    result = 0;
    if (D_80097120 != 0) {
        sp18 = 0;
        value = func_8004C3EC(*(s32 *)((u8 *)(u32)D_80097120 + 4), arg0, 1);
        result = sp18;
        if (value != 0) {
            i = 0;
            if (*(s32 *)(u32)value != 0) {
                do {
                    i++;
                    *(s32 *)((u8 *)(u32)value + i * 4) &= 0xFFFFF;
                } while ((u32)i < (u32)*(s32 *)(u32)value);
            }
            result = 1;
        }
    }
    return result;
}

s32 func_8004C948(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (4)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C468(temp_a0, arg0);
        }
    }
    return var_v1;
}

extern s32 func_8004C3B0(s32, s32);
s32 func_8004C990(s32 arg0, s32 arg1) {
    s32 var_v1;
    s32 temp_v0;
    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_v0 = func_8004C3B0(*(s32 *)((u8 *)(u32)D_80097120 + 4), arg0);
        if (temp_v0 != 0 && arg1 >= 0 && (u32)arg1 < (u32)*(s32 *)(u32)temp_v0) {
            var_v1 = *(s32 *)((u8 *)(u32)temp_v0 + arg1 * 4 + 4) + temp_v0 - 8;
        }
    }
    return var_v1;
}

s32 func_8004CA10(u16 *arg0) { u16 value = 0; if (arg0 != NULL) { value = *arg0; } return value; }

s32 func_8004CA24(u16 *arg0) { u16 value = 0; if (arg0 != NULL) { value = arg0[1]; } return value; }

s32 func_8004CA38(u8 *arg0) { s32 value = -1; if (arg0 != NULL) { value = arg0[4]; } return value; }

s32 func_8004CA4C(u8 *arg0) { s32 value = -1; if (arg0 != NULL) { value = arg0[5]; } return value; }

u8 *func_8004CA60(u8 *arg0) { u8 *value = NULL; if (arg0 != NULL) { value = arg0 + 8; } return value; }

s32 func_8004CA74(u8 *arg0) {
    s32 result = 0;
    if (arg0 != NULL) {
        switch (arg0[5]) {
        case 0: result = (*(u16 *)(arg0 + 2) * *(u16 *)(arg0 + 0)) / 2; break;
        case 1: result = *(u16 *)(arg0 + 2) * *(u16 *)(arg0 + 0); break;
        case 2: result = (*(u16 *)(arg0 + 2) * *(u16 *)(arg0 + 0)) * 2; break;
        case 3: result = (*(u16 *)(arg0 + 2) * *(u16 *)(arg0 + 0)) * 4; break;
        default: break;
        }
    }
    return result;
  }

extern s32 func_8004CA74(u8 *);
u8 *func_8004CB28(u8 *arg0) {
    u8 *result;
    u8 *base;
    s32 offset;
    result = NULL;
    if (arg0 != NULL && arg0[4] == 2) {
        base = func_8004CA60(arg0);
        offset = func_8004CA74(arg0);
        result = base + offset + 8;
    }
    return result;
}

extern Gfx *D_800D0510;
extern void func_800459AC(u8 *, u8, u8, u16, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80044270();

#pragma REWRITE_FUNCTION_HEX(func_8004CB7C, d4b8526f506666ff2b46afc74301a22cec76e8cfe3c67adf84b47b26fd1d07f6, 27bdfee8afb7005c8fb70128afb20048afb10044afb0004000c0802500e0882500809025afbf0064afbe0060afb60058afb50054afb40050afb3004cafa5011c12e00157000018250c00000002e02025afa201100c00000002e02025240e0400afa000ecafae00e896ef000296e80000241f040001f1c023afb800d892e40005011068231080000c00801825240100015061000c24190001240100025061000c240e0002240100035061000c240f00041000000c8fb8010410000009afa001042419000110000006afb90104240e000210000003afae0104240f0004afaf01048fb8010453000010240c2000241910000338001a0000601217000002000000000007000d2401ffff170100043c01800017210002000000000006000d1000000200000000240c2000104000690000000005810002018008212581000100016043148000323c040000248400008c8300003c0ffd103c18e800246e0008ac8e0000ac620004ac6f0000006028258c8300003c0ff50035ef010024790008ac990000ac600004ac780000006030258c8300003c190700246e0008ac8e0000ac790004ac6f0000006038258c8300003c0ee6003c19f00024780008ac980000ac600004ac6e0000006048258c8300003c1807033718c000246f0008ac8f0000ac780004ac790000006050258c8300003c0fe700246e0008ac8e0000ac600004ac6f000096e8000010000032006058253c040000248400008c8300003c18fd103c0fe80024790008ac990000ac620004ac780000006028258c8300003c18f50037180100246e0008ac8e0000ac600004ac6f0000006030258c8300003c0e070024790008ac990000ac6e0004ac780000006038258c8300003c19e6003c0ef000246f0008ac8f0000ac600004ac790000006048258c8300003c0f073f35efc00024780008ac980000ac6f0004ac6e0000006050258c8300003c18e70024790008ac990000ac600004ac78000096e80000006058250188001a8fa2012c15000002000000000007000d2401ffff150100043c01800015810002000000000006000d0000f0122401fffe03c1f0242401000110410006afb200f4240100021041000a0248c823100000090000000005010003000870432501000100017043024e782310000002afaf00f4afb900f405a100028fb800d801006825070100032519ffff96ee0002afae00d897a201320019c140240efc00304f000111e0000330430002afb800ecafae00e8106000028faf00d8241ffc0019e000820000a02587b900f687af00ee000dc400afb9007c87b900ea0018740330580100001fac000015ac03afb80068afae0078afa300848fb60134afaf0074afb900708fae00d896e700008fa3008401d42023009e082a92e600051020000300e04025100000020080802503c080258faf01042602ffff11e0000b00000000011400198fae01100000c8120000000000000000032f00190000c012030e88211000000900000000011400198fb801100000c8120721000300197843272100010001784301f8882114600005afa300848fae011c000010251000000601d418218faf011c0090c82300021140032f18212463ffff92e5000424180001240e000224190002afb90020afae001cafb80014afa300f0afa200e4afa00030afa0002cafa00028afa00024afa00018afb000100c000000022020258fa300f08fa200e40010940000038c008faf00748fb8007000118c030012940300029c0000139c0300123c0000112c0000052c0300073c03afb3001487a4007e87a6007aafb5001cafb60020afaf00100c000000afb800188fae00688faf00ec2418000511c0001600112c0096e80000030f70238fb800f48faf00e82519ffff01d91004011820210004240000123c0000083400000fc823afb900180006340300073c0300042403afa20010afb60020afb5001cafb300140c00000000052c038fae00d8029ea021028e082a5420ff908fae00d8240300018fbf00648fb000408fb100448fb200488fb3004c8fb400508fb500548fb600588fb7005c8fbe006027bd011803e0000800601025)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_8004CB7C, 0x48, 4, func_8004CA60)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_8004CB7C, 0x54, 4, func_8004CB28)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_8004CB7C, 0x144, 5, D_800D0510)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_8004CB7C, 0x148, 6, D_800D0510)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_8004CB7C, 0x20c, 5, D_800D0510)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_8004CB7C, 0x210, 6, D_800D0510)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_8004CB7C, 0x4c0, 4, func_800459AC)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_8004CB7C, 0x518, 4, func_80044270)
#pragma REWRITE_FUNCTION_RELOC_TARGET(func_8004CB7C, 0x580, 4, func_80044270)

s32 func_8004CB7C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u16 arg6, s32 arg7) {
    u8 *base;
    u8 *tlut;
    s32 bpp;
    s32 maxTexels;
    s32 rowsPerChunk;
    s32 xOrigin;
    s32 remainingWidth;
    s32 remainingHeight;
    s32 dsdx;
    s32 dtdy;
    s32 sStart;
    s32 tStart;
    s32 currentY;
    s32 chunkHeight;
    u8 *chunkAddr;
    s32 drawY;
    s32 width;
    s32 height;
    u8 depth;
    Gfx *g;
    u8 *arg4_ptr = (u8 *)arg4;

    if (arg4_ptr == NULL) {
        return 0;
    }

    base = func_8004CA60(arg4_ptr);
    tlut = func_8004CB28(arg4_ptr);

    dsdx = 0x400;
    sStart = 0;
    height = *(u16 *)(arg4_ptr + 2);
    width = *(u16 *)(arg4_ptr + 0);
    dtdy = 0x400;
    remainingHeight = height - arg3;
    depth = arg4_ptr[5];
    remainingWidth = width - arg2;

    switch (depth) {
    case 0:
        bpp = 0;
        break;
    case 1:
        bpp = 1;
        break;
    case 2:
        bpp = 2;
        break;
    case 3:
        bpp = 4;
        break;
    default:
        bpp = 0;
        break;
    }

    if (bpp == 0) {
        maxTexels = 0x2000;
    } else {
        maxTexels = 0x1000 / bpp;
    }

    if (tlut != NULL) {
        maxTexels /= 2;
        g = D_800D0510;
        if (depth == 0) {
            g->words.w0 = 0xFD100000;
            g->words.w1 = (u32)tlut;
            g++;
            g->words.w0 = 0xE8000000;
            g->words.w1 = 0;
            g++;
            g->words.w0 = 0xF5000100;
            g->words.w1 = 0x07000000;
            g++;
            g->words.w0 = 0xE6000000;
            g->words.w1 = 0;
            g++;
            g->words.w0 = 0xF0000000;
            g->words.w1 = 0x0703C000;
            g++;
            g->words.w0 = 0xE7000000;
            g->words.w1 = 0;
            g++;
        } else {
            g->words.w0 = 0xFD100000;
            g->words.w1 = (u32)tlut;
            g++;
            g->words.w0 = 0xE8000000;
            g->words.w1 = 0;
            g++;
            g->words.w0 = 0xF5000100;
            g->words.w1 = 0x07000000;
            g++;
            g->words.w0 = 0xE6000000;
            g->words.w1 = 0;
            g++;
            g->words.w0 = 0xF0000000;
            g->words.w1 = 0x073FC000;
            g++;
            g->words.w0 = 0xE7000000;
            g->words.w1 = 0;
            g++;
        }
        D_800D0510 = g;
        width = *(u16 *)(arg4_ptr + 0);
    }

    rowsPerChunk = (maxTexels / width) & ~1;

    if (arg5 == 1) {
        xOrigin = arg0 - (width / 2);
    } else if (arg5 == 2) {
        xOrigin = arg0 - width;
    } else {
        xOrigin = arg0;
    }

    if (remainingWidth < 0) {
        remainingWidth = width;
    }
    if (remainingHeight < 0) {
        remainingHeight = *(u16 *)(arg4_ptr + 2);
    }

    if (arg6 & 1) {
        sStart = (width - 1) << 5;
        dsdx = -0x400;
    }
    if (arg6 & 2) {
        dtdy = -0x400;
    }

    if (remainingHeight > 0) {
        currentY = 0;
        while (currentY < remainingHeight) {
            if (remainingHeight - currentY < rowsPerChunk) {
                chunkHeight = remainingHeight - currentY;
            } else {
                chunkHeight = rowsPerChunk;
            }

            if (bpp != 0) {
                chunkAddr = base + (width * currentY) * bpp;
            } else {
                chunkAddr = base + (width * currentY) / 2;
            }

            if (arg6 & 2) {
                tStart = (chunkHeight - 1) << 5;
                drawY = (remainingHeight - currentY - chunkHeight) + arg1 - 1;
            } else {
                tStart = 0;
                drawY = arg1 + currentY;
            }

            func_800459AC(chunkAddr, arg4_ptr[4], arg4_ptr[5], width, chunkHeight, 1, 0, 2, 2, 0, 0, 0, 0);
            func_80044270((s16)xOrigin, (s16)drawY, (s16)remainingWidth, (s16)chunkHeight, (s16)sStart, (s16)tStart, (s16)dsdx, (s16)dtdy, arg7);

            if (arg6 & 0x100) {
                func_80044270((s16)(remainingWidth + xOrigin), (s16)drawY, (s16)remainingWidth, (s16)chunkHeight, (s16)((width - 1) << (5 - sStart)), (s16)tStart, (s16)-dsdx, (s16)dtdy, arg7);
            }

            currentY += rowsPerChunk;
        }
    }

    return 1;
}
s32 func_8004D150(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    return func_8004CB7C(arg0, arg1, 0, 0, arg2, arg3, (s32) (u16) arg4, arg5);
}

extern s32 func_8004D150(s32, s32, s32, s32, s32, s32);
s32 func_8004D19C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    return func_8004D150(a0, a1, a2, a3, 0, a4);
}

void func_8004D1C4(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    func_8004CB7C(a0, a1, a2, a3, a4, a5, 0, a6);
}

extern void func_800459AC(u8*, u8, u8, u16, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_8004D1FC(u8 *arg0) {
    s32 sp4C;

    sp4C = 0;
    if (arg0 != NULL) {
        sp4C = 1;
        func_800459AC(func_8004CA60(arg0), (*(u8 *)((u8 *)(arg0) + (4))), (*(u8 *)((u8 *)(arg0) + (5))), (*(u16 *)((u8 *)(arg0) + (0))), (s32) (*(u16 *)((u8 *)(arg0) + (2))), 1, 0, 2, 2, 0, 0, 0, 0);
    }
    return sp4C;
}

extern void func_80045DB4(u8 *, s32, s32, u8, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_8004D27C(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp54;
    sp54 = 0;
    if (arg0 != NULL) {
        sp54 = 1;
        func_80045DB4(func_8004CA60(arg0), arg1, arg2,
                      *(u8 *)(arg0 + 4), (s32)*(u8 *)(arg0 + 5),
                      (s32)*(u16 *)(arg0 + 0), (s32)*(u16 *)(arg0 + 2),
                      1, 0, 2, 2, 0, 0, 0, 0);
    }
    return sp54;
}

s32 func_8004D314(s32 arg0, s32 arg1) { s32 result = -1; if (arg0 == 0xEF && arg1 == 0) result = 0; return result; }

s32 func_8004D334(s32 archive, s32 entry) {
    s32 result;
    result = 0;
    D_80128080.texture = (u8*)func_8004C990(archive, entry);
    if (D_80128080.texture != NULL && *(s32*)((u8*)(u32)D_80097120 + 4) != 0) {
        D_80128080.index = func_8004D314(archive, entry);
        if (D_80128080.index >= 0) {
            result = 1;
            func_800459AC(func_8004CA60(D_80128080.texture),
                           D_80128080.texture[4], D_80128080.texture[5], *(u16*)D_80128080.texture,
                           (s32)*(u16*)(D_80128080.texture + 2), 1, 0, 2, 2, 0, 0, 0, 0);
        }
    }
    return result;
}

extern s16 D_80128082;

void func_8004D40C(s32 arg0) {
    D_80128082 = (s16)arg0;
}

extern void *memcpy(void *, const void *, s32); void *func_8004D418(void *dest, const void *src, s32 size) { return (u8 *)memcpy(dest, src, size) + size; }

extern s8 *D_80097140[];
s32 func_8004D43C(s32 arg0, s32 arg1)
{
  s8 *base = D_80097140[arg0];
  s32 result = -1;
  s8 *p = base;
  if ((*p) != 0)
  {
    do
    {
      if (arg1 == (*p))
      {
        result = p - base;
      }
      p++;
    }
    while ((*p) != 0);
  }
  return result;
}

extern s16 D_8009712C[];
extern void func_80044270();
void func_8004D488(s32 x, s32 y, u8* text) {
    s32 width = D_8009712C[D_80128080.index];
    u32 character = *text;
    u8* cursor = text + 1;
    s32 glyph;
    u32 nextCharacter;
    if (character != 0) {
        do {
            glyph = func_8004D43C(D_80128080.index, character);
            if (glyph >= 0) {
                func_80044270((s16)x, (s16)y, (s16)width,
                              *(s16*)(D_80128080.texture + 2),
                              (width * glyph) << 5, 0, 0x400, 0x400, 0);
            }
            nextCharacter = *cursor;
            x += width;
            if (nextCharacter != 0) {
                x += D_80128080.spacing;
            }
            character = nextCharacter;
            cursor++;
        } while (character != 0);
    }
}

s32 func_8004D570(s32 arg0, s32 arg1, u8 *arg2) {
    s32 result = 0;
    s32 width = D_8009712C[arg0];
    u8 value = *arg2;
    u8 *cursor = arg2 + 1;
    while (value != 0) {
        value = *cursor++;
        result += width + arg1;
    }
    if (result != 0) {
        result -= arg1;
    }
    return result;
}

extern s32 _Printf(void* (*)(void*, const void*, s32), void*, const char*, va_list);
extern void func_8004D488(s32, s32, u8*);
void func_8004D5B8(s32 x, s32 y, s32 alignment, const char* format, ...) {
    char text[256];
    va_list args;
    s32 length;
    if (D_80128080.index >= 0) {
        va_start(args, format);
        length = _Printf(func_8004D418, text, format, args);
        va_end(args);
        if (length > 0) {
            text[length] = 0;
            switch (alignment) {
            case 1:
                x -= func_8004D570(D_80128080.index, D_80128080.spacing, (u8*)text) / 2;
                break;
            case 2:
                x -= func_8004D570(D_80128080.index, D_80128080.spacing, (u8*)text);
                break;
            }
            func_8004D488(x, y, (u8*)text);
        }
    }
}

extern s32 D_80097120;
extern s32 func_8004C3EC(s32, s32, s32);
s32 func_8004D690(s32 value) { s32 result = 0; s32 ptr = D_80097120; if (ptr != 0 && *(s32 *)((u8 *)(u32)ptr + 0xC) != 0) result = func_8004C3EC(*(s32 *)((u8 *)(u32)ptr + 0xC), value, 1); return result; }

extern s32 func_8004C468(s32, s32);
s32 func_8004D6D8(s32 value) { s32 result = 0; s32 ptr = D_80097120; if (ptr != 0 && *(s32 *)((u8 *)(u32)ptr + 0xC) != 0) result = func_8004C468(*(s32 *)((u8 *)(u32)ptr + 0xC), value); return result; }

extern void func_80003F74(u8*, u8*, u8*, s32);
u8* func_8004D720(u8* destination, s32 id, s32 alternate, s32 variant) {
    u8* result = NULL;
    u8* normalArchive = *(u8**)((u8*)(u32)D_80097120 + 0x10);
    u8* alternateArchive = *(u8**)((u8*)(u32)D_80097120 + 0x14);
    u8* specialArchive = *(u8**)((u8*)(u32)D_80097120 + 0x18);
    u8* entry;
    u8* start;
    u8* end;
    if (normalArchive != NULL && alternateArchive != NULL && specialArchive != NULL) {
        if (id > 0 && id < 0x118) {
            if (id == 0xEB) {
                entry = (u8*)((u32)specialArchive + (u32)variant * 0x10);
                start = (u8*)(*(u32*)(specialArchive + 4) + *(u32*)(entry + 0x10));
                end = *(u32*)(entry + 0x14) + start;
            } else if (alternate != 0) {
                entry = (u8*)((u32)alternateArchive + (u32)id * 0x10);
                start = (u8*)(*(u32*)(alternateArchive + 4) + *(u32*)entry);
                end = *(u32*)(entry + 4) + start;
            } else {
                entry = (u8*)((u32)normalArchive + (u32)id * 0x10);
                start = (u8*)(*(u32*)(normalArchive + 4) + *(u32*)entry);
                end = *(u32*)(entry + 4) + start;
            }
            func_80003F74(destination, start, end, 0);
            result = destination;
        }
    }
    return result;
}

typedef union S1_arg1_func_80010CA8 {
    struct {
        /* 0x00 */ s16 unk_00;
        /* 0x02 */ s8 unk_02;
        /* 0x03 */ s8 unk_03;
    };
    u32 raw;
} S1_arg1_func_80010CA8;
void PokeIcon_AdjustImageColors(u16* arg0, s32 a1, S1_arg1_func_80010CA8 arg2) {
    s32 cond;
    s32 arg1 = a1;

    if (!arg0) {}

    arg1 *= 2;
    osInvalDCache(arg0, arg1);

    cond = arg1 >= 2;
    arg1 -= 2;
    // clang-format off
    while (cond != 0) {
        *arg0 = Color_AdjustRGB5551(*arg0, arg2);        cond = arg1 >= 2;        arg1 -= 2;
        arg0++;
    }
    // clang-format on
}

typedef struct Result_8004B9E0 {
    s32 value;
} Result_8004B9E0;
typedef union ResourceIconTint {
    S1_arg1_func_80010CA8 tint;
    Result_8004B9E0 result;
} ResourceIconTint;
extern S1_arg1_func_80010CA8 func_8003F5AC(u8*);
extern s32 func_80064728(u8*);
extern s32 func_8003F954(u16);
extern s32 func_8006456C(s32);
extern s32 func_8004B98C(s32);
extern Result_8004B9E0 func_8004B9E0(s32);
typedef struct ResourceIconWork {
    s32 mode;
    ResourceIconTint color;
    s32 variant;
} ResourceIconWork;
u8* func_8004D878(u8* destination, s32 id, u8* mon) {
    u8* result = NULL;
    ResourceIconWork* selected;
    ResourceIconWork work;
    u8* record;
    work.variant = 0;
    if (D_80097120 != 0) {
        if (mon == NULL) {
            result = func_8004D720(destination, id, 0, 0);
        } else {
            work.color.tint = func_8003F5AC(mon);
            work.mode = 0;
            id = func_80064728(mon);
            if (id == 0xEB) {
                work.variant = func_8003F954(*(u16*)(mon + 0x16));
            }
            if (func_8006456C(*(u16*)(mon + 0x16)) != 0) {
                work.mode = func_8004B98C(id);
                switch (work.mode) {
                case 1:
                    work.color.tint.raw = 0;
                    break;
                case 2:
                    work.color.result = func_8004B9E0(id);
                    break;
                }
            }
            selected = &work;
            record = mon;
            result = func_8004D720(destination, func_80064728(record), selected->mode == 1, selected->variant);
            if (result != NULL && selected->color.tint.raw != 0) {
                PokeIcon_AdjustImageColors((u16*)destination, 0x640, selected->color.tint);
            }
        }
    }
    return result;
}

extern void Gfx_DrawTextureRgba16(s16, s16, s16, s16, u8 *, s16, s32);
void func_8004D998(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4) {
    s32 var_v0;

    var_v0 = arg0;
    if (arg2 != NULL) {
        switch (arg3) {
        case 1:
            var_v0 = arg0 - 0x14;
            break;
        case 2:
            var_v0 = arg0 - 0x28;
            break;
        }
        Gfx_DrawTextureRgba16((s16)var_v0, (s16)arg1, 0x28, 0x28, arg2, 0x28, arg4);
    }
}

s32 func_8004C8C0(u16);
s32 func_8004DA18(void *arg0) {
    s32 var_s0;

    var_s0 = 1;
    if (func_8004C8C0((*(u16 *)((u8 *)(arg0) + (0x18)))) == 0) {
        var_s0 = 0;
    }
    if (func_8004C8C0((*(u16 *)((u8 *)(arg0) + (0x1C)))) == 0) {
        var_s0 = 0;
    }
    if (func_8004C8C0((*(u16 *)((u8 *)(arg0) + (0x20)))) == 0) {
        var_s0 = 0;
    }
    if (func_8004C8C0((*(u16 *)((u8 *)(arg0) + (0x24)))) == 0) {
        var_s0 = 0;
    }
    return var_s0;
}

extern s32 func_8004C8C0(u16); extern s32 func_8004DD1C(s32);
s32 func_8004DA8C(u8 *arg0) {
    s32 result = 1;
    if (arg0[0x15] == 0) {
        if (func_8004C8C0(*(u16 *)(arg0 + 0x10)) == 0) result = 0;
    } else if (func_8004DD1C(*(u16 *)(arg0 + 0x12)) == 0) {
        result = 0;
    }
    return result;
}

extern s32 func_8004EB1C(s32);

s32 func_8004DAF0(void *arg0, s32 *arg1) {
    struct {
        s32 unused;
        s32 value;
    } result;
    s32 flags;

    result.value = 1;
    flags = func_8004EB1C(*(s32 *)((u8 *)arg0 + 0x10));
    if (func_8004C4B0(*(u16 *)((u8 *)arg0 + 0x20)) == 0) {
        result.value = 0;
    }
    if (arg1 != NULL) {
        *arg1 |= flags;
    }
    return result.value;
}

extern u16 func_8004EB38(u16*);
extern s32 func_8004EB40(u16*);
s32 func_8004DB5C(u8* cursor, s32* errors) {
    s32 result = 1;
    u8* scan = cursor;
    u16 kind;
    if (errors != NULL) {
        *errors = 0;
    }
    kind = func_8004EB38((u16*)cursor);
    if (kind != 0) {
        do {
            switch (kind) {
            case 0x11:
                if (func_8004DA18(scan) == 0 && result != 0) {
                    result = 0;
                }
                break;
            case 0x12:
                if (func_8004DA8C(scan) == 0 && result != 0) {
                    result = 0;
                }
                break;
            case 0x13:
                if (func_8004DAF0(scan, errors) == 0 && result != 0) {
                    result = 0;
                }
                break;
            }
            scan += func_8004EB40((u16*)scan);
            kind = func_8004EB38((u16*)scan);
        } while (kind != 0);
    }
    return result;
}

s32 func_8004DC6C(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x1C)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C3EC(temp_a0, arg0, 1);
        }
    }
    return var_v1;
}

s32 func_8004DCB4(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x1C)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C468(temp_a0, arg0);
        }
    }
    return var_v1;
}

void func_8004DCFC(u8* cursor, s32* errors) {
    func_8004DB5C(cursor, errors);
}

s32 func_8004DD1C(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x20)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C3EC(temp_a0, arg0, 1);
        }
    }
    return var_v1;
}

s32 func_8004DD64(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x20)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C468(temp_a0, arg0);
        }
    }
    return var_v1;
}

s32 func_8004C3B0(s32, s32);

s32 func_8004DDAC(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x20)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C3B0(temp_a0, arg0);
        }
    }
    return var_v1;
}

s32 func_8004DDF4(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = (*(s32 *)((u8 *)(D_80097120) + (0x24)));
        if (temp_a0 != 0) {
            var_v1 = func_8004C3EC(temp_a0, arg0, 0);
        }
    }
    return var_v1;
}

extern s32 func_80004B78(s32, s32, s32);
s32 func_8004DE3C(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 var_v1;
    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a1 = *(s32 *)((u8 *)(D_80097120) + 0x24);
        if (temp_a1 != 0) {
            var_v1 = func_80004B78(arg0, temp_a1, arg1);
        }
    }
    return var_v1;
}

extern s32 D_80097120;
extern s32 func_8004C3B0(s32, s32);
typedef struct HandlerResult_DE84D { u8 pad[8]; s32 *table; } HandlerResult_DE84D;
s32 func_8004DE84(s32 arg0, s32 arg1) {
    s32 var_v1;
    s32 temp_a0;
    s32 temp_v0;
    var_v1 = 0;
    if (D_80097120 != 0) {
        temp_a0 = *(s32 *)((u8 *)(u32)D_80097120 + 0x24);
        if (temp_a0 != 0) {
            temp_v0 = func_8004C3B0(temp_a0, arg0);
            if (temp_v0 != 0) {
                var_v1 = ((HandlerResult_DE84D *(*)(s32, s32))(u32)temp_v0)(0, 0)->table[arg1];
            }
        }
    }
    return var_v1;
}

void func_8004DEF8(s32 arg0) {
    func_8004DE84(arg0, 0);
}

extern u8* func_8004DF38(s32, s32, s32);
void WidgetTree_RunMessagePanelSilent(s32 arg0, s32 arg1) {
    func_8004DF38(arg0, arg1, 0);
}

extern u8* process_geo_layout(s32, void*);
u8* func_8004DF38(s32 pool, s32 id, s32 index) {
    u8* result = NULL;
    HandlerResult_DE84D* descriptor;
    s32 archive;
    s32 callback;
    s32 entry;

    entry = func_8004DE84(id, index);
    if (entry != 0) {
        archive = *(s32*)((u8*)(u32)D_80097120 + 0x24);
        result = process_geo_layout(pool, (void*)(u32)entry);
        if (result != NULL) {
            callback = func_8004C3B0(archive, id);
            descriptor = ((HandlerResult_DE84D* (*)(s32,s32))(u32)callback)(0, 0);
            *(s32*)(result + 0x2C) = callback;
            if (index < ((u8*)descriptor)[3]) {
                descriptor->table[index] = (s32)result;
            }
        }
    }
    return result;
}

typedef struct { void *value; } Func8004DFECArg;
extern void *func_8004E018(s32 arg0, s32 arg1, s32 arg2, Func8004DFECArg arg3);
void *func_8004DFEC(s32 arg0, s32 arg1, Func8004DFECArg arg2) {
    return func_8004E018(arg0, arg1, 0, arg2);
}

extern u8* process_geo_layout(s32, void*);
extern void Model_AdjustTextureColors(u8*, Func8004DFECArg);
void* func_8004E018(s32 pool, s32 id, s32 index, Func8004DFECArg tint) {
    s32 entry;
    u8* result = NULL;
    s32 archive;
    s32 callback;
    HandlerResult_DE84D* descriptor;
    entry = func_8004DE84(id, index);
    if (entry != 0) {
        archive = *(s32*)((u8*)(u32)D_80097120 + 0x24);
        result = process_geo_layout(pool, (void*)(u32)entry);
        if (result != NULL) {
            callback = func_8004C3B0(archive, id);
            descriptor = ((HandlerResult_DE84D* (*)(s32,s32))(u32)callback)(0, 0);
            *(s32*)(result + 0x2C) = callback;
            if (tint.value != NULL) {
                Model_AdjustTextureColors(result, tint);
            }
            if (index < ((u8*)descriptor)[3]) {
                descriptor->table[index] = (s32)result;
            }
        }
    }
    return result;
}

u8* func_8004E0F0(u8* destination, s32 id, s32 index) {
    s32 allocated = 0;
    s32 loaded = 0;
    u32 archiveAddress;
    s32 lookup;
    u8* chunk;
    u8* end;
    s32* header;
    if (D_80097120 != 0) {
        lookup = *(s32*)((u8*)(u32)D_80097120 + 0x28);
        if (lookup != 0) {
            archiveAddress = (u32)lookup;
            lookup = (u32)id;
            if (destination == NULL) {
                destination = (u8*)(u32)main_pool_alloc(0x2008, 0);
                allocated = 1;
            }
            if (destination != NULL && id >= 0 && (u32)lookup < (u32)*(s32*)((u8*)(u32)archiveAddress + 0xC)) {
                chunk = (u8*)(u32)(*(s32*)((u32)archiveAddress + (u32)id * 0x10 + 0x10) + *(s32*)((u8*)(u32)archiveAddress + 4));
                header = (s32*)(u32)main_pool_alloc(0x10, 1);
                if (header != NULL) {
                    end = chunk + 0x10;
                    func_80003F74((u8*)header, chunk, end, 0);
                    if (index >= 0 && index < header[0]) {
                        u8* start = *(s32*)((u8*)header + index * 4 + 4) + chunk - 8;
                        end = start;
                        end = end + 0x2008;
                        func_80003F74(destination, start, end, 0);
                        loaded = 1;
                    }
                    main_pool_try_free((s32)header);
                }
            }
            if (loaded == 0) {
                if (allocated != 0) {
                    main_pool_try_free((s32)destination);
                }
                destination = NULL;
            }
        }
    }
    return destination;
}
/* Original owner ends with three alignment NOPs after the return delay slot. */
#pragma C_FUNCTION_PADDING(12)
#endif
