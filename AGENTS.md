# Repository agent guidance

## Byte-matching decompilation

- Treat `pret/pokestadiumgs` as the immutable US-ROM matching baseline.
- Keep descriptive names independently in linker aliases and the symbol registry.
- Work in small, coherent subsystem batches; do not commit discovery-by-discovery changes.
- Replace an assembly owner with C only when its full ROM remains byte-identical.
- Keep the original assembly as the comparison oracle and run `COMPARE=1` after every batch.
- If comparison fails, classify the first drift as an instruction mismatch or layout/address drift, then reshape or revert the batch.
- Commit verified subsystem batches only; defer large state machines until smaller compiler-faithful patterns are established.
- Use the MCP candidate runner sequentially per function: try about 10 plausible compiler-faithful variants for ordinary functions, expanding to 10–50 for difficult functions when justified; stop trying that function after the first accepted candidate and retain only byte-identical winners.
- When available, use Stadium 1 as a pattern reference: prioritize direct wrapper return-vs-void forms, explicit `s32` loop counters, array-index versus pointer-add variants, deliberate signed/unsigned masks, explicit null checks, and `uintptr_t` casts for raw address arithmetic. Treat these as candidate-generation hints, not proof of Stadium 2 ABI compatibility.
- Document recurring patterns discovered from successful conversions and repository-wide scans in this guide, including the evidence and limits of each heuristic. Use those learnings to prioritize candidate variants, but continue to verify every owner with `COMPARE=1` rather than treating a pattern as proof.
- Current repository scan reinforces these candidate hints: preserve narrow `sb`/`sh`/`sw` widths, initialize results before explicit NULL branches, keep exact wrapper prototypes and call order, retain explicit temporary buffers in multi-call wrappers, and use raw 32-bit global/address arithmetic where the assembly does. For difficult state helpers, try raw-global declarations plus explicit `(u8 *)(u32)global + offset` expressions before inferred structs; these remain ABI hypotheses until comparison proves them.
- Use `tools/scan_asm_families.py` to group pragma-backed US owners by assembly shape and emit per-source runner bundles. Its generated wrapper/lookup bodies are hypotheses only; inspect the manifest's connected callees, globals, tables, bounds, and memory widths, then run each bundle through the sequential candidate runner and verify the combined ROM before committing.
