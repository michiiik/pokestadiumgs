# Failed matching attempts -- func_87E18410

## Evidence and retry boundary

The real one-pointer drawing callback is registered by func_87E18828. It captures the pointer at argument offset 12 and later reads that record's first word as a resource-table index. The real six-argument func_80007444 is the existing GfxImage_FillRectangle alias, with final u16 color; func_8004C990 and func_8004D19C have their canonical word-handle and five-word contracts. Standard SDK display-list and G_RM_TEX_EDGE macros reproduce the original command words, including render mode 0x0F0A7008.

The first candidate reproduces all 61 executable words and the 48-byte frame except the captured pointer's two stack accesses: candidate SW/LW at stack offset 44 versus retail 40. Registers, commands, index arithmetic, calls and every other instruction remain exact. Full ROM MD5 8484e95debc39f1b6c0bd3cd993aad78.

Do not repeat ordinary scalar/typed-pointer aliases, declaration order or padded scratch. A retry needs supported captured-pointer/stack lifetime evidence. No fake unused local, invented incoming argument or helper ABI change may be used to force a home.

Each failed source was saved with its object and build/checksum logs under work/session-62. Restoration replaced only the exact owner and declarations introduced by that trial; no full-translation-unit snapshot or raw baseline was used. All merged owners, including the new func_82901554, remain present. The restored US COMPARE=1 build with host checks passes, and md5sum -c baseroms/us/checksum.md5 returns OK, retail MD5 1561c75d11cedf356a8ddb1a4a5f9d5d. A local PASS is not historical remote gate proof.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact attempt or corresponding region catalog note for this owner. Actual helper definitions and original callers were audited. All earlier raw/regional failures and shared-tail exclusions remain in force. No CI, compiler, tools, layout, data or verification changes were authored.

## Captured-pointer candidate

```c
extern void func_80007444(Gfx **, s32, s32, s32, s32, u16);
extern s32 func_8004C990(s32, s32);
extern s32 func_8004D19C(s32, s32, s32, s32, s32);
extern Gfx *D_800D0510;
extern Gfx D_80094E38[];
extern Gfx D_80094F50[];
extern s32 D_87E1B468[];

void func_87E18410(u8 *arg0) {
    s32 *var_t7 = *(s32 **)(arg0 + 12);

    func_80007444(&D_800D0510, 0, 0, 100, 26, 0xFFFE);
    gSPDisplayList(D_800D0510++, D_80094E38);
    gDPSetRenderMode(D_800D0510++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    func_8004D19C(0, 0, func_8004C990(426, D_87E1B468[*var_t7]), 0, 0);
    gSPDisplayList(D_800D0510++, D_80094F50);
}
```

```text
00000000 <func_87E18410>:
   0:	27bdffd0 	addiu	sp,sp,-48
   4:	afbf0024 	sw	ra,36(sp)
   8:	afb00020 	sw	s0,32(sp)
   c:	afa40030 	sw	a0,48(sp)
  10:	8c8f000c 	lw	t7,12(a0)
  14:	3c100000 	lui	s0,0x0
			14: R_MIPS_HI16	D_800D0510
  18:	26100000 	addiu	s0,s0,0
			18: R_MIPS_LO16	D_800D0510
  1c:	2418001a 	li	t8,26
  20:	3419fffe 	li	t9,0xfffe
  24:	afb90014 	sw	t9,20(sp)
  28:	afb80010 	sw	t8,16(sp)
  2c:	02002025 	move	a0,s0
  30:	00002825 	move	a1,zero
  34:	00003025 	move	a2,zero
  38:	24070064 	li	a3,100
  3c:	0c000000 	jal	0 <func_87E18410>
			3c: R_MIPS_26	func_80007444
  40:	afaf002c 	sw	t7,44(sp)
  44:	8e030000 	lw	v1,0(s0)
  48:	3c0a0000 	lui	t2,0x0
			48: R_MIPS_HI16	D_80094E38
  4c:	254a0000 	addiu	t2,t2,0
			4c: R_MIPS_LO16	D_80094E38
  50:	24680008 	addiu	t0,v1,8
  54:	ae080000 	sw	t0,0(s0)
  58:	3c09de00 	lui	t1,0xde00
  5c:	ac690000 	sw	t1,0(v1)
  60:	ac6a0004 	sw	t2,4(v1)
  64:	8e030000 	lw	v1,0(s0)
  68:	3c0ce200 	lui	t4,0xe200
  6c:	3c0d0f0a 	lui	t5,0xf0a
  70:	246b0008 	addiu	t3,v1,8
  74:	ae0b0000 	sw	t3,0(s0)
  78:	35ad7008 	ori	t5,t5,0x7008
  7c:	358c001c 	ori	t4,t4,0x1c
  80:	ac6c0000 	sw	t4,0(v1)
  84:	ac6d0004 	sw	t5,4(v1)
  88:	8fae002c 	lw	t6,44(sp)
  8c:	3c050000 	lui	a1,0x0
			8c: R_MIPS_HI16	D_87E1B468
  90:	240401aa 	li	a0,426
  94:	8dcf0000 	lw	t7,0(t6)
  98:	000fc080 	sll	t8,t7,0x2
  9c:	00b82821 	addu	a1,a1,t8
  a0:	0c000000 	jal	0 <func_87E18410>
			a0: R_MIPS_26	func_8004C990
  a4:	8ca50000 	lw	a1,0(a1)
			a4: R_MIPS_LO16	D_87E1B468
  a8:	00002025 	move	a0,zero
  ac:	00002825 	move	a1,zero
  b0:	00403025 	move	a2,v0
  b4:	00003825 	move	a3,zero
  b8:	0c000000 	jal	0 <func_87E18410>
			b8: R_MIPS_26	func_8004D19C
  bc:	afa00010 	sw	zero,16(sp)
  c0:	8e030000 	lw	v1,0(s0)
  c4:	3c090000 	lui	t1,0x0
			c4: R_MIPS_HI16	D_80094F50
  c8:	25290000 	addiu	t1,t1,0
			c8: R_MIPS_LO16	D_80094F50
  cc:	24790008 	addiu	t9,v1,8
  d0:	ae190000 	sw	t9,0(s0)
  d4:	3c08de00 	lui	t0,0xde00
  d8:	ac680000 	sw	t0,0(v1)
  dc:	ac690004 	sw	t1,4(v1)
  e0:	8fbf0024 	lw	ra,36(sp)
  e4:	8fb00020 	lw	s0,32(sp)
  e8:	27bd0030 	addiu	sp,sp,48
  ec:	03e00008 	jr	ra
  f0:	00000000 	nop

```
