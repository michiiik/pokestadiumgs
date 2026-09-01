# Region notes -- disasm/src/fragments/4/fragment4_AFAA0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 16 handoff (2026-08-31) (2026-08-31)

requeue: func_818021B4. Eight variants; best normalized/raw similarity was 0.8095/0.7619 with operand_or_scheduling_drift. `(s32)D_81805D44` gives the expected lui/addiu. Callee prototype: s32 func_8004C8A0(void *, s32, s32, s32). Tried address typing, locals, nested and combined guards, goto, and pointer forms. Next use materially different branch shaping for regular bltz+nop rather than likely/wrong-delay-slot forms.

## Wave 24 handoff (2026-09-01) (2026-09-01)

tooling-blocked: func_81803558, 6 probe variants (3 initial f32-signature variants rejected by existing extern redeclaration; 3 s32-signature raw-offset variants compiled but best normalized/raw 0.9265/0.7794, instruction_drift at offset 16: expected lw t6,16(a0), actual sw a2,40(sp)). Assembly immediately executes mtc1 a2 after loading a0 and only spills a1, proving arg2 must be float ABI, while source has existing extern void func_81803558(s32,s32,s32,s32); runner companion_edits forbids editing candidate owner. Next action: runner/API must support replacing candidate owner prototype atomically, or separately gate prototype change to f32 before retrying explicit raw-offset call sequence.
