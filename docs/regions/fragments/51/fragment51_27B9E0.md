# fragment51_27B9E0 matching notes

## func_86306690

One independent 32-word owner now uses C with two genuine pointer arguments and no result. Original func_86306710 places its state pointer in a1 before the mode guard and loads the object pointer into a0 in the call delay slot; it ignores the result. The owner checks signed byte 33 against -1. On a successful predicate it copies that byte to byte 32 and stores -1 at byte 33, preserving the original load/store behavior.

The complete original func_86304920 establishes a word result and ten float arguments: f12/f14, the a2/a3 home words consumed as floats, and six stack floats. The caller supplies the object's floats at offsets 72 and 76, followed by 0, 180, -180, 0, 0, -180, 180 and 0. No integer prototype or invented argument is used. The helper is retained in assembly. No global, data, padding, layout, tool or verification changes are involved.

The first nested-guard recipe exactly reproduces all 32 instructions, the 48-byte frame, argument home at stack offset 52, constants and streamed byte stores. Full US make rom COMPARE=1 with default host syntax checks and explicit md5sum -c baseroms/us/checksum.md5 passes retail 1561c75d11cedf356a8ddb1a4a5f9d5d. A current-head Public PR ROM Gate must still execute successfully before merge. No semantic names, new fakes or token-known changes were introduced.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact owner attempt or reference and no normalized/raw score for this owner. Full regional notes were read: func_86305BC0 remains deferred after 12 probes with best raw 0.9412 and operand/lifetime differences; func_86305D88 remains deferred at normalized/raw 0.6579/0.5 with a rejected global/layout form. Neither family was retried. Current master had no regional document here. Every open PR scope was inspected, including own #1031/#1032 and foreign fragment 13 dispatch/layout #1029, whose owners remain deferred.
