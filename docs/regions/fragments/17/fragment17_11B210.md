# Region notes: fragment17_11B210

## 2026-10-18: rendering batch complete, 1828 original bytes

The pending batch comprises CE10 (396 bytes), CB34 (732 bytes), and B984
(700 bytes), all accepted with link verification and full-ROM gates. The
file advances from 15 C / 13 assembly owners after #1191 to 18 C / 10 ASM.
No new runtime function is introduced.

B984 traverses the eight active slots, checking resource, opacity, and both
positive scales. It doubles each scale, computes pixel extents from the
unsigned texture dimensions, rounds them with signed half-unit bias, selects
the slot's texture, emits the white/opacity environment color, and draws the
centered rectangle with reciprocal texture steps. The exact source retains
integer literal division by 2 for the half extents: 2.0f instead strength-
reduces to multiplication, while 2.0 introduces double arithmetic.

After 32 ordinary candidates, a direct symbolic endpoint resolves the saved
register rotation among the loop bound and graphics constants. Initializing
the cursor in a for-loop header resolves the final address scheduling pair.
Neither advisory register-tie warnings nor normalized scores are terminal
proof. The accepted batch is `848eb2208f49401bb0896b6e1098bbba`; first accepted
complete-object SHA256, frozen before further compilation:
`8112466873cf19f12cc84d7215fc6511299f40b5cf78216e94c826697ade56c4`.

Post-accept declaration deduplication, RGB formatting, and loop-endpoint-test
formatting preserve all frozen game bytes, section layouts, defined symbols,
and normalized relocations, including a twenty-blank control. Accepted owners
are not resubmitted as candidates. The three source bodies contain no dummy
locals, artificial homes, fixed registers, loose prototypes, manual unrolling,
or compiler/output modifications. Coverage remains CI-owned and all scratch
generators, compiler diagnostics, objects, and ROMs stay private.

