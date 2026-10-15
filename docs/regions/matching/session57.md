# Session 57 failed investigations

Both owners remain GLOBAL_ASM. Each valid trial used the full US build with default host syntax checks and COMPARE=1, followed by the explicit retail checksum. Failed source, object dumps, build logs and output MD5s remain in work/session-57. Only each failed owner and its newly introduced declaration were restored; fresh master source and all merged/open matching implementations remain intact. Both restored builds pass retail 1561c75d11cedf356a8ddb1a4a5f9d5d.

## func_82101A30

Original func_82100F68 supplies the actual pointer from its field at offset 28 and ignores the result. This is an independent 33-word leaf, with no frame, padding or shared switch tail. It reads a signed count at offset 8 and the record pointer at offset zero, scans 32-byte records, preserves both null guards, sets bit 2 in a pointed halfword at offset 2, and streams unsigned halfwords from source offsets 24/26 to destination offsets 36/38. Only the store path can alter the aliased count; the original reloads it there.

The trial used a captured signed count, a byte-offset induction variable starting at zero and increasing by 32, an initial positive count guard and a do loop with count-times-32 bound. It preserves all pointed halfword stores and reloads, but emits 29 rather than 33 words. Count/index/cursor use v0/v1/a1 instead of retail v1/a1/v0; the bound uses t5 instead of a3. The first null check is a compressed negative BEQ rather than the original positive BNE plus separate skip branch. The second guard similarly folds the separate skip tail and duplicate load into a likely branch. Full-ROM MD5: f6b712fef9b135eb10b7be57f90fbaf8.

A supported loop-value and null-guard control-lifetime model is required. Do not repeat ordinary counted/captured-count, pointer, do/while/goto, declaration or operand variants without new evidence. The exact restored fresh fragment25 source blob is c7d1e5425a5566b621c498e9011ebdb97a06d58a.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact owner attempt, reference or fragment25 regional note; current master has no regional document here. No historical normalized/raw score is available. The original caller and full body were audited; all open PR scopes were inspected before the trial.

## func_81700B8C

This independent 32-word owner has a real word selector and string pointer, word result and 40-byte frame. Original fragment24 callers forward the result of func_82B0173C in a1 and branch on the owner's result. The canonical compiled func_80049148 is s32(s32,s32,const char*,...). Its third argument is the incoming string; the original a1-to-a2 copy is essential, not an unused register move. The actual 36-byte table uses signed halfwords at offsets 6/18/20 and a pointer at offset 8. The trial retained existing byte-array D_81700DB0, pointer identity, both guards, the varargs declaration and the width-plus-75 stores.

The first nested-guard recipe reproduces all 32 words, every register, frame 40, pointer spill 28, result a3 and all control flow. Only three instructions around the real helper call differ. Retail loads a0 from table halfword 6, spills v1 at stack 28, then places a1=0 in the JAL delay slot. The candidate initializes a1=0, loads that halfword, then puts the pointer spill in the delay slot. Full-ROM MD5: 6c14e96708928838c10e25b27a5081dd.

A supported call-argument load/spill lifetime model is required. Do not repeat ordinary raw/typed table, nested guard, declaration, operand or helper-prototype permutations. Do not delete the real third helper argument or substitute a false two-argument declaration. The exact restored fresh fragment18 blob is b9851725d383ff54a4635428376e61dad58a343d.

No exact fleet owner attempt or owner-specific regional recipe exists. References in failed fragment24 drafts are caller references, not owner attempts; their stale two-word helper assumptions were not used. The full fragment18 fleet note records the unrelated accepted func_81700908 lifetime recipe, which was not replayed. Current master has no regional document here. No historical normalized/raw score is available.

## Scope and verification

Current master imports foreign fragment13/53 matches and their canonical data/layout changes exactly; these are upstream changes, not authored verification changes. Foreign #1040's entire scope was deferred and was imported only after its repository merge. No documentation or unrelated PR was merged by this process.

The original #1031 validation against master 647ef910 became stale when #1040 merged. The process returned #1031 to draft before merge, then refreshed it with a guarded fast-forward and requested a fresh gate. The stale/cancelled run is not an acceptance. Local retail checks do not repair any of the 28 older historical validation gaps. This documentation remains draft and outside matching merge authorization.
