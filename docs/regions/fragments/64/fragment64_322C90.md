# fragment64_322C90 matching notes

## func_87F00030 — accepted C, session 63

The original no-argument initializer is called without outgoing argument setup by `func_86A004B4` and other original assembly callers. The existing global pointer type is retained; its initial fields are word views. Initialization writes 20, five times that stored value, and two zeros, preserving the original reloads rather than folding those reads into constants.

The allocation chain uses the actual no-argument available-size query, two-word allocator, pointer-based layout processor and allocation finalizer. The canonical resource loader has a narrow unsigned-halfword formal, the lookup returns a word handle, and the compiled `func_87F08E3C` takes a pointer and a word. The existing four-argument `func_87F0252C` definition confirms both record pointers and the count; the container constructor receives its real null first pointer and existing destination. No invented formal, ignored incoming argument or false helper return is used.

The first candidate preserves all 66 original executable words and the 40-byte frame and matches the complete retail US ROM with default host syntax checks enabled. No FAKE construct, padding directive or companion edit is introduced. Existing C siblings and previously accepted owners are retained.

Fleet has no exact owner attempt or regional catalog record for this source. References in failed `func_86405F28` and `func_86107A20` drafts concern their callers and are not attempts of this owner; their inconsistent helper declarations do not override actual compiled definitions. All earlier raw/normalized plateaus and shared-tail exclusions remain in force.

Validation: `make rom COMPARE=1 -j2` and explicit `md5sum -c baseroms/us/checksum.md5` pass with retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. No CI, verification, tools, data, layout, linker or symbol-table changes are included.
