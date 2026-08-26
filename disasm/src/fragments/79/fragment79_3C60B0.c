#include "global.h"


#ifdef VERSION_US
extern void func_84169B80(void);
extern void _bzero(void *, s32);
extern u8 D_8419F070[];
void func_84156820(void) {
    func_84169B80();
    _bzero(D_8419F070, 0x5C90);
}
void func_84156820_padding(void) {}
void func_84156820_padding2(void) {}
#endif

#ifdef VERSION_US
s32 func_84156860(void) {
    return -1;
}
#endif

#ifdef VERSION_US
s32 func_84156868(void) {
    return -1;
}
#endif

#ifdef VERSION_US
void func_84156870(void) {}
void func_84156870_padding(void) {}
#endif

#ifdef VERSION_US
void func_84156880(void) { func_841098C0(); }
#endif

#ifdef VERSION_US
void func_841568A0(void) { func_84109780(); }
#endif

#ifdef VERSION_US
void func_841568C0(void) { func_841098C0(); }
#endif

#ifdef VERSION_US
void func_841568E0(void) { func_84109884(); }
#endif

#ifdef VERSION_US
void func_84156900(void) { func_84109590(); }
#endif

#ifdef VERSION_US
void func_84156920(void) { func_84109544(); }
#endif

#ifdef VERSION_US
void func_84156940(void) { func_841094F8(); }
#endif

#ifdef VERSION_US
void func_84156960(void) { func_8410971C(); }
#endif

#ifdef VERSION_US
void func_84156980(void) { func_84109848(); }
#endif

#ifdef VERSION_US
void func_841569A0(void) { func_841095DC(); }
#endif

#ifdef VERSION_US
void func_841569C0(void) { func_84109B1C(); }
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_841569E0.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84156AB4.s")
#endif

