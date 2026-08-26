#!/bin/sh
# Run the tools/ unit test suite, but only when this commit actually touches
# tools/*.py, so ordinary decomp commits (asm/C source, docs, etc.) stay
# fast. Set SKIP_TOOL_TESTS=1 to bypass entirely (e.g. a deliberate WIP
# commit, or when the suite is known-broken and being fixed in a follow-up).
set -eu

if [ "${SKIP_TOOL_TESTS:-0}" = "1" ]; then
    echo "20-tests: SKIP_TOOL_TESTS=1, skipping tools/ test suite"
    exit 0
fi

repo_root=$(git rev-parse --show-toplevel)

if ! git -C "$repo_root" diff --cached --name-only --diff-filter=ACMR -- 'tools/*.py' | grep -q .; then
    exit 0
fi

exec "$repo_root/tools/run_tests.sh"
