# Fleet decompilation agent brief

You are one of several Sonnet agents in a fleet. You own **one source file**
for a timeboxed session. Do not read `AGENTS.md`; this page has what you need.
Do not touch any other file's pragmas or run `make`.

## 1. Start here (under a minute)

- Scratch dir: `$CLAUDE_JOB_DIR/tmp/<file>/` — yours alone; do not share it.
- `python3 tools/file_brief.py disasm/src/<file>.c` — prints solved/remaining
  owners, existing signatures, the deduped extern block, `func_`/`D_` symbols
  other bodies already use, record-stride constants seen in this file,
  SDK macros already in use, and — critically — every function **defined
  later in the file** with its real return type/params (pass these in
  `declarations`; the runner's fallback prototype defaults to `s32` and a
  narrower real return type, e.g. `u8`, fails the probe as a "redeclaration").
- Headers live in the repo only: `disasm/lib/ultralib/include/PR/gbi.h` has
  the `gSP*`/`gDP*` macros. Never search outside this repository.

## 2. The loop, per function

1. Read the `.s` under `disasm/asm/us/nonmatchings/<file>/<func>.s`. Note
   argument masks (`andi 0xff` → `u8` param), frame size, saved registers,
   narrow loads/stores, the return tail.
2. Look at neighbouring solved functions in the same file (`file_brief.py`'s
   list) for the closest opcode-shape match; start from that spelling.
3. Write 5–10 variants differing in **one** hypothesis each (decl order, temp
   widths, index-vs-pointer, guard-return vs assign-then-return, explicit
   temporaries, old-style callee prototypes). Order candidates by §4's table.
4. Send them as one **probe-only** batch: `python3 tools/fleet_probe.py
   batch.json` (no `--gate`). Read the printed table and iterate on
   `mismatch_kind`, never on intuition: `register_allocation_only` → decl
   order/temps/widths; `immediate_drift` → offsets/strides/literal widths;
   `section_layout_drift` → reject, needs a `.rodata` subsegment first;
   `symbol_size_drift`/tail kinds → `C_FUNCTION_PADDING` or a `_padding` helper.
5. Gate the first probe hit: `python3 tools/fleet_probe.py batch.json --gate`.
6. Cap **~12 variants / ~8 minutes per owner**. If the best after two batches
   is `register_allocation_only` at similarity ≥ 0.99, stop on that owner —
   it is a known-hard register tie, not a spelling you haven't tried.

## 3. `fleet_probe.py` / `file_brief.py` usage

```
python3 tools/fleet_probe.py batch.json                # probe-only (gate: false)
python3 tools/fleet_probe.py batch.json --gate          # full ROM gate
python3 tools/fleet_probe.py variants_dir/ --source disasm/src/X.c
python3 tools/file_brief.py disasm/src/<file>.c
```
`batch.json`: `{"source": "disasm/src/X.c", "declarations": "...",
"candidates": [{"function": "func_...", "label": "family:shape:hyp", "body": "..."}]}`.
Table columns: label, status, similarity, raw similarity, mismatch kind,
expected/actual size, first-diff offset, expected vs actual instruction at
that offset. A trailing verdict line per function names the best label, and
says "register tie — stop" when §2 step 6's stop condition applies.

## 4. Verified source-shape heuristics (copied verbatim from AGENTS.md §4 — order candidates by these; always probe and gate)