The final cleaned source passes the full-ROM gate, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`, all 427 host syntax checks, 76 native
tooling tests, accepted provenance and whitespace checks. Independent strict
links resolve every undefined symbol at its game address; all 28 original
function extents and complete text including padding agree across the original
and frozen accepted objects. Naming lookup has no established mappings.
The clean publication clone runs 76 tests, with 62 passing and 14 explicit
backend-dependent skips.

## 2026-10-18: panel frame register requeue and search import fault

C6C4 remains assembly after 24 ordinary candidates. The original and the best
candidate both have 1136 bytes and frame 152. Moving the real texture dimension
locals before the RGB buffers restores the original stack offsets 128/132.
The remaining raw score is 0.9014 with the same opcode sequence: full tile width
is saved in s5 rather than s3, its short draw width in s3 rather than s4, and
short draw height in s4 rather than s5. One adjacent instruction pair also
changes order. Explicit short draw dimensions add stack-offset differences.
Pointer/word resource views, coordinate pairs, combined/staged width division,
and initialized/assigned short dimensions do not close this basin.

Known-source, declaration-layout, and twenty-blank whole-object controls pass.
Standalone AST import does not: expanding five graphics macros changes three
instruction-order pairs (offsets 100/112, 144/148, 248/252) relative to the
complete-TU candidate. A private attempt to preserve macro line groups through
permuter annotations also fails the complete-TU fingerprint control. No search
is run after either failure, and neither is evidence of a source/compiler wall.
Next repair and calibrate the macro-aware search import or trace the original
full-TU candidate's three dimension webs. Preserve the original header reads
before the texture-null guard when resuming; moving them changes the program.

## 2026-10-18: eight-piece border accepted, 732 original bytes

CB34 is accepted through the normal native runner with link verification and
a successful combined full-ROM gate, batch `057bc250934e4017999f0c630f85dc32`.
The first accepted complete object was frozen before another compilation:
SHA256 `d637dfb5766075bdc733f6c51dac2e6203e0f4cd90d960264edaf5ca931cfb44`.
The file now has 17 C / 11 assembly owners.

It reads archive 81 entry 0's unsigned texture dimensions, divides its width
into four cells, and draws eight distinct perimeter pieces. Corners use
1024 texture steps; horizontal and vertical edges hold one texture coordinate
fixed to stretch their sampled column/row. The eight calls are separate
corner/edge operations, not an unrolled source-loop workaround. The actual
rectangle helper takes eight signed-short arguments followed by a word cycle
selector; the destination x/y/width/height parameters remain full words.

The initial source has the correct 732-byte opcode sequence and 120-byte
frame, but swaps the full-width tile dimensions' saved registers s0/s1.
Loading both dimensions before the separate width division restores every
word without a forced register, unused local, padding, or prototype change.
Sixteen ordinary candidates cover resource carriers, dimension widths,
texture-coordinate temporaries, and initialization lifetimes. Accepted owners
are never submitted as candidates again; proof and cleanup use whole-TU
controls against the immutable complete object.

## 2026-10-18: scaled interior frame requeue

C470 remains assembly after 24 ordinary candidates. A typed panel parameter,
three-byte RGB aggregates, actual callee prototypes, unsigned texture-width
conversion, and SDK display-list macros reproduce all 596 instruction bytes
except the prologue/epilogue frame adjustments: candidate frame 120, target
128 (normalized/raw 1.0/0.9866). Every used stack offset and other instruction
agrees in the best source. Coordinate pairs versus separate shorts and
pointer versus word resource carriers preserve that basin. A real local panel
alias or explicit float/integer rounded-step value changes used stack offsets
without restoring the target frame. No candidate is link-verified or accepted.

Known-source, prototype-layout, and twenty-blank complete-object controls pass.
The solved fragment20_12C460 renderer provides a useful SDK/source-shape
sibling, but contains an unused two-word array that is deliberately excluded
from this campaign. Adding that array or any artificial frame padding would
not explain this function's real data flow. Next investigate authentic
conversion/expression staging or compiler frame-allocation provenance; preserve
the exact two-word residual rather than accepting a normalized score.

## 2026-10-18: confirmation text address-lifetime requeue

D3C4 remains assembly after 24 ordinary candidates: coordinate pair versus
separate shorts, table cursor versus indexed lookup, for/do loops, and scalar,
record, or menu-header views of the secondary selection. The original is 412
bytes with a 56-byte frame and five saved registers. The best candidate is
424 bytes with the same frame and six saved registers, normalized/raw
0.9528/0.7736. Its selected-field address survives in saved s5 instead of
being rematerialized for the marker and each text row; the short y home moves
from stack offset 50 to 52. Record and menu-header views do not improve it.

Known-source, declaration-layout, and twenty-blank whole-object controls pass.
Strict standalone AST/full-TU linked controls and the imported assembly/retail
control also pass, with every undefined symbol resolved. A 60-second search
with stack differences enabled reports base 782 and lower scores 682/602,
but both improved outputs move font setup across the selected-panel guard
or make the marker unconditional. They are behavior changes and are rejected;
the valid output only changes declaration/line layout and retains score 782.
No search output is installed or credited as progress toward a byte match.

Next measure the address web's allocation cost and investigate authentic
whole-function lifetime or expression lowering. This bounded negative covers
only the listed source families and search; it does not establish a compiler
wall. Do not replay the same bodies, loosen call prototypes, cache the mutable
selection across calls, or add artificial stack homes.

## 2026-10-18: panel background accepted locally, 396 original bytes

CE10 is accepted with link verification and the normal combined full-ROM
gate, batch `effebf5510014b8d9da55817ea25f16f`. First accepted complete
object SHA256: `de88be2469f80dbcd5be3971db45d76dbdd6e73ef162b14adfb9e0c1bde7c9e1`.
It draws the archive-81 resource, derives coordinates from the panel's two
halfword pairs, sets environment/primitive RGB through the SDK macros, and
draws two 300-wide rectangles at vertical offsets 36/172, heights 97/82.
C42C supplies the colors based on the panel's mode field.

The 24-candidate progression isolates genuine local layout: a panel alias
adds eight frame bytes; using the typed panel parameter restores frame 64.
The remaining 13 differing words are stack offsets. Declaring the resource
before the coordinate pair and two three-byte RGB aggregates restores every
word. No artificial padding or stack homes are added. The accepted source
uses Fragment17HalfPair for the coordinates and ordinary SDK graphics macros.
The file advances to 16 C / 12 assembly owners at this acceptance. This owner
belongs to the rendering batch above, separate from the input-handler PR #1191.

## 2026-10-18: menu input family accepted, 692 original bytes

The normal native runner accepts C08C (312 bytes, frame 24), batch
`048efcf2ab0444f4a9333507ed810649`, and C1C4 (380 bytes, frame 48), batch
`deb493e6ac1546daa618c1723c11fb8b`. Both are link-verified and pass the
combined full-ROM gate. The file now has 15 C and 13 assembly owners among
its 28 original positive-sized function extents. No runtime helper is added.

C08C clamps the primary selection to 0..2 using independent up/down checks.
It plays the movement sound only when the selection changes. Confirming the
first two entries sets the exit state and result; the third initializes the
secondary confirmation selection and enters state 3. C1C4 opens the second
panel when its state is zero and handles input when its state is two. Its
secondary selection clamps to 0..1. Confirming zero clears/commits typed save
record 21 through Save_ResetAndCommitTypedRecord; confirming the other entry
or pressing B returns to the primary menu and closes the panel.

The shared 14-byte Fragment17MenuPrefix is a header view, not the complete
allocation. Its selection fields are at offsets 10/12; the second 22-byte
panel starts at offset 42 and has its state at offset 44. Retain narrow stores
and subsequent loads, independent directional checks, and controller reloads
after sound calls. Both functions need a word-sized previous-selection local;
a short introduces extra narrowing instructions. C1C4's panel-state switch
reproduces the original dispatch; an if-chain does not. Its return_to_menu
flag controls the shared cancellation path and is not artificial stack data.

First accepted complete-object SHA256 receipts, frozen before further builds:

- C08C: `1b3fc22807f9457bd9e0324d79a4de0a8b0e5cc440221137d6ef64a5b8663834`.
- C1C4: `117425eeca7fd9c5db34255e0797883841cfbb997d0c11479b369b96ed99491f`.

Strict independent links resolve every undefined symbol at its game address.
All 28 original function starts/sizes, complete linked text including padding,
and every retail function image agree across the original and frozen objects.
Post-accept typed-field cleanup, declaration deduplication and fresh/20blank
controls preserve the complete frozen game fingerprint. Accepted owners are
not submitted as candidates again. Naming lookup has no established mappings.
No dummy locals, forced registers, loosened prototypes, manual unrolling or
compiler/output patches are used. Coverage and private artifacts are excluded.

The final source passes the full ROM gate, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`, all 427 host syntax checks, 76 native
tooling tests, accepted provenance and whitespace checks. The publication
clone runs 76 tooling tests with 14 explicit backend-dependent skips.

