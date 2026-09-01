Wave 32 fleet assignment — 2026-09-01, disjoint by tree.
Enforced here because claims are advisory and per-job: nothing else stops two
trees burning boxes on the same owner.

WHAT CHANGED SINCE WAVE 31: the permuter works again (9e9a92b0 — its venv
interpreter was being symlink-resolved to the system Python, so none of the
venv's site-packages imported). 562 owners sit at a register tie that
source-shape variants provably cannot close, and until now the documented
escape hatch was silently dead. Two trees are pointed at that pool.

tree 1  gs-fleet-1  PERMUTER + hand
                    disasm/src/fragments/79/fragment79_393CA0.c  (31 tie owners,
                    ~180 ready-fresh; requeues: func_841262C4, func_84137CA4
                    sim 1.0000 raw 0.5833, func_8412BF4C)

tree 2  gs-fleet-2  PERMUTER + hand
                    disasm/src/229E0.c  (23 tie owners, ~168 ready-fresh;
                    requeue: func_800275E8 sim 0.9474, 16 hand variants tied —
                    region notes say permuter, not more spellings)

tree 3  gs-fleet-3  HAND
                    disasm/src/fragments/14/fragment14_FF070.c  (requeues:
                    func_8130BC44 stuck-16 frame 0x30 vs 0x28; func_81309740
                    tooling-blocked on func_8130785C's void extern)
                    then disasm/src/fragments/24/fragment24_150C10.c

tree 4  gs-fleet-4  HAND — strongest single lead of wave 31
                    disasm/src/585D0.c  (func_80060250: 0.9206 normalized,
                    exact shape, ONLY an 8-byte frame overshoot — 0x4C8 vs
                    0x4C0; full reconstruction in the region note. Plus 11 tie
                    owners for the permuter. Skip the 43 JT_UNREADY owners.)

tree 5  gs-fleet-5  PERMUTER
                    disasm/src/fragments/20/fragment20_12C460.c  (func_82614BD0:
                    exact size, 0.9706/0.9559, 12 attempts on one fingerprint,
                    lui CSE tie — textbook permuter case; func_826131A4 0.8182,
                    17 attempts, arg0→s2 vs a1 tie)
                    then disasm/src/fragments/47/fragment47_246640.c
