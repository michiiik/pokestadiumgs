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

## Accepted mode-selection initializer and earlier table ownership

The file's `.rodata` window now starts at ROM 0x2367E0, extending the previous
0x236890 window by 176 bytes. Its 384 bytes retain their original linked
positions. Pinned spimdisasm 1.35.0-dev0 assigns the last two literals of
`func_8AB0148C`, both `func_8AB02D14` tables at 0x2367E8/0x236818 and the
`func_8AB03394` table at 0x236848 to their owning assembly functions. The
still-assembly layout passed the ordinary host-syntax-enabled retail-ROM
gate and independent linked-fragment/collateral checks before C probing.

`func_8AB02D14` is now `TextReference_BuildModeSelection` (484 bytes). It clears
reference state through `func_8AB003E4`, then selects the start/count by mode
or the existing subtype helpers. Its second switch calls `func_8AB02644` in
modes 1/2/3, the consecutive-range initializer in mode 0, writes one reference
in mode 11, or resets and builds a shuffled range otherwise. It refreshes the
mode before that second dispatch. Both twelve-entry tables preserve the
original source-case order and branch targets.

A word-sized `mode` declared before halfword `start` gives the original
`start` home at sp+0x1A. Halfword-mode versions or the opposite declaration
order instead put it at sp+0x1E. Both locals are used by the two switches;
the matching source adds no padding or dummy values. The runner's
relocation-masked object hit was not link-verified, so acceptance came from
the sequential ordinary full-ROM gate. The final named source passed another
ordinary gate and independent complete-module/resolved-relocation checks.
The original function symbol remains a linker alias, and the existing
`func_8AB03CE8` C wrapper calls the new name at that same address.

### Remaining early float ownership / layout-prerequisite

The first three literals used by `func_8AB0148C` at ROM
0x2367D4/0x2367D8/0x2367DC remain in the shared blob. Only its last two literals
are inside the new window. That float owner is still assembly and is not
fully ready for a literal-based C reconstruction. A start at 0x2367D0
intersects the preceding debug string and requires separate string ownership
analysis. `func_8AB03394` remains assembly, but its complete table is now owned.
Neither neighbor is counted as a new decompilation in this batch.

## Command interpreter `func_8AB03394`: requeue / layout-prerequisite

The 384-byte rodata window introduced with the mode-selection dispatcher
owns this interpreter's complete 18-entry table. Table ownership is ready;
the function remains assembly. Against native revision `1f74b338`, 32 compiled
source proposals reconstruct the command parser, reference-list editing,
question selection, and three distractors. The best proposal has normalized
similarity 0.9380 and raw similarity 0.5427, with 2,356 bytes versus the
original 2,388 and a 184-byte frame versus 200. These are rejected probe
results, not acceptance evidence.

The parser resets three reference counts, retries `func_8AB02EF8` once if
it returns null, and consumes unsigned halfwords until `0xFFFF`. A high-bit
command selects one of 18 operations. Operations set header text, choose a
preload mode, copy reference lists, append archive/entry pairs, mark pairs
with `0xFFFE`, replace a pair, or set the panel-selection word. After list
compaction and question selection, the distractor loop rejects both repeated
indices and strings equal to the selected answer or any earlier distractor.
It selects exactly three entries. The final stores clear two halfwords in
each of four row records spaced 148 bytes apart.

Loop-top terminator checks and an explicit retry loop improve the opcode
shape. Separate command-local source/destination/reference variables and a
separate question-text lifetime also help. Shared versus scoped variables,
command width, pair-copy spelling, pointer versus indexed initialization,
unsigned selection indices, array versus struct halfword fields, payload
statement grouping, and row-store grouping have been compared. One replayed
body was refused in preflight; it did not consume a compile attempt. No
source body was installed. Real one-argument signatures for
`func_8AB016E4` and `func_8AB01F80` were preserved; a live value in `$a1`
is not sufficient evidence to add an argument.

