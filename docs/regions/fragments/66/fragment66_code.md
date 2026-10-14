# Fragment 66 record reset, callback and scene setup

## 2026-10-14: three solo native full-ROM accepts

Review the older private region notes before scheduling:00700 has prior
instruction drift;01898's older probe-unavailable report was tooling evidence,
not proof that C cannot match;02508 had declaration-context failures;04734 had
an unreliable normalized match with very low raw agreement. Fresh controls first
reproduce matching callbacks/wrappers and the unchanged reset against the current
build,20-leading-blank recompiles and linked retail before new candidates run.

- `func_82E04734`:36 instructions /144 bytes, leaf. The table contains100
  twenty-byte records at D_82E05968, ending at D_82E06138. Each iteration clears
  word0, sets word4 from D_82E05948, writes word8 as old word16 minus D_82E0594C
  and copies old word16 to word12; word16 is unchanged. Direct array indexing
  lets IDO perform the original four-record unroll. Pointer loops and explicit
  cached globals are controls, not winners. The object hit has a different
  end-address relocation; link_verified=false. Gate that existing unverified hit
  sequentially through the normal runner: accepted after24 prior probes,
  5.422s probes /1.856s gate /7.282s total. The full ROM, not masking, proves it.
- `func_82E01898`:70 instructions /280 bytes, leaf. Preserve kind0/1 dispatch,
  both big-endian byte-pair values, conditional5/6 adjustment, the second value's
  unchanged high byte plus scaled low byte, flag-bit0 clearing and return0.
  Scalar numerator/denominator reuse reproduces the runtime division checks;
  swapping the second sum's operand demand fixes its temporary-register cycle.
  Explicit extra stage temporaries do not close it. Accepted after16 prior probes,
  link_verified=true,5.212s probes /1.078s combined gate /6.292s total.
- `func_82E02508`:84 instructions /336 bytes,0x28 frame. Preserve mode query,
  flag, pool state, all three graph loaders, allocation finalization, three
  320x240 views, renderer/node initialization, data-state push, post-incremented
  counter and the final0x52 call. The old prototype declared main_pool_push_state
  void, but its accepted definition in src/3280.c returns s32. Atomic prototype
  correction with the candidate fixes the four-register-word residual after
  that call. Both existing callers in02658 retain their bytes. Accepted after
  eight prior probes, link_verified=true,5.525s probes /1.231s combined gate /
  6.759s total. This is actual ABI evidence, not an invented return-category trick.

Cleanup removes an unused input-record type and redundant declarations, retains
the actual view-state/table types and keeps the real pool-return prototype.
Naming plan has no existing evidence-backed names for these three owners.
Full native COMPARE=1 retains MD51561c75d11cedf356a8ddb1a4a5f9d5d; all427 host
syntax checks pass. Fresh-source/build/blank comparisons match the entire file's
.text and individual accepted/sibling functions, including464-byte02658; all
new linked retail spans match. No compiler patch, new helper function, header,
data subsegment or linker change is needed. Scratch stays local.

## Remaining coordinate callback requeue

`func_82E00700` stays GLOBAL_ASM:60 instructions /240 bytes. Sixteen new probes
test raw/typed event and state views, switch/guard/nested-if topology and real
early returns. Best new normalized0.8500/raw0.6333 has232 bytes; old private
notes had0.8667/0.7667. Preserve both kind and selector dispatches, coordinate
updates, conditional scaling and flag clearing. Do not invent eight padding
bytes: the oracle has real duplicated/scheduled case loads and control transfers.
Next action is a calibrated control-flow/statement-line discriminator on the
closest complete body, not more record-field typing or arbitrary guards.
