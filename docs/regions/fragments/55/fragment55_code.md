# fragment55_code matching notes

## func_8670A404 — accepted C, session 65

The original no-argument initializer is called by original `func_8670A4D4` without outgoing argument setup. It initializes six float fields through a float view of the existing state global, copies the two existing float data values, sets two halfwords, and invokes the canonical one-pointer `func_8003F1DC` seven times. Its compiled definition confirms the pointer/void contract. Existing global declarations and accepted siblings are retained; no invented formals, helper signature, padding or FAKE construct is introduced.

Keep explicit references to existing D_8670C684 and D_8670C688 rather than emitting replacement literal data. The ordinary field stores retain the original pre-frame float/halfword scheduling and the seven actual object addresses. The first candidate matches all 52 original words and the 24-byte frame and preserves the complete retail ROM.

Full fleet fragment55_code history was read. No exact owner attempt or owner-specific recipe exists for A404. The unrelated 0018C .9798 normalized/.7475 raw, 00588 .9625/.8625 and exact-span .9620/.8608, 00418 .9565/.9565, 0427C .9487/.5641, 068EC .8690/.4643, 097D8 .6491/.3246, 08EDC1/.8539 and other recorded plateaus remain excluded. Inspected-only A404 from earlier sessions was not a failed trial; no old failed recipe is replayed.

Validation: default host syntax checks, `make rom COMPARE=1 -j2`, and explicit `md5sum -c baseroms/us/checksum.md5` pass with retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`. No CI, verification, tool, layout, data, linker or naming edits belong to this owner change.
