# Failed matching attempt -- func_88208FF0

## Evidence and retry boundary

The actual no-argument caller func_8822E88C and full original owner were audited. Util_Malloc has a stale void source wrapper but actually forwards the allocator pointer in v0; existing pointer-consuming callers independently establish its result. func_88207F18 consumes a word and a byte and returns a full word loaded from its selected table. func_882322B8 is the canonical no-argument cleanup/registration wrapper. The eight-byte allocation contains a word at 0 and bytes at 4 and 5; the source state has a byte selector and 44-byte row stride, with signed halfwords at row offsets 24 and 26. These are observed data accesses, not a speculative semantic type.

The first source reproduced all 39 executable instructions, the 32-byte frame, stack spill at offset 28, and every register except the ADDU operand order at owner offset 92 (address 0x8820904C). Retail is addu a1,v1,t8; the compiler emits addu a1,t8,v1. Full ROM MD5 was cec19c256cf0857885874a75ff00cf70. This is the existing address/value operand-tie family; equivalent operand reversal is not a new supported model.

Do not repeat ordinary raw/indexed/typed aliases, declaration order, or operand spelling. A retry requires supported source/address lifetime evidence that changes the remaining allocation tie without changing the actual helper ABI.

The failed candidate was never published as matching C. Only its exact owner/declaration transaction was restored; no translation-unit snapshot or raw baseline was used. Every merged source owner remains present. The restored US build with host checks and COMPARE=1 passed, and md5sum -c baseroms/us/checksum.md5 returned OK with retail MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. That local PASS does not establish any historical remote gate provenance.

The exact-owner search found no fleet attempt for func_88208FF0, and fragment31_17B150 has no regional catalog note. The unrelated previous B09C rejection and all other regional/raw-score skips remain excluded. Full source and object evidence are retained locally in work/session-61. No tools, CI, layout, data, compiler, or verification edits were authored.

## Retained candidate source

```c
extern void *Util_Malloc(s32);
extern s32 func_88207F18(s32, u8);
extern void func_800226C0(s32);
extern void func_882322B8(void);
extern void *D_88234700;
extern void *D_8800EF54;
typedef struct unk_D_88208FF0 {
    s32 unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06[2];
} unk_D_88208FF0;

void func_88208FF0(void) {
    unk_D_88208FF0 *var_a2 = Util_Malloc(8);
    u8 *var_v1;
    u8 *var_a1;

    var_a2->unk_00 = func_88207F18(1, *(u8 *)D_88234700);
    var_v1 = D_88234700;
    var_a1 = var_v1 + *var_v1 * 44;
    var_a2->unk_04 = *(s16 *)(var_a1 + 24) - *(s16 *)(var_a1 + 26);
    var_a2->unk_05 = *(u8 *)D_88234700;
    D_8800EF54 = var_a2;
    func_800226C0(99);
    func_882322B8();
}
```

## Retained candidate object

```text
<func_88208FF0>:
    1120:	27bdffe0 	addiu	sp,sp,-32
    1124:	afbf0014 	sw	ra,20(sp)
    1128:	0c000000 	jal	0 <func_88207ED0>
			1128: R_MIPS_26	Util_Malloc
    112c:	24040008 	li	a0,8
    1130:	3c0e0000 	lui	t6,0x0
			1130: R_MIPS_HI16	D_88234700
    1134:	8dce0000 	lw	t6,0(t6)
			1134: R_MIPS_LO16	D_88234700
    1138:	24040001 	li	a0,1
    113c:	91c50000 	lbu	a1,0(t6)
    1140:	0c000000 	jal	0 <func_88207ED0>
			1140: R_MIPS_26	func_88207F18
    1144:	afa2001c 	sw	v0,28(sp)
    1148:	8fa6001c 	lw	a2,28(sp)
    114c:	3c070000 	lui	a3,0x0
			114c: R_MIPS_HI16	D_88234700
    1150:	24e70000 	addiu	a3,a3,0
			1150: R_MIPS_LO16	D_88234700
    1154:	acc20000 	sw	v0,0(a2)
    1158:	8ce30000 	lw	v1,0(a3)
    115c:	3c010000 	lui	at,0x0
			115c: R_MIPS_HI16	D_8800EF54
    1160:	24040063 	li	a0,99
    1164:	906f0000 	lbu	t7,0(v1)
    1168:	000fc080 	sll	t8,t7,0x2
    116c:	030fc023 	subu	t8,t8,t7
    1170:	0018c080 	sll	t8,t8,0x2
    1174:	030fc023 	subu	t8,t8,t7
    1178:	0018c080 	sll	t8,t8,0x2
    117c:	03032821 	addu	a1,t8,v1
    1180:	84b90018 	lh	t9,24(a1)
    1184:	84a8001a 	lh	t0,26(a1)
    1188:	03284823 	subu	t1,t9,t0
    118c:	a0c90004 	sb	t1,4(a2)
    1190:	8cea0000 	lw	t2,0(a3)
    1194:	914b0000 	lbu	t3,0(t2)
    1198:	a0cb0005 	sb	t3,5(a2)
    119c:	0c000000 	jal	0 <func_88207ED0>
			119c: R_MIPS_26	func_800226C0
    11a0:	ac260000 	sw	a2,0(at)
			11a0: R_MIPS_LO16	D_8800EF54
    11a4:	0c000000 	jal	0 <func_88207ED0>
			11a4: R_MIPS_26	func_882322B8
    11a8:	00000000 	nop
    11ac:	8fbf0014 	lw	ra,20(sp)
    11b0:	27bd0020 	addiu	sp,sp,32
    11b4:	03e00008 	jr	ra
    11b8:	00000000 	nop

```
