# Fragment 45 text references and panel visibility

## Accepted batch against master `43aced10`

| Original owner | C name | Instruction bytes |
| --- | --- | ---: |
| `func_8AB02F94` | `TextReference_GetText` | 76 |
| `func_8AB04BD4` | `TextPanels_UpdateVisibility` | 192 |

Total: 268 bytes. Existing implementations on master, including
`func_8AB02C20`, `func_8AB02EF8` and `func_8AB02FE0`, are preserved. They are
excluded from the new-owner count.

### Reference lookup

Each reference contains an unsigned 16-bit archive ID and entry ID. The
unsigned 16-bit index selects a four-byte pair. Capturing both keys before
calling `func_8004C874` reproduces the original argument-home store and
register allocation; caching only the reference pointer does not. A failed
lookup returns `D_8AB1143C`, whose existing data is the string `NULL`.

`src/4CC20.c` defines the two-argument text lookup as a pointer-returning
wrapper over `func_8004C7A0(NULL, 0, archive, entry)`. Its stale signed-word
return declaration in this unit is corrected to that definition. The
separate declaration-only gate preserves the entire module and retail ROM.
No extra argument inferred by a standalone draft is added.

### Visibility update

An ordinary four-iteration `for` loop selects between the first two panel
arrays according to the word at `D_8AB14218`; the third and fourth arrays
are always enabled. Bit 0 of each node's flags halfword at offset 2 controls
render traversal in `func_8004ECD4` (`src/4F800.c`). The neighboring
`func_8AB04AE4` clears the same bit when hiding these panels.

Explicit pointer-walk loops trigger compiler unrolling and grow to 504-516
bytes. Indexing the four pointer arrays lets the compiler recover the
original 192-byte loop and strength-reduced pointer walk. No loop is manually
unrolled, and no dummy storage, forced register or instruction rewrite is
introduced.

### Verification

Normal host-syntax-enabled full-ROM gates pass, including the final named
and declaration-cleaned source. US MD5:
`1561c75d11cedf356a8ddb1a4a5f9d5d`.

Independent comparison preserves all 23,008 text bytes, 48 rodata bytes,
81 function starts/extents, full linked fragments 45/50/79 and four collateral
objects. Frozen inputs, objects, linker output, ELF and ROM have externally
checked hashes. Fresh and leading-blank controls cover the native proposal,
public proposal and unchanged public predecessor. The public Python suite runs
77 tests with 14 skips and no failures.

The reference getter has direct link verification. The visibility loop goes
through the sequential ROM gate because its endpoint uses
`D_8AB14458 + 16`, equivalent to fixed symbol `D_8AB14468`. One shared HI16
record represents the endpoint addend while serving both same-page low
halves; its rounded high-half value is unchanged. The allowed relocation
sites and both fixed symbol addresses are checked explicitly, and all linked
fragment bytes remain identical. The baseline also preserves an existing
upstream `D_8AB11210 - 8` reference to `D_8AB11208` in `func_8AB05254`.

Object-level negative controls reject changed text, rodata, endpoint addend,
shared high page and relocation symbol. Coverage files and private probe,
compiler and proof artifacts are excluded from this batch.

## Remaining work: `func_8AB03194` / register-tie, requeue

The preload loop copies archive/entry pairs to `D_8AB14D08`, resolves each
pair through the real two-argument text lookup, appends two `0xFFFF`
halfwords and returns the masked count. The retained scalar reconstruction
has the original 152-byte extent, 40-byte frame and complete opcode sequence,
but raw similarity is 0.8158: the first key uses v1 where the original uses
a2, with related call-argument temporary differences.

Direct destination reads, source snapshots, narrow/word key locals,
postincrement copies, masked word returns and declaration-order changes were
compared. A calibrated 90-second four-worker source search reproduced all
38 base words and relocation targets; score improved from 40 to 35 through
a named terminator. Its other proposal adds a redundant value alias and is
excluded. Using a named terminator throughout the loop and tail still leaves
the measured register residual. Eight unsigned-word key variants instead
produce 148-byte bodies (best raw 0.7368). No preload body is installed.

Next action: observe the scalar-key global-color decisions and their
interference before another source campaign. Preserve the two real lookup
arguments and the signed count increment followed by unsigned return masking.

## Three-word audio event forwarding