#ifdef VERSION_US
extern u8 D_841A4D08[];
extern void func_8007D454(void *, f32, f32, f32);
void func_84156BA0(void) {
    func_8007D454(D_841A4D08, 0.0f, 0.0f, 0.0f);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84156BD4.s")
#endif

#ifdef VERSION_US
extern void func_8415AD58(void);
void func_84156C40(void) {
    func_8415AD58();
}
#endif

#ifdef VERSION_US
extern s32 D_800D0510;
extern s32 func_8415ADE0();
void func_84156C60(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415ADE0(D_800D0510);
}
#endif

void func_84156CB4(void) {
}

#ifdef VERSION_US
s32 func_84156CBC(void) {
    return -1;
}
#endif

void func_84156CC4(void) {
}

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84156CCC.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D4A;
extern void func_84156BA0(void);
extern void func_8415C530(void);
extern void func_84156CCC(void);
void func_84156E58(void) {
    D_841A4D4A = 0;
    func_84156BA0();
    func_8415C530();
    func_84156CCC();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84156E8C.s")
#endif

#ifdef VERSION_US
extern s32 func_8415DBBC();
void func_84156EFC(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415DBBC(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84156F50.s")
#endif

#ifdef VERSION_US
extern void func_8415BD48(s32);
void func_84156FC8(void) { func_8415BD48(0); }
#endif

#ifdef VERSION_US
extern s32 func_8415C2E0();
void func_84156FE8(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415703C.s")
#endif

#ifdef VERSION_US
void func_841570B4(void) { func_8415BD48(1); }
#endif

#ifdef VERSION_US
void func_841570D4(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157128.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D4C;
extern void func_84162660(void);
extern void func_84157128(void);
void func_841572A0(void) {
    D_841A4D4C = 0;
    func_84156BA0();
    func_84162660();
    func_84157128();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_841572D4.s")
#endif

#ifdef VERSION_US
extern s32 func_84162DE8();
void func_84157344(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84162DE8(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157398.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D4E;
extern void func_84157398(void);
void func_84157558(void) {
    D_841A4D4E = 0;
    func_84156BA0();
    func_8415C530();
    func_84157398();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415758C.s")
#endif

#ifdef VERSION_US
void func_841575FC(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415DBBC(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157650.s")
#endif

#ifdef VERSION_US
void func_841576CC(void) { func_8415BD48(0); }
#endif

#ifdef VERSION_US
void func_841576EC(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157740.s")
#endif

#ifdef VERSION_US
void func_841577B8(void) { func_8415BD48(0); }
#endif

#ifdef VERSION_US
void func_841577D8(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415C2E0(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415782C.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D52;
extern void func_8415782C(void);
void func_841579B8(void) {
    D_841A4D52 = 0;
    func_84156BA0();
    func_8415C530();
    func_8415782C();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_841579EC.s")
#endif

#ifdef VERSION_US
void func_84157A5C(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415DBBC(D_800D0510);
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D54;
extern void func_84166130(void);
void func_84157AB0(void) {
    D_841A4D54 = 0;
    func_84156BA0();
    func_84166130();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157ADC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157C58.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D56;
void func_84157CB0(void) {
    D_841A4D56 = 0;
    func_84156BA0();
    func_84166130();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157CDC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84157E58.s")
#endif

#ifdef VERSION_US
extern void func_8415F0D0(s32);
extern void func_841603A0(s32);
void func_84157EB0(void) {
    s32 temp[3];
    extern void func_841568A0();
    func_84156BA0();
    func_841568A0(temp);
    func_8415F0D0(0x708);
}
#endif

#ifdef VERSION_US
extern void func_8415F9A0(void);
void func_84157EE0(void) {
    func_8415F9A0();
}
#endif

#ifdef VERSION_US
extern s32 func_8415FD8C();
void func_84157F00(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415FD8C(D_800D0510);
}
#endif

#ifdef VERSION_US
void func_84157F54(void) {
    s32 temp[3];
    extern void func_841568A0();
    func_84156BA0();
    func_841568A0(temp);
    func_841603A0(0x708);
}
#endif

#ifdef VERSION_US
extern void func_84160CD8(void);
void func_84157F84(void) {
    func_84160CD8();
}
#endif

#ifdef VERSION_US
extern s32 func_84161018();
void func_84157FA4(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84161018(D_800D0510);
}
#endif

#ifdef VERSION_US
void func_84157FF8(void) {
    s32 temp[3];
    extern void func_841568A0();
    extern void func_841614E0(s32);
    func_84156BA0();
    func_841568A0(temp);
    func_841614E0(0x708);
}
#endif

#ifdef VERSION_US
extern void func_84161DAC(void);
void func_84158028(void) {
    func_84161DAC();
}
#endif

#ifdef VERSION_US
extern s32 func_841621A4();
void func_84158048(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_841621A4(D_800D0510);
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D00;
extern void func_841639D0(void);
void func_8415809C(void) {
    D_841A4D00 = 0;
    func_84156BA0();
    func_841639D0();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_841580C8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84158308.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D02;
extern void func_841647D0(void);
void func_84158370(void) {
    D_841A4D02 = 0;
    func_84156BA0();
    func_841647D0();
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415839C.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84158520.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84158588.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D04;
extern s32 func_84165C2C(void);
s32 func_841586C8(void) {
    (*(s16 *)&D_841A4D04) = (*(s16 *)&D_841A4D04) + 1;
    if (*(s16 *)&D_841A4D04 >= 0x32) {
        return -1;
    }
    return func_84165C2C();
}
#endif

#ifdef VERSION_US
extern s32 func_84165CC0();
void func_84158714(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84165CC0(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84158768.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D06;
extern void func_84158768(void);
void func_84158840(void) {
    D_841A4D06 = 0;
    func_84156BA0();
    func_8415C530();
    func_84158768();
}
#endif

#ifdef VERSION_US
extern s32 func_8415DAE4(void);
s32 func_84158874(void) {
    (*(s16 *)&D_841A4D06) = (*(s16 *)&D_841A4D06) + 1;
    if (*(s16 *)&D_841A4D06 >= 0xB5) {
        return -1;
    }
    return func_8415DAE4();
}
#endif

#ifdef VERSION_US
void func_841588C0(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_8415DBBC(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84158914.s")
#endif

#ifdef VERSION_US
extern void func_84166F60(void);
extern void func_84158914(void);
void func_84158BA8(void) {
    func_84156BA0();
    func_84166F60();
    func_84158914();
}
#endif

#ifdef VERSION_US
extern void func_841677C4(void);
void func_84158BD8(void) {
    func_841677C4();
}
#endif

#ifdef VERSION_US
extern s32 func_84168000();
void func_84158BF8(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84168000(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84158C4C.s")
#endif

#ifdef VERSION_US
extern u16 D_841A4D48;
extern void func_84168540(void);
extern void func_84158C4C(void);
void func_84158E24(void) {
    D_841A4D48 = 0;
    func_84156BA0();
    func_84168540();
    func_84158C4C();
}
#endif

#ifdef VERSION_US
extern s32 func_84169040(void);
s32 func_84158E58(void) {
    (*(s16 *)&D_841A4D48) = (*(s16 *)&D_841A4D48) + 1;
    if ((*(s16 *)&D_841A4D48 % 10) == 0) {
        func_84158C4C();
    }
    return func_84169040();
}
#endif

#ifdef VERSION_US
extern s32 func_84169618();
void func_84158EAC(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84169618(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84158F00.s")
#endif

#ifdef VERSION_US
extern void func_84158F00(void);
void func_84159198(void) {
    func_84156BA0();
    func_84166F60();
    func_84158F00();
}
#endif

#ifdef VERSION_US
void func_841591C8(void) {
    func_841677C4();
}
#endif

#ifdef VERSION_US
void func_841591E8(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84168000(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415923C.s")
#endif

#ifdef VERSION_US
extern void func_8415923C(void);
void func_841594E0(void) {
    func_84156BA0();
    func_84166F60();
    func_8415923C();
}
#endif

#ifdef VERSION_US
void func_84159510(void) {
    func_841677C4();
}
#endif

#ifdef VERSION_US
void func_84159530(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84168000(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84159584.s")
#endif

#ifdef VERSION_US
extern void func_84159584(void);
void func_84159708(void) {
    func_84156BA0();
    func_84166F60();
    func_84159584();
}
#endif

#ifdef VERSION_US
void func_84159738(void) {
    func_841677C4();
}
#endif

#ifdef VERSION_US
void func_84159758(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp) D_800D0510 = func_84168000(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_841597AC.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84159A50.s")
#endif

#ifdef VERSION_US
extern void func_841597AC(void);
extern void func_84159A50(void);
void func_84159C2C(void) {
    func_84156BA0();
    func_84166F60();
    func_841597AC();
    func_84168540();
    func_84159A50();
}
#endif

#ifdef VERSION_US
extern u16 D_841A4D50;
void func_84159C6C(void) {
    (*(s16 *)&D_841A4D50) = (*(s16 *)&D_841A4D50) + 1;
    if ((*(s16 *)&D_841A4D50 % 10) == 0) {
        func_84159A50();
    }
    func_84169040();
    func_841677C4();
}
#endif

#ifdef VERSION_US
void func_84159CC8(void) {
    #define EMIT_GFX(pkt) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = 0xDA380003; _g->words.w1 = (u32)&D_841A4D08; }
    s32 temp = D_800D0510; D_800D0510 += 8; EMIT_GFX(temp)
    D_800D0510 = func_84168000(D_800D0510);
    D_800D0510 = func_84169618(D_800D0510);
}
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84159D30.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_84159FA8.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415A364.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415A9E4.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415AC64.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415AD58.s")
#endif

#ifdef VERSION_US
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/79/fragment79_3C60B0/func_8415ADE0.s")
#endif
