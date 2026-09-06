# AGENTS.md historical entries

Fully-resolved entries moved out of `AGENTS.md` §5 ("Tooling backlog and
recurring unsolved shapes") to keep that section focused on open work. Each
entry below describes a bug and a fix with no remaining open caveat at the
time it was moved — the fix is already reflected in current tool behavior
(and, where relevant, in the tool reference in `AGENTS.md` §3). Kept
verbatim for historical reference; do not restore into `AGENTS.md` unless a
regression reopens the underlying issue.

- Runner (fixed 2026-08-30): raw object comparison previously rejected exact
  source spellings when equivalent symbol-plus-addend forms changed only
  relocatable immediate fields. The runner now promotes same-topology,
  recognized relocation-field-only differences to an unverified sequential
  full-ROM gate. An audit found seven high-similarity owners worth replaying;
  `relocation_masked` must never be treated as `link_verified`.
- Runner (fixed 2026-09-02): `companion_edits` now substitutes candidate
  owners before applying same-file extern/prototype edits, so a stale callee
  signature can be corrected in the same candidate transaction while the
  no-add/remove-pragma guard remains active.
