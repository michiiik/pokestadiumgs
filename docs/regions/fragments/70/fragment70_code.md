# Fragment 70 matching notes

## Native lifecycle batch, 2026-10-15

Base: public master `624b540`. Work is solo and native on macOS, without
containers or agents. The source was clean, the local claim registry had no
fragment 70 owner, and the local probe catalog had no attempts for the six
remaining assembly functions. Before probing, fresh and 20-leading-blank builds
reproduced the complete object text and the accepted initializer, frame-render
wrapper and state-handler siblings.

Five functions are accepted through the normal repository runner, with default
host syntax checking, statistics and provenance enabled:

| Owner | Instructions / bytes | Frame | Accepted batch |
| --- | --- | --- | --- |
| `func_8F2007B4` | 46 / 184 | 0x18 | `4f7e14f148f2447f8cdc851bf605c2a7` |
| `func_8F200020` | 79 / 316 | none | `028b2e3e0a9a477dab0691a79f9ea7a7` |
| `func_8F200494` | 61 / 244 | none | `868166d4afd041138b239f6b7be15744` |
| `func_8F20015C` | 46 / 184 | 0x20 | `e864f36b47194487b93e5f1ee83ecf40` |
| `func_8F20063C` | 94 / 376 | 0x48 | `54ed3fb2553c4aa19699b9f8992ae8e9` |

All five final winners are `accepted`, `link_verified: true`, with one combined
full-ROM gate each. The five owners total 326 instructions / 1304 bytes. No
padding, forced register, fabricated argument or unused working local is added.

### Resource entry point and callback

The entry point keeps its two real incoming word homes, despite not consuming
their values. Preserve pool tag `0x53435256`, resource/display initialization,
the asset segment expression, initialization/loop call order, teardown order
and zero return. The naming plan maps the owner to `fragment70_main`; the old
address-keyed name remains available through a compatibility alias. The symbol
table and original assembly oracle are unchanged.

The registered callback has the actual graph callback ABI: a word event kind,
graph-node pointer and word result. `TargetGraphNode` is opaque here rather
than inventing a whole node layout. Event 0 and unknown events do nothing;
event 1 applies six independent held-button tests to signed halfwords at
offsets 8 and 0xA, including intermediate halfword truncation. Clamp Y to
[-960,0] and X to [-640,640] only after all updates. Do not cache the controller
load across node writes: the target reloads it after those writes. Return zero.

### Input selection

The input handler gets the resource table behind descriptor+0x1C. Decrement
selection on bit 0x200 and wrap negative values to unsigned table count minus
one; independently increment on bit 0x100 and compare unsigned against count
minus one. Preserve the target's zero-count behavior rather than adding a new
guard. Pressed bit 0x20 toggles visibility. Accept has priority over cancel and
restart: accept sets the reload flag and returns zero, cancel returns one,
and held bit 0x10 returns two only when neither preceding input is selected.

### Loader: relocation truth matters

Use allocation then script in declaration order to retain the real 0x1C/0x18
homes. Store the selected index into the loaded-index global as the argument
to `func_8004DC6C`. Preserve the child pool pop/push, script validation,
available-memory allocation, graph decode, finalize and callback registration
order, including the callback's immediate event-0 invocation.

An initial probe hit was **not** accepted: `link_verified: false` reported
relocation drift, with D_8F200904/D_8F200908 swapped in the initial load pair.
Its explicit sequential ROM gate failed and restored the pragma. This was a
real rejection, not a tooling outage, even though the unresolved instruction
words compared equal. Reversing the comparison to
`D_8F200904 != D_8F200908` retains the right relocated load order and produces
the final link-verified winner. Do not promote the first probe hit or replay
its failed gate.

### Main loop

Keep two independent loop flags and persistent state. Case 4 leaves both loops;
the default continues frames; case 3 resets state, requests reload and marks the
loaded index invalid, then recreates the configuration. Source case order
4/default/3 with `frames = 1` before `running = 1` in the default is the accepted
spelling. Ascending case order leaves a 0.9362 raw scheduling residual at the
same 376 bytes/frame 0x48. Moving default first rotates the state/reload saved
registers. Neither a ternary mode toggle nor initial default flag assignments
is the accepted spelling.

The configuration call reads the **signed byte at halfword offset 1**, matching
the original `lb`, not a value cast of a halfword load. After teardown, mode is
zero only when its previous value equals one, and one otherwise; this toggle
also occurs on the final exit. Preserve both nested pool lifetimes and the
render/input/transition order. Every switch arm assigns both loop flags before
they are tested; no uninitialized local is used.

### Verification and remaining work

Post-acceptance cleanup removes duplicate declarations and expands branches.
Fresh-source and 20-leading-blank controls reproduce complete text/data/rodata/
bss and all nine accepted C functions in this file, including existing
neighbors. Fresh native full-ROM comparison after cleanup and naming passes
with default host syntax checking, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Accepted provenance is checked directly;
tracked hooks are absent in this public checkout, so no hook execution is
claimed. Naming supplies only the entry-point name; other address names stay.

Before publication, master `e6618a6` brought in the accepted fragment 68 batch
from #943. The only merge conflict was the two appended entry-point aliases;
both are retained. The integrated tree passes a fresh full-ROM comparison and
the same controls, preserving the fragment 68 accepted C as well.

`func_8F200258` is the only remaining assembly owner in this file and has not
been probed in this batch. It is the next text-rendering target, with three
mode-dependent coordinate pairs and repeated language queries. No jump-table
or data-layout prerequisite is identified from its current assembly. This is
remaining work, not an accepted match or a terminal skip.

Only source, compatibility alias and these notes are published. No scratch
generator, diagnostic helper, object, compiler binary or ROM is included.
