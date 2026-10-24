# Fragment 45 panel reset delay

`func_8AB10D30` has a matching C implementation (180 instruction bytes).
It defaults to state 70. Argument zero resets the signed-halfword counter
at `D_8AB1744E` and calls `func_8AB01FBC`, which clears `D_8AB126A0` in
`src/fragments/45/fragment45_2251A0.c`.

Argument one increments the counter before calling
`TextHighlight_AnimateScales`. At counter 11 or above, it visits the four
panel pointers starting at `D_8AB12668`, passes each to
`func_8AB00B98` with an all-ones word, and returns `func_8AB10DE4(0)`.
The helper writes that word at offsets 40 and 44 of each panel. Other
arguments return state 70 without those operations.

The pointer loop uses `D_8AB12678`, the start of the next pointer group,
as its exclusive endpoint. The groups are 16 bytes apart and hold four
32-bit pointers each; `func_8AB00084` independently clears 16 bytes for
each group. The panel-reference consumers and both called helpers are in
`src/fragments/45/fragment45_2251A0.c`. Ordinary pointer iteration preserves
the retail loop and the reuse of the result register for its cursor.

The update dispatcher `func_8AB0FE10` calls this handler with argument one
and consumes its returned state. The draw dispatcher `func_8AB0FF40` calls
it with argument two, which leaves state 70 unchanged. These descriptions
come from source and disassembly inspection; no runtime timing is claimed.

Verification targets master `96cf6b8605a6fad481c09959613992801532a311` plus
this change. The normal host syntax check and forced compilation through
`make -W src/fragments/45/fragment45_2348E0.c -j4 VERSION=us rom` pass.
The complete US ROM passes checksum verification and compares byte-for-byte
with the retail ROM; MD5 is `1561c75d11cedf356a8ddb1a4a5f9d5d`.
The original 32-byte frame is preserved without dummy storage, forced
registers, or instruction rewrites.

## Banner and panel visibility delay

`func_8AB10DE4` now has a matching C implementation (304 instruction bytes).
It defaults to state 71. Argument zero resets `D_8AB17450`, enables bit zero
of the node flags at `D_8AB11D00`, and calls `func_8AB04AE4` to hide the
panel groups. It copies archive 57 entry 389 into the 256-byte
`D_8AB126A8` buffer, clears the visibility bit on `D_8AB1725C` and the four
nodes referenced by `D_8AB12678`, emits event 65550 with two zero parameters,
and calls `func_800225C4(40)`.

Argument one increments the signed-halfword counter and calls
`TextHighlight_AnimateScales`. At counter 61 or above, it returns
`func_8AB10F14(0)` instead of state 71. Other arguments leave state 71
unchanged. The preceding handler `func_8AB10D30` enters this state after
resetting the other four panels' words at offsets 40 and 44.

The four-node visibility update is an ordinary four-iteration C loop;
IDO unrolls it into the original stores. The counter pointer precedes the
result declaration, reproducing the result's stack offset 24. No forced
register, dummy storage, or instruction rewrite is used.

The text-copy function is the four-argument pointer-returning
`func_8004C8A0` in `src/4CC20.c`. The three-word event wrapper and the
panel-visibility and highlight helpers are defined in
`src/fragments/45/fragment45_2251A0.c`; `func_800225C4` is defined in
`src/229E0.c`. Behavior descriptions follow these sources and the original
disassembly, without assigning a broader meaning to the remaining globals.

Verification targets master `c3398bdda46be6bd771ef943820dbd644e2a5aa9` plus
this change. The normal syntax-enabled forced source compile and complete
`VERSION=us` ROM build pass. `cmp` confirms byte-for-byte equality with the
retail ROM; MD5 remains `1561c75d11cedf356a8ddb1a4a5f9d5d`.
