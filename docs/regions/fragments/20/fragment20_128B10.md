# Region notes -- disasm/src/fragments/20/fragment20_128B10.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Wave 19 successor handoff (2026-09-01)

tooling-blocked/requeue: `func_82601968` received 56 runner-only variants in 7 batches. No candidate produced a probe hit, link verification, source installation, or full-ROM gate. The best `bcopy:induction:record-shift` / `outer-explicit` body had the exact 284-byte span, normalized similarity 1.0000, raw similarity 0.9014, and `register_allocation_only` drift across seven instructions involving entry-add order, table-plus-offset order, destination outer-index temporaries, and the `MFLO` destination. The advisory stable fingerprint at offset 57 is expected `0x864e0088: lh $t6, ...` versus actual `0x86430088: lh $v1, ...`; 15 prior attempts carry the same fingerprint.

Attempted hypothesis families: pointer/index/table-local forms; s16 and s32 temporaries; record loops; bounds and constants; destination and offset arrangements; pointer increment; and outer-expression variants. The isolated worktree could not be used after the worktree permission failure, so the shared clone was used with `PRAGMA_PROBE_WORKERS=1`. The MCP `permute_candidate` path is separately blocked by `ModuleNotFoundError: No module named 'toml'`, and later shell inspection hit host-level `CreateProcess` `Too many open files` (`EMFILE`).

Next action: repair the missing `toml` dependency and descriptor/process lifecycle issue, then resume with a materially different declaration/order or ABI-lifetime hypothesis. Do not repeat the exhausted pointer/index, temporary-width, loop, bounds/constant, destination/offset, pointer-increment, or outer-expression families. Gate only a `link_verified` candidate with `make -C disasm COMPARE=1`.
