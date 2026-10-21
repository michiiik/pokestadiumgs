# Fragment 79 record queries and battle snapshots

## 2026-10-21: three matching owners

| Owner | Name | Bytes |
| --- | --- | --- |
| `841555B4` | `BattleRecord_HasPoweredMoveOfType` | 168 |
| `8415565C` | `BattleRecord_HasMove` | 104 |
| `84155750` | `BattleState_PushSnapshot` | 96 |

These 368 bytes join the 468-byte residual planner in `fragment79_3BC290.c`
for a four-owner, 836-byte batch. Address-name aliases preserve callers.

The powered-move query examines at most four move bytes at record offset 4,
stops at the first zero, and requires both the requested move type and a
power byte at least 2. The two real `u8` lookup interfaces are defined in
`src/638E0.c`. Initializing the real counter before the cursor produces the
original s1/s2 roles. The older per-file requeue and the accepted neighboring
query were consulted; an advisory register-tie report did not establish that
the ordinary source could not match.

The move predicate uses an ordinary four-iteration C loop and a real `u8`
current-move local. Stock IDO automatically emits the original four checks;
no source-level unrolling is used. The byte width and current-value-first
equality recover the original branch operands.

Snapshot push copies the original 0x19C-byte state to the slot after the
four-byte snapshot header. The byte index is post-incremented while forming
that destination, preserving the old slot and the original store-before-copy
ordering. This source form also produces the original temporary sequence.
No new bounds checks, widened index, padding, or assembly rewrite is added.

Each first successful runner gate immediately froze source, the full changed
object, four distinct collateral objects, ROM, ELF, and linked script; all
nine were independently rehashed before more compilation. Fifteen complete-
original-object controls across both batch files verify cleanup, formatting,
read-only record views, prototype parameter names, naming, and blank shifts.
Twenty-eight emitted values verify the effect/calculator layouts used by the
paired residual planner. Existing functions and their warnings are preserved.

## `84154B9C`: requeue, team scan loop shape

The draft retains the side table, count byte at 8, 0x58-byte stride, nonzero
0x3E halfword test, and 0x3C byte-mask test. The original is 116 bytes. Ordinary
top-tested loops unroll in this compiler; post-tested/goto and positive-entry
forms avoid some of that growth but still differ in entry/exit instructions
and counter/base ownership. Cached/inline counts, widths, pointer/counter
initialization order, and guard forms were tested without an accepted result.
Next: capture loop lowering and the count/cursor webs rather than repeat this
bounded family. The owner remains assembly; no draft was installed.

Older primary-checkout notes also record unresolved `84154820`/`84154948`
source/layout work. Those owners were not retried in this batch. The existing
`841556C4` query and `841557B0` snapshot-pop body are unchanged.
