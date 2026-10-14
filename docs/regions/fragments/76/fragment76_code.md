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
