# Session 67: retained func_84136CA8 failure

## Actual owner and historical audit

The original no-argument void owner increments byte 19841 of the existing D_84195280 buffer, narrows the increment to a byte before comparing with 30, wraps it to zero when needed, and calls the canonical _bzero(void *, s32) on the selected 640-byte record. Many compiled callers explicitly use func_84136CA8(void); original assembly confirms no incoming argument is consumed. The adjacent buffer getters independently confirm the index and stride. No new formal, return value, data type or helper ABI was invented.

Full fleet gs-attempt-history region79_393CA0 was reviewed together with all current regional notes. There is no exact owner attempt file; references in other owners are not attempts. The old file-level four-byte splice issue was explicitly resolved in the later regional entry for func_84136D84. That prerequisite is therefore not used as an excuse to alter tools, layout, data or verification. Existing regional raw/normalized plateaus and unrelated rodata/shared-tail restrictions remain unchanged.

## One failed candidate

```c
void func_84136CA8(void) {
    u8 *var_v1 = D_84195280;
    u8 var_v0;

    var_v0 = ++var_v1[19841];
    if (var_v0 >= 30) {
        var_v1[19841] = var_v0 = 0;
    }
    _bzero(&var_v1[var_v0 * 640], 640);
}
```

This is a natural consumed byte counter and base-pointer spelling; it contains no FAKE code and no padding directive. Original assembly contains 22 executable words, including its return delay slot, with a 24-byte frame.

US compilation and linking completed, but the full-ROM checksum failed: `f8a0ebc328424b02c45567506b94da13`. The candidate emits 23 executable words and preserves the 24-byte frame. It selects a2 for the global base instead of retail v1, emits a separate LUI/relocated store for the zero reset, uses MOVE v0,zero instead of retail ANDI v0,zero,0xFF, and reverses the final address ADDU operands. The loop-free increment/compare/stride body otherwise follows the intended operation. This is not a trailing-padding problem.

```text
00012898 <func_84136CA8>:
   12898:	3c060000 	lui	a2,0x0
			12898: R_MIPS_HI16	D_84195280
   1289c:	24c60000 	addiu	a2,a2,0
			1289c: R_MIPS_LO16	D_84195280
   128a0:	90ce4d81 	lbu	t6,19841(a2)
   128a4:	27bdffe8 	addiu	sp,sp,-24
   128a8:	afbf0014 	sw	ra,20(sp)
   128ac:	25cf0001 	addiu	t7,t6,1
   128b0:	31e200ff 	andi	v0,t7,0xff
   128b4:	2841001e 	slti	at,v0,30
   128b8:	14200004 	bnez	at,128cc <func_84136CA8+0x34>
   128bc:	a0cf4d81 	sb	t7,19841(a2)
   128c0:	3c010000 	lui	at,0x0
			128c0: R_MIPS_HI16	D_84195280
   128c4:	a0204d81 	sb	zero,19841(at)
			128c4: R_MIPS_LO16	D_84195280
   128c8:	00001025 	move	v0,zero
   128cc:	0002c080 	sll	t8,v0,0x2
   128d0:	0302c021 	addu	t8,t8,v0
   128d4:	0018c1c0 	sll	t8,t8,0x7
   128d8:	03062021 	addu	a0,t8,a2
   128dc:	0c000000 	jal	0 <func_84124410>
			128dc: R_MIPS_26	_bzero
   128e0:	24050280 	li	a1,640
   128e4:	8fbf0014 	lw	ra,20(sp)
   128e8:	27bd0018 	addiu	sp,sp,24
   128ec:	03e00008 	jr	ra
   128f0:	00000000 	nop
```

Do not repeat ordinary base-pointer/scalar/byte-counter/compound-clamp/declaration/operand or qualifier variants. A retry requires supported global-address and narrowed-counter value-lifetime evidence. Do not change global declarations, coalescing policy, tools or helper contracts to force the match.

## Narrow restoration

Only this failed owner was restored to its pragma. The entire resulting source equals fresh master blob `082cf11cc1b69bd9c6b71850f469fab60c45733f`; no historical raw/current-master/full-TU snapshot was restored and no merged source was removed.

The restored US build with default host syntax checks and COMPARE=1 passed, followed by md5sum -c baseroms/us/checksum.md5: retail `1561c75d11cedf356a8ddb1a4a5f9d5d`. Full failed owner, narrow transaction, object, build and checksum logs remain in work/session-67. All 28 historical gate gaps remain preserved exactly; local PASS supplies no retroactive public-gate proof.
