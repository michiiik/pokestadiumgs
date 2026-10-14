# Region notes: fragment73_code

## 2026-10-15: fade-state handler and resource entry accepted

Solo native work, without containers or agents. Fresh-source and
20-leading-blank controls reproduce the complete object text and the already
accepted `func_8F500810` loop before probing. Normal runner statistics stay
enabled. Two owners are accepted with `link_verified: true`, one combined
full-ROM gate each, and default host syntax checking:

| Owner | Instructions / bytes | Frame | Accepted batch |
| --- | ---: | ---: | --- |
| `func_8F500774` | 39 / 156 | 0x20 | `c90add1063da4b5abd5b3b74ec901180` |
| `func_8F50086C` -> `fragment73_main` | 69 / 276 | 0x28 | `571768e3a4dd4cb4a7a1e24baa72a03c` |

The state-handler winner is
`f73:state:separate-init-False:state-selector-False:group-False`. Preserve the
incoming selector and a separate returned state. Mode 0 waits for fade mode
zero; mode 1 polls the existing input handler and starts the exit fade and
sound transition; mode 2 waits for fade mode one. No jump table is emitted.

The entry winner is `f73:entry:natural-call-group-0`. Preserve the actual two
incoming words, the saved configuration handle, pool tag 0x42474D50, segment
selection, resource setup, main loop and reverse cleanup sequence. The known
name comes from `gs_names.json`; the original address symbol is retained by
an alias. No argument, local, padding or compiler intervention was invented.

Post-cleanup fresh/blank controls reproduce complete text/data/rodata/bss and
all three accepted C functions, including the pre-existing frame loop.
Native full-ROM comparison passes, retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Scratch recipes, probes, compiler output,
objects and ROMs remain local. The decomp-workbench command is unavailable;
existing runner diagnostics and calibrated controls are the fallback, not a
claim that workbench diagnostics ran.

### Unresolved handoffs

- `func_8F500020`: requeue. Eight cells model the actual 24-byte zeroed state
  record, camera/resource local order and initial store grouping. Best
  normalized 0.8088 / raw 0.3676; 244 bytes versus target 272, frame 0x30
  versus 0x28. The compiler retains a state base in s0 rather than the retail
  independent-symbol/shared-at addressing. The assembly includes shared-LUI
  stores with intervening instructions; no coalescer classification has yet
  been measured. Next: audit actual symbol/alias representation and classify
  those sites before choosing a different source family. Do not repeat the
  aggregate cells or claim an impossible compiler shape from this result.
- `func_8F500414`: requeue. Sixteen cells cover nested/merged animation guards,
  node pointer spelling, marker coordinate temporary, initialized consumed
  s16/s32 animation snapshots, declaration order and unsigned store view.
  Natural parent: normalized 0.9474 / raw 0.7895, correct 304-byte size and
  0x20 frame, but node stack home 0x1C instead of 0x18 and global-address
  commoning. Snapshot cells can recover the node home and reach normalized
  0.9605 / raw 0.6842, but do not close the address/scheduling residual.
  Next: inspect global expression ownership and alias representation, not
  more scalar spellings. Preserve both animation calls and reload globals
  after the first call. No failed declarations remain installed.
- `func_8F5002F4`: requeue. Sixteen cells cover advancing u8/u16 texture
  pointers, texture-load position, for/do loops, immutable base plus indexed
  source, real strip local and Y derived by division or shift. Best first
  family normalized 0.8125 / raw 0.4750; indexed family 0.8101 / 0.5443.
  Indexed parent is 316 versus target 288 bytes; both families retain a
  0x48 frame instead of 0x38. Next: inspect call-argument lifetimes and loop
  induction ownership. Preserve the first signed-halfword X load, second
  word X load and two texture calls per strip. Do not replay these families.

The remaining renderer and input handler have not been probed in this batch.
All five unresolved owners remain assembly. These are bounded negative
results, not exhaustion or impossibility claims.
