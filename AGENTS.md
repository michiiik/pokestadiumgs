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