The checksum-matched US ROM independently exposes an epilogue prerequisite:
owner offsets `0x8F4` and `0x900` load `$at` pages for two adjacent row
halfword stores. Offset `0x90C` loads the page for `D_8AB12DDC` and
`D_8AB12DDE`, with the return-address restore at `0x910` before stores at
`0x914`/`0x918`. Offset `0x91C` loads the page for `D_8AB12E70` and
`D_8AB12E72`; nine saved-register restores intervene before stores at
`0x944`/`0x948`. None redefines `$at`. The latter two runs are interleaved,
which the current contiguous-only coalescing implementation does not cover.
Direct word decoding verifies these sites in a ROM with MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`; this conclusion does not depend on the
symbolic scanner's handling of addends.

Next action: retain the best parser reconstruction and diagnose the genuine
source/assembler provenance of the interleaved epilogue before further
allocator-only searches. The frame and payload-access residuals also remain;
resolving epilogue provenance alone would not establish a match. Do not
replace the owner with a near-match, add frame storage, or rewrite its
instruction words.

## Accepted paired-reference selection and bounded random return

Match `func_8AB02644` as `TextReference_BuildShuffledPairs`: one new C owner,
888 instruction bytes. The compatibility alias preserves the address-keyed
name. Existing mode-selection calls use the descriptive name. The previously
accepted random helper remains the same machine code and is excluded from
the new-owner count.

The function fills consecutive reference IDs and halves the count. When the
halved count is at least two, it performs 500 distinct-index pair swaps,
randomly reverses each of ten pairs, then compacts ten selected IDs and their
companion words. The final byte values use the selected ID minus 330, 370,
or 392 in modes 1, 2, or 3; the signed-halfword result is divided by two and
incremented. Other modes use -2 before that arithmetic. All three passes
remain inside the count guard. Each pair's two elements are distinct data
members; the fill and compaction loops are ordinary C loops, with compiler
unrolling preserved.

The orientation pass computes its adjacent indices independently as `i * 2`
and `i * 2 + 1`. Computing the second from an already narrowed first index
loses an original instruction. A separate signed-halfword mode-offset local
preserves the original 888-byte size and 40-byte frame. With the old random
return declaration, all opcodes matched but 19 register words differed,
starting at offset `0xEC`.

`func_8AB023EC` returns zero for a zero bound and otherwise explicitly masks
its result with `0xFFFF`. Its return declaration and existing later prototype
now use `u16`, matching that bounded value. Two declaration-only object
controls, including a leading-blank source, preserve the complete existing
module. The correct return width resolves the caller's remaining register
rotation. The runner accepts the candidate with direct link verification and
the ordinary syntax-enabled retail-ROM gate. No instruction rewrite or
register constraint is involved.

The native source/allocator investigation was against revision `0ce3757f`.
The permuter reproduced the retained parent across all 222 instruction words
and normalized callee/data relocations, but its four-worker, 90-second search
stayed at score 130. A logging-only compiler observer passed eight full-module
controls covering a known matched getter and the retained caller, with stock,
observer-off, observer-on and leading-blank builds. Interference-edge logging
passed the same eight controls. These diagnostics led to the bounded-return
hypothesis; their normalized comparisons are not acceptance evidence.

The accepted runner transaction and final named, declaration-cleaned source
are separately gated and frozen. Independent verification covers all 23,008
text bytes, 384 rodata bytes, 81 function starts/extents and resolved relocation
targets, plus linked fragments 45/50/79 and four collateral objects. US ROM
MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d`. The earlier interpreter's
interleaved epilogue and other unresolved owners remain assembly. Private
compiler observers, probes, frozen objects and ROM artifacts are excluded
from the public change, as are coverage and layout files.

## Icon cache callback `func_8AB01C88`: requeue

The owner remains assembly: 588 bytes with a 112-byte frame. Against native
revision `bbb98ccb`, forty compiled C variants reconstruct the allocation,
cache refresh and drawing path. Eight earlier compile failures referenced a
type defined later in the file; those are declaration-placement diagnostics,
not valid source-shape experiments. The best normalized similarity is 0.8435
with raw similarity 0.4422. The scalar-coordinate parent has normalized
0.8163 and raw 0.4694. Neither is a byte match.

