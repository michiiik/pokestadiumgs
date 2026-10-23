# Fragment 50 paired scene models

## 2026-10-24: animation callback and model-pair construction

The US owners `func_86207280` and `func_862073CC` are now
`SceneModels_SelectAlternateAnimation` (236 bytes) and
`SceneModels_CreatePairs` (496 bytes). Together they replace 732 instruction
bytes and complete this five-function source module.

### Names and recovered layout

`SceneModels_CreatePairs` loops over indices 0 through 3. Each iteration
requests two records from the pool at context offset 469192. The primary
record registers `SceneModels_SelectAlternateAnimation`, loads resource
`resources[index][0]`, selects animation 0, randomizes its frame, positions
it through `func_87F06430`, applies scale 0.08, lowers Y by 7, and records its
index at offset 32. The secondary record has no callback, uses the shared
resource at context offset 364, applies scale 0.125, and offsets X by 2.5
and Y by -23. Allocation failure skips initialization of that record and
still attempts its partner and subsequent indices.

The four pairs of resource pointers begin at context offset 332. The
constructor reads the first pointer of each pair; its callback reads the
second using the index stored in the record. These two consumers establish
the `SceneModelResources[4][2]` view without inventing preceding context
fields. Both owners match with this array view; plain byte-offset expressions
changed the callback's address/index temporary order.

The callback runs only when context offset 232 is 2 and the current record's
animation number is 0. It resets the record's graph node, loads its alternate
resource, selects animation 4 when the random value modulo 5 is zero and
animation 3 otherwise, then sets frame 7. The pool dispatcher
`func_87F0277C` sets `D_87F119DC` to each live record before invoking its
stored argumentless callback. `ModelAnim_BindTransformCurve` stores the
animation number at node offset 64, corresponding to record offset 100.
//@src/fragments/64/fragment64_324FB0.c
//@src/229E0.c

### Compiler float pool and original layout

The original constructor loads `0.08f` from ROM offset `0x274B80`, VRAM
`0x8620E140`. Expressing it as an external global read or a manually cached
global produced a different prologue; writing the literal reproduces all
124 original instruction words and the original 96-byte frame. The literal
requires a per-file `.rodata` subsegment: its 4 bytes and 12 natural alignment
bytes formerly belonged to the shared assembly data blob. The following
range beginning at ROM `0x274B90` contains the original overlay relocation
records and remains an opaque assembly section with unchanged bytes.

The layout was first split with the pinned splat/spimdisasm toolchain while
the constructor remained assembly. That state passed the ordinary US ROM
gate before the C candidate was retried. Independent comparison reconstructs
the entire original shared data blob from its prefix, the 16-byte float pool,
and the tail, including all semantic relocations. The constructor's two
references to external `D_8620E140` become references to local `.rodata`
offset zero at the same linked address. No instructions or relocation values
are rewritten.

### Verification and remaining work

Both owners have accepted native runner attempts and passed ordinary
`make COMPARE=1 RUN_CC_CHECK=1` gates with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Final declaration consolidation, array
typedef and function names are checked again by the same gate. Complete
module comparison covers all five function extents, text, pooled data and
semantic relocations; linked fragments 50 and 79 and collateral modules
remain byte-identical. Private probes and compiler diagnostics are excluded
from the public change.

No assembly owners remain in this source file. The older shuffle owner
`func_8620169C` in `fragment50_266A60.c` remains **requeue**: eight additional
array-view variants retain the existing final-address-materialization
residual, as recorded in that file's region notes.