At public baseline `01b387fd38c0c8ec7d718631b138a60aa55e7e8c`, `func_8AB00BA4`
has a no-argument C signature, although its assembly callers `func_8AB03D10`
and `func_8AB03DFC` supply three values. The downstream `func_80024F20` reads
the incoming a0, a1 and a2 words in `hand_asm/229E0/func_80024F20_manual.s`;
it overwrites incoming a3 before use. The wrapper now forwards all three words
explicitly with matching prototypes.

Four fresh native whole-module controls (before, before plus leading blanks,
after, after plus leading blanks) preserve all 23008 text bytes, 48 rodata
bytes, 81 function extents and semantic relocations. The normal host-syntax
full-ROM gate and independently frozen linked-fragment/collateral checks pass
at native commit `b9affee9`; retail US MD5 remains
`1561c75d11cedf356a8ddb1a4a5f9d5d`. This changes an existing C definition's
signature and adds no newly decompiled owner.

## Accepted orange row state

`func_8AB03D10` is now `TextRow_SetOrangeState` (236 bytes). It emits the
three-word event, increments the row count when entering from state zero,
enables the selected panel and optional secondary node, writes orange
`0xFF500080` and texture entry zero to their highlight records, then records state one.
The input dispatchers in `fragment45_22AB80/func_8AB06D78` and
`fragment45_2348E0/func_8AB1075C` call it for the current panel index and ignore
its return. The name describes the observed writes without assigning an
unproven gameplay meaning to the row.

The decisive source change splits the record address into a base assignment
and an indexed offset addition. A calibrated 90-second four-worker source
search reproduced all 59 base words and relocation targets, then found this
single, behavior-preserving transformation at score zero. The normal runner
accepted it with `link_verified: true`; the host-syntax-enabled retail-ROM gate
and independently frozen full-module, linked-fragment and collateral checks
pass. The old symbol remains a linker alias for existing assembly callers.

## Blue row state / requeue

`func_8AB03DFC` remains assembly. Its ordinary C reconstruction emits event two,
sets blue `0x1E82FF80` and texture entry one on the selected highlight and optional
secondary node, and writes row state two. Base-plus-offset construction
recovers the original 216-byte extent, but the address-calculation schedule
still differs (best normalized 0.7407, raw 0.5926 among that family).

A calibrated 90-second four-worker search reproduces all 54 base words and
relocation targets; its best score is 560 from 1890. That proposal adds and
reuses an unjustified row-index alias and is excluded. Eight explicit row-offset
variants also reject. Next action: inspect the actual record and embedded-node
construction to explain the interleaved row/highlight address calculations.

## Preload interference / register-tie, requeue

Eight fresh stock/off/on/leading-blank controls preserve the complete known
module and retained 152-byte preload proposal under a logging-only compiler.
For proposal archive web 10, the measured interference neighbors are the entry
key (web 18), count (7), destination (4), source (0) and terminator (42). The
entry key receives v0 before the archive key receives v1. These observations
cover the proposal, not unavailable original source; logging changes are
private and the acceptance compiler is unchanged.

A follow-up eight-body campaign tests source postincrements, while-condition
assignment and entry-copy assignment/reuse. No owner is accepted: the retained
152-byte opcode-equivalent body remains raw 0.8158. Rereading the copied entry
reaches raw 0.8684 but changes opcode order (normalized 0.9737), so it is not
an instruction-equivalent improvement. Next action: inspect whether a real
record view can leave the entry as an expression temporary while carrying the
archive through its compare, copy and argument normalization. Preserve the
actual two-argument lookup contract.

Subsequent entry-expression/one-sided source-record and aggregate key-pair
campaigns accept no preload owner. A word-valued key-pair local reproduces the
152-byte opcode-equivalent scalar result (raw 0.8158); narrow aggregate and
while-assignment forms change frame sizes or instruction order. These measured
negatives narrow the next lifetime experiment; they do not establish that the
original archive register is unreachable from ordinary C.

## Blue-state construction evidence / requeue

The constructor `func_8AB04210` passes the four embedded addresses
`D_8AB12CC8`, `D_8AB12D5C`, `D_8AB12DF0`, `D_8AB12E84` (row base plus 24,
stride 148) to `func_8AC05E40`, then binds each through `func_8AC06400` to the
node pointer at row plus 20. Both callees are in fragment 43's
`src/fragments/43/fragment43_1E5A10.c`. The same constructor initializes the
four 120-byte `D_8AB14278` highlight records with those callees.

