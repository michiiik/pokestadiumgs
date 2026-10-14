# Region notes: fragment76_code

## 2026-10-15: bank lookup and four directional selectors accepted

Solo native work, no agents or containers. Fresh/20-leading-blank controls
reproduce all object sections and the twelve pre-existing C functions before
probing. `func_8F700EF4` is accepted, `link_verified: true`, batch
`df94d0bb763e4a86966bc2946a98f8f7`, one combined normal full-ROM gate with
statistics and host syntax checking enabled. Its original span is 21 words /
84 bytes, a leaf with no stack frame.

Winner: `f76:bank-lookup:guard:early-return-False:bank-pointer-False:indexed-True`.
An explicit nonempty-table guard followed by an indexed do/while permits the
original first-entry check and pointer induction. The type-byte sentinel is
eight; the bank byte is offset one in each 0x30-byte record. Store the first
matching index and return, leaving selection unchanged when no entry matches.
Post-acceptance cleanup removes an unused pointer and redundant declaration;
fresh/blank controls reproduce all sections and all thirteen C functions,
and a fresh full-ROM gate passes MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
The four directional owners are also accepted with `link_verified: true`,
batch `25b7d924c2e145bdbbb322313fc967cc`, one combined normal full-ROM gate:

| Owner | Direction | Instructions / bytes | Frame |
| --- | --- | ---: | ---: |
| `func_8F700A54` | up | 73 / 292 | 0x28 |
| `func_8F700B78` | down | 75 / 300 | 0x28 |
| `func_8F700CA4` | left | 73 / 292 | 0x28 |
| `func_8F700DC8` | right | 75 / 300 | 0x28 |

All four use winner
`f76:navigation:snapshot-chains:index-False:coordinate-False:unsigned-initial-True`.
The label names the tested family; neither chained assignment is needed.
The final change is the unsigned index for the initial selected-record
column/row reads. The search counter remains signed, and the existing
global index declaration is not retyped.

### Shared navigation source shape

Model the real 0x30-byte menu entry: four byte header fields, signed minimum
and maximum words, the label at 0x0C and value pointer at 0x2C. The assembly
renderer passes the label address, and its value dispatch dereferences the
last pointer as a byte or word according to kind. The new typedef creates
no data allocation or layout segment. Keep seven genuine byte locals:
column, row, preferred index, wrap index, preferred coordinate, wrap
coordinate and the current candidate coordinate. The real signed loop index
is declared first; that ordering recovers the stack homes and 0x28 frame.
Direct typed-record field expressions recover the initialization schedule;
unsigned initial indexing closes the last three differing register operands
(`a1` versus `v1` for the selected-record address).

Preserve bank/orthogonal-axis filtering, the nearest eligible coordinate,
inclusive preferred-coordinate tie handling, wrap to the opposite extreme,
and the fresh selected-index read after the sound call. All index snapshots
remain bytes, as in the original. No artificial local, padding, volatile
view, register forcing, extra argument or object/compiler patch is used.

The calibrated first native permuter search improved its score from 145 to
130 in 90 seconds without acceptance. A second calibrated search on the
three-word residual was interrupted after the normal runner accepted all
four functions. Neither search supplies the accepted source. Do not rerun
either search or replay rejected families now that these owners are closed.

After scoped duplicate-extern cleanup and normal source formatting,
fresh/20-leading-blank controls reproduce every object section and all
seventeen C functions against the pre-batch object. Fresh native full-ROM
comparison passes retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. The naming
plan has no known names for these five owners. Retain their address keys.
This five-owner batch leaves six assembly owners, not a complete file.

`func_8F700538`: requeue. Eight natural pointer/snapshot/address cells were
first tested with an incorrect word-return declaration for `func_80003F74`.
Its actual definition in `src/4420.c` returns void. Eight correctly declared
cells remain rejected: best normalized 0.8571/raw 0.5714, 80 versus 84 bytes.
Do not interpret the first family as correct-prototype exhaustion. Next:
compare argument stack homes and initial byte reloads with the accepted
neighbor `func_8F70058C` before another compiler-shape family.
Eight further split guard/index snapshot cells reach normalized 0.8571/raw
0.6190, still 80 versus 84 bytes. The compiler caches the input byte in a
register where the original reloads its stack home. A new hypothesis should
address that lifetime, not repeat pointer arithmetic or return-type guesses.

`func_8F700420`: requeue. Natural, guarded-loop, first-header-pointer and
typed-header cells reach normalized 0.9714/raw 0.9286. Guard-lifetime cells
recover the exact 280-byte size and 0x30 frame, but the first type-byte load
still shares its array base with the loop setup rather than using the
original independent absolute load. Next: use the newly verified typed
full-record representation to inspect that address-expression ownership;
do not replay the header-only or byte-pointer variants. No failed source or
declarations remain installed.

