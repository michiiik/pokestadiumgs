# Region notes -- disasm/src/fragments/79/fragment79_37A6E0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Unsolved shape: second-formal +0x10 cost (AGENTS.md §5, blocking as of 2026-08-28) (2026-08-28)

Adding a **second formal** to an already-accepted one-parameter function costs +0x10 of `.text` (IDO reserves an incoming-argument save area) regardless of the new parameter's type. This makes the `func_84111E50` fix unviable and leaves `func_841137F8`, `func_8411388C`, `func_8411B160`, `func_84115988` blocked. It is *not* a blanket N->N+1 rule: the same edit on `BattleAnim_ModelDispatch_044` produced zero drift. The probe's link-shape check reports it as `section_layout_drift` before any gate -- always probe a `companion_edits` change rather than reasoning about it.

## Unsolved shape: branch-likely null guard (AGENTS.md §5) (2026-08-28)

A leading null/zero guard that IDO emits as a branch-likely (`bnel`/`beql`) where every C spelling produces a plain `bne` -- `func_84112418`. The §4 guard-polarity row does not cover it.
