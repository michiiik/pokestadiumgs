# Session68: retained func_8AF08644 failure

## ABI and full history audit

Original func_8AF087D4 passes7 and consumes the result through a signed-halfword conversion. The owner stores its incoming argument home and normalizes that real signed-halfword formal at entry, returning the unchanged normalized value except that the final guarded action returns16. The actual halfword flags at D_8AF263C0+8 are checked in priority order with masks0x800,0x100,0x8000. The first two paths set the existing signed-halfword D_8AF2C960 to0 or5. The final path calls the real void func_8AF00130(s32) with191 and real void func_8AF15EF0(void), then returns16.

Both canonical helpers were read in their compiled definitions: fragment44_1EE290 forwards the word code to func_800226C0; fragment44_2030B0 contains the no-argument halfword initializer. The existing void* global declaration and signed-halfword state type are preserved. No false helper signature, argument, global qualifier or zero substitute was used.

There is no exact owner attempt or 44_1F5F20 regional file in the consulted fleet catalog. Complete retained history was reviewed and all open scopes were checked before this first candidate. Related earlier failures and regional plateaus remain untouched.

## One failed candidate

```c
extern void *D_8AF263C0;
extern void func_8AF00130(s32);
extern void func_8AF15EF0(void);

s32 func_8AF08644(s16 arg0) {
    u16 var_v0 = *(u16 *)((u8 *)D_8AF263C0 + 8);

    if (var_v0 & 0x800) {
        D_8AF2C960 = 0;
    } else if (var_v0 & 0x100) {
        D_8AF2C960 = 5;
    } else if (var_v0 & 0x8000) {
        func_8AF00130(191);
        func_8AF15EF0();
        arg0 = 16;
    }
    return arg0;
}
```

US compilation and linking completed, but the full ROM checksum failed: `c2f303e3830b0ecc704fa25caed43e00`. This result is retained as a failure.

All32 words, the24-byte frame, incoming home, normalization, branches, delay slots, calls, stores and return agree except four instructions: the halfword flag load and three ANDI operations use v1 instead of retail v0. Equal size/opcode shape does not pass the whole-ROM comparison.

A retry requires supported flag-value/result lifetime evidence. Do not repeat ordinary flag widths, scalar/captured locals, declaration order, return-width changes, control spelling or operand variants to recolor this register. Never change the actual helper contracts or invent incoming arguments.

```text
00000994 <func_8AF08644>:
 994:	3c0e0000 	lui	t6,0x0
			994: R_MIPS_HI16	D_8AF263C0
 998:	8dce0000 	lw	t6,0(t6)
			998: R_MIPS_LO16	D_8AF263C0
 99c:	27bdffe8 	addiu	sp,sp,-24
 9a0:	afbf0014 	sw	ra,20(sp)
 9a4:	afa40018 	sw	a0,24(sp)
 9a8:	95c30008 	lhu	v1,8(t6)
 9ac:	00042400 	sll	a0,a0,0x10
 9b0:	00042403 	sra	a0,a0,0x10
 9b4:	306f0800 	andi	t7,v1,0x800
 9b8:	11e00004 	beqz	t7,9cc <func_8AF08644+0x38>
 9bc:	30780100 	andi	t8,v1,0x100
 9c0:	3c010000 	lui	at,0x0
			9c0: R_MIPS_HI16	D_8AF2C960
 9c4:	1000000e 	b	a00 <func_8AF08644+0x6c>
 9c8:	a4200000 	sh	zero,0(at)
			9c8: R_MIPS_LO16	D_8AF2C960
 9cc:	13000005 	beqz	t8,9e4 <func_8AF08644+0x50>
 9d0:	30688000 	andi	t0,v1,0x8000
 9d4:	24190005 	li	t9,5
 9d8:	3c010000 	lui	at,0x0
			9d8: R_MIPS_HI16	D_8AF2C960
 9dc:	10000008 	b	a00 <func_8AF08644+0x6c>
 9e0:	a4390000 	sh	t9,0(at)
			9e0: R_MIPS_LO16	D_8AF2C960
 9e4:	51000007 	beqzl	t0,a04 <func_8AF08644+0x70>
 9e8:	8fbf0014 	lw	ra,20(sp)
 9ec:	0c000000 	jal	0 <func_8AF07CB0>
			9ec: R_MIPS_26	func_8AF00130
 9f0:	240400bf 	li	a0,191
 9f4:	0c000000 	jal	0 <func_8AF07CB0>
			9f4: R_MIPS_26	func_8AF15EF0
 9f8:	00000000 	nop
 9fc:	24040010 	li	a0,16
 a00:	8fbf0014 	lw	ra,20(sp)
 a04:	27bd0018 	addiu	sp,sp,24
 a08:	00801025 	move	v0,a0
 a0c:	03e00008 	jr	ra
 a10:	00000000 	nop
```

## Narrow restoration and validation

Only this owner's exact pragma was restored, including removal of its new local declaration block. The resulting source equals its fresh-master blob `f7dcb16e4343f1b666cbc7287ee87d3369e740bb`. No historical raw/current-master/full-TU snapshot was used as a restoration baseline, and no previously merged source was removed. No FAKE code, new known names or authored CI/tools/layout/data/verification changes were introduced.

The restored full US build with default host syntax checks and COMPARE=1 passed, followed by `md5sum -c baseroms/us/checksum.md5`: retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. Complete source, narrow transaction, object text, build log and failed checksum remain in work/session-68. All28 historical public-gate proof gaps remain preserved; local PASS supplies no retroactive proof.
