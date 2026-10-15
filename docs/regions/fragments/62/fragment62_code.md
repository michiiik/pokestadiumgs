# Fragment 62

## 2026-10-15: func_86C000B4

Matched the independent 37-instruction owner with a word argument/result and a switch retaining the incoming value for unhandled cases. The original caller func_86C00148 passes its word state and consumes the returned word. Modes 0 and 2 query the existing byte-result StageContext_GetFadeMode; mode 1 calls the existing word-result func_86C002C4 and forwards duration 5 to StageFade_StartFromTransparent when that result is nonzero.

This owner was previously inspected without a trial because the fade wrapper's implicit forwarding needed an ABI audit. Current master has the explicit canonical s32 StageFade_StartFromTransparent(s32) definition, resolving that prerequisite. No invented arguments or changed helper definitions are needed. No padding or shared switch tails are involved.

The fleet history at afee707ab78d3f63f2f9deeadc7551ec0080eeed contains no exact owner attempt (including the solved archive), owner references, or fragment 62 region note; consequently no historical normalized/raw similarity score exists for this owner. All open PR scopes were documentation only before the trial.

The first candidate passes the full US build with default host syntax checks and COMPARE=1, followed by md5sum -c baseroms/us/checksum.md5: retail 1561c75d11cedf356a8ddb1a4a5f9d5d. The trial is based on master a6247e6263c537e663eb035e7fbac5cd6a064150 and preserves all 206 earlier process matches. No new semantic names, tokens, fakes, data, tooling, layout, or verification changes.
