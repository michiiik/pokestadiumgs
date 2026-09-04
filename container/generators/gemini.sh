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
#                              print the response (takes the prompt text as
#                              its argument, like claude.sh/qwen.sh -- not
#                              codex.sh's stdin style)
#   --model                   Model for the current CLI session
#   --effort                  Reasoning effort (low|medium|high) -- optional,
#                              orthogonal to an effort-suffixed model id
#   --output-format            text | json | stream-json
#   --dangerously-skip-permissions
#                              Auto-approve all tool permission requests
#                              without prompting -- this always runs inside
#                              the already-sandboxed gs-decomp-agent
#                              container, same reasoning as codex.sh's
#                              --dangerously-bypass-approvals-and-sandbox.
set -eu
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

agy \
  -p "$(cat "$PROMPT")" \
  --model "${GENERATOR_MODEL:-gemini-3.8-flash-medium}" \
  --output-format text \
  --dangerously-skip-permissions \
  "${effort_args[@]}"

validate_batch "$BATCH"
