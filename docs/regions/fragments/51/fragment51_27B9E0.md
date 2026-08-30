# Region notes -- disasm/src/fragments/51/fragment51_27B9E0.c

Per-file spellings, skip lists, and unsolved shapes for this source file. Delivered to agents by `tools/file_brief.py`; extend it with `tools/region_notes.py append`.

## Fleet box 2026-08-31: float leaves requeued (2026-08-31)

No accepted owner. func_86305BC0 received 12 valid CC_CHECK-enabled probes across the box; best raw similarity 0.9412 with immediate_drift, retaining a 136-byte body but differing in dot-product operand order and later float allocation. Requeue BC0 targeting declaration/lifetime shapes for those two differences. func_86305D88 reached normalized/raw 0.6579/0.5000; a cap-global spelling caused section_layout_drift, so do not repeat it until layout handling is resolved. func_86305FD8 was not attempted. No source change or ROM gate.