The graph record's pointer at offset 32 selects a cache containing a choice
pointer at 0, pixel buffer at 4, signed cached entry at 8 and validity word at
12. The choice supplies archive/entry halfwords at 48/50. Phase 0 allocates
3200 bytes and clears validity. Phase 1 reloads the pixels when archive is
zero and either validity is clear or the entry changed. It calls the real
three-argument `func_8004D878` with the buffer, cached entry plus one and a
null record. A nonzero archive clears validity instead. The draw path queries
its parent coordinates, loads a 40-by-40 RGBA16 texture with clamp addressing,
and draws a 53-by-53 rectangle with 0x300 texture steps in `G_CYC_COPY`.
`GfxRect_DrawTextured` in `src/44E70.c` implements that cycle mode's horizontal
step adjustment. The separate resource loader definition in `src/4CC20.c`
establishes its actual pointer return and three parameters.

Scalar versus pair coordinates, separate versus shared coordinate storage,
cache struct versus byte views, declaration order, initial-buffer capture,
switch versus if dispatch, an early allocation return, combined versus
individual texture macros, statement grouping and legacy call promotions have
been compared. A coordinate pair brings the instruction shape closer but
puts its fields in different stack homes. No volatile storage, extra stack
space or padding is introduced to force the scalar homes.

The checksum-matched ROM independently contains an additional `jr ra; nop`
at VRAM 0x8AB01ECC / ROM 0x22704C, after the callback's ordinary return.
The runner calls this `duplicate_jr_nop_tail`; the C proposals produce a
normal return. Its source or boundary explanation remains unknown. Do not
invent an empty helper to supply the bytes or assume this is an established
compiler limitation.

A stock-compiler diagnostic reproduces the retained 7.1 candidate's function
bytes from identical source. IDO 5.3 also preserves the 76-byte known getter
control, including its leading-blank variant, but produces 584-byte callback
proposals: normalized 0.8299 for scalar coordinates and 0.8776 for the pair.
Neither reproduces the extra tail. The known-source rows retain this owner
in assembly; their exact target comparison is not a C match. No alternate
historical compiler has been identified, and the build compiler is unchanged.

Next action: capture the stock compiler's phase streams for the retained
scalar and pair parents, locate the coordinate homing and display-list
scheduling decisions, and investigate the eight-byte tail's provenance.
Keep compiler/debug-option tests diagnostic until known-source controls and
the complete retail-ROM gate establish their scope. Do not repeat the source
families above.

## Wobbling texture renderer `func_8AB019B8`: requeue

This owner remains assembly after 56 compiled C variants and eight initial
declaration failures. The best proposal has the original 588-byte size and
48-byte frame, normalized similarity 0.9728 and raw similarity 0.3061. The
remaining opcode-order differences are concentrated in the initial integer/
float expression; register differences extend through the function.

The renderer converts x to quarter-pixel coordinates with signed-halfword
wrapping, adds a 40-quarter-pixel sine displacement, and truncates back to a
signed halfword. Its phase wraps the frame counter shifted by 12 to sixteen
bits. Direct decoding of the checksum-matched ROM verifies sine-table values
0, approximately 0.3826834, approximately 0.7071068 and 1 at angles 0, 4096,
8192 and 16384. Thus the displacement amplitude is ten pixels. The texture
comes from the record's archive/entry fields at 36/38. The renderer queries
its width and height, loads it through `func_8004D1FC`, and emits either a
normal texture rectangle or a horizontally mirrored rectangle. Bit 0 of the
record's first halfword selects mirroring; the field at 12 supplies the
mirrored starting S coordinate. The display-list setup/restoration pointers
are `D_80094E38` and `D_80094F50`.

The unit already uses the loader through implicit declarations before this
owner. Adding its actual `s32 func_8004D1FC(u8 *)` prototype only beside the
new owner conflicts with that earlier implicit-int declaration. A companion
that inserts the prototype before `func_8AB00BC4` is valid: declaration-only
and leading-blank controls preserve the complete existing module, all 81
extents and resolved relocation targets. Keep the existing byte-array
spelling of `D_80094E38`; adding a conflicting Gfx-array extern is another
compile diagnostic, not a source hypothesis.

