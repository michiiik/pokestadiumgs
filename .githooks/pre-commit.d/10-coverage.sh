#!/bin/sh
# Regenerate COVERAGE.md from the staged tree (the index, i.e. what this
# commit will contain) and stage the result, so the coverage snapshot lands
# in the same commit it describes instead of lagging by one commit the way
# the old post-commit hook did.
set -eu

repo_root=$(git rev-parse --show-toplevel)
python3 "$repo_root/tools/update_coverage.py" --repo-root "$repo_root" --staged
git -C "$repo_root" add "$repo_root/COVERAGE.md"
