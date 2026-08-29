# Region notes -- disasm/src/fragments/47/fragment47_24AE60.c

Per-file spellings, skip lists, and unsolved shapes for this source file.
Delivered to agents by `tools/file_brief.py`; extend it with
`tools/region_notes.py append`.

## 2026-08-29

The box at `git_head cbc9af3` produced 0 accepts from 42 attempts. All 42
attempts targeted `func_86006364` and repeated the same operand/scheduling
first difference: the oracle frame is `addiu $sp,$sp,-0x68` (104 bytes), while
the candidate frame was `-0x60` (96 bytes). Best normalized/raw similarity was
0.9825/0.8772. Treat this as a frame-layout/source-shape problem and do not
repeat the same hypothesis family without changing the local declarations.

The file also contains fresh dispatcher/large owners and register-tie or
near-miss owners; rank them separately after reading the current file brief.