`func_8AC05E40` clears 120 bytes, copies the 56-byte resource header, and
registers `func_8AC049A8` against the destination. `func_8AC06400` initializes
the two scale floats at offsets 64/68 and derives the center at 72/76 from
node coordinates and dimensions. This establishes that the row's secondary
highlight at plus 24 is the same concrete 120-byte object as a panel
highlight; it is stronger evidence than matching offsets alone. Next action:
read that renderer and use the actual embedded-object relation to test the
blue caller's pointer lifetimes, without inventing fields or padding to fill
the still-unexplained row prefix and final four bytes.

## Highlight texture key / requeue

The callback `func_8AC049A8` in fragment 43 loads unsigned halfwords at
highlight offsets 36 and 38 into a0/a1 and passes them to `func_8004C990`.
That lookup selects the archive at the first key and an indexed texture entry
at the second; `src/4CC20.c` also uses it to populate
`D_80128080.texture`. Therefore the row-state stores at highlight plus 38
(and row plus 62) select texture entry zero or one. They are not a distinct
animation-mode field.

Eight embedded-highlight lifetime variants and eight unsigned/key-prefix views
reproduce the earlier blue-state outcomes: the 216-byte split-base construction
has an exact prologue and exact state-update tail, with differences localized
to offsets 64 through 156 in the interleaved row/highlight address calculations.
A field-typing change alone does not close that instruction-order residual.

## Accepted model preview and text callbacks

Against public master `1b390fce1b246409ad8b2cb7c8fb675770fe7f0f`:

| Original owner | C name | Bytes |
| --- | --- | ---: |
| `func_8AB01ED4` | `TextPreview_InitializeModel` | 172 |
| `func_8AB0178C` | `TextNumber_DrawCallback` | 196 |
| `func_8AB01850` | `TextLabel_DrawCallback` | 360 |

Total: 728 bytes. All three have normal runner acceptance and independently
frozen full-module/linked-fragment/collateral proofs. The initializer uses the
existing `PokeIcon_AllocLoadContext` alias instead of its address-keyed name;
its sequential retail-ROM gate verifies that relocation spelling. Both
callbacks have direct link verification.

The initializer allocates the context, creates an 80-by-80 model preview,
sets its clear color to zero, selects the species, sets flag 0x100, clears
flags 2/4, and clears `D_8AB126A0`. The producer and preview API are defined
in `src/229E0.c` and `src/43700.c`.

The number callback reads the signed halfword through the node's data pointer,
clamps negative values to zero, obtains the current origin with
`func_800504BC`, and adds the node's relative coordinates. It copies the actual
four-byte color and passes RGB to `func_8AB00BC4`, which draws decimal digit
textures. Phase zero clears node flag 2; phase one draws. A real counter
pointer, coordinate pair, color copy and coordinate locals recover the
72-byte frame. Computing coordinates before the color copy, then arranging
those existing locals, closes the measured stack offsets and operand order;
no extra storage is added.

The label callback uses the same origin and two four-byte foreground/shadow
colors. If the distinguished node's text pointer is null, it uses the existing
`D_8AB11400` string (`NULL`, decoded from the linked retail fragment). Font
setup and drawing use the APIs in `src/47580.c`. Its unsigned alignment local
maps the low nibble at node plus 39 as 2->0, 1->2, 0->1, default->0. The
source arm order and real local storage recover the original 64-byte frame
and dispatch. It returns zero on every path, as the original assembly does.

## Accepted preview image rendering

Against public master `413f40ec4867ac200b5155adfa4ca4342e790270`:

| Original owner | C name | Bytes |
| --- | --- | ---: |
| `func_8AB01FC8` | `TextPreview_DrawRgba16Rect` | 632 |
| `func_8AB02240` | `TextPreview_DrawImage80` | 268 |

Total: 900 new instruction bytes. Both owners have ordinary runner acceptance
with direct link verification and independently frozen whole-module,
linked-fragment, collateral and retail-ROM comparisons.