| Shape | Spelling that matched | Evidence | Limit |
|---|---|---|---|
| Wrapper returning a callee result vs void | Direct `return f(...)` / plain call, exact prototype and call order; explicit temporaries in multi-call wrappers | many owners | — |
| Fixed-stride byte-flag pool scan | Uniquely named padded local record, `s8` flag at the proven offset, `s32 i`, result initialised before the pool load, post-incremented record pointer | 1 S1 transfer | same scan only |
| `lbu`/`andi`/`jr`/`sb` flag clear | `arg0[off] &= 0xFF7F` (`0xFFFE`) on a `u8 *`, literal 16-bit mask kept | 2 | same load-mask-store shape |
| `lbu` index → pointer table → `lbu`/`ori`/`sb` | `table[index][off] \|= lit` with `u8 *[]` table declared locally; byte-typed argument when the asm masks it | 2 (+1) | — |
| Four `sh` stores at 0/2/4/6, fifth value from stack | `u8 *` plus `u16 *` casts, `s32` params, explicit halfword widths | 2 | no struct inferred |
| Two-component `s16` add/sub | add: uniquely named two-`s16` struct; sub: explicit `u8 *` offsets — probe both | 2 | — |
| Three-component float copy | `arg0[0..2] = arg1[0..2]` on `f32 *` | 3 | exact 3-copy shape |
| `lhu`/`andi` bit test | `s32 result = 0; if (global & mask) result = 1; return result;` with `u16` global | 5 | no ternary / compact bool |
| Byte-argument state predicates | `u8` parameter, initialised `s32` result, nested explicit checks over raw byte offsets | 4 | `s32` params did not match |
| Word-field predicates | Uniquely named local struct overlay padded to 0x10/0x14, comparison written `arg0 == state->value` | 2 | overlay is local |
| Isolated stack-slot immediate drift | 12-byte local with 4-byte leading pad; declare a temp pointer before the saved-result pointer | 3 (`14640.c`) | only for slot drift |
| Forwarded 3-arg wrapper into 5-arg helper | Four-word `s32 locals[4]`, pass `&locals[2]`, `&locals[1]` | 2 | keeps 0x30 frame |
| Post-call index fallback | Keep the incoming index formal in place; single `u8 *` temp from `(u8 *)(u32)f(arg0) + (arg1 << 4)` | 1 | — |
| Compact enum dispatcher | C `switch` over a `u8` global with literal cases | 1 | blocked by §2.7 when a jtbl is emitted |
| Resource initializer | Byte-stride global write, `s32`-indexed `while (i < table[arg][bound])`, final wrapper call | 1 | same table/loop shape |
| Multi-local near-miss | Declare fixed stack locals ascending (`sp24, sp26, sp28`) rather than m2c's descending order (`stack-slots-ascending` retry) | audit | — |
| Duplicate `jr`/`nop` tail | Empty owner + uniquely named `<owner>_padding(void) {}` helper | 1 | not for alignment-only tails |
| Trailing alignment nops | `#pragma C_FUNCTION_PADDING(bytes)` | several | verified layout bytes only |
| Bounded lookup returning a value | Guard-clause early return `if (cond) return table[i]; return 0;` first; assign-then-return second; ternary last; `u8` param when the asm masks with `andi 0xff`; compound condition read from the real second range check (`blez` → `> 0`, `bltz` → `>= 0`); non-power-of-two strides from the `sll`/`subu`/`addu` chain | 9/14 guard, 5/14 assign, 0/14 ternary | — |
| Globals loaded with `lw` into an argument | Try `void *` before `u32` | scan | no help for `lui`-before-`sw $ra` scheduling drift |
| Near-miss `immediate_drift` with an `addiu $sp` frame mismatch | `near_miss_kinds` `frame-padding` (add/remove a pad local to hit the baseline frame) | 2/2 probe hits accepted (first bounded run, 2026-08-27) | — |
| Near-miss `register_allocation_only` / `operand_or_scheduling_drift` | `commute-swap`, `decl-order`, `hoist-temp`, `type-width`, `loop-form`, `reorder-store-call` | 0 hits in 146 attempts on the first run — treat as unproven; prefer hand analysis of the first differing instruction | — |
| Float divide by a power of two | Divide by the **integer** literal (`x / 16`), not `16.0f`: a float literal divisor is strength-reduced to `mul.s` by the reciprocal, an int divisor keeps `div.s` | 1 (`func_8130A98C`) | — |
| Guard/return polarity | IDO branches on the negated condition: write the `if` in the polarity whose negation is the observed `beq`/`bne`, e.g. `if (arg1 == x) { ... } return v;` rather than `if (arg1 != x) return v;` | 2 (`func_81306EE0`, `func_80059234`) | — |
| Display-list append (`Gfx` command into `D_800D0510++`) | Use the real `gbi.h` macros — `gSPDisplayList(D_800D0510++, addr)`, `gDPSetFillColor`, `gDPFillRectangle` — never hand-written `p->words.w0 = ...; p->words.w1 = ...;` stores, which stall at 0.93–0.95 on a constant-load/pointer-increment scheduling swap | 6 (`4AC10.c`: `func_8004AC24/AE3C/AF18/A5B8/A708/AD00`) | RDP texture-load sequences (`gDPSetTile`/`gDPLoadBlock`, `func_8004A010`) not yet tried |
| Several `return 1;` guards sharing one epilogue | A single `return a \|\| b \|\| c \|\| d;` expression; separate guard clauses allocate differently and add bytes | 2 (`func_8130AA54`, `func_80057A80`) | — |
| Wrapper whose callee result feeds a conditional second call | `s32 result = f(arg0, N); if (result != 0) { g(arg0); } return result;` (second call's value discarded; `$v1` spill/reload across the call is the tell) | 3 (`func_8005A0B4/A0F4/A134`) | — |
| Table-field forward with 112-byte stride into bcopy/bzero | Load the field into an explicit `s32 v0 = *(s32 *)(D_X + idx * 112);` **before** the call; inlining it into the argument reorders the frame allocation | 6 (`585D0.c`) | same stride/forward shape |
| Non-power-of-two stride (`arg2 * 47`) | Hoist the multiply into its own local declared **before** the table-load local to fix `addu` operand order | 2 (`func_8005C880/C988`) | — |
| Selector index into two parallel tables | `idx = f(SEL, -1); if (arg0 == 0) D_A[idx * 0xC] + ADD else D_B[idx * 0xC] + ADD` — note the inverted condition sense | 11 (`517E0.c` wrapper family) | — |
| Small struct copy from a returned pointer | Uniquely named `typedef struct { s32 a, b; }` and `*arg0 = *(Pair *)((u8 *)ret + off);` | 3 (`func_80054210/8005493C/8005487C`) | — |
| Nested command constructor from a fixed record | Use a local typed overlay with the proven padding/child field, then pass the nested field directly to the helper; keep each constructor's exact field width | 10 (`229E0.c`: `func_8003FD98/3FE6C/40004/40050/4009C/400E8`; `4EE50.c`: `func_8004E868/4E8D0/4E9C8/4EA60`) | only when the record offsets and helper call shape are proven |
| Fixed-record parser/serializer with narrow fields | Keep the raw record base, use explicit `u8`/`u16` temporaries and direct offset loads/stores; parser loops use the observed break/fill shape, serializers keep the observed conversion order | 8 (`615D0.c`) | exact record format only; do not infer a shared struct from this pattern |
| Byte-indexed state-table loop | Use a byte-typed argument/index, initialize the table pointer before the loop, and preserve explicit post-increment/index updates around the lookup | 2 (`615D0.c`: `func_80060B28/60F98`) | only when the assembly shows byte masking and the same loop-carried pointer |
| Aligned pool wrapper with conditional initialization | Round the requested size with `(arg0 + 3) & ~3`, declare the allocation local before the result, and initialize/return the result only when the block is nonzero | 2 (`3A00.c`: `func_80002E00/030D0`) | same pool-allocation wrapper shape |
| Aligned graph-node constructor wrapper | If the pool handle is nonzero, replace the incoming result with `MainPool_AllocAligned`; if the result is nonzero, call the constructor with the observed old-style narrow-field formals, then return it | 4 (`4EE50.c`: `func_8004E368/4E3C8/4E438/4E52C`) | only for the matching allocation/constructor call sequence |
| Callee prototyped earlier as `void` but its return is needed | Block-scope re-prototype does not work (hard "redeclaration" error); the earlier definition must change to return the value — do it as a separate gated change | 1 (`func_80055BA8`, open) | — |
| Wrapper called with four registers but only three read | Declare only the parameters the body reads (`a3` was caller garbage); the fourth formal changes the frame | 1 (`func_841518D0`) | — |
| General | Preserve narrow `sb`/`sh`/`sw` widths, initialise results before NULL checks, raw 32-bit address arithmetic (`(u8 *)(u32)global + off`) before inferred structs, `uintptr_t` casts for raw addresses, explicit `s32` loop counters, array-index vs pointer-add as separate variants, deliberate signed/unsigned masks | repo scan | ABI hypotheses until compared |

## 5. Hard rules

- Touch **only your assigned file**. Never another agent's `disasm/src/*.c`.
- Runner-only installs (`fleet_probe.py --gate`). Never hand-edit a tracked
  source to test a hypothesis. Never `DECOMP_PROVENANCE_SKIP`.
- Never `git add -A`, `git commit -a`, `git stash`, or `git reset`. Commit by
  **explicit path** (`git add disasm/src/<file>.c ... && git commit`) every
  ~5 accepts, so a broad stage never sweeps up another agent's uncommitted
  work in a shared checkout.
- Never search outside this repository (no `find /`) — SDK headers are all
  under `disasm/lib/ultralib/include/PR/`.
- Stay inside your time box. Stop and report when it expires, even mid-owner.
- **Do not set `CLAIMS_OWNER`.** The runner records an advisory claim on the
  file you install into, using this job's identity. A custom per-agent value
  looks like a different session to `tools/file_claims.py`, and because the
  Bash tool does not carry an `export` from one call to the next, you would
  alternate between two identities and collide with your own earlier claim
  (agents hit `file_claimed_by_other` against themselves, 2026-08-28). If a
  claim warning names another session, that is information, not an error:
  finish your batch, commit by explicit path, and say so in your report.

## 6. Report format

For each accepted owner: one line — spelling/family that matched, evidence
(similarity, gate result), commit sha. Then: total attempted/accepted,
variants probed, the most common `mismatch_kind` you hit, why you stopped
on any owner you gave up on (near-miss similarity + kind), and any new
shape worth a §4 row (spelling + evidence count + limit) for the
coordinator to fold in.
