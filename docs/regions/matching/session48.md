# Matching investigation, session 48

## func_8F100020: retained assembly

One audited source recipe failed the full US ROM checksum. Its output MD5 was `acd230aee923b431c2be2360b27340eb`, rather than retail `1561c75d11cedf356a8ddb1a4a5f9d5d`. The original owner remains assembly; the fresh current-master source was restored and the default host syntax / full US `COMPARE=1` build and explicit checksum passed.

Actual ABI: original `func_8F100E78` registers this owner through `func_80037E3C`. Its canonical callback type is a word result with an incoming mode word and node pointer. Registration calls mode 0; the compiled dispatcher calls the callback with mode 2 and a child pointer, then consumes its word result through `D_80124D60`. The owner returns zero on every path, reads the halfword at offset 8 through existing `D_80087200` in mode 2, toggles the real word `D_8F103A50` when mask `0x2000` is set, and sets or clears mask `0x40` in the node byte at offset 2. There are no speculative arguments or return categories.

The ordinary nested mode and input guards, direct word XOR and byte OR/AND reproduce the byte operations and return control. They emit 28 words instead of the retail owner's 27. The global word address becomes a `v0` LUI/ADDIU pair used by the first load/store and is materialized again after the input guard. Retail uses separate early LUI registers and a store LUI instead. This requires supported evidence about the global address lifetime. Do not replay ordinary scalar, raw-pointer, typed-alias, qualifier or declaration forms, and do not change global qualifiers, data, tools or address coalescing to force a result.

History audit: no exact owner attempt or owner-specific recipe was found in fleet main `afee707ab78d3f63f2f9deeadc7551ec0080eeed`. The complete fragment 69 fleet notes were read: unrelated terminal `func_8F10049C` normalized 0.7903/raw 0.3548, `func_8F100B54` 0.8676/0.8676, `func_8F1037C4` 0.9620/0.9494 and `func_8F101FF4` 0.9778/0.2222 were not retried. Current master had no fragment 69 regional document. All open scopes were checked before the trial. Merged matching sources were retained throughout.

Accepted investigations are documented separately with matching PRs #927, #928, #929 and #931. This documentation adds no source or verification changes and is outside the matching-PR merge authorization.