Dimension declaration order, reusing x versus a separate fixed-point local,
operand order, integer versus float scale literals, halfword versus byte
flag reads, phase locals, a named amplitude, and multiply-versus-shift forms
of the phase and x arithmetic have been tested. A signed-word x parameter,
with its forward declaration changed in the same transaction, produces a
worse 584-byte shape. An explicit motion-result temporary sinks part of the
position calculation past the resource calls and duplicates it in the two
draw branches, producing 648 bytes. Replaying it with the validated loader
prototype still produces 648 bytes, isolating that source-shape failure from
the declaration correction. None of these bodies is installed.

The repeated best-parent first difference is the frame-counter load:
retail uses `lw t7, 0(t6)`, while the parent uses `lw t6, 0(t6)`. The original
also materializes the float scale before the sine-table load. Named phases
and amplitudes do not recover that prefix; ordinary arithmetic spelling
changes compile back to the same residual. The original width/height homes
are sp+0x2C/sp+0x2A, with the texture pointer at sp+0x24 and mirror flag at
sp+0x20. Next action: observe the counter-address load and initial expression
at the compiler phase boundary, then target a measured lowering difference.
Do not add a redundant alias or a guessed global record simply to obtain a
different load register. The normal syntax-enabled retail-ROM gate remains
mandatory for any eventual match.

## Texture renderer phase-capture follow-up: requeue

The follow-up against native parent `96d64a47` compiles 32 additional proposals.
Splitting the horizontal-coordinate calculation into `x_fixed = x * 4;`
and a compound addition of the floating displacement recovers all 147 retail
opcodes, the 588-byte size and the 48-byte frame. The best runner raw similarity
is 0.3333. Register rotation still begins at the frame-counter load, and the
height home remains sp+0x2E instead of sp+0x2A. This body remains uninstalled.
The two assignments preserve the signed-halfword wrap before the float addition.

Normal IDO 7.1 `cc -v -keep` captures were calibrated against both the existing
module and the retained candidate. For each, stock, captured and leading-blank
builds preserve the complete module; identity replay of the actual binary G/T
assembler inputs preserves instruction bits and relocation topology/addends.
The readable UGEN listing from that same binary pipeline shows `li.s f4,40.0`
before the symbolic counter load in the split candidate. It still emits one
symbolic `lw t6,D_8AB1268C`, rather than establishing the retail address/value
register distinction. This locates the candidate's form; it does not establish
what the unavailable original compiler input contained.

A probe-only byte-storage/indirect-access diagnostic collapses to the same load
and does not justify changing the scalar counter representation. Narrowing the
height query return, or both dimension-query returns, to u16 also leaves the
residual unchanged; existing s32 prototypes are retained. Stock IDO 5.3 preserves
the 76-byte getter control but generates a 584-byte split renderer, so that
compiler comparison does not supply a match or justify changing the build.

A calibrated 180-second, four-worker permuter search lowers its own score from
2063 to 868. The five retained programs have the same parsed syntax tree as the
base modulo commutative bitwise AND, including their naturally expanded GBI
operations. Full-unit runner checks nevertheless reject all five; the best has
normalized similarity 0.9932. Three simpler statement-grouping proposals retain
the original 1.0 opcode similarity and the same register/height-home residual.
Keep the split source as the next baseline. Investigate the first UGEN temporary
allocation and the real halfword homes; do not repeat the ruled-out storage,
return-category, compiler-version or formatting families above.

## Main input/render loop `TextInterface_RunMainLoop`: accepted

`func_8AB05300` is replaced by 568 bytes of genuine C. The US assembly selects
controllers by testing bits 0 through 3 of the configuration byte at offset 14,
in priority order. Each branch copies 40 bytes from the corresponding pointer
at `D_80087200`, `D_80087204`, `D_80087208` or `D_8008720C` into `D_8AB13F00`,
and stores the selected zero-based port at `D_8AB13F2C`. A normal aggregate copy
of an opaque ten-word snapshot reproduces IDO's three-word copy loop and final
word. No manually unrolled copy or guessed controller fields are needed.

Each iteration polls input through `func_80064D28`, adjusts the snapshot through
`func_8AB05254`, and advances `D_8AB14188` through `func_8AB051AC`. A saved previous
state is passed to the frame renderer `func_8AB04EE8`. When `D_8AB126A0` is 1,
`func_80043678` supplies the RGBA16 preview address and the flag becomes 2.
The loop exits when the new state is zero and invokes `func_8AB01FBC`. These
input, dispatch and rendering operations support the new function name.

