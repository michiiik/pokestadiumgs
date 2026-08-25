#!/bin/sh
# Install the optional decompilation helpers used by the pragma MCP runner:
#   - m2c (MIPS to C drafts)            -> disasm/tools/m2c
#   - decomp-permuter (candidate search) -> disasm/tools/decomp-permuter
#   - a private venv with the permuter's Python dependencies
# All three locations are gitignored. Re-running updates nothing that already
# exists; delete a directory to reinstall it.
set -eu

root="$(cd "$(dirname "$0")/.." && pwd)"
tools="$root/disasm/tools"
python="${PYTHON:-python3}"

if [ ! -d "$tools/m2c" ]; then
    git clone --depth 1 https://github.com/matt-kempster/m2c.git "$tools/m2c"
fi
if [ ! -d "$tools/decomp-permuter" ]; then
    git clone --depth 1 https://github.com/simonlindholm/decomp-permuter.git "$tools/decomp-permuter"
fi
if [ ! -x "$tools/decomp-venv/bin/python3" ]; then
    "$python" -m venv "$tools/decomp-venv"
    "$tools/decomp-venv/bin/python3" -m pip install --quiet toml Levenshtein pynacl
fi

"$python" "$tools/m2c/m2c.py" --help >/dev/null
"$tools/decomp-venv/bin/python3" "$tools/decomp-permuter/permuter.py" --help >/dev/null
echo "decomp tools ready: m2c, decomp-permuter, decomp-venv"
