# Region notes -- disasm/src/fragments/67/fragment67_344D70.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Accepted owners: func_82908270 / func_82908370 (0x100-spaced sibling pair) (2026-09-06)

Both accepted through the full link-verified ROM gate (MD5 1561c75d11cedf356a8ddb1a4a5f9d5d), label `struct-array-index:0x12-entry:pad3-locals`.

The two are byte-for-byte the same shape: identical 64 instructions apart from five `D_82916B80` entry offsets (0x0/0x1/0x2/0xA/0xC in 8270 versus 0x3/0x4/0x5/0xE/0x10 in 8370). Any recorded score is therefore expected to be identical for both; that on its own is not a systemic signal here.

Two things had to be right at once, and manual byte arithmetic gets neither:

1. **Index `D_82916B80` as a real 0x12-byte struct array, not `&D_82916B80 + idx * 0x12`.** The hand-rolled byte form compiles to the same 64 instructions and the same sizes but rotates three registers (`$t0`/`$t1`/`$v1` are assigned to the wrong one of {`&D_8291A7C0`, constant 0x12, `&D_82916B80`}) and emits `addu $t8, $t7, $t1` (index + base) where the ROM has `addu $t8, $v1, $t7` (base + index). Declaring `extern Fragment67Entry D_82916B80[];` with a 0x12-byte entry and writing `D_82916B80[idx].unkN` fixes the operand order and the register rotation together -- this was reported as `immediate_drift` at similarity 1.0 / raw 0.5938, first diff instruction 25 expected `lui $t0` actual `lui $v1`, i.e. the diagnostic label pointed at a relocation while the real cause was the address-arithmetic spelling.

2. **Three dead `s16` scalars declared before the three live out-params.** The frame is 0x38 either way, but the ROM puts the `func_80037120` out-params at 0x30/0x2E/0x2C, six bytes below the top of the local area; without the padding they land at 0x36/0x34/0x32. They must be three separate scalars: `s16 pad[3];` is allocated as an aggregate and grows the frame to 0x40 instead.

Both fixes are independent -- neither alone matches -- and both siblings need the identical pair, which is what a 0x100-spaced templated pair should look like.

Working spelling (8270; 8370 is the same body with unk3/unk4/unk5/unkE/unk10):

```c
extern Fragment67Entry D_82916B80[];   /* 0x12-byte entries */
extern u8 D_8291A7C0;
extern void *D_80094908;

s16 pad0; s16 pad1; s16 pad2;          /* dead, but load-bearing for the frame */
s16 sp30; s16 sp2E; s16 sp2C;
...
D_82916B80[*(s16 *)(&D_8291A7C0 + 0x1068)].unk0
func_80037120((u8 *)D_80094908 + 0xB4, (u8 *)D_80094908 + 0xA8, &sp30, &sp2E, &sp2C);
```

`D_8291A7C0 + 0x1068` (the entry index, an `s16`) is deliberately left as raw byte arithmetic: the ROM materialises that address separately from the table base, so typing it as a struct is not required and was not probed.

## 2026-09-07

func_82908470: matched (state_field_access:guard:indexed-member), 1 iterations, agent codex

## 2026-09-07

func_82908520: plateau at 0.8621 (raw 0.7586), mismatch instruction_drift; tried families: bounded_lookup; tie-pool no

## 2026-09-07

func_82908594: matched (call_chain:pointer_walk:store-then-increment), 2 iterations, agent codex

## 2026-09-07

func_8290867C: plateau at 0.8621 (raw 0.7586), mismatch instruction_drift; tried families: bounded_lookup; tie-pool no

## 2026-09-07

func_82908B60: time cap at 0.9062 (raw 0.25) after 2408s, mismatch operand_or_scheduling_drift; tried families: state_field_access; tie-pool no