## 2026-10-18: panel draw traversal requeue

D560 remains assembly after 40 ordinary native candidates. The original
208-byte function has a 48-byte frame and six saved registers. The best
independent-global traversal emits 220 bytes with a 56-byte frame and seven
saved registers (normalized/raw 0.9273/0.4727). Tested families cover typed
versus offset state access, for/do loops, switch/if dispatch, integer address
carriers, pointer scope, selection predicate spelling, and a typed menu
context with transactional getter updates. The context's 64-byte span and
panel offset 20/stride 22 pass whole-object controls, but its eight candidates
do not match (204/212-byte functions, still 56-byte frames). No context or
candidate source is installed.

Calibrated logging-only stock/off/on/blank controls preserve the known
sibling and candidate objects. Procedure 31's web 40 caches the selected-panel
field address in saved register 20, saving 2.5; relocation inspection identifies
it as D_82210C36. The original instead reloads that address inside the active
panel branch. The candidate also carries the enabled-field address across the
initial guard, whereas the original rematerializes the traversal base.

Strict linked standalone AST/full-translation-unit import controls pass with
every undefined symbol resolved. The imported assembly target independently
agrees with the retail-gated executable. A conservative 60-second search with
stack differences enabled produces no improved output (search base/best 645).
The separately compiled AST's strict score is 652 versus masked 582; scores
refer to distinct compiled sources and are not interchangeable exactness
evidence. No accepted result follows from this bounded negative.

Next inspect authentic aggregate/address expression lowering that avoids
retaining the selected-field address across calls. Keep this owner requeued;
do not replay the completed families or introduce fake homes, volatile loads,
loose prototypes, manual unrolling, or output patches. All retained compiler
and search artifacts are private. Work continues on the same file's controller
input family while this allocation hypothesis awaits a new mechanism.

## 2026-10-18: slot and panel family accepted, 464 original bytes

Four original owners are accepted through the normal native runner, each
with link verification and a successful combined full-ROM gate:

- B850: 176 bytes / 44 instructions, frame 32;
  batch `075276b7577741a9bbaadf4dbb91c234`.
- B930: 84 bytes / 21 instructions, frame 32;
  batch `d46c17384b864291a92e3b97d0a2f4a9`.
- BC40: 60 bytes / 15 instructions, leaf;
  batch `ca4e92e953fd47f6b5dacde9a3a8b34a`.
- BD00: 144 bytes / 36 instructions, leaf;
  batch `daef074e62164d39950572ecdf693285`.

The file advances from 9 C / 19 assembly owners to 13 C / 15 assembly owners
among its 28 original positive-sized function extents. No new runtime
function is added.

