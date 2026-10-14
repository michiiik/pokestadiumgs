# Matching investigations, session 50

Accepted recipes are documented separately in matching PRs #947 (`func_8414C7D4`), #949 (`func_8130D45C`) and #950 (`func_881000B8`). This document retains one failed investigation. It changes no game source or verification and is outside the matching-PR merge authorization.

## func_81801420: retained assembly

Original `func_81805308` calls this owner without arguments and ignores its result. The compiled `func_818006B4(void)` returns the real float increment, and the SDK `__sinf(f32)` definition confirms the actual single-float ABI. The original owner reads and writes float `D_81805924`, wraps it by subtracting 1 when greater than 1, computes the sine through the existing float `D_81805CD8`, and writes `D_81805920`. The complete body has 34 instructions and a 24-byte frame, with no trailing padding or shared switch tail.

The first valid scalar recipe captured `D_81805924 + func_818006B4() / 60.0f` in `var_f2`, applied the guard, stored it back, and computed `__sinf((var_f2 + var_f2) * D_81805CD8) * 0.5f + 0.5f`. It preserves those operations and the true helper types. It emitted the same 34 instructions and frame, but materialized the address of `D_81805924` in `v0` with LUI/ADDIU instead of the retail separate direct relocations. The global load occurred after the division in `f8` rather than early in `f2`; subsequent FPU register assignments, addition operand order and load/store scheduling differ. Full-ROM MD5: `df3c6223af7c5321cb1fcb681b437e51`.

A supported global-address and FPU value-lifetime model is required before another attempt. Do not replay ordinary captured/global scalar, qualifier, declaration or operand variants. No global declaration, data, compiler, coalescer or layout change was used. The failed source was restored immediately, and the full US build with default host syntax checks and `COMPARE=1`, followed by `md5sum -c baseroms/us/checksum.md5`, returned to retail `1561c75d11cedf356a8ddb1a4a5f9d5d`. The separate then-open #947 implementation was excluded only for the independent trial and restored immediately; no merged source was removed.

History audit: live fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed` has no exact owner attempt, owner reference or `4_AE600` regional document in the consulted catalog; current master had no regional document. No historical normalized or raw similarity score is available. All open scopes were inspected before the trial: #947 covered another owner, #948 covered fragment 73, and #922, #932 and #940 were session documentation drafts.

## Read-only handoffs

Current master notes preserve fresh foreign requeues: `func_8F000098` is normalized/raw 0.9919/0.9675 with a scalar toggle address-materialization residual; `func_8F000284` is 0.9610/0.4675 with loop constant lifetimes. Fragment 73 retains `func_8F500020` at 0.8088/0.3676, `func_8F500414` at 0.9474/0.7895 (snapshot 0.9605/0.6842), and `func_8F5002F4` at 0.8125/0.4750 (indexed 0.8101/0.5443). Fragment 72 retains `func_8F401828` at 0.9500/0.3500, word-handle raw 0.4500. These full notes were consulted; none of their recorded source families was retried.

`func_86C00148` needs the actual fade-duration forwarding ABI before a loop trial. `func_8AF02FC8` has the previously failed offset-40 pointer/spill lifetime family. `func_86408C1C` and `func_8415AD58` need supported global/address models. `func_885011EC` requires a complete callback/helper audit, including the last two narrow formals of `func_88802DCC`; no speculative word-only declaration was used. These owners were inspected without trials.
