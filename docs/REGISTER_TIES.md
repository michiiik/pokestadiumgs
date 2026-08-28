# Register-allocation ties

A **register tie** is a near-miss owner whose best recorded attempt has
`similarity_score >= 0.99` (opcodes/immediates match almost everywhere) but
`mismatch_kind == "register_allocation_only"`: the only remaining diff is
*which* register IDO picked, not the code shape. `similarity_score` (register
IDs normalized away) sits near 1.0 while `exact_similarity_score` (raw,
register-sensitive) is visibly lower for the same attempt -- that gap is the
tell. Source-shape edits (declaration order, temp width, hoisting) rarely fix
these; a random-restart search (`decomp-permuter`) usually does, cheaply.

## Recognizing one in runner output

- `mismatch_kind: "register_allocation_only"`, `similarity_score >= 0.99`.
- `expected_instruction_text`/`actual_instruction_text`: same opcode and
  immediate, different `$reg`.
- Survives several hand variants (declaration order, temp hoist/inline,
  width swaps) at the same ~0.99+ score without moving.

## The rule

**Agents stop after two batches.** Still a clean register tie after two
probe-only batches (roughly 12-24 variants) of hand analysis? Stop -- leave
the stats record (the near-miss tooling reads it) and move to the next
owner. **Coordinators run the permuter overnight**, once enough ties have
accumulated, instead of looping agents through the same class of diff.

## Finding the tie pool

```
python3 tools/near_miss_kinds.py tag-ties [--min-attempts 6] [--min-similarity 0.99] [--json] [--names] [--stats PATH]
```

`--names` prints one function per line, ready for `--targets-file`.

## The overnight command

```
python3 tools/sweep_targets.py --near-miss --tie-pool \
    --near-miss-parallel 4 --near-miss-kind-seconds 300
```

`--tie-pool` computes the same pool as `tag-ties` internally (same
`--stats`/`--tie-pool-min-attempts`/`--tie-pool-min-similarity` defaults).
Pass `--targets-file ties.txt` (from `tag-ties --names`) to pin an exact
list instead. `--near-miss-kind-seconds` gives `register_allocation_only`
(and `immediate_drift`) owners a 300s permuter budget instead of the plain
45s/120s defaults. `--skip-attempted` never applies here (see `--help`): a
tie is targeted *because* it was already attempted by hand.

## Reading the result the next morning

Run `tag-ties` again. A conversion shows up as an `accepted` attempt labeled
`permute:<original-label>` (the near-miss permuter prefixes every outcome it
records with `permute:`), and the owner drops out of the pool (accepted
owners are excluded). An owner still listed with `permuted: true` was
retried and remains open -- it needs a different candidate shape or a
longer budget, not more hand variants; do not send it back to an agent.