`func_8F700028`, `func_8F7005D8`, `func_8F700624`, `func_8F7006F0`:
layout-prerequisite.
Read-only assembly inspection confirms jump tables `jtbl_8F702308`,
`jtbl_8F702324`, `jtbl_8F702340`, plus the renderer's `jtbl_8F7022E8`.
The current YAML has the code subsegment
immediately followed by the shared data subsegment, without a per-file
rodata subsegment. No switch candidate has been probed in this batch.
Follow the documented layout/split/assembly-gate prerequisite first.

Only this game C file and its region notes are published. Scratch, rejected
candidates, statistics, objects and ROMs remain local. No tooling helper is
published. Tracked hooks and decomp-workbench are absent in this clone;
explicit native runner/object/provenance checks are the fallback, not a claim
that unavailable checks ran. No exhaustion or compiler-impossibility claim.

## 2026-10-15: narrow rodata split and three switch owners accepted

The layout prerequisite above is now resolved. Native work is performed in
an isolated owned snapshot of the public checkout. The initial snapshot
matches retail before any layout edits. Do not apply the planner's whole-file
run (`0x367B40..0x368B60`): that includes mutable menu records and pointers.
The verified tight window is `0x368AD0..0x368B50` (128 bytes), followed by a
`rodata`-typed tail subsegment so the original output order is retained.

The window starts in the final eight bytes of the title at `D_8F7022D4`.
Splat drops those bytes because they lack an independently referenced symbol;
leaving them out produces a checksum failure even with every switch still
assembly. `const u32 D_8F7022E0[2] = {0xA1C1A4EB, 0}` explicitly represents
the real suffix at the original address before the jump tables. This is
actual read-only string data, not an executable padding helper or invented
stack slot. No mutable data moves into the code object's rodata window.

With pinned spimdisasm 1.35.0-dev0, the split migrates all four tables into
their assembly owners. Before any C switch is installed, a normal full-ROM
gate passes. Fresh/blank controls reproduce the 128-byte object rodata,
including the title suffix, and preserve all seventeen existing C functions'
instruction words and offsets. The generated linker-script change is one
line for the trailing rodata object. All compatibility aliases are retained.

### Accepted switch functions

| Owner | Instructions / bytes | Frame | Accepted batch |
| --- | ---: | ---: | --- |
| `func_8F7005D8` | 19 / 76 | leaf | `5de9d629f5484e7a906a1afdeac76a81` |
| `func_8F700624` | 51 / 204 | leaf | `6078a63753f842fa971a7547504bfaf6` |
| `func_8F7006F0` | 50 / 200 | 0x18 | `6078a63753f842fa971a7547504bfaf6` |

Each result is `accepted`, `relocation_masked: true`, `link_verified: false`.
The object differences are recognized relocation fields; they are permission
to run the sequential full-ROM gate, never acceptance proof by themselves.
The authoritative gates pass retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`.
Do not rewrite these results as link-verified. Normal host syntax checking
and statistics stay enabled.

Winners:

- `f76:switch-read:typed-True:temporary-False:return-True`: kinds 1-4 read
  the value pointer as an unsigned byte, kinds 5-7 as a signed word.
- `f76:switch-adjust:typed-True:case-scope-True:return-True`: kinds 1-4 use
  the four-action nested switch, including the original unsigned divide by
  ten for the large step; kinds 5-7 XOR with the maximum word.
- `f76:switch-write:typed-True:bounds-temporaries-False:return-True`: preserve
  source case order 3, then 2/4, then 5/6/7. Kind three clamps, writes the
  byte and selected resource and calls the existing loader. Kinds 2/4 clamp
  and write a byte; kinds 5-7 write the word unchanged.

All use the existing record layout and original void-pointer interfaces.
After acceptance the duplicate draft typedef is consolidated into the one
`F76MenuEntry` definition, hoisted above its first use. No fake temporary,
volatile view, extra argument, forced register or compiler/object patch is
introduced. The naming plan has no known mappings for these three owners.

### Build-state trap observed during sequential gates

The first authoritative gate noticed the changed YAML extraction marker and
regenerated the assembly tree while its candidate was installed. That
successfully accepted `func_8F7005D8`, but the later attempts in the same batch
reinserted the pre-batch assembly pragma after its `.s` file had been removed
by fresh extraction. They failed compilation with `Cannot open file
GLOBAL_ASM:.../func_8F7005D8.s`, not with a C-code mismatch. A new batch based
on the installed winner, reusing its real shared type instead of redeclaring
it, accepted the remaining two owners. Preserve these diagnostics as tooling
evidence; do not charge them as failed source-shape hypotheses. Future layout
campaigns should establish extraction currency before beginning a multi-owner
sequential gate transaction.

After cleanup, fresh/20-leading-blank controls reproduce all object sections
against the accepted baseline, all twenty current C definitions are stable,
and the seventeen pre-existing definitions retain their pre-layout words.
The linked spans of all three new C owners match retail. A fresh split with
the final C source and a normal full-ROM rebuild both pass, as does the
post-deduplication full-ROM verification. Neither scratch recipes nor
generated ASM/assets belong in the PR. The remaining owners are
`func_8F700028`, `func_8F700420` and
`func_8F700538`. The first is now layout-ready, not blocked on rodata.
