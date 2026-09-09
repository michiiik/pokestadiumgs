#!/usr/bin/env bash
# Generator wrapper: Google Antigravity CLI (agy), pointed at a Claude model
# instead of container/generators/gemini.sh's default Gemini model, and under
# a SEPARATE Antigravity account/login so its usage is tracked independently
# of AGENT=gemini's quota. Same underlying CLI/protocol as gemini.sh -- see
# that script's header for the full flag rationale (stdin NDJSON to dodge
# Linux's per-argument execve() limit, --print-timeout raised past agy's 5m
# default, --dangerously-skip-permissions only ever inside this sandboxed
# container). This file only documents what's actually different.
#
# Usage: antigravity.sh <prompt-file> <batch-file>
# Default model: claude-sonnet-4-6 (override with GENERATOR_MODEL; confirmed
#   available via `agy models` alongside claude-opus-4-6-thinking and the
#   gemini-3.x family -- agy is a multi-model CLI, not Gemini-specific
#   despite gemini.sh's name).
#
# Why a second login, not just AGENT=gemini GENERATOR_MODEL=claude-sonnet-4-6:
#   fleetctl's cooldown/concurrency bookkeeping (plan.json's `cooldowns`/
#   `agent_concurrency`) is keyed by the bare AGENT name, not agent:model --
#   reusing AGENT=gemini would put Claude-via-Antigravity traffic in the same
#   cooldown bucket as Gemini-via-Antigravity traffic under one account, so a
#   generator_exhausted on one model would cool down both regardless of
#   whether the underlying account-level quota is actually shared. A distinct
#   AGENT name here gets its own bucket in fleetctl's config.
#
#   Separately, and the actual point of this script: a second Google account
#   was logged into Antigravity specifically so this pulls from a completely
#   independent per-account quota, not just a differently-bucketed view of
#   the same one. Confirmed empirically (2026-09-09): a plain
#   `GEMINI_HOME=~/.gs-fleet-agy-creds agy -p "..." --model claude-sonnet-4-6`
#   answered correctly with no interaction with AGENT=gemini's own
#   ~/.gemini-based cooldown state.
#
# Credential home: ANTIGRAVITY_SONNET_HOME (default
#   ~/.gs-fleet-agy-creds), the same four-file shape gemini.sh's login
#   produces under ~/.gemini (antigravity-cli/antigravity-oauth-token,
#   antigravity-cli/installation_id, config/config.json,
#   config/projects/default-cli-project.json) but for the second account --
#   container/run.sh mounts a throwaway copy of it to /root/.gemini (agy's
#   own fixed lookup path, GEMINI_HOME is not itself something agy reads --
#   see that mount's comment) whenever AGENT=antigravity.
set -eu
set -o pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=./_common.sh
. "$SCRIPT_DIR/_common.sh"

PROMPT="$1"
BATCH="$2"

# agy itself has no AGENT-awareness and always reads its fixed
# ${GEMINI_HOME:-~/.gemini} regardless of which script invoked it --
# container/run.sh mounts the second Antigravity account's credentials
# there (from the host's ANTIGRAVITY_SONNET_HOME/~/.gs-fleet-agy-creds)
# specifically when AGENT=antigravity, so the actual in-container
# credential path to check is identical to gemini.sh's, not a separate
# ANTIGRAVITY_SONNET_HOME path inside the container -- that host-side
# variable name is only meaningful to run.sh's own mount-source lookup.
GEMINI_HOME="${GEMINI_HOME:-$HOME/.gemini}"
if [ ! -f "$GEMINI_HOME/antigravity-cli/antigravity-oauth-token" ]; then
  echo "container/generators: antigravity needs run.sh to have mounted a logged-in second Antigravity account at \${GEMINI_HOME:-~/.gemini} (antigravity-cli/antigravity-oauth-token missing) -- on the host, that's staged from \${ANTIGRAVITY_SONNET_HOME:-~/.gs-fleet-agy-creds}; see container/generators/gemini.sh's header for the one-time Linux login flow to produce one" >&2
  exit 1
fi

effort_args=()
if [ -n "${GENERATOR_EFFORT:-}" ]; then
  effort_args=(--effort "${GENERATOR_EFFORT}")
fi

python3 -c '
import json, sys
with open(sys.argv[1], "r") as f:
    prompt = f.read()
sys.stdout.write(json.dumps({"event": "user", "message": {"content": prompt}}) + "\n")
' "$PROMPT" | agy \
  --print= \
  --input-format stream-json \
  --output-format stream-json \
  --model "${GENERATOR_MODEL:-claude-sonnet-4-6}" \
  --print-timeout "${GENERATOR_PRINT_TIMEOUT:-25m}" \
  --dangerously-skip-permissions \
  "${effort_args[@]}"

validate_batch "$BATCH"
