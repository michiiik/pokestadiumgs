# Region notes: fragment17_11B210

## 2026-10-18: slot and panel family accepted, 464 original bytes

Four original owners are accepted through the normal native runner, each
with link verification and a successful combined full-ROM gate:

- B850: 176 bytes / 44 instructions, frame 32;
  batch `075276b7577741a9bbaadf4dbb91c234`.
- B930: 84 bytes / 21 instructions, frame 32;
  batch `d46c17384b864291a92e3b97d0a2f4a9`.
- BC40: 60 bytes / 15 instructions, leaf;
  batch `ca4e92e953fd47f6b5dacde9a3a8b34a`.
- BD00: 144 bytes / 36 instructions, leaf;
  batch `daef074e62164d39950572ecdf693285`.

The file advances from 9 C / 19 assembly owners to 13 C / 15 assembly owners
among its 28 original positive-sized function extents. No new runtime
function is added.

### Source and layout evidence

BC7C initializes eight slots with stride 24, storing each slot's state at
pool offset 4 + index * 24 and its final float at offset 24 + index * 24.
B900 clears 196 bytes. Together these establish a four-byte pool prefix and
eight complete 24-byte slots, rather than overlapping 28-byte records.
BC40 searches their state fields in order and returns the first free index,
or -1. The original break/result spelling matches with a typed pool view.

B850 increments the slot counter. Below 21, it computes the short field at
offset 4 as 155 - count * 155 / 20, looks up archive 159 using the selected
12-byte E1D0 frame row, and copies its two float fields to slot offsets
16/20. At 21 or above it clears the slot state. Keep frame selection before
the short-field calculation: reversing them changes temporary allocation.
A local alias for the slot pointer leaves the frame-row spill at 24 instead
of 28; using the actual pointer parameter restores the original home without
adding an unused local. Post-accept typed-field cleanup is byte-inert.

B930 calls B850 for each active slot, advancing a pool-relative cursor by
24 until C20. Its two pointer initializers share one declaration. Splitting
them preserves register roles but changes the order of the low address
instructions. Grouping the real initializers restores all 84 bytes, even
after the advisory runner labels that earlier basin a register tie.

BD00 initializes two mode-specific sets of halfword pairs and always copies
the pair at offset 10 to offset 14, including for other mode values. The
22-byte, halfword-aligned panel view agrees with BF68's traversal stride.
A two-halfword aggregate copy reproduces the original lwl/lwr/swl/swr
sequence; independent component assignments do not. Keep the two-case switch
and offset-based pair names while their complete interpretation is unknown.

BD90 and BE84 set the panel halfword at offset 2 to states 1 and 3;
BDAC and BE94 increment the separate short tick counter at offset 4.
The typed view distinguishes these fields as state and counter. Correcting
their names preserves the frozen complete-object game fingerprint.

### Acceptance controls

Each first accepted complete object was frozen before further compilation:

- B850: `ef6eeee72cd207fa81625cffa91267b7b350e1f2de121597a59fc0bdbf2434d3`.
- B930: `712ccad8fdf06834e8a2512c06f97aabff0845c49c88de790aaf9941b315f777`.
- BC40: `2ecfe22071c83938545ab2b2fc0b2e30080a549e7316e6e9c1bff8aeb6a878cf`.
- BD00: `1cdecd236fedb71910cde55952efa22cfeca2ab18b30b2c28192268e1eb35353`.

Independent strict links resolve every undefined symbol at its actual game
address. The original and every frozen object's complete linked text,
including padding, agree; all 28 function images also agree with the
retail-gated executable. All original starts and sizes are preserved, and
the object has no other allocatable section to hide collateral changes.
Known/type-layout/twenty-blank controls pass. Typed-field cleanup and extern
deduplication reproduce the final frozen game bytes, layouts, defined
symbols and normalized relocations. Accepted owners are not candidate
probes again.

The cleaned source passes the full ROM gate, MD5
`1561c75d11cedf356a8ddb1a4a5f9d5d`, all 427 host syntax checks, 76 native
tooling tests, accepted provenance and whitespace checks. The naming plan
has no established mappings, so address names remain. No fake homes, dead
locals, fixed registers, loosened prototypes, padding, manual unrolling or
compiler/output patches are used. Coverage remains CI-owned; generators,
diagnostic copies, objects and ROMs stay private.

## Earlier handoffs retained from the shared region notes

The available statistics omit the older rows below; zero recorded attempts
in that snapshot does not make these owners fresh.

- BDAC remains `register-tie`: cached-divisor source reaches 216 bytes and
  normalized/raw 1.0/0.8400, with v0/v1 counter/divisor roles swapped from
  offset 4. Direct/cached loads, widths, declaration order, register hints,
  pointer/global aliases and a 75-second search did not close it. Retain the
  divisor-before-increment family for a measured allocator/permuter follow-up.
- BE94 has the corresponding 212-byte `register-tie`, normalized/raw
  1.0/0.8367 and the same offset-4 role swap. Reload the short count after
  incrementing it, retaining a divisor loaded beforehand. The older bounded
  search had no output; do not replay the completed source grid unchanged.
- C340 remains `requeue`: best recorded 232 versus 236 original bytes,
  normalized/raw 0.8644/0.7966. CSE retains C30 in saved s1 instead of using
  a0 initially and separate C30/C5C iteration addresses later. Switch/if
  dispatch and the 22-byte record overlay were already tried. Investigate
  genuine address-expression/aggregate context, not a forced address alias;
  neither interpolation helper is accepted C.
