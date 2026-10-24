# Fragment 45 state handlers

## Matched handlers

| Owner | Instruction bytes |
| --- | ---: |
| `func_8AB0E21C` | 100 |
| `func_8AB0E280` | 108 |

`func_8AB0E21C` defaults to state 34. Argument zero calls
`func_8AB04AE4`, which clears panel visibility flags in
`src/fragments/45/fragment45_2251A0.c`. Argument one checks
`StageContext_GetFadeMode` and, when it returns zero, returns the result of
`func_8AB0E4BC(0)`. Other arguments leave the default state unchanged.
Its forward declaration now reflects the signed-word return value.

`func_8AB0E280` always returns state 36. Argument zero resets the signed
halfword at `D_8AB1723A`. Argument one checks that counter before incrementing
it: a value of at least 10 calls `func_8AB0E2EC(0)`, which starts a fade from
transparent with duration argument five. The counter continues incrementing
after that call; it is neither clamped nor reset. Other arguments perform no
counter update. A local pointer to the counter preserves the original
separate loads around the conditional call.

These operations are established by source and US ROM disassembly. No
runtime observations or broader gameplay interpretation are claimed.

## Verification

The working-tree changes based on `ba03721d554a0d5f588c5b0c10914d96f0ab7b8a`
were verified for `VERSION=us` with the normal host syntax check and a fresh
compile of `src/fragments/45/fragment45_2324B0.c`. The linked ROM compares
byte-for-byte with `baseroms/us/baserom.z64`, with MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`. Both owners retain their original
addresses and extents. The match uses ordinary C without instruction
rewrites or forced registers.