### Source and layout evidence

BC7C initializes eight slots with stride 24, storing each slot's state at
pool offset 4 + index * 24 and its final float at offset 24 + index * 24.
B900 clears 196 bytes. Together these establish a four-byte pool prefix and
eight complete 24-byte slots, rather than overlapping 28-byte records.
BC40 searches their state fields in order and returns the first free index,
or -1. The original break/result spelling matches with a typed pool view.

B850 increments the slot counter. Below 21, it computes the short field at
offset 4 as 155 - count * 155 / 20, looks up archive 159 using the selected
12-byte E1D0 frame row, and copies its two float fields to slot offsets
16/20. At 21 or above it clears the slot state. Keep frame selection before
the short-field calculation: reversing them changes temporary allocation.
A local alias for the slot pointer leaves the frame-row spill at 24 instead
of 28; using the actual pointer parameter restores the original home without
adding an unused local. Post-accept typed-field cleanup is byte-inert.

B930 calls B850 for each active slot, advancing a pool-relative cursor by
24 until C20. Its two pointer initializers share one declaration. Splitting
them preserves register roles but changes the order of the low address
instructions. Grouping the real initializers restores all 84 bytes, even
after the advisory runner labels that earlier basin a register tie.

BD00 initializes two mode-specific sets of halfword pairs and always copies
the pair at offset 10 to offset 14, including for other mode values. The
22-byte, halfword-aligned panel view agrees with BF68's traversal stride.
A two-halfword aggregate copy reproduces the original lwl/lwr/swl/swr
sequence; independent component assignments do not. Keep the two-case switch
and offset-based pair names while their complete interpretation is unknown.

BD90 and BE84 set the panel halfword at offset 2 to states 1 and 3;
BDAC and BE94 increment the separate short tick counter at offset 4.
The typed view distinguishes these fields as state and counter. Correcting
their names preserves the frozen complete-object game fingerprint.

### Acceptance controls

Each first accepted complete object was frozen before further compilation:

- B850: `ef6eeee72cd207fa81625cffa91267b7b350e1f2de121597a59fc0bdbf2434d3`.
- B930: `712ccad8fdf06834e8a2512c06f97aabff0845c49c88de790aaf9941b315f777`.
- BC40: `2ecfe22071c83938545ab2b2fc0b2e30080a549e7316e6e9c1bff8aeb6a878cf`.
- BD00: `1cdecd236fedb71910cde55952efa22cfeca2ab18b30b2c28192268e1eb35353`.

Independent strict links resolve every undefined symbol at its actual game
address. The original and every frozen object's complete linked text,
including padding, agree; all 28 function images also agree with the
retail-gated executable. All original starts and sizes are preserved, and
the object has no other allocatable section to hide collateral changes.
Known/type-layout/twenty-blank controls pass. Typed-field cleanup and extern
deduplication reproduce the final frozen game bytes, layouts, defined
symbols and normalized relocations. Accepted owners are not candidate
probes again.

The cleaned source passes the full ROM gate, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`, all 427 host syntax checks, 76 native
tooling tests, accepted provenance and whitespace checks. The naming plan
has no established mappings, so address names remain. No fake homes, dead
locals, fixed registers, loosened prototypes, padding, manual unrolling or
compiler/output patches are used. Coverage remains CI-owned; generators,
diagnostic copies, objects and ROMs stay private.

## Earlier handoffs retained from the shared region notes

The available statistics omit the older rows below; zero recorded attempts
in that snapshot does not make these owners fresh.

- BDAC remains `register-tie`: cached-divisor source reaches 216 bytes and
  normalized/raw 1.0/0.8400, with v0/v1 counter/divisor roles swapped from
  offset 4. Direct/cached loads, widths, declaration order, register hints,
  pointer/global aliases and a 75-second search did not close it. Retain the
  divisor-before-increment family for a measured allocator/permuter follow-up.
- BE94 has the corresponding 212-byte `register-tie`, normalized/raw
  1.0/0.8367 and the same offset-4 role swap. Reload the short count after
  incrementing it, retaining a divisor loaded beforehand. The older bounded
  search had no output; do not replay the completed source grid unchanged.
- C340 remains `requeue`: best recorded 232 versus 236 original bytes,
  normalized/raw 0.8644/0.7966. CSE retains C30 in saved s1 instead of using
  a0 initially and separate C30/C5C iteration addresses later. Switch/if
  dispatch and the 22-byte record overlay were already tried. Investigate
  genuine address-expression/aggregate context, not a forced address alias;
  neither interpolation helper is accepted C.