The rectangle helper is exactly the standard `gDPLoadTextureBlock` and
`gSPTextureRectangle` macros: RGBA16 pixels, a supplied source stride and
height, clamped tiles, and 1:1 texture steps. Its signed-halfword coordinate,
dimension and stride arguments reproduce the original parameter-home accesses.
The first typed, separate-line proposal matches; no command words are written
by hand and no instruction or relocation is post-processed.

The image wrapper draws twenty four-row strips from an 80-by-80 image. An
ordinary twenty-iteration loop indexes `y + row * 4` and advances the source
pointer by 640 bytes. The compiler creates the original four-row induction
step and 80-row limit. Fully indexing both the coordinate and source instead
creates a byte-count induction variable and a 12800-byte limit; mutating both
parameters changes normalization and scheduling. The mixed form closes the
measured residual without changing the matched helper's interface.

`D_8AB111B0`/`D_80094F50` bracket the loop. The fourth argument supplies the
primitive LOD fraction through `gDPSetPrimColor`; its RGBA value remains opaque
black. `func_8AB05300` obtains the pixel address from `func_80043678` on the
preview state and stores it in `D_8AB16794`. The existing dispatcher now casts
that address word explicitly at its two pointer-typed draw calls. The producer
and image-descriptor access are defined in `src/43700.c`.

The eight logical-line grouping probes for `func_8AB03DFC` retain the earlier
216-byte result (normalized 0.7222, raw 0.6296). That family is a measured
negative for the blue caller, not a reason to repeat it or declare the caller
unreachable. Its next hypothesis must change the address-expression input to
uopt rather than the tested statement groupings.

## Formatting-sensitive compiler input / verified replay identity

A calibrated 90-second four-worker label search reproduced all 88 parent
words/relocations, then reduced its score from 974 to 723 through formatting
alone. The label was subsequently matched through token-changing source
mechanisms above; the formatted search result itself was never installed.

Eight fresh stock whole-module controls compare the known source, calibrated
parent, and two token-identical formatting fixtures, each with and without
20 leading blank lines. The known source preserves the complete retail module;
the parent reproduces its retained function words; each uniform-blank pair
preserves complete sections, extents and relocations. The two fixtures both
have 352-byte label bodies but different generated instruction bytes.

`tools/candidate_identity.py`, merged in PR #850, already preserves the
token-bearing logical-line groups that distinguish these two fixtures. An
audit of the active native runner confirms its rejected-body preflight calls
that identity for both bodies and shared declarations. The fixture's formatted
body remains eligible after the other form is rejected; exact, indentation-only
and leading-blank repeats are refused. All 14 existing identity tests pass.

There is no formatting-replay blocker in this tested native runner. Integrators
should use the existing identity module rather than a whitespace-collapsed key.
The acceptance verifier remains unchanged: the rejected 352-byte proposals
have layout drift and are not ROM matches.

## Existing draw dispatcher / register-tie, requeue

`func_8AB0234C` was already C at public baseline `413f40ec`. Its empty
`if (D_8AB14678)` is now explicitly marked `FAKE`; this batch does not count
that existing 160-byte function as a new decompilation or claim it is cleaned.
The real operation checks view states 2/4 and ready state 2, draws with LOD
fraction 255/0 respectively, then returns the ready field to state 1.

Fifty-six cleanup fixtures cover state snapshots, direct global reads,
equivalent guards, switch/if forms, ready-value predicates, node/coordinate
locals and minimal removal of the empty check/repeated read. The closest
ordinary C keeps 160 bytes and differs at six word positions: comparison
operand order and the shared constant 2 using v1 instead of a1. None preserves
the complete module. No rejected cleanup body is installed.

A calibrated 90-second four-worker cleanup search reproduces all 40 parent
words and relocation targets. Its best score is 45 from 50, through a redundant
literal alias; that proposal is excluded. Next action: compare the constant-2
uopt coloring/interference in the existing implementation and the retained
clean reconstruction, then find a real value-lifetime change. Preserve both
full-ROM-matched image functions while doing so.

## Accepted highlight scale animation and literal ownership

`func_8AB03ED4` is now `TextHighlight_AnimateScales` (356 bytes). It applies
`1.0f + cosine * amplitude` to both scale fields at offsets 64/68. Four panel
highlights use stride 120 and amplitude 0.1f; their phase halfwords advance by
2048. Four row highlights use stride 148 and amplitude 0.2f, reading the
updated phases. The cosine lookup is `D_80088E50[phase >> 4]`, also used by
rotation calculations in `src/229E0.c`. The original symbol remains an alias.

