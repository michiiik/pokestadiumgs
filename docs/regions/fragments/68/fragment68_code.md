# Fragment 68 code matching notes

## func_8F000020

Accepted recipe: preserve the one incoming word while allocating through `func_80041C98(5)`, calling the actual no-argument `func_80041E2C`, and forwarding the returned pointer to `func_80042C68` with both dimensions equal to 128. Store the real returned pointer in `D_8F000924`, clear bit `0x100` of its first halfword, clear `D_8F00092C`, and set `D_8F000920` to zero or the nonzero incoming word minus one. The existing unknown global names are retained; no fake, semantic name or artificial argument is introduced.

Original `func_8F0007E8` forwards its first incoming word from its real stack home and ignores the owner's result. The owner has a complete 30-instruction body, a 32-byte frame and one incoming argument home, with no trailing padding or shared switch tail. Original `func_80041C98` takes one word and returns an allocated pointer; `func_80041E2C` reads no incoming arguments; `func_80042C68` takes the real pointer and two word dimensions, stores those dimensions as halfwords, and returns the allocated object. The helper declarations follow those definitions rather than unrelated stale word-handle declarations.

History audit: fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt or fragment 68 regional document in the consulted catalog. No historical normalized or raw similarity score is available for this owner. Current master has no regional document at this path. All open PR scopes were inspected; only documentation draft #922 was open, and its scope did not cover this owner.

Independent validation against master `3bea111c0caa68eed37a2c812c4adab1f491c75f`: the first pointer initializer recipe passed the full US ROM build with default host syntax checks and `COMPARE=1`, then `md5sum -c baseroms/us/checksum.md5` passed with retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. All 198 previous matched US owners and foreign #930 remain present. The current-head and merge-result Public PR ROM Gate must actually run its checksum build before merging; skipped draft checks do not count.

## Native menu lifecycle batch, 2026-10-15

Base: public master `624b540` (#942). Solo native Mac work, no containers or
delegation. Before probing, fresh and 20-leading-blank builds reproduced the
complete file text and all three already accepted siblings exactly. No local
probe-history rows existed for the five remaining owners. Three owners are now
accepted by the normal runner, each link-verified with one combined full-ROM
gate and default host syntax checks enabled:

| Owner | Instructions / bytes | Frame | Accepted batch |
| --- | --- | --- | --- |
| `func_8F0007E8` | 66 / 264 | 0x28 | `705fa2940bae40dabeccab5226deb2b9` |
| `func_8F000524` | 90 / 360 | 0x28 | `34bf756348dc4324b1d393d28f7eb505` |
| `func_8F00068C` | 79 / 316 | 0x50 | `3e032be0caf24d4396d8cf1da9dec150` |

The entry point keeps both real incoming word homes, passes the first word to
the existing initializer, and returns the existing result helper. Preserve the
resource setup/teardown call order and `0x4442534C` pool tag.

The state handler uses a separate next-state local initialized from the input;
mutating the parameter instead produces a 0x20 frame and wrong stack offsets.
Preserve both independent navigation tests, their 0..15 wrap, the previous
selection comparison, accept-before-cancel priority, cancel selection -1,
fade initiation, and the unknown-state default return. A signed comparison is
required when decrementing selection below zero.

The frame loop snapshots the actual six-byte record behind object+0x1C at
node+0x1E, restoring it only when `func_80043064` reports an update. It reloads
the node pointer for the restore after calls, rather than assuming it cannot
change. A real countdown local plus the persistent state local puts the saved
record at stack+0x40, with no padding or dummy local. Without the countdown
local the same 316-byte body differs only in that stack address (0x44/0x48).
Keep the countdown reset to 150, index wrap at 252, output assignment, frame
render call and state transition order, and first-iteration execution.

Post-acceptance cleanup removes duplicate declarations and expands compact
branches. Fresh and 20-leading-blank controls reproduce complete text, data,
rodata and bss and all six accepted functions. A fresh native full-ROM build
after cleanup passes `COMPARE=1`, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. The naming plan maps the entry point to
`fragment68_main`; its source definition uses that name with the old address
name preserved by a compatibility alias, without changing the symbol table
or original assembly oracle. No mapping exists for the other two owners.
Scratch generators, probe
objects, binaries and ROMs are not part of the published batch.

### Remaining renderer handoffs

- `func_8F000098`: requeue, best normalized 0.9919 / raw 0.9675, 492 bytes
  and correct 0x38 frame. Exactly four positional differences are in the
  `D_8F000914` toggle at offsets 0x3C, 0x40, 0x44 and 0x4C: target uses
  `lui t9; lw t9; lui at; ...; sw t0,lo(at)`, while the candidate materializes
  the address in v0 with `lui; addiu; lw; ...; sw`. The remainder, including
  text calls, selection colors, loop, quotient/remainder layout and saved
  registers, matches. Thirty-two normal cells covered loop bounds/divisor,
  declaration order, separate XOR assignment, unsigned value/load views,
  temporary toggle values, scalar/array storage views and local line grouping.
  None closes the address-materialization shape; do not replay these cells.
  Next: inspect the optimizer's address-expression decision in this toggle,
  with a calibrated known-matching sibling, rather than more XOR spelling.
- `func_8F000284`: requeue, best normalized 0.9610 / raw 0.4675, 612 versus
  616 target bytes, correct 0x58 frame. Natural three-loop tiled rendering
  reproduces the display-list operations and scroll updates, but a hoisted
  640 loop bound occupies a saved register where the target retains tile
  constant 0x07000070. Twenty-four cells covered row offset versus derived
  multiplication, comparisons, first-tile predicates, do-loop topology and
  explicit standard GBI calls with line grouping. Do-loop cells are worse;
  explicit macros do not repair allocation. Next: audit whole-loop roles and
  constant lifetimes before a focused allocator experiment. No renderer body
  has been installed, and these bounded negatives do not prove C impossible.
