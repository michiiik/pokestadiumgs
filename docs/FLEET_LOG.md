# Fleet measurements and incidents

Evidence behind the coordinator rules in `AGENTS.md` §1. Rules live there;
the numbers and the war stories live here, so `AGENTS.md` stays a rulebook.
Per-file spellings and skip lists are not here either — they live in
`docs/regions/` and reach an agent through `tools/file_brief.py`.

## Throughput

| Date | Shape of the run | Result |
| --- | --- | --- |
| 2026-08-27 | Pilot: 4 agents, 20 min, text-segment files | 40 owners, ~17k tokens/owner (~10k text, ~55k fragments) |
| 2026-08-28 morning | 6 boxes on the text-segment files no session had touched for 19 h (`585D0` ×2, `14640`, `6E850`, `CE80`, `4AC10`) | 12 owners from ~295 variants, ~105k tokens/owner |
| 2026-08-28 evening | 15 boxes on 9 fragment files, family unlocks + hand-off | 85 owners, ~20–30k tokens/owner on the productive files |

A single hand session, for comparison, lands 4–5 owners/hour.

## 2026-08-30 Wave 4 low-yield audit

The 60-minute wave produced one accepted owner from five boxes: 611 attempts,
543 genuine probe rejections, 54 compiler failures, 12 invalid companion-edit
batches, and one full-ROM-gated acceptance. The agents stayed on their assigned
owners; the low yield was target and hypothesis quality.

- `func_8001874C` was selected from a fresh-heavy file but had 281 prior
  attempts at start; its best result was 0.9231 normalized / 0.8462 raw with
  repeated prologue drift.
- `func_8AC00028` was an intentional requeue with 203 attempts and repeated
  scheduling drift; it was a permuter/tooling follow-up, not a fresh slot.
- Three genuinely fresh owners produced the one acceptance: `func_82208DCC`
  accepted after a state-loop/permuter pass; `func_82609584` reached
  0.9720 normalized / 0.5514 raw; `func_8AE01A90` reached 0.9677 / 0.9516
  with persistent operand drift.
- The 12 companion failures named unresolved pragma owners. Compiler failures
  included unsupported IDO `uintptr_t`, syntax errors, and conflicting
  prototypes; these should be rejected before the batch starts.

Corrective process: rank at owner level, reserve requeues without counting them
as fresh slots, distinguish display-list GBI from texture-load families, and
preflight invalid owners and companion edits.

## 2026-08-30 jump-table readiness audit

The next five-box wave produced no new source acceptance. The boxes did make
progress on durable diagnostics, but several selected owners were prerequisites
rather than probeable C work: `6E850.c` had three dispatcher owners blocked by
the missing per-file rodata layout, `14640.c` had an owner whose assembly begins
with a local `.rodata` section, and `585D0.c` still contained a large
layout-blocked pool. A concurrent foreign change accepted
`func_8003FC34` in `229E0.c`; it is not counted as a result of this wave.

The repository-wide audit found 649 active jump-table owners in 177 files:
548 `dispatcher_switch` and 101 `jump_table_map` owners. Only 60 owners in 24
files have a matching dotted `.rodata` subsegment in `rom.yaml`; 589 owners in
153 files do not, including all 505 fragment owners. In the default <=128
instruction pool, 358 jump-table owners remain and 329 in 111 files are
unready. The previous ranker counted these as fresh, so a large apparent fresh
pool could produce a zero-yield box without any agent hypothesis being tested.

The corrective tooling now reports `READY_FRESH`/`JT_UNREADY` in
`rank-files`, exposes per-owner `jump_table_status` in `targets`, and makes
`file_brief.py` warn about owner-local rodata that disappears with a pragma.
The next wave should select ready fresh owners, reserve explicit requeues
separately, and route unready owners to a layout-preparation queue.

## What the numbers say

- **Family unlocks carry the yield.** Half the morning's accepts came from one
  file where one spelling (the `gbi.h` macros) unlocked a family; in the
  evening, `fragment79_393CA0` gave 10, 10, 8 and 4 owners over four boxes,
  almost all as 3–4 siblings sharing a spelling.
- **Hand-off sustains it.** Boxes that received the previous agent's winning
  spellings *and* an explicit skip list ran at ~20–25k tokens/owner; the
  morning wave, with no hand-off, ran at ~105k.
- **Fragments are not 5× more expensive than text segments.** The earlier
  ratio measured agents working without family unlocks.
- **Files a running fleet has left alone are usually hard, not merely
  unvisited** — their small owners are register-allocation ties. Rank by the
  `fresh` column: the two files picked off `rank-files`' composite `score`
  (`fragment7_BA250`, 19 fresh / 28 drift; `fragment17_10FFC0`) returned 0
  accepts between them, while every fresh-heavy fragment returned 2–10.
- `analyze_family_shapes.py siblings --all` found 984 unsolved shape groups
  tree-wide on 2026-08-28; the largest have 7–12 members.

## Incidents

- **The git index is shared between sessions.** A coordinator's tooling commit
  (`c709fc3`), staged with three explicit `tools/` paths, still committed an
  agent's `fragment79_38EFE0.c` because that agent had already run `git add`
  and had not yet committed. Hence the `git commit --only` rule. Verified on
  `9494a60`: `--only` needs only your own path — the coverage hook stages
  `COVERAGE.md` into the partial-commit index by itself.
- **Agents distrust mid-task messages, correctly.** Three separate agents
  refused genuine coordinator instructions delivered by message as suspected
  prompt injection; one of them also caught that the instruction was wrong
  (it asked the agent to stage a path outside its assignment). Rules now go
  into a committed document first, and a message may carry only a pointer to
  the sha.
- **Two sessions on one file.** A Codex session and a fleet agent both worked
  `fragment43_1E5A10.c` for ten minutes (Codex commit `ae9d92e` interleaved
  with five of ours) before the overlap was noticed. Re-check claims and
  `git status` when reassigning a file for a second box, not just when first
  assigning it.
- **Claim identity is per job, not per agent.** Every agent under one
  coordinator shares `$CLAUDE_JOB_DIR`, and a per-agent `CLAIMS_OWNER` export
  does not survive between Bash calls, so agents refused their own claims.
  Install-time claims are advisory as a result (`PRAGMA_CLAIMS_ENFORCE=1`
  restores refusal); the commit-time hook is the real guard.
- **A whole-disk `find`** (`find / -iname gbi.h`) walked `~/Music` and raised
  a macOS media-library permission prompt. The N64 headers are under
  `disasm/lib/ultralib/include/PR/`.
- **Agents sharing one scratch directory** overwrote each other's
  `batch1.py`; each agent now gets its own subdirectory.
