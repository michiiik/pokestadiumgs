# Display thread intro (`src/dp_intro.c`)

## func_80001B20 — 2026-10-17; dp_intro.c complete

Decompilation of `func_80001B20` completes `src/dp_intro.c`, which now has 0 remaining `GLOBAL_ASM` pragmas.

| Original owner | Instructions / bytes | Frame | Status |
| --- | ---: | ---: | --- |
| `func_80001B20` | 98 / 392 | 0x50 | Matched (retail MD5 `1561c75d11cedf356a8ddb1a4a5f9d5d`) |

### Findings and heuristics

- `func_80001B20` is the thread 5 entry point function created in `src/dp_intro.c` line 363:
  `osCreateThread(thread, 5, func_80001B20, NULL, &D_800AB3C0, 0x28);`.
- Configures FPU control register with `__osSetFpcCsr(0x1000C01)`.
- Calls `func_80001FA8` twice for `&D_800AB490` and `&D_800AB480`.
- Initializes client scheduler queue with `Sched_InitClientQueue(leoDiskID, 0, 4)` and registers client via `func_80005568(leoDiskID)`.
- Initializes display task structure via `DisplayTask_Initialize((S1_UnkStruct80001380 *)&D_800AB400)`.
- In the main loop (`while (1)`):
  - Checks `if (*(s16 *)(D_800CD020 + 0xA38) > 0)`: drains events via `DisplayWorker_DrainEvents()`.
  - In `else`:
    - Calls `func_8000A080(0)`.
    - Sets flag `leoDiskID[0xA8A] = 1`.
    - Receives message from `&D_800AB3CC` via `osRecvMesg(&D_800AB3CC, &msg, 1)`.
    - Clears flag `leoDiskID[0xA8A] = 0`.
    - Calls `func_8000A080(1)` and `func_8000A080(2)`.
    - Processes message with `func_8000177C(msg)`.
    - Calls `func_800017F8()` and stores result in `leoDiskID[0xA8B]`.
    - Signals completion to `&D_800AB3E4` via `osSendMesg(&D_800AB3E4, (OSMesg)0x444F4E45, 0)`.
- Lowering shape: Writing the dispatch loop as an `if (...) { ... } else { ... }` inside `while (1)` places both `leoDiskID` and `D_800CD020` in loop depth 1. Because `leoDiskID` has additional usages outside the loop, IDO's `uopt` prioritizes `leoDiskID` into `$s0` and `D_800CD020` into `$s1`, correctly filling branch delay slots with `lh $t8, 0xA38($s1)` and allocating all 7 saved registers `$s0`–`$s6`.
