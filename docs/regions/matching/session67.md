# Session 67: retained func_8006D268 failure

## Actual ABI and new prerequisite

Original assembly takes one narrow unsigned selector and returns a word predicate. It stores the incoming argument at its home, normalizes it with ANDI 0xFFFF into a1, passes its high byte mask to the existing func_8006D1A0(u16) pointer helper, and preserves the normalized word at stack offset 28 across the call. A default word result at offset 36 is replaced by the selected halfword masked with the selector and 0xFF, normalized to zero or one. Its 40-byte frame contains 21 executable words and one trailing zero word.

Five original call sites were audited: compiled fragment16 passes 514 and 513; original assembly in 674D0, fragment20 and fragment21 passes 258, 257 and 769. All branch on the word result. The existing compiled helper returns addresses of the actual halfword flag globals and keeps its original definition. The two compiled calls' one stale word-formal declaration was corrected consistently for this trial; their entire text section remained byte-identical.

Session 23 inspected this owner without a trial because exact four-byte padding was unavailable. Merged upstream #1103 now supplies C_FUNCTION_PADDING(4), allowing the first owner trial on fresh master 4ed098bfe7b757560f1a0a17f9f737cf913bf9b3. Full fleet gs-attempt-history has no exact owner attempt or 6DDA0 regional note; unrelated references are not owner attempts.

## One failed candidate

```c
s32 func_8006D268(u16 arg0) {
    u16 *var_v0;
    s32 var_v1 = 0;
    u32 var_a1 = arg0;

    var_v0 = (u16 *)func_8006D1A0(var_a1 & 0xFF00);
    if (var_v0 != NULL) {
        var_v1 = (*var_v0 & var_a1 & 0xFF) != 0;
    }
    return var_v1;
}
#pragma C_FUNCTION_PADDING(4)
```

Companion transaction: `extern s32 func_8006D268(s32);` became `extern s32 func_8006D268(u16);` in src/fragments/16/fragment16_code.c. No helper ABI, data, tool, layout, CI or verification code was changed. No FAKE code was used.

US compilation and linking completed, but the full ROM comparison failed with MD5 `9a4037191dd08af17d16dbf7c09b77af`. The candidate emits 20 executable words and a 32-byte frame: result stack offset 24, incoming home 32, repeated halfword argument loads at 34 and an additional outgoing ANDI 0xFFFF. It does not preserve retail's normalized word in a1 at offset 28 or its result at offset 36. The explicit word local is optimized back into halfword-home reloads. Padding cannot repair these executable and lifetime differences.

```text
000000c8 <func_8006D268>:
  c8:	27bdffe0 	addiu	sp,sp,-32
  cc:	afa40020 	sw	a0,32(sp)
  d0:	97a40022 	lhu	a0,34(sp)
  d4:	afbf0014 	sw	ra,20(sp)
  d8:	afa00018 	sw	zero,24(sp)
  dc:	3084ff00 	andi	a0,a0,0xff00
  e0:	0c000000 	jal	0 <func_8006D1A0>
			e0: R_MIPS_26	func_8006D1A0
  e4:	3084ffff 	andi	a0,a0,0xffff
  e8:	10400006 	beqz	v0,104 <func_8006D268+0x3c>
  ec:	8fa30018 	lw	v1,24(sp)
  f0:	944e0000 	lhu	t6,0(v0)
  f4:	97af0022 	lhu	t7,34(sp)
  f8:	01cf1824 	and	v1,t6,t7
  fc:	306300ff 	andi	v1,v1,0xff
 100:	0003182b 	sltu	v1,zero,v1
 104:	8fbf0014 	lw	ra,20(sp)
 108:	27bd0020 	addiu	sp,sp,32
 10c:	00601025 	move	v0,v1
 110:	03e00008 	jr	ra
 114:	00000000 	nop
	...
```

Do not repeat ordinary narrow-formal, captured-word, scalar-result, declaration, padding or operand variants. A retry needs supported evidence for the authentic normalized-word/argument-home and result lifetimes; never manufacture homes, extra formals or a false helper contract.

## Restoration and preserved evidence

Restored only the failed owner's exact pragma and the one declaration. Both files equal their fresh-master blob hashes: src/6DDA0.c `2379ad1af9b59b8f6ff8419f1ef7293b9b50c17c`, fragment16 `b01b5b6dd8890e12327020b9995e157ba681c72c`. All imported and previously merged C remains installed. No historical raw/current-master/full-TU snapshot was used as a restoration baseline.

The restored US build with host syntax checks and explicit md5sum -c baseroms/us/checksum.md5 passed retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. Full failed owner, narrow transaction, object, build log, MD5 and restoration evidence remain in work/session-67. The 28 historical public-gate proof gaps remain unchanged; local PASS supplies no retroactive CI proof.
