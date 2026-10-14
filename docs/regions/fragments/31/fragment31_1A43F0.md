# Region notes: fragment31_1A43F0

## 2026-10-14: func_882313A4

The owner has three incoming formals: signed bytes `arg0` and `arg1`, and
unsigned halfword `arg2`. `func_88802DCC` stores the supplied callback at
state offset 0x58; `func_888003EC` invokes it with two signed byte loads and
an unsigned halfword load. No additional arguments or return value are needed.

The accepted source registers the existing callbacks through `func_88005B60`,
allocates four bytes through `Util_Malloc`, stores the three fields through
`D_882349D0`, and publishes that pointer through `D_8800EF54`. The repeated
global pointer reloads are part of the retail instruction sequence.
`unk_func_882313A4` describes offsets 0x00, 0x01, and 0x02 without assigning
semantic names to unknown tokens. The existing callback symbol `D_88000E4C`
is preserved; its shared assembly location is not a separate matching target.

The body has 32 executable instructions followed by three alignment nops.
`C_FUNCTION_PADDING(12)` preserves those bytes. The first typed record spelling
matched; changing the record and field names to the contributing style guide's
unknown-token forms preserved the match.

History audit: no exact owner attempt or source-region note was present in
`michiiik/pokestadium-fleet/knowledge-base/gs-attempt-history` at main
`afee707ab78d3f63f2f9deeadc7551ec0080eeed`. Open PR scopes were checked for
an existing owner replacement before publication.

Independent validation on master `ee1809985d223e91e535e5cbe9fb4d7cabbce68c`:
US ROM rebuilt with default host syntax checks and `COMPARE=1`; then
`md5sum -c baseroms/us/checksum.md5` passed with retail MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. All twelve other open process matching
PRs were excluded, including both files of #885. The combined 186-owner
workspace also passed. This local result does not establish the Public PR ROM
Gate for a later PR head or merge result.
