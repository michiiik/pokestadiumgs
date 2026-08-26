#!/bin/sh
# Refuse to commit a removed GLOBAL_ASM pragma whose function has no
# `accepted` runner attempt in the probe stats. DECOMP_PROVENANCE_SKIP=1
# bypasses (state the justification in the commit message).
set -eu

repo_root=$(git rev-parse --show-toplevel)
exec python3 "$repo_root/tools/check_decomp_provenance.py" --staged --repo-root "$repo_root"
