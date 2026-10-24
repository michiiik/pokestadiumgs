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

## Image strips / requeue

`func_8AB02240` remains assembly. It draws an 80-by-80 RGBA16 image in twenty
four-row strips, advances the source by 640 bytes per strip, and brackets the
loop with `D_8AB111B0`/`D_80094F50` display lists. The fourth input supplies
the primitive LOD fraction (`gDPSetPrimColor`'s second data argument), not the
RGBA alpha byte. `func_8AB05300` obtains the image from `func_80043678` on the
preview state, then stores it in `D_8AB16794`.

The word-coordinate candidate has the original 268-byte size (normalized
0.9403, raw 0.7463), with differences in temporary allocation and width/stride
argument normalization. An old-style six-argument helper declaration instead
produces 260 bytes and rejects. No changed declaration or rejected image body
is installed. Next action: recover `func_8AB01FC8`'s actual strip interface
before changing more caller spellings; do not infer formal parameter widths
solely from its narrowed hardware-coordinate uses.

## Formatting-sensitive compiler input / tooling-blocked replay

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

This is evidence against treating whitespace-insensitive body identity as
compiler-input equivalence. The runner's rejected-body preflight currently
uses that identity, so formatting-only replays require a tooling correction
and regression fixture first. Keep the acceptance verifier unchanged: the
rejected 352-byte proposals have layout drift and are not ROM matches.
