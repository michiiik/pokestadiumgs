#!/usr/bin/env bash
# Dispatcher for tools/container_agent.py's --generator-cmd. Point the
# driver at:
#   container/generators/run_generator.sh {prompt} {batch}
# and select which coding agent generates candidates with the AGENT env var
# (default: claude). See container/generators/README.md for the full list.
#
# AGENT=alibaba and AGENT=zai are shorthands for AGENT=claude_via
# CLAUDE_VIA=<that provider> (container/generators/claude_via.sh -- the
# Claude Code CLI pointed at a third-party Anthropic-compatible endpoint):
# expanded here rather than requiring the caller to set both env vars.
#
# Usage: run_generator.sh <prompt-file> <batch-file>
set -eu
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

AGENT="${AGENT:-claude}"
case "$AGENT" in
  alibaba|zai)
    export CLAUDE_VIA="$AGENT"
    AGENT=claude_via
    ;;
esac
TARGET="$SCRIPT_DIR/$AGENT.sh"

if [ ! -f "$TARGET" ]; then
  echo "run_generator.sh: unknown AGENT '$AGENT' (no $TARGET)." >&2
  echo "run_generator.sh: available agents:" >&2
  for f in "$SCRIPT_DIR"/*.sh; do
    base="$(basename "$f" .sh)"
    case "$base" in
      run_generator|_common) continue ;;
    esac
    echo "  - $base" >&2
  done
  exit 1
fi

exec "$TARGET" "$@"
