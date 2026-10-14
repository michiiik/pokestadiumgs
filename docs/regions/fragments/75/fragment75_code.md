# Region notes: fragment75_code

## 2026-10-15: resource loading, frame loop and entry accepted

Solo native work, without agents or containers. Before probing, fresh-source
and 20-leading-blank controls reproduce all object sections and the five
existing C definitions. Three owners are accepted by the normal runner with
statistics and host syntax checking enabled:

| Owner | Instructions / bytes | Frame | Accepted batch |
| --- | ---: | ---: | --- |
| `func_8FA0069C` | 32 / 128 | 0x28 | `3c7de798065240d1a56c63c4cf48c3b0` |
| `func_8FA017B8` | 30 / 120 | 0x28 | `b9b011402e5642c8842c6f35eaf9304a` |
| `func_8FA01830` -> `fragment75_main` | 72 / 288 | 0x28 | `b9b011402e5642c8842c6f35eaf9304a` |

All three results are `accepted`, `link_verified: true`. The loop and entry
share one combined full-ROM gate; the resource loader has its own combined
gate. Retail MD5: `1561c75d11cedf356a8ddb1a4a5f9d5d`.

### Winning source shapes

- Resources: `f75:resources:line-topology:leading-False:loop-False:all-True`.
  Allocate the real 0x1900-byte global buffer, advance the two-entry asset
  table and byte offset together, and reload the buffer for each unpack.
  `offset + buffer` preserves the observed operand order. Initialization and
  the do/while loop must remain on one physical source line: under the
  normal compiler, separating them delays the end-table address setup.
  A comment in the source protects this measured scheduling constraint.
  This is another source-line-sensitive file after fragment 74, not a
  claim that every scheduling residual has the same cause.
- Loop: `f75:loop:early-True:temporary-False:kind-do`. Initialize the genuine
  state before the startup calls; poll input only in state one, render each
  frame, and consume the returned state until it reaches three.
- Entry:
  `f75:entry:segment-address-False:return-local-False:unsigned-handle-False`.
  Preserve pool tag MDLV, configuration handle, text/resource setup, segment
  load and reverse cleanup. The fragment header trampoline proves the
  `fragment75_main` name; an alias preserves the original address symbol.
  Its 288-byte owner span includes two trailing alignment nops outside the
  compiler's 280-byte function symbol; post-naming controls compare the
  complete original span and symbol offset, not unlike symbol-size ranges.

After declaration cleanup, naming and source formatting, fresh and
20-leading-blank controls reproduce complete text/data/rodata/bss and all
eight C functions against the pre-batch object. A fresh native
`gmake rom COMPARE=1 -j2` passes with the normal host syntax check. Existing
unused `pad` locals in the two old callbacks are untouched; no new padding,
unused local, extra argument, volatile view, forced register, line directive,
object patch, helper or tool change is introduced.

### Unresolved handoffs

- `func_8FA005A0`: layout-prerequisite. The natural camera source with real
  three-float at/eye vectors matches all 61 generated words, including the
  0x40 frame and array homes. The original owner additionally contains an
  unreachable `jr ra; nop` pair at offsets 0xF4/0xF8: 252 versus 244 bytes.
  Both ordinary and explicit void returns retain that residual. A void
  return-expression trial is rejected by the actual C frontend, not scored
  as a source mismatch. No artificial padding helper is installed. Next:
  investigate an authentic compiler return-tail spelling or an explicitly
  reviewed mechanism for retaining these verified unreachable layout bytes;
  do not spend more vector-order variants on the tail-only mismatch.
- `func_8FA01718`: requeue. Fourteen source cells cover separate returned
  state versus argument mutation, word/narrow local, declaration versus
  statement initialization, switch selector and last-case return. None
  matches: best raw 0.4634 (164 versus 160 bytes), with an unwanted saved
  state register instead of the target's 0x1C stack home. Narrow selector
  trials are not candidates for adoption: they need not preserve arbitrary
  incoming word states. The original also has a duplicate return tail.
  Next: inspect optimizer lifetime/stack-home evidence, using the accepted
  fragment-73 fade handler as a structural control, before another spelling
  family. This is not evidence of compiler impossibility.
- `func_8FA00E2C`: requeue. Twenty-three cells cover independent/field-pointer
  state and current-object views, node/resource initialization order,
  array/end-symbol bounds, nested guards, store order and real frame-counter
  pointer/prefix increment. Best opcode-normalized 1.0, raw 0.8056, correct
  288 bytes and 0x30 frame. A 284-byte sibling has the same raw score but
  incorrectly reuses the loop-end address for the post-loop scene load.
  Next: trace the resource/current-node/current-resource address lifetimes
  and their saved-register allocation on the exact-size parent. Do not
  mistake the normalized 1.0 for a match or replay pointer spelling cells.
- `func_8FA00F4C`: requeue. Eight cells cover controller, zoom and angle
  field-pointer versus scalar views. Best normalized 0.9326/raw 0.6517,
  correct 356 bytes; the original's reload/scheduling pattern differs.
  Preserve the float steps and limits, signed-halfword angle updates and
  camera call. Next: localize those load/store differences before changing
  expression lifetimes; no volatile qualification has been inferred.

The other six assembly owners are not probed in this batch. All ten
unresolved owners remain assembly; this is not an exhaustion claim.
Scratch generators, rejected candidates, compiler output, statistics,
objects and ROMs stay local. Tracked hooks and decomp-workbench are absent
in this public clone; native runner/object/provenance checks are the stated
fallback, not a claim that unavailable checks ran.
