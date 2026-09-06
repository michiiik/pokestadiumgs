#!/bin/sh
# Refuse to commit a symbol_addrs_code.txt rename (an existing address-keyed
# entry's name changed) that doesn't also add a matching aliases.ld
# compatibility entry in the same commit. See tools/check_alias_rename.py
# and tools/container_merge.py's merge() for the convention this enforces
# (PR #58/#59). ALIAS_RENAME_SKIP=1 bypasses (state the justification in the
# commit message).
set -eu

repo_root=$(git rev-parse --show-toplevel)
exec python3 "$repo_root/tools/check_alias_rename.py" --staged --repo-root "$repo_root"