Initial aggregate-copy proposals reproduce 140 of 142 instruction words.
Saving the previous state separately while passing the global current state
to the transition routine recovers the remaining `lw a0` / `move s0,a0` pair;
passing the saved local or assigning it inside the call argument produces the
reverse register roles. The accepted runner label is
`text-main-loop:global-transition-with-history-snapshot:parent-0:layout-separate`.
The isolated probe is link-verified and the ordinary syntax-enabled full US
ROM comparison passes with MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.

## Entry table ownership and `TextInterface_Run`: accepted

The next verified layout boundary extends this file's rodata from 384 to 432
bytes. The twelve words at ROM 0x236960 through 0x23698C are
`jtbl_8AB117E0`, consumed by `func_8AB05538`. Entries 0-3 select 0x8AB057B8,
entries 4-10 select 0x8AB05800, and entry 11 selects 0x8AB05948. Every target
lies inside that owner. The next debug string begins at ROM 0x236990 /
VRAM 0x8AB11810, on a 16-byte boundary, and stays in the external tail.
The pinned spimdisasm commit `fe1338434c99240eb4adca0b7860edc12b847565`
re-splits the table into the owner's `.late_rodata`. The still-assembly ROM
passes comparison before any C proposal is installed. The complete former
rodata tail, all existing module instructions and relocation destinations,
and the linked fragments are verified across the migration.

`func_8AB05538` becomes `TextInterface_Run`. It stores the supplied configuration,
loads its mode and controller-mask byte, prepares display/stage resources,
loads and caches 598 archive entries, selects font resources by mode, allocates
the audio buffer, constructs the interface and invokes `TextInterface_RunMainLoop`.
The remaining calls tear down resources before returning zero. The constructor
`func_8AB00084` independently clears 0x958 bytes for the 598 four-byte entries.
These resource and main-loop operations support the entry function's name.

Both m2c drafts omit the empty mode-11 switch case, including a draft supplied
with the migrated table inside the assembly owner. The retail table explicitly
jumps past font initialization for mode 11. A faithful switch must include
`case 11: break;`; sending that mode through the default nine-font setup changes
behavior and removes the original table shape. The apparent second argument
on m2c's `func_8AB003A4(239, ...)` is also an unchanged loop-counter register,
not an argument consumed by the wrapper or its callee.

The accepted source parses the mode through the newly stored global
configuration and uses an indexed cache write with a named archive-file result.
The ordinary compiler generates the retail pointer induction variable and
spill locations. A manually advanced cursor uses different homes. Declaring
the index before the stage/archive/result locals recovers the original
56-byte frame and all executable words. The accepted runner label is
`text-entry:indexed-resource-cache:decl-order-0:loop-for`. Its probe differs
only in relocation fields; the runner's sequential syntax-enabled full-ROM
gate proves acceptance. A normalized probe or relocation mask alone is not
acceptance evidence.

The assembly owner's 1224-byte span includes a final alignment nop. IDO's C
symbol is 1220 bytes and the compiler supplies the final four zero bytes as
normal section alignment. The complete 23008-byte text section remains exact.
Object comparison checks the actual zero word at the terminal boundary while
preserving the other 80 function symbols' extents. No padding pragma, dummy
local or instruction rewrite is introduced.

Two earlier wrappers now explicitly accept and forward their resource IDs:
`func_8AB003A4` to `func_8004C8C0`, and `func_8AB003C4` to `func_8004C4B0`.
Their earlier zero-argument C definitions accidentally relied on the incoming
argument register surviving an argument-free call. The callees in `src/4CC20.c`
consume the ID. Four known/forwarding/leading-blank controls preserve the entire
existing module, including all relocation destinations, before these companion
edits are used with the new owner.

`fragment64_main` in `src/fragments/64/fragment64_322C90.c` receives the integer
20 from this entry path and stores that word at the beginning of its state.
`func_87F00030` initializes the same word to 20. Correcting the setter's pointer
parameter/store to an s32 parameter/store preserves its complete object and
linked fragment. The full US-ROM comparison after naming and cleanup matches
MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`, based on parent `59d9d6b9` plus this
entry/table change; public integration starts at `26b6436b`.
