#!/bin/sh
# Run the tools/ unit test suite from the repo root.
set -eu

repo_root=$(cd "$(dirname "$0")/.." && pwd)
cd "$repo_root"
exec python3 -m unittest discover -s tools -p 'test_*.py'
