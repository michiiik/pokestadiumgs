#!/usr/bin/env bash
# Generator wrapper: Google Antigravity CLI (agentic -- writes $BATCH itself;
# the prompt file already contains the batch JSON schema and output path per
# tools/container_agent.py's BATCH_CONTRACT).
#
# Usage: gemini.sh <prompt-file> <batch-file>
# Install: curl -fsSL https://antigravity.google/cli/install.sh | bash
#   (places the `agy` binary at ~/.local/bin/agy; Linux amd64 build confirmed
#   working, container/Dockerfile installs it under /root/.local/bin)
# Requires: an OAuth login under GEMINI_HOME (default ~/.gemini) --
#   container/run.sh mounts a copy of the host's antigravity-cli/config
#   state there. There is no API-key/env-var auth path for this CLI (unlike
#   codex/qwen): `agy --help` has no login/auth/token-export subcommand, and
#   on macOS the real credential is Keychain-bound (`security dump-keychain`
#   shows service "gemini" / account "antigravity"), not a portable file --
#   so the one-time login has to happen on Linux, where it lands in a plain
#   file instead (confirmed: fresh `curl | bash` install + `agy -p ...` with
#   no prior state prints a Google OAuth URL and a "paste the authorization
#   code" fallback; after completing that once, the credential persists as
#   ~/.gemini/antigravity-cli/antigravity-oauth-token, portable by copy).
# Default model: gemini-3.8-flash-medium (override with GENERATOR_MODEL;
#   `agy models` lists what an account can reach, mirroring codex.sh's
#   "accounts vary" note -- effort is baked into the model id for the
#   gemini-3.x-flash family, e.g. -low/-medium/-high suffixes)
#
# Flags verified locally against `agy --help` (agy 1.1.25):
#   -p, --print               Run a single prompt non-interactively and
#                              print the response. Taking the prompt text as
#                              its own argument (like claude.sh/qwen.sh) is
#                              NOT used here -- see the stdin note below.
#   --input-format stream-json With --print='' (no value -- see below), reads
#                              one NDJSON message per line from stdin instead
#                              and runs a turn for each; requires
#                              --output-format stream-json too. Schema
#                              confirmed empirically (agy's own error text
#                              for a bad line names the required top-level
#                              "event" field; the one that actually ran a
#                              turn was {"event":"user","message":{"content":
#                              "..."}}} -- undocumented in --help, this is
#                              the only working form found).
#   --model                   Model for the current CLI session
#   --effort                  Reasoning effort (low|medium|high) -- optional,
#                              orthogonal to an effort-suffixed model id
#   --output-format            text | json | stream-json
#   --print-timeout            Timeout for print mode wait, default 5m0s --
#                              far shorter than tools/container_agent.py's
#                              own DEFAULT_GENERATOR_TIMEOUT (30m), which
#                              already enforces the real per-call budget.
#                              A real decompilation prompt with probe_one.py
#                              tool round-trips reliably exceeds 5 minutes
#                              (confirmed: two consecutive real attempts each
#                              hit "Error: timeout waiting for response" at
#                              the 5m mark). Raised to match the driver's own
#                              budget so agy's internal timeout is never the
#                              thing that cuts an attempt short.
#   --dangerously-skip-permissions
#                              Auto-approve all tool permission requests
#                              without prompting -- this always runs inside
#                              the already-sandboxed gs-decomp-agent
#                              container, same reasoning as codex.sh's
#                              --dangerously-bypass-approvals-and-sandbox.
#
# Why stdin, not `-p "$(cat "$PROMPT")"`: that passed the whole prompt as one
# argv string, which silently hits Linux's per-argument execve() limit
# (MAX_ARG_STRLEN, 128KiB) well before the overall ARG_MAX -- observed live:
# a real owner's iter0 prompt (98.6KiB) ran fine, but iter1 (129.1KiB, grown
# by retry-history context) failed every attempt with "agy: Argument list
# too long" in well under a second, which container_agent.py's 3-strikes
# rule then reported as an ordinary generator_exhausted (fleetctl read it as
# a rate limit and applied a cooldown) -- not a real capability or quota
# problem, and easy to hit again on any owner whose context grows past
# 128KiB on a retry. Feeding the prompt over stdin as a single stream-json
# NDJSON message has no such argv-length ceiling.
set -eu
set -o pipefail  # so a python3 failure building the stdin message isn't
                 # masked by agy still running (with empty stdin) and
                 # failing on its own, more confusing, terms
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=./_common.sh
. "$SCRIPT_DIR/_common.sh"

PROMPT="$1"
BATCH="$2"

GEMINI_HOME="${GEMINI_HOME:-$HOME/.gemini}"
if [ ! -f "$GEMINI_HOME/antigravity-cli/antigravity-oauth-token" ]; then
  echo "container/generators: gemini needs a logged-in \${GEMINI_HOME:-~/.gemini} (antigravity-cli/antigravity-oauth-token missing) -- see this script's header for the one-time Linux login" >&2
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
  --model "${GENERATOR_MODEL:-gemini-3.8-flash-medium}" \
  --print-timeout "${GENERATOR_PRINT_TIMEOUT:-25m}" \
  --dangerously-skip-permissions \
  "${effort_args[@]}"

validate_batch "$BATCH"
