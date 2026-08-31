# Region notes -- disasm/src/fragments/4/fragment4_AFAA0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 16 handoff (2026-08-31) (2026-08-31)

requeue: func_818021B4. Eight variants; best normalized/raw similarity was 0.8095/0.7619 with operand_or_scheduling_drift. `(s32)D_81805D44` gives the expected lui/addiu. Callee prototype: s32 func_8004C8A0(void *, s32, s32, s32). Tried address typing, locals, nested and combined guards, goto, and pointer forms. Next use materially different branch shaping for regular bltz+nop rather than likely/wrong-delay-slot forms.