The file's `.rodata` window now starts at ROM 0x236890 instead of 0x236930.
Both boundaries are 16-byte aligned. Pinned spimdisasm 1.35.0-dev0 moves the
0.1f/0.2f literals into this owner's `.late_rodata`, the neighboring 0.1f/0.9f
literals into `func_8AB04038`, and tables `jtbl_8AB11720`/`jtbl_8AB11750` into
`func_8AB04210` and `jtbl_8AB11780` into `func_8AB04EE8`. The existing table
`jtbl_8AB117B0` stays in the same file. This assigns 208 existing ROM bytes to
the source object without changing their linked positions.

Treating the amplitudes as extern globals produced a setup-scheduling
near-match. Ordinary float literals recover the intended instruction shape;
the literal-pool ownership change lets those bytes link at their original
addresses. The accepted C uses indexed loops and real amplitude values; IDO
performs the observed pair unrolling of the row loop. Operand order matters:
the gate accepted `1.0f + cosine * amplitude`.

The still-assembly ownership split first passed the ordinary retail-ROM gate.
The C replacement then passed the runner's sequential full-ROM gate; its
object comparison reported relocation drift, so link verification alone was
not its acceptance evidence. The named source also passed a fresh ordinary
host-syntax-enabled gate. Independent checks cover the complete 23008-byte
text, 208-byte rodata, all 81 function extents, resolved relocation targets,
three linked fragments and four collateral objects. The US ROM MD5 remains
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Neighboring assembly owners are not counted
as newly decompiled functions.

## Edge-scale animation / tooling-blocked, requeue

`func_8AB04038` remains assembly (472 bytes). Constructor `func_8AB04210`
initializes four 120-byte highlight records at `D_8AB14468`, `D_8AB144E0`,
`D_8AB14558` and `D_8AB145D0` through `func_8AC05E40`, then binds each through
`func_8AC06400`. The animation advances four halfword phases at `D_8AB14670`
through `D_8AB14676` by 4096. It applies 0.1f cosine plus 0.9f to alternating
Y/X/Y/X scale fields. Their corresponding center-relative offsets use
minus/plus/plus/minus cosine times the appropriate dimension times 0.1f.
These are four distinct edge operations; proposed C retains a phase loop and
does not manually unroll that loop.

Sixteen calibrated runner proposals test first-record scalar/record access,
walking/indexed remaining records, amplitude locals, an actual phase pointer,
and one four-phase versus two two-phase loops. No owner is accepted. The
proposals have 400-504 bytes and differ in address scheduling, repeated cosine
loads and float allocation; the best normalized result is 0.5678 (412 bytes),
which is not an instruction-equivalent near-match.

The frozen linked fragment confirms a shared `lui $at` at owner offset 8 and
four `sh` instructions at offsets 20/40/60/80 addressing 0x8AB14670/72/74/76,
without any intervening write to $at. Unrelated instructions separate the
stores. The ordinary phase-loop proposal emits three extra `lui $at` loads.
This is the interleaved shape excluded by the current contiguous-only
coalescing mechanism. The existing symbolic scanner misses this site because
its `%lo` parser stops at addend-bearing operands; the evidence here comes
from decoding the frozen linked words and checking the register writes.

Next action: preserve this concrete interleaved-site evidence and resolve a
compiler-faithful address-reuse mechanism before spending another body batch.
The literal ownership prerequisite is fixed; it does not resolve this separate
shared-address shape. Keep the accepted scale animator and its ordinary ROM
proof intact while continuing other owners.

## Accepted reference and choice shuffles

`func_8AB02A58` is now `TextReference_BuildShuffledRange` (336 bytes). Like the
neighboring `func_8AB029BC`, it first writes consecutive IDs into
`D_8AB14680`. For counts of at least two, it performs 500 swaps, drawing two
signed-halfword indices through `func_8AB023EC` and resampling the second until
they differ. `func_8AB02EF8` consumes those IDs as indices into the text-reference
pointer table `D_8AB11D10`.

