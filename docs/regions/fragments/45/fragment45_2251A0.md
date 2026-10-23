# Fragment 45 text references and panel visibility

## Accepted batch against master `43aced10`

| Original owner | C name | Instruction bytes |
| --- | --- | ---: |
| `func_8AB02F94` | `TextReference_GetText` | 76 |
| `func_8AB04BD4` | `TextPanels_UpdateVisibility` | 192 |

Total: 268 bytes. Existing implementations on master, including
`func_8AB02C20`, `func_8AB02EF8` and `func_8AB02FE0`, are preserved. They are
excluded from the new-owner count.

### Reference lookup

Each reference contains an unsigned 16-bit archive ID and entry ID. The
unsigned 16-bit index selects a four-byte pair. Capturing both keys before
calling `func_8004C874` reproduces the original argument-home store and
register allocation; caching only the reference pointer does not. A failed
lookup returns `D_8AB1143C`, whose existing data is the string `NULL`.

`src/4CC20.c` defines the two-argument text lookup as a pointer-returning
wrapper over `func_8004C7A0(NULL, 0, archive, entry)`. Its stale signed-word
return declaration in this unit is corrected to that definition. The
separate declaration-only gate preserves the entire module and retail ROM.
No extra argument inferred by a standalone draft is added.

### Visibility update

An ordinary four-iteration `for` loop selects between the first two panel
arrays according to the word at `D_8AB14218`; the third and fourth arrays
are always enabled. Bit 0 of each node's flags halfword at offset 2 controls
render traversal in `func_8004ECD4` (`src/4F800.c`). The neighboring
`func_8AB04AE4` clears the same bit when hiding these panels.

Explicit pointer-walk loops trigger compiler unrolling and grow to 504-516
bytes. Indexing the four pointer arrays lets the compiler recover the
original 192-byte loop and strength-reduced pointer walk. No loop is manually
unrolled, and no dummy storage, forced register or instruction rewrite is
introduced.

### Verification

Normal host-syntax-enabled full-ROM gates pass, including the final named
and declaration-cleaned source. US MD5:
`1561c75d11cedf356a8ddb1a4a5f9d5d`.

Independent comparison preserves all 23,008 text bytes, 48 rodata bytes,
81 function starts/extents, full linked fragments 45/50/79 and four collateral
objects. Frozen inputs, objects, linker output, ELF and ROM have externally
checked hashes. Fresh and leading-blank controls cover the native proposal,
public proposal and unchanged public predecessor. The public Python suite runs
77 tests with 14 skips and no failures.

The reference getter has direct link verification. The visibility loop goes
through the sequential ROM gate because its endpoint uses
`D_8AB14458 + 16`, equivalent to fixed symbol `D_8AB14468`. One shared HI16
record represents the endpoint addend while serving both same-page low
halves; its rounded high-half value is unchanged. The allowed relocation
sites and both fixed symbol addresses are checked explicitly, and all linked
fragment bytes remain identical. The baseline also preserves an existing
upstream `D_8AB11210 - 8` reference to `D_8AB11208` in `func_8AB05254`.

Object-level negative controls reject changed text, rodata, endpoint addend,
shared high page and relocation symbol. Coverage files and private probe,
compiler and proof artifacts are excluded from this batch.

## Remaining work: `func_8AB03194` / register-tie, requeue

The preload loop copies archive/entry pairs to `D_8AB14D08`, resolves each
pair through the real two-argument text lookup, appends two `0xFFFF`
halfwords and returns the masked count. The retained scalar reconstruction
has the original 152-byte extent, 40-byte frame and complete opcode sequence,
but raw similarity is 0.8158: the first key uses v1 where the original uses
a2, with related call-argument temporary differences.

Direct destination reads, source snapshots, narrow/word key locals,
postincrement copies, masked word returns and declaration-order changes were
compared. A calibrated 90-second four-worker source search reproduced all
38 base words and relocation targets; score improved from 40 to 35 through
a named terminator. Its other proposal adds a redundant value alias and is
excluded. Using a named terminator throughout the loop and tail still leaves
the measured register residual. Eight unsigned-word key variants instead
produce 148-byte bodies (best raw 0.7368). No preload body is installed.

Next action: observe the scalar-key global-color decisions and their
interference before another source campaign. Preserve the two real lookup
arguments and the signed count increment followed by unsigned return masking.
