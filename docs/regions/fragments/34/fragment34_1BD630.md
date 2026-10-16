# Failed matching attempt -- func_88500C10

## Evidence and retry boundary

The real owner has two unused incoming word homes, returns 7, and performs 15 calls. The first five arguments of func_800082E0 are signed bytes; its actual result is a pointer. main_pool_push_state and main_pool_pop_state return words; the latter returns main_pool_get_available. The current func_8004C09C definition accepts a four-byte union containing a raw word and two halfwords. The trial preserved that declared union ABI rather than substituting a scalar declaration. The two local no-argument helpers were audited in their complete original ASM. No extra incoming arguments or false return values were invented.

The ordinary union-local trial produced ROM MD5 381ceaba62d254925577e45f4baf6f1b. Its frame remains 40 bytes, but the initialized union requires a data load, a spill at stack offset 32, a reload before the call, and an outgoing aggregate home store. Those instructions are absent in retail; they also rotate the two outgoing literal temporaries. The expected pointer spill at stack offset 36 and the later call/store sequence otherwise survive. Retail has three genuine trailing padding words, represented with the existing 12-byte padding directive; padding is not the observed mismatch.

Do not repeat an ordinary initialized union or replace the current aggregate helper declaration with a convenient word prototype. A retry needs supported ABI/source evidence reconciling the canonical helper declaration with this caller's scalar-looking call sequence, followed by a full independent ROM check.

The failed candidate was never published as matching C. Only its exact owner/declaration transaction was restored; no translation-unit snapshot or raw baseline was used. Every merged source owner remains present. The restored US build with host checks and COMPARE=1 passed, and md5sum -c baseroms/us/checksum.md5 returned OK with retail MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. That local PASS does not establish any historical remote gate provenance.

The exact-owner fleet search had no attempt for this owner. Both complete fragment-34 regional notes were read; the 1BD630 catalog record is absent, and unrelated helper references were not counted as owner attempts. Full source and object evidence are retained locally in work/session-61. No tools, CI, layout, data, compiler, or verification edits were authored.

## Retained candidate source

```c
extern s32 main_pool_push_state(s32);
extern s32 main_pool_pop_state(s32);
extern void Gfx_InitDisplayListBuffers(s32, s32);
extern void Gfx_FreeDisplayListBuffers(void);
extern void *func_800082E0(s8, s8, s8, s8, s8, s32);
typedef union unk_D_88500C10 {
    u32 unk_00;
    struct {
        u16 unk_00;
        u16 unk_02;
    } unk_00_half;
} unk_D_88500C10;
extern s32 func_8004C09C(unk_D_88500C10);
extern u8 *func_80047588(s32, s32);
extern void Font_EnableLineBreak(void);
extern void func_885009D0(void);
extern void func_80008514(s32);
extern void func_8850089C(void);
extern void func_800086A4(s32);
extern void func_80008574(void);
extern void func_80047610(void);
extern void func_8004C398(void);
extern u8 *D_8800687C;

s32 func_88500C10(s32 arg0, s32 arg1) {
    void *var_v0;
    unk_D_88500C10 var_a0 = { 11 };

    main_pool_push_state(1347241304);
    Gfx_InitDisplayListBuffers(81920, 0);
    var_v0 = func_800082E0(1, 0, 2, 0, 2, 1);
    func_8004C09C(var_a0);
    D_8800687C = func_80047588(28, 0);
    Font_EnableLineBreak();
    func_885009D0();
    func_80008514((s32)var_v0);
    func_8850089C();
    func_800086A4(2);
    func_80008574();
    func_80047610();
    func_8004C398();
    Gfx_FreeDisplayListBuffers();
    main_pool_pop_state(1347241304);
    return 7;
}
#pragma C_FUNCTION_PADDING(12)
```

## Retained candidate object

