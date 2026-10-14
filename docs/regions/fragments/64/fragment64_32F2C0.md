# Fragment 64 fade/timer and scrolling-text family

## 2026-10-14: four-owner solo native batch, file complete

Replace the four remaining existing assembly owners with normal-runner C:

- `func_87F0C6F4`:47 instructions /188 bytes, original0x20 frame.
- `func_87F0C7B0`:55 instructions /220 bytes, original0x20 frame.
- `func_87F0C88C`:41 instructions /164 bytes, original0x20 frame.
- `func_87F0C930`:17 executable instructions /68 bytes plus12 alignment
  bytes,80-byte owner span, original0x18 frame.

The two previously accepted68/96-byte initializers stay unchanged. No active
GLOBAL_ASM function remains in this file. Full project decompilation is still
unfinished. Address names await independent naming evidence.

No prior attempts for these owners were found in the consulted private ledger.
Baseline native ROM verification and fresh source/build/20-leading-blank-line
controls match both existing neighbors before hypotheses. Submit eight distinct
variants per owner,32 in the first batch. Update, render and fade start accept
in one combined gate:link_verified=true and auto_gated=true. Timing:5.913s
probes /1.576s gate /7.493s total. Statistics remain enabled; stop accepted owners.

The timer has signed elapsed/limit words at0/4 and the active/pending flags at
bits31/30 of the word at8. Preserve the pending branch's fade-mode1 result;
otherwise only fade-mode0 with active set increments and saturates elapsed.
Controller pressed bits at6 masked by0xD000 can also start the fade. The real
finished carrier is separate from the return value, which stays0 on that path.
Fade start sets pending only once, then calls the original clear-color and
fade routines with the original1/0x14 arguments. Keep the actual return and
old-style call view for the latter; do not invent a new off-file signature.

Rendering remains active-only. Emit the original two display lists around the
existing resource-based199/182 draw, then invoke scrolling text. Use standard
GBI macros. Preserve the original guards, resource IDs and argument widths;
no new null checks, timer guards or callbacks.

## Scrolling text: recover function-local initialized data, not register fakes

Initial extern-global spellings have the right220-byte size/frame but best
normalized0.9636/raw0.6727. Expected global value carrier is a3; the wrong
context materializes an address in a0 and leaves values in temporary registers.
Four initial cached-position variants fail because a declaration followed
statements in that C89 block; retain those failures honestly, not as scored
source hypotheses. Corrected families test actual call views, real carriers,
integer/byte-pointer types, shared-counter access, word views, expression
topology and K&R formal spelling. None resolves the extern-scalar mismatch.

Calibrated native90-second permuter:parent/probe and target/oracle220-byte
words match before search; score725 improves to375 without a zero. Reject
uninitialized reads, empty conditions and unsequenced assignments in proposals.
Testing their reviewed live carriers does not accept a body. No mutation-only
winner, artificial loop or forced register is published.

The decisive evidence is the data: D_87F112A0 starts at0xA0 and this function
alone references it in the consulted assembly. A function-local static yields
raw/normalized1.0 immediately, but initially fails section_layout_drift. A
file-scope private static is not equivalent compiler input here: it reproduces
the old allocation mismatch. Preserve the function-local ownership.

Give this C object the existing16-byte initialized slot at ROM0x333F10 through
0x333F20, VRAM0x87F112A0:one0xA0 word and12 zero alignment bytes. Add its
`.data` subsegment and split the remainder into fragment64_data_tail. Re-split
with the existing native splat; the generated linker changes are limited to
this placement. The original data name aliases the C-owned slot in aliases.ld.
No new data capacity or padding-only C variable is introduced.

Gate both prerequisite stages while scrolling still owns GLOBAL_ASM:the data
slot, original function and all neighboring text remain byte-identical. A
temporary assembly-backed initializer inside the accepted fade-start function
provides an exact baseline data object. The normal companion transaction then
removes that initializer while installing scrolling's own local static, so
there is exactly one live counter at the original address. Preflight requires
the edit to include the owning function header; correct that before workers
start. This diagnostic costs no source hypothesis and removes no pragma.

The first post-handoff candidate accepts after80 prior attempts. Its relocation
identity differs from the old assembly name, so link_verified=false with
relocation_drift; the authoritative sequential ROM gate, not link-shape
similarity, establishes acceptance. Timing:5.421s probes /47.507s gate /
52.931s total. Do not describe this as an auto-gated or link-verified accept.

The private counter persists across calls with initial x160. Skip work when
the original control query is nonzero, measure text ID0x16, decrement by1 and
wrap only below negative width by width+60. Preserve setup, white color, y170,
two draw positions and final existing callback. No extra bounds/format guards.

## Final verification and follow-up

Post-acceptance cleanup restores modern formal spelling, removes redundant
declarations, annotates field offsets and indents the matched statements. The
temporary data initializer is gone; only the genuine function-local counter
remains. Native gmake rom COMPARE=1 passes with default syntax checks, MD5
1561c75d11cedf356a8ddb1a4a5f9d5d. All427 C sources pass cc-check. Fresh
final-source/build/blank controls match all six functions, including the full
80-byte fade-start span. Independently verify their linked retail spans and
the complete16-byte counter-data section. git diff --check passes.

Only game source, required layout/alias metadata and this history are published.
No helpers, headers, compiler patches, scratch adapters, ROMs or target objects.
For future exclusive initialized-data owners, investigate local static binding
early rather than spending another allocation-only campaign on an extern view.
This is evidence from this file, not a general source-shape guarantee.
