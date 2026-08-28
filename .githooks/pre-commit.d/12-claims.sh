#!/bin/sh
# Refuse to commit a disasm/src file a different, still-live runner session
# holds (tools/file_claims.py's registry). PRAGMA_CLAIMS_SKIP=1 bypasses
# (state the justification in the commit message).
set -eu

repo_root=$(git rev-parse --show-toplevel)
exec python3 "$repo_root/tools/check_file_claims.py" --staged --repo-root "$repo_root"