```text
<func_88500C10>:
 bf0:	27bdffd8 	addiu	sp,sp,-40
 bf4:	3c0e0000 	lui	t6,0x0
			bf4: R_MIPS_HI16	.data
 bf8:	8dce0000 	lw	t6,0(t6)
			bf8: R_MIPS_LO16	.data
 bfc:	afa40028 	sw	a0,40(sp)
 c00:	afbf001c 	sw	ra,28(sp)
 c04:	3c04504d 	lui	a0,0x504d
 c08:	afa5002c 	sw	a1,44(sp)
 c0c:	34844558 	ori	a0,a0,0x4558
 c10:	0c000000 	jal	0 <func_88500020>
			c10: R_MIPS_26	main_pool_push_state
 c14:	afae0020 	sw	t6,32(sp)
 c18:	3c040001 	lui	a0,0x1
 c1c:	34844000 	ori	a0,a0,0x4000
 c20:	0c000000 	jal	0 <func_88500020>
			c20: R_MIPS_26	Gfx_InitDisplayListBuffers
 c24:	00002825 	move	a1,zero
 c28:	240f0002 	li	t7,2
 c2c:	24180001 	li	t8,1
 c30:	afb80014 	sw	t8,20(sp)
 c34:	afaf0010 	sw	t7,16(sp)
 c38:	24040001 	li	a0,1
 c3c:	00002825 	move	a1,zero
 c40:	24060002 	li	a2,2
 c44:	0c000000 	jal	0 <func_88500020>
			c44: R_MIPS_26	func_800082E0
 c48:	00003825 	move	a3,zero
 c4c:	8fa40020 	lw	a0,32(sp)
 c50:	afa20024 	sw	v0,36(sp)
 c54:	0c000000 	jal	0 <func_88500020>
			c54: R_MIPS_26	func_8004C09C
 c58:	afa40000 	sw	a0,0(sp)
 c5c:	2404001c 	li	a0,28
 c60:	0c000000 	jal	0 <func_88500020>
			c60: R_MIPS_26	func_80047588
 c64:	00002825 	move	a1,zero
 c68:	3c010000 	lui	at,0x0
			c68: R_MIPS_HI16	D_8800687C
 c6c:	0c000000 	jal	0 <func_88500020>
			c6c: R_MIPS_26	Font_EnableLineBreak
 c70:	ac220000 	sw	v0,0(at)
			c70: R_MIPS_LO16	D_8800687C
 c74:	0c000000 	jal	0 <func_88500020>
			c74: R_MIPS_26	func_885009D0
 c78:	00000000 	nop
 c7c:	0c000000 	jal	0 <func_88500020>
			c7c: R_MIPS_26	func_80008514
 c80:	8fa40024 	lw	a0,36(sp)
 c84:	0c000000 	jal	0 <func_88500020>
			c84: R_MIPS_26	func_8850089C
 c88:	00000000 	nop
 c8c:	0c000000 	jal	0 <func_88500020>
			c8c: R_MIPS_26	func_800086A4
 c90:	24040002 	li	a0,2
 c94:	0c000000 	jal	0 <func_88500020>
			c94: R_MIPS_26	func_80008574
 c98:	00000000 	nop
 c9c:	0c000000 	jal	0 <func_88500020>
			c9c: R_MIPS_26	func_80047610
 ca0:	00000000 	nop
 ca4:	0c000000 	jal	0 <func_88500020>
			ca4: R_MIPS_26	func_8004C398
 ca8:	00000000 	nop
 cac:	0c000000 	jal	0 <func_88500020>
			cac: R_MIPS_26	Gfx_FreeDisplayListBuffers
 cb0:	00000000 	nop
 cb4:	3c04504d 	lui	a0,0x504d
 cb8:	0c000000 	jal	0 <func_88500020>
			cb8: R_MIPS_26	main_pool_pop_state
 cbc:	34844558 	ori	a0,a0,0x4558
 cc0:	8fbf001c 	lw	ra,28(sp)
 cc4:	27bd0028 	addiu	sp,sp,40
 cc8:	24020007 	li	v0,7
 ccc:	03e00008 	jr	ra
 cd0:	00000000 	nop
	...

```
