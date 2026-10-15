# Fragment 69

## 2026-10-15: func_8F102A20

Matched the independent 30-instruction no-argument owner, called by original func_8F102BC8 with no result use. Existing D_80087200 supplies the halfword at offset 12; the original concrete global D_8F1DECA8 supplies unsigned byte offset 28. Mask 0x200 decrements that byte, and mask 0x100 increments it with a maximum of 2. Keep both independent input tests and both original base materializations.

The original decrement narrows to an unsigned byte before comparing against zero. Its BGEZ always skips the lower clamp, so zero decrements to 255. Preserve the source's unreachable lower-clamp test and label this existing bug with //!bug. Do not silently correct the field to signed or remove the comparison. This is an actual retail bug, not a fake, empty debug operation, padding or independent switch tail.

The first direct byte-lvalue recipe passes the full US build with default host syntax checks and COMPARE=1, then explicit md5sum -c baseroms/us/checksum.md5: retail 1561c75d11cedf356a8ddb1a4a5f9d5d. Based on master 13df50bb51c537a3f669831a147cd7c7654bb95a, preserving all 209 previous process matches and the exact new foreign fragment 13 changes. Source/object/build evidence is retained in work/session-54.

Fleet main afee707ab78d3f63f2f9deeadc7551ec0080eeed has no exact or solved owner attempt or owner reference, so no normalized/raw score exists for this owner. The complete fragment 69 notes were consulted, including the accepted direct-global-lvalue 2A98 recipe and terminal 049C (0.7903/raw0.3548), B54 (0.8676/raw0.8676), 37C4 (0.9620/raw0.9494), and 1FF4 (0.9778/raw0.2222) histories; none was retried. The earlier process failure for 8F100020 remains untouched. All open PR scopes were documentation only before edits. No new names, tokens, fakes, qualifiers, data, tooling, layout or verification changes.