`func_8AB02438` is now `TextChoice_ShuffleAndRefresh` (524 bytes). It performs
100 distinct-index swaps of archive/entry pairs at node offsets 48/50 and
updates the selected-choice index `D_8AB1269A` when that choice moves. Its real
52-byte node copy supplies the saved pair; the preceding twelve words remain
unknown node data. It then calls `func_8004C8A0` for four 256-byte buffers,
updates the associated visibility flags, clears four row states and sets
`D_8AB1269C` to 20. `func_8AB04C94` uses that field as its marker draw count
and switches color below four. Texture lookup semantics follow the
archive/entry parameters of `func_8004C8A0` in `src/4CC20.c`.

Both owners accepted on their first candidate with object link verification
and ordinary host-syntax-enabled full-ROM gates. Independent complete-module,
resolved-relocation, linked-fragment and collateral checks pass. Both original
symbols remain linker aliases. The new accepted batch totals 860 bytes.

## Frame rendering dispatcher / register-tie, requeue

`func_8AB04EE8` remains assembly (708 bytes). Its `jtbl_8AB11780` ownership is
ready after the aligned literal-window split. The recovered flow updates the
countdown and background, enables/disables six nodes in modes 4/6/8, renders
through the mode table, draws the preview, increments/wraps the frame counter
and submits the frame. Source case order is 0/1/2/3, 11, 4/5, 6, 8, default.

Forty calibrated proposals cover direct/pointer timer access, real background
and node snapshots, typed flag headers, real flag locals and the final frame
status return. A background snapshot recovers the original opcode sequence
and 708-byte size (raw 0.5819). The best clean proposal additionally loads,
masks and stores the final node's flags through a real u16 local; it remains
708 bytes/opcode-equivalent and reaches raw 0.8079. Grouping node snapshots
and forwarding the final s32 frame-status return do not resolve the residual.
The boolean countdown assignment changes the owner to 688 bytes and is worse.

A 90-second four-worker source search first reproduces all 177 masked words,
callee targets and twelve owner-relative table branches of the retained
parent. The calibrated search descends from score 730 to 485 only by adding
a dead assignment of node flags to the background variable. That proposal is
excluded. Context calibration resolves internal-definition versus external-
prototype callee spellings by actual symbol identity and checks all table
branches; no native hypothesis was accepted from the search.

Next action: capture calibrated uopt/ugen traces for the best clean flag-local
proposal. Its first address load at offset 32 uses t4 where the original uses
a0; offset 92 uses a0 where the original uses t6. The final node's flag value
is colored v0 rather than emitted through the original temporary registers,
which also shifts later temporary choices. Identify the real value/address
lifetime before another source batch. Preserve the matched shuffle owners and
the full 208-byte rodata window while doing so.

## Accepted marker renderer

`func_8AB04C94` is now `TextInterface_DrawMarkers` (580 bytes). It emits
3-by-7-pixel rectangles at five-pixel X intervals, starting six pixels from
both coordinates of the node referenced by `D_8AB14190`. `D_8AB1269C` supplies
the count. Counts below four choose environment color 0xFF5A96FF; otherwise
the color is 0xFFFF00FF. The function does not modify the count.

The display-list setup decodes to the standard GBI pipe sync, one-cycle mode,
texture enable, culling/lighting clear, affine texture perspective, opaque
surface render mode and environment-only color/alpha combine. All setup and
rectangle commands are written with their standard macros.

An explicit spacing variable swapped the X/spacing carriers. Using `i * 5`
recovers the original opcode sequence, but a named node pointer still swaps
X and node registers. Direct reads of the global node's two coordinates match
all instructions. The runner accepts this source with link verification and
an ordinary full-ROM gate. The named source also passes a fresh ordinary gate;
independent full-module, resolved-relocation, linked-fragment and collateral
checks pass. The original function symbol remains a linker alias.

## Earlier literal/table window / layout-prerequisite

The current 0x236890 rodata window still excludes the five literals used by
`func_8AB0148C` at ROM 0x2367D4..0x2367E4, both tables of `func_8AB02D14`
at 0x2367E8/0x236818, and the table of `func_8AB03394` at 0x236848.
A proposed earlier aligned start of 0x2367E0 covers all three tables and the
last two literals, while leaving the first three literals in the shared blob.
That proposal has not been split or ROM-gated. It is layout preparation for
the table owners, not evidence that the entire float owner is ready. A start
at 0x2367D0 intersects the preceding debug string and requires separate string
ownership analysis. Gate any further layout split with the owners still in
assembly before replaying C candidates.
